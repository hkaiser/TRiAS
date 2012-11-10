// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module CountAreaIsland.h | Declaration of the <c CCountAreaIsland> class

#if !defined(__COUNTAREAISLAND_H_)
#define __COUNTAREAISLAND_H_

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
// Objekteigenschaft CCountAreaIsland
class ATL_NO_VTABLE CCountAreaIsland : 
	public CComCoClass<CCountAreaIsland, &CLSID_CountAreaIsland>,
	public CObjectPropertyBase
{
public:

	CCountAreaIsland() : 
		CObjectPropertyBase (IDS_OP_NAME_COUNTAREAISLAND, IDS_OP_DESCRIPTION_COUNTAREAISLAND)
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

	BEGIN_COM_MAP(CCountAreaIsland)
	// der erste Eintrag in dieser Map muﬂ ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)

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

#endif // !defined(__COUNTAREAISLAND_H_)
