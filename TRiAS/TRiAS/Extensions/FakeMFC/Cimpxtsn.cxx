// Implementation des ITriasXtension ------------------------------------------
// File: CIMPXTSN.CXX

#include "fakemfcp.hxx"

#include <xtsnguid.h>

#include "cimpxtsn.hxx"
#include "FakeMfc.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImpTriasXtension :: CImpTriasXtension (LPUNKNOWN pUnkOuter, CFakeMFCExtension *pObj)
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
#if defined(_USE_DRAG_N_DROP)
// die Abfrage muﬂ vor dem UnkOut erfolgen, da es sonst eine Rekursion gibt
	if (riid == IID_ITRiASDropTarget) {
		*ppvObj = static_cast<ITRiASDropTarget *>(this);
		LPUNKNOWN(*ppvObj) -> AddRef();
		return S_OK;
	}
	else if (riid == IID_IDragDropAction) {
		*ppvObj = static_cast<IDragDropAction *>(this);
		LPUNKNOWN(*ppvObj) -> AddRef();
		return S_OK;
	}
#endif // defined(_USE_DRAG_N_DROP)
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
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> LoadExtension (pTL, hWnd);
}

// Abgeleitete Funktionen sollten zuerst! diese Funktion rufen ----------------
STDMETHODIMP_(BOOL) CImpTriasXtension :: InitExtension (short iMode)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> InitExtension (iMode);
}

STDMETHODIMP_(BOOL) CImpTriasXtension :: UnLoadExtension (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> UnLoadExtension();
}

STDMETHODIMP_(BOOL)  CImpTriasXtension :: MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> MenuInit (hMenu, lParam, hWnd);
}

STDMETHODIMP_(BOOL) CImpTriasXtension :: MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> MenuSelect (uiMenuID, hMenu, hWnd);
}

STDMETHODIMP_(BOOL) CImpTriasXtension :: MenuCommand (WPARAM wParam, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> MenuCommand (wParam, hWnd);
}

STDMETHODIMP_(LRESULT) CImpTriasXtension :: Notification (WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> Notification (wParam, lParam);
}

STDMETHODIMP_(LRESULT) CImpTriasXtension :: WindowsNotification (UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> WindowsNotification (wMsg, wParam, lParam);
}

STDMETHODIMP_(LRESULT) CImpTriasXtension :: GetCapabilities (UINT uiCap)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> GetCapabilities (uiCap);
}

// *** ITriasXtension2 specific functions ***
STDMETHODIMP CImpTriasXtension :: SetXtensionSite (ITriasXtensionSite *pXtnSite) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> SetXtensionSite (pXtnSite);
}

///////////////////////////////////////////////////////////////////////////////
// DropTarget f¸r CF_DROP
#if defined(_USE_DRAG_N_DROP)
// *** ITRiASDropTarget
STDMETHODIMP CImpTriasXtension::DragEnter (
	DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> DragEnter (rgType, hWnd, pDataObj, grfKeyState, pt, pdwEffect);
}

STDMETHODIMP CImpTriasXtension::DragOver (
	DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> DragOver (rgType, hWnd, grfKeyState, pt, pdwEffect);
}

STDMETHODIMP CImpTriasXtension::DragLeave (DRAGDROPTYPE rgType, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> DragLeave (rgType, hWnd);
}

STDMETHODIMP CImpTriasXtension::Drop (
	DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return m_pObj -> Drop (rgType, hWnd, pDataObj, grfKeyState, pt, pdwEffect);
}

// IDragDropAction
STDMETHODIMP CImpTriasXtension::BeginDragDrop (DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags, IDataObject *pIDO)
{
	return S_FALSE;
}

STDMETHODIMP CImpTriasXtension::DoDragDrop (DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDO, IDropSource *pISrc, DWORD dwOKEffects, DWORD *pdwEffect)
{
	return S_FALSE;
}

STDMETHODIMP CImpTriasXtension::EndDragDrop (DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags)
{
	return S_FALSE;
}


#endif // defined(_USE_DRAG_N_DROP)

