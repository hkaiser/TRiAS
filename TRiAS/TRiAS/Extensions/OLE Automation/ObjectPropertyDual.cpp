// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "precomp.hxx"

#include <Com/ComBool.h>

#include "ObjectPropertyDual.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineSmartInterface(EnumObjectsByNumber);
DefineSmartInterface(QueryEnumLONG);
DefineSmartInterface(EnumLONG);

DefineSmartInterface2(DGeoObject, IID_DGeoObject);
DefineSmartInterface2(DGeoObjects, IID_DGeoObjects);
DefineSmartInterface2(DWriteAbleObjectProperty, IID_DWriteAbleObjectProperty);
DefineSmartInterface2(DSearchAbleObjectProperty, IID_DSearchAbleObjectProperty);

/////////////////////////////////////////////////////////////////////////////
// Initialisierung
COleObjectPropertyDual::COleObjectPropertyDual (void)
{
	m_pDoc = NULL;
	m_fWriteAble = false;
	m_fSearchAble = false;
}

COleObjectPropertyDual::~COleObjectPropertyDual (void)
{
	if (NULL != m_pDoc) 
		((_DDocument *)m_pDoc) -> Release();
	m_pDoc = NULL;
}

HRESULT COleObjectPropertyDual::InitDocumentDispatch (void)
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
HRESULT WINAPI COleObjectPropertyDual::_ChoiceWritable (void *pv, REFIID iid, 
	void** ppvObject, DWORD dw)
{
COleObjectPropertyDual *pThis = (COleObjectPropertyDual *)pv;

	if (!pThis->m_fWriteAble)
		return E_NOINTERFACE;		// 'Set' ist nicht verfügbar

// ansonsten normales QI
IUnknown* pUnk = (IUnknown*)((int)pThis+dw);

	pUnk->AddRef();
	*ppvObject = pUnk;
	return S_OK;
}

// Funktion entscheidet, ob DSearchObjects verfügbar ist oder nicht
HRESULT WINAPI COleObjectPropertyDual::_ChoiceSearchable (void *pv, REFIID iid, 
	void** ppvObject, DWORD dw)
{
COleObjectPropertyDual *pThis = (COleObjectPropertyDual *)pv;

	if (!pThis->m_fSearchAble)
		return E_NOINTERFACE;		// 'ConsiderSearch' et. al. ist nicht verfügbar

// ansonsten normales QI
IUnknown* pUnk = (IUnknown*)((int)pThis+dw);

	pUnk->AddRef();
	*ppvObject = pUnk;
	return S_OK;
}

HRESULT COleObjectPropertyDual::FInit (DObjectProperty *pIObjProp)
{
	if (NULL == pIObjProp) return E_POINTER;
	try {
		m_ObjProp = pIObjProp;	// throws hr

	PROPERTYCAPS rgFlags = PROPERTYCAPS_NONE;

		THROW_FAILED_HRESULT(m_ObjProp -> get_PropertyFlags(&rgFlags));

	WDWriteAbleObjectProperty ObjPropEx;
	
		if (SUCCEEDED(m_ObjProp->QueryInterface(ObjPropEx.ppi())) &&
			rgFlags & PROPERTYCAPS_NOTREADONLY)
		{
			m_fWriteAble = true;	// DWriteAbleObjectProperty wird unterstützt
		}

	WDSearchAbleObjectProperty ObjPropSrch;

		if (SUCCEEDED(m_ObjProp->QueryInterface(ObjPropSrch.ppi())) &&
			rgFlags & PROPERTYCAPS_SEARCHABLE)
		{
			m_fSearchAble = true;	// DSearchAbleObjectProperty wird unterstützt
		}

	} catch (_com_error& hr) {
		m_fWriteAble = false;
		m_fSearchAble = false;
		return _COM_ERROR(hr);
	}
	return InitDocumentDispatch();
}

/////////////////////////////////////////////////////////////////////////////
// COleObjectPropertyDual operations
STDMETHODIMP COleObjectPropertyDual::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
HRESULT result = S_OK;

	try {
	CComVariant vResult;

		THROW_FAILED_HRESULT(m_ObjProp -> get_Cumulation (&vResult));

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

	} catch (_com_error& hr) {
		result = _COM_ERROR(hr);
	} 

	return result;
}

STDMETHODIMP_(ULONG) COleObjectPropertyDual::Count (void)
{
long lCnt = 0;
HRESULT result = m_ObjProp -> get_Count (&lCnt);

	return (S_OK == result) ? lCnt : -1;
}

STDMETHODIMP COleObjectPropertyDual::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
HRESULT result = S_OK;

	try {
	// get_PropertyName
		if (NULL != pBuffer && wLen > 0) {
		CComBSTR bstrName;

			THROW_FAILED_HRESULT(m_ObjProp -> get_PropertyName(CLEARED(&bstrName)));

		ULONG ulT = min ((ULONG)wLen-1, (ULONG)SysStringLen(bstrName));

			USES_CONVERSION;
			strncpy (pBuffer, OLE2A(bstrName), ulT);
			pBuffer[ulT] = '\0';
		}
			
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	} 

	try {
	PROPERTYCAPS lFlags = PROPERTYCAPS_NONE;

	// get_PropertyFlags
		if (NULL != pdwFlags) {
			THROW_FAILED_HRESULT(m_ObjProp -> get_PropertyFlags(&lFlags));
			
			if (m_fWriteAble)
				lFlags = PROPERTYCAPS(lFlags | PROPERTYCAPS_NOTREADONLY);
			else
				lFlags = PROPERTYCAPS(lFlags & ~PROPERTYCAPS_NOTREADONLY);
			
			if (m_fSearchAble)
				lFlags = PROPERTYCAPS(lFlags | PROPERTYCAPS_SEARCHABLE);
			else
				lFlags = PROPERTYCAPS(lFlags & ~PROPERTYCAPS_SEARCHABLE);

			*pdwFlags = DWORD(lFlags);
		}
			
	} catch (_com_error&) {
		*pdwFlags = DWORD(PROPERTYCAPS_NONE);
		if (m_fWriteAble)
			*pdwFlags |= DWORD(PROPERTYCAPS_NOTREADONLY);
		if (m_fSearchAble)
			*pdwFlags |= DWORD(PROPERTYCAPS_SEARCHABLE);
	} 

	return S_OK;
}

STDMETHODIMP COleObjectPropertyDual::HelpInfo (
	LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
HRESULT result = S_OK;

	try {
	CComBSTR bstrInfo;
	CComVariant vHelpFile;
	CComVariant vHelpCtx;

		THROW_FAILED_HRESULT(m_ObjProp -> HelpInfo(&vHelpFile, &vHelpCtx, CLEARED(&bstrInfo)));

		USES_CONVERSION;
		if (NULL != pBuffer && ulLen > 0) {
		ULONG ulT = min (ulLen-1, (ULONG)SysStringLen(bstrInfo));

			strncpy (pBuffer, OLE2A(bstrInfo), ulT);
			pBuffer[ulT] = '\0';
		}
		if (NULL != pHelpFile && VT_BSTR == vHelpFile.vt) 
			strcpy (pHelpFile, OLE2A(V_BSTR(&vHelpFile)));

		if (NULL != pulHelpCtx && VT_I4 == vHelpCtx.vt) 
			*pulHelpCtx = V_I4(&vHelpCtx);

	} catch (_com_error& hr) {
		result = _COM_ERROR(hr);
	}

	return result;
}

STDMETHODIMP COleObjectPropertyDual::Reset (void)
{
	return m_ObjProp -> Reset();
}

STDMETHODIMP COleObjectPropertyDual::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
HRESULT result = S_OK;

	try {
	CComVariant vResult;
	WDGeoObject Obj;

		THROW_FAILED_HRESULT(InitDocumentDispatch());
		THROW_FAILED_HRESULT(m_pDoc -> FGetGeoObject (lONr, Obj.ppi()));
		THROW_FAILED_HRESULT(m_ObjProp -> GetProperty(Obj, &vResult));

		result = ConvertResultString (vResult, pBuffer, ulLen, pulWritten);

	} catch (_com_error& hr) {
		result = _COM_ERROR(hr);
	}

	return result;
}

HRESULT COleObjectPropertyDual::ConvertResultString (CComVariant &vResult, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
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

STDMETHODIMP COleObjectPropertyDual::Set (LONG lONr, LPCSTR pcBuffer) 
{
HRESULT result = S_OK;

	ASSERT(m_fWriteAble);	// muß beschreibbar sein
	
	try {
	CComVariant vValue (pcBuffer);
	WDGeoObject Obj;
	WDWriteAbleObjectProperty ObjPropEx(m_ObjProp);	// throws hr

		THROW_FAILED_HRESULT(InitDocumentDispatch());
		THROW_FAILED_HRESULT(m_pDoc -> FGetGeoObject (lONr, Obj.ppi()));
		THROW_FAILED_HRESULT(ObjPropEx -> SetProperty (Obj, vValue));

	} catch (_com_error& hr) {
		result = _COM_ERROR(hr);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////
// Serverseitige Initialisierung
HRESULT COleObjectPropertyDual::Init (DApplication *pIApp, BOOL *pfSuccess)
{
	if (NULL == pfSuccess) return E_POINTER;
	*pfSuccess = true;

HRESULT result = S_OK;
VARIANT_BOOL fSuccess = false;

	try {
		THROW_FAILED_HRESULT(m_ObjProp -> Init (pIApp, &fSuccess));
		*pfSuccess = fSuccess ? TRUE : FALSE;

	} catch (_com_error& hr) {
		result = _COM_ERROR(hr);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////
// DSearchObjects
VARIANT GetSearchMode (SEARCHMODE rgMode)
{
FEATURESEARCHMODE rgResult = FEATURESEARCHMODE_ExactMatch;
SEARCHMODE rgQualifier = SEARCHMODE(rgMode & SEARCHMODE_SEARCHMODIFIERS);

	switch (rgMode & ~SEARCHMODE_SEARCHMODIFIERS) {
	case SEARCHMODE_NORMAL:
		if (rgQualifier & SEARCHMODE_PARTIALMATCH) {
			if (rgQualifier & SEARCHMODE_PARTIALMATCHBOB)
				rgResult = FEATURESEARCHMODE_SubStringStartMatch;
			else
				rgResult = FEATURESEARCHMODE_SubStringMatch; 
		}
		break;

	case SEARCHMODE_REGEXPR:
		if (rgQualifier & SEARCHMODE_PARTIALMATCH)
			rgResult = FEATURESEARCHMODE_SubRegularExpression;
		else
			rgResult = FEATURESEARCHMODE_RegularExpression;
		break;

	case SEARCHMODE_LIKE:
		rgResult = FEATURESEARCHMODE_InexactMatch;
		break;

	case SEARCHMODE_ONLYEXISTANCE:
		rgResult = FEATURESEARCHMODE_ExistanceOnly;
		break;

	default:
		_ASSERTE(FALSE);
		return CComVariant(FEATURESEARCHMODE_ExactMatch, VT_I4);
	}

	if (rgQualifier & SEARCHMODE_NOMATCHCASE)
		rgResult = FEATURESEARCHMODE(rgResult | FEATURESEARCHQUALIFIER_IgnoreCase);
	if (rgQualifier & SEARCHMODE_NEGATERESULT)
		rgResult = FEATURESEARCHMODE(rgResult | FEATURESEARCHQUALIFIER_NegateResult);

	return CComVariant(rgResult, VT_I4);
}

STDMETHODIMP COleObjectPropertyDual::ConsiderSearch(BSTR bstrToMatch, 
	SEARCHMODE rgFlags, ULONG ulCnt)
{
CComBool fCanSearch;

	_ASSERTE(m_fSearchAble);	// muß suchen können

	COM_TRY {
	WDSearchAbleObjectProperty Search(m_ObjProp);

		THROW_FAILED_HRESULT(Search -> ConsiderSearch(bstrToMatch, 
			GetSearchMode(rgFlags), &fCanSearch));

	} COM_CATCH;
	return fCanSearch ? S_OK : E_NOTIMPL;
}

STDMETHODIMP COleObjectPropertyDual::SearchObjects(BSTR bstrToMatch, 
	SEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj)
{
	if (NULL == ppvObj)
		return E_POINTER;
	*ppvObj = NULL;

	_ASSERTE(m_fSearchAble);	// muß suchen können
	
	COM_TRY {
	WDSearchAbleObjectProperty Search(m_ObjProp);
	WDGeoObjects Objs;

		THROW_FAILED_HRESULT(Search -> SearchObjects(bstrToMatch, 
			GetSearchMode(rgFlags), Objs.ppi()));

	WQueryEnumLONG QueryEnum(Objs);
	WEnumLONG Enum;

		THROW_FAILED_HRESULT(QueryEnum -> QueryEnumLONG (Enum.ppi()));

	WEnumObjectsByNumber EnumObjs(Enum);

		*ppvObj = EnumObjs.detach();

	} COM_CATCH;
	return S_OK;
}
