// DlgNewDocument.cpp : implementation file
//

#include "stdafx.h"
#include "mapmgr.h"
#include "DlgNewDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPgDocStart property page

IMPLEMENT_DYNCREATE(CPgDocStart, CPropertyPage)

CPgDocStart::CPgDocStart() : CPropertyPage(CPgDocStart::IDD) {
	//{{AFX_DATA_INIT(CPgDocStart)
	m_nStartAction = -1;
	//}}AFX_DATA_INIT
}

CPgDocStart::~CPgDocStart() {
}

void CPgDocStart::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgDocStart)
	DDX_Radio(pDX, IDC_BTN_MAPOTHER, m_nStartAction);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPgDocStart, CPropertyPage)
	//{{AFX_MSG_MAP(CPgDocStart)
	ON_BN_CLICKED(IDC_BTN_MAPLAST, OnBtnMaplast)
	ON_BN_CLICKED(IDC_BTN_MAPOTHER, OnBtnMapother)
	ON_BN_CLICKED(IDC_BTN_PRJNEW, OnBtnPrjnew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgDocStart message handlers

BOOL CPgDocStart::OnInitDialog()  {
	CPropertyPage::OnInitDialog();
	m_nStartAction = 1;
	UpdateData( FALSE );
	return TRUE;
}

void CPgDocStart::OnBtnMaplast() 
	{	UpdateData(); }

void CPgDocStart::OnBtnMapother() 
	{	UpdateData(); }

void CPgDocStart::OnBtnPrjnew() 
	{	UpdateData(); }

BOOL CPgDocStart::OnSetActive()  {
	CPropertySheet *pSheet = (CPropertySheet*) GetParent();
	pSheet->SetWizardButtons( PSWIZB_NEXT );
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// CPgMapType property page

IMPLEMENT_DYNCREATE(CPgMapType, CPropertyPage)

CPgMapType::CPgMapType() : CPropertyPage(CPgMapType::IDD) {
	//{{AFX_DATA_INIT(CPgMapType)
	m_nMapType = -1;
	m_bSrchMaps = FALSE;
	m_strSearchMask = _T("");
	m_strMapItem = _T("");
	//}}AFX_DATA_INIT
}

CPgMapType::~CPgMapType() {
}

void CPgMapType::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgMapType)
	DDX_Control(pDX, IDC_EDIT_SEARCHMASK, m_editSearchMask);
	DDX_Control(pDX, IDC_SEARCHMAPS, m_chkSrchMaps);
	DDX_Control(pDX, IDC_DROP_MAPTYPESTYPES, m_listMapTypes);
	DDX_Control(pDX, IDC_LIST_MAPDIRS, m_listMapDirs);
	DDX_CBIndex(pDX, IDC_DROP_MAPTYPESTYPES, m_nMapType);
	DDX_Check(pDX, IDC_SEARCHMAPS, m_bSrchMaps);
	DDX_Text(pDX, IDC_EDIT_SEARCHMASK, m_strSearchMask);
	DDX_LBString(pDX, IDC_LIST_MAPDIRS, m_strMapItem);
	//}}AFX_DATA_MAP
	if( pDX->m_bSaveAndValidate ) {
		const MAPTYPE	*pType = GetTypeFromType( (TOPOMAPTYPE) ( m_listMapTypes.GetCurSel() + 1 ) );
		m_chkSrchMaps.ShowWindow( NULL == pType || MPT_UNKNOWN == pType->m_mtType ? SW_HIDE : SW_SHOW );	// || FALSE == pType->m_bHaveParser 
		m_editSearchMask.ShowWindow( NULL == pType || MPT_UNKNOWN == pType->m_mtType || TRUE == pType->m_bHaveParser ? SW_HIDE : SW_SHOW );
		if( 0 == m_listMapDirs.GetCount() ) {
//			m_chkSrchMaps.SetCheck( 0 );
// KK000605
			m_chkSrchMaps.SetCheck( 1 );
			m_chkSrchMaps.EnableWindow( FALSE );
			m_editSearchMask.EnableWindow( FALSE );
		} else {
// KK000605
			m_chkSrchMaps.SetCheck( 1 );
			m_chkSrchMaps.EnableWindow( FALSE );
			m_editSearchMask.EnableWindow( FALSE );
//--------------------------------------------
//			m_chkSrchMaps.EnableWindow( TRUE );
//			m_editSearchMask.EnableWindow( TRUE );
		}
	}
}

BEGIN_MESSAGE_MAP(CPgMapType, CPropertyPage)
	//{{AFX_MSG_MAP(CPgMapType)
	ON_BN_CLICKED(IDC_SEARCHMAPS, OnSearchmaps)
	ON_CBN_SELCHANGE(IDC_DROP_MAPTYPESTYPES, OnSelchangeDropMaptypestypes)
	//}}AFX_MSG_MAP
	ON_LBN_ADDITEM( IDC_LIST_MAPDIRS, OnAddDir )
	ON_LBN_DELITEM( IDC_LIST_MAPDIRS, OnDelDir )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgMapType message handlers

BOOL CPgMapType::OnInitDialog()  {
	CPropertyPage::OnInitDialog();
	CString	S;
	
	for( MAPTYPE* pType = mapTypes; MPT_INVALID != pType->m_mtType; pType++ )
		m_listMapTypes.AddString( pType->m_strLongName );
	m_nMapType = 0;
	m_bSrchMaps = FALSE;
	m_listMapDirs.SetWindowText( "Suchverzeichnisse" );
	UpdateData( FALSE );
	return TRUE;
}

BOOL CPgMapType::OnSetActive()  {
	CPropertySheet *pSheet = (CPropertySheet*) GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );
	return CPropertyPage::OnSetActive();
}

void CPgMapType::OnAddDir() {
	CDirSelectDialog	dlg(this);
	if( IDOK == dlg.DoModal() ) {
		CString strDir = dlg.m_strDirectory;
		int idx = m_listMapDirs.GetCurSel();
		m_listMapDirs.InsertString( idx + 1, strDir );
		m_listMapDirs.SetCurSel( idx + 1 );
	}
	UpdateData( );	
}

void CPgMapType::OnDelDir()
	{ UpdateData(); }

void CPgMapType::OnSearchmaps() 
	{ UpdateData( ); }

void CPgMapType::OnSelchangeDropMaptypestypes() 
	{ UpdateData( ); }

/////////////////////////////////////////////////////////////////////////////
// CPgDoSearch property page

IMPLEMENT_DYNCREATE(CPgDoSearch, CPropertyPage)

CPgDoSearch::CPgDoSearch() : CPropertyPage(CPgDoSearch::IDD) {
	//{{AFX_DATA_INIT(CPgDoSearch)
	//}}AFX_DATA_INIT
	m_pSrchThread = NULL;
}

CPgDoSearch::~CPgDoSearch() {
}

void CPgDoSearch::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgDoSearch)
	DDX_Control(pDX, IDC_LIST_MAPS, m_listMaps);
	//}}AFX_DATA_MAP
}

#define	WM_MYTHREAD	(WM_USER + 1)

#define	THREAD_ENTERDIR		(WM_USER + 2)
#define THREAD_FILEFOUND	(WM_USER + 3)
#define	THREAD_END			(WM_USER + 4)

BEGIN_MESSAGE_MAP(CPgDoSearch, CPropertyPage)
	//{{AFX_MSG_MAP(CPgDoSearch)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_MYTHREAD, OnThreadMessage )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgDoSearch message handlers

typedef struct tagSEARCHPARAM {
	HWND		m_hWnd;
	TOPOMAPTYPE	m_mapType;
	LPCTSTR		m_strSearchDirs;
	LPCTSTR		m_strSearchMask;
} SEARCHPARAM;

static void ScanDir( LPCTSTR lpszDir, TOPOMAPTYPE mapType, LPCTSTR lpszMask, HWND hWnd ) {
	CString	*pStr = new CString( lpszDir );
	::SendMessage( hWnd, WM_MYTHREAD, THREAD_ENTERDIR, (LPARAM) pStr );

	CFileFind	f;
	CFileFind	findLayer;
	BOOL tMore;
	CString	strPath( lpszDir );
	CString strFileExtension;
	CString strLayer;

	strPath += "/";
	switch( mapType ) {
	case MPT_AS : 
	case MPT_AS_L : 
	case MPT_AV : 
	case MPT_N :
	case MPT_N_L :
		strPath += _T("*.*");
		break;
	default :
		strPath += NULL == lpszMask || '\0' == *lpszMask ? _T("*.*") : lpszMask;
		break;
	}

// KK000605 - für hs-File
		BOOL bHaveMaphs = FALSE;
		BOOL bHaveMapFirst = FALSE;			// noch keine Karte gefunfen
		CString	SMe;
		SMe.Empty();
//-------------------------
	
	if( f.FindFile( strPath ) ) {

		do {
			tMore =	f.FindNextFile();
			if( f.IsDirectory() && !f.IsDots() ) {
				strPath = f.GetFilePath();	//#fje+
				ScanDir( strPath, mapType, lpszMask, hWnd );
			} else if( !f.IsDots() ) {
				strPath = f.GetFilePath();
				strFileExtension = strPath.Right(3);
				strFileExtension.MakeLower();
				if( "tif" == strFileExtension ) {
					strPath = strPath.Left( strPath.GetLength() - 4 );
					BOOL bHaveMap = FALSE;

					CString	S;

					switch( mapType ) {
					case MPT_AS :
						bHaveMap = ParserForASMap::IsMapName( strPath, S );
						break;
					case MPT_AS_L :
						strLayer = strPath.Right(2);
						strLayer.MakeLower();
						if( "hs" == strLayer ) {
							strPath = strPath.Left( strPath.GetLength() - 2 );
							bHaveMap = ParserForASMap::IsMapName( strPath, S );
							S = "<" + S + ">";
				// KK000607
							bHaveMapFirst = FALSE;			// noch keine Karte gefunden
							SMe.Empty();
						} else {
				// KK000606
							if ( !bHaveMapFirst) {
								strPath = strPath.Left( strPath.GetLength() - 2 );
								bHaveMapFirst = ParserForASMap::IsMapName( strPath, S );
								SMe = "<" + S + ">";
								SMe += '\t';
								SMe += f.GetFilePath();
							}
						}
						break;
					case MPT_AV :
						bHaveMap = ParserForAVMap::IsMapName( strPath, S );
						break;
					case MPT_N :
						bHaveMap = ParserForNMap::IsMapName( strPath, S );
						break;
					case MPT_N_L :
						strLayer = strPath.Right(2);
						strLayer.MakeLower();
						if( "hs" == strLayer ) {
							strPath = strPath.Left( strPath.GetLength() - 2 );
							bHaveMap = ParserForNMap::IsMapName( strPath, S );
							S = "<" + S + ">";
				// KK000607
							bHaveMapFirst = FALSE;			// noch keine Karte gefunden
							SMe.Empty();
						} else {
				// KK000606
							if ( !bHaveMapFirst) {
								strPath = strPath.Left( strPath.GetLength() - 2 );
								bHaveMapFirst = ParserForNMap::IsMapName( strPath, S );
								SMe = "<" + S + ">";
								SMe += '\t';
								SMe += f.GetFilePath();
							}
						}
						break;

					default: {
							CPath p( f.GetFilePath() );
							S = p.Prefix();
							bHaveMap = !S.IsEmpty();
						}
						break;
					}
					if( bHaveMap ) {
// KK000605
						bHaveMaphs = TRUE;
// hs gefunden !!
						S += '\t';
						S += f.GetFilePath();
						CString	*pStr = new CString( S );
						::SendMessage( hWnd, WM_MYTHREAD, THREAD_FILEFOUND, (LPARAM) pStr );
					}
				}
			}
		} while( tMore );

	}

// KK000605
	if ( !bHaveMaphs) {
//		MessageBox (0,"Fehlende hs-Datei !","MapMgr",MB_OK);
		if ( bHaveMapFirst) {
			if ( !SMe.IsEmpty()) {
				CString	*pStr = new CString( SMe );
				::SendMessage( hWnd, WM_MYTHREAD, THREAD_FILEFOUND, (LPARAM) pStr );
			}

		}
	}

	f.Close();

}

static UINT SearchFiles( LPVOID pParam ) {
	SEARCHPARAM *pSearch = (SEARCHPARAM*) pParam;
	// Threaddaten lokal machen
	HWND	hWnd = pSearch->m_hWnd;
	TOPOMAPTYPE	mapType = pSearch->m_mapType;
	CString	strSearchDirs = pSearch->m_strSearchDirs;
	CString	strSearchMask = pSearch->m_strSearchMask;
	CString	strDir;
	for( int dir = 0; ::AfxExtractSubString( strDir, strSearchDirs, dir, '\n' ); dir++ ) {
		ScanDir( strDir, mapType, strSearchMask, pSearch->m_hWnd );
	}
	::SendMessage( hWnd, WM_MYTHREAD, THREAD_END, 0 );
	delete pSearch;
	return 0;
}

BOOL CPgDoSearch::OnSetActive()  {
	m_listMaps.ResetContent();

	CPropertySheet *pSheet = (CPropertySheet*) GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( 0 );

	SEARCHPARAM	*sp = new SEARCHPARAM;
	sp->m_hWnd = GetSafeHwnd();
	sp->m_mapType = (TOPOMAPTYPE) m_mapType;
	sp->m_strSearchDirs = m_strSearchDirs;
	sp->m_strSearchMask = m_strSearchMask;
	m_pSrchThread = ::AfxBeginThread( SearchFiles, (LPVOID) sp );

	return CPropertyPage::OnSetActive();
}

LONG CPgDoSearch::OnThreadMessage( UINT wP, LONG lP ) {
	switch( wP ) {

	case THREAD_ENTERDIR : {
//		break;	//#fje
// KK000607
			CString	*pStr = (CString*) lP;
			m_listMaps.AddString( *pStr );
			delete pStr;
			break;
	}

	case THREAD_FILEFOUND : {
			CString	*pStr = (CString*) lP;
// KK000607
			int iIndex = m_listMaps.GetCount() -1;
			CString SS;
			m_listMaps.GetText(iIndex, SS );
			int IT = SS.Find( '\t' );
			if( -1 != IT ) {
				if ( SS.Left(IT) != pStr->Left(IT))
					m_listMaps.AddString( *pStr );
			} else {
				m_listMaps.AddString( *pStr );
			}
//---------------------------------------
//			m_listMaps.AddString( *pStr );
			delete pStr;
		}
		break;
	case THREAD_END : {
			ASSERT_VALID( m_pSrchThread );
			m_pSrchThread = NULL;
			CPropertySheet *pSheet = (CPropertySheet*) GetParent();
			ASSERT_KINDOF(CPropertySheet, pSheet);
			pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );
		}
		break;
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////////////
// CPgFinishNewDoc property page

IMPLEMENT_DYNCREATE(CPgFinishNewDoc, CPropertyPage)

CPgFinishNewDoc::CPgFinishNewDoc() : CPropertyPage(CPgFinishNewDoc::IDD) {
	//{{AFX_DATA_INIT(CPgFinishNewDoc)
	m_strMapParam = _T("");
	//}}AFX_DATA_INIT
}

CPgFinishNewDoc::~CPgFinishNewDoc() {
}

void CPgFinishNewDoc::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgFinishNewDoc)
	DDX_Text(pDX, IDC_EDIT_MAPPARAM, m_strMapParam);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPgFinishNewDoc, CPropertyPage)
	//{{AFX_MSG_MAP(CPgFinishNewDoc)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgFinishNewDoc message handlers

BOOL CPgFinishNewDoc::OnSetActive()  {
	CPropertySheet	*pSheet = (CPropertySheet*) GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_FINISH );
	pSheet->SetFinishText( _T("OK" ) );
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// CDlgNewDocument

IMPLEMENT_DYNAMIC(CDlgNewDocument, CPropertySheet)

CDlgNewDocument::CDlgNewDocument(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDD, pParentWnd, iSelectPage)
{
	AddPage( &m_pgDocStart );
	AddPage( &m_pgMapType );
	AddPage( &m_pgSearch );
	AddPage( &m_pgFinish );
	SetWizardMode( );
	m_nStartAction = -1;
}

CDlgNewDocument::~CDlgNewDocument() {
}

CString CDlgNewDocument::FormatDirs( BOOL bForFinish ) {
	CString	S, S1;

	for( int i = 0; i < m_pgMapType.m_listMapDirs.GetCount(); i++ ) {
		if( bForFinish )
			S += '\t';
		m_pgMapType.m_listMapDirs.GetText( i, S1 );
			S += S1;
		if( i < m_pgMapType.m_listMapDirs.GetCount() - 1 ) {
			if( bForFinish )
				S += '\r';
			S += '\n';
		}
	}
	return S;
}

void CDlgNewDocument::FormatFinish() {
	CString	S1, S2;
	S2 = FormatDirs( TRUE );
	if( S2.IsEmpty() )
		S2.LoadString( IDS_NOSRCHDIR );
	else {
		::AfxFormatString1( S1, IDS_SRCHDIR, S2 );
		S2 = S1;
	}
	m_pgMapType.m_listMapTypes.GetLBText( m_pgMapType.m_listMapTypes.GetCurSel(), S1 );
	::AfxFormatString2( m_pgFinish.m_strMapParam, IDS_NEWDOC, S1, S2 );
}

BEGIN_MESSAGE_MAP(CDlgNewDocument, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgNewDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND( ID_WIZBACK, OnWizardBack )
	ON_COMMAND( ID_WIZNEXT, OnWizardNext )
	ON_COMMAND( ID_WIZFINISH, OnWizardFinish )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewDocument message handlers
// 00246-94136340

BOOL CDlgNewDocument::OnInitDialog()  {
	m_pgMapType.m_strMapTypes = m_strMapTypes;
	return CPropertySheet::OnInitDialog();
}

void CDlgNewDocument::OnWizardNext() {
	CPropertyPage	*pPage = GetActivePage();
	int	idx = GetActiveIndex();

	if( pPage->IsKindOf( RUNTIME_CLASS( CPgDocStart ) ) ) {
		m_pgDocStart.UpdateData();
		switch( m_nStartAction = m_pgDocStart.m_nStartAction ) {
		case 0 :
		case 1 :
			EndDialog( ID_WIZFINISH );
			return;
		}
	} else if( pPage->IsKindOf( RUNTIME_CLASS( CPgMapType ) ) ) {
		m_pgMapType.UpdateData();
		if( m_pgMapType.m_bSrchMaps && m_pgMapType.m_listMapDirs.GetCount() > 0 ) {
			m_pgSearch.m_strSearchDirs = FormatDirs();
			m_pgSearch.m_strSearchMask = m_pgMapType.m_strSearchMask;
//			m_pgSearch.m_mapType = m_pgMapType.m_nMapType + 1;	#fje-
			m_pgSearch.m_mapType = mapTypes[m_pgMapType.m_nMapType].m_mtType;	//#fje+
			// MapType INVALID ist letzter und alle anderen wurden in Reihenfolge hinzugefügt
		} else {
			FormatFinish();
			idx++;
		}
	} else if( pPage->IsKindOf( RUNTIME_CLASS( CPgDoSearch ) ) ) {
		CString	S;
		int nItems = m_pgSearch.m_listMaps.GetCount();
		m_strMaps.Empty();
		for( int i = 0; i < nItems; i++ ) {
			m_pgSearch.m_listMaps.GetText( i, S );
			if( -1 != S.Find( '\t' ) ) {
				m_strMaps += S;
				if( i < nItems - 1 )
					m_strMaps += '\n';
			}
		}
		FormatFinish();
	} else {
		ASSERT( FALSE );
	}
	SetActivePage( idx + 1 );
	GetDlgItem( ID_WIZFINISH )->SetFocus();
}

void CDlgNewDocument::OnWizardBack() {
	SetActivePage( GetActiveIndex() - 1 );
}

void CDlgNewDocument::OnWizardFinish() {
	m_mapType = m_pgMapType.m_nMapType + 1;
	m_strMapDirs = FormatDirs( );
	EndDialog( ID_WIZFINISH );
}
