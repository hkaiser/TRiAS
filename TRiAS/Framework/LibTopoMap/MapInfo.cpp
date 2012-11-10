#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

static BOOL ParseMap( LPCTSTR lpszMapIdent, TOPOMAPTYPE mapType, GEOPOINT& pt, GEOSIZE& sz, long& scale ) {
	CString strMapIdent(lpszMapIdent);
	if(">" == strMapIdent.Right(1) )
		strMapIdent = strMapIdent.Mid(1,strMapIdent.GetLength()-2);
	switch( mapType ) {
	case MPT_AS :
	case MPT_AS_L :
		ParserForASMap::ParseMapName( strMapIdent, pt, sz, scale );
		break;
	case MPT_AV :
		ParserForAVMap::ParseMapName( strMapIdent, pt, sz, scale );
		break;
	case MPT_N :
	case MPT_N_L :
		ParserForNMap::ParseMapName( strMapIdent, pt, sz, scale );
		break;
	case MPT_SOE1 :

	default :
		pt = GEOPOINT();
		sz = GEOSIZE();
		scale = 1;
		return FALSE;
	}
	return TRUE;
}

CMapInfo::~CMapInfo() {
	m_gcpArray.RemoveAll();
}

void CMapInfo::Clear() {
	m_mapType = MPT_UNKNOWN;
	m_strMapIdent.Empty();
	m_btmleftOfMap = GEOPOINT();
	m_sizeOfMap = GEOSIZE();
	m_scale = -1;

	m_strTifPath.Empty();
	m_strBmpPath.Empty();
	m_sizeOfPict.cx = m_sizeOfPict.cy = 0;
	m_geoPoints.SetSize( 0 );
	m_gcpArray.SetSize( 4 );
	for( int i = 0; i < m_gcpArray.GetSize(); i++ )
		m_gcpArray[i].Clear();
}

CMapInfo& CMapInfo::operator=( CMapInfo& rI ) {
	m_mapType = rI.m_mapType;
	m_strMapIdent = rI.m_strMapIdent;
	m_btmleftOfMap = rI.m_btmleftOfMap;
	m_sizeOfMap = rI.m_sizeOfMap;
	m_scale = rI.m_scale;
	m_strBmpPath = rI.m_strBmpPath;
	m_sizeOfPict = rI.m_sizeOfPict;
	m_gcpArray.SetSize( 0, 4 );
	for( int i = 0; i < rI.m_gcpArray.GetSize(); i++ )
		m_gcpArray.Add( rI.m_gcpArray[i] );
	return *this;
}

BOOL CMapInfo::SetCoord( const GEOPOINT& ptBtmLeft, const GEOPOINT& ptTopRight ) {
	m_btmleftOfMap = ptBtmLeft;
	m_sizeOfMap.dX = ptTopRight.X - ptBtmLeft.X;
	m_sizeOfMap.dY = ptTopRight.Y - ptBtmLeft.Y;
	m_scale = 1;
		m_gcpArray[0].m_ptGeoCoord.X = ptBtmLeft.X;
		m_gcpArray[0].m_ptGeoCoord.Y = ptBtmLeft.Y;
		m_gcpArray[1].m_ptGeoCoord.X = ptTopRight.X;
		m_gcpArray[1].m_ptGeoCoord.Y = ptBtmLeft.Y;
		m_gcpArray[2].m_ptGeoCoord.X = ptTopRight.X;
		m_gcpArray[2].m_ptGeoCoord.Y = ptTopRight.Y;
		m_gcpArray[3].m_ptGeoCoord.X = ptBtmLeft.X;
		m_gcpArray[3].m_ptGeoCoord.Y = ptTopRight.Y;
	return TRUE;
}

BOOL	CMapInfo::Validate( ) {
	if( m_geoPoints.GetSize() != 5 )
		return FALSE;
	m_btmleftOfMap.X = m_geoPoints[0].X;
	m_btmleftOfMap.Y = m_geoPoints[0].Y;
	m_sizeOfMap.dX = ( m_geoPoints[2].X - m_geoPoints[0].X );
	m_sizeOfMap.dY = ( m_geoPoints[2].Y - m_geoPoints[0].Y );

	m_gcpArray[0].m_ptGeoCoord.X = m_geoPoints[0].X;
	m_gcpArray[0].m_ptGeoCoord.Y = m_geoPoints[0].Y;
	m_gcpArray[1].m_ptGeoCoord.X = m_geoPoints[1].X;
	m_gcpArray[1].m_ptGeoCoord.Y = m_geoPoints[1].Y;
	m_gcpArray[2].m_ptGeoCoord.X = m_geoPoints[2].X;
	m_gcpArray[2].m_ptGeoCoord.Y = m_geoPoints[2].Y;
	m_gcpArray[3].m_ptGeoCoord.X = m_geoPoints[3].X;
	m_gcpArray[3].m_ptGeoCoord.Y = m_geoPoints[3].Y;
	
	if( m_sizeOfMap.dX > 0 && m_sizeOfMap.dY > 0 )
		return TRUE;
	return FALSE;
}

BOOL CMapInfo::SetType( TOPOMAPTYPE mapType ) {
	GEOPOINT	pt;
	GEOSIZE	sz;
	long	scale;
	m_mapType = mapType;
	if( !m_strMapIdent.IsEmpty() && ParseMap( m_strMapIdent, mapType, pt, sz, scale ) ) {
		m_btmleftOfMap = pt;
		m_sizeOfMap = sz;
		m_scale = scale;
		m_gcpArray[0].m_ptGeoCoord.X= pt.X;
		m_gcpArray[0].m_ptGeoCoord.Y = pt.Y;
		m_gcpArray[1].m_ptGeoCoord.X = pt.X + sz.dX;
		m_gcpArray[1].m_ptGeoCoord.Y = pt.Y;
		m_gcpArray[2].m_ptGeoCoord.X = pt.X + sz.dX;
		m_gcpArray[2].m_ptGeoCoord.Y = pt.Y + sz.dY;
		m_gcpArray[3].m_ptGeoCoord.X = pt.X;
		m_gcpArray[3].m_ptGeoCoord.Y = pt.Y + sz.dY;
		return TRUE;
	}
	return FALSE;
}

BOOL CMapInfo::SetIdent( LPCTSTR lpszMapIdent ) {
	GEOPOINT	pt;
	GEOSIZE	sz;
	long	scale;
	m_strMapIdent = lpszMapIdent;
	if( MPT_INVALID != m_mapType && ParseMap( lpszMapIdent, m_mapType, pt, sz, scale ) ) {
		m_btmleftOfMap = pt;
		m_sizeOfMap = sz;
		m_scale = scale;
		m_gcpArray[0].m_ptGeoCoord.X = pt.X;
		m_gcpArray[0].m_ptGeoCoord.Y = pt.Y;
		m_gcpArray[1].m_ptGeoCoord.X = pt.X + sz.dX;
		m_gcpArray[1].m_ptGeoCoord.Y = pt.Y;
		m_gcpArray[2].m_ptGeoCoord.X = pt.X + sz.dX;
		m_gcpArray[2].m_ptGeoCoord.Y = pt.Y + sz.dY;
		m_gcpArray[3].m_ptGeoCoord.X = pt.X;
		m_gcpArray[3].m_ptGeoCoord.Y = pt.Y + sz.dY;
		return TRUE;
	}
	return FALSE;
}
