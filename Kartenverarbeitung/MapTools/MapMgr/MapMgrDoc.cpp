#include "stdafx.h"
#include "MapMgr.h"
#include "MapMgrApp.h"

#include "MapMgrDoc.h"
#include "Dialogs.h"
#include "UpdtHint.h"
#include "DlgNewDocument.h"
#include "DlgFileProp.h"
#include "DlgDocErrors.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: mapmgrdoc.cpp 1.1 1996/07/12 10:50:01 andy Exp andy $";
/* $Log: mapmgrdoc.cpp $
// Revision 1.1  1996/07/12  10:50:01  andy
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

#define	DOCUMENT_VERSION1	0x0100
#define	DOCUMENT_VERSION	DOCUMENT_VERSION1

MMGR_ASC_HEADER MMGR_ASC_HEADER::operator=( const MMGR_ASC_HEADER& hdr ) {
	m_nIdentBase = hdr.m_nIdentBase;
	m_nMcodeBase = hdr.m_nMcodeBase;
	m_nVersion = hdr.m_nVersion;
	m_dwTKIdent = hdr.m_dwTKIdent;
	m_dwTKIcode = hdr.m_dwTKIcode;
	m_dwTKMcode = hdr.m_dwTKMcode;
	m_dwTKVcode = hdr.m_dwTKVcode;
	m_mapType = hdr.m_mapType;
	return *this;
}

void MMGR_ASC_HEADER::Init() {
	m_nIdentBase = 16;
	m_nMcodeBase = 10;
	m_nVersion = HDRVER_OLD;
	m_dwTKIdent = 0x99999300;
	m_dwTKIcode = 51200000;
	m_dwTKMcode = 99999301;
	m_dwTKVcode = 99999302;
	m_mapType = MPT_INVALID;
}

/////////////////////////////////////////////////////////////////////////////
// CMapMgrDoc

IMPLEMENT_DYNCREATE(CMapMgrDoc, CDocument)

/////////////////////////////////////////////////////////////////////////////
// CMapMgrDoc construction/destruction

CMapMgrDoc::CMapMgrDoc() {
	// TODO: add one-time construction code here
	HRSRC hRes = ::FindResource( AfxGetResourceHandle(), "HIST_UNCOMPR", "COLORPARAM" );
	if( NULL != hRes ) {
		HGLOBAL	hMem = ::LoadResource( AfxGetResourceHandle(), hRes );
		DWORD	dwSize = ::SizeofResource( AfxGetResourceHandle(), hRes );
		HPBYTE pData = (HPBYTE) ::LockResource( hMem );
		CMemFile memFile;
		memFile.Write( (LPVOID) pData, dwSize );
		memFile.SeekToBegin();

		CArchive	ar( &memFile, CArchive::load );
		WORD v;		// Version
		ar >> v;
		m_listOfFilters.Serialize( ar );

		UnlockResource( hMem );
		FreeResource( hMem );
	}

	DeleteContents();
	m_bStartup = TRUE;
	m_szJump.cx = m_szJump.cy = 100;
}

CMapMgrDoc::~CMapMgrDoc() {
	CString	key;
	CObject	*pObject;
#ifdef _DEBUG
	CRuntimeClass *pRT;
#endif
	POSITION	pos;

	DeleteContents();

	for( pos = m_listOfFilters.GetStartPosition(); NULL != pos; ) {
		m_listOfFilters.GetNextAssoc( pos, key, pObject );
#ifdef _DEBUG
		ASSERT_VALID( pObject );
		pRT = pObject->GetRuntimeClass();
#endif
		delete pObject;
		m_listOfFilters.RemoveKey( key );
	}

	while( !m_listOfEmptyMapInfos.IsEmpty() )
		delete m_listOfEmptyMapInfos.RemoveHead();
}

void CMapMgrDoc::DeleteContents() {
	while( !m_listOfMapInfos.IsEmpty() )
		m_listOfEmptyMapInfos.AddTail( m_listOfMapInfos.RemoveHead() );
	m_strPictDirs.RemoveAll();
	m_ascHdrGlob.Init();
	m_ascHdrMmgr.Init();
	m_pCurrMapInfo = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CMapMgrDoc diagnostics

#ifdef _DEBUG
void CMapMgrDoc::AssertValid() const			{ CDocument::AssertValid(); }
void CMapMgrDoc::Dump(CDumpContext& dc) const	{ CDocument::Dump(dc); }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapMgrDoc commands

CMapInfo* CMapMgrDoc::GetNewMapInfo() {
	if( m_listOfEmptyMapInfos.IsEmpty() )
		return new CMapInfo;
	CMapInfo *pInfo = (CMapInfo*) m_listOfEmptyMapInfos.RemoveHead();
	pInfo->Clear();
	return pInfo;
}

void CMapMgrDoc::ChangeMapIdent( LPCTSTR lpszMapIdent ) {
	m_pCurrMapInfo = NULL;
	for( POSITION pos = m_listOfMapInfos.GetHeadPosition(); NULL != pos; ) {
		m_pCurrMapInfo = m_listOfMapInfos.GetNext( pos );
		if( m_pCurrMapInfo->GetIdent() == lpszMapIdent )
			break;
		else
			m_pCurrMapInfo = NULL;
	}
	UpdateAllViews( NULL, ON_UPDATE_CHGPICTNAME, NULL );
}

void CMapMgrDoc::ResetStartState() {
	m_bStartup = FALSE;
}

void CMapMgrDoc::RecalcGeometry() {
	double	xMin = DBL_MAX;
	double	yMin = DBL_MAX;

	CMapInfo*	pMapInfo;

	for( POSITION pos = m_listOfMapInfos.GetHeadPosition(); NULL != pos; )
	{
		pMapInfo = m_listOfMapInfos.GetNext( pos );
		xMin = __min( pMapInfo->GetBtmLeft().X, xMin );
		yMin = min( pMapInfo->GetBtmLeft().Y, yMin );
	}
	m_ascHdrGlob.m_dwOffsetX = (xMin / 10000) * 10000;
	m_ascHdrGlob.m_dwOffsetY = (yMin / 10000) * 10000;
}

void CMapMgrDoc::ResetItems() {
	m_posEnumItems = m_listOfMapInfos.GetHeadPosition();
}

BOOL CMapMgrDoc::NextItem( LPCTSTR *ppszItem ) {
	if( NULL == m_posEnumItems )
		return FALSE;
	CMapInfo	*pInfo = m_listOfMapInfos.GetNext( m_posEnumItems );
	*ppszItem = pInfo->GetIdent();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMapMgrDoc serialization

void CMapMgrDoc::Serialize(CArchive& ar) {
	if( ar.IsStoring() ) {
		CheckDocument();
		WriteAscFile( ar );
		UpdateAllViews( NULL, ON_UPDATE_POSTSAVING, NULL );
	} else {
		ReadAscFile( ar );
		m_pCurrMapInfo = m_listOfMapInfos.GetCount() > 0 ? m_listOfMapInfos.GetHead() : NULL;
		UpdateAllViews( NULL, ON_UPDATE_POSTLOADING, NULL );
	}
}

BOOL CMapMgrDoc::LoadFromDialog( CDialog *ptr ) {
	ASSERT( MPT_INVALID == m_ascHdrMmgr.m_mapType );
	CDlgNewDocument	*pDlg = (CDlgNewDocument*) ptr;
	ASSERT_KINDOF( CDlgNewDocument, pDlg );
	CString	S, strID, strPath;
	POSITION	pos;
//	m_ascHdrMmgr.m_mapType = (TOPOMAPTYPE) pDlg->m_mapType;	//#fje-
	m_ascHdrMmgr.m_mapType = (TOPOMAPTYPE) mapTypes[pDlg->m_mapType-1].m_mtType;	//#fje+
	// MapType INVALID ist letzter und alle anderen wurden in Reihenfolge hinzugefügt
	m_ascHdrGlob.m_strCoordTrans = GetTypeFromType( (TOPOMAPTYPE) pDlg->m_mapType )->m_strCtf;
	if( !pDlg->m_strMaps.IsEmpty() ) {
		for( int nMap = 0; ::AfxExtractSubString( S, pDlg->m_strMaps, nMap, '\n' ); nMap++ ) {
			::AfxExtractSubString( strID, S, 0, '\t' );
			::AfxExtractSubString( strPath, S, 1, '\t' );
			pos = m_listOfMapInfos.Find( m_pCurrMapInfo, NULL );
			m_listOfMapInfos.InsertAfter( pos, m_pCurrMapInfo = GetNewMapInfo() );
			m_pCurrMapInfo->SetType( m_ascHdrMmgr.m_mapType );
			m_pCurrMapInfo->SetIdent( strID );
			m_pCurrMapInfo->m_strBmpPath = strPath;
			m_pCurrMapInfo->m_gcpArray[0].m_ptPictPoint = GEOPOINT(-1,-1);
			m_pCurrMapInfo->m_gcpArray[1].m_ptPictPoint = GEOPOINT(-1,-1);
			m_pCurrMapInfo->m_gcpArray[2].m_ptPictPoint = GEOPOINT(-1,-1);
			m_pCurrMapInfo->m_gcpArray[3].m_ptPictPoint = GEOPOINT(-1,-1);
		}
		RecalcGeometry();
	}
	m_pCurrMapInfo = m_listOfMapInfos.GetCount() > 0 ? m_listOfMapInfos.GetHead() : NULL;
	SetModifiedFlag();
	UpdateAllViews( NULL, ON_UPDATE_POSTLOADING, NULL );
	UpdateAllViews( NULL, ON_UPDATE_CHGPICTNAME, NULL );
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMapMgrDoc message map

BEGIN_MESSAGE_MAP(CMapMgrDoc, CDocument)
	//{{AFX_MSG_MAP(CMapMgrDoc)
	ON_COMMAND(ID_ADD_MAP, OnAddMap)
	ON_COMMAND(ID_DEL_MAP, OnDelMap)
	ON_UPDATE_COMMAND_UI(ID_DEL_MAP, OnUpdateDelMap)
	ON_COMMAND(ID_MAP_MODIFY_IDENT, OnMapModifyIdent)
	ON_UPDATE_COMMAND_UI(ID_MAP_MODIFY_IDENT, OnUpdateMapModifyIdent)
	ON_COMMAND(ID_MAP_MODIFY_FILENAME, OnMapModifyFilename)
	ON_UPDATE_COMMAND_UI(ID_MAP_MODIFY_FILENAME, OnUpdateMapModifyFilename)
	ON_COMMAND(ID_FILE_PROPERTIES, OnFileProperties)
	ON_UPDATE_COMMAND_UI(ID_FILE_PROPERTIES, OnUpdateFileProperties)
	ON_UPDATE_COMMAND_UI(ID_MAP_PROPERTIES, OnUpdateMapProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapMgrDoc message handlers

void CMapMgrDoc::OnFileProperties()  {
	CDlgFileProp	dlg;
	if( 0 == m_ascHdrGlob.m_dwOffsetX && 0 == m_ascHdrGlob.m_dwOffsetY )
		RecalcGeometry();
	dlg.m_pgGeometry.m_ascHeader = m_ascHdrGlob;
	dlg.m_pgGeometry.m_nMapType = m_ascHdrMmgr.m_mapType - 1;
	dlg.m_pgGeometry.m_mapType = m_ascHdrMmgr.m_mapType;
	dlg.m_pgVisdata.m_ascHeader = m_ascHdrMmgr;
	dlg.m_pgFileOpt.m_nJumpX = m_szJump.cx;
	dlg.m_pgFileOpt.m_nJumpY = m_szJump.cy;
	if( IDOK == dlg.DoModal() ) {
		m_ascHdrGlob = dlg.m_pgGeometry.m_ascHeader;
		m_ascHdrMmgr = dlg.m_pgVisdata.m_ascHeader;
		m_ascHdrMmgr.m_mapType = (TOPOMAPTYPE) ( dlg.m_pgGeometry.m_nMapType + 1 );
		m_szJump.cx = dlg.m_pgFileOpt.m_nJumpX;
		m_szJump.cy = dlg.m_pgFileOpt.m_nJumpY;
	}
}

BOOL CMapMgrDoc::OnNewDocument() {
	if( FALSE == m_bStartup ) {
		CDlgNewDocument	dlg( NULL, 1 );
		if( ID_WIZFINISH == dlg.DoModal() ) {
			if (!CDocument::OnNewDocument())
				return FALSE;
			LoadFromDialog( (CDialog*) &dlg );
		}
	}
	return TRUE;
}

BOOL CMapMgrDoc::OnOpenDocument(LPCTSTR lpszPathName) {
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	m_pCurrMapInfo = m_listOfMapInfos.IsEmpty() ? NULL : m_listOfMapInfos.GetHead();
	return TRUE;
}

void CMapMgrDoc::OnAddMap()  {
	CDlgMapName	dlg;

	ASSERT( NULL == m_pCurrMapInfo || !m_listOfMapInfos.IsEmpty() );

	if( NULL != m_pCurrMapInfo ) {
		ASSERT_VALID( m_pCurrMapInfo );
		dlg.m_strMapIdent = m_pCurrMapInfo->GetIdent();
		dlg.m_mapType = m_ascHdrMmgr.m_mapType;
	} else
		dlg.m_mapType = MPT_UNKNOWN;

	if( IDOK == dlg.DoModal() ) {
		if( dlg.m_strMapIdent.IsEmpty() )
			return;

		BOOL bMapFound = FALSE;
		POSITION	pos;
		CMapInfo	*pMapInfo;
		for( pos = m_listOfMapInfos.GetHeadPosition(); NULL != pos; ) {
			pMapInfo = m_listOfMapInfos.GetNext( pos );
			if( pMapInfo->GetIdent() == dlg.m_strMapIdent ) {
				bMapFound = TRUE;
				break;
			}
		}
		if( !bMapFound ) {
			pos = m_listOfMapInfos.Find( m_pCurrMapInfo, NULL );
			m_listOfMapInfos.InsertAfter( pos, m_pCurrMapInfo = GetNewMapInfo() );
			m_pCurrMapInfo->SetIdent( dlg.m_strMapIdent );
			m_pCurrMapInfo->SetType( m_ascHdrMmgr.m_mapType );
			UpdateAllViews( NULL, ON_UPDATE_ADDPICTNAME, NULL );
			SetModifiedFlag();
		}
	}
}

void CMapMgrDoc::OnDelMap() {
	ASSERT_VALID( m_pCurrMapInfo );
	POSITION pos = m_listOfMapInfos.Find( m_pCurrMapInfo, NULL );

	m_listOfEmptyMapInfos.AddTail( m_pCurrMapInfo );
	m_listOfMapInfos.RemoveAt( pos );
	if( !m_listOfMapInfos.IsEmpty() )
		m_pCurrMapInfo = m_listOfMapInfos.GetHead();
	else
		m_pCurrMapInfo = NULL;
	UpdateAllViews( NULL, ON_UPDATE_DELPICTNAME, NULL );
	SetModifiedFlag();
}

void CMapMgrDoc::OnMapModifyIdent() {
	ASSERT_VALID( m_pCurrMapInfo );
	CDlgMapName	dlg;
	dlg.m_strMapIdent = m_pCurrMapInfo->GetIdent();
	dlg.m_mapType = m_pCurrMapInfo->GetType();
	if( IDOK == dlg.DoModal() ) {
		if( dlg.m_strMapIdent.IsEmpty() )
			return;
		m_pCurrMapInfo->SetIdent( dlg.m_strMapIdent );
		m_pCurrMapInfo->SetType( m_ascHdrMmgr.m_mapType );
		UpdateAllViews( NULL, ON_UPDATE_CHGPICTNAME, NULL );
		SetModifiedFlag();
	}
}

void CMapMgrDoc::OnMapModifyFilename()  {
	ASSERT_VALID( m_pCurrMapInfo );
	CString	S, s1, s2;
	VERIFY( S.LoadString( IDS_PICTTYPE_ALL ) );
	::AfxExtractSubString(s1,S,0,'\n');
	::AfxExtractSubString(s2,S,1,'\n');
	CFileDialog	dlg( TRUE, s1, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, s2 );
	if( IDOK == dlg.DoModal() ) {
		CPath	p( dlg.GetPathName() );
		m_pCurrMapInfo->m_strBmpPath = dlg.GetPathName(); // p.FileName();
		BOOL bHaveFound = FALSE;
		for( int i = 0; i < m_strPictDirs.GetSize(); i++ ) {
			if( m_strPictDirs[i] == p.Dir() ) {
				bHaveFound = TRUE;
				break;
			}
		}
		if( !bHaveFound )
			m_strPictDirs.Add( p.Dir() );
		UpdateAllViews( NULL, ON_UPDATE_CHGPICTNAME, NULL );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CmdUI-Handler

void CMapMgrDoc::OnUpdateAddMap(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable( MPT_INVALID != m_ascHdrMmgr.m_mapType ); }
void CMapMgrDoc::OnUpdateDelMap(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable( NULL != m_pCurrMapInfo ); }
void CMapMgrDoc::OnUpdateMapModifyIdent(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable( NULL != m_pCurrMapInfo ); }
void CMapMgrDoc::OnUpdateMapModifyFilename(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable( NULL != m_pCurrMapInfo ); }
void CMapMgrDoc::OnUpdateFileProperties(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(); }
void CMapMgrDoc::OnUpdateMapProperties(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable( NULL != m_pCurrMapInfo ); }

void CMapMgrDoc::CheckDocument() {
	CStringArray	strErrors, strWarnings;
	CString	S, SForm;
	double	xMin = DBL_MAX;
	double	yMin = DBL_MAX;

	CMapInfo*	pMapInfo;

	for( POSITION pos = m_listOfMapInfos.GetHeadPosition(); NULL != pos; ) {
		pMapInfo = m_listOfMapInfos.GetNext( pos );
		if( 0 == pMapInfo->GetBtmLeft().X ) {
			VERIFY( SForm.LoadString( IDS_INVALID_BTMLEFT ) );
			S.Format( SForm, IDS_INVALID_BTMLEFT, pMapInfo->GetIdent() );
			strErrors.Add( S );
		}
		if( 0 == pMapInfo->GetBtmLeft().Y ) {
			VERIFY( SForm.LoadString( IDS_INVALID_TOPRIGHT ) );
			S.Format( SForm, IDS_INVALID_TOPRIGHT, pMapInfo->GetIdent() );
			strErrors.Add( S );
		}
		if( pMapInfo->m_strBmpPath.IsEmpty() ) {
			VERIFY( SForm.LoadString( IDS_INVALID_PICTPATH ) );
			S.Format( SForm, IDS_INVALID_PICTPATH, pMapInfo->GetIdent() );
			strWarnings.Add( S );
		}
		xMin = min( pMapInfo->GetBtmLeft().X, xMin );
		yMin = min( pMapInfo->GetBtmLeft().Y, yMin );
	}

	if( 0 == m_ascHdrGlob.m_dwOffsetX ) {
		VERIFY( SForm.LoadString( IDS_INVALID_OFFSETX0 ) );
		S.Format( SForm, IDS_INVALID_OFFSETX0 );
		strWarnings.Add( S );
	}
	if( 0 == m_ascHdrGlob.m_dwOffsetY ) {
		VERIFY( SForm.LoadString( IDS_INVALID_OFFSETY0 ) );
		S.Format( SForm, IDS_INVALID_OFFSETY0 );
		strWarnings.Add( S );
	}

	double	diff = m_ascHdrGlob.m_dwOffsetX - (xMin / 10000) * 10000;
	if( diff < 0 ) {
		VERIFY( SForm.LoadString( IDS_INVALID_OFFSETX1 ) );
		S.Format( SForm, IDS_INVALID_OFFSETX1, diff );
		strErrors.Add( S );
	}
	if( fabs( diff ) > 10000 ) {
		VERIFY( SForm.LoadString( IDS_INVALID_OFFSETX2 ) );
		S.Format( SForm, IDS_INVALID_OFFSETX2, diff );
		strWarnings.Add( S );
	}
	diff = m_ascHdrGlob.m_dwOffsetY - (yMin / 10000) * 10000;
	if( diff < 0 ) {
		VERIFY( SForm.LoadString( IDS_INVALID_OFFSETY1 ) );
		S.Format( SForm, IDS_INVALID_OFFSETY1, diff );
		strErrors.Add( S );
	}
	if( fabs( diff ) > 10000 ) {
		VERIFY( SForm.LoadString( IDS_INVALID_OFFSETY2 ) );
		S.Format( SForm, IDS_INVALID_OFFSETY2, diff );
		strWarnings.Add( S );
	}
	if( 0 != strErrors.GetSize( ) || 0 != strWarnings.GetSize() ) {
		CPropertySheet	sheet( IDS_INVALID_DOCUMENT );
		CPgDocErrors	pgErr( IDS_ERRORS );
		CPgDocErrors	pgWarn( IDS_WARNINGS );
		if( 0 != strErrors.GetSize() ) {
			sheet.AddPage( &pgErr );
			for( int i = 0; i < strErrors.GetSize(); ++i )
				pgErr.m_strErrors.Add( strErrors.GetAt( i ) );
		}
		if( 0 != strWarnings.GetSize() ) {
			sheet.AddPage( &pgWarn );
			for( int i = 0; i < strWarnings.GetSize(); ++i )
				pgWarn.m_strErrors.Add( strWarnings.GetAt( i ) );
		}
		sheet.DoModal();
	}
}
