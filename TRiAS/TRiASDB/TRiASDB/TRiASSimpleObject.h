///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASSimpleObject.h | Declaration of the <c CTRiASSimpleObject> class

#if !defined(_TRIASSIMPLEOBJECT_H__90378E25_C54C_11D1_85D2_00600875138A__INCLUDED_)
#define _TRIASSIMPLEOBJECT_H__90378E25_C54C_11D1_85D2_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////////////////
// Datenbank-support
#include <NativeObject.h>

using namespace trias_nativeobject;

#if defined(_USE_CLASSFACTORY_CACHE)
///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#include <Com/ClassFactoryCache.h>
typedef CClassFactoryCache<&CLSID_TRiASObject> CObjectFactory;
extern CObjectFactory MakeObjects;
#endif // defined(_USE_CLASSFACTORY_CACHE)

/////////////////////////////////////////////////////////////////////////////
// CTRiASSimpleObject
class ATL_NO_VTABLE CTRiASSimpleObject : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CTRiASSimpleObject, &CLSID_TRiASSimpleObject, &IID_ITRiASSimpleObject>,
	public ISupportErrorInfo,
	public ITRiASObjectCallback,
	public IPersistStreamInit,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASSimpleObject>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IDispatchImpl<ITRiASSimpleObject, &IID_ITRiASSimpleObject, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef CComCoClass<CTRiASSimpleObject, &IID_ITRiASObject> base_t;

	CTRiASSimpleObject()
		: m_lONr(0L), m_fIsInitialized(false), 
		  m_fIsDirty(false), m_fHasFeatures(false), m_fHasGeoFeatures(false) 
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASSimpleObject)

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASSimpleObject);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSIMPLEOBJECT)

	DECLARE_AGGREGATE_EX_SUPPORT()
	BEGIN_COM_MAP(CTRiASSimpleObject)
		COM_INTERFACE_ENTRY(ITRiASSimpleObject)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASObjectCallback)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASObject, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IConnectionPointContainer, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)

		COM_INTERFACE_ENTRY_DUMPOBJECT()

	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
#if defined(_USE_CLASSFACTORY_CACHE)
		RETURN_FAILED_HRESULT(MakeObjects.CreateInstance (m_BaseUnk.ppi(), GetControllingUnknown()));
#else
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASObject, CLSCTX_ALL, GetControllingUnknown()));
#endif // defined(_USE_CLASSFACTORY_CACHE)

	WTRiASObject BaseObj;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObj.ppi()));
		return BaseObj -> putref_ObjectCallback(this);
	}
	void FinalRelease (void);

// Funktionen für das ErrorHandling
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASSimpleObject)
		{ 
			CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
			return base_t::Error (str, riid, hr); 
		}
	HRESULT Error (LPCTSTR pcText, HRESULT hr, REFIID riid = IID_ITRiASSimpleObject)
		{
			return base_t::Error (pcText, riid, hr); 
		}

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASObjectCallback
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(SetupObject)(/*[in,optional,defaultvalue]*/ SETUPOBJECTMODE rgMode);
	STDMETHOD(SetupFeatures)(/*[in,optional,defaultvalue]*/ SETUPFEATURESMODE rgMode);
	STDMETHOD(OnDelete)();
	STDMETHOD(OnChanging)(/*[in]*/ CHANGEDOBJECT rgWhat, /*[in]*/ VARIANT vNewValue, /*[out, retval]*/ VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(/*[in]*/ CHANGEDOBJECT rgWhat, /*[in]*/ VARIANT vOldValue);
	STDMETHOD(OnFinalRelease)();

// ITRiASSimpleObject
public:
	STDMETHOD(InitTarget)(/*[in]*/ INT_PTR lONr, /*[in]*/ OBJECTTYPE dwType, /*[in]*/ INT_PTR lIdent, /*[in]*/ INT_PTR hObjs, /*[in,out]*/ INT_PTR *phObj);
	STDMETHOD(get_LocalHandle)(/*[out, retval]*/ INT_PTR *pHandle);
	STDMETHOD(get_RelatedObject)(/*[out, retval]*/ ITRiASObject **pIObj);
	STDMETHOD(put_RelatedObject)(/*[in]*/ ITRiASObject *pIObj);

protected:
	HRESULT RetrieveDBHandle (HPROJECT *phPr)
	{
		COM_TRY {
		WDispatch Parent;

			THROW_FAILED_HRESULT(WTRiASObject(m_BaseUnk) -> get_Parent (Parent.ppi()));
			THROW_FAILED_HRESULT(WTRiASDatabase(Parent) -> get_Handle ((INT_PTR *)phPr));

		} COM_CATCH;
		return S_OK;
	}
	HRESULT EnsureFeatures(VARIANT_BOOL fForceSetup);

// Enumeration der abhängigen Objekte
	class CEnumRelatedObjectCallback
	{
	public:
		CEnumRelatedObjectCallback() : lONr(NULL), iRelType(0) {}
		
		INT_PTR lONr;
		int iRelType;
	};
	static HRESULT CALLBACK EnumRelatedObjectCallBack (INT_PTR lObj, int iRelType, UINT_PTR dwData);


private:
	bool m_fIsInitialized;
	bool m_fIsDirty;
	bool m_fHasFeatures;
	bool m_fHasGeoFeatures;

	INT_PTR m_lONr;						// Objektnummer
	WUnknown m_BaseUnk;					// aggregiertes Objekt
};

/////////////////////////////////////////////////////////////////////////////
// Initialisierungsobject
#include "GenObjectMap.h"

/////////////////////////////////////////////////////////////////////////////
// 

class CInitializeSimpleObject :
	public binary_initialize<WTRiASObject>
{
private:
	INT_PTR m_lIdent;		// wirklicher Identifikator in der GeoDB
	INT_PTR m_hObjs;		// vergebene Zugriffsnummer (kann u.U. verschieden von m_lIdent sein)
	OBJECTTYPE m_rgType;
	WDispatch m_App;
	WDispatch m_Parent;

public:
	CInitializeSimpleObject (IDispatch *pIApp, IDispatch *pIParent, INT_PTR lIdent, INT_PTR hObjs, OBJECTTYPE rgType)
		: m_App(pIApp), m_Parent(pIParent), m_lIdent(lIdent), m_hObjs(hObjs), m_rgType(rgType)
	{}

	HRESULT operator() (binary_inititialize_target Obj, INT_PTR &rlONr, INT_PTR &rhObj, bool fFullInit)
	{
		if (fFullInit) {
			COM_TRY {
				THROW_FAILED_HRESULT(WPersistStreamInit(Obj) -> InitNew());

				THROW_FAILED_HRESULT(Obj -> put_Application (m_App));
				THROW_FAILED_HRESULT(Obj -> put_Parent (m_Parent));

			WTRiASSimpleObject SimpleObj(Obj);

				THROW_FAILED_HRESULT(SimpleObj -> InitTarget (rlONr, m_rgType, m_lIdent, m_hObjs, &rhObj));
				if (NULL == rlONr) {
				// für neu erzeugtes Objekt das GeoDB-Handle rausliefern
					THROW_FAILED_HRESULT(SimpleObj -> get_LocalHandle (&rlONr));
				}

			} COM_CATCH;
			return S_OK;
		} 
		else if (NULL == rhObj) 
			rhObj = rlONr;

		return S_FALSE;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Versionen des PersistStream-Formates
const long SIMPLEOBJECT_SIGNATURE = 0x4A424F54L;	// "TOBJ"
const long SIMPLEOBJECT_VERSION_MINOR_MASK = 0xff;
const long SIMPLEOBJECT_VERSION_100 = 0x0100L;
const long LASTKNOWN_SIMPLEOBJECT_VERSION = SIMPLEOBJECT_VERSION_100;

#endif // !defined(_TRIASSIMPLEOBJECT_H__90378E25_C54C_11D1_85D2_00600875138A__INCLUDED_)
