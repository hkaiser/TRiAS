// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.10.2000 18:40:03
//
// @doc
// @module PropertyActionJoin.h | Declaration of the <c CPropertyActionJoin> class

#if !defined(_PROPERTYACTIONJOIN_H__FB8EBB7A_E065_47D2_9A1E_625E05C3680C__INCLUDED_)
#define _PROPERTYACTIONJOIN_H__FB8EBB7A_E065_47D2_9A1E_625E05C3680C__INCLUDED_

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
#include <ospace/std/list>

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ipropseq.hxx>

/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(DataObject);
DefineSmartInterface(PropertyAction);

/////////////////////////////////////////////////////////////////////////////
// CPropertyActionJoin
class ATL_NO_VTABLE CPropertyActionJoin : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPropertyActionJoin, &CLSID_PropertyActionJoin>,
	public IObjectWithSiteImpl<CPropertyActionJoin>,
	public IPropertyActionSequence,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_CONTAINER_IS_SEQUENCE
	};

	CPropertyActionJoin() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_PROPERTYACTIONJOIN),
		m_lPacketOffset(0)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_PROPERTYACTIONJOIN)
	BEGIN_CATEGORY_MAP(CPropertyActionJoin)
		IMPLEMENTED_CATEGORY(CATID_TRiASGeoComponentContainer)
		IMPLEMENTED_CATEGORY(CATID_TRiASGeoComponent)
	END_CATEGORY_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CPropertyActionJoin)
		COM_INTERFACE_ENTRY(IPropertyActionSequence)
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
	STDMETHOD(AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD(PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags);

// IPropertyActionSequence
	STDMETHOD(AddAction) (THIS_ IPropertyAction *pIAct);
	STDMETHOD(AddActionsByCLSID) (THIS_ CALPCLSID *pcaClsIds);
	STDMETHOD(DoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus, IDataObject *pIData, IDataObject **ppOutData);
	STDMETHOD(GetDescription) (THIS_ LPSTR pDesc, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(RedoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus, IDataObject *pIData, IDataObject **ppOutData);
	STDMETHOD(PrepareActions) (THIS_ HWND hParent, IDataObject *pIData);
	STDMETHOD(GetSequenceContext) (THIS_ IDataObject **ppIData);
	STDMETHOD(SetDescription) (THIS_ LPCSTR pcDesc);

	STDMETHOD (GetVersion) (THIS_ LPSTR pDesc, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD (SetVersion) (THIS_ LPCSTR pcDesc);
	STDMETHOD (SetIsWizard97) (THIS_ VARIANT_BOOL fIsWizard97);
	STDMETHOD (GetHeaderTitle) (THIS_ LPSTR pBuffer, ULONG wLen);
	STDMETHOD (SetHeaderTitle) (THIS_ LPCSTR pcHeaderTitle);
	STDMETHOD (GetHeaderSubTitle) (THIS_ LPSTR pSubBuffer, ULONG wLen);
	STDMETHOD (SetHeaderSubTitle) (THIS_ LPCSTR pcHeaderSubTitle);

// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew)(THIS);

// IObjectWithSite
	STDMETHOD(SetSite)(THIS_ IUnknown *pUnkSite);

// IPersistPropertyBag
	STDMETHOD(Load)(IPropertyBag *pBag, IErrorLog *pLog);

protected:

private:
	typedef list<WDataObject> CListOfDataObjects;
	CListOfDataObjects m_listObjects;		// zu bearbeitende Objektmengen (direct input)
	CListOfDataObjects::iterator m_itlist;
	
// Menge der sonst noch am Eingang stehenden Geo-Komponenten
	typedef list<WPropertyAction> CActionList;
	CActionList m_Actions;					// Liste der auszuführenden Aktionen
	CActionList::iterator m_itact;
	size_t m_iCurrAct;
	bool m_fHasDoAction : 1;				// für m_iCurrAct wurde bereits DoAction gerufen

	int m_iFirst;							// erstes und letztes Objekt mit Dialog merken
	int m_iLast;

	long m_lPacketOffset;					// Offset für Packetnummern
};

///////////////////////////////////////////////////////////////////////////////
// Versionen für Speichern eines PropertyActionJoin
const DWORD PROPERTYACTIONJOIN_SIGNATURE = 0x4A434150;	// "PACJ"
const DWORD PROPERTYACTIONJOIN_VERSION_100 = 0x0100;
const DWORD PROPERTYACTIONJOIN_VERSION_101 = 0x0101;
const DWORD PROPERTYACTIONJOIN_MINOR_MASK = 0xff;
const DWORD PROPERTYACTIONJOIN_LASTVERSION = PROPERTYACTIONJOIN_VERSION_101;

#endif // !defined(_PROPERTYACTIONJOIN_H__FB8EBB7A_E065_47D2_9A1E_625E05C3680C__INCLUDED_)
