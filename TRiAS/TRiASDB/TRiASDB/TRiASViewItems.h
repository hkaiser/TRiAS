///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASViewItems.h | Declaration of the CTRiASViewItems

#if !defined(_TRIASVIEWITEMS_H__7C8CB9B8_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASVIEWITEMS_H__7C8CB9B8_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "TRiASViewItem.h"

///////////////////////////////////////////////////////////////////////////////
// FMTID fürs Speichern/Laden
// {7CD5571F-6427-11D2-9EDE-006008447800}
extern "C" const FMTID __declspec(selectany) FMTID_EnumViewItems = 
	{0x7cd5571f,0x6427,0x11d2,{0x9e,0xde,0x00,0x60,0x08,0x44,0x78,0x00}};

///////////////////////////////////////////////////////////////////////////////
// Geeigneter Enumerator für ViewItems, der gleichzeitig den schnellen
// Zugriff über die Namen ermöglicht

// {422FB8C5-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASViewItem = 
	{0x422fb8c5,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

DefineSmartInterface(TRiASViewItem);

// Enumerator soll FindItem und RemoveItem über CComBSTR haben (s. iterenum.h)
typedef IEnumEx<CComBSTR, WTRiASViewItem> IEnumTRiASViewItem;

///////////////////////////////////////////////////////////////////////////////
// Die folgenden typedef's verwenden die in <ospace/com/iterenum.h> definierten Templates,
// um einen Enumerator zu definieren, der neben der Standardfunktionalität (Reset, Skip, Clone etc.)
// zusätzlich die Möglichkeit bietet, schnell an einzelne Einträge heranzukommen (hier über den
// Bezeichner des ViewItems, s.a. 'bool operator< (const CComBSTR &, const CComBSTR &)' ).

// Helperklasse zur Verpackung des CLSID's als Klasse
DefineEnumIIDWrapper2(WTRiASViewItem, IID_IEnumTRiASViewItem);		// CIID_WTRiASViewItemEnum

// der eigentliche Enumerator
typedef map<CComBSTR, WTRiASViewItem, less<CComBSTR> > CEnumViewItemMap;	// unterliegende Map
typedef __Enumerator<WTRiASViewItem, CIID_WTRiASViewItemEnum, CEnumViewItemMap, 
			__EnumeratorBaseTarget<WTRiASViewItem, CEnumViewItemMap, IEnumTRiASViewItem> > 
		TEnumWTRiASViewItem;

// Wrapper für Interface, über welches der definierte Enumerator ansprechbar ist
typedef __Interface<IEnumTRiASViewItem, CIID_WTRiASViewItemEnum, CComPtr<IEnumTRiASViewItem> > WEnumWTRiASViewItem;

///////////////////////////////////////////////////////////////////////////////
// CTRiASViewItems

class ATL_NO_VTABLE CTRiASViewItems : 
	public CReportErrorComCoClass<CTRiASViewItems, &CLSID_TRiASViewItems, &IID_ITRiASViewItems>,
	public ISupportErrorInfo,
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASConnectionEvents,
	public ITRiASViewItemEvents,
	public IDispatchImpl<ITRiASViewItems, &IID_ITRiASViewItems, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASViewItems interface_t;
	typedef ITRiASViewItem controlled_t;

	CTRiASViewItems()
		: m_dwCookie(0L), m_pIParent(NULL), m_lSemDel(0L)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASViewItems)
	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASVIEWITEMS)

	BEGIN_COM_MAP(CTRiASViewItems)
		COM_INTERFACE_ENTRY(ITRiASViewItems)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASViewItems)
		COM_INTERFACE_ENTRY(ITRiASViewItemEvents)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASConnectionEvents)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct();
	void FinalRelease (void);

	HRESULT InitEnum (IEnumTRiASViewItem *pTarget)
	{ 
		return pTarget -> Clone (m_Enum.ppi()); 
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASViewItemEvents
	STDMETHOD(CreatingViewItem)(BSTR Name, VARIANT_BOOL *pVal);
	STDMETHOD(ViewItemToCreate)(BSTR Name);
	STDMETHOD(ViewItemCreated)(IDispatch *pIViewItem);
	STDMETHOD(ModifyingViewItem)(IDispatch *pIViewItem, VARIANT_BOOL *pVal);
	STDMETHOD(ViewItemToModify)(IDispatch *pIViewItem);
	STDMETHOD(ViewItemModified)(BSTR Name);
	STDMETHOD(DeletingViewItem)(IDispatch *pIViewItem, VARIANT_BOOL *pVal);
	STDMETHOD(ViewItemToDelete)(IDispatch *pIViewItem);
	STDMETHOD(ViewItemDeleted)(BSTR Name);

// ITRiASConnectionEvents
	STDMETHOD(CreatingConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionCreated)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(OpeningConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToOpen)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionOpened)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ClosingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToClose)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionClosed)(/*[in]*/ BSTR Name);
	STDMETHOD(DeletingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToDelete)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionDeleted)(/*[in]*/ BSTR Name);
	STDMETHOD(RenamingConnection)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToRename)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName);
	STDMETHOD(ConnectionRenamed)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ChangingConnectedDatasource)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectedDatasourceToChange)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectedDatasourceChanged)(/*[in]*/ IDispatch *pIConn);

// ITRiASViewItems
public:
	STDMETHOD(SetEventSink)(/*[in]*/ IUnknown *pIUnk, /*[in]*/ VARIANT_BOOL fAdvise);
	STDMETHOD(_Clone)(/*[out, retval]*/ ITRiASViewItems **pIViewItems);
	STDMETHOD(_Add)(/*[in]*/ ITRiASViewItem *pIViewItem, /*[in, optional, defaultvalue(VARIANT_TRUE)]*/ VARIANT_BOOL fFullAdd);

	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Remove)(/*[in]*/ VARIANT Index);
	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ ITRiASViewItem **ViewItem);
	STDMETHOD(Add)(/*[in]*/ BSTR Name, /*[in, optional, defaultvalue]*/ BSTR Type, /*[out, retval]*/ ITRiASViewItem **ViewItem);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_ItemCount)(/*[out, retval]*/ long *pVal);

	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

protected:
// Events verschicken
	HRESULT Fire_CreatingViewItem (BSTR Name, VARIANT_BOOL *pVal);
	HRESULT Fire_ViewItemToCreate (BSTR Name);
	HRESULT Fire_ViewItemCreated (IDispatch *pIViewItem);
	HRESULT Fire_DeletingViewItem (IDispatch *pIViewItem, VARIANT_BOOL *pVal);
	HRESULT Fire_ViewItemToDelete (IDispatch *pIViewItem);
	HRESULT Fire_ViewItemDeleted (BSTR Name);

	HRESULT RemoveViewItem (ITRiASViewItem *pIViewItem);

private:
	CComPtr<IDispatch> m_Application;
	IDispatch *m_pIParent;			// no AddRef (fully contained)

	WEnumWTRiASViewItem m_Enum;		// enumerator der zugehörigen ViewItems

	LONG m_lSemDel;					// Semaphore für Eventbehandlung
	DWORD m_dwCookie;				// Connection zu View
};

#endif // !defined(_TRIASVIEWITEMS_H__7C8CB9B8_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
