///////////////////////////////////////////////////////////////////////////
// TRiASView.h : Declaration of the CTRiASView

#if !defined(_TRIASVIEW_H__7C8CB9C1_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASVIEW_H__7C8CB9C1_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CPTRiASPropertyEvents.h"		// connection point
#include "CPTRiASViewItemEvents.h"

#include "resource.h"       // main symbols
#include "TRiASProperties.h"
#include "PropertySupport.h"
#include "PropertyBase.h"

/////////////////////////////////////////////////////////////////////////////
// SmartIF's etc. 
DefineSmartInterface(TRiASViewItems);					// WTRiASViewItems

/////////////////////////////////////////////////////////////////////////////
// CTRiASView
class ATL_NO_VTABLE CTRiASView : 
	public ISupportErrorInfo,
	public IPersistStreamInit,
	public CProxyITRiASPropertyEvents<CTRiASView>,
	public CProxyITRiASViewItemEvents<CTRiASView>,
	public CManagePropertySupport<CTRiASView>,
	public CManagePropertyBase<CTRiASView>,
	public IConnectionPointContainerImpl<CTRiASView>,
	public CReportErrorComCoClass<CTRiASView, &CLSID_TRiASView, &IID_ITRiASView>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASConnectionEvents,
	public ITRiASViewItemEvents,
	public ITRiASPropertyEvents,
	public IProvideClassInfo2Impl<&CLSID_TRiASView, &IID_ITRiASViewItemEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASView, &IID_ITRiASView, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASView()
		: m_fIsInitialized(false), m_fIsDirty(false),
		  m_fIsStartView(false), m_bstrName(g_cbNil)
	{
	}

	DECLARE_ONE_SIZE_PRIVATE_HEAP();

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASView)
//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASView)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASVIEW)

	BEGIN_COM_MAP(CTRiASView)
		COM_INTERFACE_ENTRY(ITRiASView)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASView)
		COM_INTERFACE_ENTRY(ITRiASPropertySupport)		// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyMapHandler)	// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyBase)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
		COM_INTERFACE_ENTRY(ITRiASViewItemEvents)
		COM_INTERFACE_ENTRY(ITRiASPropertyEvents)
		COM_INTERFACE_ENTRY(ITRiASConnectionEvents)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASView)
		CONNECTION_POINT_ENTRY(IID_ITRiASViewItemEvents)
		CONNECTION_POINT_ENTRY(IID_ITRiASPropertyEvents)
	END_CONNECTION_POINT_MAP()

// die folgenden Properties sind jetzt schon bekannt
	BEGIN_PROPERTYSUPPORT_MAP(CTRiASView)
		PROPERTYSUPPORT_ENTRY(L"SichtContMCode", CLSID_TRiASAutoSaveProperty)
		PROPERTYSUPPORT_ENTRY(L"BMasstabMCode", CLSID_TRiASAutoSaveProperty)
		PROPERTYSUPPORT_ENTRY(L"ObjectRegion", CLSID_TRiASAutoSaveProperty)
		PROPERTYSUPPORT_ENTRY(L"ObjPropToShow", CLSID_TRiASAutoSaveProperty)
		PROPERTYSUPPORT_ENTRY(L"HideAndSortFlags", CLSID_TRiASAutoSaveProperty)

	// alle anderen werden einfach so erzeugt und nicht gekäscht :-)
		PROPERTYSUPPORT_ENTRY_DEFAULT(CLSID_TRiASAutoSaveProperty)
	END_PROPERTYSUPPORT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease (void)
	{
		m_ViewItems.Assign (NULL);
		FreePropertiesCollection();

		m_Parent = NULL;
		m_Application = NULL;
	}
	IDispatch *GetDispatch() { return static_cast<ITRiASView *>(this); }
	ITRiASView *GetTRiASView() { return static_cast<ITRiASView *>(this); }

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

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

// ITRiASPropertyEvents
	STDMETHOD(CreatingProperty)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(PropertyCreated)(/*[in]*/ IDispatch *pIProp);
	STDMETHOD(ModifyingProperty)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToModify)(/*[in]*/ BSTR Name);
	STDMETHOD(PropertyModified)(/*[in]*/ BSTR Name);
	STDMETHOD(DeletingProperty)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToDelete)(/*[in]*/ BSTR Name);
	STDMETHOD(PropertyDeleted)(/*[in]*/ BSTR Name);

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

// ITRiASView
public:
	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_RelatedDataSourceName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_RelatedDataSourceName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ConnectionFilter)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ConnectionFilter)(/*[in]*/ BSTR newVal);

	STDMETHOD(AddViewItem)(/*[in]*/ ITRiASViewItem *Item);

	STDMETHOD(get_ViewItem)(/*[in]*/ VARIANT vItem, /*[in, defaultvalue]*/ VARIANT_BOOL fCreate, /*[in, defaultvalue]*/ BSTR Type, /*[out, retval]*/ ITRiASViewItem **pVal);
	STDMETHOD(get_ViewItems)(/*[out, retval]*/ ITRiASViewItems **pVal);
	STDMETHOD(get_ObjectsDefs)(/*[out, retval]*/ ITRiASObjectsCollection * *pVal);

	STDMETHOD(get_IsStartView)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsStartView)(/*[in]*/ VARIANT_BOOL newVal);

	STDMETHOD(get_Relations)(/*[out, retval]*/ ITRiASRelations * *pVal);
	STDMETHOD(put_Relations)(/*[in]*/ ITRiASRelations *pVal);

	STDMETHOD(OnFinalRelease)();

// ITRiASPropertySupport
	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);

// ITRiASPropertyBase
//	STDMETHOD(get_Property)(BSTR Which, /*[out, retval]*/ ITRiASProperty * *pVal);
//	STDMETHOD(get_Properties)(/*[out, retval]*/ ITRiASProperties * *pVal);
//	STDMETHOD(put_Properties)(/*[in]*/ ITRiASProperties *pVal);

	HRESULT IsInitialized()
	{
		if (m_fIsInitialized) 
			return S_OK;
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	}

protected:
	HRESULT CreateViewItemCollection();

	HRESULT Fire_ChangingView(BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal);
	HRESULT Fire_ViewToChange(BSTR OldName, BSTR NewName);
	HRESULT Fire_ViewChanged(IDispatch * pIView);

private:
// allgemeine Daten
	CComPtr<IDispatch> m_Application;
	CComPtr<IDispatch> m_Parent;

	bool m_fIsDirty;
	bool m_fIsInitialized;
	bool m_fIsStartView;

// Ansichts-spezifische Daten
	WTRiASViewItems m_ViewItems;			// ViewItems dieser Ansicht
	CComBSTR m_bstrName;					// AnsichtsName
	CComBSTR m_bstrRelatedDataSourceName;	// Ursprungsdatenquelle
	CComBSTR m_bstrConnectionFilter;		// zugeordneter räumlicher Filter
};

///////////////////////////////////////////////////////////////////////////////
// Version des PersistStream-Formates
const long VIEW_SIGNATURE = 0x57454956L;	// "VIEW"
const long VIEW_VERSION_MINOR_MASK = 0xff;
const long VIEW_VERSION_100 = 0x0100L;
const long VIEW_VERSION_101 = 0x0101L;
const long VIEW_VERSION_102 = 0x0102L;
const long VIEW_VERSION_103 = 0x0103L;		// #HK990709
const long VIEW_VERSION_104 = 0x0104L;		// #HK030319, ADDED: ConnectionFilter
const long LASTKNOWN_VIEW_VERSION = VIEW_VERSION_104;

#endif // !defined(_TRIASVIEW_H__7C8CB9C1_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
