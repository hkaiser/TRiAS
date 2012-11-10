// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.12.1999 12:45:32 
//
// @doc
// @module DefaultInitItem.h | Declaration of the <c CDefaultInitItem> class

#if !defined(_DEFAULTINITITEM_H__8F433AB4_7CA2_4F7C_B25D_BD19DD5C2049__INCLUDED_)
#define _DEFAULTINITITEM_H__8F433AB4_7CA2_4F7C_B25D_BD19DD5C2049__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Predikatklasse zur Verwendung in LoadEnumeratedItems[Stg]Ex
template<class T> 
struct unary_initialize : 
	public os_unary_function<T, HRESULT> 
{
	typedef T unary_initialize_target;
};

///////////////////////////////////////////////////////////////////////////////
// default predicate for LoadEnumeratedItems[Stg]Ex
template<class IF>
class CDefaultInitItem :
	public unary_initialize<__Interface<IF> >
{
public:
	typedef unary_initialize<__Interface<IF> > base_t;
	typedef base_t::unary_initialize_target unary_initialize_target;

	base_t::result_type operator() (base_t::argument_type Prop)
	{
		return S_OK;	// do nothing
	}
};

///////////////////////////////////////////////////////////////////////////////
// Predikatklasse zur Verwendung inSaveEnumeratedItems[Stg]Ex
template<class T1, class T2>
struct binary_initialize_getname :
	public os_binary_function<T1, T2, HRESULT>
{
	typedef T1 binary_initialize_target;
};

///////////////////////////////////////////////////////////////////////////////
// default predicate for SaveEnumeratedItems[Stg]Ex
template<class IF>
class CDefaultGetItemName :
	public binary_initialize_getname<__Interface<IF>, BSTR *>
{
public:
	typedef binary_initialize_getname<__Interface<IF>, BSTR *> base_t;
	typedef base_t::binary_initialize_target binary_initialize_target;

	base_t::result_type operator() (base_t::first_argument_type obj, base_t::second_argument_type val)
	{
		return obj -> get_Name (val);
	}
};

#endif // !defined(_DEFAULTINITITEM_H__8F433AB4_7CA2_4F7C_B25D_BD19DD5C2049__INCLUDED_)
