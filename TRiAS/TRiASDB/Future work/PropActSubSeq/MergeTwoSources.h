// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
//
// @doc
// @module MergeTwoSources.h | Declaration of the <c CMergeTwoSources> class

#if !defined(__MERGETWOSOURCES_H_)
#define __MERGETWOSOURCES_H_

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

#include "MergeTwoSourcesDlg.h"

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
// CMergeTwoSources
class ATL_NO_VTABLE CMergeTwoSources : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMergeTwoSources, &CLSID_MergeTwoSources>,
	public IObjectWithSiteImpl<CMergeTwoSources>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_NONE
	};

	CMergeTwoSources() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_MERGETWOSOURCES)
	{
		m_pCfgDlg = NULL;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MERGETWOSOURCES)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CMergeTwoSources)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStream)
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

private:
	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
	CMergeTwoSourcesDlg *m_pCfgDlg;	// Konfigurationsdialog
};

#endif // !defined(__MERGETWOSOURCES_H_)
