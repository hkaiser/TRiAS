// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/18/1998 08:27:11 PM
//
// @doc
// @module MatchRegExprExakt.h | Description goes here

#if !defined(_MATCHREGEXPREXAKT_H__C3BF0D3C_7DF6_11D2_9EF6_006008447800__INCLUDED_)
#define _MATCHREGEXPREXAKT_H__C3BF0D3C_7DF6_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/string/src/regex.h>	// GNU regular expression matcher
#include <ospace/string/regexp.h>

#include "resource.h"       // main symbols
#include "MatchBase.h"

/////////////////////////////////////////////////////////////////////////////
// CMatchRegExprExakt
class ATL_NO_VTABLE CMatchRegExprExakt : 
	public CMatchStringBase,
	public CComCoClass<CMatchRegExprExakt, &CLSID_MatchRegExprExakt>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMatchRegExpr, &IID_IMatchRegExpr, &LIBID_TRiASSupport,
		TYPELIB_TRIASSUPPORT_VERSION_MAJOR, TYPELIB_TRIASSUPPORT_VERSION_MINOR>
{
public:
	CMatchRegExprExakt()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CMatchRegExprExakt)
	DECLARE_REGISTRY_RESOURCEID(IDR_MATCHREGEXPREXAKT)

	BEGIN_COM_MAP(CMatchRegExprExakt)
		COM_INTERFACE_ENTRY(IMatchRegExpr)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_CHAIN(CMatchStringBase)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMatchRegExpr
	DECLARE_PROPERTY_ACCESS(FullMatch, VARIANT_BOOL);

// DMatchString
public:
	STDMETHOD(MatchString)(/*[in]*/ BSTR StringToMatch, /*[out, retval]*/ int *Matched);
	STDMETHOD(MatchAndReplaceString)(/*[in]*/ BSTR StringToMatch, /*[in]*/ BSTR StringToReplace, /*[out]*/ int *Matched, /*[out, retval]*/ BSTR *pbstrResult);

	DECLARE_PROPERTY_PUT(MatchText, BSTR);
	DECLARE_PROPERTY_PUT(MatchCase, VARIANT_BOOL);

private:
	VARIANT_BOOL m_FullMatch;

// RegExpression Matching (mit/ohne CaseTest)
	class CRegExpr : 
		public os_regexp 
	{
	public:
		CRegExpr() {}
		~CRegExpr (void);

		void MatchCase (bool fMatchCase);
		os_string ExpandBackReferences (const char *pcPattern);
	};
	CRegExpr m_regxToMatch;
};

#endif // !defined(_MATCHREGEXPREXAKT_H__C3BF0D3C_7DF6_11D2_9EF6_006008447800__INCLUDED_)
