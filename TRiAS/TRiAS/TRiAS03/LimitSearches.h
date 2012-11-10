// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 15.04.2002 11:20:46 
//
// @doc
// @module LimitSearches.h | Declaration of the <c CLimitSearches> class

#if !defined(_LIMITSEARCHES_H__697D3B60_E1AA_43F2_8DF0_418BB5643E74__INCLUDED_)
#define _LIMITSEARCHES_H__697D3B60_E1AA_43F2_8DF0_418BB5643E74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

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
// CLimitSearches
class ATL_NO_VTABLE CLimitSearches : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLimitSearches, &CLSID_LimitSearches>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_NONE
	};

	CLimitSearches() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_LIMITSEARCHES)
	{
	}
	~CLimitSearches()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_LIMITSEARCHES)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CLimitSearches)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStream)
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

protected:
	HRESULT EnsureRefObjects();
	BOOL __stdcall AddRefObject (HOBJECT ONr, BOOL iNotLast, void *pData);

private:
	typedef list<SEnumLONG> CListOfPackets;
	CListOfPackets m_Objects;				// zu bearbeitende Objektmenge
	CListOfPackets::iterator m_itlist;
	long m_lPacket;							// Paketnummer

	SEnumLONG m_RefObjects;					// alle Objekte des Ausschnittes
	bool m_fRefObjectsInit;					// Objekte bereits initialisiert
};

#endif // !defined(_LIMITSEARCHES_H__697D3B60_E1AA_43F2_8DF0_418BB5643E74__INCLUDED_)
