// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 12.11.2004 11:41:37 
//
// @doc
// @module LoadableCommands.h | Declaration of the <c CLoadableCommandsExtension> class

#if !defined(_LOADABLECOMMANDS_H__27930245_FEE4_4A05_901B_D99C6178AEDE__INCLUDED_)
#define _LOADABLECOMMANDS_H__27930245_FEE4_4A05_901B_D99C6178AEDE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoadableCommandsExtension
class ATL_NO_VTABLE CLoadableCommandsExtension : 
	public CComCoClass<CLoadableCommandsExtension, &CLSID_LoadableCommands>,
	public CTriasExtension 
{
public:
	CLoadableCommandsExtension()
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CLoadableCommandsExtension, g_pTE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CLoadableCommandsExtension)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);

// Menuhandling
	STDMETHOD_(BOOL, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
};

#endif // !defined(_LOADABLECOMMANDS_H__27930245_FEE4_4A05_901B_D99C6178AEDE__INCLUDED_)
