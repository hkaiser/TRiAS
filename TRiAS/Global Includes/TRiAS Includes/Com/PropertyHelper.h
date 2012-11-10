///////////////////////////////////////////////////////////////////////////////
// @doc
// @module PropertyHelper.h | HelperRoutinen für Properties

#if !defined(_PROPERTYHELPER_H__99F636F4_5C50_11D1_9717_00A024D6F582__INCLUDED_)
#define _PROPERTYHELPER_H__99F636F4_5C50_11D1_9717_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Atl/atlbasex.h>
#include <com/VariantHelpers.h>		// V_ISDISPATCH etc. 

///////////////////////////////////////////////////////////////////////////////
// LocaleID für English
#define LOCALE_ENGLISH \
	(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT))
#define LOCALE_GERMAN \
	(MAKELCID(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN), SORT_DEFAULT))

///////////////////////////////////////////////////////////////////////////////
// Besorgen einer Properties-Collection
inline
HRESULT GetProperties (IDispatch *pIDisp, ITRiASProperties **ppIProps)
{
	if (NULL == pIDisp || NULL == ppIProps) 
		return E_POINTER;

CComPtr<ITRiASPropertyBase> pIBase;

	if (SUCCEEDED(pIDisp -> QueryInterface (IID_ITRiASPropertyBase, (LPVOID *)&pIBase)))
		return pIBase -> get_Properties (ppIProps);
	
	return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
// Einlesen einer Property
template<class T, class S>
inline T GetProperty (ITRiASProperties *pIProps, S pcKey, T vDefault, LCID lcid = LOCALE_NEUTRAL)
{
CComPtr<ITRiASProperty> pIProp;

	if (SUCCEEDED(pIProps -> Item (CComVariant(pcKey), &pIProp))) {
	CComVariantEx vVal (lcid);

		if (SUCCEEDED(pIProp -> get_Value (&vVal)))
		{
			try {
				return T(vVal);
			} catch (_com_error &) {
				;	// TypeMismatch
			}
		}
	}
	return vDefault;
}

#if defined(__CV__)
template<class T>
inline T GetPropertyResID (ITRiASProperties *pIProps, ResID resID, T vDefault, LCID lcid = LOCALE_NEUTRAL)
{
	return GetProperty (pIProps, ResString(resID, _MAX_PATH), vDefault, lcid);
}
#endif

template<class T, class S>
inline T GetPropertyFrom (ITRiASPropertyBase *pIBase, S pcKey, T vDefault, LCID lcid = LOCALE_NEUTRAL)
{
CComPtr<ITRiASProperties> pIProps;

	if (SUCCEEDED(pIBase -> get_Properties (&pIProps)))
		return GetProperty (pIProps, pcKey, vDefault, lcid);
	return vDefault;
}

template<class T, class S>
inline T GetPropertyFrom (IDispatch *pIBase, S pcKey, T vDefault, LCID lcid = LOCALE_NEUTRAL)
{
CComPtr<ITRiASProperties> pIProps;

	if (SUCCEEDED(GetProperties (pIBase, &pIProps)))
		return GetProperty (pIProps, pcKey, vDefault, lcid);
	return vDefault;
}

///////////////////////////////////////////////////////////////////////////////
// Setzen einer Property
template<class T, class S>
inline HRESULT SetPropertyBy (ITRiASPropertyBase *pIBase, S pcKey, T vValue, bool bCreateProperty = false, LCID lcid = LOCALE_NEUTRAL)
{
	_ASSERTE(NULL != pIBase);

CComPtr<ITRiASProperties> pIProps;
HRESULT hr = pIBase -> get_Properties (&pIProps);

	if (SUCCEEDED(hr))
		hr = SetProperty(pIProps, pcKey, vValue, bCreateProperty, lcid);
	return hr;
}

template<class T, class S>
inline HRESULT SetPropertyBy (IDispatch *pIBase, S pcKey, T vValue, bool bCreateProperty = false, LCID lcid = LOCALE_NEUTRAL)
{
	_ASSERTE(NULL != pIBase);

CComPtr<ITRiASProperties> pIProps;
HRESULT hr = GetProperties (pIBase, &pIProps);

	if (SUCCEEDED(hr))
		hr = SetProperty(pIProps, pcKey, vValue, bCreateProperty, lcid);
	return hr;
}

template<class T, class S>
inline HRESULT SetProperty (
	ITRiASProperties *pIProps, S pcKey, T vNewValue, bool fCreate = false, LCID lcid = LOCALE_NEUTRAL)
{
CComPtr<ITRiASProperty> pIProp;
CComVariant vKey (pcKey);
HRESULT hr = pIProps -> Item (vKey, &pIProp);

	if (FAILED(hr) && fCreate)		// evtl. neu erzeugen
		hr = pIProps -> Add (vKey, &pIProp);

	if (SUCCEEDED(hr)) {			// Wert setzen
	CComVariantEx vVal(vNewValue, lcid);

		if( !V_ISUNKNOWN(&vVal) && !V_ISDISPATCH(&vVal) ) {
			hr = vVal.ChangeTypeEx(VT_BSTR);
			_ASSERTE( SUCCEEDED(hr) );
		}
		hr = pIProp -> put_Value (vVal);
	} 
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Setzen einer Property mit Typ
template<class T, class S>
inline HRESULT SetPropertyAndTypeBy (
	ITRiASPropertyBase *pIBase, S pcKey, T vValue, PROPERTY_TYPE rgType, bool bCreateProperty = false, LCID lcid = LOCALE_NEUTRAL)
{
	_ASSERTE(NULL != pIBase);

CComPtr<ITRiASProperties> pIProps;
HRESULT hr = pIBase -> get_Properties (&pIProps);

	if (SUCCEEDED(hr))
		hr = SetPropertyAndType(pIProps, pcKey, vValue, rgType, bCreateProperty, lcid);
	return hr;
}

template<class T, class S>
inline HRESULT SetPropertyAndType (
	ITRiASProperties *pIProps, S pcKey, T vNewValue, PROPERTY_TYPE rgType, bool fCreate = false, LCID lcid = LOCALE_NEUTRAL)
{
CComPtr<ITRiASProperty> pIProp;
CComVariant vKey (pcKey);
HRESULT hr = pIProps -> Item (vKey, &pIProp);

	if (FAILED(hr) && fCreate)		// evtl. neu erzeugen
		hr = pIProps -> Add (vKey, &pIProp);

	if (SUCCEEDED(hr)) {			// Wert setzen
	CComVariantEx vVal(vNewValue, lcid);

		if( !V_ISUNKNOWN(&vVal) && !V_ISDISPATCH(&vVal) ) {
			hr = vVal.ChangeTypeEx(VT_BSTR);
			_ASSERTE( SUCCEEDED(hr) );
		}
		hr = pIProp -> SetValueAndType (vVal, rgType);
	} 
	return hr;
}

#if defined(__CV__)
template<class T>
inline HRESULT SetPropertyResID (ITRiASProperties *pIProps, ResID resID, T vNewValue, bool fCreate = false, LCID lcid = LOCALE_NEUTRAL)
{
	return SetProperty (pIProps, ResString(resID, _MAX_PATH), vNewValue, fCreate, lcid);
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Löschen einer Property
template<class S>
inline HRESULT DelPropertyBy (IDispatch *pIBase, S pcKey)
{
CComPtr<ITRiASProperties> pIProps;
HRESULT hr = GetProperties (pIBase, &pIProps);

	if (SUCCEEDED(hr))
		return pIProps -> Remove (CComVariant(pcKey));
	return hr;
}

template<class S>
inline HRESULT DelPropertyBy (ITRiASPropertyBase *pIBase, S pcKey)
{
CComPtr<ITRiASProperties> pIProps;
HRESULT hr = pIBase -> get_Properties (&pIProps);

	if (SUCCEEDED(hr))
		return pIProps -> Remove (CComVariant(pcKey));
	return hr;
}

template<class S>
inline HRESULT DelProperty (ITRiASProperties *pIProps, S pcKey)
{
	return pIProps -> Remove (CComVariant(pcKey));
}

#if defined(__CV__)
inline HRESULT DelProperty (ITRiASProperties *pIProps, ResID resID)
{
	return DelProperty (pIProps, ResString(resID, _MAX_PATH));
}
#endif

#endif // !defined(_PROPERTYHELPER_H__99F636F4_5C50_11D1_9717_00A024D6F582__INCLUDED_)
