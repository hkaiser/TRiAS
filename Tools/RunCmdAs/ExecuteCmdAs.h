// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 20.04.2002 19:54:18 
//
// @doc
// @module ExecuteCmdAs.h | Declaration of the <c CExecuteCmdAs> class

#if !defined(_EXECUTECMDAS_H__08C99E65_1B1A_48AF_B297_358D94F12536__INCLUDED_)
#define _EXECUTECMDAS_H__08C99E65_1B1A_48AF_B297_358D94F12536__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExecuteCmdAs
class ATL_NO_VTABLE CExecuteCmdAs : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExecuteCmdAs, &CLSID_ExecuteCmdAs>,
	public ISupportErrorInfo,
	public IDispatchImpl<IExecuteCmdAs, &IID_IExecuteCmdAs, &LIBID_RunCmdAs>
{
public:
	CExecuteCmdAs()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_EXECUTECMDAS)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CExecuteCmdAs)
		COM_INTERFACE_ENTRY(IExecuteCmdAs)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IExecuteCmdAs
public:
	STDMETHOD(ExecuteCmd)(/*[iin]*/ BSTR Cmd, /*[in]*/ BSTR CommandLine, /*[out, retval]*/ int *RetVal);
};

#endif // !defined(_EXECUTECMDAS_H__08C99E65_1B1A_48AF_B297_358D94F12536__INCLUDED_)
