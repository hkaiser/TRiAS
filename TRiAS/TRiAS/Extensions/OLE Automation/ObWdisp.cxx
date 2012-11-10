// Collection vor Object Windows (ProgrammierInterface) -----------------
// File: OBWDISP.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "oleautor.h"

#include "obwarray.hxx"
#include "enumobws.hxx"
#include "objwins.hxx"

#include "objwin.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// ProgrammierInterfaceFunktionen ---------------------------------------------
// Das StandardProperty Parent liefert das ¸bergeordnete Object Window, ¸ber welches 
// diese Collection angelegt wurde.
STDMETHODIMP CGeoObjectWins::get_isA (LONG *plRTTI)
{
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoObjectWins;
	return NOERROR;
}

STDMETHODIMP CGeoObjectWins::get_Parent (IDispatch **ppIDisp)
{
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

// Dieses StandardProperty liefert das ApplicationInterface (das allen anderen
// Objekten ¸bergeordnete)
STDMETHODIMP CGeoObjectWins::get_Application (IDispatch **ppIDisp)
{
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoObjectWins::put_Parent (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGeoObjectWins::put_Application (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

// Liefert die Anzahl der Objects ---------------------------------
STDMETHODIMP CGeoObjectWins::get_Count (long *plCount)
{
	if (NULL == plCount) return E_POINTER;

	*plCount = Count();
	return NOERROR;
}


STDMETHODIMP CGeoObjectWins::Item (VARIANT vCode, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// 1. Zahl als Collection Index
CComVariant vArg;
HRESULT hr = VariantChangeType (&vArg, &vCode, 0, VT_I4);	 

	if (SUCCEEDED(hr)) {
		if (V_I4(&vArg) > 0 && ULONG(V_I4(&vArg)) <= Count()) 
		// Index ist g¸ltig: Dispatch-Interface abfragen
			return GetObjectWinDisp (V_I4(&vArg)-1, (LPVOID *)ppIDisp);

		return DISP_E_BADINDEX;
	}

// Versuch vt als String interpretieren (":hWnd", "Name")
	hr = VariantChangeType (&vArg, &vCode, 0, VT_BSTR);
	if (SUCCEEDED(hr)) {
	HWND hWnd = NULL;
	string strArg = AnsiString (V_BSTR(&vArg));

		if (':' == strArg[0]) {
		// 2. first char == ':' --> ":hWnd"
			hWnd = (HWND)strtoul (strArg.c_str()+1, NULL, 10); 
			return GetObjectWinDispValue (hWnd, (LPVOID *)ppIDisp);
		} 
	
	// 3. Object Window "Name"
		return GetObjectWinDisp (strArg.c_str(), (LPVOID *)ppIDisp);
	}

// Versuch: evtl. ist Parameter nicht gegeben
	hr = VariantChangeType (&vArg, &vCode, 0, VT_ERROR);
	if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) 
	// liefert sich selbst (Object Collection)
		hr = ((_DGeoObjectWins *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);

	return hr;
}


// Dieses StandardInterface liefert einen neuen Enumerator IEnumVARIANT mit
// allen Object Windows
// Dieses gelieferte Interface ist allerdings von VB aus schlecht verwendbar.
//
STDMETHODIMP CGeoObjectWins::_NewEnum (IUnknown **ppIUnk)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == ppIUnk) return E_POINTER;

// neuen Enumerator anlegen
CEnumGeoObjWins *pEGeoObjWins = CEnumGeoObjWins::CreateInstance (m_pEnumOWins -> m_pOWArray);

	if (NULL == pEGeoObjWins) return E_OUTOFMEMORY;
	
HRESULT hr = pEGeoObjWins -> QueryInterface (IID_IEnumVARIANT, (LPVOID *)ppIUnk);

	pEGeoObjWins -> Release();

return hr;
}

STDMETHODIMP CGeoObjectWins::Add (VARIANT vObjWin, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

CComVariant vArg;
INITOBJWINSTATUS rgIOS = INITOBJWINSTATUS_Error;

// 1. Object Window hWnd
HRESULT hr = VariantChangeType (&vArg, &vObjWin, 0, VT_I4); 

	if (SUCCEEDED(hr)) {
	HWND hWnd = (HWND)V_I4(&vArg);
	long lIndex = m_pEnumOWins -> m_pOWArray -> hasObjectWin (hWnd);
	
		if (lIndex == -1L) {
		CGeoObjectWinCreator ObCr (*(m_pEnumOWins -> m_pOWArray));
		
			rgIOS = m_pICProc (m_pUnk, m_pApp, m_pDoc, ObCr, m_dwData, &hWnd);
			if (rgIOS == INITOBJWINSTATUS_Error) 
				return E_FAIL;
		} else  
			rgIOS = INITOBJWINSTATUS_Exists;

		if (rgIOS == INITOBJWINSTATUS_Created || rgIOS == INITOBJWINSTATUS_Exists) 
			return GetObjectWinDisp (lIndex, (LPVOID *)ppIDisp);

		return E_UNEXPECTED;
	}

// 2. Object Window Name
	hr = VariantChangeType (&vArg, &vObjWin, 0, VT_BSTR);
	if (SUCCEEDED(hr)) { 
	string strName = AnsiString(V_BSTR(&vArg));
	HWND hWnd = m_pDoc -> GethWndFromObjWinName (strName.c_str());
	long lIndex = (hWnd != NULL) ? m_pEnumOWins -> m_pOWArray -> hasObjectWin (hWnd) : -1L;

		if (lIndex == -1L) {
		CGeoObjectWinCreator ObCr (*(m_pEnumOWins -> m_pOWArray));
		
			rgIOS = m_pICProc (m_pUnk, m_pApp, m_pDoc, ObCr, m_dwData, &hWnd);
			if (rgIOS == INITOBJWINSTATUS_Error) 
				return E_FAIL;
		} else  
			rgIOS = INITOBJWINSTATUS_Exists;
		
		if (rgIOS == INITOBJWINSTATUS_Created || rgIOS == INITOBJWINSTATUS_Exists) {
		// get IDispatch
			m_pDoc -> SetObjWinName (hWnd, strName.c_str());
			return GetObjectWinDispValue (hWnd, (LPVOID *)ppIDisp);
		}
		return E_UNEXPECTED;
	}

return hr;
}


STDMETHODIMP CGeoObjectWins::Remove(VARIANT vObjWin)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// 1. Object Window hWnd
CComVariant vArg;
HRESULT hr = vArg.ChangeType (VT_I4, &vObjWin);

	if (SUCCEEDED(hr)) {
	HWND hWnd = (HWND)V_I4(&vArg);
	
		if (NULL != m_pDCProc && !(*m_pDCProc)(hWnd, m_pDoc))
			return E_FAIL;

		m_pEnumOWins -> m_pOWArray -> DeleteObjectWin (hWnd);
		return NOERROR;
	}
	

// 2. Object Window Name
	hr = vArg.ChangeType (VT_BSTR, &vObjWin);
	if (SUCCEEDED(hr)) {
	HWND hWnd = m_pDoc -> GethWndFromObjWinName (AnsiString(V_BSTR(&vArg)));
										  
		if (NULL != m_pDCProc && !(*m_pDCProc)(hWnd, m_pDoc))
			return E_FAIL;

		m_pEnumOWins -> m_pOWArray -> DeleteObjectWin (hWnd);
		return NOERROR;
	}
	return hr;
}

STDMETHODIMP CGeoObjectWins::Refresh (void)
{
// wenn Informationen ¸ber Herkunft existieren, dann neu erzeugen, ansonsten
// tote Seelen beseitigen
	if (CanRegenerate()) 
		return Regenerate() ? NOERROR : E_OUTOFMEMORY;

	return m_pEnumOWins -> m_pOWArray -> Refresh();
}

STDMETHODIMP CGeoObjectWins::get_ActGeoObjectWin (DGeoObjectWin **ppIWin)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

HWND hWnd = DEX_GetActiveORWnd();

	TX_ASSERT(NULL == hWnd || DEX_IsORWindow(hWnd));
	
	if (NULL == hWnd) return E_UNEXPECTED;		// kein ORFenster vorhanden

long lIndex = m_pEnumOWins -> m_pOWArray -> hasObjectWin (hWnd);
INITOBJWINSTATUS rgIOS = INITOBJWINSTATUS_Error;
	
	if (-1L != lIndex)	// Fenster muﬂ existieren
		return GetObjectWinDisp (lIndex, (LPVOID *)ppIWin);

	return E_UNEXPECTED;
}
 
