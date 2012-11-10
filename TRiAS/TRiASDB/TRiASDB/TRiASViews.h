///////////////////////////////////////////////////////////////////////////
// TRiASViews.h : Declaration of the CTRiASViews

#if !defined(_TRIASVIEWS_H__7C8CB9C2_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASVIEWS_H__7C8CB9C2_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"			// main symbols
#include "PersistStgImpl.h"		// IPersistStorageOMImpl

/////////////////////////////////////////////////////////////////////////////
// SmartIF's etc. 
// {422FB8C4-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumWTRiASView = 
	{0x422fb8c4,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

// Enumerator soll FindItem und RemoveItem über CComBSTR haben (s. iterenum.h)
typedef IEnumEx<CComBSTR, WTRiASView> IEnumWTRiASView;

///////////////////////////////////////////////////////////////////////////////
// Die folgenden typedef's verwenden die in <ospace/com/iterenum.h> definierten Templates,
// um einen Enumerator zu definieren, der neben der Standardfunktionalität (Reset, Skip, Clone etc.)
// zusätzlich die Möglichkeit bietet, schnell an einzelne Einträge heranzukommen (hier über den
// Bezeichner der View, s.a. 'bool operator< (const CComBSTR &, const CComBSTR &)' ).

// Helperklasse zur Verpackung des CLSID's als Klasse
DefineEnumIIDWrapper2(WTRiASView, IID_IEnumWTRiASView);			// CIID_WTRiASViewEnum

// ViewNamen kennen keine Groß/Kleinschreibung!
class CCmpViewNames : 
	public os_binary_function<CComBSTR, CComBSTR, bool>
{
public:
	enum { MAX_VIEWNAMELEN = 40, };
	bool operator()(const CComBSTR& x, const CComBSTR& y) const
	{
		if (x.Length() > MAX_VIEWNAMELEN || y.Length() > MAX_VIEWNAMELEN)
			return (_wcsnicmp (x, y, MAX_VIEWNAMELEN) < 0) ? true : false;	// tribut to old TRiAS
		return (_wcsicmp (x, y) < 0) ? true : false;
	}
};

// der eigentliche Enumerator
typedef map<CComBSTR, WTRiASView, CCmpViewNames> CEnumViewMap;	// unterliegende Map
typedef __Enumerator<WTRiASView, CIID_WTRiASViewEnum, CEnumViewMap, 
			__EnumeratorBaseTarget<WTRiASView, CEnumViewMap, IEnumWTRiASView> > 
		TEnumWTRiASView;

// Wrapper für Interface, über welches der definierte Enumerator ansprechbar ist
typedef __Interface<IEnumWTRiASView, CIID_WTRiASViewEnum, CComPtr<IEnumWTRiASView> > WEnumWTRiASView;


/////////////////////////////////////////////////////////////////////////////
// CTRiASViews

class ATL_NO_VTABLE CTRiASViews : 
	public ISupportErrorInfo,
	public IPersistStorageOMImpl<CTRiASViews>,
	public CReportErrorComCoClass<CTRiASViews, &CLSID_TRiASViews, &IID_ITRiASViews>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASViewEvents,
	public ITRiASConnectionEvents,
	public IDispatchImpl<ITRiASViews, &IID_ITRiASViews, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASViews interface_t;
	typedef ITRiASView controlled_t;

	CTRiASViews() :
		m_lSemDel(0), m_lSemAdd(0), m_pIParent(NULL), 
		m_dwCookie(0), m_dwCookieConns(0)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASViews)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASVIEWS)

	BEGIN_COM_MAP(CTRiASViews)
		COM_INTERFACE_ENTRY(ITRiASViews)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASViews)
		COM_INTERFACE_ENTRY(ITRiASViewEvents)
		COM_INTERFACE_ENTRY(ITRiASConnectionEvents)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IID(IID_IPersistStorage, IPersistStorageOMImpl<CTRiASViews>)
		COM_INTERFACE_ENTRY2_IID(IID_IPersist, IPersist, IPersistStorageOMImpl<CTRiASViews>)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct (void);
	void FinalRelease (void);

	HRESULT InitEnum (IEnumWTRiASView *pTarget)
	{ 
		return pTarget -> Clone (m_Enum.ppi()); 
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASViews
public:
	STDMETHOD(RemoveView)(/*[in]*/ ITRiASView *pIView);
	STDMETHOD(SetEventSink)(/*[in]*/ IUnknown *pIUnk, /*[in]*/ VARIANT_BOOL fAdvise);
	STDMETHOD(_Clone)(/*[out, retval]*/ ITRiASViews **ppIViews);
	STDMETHOD(_Add)(/*[in]*/ ITRiASView *pIView, /*[in, optional, defaultvalue(VARIANT_TRUE)]*/ VARIANT_BOOL fFullAdd);

	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Remove)(/*[in]*/ VARIANT Index);
	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ ITRiASView **ppIView);
	STDMETHOD(Add)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASView **ppIView);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);

	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch * newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_StartViewName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_StartViewName)(/*[in]*/ BSTR newVal);

	STDMETHOD(OnFinalRelease)();

// ITRiASViewEvents
	STDMETHOD(CreatingView)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ViewToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(ViewCreated)(/*[in]*/ IDispatch *pIView);
	STDMETHOD(ChangingView)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ViewToChange)(/*[in]*/ BSTR Name, /*[in]*/ BSTR NewName);
	STDMETHOD(ViewChanged)(/*[in]*/ IDispatch *pIView);
	STDMETHOD(DeletingView)(/*[in]*/ IDispatch *pIView, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ViewToDelete)(/*[in]*/ IDispatch *pIView);
	STDMETHOD(ViewDeleted)(/*[in]*/ BSTR Name);

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

// must be implemented for IPersistStorageOMImpl<>
//	HRESULT AddTeanant (IUnknown *pIUnk) throw (_com_error &)
//		{ return _Add(WTRiASView(pIUnk)); }
	LPCTSTR GetDescription() const 
		{ return g_cbTRiASViews; }

protected:
// Events verschicken
	HRESULT Fire_CreatingView (BSTR Name, VARIANT_BOOL *pVal);
	HRESULT Fire_ViewToCreate (BSTR Name);
	HRESULT Fire_ViewCreated (IDispatch * pIConn);
	HRESULT Fire_DeletingView (IDispatch *pIConn, VARIANT_BOOL * pVal);
	HRESULT Fire_ViewToDelete (IDispatch * pIConn);
	HRESULT Fire_ViewDeleted(BSTR Name);

	HRESULT GetClonedEnum (IEnumWTRiASView **ppIEnum)
	{
		return m_Enum -> Clone (ppIEnum);
	}

private:
	CComPtr<IDispatch> m_Application;
	IDispatch *m_pIParent;			// no AddRef (fully contained)

// Views spezifische member
	WEnumWTRiASView m_Enum;	// eigener Enumerator

	LONG m_lSemDel;					// Semaphore für Eventbehandlung
	LONG m_lSemAdd;

	DWORD m_dwCookie;				// ViewEvents
	DWORD m_dwCookieConns;			// ConnEvents
};

#endif // !defined(_TRIASVIEWS_H__7C8CB9C2_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
