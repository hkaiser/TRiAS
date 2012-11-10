// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.11.2002 09:25:38 
//
// @doc
// @module LineTools.h | Declaration of the <c CLineToolsExtension> class

#if !defined(_LINETOOLS_H__BABC0172_4DFC_48B1_AFC1_959399A240C2__INCLUDED_)
#define _LINETOOLS_H__BABC0172_4DFC_48B1_AFC1_959399A240C2__INCLUDED_

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
// CLineToolsExtension
class ATL_NO_VTABLE CLineToolsExtension : 
	public CComCoClass<CLineToolsExtension, &CLSID_LineTools>,
	public CTriasExtension 
{

//	UINT	m_iMainMenu;
//	UINT	m_iORMenu;
	BOOL	m_bHaveXML;
	BOOL	m_bHaveEngines;
	int	m_iMethod;				// Prüfmethode


public:
	CLineToolsExtension()
		: CTriasExtension (IDR_MENU1,IDR_MENU2)
//		: m_iMainMenu(0)
//		, m_iORMenu(0)
		, m_bHaveXML(TRUE)
		, m_bHaveEngines(TRUE)
		, m_iMethod(0)
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CLineToolsExtension, g_pTE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CLineToolsExtension)
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


	HRESULT OnCodeCheckData( WPARAM wParam,bool bMainData );

	int Method (void ) { return m_iMethod; }
	

};

#pragma HDR_OFF()


#endif // !defined(_LINETOOLS_H__BABC0172_4DFC_48B1_AFC1_959399A240C2__INCLUDED_)
