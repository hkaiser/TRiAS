// TRiASToolBar.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include "strings.h"

#include <xtensnn.h>

#include <itoolbar.h>
#include <dtoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#if defined(_USE_SEC_CLASSES)
#if !defined(_SEC_VER) || _SEC_VER < 0x0600
#include <secdll.h>
#include <sbardock.h>
#endif // !defined(_SEC_VER) || _SEC_VER < 0x0600
#endif // _USE_SEC_CLASSES

#include "Wrapper.h"		// SmartInterfaces
#include "mainfrm.h"
#include "fakemfc.hxx"

#include "TRiASCmdUI.h"
#include "TRiASToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTRiASToolBar, SECCustomToolBar);

// Helperfunktion -------------------------------------------------------------
void CTRiASToolBar::_GetButtonEx (int nIndex, TBBUTTON* pButton) const
{
CTRiASToolBar* pBar = (CTRiASToolBar*)this;

#if !defined(_USE_SEC_CLASSES)
	VERIFY(pBar -> DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)pButton));
#else
	VERIFY(SUCCEEDED(m_pMainFrm -> GetButton (this, nIndex, pButton)));
#endif // _USE_SEC_CLASSES

	// TBSTATE_ENABLED == TBBS_DISABLED so invert it
	pButton->fsState ^= TBSTATE_ENABLED;
}

void CTRiASToolBar::_SetButtonEx (int nIndex, TBBUTTON* pButton)
{
// get original button state
TBBUTTON button;

#if !defined(_USE_SEC_CLASSES)
	VERIFY(DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)&button));
#else
	VERIFY(SUCCEEDED(m_pMainFrm -> GetButton (this, nIndex, &button)));
#endif // _USE_SEC_CLASSES

// prepare for old/new button comparsion
	button.bReserved[0] = 0;
	button.bReserved[1] = 0;

// TBSTATE_ENABLED == TBBS_DISABLED so invert it
	pButton->fsState ^= TBSTATE_ENABLED;
	pButton->bReserved[0] = 0;
	pButton->bReserved[1] = 0;

// nothing to do if they are the same
	if (memcmp(pButton, &button, sizeof(TBBUTTON)) != 0) {
	// don't redraw everything while setting the button
	DWORD dwStyle = GetStyle();

		ModifyStyle(WS_VISIBLE, 0);
#if !defined(_USE_SEC_CLASSES)
		VERIFY(DefWindowProc(TB_DELETEBUTTON, nIndex, 0));
		VERIFY(DefWindowProc(TB_INSERTBUTTON, nIndex, (LPARAM)pButton));
#else
		{
		WTRiASUIOwner UIOwner;

			VERIFY(SUCCEEDED(m_pMainFrm -> GetUIOwner (this, nIndex, UIOwner.ppi())));
			VERIFY(SUCCEEDED(m_pMainFrm -> DeleteButton (this, nIndex)));
			VERIFY(SUCCEEDED(m_pMainFrm -> InsertButton (this, nIndex, pButton, UIOwner)));
		}
#endif // _USE_SEC_CLASSES
		ModifyStyle(0, dwStyle & WS_VISIBLE);

	// invalidate appropriate parts
		if (((pButton->fsStyle ^ button.fsStyle) & TBSTYLE_SEP) ||
			((pButton->fsStyle & TBSTYLE_SEP) && pButton->iBitmap != button.iBitmap))
		{
		// changing a separator
			Invalidate(FALSE);
		}
		else {
		// invalidate just the button
		CRect rect;

#if !defined(_USE_SEC_CLASSES)
			if (DefWindowProc(TB_GETITEMRECT, nIndex, (LPARAM)&rect))
				InvalidateRect(rect, FALSE);    // don't erase background
#else
			GetItemRect (nIndex, &rect);
			InvalidateRect(rect, FALSE);		// don't erase background
#endif // _USE_SEC_CLASSES
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASToolBar

CTRiASToolBar::CTRiASToolBar(ITRiASToolBar *pIBar)
{
	m_pMainFrm = (CMainFrame *)AfxGetMainWnd();
	m_uiID = 0;
	m_pIBar = pIBar;		// kein AddRef()!, fully contained
	m_fHasDummySep = false;
	m_dwFlags = 0L;
	m_bAutoDelete = true;
}

CTRiASToolBar::~CTRiASToolBar()
{
	ASSERT_VALID(this);

	m_Owners.erase();		// alle UIOwner freigeben
	FreeInstalledControls();

#if defined(_USE_SEC_CLASSES)
	if (IsWindow(m_pMainFrm -> GetSafeHwnd()))
		m_pMainFrm -> RecalcLayout();
#endif // _USE_SEC_CLASSES

	m_bAutoDelete = false;
	DestroyWindow();		// avoid PostNcDestroy problems

	if (m_pDockSite != NULL) {
		m_pDockSite->RemoveControlBar(this);
		m_pDockSite = NULL;
	} 

#if defined(_USE_SEC_CLASSES)
	if (m_pDockBar && m_pDockBar->IsKindOf(RUNTIME_CLASS(SECDockBar)))
		((SECDockBar *)m_pDockBar) -> m_pBarDocked = NULL;
#endif // _USE_SEC_CLASSES

	m_pMainFrm = NULL;		// wird nicht mehr gebraucht
	m_pIBar = NULL;
}


BEGIN_MESSAGE_MAP(CTRiASToolBar, SECCustomToolBar)
	//{{AFX_MSG_MAP(CTRiASToolBar)
	ON_WM_CONTEXTMENU()
	ON_WM_NCDESTROY()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionalität

int CTRiASToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (SECCustomToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
// speichern des FensterID's und der anderen Parameter
	m_uiID = (UINT)(lpCreateStruct -> hMenu);

#if defined(_USE_SEC_CLASSES)
// jetzt beim MainFrame registrieren
	m_pMainFrm -> AddNewBar (m_pIBar);
#endif // _USE_SEC_CLASSES

	return 0;
}

HRESULT CTRiASToolBar::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
	ASSERT_VALID(m_pMainFrm);

#if !defined(_USE_SEC_CLASSES)
	m_uiID = m_pMainFrm -> GetNextBarID();
	if (!Create (m_pMainFrm, WS_CHILD|CBRS_ALIGN_TOP|CBRS_FLOATING, m_uiID))
		return E_FAIL;

	SetBarStyle(GetBarStyle() | (CBRS_TOOLTIPS|CBRS_SIZE_FIXED));
	EnableDocking (CBRS_ALIGN_ANY);

	m_pMainFrm -> AddNewBar (m_pIBar);		// jetzt hier, damit alle von außen das geleiche tun können
	m_pMainFrm -> ShowControlBar (this, false, false);
	m_pMainFrm -> DockControlBar (this);

TBBUTTON tb = { 25, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0, };
CToolBarCtrl &rTB = GetToolBarCtrl();

	rTB.SetButtonSize (CSize(24, 23));

HRESULT hr = (rTB.InsertButton (0, &tb)) ? NOERROR : S_FALSE;

	if (S_OK == hr)			// leeres Feld einfügen
		m_fHasDummySep = true;
#endif // _USE_SEC_CLASSES

	return NOERROR;
}

HRESULT CTRiASToolBar::SetBarID (int iCtrlID, BOOL fAdjustWnd)
{
#if !defined(_USE_SEC_CLASSES)
UINT uiOldID = m_uiID;

	if (fAdjustWnd) {
		uiOldID = SetDlgCtrlID (iCtrlID);
		ASSERT(uiOldID == m_uiID);
	}

	if ((int)m_uiID != iCtrlID) {
		m_uiID = (UINT)iCtrlID;
		return m_pMainFrm -> RemapBarID (m_pIBar, uiOldID, m_uiID);
	}
	
	return S_OK;
#else
// nicht mehr einstellbar, da intern vorgegeben
	return S_OK;	
#endif // !_USE_SEC_CLASSES
}

HRESULT CTRiASToolBar::RemoveBar (void)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
	ASSERT_VALID(m_pMainFrm);

	return m_pMainFrm -> RemoveBar (m_pIBar);		// deletes this object !
}

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT CTRiASToolBar::GetBarStyleEx (LPSTR pName, ULONG ulLen, ULONG *pulWritten, 
									  DWORD *pdwStyle, DWORD *pdwStyleEx)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

bool fOK = false;

	if (NULL != pdwStyle) {
	// Style abfragen
		*pdwStyle = GetBarStyle();
		if (GetStyle() & WS_VISIBLE)
			*pdwStyle |= WS_VISIBLE;
		else
			*pdwStyle &= ~WS_VISIBLE;

		fOK = true;
	}

	if (NULL != pdwStyleEx) {
		*pdwStyleEx = m_dwFlags;
#if defined(_USE_SEC_CLASSES)
		*pdwStyleEx |= m_dwExStyle;
#endif // _USE_SEC_CLASSES
	}

	if (NULL != pName) {
	// Caption abfragen
	int iLen = GetWindowText (pName, ulLen);

		if (pulWritten) *pulWritten = iLen;
		fOK = true;
	}

return fOK ? S_OK : S_FALSE;
}

HRESULT CTRiASToolBar::SetBarStyleEx (LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

// Sichtbar/unsichtbar
bool fWasVisible = (GetStyle() & WS_VISIBLE) ? true : false;
bool fMadeVisible = (WS_VISIBLE & dwStyle) ? true : false;

// Style ändern
#if _MSC_VER >= 1200
	dwStyle &= CBRS_ALL;
#endif // _MSC_VER >= 1200
	SetBarStyle (dwStyle);
	m_pMainFrm -> ShowControlBar (this, fMadeVisible, fDelay);

// sonstige Flags
#if !defined(_USE_SEC_CLASSES)
	m_dwFlags = dwStyleEx;
#else
	m_dwFlags = dwStyleEx & TRIASTOOLBAR_FLAGS;		// TRiASExFlags
	SetExBarStyle (dwStyleEx & ~TRIASTOOLBAR_FLAGS, fWasVisible && fMadeVisible);	// SEC-ExFlags
	if(m_dwExStyle & CBRS_EX_COOLBORDERS)
		Invalidate();

	if (fWasVisible || fMadeVisible)
		m_pMainFrm -> DelayRecalcLayout();		// evl. neu zeichnen
#endif // _USE_SEC_CLASSES

// Caption neu setzen
	if (NULL != pcName)		
		SetWindowText (pcName);

	return NOERROR;
}

HRESULT CTRiASToolBar::FloatBar (const POINT &pt, DWORD dwStyle)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));
	ASSERT_VALID(m_pMainFrm);

	m_pMainFrm -> FloatControlBar (this, pt, dwStyle);
	return NOERROR;
}

HRESULT CTRiASToolBar::DockBar (UINT uiWhere, LPCRECT pcRc)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));
	ASSERT_VALID(m_pMainFrm);

	m_pMainFrm -> DockControlBar (this, uiWhere, pcRc);
	return NOERROR;
}

// Hinzufügen einer Bitmap zur Toolbar, liefert Index des ersten Buttons der 
// Bitmap
HRESULT CTRiASToolBar::AddBitmap (HINSTANCE hInst, UINT uiRsc, int nNumButtons, int *piOffset)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

	if (NULL != piOffset) *piOffset = -1;	// für alle Fälle

#if !defined(_USE_SEC_CLASSES)
// Größen für das Control ausrechnen
HBITMAP hBmp = NULL;

	if (NULL == hInst)
		hBmp = (HBITMAP)uiRsc;
	else {
	HRSRC hRsrcImageWell = ::FindResource(hInst, (LPCSTR)uiRsc, RT_BITMAP);
	
		if (hRsrcImageWell == NULL)
			return E_FAIL;		// Bitmap not found

		hBmp = AfxLoadSysColorBitmap(hInst, hRsrcImageWell);
	}
	if (NULL == hBmp) return E_FAIL;

// need complete bitmap size to determine size of images
BITMAP bitmap;

	VERIFY(::GetObject(hBmp, sizeof(BITMAP), &bitmap));

int iWidth = bitmap.bmWidth / nNumButtons;
int iHeight = bitmap.bmHeight;

CSize sizeImage(iWidth, iHeight+1);
CSize sizeButton(iWidth + 7, iHeight + 7);

	SetSizes(sizeButton, sizeImage);

// Bitmap zu Control hinzufügen
TBADDBITMAP tbab;

	tbab.hInst = NULL;
	tbab.nID = (UINT)hBmp;

int iOffset = (int) DefWindowProc(TB_ADDBITMAP, (WPARAM)nNumButtons, (LPARAM)&tbab);

	if (NULL != piOffset) *piOffset = iOffset;

	return NOERROR;
#else
// einfach weiterreichen
	return m_pMainFrm -> AddBitmap (hInst, uiRsc, nNumButtons, piOffset);
#endif // _USE_SEC_CLASSES
}

HRESULT CTRiASToolBar::AddButtons (
	const TBBUTTON *pBttns, int iCnt, ITRiASUIOwner *pIOwner)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));
	ASSERT(0 < iCnt);
	ASSERT(NULL != pBttns);

// jetzt Owner zusammen mit dem ID speichern ...
	for (int i = 0; i < iCnt; i++) {
		if (pBttns[i].fsStyle & TBSTYLE_SEP && 0 == pBttns[i].idCommand)
			continue;		// Separators not handled here

	pair<UIOwners::iterator, bool> p = m_Owners.insert (pBttns[i].idCommand, pIOwner);

		ASSERT(p.second);
		if (!p.second)
			return ResultFromScode (E_FAIL);
	}

// ... und zur Toolbar hinzufügen
#if !defined(_USE_SEC_CLASSES)
// wenn dieses der erste Zugriff ist, dann Separator entfernen
	if (m_fHasDummySep) {
		DeleteItem (0);
		m_fHasDummySep = false;
	}

CToolBarCtrl &rTB = GetToolBarCtrl();
HRESULT hr = rTB.AddButtons (iCnt, const_cast<TBBUTTON *>(pBttns)) ? NOERROR : ResultFromScode (S_FALSE);

// jetzt Controls installieren
DWORD dwStyle = GetBarStyle() & CBRS_ALIGN_ANY;

	for (int j = 0; j < iCnt; j++) {
		if (pBttns[j].fsStyle & TBSTYLE_SEP) {
			if (0 == pBttns[j].idCommand)
				continue;		// Separators not handled here
			
			if (0 != pBttns[j].dwData) {
			HRESULT hr1 = reinterpret_cast<ITRiASBarInstallControl *>(pBttns[j].dwData) -> 
							InstallControl (m_pIBar, pBttns[j].idCommand, dwStyle);
				
				if (SUCCEEDED(hr1)) {		// Enable/Disable des neuen Controls
				CWnd *pWnd = GetDlgItem (pBttns[j].idCommand);

					pWnd -> EnableWindow (pBttns[j].fsState & TBSTATE_ENABLED);
				}
			}
		}
	}
#else
HRESULT hr = m_pMainFrm -> AddButtons (this, iCnt, pBttns, pIOwner);
#endif // _USE_SEC_CLASSES

	if (S_OK == hr && IsWindowVisible())
		m_pMainFrm -> DelayRecalcLayout();

	return hr;
}

HRESULT CTRiASToolBar::InsertButton (
	int iIndex, const TBBUTTON *pBttn, ITRiASUIOwner *pIOwner)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

// jetzt Owner zusammen mit dem ID speichern
	if (!((pBttn -> fsStyle & TBSTYLE_SEP) && 0 == pBttn -> idCommand)) {	// Separators not handled here
	pair<UIOwners::iterator, bool> p = m_Owners.insert (pBttn -> idCommand, pIOwner);

		ASSERT(p.second);
		if (!p.second)
			return ResultFromScode (E_FAIL);
	}

// und zur Toolbar hinzufügen
#if !defined(_USE_SEC_CLASSES)
// wenn dieses der erste Zugriff ist, dann Separator entfernen
	if (m_fHasDummySep) {
		DeleteItem (0);
		m_fHasDummySep = false;
	}

CToolBarCtrl &rTB = GetToolBarCtrl();
HRESULT hr = (rTB.InsertButton (iIndex, const_cast<TBBUTTON *>(pBttn))) ? NOERROR : S_FALSE;
#else
HRESULT hr = m_pMainFrm -> InsertButton (this, iIndex, pBttn, pIOwner);
#endif // _USE_SEC_CLASSES

	if (S_OK == hr && IsWindowVisible())
		m_pMainFrm -> DelayRecalcLayout();

	return hr;
}

HRESULT CTRiASToolBar::DeleteItem (int iIndex)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

TBBUTTON button;

	_GetButtonEx (iIndex, &button);

	if (0 != button.idCommand && !m_Owners.erase (button.idCommand))
		return E_FAIL;

#if !defined(_USE_SEC_CLASSES)
CToolBarCtrl &rTB = GetToolBarCtrl();
HRESULT hr = rTB.DeleteButton (iIndex) ? NOERROR : S_FALSE;
#else
HRESULT hr = m_pMainFrm -> DeleteButton (this, iIndex);
#endif // _USE_SEC_CLASSES
	
	if (S_OK == hr && IsWindowVisible())
		m_pMainFrm -> DelayRecalcLayout();

	return hr;
}

HRESULT CTRiASToolBar::CommandToIndex (UINT uiID, int *piIndex)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));
	ASSERT(NULL != piIndex);

	*piIndex = SECCustomToolBar::CommandToIndex (uiID);
	return NOERROR;
}

HRESULT CTRiASToolBar::GetItemRect (int iIndex, LPRECT pRc)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));
	ASSERT(NULL != pRc);

	if (NULL == pRc) return E_POINTER;

	SECCustomToolBar::GetItemRect (iIndex, pRc);
	return NOERROR;
}

HRESULT CTRiASToolBar::GetBarID (UINT *puiID)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

	if (NULL == puiID) return E_POINTER;

	*puiID = m_uiID;
	return (0 != m_uiID) ? NOERROR : ResultFromScode(E_UNEXPECTED);
}

HRESULT CTRiASToolBar::GetBarHandle (HWND *phWnd)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

	if (NULL == phWnd) return E_POINTER;

	*phWnd = m_hWnd;
	return (NULL != m_hWnd) ? NOERROR : ResultFromScode(E_UNEXPECTED);
}

HRESULT CTRiASToolBar::GetButtonStyle (int iIndex, UINT *puiStyle, UINT *puiID)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

	if (NULL == puiStyle && NULL == puiID)
		return E_POINTER;

	if (NULL != puiStyle) 
		*puiStyle = SECCustomToolBar::GetButtonStyle (iIndex);
	
	if (NULL != puiID) {
	TBBUTTON button;
	
		_GetButtonEx (iIndex, &button);
		*puiID = button.idCommand;
	}

	return NOERROR;
}

HRESULT CTRiASToolBar::SetButtonStyle (int iIndex, UINT uiStyle)
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

	SECCustomToolBar::SetButtonStyle (iIndex, uiStyle);

	return NOERROR;
}

BOOL CTRiASToolBar::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (S_OK == OnCmdMessage(nID, nCode, pExtra, pHandlerInfo))
		return true;
	return SECCustomToolBar::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

#if defined(_USE_SEC_CLASSES)
BOOL CTRiASToolBar::IDToBmpIndex (UINT nID, int *piIndex)
{
// Converts a command ID to a toolbar bitmap index.
	for(int i = 0; i < GetBtnCount(); i++)
	{
		if(m_btns[i]->m_nID == nID) {
		// existiert in dieser ToolBar
			*piIndex = m_btns[i]->m_nImage;
			return TRUE;	// found
		}
	}
	return FALSE;
}

// alle Buttons in kenntnis setzen, ob senkrecht gedockt ist oder nicht
void CTRiASToolBar::PropagateMode (void)
{
	for (int i = 0; i < GetBtnCount(); i++)
		m_btns[i] -> SetMode (m_bVertical);
}

#endif // _USE_SEC_CLASSES

HRESULT CTRiASToolBar::FindOwner (UINT uiID, ITRiASUIOwner **ppUIOwner)
{
	TEST_E_POINTER("CTRiASToolBar::FindOwner", ppUIOwner);

UIOwners::iterator it = m_Owners.find (uiID);
WTRiASUIOwner UIOwner;

#if defined(_USE_SEC_CLASSES)
// wenn dieser Button standardmäßig nicht zu dieser Toolbar gehört,
// dann den UIOwner von der Zentrale besorgen
	if (it == m_Owners.end()) {
	int iIndex = 0;
	
		if (!IDToBmpIndex (uiID, &iIndex))
			return S_FALSE;		// not found

	HRESULT hr = m_pMainFrm -> GetUIOwner (this, iIndex, UIOwner.ppi());

		if (S_OK == hr) {
			m_Owners.insert (uiID, UIOwner);	// jetzt lokal mit speichern
			*ppUIOwner = UIOwner.detach();
			return S_OK;		// bearbeitet
		}
	}
#endif // _USE_SEC_CLASSES

	if (it != m_Owners.end()) {
		if (NULL != (IUnknown *)(*it).second) {
			UIOwner = (*it).second;
			*ppUIOwner = UIOwner.detach();
			return S_OK;		// bearbeitet
		}
	}

	return S_FALSE;
}

HRESULT CTRiASToolBar::OnCmdMessage (UINT uiID, int nCode, void *pExtra, AFX_CMDHANDLERINFO *pHandlerInfo)
{
//	if (nCode != CN_COMMAND)
//		return S_FALSE;			// nur WM_COMMAND's bearbeiten

	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

// nur bearbeiten, wenn dieses Fenster angezeigt ist
	if (!(GetStyle() & WS_VISIBLE))
		return S_FALSE;		// nicht bearbeitet

// Versuchen diesen Befehl an entsprechenden Handler zu schicken
	{
	WTRiASUIOwner UIOwner;
	HRESULT hr = FindOwner (uiID, UIOwner.ppi());

		if (S_OK == hr) {
			if (NULL != pHandlerInfo)
				return S_OK;		// lediglich abfragen

			if (S_OK == UIOwner -> OnCommand (m_pIBar, uiID, nCode))
				return S_OK;		// bearbeitet
		}
	}
	return S_FALSE;					// nicht bearbeitet
}

#if !defined(_USE_SEC_CLASSES)
inline bool IsClass (HWND hWnd, LPCSTR pcClsName)
{
char classname[80];

	::GetClassName (hWnd, classname, sizeof(classname));
	return !stricmp (classname, pcClsName);
}
#endif // _USE_SEC_CLASSES

BOOL CTRiASToolBar::OnCommand(WPARAM wParam, LPARAM lParam) 
{
#if !defined(_USE_SEC_CLASSES)
	{	// spezielle Behandlung des VK_RETURN in EditControl einer ComboBox
	HWND hFocusWnd = ::GetFocus();

		if (IsClass (hFocusWnd, "Edit")) {						// if it's an edit control:
			if (IDOK == wParam && 0 == lParam) {
			// VK_RETURN in EditTeil einer ComboBox
			UINT uiID = ::GetDlgCtrlID(hFocusWnd);
			HWND hWndCBox = ::GetParent(hFocusWnd);

				if (IsClass (hWndCBox, "ComboBox")) {
					uiID = ::GetDlgCtrlID (hWndCBox);

				// der ComboBox den Event schicken
					if (OnCmdMsg(uiID, CBN_HITRETURN, NULL, NULL))
						return true;
				}
			}
		}
	}
#endif // _USE_SEC_CLASSES

	return SECCustomToolBar::OnCommand(wParam, lParam);
}

HRESULT CTRiASToolBar::GetButtonEx (int iIndex, TBBUTTON *pBttn, ITRiASUIOwner **ppIOwner) 
{
	AFX_MANAGE_STATE(AfxGetModuleState());
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));

	if (NULL == pBttn && NULL == ppIOwner)
		return E_POINTER;

	if (NULL != pBttn) 
		_GetButtonEx (iIndex, pBttn);

	if (NULL != ppIOwner) {
	TBBUTTON tb;

		_GetButtonEx (iIndex, &tb);

		{
		WTRiASUIOwner UIOwner;
		HRESULT hr = FindOwner (tb.idCommand, UIOwner.ppi());

			if (S_OK != hr)
				return E_UNEXPECTED;

			*ppIOwner = UIOwner.detach();
		}
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// CTRiASToolBar message handlers

// Nutzerinterface anpassen (gray/enable/disable ...) -------------------------
void CTRiASToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
// nur bearbeiten, wenn dieses Fenster angezeigt ist
	if (!(GetStyle() & WS_VISIBLE))	return;		// nicht bearbeitet

// jetzt geht's richtig los
CComObject<CTRiASToolCmdUI> *pCmdUI = NULL;

	TRY {
		if (FAILED(CComObject<CTRiASToolCmdUI>::CreateInstance(&pCmdUI)))
			AfxThrowMemoryException();

		pCmdUI -> AddRef();			// RefCnt auf 1 setzen
	} CATCH (CMemoryException, e) {
		ASSERT(NULL != pCmdUI);
	
	// update the dialog controls added to the toolbar
		UpdateDialogControls (pTarget, bDisableIfNoHndler);
		return;
	} END_CATCH

CCmdUI &state = pCmdUI -> state;

	state.m_pOther = this;			// Owner setzen
#if !defined(_USE_SEC_CLASSES)
	state.m_nIndexMax = (UINT)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
#else
	state.m_nIndexMax = GetBtnCount();
#endif // _USE_SEC_CLASSES
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
	{
	// get button state
	TBBUTTON button;
	
		_GetButtonEx (state.m_nIndex, &button);

	// ignore separators
		if (button.fsStyle & TBSTYLE_SEP && 0 == button.idCommand)
			continue;

	// send to UIOwner
		state.m_nID = button.idCommand;

		{
		WTRiASUIOwner UIOwner;
		HRESULT hr = FindOwner (button.idCommand, UIOwner.ppi());

			if (S_OK != hr)
				continue;		// Fehler: erstmal weitermachen

			if (S_OK == (UIOwner -> OnUpdateUI (m_pIBar, pCmdUI)))
			{
				continue;
			}
		}

	// allow the owner to process the update
		state.DoUpdate(pTarget, bDisableIfNoHndler);
	}

// update the dialog controls added to the toolbar
	UpdateDialogControls (pTarget, bDisableIfNoHndler);

	pCmdUI -> Release();
}

// rechter MausKlick auf Toolbar ----------------------------------------------
void CTRiASToolBar::OnContextMenu(CWnd *pWnd, CPoint point)
{
	m_pMainFrm -> OnContextMenu (pWnd, point);
}

// gehört zu rechtem MausKlick (TastaturInterface) ----------------------------
BOOL CTRiASToolBar::PreTranslateMessage(MSG* pMsg)
{
// CG: This block was added by the Pop-up Menu component
	{	
	// Shift+F10: show pop-up menu.
		if ((((pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN) && // If we hit a key and
			(pMsg->wParam == VK_F10) && (GetKeyState(VK_SHIFT) & ~1)) != 0) ||	// it's Shift+F10 OR
			(pMsg->message == WM_CONTEXTMENU))									// Natural keyboard key
		{
		CRect rect;

			GetClientRect(rect);
			ClientToScreen(rect);

		CPoint point = rect.TopLeft();

			point.Offset(5, 5);
			OnContextMenu(NULL, point);
			return true;
		}
	}

return SECCustomToolBar::PreTranslateMessage(pMsg);
}

// Anzeige des richtigen Textes in der Statuszeile ----------------------------
HRESULT CTRiASToolBar::GetStatusText (UINT uiID, CString &rStr)
{
	if (0 == uiID) return S_FALSE;		// separators not handled here

// get buttons state
int iIndex = SECCustomToolBar::CommandToIndex (uiID);

	if (-1 == iIndex) {
#if defined(_USE_SEC_CLASSES)
		iIndex = SECCustomToolBar::CommandToIndex (uiID -1);		// evtl. ComboBox et.al.
//		ASSERT(iIndex != -1);
		if (-1 == iIndex)
			return S_FALSE;
		uiID -= 1;		// mit zugehörigem Button weiterarbeiten
#else
		return E_UNEXPECTED;
#endif // _USE_SEC_CLASSES
	}

UINT uiStyle = SECCustomToolBar::GetButtonStyle (iIndex);

// ignore separators
	if (!(LOWORD(uiStyle) & TBSTYLE_SEP && 0 == uiID)) {
	// send to UIOwner
	WTRiASUIOwner UIOwner;
	HRESULT hr = FindOwner (uiID, UIOwner.ppi());

		if (S_OK == hr) {
		LPSTR pBuffer = rStr.GetBuffer (_MAX_PATH);
		HRESULT hr = UIOwner -> OnSelect (m_pIBar, uiID, pBuffer, _MAX_PATH, NULL);

			if (FAILED(hr)) {
				rStr.Empty();
				return hr;
			}
			rStr.ReleaseBuffer();
			return NOERROR;
		}
	}

	return E_FAIL;
}

HRESULT CTRiASToolBar::Reset (void)
{
#if !defined(_USE_SEC_CLASSES)
	ATLTRACENOTIMPL("CTRiASToolBar::Reset");
#else
	return m_pMainFrm -> ResetToolBar(this);
#endif // _USE_SEC_CLASSES
}

// original CControlBar::PreTranslateMesage()
#define ID_TIMER_WAIT   0xE000  // timer while waiting to show status
#define ID_TIMER_CHECK  0xE001  // timer to check for removal of status

// AFXPRIV.H:
#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
									// lParam = lpszOther (or NULL)
// same as WM_SETMESSAGESTRING except not popped if IsTracking()
#define WM_POPMESSAGESTRING 0x0375		

// Überladene Funktion aus CControlBar
BOOL CTRiASToolBar::SetStatusText(int nHit)
{
CWnd* pOwner = GetOwner();
_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();

	if (nHit == -1)	{
	// handle reset case
	
		pThreadState->m_pLastStatus = NULL;
		if (m_nStateFlags & statusSet) {
			pOwner->SendMessage(WM_POPMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
			m_nStateFlags &= ~statusSet;
			return TRUE;
		}
		KillTimer(ID_TIMER_WAIT);
	} else {
	// handle setnew case
		if (!(m_nStateFlags & statusSet) || pThreadState->m_nLastStatus != nHit) {
			pThreadState->m_pLastStatus = this;

		// hier ist die einzige Änderung gegenüber dem Original:
		// anstelle von: 'pOwner->SendMessage(WM_SETMESSAGESTRING, nHit);'
		// wird der Anzuzeigende String vom Button abgefragt und eingestellt
		CString str, strStatusText;
		
			if (S_OK == GetStatusText (nHit, str)) {		// nHit enthält den ButtonID
				AfxExtractSubString(strStatusText, str, 0, '\n');
				pOwner->SendMessage(WM_SETMESSAGESTRING, 0, (LPARAM)(LPCSTR)strStatusText);
			}

			m_nStateFlags |= statusSet;
			ResetTimer(ID_TIMER_CHECK, 200);
			return TRUE;
		}
	}
	return FALSE;
}

// ToolBar soll zerlegt werden ------------------------------------------------
void CTRiASToolBar::OnDestroy() 
{
	FreeInstalledControls();
	SECCustomToolBar::OnDestroy();
}

bool CTRiASToolBar::FreeInstalledControls (void)
{
	if (!::IsWindow(m_hWnd))	// breits zerlegt
		return false;

// InstallObjekte freigeben
#if !defined(_USE_SEC_CLASSES)
int iIndexMax = (UINT)DefWindowProc(TB_BUTTONCOUNT, 0, 0);

	for (int i = 0; i < iIndexMax; i++) {
	TBBUTTON button;		// get button info
	
		_GetButtonEx (i, &button);
		if (0 != button.idCommand && 0 != button.dwData)
			reinterpret_cast<IUnknown *>(button.dwData) -> Release();
	}
#endif // _USE_SEC_CLASSES

	return true;
}

// Das letzte vom Tage: alles was wir noch halten JETZT freigeben -------------
void CTRiASToolBar::OnNcDestroy() 
{
// AddRefLoop auflösen: ~CTRiASToolBar wird gerufen
	ExternalAddRef();
	m_Owners.erase();		// alle UIOwner freigeben

// jetzt kann alles freigegeben werden
//	m_bAutoDelete = true;
	ExternalRelease();

	SECCustomToolBar::OnNcDestroy();
}

// Tooltiptexte herausfischen und an ToolTipControl weitergeben ---------------
#define _countof(array) (sizeof(array)/sizeof(array[0]))

bool CTRiASToolBar::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

// allow top level routing frame to handle the message
	if (GetRoutingFrame() != NULL)
		return FALSE;

	*pResult = 0;

// need to handle both ANSI and UNICODE versions of the message
TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
CString strTipText (g_cbNil);

	if (m_pMainFrm -> ShowToolTips()) {		// nur wenn Tooltips angezeigt werden sollen
	UINT nID = pNMHDR->idFrom;

		if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
			pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
		{
			// idFrom is actually the HWND of the tool
			nID = ((UINT)(WORD)::GetDlgCtrlID((HWND)nID));
		}

		if (nID != 0) {	// will be zero on a separator
		// this is the command id, not the button index
		CString str;
		
			if (S_OK != GetStatusText (nID, str))			// nHit enthält den ButtonID
				return false;	// no text, no fun
			AfxExtractSubString(strTipText, str, 1, '\n');
		}
	}

#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, _countof(pTTTA->szText));
	else
		_mbstowcsz(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, _countof(pTTTA->szText));
	else
		lstrcpyn(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#endif

// bring the tooltip window above other popup windows
	::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
		SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);

return true;    // message was handled
}

#define CBRS_ALIGN_VERT		(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT)
#define CBRS_ALIGN_HORZ		(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM)

#if _MSC_VER <= 1020
template<class T> 
inline void swap (T &x_, T &y_)
{
	T t_ = x_; x_ = y_; y_ = t_;
}
#endif // _MSC_VER <= 1020

void CTRiASToolBar::OnBarStyleChange (DWORD dwOldStyle, DWORD dwNewStyle)
{
#if defined(_USE_SEC_CLASSES)
/*	if (m_pMainFrm -> CoolLookEnabled()) {
		m_cxLeftBorder = m_cyTopBorder = max(m_cxLeftBorder, m_cyTopBorder);
		m_cxRightBorder = m_cyBottomBorder = max(m_cxRightBorder, m_cyBottomBorder);
		SECCustomToolBar::OnBarStyleChange (dwOldStyle, dwNewStyle);
		return;
	}
*/
#endif // _USE_SEC_CLASSES
		
	if (!((dwOldStyle & CBRS_ALIGN_ANY) ^ (dwNewStyle & CBRS_ALIGN_ANY))) {
		SECCustomToolBar::OnBarStyleChange (dwOldStyle, dwNewStyle);
		return;
	}

	if (((dwNewStyle & CBRS_ALIGN_VERT) && !(dwOldStyle & CBRS_ALIGN_VERT)) ||
		((dwNewStyle & CBRS_ALIGN_HORZ) && !(dwOldStyle & CBRS_ALIGN_HORZ)))
	{
	// jetzt horizontal oder jetzt vertikal
		swap (m_cxLeftBorder, m_cyTopBorder);
		swap (m_cxRightBorder, m_cyBottomBorder);
	}

	SECCustomToolBar::OnBarStyleChange (dwOldStyle, dwNewStyle);
}

/* ----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
// wenn Controls in der Toolbar sind, dann diese bei LM_VERTDOCK 
// durch normale Buttons ersetzen

#define CBRS_ALIGN_VERT		(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT)
#define CBRS_ALIGN_HORZ		(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM)

CSize CTRiASToolBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
DWORD dwCtrl = 0;

	if (dwMode & LM_VERTDOCK)
		dwCtrl |= CBRS_ALIGN_VERT;
	else 
		dwCtrl |= CBRS_ALIGN_HORZ;
	
	{
	int nCount = DefWindowProc(TB_BUTTONCOUNT, 0, 0);
	TBBUTTON *pData = NULL;

		if (nCount != 0) {
		// horizontale Controls evtl. durch Buttons ersetzen
		int i;

			pData = new TBBUTTON[nCount];
			for (i = 0; i < nCount; i++) {
				::_GetButton(this, i, &pData[i]);
				if (0 != pData[i].idCommand && NULL != pData[i].dwData) 
				{
				// Custom control in der Toolbar
				TBBUTTON tb = pData[i];
				HRESULT hr = reinterpret_cast<ITRiASBarInstallControl *>(pData[i].dwData) -> 
								GetAdjustedInfo (m_pIBar, pData[i].idCommand, dwCtrl, &tb);
					
					if (S_OK == hr) 
						::_SetButton (this, i, &tb);
				}
			}

		// jetzt Größe berechnen
		CSize szBar = CToolBar::CalcDynamicLayout (nLength, dwMode);

		// und alles wieder zurücksetzen
			for (i = 0; i < nCount; i++) {
				if (0 != pData[i].idCommand && NULL != pData[i].dwData) 
				{
				TBBUTTON tb;

					::_GetButton (this, i, &tb);
					if (memcmp (&tb, &pData[i], sizeof(TBBUTTON)))
						::_SetButton (this, i, &pData[i]);
				}
			}

			delete[] pData;
			return szBar;
		}
	}

return CToolBar::CalcDynamicLayout (nLength, dwMode);
}

void CTRiASToolBar::OnBarStyleChange (DWORD dwOldStyle, DWORD dwNewStyle)
{
	if (!((dwOldStyle & CBRS_ALIGN_ANY) ^ (dwNewStyle & CBRS_ALIGN_ANY)))
		return;

	if (((dwNewStyle & CBRS_ALIGN_VERT) && !(dwOldStyle & CBRS_ALIGN_VERT)) ||
		((dwNewStyle & CBRS_ALIGN_HORZ) && !(dwOldStyle & CBRS_ALIGN_HORZ)))
	{
	// jetzt vertikal oder jetzt horizontal
	int nCount = DefWindowProc(TB_BUTTONCOUNT, 0, 0);
	TBBUTTON *pData = NULL;

		if (0 == nCount) return;
	
	// horizontale Controls evtl. durch Buttons ersetzen bzw.
	// Buttons evtl. durch horizontale Controls ersetzen
	TBBUTTON tb;

		for (int i = 0; i < nCount; i++) {
			::_GetButton(this, i, &tb);
		
			if (0 != tb.idCommand && NULL != tb.dwData) {
			// Custom control in der Toolbar
			ITRiASBarInstallControl *pICtrl = reinterpret_cast<ITRiASBarInstallControl *>(tb.dwData);
			HRESULT hr = pICtrl -> GetAdjustedInfo (m_pIBar, tb.idCommand, dwNewStyle & CBRS_ALIGN_ANY, &tb);

				if (S_OK == hr) {
					::_SetButton (this, i, &tb);
					pICtrl -> AdjustControl (m_pIBar, tb.idCommand, dwNewStyle & CBRS_ALIGN_ANY);
				}
				m_bDelayedButtonLayout = true;
			}
		}
	} 
}

---------------------------------------------------------------------------- */

