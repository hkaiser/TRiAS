// CreateNewParamWiz.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <hdrentrx.hxx>

#include "Strings.h"
#include "CreateNewParamWiz.h"
#include "NewProjectAdvancedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateNewParamWiz property page

IMPLEMENT_DYNCREATE(CCreateNewParamWiz, CPropertyPage)

CCreateNewParamWiz::CCreateNewParamWiz() 
	: CPropertyPage(IsWin40() ? CCreateNewParamWiz::IDD : CCreateNewParamWiz::IDD_NT)
{
	//{{AFX_DATA_INIT(CCreateNewParamWiz)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iCreateMode = CREATEMODE_Unknown;
	m_iIdBase = 16;		// default ist hexadezimal
	m_fCompatible = false;

// Caption den aktuellen Erfordernissen anpassen
	TRY {
	CString strOrgCap;

		VERIFY(strOrgCap.LoadString (IDS_CREATENEWPARAMDLG));
		m_strCaption.Format (strOrgCap, g_cbTRiAS);
		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;

	} CATCH (CMemoryException, e) {
		TRACE("Couldn't change caption for CCreateNewParamWiz\r\n");
	} END_CATCH;
}

CCreateNewParamWiz::~CCreateNewParamWiz()
{
}

void CCreateNewParamWiz::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateNewParamWiz)
	DDX_Control(pDX, IDC_IMPORTDATA, m_rbImportData);
	DDX_Control(pDX, IDC_EDITDATA, m_rbEditData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateNewParamWiz, CPropertyPage)
	//{{AFX_MSG_MAP(CCreateNewParamWiz)
	ON_BN_CLICKED(IDC_EDITDATA, OnEditdata)
	ON_BN_CLICKED(IDC_IMPORTDATA, OnImportdata)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Sonstige Helper
void CCreateNewParamWiz::AdjustButtons(void)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);

DWORD dwBttns = 0;

	if (CREATEMODE_ImportData == m_iCreateMode)
	{
//		dwBttns = PSWIZB_NEXT|PSWIZB_BACK;		// vorerst, solange import separat läuft
		dwBttns = PSWIZB_FINISH|PSWIZB_BACK;
	}
	else if (CREATEMODE_EditData == m_iCreateMode)
		dwBttns = PSWIZB_FINISH|PSWIZB_BACK;
	else
		ASSERT(m_iCreateMode != CREATEMODE_Unknown);

	pSheet -> SetWizardButtons (dwBttns);
}

CCreateNewParamWiz::CREATEMODE CCreateNewParamWiz::RetrieveCreateMode (void)
{
	if (m_rbImportData.GetCheck())
		return CCreateNewParamWiz::CREATEMODE_ImportData;

	return CCreateNewParamWiz::CREATEMODE_EditData;
}

bool CCreateNewParamWiz::RegisterEntries (void)
{
	ASSERT(10 == m_iIdBase || 16 == m_iIdBase);

	if (m_fCompatible) {
	HeaderEntryX HEC (g_cbCompatible, TEXT("1"), HEADER_SYSTEMRO);

		if (EC_OKAY != HEC.WriteBack()) 
			return false;
	
	HeaderEntryX HEP (g_cbUseOldPointStyle, TEXT("1"), HEADER_SYSTEMRO);

		if (EC_OKAY != HEP.WriteBack()) 
			return false;
	}

CString str; str.Format ("%d", m_iIdBase);
HeaderEntryX HE (g_cbIdentBase, str, HEADER_SYSTEMRO);

	return (EC_OKAY == HE.WriteBack()) ? true : false;	
}

/////////////////////////////////////////////////////////////////////////////
// CCreateNewParamWiz message handlers


BOOL CCreateNewParamWiz::OnSetActive() 
{
	AdjustButtons();

// Caption den aktuellen Erfordernissen anpassen
	TRY {
	CString strOrgCap, strCap;

		GetWindowText (strOrgCap);
		strCap.Format (strOrgCap, g_cbTRiAS);
		SetWindowText (strCap);
	
	} CATCH (CMemoryException, e) {
		TRACE("Couldn't change caption\r\n");
	} END_CATCH;

	return CPropertyPage::OnSetActive();
}

LRESULT CCreateNewParamWiz::OnWizardNext() 
{
	ASSERT(CREATEMODE_ImportData == m_iCreateMode);
	return CPropertyPage::OnWizardNext();
}

BOOL CCreateNewParamWiz::OnWizardFinish() 
{
	ASSERT(CREATEMODE_EditData == m_iCreateMode || 
		   CREATEMODE_ImportData == m_iCreateMode);
	return CPropertyPage::OnWizardFinish();
}

void CCreateNewParamWiz::OnEditdata() 
{
	m_iCreateMode = RetrieveCreateMode();
	AdjustButtons();
}

void CCreateNewParamWiz::OnImportdata() 
{
	m_iCreateMode = RetrieveCreateMode();
	AdjustButtons();
}

BOOL CCreateNewParamWiz::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_iCreateMode = CREATEMODE_ImportData;
	m_rbImportData.SetCheck (true);
	m_rbEditData.SetCheck (false);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCreateNewParamWiz::OnAdvanced() 
{
CNewProjectAdvancedDlg Dlg (this, m_iIdBase);

	if (IDCANCEL == Dlg.DoModal())
		return;

	m_iIdBase = Dlg.GetIdentBase ();
	m_fCompatible = Dlg.GetCompatibilityMode();
}
