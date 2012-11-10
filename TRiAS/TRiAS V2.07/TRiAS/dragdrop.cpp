// Drag'n Drop für Erweiterungen
// File: DRAGDROP.CPP

#include "triaspre.hxx"

#if !defined(_OLD_DRAGNDROP)

#include <dirisole.h>
#include <xtsnguid.h>
#include "extmain3.hxx"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface(TRiASDropTarget);
DefineSmartInterface(DragDropAction);

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
STDMETHODIMP ExtensionList::DragEnter (DRAGDROPTYPE rgType, HWND hWnd, 
	IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
CTable r (*this);
HRESULT hr = E_FAIL;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	
		TX_ASSERT(NULL != (Extension *)l);
		if (!l) continue;

		hr = l -> DragEnter (rgType, hWnd, pIDataSource, grfKeyState, pt, pdwEffect);
		if (S_OK == hr)		// bearbeitet und raus, 
			return NOERROR;
	}

	return S_FALSE;
}

STDMETHODIMP ExtensionList::DragOver (
	DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, 
	DWORD *pdwEffect)
{
CTable r (*this);
HRESULT hr = E_FAIL;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	
		TX_ASSERT(NULL != (Extension *)l);
		if (!l) continue;

		hr = l -> DragOver (rgType, hWnd, grfKeyState, pt, pdwEffect);
		if (S_OK == hr)		// bearbeitet und raus, 
			return NOERROR;
	}

	return S_FALSE;
}

STDMETHODIMP ExtensionList::DragLeave (DRAGDROPTYPE rgType, HWND hWnd)
{
CTable r (*this);
HRESULT hr = E_FAIL;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	
		TX_ASSERT(NULL != (Extension *)l);
		if (!l) continue;

		hr = l -> DragLeave (rgType, hWnd);
		if (S_OK == hr)		// bearbeitet und raus, 
			return NOERROR;
	}

	return S_FALSE;
}

STDMETHODIMP ExtensionList::Drop (
	DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, 
	DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
CTable r (*this);
HRESULT hr = E_FAIL;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	
		TX_ASSERT(NULL != (Extension *)l);
		if (!l) continue;

		hr = l -> Drop (rgType, hWnd, pIDataSource, grfKeyState, pt, pdwEffect);
		if (S_OK == hr)		// bearbeitet und raus, 
			return NOERROR;
	}

	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop für die Erweiterungen selbst
HRESULT COleExtension::DragEnter (
	DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, 
	DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	if (NULL == m_pTE) return S_FALSE;		// nicht geladen
	if (m_fNoDragDropTarget) return S_FALSE;		// nicht unterstützt

HRESULT hr = S_FALSE;

	try {
	WTRiASDropTarget DropTarget (m_pTE);		// throws HRESULT

		hr = DropTarget -> DragEnter (rgType, hWnd, pIDataSource, grfKeyState, pt, pdwEffect);

	} catch (_com_error& hr) {
		m_fNoDragDropTarget = true;
		return _COM_ERROR(hr);
	}

return hr;
}

HRESULT COleExtension::DragOver (
	DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, 
	DWORD *pdwEffect)
{
	if (NULL == m_pTE) return S_FALSE;		// nicht geladen
	if (m_fNoDragDropTarget) return S_FALSE;		// nicht unterstützt

HRESULT hr = S_FALSE;

	try {
	WTRiASDropTarget DropTarget (m_pTE);		// throws HRESULT

		hr = DropTarget -> DragOver (rgType, hWnd, grfKeyState, pt, pdwEffect);

	} catch (_com_error& hr) {
		m_fNoDragDropTarget = true;
		return _COM_ERROR(hr);
	}

return hr;
}

HRESULT COleExtension::DragLeave (DRAGDROPTYPE rgType, HWND hWnd)
{
	if (NULL == m_pTE) return S_FALSE;		// nicht geladen
	if (m_fNoDragDropTarget) return S_FALSE;		// nicht unterstützt

HRESULT hr = S_FALSE;

	try {
	WTRiASDropTarget DropTarget (m_pTE);		// throws HRESULT

		hr = DropTarget -> DragLeave (rgType, hWnd);

	} catch (_com_error& hr) {
		m_fNoDragDropTarget = true;
		return _COM_ERROR(hr);
	}

return hr;
}

HRESULT COleExtension::Drop (
	DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, 
	DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	if (NULL == m_pTE) return S_FALSE;		// nicht geladen
	if (m_fNoDragDropTarget) return S_FALSE;		// nicht unterstützt

HRESULT hr = S_FALSE;

	try {
	WTRiASDropTarget DropTarget (m_pTE);		// throws HRESULT

		hr = DropTarget -> Drop (rgType, hWnd, pIDataSource, grfKeyState, pt, pdwEffect);
	
	} catch (_com_error& hr) {
		m_fNoDragDropTarget = true;
		return _COM_ERROR(hr);
	}

return hr;
}

HRESULT COleExtension::BeginDragDrop (
	DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags, IDataObject *pIDO)
{
	if (NULL == m_pTE) return S_FALSE;		// nicht geladen
	if (m_fNoDragDropSource) return S_FALSE;		// nicht unterstützt

HRESULT hr = S_FALSE;

	try {
	WDragDropAction DDAction (m_pTE);		// throws HRESULT

		hr = DDAction -> BeginDragDrop (rgType, hWnd, dwFlags, pIDO);
	
	} catch (_com_error& hr) {
		m_fNoDragDropSource = true;
		return _COM_ERROR(hr);
	}

return hr;
}

HRESULT COleExtension::EndDragDrop (
	DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags)
{
	if (NULL == m_pTE) return S_FALSE;		// nicht geladen
	if (m_fNoDragDropSource) return S_FALSE;		// nicht unterstützt

HRESULT hr = S_FALSE;

	try {
	WDragDropAction DDAction (m_pTE);		// throws HRESULT

		hr = DDAction -> EndDragDrop (rgType, hWnd, dwFlags);
	
	} catch (_com_error& hr) {
		m_fNoDragDropSource = true;
		return _COM_ERROR(hr);
	}

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// DragSource support für Erweiterungen
STDMETHODIMP ExtensionList::BeginDragDrop (
	DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags, IDataObject *pIDO)
{
	if (0 < piInterlockedIncrement(&m_lIsDropSourceInst)) {
	// nicht doppelt abarbeiten
		piInterlockedDecrement(&m_lIsDropSourceInst);
		return E_FAIL;
	}

CTable r (*this);
HRESULT hr = E_FAIL;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	
		TX_ASSERT(NULL != (Extension *)l);
		if (!l) continue;

		hr = l -> BeginDragDrop (rgType, hWnd, dwFlags, pIDO);
		if (S_OK == hr)		// bearbeitet und raus, 
			return NOERROR;
	}

	return S_FALSE;
}

STDMETHODIMP ExtensionList::DoDragDrop (
	DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDO, IDropSource *pISrc, 
	DWORD dwOKEffects, DWORD *pdwEffect)
{
	return E_NOTIMPL;
}

STDMETHODIMP ExtensionList::EndDragDrop (
	DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags)
{
CTable r (*this);
HRESULT hr = E_FAIL;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	
		TX_ASSERT(NULL != (Extension *)l);
		if (!l) continue;

		hr = l -> EndDragDrop (rgType, hWnd, dwFlags);
		if (S_OK == hr)		// bearbeitet und raus, 
			return NOERROR;
	}

	piInterlockedDecrement(&m_lIsDropSourceInst);
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop für ViewFenster
HRESULT IrisWind::DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{ 
	return GetFrame() -> DragEnter (pIDataSource, grfKeyState, pt, pdwEffect); 
}

HRESULT IrisWind::DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{ 
	return GetFrame() -> DragOver (grfKeyState, pt, pdwEffect); 
}

HRESULT IrisWind::DragLeave (void) 
{ 
	return GetFrame() -> DragLeave(); 
}
HRESULT IrisWind::Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{ 
	return GetFrame() -> Drop (pIDataSource, grfKeyState, pt, pdwEffect); 
}

///////////////////////////////////////////////////////////////////////////////
bool IrisWind::FQueryPasteFromData (IDataObject *pIDataObject)
{
	return true;
}

bool IrisWind::FPasteFromData (IDataObject *pIDataObject)
{
	return true;
}

UINT IrisWind::TestDroppablePoint (POINTL *pPt)
{
	return UDROP_CLIENT;
}

void IrisWind::GiveFeedBack (POINTL *pPt, bool fRemove, bool fDraw)
{
}

#endif // !_OLD_DRAGNDROP
