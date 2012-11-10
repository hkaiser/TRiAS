// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module SimpleAreaRadius.h | Declaration of the <c CSimpleAreaRadius> class

#if !defined(__SIMPLEAREARADIUS_H_)
#define __SIMPLEAREARADIUS_H_

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
// Objekteigenschaft CSimpleAreaRadius
class ATL_NO_VTABLE CSimpleAreaRadius : 
	public CComCoClass<CSimpleAreaRadius, &CLSID_SimpleAreaRadius>,
	public CObjectPropertyBase


{
public:

	CSimpleAreaRadius() : 
		CObjectPropertyBase (IDS_OP_NAME_SIMPLEAREARADIUS, IDS_OP_DESCRIPTION_SIMPLEAREARADIUS) 
	{
	}


	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return m_CumPts.LocalCreateInstance (CLSID_TRiASSimpleStatistics);
	}

	void FinalRelease()
	{
		m_CumPts.Assign (NULL);
	}

	BEGIN_COM_MAP(CSimpleAreaRadius)
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

#endif // !defined(__SIMPLEAREARADIUS_H_)
