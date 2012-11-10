// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/18/1998 08:22:14 PM
//
// @doc
// @module MatchObjects.h | Description goes here

#if !defined(_MATCHOBJECTS_H__C3BF0D38_7DF6_11D2_9EF6_006008447800__INCLUDED_)
#define _MATCHOBJECTS_H__C3BF0D38_7DF6_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "MatchBase.h"

/////////////////////////////////////////////////////////////////////////////
// CMatchPlainTextExakt
class ATL_NO_VTABLE CMatchPlainTextExakt : 
	public CMatchStringBase,
	public CComCoClass<CMatchPlainTextExakt, &CLSID_MatchPlainTextExakt>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMatchPlainText, &IID_IMatchPlainText, &LIBID_TRiASSupport,
		TYPELIB_TRIASSUPPORT_VERSION_MAJOR, TYPELIB_TRIASSUPPORT_VERSION_MINOR>
{
public:
	CMatchPlainTextExakt() :
		m_FullMatch(VARIANT_TRUE), m_ExistanceOnly(VARIANT_FALSE), 
		m_TestBOB(VARIANT_FALSE), m_iMatchLen(0)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CMatchPlainTextExakt)
	DECLARE_REGISTRY_RESOURCEID(IDR_MATCHPLAINTEXTEXAKT)

	BEGIN_COM_MAP(CMatchPlainTextExakt)
		COM_INTERFACE_ENTRY(IMatchPlainText)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_CHAIN(CMatchStringBase)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMatchPlainText
	DECLARE_PROPERTY_ACCESS(TestBOB, VARIANT_BOOL);
	DECLARE_PROPERTY_ACCESS(ExistanceOnly, VARIANT_BOOL);
	DECLARE_PROPERTY_ACCESS(FullMatch, VARIANT_BOOL);

// DMatchString
public:
	STDMETHOD(MatchString)(/*[in]*/ BSTR StringToMatch, /*[out, retval]*/ int *Matched);
	STDMETHOD(MatchAndReplaceString)(/*[in]*/ BSTR StringToMatch, /*[in]*/ BSTR StringToReplace, /*[out]*/ int *Matched, /*[out, retval]*/ BSTR *pbstrResult);
	
	DECLARE_PROPERTY_PUT(MatchCase, VARIANT_BOOL);
	DECLARE_PROPERTY_PUT(MatchText, BSTR);

private:
	VARIANT_BOOL m_FullMatch;
	VARIANT_BOOL m_ExistanceOnly;
	VARIANT_BOOL m_TestBOB;

	size_t m_iMatchLen;
};

#endif // !defined(_MATCHOBJECTS_H__C3BF0D38_7DF6_11D2_9EF6_006008447800__INCLUDED_)
