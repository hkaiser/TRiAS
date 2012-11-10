#include "stdafx.h"
#include "MapMgrApp.h"
#include "MapMgrDoc.h"

#include <fstream.h>

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: ascread.cpp 1.1 1996/07/12 10:49:54 andy Exp andy $";
/* $Log: ascread.cpp $
// Revision 1.1  1996/07/12  10:49:54  andy
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

/*
H by MapManager generated DIRIS-File
; MMGR@DIR@h:\Schwerin100000
; MMGR@DIR@h:\Schwerin\N-32-83
D Entry "CoordTransform  " "KRGEOD          "
D Entry "Offset          " "30000.0 190000.0"
D Entry "Scale           " "10000.0 0.0 0.0 10000.0"
D Entry "IdentBase       " "10              "
D Entry "MCodeBase       " "10              "
D Entry "@TopKartMCode   " "99999301"
D Entry "Unique Ident    " "51200000"
F 1 99999300 5
M 51200000 1 A 13
W "TK@AS@N-32-83"
M 99999301 1 A 49
W "N-32-83.bmp 2787 3102 104 97 81 100 95 91 111 93 "
G 39600.00 193200.00
G 41400.00 193200.00
G 41400.00 194400.00
G 39600.00 194400.00
G 39600.00 193200.00
E
*/

class CAscParser : public CAscParserBase {
	CMapMgrDoc	*m_pDoc;
	CMapInfo	*m_pMapInfo;
	int m_nGenericIdent;
public:
	CAscParser( CMapMgrDoc *pDoc, istream& is );
	virtual	BOOL Parse();
protected:
	void OnComment( LPCTSTR lpszComment );
	void OnHeadline( LPCTSTR lpszHeadline );
	void OnProjPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue );
	void OnSysPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue );
	void OnPdbentry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue );

	void OnPoint( DWORD dwIdent, DWORD dwObjectNumber, int nCoords );
	void OnLine( DWORD dwIdent, DWORD dwObjectNumber, int nCoords );
	void OnArea( DWORD dwIdent, DWORD dwObjectNumber, int nCoords );
	void OnBObject( DWORD dwIdent, DWORD dwObjectNumber, int nCoords );

	void OnMcode( DWORD dwMCode, LPCTSTR lpszValue );
	void OnReferenz( DWORD dwMCode, LPCTSTR lpszValue );
	void OnCoord( double X, double Y );

	DECLARE_ASC_PARSERMAP()
};

CAscParser::CAscParser( CMapMgrDoc *pDoc, istream& is ) {
	m_pDoc = pDoc;
	m_nGenericIdent = 1;
	m_pMapInfo = NULL;
	Attach( is );
}

BEGIN_ASC_PARSERMAP(CAscParser,CAscParserBase)
	ON_HEADLINE( OnHeadline )
	ON_COMMENT( OnComment )
	ON_PDB_ENTRY( OnPdbentry )
	ON_PROJPDB_ENTRY( OnProjPdbEntry )
	ON_SYSPDB_ENTRY( OnSysPdbEntry )
	ON_POINT( OnPoint )
	ON_LINE( OnLine )
	ON_AREA( OnArea )
	ON_BOBJECT( OnBObject )
	ON_REFERENZ( OnReferenz )
	ON_MCODE( OnMcode )
	ON_COORD( OnCoord )
END_ASC_PARSERMAP()

static char szMMgr[] = _T("MMGR");
static char szEntryDir[] = _T("DIR");
static char szEntryTyp[] = _T("TYP");
static char szEntryPath[] = _T("PATH");

// ; MMGR@DIR@\Karttiff\Imagine\
// ; MMGR@PATH@spreewald@G:\Karttiff\Imagine\spreewald.bmp

void CAscParser::OnComment( LPCTSTR lpszComment ) {
	CString	S1, S2;
	::AfxExtractSubString( S1, lpszComment, 0, '@' );
	if( szMMgr == S1 ) {
		::AfxExtractSubString( S1, lpszComment, 1, '@' );
		if( szEntryPath == S1 ) {
			::AfxExtractSubString( S1, lpszComment, 2, '@' );
			::AfxExtractSubString( S2, lpszComment, 3, '@' );
			if( NULL != m_pMapInfo && !S2.IsEmpty() && m_pMapInfo->GetIdent() == S1 )
				m_pMapInfo->m_strBmpPath = S2;
		} else if( szEntryDir == S1 ) {
		}
	}
}

void CAscParser::OnHeadline( LPCTSTR lpszHeadline ) {
}

static char szHdrCtrans[] = _T("CoordTransform");
static char szHdrCMerid[] = _T("CoordMeridian");
static char szHdrCWidth[] = _T("CoordStrBreite");
static char szHdrOffset[] = _T("Offset");
static char szHdrScale[] = "Scale";
static char szHdrIdentBase[] = "IdentBase";
static char szHdrMcodeBase[] = "MCodeBase";
static char szHdrTKI[] = "Unique Ident";
static char szHdrTKM[] = "@TopKartMCode";
static char szHdrTKV[] = "@TopKartVCode";

void CAscParser::OnPdbentry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue ) {
	istrstream	is( (char*) lpszEntryValue );
	CString	s1( lpszEntryName ), s2( lpszEntryValue );

	ASSERT_VALID( m_pDoc );

	if( szHdrCtrans == s1 ) {
		m_pDoc->m_ascHdrGlob.m_strCoordTrans = s2;
	}
	else if( szHdrOffset == s1 )
		is 
			>> m_pDoc->m_ascHdrGlob.m_dwOffsetX
			>> m_pDoc->m_ascHdrGlob.m_dwOffsetY
			;
	else if( szHdrScale == s1 )
		is
			>> m_pDoc->m_ascHdrGlob.m_dwScale11
			>> m_pDoc->m_ascHdrGlob.m_dwScale12
			>> m_pDoc->m_ascHdrGlob.m_dwScale21
			>> m_pDoc->m_ascHdrGlob.m_dwScale22
		;
	else if( szHdrIdentBase == s1 )
		is
			>> m_pDoc->m_ascHdrMmgr.m_nIdentBase
			;
	else if( szHdrMcodeBase == s1 )
		is
			>> m_pDoc->m_ascHdrMmgr.m_nMcodeBase
			;
	else if( szHdrTKI == s1 )
		m_pDoc->m_ascHdrMmgr.m_dwTKIcode = strtol( s2, m_pDoc->m_ascHdrMmgr.m_nMcodeBase );
	else if( szHdrTKM == s1 )
		m_pDoc->m_ascHdrMmgr.m_dwTKMcode = strtol( s2, m_pDoc->m_ascHdrMmgr.m_nMcodeBase );
	else if( szHdrTKV == s1 )
		m_pDoc->m_ascHdrMmgr.m_dwTKVcode = strtol( s2, m_pDoc->m_ascHdrMmgr.m_nMcodeBase );
}

void CAscParser::OnProjPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue ) {
	OnPdbentry( lpszEntryName, lpszEntryValue );
}

void CAscParser::OnSysPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue ) {
	OnPdbentry( lpszEntryName, lpszEntryValue );
}

void CAscParser::OnPoint( DWORD dwIdent, DWORD dwObjectNumber, int nCoords ) {
}

void CAscParser::OnLine( DWORD dwIdent, DWORD dwObjectNumber, int nCoords ) {
}

void CAscParser::OnArea( DWORD dwIdent, DWORD dwObjectNumber, int nCoords ) {
	if( dwIdent == m_pDoc->m_ascHdrMmgr.m_dwTKIdent ) {
		ASSERT_VALID( m_pDoc );
		if( NULL != m_pMapInfo && m_pMapInfo->Validate() ) {
			m_pDoc->m_listOfMapInfos.AddTail( m_pMapInfo );
			m_pMapInfo = NULL;
		}
		if( NULL == m_pMapInfo )
			m_pMapInfo = m_pDoc->GetNewMapInfo();
		m_pMapInfo->SetType( m_pDoc->m_ascHdrMmgr.m_mapType );
	}
}

void CAscParser::OnBObject( DWORD dwIdent, DWORD dwObjectNumber, int nCoords ) {
}

void CAscParser::OnReferenz( DWORD dwMCode, LPCTSTR lpszValue ) {
}

////// TKMcode
//M 99999301 1 A 55
//W "spreewald.bmp 4422 2924 100 101 101 101 101 100 100 100"

////// TKIcode
// M 51200000 1 A 20
// W "TK@USRBEGK@spreewald"

void CAscParser::OnMcode( DWORD dwMCode, LPCTSTR lpszValue ) {
	ASSERT_VALID( m_pDoc );
	if( NULL == m_pMapInfo )
		return;
	CString	S1, S2, S3;
	if( dwMCode == m_pDoc->m_ascHdrMmgr.m_dwTKMcode )  {
		::AfxExtractSubString( S1, lpszValue, 0, ' ' );
		if( m_pMapInfo->m_strBmpPath.IsEmpty() )
			m_pMapInfo->m_strBmpPath = S1;
		SIZEL	szPict;

		::AfxExtractSubString( S1, lpszValue, 1, ' ' );
		::AfxExtractSubString( S2, lpszValue, 2, ' ' );
		szPict.cx = atol( S1 );
		szPict.cy = atol( S2 );

		m_pMapInfo->m_sizeOfPict = szPict;

		::AfxExtractSubString( S1, lpszValue, 3, ' ' );
		::AfxExtractSubString( S2, lpszValue, 4, ' ' );
		m_pMapInfo->m_gcpArray[0].m_ptPictPoint.X = S1.IsEmpty() ? -1 : atol( S1 );
		m_pMapInfo->m_gcpArray[0].m_ptPictPoint.Y = szPict.cy - 1 - ( S2.IsEmpty() ? -1 : atol( S2 ) );

		::AfxExtractSubString( S1, lpszValue, 5, ' ' );
		::AfxExtractSubString( S2, lpszValue, 6, ' ' );
		m_pMapInfo->m_gcpArray[1].m_ptPictPoint.X = szPict.cx - 1 - ( S1.IsEmpty() ? -1 : atol( S1 ) );
		m_pMapInfo->m_gcpArray[1].m_ptPictPoint.Y = szPict.cy - 1 - ( S2.IsEmpty() ? -1 : atol( S2 ) );
		
		::AfxExtractSubString( S1, lpszValue, 7, ' ' );
		::AfxExtractSubString( S2, lpszValue, 8, ' ' );
		m_pMapInfo->m_gcpArray[2].m_ptPictPoint.X = szPict.cx - 1 - ( S1.IsEmpty() ? -1 : atol( S1 ) );
		m_pMapInfo->m_gcpArray[2].m_ptPictPoint.Y = S2.IsEmpty() ? -1 : atol( S2 );
		
		::AfxExtractSubString( S1, lpszValue, 9, ' ' );
		::AfxExtractSubString( S2, lpszValue, 10, ' ' );
		m_pMapInfo->m_gcpArray[3].m_ptPictPoint.X = S1.IsEmpty() ? -1 : atol( S1 );
		m_pMapInfo->m_gcpArray[3].m_ptPictPoint.Y = S2.IsEmpty() ? -1 : atol( S2 );
	} else if( dwMCode == m_pDoc->m_ascHdrMmgr.m_dwTKIcode ) {
		::AfxExtractSubString( S1, lpszValue, 0, '@' );
		if( _T("TK") == S1 ) {
			::AfxExtractSubString( S2, lpszValue, 1, '@' );
			::AfxExtractSubString( S3, lpszValue, 2, '@' );
			if( S3.IsEmpty() )
				S3.Format( "%08d", m_nGenericIdent++ );
			if( NULL != m_pMapInfo )
				m_pMapInfo->SetIdent( S3 );
			if( MPT_INVALID == m_pDoc->m_ascHdrMmgr.m_mapType ) {
				const MAPTYPE	*pMapType = GetTypeFromName( S2 );
				if( NULL != pMapType && MPT_INVALID != pMapType->m_mtType )
					m_pDoc->m_ascHdrMmgr.m_mapType = pMapType->m_mtType;
			}
		}
	}
}

void CAscParser::OnCoord( double X, double Y ) {
	if( NULL != m_pMapInfo ) {
		GEOPOINT	gp;
		gp.X = X;
		gp.Y = Y;
		gp.Z = 0;
		m_pMapInfo->AddPoint( gp );
	}
}

BOOL CAscParser::Parse() {
	if( CAscParserBase::Parse() ) {
		if( NULL != m_pMapInfo && m_pMapInfo->Validate() ) {
			m_pDoc->m_listOfMapInfos.AddTail( m_pMapInfo );
			m_pMapInfo = NULL;
		}
		return TRUE;
	}
	return FALSE;
}

void CMapMgrDoc::ReadAscFile( CArchive& ar ) {
	ifstream	ifs( ar.GetFile()->GetFilePath() );
	CAscParser	parser( this, ifs );
	if( FALSE == parser.Parse() )
		DeleteContents();
	else {
		CMapInfo	*pInfo;
		for( POSITION pos = m_listOfMapInfos.GetHeadPosition(); NULL != pos; ) {
			pInfo = m_listOfMapInfos.GetNext( pos );
			pInfo->SetType( m_ascHdrMmgr.m_mapType );
		}
	}
}
