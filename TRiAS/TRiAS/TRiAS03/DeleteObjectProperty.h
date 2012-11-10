// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 08:52:33
//
// @doc
// @module DeleteObjectProperty.h | Declaration of the <c CDeleteObjectProperty> class

#if !defined(_DELETEOBJECTPROPERTY_H__95B141A8_7F09_4789_8675_A24BF5BF3B17__INCLUDED_)
#define _DELETEOBJECTPROPERTY_H__95B141A8_7F09_4789_8675_A24BF5BF3B17__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiAS03.h"       // main symbols

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>
#include <ospace/std/list>

#include "DeleteObjectPropertyDlg.h"

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
// CDeleteObjectProperty
class ATL_NO_VTABLE CDeleteObjectProperty : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDeleteObjectProperty, &CLSID_DeleteObjectProperty>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_NONE
	};

	CDeleteObjectProperty() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_DELETEOBJECTPROPERTY)
	{
		m_pCfgDlg = NULL;
	}
	~CDeleteObjectProperty()
	{
		DELETE_OBJ(m_pCfgDlg);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_DELETEOBJECTPROPERTY)
	
	BEGIN_CATEGORY_MAP(CDeleteObjectProperty)
		IMPLEMENTED_CATEGORY(CATID_TRiASGeoComponent)
	END_CATEGORY_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CDeleteObjectProperty)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
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

// Geokomponente hat eigenen Dialog
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD(AddConfigPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);

// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

protected:
	HRESULT GetPropList(list<WObjectProperty> &rLstProps);

private:
	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
	CDeleteObjectPropertyDlg *m_pCfgDlg;	// Konfigurationsdialog
	list<os_string> m_lstProps;			// Objekteigenschaften (in der richtigen Reihenfolge)
};

#endif // !defined(_DELETEOBJECTPROPERTY_H__95B141A8_7F09_4789_8675_A24BF5BF3B17__INCLUDED_)
