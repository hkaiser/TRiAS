// Implementation des ITriasXtension ------------------------------------------
// File: CIMPXTSN.CXX

#include "fakemfcp.hxx"
#include "cimpxtsn.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImpTriasXtension :: CImpTriasXtension (LPUNKNOWN pUnkOuter, CTriasExtension *pObj)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG
	m_pUnkOuter = pUnkOuter;
	m_pObj = pObj;
}	

CImpTriasXtension :: ~CImpTriasXtension (void)
{
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CImpTriasXtension :: QueryInterface (REFIID riid, LPVOID FAR* ppvObj)
{
	return m_pUnkOuter -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CImpTriasXtension :: AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;	// debug purposes only
#endif // _DEBUG
	return m_pUnkOuter -> AddRef();
}

STDMETHODIMP_(ULONG) CImpTriasXtension :: Release (void)
{
#if defined(_DEBUG)
	--m_dwRefCnt;	// debug purposes only
#endif // _DEBUG
	return m_pUnkOuter -> Release();
}

// *** ITriasXtension specific functions *** ----------------------------------
STDMETHODIMP_(HDEX) CImpTriasXtension :: LoadExtension (TRIASLOADEX *pTL, HWND hWnd)
{
	return m_pObj -> LoadExtension (pTL, hWnd);
}

// Abgeleitete Funktionen sollten zuerst! diese Funktion rufen ----------------
STDMETHODIMP_(bool) CImpTriasXtension :: InitExtension (short iMode)
{
	return m_pObj -> InitExtension (iMode);
}

STDMETHODIMP_(bool) CImpTriasXtension :: UnLoadExtension (void)
{
	return m_pObj -> UnLoadExtension();
}

STDMETHODIMP_(bool)  CImpTriasXtension :: MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	return m_pObj -> MenuInit (hMenu, lParam, hWnd);
}

STDMETHODIMP_(bool) CImpTriasXtension :: MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	return m_pObj -> MenuSelect (uiMenuID, hMenu, hWnd);
}

STDMETHODIMP_(bool) CImpTriasXtension :: MenuCommand (WPARAM wParam, HWND hWnd)
{
	return m_pObj -> MenuCommand (wParam, hWnd);
}

STDMETHODIMP_(LRESULT) CImpTriasXtension :: Notification (WPARAM wParam, LPARAM lParam)
{
	return m_pObj -> Notification (wParam, lParam);
}

STDMETHODIMP_(LRESULT) CImpTriasXtension :: WindowsNotification (UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	return m_pObj -> WindowsNotification (wMsg, wParam, lParam);
}

STDMETHODIMP_(LRESULT) CImpTriasXtension :: GetCapabilities (UINT uiCap)
{
	return m_pObj -> GetCapabilities (uiCap);
}

// *** ITriasXtension2 specific functions ***
STDMETHODIMP CImpTriasXtension :: SetXtensionSite (ITriasXtensionSite *pXtnSite) 
{
	return m_pObj -> SetXtensionSite (pXtnSite);
}

