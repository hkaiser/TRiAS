// ToolbarsPage.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include <xtensnn.h>

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"		// SmartInterfaces
#include "fakemfc.hxx"		// die Erweiterung selbst
#include "MainFrm.h"
#include "ToolBarsPage.h"

#if defined(_USE_SEC_CLASSES)
#include <afxtempl.h>
#define __AFXCONV_H__
#include <afxpriv.h>		// CDockState et.al.
#include <sdocksta.h>
#include <tbarcust.h>
#include <tbarmgr.h>		// SECToolBarManager

#include "ToolBarManager.h"
#endif // _USE_SEC_CLASSES

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//
DefineSmartInterface(ControlToolBar);
DefineSmartInterface(EnumITRiASBar);

/////////////////////////////////////////////////////////////////////////////
// CToolBarsPage dialog

IMPLEMENT_DYNCREATE(CToolBarsPage, CPropertyPage)

CToolBarsPage::CToolBarsPage()
	: CPropertyPage(CToolBarsPage::IDD)
{
	m_psp.hInstance = _Module.GetResourceInstance();	// aus dieser DLL laden
	//{{AFX_DATA_INIT(CToolBarsPage)
	m_fShowToolTips = false;
	//}}AFX_DATA_INIT

	m_fCoolLook = TRIASUI_LEGACYLOOK;	
	m_iCurrIndex = -1;

#if defined(_USE_SEC_CLASSES)
	m_pControlBarManager = NULL;
#endif // _USE_SEC_CLASSES
}

CToolBarsPage::~CToolBarsPage()
{
	Terminate();
}

void CToolBarsPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolBarsPage)
	DDX_Control(pDX, IDC_COOLLOOK, m_pbCoolLook);
	DDX_Control(pDX, IDC_REMOVE, m_pbRemove);
	DDX_Control(pDX, IDC_RESETALL, m_pbResetAll);
	DDX_Control(pDX, IDC_TOOLBARNAME, m_ecToolBarName);
	DDX_Control(pDX, IDC_NEWTOOLBAR, m_pbNew);
	DDX_Control(pDX, IDC_RESET, m_pbReset);
	DDX_Control(pDX, IDC_TOOLBARLIST, m_lbToolBars);
	DDX_Check(pDX, IDC_TOOLTIPS, m_fShowToolTips);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolBarsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CToolBarsPage)
	ON_LBN_SELCHANGE(IDC_TOOLBARLIST, OnSelchangeToolbarlist)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_EN_KILLFOCUS(IDC_TOOLBARNAME, OnKillfocusToolbarname)
	ON_BN_CLICKED(IDC_RESET, OnResetToolbar)
	ON_BN_CLICKED(IDC_RESETALL, OnResetAllToolbars)
	ON_BN_CLICKED(IDC_COOLLOOK, OnCoollook)
	ON_BN_CLICKED(IDC_TOOLTIPS, OnTooltips)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_TOOLBARNAME, OnChangeToolbarname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarsPage message handlers

BOOL CToolBarsPage::OnInitDialog() 
{
// ToolBars einbinden
CMainFrame *pWnd = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());

	ASSERT(NULL != pWnd);

CTRiASToolBarManager *pManager = DYNAMIC_DOWNCAST(CTRiASToolBarManager, pWnd -> GetControlBarManager()); 

	ASSERT(NULL != pManager);
	SetManager (pManager);

	m_fShowToolTips = pWnd -> ShowToolTips();
	m_fCoolLook = pWnd -> CoolLookEnabled();

// jetzt fertig initialisieren
	CPropertyPage::OnInitDialog();
	FillToolbarList();

// sonstige Controls initialisieren
	m_pbNew.EnableWindow (false);
	m_pbRemove.EnableWindow (false);

#if !defined(_USE_SEC_CLASSES)
	m_pbReset.EnableWindow (false);

	m_pbCoolLook.SetCheck (0);
	m_pbCoolLook.EnableWindow (false);
	m_pbCoolLook.ShowWindow (SW_HIDE);
#else
	switch (m_fCoolLook) {
	case TRIASUI_LEGACYLOOK:
		m_pbCoolLook.SetCheck (0);
		break;

	case TRIASUI_COOLLOOK:
		m_pbCoolLook.SetCheck (2);
		break;

	case TRIASUI_OVERALLCOOLLOOK|TRIASUI_COOLLOOK:
		m_pbCoolLook.SetCheck (1);
		break;
	}

	ASSERT_VALID(m_pControlBarManager);
	m_pControlBarManager -> EnableMainFrame();
	m_pControlBarManager -> EnableConfigMode(TRUE);
#endif // _USE_SEC_CLASSES

	return true;
}

// ListBox füllen
BOOL CToolBarsPage::FillToolbarList()
{
	m_lbToolBars.ResetContent();		// erstmal alles freigeben

int iIndex = -1;

	COM_TRY {
	WEnumITRiASBar Bars;
	WTRiASBar Bar;
	int i = 0;
	CMainFrame *pWnd = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());

		ASSERT(NULL != pWnd);
		THROW_FAILED_HRESULT(pWnd -> GetEnumTRiASToolBars (Bars.ppi()));
		for (Bars -> Reset(); S_OK == Bars -> Next (1, Bar.ppi(), 0); i++) {
		char cbName[64];
		DWORD dwStyle;
		UINT uiID = 0;
		WTRiASToolBar ToolBar (Bar);		// throws HRESULT
		HRESULT hr = ToolBar -> GetBarStyle (cbName, sizeof(cbName), NULL, &dwStyle, NULL);

			if (SUCCEEDED(hr)) {
				ToolBar -> GetBarID (&uiID);
				iIndex = m_lbToolBars.AddString (cbName);
				m_lbToolBars.SetCheck (iIndex, dwStyle & WS_VISIBLE ? 1 : 0);
			}
		}

	// ersten Eintrag aktivieren
		if (iIndex >= 0) 
			ActivateEntry (0);

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}
	
///////////////////////////////////////////////////////////////////////////////
// Einen Eintrag aktivieren
bool CToolBarsPage::ActivateEntry (int iIndex)
{
	ASSERT(iIndex >= 0 && iIndex < m_lbToolBars.GetCount());

CString str;

// neuen Eintrag ausgewählt
	m_iCurrIndex = iIndex;

	if (m_lbToolBars.GetCurSel() != iIndex) 
		m_lbToolBars.SetCurSel (iIndex);

// Namen der Toolbar setzen
	m_lbToolBars.GetText (iIndex, str);
	m_ecToolBarName.SetWindowText (str);
	m_ecToolBarName.SetReadOnly (true);
	return true;
}

void CToolBarsPage::OnSelchangeToolbarlist() 
{
int iIndex = m_lbToolBars.GetCurSel();

	if (0 <= iIndex) {
		ActivateEntry (iIndex);
		UpdateShownToolBars (iIndex);
	}
}

bool CToolBarsPage::UpdateShownToolBars (int iIndex)
{
// Namen der Toolbar besorgen
CString str;

	m_lbToolBars.GetText (iIndex, str);

WTRiASToolBar ToolBar;
HRESULT hr = ((CMainFrame *)AfxGetMainWnd()) -> GetTRiASToolBar (str, ToolBar.ppi());

	if (S_OK == hr)	{
	DWORD dwStyle = 0L;
	DWORD dwStyleEx = 0L;

		ToolBar -> GetBarStyle (NULL, 0L, NULL, &dwStyle, &dwStyleEx);
	
	bool fVisible = (dwStyle & WS_VISIBLE) ? true : false;
	bool fChecked = m_lbToolBars.GetCheck (iIndex) ? true : false;

		if (fVisible && !fChecked)
			ToolBar -> SetBarStyle (NULL, dwStyle & ~WS_VISIBLE, dwStyleEx, false);
		else if (!fVisible & fChecked) {
			ToolBar -> SetBarStyle (NULL, dwStyle | WS_VISIBLE, dwStyleEx, false);
			BringWindowToTop();
		}

	bool fPredefined = (dwStyleEx & TRIASTOOLBAR_PREDEFINED) ? true : false;

		m_ecToolBarName.SetReadOnly (fPredefined);
		m_pbRemove.EnableWindow (!fPredefined);
	}
	return true;
}

void CToolBarsPage::OnRemove() 
{
// Namen der Toolbar besorgen
int iIndex = m_lbToolBars.GetCurSel();

	if (0 > iIndex) return;

CString str;

	m_lbToolBars.GetText (iIndex, str);

	if (SUCCEEDED(RemoveBar (str))) {
	// aus Listbox herausnehmen
		m_lbToolBars.DeleteString (iIndex);
		if (0 < m_lbToolBars.GetCount()) 
			m_lbToolBars.SetCurSel(0);			// ersten aktivieren
	}
}

HRESULT CToolBarsPage::RemoveBar (LPCSTR pcName)
{
WTRiASToolBar ToolBar;
CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
HRESULT hr = pMainFrm -> GetTRiASToolBar (pcName, ToolBar.ppi());

	if (S_OK == hr)	{	// ausklinken und freigeben	
	// Toolbar sofort ausblenden
	DWORD dwStyle = 0L;
	DWORD dwStyleEx = 0L;

		ToolBar -> GetBarStyle (NULL, 0L, NULL, &dwStyle, &dwStyleEx);
		ToolBar -> SetBarStyle (NULL, dwStyle & ~WS_VISIBLE, dwStyleEx, false);

	// aus Liste herausnehmen
		pMainFrm -> RemoveBar (ToolBar);
	}
	return hr;
}

void CToolBarsPage::OnKillfocusToolbarname() 
{
	if (!m_ecToolBarName.GetModify()) return;	// nicht verändert

// Namen der Toolbar besorgen
int iIndex = m_lbToolBars.GetCurSel();

	if (0 > iIndex) return;

CString strOld;
CString strNew;

	m_lbToolBars.GetText (iIndex, strOld);
	m_ecToolBarName.GetWindowText (strNew);

WTRiASToolBar ToolBar;
CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
HRESULT hr = pMainFrm -> GetTRiASToolBar (strOld, ToolBar.ppi());

	if (S_OK == hr)	{	// ausklinken und freigeben	
	DWORD dwStyle = 0L, dwStyleEx = 0L;

		ToolBar -> GetBarStyle (NULL, 0, NULL, &dwStyle, &dwStyleEx);
		ToolBar -> SetBarStyle (strNew, dwStyle, dwStyleEx, false);

	int iIndex = m_lbToolBars.GetCurSel();

		if (0 <= iIndex) {
		int iIsChecked = m_lbToolBars.GetCheck (iIndex);

			m_lbToolBars.DeleteString (iIndex);
			m_lbToolBars.InsertString (iIndex, strNew);
			m_lbToolBars.SetCheck (iIndex, iIsChecked);
		}
	}
}

void CToolBarsPage::OnResetToolbar() 
{
#if defined(_USE_SEC_CLASSES)
// The Reset/Delete button has been clicked. Take appropriate action.
// Namen der Toolbar besorgen
int iIndex = m_lbToolBars.GetCurSel();

	if (0 > iIndex) return;

CString str;

	m_lbToolBars.GetText (iIndex, str);

WTRiASToolBar ToolBar;
HRESULT hr = ((CMainFrame *)AfxGetMainWnd()) -> GetTRiASToolBar (str, ToolBar.ppi());

	if (S_OK == hr)	{
	UINT nID = 0L;
	
		if (FAILED(ToolBar -> GetBarID (&nID))) 
			return;
	
		if(nID >= SEC_IDW_FIRST_USER_TOOLBAR) {
		// A user toolbar so delete it.
			RemoveBar(str);
			if (0 < m_lbToolBars.GetCount()) 
				m_lbToolBars.SetCurSel(0);			// ersten aktivieren
		} else {
		// A system toolbar so reset the toolbars button state
			ATLTRY(WControlToolBar(ToolBar) -> Reset());	// throws hr
		}
	}
#endif // _USE_SEC_CLASSES
}

void CToolBarsPage::OnResetAllToolbars() 
{
#if defined(_USE_SEC_CLASSES)
// The Reset/Delete button has been clicked. Take appropriate action.
// Namen der Toolbar besorgen
int iIndex = m_lbToolBars.GetCurSel();

	if (0 > iIndex) return;

CString str;

	m_lbToolBars.GetText (iIndex, str);

WEnumITRiASBar Bars;
HRESULT hr = ((CMainFrame *)AfxGetMainWnd()) -> GetEnumTRiASToolBars (Bars.ppi());

	if (S_OK == hr)	{
	WTRiASBar Bar;
	int i = 0;
	bool fRemoved = false;

		for (Bars -> Reset(); S_OK == Bars -> Next (1, Bar.ppi(), 0); i++) {
		WTRiASToolBar ToolBar (Bar);
		UINT nID = 0L;
	
			if (FAILED(ToolBar -> GetBarID (&nID))) 
				return;
		
			if(nID >= SEC_IDW_FIRST_USER_TOOLBAR) {
			// A user toolbar so delete it.
			char cbName[64];
			WTRiASToolBar ToolBar (Bar);		// throws HRESULT
			
				VERIFY(SUCCEEDED(ToolBar -> GetBarStyle (cbName, sizeof(cbName), NULL, NULL, NULL)));
				RemoveBar (cbName);
				if (i == m_lbToolBars.GetCurSel())
					fRemoved = true;
			} else {
			// A system toolbar so reset the toolbars button state
				ATLTRY(WControlToolBar(ToolBar) -> Reset());	// throws hr
			}
		}
		if (fRemoved && 0 < m_lbToolBars.GetCount())
			m_lbToolBars.SetCurSel(0);			// ersten aktivieren
	}
#endif // _USE_SEC_CLASSES
}

void CToolBarsPage::OnOK() 
{
#if defined(_USE_SEC_CLASSES)
	switch (m_pbCoolLook.GetCheck()) {
	case 0:
		m_fCoolLook = TRIASUI_LEGACYLOOK;
		break;

	case 1:
		m_fCoolLook = TRIASUI_OVERALLCOOLLOOK;
		break;

	default:
	case 2:
		m_fCoolLook = TRIASUI_COOLLOOK;
		break;
	}

CMainFrame *pWnd = (CMainFrame *)AfxGetMainWnd();

	ASSERT(NULL != pWnd);
	pWnd -> EnableCoolLook (m_fCoolLook);
	pWnd -> EnableToolTips (m_fShowToolTips);

	Terminate();
#endif // _USE_SEC_CLASSES

	SetModified (FALSE);
}

void CToolBarsPage::OnCancel() 
{
#if defined(_USE_SEC_CLASSES)
	Terminate();
#endif // _USE_SEC_CLASSES
}

#if defined(_USE_SEC_CLASSES)
void CToolBarsPage::Terminate(void)
{
	if (NULL != m_pControlBarManager) {
		ASSERT_VALID(m_pControlBarManager);
		m_pControlBarManager -> EnableConfigMode(FALSE);
		m_pControlBarManager -> DisableMainFrame();
		m_pControlBarManager = NULL;
	}
}

void CToolBarsPage::SetManager(SECToolBarManager* pManager)
{
	ASSERT_VALID(pManager);
	ASSERT_KINDOF(SECToolBarManager, pManager);

	m_pControlBarManager = pManager;
}
#endif // _USE_SEC_CLASSES

void CToolBarsPage::OnCoollook() 
{
	SetModified (TRUE);
}

void CToolBarsPage::OnTooltips() 
{
	SetModified (TRUE);
}

BOOL CToolBarsPage::OnSetActive()
{
	if(m_pControlBarManager) {
		m_pControlBarManager->EnableConfigMode(TRUE);		// Put all toolbars into config mode.
		m_pControlBarManager->EnableMainFrame();			// Re-enable the main frame - so toolbar buttons can be dragged
	}
	return FillToolbarList();
}

BOOL CToolBarsPage::OnKillActive()
{
	if(m_pControlBarManager) {
		m_pControlBarManager -> EnableConfigMode(FALSE);
		m_pControlBarManager -> DisableMainFrame();
	}
	return CPropertyPage::OnKillActive();
}

void CToolBarsPage::OnReset() 
{
// The property sheet is being closed
	Terminate();
	CPropertyPage::OnReset();
}

void CToolBarsPage::OnChangeToolbarname() 
{
	SetModified(TRUE);
}
