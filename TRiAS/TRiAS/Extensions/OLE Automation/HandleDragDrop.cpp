// File: HandleDragDrop.cpp

#include "precomp.hxx"		// Alle Header auf einen Blick

#include "GlobalFuncs.h"
#include "MonikerStream.h"
#include "ViewDropTarget.h"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface(EnumLONG);

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASDropTarget
STDMETHODIMP OLE2AutoExtension::DragEnter (
	DRAGDROPTYPE rgType, HWND hWnd, 
	IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return m_DropTargets.DragEnter (hWnd, pDataObj, grfKeyState, pt, pdwEffect);
}

STDMETHODIMP OLE2AutoExtension::DragOver (
	DRAGDROPTYPE rgType, HWND hWnd, 
	DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return m_DropTargets.DragOver (hWnd, grfKeyState, pt, pdwEffect);
}

STDMETHODIMP OLE2AutoExtension::DragLeave (DRAGDROPTYPE rgType, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return m_DropTargets.DragLeave (hWnd);
}

STDMETHODIMP OLE2AutoExtension::Drop (
	DRAGDROPTYPE rgType, HWND hWnd, 
	IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return m_DropTargets.Drop (hWnd, pDataObj, grfKeyState, pt, pdwEffect);
}

///////////////////////////////////////////////////////////////////////////////
// *** IDragDropAction
STDMETHODIMP OLE2AutoExtension::BeginDragDrop (
	DRAGDROPTYPE rgType, HWND hWndSrc, DWORD dwFlags, IDataObject *pIDO)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	m_fIsDragSourceInst = true;

	switch (rgType) {
	case DRAGDROPTYPE_VIEWWINDOW:	// Dokumentfenster
		m_hPrIsDragSource = DEX_GetActiveProjectHandle();
		BeginDragDropWindow (hWndSrc, dwFlags, pIDO);
		break;

	case DRAGDROPTYPE_ORWINDOW:		// Objektrecherchefenster
		BeginDragDropWindow (hWndSrc, dwFlags, pIDO);
		break;

	case DRAGDROPTYPE_LEGENDWINDOW:	// Legende
		break;
	}
	return S_FALSE;		// weiterreichen
}

STDMETHODIMP OLE2AutoExtension::DoDragDrop (
	DRAGDROPTYPE rgType, HWND hWnd, 
	IDataObject *pIDO, IDropSource *pISrc, DWORD dwOKEffects, LPDWORD pdwEffect)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return E_NOTIMPL;
}

STDMETHODIMP OLE2AutoExtension::EndDragDrop (
	DRAGDROPTYPE rgType, HWND hWndSrc, DWORD dwEffect)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	m_fIsDragSourceInst = false;
	m_hPrIsDragSource = NULL;
	return S_FALSE;		// weiterreichen
}

///////////////////////////////////////////////////////////////////////////////
// DragDrop aus ORFenster
HRESULT OLE2AutoExtension::BeginDragDropWindow (
	HWND hWndSrc, DWORD dwFlags, IDataObject *pIDO)
{
	if (NULL == pIDO) return E_POINTER;

	try {
	// in IDataObject muß die Objektmenge drinstehen
	WEnumLONG EnumObjs;
	WMoniker mkObjs, mkDoc;

		THROW_FAILED_HRESULT_ASSERT(GetEnumLONGData (pIDO, EnumObjs.ppi()));
		THROW_FAILED_HRESULT_ASSERT(CreateItemMonikerFromEnumLONG (EnumObjs, mkObjs.ppi()));
		THROW_FAILED_HRESULT_ASSERT(App()->GetDocMoniker (NULL, mkDoc.ppi()));

	// jetzt vollständigen Moniker zusammenstellen und streamen
	WMoniker mkFull;

		THROW_FAILED_HRESULT_ASSERT(mkDoc -> ComposeWith (mkObjs, false, mkFull.ppi()));

		THROW_FAILED_HRESULT_ASSERT(SetMonikerData (mkDoc, pIDO, &c_feMkGeoDocument));
		THROW_FAILED_HRESULT_ASSERT(SetMonikerData (mkFull, pIDO, &c_feMkGeoObjects));

	// diese Applikation als aktives Objekt registrieren
		THROW_FAILED_HRESULT_ASSERT(ReRegisterActiveObject());

	} catch (_com_error& hr) {
		ASSERT(_COM_ERROR(hr) == S_OK);
		return _COM_ERROR(hr);
	}

	return S_OK;
}

HRESULT OLE2AutoExtension::ReRegisterActiveObject (void)
{
HRESULT hr = S_OK;

	if (m_dwRegister) {
	// aktives Objekt abmelden
		hr = RevokeActiveObject (m_dwRegister, NULL);
		if (FAILED(hr)) return hr;

		m_dwRegister = 0L;
	}

// aktives Objekt wieder anmelden (RunningObjectTable)
	return RegisterActiveObject ((_DApplication *)m_pApp, CLSID_Application, 
								 ACTIVEOBJECT_STRONG, &m_dwRegister);
}

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop support - Liste der installierten DropTargets
HRESULT OLE2AutoExtension::InstallDropTargets (HPROJECT hPrDst)
{
// installieren aller bekannten DropTargets
	try {
	// DropTarget für DokumentFenster
	CComObject<CViewDropTarget> *pViewTarget = NULL;
	HRESULT hr = CComObject<CViewDropTarget>::CreateInstance(&pViewTarget);

		if (FAILED(hr)) _com_issue_error(hr);
		
		if (pViewTarget -> FInit(this, App()->FGetGeoDocument (hPrDst))) 
		{
		WDropTarget ViewTarget (pViewTarget);
		HWND hWnd = DEX_GetActiveViewWindow();

			ASSERT(::IsWindow(hWnd));

			m_DropTargets.insert(hWnd, ViewTarget);
		}

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	} catch (...) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT OLE2AutoExtension::RemoveDropTargets (void)
{
	m_DropTargets.erase();
	return S_OK;
}

