///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASDatabase.h | Declaration of the <c CTRiASDatabase> and 
// <o TRiASCompatibleDatabase> classes

#if !defined(_TRIASDATABASE_H__910C1739_6680_11D1_972F_00A024D6F582__INCLUDED_)
#define _TRIASDATABASE_H__910C1739_6680_11D1_972F_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"					// main symbols

#include <Com/OleItemContainerSupport.h>

#include <NativeView.h>
#include <NativeIdent.h>

#include "CPTRiASPropertyEvents.h"		// connection point

#include "ActDB.h"
#include "TRiASProperties.h"
#include "PropertySupport.h"
#include "PropertyBase.h"
//#include "PropSheetExt.h"

#import "tlb/Helper.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") \
	exclude("IParseStringPairs2")

using namespace trias_nativeview;
using namespace trias_nativeident;

/////////////////////////////////////////////////////////////////////////////
//
class ATL_NO_VTABLE CTRiASDatabaseBase : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public IOleClientSite,
	public COleItemContainerSupport<CTRiASDatabaseBase>,
	public CManagePropertySupportWithDefaultValues<CTRiASDatabaseBase>,
	public CManagePropertyBase<CTRiASDatabaseBase>,
	public ITRiASPropertyCallback,
	public CProxyITRiASPropertyEvents<CTRiASDatabaseBase>,
	public IConnectionPointContainerImpl<CTRiASDatabaseBase>,
	public IDispatchImpl<ITRiASSearchObjects, &IID_ITRiASSearchObjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASAccessDatabase, &IID_ITRiASAccessDatabase, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASDatabase, &IID_ITRiASDatabase, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public ICookieHelperEvents
{
public:
	CTRiASDatabaseBase()
		: m_hPr(NULL), m_hPrPbd(NULL), 
		  m_fIsReadOnly(false), m_fIsTemporary(false), m_fMustSaveLastCookie(false),
		  m_dwRegROT(0L), m_dwRegROTAll(0L),
		  m_lSemModCTF(0L),
		  m_bstrName(g_cbNil), m_bstrLocale(g_cbNil), m_bstrSource(g_cbNil),
		  m_dwCookieHolderCookie(0L)
	{
	}

	static HRESULT WINAPI UpdateRegistry (BOOL bRegister, UINT uiRes);
	BEGIN_COM_MAP(CTRiASDatabaseBase)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASDatabase)
		COM_INTERFACE_ENTRY(ITRiASAccessDatabase)
		COM_INTERFACE_ENTRY(ITRiASSearchObjects)
		COM_INTERFACE_ENTRY(ITRiASPropertyBase)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASPropertySupport)		// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(IOleClientSite)
		COM_INTERFACE_ENTRY(IOleItemContainer)			// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IOleContainer)				// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IParseDisplayName)			// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(ICookieHelperEvents)
	END_COM_MAP()

public:
// callback aus CManagePropertyBase<>
	HRESULT RefreshingProperties()
	{
		return ChangeMapEntry(CComBSTR(g_cbTRiASDataSource), 
            (INT_PTR)&CLSID_TRiASVariantProperty, PROPERTYSUPPORT_HASINITDATA, 
            vtMissing, GetDefaultValuesProc());
	}

public:
	BEGIN_PROPERTYSUPPORT_MAP(CTRiASDatabaseBase)
		PROPERTYSUPPORT_ENTRY_AGGR(g_cbCTFService, CLSID_TRiASCTFProperty)
		PROPERTYSUPPORT_ENTRY_AGGR(g_cbStgService, CLSID_TRiASStgProperty)
		PROPERTYSUPPORT_ENTRY(g_cbObjectsMap, CLSID_GenObjectMap)
		PROPERTYSUPPORT_ENTRY(g_cbObjectMap, CLSID_GenObjectMap)
		PROPERTYSUPPORT_ENTRY(g_cbFeatureMap, CLSID_GenObjectMap)
		PROPERTYSUPPORT_ENTRY(g_cbTRiASCSTransform, CLSID_TRiASAutoSaveProperty)
//		PROPERTYSUPPORT_ENTRY_INITFUNC(g_cbIdentBaseHdr, CLSID_TRiASVariantProperty, m_GetDefaultValuesThunk.GetProc())
		PROPERTYSUPPORT_ENTRY_DEFAULTINITFUNC(g_cbTRiASDataSource, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(g_cbSimpleFeatures, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(g_cbHasSimpleFeatures, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(g_cbSimpleGeoFeatures, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(g_cbHasSimpleGeoFeatures, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(g_cbActLookupWindow, CLSID_TRiASVariantProperty)
		PROPERTYSUPPORT_ENTRY(g_cbCoordExternPipe, CLSID_TRiASVariantProperty)
	END_PROPERTYSUPPORT_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASDatabaseBase)
		CONNECTION_POINT_ENTRY(IID_ITRiASPropertyEvents)
	END_CONNECTION_POINT_MAP()

	BEGIN_OLEITEMCONTAINERSUPPORT_MAP(CTRiASDatabaseBase)
		OLEITEMCONTAINERSUPPORT_ENTRYEX(g_cbMkObjectsDef, GetObjectsDef, ParseObjectsDef)
		OLEITEMCONTAINERSUPPORT_ENTRYEX(g_cbMkObjectDef, GetObjectDef, ParseObjectDef)
	END_OLEITEMCONTAINERSUPPORT_MAP()

// Defaultwerte für Properties
	BEGIN_PROPERTYSUPPORT_DEFAULTVALUE_MAP(CTRiASDatabaseBase)
		PROPERTYSUPPORT_DEFAULTVALUE_ENTRY(g_cbTRiASDataSource, VT_BOOL, 
            VARIANT_TRUE, PROPERTY_TYPE_System|PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_Hidden)
	END_PROPERTYSUPPORT_DEFAULTVALUE_MAP()

public:
	virtual HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASDatabase) = 0;
	virtual HRESULT Error (LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ITRiASDatabase) = 0;

	HRESULT FinalConstruct (void);
	void FinalRelease();

	IDispatch *GetDispatch() { return (ITRiASDatabase *)this; }

///////////////////////////////////////////////////////////////////////////////
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IOleClientSite
	STDMETHOD(SaveObject)();
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);
	STDMETHOD(GetContainer)(IOleContainer **ppContainer);
	STDMETHOD(ShowObject)();
	STDMETHOD(OnShowWindow)(BOOL fShow);
	STDMETHOD(RequestNewObjectLayout)();

// IOleItemContainer
	STDMETHOD(GetObject)(LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, void **ppvObject);
	STDMETHOD(GetObjectStorage)(LPOLESTR pszItem, IBindCtx *pbc, REFIID riid, void **ppvStorage);

// ITRiASDatabase
public:
	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

	STDMETHOD(get_TemporaryName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Temporary)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Temporary)(/*[in]*/ VARIANT_BOOL newVal);
//	STDMETHOD(get_Property)(BSTR Which, /*[out, retval]*/ ITRiASProperty * *pVal);
//	STDMETHOD(get_Properties)(/*[out, retval]*/ ITRiASProperties * *pVal);
//	STDMETHOD(put_Properties)(/*[in]*/ ITRiASProperties *pVal);

	HRESULT IsInitialized()
	{
		if (NULL != m_hPr) 
			return S_OK;
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	}

	STDMETHOD(get_IsDirty)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsDirty)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Handle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(get_VersionLong)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_Version)(BSTR *Version);

	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_StorageMode)(/*[out, retval]*/ DATABASESTORAGEMODE *pVal);

	STDMETHOD(OpenDatabase)(/*[in]*/ BSTR Name, /*[in, optional, defaultvalue]*/ VARIANT_BOOL Exclusive, /*[in, optional, defaultvalue]*/ VARIANT_BOOL ReadOnly, /*[in, optional, defaultvalue]*/ VARIANT_BOOL ModTrack, /*[in, optional, defaultvalue]*/ BSTR Source);
	STDMETHOD(OpenFilesAsDatabase)(/*[in]*/ IUnknown *pEnum, /*[in, optional, defaultvalue]*/ VARIANT_BOOL /*Exclusive*/, /*[in, optional, defaultvalue]*/ VARIANT_BOOL fReadOnly, /*[in, optional, defaultvalue]*/ VARIANT_BOOL /*ModTrack*/, /*[in, optional, defaultvalue]*/ BSTR Source);
	STDMETHOD(OpenStorageAsDatabase)(/*[in]*/ IUnknown *pIStorage, /*[in, optional, defaultvalue]*/ VARIANT_BOOL /*Exclusive*/, /*[in, optional, defaultvalue]*/ VARIANT_BOOL fReadOnly, /*[in, optional, defaultvalue]*/ VARIANT_BOOL /*ModTrack*/, /*[in, optional, defaultvalue]*/ BSTR Source);
	STDMETHOD(CreateDatabase)(/*[in]*/ BSTR Name, /*[in]*/ BSTR Locale, /*[in]*/ BSTR Source);
	STDMETHOD(CreateDatabaseFromFiles)(/*[in]*/ IUnknown *pIEnum, /*[in]*/ BSTR Locale, /*[in]*/ BSTR Source);
	STDMETHOD(CreateDatabaseOnStg)(/*[in]*/ IUnknown *pIUnk, /*[in]*/ BSTR Name, BSTR /*[in]*/ Locale, /*[in]*/ BSTR Source);
	STDMETHOD(Close)(void);

    STDMETHOD(get_CollatingOrder)(long *pCollatingOrder);
    STDMETHOD(get_Connect)(BSTR *Connect);
    STDMETHOD(get_Transactions)(VARIANT_BOOL *Transactions);

//    STDMETHOD(get_GAliasTable)(BSTR *AliasTableName);
//    STDMETHOD(get_GErrors)(GErrors **ppGErrors);
//    STDMETHOD(get_GRecordsets)(GRecordsets **ppGRecordsets);
//    STDMETHOD(get_GTableDefs)(GTableDefs **ppGTabledefs);
//    STDMETHOD(get_SQLConformance)(long *pSQLConformance);

    STDMETHOD(BeginTrans)(void);
    STDMETHOD(ClearModificationLog)(/*[in, optional, defaultvalue]*/ LONG Entry);
    STDMETHOD(CommitTrans)(void);
    STDMETHOD(Rollback)(void);

	STDMETHOD(ReLoad)(/*[in]*/ RELOADDATABASE rgWhat);
	STDMETHOD(RefreshChangesFromModificationLog)(/*[in]*/ ITRiASRefreshChangesCallback *pICallback);

//    STDMETHOD(CreateTableDef)(VARIANT Name, GTableDef **ppGTableDef);
//    STDMETHOD(GetExtension)(BSTR Name, IDispatch **ppGExtension);
//    STDMETHOD(OpenRecordset)(BSTR Name, VARIANT Type, VARIANT options, VARIANT SpatialOp, VARIANT SpatialGeometryFilter, VARIANT GeometryFieldName, GRecordset **ppGRecordset);

// ITRiASAccessDatabase
	STDMETHOD(get_Views)(/*[out, retval]*/ ITRiASViews **pVal);
	STDMETHOD(get_StartViewName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ObjectsDefs)(/*[out, retval]*/ ITRiASObjectsCollection **pVal);
	STDMETHOD(get_ObjectsDef)(/*[in]*/ VARIANT vItem, /*[in, optional, defaultvalue]*/ VARIANT_BOOL fCreate, /*[in, optional, defaultvalue]*/ BSTR Type, /*[out, retval]*/ ITRiASObjects * *pVal);
	STDMETHOD(get_Envelope)(/*[in]*/ ENVELOPETYPE rgType, IDispatch **pVal);
	STDMETHOD(get_ObjectCount)(long *pVal);
	STDMETHOD(get_AttachedCS)(/*[in]*/ BSTR bstrDbName, /*[out, retval]*/ BSTR *AssocCS);
	STDMETHOD(get_ConnectionFilter)(/*[out, retval]*/ ITRiASConnectionFilter **ppIGeom);
	STDMETHOD(put_ConnectionFilter)(/*[in]*/ ITRiASConnectionFilter *pIGeom);

// ITRiASSearchObjects
	STDMETHOD(ConsiderSearch)(/*[in]*/ BSTR bstrCommand, /*[in, optional, defaultvalue]*/ SAFEARRAY *pParams);
	STDMETHOD(SearchObjects)(/*[in]*/ BSTR bstrCommand, /*[in]*/ITRiASObjects *pIObjs, /*[in,optional]*/ SAFEARRAY *pParams);
	STDMETHOD(ConstraintObjects)(/*[in]*/ ITRiASObjects *pObjs);

// ITRiASPropertySupport
	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(FillWithProperties)(/*[in, out]*/ IUnknown **Props);
	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);
	STDMETHOD(PutValue)(/*[in]*/ BSTR Name, VARIANT newVal);
	STDMETHOD(GetValue)(/*[in]*/ BSTR Name, VARIANT *pVal);
	STDMETHOD(PutType)(/*[in]*/ BSTR Name, PROPERTY_TYPE newVal);
	STDMETHOD(GetType)(/*[in]*/ BSTR Name, PROPERTY_TYPE *pVal);
	STDMETHOD(GetValueAndType)(/*[in]*/ BSTR Name, /*[out]*/ VARIANT *pVal, /*[out]*/ PROPERTY_TYPE *pType);
	STDMETHOD(PutValueAndType)(/*[in]*/ BSTR Name, /*[in]*/ VARIANT Val, /*[in]*/ PROPERTY_TYPE Type);
	STDMETHOD(Refresh)(/*[in]*/ BSTR Name);

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

// ICookieHelperEvents
	STDMETHOD(CookieHolderInitialized)(/*[in]*/ BSTR Name, /*[in]*/ INT_PTR NewCookie);
	STDMETHOD(IssuedNextCookie)(/*[in]*/ BSTR Name, /*[in]*/ INT_PTR NextCookie);

// Pbd öffnen
	STDMETHOD(OpenMetaDatabase)(void) PURE;

// sonstige Member
	HRESULT Open (LPCTSTR pcName, IStorage *pIStg, bool &rfReadOnly, HPROJECT *phPr);
	HRESULT GetCompatibilityModeFromSource(BSTR bstrSrc, int *piCompatible, BOOL *pfCompressed = NULL);

	HRESULT GetProjectStorage (IStorage **ppIStg)
		{ _ASSERTE(NULL != m_hPr); return ::GetProjectStorage(m_hPr, ppIStg); }
	HRESULT GetMetaStorage (IStorage **ppIStg)
		{ _ASSERTE(NULL != m_hPrPbd); return ::GetProjectStorage(m_hPrPbd, ppIStg); }

// Enumeration aller Ansichten 
	struct CEnumViewCallback
	{
		CTRiASDatabaseBase *m_pDB;
		WTRiASViews m_Views;
	};
	static HRESULT CALLBACK EnumViewCallBack (LPCSTR pcKey, DWORD dwData);

// Enumeration aller Einträge einer Ansicht
	class CEnumViewEntryCallback
	{
	public:
		CEnumViewEntryCallback() 
		{
			m_pDB = NULL;
			m_pTarget = NULL;
			m_lObjVisMCode = 0;
			m_lLegVisMCode = 0;
			ZeroMemory (m_lScaleMCode, 4*sizeof(ULONG));
		}

		CTRiASDatabaseBase *m_pDB;
		WTRiASView m_View;
		CNativeView *m_pTarget;

		ULONG m_lObjVisMCode;		// MCode der objektbezogenen Visualisierung an der Objektklasse in der Ansicht
		ULONG m_lLegVisMCode;		// MCode der Legendeninfo an der Objektklasse/Objekt in der Ansicht
		ULONG m_lScaleMCode[4];		// MCodes Maßstabsbereiche einer Visualisierung an der Objektklasse in der Ansicht
	};
	static HRESULT CALLBACK EnumViewEntryCallBack (LONG lIdent, CNativeView::VisType rgType, DWORD dwData);
	HRESULT CorrectViewEntry (CNativeView &rView, LPCOLESTR pcoleEntry, ULONG &rulMCodeView, ULONG &rlMCode);

// Enumeration aller Identifikatoren der gesamten Datenbank
	struct CEnumIdentEntryCallback
	{
		CTRiASDatabaseBase *m_pDB;
		WTRiASObjectsCollection m_Coll;
	};
	static HRESULT CALLBACK EnumIdentCallBack (INT_PTR lIdent, DWORD dwTypes, UINT_PTR dwData);

protected:
// Moniker support
	HRESULT RenameDatabase (IMoniker *pIMk);
	HRESULT RenamingDatabase (void);
	HRESULT DatabaseSaved (void);
	HRESULT GetRunning (LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, void **ppvObject, bool fTestRunningOnly);
	HRESULT GetContainerMoniker (IMoniker **ppIMk);
	HRESULT GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk);

	HRESULT EnsureObjectsDefs (ITRiASObjectsCollection **pVal = NULL);

// OleItemContainerSupport
	HRESULT GetObjectsDef (LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT GetObjectDef (LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT ParseObjectsDef (LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut);
	HRESULT ParseObjectDef (LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut);

// RechercheHelper
	HRESULT GetSearchFeature (SAFEARRAY *pParams, ITRiASFeature **ppIFeat);

	HRESULT InitCoordSystemService();
	HRESULT ShutdownCoordSystemService();

	HRESULT InitConnectFilter();

// LastCookie verwalten
	HRESULT RetrieveLastCookie();
	HRESULT SaveLastCookie(BSTR bstrWhich = NULL);
//	bool MustSaveLastCookie();
	HRESULT ConnectCookieHolder();
	HRESULT DisconnectCookieHolder();

// ReLoad-Funktionalität
	HRESULT OnReLoadObjects();
	HRESULT OnReLoadEnvelope();
	HRESULT OnResetLookupWindow();
	HRESULT OnReLoadFeatures(RELOADDATABASE rgWhat);

protected:
// data members
	CComPtr<IDispatch> m_Application;
	CComPtr<IDispatch> m_Parent;

	CComBSTR m_bstrName;		// Name dieser Database
	CComBSTR m_bstrLocale;		// CollatingOrder etc.
	CComBSTR m_bstrSource;		// ConnectString (hier nicht verwendet)
	HPROJECT m_hPr;				// ProjektHandle der geöffneten DB
	HPROJECT m_hPrPbd;			// ProjektHandle der geöffneten zugehörigen PBD
	bool m_fIsReadOnly;			// ist schreibgeschützt geöffnet

	bool m_fIsTemporary;		// soll nach schließen gelöscht werden
	bool m_fMustSaveLastCookie;	// Cookies müssen gespeichert werden

	LONG m_lSemModCTF;			// Semaphore für Eventbehandlung
	WTRiASObjectsCollection m_ObjectsDefs;	// alle Objektklassen dieser Database

	WMoniker m_FileMK;			// Monikersupport
	DWORD m_dwRegROT;
	DWORD m_dwRegROTAll;

// CookieHolder 
	DWORD m_dwCookieHolderCookie;
	WDispatch m_ConnectFilter;
};

class ATL_NO_VTABLE CTRiASDatabase : 
	public CTRiASDatabaseBase
{
public:
// Defaultwerte für DBHeader-Properties
	BEGIN_PROPERTYSUPPORT_DEFAULTVALUE_MAP(CTRiASDatabase)
		PROPERTYSUPPORT_DEFAULTVALUE_ENTRY(g_cbTRiASDataSource, VT_BOOL, 
            VARIANT_TRUE, PROPERTY_TYPE_System|PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_Hidden)
	END_PROPERTYSUPPORT_DEFAULTVALUE_MAP()

// ITRiASDatabase
public:
	STDMETHOD(get_OpenedAsCopy)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_CouldOpenTarget)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Updatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_SchemaUpdatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ BSTR *pVal);

	STDMETHOD(SaveAs)(/*[in]*/ BSTR NewName);
	STDMETHOD(Save)();

protected:
	HRESULT CreateMetaDatabase (IStorage *pIStg, UINT uiResID = IDR_PBD013, BOOL fCompressed = FALSE, LPCTSTR pcName = NULL);
	HPROJECT OpenStoragePbd (IStorage *pIStg, bool &rfReadOnly) throw (_com_error &);
	HRESULT SaveMetaDatabase (void);

// Pbd behandlen
	STDMETHOD(OpenMetaDatabase)(void);
};

///////////////////////////////////////////////////////////////////////////////
// Normale *.ris -Datenbank in einer separaten Datei
class ATL_NO_VTABLE CTRiASDatabaseOnFile : 
	public CComCoClass<CTRiASDatabaseOnFile, &CLSID_TRiASDatabaseOnFile>,
	public IProvideClassInfo2Impl<&CLSID_TRiASDatabaseOnFile, &IID_ITRiASPropertyEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public CTRiASDatabase
{
public:
//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASDATABASE)
	static HRESULT WINAPI UpdateRegistry (BOOL bRegister)
		{ return CTRiASDatabaseBase::UpdateRegistry (bRegister, IDR_TRIASDATABASE); }

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASDatabaseOnFile)

	BEGIN_COM_MAP(CTRiASDatabaseOnFile)
		COM_INTERFACE_ENTRY(ITRiASDatabase)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASDatabaseBase)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
	END_COM_MAP()

public:
// ITRiASDatabase
	STDMETHOD(CreateDatabase)(/*[in]*/ BSTR Name, /*[in]*/ BSTR Locale, /*[in]*/ BSTR Source);

// Funktionen für das ErrorHandling
	typedef CComCoClass<CTRiASDatabaseOnFile, &CLSID_TRiASDatabaseOnFile> base_t;
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASDatabase)
		{ 
			CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
			return base_t::Error (str, riid, hr); 
		}
	HRESULT Error (LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ITRiASDatabase)
		{
			return base_t::Error (pcText, riid, hr); 
		}

protected:
	HRESULT CreateMainDatabase (BSTR Name, UINT uiResID, BOOL fCompressed, os_string &rStr, IStorage **ppIStg);
};

///////////////////////////////////////////////////////////////////////////////
// Normale *.ris -Datenbank in einem beliebigen IStorage
class ATL_NO_VTABLE CTRiASDatabaseOnStg : 
	public CComCoClass<CTRiASDatabaseOnStg, &CLSID_TRiASDatabaseOnStg>,
	public IProvideClassInfo2Impl<&CLSID_TRiASDatabaseOnStg, &IID_ITRiASPropertyEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IPersistStorage,
	public CTRiASDatabase
{
public:
	CTRiASDatabaseOnStg() : 
		m_StgMode(STGMODE_Unknown)
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASDATABASE)
	static HRESULT WINAPI UpdateRegistry (BOOL bRegister)
		{ return CTRiASDatabaseBase::UpdateRegistry (bRegister, IDR_TRIASDATABASEONSTG); }

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASDatabaseOnStg)

	BEGIN_COM_MAP(CTRiASDatabaseOnStg)
		COM_INTERFACE_ENTRY(ITRiASDatabase)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASDatabaseBase)
		COM_INTERFACE_ENTRY(IPersistStorage)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
	END_COM_MAP()

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStorage
	STDMETHOD(IsDirty)();
	STDMETHOD(InitNew)(IStorage *pStorage);
	STDMETHOD(Load)(IStorage *pStorage);
	STDMETHOD(Save)(IStorage *pStorage, BOOL fSameAsLoad);
	STDMETHOD(SaveCompleted)(IStorage *pStorage);
	STDMETHOD(HandsOffStorage)(void);

public:
// ITRiASDatabase
	STDMETHOD(OpenStorageAsDatabase)(/*[in]*/ IUnknown *pIStorage, /*[in, optional, defaultvalue]*/ VARIANT_BOOL /*Exclusive*/, /*[in, optional, defaultvalue]*/ VARIANT_BOOL fReadOnly, /*[in, optional, defaultvalue]*/ VARIANT_BOOL /*ModTrack*/, /*[in, optional, defaultvalue]*/ BSTR Source);
	STDMETHOD(CreateDatabaseOnStg)(/*[in]*/ IUnknown *pIUnk, /*[in]*/ BSTR Name, /*[in]*/ BSTR Locale, /*[in]*/ BSTR Source);
	STDMETHOD(SaveAs)(/*[in]*/ BSTR NewName);
	STDMETHOD(Save)();
	STDMETHOD(get_StorageMode)(/*[out, retval]*/ DATABASESTORAGEMODE *pVal);

// Funktionen für das ErrorHandling
	typedef CComCoClass<CTRiASDatabaseOnStg, &CLSID_TRiASDatabaseOnStg> base_t;
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASDatabase)
		{ 
			CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
			return base_t::Error (str, riid, hr); 
		}
	HRESULT Error (LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ITRiASDatabase)
		{
			return base_t::Error (pcText, riid, hr); 
		}

protected:
	HRESULT CreateMainDatabase (IStorage *pIStg, UINT uiResID, BOOL fCompressed);
	HRESULT GetSubStorage (BSTR bstrName, IStorage *pIStgBase, IStorage **ppIStg, BOOL fCreate = FALSE);

private:
	STGMODE m_StgMode;
};

///////////////////////////////////////////////////////////////////////////////
// Kompatibilitätswrapper für *.stb-Datenbanken
class ATL_NO_VTABLE CTRiASCompatibleDatabase : 
	public CComCoClass<CTRiASCompatibleDatabase, &CLSID_TRiASCompatibleDatabase>,
	public IProvideClassInfo2Impl<&CLSID_TRiASCompatibleDatabase, &IID_ITRiASPropertyEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public CTRiASDatabaseBase
{
public:
    CTRiASCompatibleDatabase()
    {
		AddMapEntry(CComBSTR(g_cbDataSourceGuid), (INT_PTR)&CLSID_TRiASAutoSaveProperty);
		AddMapEntry(CComBSTR("ObjName.3"), (INT_PTR)&CLSID_TRiASAutoSaveProperty);
		AddMapEntry(CComBSTR("Old Unique Ident"), (INT_PTR)&CLSID_TRiASAutoSaveProperty);
		AddMapEntry(CComBSTR("LastObjsCookie"), (INT_PTR)&CLSID_TRiASAutoSaveProperty);
		AddMapEntry(CComBSTR("LastObjCookie"), (INT_PTR)&CLSID_TRiASAutoSaveProperty);
		AddMapEntry(CComBSTR("LastFeatCookie"), (INT_PTR)&CLSID_TRiASAutoSaveProperty);
    }

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCompatibleDatabase)

//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCOMPATIBLEDATABASE)
static HRESULT WINAPI UpdateRegistry (BOOL bRegister)
	{ return CTRiASDatabaseBase::UpdateRegistry (bRegister, IDR_TRIASCOMPATIBLEDATABASE); }

	BEGIN_COM_MAP(CTRiASCompatibleDatabase)
		COM_INTERFACE_ENTRY(ITRiASDatabase)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASDatabaseBase)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
	END_COM_MAP()

// Defaultwerte für DBHeader-Properties
public:
	BEGIN_PROPERTYSUPPORT_DEFAULTVALUE_MAP(CTRiASCompatibleDatabase)
		PROPERTYSUPPORT_DEFAULTVALUE_ENTRY(g_cbTRiASDataSource, VT_BOOL, 
            VARIANT_TRUE, PROPERTY_TYPE_System|PROPERTY_TYPE_ReadOnly|PROPERTY_TYPE_Hidden)
	END_PROPERTYSUPPORT_DEFAULTVALUE_MAP()

// ITRiASDatabase
	STDMETHOD(CreateDatabase)(/*[in]*/ BSTR Name, /*[in]*/ BSTR Locale, /*[in]*/ BSTR Source);
	STDMETHOD(SaveAs)(/*[in]*/ BSTR NewName);
	STDMETHOD(Save)();
	STDMETHOD(get_OpenedAsCopy)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_CouldOpenTarget)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Updatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_SchemaUpdatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ BSTR *pVal);

// ITRiASPropertySupport
//	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
//	STDMETHOD(FillWithProperties)(/*[in, out]*/ IUnknown **Props);
//	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);
//	STDMETHOD(PutValue)(/*[in]*/ BSTR Name, VARIANT newVal);
//	STDMETHOD(GetValue)(/*[in]*/ BSTR Name, VARIANT *pVal);
//	STDMETHOD(PutType)(/*[in]*/ BSTR Name, PROPERTY_TYPE newVal);
//	STDMETHOD(GetType)(/*[in]*/ BSTR Name, PROPERTY_TYPE *pVal);
//	STDMETHOD(GetValueAndType)(/*[in]*/ BSTR Name, /*[out]*/ VARIANT *pVal, /*[out]*/ PROPERTY_TYPE *pType);
//	STDMETHOD(PutValueAndType)(/*[in]*/ BSTR Name, /*[in]*/ VARIANT Val, /*[in]*/ PROPERTY_TYPE Type);
//	STDMETHOD(Refresh)(/*[in]*/ BSTR Name);

// Funktionen für das ErrorHandling
	typedef CComCoClass<CTRiASCompatibleDatabase, &CLSID_TRiASCompatibleDatabase> base_t;
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASDatabase)
		{ 
			CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
			return base_t::Error (str, riid, hr); 
		}
	HRESULT Error (LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ITRiASDatabase)
		{
			return base_t::Error (pcText, riid, hr); 
		}

protected:
	HRESULT CreateMainDatabase (BSTR Name, os_string &rStr);
	HRESULT CreateMetaDatabase (LPCTSTR pcName);
	HRESULT SaveMetaDatabase (void);

// Pbd behandlen
	STDMETHOD(OpenMetaDatabase)(void);
};

#endif // !defined(_TRIASDATABASE_H__910C1739_6680_11D1_972F_00A024D6F582__INCLUDED_)
