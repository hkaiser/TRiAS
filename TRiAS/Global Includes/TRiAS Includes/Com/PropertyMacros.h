// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/18/1998 08:58:03 PM
//
// @doc
// @module PropertyMacros.h | Macros, die das Leben vereinfachen

#if !defined(_PROPERTYMACROS_H__C3BF0D44_7DF6_11D2_9EF6_006008447800__INCLUDED_)
#define _PROPERTYMACROS_H__C3BF0D44_7DF6_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// DeklarationsMacros
#define DECLARE_PROPERTY_GET(prop,type) STDMETHOD(get_##prop)(type *pVal);
#define DECLARE_PROPERTY_PUT(prop,type) STDMETHOD(put_##prop)(type newVal);
#define DECLARE_PROPERTY_ACCESS(prop,type) \
	DECLARE_PROPERTY_GET(prop,type) \
	DECLARE_PROPERTY_PUT(prop,type) 

///////////////////////////////////////////////////////////////////////////////
// ImplementationsMacros
#define IMPLEMENT_PROPERTY_GET(class,prop,type) \
STDMETHODIMP class::get_##prop(type *pVal) { return CopyProperty(*pVal, m_##prop); }
#define IMPLEMENT_PROPERTY_PUT(class,prop,type) \
STDMETHODIMP class::put_##prop(type newVal) { m_##prop = newVal; return S_OK; }
#define IMPLEMENT_PROPERTY_ACCESS(class,prop,type) \
	IMPLEMENT_PROPERTY_GET(class,prop,type) \
	IMPLEMENT_PROPERTY_PUT(class,prop,type)

///////////////////////////////////////////////////////////////////////////////
// HelperFunktionen für propget's
template<class T>
inline HRESULT CopyProperty (T &dest, T &src)
{
	dest = src;
	return S_OK;
}

inline HRESULT CopyProperty (BSTR &dest, CComBSTR &src)
{
CComBSTR bstr (src);

	dest = bstr.Detach();
	return S_OK;
}

template<class T>
inline HRESULT CopyProperty (T *&dest, __Interface<T> &src)
{
	COM_TRY {
	__Interface iface (src);

		dest = iface.detach();
	} COM_CATCH;
	return S_OK;
}

#endif // !defined(_PROPERTYMACROS_H__C3BF0D44_7DF6_11D2_9EF6_006008447800__INCLUDED_)
