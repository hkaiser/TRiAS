// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 14.03.2002 22:41:49 
//
// @doc
// @module SabisTabChildWindow.cpp | Definition of the <c CSabisTabChildWindow> class

#include "stdafx.h"
#include "TRSABIS.h"

#include <SidManageTabs.h>
#include <Com/ComBool.h>

#include "SabisTabChildWindow.h"
#include "SABiSTabChildWindowCallback.h"

///////////////////////////////////////////////////////////////////////////////
// hilfreiche Macros
#undef CHECKOUTPOINTER
#undef CHECKINPOINTER

#define CHECKINPOINTER(x) if (NULL != x) {} else { return E_POINTER; }
#define CHECKOUTPOINTER(x) if (NULL != x) { *(x) = NULL; } else { return E_POINTER; }

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TriasXtensionSite);
DefineSmartInterface(ServiceProvider);
DefineSmartInterface(ManageTabWindows);

/////////////////////////////////////////////////////////////////////////////
// CSabisTabChildWindow

/*static*/
HRESULT CSabisTabChildWindow::RegisterTabWindows()
{
WManageTabWindows Tabs;

	RETURN_FAILED_HRESULT(RetrieveTabManager(false, Tabs.ppi()));
	RETURN_FAILED_HRESULT(RetrieveTabManager(true, Tabs.ppi()));
	return S_OK;
}

// ISupportsErrorInfo
STDMETHODIMP CSabisTabChildWindow::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid == IID_CommonChildWindow2 ? S_OK : S_FALSE;
}

// Constructor
CSabisTabChildWindow::CSabisTabChildWindow() :
	m_pWnd(NULL), m_fIThinkItsVisible(false), 
	m_fHasBkColor(false), m_fWasShownOnce(false), 
	m_cBkColor(0), m_fUse2ndOne(false)
{
}

// Destructor
CSabisTabChildWindow::~CSabisTabChildWindow()
{
	if (NULL != m_pWnd) 
		DeleteWindow();			
	if (NULL != m_pWnd) {
		delete m_pWnd;
		m_pWnd = NULL;
	}
}

HRESULT CSabisTabChildWindow::FinalConstruct()
{
//	Erweiterung laden
LOADEXTENSIONEX le;

	memset (&le, 0, sizeof (LOADEXTENSIONEX));
	le.m_pDesc = NULL;
	le.m_pName = "TRiAS.TRiASSabis.1";
	le.m_iMode = LEFullLoad;
	le.m_fGlobal = TRUE;		
	if (NULL == DEX_ExternalLoadExtensionEx (le)) 
		return E_FAIL;
	return S_OK;
}

void CSabisTabChildWindow::FinalRelease()
{
// Fenster freigeben und Deregistrieren
	DeleteWindow();

// Erweiterung freigeben
LOADEXTENSIONEX le;

	memset (&le, 0, sizeof (LOADEXTENSIONEX));
	le.m_pDesc = NULL;
	le.m_pName = "TRiAS.TRiASSabis.1";
	le.m_iMode = LENoLoad;
	le.m_fGlobal = TRUE;		
	DEX_ExternalUnLoadExtensionEx (le);
}

HRESULT CSabisTabChildWindow::RegisterTabWindow(BSTR bstrInit, bool fUse2ndOne)
{
	m_fUse2ndOne = fUse2ndOne;
	COM_TRY {
	WManageTabWindows Tabs;

		THROW_FAILED_HRESULT(RetrieveTabManager(m_fUse2ndOne, Tabs.ppi()));

	CComObject<CSABiSTabChildWindowCallback> *pCallback = NULL;

		THROW_FAILED_HRESULT(CComObject<CSABiSTabChildWindowCallback>::CreateInstance(&pCallback));
		THROW_FAILED_HRESULT(pCallback->InitTarget(this));

	WUnknown Unk(pCallback);		// pending AddRef
	CComBSTR bstr (bstrInit);

		if (0 == bstr.Length()) 
			bstr.LoadString(IDS_SABISTABNAME);

		m_bstrInit = bstr;
		THROW_FAILED_HRESULT(Tabs -> AddTabWindowDelayed(bstr, pCallback));

	} COM_CATCH;
	return S_OK;
}

HRESULT CSabisTabChildWindow::CreateClientWindow(bool fShow) 
{
	COM_TRY {
	// SABiS-Fenster erzeugen
	CTRiASTabChild *pClient = m_pWnd;
	CWaitCursor Wait;

	WManageTabWindows Tabs;

		THROW_FAILED_HRESULT(RetrieveTabManager(m_fUse2ndOne, Tabs.ppi()));

	INT_PTR hParent = NULL;

		THROW_FAILED_HRESULT(Tabs -> get_ParentWindow(&hParent));
		if (NULL == pClient) {
			pClient = GetWindow(reinterpret_cast<HWND>(hParent));
			_ASSERTE(NULL != pClient && NULL != m_pWnd && m_pWnd == pClient);
		}

	INT_PTR hHandle = NULL;
	HWND hWnd = pClient -> GetSafeHwnd();

		_ASSERTE(NULL != hWnd);
		_ASSERTE(m_bstrInit.Length() > 0);
		THROW_FAILED_HRESULT(Tabs -> AddTabWindow(reinterpret_cast<INT_PTR>(hWnd), 
			m_bstrInit, pClient -> GetIcon(), &hHandle));
		_ASSERTE(reinterpret_cast<HWND>(hHandle) == HWND(*pClient));

		THROW_FAILED_HRESULT(Tabs -> ActivateTabWindow(hHandle));

	// ggf. Tabfenster anzeigen
		if (fShow) {
		CComBool fVisible;

			THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
			if (!fVisible)
				THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_TRUE));
			m_fIThinkItsVisible = true;
		}
		else
			m_fIThinkItsVisible = false;

	} COM_CATCH;
	return S_OK;
}

bool CSabisTabChildWindow::ReShow()
{
	COM_TRY {
	// SABiS-Fenster wieder anzeigen
	CWaitCursor Wait;
	WManageTabWindows Tabs;

		THROW_FAILED_HRESULT(RetrieveTabManager(m_fUse2ndOne, Tabs.ppi()));

	INT_PTR hHandle = NULL;

		_ASSERTE(m_bstrInit.Length() > 0);
		THROW_FAILED_HRESULT(Tabs -> FindTabWindow(m_bstrInit, &hHandle));
		THROW_FAILED_HRESULT(Tabs -> ActivateTabWindow(hHandle));

	// ggf. Tabfenster anzeigen
		THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_TRUE));
		m_fIThinkItsVisible = true;

	} COM_CATCH_RETURN(false);
	return true;
}

HRESULT CSabisTabChildWindow::DestroyWindow()
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (NULL != m_pWnd && ::IsWindow(m_pWnd->GetSafeHwnd())) {	
		delete m_pWnd;
		m_pWnd = NULL;
	}
	return S_OK;
}

HRESULT CSabisTabChildWindow::DeleteWindow(bool fTabOnly)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (!::IsWindow(m_pWnd->GetSafeHwnd()))
		return S_FALSE;		// schon zerlegt

	COM_TRY {
	WManageTabWindows Tabs;

		THROW_FAILED_HRESULT(RetrieveTabManager(m_fUse2ndOne, Tabs.ppi()));

		_ASSERTE(::IsWindow(m_pWnd->GetSafeHwnd()));

	HRESULT hr = fTabOnly ? 
			Tabs -> DeleteTabWindow(reinterpret_cast<INT_PTR>(m_pWnd->GetSafeHwnd())) :
			Tabs -> DeleteTabWindowDelayed(reinterpret_cast<INT_PTR>(m_pWnd->GetSafeHwnd()));

		if (SUCCEEDED(hr)) {
			if (!fTabOnly) 
				DestroyWindow();

		// ggf. TabFenster ausblenden (wenns die letzte TabLasche war)
		int iCount = 0;

			THROW_FAILED_HRESULT(Tabs -> get_Count(&iCount));
			if (0 == iCount) {
			CComBool fVisible;

				THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
				if (fVisible) 
					THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_FALSE));
			}
		}
		else {
			_ASSERTE(!fTabOnly);		// Fenster muß zerlegt werden sollen
			DestroyWindow();
		}
		m_fIThinkItsVisible = false;

	} COM_CATCH;
	return S_OK;
}

void CSabisTabChildWindow::InitiateShutDown()
{
	if (NULL != m_pWnd && ::IsWindow(m_pWnd->GetSafeHwnd())) 
		m_pWnd -> PostMessage(WM_SYSCOMMAND, SC_CLOSE);
}

/////////////////////////////////////////////////////////////////////////////
// CommonChildWindow2

// Implementation of put_BackColor
STDMETHODIMP CSabisTabChildWindow::put_BackColor(long cBkColor)
{
	if (NULL != m_pWnd) 
		m_pWnd -> SetBackgroundColor(cBkColor);
	else {
		m_cBkColor = cBkColor;
		m_fHasBkColor = true;
	}
	return S_OK;
}

// Implementation of get_BackColor
STDMETHODIMP CSabisTabChildWindow::get_BackColor(long *pcBkColor)
{
	CHECKOUTPOINTER(pcBkColor);
	if (NULL != m_pWnd) 
		*pcBkColor = m_pWnd -> GetBackgroundColor();
	else if (m_fHasBkColor) 
		*pcBkColor = m_cBkColor;
	else
		return E_UNEXPECTED;
	return S_OK;
}

// Implementation of put_Caption
STDMETHODIMP CSabisTabChildWindow::put_Caption(BSTR bstrCaption)
{
	_ASSERTE(NULL != m_pWnd);		// Fenster darf noch nicht existieren
	COM_TRY {
	// SABiS-Fenster wieder anzeigen
	CWaitCursor Wait;
	WManageTabWindows Tabs;

		THROW_FAILED_HRESULT(RetrieveTabManager(m_fUse2ndOne, Tabs.ppi()));

		_ASSERTE(m_bstrInit.Length() > 0);
		THROW_FAILED_HRESULT(Tabs -> RenameTabWindow(m_bstrInit, bstrCaption));
		m_bstrInit = bstrCaption;

	} COM_CATCH;
	return S_OK;
}

// Implementation of get_Caption
STDMETHODIMP CSabisTabChildWindow::get_Caption(BSTR *pbstrCaption)
{
	CHECKOUTPOINTER(pbstrCaption);
	*pbstrCaption = CComBSTR(m_bstrInit).Detach();
	return S_OK;
}

// Implementation of put_Enabled
STDMETHODIMP CSabisTabChildWindow::put_Enabled(VARIANT_BOOL fEnabled)
{
	_ASSERTE(NULL != m_pWnd);
	m_pWnd -> EnableWindow(fEnabled ? TRUE : FALSE);
	return S_OK;
}

// Implementation of get_Enabled
STDMETHODIMP CSabisTabChildWindow::get_Enabled(VARIANT_BOOL *pfEnabled)
{
	CHECKOUTPOINTER(pfEnabled);
	_ASSERTE(NULL != m_pWnd);

	*pfEnabled = m_pWnd -> IsWindowEnabled() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

// Implementation of get_Height
STDMETHODIMP CSabisTabChildWindow::get_Height(long *plHeight)
{
	CHECKOUTPOINTER(plHeight);
	_ASSERTE(NULL != m_pWnd);

CRect rect;

	RETURN_FAILED_HRESULT(GetWindowRect(rect));
	*plHeight = rect.Height();
	return S_OK;
}

// Implementation of put_Height
STDMETHODIMP CSabisTabChildWindow::put_Height(long lHeight)
{
	return S_OK;
}

// Implementation of get_hWnd
STDMETHODIMP CSabisTabChildWindow::get_hWnd(long *phWnd)
{
	CHECKOUTPOINTER(phWnd);
	*phWnd = reinterpret_cast<long>(m_pWnd -> GetSafeHwnd());
	return S_OK;
}

// Implementation of put_Icon
STDMETHODIMP CSabisTabChildWindow::put_Icon(VARIANT vPict)
{
	_ASSERTE(NULL != m_pWnd);		// Fenster darf noch nicht existieren
	COM_TRY {
	// SABiS-Fenster wieder anzeigen
	CWaitCursor Wait;

	WManageTabWindows Tabs;
	INT_PTR hHandle = NULL;

		THROW_FAILED_HRESULT(RetrieveTabManager(m_fUse2ndOne, Tabs.ppi()));

		_ASSERTE(m_bstrInit.Length() > 0);
		THROW_FAILED_HRESULT(Tabs -> FindTabWindow(m_bstrInit, &hHandle));
		THROW_FAILED_HRESULT(Tabs -> SetTabIcon(hHandle, vPict));

	} COM_CATCH;
	return S_OK;
}

// Implementation of get_Left
STDMETHODIMP CSabisTabChildWindow::get_Left(long *plLeft)
{
	CHECKOUTPOINTER(plLeft);
	_ASSERTE(NULL != m_pWnd);

CRect rect;

	RETURN_FAILED_HRESULT(GetWindowRect(rect));
	*plLeft = rect.left;
	return S_OK;
}

// Implementation of put_Left
STDMETHODIMP CSabisTabChildWindow::put_Left(long lLeft)
{
	return S_OK;
}

// Implementation of Move
STDMETHODIMP CSabisTabChildWindow::Move(long X, long Y)
{
	return S_OK;
}

// Implementation of OnKeyDown
STDMETHODIMP CSabisTabChildWindow::OnKeyDown(short *KeyCode, short *Shift)
{
	return S_OK;
}

// Implementation of put_Tag
STDMETHODIMP CSabisTabChildWindow::put_Tag(BSTR bstrTag)
{
	m_bstrTag = bstrTag;
	return S_OK;
}

// Implementation of get_Tag
STDMETHODIMP CSabisTabChildWindow::get_Tag(BSTR *pbstrTag)
{
	CHECKPOINTERHR(pbstrTag);

CComBSTR bstr (m_bstrTag);

	*pbstrTag = bstr.Detach();
	return S_OK;
}

// Implementation of get_Top
STDMETHODIMP CSabisTabChildWindow::get_Top(long *plTop)
{
	CHECKOUTPOINTER(plTop);
	_ASSERTE(NULL != m_pWnd);

CRect rect;

	RETURN_FAILED_HRESULT(GetWindowRect(rect));
	*plTop = rect.top;
	return S_OK;
}

// Implementation of put_Top
STDMETHODIMP CSabisTabChildWindow::put_Top(long lTop)
{
	return S_OK;
}

// Implementation of put_Visible
STDMETHODIMP CSabisTabChildWindow::put_Visible(VARIANT_BOOL fVisible)
{
bool fIThoughtItsVisible = m_fIThinkItsVisible;

	m_fIThinkItsVisible = fVisible ? true : false;
	if (m_fIThinkItsVisible) {
		if (NULL == m_pWnd || !fIThoughtItsVisible) {
			RETURN_FAILED_HRESULT(CreateClientWindow(true));
			_ASSERTE(NULL != m_pWnd);
		}
		else {
			_ASSERTE(::IsWindow(m_pWnd->GetSafeHwnd()));
			RETURN_FAILED_HRESULT(ReShow());
		}
		m_fWasShownOnce = true;
	}
	else if (NULL != m_pWnd && ::IsWindow(m_pWnd->GetSafeHwnd()) && m_fWasShownOnce) 
		DeleteWindow(true);
	return S_OK;
}

// Implementation of get_Visible
STDMETHODIMP CSabisTabChildWindow::get_Visible(VARIANT_BOOL *pfVisible)
{
	CHECKOUTPOINTER(pfVisible);

bool fVisible = false;

	if (NULL != m_pWnd && m_pWnd->IsWindowVisible())
		fVisible = true;

	*pfVisible = (m_fIThinkItsVisible && fVisible) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

// Implementation of get_Width
STDMETHODIMP CSabisTabChildWindow::get_Width(long *plWidth)
{
	CHECKOUTPOINTER(plWidth);
	_ASSERTE(NULL != m_pWnd);

CRect rect;

	RETURN_FAILED_HRESULT(GetWindowRect(rect));
	*plWidth = rect.Width();
	return S_OK;
}

// Implementation of put_Width
STDMETHODIMP CSabisTabChildWindow::put_Width(long lWIdth)
{
	return S_OK;
}

// Implementation of get_WindowState
STDMETHODIMP CSabisTabChildWindow::get_WindowState(long *plState)
{
	return S_OK;
}

// Implementation of put_WindowState
STDMETHODIMP CSabisTabChildWindow::put_WindowState(long lState)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Zugriffsfunktion auf das Fenster (wird bei Bedarf erzeugt)
CTRiASTabChild* CSabisTabChildWindow::GetWindow(HWND hWndParent)
{
	if (NULL == m_pWnd)	{
		TRY	{
			AFX_MANAGE_STATE(AfxGetAppModuleState());
			m_pWnd = new CTRiASTabChild(CWnd::FromHandlePermanent(hWndParent));
			if (m_fHasBkColor)
				m_pWnd -> SetBackgroundColor(m_cBkColor);
		}
		CATCH(CMemoryException, e) {
			;
		} END_CATCH
	}
	CHECKPOINTER(m_pWnd, NULL);	// endgültiger Check des Pointers 
								// keine weiteren Tests im Quellcode notwendig, 
								// solange dieser Accessor benutzt wird
	return m_pWnd;
}

HRESULT CSabisTabChildWindow::GetWindowRect(CRect& rect)
{
// get the screen coords of the wnd
	m_pWnd -> GetWindowRect(rect);

// change to client coordinates of the Parent
CWnd* pParent = m_pWnd -> GetParent();

	_ASSERTE(NULL != pParent);
	pParent -> ScreenToClient(rect);
	return S_OK;
}

/*static*/
HRESULT CSabisTabChildWindow::RetrieveTabManager(bool fUse2ndOne, 
	IManageTabWindows **ppITabs)
{
	CHECKOUTPOINTER(ppITabs);
	COM_TRY {
	WTriasXtensionSite Site;
	WServiceProvider SP;
	WManageTabWindows Tabs;

		_ASSERTE(NULL != g_pTE);
		THROW_FAILED_HRESULT(g_pTE -> GetXtensionSite(Site.ppi()));
		THROW_FAILED_HRESULT(Site -> QueryInterface(SP.ppi()));
		THROW_FAILED_HRESULT(SP -> QueryService(
			fUse2ndOne ? SID_ManageSABiSTabs2 : SID_ManageSABiSTabs, 
			__uuidof(IManageTabWindows), Tabs.ppv()));
		*ppITabs = Tabs.detach();

	} COM_CATCH;
	return S_OK;
}

