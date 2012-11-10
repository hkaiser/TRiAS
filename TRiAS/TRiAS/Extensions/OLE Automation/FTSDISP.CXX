// Collection vor Features (ProgrammierInterface) -----------------
// File: FTSDISP.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "ftsarray.hxx"
#include "enumfts.hxx"
#include "fts.hxx"		// Collection: Features
#include "feat.hxx"		// Feature

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// ProgrammierInterfaceFunktionen ---------------------------------------------
// Das StandardProperty Parent liefert das übergeordnete Objekt, über welches 
// diese Collection angelegt wurde.
STDMETHODIMP CGeoFeatures::get_isA (LONG *plRTTI)
{
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoFeatures;
	return NOERROR;
}

STDMETHODIMP CGeoFeatures::get_Parent (IDispatch **ppIDisp)
{
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

// Dieses StandardProperty liefert das ApplicationInterface (das allen anderen
// Features übergeordnete)
STDMETHODIMP CGeoFeatures::get_Application (IDispatch **ppIDisp)
{
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoFeatures::put_Parent (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGeoFeatures::put_Application (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

// Liefert die Anzahl der Feature ---------------------------------
STDMETHODIMP CGeoFeatures::get_Count (long *plCount)
{
	if (NULL == plCount) return E_POINTER;

	*plCount = Count();
	return NOERROR;
}


STDMETHODIMP CGeoFeatures::Item (VARIANT vt, IDispatch **ppIDisp)
{
// versuchen, Parameter auszuwerten
CComVariant vArg; 
HRESULT hr = VariantChangeType (&vArg, &vt, 0, VT_I4);	// Zahl als Index 

	if (SUCCEEDED(hr)) {
		if (V_I4(&vArg) > 0 && ULONG(V_I4(&vArg)) <= Count()) 
		// Index ist gültig: Dispatch-Interface abfragen
			return GetFeatureDisp (V_I4(&vArg)-1, (DGeoFeature **)ppIDisp);

		return DISP_E_BADINDEX;	// raus hier
	}


// 2. Versuch vt als String interpretieren (Name ?)
	hr = VariantChangeType (&vArg, &vt, 0, VT_BSTR);
	if (SUCCEEDED(hr)) {
	string str = AnsiString(V_BSTR(&vArg));

		return GetFeatureDisp (str.c_str(), (DGeoFeature **)ppIDisp);
	}

// 3. Versuch: evtl. ist Parameter nicht gegeben
	hr = VariantChangeType (&vArg, &vt, 0, VT_ERROR);
	if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) 
	// liefert sich selbst (FeatureCollection)
		hr = ((DGeoFeatures *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);

	return hr;
}


// Dieses StandardInterface liefert einen neuen Enumerator IEnumVARIANT mit
// allen Features
// Dieses gelieferte Interface ist allerdings von VB aus schlecht verwendbar.
//
STDMETHODIMP CGeoFeatures::_NewEnum (IUnknown **ppIUnk)
{
	if (NULL == ppIUnk) return E_POINTER;

// neuen Enumerator anlegen
CEnumGeoFts *pEGeoFts = CEnumGeoFts::CreateInstance (m_pEnumFts -> m_pGeoFtsArray);

	if (NULL == pEGeoFts) return E_OUTOFMEMORY;

HRESULT hr = pEGeoFts -> QueryInterface (IID_IEnumVARIANT, (LPVOID *)ppIUnk);	

	pEGeoFts -> Release();
		
return hr;
}


STDMETHODIMP CGeoFeatures::Add(VARIANT vFeature, IDispatch **ppIDisp)
{
// versuchen, Parameter auszuwerten
CComVariant vArg; 
INITFEATSTATUS rgIOS = INITFEATSTATUS_Error;
HRESULT	hr = VariantChangeType (&vArg, &vFeature, 0, VT_BSTR);

	if (FAILED(hr)) return hr;

string strName = AnsiString(V_BSTR(&vArg));
long lIndex = m_pEnumFts -> m_pGeoFtsArray -> hasFeature (strName.c_str());

	if (lIndex == -1L) {
	CGeoFeatureBaseCreator FeatureCr (*(m_pEnumFts -> m_pGeoFtsArray));
	
		rgIOS = m_pICProc (m_pUnk, m_pApp, m_pDoc, m_pViewClsObj, FeatureCr, m_dwData, &strName);
		if (INITFEATSTATUS_Error == rgIOS)
			return E_FAIL;
	} else 
		rgIOS = INITFEATSTATUS_Exists;
	
	if (INITFEATSTATUS_Created == rgIOS || INITFEATSTATUS_Exists == rgIOS)
		return GetFeatureDisp (strName.c_str(), (DGeoFeature **)ppIDisp);

return E_UNEXPECTED;
}

STDMETHODIMP CGeoFeatures::Remove(VARIANT vFeature)
{
CComVariant vArg; 
HRESULT	hr = vArg.ChangeType (VT_BSTR, &vFeature);

	if (SUCCEEDED(hr)) {
	string strName = AnsiString(V_BSTR(&vArg));

		if (NULL != m_pDCProc && !(*m_pDCProc)(strName.c_str(), m_pViewClsObj))
			return E_FAIL;

		m_pEnumFts -> DeleteFeature (strName.c_str());
		return NOERROR;
	}
	return hr;
}

STDMETHODIMP CGeoFeatures::Refresh (void)
{
// wenn Informationen über Herkunft existieren, dann neu erzeugen, ansonsten
// tote Seelen beseitigen
	if (CanRegenerate()) 
		return Regenerate() ? NOERROR : E_OUTOFMEMORY;

	return m_pEnumFts -> m_pGeoFtsArray -> Refresh();
}

