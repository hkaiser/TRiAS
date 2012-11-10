// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 07/10/1998 08:18:06 PM
//
// @doc
// @module EnumProperty.h | Wrapperdefinition für PropertyEnumerator

#if !defined(_ENUMPROPERTY_H__95F09634_181D_11D2_9E8F_006008447800__INCLUDED_)
#define _ENUMPROPERTY_H__95F09634_181D_11D2_9E8F_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// {422FB8C1-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASProperty = 
	{0x422fb8c1,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

//DefineEnumerator2(WTRiASProperty, IID_IEnumTRiASProperty);		// NEnumWTRiASProperty
//DefineSmartEnumerator(WTRiASProperty);							// WEnumWTRiASProperty
//typedef IEnum<WTRiASProperty> IEnumTRiASProperty;

///////////////////////////////////////////////////////////////////////////////
// Geeigneter Enumerator für Propertys, der gleichzeitig den schnellen
// Zugriff über die Namen ermöglicht

DefineSmartInterface(TRiASProperty);

// Enumerator soll FindItem und RemoveItem über CComBSTR haben (s. iterenum.h)
typedef IEnumEx<CComBSTR, WTRiASProperty> IEnumTRiASProperty;

///////////////////////////////////////////////////////////////////////////////
// Die folgenden typedef's verwenden die in <ospace/com/iterenum.h> definierten Templates,
// um einen Enumerator zu definieren, der neben der Standardfunktionalität (Reset, Skip, Clone etc.)
// zusätzlich die Möglichkeit bietet, schnell an einzelne Einträge heranzukommen (hier über den
// Bezeichner des Propertys, s.a. 'bool operator< (const CComBSTR &, const CComBSTR &)' ).

// Helperklasse zur Verpackung des CLSID's als Klasse
DefineEnumIIDWrapper2(WTRiASProperty, IID_IEnumTRiASProperty);		// CIID_WTRiASPropertyEnum

// der eigentliche Enumerator
typedef map<CComBSTR, WTRiASProperty, less<CComBSTR> > CEnumPropertyMap;	// unterliegende Map
typedef __Enumerator<WTRiASProperty, CIID_WTRiASPropertyEnum, CEnumPropertyMap, 
			__EnumeratorBaseTarget<WTRiASProperty, CEnumPropertyMap, IEnumTRiASProperty> > 
		TEnumWTRiASProperty;

// Wrapper für Interface, über welches der definierte Enumerator ansprechbar ist
typedef __Interface<IEnumTRiASProperty, CIID_WTRiASPropertyEnum, CComPtr<IEnumTRiASProperty> > WEnumWTRiASProperty;

#endif // !defined(_ENUMPROPERTY_H__95F09634_181D_11D2_9E8F_006008447800__INCLUDED_)
