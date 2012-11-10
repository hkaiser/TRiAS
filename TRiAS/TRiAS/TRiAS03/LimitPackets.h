// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.08.2002 10:53:49 
//
// @doc
// @module LimitPackets.h | Declaration of the <c CLimitPackets> class

#if !defined(_LIMITPACKETS_H__182C09BD_E9B2_4D31_8193_01B1133277B5__INCLUDED_)
#define _LIMITPACKETS_H__182C09BD_E9B2_4D31_8193_01B1133277B5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "trias03.h"       // main symbols

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

#include "LimitPacketsDlg.h"

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
// CLimitPackets
class ATL_NO_VTABLE CLimitPackets : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLimitPackets, &CLSID_LimitPackets>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_NONE
	};

	CLimitPackets() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_LIMITPACKETS)
	{
		m_pCfgDlg = NULL;
	}
	~CLimitPackets()
	{
		DELETE_OBJ(m_pCfgDlg);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_LIMITPACKETS)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CLimitPackets)
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
// IPersistStreamInit
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(IPropertyBag *pBag, IErrorLog *pLog);

protected:
	bool BlockPacket (IEnum<LONG> *pIEnumObjs);

private:
	typedef list<WEnumLONG> CListOfPackets;
	CListOfPackets m_Objects;				// zu bearbeitende Objektmenge
	CListOfPackets::iterator m_itlist;
	long m_lPacket;
	long m_lORWndCnt;

	CLimitPacketsDlg *m_pCfgDlg;	// Konfigurationsdialog
	LIMITPACKETSDATA m_selData;
};

#endif // !defined(_LIMITPACKETS_H__182C09BD_E9B2_4D31_8193_01B1133277B5__INCLUDED_)
