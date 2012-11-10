// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/18/1998 08:34:01 PM
//
// @doc
// @module MatchBase.h | Description goes here

#if !defined(_MATCHBASE_H__C3BF0D40_7DF6_11D2_9EF6_006008447800__INCLUDED_)
#define _MATCHBASE_H__C3BF0D40_7DF6_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Com/PropertyMacros.h>

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für Matching von String

class CMatchStringBase :
	public CComObjectRootEx<CComObjectThreadModel>,
	public IDispatchImpl<DMatchString2, &IID_DMatchString2, &LIBID_TRiASSupport,
		TYPELIB_TRIASSUPPORT_VERSION_MAJOR, TYPELIB_TRIASSUPPORT_VERSION_MINOR>
{
public:
	CMatchStringBase(void) : 
		m_MatchCase(VARIANT_FALSE), m_NegateMatch(VARIANT_FALSE)
	{
	}

	BEGIN_COM_MAP(CMatchStringBase)
		COM_INTERFACE_ENTRY(DMatchString2)
		COM_INTERFACE_ENTRY(DMatchString)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

// sonstige Member
	DECLARE_PROPERTY_ACCESS(MatchText, BSTR);
	DECLARE_PROPERTY_ACCESS(MatchCase, VARIANT_BOOL);
	DECLARE_PROPERTY_ACCESS(NegateMatch, VARIANT_BOOL);

// Test, ob Objekt initialisiert ist
	inline bool IsNotValid (void) { return !m_MatchText; }

protected:
	VARIANT_BOOL m_MatchCase;
	VARIANT_BOOL m_NegateMatch;
	CComBSTR m_MatchText;
};

#endif // !defined(_MATCHBASE_H__C3BF0D40_7DF6_11D2_9EF6_006008447800__INCLUDED_)
