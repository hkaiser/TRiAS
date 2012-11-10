// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
//
// @doc
// @module ExportPropertyActionDlg.cpp | Implementation of the <c CExportPropertyActionDlg> class

#include "stdafx.h"

#include <Com/ComBool.h>
#include "ExportImpl.h"

#include "ExportPropertyActionDlg.h"
#include "PathDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined(_DEBUG)
static inline bool IsHost( LPCTSTR lpszHostname ) 
{
	char	strHost[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD	dwLength = sizeof( strHost );
	if( !::GetComputerName( strHost, &dwLength ) )
		return false;
	if( 0 != stricmp( strHost, lpszHostname ) )
		return false;
	return true;
}
#endif // Defined(_DEBUG)

static inline HRESULT GetDisplayname( WTRiASExtDataEngine& pTRiASExtDataEngine, CComBSTR& strName ) 
{
	TCHAR	_buf[_MAX_PATH];
	USES_CONVERSION;
	CComBSTR	strExt;
	pTRiASExtDataEngine->get_Name( &strName );
	pTRiASExtDataEngine->get_Extension( &strExt );
	sprintf( _buf, _T("%s (%s)"), W2A(strName), W2A(strExt) );
	strName = _buf;
	return S_OK;
}

static inline HRESULT GetFilefilter( WTRiASExtDataEngine& pTRiASExtDataEngine, CComBSTR& strFilter, CComBSTR& strExt ) 
{
	TCHAR	_buf[_MAX_PATH];
	USES_CONVERSION;
	pTRiASExtDataEngine->get_Name( &strFilter );
	pTRiASExtDataEngine->get_Extension( &strExt );
	sprintf( _buf, _T("%s (*.%s)|*.%s||"), W2A(strFilter), W2A(strExt), W2A(strExt) );
	strFilter = _buf;
	sprintf( _buf, _T(".%s"), W2A(strExt) );
	strExt = _buf;
	return S_OK;
}

static inline HRESULT GetOutputIsDirectory (ITRiASExtDataEngine *pTRiASExtDataEngine, VARIANT_BOOL *pfIsDir)
{
long lYesNo = 0;

	pTRiASExtDataEngine -> get_Capability(CComBSTR(L"OutputIsDirectory"), &lYesNo);
	*pfIsDir = lYesNo ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CExportPropertyActionDlg property page

CExportPropertyActionDlg* CExportPropertyActionDlg::CreateInstance (LPCSTR pcCaption) 
{
	CExportPropertyActionDlg *pCfgDlg = NULL;
	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CExportPropertyActionDlg();

	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

IMPLEMENT_DYNCREATE(CExportPropertyActionDlg, CPropertyPage)

CExportPropertyActionDlg::CExportPropertyActionDlg() 
	: CPropertyPage(CExportPropertyActionDlg::IDD)
{
	//{{AFX_DATA_INIT(CExportPropertyActionDlg)
	m_strFilename = _T("");
	m_bSeparate = FALSE;
	m_bSelect = FALSE;
	m_nSelectedEngine = -1;
	//}}AFX_DATA_INIT
//	m_strCoordsys = _T("");
	m_dwFlags = 0;
	m_pObjPropDlg = NULL;
	m_pSelCsDlg = NULL;
}

CExportPropertyActionDlg::~CExportPropertyActionDlg() 
{
	m_vecOfEngines.clear();
}

void CExportPropertyActionDlg::DoDataExchange(CDataExchange* pDX) 
{
	if (!pDX->m_bSaveAndValidate) 
		RereadControldata();

	CPropertyPage::DoDataExchange(pDX);

//	DDX_Control(pDX, IDC_BTNEXPORTCOORDSYS00, m_btnCoordsys00);
//	DDX_Control(pDX, IDC_BTNEXPORTCOORDSYS, m_btnCoordsys);
//	DDX_Control(pDX, IDC_EXPORTCOORDSYS, m_StaticCoordsys);
//	DDX_Text(pDX, IDC_EXPORTCOORDSYS, m_strCoordsys);
//	DDX_Control(pDX, IDC_STATIC_COORDSYS, m_SeparateCoordsys);
	//{{AFX_DATA_MAP(CExportPropertyActionDlg)
	DDX_Control(pDX, IDC_SEPARATE, m_btnSeparate);
	DDX_Control(pDX, IDC_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_EXPORTFORMATS, m_boxOfExportFormats);
	DDX_Control(pDX, IDC_STATIC_FORMAT, m_SeparateFormat);
	DDX_Control(pDX, IDC_STATIC_FILENAME, m_SeparateFilename);
	DDX_Control(pDX, IDC_STATIC_OPTIONS, m_SeparateOptions);
	DDX_Control(pDX, IDC_EXPORTFILENAME, m_StaticFilename);
	DDX_Text(pDX, IDC_EXPORTFILENAME, m_strFilename);
	DDX_Check(pDX, IDC_SEPARATE, m_bSeparate);
	DDX_Check(pDX, IDC_SELECT, m_bSelect);
	DDX_CBIndex(pDX, IDC_EXPORTFORMATS, m_nSelectedEngine);
	//}}AFX_DATA_MAP

	if (!pDX->m_bSaveAndValidate) {
		AdjustSheetButtons();
		AdjustControls();
	}
}

//////////////////////////////////////////////////////////////
// Auslesen der einschlägigen Daten aus der aktuell gewählten
// Engine und Dialogdaten damit versorgen

void CExportPropertyActionDlg::RereadControldata() 
{
	if( m_nSelectedEngine < 0 || !m_pTRiASExtDataEngine.IsValid() )
		return;					// u.U. noch nicht initialisiert
		
	USES_CONVERSION;

CComBSTR strFilename;
long lVal;

	m_pTRiASExtDataEngine->get_Filename(&strFilename);
	m_strFilename = W2A(strFilename);
	m_pTRiASExtDataEngine->get_SeparateOutput(&lVal);
	m_bSeparate = 0 != lVal ? TRUE : FALSE;
	m_pTRiASExtDataEngine->get_AppendOutput(&lVal);

// KK000816
	m_pTRiASExtDataEngine->get_SelectOutput(&lVal);
	m_bSelect = 0 != lVal ? TRUE : FALSE;


CComBSTR strCSName;
WTRiASCS pTRiASCS;
WDispatch pDispatch;

	m_pTRiASExtDataEngine->get_CoordSystem( pDispatch.ppi() );
	pTRiASCS = pDispatch;
	pTRiASCS->get_Description( &strCSName );
//	m_strCoordsys = W2A(strCSName);

CComBool fIsDirectory;
CString strSelText;

	GetOutputIsDirectory(m_pTRiASExtDataEngine, &fIsDirectory);
	VERIFY(strSelText.LoadString(fIsDirectory ? IDS_SELECTDIRNAME : IDS_SELECTFILENAME));
	m_SeparateFilename.SetWindowText(strSelText);
	m_SeparateFilename.InvalidateRect(NULL);
}

BEGIN_MESSAGE_MAP(CExportPropertyActionDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CExportPropertyActionDlg)
	ON_BN_CLICKED(IDC_BTNEXPORTFILENAME, OnSelectexportfile)
	ON_CBN_SELCHANGE(IDC_EXPORTFORMATS, OnSelchangeExportformats)
	ON_BN_CLICKED(IDC_SEPARATE, OnSeparate)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDC_EXPORTOBJPROPS, OnExportobjprops)
//	ON_BN_CLICKED(IDC_BTNEXPORTCOORDSYS, OnCoordsys)
//	ON_BN_CLICKED(IDC_BTNEXPORTCOORDSYS00, OnBtnexportcoordsys00)
END_MESSAGE_MAP()

void CExportPropertyActionDlg::AdjustSheetButtons()
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte Seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons(dwBttns);
}

BOOL CExportPropertyActionDlg::GetDisableNextPage() {
	// TODO: return TRUE, if 'Next >' - button should be disabled
	if( 0 == m_strFilename.GetLength() )
		return TRUE;
	return FALSE;
}

void CExportPropertyActionDlg::AdjustControls() 
{
	if( !m_pTRiASExtDataEngine.IsValid() ) {
//		_ASSERTE( m_pTRiASExtDataEngine.IsValid() );
		return;
	}
	HRESULT	hr;
	long	bBool;
	hr = m_pTRiASExtDataEngine->get_Capability( CComBSTR(L"CanSeparateOutput"), &bBool );
	m_btnSeparate.EnableWindow( FAILED(hr) || FALSE == bBool ? FALSE : TRUE );
//	if( TRUE == bBool ) {
//		hr = m_pTRiASExtDataEngine->get_Capability( CComBSTR(L"MustSeparateOutput"), &bBool );
//		m_btnSeparate.EnableWindow( ( SUCCEEDED(hr) && TRUE == bBool ) ? FALSE : TRUE );
//	}
	hr = m_pTRiASExtDataEngine->get_Capability( CComBSTR(L"CanSpecifyTransformation"), &bBool );
//	m_btnCoordsys.EnableWindow( FAILED(hr) || FALSE == bBool ? FALSE : TRUE );
//	m_btnCoordsys00.EnableWindow( FAILED(hr) || FALSE == bBool ? FALSE : TRUE );
}

/////////////////////////////////////////////////////////////////////////////
// CExportPropertyActionDlg message handlers

BOOL CExportPropertyActionDlg::OnSetActive() 
{
	return CPropertyPage::OnSetActive();
}

BOOL CExportPropertyActionDlg::OnInitDialog() 
{
	if( FALSE == CPropertyPage::OnInitDialog() )
		return FALSE;
	WPersistStreamInit	pPersistStreamInit;
	CLSID	clsidLastUsed(CLSID_NULL);
	if( m_pTRiASExtDataEngine.IsValid() ) {
		RETURN_FAILED_HRESULT( m_pTRiASExtDataEngine->QueryInterface( pPersistStreamInit.GetIID(), pPersistStreamInit.ppv() ) );
		pPersistStreamInit->GetClassID( &clsidLastUsed );
	}

	USES_CONVERSION;
	_ASSERTE( -1 == m_nSelectedEngine );
	_ASSERTE( m_vecOfEngines.size() > 0 );
	int	nEngine = 0;
	for (vector<WTRiASExtDataEngine>::iterator i = m_vecOfEngines.begin(); 
		 m_vecOfEngines.end() != i; 
		 ++i, ++nEngine) 
	{
	CComBSTR strName;
	CLSID clsid;
	WTRiASExtDataEngine	pTRiASExtDataEngine;

		if (FAILED((*i)->QueryInterface(pTRiASExtDataEngine.ppi()))) 
			continue;
		if (FAILED((*i)->QueryInterface(pPersistStreamInit.ppi())))
			continue;

		GetDisplayname(pTRiASExtDataEngine, strName);

	// ist es die im letzten Dialog gewählte Engine?
	int nIndex = m_boxOfExportFormats.AddString(W2A(strName));

		pPersistStreamInit->GetClassID(&clsid);
		if (clsid == clsidLastUsed) {
			m_nSelectedEngine = nEngine;
			_ASSERTE(m_pTRiASExtDataEngine == pTRiASExtDataEngine);
		}
	}
	if (-1 == m_nSelectedEngine) {
		m_nSelectedEngine = 0;
		m_pTRiASExtDataEngine = m_vecOfEngines[0];
	}

	m_StaticFilename.SetPath (TRUE);

//#if defined(_DEBUG)
//	if( IsHost( "xxrioja" ) ) {
//		GetDlgItem(IDC_BTNEXPORTCOORDSYS00)->ShowWindow( SW_HIDE );
//	} else 
//#endif // defined(_DEBUG)
//	{
//		GetDlgItem(IDC_STATIC_COORDSYS)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_EXPORTCOORDSYS)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_BTNEXPORTCOORDSYS)->ShowWindow(SW_HIDE);
//	}

long lCont[4];
CString strSelText;
bool fIsSelection = DEX_GetActiveSelection(lCont);

	VERIFY(strSelText.LoadString(fIsSelection ? IDS_SELECTBEREICH : IDS_SELECTAUSSCHNITT));
	m_btnSelect.SetWindowText(strSelText);

//#if !defined(_DEBUG)
//	if (!(QMSysAdmin & DEX_QueryMode())) 
//	{
//		GetDlgItem(IDC_EXPORTOBJPROPS)->ShowWindow(SW_HIDE);
//	}
//#endif // !defined(_DEBUG)


	if (m_pTRiASExtDataEngine.IsValid()) {
		OnSelchangeExportformats(FALSE);
		OnSelect(FALSE);
		OnSeparate(FALSE);
	}
	UpdateData(FALSE);

	return TRUE; // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HRESULT	CExportPropertyActionDlg::SelectExportfile() 
{
	COM_TRY {
		_ASSERTE( m_pTRiASExtDataEngine.IsValid() );
		USES_CONVERSION;

	CString strTitle;

//		strTitle.LoadString(IDS_LONGCLASSNAME);
// KK010321
		strTitle.LoadString(IDS_EXPORTCAP);

	CComBool fIsDirectory;
	CComBSTR strFilename;
	
		RETURN_FAILED_HRESULT(GetOutputIsDirectory(m_pTRiASExtDataEngine, &fIsDirectory));
		if (!fIsDirectory) {
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
		CComBSTR strFilter;
		CComBSTR strDefExt;

			if( IsWin41() || ( IsWinNT() && IsWin50() ) ) {
				dwFlags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
				dwFlags |= OFN_DONTADDTORECENT;
#endif
			}
			GetFilefilter (m_pTRiASExtDataEngine, strFilter, strDefExt);

		CFileDialog	dlg (FALSE, W2A(strDefExt), m_strFilename, dwFlags, W2A(strFilter), this);

			dlg.m_ofn.lpstrTitle = strTitle;
			if (IDOK != dlg.DoModal()) 
				return S_FALSE;
			strFilename = dlg.GetPathName();
		} else {
		CString strPrompt;

			VERIFY(strPrompt.LoadString(IDS_SELECTDIRPRROMPT));

		CPathDialog dlg (FALSE, strTitle, strPrompt, m_strFilename, this);

			if (IDOK != dlg.DoBrowse())
				return S_FALSE;
			strFilename = dlg.GetPathName();
			if (L'\\' != strFilename[strFilename.Length()-1])
				strFilename.Append (L"\\");
		}

		m_pTRiASExtDataEngine->put_Filename (strFilename);
		UpdateData(FALSE);

	} COM_CATCH;
	return S_OK;
}

HRESULT CExportPropertyActionDlg::SelectExportCoordsys() {
	COM_TRY {
	} COM_CATCH;
	return S_OK;
}

void CExportPropertyActionDlg::OnSelectexportfile() {
	HRESULT hr = SelectExportfile();
}

void CExportPropertyActionDlg::OnCoordsys() {
	HRESULT hr = SelectExportCoordsys();
	UpdateData(FALSE);
}
void CExportPropertyActionDlg::OnBtnexportcoordsys00()  {
	HRESULT hr = SelectExportCoordsys();
	UpdateData(FALSE);
}

void CExportPropertyActionDlg::OnSelchangeExportformats()  
{
	OnSelchangeExportformats(TRUE);
}

void CExportPropertyActionDlg::OnSelchangeExportformats(BOOL fUpdate)  
{
	if (fUpdate)
		UpdateData();
	m_pTRiASExtDataEngine = m_vecOfEngines[m_nSelectedEngine];

long lRes = FALSE;

	_ASSERTE(NULL != m_pObjPropDlg);
	m_pTRiASExtDataEngine->get_Capability(CComBSTR(L"EC_StandardMerkmale"), &lRes);
	if (NULL != m_pObjPropDlg)
		m_pObjPropDlg->SetLimitCount(lRes ? 2 : -1);	// BNA-Format kann nur 2 Merkmale
		
	if (fUpdate)
		UpdateData(FALSE);
}

void CExportPropertyActionDlg::OnSeparate()  
{
	OnSeparate(TRUE);
}

void CExportPropertyActionDlg::OnSeparate(BOOL fUpdate)  
{
	if (fUpdate)
		UpdateData();

	_ASSERTE( m_pTRiASExtDataEngine.IsValid() );
	long	lSeparate = m_bSeparate;
	m_pTRiASExtDataEngine->put_SeparateOutput(lSeparate);

	if (fUpdate)
		UpdateData(FALSE);
}

// KK000816
void CExportPropertyActionDlg::OnSelect() 
{
	OnSelect(TRUE);
}

void CExportPropertyActionDlg::OnSelect(BOOL fUpdate) 
{
	if (fUpdate)
		UpdateData();

	_ASSERTE( m_pTRiASExtDataEngine.IsValid() );
	long	lSelect = m_bSelect;
	m_pTRiASExtDataEngine->put_SelectOutput(lSelect);

	if (fUpdate)
		UpdateData(FALSE);
}

void CExportPropertyActionDlg::OnExportobjprops() 
{
	UpdateData();
	_ASSERTE(m_pTRiASExtDataEngine.IsValid());
	long	lExportObjProps = TRUE;
	m_pTRiASExtDataEngine->put_ExportObjProps(lExportObjProps);
	UpdateData(FALSE);
}

