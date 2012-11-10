// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 11.11.2004 20:23:51
//
// @doc
// @module LinesToAreas.h | Declaration of the <c CLinesToAreas> class

#if !defined(__LINESTOAREAS_H_)
#define __LINESTOAREAS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "trias03.h"       // main symbols
#include "Strings.h"

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
// CLinesToAreas
class ATL_NO_VTABLE CLinesToAreas : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLinesToAreas, &CLSID_LinesToAreas>,
	public IObjectWithSiteImpl<CLinesToAreas>,
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

	CLinesToAreas() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_LINESTOAREAS),
        m_hPr(HACTCONNECTION)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_LINESTOAREAS)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CLinesToAreas)
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

// IPersistBla
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

	STDMETHOD(Load)(IPropertyBag *pBag, IErrorLog *pLog);

// functional member functions
    HRESULT LineToArea(HOBJECT lONr, HOBJECT *plNewONr);

private:
	typedef list<SEnumLONG> CListOfPackets;
	CListOfPackets m_Objects;				// zu bearbeitende Objektmenge
	CListOfPackets::iterator m_itlist;
	long m_lPacket;							// Paketnummer

    HPROJECT m_hPr;
    CComBSTR m_bstrDataSource;
};

#endif // !defined(__LINESTOAREAS_H_)
