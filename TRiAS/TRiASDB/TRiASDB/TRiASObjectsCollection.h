///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASObjectsCollection.h | Declaration of the <c CTRiASObjectsCollection>
// class

#if !defined(_TRIASOBJECTSCOLLECTION_H__48172D66_AB72_11D1_858D_00600875138A__INCLUDED_)
#define _TRIASOBJECTSCOLLECTION_H__48172D66_AB72_11D1_858D_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Atl/Ciid.h>
#include <Com/EnumVariantIterators.h>

#include "resource.h"			// main symbols
#include "PersistStgImpl.h"		// IPersistStorageOMImpl
#include "GlobalVars.h"

/////////////////////////////////////////////////////////////////////////////
// SmartIF's etc. 
// {422FB8C7-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASObjects = 
	{0x422fb8c7,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

DefineEnumerator2(WTRiASObjects, IID_IEnumTRiASObjects);		// NEnumWTRiASObjects
DefineSmartEnumerator2(WTRiASObjects, IID_IEnumTRiASObjects);	// WEnumWTRiASObjects

DefineSmartInterface(TRiASObjectsOperations);					// WTRiASObjectsOperations

///////////////////////////////////////////////////////////////////////////////
//
#include <NativeIdent.h>
#include <NativePbd.h>

#include "CPTRiASObjectEvents.h"

using namespace trias_nativeident;
using namespace trias_nativepbd;

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectsCollection
class ATL_NO_VTABLE CTRiASObjectsCollection : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CTRiASObjectsCollection, &CLSID_TRiASObjectsCollection, &IID_ITRiASObjectsCollection>,
	public ISupportErrorInfo,
	public IPersistStorageOMImpl<CTRiASObjectsCollection>,
	public IDispatchImpl<ITRiASSearchObjects, &IID_ITRiASSearchObjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASObjectsCollection, &IID_ITRiASObjectsCollection, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASObjectsCollection interface_t;
	typedef ITRiASObjects controlled_t;

	typedef IPersistStorageOMImpl<CTRiASObjectsCollection> IPSImpl;

	CTRiASObjectsCollection() :
		m_pIParent(NULL), m_pICallback(NULL)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASObjectsCollection)

	BEGIN_COM_MAP(CTRiASObjectsCollection)
		COM_INTERFACE_ENTRY(ITRiASObjectsCollection)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASObjectsCollection)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ITRiASSearchObjects)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IID(IID_IPersistStorage, IPersistStorageOMImpl<CTRiASObjectsCollection>)
		COM_INTERFACE_ENTRY2_IID(IID_IPersist, IPersist, IPersistStorageOMImpl<CTRiASObjectsCollection>)
	END_COM_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASOBJECTSCOLLECTION)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct (void);
	void FinalRelease (void);

	HRESULT CreateNewEnum (IEnum<WTRiASObjects> **ppIEnum)
	{
		ATLTRY(*ppIEnum = new NEnumWTRiASObjects());	// Konstruktor hinterläßt RefCnt==1
		return (NULL == *ppIEnum) ? E_OUTOFMEMORY : S_OK;
	}
	HRESULT InitEnum (IEnum<WTRiASObjects> *pTarget)
	{ 
		return pTarget -> Clone (m_Enum.ppi()); 
	}

// must be implemented for IPersistStorageOMImpl<>
	LPCTSTR GetDescription() const 
		{ return g_cbTRiASQueryCollection; }
	ITRiASObjectsCollection *GetObjectsDefs() { return static_cast<ITRiASObjectsCollection *>(this); }

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASObjectsCollection
public:
	STDMETHOD(putref_ObjectsCollectionCallback)(/*[in]*/ ITRiASObjectsCollectionCallback *pVal);

	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

	STDMETHOD(get_Count)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(Item)(/*[in]*/ VARIANT vItem, /*[out, retval]*/ ITRiASObjects **pVal);
	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **pVal);
	STDMETHOD(Add)(/*[in]*/ BSTR Name, /*[in, optional,defaultvalue]*/ BSTR Type, /*[out, retval]*/ ITRiASObjects **pVal);
	STDMETHOD(_Add)(/*[in]*/ ITRiASObjects *newVal, /*[in, optional, defaultvalue(VARIANT_TRUE)]*/ VARIANT_BOOL FullAdd);
	STDMETHOD(_Clone)(/*[out, retval]*/ ITRiASObjectsCollection **pVal);
	STDMETHOD(Remove)(/*[in]*/ VARIANT vWhich);
	STDMETHOD(Refresh)();

// ITRiASSearchObjects
	STDMETHOD(ConsiderSearch)(/*[in]*/ BSTR bstrCommand, /*[in, optional, defaultvalue]*/ SAFEARRAY *pParams);
	STDMETHOD(SearchObjects)(/*[in]*/ BSTR bstrCommand, /*[in]*/ ITRiASObjects *pIObjs, /*[in, optional, defaultvalue]*/ SAFEARRAY *pParams);
	STDMETHOD(ConstraintObjects)(/*[in]*/ ITRiASObjects *pObjs);

protected:
// Erzeugen und initialisieren eines neuen TRiASObjects- Objektes
	HRESULT MakeNewObjects (BSTR bstrName, REFCLSID rClsId, OBJECTSCOLLECTIONTYPE rgType, ITRiASObjects **ppIObjs) throw(_com_error)
	{
	WTRiASObjectsOperations ObjOper (CLSID_TRiASObjectsOperations);		// throws hr

		return ObjOper -> MakeNewObjects(m_pIParent, bstrName, CComBSTR(CIID(rClsId).ProgID().c_str()), rgType, ppIObjs);
	}
	HRESULT GetSearchFeature (SAFEARRAY *pParams, ITRiASFeature **ppIFeat, ITRiASObjects **ppIObjs);

private:
// data members
	CComPtr<IDispatch> m_Application;
	IDispatch *m_pIParent;

	WEnumWTRiASObjects m_Enum;
	ITRiASObjectsCollectionCallback *m_pICallback;
};

///////////////////////////////////////////////////////////////////////////////
// Hilfsobjekte für Rechercheoperationen

typedef __InEnumIterator<ITRiASObjects, ITRiASObjectsCollection> InEnumObjsColl;
DefineSmartInterface(TRiASSearchObjects);

// Die Klasse 'CEnumConsiderSearch' kann z.B. in folgenden Szenarios eingesetzt werden
// 		for_each(InEnumObjsColl(m_ObjectsDefs), InEnumObjsColl(), 
//				 CEnumConsiderSearch(bstrCommand, pParams));
// In diesem Fall werden sämtliche Objektklassen der ObjectsDefs-Collection befragt, ob
// eine evtl. die Recherche durchführen kann.

class CEnumConsiderSearch 
{
private:
	CEnumConsiderSearch();		// do not use explicitly

public:
	CEnumConsiderSearch (BSTR bstrCommand, SAFEARRAY *pParams)
		: m_bstrCommand(bstrCommand), m_pParams(pParams)
	{
	}

	bool operator() (ITRiASObjects *pIObjs) throw(_com_error)
	{ 
		return ConsiderSearch (pIObjs, m_bstrCommand, m_pParams);
	}

	static bool ConsiderSearch (ITRiASObjects *pIObjs, BSTR bstrCmd, SAFEARRAY *pParams) throw(_com_error)
	{
		_ASSERTE(NULL != pIObjs);

	WTRiASSearchObjects SearchObjs;

	// zuerst versuchen, ob Objektklasse es direkt kann
		if (SUCCEEDED(pIObjs -> QueryInterface (SearchObjs.ppi())))
		{
			THROW_FAILED_HRESULT(SearchObjs -> ConsiderSearch (bstrCmd, pParams));
			return true;
		}
		return false;	// Recherche nicht unterstützt
	}

private:
	CComBSTR m_bstrCommand;
	SAFEARRAY *m_pParams;
};

// Die Klasse 'CEnumSearchObjs' kann z.B. in folgenden Szenarios eingesetzt werden
// 		for_each(InEnumObjsColl(m_ObjectsDefs), InEnumObjsColl(), 
//				 CEnumSearchObjs(bstrCommand, vObjProp, pParams, ObjsOut));
// In diesem Fall werden sämtliche Objektklassen der ObjectsDefs-Collection behandelt.
class CEnumSearchObjs 
{
private:
	CEnumSearchObjs();		// do not use explicitly

public:
	CEnumSearchObjs (BSTR bstrCommand, SAFEARRAY *pParams, ITRiASObjects *pIObjs)
		: m_bstrCommand(bstrCommand), m_pParams(pParams), m_ObjsOut(pIObjs)
	{
		_ASSERTE(m_ObjsOut.IsValid());
	}

	bool operator() (ITRiASObjects *pIObjs) throw(_com_error)
	{
		return SearchObjects (pIObjs, m_bstrCommand, m_pParams, m_ObjsOut);
	}

	static bool SearchObjects (
		ITRiASObjects *pIObjs, BSTR bstrCmd, SAFEARRAY *pParams, ITRiASObjects *pIOut) throw(_com_error)
	{
		_ASSERTE(NULL != pIObjs);

	WTRiASSearchObjects SearchObjs;

	// versuchen, ob Objektklasse es direkt kann; !!außen läuft boolop_and, also *immer* true zurück damit es weitergeht
		if (FAILED(pIObjs -> QueryInterface (SearchObjs.ppi())) ||
			S_OK != SearchObjs -> ConsiderSearch (bstrCmd, pParams)) 
		{
			return true;
		}

	// Feature evtl. aus einer anderen Objektklasse, dann ok
	HRESULT hr = SearchObjs -> SearchObjects (bstrCmd, pIOut, pParams);

		if (FAILED(hr) && TRIASDB_E_UNKNOWN_FEATURE != hr)
		{
			THROW_FAILED_HRESULT(hr);
		}
		return true;		// ansonsten weitermachen
	}

private:
	CComBSTR m_bstrCommand;
	SAFEARRAY *m_pParams;
	WTRiASObjects m_ObjsOut;
};

#endif // !defined(_TRIASOBJECTSCOLLECTION_H__48172D66_AB72_11D1_858D_00600875138A__INCLUDED_)
