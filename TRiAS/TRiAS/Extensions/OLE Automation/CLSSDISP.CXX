// Collection von Objektklassen (ProgrammierInterface) ------------------------
// File: CLSSDISP.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "clsarray.hxx"		// CIdentArray
#include "enumclss.hxx"		// CEnumClasses
#include "classes.hxx"		// Collection: GeoClasses
#include "class.hxx"		// ObjektKlasse

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// ProgrammierInterfaceFunktionen ---------------------------------------------
STDMETHODIMP CClasses::get_isA (LONG *plRTTI)
{
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoClasses;
	return NOERROR;
}

STDMETHODIMP CClasses::get_Parent (IDispatch **ppIDisp)
{
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CClasses::get_Application (IDispatch **ppIDisp)
{
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CClasses::put_Parent (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CClasses::put_Application (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

// Liefert die Anzahl der Objektklassen ---------------------------------------
STDMETHODIMP CClasses::get_Count (long *plCount)
{
	if (NULL == plCount) return E_POINTER;

	*plCount = Count();
	return NOERROR;	
}

extern "C"
BOOL CALLBACK EnumIdentsForOKS (HPROJECT hPr, LPCSTR pcClass, UINT_PTR dwData)
{
	if (SUCCEEDED(IdentFromClassX (hPr, pcClass, reinterpret_cast<ULONG *>(dwData))))
		return FALSE;		// immer nur den ersten nehmen

	return TRUE;	// ansonsten weitermachen
}

// Liefert eine der enthaltenen Objektklassen, entweder über einen numerischen
// Index oder über den Kurztext der gesuchten Klasse
STDMETHODIMP CClasses::Item (VARIANT vt, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// versuchen, Parameter auszuwerten
CComVariant vArg;
HRESULT hr = vArg.ChangeType (VT_I4, &vt);	// Zahl als Index

	if (SUCCEEDED(hr)) {
		if (V_I4(&vArg) > 0 && ULONG(V_I4(&vArg)) <= Count()) 
		// Index ist gültig: liefern der gesuchten ObjektKlasse
			return GetClassDisp (V_I4(&vArg)-1, (LPVOID *)ppIDisp);

		return DISP_E_BADINDEX;
	} 

// 2. Versuch vt als String interpretieren (Name ?)
	hr = vArg.ChangeType (VT_BSTR, &vt);
	if (SUCCEEDED(hr)) {
	ULONG lIdent = INVALID_IDENT;
	string strClsName = AnsiString(V_BSTR(&vArg));

		VariantClear (&vArg);
		if (!strncmp(strClsName.c_str(), OKS_SCOPE_BEGIN, OKS_SCOPE_BEGIN_LEN)) {	
		// first char == '[' ? --> '[OKS]'
		HPROJECT hPrCtx = m_pDoc -> GetCtxDataSource();

			if (HACTCONNECTION == hPrCtx)
				hPrCtx = DEX_GetDataSourceHandle();

			ASSERT(HACTCONNECTION != hPrCtx);
			hr = IdentFromClassX (hPrCtx, strClsName.c_str()/*+OKS_SCOPE_BEGIN_LEN*/, &lIdent);
			if (FAILED(hr)) {
			// im aktuellen (Kontext-)Projekt nicht gefunden, also versuchen in allen anderen wiederzufinden
			// hierbei den ersten gefunden liefern
			ENUMTEXTKEY ETK;

				ETK.eKey = (LPSTR)strClsName.c_str();
				ETK.eFcn = (ENUMTEXTKEYPROC)EnumIdentsForOKS;
				ETK.ePtr = &lIdent;
				DEX_EnumClassProjects(ETK);

				if (INVALID_IDENT != lIdent)
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
			}
			return GetClassDispValue (lIdent, (LPVOID *)ppIDisp);
		}
	
	// Class name given
 		return GetClassDisp (strClsName.c_str(), (LPVOID *)ppIDisp);
	}

// 3. Versuch: evtl. ist Parameter nicht gegeben
	hr = vArg.ChangeType (VT_ERROR, &vt);
	if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) 
	// liefert sich selbst
		hr = ((_DGeoClass *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);

	return hr;
}


// Liefert neuen Enumerator für diese Collection ------------------------------
STDMETHODIMP CClasses::_NewEnum (IUnknown **ppIUnk)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == ppIUnk) return E_POINTER;

// neuen Enumerator anlegen
CEnumClasses *pClassArray = CEnumClasses::CreateInstance (m_pIdents -> m_pIdArray);

	if (NULL == pClassArray) return E_OUTOFMEMORY;

HRESULT hr = pClassArray -> QueryInterface (IID_IEnumVARIANT, (LPVOID *)ppIUnk);	

	pClassArray -> Release();
		
return hr;
}


STDMETHODIMP CClasses::Add(VARIANT vCls, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// versuchen, Parameter auszuwerten
VARIANTARG vArg; VariantInit (&vArg);
INITCLSSTATUS rgIOS = INITCLSSTATUS_Error;
HRESULT hr = VariantChangeType (&vArg, &vCls, 0, VT_I4);	// Class Ident 

	if (SUCCEEDED(hr)) {
	ULONG lIdent = (ULONG)V_I4(&vArg);
	long lIndex = m_pIdents -> m_pIdArray -> hasIdent (lIdent);
	
		if (lIndex == -1L) {
		CClassCreator ClCr (*(m_pIdents -> m_pIdArray));
		
			rgIOS = m_pICProc (m_pUnk, m_pApp, m_pDoc, ClCr, m_dwData, &lIdent);
			if (INITCLSSTATUS_Error == rgIOS) 
				return E_FAIL;
		} else 
			rgIOS = INITCLSSTATUS_Exists;

		if (INITCLSSTATUS_Created == rgIOS || INITCLSSTATUS_Exists == rgIOS)
			return GetClassDisp (lIndex, (LPVOID *)ppIDisp);

		return E_UNEXPECTED;
	}

	hr = VariantChangeType (&vArg, &vCls, 0, VT_BSTR);         // Class Name
	if (SUCCEEDED(hr)) {
	string strName = AnsiString(V_BSTR(&vArg));
	ULONG lIdent = m_pDoc -> GetIdentFromClsName (strName.c_str());
	long lIndex = (lIdent != INVALID_IDENT) ? m_pIdents -> m_pIdArray -> hasIdent (lIdent) : -1L;
	
		VariantClear (&vArg);
		if (lIndex == -1L) {
		CClassCreator ClCr (*(m_pIdents -> m_pIdArray));
		
			rgIOS = m_pICProc (m_pUnk, m_pApp, m_pDoc, ClCr, m_dwData, &lIdent);
			if (INITCLSSTATUS_Error == rgIOS) 
				return E_UNEXPECTED;
		} else 
			rgIOS = INITCLSSTATUS_Exists;
		
		if (INITCLSSTATUS_Created == rgIOS || INITCLSSTATUS_Exists == rgIOS) {
		// set Class Name, get IDispatch
			m_pDoc -> SetClassName (lIdent, strName.c_str());
			return GetClassDispValue (lIdent, (LPVOID *)ppIDisp);
		}
		return E_UNEXPECTED;
	}

return hr;
}

STDMETHODIMP CClasses::Remove (VARIANT vCls)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// versuchen, Parameter auszuwerten 
CComVariant vArg; 
HRESULT hr = vArg.ChangeType (VT_I4, &vCls);	// Class Ident 

	if (SUCCEEDED(hr)) {
	long lIdent = V_I4(&vArg);
	
		if (NULL != m_pDCProc && !(*m_pDCProc)(lIdent, m_pDoc, m_dwData))
			return E_FAIL;

		m_pIdents -> m_pIdArray -> DeleteClass (lIdent);
		return NOERROR;
	}
	
	hr = vArg.ChangeType (VT_BSTR, &vCls);      // Class Name
	if (SUCCEEDED(hr)) {
	long lIdent = m_pDoc -> GetIdentFromClsName (AnsiString(V_BSTR(&vArg)));

		if (NULL != m_pDCProc && !(*m_pDCProc)(lIdent, m_pDoc, m_dwData))
			return E_FAIL;

		m_pIdents -> m_pIdArray -> DeleteClass (lIdent);
	}
	return S_OK;
}

STDMETHODIMP CClasses::Refresh (void)
{
// wenn Informationen über Herkunft existieren, dann neu erzeugen, ansonsten
// tote Seelen beseitigen
	if (CanRegenerate())
		return Regenerate() ? NOERROR : E_OUTOFMEMORY;

	return m_pIdents -> m_pIdArray -> Refresh();
}

