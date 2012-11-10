// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/06/1998 01:36:29 PM
//
// @doc
// @module BerlinExt.h | TRiAS Berlinfachschale

#if !defined(_BerlinEXT_H__E2054A33_4327_11D2_9EBE_006008447800__INCLUDED_)
#define _BerlinEXT_H__E2054A33_4327_11D2_9EBE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface(ExtendBScript);

///////////////////////////////////////////////////////////////////////////////
// ErweiterungsKlasse 


class CBerlinExt : 
	public CTriasExtension,
#if defined ( BERLINUPDATE)
	public CComCoClass<CBerlinExt, &CLSID_BerlinUpdate>
#else
	public CComCoClass<CBerlinExt, &CLSID_BerlinExt>
#endif

{
public:
	BEGIN_COM_MAP(CBerlinExt)
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(ITriasXtension)
	END_COM_MAP()

// Die folgende Zeile einfügen, wenn der alte Mechanismus der
// Registrierung der Erweiterungen intakt bleibt
	DECLARE_NO_REGISTRY();
	DECLARE_NOT_AGGREGATABLE_SINGLE(CBerlinExt, g_pTE);

		CBerlinExt (void) {}
		~CBerlinExt() {}


	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

	HRESULT CreateBlnDataToolBar(void);
	HRESULT RemoveBlnDataToolBar(void);
//----------------------------------------------------------------
//-ToolBar
	HRESULT StartALB ( void);
	HRESULT StartBlink(void);
	HRESULT StartGiTest ( void);
	HRESULT StartFTeil(void);
	HRESULT StartUnbau(void);
	HRESULT StartInsel ( void);
	HRESULT StartNummer ( void);
	HRESULT StartIdent ( void);
	HRESULT StartObjNummer ( void);
#if defined ( BERLINUPDATE)
	HRESULT StartFlurTest(void);
	HRESULT StartIDTest(void);
#endif


// Zugriff auf BasicScriptExtension
	HRESULT GetBasicScript (IExtendBScript **ppIBasicScript)
	{
		if (NULL == ppIBasicScript) return E_POINTER;

	WExtendBScript BScript (m_BasicScript);

		*ppIBasicScript = BScript.detach();
		return S_OK;
	}

private:
	WExtendBScript m_BasicScript;
};

#endif // !defined(_BerlinEXT_H__E2054A33_4327_11D2_9EBE_006008447800__INCLUDED_)
