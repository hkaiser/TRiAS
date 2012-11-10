// @doc 
// @module TRiASCustomizeToolBar.cpp | Description goes here

#include "fakemfcp.hxx"
#include "fakemfc.h"

#if defined(_USE_TOOLBARCUSTOMIZE)

#include "TRiASBarObj.h"
#include "TRiASToolBar.h"
#include "ToolBarManager.h"
#include "TRiASCustomizeToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineSmartInterface(TRiASUIOwner);

/////////////////////////////////////////////////////////////////////////////
// TRiASCustomizeToolBar property page

IMPLEMENT_DYNCREATE(CTRiASCustomizeToolBar, SECToolBarCmdPage)

CTRiASCustomizeToolBar::CTRiASCustomizeToolBar() 
	: SECToolBarCmdPage((UINT)CTRiASCustomizeToolBar::IDD)
{
	m_psp.hInstance = _Module.GetResourceInstance();	// aus dieser DLL laden
	//{{AFX_DATA_INIT(CTRiASCustomizeToolBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTRiASCustomizeToolBar::~CTRiASCustomizeToolBar()
{
}

void CTRiASCustomizeToolBar::DoDataExchange(CDataExchange* pDX)
{
	SECToolBarCmdPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTRiASCustomizeToolBar)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTRiASCustomizeToolBar, SECToolBarCmdPage)
	//{{AFX_MSG_MAP(CTRiASCustomizeToolBar)
	ON_CBN_SELCHANGE(IDC_TOOLBAR_LIST, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TRiASCustomizeToolBar message handlers

BOOL CTRiASCustomizeToolBar::OnInitDialog() 
{
// ToolBars einbinden
SECFrameWnd *pWnd = DYNAMIC_DOWNCAST(SECFrameWnd, AfxGetMainWnd());

	ASSERT(NULL != pWnd);

CTRiASToolBarManager *pManager = DYNAMIC_DOWNCAST(CTRiASToolBarManager, pWnd -> GetControlBarManager()); 

	ASSERT(NULL != pManager);
	SetManager (pManager);

// Button-Groups definieren
CPtrArray *pPtrArray = pManager -> GetDefaultToolBarArray();

	for(int iCnt = 0; iCnt < pPtrArray -> GetSize(); iCnt++) {
	CTRiASToolBarManager::SECDefaultToolBar *pDefault = (CTRiASToolBarManager::SECDefaultToolBar *)((*pPtrArray)[iCnt]);

		ASSERT(NULL != pDefault);
		DefineBtnGroup (pDefault -> lpszTitle, pDefault -> nBtnCount, pDefault -> lpBtnIDs);
	}

// Must have at least 1 btn group defined.
	ASSERT(m_btnGroups.GetSize() > 0);

// Initialization
	CPropertyPage::OnInitDialog();

// Calc. where to create the toolbars on the page by positioning them
// slightly inside the IDC_TOOLBAR_FRAME static control.
CComboBox* pList = (CComboBox *) GetDlgItem(IDC_TOOLBAR_LIST);
WINDOWPLACEMENT wp;

	wp.length = sizeof(wp);
	GetDlgItem(IDC_TOOLBAR_FRAME)->GetWindowPlacement(&wp);

CRect rect = wp.rcNormalPosition;
int x = 6;			// in DBU
int y = 8;

	SECConvertDialogUnitsToPixels(*(GetFont()), x, y);
	rect.DeflateRect(x, y);

int nID = AFX_IDW_TOOLBAR + 0xaf;

	for(int i=0; i < m_btnGroups.GetSize(); i++, nID--)
	{
	// Create and initialise the toolbar
	SECBtnGroup *pGroup = (SECBtnGroup *)m_btnGroups[i];

		if(!pGroup->Create(this, m_pManager, nID))
			return FALSE;

	// Position and size the new toolbar.
	CRect r = rect;

		pGroup->GetWnd()->SetWindowPos(&wndTop, r.left, r.top, r.Width(), r.Height(), SWP_DRAWFRAME);
		pGroup->DoSize(r);

		if(i != 0)	// All toolbars are hidden except the very first one.
			pGroup->GetWnd()->ShowWindow(SW_HIDE);

	// Add the name of this toolbar to the listbox
		pList->AddString(pGroup->GetTitle());
	}
	pList->SetCurSel(0);
	return TRUE;
}

BOOL CTRiASCustomizeToolBar::OnSetActive()
{
	if(m_pManager) {
	// Put all toolbars into config mode.
		m_pManager->EnableConfigMode(TRUE);

	// Re-enable the main frame - so toolbar buttons can be dragged
		m_pManager->EnableMainFrame();

	// Don't allow buttons to be dropped on me.
		m_pManager->SetNoDropWnd(this);
	}

// EnableConfigMode will only work on those toolbars returned by
// the main frames GetControlBar function. Since my custom toolbars do
// not have the main frame as a parent, they will not be in the list.
// I therefore do this by hand.
CComboBox* pList = (CComboBox *) GetDlgItem(IDC_TOOLBAR_LIST);
int nIndex = pList->GetCurSel();

	if(nIndex != LB_ERR)
	{
		m_btnGroups[nIndex]->EnableConfigMode(TRUE);
		m_nCurSel = nIndex;
	}
	return TRUE;
}

void CTRiASCustomizeToolBar::OnReset() 
{
// The property sheet is being closed
	if(m_nCurSel != LB_ERR)
	{
		m_btnGroups[m_nCurSel]->EnableConfigMode(FALSE);
		m_nCurSel = LB_ERR;
	}

	SECToolBarCmdPage::OnReset();
}

void CTRiASCustomizeToolBar::OnSelchange() 
{
// The current selection has changed. I need to show the newly selected
// toolbar
CComboBox* pList = (CComboBox *) GetDlgItem(IDC_TOOLBAR_LIST);
int nIndex = pList->GetCurSel();

	if(nIndex == m_nCurSel)
		return;

	if(m_nCurSel != LB_ERR)
	{
		m_btnGroups[m_nCurSel]->EnableConfigMode(FALSE);
		m_nCurSel = LB_ERR;
	}

	for(int i=0; i<m_btnGroups.GetSize(); i++)
	{
	CWnd* pWnd = m_btnGroups[i]->GetWnd();

		if(i == nIndex)
		{
			m_btnGroups[i]->EnableConfigMode(TRUE);
			pWnd->ShowWindow(SW_SHOW);
			m_nCurSel = i;
		}
		else
			pWnd->ShowWindow(SW_HIDE);
	}
}

void CTRiASCustomizeToolBar::SetDescription(int nID)
{
// Sets the description to text to the flyby help text for the given item
CString strDescription;
int nIndex = 0;
CTRiASToolBarManager *pMgr = (CTRiASToolBarManager *)m_pManager; 

	ASSERT(NULL != pMgr);

	if (nID != -1 && SUCCEEDED(pMgr -> FindIndex4CommandID (nID, nIndex))) {
	WTRiASUIOwner UIOwner;
	LPTSTR lpsz = strDescription.GetBuffer(_MAX_PATH);

		if (SUCCEEDED(pMgr -> GetUIOwner (NULL, nIndex, UIOwner.ppi())) && 
			SUCCEEDED(UIOwner -> OnSelect (NULL, nID, lpsz, _MAX_PATH, NULL))) 
		{
			lpsz = _tcschr(lpsz, '\n');
			if (lpsz != NULL)
				*lpsz = '\0';
			strDescription.ReleaseBuffer();
		} else 
			strDescription.Empty();
	} else 
		strDescription.Empty();

	GetDlgItem(IDC_TOOLBAR_DESCRIPTION)->SetWindowText(strDescription);
}

#endif // defined(_USE_TOOLBARCUSTOMIZE)
