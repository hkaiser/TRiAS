// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.03.2000 19:22:32 
//
// @doc
// @module RemoveFromObjectClass.h | Declaration of the <c CRemoveFromObjectClass> class

#if !defined(_REMOVEFROMOBJECTCLASS_H__D75B9A49_E694_4814_8174_4F32CDBF752B__INCLUDED_)
#define _REMOVEFROMOBJECTCLASS_H__D75B9A49_E694_4814_8174_4F32CDBF752B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

#include <DelFromClsPrp.h>

/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

/////////////////////////////////////////////////////////////////////////////
// CRemoveFromObjectClass
class ATL_NO_VTABLE CRemoveFromObjectClass : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CRemoveFromObjectClass, &CLSID_RemoveFromObjectClass>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_ACTION_MUSTREPAINT
	};

	CRemoveFromObjectClass() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_REMOVEFROMOBJECTCLASS)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_REMOVEFROMOBJECTCLASS)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CRemoveFromObjectClass)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
	END_COM_MAP()

// IPropertyAction 
public:
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD(DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD(EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);

private:
	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
};

#endif // !defined(_REMOVEFROMOBJECTCLASS_H__D75B9A49_E694_4814_8174_4F32CDBF752B__INCLUDED_)
