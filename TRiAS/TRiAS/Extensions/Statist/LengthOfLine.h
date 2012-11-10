// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.12.2000 19:58:24 
//
// @doc
// @module LengthOfLine.h | Declaration of the <c CLengthOfLine> class

#if !defined(_LENGTHOFLINE_H__D9841078_EA07_428C_8874_7691AD630E22__INCLUDED_)
#define _LENGTHOFLINE_H__D9841078_EA07_428C_8874_7691AD630E22__INCLUDED_

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
// Objekteigenschaft CLengthOfLine
class ATL_NO_VTABLE CLengthOfLine : 
	public CComCoClass<CLengthOfLine, &CLSID_LengthOfLine>,
	public CObjectPropertyBase
{
public:

	CLengthOfLine() : 
		CObjectPropertyBase (IDS_OP_NAME_LENGTHOFLINE, IDS_OP_DESCRIPTION_LENGTHOFLINE)
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
//		RETURN_FAILED_HRESULT(m_UnitMeas.LocalCreateInstance(CLSID_TRiASUnitsOfMeasure));
		RETURN_FAILED_HRESULT(m_CumPts.LocalCreateInstance (CLSID_TRiASSimpleStatistics));
		return S_OK;
	}

	void FinalRelease()
	{
//		m_UnitMeas.Assign(NULL);
		m_CumPts.Assign (NULL);
	}


	BEGIN_COM_MAP(CLengthOfLine)
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
//	WTRiASUnitsOfMeasure m_UnitMeAs;	// Maßeinheiten
};

#endif // !defined(_LENGTHOFLINE_H__D9841078_EA07_428C_8874_7691AD630E22__INCLUDED_)
