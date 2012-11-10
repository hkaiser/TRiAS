// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 01.03.2001 10:48:32 
//
// @doc
// @module DockingTabFrame.cpp | Definition of the <c CDockingTabFrame> class

#include "stdafx.h"

#if defined(_USE_DOCKEDTABWINDOW)

#include <Com/MfcHelper.h>

#include "fakemfc.h"
#include "DockingTabFrame.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"		// SmartInterfaces
#include "Picture.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDockingTabFrame, SECControlBar)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// CDockingTabFrame

CDockingTabFrame::CDockingTabFrame() 
{
	VERIFY(m_GripperInfo.m_strCloseTipText.LoadString(IDS_HIDEWINDOW));
	VERIFY(m_GripperInfo.m_strContractTipText.LoadString(IDS_CONTRACTWINDOW));
	VERIFY(m_GripperInfo.m_strExpandTipText.LoadString(IDS_EXPANDWINDOW));
}

CDockingTabFrame::~CDockingTabFrame()
{
}

HRESULT CDockingTabFrame::get_Visible(VARIANT_BOOL *pfVisible)
{
	if (NULL == pfVisible)
		return E_POINTER;

	*pfVisible = IsVisible() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

HRESULT CDockingTabFrame::put_Visible(VARIANT_BOOL fVisible)
{
CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	pFrame -> ShowControlBar(this, fVisible ? TRUE : FALSE, TRUE);
	DEX_KickIdle();		// alles neu zeichnen
	return S_OK;
}

HRESULT CDockingTabFrame::get_Count(int *pfCount)
{
	if (NULL == pfCount)
		return E_POINTER;

	*pfCount = m_wndTab.GetTabCount();
	return S_OK;
}

HRESULT CDockingTabFrame::get_ActiveTabWindow(INT_PTR *phHandle)
{
	if (NULL == phHandle)
		return E_POINTER;
	
CWnd *pWnd = NULL;

	if (!m_wndTab.GetActiveTab(pWnd) || NULL == pWnd)
		return E_UNEXPECTED;

	*phHandle = reinterpret_cast<INT_PTR>(pWnd -> GetSafeHwnd());
	return S_OK;
}

HRESULT CDockingTabFrame::get_ParentWindow(INT_PTR *phHandle)
{
	if (NULL == phHandle)
		return E_POINTER;

	*phHandle = reinterpret_cast<INT_PTR>(m_wndTab.GetSafeHwnd());
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Wiederfinden einer bestimmten Tablasche
HRESULT CDockingTabFrame::FindTabWindow(BSTR bstrName, INT_PTR *phHandle)
{
	if (NULL == phHandle)
		return E_POINTER;
	*phHandle = NULL;

	USES_CONVERSION;

BOOL fFound = FALSE;
LPCSTR pcToFind = OLE2A(bstrName);

	COM_TRY {
		for (int nIndex = 0; nIndex < m_wndTab.GetTabCount(); ++nIndex) {
		LPSTR pcLabel = NULL;
		BOOL fSelected = FALSE;
		CWnd *pWnd = NULL;
		void *pExtra = NULL;

			if (!m_wndTab.GetTabInfo(nIndex, pcLabel, fSelected, pWnd, pExtra))
				break;

			if (!strcmp (pcLabel, pcToFind)) {
				*phHandle = reinterpret_cast<INT_PTR>(pWnd -> GetSafeHwnd());
				fFound = TRUE;
				break;
			}
		}
	} COM_CATCH;
	return fFound ? S_OK : E_INVALIDARG;
}

///////////////////////////////////////////////////////////////////////////////
// Umbenennen eines TabWindows
HRESULT CDockingTabFrame::RenameTabWindow(BSTR bstrOldName, BSTR bstrNewName)
{
	USES_CONVERSION;
	COM_TRY {
	LPCSTR pcToFind = OLE2A(bstrOldName);

		for (int nIndex = 0; nIndex < m_wndTab.GetTabCount(); ++nIndex) {
		LPSTR pcLabel = NULL;
		BOOL fSelected = FALSE;
		CWnd *pWnd = NULL;
		void *pExtra = NULL;

			if (!m_wndTab.GetTabInfo(nIndex, pcLabel, fSelected, pWnd, pExtra))
				break;

			if (!strcmp (pcLabel, pcToFind)) {
				m_wndTab.RenameTab(nIndex, bstrOldName, bstrNewName);
				break;
			}
		}
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Hinzufügen einer neuen Tablasche
namespace {
// ein IPicture aus einem Icon erzeugen
	HRESULT CreatePicture (HICON hIcon, bool fOwn, IPictureDisp **ppIDisp)
	{
	PICTDESC pdesc;
	WDispatch Disp;

		pdesc.cbSizeofstruct = sizeof(pdesc);
		pdesc.picType = PICTYPE_ICON;
		pdesc.icon.hicon = hIcon;

	HRESULT hr = OleCreatePictureIndirect (&pdesc, IID_IPictureDisp, fOwn, (LPVOID *)ppIDisp);

		if (FAILED(hr)) {
			::DeleteObject (hIcon);
			return hr;
		}
		return S_OK;
	}

	HRESULT RetrievePicture (VARIANT &vPicture, IPictureDisp **ppIPict)
	{
	CComVariant vArg;
	HRESULT hr = vArg.ChangeType (VT_DISPATCH, &vPicture);

		if (SUCCEEDED(hr)) 
			return V_DISPATCH(&vArg) -> QueryInterface(IID_IPictureDisp, (LPVOID *)ppIPict);

		hr = vArg.ChangeType (VT_I4, &vPicture);		// IconHandle ?
		if (SUCCEEDED(hr)) 
			return CreatePicture ((HICON)V_I4(&vArg), false, ppIPict);

		return E_INVALIDARG;
	}
}

HRESULT CDockingTabFrame::AddTabWindow(INT_PTR hWnd, BSTR bstrName, VARIANT vPict, INT_PTR *phHandle)
{
	if (NULL == phHandle)
		return E_POINTER;
	*phHandle = NULL;

	USES_CONVERSION;
	COM_TRY {
		if (SUCCEEDED(FindTabWindow(bstrName, phHandle)) && hWnd == *phHandle)
			return S_FALSE;		// existierte bereits

		*phHandle = NULL;		// doch nichts

	// neue TablaschenDaten erzeugen
		_ASSERTE(::IsWindow(reinterpret_cast<HWND>(hWnd)));

	CTabData *pTabData = new CTabData;
	CWnd *pWnd = CWnd::FromHandlePermanent(reinterpret_cast<HWND>(hWnd));

		if (NULL == pWnd) {
		// hWnd ist kein MFC-Fenster
			pWnd = new CWnd;
			pWnd -> Attach(reinterpret_cast<HWND>(hWnd));	// trägt hWnd in CWndMap ein
			pTabData -> m_fIsAttached = true;
			pTabData -> m_pWnd = pWnd;
			pTabData -> m_hOldParentWnd = ::GetParent(reinterpret_cast<HWND>(hWnd));

			pWnd -> SetParent(&m_wndTab);
		} 
		else {
			pTabData -> m_fIsAttached = false;
			pTabData -> m_pWnd = pWnd;
			pTabData -> m_hOldParentWnd = NULL;
		}

	// erzeugen der TabLasche, speichern der eigenen Daten
	SECTab *pTab = m_wndTab.AddTab(pWnd, OLE2A(bstrName));

		pTab -> m_pExtra = pTabData;

	// ggf. Bildchen hinzufügen
	WPictureDisp PictDisp;

		if (SUCCEEDED(RetrievePicture(vPict, PictDisp.ppi()))) {
		CPicture Pict (PictDisp, false);

			_ASSERTE(NULL != Pict.GetHandle());
			m_wndTab.SetTabIcon(m_wndTab.GetTabCount()-1, reinterpret_cast<HICON>(Pict.GetHandle()));
		}

	// Erfolg: Fensterhandle wieder zurückliefern
		*phHandle = hWnd;

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Bildchen setzen
HRESULT CDockingTabFrame::SetTabIcon(INT_PTR hHandle, VARIANT vPict)
{
	COM_TRY {
	// ggf. Bildchen hinzufügen
	WPictureDisp PictDisp;

		THROW_FAILED_HRESULT(RetrievePicture(vPict, PictDisp.ppi()));

		for (int nIndex = 0; nIndex < m_wndTab.GetTabCount(); ++nIndex) {
		LPSTR pcLabel = NULL;
		BOOL fSelected = FALSE;
		CWnd *pWnd = NULL;
		void *pExtra = NULL;

			if (!m_wndTab.GetTabInfo(nIndex, pcLabel, fSelected, pWnd, pExtra))
				break;

			if (reinterpret_cast<HWND>(hHandle) == pWnd -> GetSafeHwnd()) {
			CPicture Pict (PictDisp, false);

				_ASSERTE(NULL != Pict.GetHandle());
				m_wndTab.SetTabIcon(nIndex, reinterpret_cast<HICON>(Pict.GetHandle()));
				break;
			}
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Entfernen einer Tablasche, freigeben der zugehörigen Daten
HRESULT CDockingTabFrame::DeleteTabWindow(INT_PTR hHandle, BOOL fRemoveCallback)
{
	COM_TRY {
		for (int nIndex = 0; nIndex < m_wndTab.GetTabCount(); ++nIndex) {
		LPSTR pcLabel = NULL;
		BOOL fSelected = FALSE;
		CWnd *pWnd = NULL;
		void *pExtra = NULL;

			if (!m_wndTab.GetTabInfo(nIndex, pcLabel, fSelected, pWnd, pExtra))
				break;

			if (reinterpret_cast<HWND>(hHandle) == pWnd -> GetSafeHwnd()) {
			CTabData *pData = reinterpret_cast<CTabData *>(pExtra);

				m_wndTab.RemoveTab(nIndex, fRemoveCallback);
				if (pData -> m_fIsAttached) {
				HWND hWnd = pData -> m_pWnd -> Detach();

					if (NULL != hWnd)
						::SetParent(hWnd, pData -> m_hOldParentWnd);
					delete pData -> m_pWnd;
				}
				delete pData;

				m_wndTab.Invalidate();			// vollständig neu zeichnen
				m_wndTab.UpdateWindow();
				return S_OK;
			}
		}
	} COM_CATCH;
	return E_INVALIDARG;	// not found
}

HRESULT CDockingTabFrame::ActivateTabWindow(INT_PTR hHandle)
{
	COM_TRY {
		for (int nIndex = 0; nIndex < m_wndTab.GetTabCount(); ++nIndex) {
		LPSTR pcLabel = NULL;
		BOOL fSelected = FALSE;
		CWnd *pWnd = NULL;
		void *pExtra = NULL;

			if (!m_wndTab.GetTabInfo(nIndex, pcLabel, fSelected, pWnd, pExtra))
				break;

			if (reinterpret_cast<HWND>(hHandle) == pWnd -> GetSafeHwnd()) {
				m_wndTab.ActivateTab(nIndex);
				m_wndTab.ScrollToTab(nIndex);
				return S_OK;
			}
		}
	} COM_CATCH;
	return E_INVALIDARG;	// not found
}

HRESULT CDockingTabFrame::AddTabWindowDelayed(BSTR bstrName, ITabWindowCallback *pICallback)
{
	return m_wndTab.AddTabWindowDelayed(bstrName, pICallback);
}

BEGIN_MESSAGE_MAP(CDockingTabFrame, SECControlBar)
	//{{AFX_MSG_MAP(CDockingTabFrame)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(WM_ADDTAB, OnAddTab)
	ON_REGISTERED_MESSAGE(WM_REMOVETAB, OnRemoveTab)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(SEC_IDW_TABCLIENT_FIRST, SEC_IDW_TABCLIENT_FIRST+256, OnTabCommand)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDockingTabFrame message handlers

LRESULT CDockingTabFrame::OnAddTab (WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CDockingTabFrame::OnRemoveTab (WPARAM wParam, LPARAM lParam)
{
	_ASSERTE(::IsWindow(reinterpret_cast<HWND>(wParam)));

// Fenster sicherheitshalber ausblenden
	if (::IsWindowVisible(reinterpret_cast<HWND>(wParam)))
		::ShowWindow(reinterpret_cast<HWND>(wParam), SW_HIDE);

// gesamten Tab entfernen
	return SUCCEEDED(DeleteTabWindow(wParam, FALSE));
}

void CDockingTabFrame::OnExtendContextMenu(CMenu* pCtxMenu)
{
// alle enthaltenen Items rausnehmen
int iCnt = pCtxMenu -> GetMenuItemCount();

	for (int i = iCnt-1; i >= 0; --i)
		pCtxMenu -> DeleteMenu(i, MF_BYPOSITION);

// Menu neu zusammenbauen (Standardbefehle)
CString strMenu;

	VERIFY(strMenu.LoadString(IDS_ALLOWDOCKING));
	pCtxMenu -> AppendMenu(((m_dwDockStyle & CBRS_ALIGN_ANY) != 0 ? MF_STRING | MF_CHECKED : MF_STRING), 
		ID_SEC_ALLOWDOCKING, strMenu);

	VERIFY(strMenu.LoadString(IDS_HIDEWINDOW));
	pCtxMenu -> AppendMenu(MF_STRING, ID_SEC_HIDE, strMenu);

// wenn Klick auf eine der Tablaschen erfolgte, dann alle existierenden Tabs einfügen
	if (-1 != m_wndTab.ClickedOnTab()) 
		m_wndTab.OnExtendContextMenu(pCtxMenu);
}

void CDockingTabFrame::OnTabCommand(UINT nID)
{
	m_wndTab.OnTabCommand(nID);
}

void CDockingTabFrame::OnSize(UINT nType, int cx, int cy) 
{
CRect rectInside;

	GetInsideRect(rectInside);
	m_wndTab.SetWindowPos(NULL, rectInside.left, rectInside.top, 
		rectInside.Width(), rectInside.Height(),
		SWP_NOZORDER|SWP_NOACTIVATE);
	SECControlBar::OnSize(nType, cx, cy);
}

int CDockingTabFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (SECControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndTab.Create(this, WS_CHILD|WS_VISIBLE|TWS_TABS_ON_BOTTOM|TWS_NOACTIVE_TAB_ENLARGED, ID_TABCONTROL)) {
		TRACE("Could not create docking TabWindow!");
		return -1;
	}
	return 0;
}

void CDockingTabFrame::OnBarFloat()
{
	m_rcBorderSpace.SetRect(0, 3, 0, 0);		// ltrb
	SECControlBar::OnBarFloat();
}

void CDockingTabFrame::OnBarDock()
{
	m_rcBorderSpace.SetRect(10, 13, 8, 10);
	SECControlBar::OnBarDock();
}

///////////////////////////////////////////////////////////////////////////////
// IManageTabWindows
BEGIN_INTERFACE_MAP(CDockingTabFrame, SECControlBar)
	INTERFACE_PART(CDockingTabFrame, IID_IManageTabWindows, ManageTabWindows)
END_INTERFACE_MAP()

IMPLEMENT_IUNKNOWN(CDockingTabFrame, ManageTabWindows)
FAKE_IDISPATCH(CDockingTabFrame, ManageTabWindows)

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::get_Visible (VARIANT_BOOL *pfVisible)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> get_Visible (pfVisible);	
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::put_Visible (VARIANT_BOOL fVisible)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> put_Visible (fVisible);	
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::get_Count(int *pfCount)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> get_Count(pfCount);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::get_ActiveTabWindow (INT_PTR *phHandle)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> get_ActiveTabWindow (phHandle);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::get_ParentWindow (INT_PTR *phHandle)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> get_ParentWindow (phHandle);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::FindTabWindow (BSTR bstrName, INT_PTR *phHandle)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> FindTabWindow(bstrName, phHandle);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::AddTabWindow (INT_PTR hWnd, BSTR bstrName, VARIANT vPict, INT_PTR *phHandle)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> AddTabWindow (hWnd, bstrName, vPict, phHandle);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::DeleteTabWindow (INT_PTR hHandle)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> DeleteTabWindow (hHandle, FALSE);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::ActivateTabWindow (INT_PTR hHandle)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> ActivateTabWindow (hHandle);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::AddTabWindowDelayed (BSTR bstrName, ITabWindowCallback *pICallback)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> AddTabWindowDelayed (bstrName, pICallback);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::RenameTabWindow(BSTR bstrOldName, BSTR bstrNewName)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> RenameTabWindow (bstrOldName, bstrNewName);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::SetTabIcon (INT_PTR hHandle, VARIANT vIcon)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> SetTabIcon (hHandle, vIcon);
}

STDMETHODIMP CDockingTabFrame::
XManageTabWindows::DeleteTabWindowDelayed (INT_PTR hHandle)
{
    METHOD_PROLOGUE(CDockingTabFrame, ManageTabWindows)
	return pThis -> DeleteTabWindow (hHandle, TRUE);
}

#if defined(_USE_PROJECTVALUES)
///////////////////////////////////////////////////////////////////////////////
// 
CDockingProjectTabFrame::CDockingProjectTabFrame() 
{
	m_pPrjValues = NULL;
}

CDockingProjectTabFrame::~CDockingProjectTabFrame()
{
	_ASSERTE(NULL == m_pPrjValues);
}

BEGIN_MESSAGE_MAP(CDockingProjectTabFrame, CDockingTabFrame)
	//{{AFX_MSG_MAP(CDockingProjectTabFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDockingProjectTabFrame::OnProjectOpened()
{
	_ASSERT(NULL == m_pPrjValues);
	ATLTRY(m_pPrjValues = new CProjectValues);
	if (NULL == m_pPrjValues) return FALSE;

	if (!m_pPrjValues -> Create(CProjectValues::IDD, &m_wndTab)) {
		TRACE("Could not create modeless dialog CProjectValues!");
		return FALSE;
	}

CTabData *pTabData = NULL;
CString strProjectValues;

	ATLTRY(pTabData = new CTabData);
	if (NULL == pTabData) return -1;

	pTabData -> m_fIsAttached = false;
	pTabData -> m_pWnd = m_pPrjValues;
	pTabData -> m_hOldParentWnd = NULL;
	VERIFY(strProjectValues.LoadString(IDS_PROJECTVALUES));

SECTab *pTab = m_wndTab.AddTab(m_pPrjValues, strProjectValues);

	if (NULL != pTab) {
		pTab -> m_pExtra = pTabData;

	int iIndex = m_wndTab.GetTabCount()-1;

		m_wndTab.SetTabIcon(iIndex, AfxGetApp() -> LoadIcon(IDI_STATISTICS));
		m_wndTab.ActivateTab(iIndex);
		m_wndTab.ScrollToTab(iIndex);
	}
	return TRUE;
}

BOOL CDockingProjectTabFrame::OnProjectClosed()
{
int nIndex = -1;

	if (NULL == m_pPrjValues || !m_wndTab.FindTab(m_pPrjValues, nIndex) || -1 == nIndex)
		return FALSE;

LPSTR pcLabel = NULL;
BOOL fSelected = FALSE;
CWnd *pWnd = NULL;
void *pExtra = NULL;

	if (!m_wndTab.GetTabInfo(nIndex, pcLabel, fSelected, pWnd, pExtra))
		return FALSE;

// zugehörige Daten freigeben
CTabData *pData = reinterpret_cast<CTabData *>(pExtra);

	_ASSERTE(m_pPrjValues == pWnd);
	_ASSERTE(NULL != pData);

	m_wndTab.RemoveTab(nIndex);

	DELETE_OBJ(m_pPrjValues);
	DELETE_OBJ(pData);

	if (0 == m_wndTab.GetTabCount())
		m_wndTab.Invalidate();			// vollständig neu zeichnen

	return TRUE;
}
#endif // defined(_USE_PROJECTVALUES)

#endif // defined(_USE_DOCKEDTABWINDOW)

