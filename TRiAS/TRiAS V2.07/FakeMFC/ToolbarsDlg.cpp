// ToolbarsDlg.cpp : implementation file
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
#include "ToolBarsDlg.h"

#if defined(_USE_SEC_CLASSES)
#include <afxtempl.h>
#define __AFXCONV_H__
#include <afxpriv.h>		// CDockState et.al.
#include <sdocksta.h>
#include <tbarcust.h>
#include <tbarmgr.h>		// SECToolBarManager
#endif // _USE_SEC_CLASSES

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//
DefineSmartInterface(ControlToolBar);

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDlg dialog

CToolBarsDlg::CToolBarsDlg(
	CMainFrame* pParent, IEnumITRiASBar *pIEnum, bool fShowTT, bool fCoolLook)
	: CDialog(CToolBarsDlg::IDD, pParent), m_Bars(pIEnum)
{
	//{{AFX_DATA_INIT(CToolBarsDlg)
	m_fShowToolTips = fShowTT;
	//}}AFX_DATA_INIT

	m_fCoolLook = fCoolLook;	
	m_iCurrIndex = -1;

#if defined(_USE_SEC_CLASSES)
	m_pControlBarManager = NULL;
#endif // _USE_SEC_CLASSES
}

void CToolBarsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolBarsDlg)
	DDX_Control(pDX, IDC_COOLLOOK, m_pbCoolLook);
	DDX_Control(pDX, IDC_REMOVE, m_pbRemove);
	DDX_Control(pDX, IDC_CUSTOMIZE, m_pbCustomize);
	DDX_Control(pDX, IDC_TOOLBARNAME, m_ecToolBarName);
	DDX_Control(pDX, IDC_NEWTOOLBAR, m_pbNew);
	DDX_Control(pDX, IDC_RESET, m_pbReset);
	DDX_Control(pDX, IDC_TOOLBARLIST, m_lbToolBars);
	DDX_Check(pDX, IDC_TOOLTIPS, m_fShowToolTips);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolBarsDlg, CDialog)
	//{{AFX_MSG_MAP(CToolBarsDlg)
	ON_BN_CLICKED(IDC_CUSTOMIZE, OnCustomize)
	ON_LBN_SELCHANGE(IDC_TOOLBARLIST, OnSelchangeToolbarlist)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_EN_KILLFOCUS(IDC_TOOLBARNAME, OnKillfocusToolbarname)
	ON_BN_CLICKED(IDC_RESET, OnResetToolbar)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDlg message handlers

BOOL CToolBarsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// ListBox füllen
int iIndex = -1;

	try {
	ITRiASBar *pIBar = NULL;
	int i = 0;

		for (m_Bars -> Reset();
			 S_OK == m_Bars -> Next (1, &pIBar, 0); i++)
		{
		char cbName[64];
		DWORD dwStyle;
		UINT uiID = 0;
		WTRiASToolBar ToolBar = pIBar;		// throws HRESULT
		HRESULT hr = ToolBar -> GetBarStyle (cbName, sizeof(cbName), NULL, &dwStyle, NULL);

			if (SUCCEEDED(hr)) {
				ToolBar -> GetBarID (&uiID);
				iIndex = m_lbToolBars.AddString (cbName);
				m_lbToolBars.SetCheck (iIndex, dwStyle & WS_VISIBLE ? 1 : 0);
			}
			pIBar -> Release();
			pIBar = NULL;
		}

	// ersten Eintrag aktivieren
		if (iIndex >= 0) 
			ActivateEntry (0);
	} catch (_com_error& hr) {
		UNUSED(hr);
		ASSERT(_COM_ERROR(hr) == S_OK);
	}
	
// sonstige Controls initialisieren
	m_pbNew.EnableWindow (false);
	m_pbRemove.EnableWindow (false);
#if !defined(_USE_SEC_CLASSES)
	m_pbReset.EnableWindow (false);

	m_pbCoolLook.SetCheck (0);
	m_pbCoolLook.EnableWindow (false);
	m_pbCoolLook.ShowWindow (SW_HIDE);
#else
	m_pbCoolLook.SetCheck (m_fCoolLook);

	ASSERT_VALID(m_pControlBarManager);
	m_pControlBarManager -> EnableMainFrame();
	m_pControlBarManager -> EnableConfigMode(TRUE);
#endif // _USE_SEC_CLASSES

// Anpassen nur, wenn Projekt offen ist
	TRY {
	CString strPrj;
	LPSTR pBuffer = strPrj.GetBuffer (_MAX_PATH);

		if (NULL == DEX_GetActiveProject (pBuffer))
			m_pbCustomize.EnableWindow (false);
	} CATCH (CMemoryException, e) {
		return false;
	} END_CATCH

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Einen Eintrag aktivieren
bool CToolBarsDlg::ActivateEntry (int iIndex)
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

void CToolBarsDlg::OnCustomize() 
{
#if defined(_USE_SEC_CLASSES)
	m_fCoolLook = m_pbCoolLook.GetCheck() ? TRUE : FALSE;
	Terminate();
#endif // _USE_SEC_CLASSES

	EndDialog (IDC_CUSTOMIZE);
}

void CToolBarsDlg::OnSelchangeToolbarlist() 
{
int iIndex = m_lbToolBars.GetCurSel();

	if (0 <= iIndex) {
		ActivateEntry (iIndex);
		UpdateShownToolBars (iIndex);
	}
}

bool CToolBarsDlg::UpdateShownToolBars (int iIndex)
{
// Namen der Toolbar besorgen
CString str;

	m_lbToolBars.GetText (iIndex, str);

WTRiASToolBar ToolBar;
HRESULT hr = ((CMainFrame *)GetParent()) -> GetTRiASToolBar (str, ToolBar.ppi());

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

void CToolBarsDlg::OnRemove() 
{
// Namen der Toolbar besorgen
int iIndex = m_lbToolBars.GetCurSel();

	if (0 > iIndex) return;

CString str;

	m_lbToolBars.GetText (iIndex, str);

WTRiASToolBar ToolBar;
CMainFrame *pMainFrm = (CMainFrame *)GetParent();
HRESULT hr = pMainFrm -> GetTRiASToolBar (str, ToolBar.ppi());

	if (S_OK == hr)	{	// ausklinken und freigeben	
	// aus Listbox herausnehmen
		m_lbToolBars.DeleteString (iIndex);

	// Toolbar sofort ausblenden
	DWORD dwStyle = 0L;
	DWORD dwStyleEx = 0L;

		ToolBar -> GetBarStyle (NULL, 0L, NULL, &dwStyle, &dwStyleEx);
		ToolBar -> SetBarStyle (NULL, dwStyle & ~WS_VISIBLE, dwStyleEx, false);

	// aus Liste herausnehmen
		pMainFrm -> RemoveBar (ToolBar);
	}
}

void CToolBarsDlg::OnKillfocusToolbarname() 
{
	if (!m_ecToolBarName.GetModify()) return;	// nicht verändert

CString str;

	m_ecToolBarName.GetWindowText (str);

WTRiASToolBar ToolBar;
CMainFrame *pMainFrm = (CMainFrame *)GetParent();
HRESULT hr = pMainFrm -> GetTRiASToolBar (str, ToolBar.ppi());

	if (S_OK == hr)	{	// ausklinken und freigeben	
	DWORD dwStyle = 0L, dwStyleEx = 0L;

		ToolBar -> GetBarStyle (NULL, 0, NULL, &dwStyle, &dwStyleEx);
		ToolBar -> SetBarStyle (str, dwStyle, dwStyleEx, false);

	int iIndex = m_lbToolBars.GetCurSel();

		if (0 <= iIndex) {
			m_lbToolBars.DeleteString (iIndex);
			m_lbToolBars.InsertString (iIndex, str);
		}
	}
}

void CToolBarsDlg::OnResetToolbar() 
{
#if defined(_USE_SEC_CLASSES)
// The Reset/Delete button has been clicked. Take appropriate action.
// Namen der Toolbar besorgen
int iIndex = m_lbToolBars.GetCurSel();

	if (0 > iIndex) return;

CString str;

	m_lbToolBars.GetText (iIndex, str);

WTRiASToolBar ToolBar;
HRESULT hr = ((CMainFrame *)GetParent()) -> GetTRiASToolBar (str, ToolBar.ppi());

	if (S_OK == hr)	{
	UINT nID = 0L;
	
		if (FAILED(ToolBar -> GetBarID (&nID))) 
			return;
	
		if(nID >= SEC_IDW_FIRST_USER_TOOLBAR) {
		// A user toolbar so delete it.
			OnRemove();
		} else {
		// A system toolbar so reset the toolbars button state
			try {
			WControlToolBar TB (ToolBar);	// throws hr

				TB -> Reset();
			} catch (_com_error &) {
				;
			}
		}
	}
#endif // _USE_SEC_CLASSES
}

void CToolBarsDlg::OnOK() 
{
#if defined(_USE_SEC_CLASSES)
	m_fCoolLook = m_pbCoolLook.GetCheck() ? TRUE : FALSE;
	Terminate();
#endif // _USE_SEC_CLASSES

	CDialog::OnOK();
}

void CToolBarsDlg::OnClose() 
{
#if defined(_USE_SEC_CLASSES)
	Terminate();
#endif // _USE_SEC_CLASSES

	CDialog::OnClose();
}

#if defined(_USE_SEC_CLASSES)
void CToolBarsDlg::Terminate(void)
{
	ASSERT_VALID(m_pControlBarManager);
	m_pControlBarManager -> DisableMainFrame();
	m_pControlBarManager -> EnableConfigMode(FALSE);
}

void CToolBarsDlg::SetManager(SECToolBarManager* pManager)
{
	ASSERT_VALID(pManager);
	ASSERT_KINDOF(SECToolBarManager, pManager);

	m_pControlBarManager = pManager;
}
#endif // _USE_SEC_CLASSES


