// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "precomp.hxx"
#include "ObjectProperty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineSmartInterface2(DGeoObject, IID_DGeoObject);

/////////////////////////////////////////////////////////////////////////////
// Initialisierung
COleObjectProperty::COleObjectProperty (void)
{
	for (int i = 0; i < _countof(s_pcoleObjPropNames); i++) 
		m_dwDispId[i] = DISPID_UNKNOWN;
	m_lcid = GetUserDefaultLCID();
	m_pDoc = NULL;
}

COleObjectProperty::~COleObjectProperty (void)
{
	if (NULL != m_pDoc) 
		((_DDocument *)m_pDoc) -> Release();
	m_pDoc = NULL;
}

HRESULT COleObjectProperty::InitDocumentDispatch (void)
{
	if (NULL != m_pDoc)
		return S_OK;

char cbBuffer[_MAX_PATH];

	if (NULL != DEX_GetActiveProject(cbBuffer)) {
	CGeoDoc *pDoc = ((OLE2AutoExtension *)g_pTE) -> App() -> FFindDoc (cbBuffer);

		if (NULL == pDoc) return E_UNEXPECTED;

		m_pDoc = pDoc;
		((_DDocument *)m_pDoc) -> AddRef();
	}
	return S_OK;
}

// Funktion entscheidet, ob IObjectProperty2 verfügbar ist oder nicht
HRESULT WINAPI COleObjectProperty::_Choice (void *pv, REFIID iid, void** ppvObject, DWORD dw)
{
COleObjectProperty *pThis = (COleObjectProperty *)pv;

	if (DISPID_UNKNOWN == pThis->m_dwDispId[DISPID_SET] && 
		DISPID_UNKNOWN == pThis->m_dwDispId[DISPID_SETPROPERTY])
		return E_NOINTERFACE;		// 'Set' ist nicht verfügbar

// ansonsten normales QI
IUnknown* pUnk = (IUnknown*)((int)pThis+dw);

	pUnk->AddRef();
	*ppvObject = pUnk;
	return S_OK;
}

HRESULT COleObjectProperty::FInit (IDispatch *pIDisp)
{
	if (NULL == pIDisp) return E_POINTER;

	pIDisp -> AddRef();
	AttachDispatch(pIDisp);

	for (int i = 0; i < _countof(s_pcoleObjPropNames); i++) {
	HRESULT hr = pIDisp -> GetIDsOfNames (IID_NULL, (LPOLESTR *)&s_pcoleObjPropNames[i], 1, m_lcid, &m_dwDispId[i]);
		
		if (FAILED(hr)) {
			if (hr != DISP_E_UNKNOWNNAME)
				return hr;

		// solange dual interfaces nicht unterstützt werden hier nach
		// den alternativen Namen von VB5 fragen
			hr = pIDisp -> GetIDsOfNames (IID_NULL, (LPOLESTR *)&s_pcoleAltObjPropNames[i], 1, m_lcid, &m_dwDispId[i]);
			if (FAILED(hr) && hr != DISP_E_UNKNOWNNAME)
				return hr;
		}
	}

// GetPropertyNamemuß implementiert sein, sonst geht nichts
	if (DISPID_UNKNOWN == m_dwDispId[DISPID_GETPROPERTYNAME])
		return DISP_E_UNKNOWNNAME;

	return InitDocumentDispatch();
}

/////////////////////////////////////////////////////////////////////////////
// COleObjectProperty operations
STDMETHODIMP COleObjectProperty::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
HRESULT result = S_OK;

	TRY {
	CComVariant vResult;
	CString str;

		InvokeHelper(m_dwDispId[DISPID_GETCUMULATION], DISPATCH_PROPERTYGET, 
					 VT_VARIANT, (void *)&vResult, NULL);

		if (NULL != pBuffer && ulLen > 0) {
		CComVariant vString;
		BSTR *pResult = NULL;

			USES_CONVERSION;

			if (VT_BSTR == V_VT(&vResult)) 
				pResult = &V_BSTR(&vResult);
			else {
			HRESULT hr = VariantChangeType (&vString, &vResult, 0, VT_BSTR);

				if (FAILED(hr)) return hr;
				pResult = &V_BSTR(&vString);
			}
			ASSERT(NULL != pResult);
			if (NULL == pResult)
				return E_INVALIDARG;

		ULONG ulT = min (ulLen-1, (ULONG)SysStringLen(*pResult));

			strncpy (pBuffer, OLE2A(*pResult), ulT);
			pBuffer[ulT] = '\0';

			if (NULL != pulWritten)
				*pulWritten = ulT;
		} else
			result = E_INVALIDARG;

	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

STDMETHODIMP_(ULONG) COleObjectProperty::Count (void)
{
HRESULT result = S_OK;
long lCnt = 0;

	TRY {
		InvokeHelper(m_dwDispId[DISPID_GETCOUNT], DISPATCH_PROPERTYGET, 
					 VT_I4, (void*)&lCnt, NULL);
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return (S_OK == result) ? lCnt : -1;
}

STDMETHODIMP COleObjectProperty::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
HRESULT result = S_OK;

	TRY {
	CString str;

	// get_PropertyName
		if (NULL != pBuffer && wLen > 0) {
			InvokeHelper(m_dwDispId[DISPID_GETPROPERTYNAME], DISPATCH_PROPERTYGET, 
						 VT_BSTR, (void *)&str, NULL);

		ULONG ulT = min ((ULONG)wLen-1, (ULONG)str.GetLength());

			strncpy (pBuffer, str, ulT);
			pBuffer[ulT] = '\0';
		}
			
	} CATCH (COleException, e) {
		return e -> m_sc;
	} CATCH (COleDispatchException, e) {
		return e -> m_scError;
	} END_CATCH;

	TRY {
	long lFlags = 0;

	// get_PropertyFlags
		if (NULL != pdwFlags) {
			InvokeHelper(m_dwDispId[DISPID_GETPROPERTYFLAGS], DISPATCH_PROPERTYGET, 
						 VT_I4, (void *)&lFlags, NULL);
			*pdwFlags = DWORD(lFlags);
		}

	} CATCH (COleException, e) {
		*pdwFlags = DWORD(PROPERTYCAPS_NONE);
		if (DISPID_UNKNOWN != m_dwDispId[DISPID_SET] ||
			DISPID_UNKNOWN != m_dwDispId[DISPID_SETPROPERTY])
		{
			*pdwFlags |= DWORD(PROPERTYCAPS_NOTREADONLY);
		}
	} CATCH (COleDispatchException, e) {
		*pdwFlags = DWORD(PROPERTYCAPS_NONE);
		if (DISPID_UNKNOWN != m_dwDispId[DISPID_SET] ||
			DISPID_UNKNOWN != m_dwDispId[DISPID_SETPROPERTY])
		{
			*pdwFlags |= DWORD(PROPERTYCAPS_NOTREADONLY);
		}
	} END_CATCH;

	return S_OK;
}

STDMETHODIMP COleObjectProperty::HelpInfo (
	LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
HRESULT result = S_OK;
static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT;

	TRY {
	CString str;
	CComVariant vHelpFile;
	CComVariant vHelpCtx;

		InvokeHelper(m_dwDispId[DISPID_HELPINFO], DISPATCH_METHOD, 
					 VT_BSTR, (void*)&str, parms, &vHelpFile, &vHelpCtx);
		if (NULL != pBuffer && ulLen > 0) {
		ULONG ulT = min (ulLen-1, (ULONG)str.GetLength());

			strncpy (pBuffer, str, ulT);
			pBuffer[ulT] = '\0';
		}
		if (NULL != pHelpFile && VT_BSTR == vHelpFile.vt) {
			USES_CONVERSION;
			strcpy (pHelpFile, OLE2A(V_BSTR(&vHelpFile)));
		}
		if (NULL != pulHelpCtx && VT_I4 == vHelpCtx.vt) 
			*pulHelpCtx = V_I4(&vHelpCtx);

	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

STDMETHODIMP COleObjectProperty::Reset (void)
{
HRESULT result = S_OK;

	TRY {
		InvokeHelper(m_dwDispId[DISPID_RESET], DISPATCH_METHOD, 
					 VT_EMPTY, NULL, NULL);
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

STDMETHODIMP COleObjectProperty::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
HRESULT result = S_OK;

	TRY {
	CComVariant vResult;

		if (DISPID_UNKNOWN != m_dwDispId[DISPID_GETPROPERTY]) {	// hat den Vorrang
		static BYTE parms[] = VTS_DISPATCH;

			try {
			WDGeoObject Obj;

				THROW_FAILED_HRESULT(InitDocumentDispatch());
				THROW_FAILED_HRESULT(m_pDoc -> FGetGeoObject (lONr, Obj.ppi()));

				InvokeHelper(m_dwDispId[DISPID_GETPROPERTY], DISPATCH_METHOD, 
							 VT_VARIANT, (void*)&vResult, parms, Obj);
				return ConvertResultString (vResult, pBuffer, ulLen, pulWritten);

			} catch (_com_error&) {
				;
			}
		} 

	// wenn was schief geht mit alter Funktion versuchen	
	static BYTE parms_old[] = VTS_I4;

		InvokeHelper(m_dwDispId[DISPID_EVAL], DISPATCH_METHOD, 
					 VT_VARIANT, (void *)&vResult, parms_old, lONr);
		result = ConvertResultString (vResult, pBuffer, ulLen, pulWritten);

	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

HRESULT COleObjectProperty::ConvertResultString (CComVariant &vResult, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (VT_EMPTY == V_VT(&vResult) || VT_NULL == V_VT(&vResult))
		return E_FAIL;		// nicht existent für dieses Objekt

	if ((VT_DISPATCH == V_VT(&vResult) && NULL == V_DISPATCH(&vResult)) || 
		(VT_UNKNOWN == V_VT(&vResult) && NULL == V_UNKNOWN(&vResult)))
	{
		return E_FAIL;		// nicht existent für dieses Objekt
	}

HRESULT result = S_OK;

	if (NULL != pBuffer && ulLen > 0) {
	CComVariant vString;
	BSTR *pResult = NULL;

		USES_CONVERSION;

		if (VT_BSTR == V_VT(&vResult)) 
			pResult = &V_BSTR(&vResult);
		else {
		HRESULT hr = VariantChangeType (&vString, &vResult, 0, VT_BSTR);

			if (FAILED(hr)) return hr;
			pResult = &V_BSTR(&vString);
		}
		
		ASSERT(NULL != pResult);
		if (NULL == pResult) return E_INVALIDARG;

	ULONG ulT = min (ulLen-1, (ULONG)SysStringLen(*pResult));

		strncpy (pBuffer, OLE2A(*pResult), ulT);
		pBuffer[ulT] = '\0';

		if (NULL != pulWritten)
			*pulWritten = ulT;
	} 

	return result;
}

STDMETHODIMP COleObjectProperty::Set (LONG lONr, LPCSTR pcBuffer) 
{
HRESULT result = S_OK;

	ASSERT(DISPID_UNKNOWN != m_dwDispId[DISPID_SET] || 
		   DISPID_UNKNOWN != m_dwDispId[DISPID_SETPROPERTY]);

	TRY {
	CComVariant vValue (pcBuffer);

		if (DISPID_UNKNOWN != m_dwDispId[DISPID_SETPROPERTY]) {	// hat den Vorrang
		static BYTE parms[] = VTS_DISPATCH VTS_VARIANT;

			try {
			WDGeoObject Obj;

				THROW_FAILED_HRESULT(InitDocumentDispatch());
				THROW_FAILED_HRESULT(m_pDoc -> FGetGeoObject (lONr, Obj.ppi()));

				InvokeHelper(m_dwDispId[DISPID_SETPROPERTY], DISPATCH_METHOD, 
							 VT_EMPTY, NULL, parms, Obj, &vValue);
				return S_OK;

			} catch (_com_error&) {
				;
			}
		} 

	// wenn was schief geht mit alter Funktion versuchen	
	static BYTE parms_old[] = VTS_I4 VTS_VARIANT;

		InvokeHelper(m_dwDispId[DISPID_SET], DISPATCH_METHOD, 
					 VT_EMPTY, NULL, parms_old, lONr, &vValue);

	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
// Serverseitige Initialisierung
HRESULT COleObjectProperty::Init (_DApplication *pIApp, BOOL *pfSuccess)
{
	if (NULL == pfSuccess) return E_POINTER;
	*pfSuccess = true;

HRESULT result = S_OK;
static BYTE parms[] = VTS_DISPATCH;

	TRY {
		InvokeHelper(m_dwDispId[DISPID_INIT], DISPATCH_METHOD, VT_BOOL, 
					 (void*)pfSuccess, parms, pIApp);

	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

