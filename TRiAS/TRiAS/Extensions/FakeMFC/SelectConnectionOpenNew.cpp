// SelectConnectionOpenNew.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include "Strings.h"
#include "OpenNewPropertySheet.h"
#include "SelectConnectionOpenNew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectionOpenNew property page

IMPLEMENT_DYNCREATE(CSelectConnectionOpenNew, CPropertyPage)

CSelectConnectionOpenNew::CSelectConnectionOpenNew(UINT uiID, UINT uiIDCap) 
	: CPropertyPage(uiID)
{
	//{{AFX_DATA_INIT(CSelectConnectionOpenNew)
	//}}AFX_DATA_INIT
	m_iDatasourceMode = DATASOURCEMODE_Unknown;
	m_fStandAlone = FALSE;

// Caption den aktuellen Erfordernissen anpassen
	TRY {
	CString strOrgCap;

		VERIFY(strOrgCap.LoadString (uiIDCap));
		m_strCaption.Format (strOrgCap, g_cbTRiAS);
		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;

	} CATCH (CMemoryException, e) {
		TRACE("Couldn't change caption for CSelectConnectionOpenNew\r\n");
	} END_CATCH;
}

CSelectConnectionOpenNew::~CSelectConnectionOpenNew()
{
}

void CSelectConnectionOpenNew::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectConnectionOpenNew)
	DDX_Control(pDX, IDC_CREATEDATASOURCE, m_rbCreateDatasource);
	DDX_Control(pDX, IDC_OPENDATASOURCE, m_rbOpenDatasource);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelectConnectionOpenNew, CPropertyPage)
	//{{AFX_MSG_MAP(CSelectConnectionOpenNew)
	ON_BN_CLICKED(IDC_CREATEDATASOURCE, OnCreatedatasource)
	ON_BN_CLICKED(IDC_OPENDATASOURCE, OnOpendatasource)
	ON_BN_DOUBLECLICKED(IDC_CREATEDATASOURCE, OnDoubleclickedCreatedatasource)
	ON_BN_DOUBLECLICKED(IDC_OPENDATASOURCE, OnDoubleclickedOpendatasource)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

DATASOURCEMODE CSelectConnectionOpenNew::RetrieveOpenMode (void)
{
	if (m_rbOpenDatasource.GetCheck())
		GetPropSheet() -> m_rgDatasource = DATASOURCEMODE_OpenExistend;
	else 
		GetPropSheet() -> m_rgDatasource = DATASOURCEMODE_CreateNew;
		
	return GetPropSheet() -> GetDatasourceMode();
}

///////////////////////////////////////////////////////////////////////////////
// Knöpfchen richten
void CSelectConnectionOpenNew::AdjustButtons(void)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);

DWORD dwBttns = PSWIZB_NEXT;

	if (!m_fStandAlone)
		dwBttns |= PSWIZB_BACK;

	pSheet -> SetWizardButtons (dwBttns);
}

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectionOpenNew message handlers

void CSelectConnectionOpenNew::OnCreatedatasource() 
{
	m_iDatasourceMode = RetrieveOpenMode();
	AdjustButtons();
}

void CSelectConnectionOpenNew::OnOpendatasource() 
{
	m_iDatasourceMode = RetrieveOpenMode();
	AdjustButtons();
}

BOOL CSelectConnectionOpenNew::OnSetActive() 
{
	AdjustButtons();
	return CPropertyPage::OnSetActive();
}

LRESULT CSelectConnectionOpenNew::OnWizardNext() 
{
	ASSERT(DATASOURCEMODE_CreateNew == m_iDatasourceMode ||
		   DATASOURCEMODE_OpenExistend == m_iDatasourceMode);

	if (!(TRIASMODE_GDO & g_dwHookFlags) || 
		1 == GetPropSheet()->CountAvailableDataServers()) 
	{
	// die nächste Seite (IDD_SELECT_CONNECTION) muß übersprungen werden
		CPropertyPage::OnWizardNext();
		SetWindowLong (m_hWnd, DWL_MSGRESULT, IDD_CONNECTION_PARAMS);
		return IDD_CONNECTION_PARAMS;
	} 
	return CPropertyPage::OnWizardNext();
}

LRESULT CSelectConnectionOpenNew::OnWizardBack() 
{
	ASSERT(!m_fStandAlone);
	return CPropertyPage::OnWizardBack();
}

#if defined(_DEBUG)
BOOL CSelectConnectionOpenNew::OnWizardFinish() 
{
	ASSERT(FALSE);
	return CPropertyPage::OnWizardFinish();
}
#endif // _DEBUG

BOOL CSelectConnectionOpenNew::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_rbOpenDatasource.SetCheck(TRUE);
	m_rbCreateDatasource.SetCheck(FALSE);
	m_iDatasourceMode = RetrieveOpenMode();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectConnectionOpenNew::OnDoubleclickedCreatedatasource() 
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);
	pSheet -> PressButton (PSBTN_NEXT);
}

void CSelectConnectionOpenNew::OnDoubleclickedOpendatasource() 
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);
	pSheet -> PressButton (PSBTN_NEXT);
}

