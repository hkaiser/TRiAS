// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module FullAreaFrame.h | Declaration of the <c CFullAreaFrame> class

#if !defined(__FULLAREAFRAME_H_)
#define __FULLAREAFRAME_H_

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
// Objekteigenschaft CFullAreaFrame
class ATL_NO_VTABLE CFullAreaFrame : 
	public CComCoClass<CFullAreaFrame, &CLSID_FullAreaFrame>,
	public CObjectPropertyBase
{
public:

	CFullAreaFrame() : 
		CObjectPropertyBase (IDS_OP_NAME_FULLAREAFRAME, IDS_OP_DESCRIPTION_FULLAREAFRAME)
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


	BEGIN_COM_MAP(CFullAreaFrame)
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

#endif // !defined(__FULLAREAFRAME_H_)
