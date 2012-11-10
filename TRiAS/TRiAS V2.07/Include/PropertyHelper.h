///////////////////////////////////////////////////////////////////////////////
// @doc
// @module PropertyHelper.h | HelperRoutinen für Properties

#if !defined(_PROPERTYHELPER_H__99F636F4_5C50_11D1_9717_00A024D6F582__INCLUDED_)
#define _PROPERTYHELPER_H__99F636F4_5C50_11D1_9717_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <atlbasex.h>

///////////////////////////////////////////////////////////////////////////////
// Einlesen einer Property
template<class T>
inline T GetProperty (ITRiASProperties *pIProps, LPCSTR pcKey, T vDefault)
{
ITRiASProperty *pIProp = NULL;
CComVariant vProp (pcKey);

	if (SUCCEEDED(pIProps -> Item (vProp, &pIProp))) {
	CComVariantEx vVal;

		if (SUCCEEDED(pIProp -> get_Value (&vVal)))
		{
			pIProp -> Release();
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
inline T GetProperty (ITRiASProperties *pIProps, ResID resID, T vDefault)
{
	return GetProperty (pIProps, ResString(resID, _MAX_PATH), vDefault);
}
#endif

#endif // !defined(_PROPERTYHELPER_H__99F636F4_5C50_11D1_9717_00A024D6F582__INCLUDED_)
