// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/12/1998 09:20:50 PM
//
// @doc
// @module ObjekteDoppeln.h | Declaration of the <c CObjekteDoppeln> class

#if !defined(_OBJEKTEDOPPELN_H__E3C50CA4_4A48_11D2_9EC2_006008447800__INCLUDED_)
#define _OBJEKTEDOPPELN_H__E3C50CA4_4A48_11D2_9EC2_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "trias03.h"       // main symbols
#include "Strings.h"

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

#include "CopyObjectsDlg.h"

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
// CCopyObjects
class ATL_NO_VTABLE CCopyObjects : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCopyObjects, &CLSID_ObjekteDoppelnV2>,
	public IObjectWithSiteImpl<CCopyObjects>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_ACTION_MUSTREPAINT
	};

	CCopyObjects() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_COPYOBJECTS_COPYOBJS),
		m_hPr(HACTCONNECTION)
	{
		m_pCfgDlg = NULL;
	}
	~CCopyObjects()
	{
		DELETE_OBJ(m_pCfgDlg);
	}

	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_OBJEKTEDOPPELN)
	DECLARE_NOT_AGGREGATABLE(CCopyObjects)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CCopyObjects)
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

// IPersistBla
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

	STDMETHOD(Load)(IPropertyBag *pBag, IErrorLog *pLog);

// Geokomponente hat eigenen Dialog
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD(AddConfigPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);

public:
	HPROJECT GetDestinationProject() { return m_hPr; }

private:
	typedef list<SEnumLONG> CListOfPackets;
	CListOfPackets m_Objects;				// zu bearbeitende Objektmenge
	CListOfPackets::iterator m_itlist;
	long m_lPacket;							// Paketnummer

	HPROJECT m_hPr;

	CComBSTR m_bstrDataSource;	// ggf. Zieldatenquelle
	CCopyObjectsDlg *m_pCfgDlg;	// Konfigurationsdialog
};

#endif // !defined(_OBJEKTEDOPPELN_H__E3C50CA4_4A48_11D2_9EC2_006008447800__INCLUDED_)
