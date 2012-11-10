// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.01.2000 21:47:54 
//
// @doc
// @module AddAsObjectClass.h | Declaration of the <c CAddAsObjectClass> class

#if !defined(_ADDASOBJECTCLASS_H__DAC01BFD_D94B_4A00_871D_F241BF4BCBB1__INCLUDED_)
#define _ADDASOBJECTCLASS_H__DAC01BFD_D94B_4A00_871D_F241BF4BCBB1__INCLUDED_

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

#include "AddAsObjectClassDlg.h"

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
// CAddAsObjectClass
class ATL_NO_VTABLE CAddAsObjectClass : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CAddAsObjectClass, &CLSID_AddAsObjectClass>,
	public IObjectWithSiteImpl<CAddAsObjectClass>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_ACTION_MUSTREPAINT |
			PROPCAPS_NONE
	};

	CAddAsObjectClass() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_MAKEOBJCLASS_DESC)
	{
		m_pCfgDlg = NULL;
	}
	~CAddAsObjectClass()
	{
		DELETE_OBJ(m_pCfgDlg);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_ADDASOBJECTCLASS)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CAddAsObjectClass)
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

// Geokomponente hat eigenen Dialog
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD(AddConfigPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);

// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

public:
	LONG GetDestClass() { return m_lIdent; }
	bool GetAddToView() { return m_fAddToView; }

private:
	long m_lIdent;			// Resultate
	bool m_fAddToView;
	bool m_fHasInitData;

	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
	CAddAsObjectClassDlg *m_pCfgDlg;	// Konfigurationsdialog
};

#endif // !defined(_ADDASOBJECTCLASS_H__DAC01BFD_D94B_4A00_871D_F241BF4BCBB1__INCLUDED_)
