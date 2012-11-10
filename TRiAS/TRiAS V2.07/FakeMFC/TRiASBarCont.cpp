// TRiASBarCont.cpp : Implementation of CcomApp and DLL registration.

#include "fakemfcp.hxx"
#include <xtensnn.h>

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>
#include <fnamestr.h>

#include "strings.h"
#include "Wrapper.h"		// SmartInterfaces
#include "MainFrm.h"
#include "TRiASBarCont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Enumerator aller installierten ToolBars - (NEnumWTRiASToolBar)
DefineEnumerator2(WTRiASToolBar, IID_IEnumITRiASBar);
// typedef __Enumerator<WTRiASToolBar, &IID_IEnumITRiASBar, list<WTRiASToolBar> > NEnumWTRiASToolBar;

// SmartInterface für diesen Enumerator - (WEnumWTRiASToolBar)
DefineSmartEnumerator(WTRiASToolBar);
// typedef __Interface<IEnum<WTRiASToolBar>, CIID_WTRiASToolBarEnum> WEnumWTRiASToolBar;

// OutputIterator, der den o.g. Enumerator füllt - (OutEnumWTRiASToolBar)
DefineEnumOutputIterator(WTRiASToolBar);
// typedef oenum_iterator<WTRiASToolBar, CIID_WTRiASToolBarEnum> OutEnumWTRiASToolBar;

// InputIterator, der aus dem o.g. Enumerator liest - (InEnumWTRiASToolBar)
DefineEnumInputIterator(WTRiASToolBar);
// 	typedef ienum_iterator<WTRiASToolBar, CIID_WTRiASToolBarEnum, ptrdiff_t> InEnumWTRiASToolBar;

///////////////////////////////////////////////////////////////////////////////
// sonstige (stino)
DefineSmartInterface(Dispatch);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(EnumVARIANT);
DefineSmartInterface2(DControlToolBar, IID_DControlToolBar);

/////////////////////////////////////////////////////////////////////////////
// *** ITRiASBarCont specific functions
STDMETHODIMP CTRiASBarCont::EnumTRiASBars (IEnumITRiASBar **ppEnum)
{
	ASSERT(NULL != m_pFrame);
	ASSERT_VALID(m_pFrame);

	return m_pFrame -> GetEnumTRiASToolBars (ppEnum);
}

STDMETHODIMP CTRiASBarCont::FindTRiASBar (LPCSTR pcName, ITRiASBar **ppIBar)
{
	ASSERT(NULL != m_pFrame);
	ASSERT_VALID(m_pFrame);

WEnumITRiASBar IEnum;
HRESULT hr = m_pFrame -> GetEnumTRiASToolBars (IEnum.ppi());

	if (FAILED(hr)) return hr;

ITRiASBar *pIBar = NULL;

	for (IEnum -> Reset();
		 S_OK == IEnum -> Next (1, &pIBar, NULL); /**/)
	{
		try {
		WTRiASToolBar ToolBar = pIBar;		// throws HRESULT
		char cbName[64];
		HRESULT hr = ToolBar -> GetBarStyle (cbName, sizeof(cbName), NULL, NULL, NULL);

			if (SUCCEEDED(hr) && !strcmp(cbName, pcName)) {
				*ppIBar = pIBar;		// übernummt RefCnt
				return S_OK;
			}
		} catch (_com_error& hr) {
			UNUSED(hr);
			ASSERT(_COM_ERROR(hr) == S_OK);
		}
		pIBar -> Release();
		pIBar = NULL;
	}

return S_FALSE;		// not found
}

STDMETHODIMP CTRiASBarCont::AddTRiASBar (
	LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, ITRiASBar **ppITools)
{
	if (NULL == ppITools) return E_POINTER;

	*ppITools = NULL;

	try {
#if defined(_USE_SEC_CLASSES)
	WTRiASToolBar Tools;

		THROW_FAILED_HRESULT(m_pFrame -> CreateToolBar (pcName, Tools.ppi()));

	// Namen etc. setzen
	DWORD dwExStyle = 0L;

		THROW_FAILED_HRESULT(Tools -> GetBarStyle (NULL, 0, NULL, NULL, &dwExStyle));
		THROW_FAILED_HRESULT(Tools -> SetBarStyle (pcName, dwStyle, dwStyleEx | dwExStyle, false));
#else
	WTRiASToolBar Tools(CLSID_TRiASToolBar);	// throws hr

		{	// initialisieren
		WPersistStreamInit IInit = Tools;		// throws hr

			THROW_FAILED_HRESULT(IInit -> InitNew());
		}

	// Namen setzen
		THROW_FAILED_HRESULT(Tools -> SetBarStyle (pcName, dwStyle, dwStyleEx, false));
#endif // _USE_SEC_CLASSES

	// Ergebnis liefern
		*ppITools = Tools.detach();
	
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

STDMETHODIMP CTRiASBarCont::DeleteTRiASBar (LPCSTR pcName)
{
	try {
	WTRiASBar Tools;

		THROW_FAILED_HRESULT(FindTRiASBar (pcName, Tools.ppi()));
		THROW_FAILED_HRESULT(WDControlToolBar(Tools) -> Remove());
	
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	} 

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// *** DControlToolBars specific functions
STDMETHODIMP CTRiASBarCont::get_isA (LONG *plRTTI)					// ObjektTyp (RTTI)
{
	if (NULL == plRTTI) return E_POINTER;

	*plRTTI = RTTI_ToolBars;
	return NOERROR;
}

STDMETHODIMP CTRiASBarCont::get_Parent (IDispatch **ppIBase)		// übergeordnetes Objekt
{
	if (NULL != (IUnknown *)m_Parent) 
		return m_Parent -> QueryInterface (IID_IDispatch, (LPVOID *)ppIBase); 
	return E_UNEXPECTED;
}

STDMETHODIMP CTRiASBarCont::put_Parent (IDispatch *pIBase)
{
	m_Parent = pIBase; 
	return NOERROR;
}

STDMETHODIMP CTRiASBarCont::get_Application (IDispatch **ppIApp)	// Anwendung
{
	if (NULL != (IUnknown *)m_App) 
		return m_App -> QueryInterface (IID_IDispatch, (LPVOID *)ppIApp); 
	return E_UNEXPECTED;
}

STDMETHODIMP CTRiASBarCont::put_Application (IDispatch *pIApp)
{
	m_App = pIApp; 
	return NOERROR;
}

STDMETHODIMP CTRiASBarCont::get_Count (LONG *plCnt)
{
	if (NULL == plCnt) return E_POINTER;

	ASSERT(NULL != m_pFrame);
	ASSERT_VALID(m_pFrame);

WEnumITRiASBar IEnum;

	return m_pFrame -> GetEnumTRiASToolBars (IEnum.ppi(), plCnt);
}

STDMETHODIMP CTRiASBarCont::Item (VARIANT vItem, IDispatch **ppIDisp)
{
	if (NULL == ppIDisp) return E_POINTER;
	*ppIDisp = NULL;

	try {
		USES_CONVERSION;

	CComVariant vPar;
	WTRiASBar Bar;

		THROW_FAILED_HRESULT(VariantChangeType (&vPar, &vItem, 0, VT_BSTR));
		THROW_FAILED_HRESULT(FindTRiASBar (OLE2A(V_BSTR(&vPar)), Bar.ppi()));

	WDispatch Disp (Bar);

		*ppIDisp = Disp.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

STDMETHODIMP CTRiASBarCont::_NewEnum (IUnknown **pvEnum)
{
	if (NULL == pvEnum) return E_POINTER;

CComObject<CToolBarNewEnum> *pNewEnum = NULL;
HRESULT hr = CComObject<CToolBarNewEnum>::CreateInstance(&pNewEnum);

	if (FAILED(hr)) return hr;

WUnknown Unk (pNewEnum);	

	hr = pNewEnum -> FInit (m_pFrame);
	if (FAILED(hr)) return hr;

	*pvEnum = Unk.detach();
	return S_OK;
}

STDMETHODIMP CTRiASBarCont::Add (VARIANT vAdd, IDispatch **ppIDisp)
{
	if (NULL == ppIDisp) return E_POINTER;
	*ppIDisp = NULL;

	try {
		USES_CONVERSION;

	WTRiASBar Bar;
	DWORD dwStyle = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
					CBRS_BORDER_ANY|CBRS_BORDER_3D|CBRS_FLYBY;
	CComVariant vPar;

		THROW_FAILED_HRESULT(VariantChangeType (&vPar, &vAdd, 0, VT_BSTR));
		THROW_FAILED_HRESULT(AddTRiASBar (OLE2A(V_BSTR(&vPar)), dwStyle, 0L, Bar.ppi()));

	WDispatch Disp (Bar);		// throws hr

		*ppIDisp = Disp.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

STDMETHODIMP CTRiASBarCont::Remove (VARIANT vRemove)
{
	try {
		USES_CONVERSION;

	CComVariant vPar;

		THROW_FAILED_HRESULT(VariantChangeType (&vPar, &vRemove, 0, VT_BSTR));
		THROW_FAILED_HRESULT(DeleteTRiASBar(OLE2A(V_BSTR(&vPar))));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

STDMETHODIMP CTRiASBarCont::Refresh (void)
{
	return S_OK;		// nothing to do
}

LPSTR ReplaceExt (LPSTR pPath, LPCSTR pcNewExt)
{
string strName (pPath);
string strNew = get_drive(strName) + get_path(strName) + get_name(strName) + pcNewExt;

	strcpy (pPath, strNew.c_str());
	return pPath;
}

STDMETHODIMP CTRiASBarCont::SaveState (VARIANT vKey, VARIANT vProject)
{
CComVariant vArg, vPrj;
HRESULT hr = vPrj.ChangeType (VT_BOOL, &vProject);

	USES_CONVERSION;
	if (SUCCEEDED(hr) && V_BOOL(&vPrj)) {
		hr = vArg.ChangeType (VT_BSTR, &vKey);
		if (FAILED(hr))	return hr;

	char cbBuffer[_MAX_PATH];

		if (NULL != DEX_GetActiveProject(cbBuffer)) 
			return m_pFrame -> SaveToolbarState (OLE2A(V_BSTR(&vArg)), ReplaceExt (cbBuffer, g_cbINI));

		return E_FAIL;
	} else {
	// entweder lediglich wegschreiben oder neuen Namen vergeben
		hr = vArg.ChangeType (VT_BSTR, &vKey);
		return m_pFrame -> SaveToolbarState (FAILED(hr) ? NULL : OLE2A(V_BSTR(&vArg)));
	}
}

STDMETHODIMP CTRiASBarCont::LoadState (VARIANT vKey, VARIANT vProject)
{
CComVariant vArg, vPrj;
HRESULT hr = vPrj.ChangeType (VT_BOOL, &vProject);

	USES_CONVERSION;
	if (SUCCEEDED(hr) && V_BOOL(&vPrj)) {
		hr = vArg.ChangeType (VT_BSTR, &vKey);
		if (FAILED(hr))	return hr;

	char cbBuffer[_MAX_PATH];

		if (NULL != DEX_GetActiveProject(cbBuffer)) 
			return m_pFrame -> LoadToolbarState (OLE2A(V_BSTR(&vArg)), ReplaceExt (cbBuffer, g_cbINI));

		return E_FAIL;
	} else {
	// entweder lediglich wegschreiben oder neuen Namen vergeben
		hr = vArg.ChangeType (VT_BSTR, &vKey);
		return m_pFrame -> LoadToolbarState (FAILED(hr) ? NULL : OLE2A(V_BSTR(&vArg)));
	}
}

///////////////////////////////////////////////////////////////////////////////
// _NewEnum-Enumerator
HRESULT CToolBarNewEnum::FInit (CMainFrame *pFrame)
{
	ASSERT(NULL != pFrame);
	ASSERT_VALID(pFrame);

	return pFrame -> GetEnumTRiASToolBars (m_Enum.ppi());
}

// *** IEnumVARIANT methods
STDMETHODIMP CToolBarNewEnum::Next (ULONG celt, VARIANT *rgvar, ULONG *pceltFetched)
{
	if (!m_Enum) return E_UNEXPECTED;

ITRiASBar *pIBar = NULL;
int iLast = 0;

	for(ULONG i = 0; i < celt; ++i)
		VariantInit (&rgvar[i]);

	try {
	HRESULT hr = S_OK;

		for(ULONG i = 0; i < celt; ++i) {
			hr = m_Enum -> Next (1, &pIBar, NULL);
			if (FAILED(hr)) _com_issue_error(hr);

			if (S_FALSE == hr) {
			// das war der letzte
				iLast = i;
				break;
			}

		WDispatch ToolBar (pIBar);		// throws HRESULT

			pIBar -> Release();
			pIBar = NULL;

			V_VT(&rgvar[i]) = VT_DISPATCH;
			V_DISPATCH(&rgvar[i]) = ToolBar.detach();
		}

	} catch (_com_error& hr) {
	// alles bisherige wieder aufräumen
		for(ULONG i = 0; i < celt; ++i)
			VariantClear(&rgvar[i]);
		
		if (NULL != pIBar) 
			pIBar -> Release();
		return _COM_ERROR(hr);
	}

	if (NULL != pceltFetched)
		*pceltFetched = iLast;

	return S_OK;
}

STDMETHODIMP CToolBarNewEnum::Skip (ULONG celt)
{
	if (!m_Enum) return E_UNEXPECTED;

	return m_Enum -> Skip (celt);
}

STDMETHODIMP CToolBarNewEnum::Reset (void)
{
	if (!m_Enum) return E_UNEXPECTED;

	return m_Enum -> Reset();
}

STDMETHODIMP CToolBarNewEnum::Clone (LPENUMVARIANT *ppenum)
{
	if (!m_Enum) return E_UNEXPECTED;

	try {
	WEnumWTRiASToolBar NewEnum (new NEnumWTRiASToolBar());

	// InterfacePointer umkopieren
		{
		InEnumWTRiASToolBar in_iter (m_Enum);
		OutEnumWTRiASToolBar out_iter (NewEnum);

			copy (in_iter, InEnumWTRiASToolBar(), out_iter);
		}
		NewEnum -> Release();			// wird mit RefCnt 1 generiert
		
	CComObject<CToolBarNewEnum> *pNewEnum = NULL;
	
		THROW_FAILED_HRESULT(CComObject<CToolBarNewEnum>::CreateInstance(&pNewEnum));

	WEnumVARIANT Result (pNewEnum);		// RefCnt ist jetzt 1

		THROW_FAILED_HRESULT(pNewEnum -> FInit ((IEnumITRiASBar *)(IEnum<WTRiASToolBar> *)NewEnum));

		*ppenum = Result.detach();

	} catch (CMemoryException *e) {
		e -> Delete();
		return E_OUTOFMEMORY;
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}


