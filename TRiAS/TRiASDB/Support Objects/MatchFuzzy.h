// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/18/1998 08:30:30 PM
//
// @doc
// @module MatchFuzzy.h | Description goes here

#if !defined(_MATCHFUZZY_H__C3BF0D3F_7DF6_11D2_9EF6_006008447800__INCLUDED_)
#define _MATCHFUZZY_H__C3BF0D3F_7DF6_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "MatchBase.h"

/////////////////////////////////////////////////////////////////////////////
// required constants
const int COMP_LEN = 20;
const int ARR_SIZE = COMP_LEN + 1;

const int addition = 1;		// change constants in this block
const int change   = 2;		// of four lines if needed.
const int deletion = 3;

inline int SMALLEST_OF (int x, int y, int z)
{ 
	return ((x < y) ? min(x, z) : min(y, z)); 
}

/////////////////////////////////////////////////////////////////////////////
// CMatchFuzzy
class ATL_NO_VTABLE CMatchFuzzy : 
	public CMatchStringBase,
	public CComCoClass<CMatchFuzzy, &CLSID_MatchFuzzy>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMatchFuzzy, &IID_IMatchFuzzy, &LIBID_TRiASSupport,
		TYPELIB_TRIASSUPPORT_VERSION_MAJOR, TYPELIB_TRIASSUPPORT_VERSION_MINOR>
{
public:
	CMatchFuzzy()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CMatchFuzzy)
	DECLARE_REGISTRY_RESOURCEID(IDR_MATCHFUZZY)

	BEGIN_COM_MAP(CMatchFuzzy)
		COM_INTERFACE_ENTRY(IMatchFuzzy)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_CHAIN(CMatchStringBase)
	END_COM_MAP()

	inline int ZERO_IF_EQUAL (BSTR bstr, int x, int y)
		{ return (towupper(m_MatchText[x-1]) == towupper(bstr[y-1]) ? 0 : change); }

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMatchFuzzy

// DMatchString
public:
	STDMETHOD(MatchString)(/*[in]*/ BSTR StringToMatch, /*[out, retval]*/ int *Matched);
	STDMETHOD(MatchAndReplaceString)(/*[in]*/ BSTR StringToMatch, /*[in]*/ BSTR StringToReplace, /*[out]*/ int *Matched, /*[out, retval]*/ BSTR *pbstrResult);

	DECLARE_PROPERTY_PUT(MatchText, BSTR);

private:
	int m_distance[ARR_SIZE][ARR_SIZE];
	int m_iLen;
	int m_iThreshold;
};

#endif // !defined(_MATCHFUZZY_H__C3BF0D3F_7DF6_11D2_9EF6_006008447800__INCLUDED_)
