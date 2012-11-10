// DlgImportOpt.cpp : implementation file
//

#include "stdafx.h"
#include <afxdlgs.h>

#include "TRiASImport.h"
#include "Resource.h"

#include "Wrapper.h"
#include "DlgImportOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImportOpt dialog

IMPLEMENT_DYNCREATE(CDlgImportOpt, CPropertyPage)

CDlgImportOpt::CDlgImportOpt()
	: CPropertyPage(CDlgImportOpt::IDD)
{
	//{{AFX_DATA_INIT(CDlgImportOpt)
	m_bImpAnsiOEM = FALSE;
	m_bImpFeatures = FALSE;
	m_bImpGeometry = FALSE;
	m_bImpRelations = FALSE;
	m_bImpVisu = FALSE;
	m_strDesc = _T("");
	//}}AFX_DATA_INIT
}

CDlgImportOpt::~CDlgImportOpt()
{
}


void CDlgImportOpt::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImportOpt)
	DDX_Control(pDX, IDC_VISU, m_btnVisu);
	DDX_Control(pDX, IDC_RELATIONS, m_btnRelations);
	DDX_Control(pDX, IDC_KONFIG, m_btnKonfig);
	DDX_Control(pDX, IDC_GEOMETRY, m_btnGeometry);
	DDX_Control(pDX, IDC_FEATURES, m_btnFeatures);
	DDX_Control(pDX, IDC_ANSIOEM, m_btnAnsiOEM);
	DDX_Check(pDX, IDC_ANSIOEM, m_bImpAnsiOEM);
	DDX_Check(pDX, IDC_FEATURES, m_bImpFeatures);
	DDX_Check(pDX, IDC_GEOMETRY, m_bImpGeometry);
	DDX_Check(pDX, IDC_RELATIONS, m_bImpRelations);
	DDX_Check(pDX, IDC_VISU, m_bImpVisu);
	DDX_Text(pDX, IDC_ADVANCEDDESC, m_strDesc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImportOpt, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgImportOpt)
	ON_BN_CLICKED(IDC_KONFIG, OnKonfig)
	ON_BN_CLICKED(IDC_KOORD, OnKoord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Sonstige Helper
void CDlgImportOpt::AdjustButtons(void)
{
	CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);
	DWORD dwBttns = PSWIZB_FINISH|PSWIZB_BACK;

	pSheet -> SetWizardButtons (dwBttns);
}

HRESULT CDlgImportOpt::SaveSettingsToPairs()
{
	if (!m_Pairs) 
		return E_UNEXPECTED;

//CComBSTR bstrCompatible (m_fCompatible ? "1" : "0");
//CComBSTR bstrIdBase ((10 == m_iIdBase) ? "10" : "16");

//	RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(g_cbCompatible), bstrCompatible, VARIANT_TRUE));
//	RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(g_cbIdentBase), bstrIdBase, VARIANT_TRUE));
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgImportOpt message handlers

BOOL CDlgImportOpt::OnSetActive() 
{
	AdjustButtons();
	return CPropertyPage::OnSetActive();
}

LRESULT CDlgImportOpt::OnWizardNext() 
{
	SaveSettingsToPairs();
	return CPropertyPage::OnWizardNext();
}

BOOL CDlgImportOpt::OnWizardFinish() 
{
	SaveSettingsToPairs();
	return CPropertyPage::OnWizardFinish();
}


/////////////////////////////////////////////////////////////////////////////
// CDlgImportOpt message handlers

void CDlgImportOpt::OnKonfig() 
{
	if ( m_ImportGeoData )
	{
		EnableWindow( FALSE );
		m_ImportGeoData -> Configure( GetSafeHwnd());
		EnableWindow( TRUE );
	}
}

void CDlgImportOpt::OnKoord() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CDlgImportOpt::OnInitDialog() 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	CPropertyPage::OnInitDialog();

CRegKey key;
char cbBuffer[_MAX_PATH];
DWORD dwLen = _countof(cbBuffer);
DWORD	lType = REG_SZ;
CString	strDescr;

	if (ERROR_SUCCESS == key.Open (HKEY_CLASSES_ROOT, m_strProgID) &&
		ERROR_SUCCESS == key.Open (key, TEXT("TRiASDB")) &&
		ERROR_SUCCESS == key.Open (key, TEXT("Description")))
	{
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbCanImpGeom, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bImpGeometry = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbOptImpGeom, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bOptGeometry = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbCanImpFeat, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bImpFeatures = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbOptImpFeat, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bOptFeatures = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbCanImpRela, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bImpRelations = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbOptImpRela, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bOptRelations = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbCanImpVisu, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bImpVisu = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbOptImpVisu, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bOptVisu = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbCanImpAnsiOEM, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bImpAnsiOEM = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbOptImpAnsiOEM, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bOptAnsiOEM = (cbBuffer[0] != '0');
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbShouldConfig, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			cbBuffer[0] = '0';
		m_bShouldConfig = (cbBuffer[0] != '0');

		dwLen = _countof(cbBuffer);
		if (ERROR_SUCCESS != ::RegQueryValueEx (key, g_cbShortName, NULL, &lType, (LPBYTE)cbBuffer, &dwLen))
			strDescr = "X-Datei";
		else
			strDescr = cbBuffer;

//		strDescr.MakeUpper();
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState())

			m_strDesc.Format (IDS_ADVDESCTEXT, (const char*)strDescr);
		}
	}

	m_btnAnsiOEM.SetCheck( m_bImpAnsiOEM ? 1 : 0 );
	m_btnFeatures.SetCheck( m_bImpFeatures ? 1 : 0 );
	m_btnGeometry.SetCheck( m_bImpGeometry ? 1 : 0 );
	m_btnRelations.SetCheck( m_bImpRelations ? 1 : 0 );
	m_btnVisu.SetCheck( m_bImpVisu ? 1 : 0 );
	m_btnAnsiOEM.EnableWindow( m_bOptAnsiOEM );
	m_btnFeatures.EnableWindow( m_bOptFeatures );
	m_btnGeometry.EnableWindow( m_bOptGeometry );
	m_btnRelations.EnableWindow( m_bOptRelations );
	m_btnVisu.EnableWindow( m_bOptVisu );
	m_btnKonfig.EnableWindow( m_bShouldConfig );

	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
