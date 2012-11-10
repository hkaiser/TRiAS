// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.10.2000 17:38:25
//
// @doc
// @module GenerateObjectProperties.h | Declaration of the <c CGenerateObjectProperties> class

#if !defined(_GENERATEOBJECTPROPERTIES_H__7E176BEB_78CA_4E4C_B956_FE48D3081CDE__INCLUDED_)
#define _GENERATEOBJECTPROPERTIES_H__7E176BEB_78CA_4E4C_B956_FE48D3081CDE__INCLUDED_

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

#include "GenerateObjectPropertiesDlg.h"
#include "GenerateObjectPropertiesSequenceDlg.h"
#include "GenerateObjectPropertiesOptionsDlg.h"

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
// CGenerateObjectProperties
class CGenObjPropDest;

class ATL_NO_VTABLE CGenerateObjectProperties : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CGenerateObjectProperties, &CLSID_GenerateObjectProperties>,
	public IObjectWithSiteImpl<CGenerateObjectProperties>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_NONE
	};

	CGenerateObjectProperties() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_GENERATEOBJECTPROPERTIES)
	{
		m_pCfgSelect = NULL;
		m_pCfgSequence = NULL;
		m_pCfgOptions = NULL;
	}
	~CGenerateObjectProperties()
	{
		DELETE_OBJ(m_pCfgOptions);
		DELETE_OBJ(m_pCfgSelect);
		DELETE_OBJ(m_pCfgSequence);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_GENERATEOBJECTPROPERTIES)
	BEGIN_CATEGORY_MAP(CGenerateObjectProperties)
		IMPLEMENTED_CATEGORY(CATID_TRiASGeoComponent)
	END_CATEGORY_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CGenerateObjectProperties)
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

// sonstiges
	bool GetSelectedProps (list<os_string> &rLstProps)
	{
		if (m_pCfgSelect -> ChangedPropList()) {
			_ASSERTE(m_pCfgSelect);
			rLstProps = m_pCfgSelect -> GetSelectedObjProps();
		} else
			rLstProps = m_lstProps;		// Reihenfolge des vorherigen Aufrufes beibehalten
		return true;
	}
	int GetCountSelectedProps() { return m_pCfgSelect -> GetSelectedObjProps().size(); }

// eigentliche Ausgabe
	HRESULT OutputToClipboard(OutEnumLONG &rIterOut);
	HRESULT OutputToFile(OutEnumLONG &rIterOut);
	HRESULT OutputToObjProp(OutEnumLONG &rIterOut);
	HRESULT OutputToWindow(OutEnumLONG &rIterOut);
	HRESULT GenericOutput(OutEnumLONG &rIterOut, CGenObjPropDest *pDest, bool fHideStatus = false);

	HRESULT GetPropList(list<WObjectProperty> &rLstProps);
	long GetObjectsCount();
//	list<os_string>::difference_type GetObjPropCount() { return m_lstProps.size(); }
	
private:
	typedef list<SEnumLONG> CListOfPackets;
	CListOfPackets m_Objects;				// zu bearbeitende Objektmenge
	CGenerateObjectPropertiesSelectDlg *m_pCfgSelect;	// Konfigurationsdialoge
	CGenerateObjectPropertiesSequenceDlg *m_pCfgSequence;
	CGenerateObjectPropertiesOptionsDlg *m_pCfgOptions;

// ausgewählte Einstellungen
	list<os_string> m_lstProps;			// Objekteigenschaften (in der richtigen Reihenfolge)

	bool m_fHeadLine;					// auszugebenede Informationen
	bool m_fCumulate;
	bool m_fProps;
	bool m_fCounter;

	CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST m_rgDest;	// wohin ausgeben
	os_string m_strObjPropName;			// ggf. ZielProp
	os_string m_strFileName;			// ggf. Dateiname
	char m_cDelimiter;					// Trennzeichen
};

#endif // !defined(_GENERATEOBJECTPROPERTIES_H__7E176BEB_78CA_4E4C_B956_FE48D3081CDE__INCLUDED_)
