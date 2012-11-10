// Collection von Views (ProgrammierInterface) ------------------------
// File: VIEWSDSP.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "viewarry.hxx"		// CGeoViewsArray
#include "enuviews.hxx"		// CEnumViews
#include "views.hxx"		// Collection: Views
#include "view.hxx"		// View

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// ProgrammierInterfaceFunktionen ---------------------------------------------
STDMETHODIMP CGeoViews::get_isA (LONG *plRTTI)
{
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoViews;
	return NOERROR;
}

STDMETHODIMP CGeoViews::get_Parent (IDispatch **ppIParent)
{
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIParent);
}

STDMETHODIMP CGeoViews::get_Application (IDispatch **ppIApp)
{
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIApp);
}

STDMETHODIMP CGeoViews::put_Parent (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGeoViews::put_Application (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

// Liefert die Anzahl der Objektklassen ---------------------------------------
STDMETHODIMP CGeoViews::get_Count (long *plCount)
{
	if (NULL == plCount) return E_POINTER;

	*plCount = Count();
	return NOERROR;
}


// Liefert eine der enthaltenen Objektklassen, entweder über einen numerischen
// Index oder über den Kurztext der gesuchten Klasse
STDMETHODIMP CGeoViews::Item (VARIANT vt, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// versuchen, Parameter auszuwerten
CComVariant vArg;
HRESULT hr = VariantChangeType (&vArg, &vt, 0, VT_I4);	// Zahl als Index

	if (SUCCEEDED(hr)) {
		if (V_I4(&vArg) > 0 && ULONG(V_I4(&vArg)) <= Count()) 
		// Index ist gültig: liefern der gesuchten View
			return GetViewDisp (V_I4(&vArg)-1, (LPVOID *)ppIDisp);

		return DISP_E_BADINDEX;
	} 

// 2. Versuch vt als String interpretieren (Name ?)
	hr = VariantChangeType (&vArg, &vt, 0, VT_BSTR);
	if (SUCCEEDED(hr)) {
	string str = AnsiString(V_BSTR(&vArg));

		return GetViewDisp (str.c_str(), (LPVOID *)ppIDisp);
	}

// 3. Versuch: evtl. ist Parameter nicht gegeben
	hr = VariantChangeType (&vArg, &vt, 0, VT_ERROR);
	if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) 
	// liefert sich selbst
		hr = ((_DViews *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);

	return hr;
}

// Liefert neuen Enumerator für diese Collection ------------------------------
STDMETHODIMP CGeoViews::_NewEnum (IUnknown **ppIUnk)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == ppIUnk) return E_POINTER;

// neuen Enumerator anlegen
CEnumViews *pEViews = CEnumViews::CreateInstance (m_pEnumViews-> m_pViewsArray);

	if (NULL == pEViews) return E_OUTOFMEMORY;

HRESULT hr = pEViews -> QueryInterface (IID_IEnumVARIANT, (LPVOID *)ppIUnk);	

	pEViews -> Release();
		
return hr;
}



STDMETHODIMP CGeoViews::Add(VARIANT vView, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// versuchen, Parameter auszuwerten
CComVariant vArg;
INITVIEWSTATUS rgIOS = INITVIEWSTATUS_Error;
HRESULT	hr = VariantChangeType (&vArg, &vView, 0, VT_BSTR);

	if (FAILED(hr)) return hr;

string strName = AnsiString(V_BSTR(&vArg));
long lIndex = m_pEnumViews -> m_pViewsArray -> hasView (strName.c_str());

	if (-1L == lIndex) {
	CGeoViewCreator ViewCr (*(m_pEnumViews -> m_pViewsArray));
	
		rgIOS = m_pICProc (m_pUnk, m_pApp, m_pDoc, ViewCr, m_dwData, &strName);
		if (INITVIEWSTATUS_Error == rgIOS) 
			return E_UNEXPECTED;
	} else 
		rgIOS = INITVIEWSTATUS_Exists;
	
	if (INITVIEWSTATUS_Created == rgIOS || INITVIEWSTATUS_Exists == rgIOS) 
		return GetViewDisp (strName.c_str(), (LPVOID *)ppIDisp);	// get IDispatch

return E_UNEXPECTED;
}

STDMETHODIMP CGeoViews::Remove (VARIANT vView)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

CComVariant vArg;
HRESULT	hr = vArg.ChangeType (VT_BSTR, &vView);

	if (SUCCEEDED(hr)) {
	string strName = AnsiString(V_BSTR(&vArg));

		if (NULL != m_pDCProc && !(*m_pDCProc)(strName.c_str(), m_pDoc))
			return E_FAIL;

		m_pEnumViews -> DeleteView (strName.c_str());
		return NOERROR;
	}
	return hr;
}

STDMETHODIMP CGeoViews::Refresh (void)
{
// wenn Informationen über Herkunft existieren, dann neu erzeugen, ansonsten
// tote Seelen beseitigen
	if (CanRegenerate()) 
		return Regenerate() ? NOERROR : E_OUTOFMEMORY;

	return m_pEnumViews -> m_pViewsArray -> Refresh();
}

