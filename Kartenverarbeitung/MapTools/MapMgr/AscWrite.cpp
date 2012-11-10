#include "stdafx.h"
#include "MapMgrApp.h"

#include "MapMgrDoc.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: ascexp.cpp 1.1 1996/07/12 10:49:53 andy Exp andy $";
/* $Log: ascexp.cpp $
// Revision 1.1  1996/07/12  10:49:53  andy
// initial version
//
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#pragma warning( disable : 4270 )

/////////////////////////////////////////////////////////////////////////////
// ASC - Export
// für den Debugger:
// *(*(((*(ios*)(&(*(ostream*)(&os))))).bp))._base

void CMapMgrDoc::WriteAscFile( CArchive& ar )
{
	strstream	os;
	WriteAscHeader( os, &m_ascHdrGlob );

	os << ASCHR( "IdentBase", m_ascHdrMmgr.m_nIdentBase );
	os << ASCHR( "MCodeBase", m_ascHdrMmgr.m_nMcodeBase );
	os << ASCHR( "@TopKartMCode", m_ascHdrMmgr.m_dwTKMcode, m_ascHdrMmgr.m_nMcodeBase );
	os << ASCHR( "@TopKartVCode", m_ascHdrMmgr.m_dwTKVcode, m_ascHdrMmgr.m_nMcodeBase );

	CString	strComment( "MMGR@DIR@" );
	for( int i = 0; i < m_strPictDirs.GetSize(); i++ )
		os << ASCTR( strComment + m_strPictDirs[i] );

	int nRec = 1;
	CMapInfo	*pMapInfo;
	for( POSITION pos = m_listOfMapInfos.GetHeadPosition(); NULL != pos; ) {
		pMapInfo = m_listOfMapInfos.GetNext( pos );
		switch( pMapInfo->GetType() ) {
		case MPT_AS_L:
		case MPT_N_L:
			{
				CFileFind f;
				CString strPath(pMapInfo->m_strBmpPath);
				BOOL tMore;
				strPath = strPath.Mid(0,strPath.GetLength()-6) + "??" + strPath.Mid(strPath.GetLength()-4);
				if( f.FindFile( strPath ) ) {
					do {
						tMore =	f.FindNextFile();
						pMapInfo->m_strBmpPath = f.GetFilePath();
						WriteAscRecord( os, nRec++, pMapInfo );
					} while( tMore );
				}
				f.Close();
			}
			break;
		default:
			WriteAscRecord( os, nRec++, pMapInfo );
		}
	}

	os << 'E' << endl << ends;
	CString	strOutput;
	char c;
	os.seekg(0);
	os.unsetf( ios::skipws );
	for( ; !os.fail(); ) {
		os >> c;
		if( '\n' == c )
			strOutput += '\r';
		strOutput += c;
	}
	ar.WriteString( strOutput );
}

void CMapMgrDoc::WriteAscRecord( iostream& os, int nRec, CMapInfo *pMapInfo ) {
	GCP	GCP;
	int		iBase = m_ascHdrMmgr.m_nIdentBase;
	int		mBase = m_ascHdrMmgr.m_nMcodeBase;
	DWORD	iDent = m_ascHdrMmgr.m_dwTKIdent;
	DWORD	mCode = m_ascHdrMmgr.m_dwTKMcode;
	
	/////////////////////////////////////////////////////////////////////////
	// Angaben überprüfen

	ASSERT_VALID( pMapInfo );
	ASSERT( pMapInfo->m_gcpArray.GetSize() > 3 );	// mindestens die ersten vier Punkte

	if( pMapInfo->GetIdent().IsEmpty() )
		return;
	if( pMapInfo->m_strBmpPath.IsEmpty() )
		return;

	/////////////////////////////////////////////////////////////////////////
	// scheint alles ok zu sein... kann losgehen

	GEOPOINT	ptMap = pMapInfo->GetBtmLeft();
	GEOSIZE	szMap = pMapInfo->GetSize();
	SIZE	szPict = pMapInfo->m_sizeOfPict;
	long	scale = pMapInfo->GetScale();

	/////////////////////////////////////////////////////////////////////////
	// Ident schreiben

	os << ASCIR( iDent, nRec, 5, iBase );

	/////////////////////////////////////////////////////////////////////////
	// Merkmalswert Kartenidentifikator
	{
		CString	S;
		const MAPTYPE	*pMapType = GetTypeFromType( pMapInfo->GetType() );

		CString strMapIdent(pMapInfo->GetIdent());
		CString strLayer;
		if(">" == strMapIdent.Right(1) ) {	// für Layerkarten
			strMapIdent = strMapIdent.Mid(1,strMapIdent.GetLength()-2);
			strLayer = pMapInfo->m_strBmpPath;
			strLayer = strLayer.Mid(strLayer.GetLength()-6,2);
		}
		strMapIdent.MakeUpper();
		strLayer.MakeLower();

		S = "TK@";
		S += NULL != pMapType ? pMapType->m_strShortName : "<>";
		S += '@';
//		S += pMapInfo->GetIdent();
		S += strMapIdent + strLayer;
		os << ASCMR( m_ascHdrMmgr.m_dwTKIcode, S, mBase );

//		os << ASCMR( 99999303, pMapInfo->GetIdent(), mBase );
		os << ASCMR( 99999303, strMapIdent, mBase );

		S = "MMGR@PATH@";
		S += pMapInfo->GetIdent();
		S += '@';
		S += pMapInfo->m_strBmpPath;
		os << ASCTR( S );
	}

	/////////////////////////////////////////////////////////////////////////
	// Merkmalswert Visualisierungsinformationen
	{
		ostrstream	ostr;
		CPath	p( pMapInfo->m_strBmpPath );

		ostr << p.FileName();
		ostr << ' ' << pMapInfo->m_sizeOfPict.cx << ' ' << pMapInfo->m_sizeOfPict.cy;

		GCP = pMapInfo->m_gcpArray.GetAt( 0 );
			ostr << ' ' << ( GCP.m_ptPictPoint.X );
			ostr << ' ' << ( szPict.cy - 1 - GCP.m_ptPictPoint.Y );
		GCP = pMapInfo->m_gcpArray.GetAt( 1 );
			ostr << ' ' << ( szPict.cx - 1 - GCP.m_ptPictPoint.X );
			ostr << ' ' << ( szPict.cy - 1 - GCP.m_ptPictPoint.Y );
		GCP = pMapInfo->m_gcpArray.GetAt( 2 );
			ostr << ' ' << ( szPict.cx - 1 - GCP.m_ptPictPoint.X );
			ostr << ' ' << ( GCP.m_ptPictPoint.Y );
		GCP = pMapInfo->m_gcpArray.GetAt( 3 );
			ostr << ' ' << ( GCP.m_ptPictPoint.X );
			ostr << ' ' << ( GCP.m_ptPictPoint.Y );

		for( int i = 4; i < pMapInfo->m_gcpArray.GetSize(); i++ )
		{
			ostr << ' ' << pMapInfo->m_gcpArray[i].m_ptGeoCoord.X;
			ostr << ' ' << pMapInfo->m_gcpArray[i].m_ptGeoCoord.Y;
			ostr << ' ' << pMapInfo->m_gcpArray[i].m_ptPictPoint.X;
			ostr << ' ' << pMapInfo->m_gcpArray[i].m_ptPictPoint.Y;
		}
	/*
		// korrektes Rausschreiben von langen MCode-Werten testen
		ostr << " Und hier kommt noch ein sehr sehr langer String, der hinten rangeschrieben wird.";
		ostr << " Und hier kommt noch ein sehr sehr langer String, der hinten rangeschrieben wird.";
		ostr << " Und hier kommt noch ein sehr sehr langer String, der hinten rangeschrieben wird.";
		ostr << " Und hier kommt noch ein sehr sehr langer String, der hinten rangeschrieben wird.";
		ostr << " Und hier kommt noch ein sehr sehr langer String, der hinten rangeschrieben wird.";
	*/
		ostr << ends;

		os << ASCMR( mCode, ostr.str(), mBase );
	}

	/////////////////////////////////////////////////////////////////////////
	// Koordinaten

	os.flags( ( os.flags() & ~ios::scientific ) | ios::fixed );
	os.precision( 5 );
	os << ASCCR( ptMap.X, ptMap.Y );
	os << ASCCR( ptMap.X + szMap.dX, ptMap.Y );
	os << ASCCR( ptMap.X + szMap.dX, ptMap.Y + szMap.dY );
	os << ASCCR( ptMap.X, ptMap.Y + szMap.dY );
	os << ASCCR( ptMap.X, ptMap.Y );
}
