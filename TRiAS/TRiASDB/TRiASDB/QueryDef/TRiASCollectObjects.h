// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.07.99 20:43:50 
//
// @doc
// @module TRiASCollectObjects.h | Declaration of the <c CTRiASCollectObjects> class

#if !defined(_TRIASCOLLECTOBJECTS_H__B2C0DED0_33D2_11D3_94FA_0080C786297B__INCLUDED_)
#define _TRIASCOLLECTOBJECTS_H__B2C0DED0_33D2_11D3_94FA_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "Strings.h"

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASObjects);				// WTRiASObjects
DefineSmartInterface(Moniker);					// WMoniker

///////////////////////////////////////////////////////////////////////////////
// Geeigneter Enumerator für Moniker's

///////////////////////////////////////////////////////////////////////////////
// FMTID fürs Speichern/Laden
// {E7652D69-EBA0-4067-BBBD-7B2EFE8B7619}
extern "C" const IID __declspec(selectany) FMTID_EnumMoniker = 
	{0xe7652d69,0xeba0,0x4067,{0xbb,0xbd,0x7b,0x2e,0xfe,0x8b,0x76,0x19}};

// {B1E7F232-9DCE-45D3-9661-1AF4F002F131}
extern "C" const IID __declspec(selectany) IID_IEnumMonikerEx = 
	{0xb1e7f232,0x9dce,0x45d3,{0x96,0x61,0x1a,0xf4,0xf0,0x02,0xf1,0x31}};

DefineEnumerator2(WMoniker, IID_IEnumMonikerEx);			// NEnumWMoniker
DefineSmartEnumerator2(WMoniker, IID_IEnumMonikerEx);		// WEnumWMoniker

// Enumerator soll FindItem und RemoveItem über CComBSTR haben (s. iterenum.h)
//typedef IEnumEx<CComBSTR, WMoniker> IEnumMonikerEx;

///////////////////////////////////////////////////////////////////////////////
// Die folgenden typedef's verwenden die in <ospace/com/iterenum.h> definierten Templates,
// um einen Enumerator zu definieren, der neben der Standardfunktionalität (Reset, Skip, Clone etc.)
// zusätzlich die Möglichkeit bietet, schnell an einzelne Einträge heranzukommen (hier über den
// Bezeichner des ViewItems, s.a. 'bool operator< (const CComBSTR &, const CComBSTR &)' ).

// Helperklasse zur Verpackung des CLSID's als Klasse
//DefineEnumIIDWrapper2(WMoniker, IID_IEnumMonikerEx);		// CIID_WMonikerEnum

// der eigentliche Enumerator
//typedef map<CComBSTR, WMoniker, less<CComBSTR> > CEnumMonikerMap;	// unterliegende Map
//typedef __Enumerator<WMoniker, CIID_WMonikerEnum, CEnumMonikerMap, 
//			__EnumeratorBaseTarget<WMoniker, CEnumMonikerMap, IEnumMonikerEx> > 
//		TEnumWMoniker;

// Wrapper für Interface, über welches der definierte Enumerator ansprechbar ist
//typedef __Interface<IEnumMonikerEx, CIID_WMonikerEnum, CComPtr<IEnumMonikerEx> > WEnumWMoniker;

/////////////////////////////////////////////////////////////////////////////
// CTRiASCollectObjects
typedef map<INT_PTR, INT_PTR, less<INT_PTR> > CObjHandleMap;

class ATL_NO_VTABLE CTRiASCollectObjects : 
	public ITRiASObjectsCallback,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CErrSupport<CTRiASCollectObjects, &CLSID_TRiASCollectObjects>,
	public CComCoClass<CTRiASCollectObjects, &CLSID_TRiASCollectObjects>,
	public IPersistStreamInit,
	public ITRiASObjectEvents,
	public IDispatchImpl<ITRiASCollectObjects, &IID_ITRiASObjectsEx, &LIBID_TRiASDB,
		TYPELIB_TRiASDB_VERSION_MAJOR, TYPELIB_TRiASDB_VERSION_MINOR>
{
public:
	CTRiASCollectObjects() :
		m_lInitData(0), m_fIsDirty(false), m_rgInitState (INITSTATE_NotInitialized),
		m_pObjs(NULL)
	{
		ResetCounters();
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCollectObjects)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCOLLECTOBJECTS)
	DECLARE_AGGREGATE_EX_SUPPORT();

	BEGIN_COM_MAP(CTRiASCollectObjects)
		COM_INTERFACE_ENTRY(ITRiASCollectObjects)
		COM_INTERFACE_ENTRY(ITRiASObjectsEx)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASObjectsCallback)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(ITRiASObjectEvents)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASObjects, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IConnectionPointContainer, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeatureEvents, m_BaseUnk.p)

		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)		// alles andere nicht gesondert behandeln
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASObjects, CLSCTX_ALL, GetControllingUnknown()));

	WTRiASObjects BaseObjs;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObjs.ppi()));
		RETURN_FAILED_HRESULT(BaseObjs -> putref_ObjectsCallback(this));
		RETURN_FAILED_HRESULT(CreateNewEnum (m_Enum.ppi()));
		return S_OK;
	}
	void FinalRelease (void)
	{
		DELETE_OBJ(m_pObjs);
		m_Enum.Assign(NULL);	// Enumerator freigeben
		m_BaseUnk.Assign(NULL);
	}
	IDispatch *GetDispatch() { return static_cast<ITRiASObjectsEx *>(this); }

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASObjectsCallback
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(SetupFeatures)(/*[in,optional,defaultvalue]*/ SETUPFEATURESMODE rgMode);
	STDMETHOD(SetupObjects)(/*[in]*/ SETUPOBJECTSMODE rgMode);

	STDMETHOD(OnDelete)(/*[in]*/ INT_PTR hObj);
	STDMETHOD(OnChanging)(/*[in]*/ CHANGEDOBJECTS rgWhat, /*[in]*/ VARIANT vNewValue, /*[out, retval]*/ VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(/*[in]*/ CHANGEDOBJECTS rgWhat, /*[in]*/ VARIANT vOldValue);
	STDMETHOD(OnCreate)(/*[in]*/ BSTR Name, /*[in]*/ BSTR Type, /*[in]*/ OBJECTTYPE rgType, /*[out, retval]*/ ITRiASObject **ppIObj);
	STDMETHOD(OnAdd)(/*[in]*/ ITRiASObject *pIObj, /*[in]*/ CLASSIFYMODE rgMode);
	STDMETHOD(OnRemove)(/*[in]*/ ITRiASObject *pIObj);
	STDMETHOD(MapFeatureHandle)(/*[in]*/ VARIANT vNameOrHandle, /*[out,retval]*/ VARIANT *pvNewNameOrHandle);
	STDMETHOD(OnFinalRelease)();

// ITRiASObjectsEx
	STDMETHOD(get_Count)(/*[in]*/ OBJECTTYPE rgType, /*[out, retval]*/ long *plObjCnt);
	STDMETHOD(get_LocalHandle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(get_Handles)(/*[in]*/ long lCount, /*[in, out, size_is(Count)]*/INT_PTR *plObjs);

// ITRiASCollectObjects
	STDMETHOD(GetMappedObjectHandle)(/*[in]*/ INT_PTR hObjOrig, /*[out, retval]*/ INT_PTR *phObjMapped);

// ITRiASObjectEvents
	STDMETHOD(CreatingObject)(BSTR Name, VARIANT_BOOL *pVal);
	STDMETHOD(ObjectToCreate)(BSTR Name);
	STDMETHOD(ObjectCreated)(IDispatch *pIObj);
	STDMETHOD(ModifyingObject)(IDispatch *pIObj, VARIANT_BOOL *pVal);
	STDMETHOD(ObjectToModify)(IDispatch *pIObj);
	STDMETHOD(ObjectModified)(BSTR Name);
	STDMETHOD(DeletingObject)(IDispatch *pIObj, VARIANT_BOOL *pVal);
	STDMETHOD(ObjectToDelete)(IDispatch *pIObj);
	STDMETHOD(ObjectDeleted)(BSTR Name);

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

	HRESULT CreateNewEnum (IEnum<WMoniker> **ppIEnum)
	{
		ATLTRY(*ppIEnum = new NEnumWMoniker());	// Konstruktor hinterläßt RefCnt==1
		return (NULL == *ppIEnum) ? E_OUTOFMEMORY : S_OK;
	}
	HRESULT InitEnum (IEnum<WMoniker> *pTarget)
	{ 
		return pTarget -> Clone (m_Enum.ppi()); 
	}

// Faking collection members for {Load|Save}EnumeratedItems[Ex]
	HRESULT Item (VARIANT vName, IMoniker **ppIMk);
	HRESULT _Add (IMoniker *pIMk, VARIANT_BOOL fFullAdd);
	HRESULT Remove (VARIANT vName);
	HRESULT _NewEnum (IUnknown **ppIEnum);

protected:
	HRESULT OnChangedName();
	HRESULT OnChangedDescription();
	HRESULT OnChangedOKS();
	HRESULT OnChangedHandle();
	HRESULT OnChangedTypes();
	HRESULT OnChangedROMode();

	HRESULT OnLoadObjects();
	HRESULT EnsureObjectCount();

	HRESULT EnsureLocalHandleCont(bool fClearMap = false);
	void ResetCounters(bool fResetAll = false)
	{
		ZeroMemory (m_lCounts, sizeof(m_lCounts));
	}
	HRESULT IncrementObjectCount (ITRiASObject *pIObj);
	HRESULT DecrementObjectCount (ITRiASObject *pIObj);

// ITRiASCollectObjects
public:

private:
	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASObjects)
	LONG m_lInitData;
	bool m_fIsDirty;

	WEnumWMoniker m_Enum;			// Liste der ObjektMoniker

// Initialisierungszustand dieser Collection
	enum INITSTATE {
		INITSTATE_NotInitialized = 0x00,
		INITSTATE_Initialized = 0x01,
		INITSTATE_CountsInitialized = 0x02,
		INITSTATE_EnumLoaded = 0x04,
		INITSTATE_ObjectsLoaded = 0x08,
	};
	INITSTATE m_rgInitState;

	CObjHandleMap *m_pObjs;			// Objektnummern zu PseudoHandles
	long m_lCounts[4];

// Map, welche die Eventregistrierung bei den Objektklassen koordiniert
	class CRegisteredObjectClasses :
		public map<INT_PTR, pair<ULONG, DWORD>, less<INT_PTR> >
	{
	public:
		CRegisteredObjectClasses() {}
		~CRegisteredObjectClasses() {}

		HRESULT Remove (INT_PTR hObjs)
		{
		iterator it = find (hObjs);

			if (it != end()) {
				if (0 == --((*it).second.first)) {
					_ASSERTE(0L != (*it).second.second);	// Cookie muß gegeben sein

				WTRiASObjects Objs;
				WTRiASObjectHandleMap Map(((CQueryDefExtension *)g_pTE) -> GetObjectsMap());

					RETURN_FAILED_HRESULT(Map -> GetObject (hObjs, Objs.ppu()));
					RETURN_FAILED_HRESULT(AtlUnadvise (Objs, IID_ITRiASObjectEvents, (*it).second.second));
					erase (it);
				}
				return S_OK;
			}
			return S_FALSE;
		}
		HRESULT Insert (IUnknown *pThisObjs, INT_PTR hObjs)
		{
		iterator it = find (hObjs);

			if (it == end()) {
			DWORD dwCookie = 0L;
			WTRiASObjects Objs;
			WTRiASObjectHandleMap Map(((CQueryDefExtension *)g_pTE) -> GetObjectsMap());

				RETURN_FAILED_HRESULT(Map -> GetObject (hObjs, Objs.ppu()));
				RETURN_FAILED_HRESULT(AtlAdvise (Objs, pThisObjs, IID_ITRiASObjectEvents, &dwCookie));

				_ASSERTE(0L != dwCookie);
				insert (value_type(hObjs, referent_type(1, dwCookie)));
			} else
				++((*it).second.first);

			return S_OK;
		}
	};
	CRegisteredObjectClasses m_Classes;
};

///////////////////////////////////////////////////////////////////////////////
// Versionen des PersistStream-Formates
const long COLLECTOBJECTS_SIGNATURE = 0x53424F43L;		// "COBS"
const long COLLECTOBJECTS_VERSION_MINOR_MASK = 0xff;
const long COLLECTOBJECTS_VERSION_100 = 0x0100L;
const long COLLECTOBJECTS_VERSION_101 = 0x0101L;
const long COLLECTOBJECTS_VERSION_102 = 0x0102L;		// Stream ist komprimiert (#HK000123)
const long COLLECTOBJECTS_VERSION_103 = 0x0103L;		// Typen und Objektzähler mitgespeichert (#HK000312)
const long COLLECTOBJECTS_VERSION_104 = 0x0104L;		// typespezifische Zähler mitgespeichert (#HK000312)
const long LASTKNOWN_COLLECTOBJECTS_VERSION = COLLECTOBJECTS_VERSION_104;

#endif // !defined(_TRIASCOLLECTOBJECTS_H__B2C0DED0_33D2_11D3_94FA_0080C786297B__INCLUDED_)
