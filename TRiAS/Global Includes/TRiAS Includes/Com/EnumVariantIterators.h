// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/16/1998 12:18:38 PM
//
// @doc
// @module EnumVariantIterators.h | STL Iteratoren für IEnumVARIANT's

#if !defined(_ENUMVARIANTITERATORS_H__F45F28D5_7D2F_11D2_9EF6_006008447800__INCLUDED_)
#define _ENUMVARIANTITERATORS_H__F45F28D5_7D2F_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/com/iterenum.h>

///////////////////////////////////////////////////////////////////////////////
// STL Input-Iterator für einen IEnumVARIANT

typedef ienum_iterator<CComVariant, __CIID<&__uuidof(IEnumVARIANT)>, ptrdiff_t> InEnumVARIANT;

template<class InterfaceType, class CollInterfaceType>
class __InEnumIterator :
	public InEnumVARIANT
{
public:
	typedef CollInterfaceType enum_t;
	typedef __InEnumIterator<InterfaceType, CollInterfaceType> self_t;
	typedef __Interface<InterfaceType> target_t;

	__InEnumIterator () throw() {}
	__InEnumIterator (enum_t *pIObjs) throw(_com_error &)
	{
	__Interface<IEnumVARIANT> Enum;

		THROW_FAILED_HRESULT(pIObjs -> _NewEnum (Enum.ppu()));
		enumerator = (IEnum<VARIANT> *)Enum.detach();
		enumerator -> Reset(); 
		read(); 
	}

	target_t operator *() throw(_com_error &)
	{
	CComVariant v(value);

		_ASSERTE(end_marker || V_VT(&v) == VT_DISPATCH);
		return target_t(end_marker ? NULL : V_DISPATCH(&v));
	}
	
	target_t operator++ (void) throw(_com_error &) { read(); return this->operator*(); }
	target_t operator++ (int) throw(_com_error &) { target_t tmp(*this); read(); return tmp; }
};

///////////////////////////////////////////////////////////////////////////////
// STL Output-Iterator für einen IEnumVARIANT

template<class InterfaceType, class CollInterfaceType>
class __OutEnumIterator
	: public output_iterator
{
public:
	typedef CollInterfaceType enum_t;
	typedef __Interface<InterfaceType> target_t;
	typedef __OutEnumIterator<InterfaceType, CollInterfaceType> self_t;

protected:
	__Interface<enum_t> enumerator;

public:
	__OutEnumIterator (void) throw() : enumerator() {}
	__OutEnumIterator (enum_t *pIEnum) throw() : enumerator(pIEnum) {}
	__OutEnumIterator (IUnknown *pIUnk) throw(_com_error &) : enumerator(pIUnk) {}	// throws hr
	__OutEnumIterator (const self_t &iter) throw() : enumerator(iter.enumerator) {}

    self_t& operator= (const target_t &value) throw(_com_error &) 
		{ THROW_FAILED_HRESULT(enumerator -> _Add(value)); return *this; }
	self_t& operator * (void) throw() { return *this; }
	self_t& operator++ (void)	throw() { return *this; }
	self_t operator++ (int) throw() { return *this;	}
};

#endif // !defined(_ENUMVARIANTITERATORS_H__F45F28D5_7D2F_11D2_9EF6_006008447800__INCLUDED_)
