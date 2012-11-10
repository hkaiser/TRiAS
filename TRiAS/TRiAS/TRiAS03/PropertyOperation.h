// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.10.2000 15:48:46
//
// @doc
// @module PropertyOperation.h | Declaration of the <c CPropertyOperation> class

#if !defined(_PROPERTYOPERATION_H__CF7F29B6_73CA_4B9A_8593_148B71A49E96__INCLUDED_)
#define _PROPERTYOPERATION_H__CF7F29B6_73CA_4B9A_8593_148B71A49E96__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiAS03.h"       // main symbols

#include <ospace/com/iterenum.h>
#include <ospace/std/set>
#include <ospace/std/map>

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>

/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

DefineSmartInterface(PropertyAction);

/////////////////////////////////////////////////////////////////////////////
// CPropertyOperation
class ATL_NO_VTABLE CPropertyOperation : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CPropertyOperation, &CLSID_PropertyOperation>,
	public IObjectWithSiteImpl<CPropertyOperation>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE
	};

	CPropertyOperation() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_PROPERTYOPERATION),
		m_rgOperation(PROPERTYOPERATION_A_Or_B)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_PROPERTYOPERATION)
	BEGIN_CATEGORY_MAP(CObjPropMerkmal)
		IMPLEMENTED_CATEGORY(CATID_TRiASGeoComponent)
	END_CATEGORY_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CPropertyOperation)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

// IPropertyAction 
public:
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD(DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD(EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

// IPersistPropertyBag
	STDMETHOD(Load) (THIS_ IPropertyBag *pBag, IErrorLog *pLog);

protected:
	HRESULT A_Or_B(OutEnumLONG &rIterOut);
	HRESULT A_And_B(OutEnumLONG &rIterOut);
	HRESULT NotA_And_B(OutEnumLONG &rIterOut);
	HRESULT A_And_NotB(OutEnumLONG &rIterOut);
	HRESULT A_Xor_B(OutEnumLONG &rIterOut);

private:
	typedef map<long, SEnumLONG, less<long> > CMapOfPackets;
	CMapOfPackets m_Objects;		// zu bearbeitenden Objektmengen

	enum PROPERTYOPERATION {
		PROPERTYOPERATION_Unknown = -1,
		PROPERTYOPERATION_A_Or_B = 0x10,		// Vereinigungsmenge 
		PROPERTYOPERATION_A_And_B = 0x20,		// Schnittmenge
		PROPERTYOPERATION_NotA_And_B = 0x21,	// Komplementärmenge zu A aus B
		PROPERTYOPERATION_A_And_NotB = 0x22,	// Komplementärmenge zu B aus A
		PROPERTYOPERATION_A_Xor_B = 0x30,		// symmetrische Differenz (xor)
	};
	PROPERTYOPERATION m_rgOperation;
};

#endif // !defined(_PROPERTYOPERATION_H__CF7F29B6_73CA_4B9A_8593_148B71A49E96__INCLUDED_)
