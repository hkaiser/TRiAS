// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 19.07.2002 09:14:00 
//
// @doc
// @module Segment.h | Declaration of the <c CSegmentExtension> class

#if !defined(_SEGMENT_H__FD748927_F10D_412D_93CC_EBAD6C6258F9__INCLUDED_)
#define _SEGMENT_H__FD748927_F10D_412D_93CC_EBAD6C6258F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#pragma HDR_ON()

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSegmentExtension
class ATL_NO_VTABLE CSegmentExtension : 
	public CComCoClass<CSegmentExtension, &CLSID_Segment>,
	public CTriasExtension 
{

	UINT	m_iMainMenu;
	UINT	m_iORMenu;
	BOOL	m_bHaveXML;
	BOOL	m_bHaveEngines;

public:
	CSegmentExtension()
		: m_iMainMenu(0)
		, m_iORMenu(0)
		, m_bHaveXML(TRUE)
		, m_bHaveEngines(TRUE)
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CSegmentExtension, g_pTE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CSegmentExtension)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);

// Menuhandling
	STDMETHOD_(BOOL, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);


	HRESULT OnSegmentData( bool bMainData );
	
};

#pragma HDR_OFF()

#endif // !defined(_SEGMENT_H__FD748927_F10D_412D_93CC_EBAD6C6258F9__INCLUDED_)
