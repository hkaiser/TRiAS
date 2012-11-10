// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: $$date_n_time$$ 
//
// @doc
// @module $$root$$.h | Declaration of the <c C$$safe_root$$Extension> class

#if !defined(_$$SAFE_ROOT$$_H__$$XTENSION_H_GUID$$__INCLUDED_)
#define _$$SAFE_ROOT$$_H__$$XTENSION_H_GUID$$__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// C$$safe_root$$Extension
class ATL_NO_VTABLE C$$safe_root$$Extension : 
	public CComCoClass<C$$safe_root$$Extension, &CLSID_$$safe_root$$>,
	public CTriasExtension 
{
public:
	C$$safe_root$$Extension()
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(C$$safe_root$$Extension, g_pTE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(C$$safe_root$$Extension)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);
};

#endif // !defined(_$$SAFE_ROOT$$_H__$$XTENSION_H_GUID$$__INCLUDED_)
