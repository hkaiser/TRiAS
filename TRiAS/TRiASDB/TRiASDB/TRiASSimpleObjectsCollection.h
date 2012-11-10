// @doc 
// @module TRiASSimpleObjectsCollection.h | Declaration of the <c CTRiASSimpleObjectsCollection> class

#if !defined(_TRIASSIMPLEOBJECTSCOLLECTION_H__5F20C608_B87C_11D2_95A8_006008447800__INCLUDED_)
#define _TRIASSIMPLEOBJECTSCOLLECTION_H__5F20C608_B87C_11D2_95A8_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
//
#include <NativePbd.h>

using namespace trias_nativepbd;

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleObjectsCollection
class ATL_NO_VTABLE CTRiASSimpleObjectsCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASSimpleObjectsCollection, &CLSID_TRiASSimpleObjectsCollection>,
	public ISupportErrorInfo,
	public ITRiASObjectsCollectionCallback,
	public IDispatchImpl<ITRiASSimpleObjectsCollection, &IID_ITRiASSimpleObjectsCollection, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASSimpleObjectsCollection()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASSimpleObjectsCollection)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSIMPLEOBJECTSCOLLECTION)
	DECLARE_AGGREGATE_EX_SUPPORT()

	BEGIN_COM_MAP(CTRiASSimpleObjectsCollection)
		COM_INTERFACE_ENTRY(ITRiASSimpleObjectsCollection)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASObjectsCollectionCallback)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASObjectsCollection, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASSearchObjects, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)		// alles andere nicht gesondert behandeln
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASObjectsCollection, CLSCTX_ALL, GetControllingUnknown()));

	WTRiASObjectsCollection BaseObj;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObj.ppi()));
		return BaseObj -> putref_ObjectsCollectionCallback(this);
	}
	void FinalRelease()
	{
		m_BaseUnk.Assign(NULL);
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASSimpleObjectsCollection
public:
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(OnCreate)(/*[in]*/ VARIANT NameOrHandle, /*[in, optional, defaultvalue]*/ BSTR Type, /*[in]*/ OBJECTSCOLLECTIONTYPE rgType, /*[out, retval]*/ ITRiASObjects **ppIObjs);
	STDMETHOD(OnDelete)(/*[in]*/ VARIANT vWhich);
	STDMETHOD(OnFinalRelease)();

protected:
	HRESULT CreateObject (VARIANT NameOrHandle, DWORD dwType, const CLSID *pClsId, ITRiASObjects **ppIObjs);
	HRESULT RetrieveDBHandle (HPROJECT *phPr)
	{
		COM_TRY {
		WDispatch Parent;

			THROW_FAILED_HRESULT(WTRiASObjectsCollection(m_BaseUnk) -> get_Parent (Parent.ppi()));
			THROW_FAILED_HRESULT(WTRiASDatabase(Parent) -> get_Handle ((INT_PTR *)phPr));

		} COM_CATCH;
		return S_OK;
	}

private:
	WUnknown m_BaseUnk;					// aggregiertes Objekt
};

#endif // !defined(_TRIASSIMPLEOBJECTSCOLLECTION_H__5F20C608_B87C_11D2_95A8_006008447800__INCLUDED_)
