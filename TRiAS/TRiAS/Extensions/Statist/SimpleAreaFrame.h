// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.12.2000 20:06:16 
//
// @doc
// @module SimpleAreaFrame.h | Declaration of the <c CSimpleAreaFrame> class

#if !defined(_SIMPLEAREAFRAME_H__71888AEF_DECB_4B06_8A98_85CC1CA000E7__INCLUDED_)
#define _SIMPLEAREAFRAME_H__71888AEF_DECB_4B06_8A98_85CC1CA000E7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

#include <Com/ObjectPropertyBase.h>

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft CSimpleAreaFrame
class ATL_NO_VTABLE CSimpleAreaFrame : 
	public CComCoClass<CSimpleAreaFrame, &CLSID_SimpleAreaFrame>,
	public CObjectPropertyBase
{
public:

	CSimpleAreaFrame() : 
		CObjectPropertyBase (IDS_OP_NAME_SIMPLEAREAFRAME, IDS_OP_DESCRIPTION_SIMPLEAREAFRAME)
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_CumPts.LocalCreateInstance (CLSID_TRiASSimpleStatistics));
		return S_OK;
	}
	void FinalRelease()
	{
		m_CumPts.Assign (NULL);
	}

	BEGIN_COM_MAP(CSimpleAreaFrame)
	// der erste Eintrag in dieser Map muß ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)

	// die folgenden werden hier nicht unterstützt 
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStreamInit)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStream)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersist)

	// alles andere macht die Basisklasse
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)
	END_COM_MAP()

// IObjectProperty
public:
	STDMETHOD(Reset)(THIS);
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

private:
	WTRiASSimpleStatistics m_CumPts;	// kumulierte Punktanzahl (Mittelwertberechnung)
};

#endif // !defined(_SIMPLEAREAFRAME_H__71888AEF_DECB_4B06_8A98_85CC1CA000E7__INCLUDED_)
