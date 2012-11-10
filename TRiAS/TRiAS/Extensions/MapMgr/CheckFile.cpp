#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

//#include "libdgn/libdgn.h"

static void makeEditText( CString const& strSrc, CString& strDst ) {
	TCHAR	c;
	for( int i = 0; i < strSrc.GetLength(); i++ ) {
		c = strSrc[i];
		if( _T('\n') == c )
			strDst += _T('\r');
		strDst += c;
	}
}

static bool GetPictInfo( CPicture const *&p, long &X0, long &Y0, long &X1, long &Y1 ) {
	TAG	tag256, tag257;
	X0 = Y0 = X1 = Y1 = 0;
	if( p->GetTag( 256, tag256 ) && p->GetTag( 257, tag257 ) ) {
		X1 = tag256.ulVal();
		Y1 = tag257.ulVal();
		return true;
	}
	return false;
}

static bool GetArcInfo( CFile& rFile, CString& rString ) {
	return true;
}

typedef struct IGTAG33918 {
	short	v[4];
	double	dblVal[16];
} IGTAG33918;

static bool GetIntergraph( CFile& rFile, CString& rString, TOPOMAP& theMap ) {
	CRuntimeClass	*pRT;
	bool	bRet = false;
	if( NULL == ( pRT = GetPictureType( &rFile ) ) );
	CPicture	*pPict = (CPicture*) pRT->CreateObject();
	VERIFY( pPict->Attach( &rFile ) && pPict->ReadHeader() );
	long X0, Y0, X1, Y1;
	TAG	tag270;
	TAG tag33918;
	GetPictInfo( pPict, X0, Y0, X1, Y1);
	if( pPict->GetTag( 33918, tag33918 ) ) {
		long	nItems = tag33918.Count();
		if( ( 4 + 64 ) == nItems ) {
			IGTAG33918*	pData = (IGTAG33918*) tag33918.pVal();
			_ASSERTE(sizeof(theMap.m_transform.m_matrix) == sizeof(pData->dblVal) );
			memcpy( theMap.m_transform.m_matrix, pData->dblVal, sizeof(theMap.m_transform.m_matrix) );
			//////////////////////////////////////////////////////////////////
			// Karteninformation basteln
			theMap.m_sizeOfPicture.cx = X1;
			theMap.m_sizeOfPicture.cy = Y1;
			// GCP's: LinksUnten, RechtsUnten, RechtsOben, LinksOben
			theMap.m_listOfGCP.erase( theMap.m_listOfGCP.begin(), theMap.m_listOfGCP.end() );
			theMap.m_listOfGCP.push_back(  GCP( GEOPOINT( ),  GEOPOINT(  0, Y1, 0 ) ) );
			theMap.m_listOfGCP.push_back(  GCP( GEOPOINT( ),  GEOPOINT( X1, Y1, 0 ) ) );
			theMap.m_listOfGCP.push_back(  GCP( GEOPOINT( ),  GEOPOINT( X1,  0, 0 ) ) );
			theMap.m_listOfGCP.push_back(  GCP( GEOPOINT( ),  GEOPOINT(  0,  0, 0 ) ) );
			bRet = true;
		}
	}
	delete pPict;
	return bRet;
}

static bool GetReferenced( CFile& rFile, CString& rString, TOPOMAP& theMap ) {
	CRuntimeClass	*pRT;
	if( NULL == ( pRT = GetPictureType( &rFile ) ) );
	CPicture	*pPict = (CPicture*) pRT->CreateObject();
	VERIFY( pPict->Attach( &rFile ) && pPict->ReadHeader() );
	long X0, Y0, X1, Y1;
	TAG	tag270;
	GetPictInfo( pPict, X0, Y0, X1, Y1);
	if( pPict->GetTag( 270, tag270 ) ) {
		rString = tag270.strVal();
	}
	delete pPict;
	//////////////////////////////////////////////////////////////////
	// Karteninformation basteln
	theMap.m_sizeOfPicture.cx = X1;
	theMap.m_sizeOfPicture.cy = Y1;
	// GCP's: LinksUnten, RechtsUnten, RechtsOben, LinksOben
	GEOPOINT	LO, RU;
	LO.X = 0; LO.Y = 0;
	RU.X = 0; RU.Y = 0;
	theMap.m_listOfGCP.erase( theMap.m_listOfGCP.begin(), theMap.m_listOfGCP.end() );
	theMap.m_listOfGCP.push_back(  GCP( GEOPOINT( LO.X, RU.Y, 0 ),  GEOPOINT(  0, Y1, 0 ) ) );
	theMap.m_listOfGCP.push_back(  GCP( GEOPOINT( RU.X, RU.Y, 0 ),  GEOPOINT( X1, Y1, 0 ) ) );
	theMap.m_listOfGCP.push_back(  GCP( GEOPOINT( RU.X, LO.Y, 0 ),  GEOPOINT( X1,  0, 0 ) ) );
	theMap.m_listOfGCP.push_back(  GCP( GEOPOINT( LO.X, LO.Y, 0 ),  GEOPOINT(  0,  0, 0 ) ) );
	return true;
}

bool CMapImportDlg::CheckInfile( ) {
	CString	strDescr;
	CFile	file( m_strSrcMap, CFile::modeRead | CFile::typeBinary );
//	m_TDI.m_strSrcDescr = _T("");
//	infoMap::iterator	i = m_infoMap.find( m_TDI.m_strMapType );
	bool	bRet = false;
//	switch( (*i).second.type ) {
	switch(0) {
	case 0: {
		}
		break;
	case 1 : {
			if( GetReferenced( file, strDescr, m_mapInfo ) ) {
				CPath	pathOfSrc( m_strSrcMap );
				m_mapInfo.m_strName = (LPCTSTR) pathOfSrc.Prefix();
				m_mapInfo.m_strIdent.Format( _T("TK@USRBEGK@%s"), (LPCTSTR) pathOfSrc.Prefix() );
				m_mapInfo.m_csType = tcsCS_Projected;
				m_mapInfo.m_csDatum = tcsGD_DeutscheHauptdreiecksnetz;
				m_mapInfo.m_csMeridian = tcsPM_Greenwich;
				m_mapInfo.m_csProjection = tcsPA_GaussKrueger;
				bRet = true;
			}
		}
		break;
	case 2 : {
			if( GetIntergraph( file, strDescr, m_mapInfo ) ) {
				CPath	pathOfSrc( m_strSrcMap );
				m_mapInfo.m_strName = (LPCTSTR) pathOfSrc.Prefix();
				m_mapInfo.m_strIdent.Format( _T("TK@USRBEGK@%s"), (LPCTSTR) pathOfSrc.Prefix() );
				m_mapInfo.m_csType = tcsCS_Projected;
				m_mapInfo.m_csDatum = tcsGD_DeutscheHauptdreiecksnetz;
				m_mapInfo.m_csMeridian = tcsPM_Greenwich;
				m_mapInfo.m_csProjection = tcsPA_GaussKrueger;
				bRet = true;
			}
		}
		break;
	}
	if( true == bRet ) {
		CPath	pathOfSrc( m_strSrcMap );
		CPath	pathOfDst;
//		pathOfDst.Dir( m_TDI.m_strDstDir );
//		pathOfDst.FileName( pathOfSrc.FileName() );
		m_mapInfo.m_strSrcPath = pathOfSrc.Path();
		m_mapInfo.m_strDstPath = pathOfDst.Path();
	}
	return bRet;
}

bool CMapImportDlg::Finish( ) {
	bool bRet = true;
	return bRet;
}
