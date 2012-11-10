// Interne Objekteigenschaften ------------------------------------------------
// File: INTOPROP.HXX

#if !defined(_INTOPROP_HXX)
#define _INTOPROP_HXX

#if !defined(_LPFNDESTROY_DEFINED)
#define _LPFNDESTROY_DEFINED
// Type for an object-destroyed callback
typedef void (FAR PASCAL *LPFNDESTROYED)(void);

#endif // _LPFNDESTROY_DEFINED

#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
#include <Atl/AtlCtlEx.h>
#include <Atl/AtlAggregate.h>

#include <TRiASDBDispIds.h>
#include <TrCatIds.h>

#include "LockFeatureTearOff.h"
#include "DispExImpl.h"

#import "tlb/TRiASUI.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids

///////////////////////////////////////////////////////////////////////////////
// Klasse, die TRiASLockFeature und PropertyPage implementiert
class ATL_NO_VTABLE CTRiASLockFeatureImplBase :
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISpecifyPropertyPagesExImpl<CTRiASLockFeatureImplBase>,
	public ITRiASLockFeatureUnk
{
public:
	CTRiASLockFeatureImplBase()
	{
	}
	~CTRiASLockFeatureImplBase() 
	{
	}

	BEGIN_COM_MAP(CTRiASLockFeatureImplBase)
		COM_INTERFACE_ENTRY(ITRiASLockFeatureUnk)
	END_COM_MAP()

///////////////////////////////////////////////////////////////////////////////
// PropertyPages für Editierung der Objekteigenschaft selbst
	BEGIN_PROPERTY_MAP_RUNTIME(CTRiASLockFeatureImplBase)
		PROP_ENTRY_EX("Feature", DISPID_LOCKEDFEATURE, CLSID_EditFeatureDlg, IID_ITRiASLockFeatureEx)
	END_PROPERTY_MAP()

	BEGIN_PROPERTY_MAP_DESIGN(CTRiASLockFeatureImplBase)
	END_PROPERTY_MAP()

	HRESULT GetAmbientUserMode (BOOL &rfUserMode) {	rfUserMode = TRUE; return S_OK; }	// immer RuntimeMap verwenden

// ITRiASLockFeatureUnk
	STDMETHODIMP get_Feature(INT_PTR lONr, VARIANT *pVal);
	STDMETHODIMP put_Feature(INT_PTR lONr, VARIANT newVal);
	STDMETHODIMP get_Name(BSTR *pVal);
	STDMETHODIMP get_Description(BSTR *pVal);
	STDMETHODIMP get_IsRO(INT_PTR lONr, VARIANT_BOOL *pVal);
	STDMETHODIMP UnlockFeature(INT_PTR lONr, VARIANT_BOOL fCommit);
	STDMETHODIMP LockFeature(INT_PTR Obj);
	STDMETHODIMP get_IsLocked(INT_PTR lONr, VARIANT_BOOL *pVal);

protected:
	HRESULT get_Feature (INT_PTR lONr, IUnknown *pIUnk, VARIANT *pVal);
	HRESULT put_Feature(INT_PTR lONr, IUnknown *pIUnk, VARIANT newVal);
	HRESULT get_IsRO (INT_PTR lONr, IUnknown *pIUnk, VARIANT_BOOL *pVal);
	HRESULT get_Name (IUnknown *pIUnk, BSTR *pVal);
	HRESULT get_Description (IUnknown *pIUnk, BSTR *pVal);

	HRESULT CommitFeature (INT_PTR lONr, IUnknown *pIUnk, VARIANT_BOOL fCommit);
	HRESULT UnlockFeature (INT_PTR lONr);

protected:
	class CLockData 
	{
	public:
		CLockData() : m_fIsDirty(false), m_fIsEvaluated(false) {}

		CComVariant m_vValue;
		bool m_fIsDirty;
		bool m_fIsEvaluated;
	};
	typedef map<INT_PTR, CLockData, less<INT_PTR> > CLockedObjs;
	CLockedObjs m_Objs;
};

class ATL_NO_VTABLE CTRiASLockFeatureStandAlone : 
	public CTRiASLockFeatureImplBase,
	public IInitInnerObject,
	public IDispatchExImpl<CTRiASLockFeatureStandAlone, ITRiASLockFeatureEx, 
		&IID_ITRiASLockFeatureEx, &LIBID_TRiASHelperLib, 
		TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>,
	public CComCoClass<CTRiASLockFeatureStandAlone, &CLSID_FakeTRiASLockFeature>
{
public:
	CTRiASLockFeatureStandAlone() {}
	~CTRiASLockFeatureStandAlone() {}

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_AGGREGATE_EX_SUPPORT()
	BEGIN_COM_MAP(CTRiASLockFeatureStandAlone)
		COM_INTERFACE_ENTRY(IInitInnerObject)
		COM_INTERFACE_ENTRY(ITRiASLockFeatureEx)
		COM_INTERFACE_ENTRY(IDispatchEx)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_AGGREGATE_HRESULT(IID_ISpecifyPropertyPages, m_Unk.p, S_FALSE)	// erstmal das inner object befragen
		COM_INTERFACE_ENTRY_IID(IID_ISpecifyPropertyPages, ISpecifyPropertyPagesExImpl<CTRiASLockFeatureImplBase>)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_Unk.p)
	END_COM_MAP()

	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_FAKETRIASLOCKFEATURE)
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASLockFeatureStandAlone)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		HR(m_members.PreDefineMember(CComBSTR(L"Feature"), fdexNameCaseInsensitive|fdexNameInternal, vtMissing, DISPID_LOCKEDFEATURE));
		HR(m_members.PreDefineMember(CComBSTR(L"IsRO"), fdexNameCaseInsensitive|fdexNameInternal, vtMissing, DISPID_LOCKEDISRO));
		return S_OK;
	}
	void FinalRelease()
	{
		m_Unk.Assign(NULL);
	}

// ITRiASLockFeatureUnk
	STDMETHODIMP UnlockFeature(INT_PTR lONr, VARIANT_BOOL fCommit);
	STDMETHODIMP get_Feature (INT_PTR lONr, VARIANT *pVal);
	STDMETHODIMP get_IsRO (INT_PTR lONr, VARIANT_BOOL *pVal);
	STDMETHODIMP get_Name (BSTR *pVal);
	STDMETHODIMP get_Description (BSTR *pVal);
	STDMETHODIMP put_Feature(INT_PTR lONr, VARIANT newVal)
	{
		return CTRiASLockFeatureImplBase::put_Feature(lONr, newVal);
	}
	STDMETHODIMP get_IsLocked(INT_PTR lONr, VARIANT_BOOL *pVal)
	{
		return CTRiASLockFeatureImplBase::get_IsLocked(lONr, pVal);
	}
	STDMETHODIMP LockFeature(INT_PTR lONr)
	{
		return CTRiASLockFeatureImplBase::LockFeature(lONr);
	}

// IInitInnerObject
	STDMETHOD(SetInnerObject)(/*[in]*/ IUnknown *pIInner, /*[in]*/ REFIID riid, /*[out, retval]*/ IUnknown **ppIOuter);

private:
	WUnknown m_Unk;
};
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für eine Objekteigenschaft
class ATL_NO_VTABLE CBaseObjectProperty : 
	public IObjectProperty3,
	public IPersistStream,
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
	public CTRiASLockFeatureImplBase
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
{
private:
	bool m_fReadOnly;
	bool m_fIsDirty;

protected:
	LPFNDESTROYED m_pfnDestroy;

	ResID m_resHelpID;
	ULONG m_ulCnt;
	string m_strName;

	bool FInit (const CBaseObjectProperty &rOP);		// Helper for Clone

public:
	void FinalRelease()
	{
		m_TearOff.Release();
	}
	typedef CLockFeatureTearOff<CBaseObjectProperty> tearoff_t;
	CComPtr<IUnknown> m_TearOff;

	DECLARE_GET_CONTROLLING_UNKNOWN()
	BEGIN_COM_MAP(CBaseObjectProperty)
		COM_INTERFACE_ENTRY(IObjectProperty)
		COM_INTERFACE_ENTRY(IPersistStream)
		COM_INTERFACE_ENTRY(IPersist)
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(ITRiASLockFeatureEx), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IDispatchEx), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_CACHED_TEAR_OFF(_ATL_IIDOF(IDispatch), tearoff_t, m_TearOff.p)
		COM_INTERFACE_ENTRY_IID(IID_ISpecifyPropertyPages, ISpecifyPropertyPagesExImpl<CTRiASLockFeatureImplBase>)
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
	END_COM_MAP()

	DECLARE_NO_REGISTRY()		// ObjProps waren früher nicht registriert

#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
// ITRiASLockFeature
	STDMETHOD(UnlockFeature)(INT_PTR lONr, /*[in]*/ VARIANT_BOOL fCommit);
	STDMETHOD(get_Feature)(INT_PTR lONr, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_IsRO)(INT_PTR lONr, /*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
//
public:
		CBaseObjectProperty (LPCSTR pcName, ResID resHelp, bool fReadOnly = true);
virtual	~CBaseObjectProperty (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID) PURE;

// *** IPersistStream methods ***
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten) PURE;

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// *** IObjectProperty3 specific functions ***
	STDMETHOD(SetWithUndo)(THIS_ LONG lONr, LPCSTR pcBuffer);

// sonstige Member
	void SetRO (bool fRO) { m_fReadOnly = fRO ? true : false; }
	bool GetRO (void) { return m_fReadOnly; }

	void SetName (LPCSTR pcName) { if (NULL != pcName) m_strName = pcName; }
	LPCSTR GetName (void) { return m_strName.c_str(); }
	string &GetNameStr (void) { return m_strName; }

	bool HasDeleteFcn (void) { return (NULL != m_pfnDestroy); }

	void SetDirty (bool fDirty) { m_fIsDirty = fDirty ? true : false; }
	bool GetDirty (void) { return m_fIsDirty ? true : false; }
};

#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Datenquelle liefert, aus der dieses Objekt stammt
class ATL_NO_VTABLE CObjPropDataSource : 
	public CBaseObjectProperty,
	public CComCoClass<CObjPropDataSource, &CLSID_ObjPropDataSource>
{
public:
	DECLARE_AGGREGATABLE(CObjPropDataSource)		// class factory
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjPropDataSource)
	
#if defined(_REGISTER_OBJECT_PROPERTIES)
	DECLARE_REGISTRY_RESOURCEID(IDR_OJPROP_DATASOURCE)
	BEGIN_CATEGORY_MAP(CObjPropDataSource)
		IMPLEMENTED_CATEGORY(CATID_TRiASObjectPropertyRO)
	END_CATEGORY_MAP()
#endif // defined(_REGISTER_OBJECT_PROPERTIES)

		CObjPropDataSource (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die die Beschreibung der Datenquelle liefert, aus der 
// dieses Objekt stammt
class ATL_NO_VTABLE CObjPropDataSourceDesc : 
	public CBaseObjectProperty,
	public CComCoClass<CObjPropDataSourceDesc, &CLSID_ObjPropDataSourceDesc>
{
public:
	DECLARE_AGGREGATABLE(CObjPropDataSourceDesc)		// class factory
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjPropDataSourceDesc)
	
#if defined(_REGISTER_OBJECT_PROPERTIES)
	DECLARE_REGISTRY_RESOURCEID(IDR_OJPROP_DATASOURCEDESC)
	BEGIN_CATEGORY_MAP(CObjPropDataSourceDesc)
		IMPLEMENTED_CATEGORY(CATID_TRiASObjectPropertyRO)
	END_CATEGORY_MAP()
#endif // defined(_REGISTER_OBJECT_PROPERTIES)

		CObjPropDataSourceDesc (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};
#endif // !_FORCE_LEGACY_CODE && _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
// Liefert Objektnummer als Zeichenkette 
class ATL_NO_VTABLE CObjPropONr : 
	public CBaseObjectProperty,
	public CComCoClass<CObjPropONr, &CLSID_ObjPropONr>
{
public:
	DECLARE_AGGREGATABLE(CObjPropONr)		// class factory
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjPropONr)
	
#if defined(_REGISTER_OBJECT_PROPERTIES)
	DECLARE_REGISTRY_RESOURCEID(IDR_OJPROP_OBJNR)
	BEGIN_CATEGORY_MAP(CObjPropONr)
		IMPLEMENTED_CATEGORY(CATID_TRiASObjectPropertyRO)
	END_CATEGORY_MAP()
#endif // defined(_REGISTER_OBJECT_PROPERTIES)

		CObjPropONr (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Objektnummer als Zeichenkette --------------------------------------
class ATL_NO_VTABLE CObjPropGUID : 
	public CBaseObjectProperty,
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
	public IPropertyInfo2,
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
	public CComDualImpl<DSearchObjects, &IID_DSearchObjects, &LIBID_TRiASHelperLib, 
				TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DSearchObjects>,
	public CComCoClass<CObjPropGUID, &CLSID_ObjPropGUID>
{
public:
	DECLARE_AGGREGATABLE(CObjPropGUID)		// class factory
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjPropGUID)
	
#if defined(_REGISTER_OBJECT_PROPERTIES)
	DECLARE_REGISTRY_RESOURCEID(IDR_OJPROP_GUID)
	BEGIN_CATEGORY_MAP(CObjPropGUID)
		IMPLEMENTED_CATEGORY(CATID_TRiASObjectPropertyRO)
	END_CATEGORY_MAP()
#endif // defined(_REGISTER_OBJECT_PROPERTIES)

	BEGIN_COM_MAP(CObjPropGUID)
		COM_INTERFACE_ENTRY(IObjectProperty2)
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
		COM_INTERFACE_ENTRY(IPropertyInfo2)
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
		COM_INTERFACE_ENTRY_CHAIN(CBaseObjectProperty)		// IDispatch der Basisklasse verwenden
		COM_INTERFACE_ENTRY(DSearchObjects)
		COM_INTERFACE_ENTRY2(IDispatch, DSearchObjects)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

		CObjPropGUID (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
// *** IPropertyInfo specific functions ***
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
		{ return CBaseObjectProperty::HelpInfo(pBuffer, ulLen, pHelpFile, pulHelpCtx); }
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx);

// *** IPropertyInfo2 specific functions ***
	STDMETHOD(GetConfigData) (THIS_ VARIANT *pvOptData);
	STDMETHOD(EvaluatesForClass) (THIS_ INT_PTR hObjs);
	STDMETHOD(GetConfigDataEx) (THIS_ INT_PTR hObjs, VARIANT *pvOptData);
	STDMETHOD(GetPropInfoEx) (THIS_ INT_PTR hObjs, LPSTR pBuffer, WORD wLen, DWORD *pdwData);
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300

// *** DSearchObjects specific functions
	STDMETHOD(ConsiderSearch)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, ULONG ulCnt);
	STDMETHOD(SearchObjects)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Identifikator als Zeichenkette -------------------------------------
class ATL_NO_VTABLE CObjPropIdent : 
	public CBaseObjectProperty,
	public CComCoClass<CObjPropIdent, &CLSID_ObjPropIdent>
{
public:
	DECLARE_AGGREGATABLE(CObjPropIdent)		// class factory
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjPropIdent)
	
#if defined(_REGISTER_OBJECT_PROPERTIES)
	DECLARE_REGISTRY_RESOURCEID(IDR_OJPROP_IDENT)
	BEGIN_CATEGORY_MAP(CObjPropIdent)
		IMPLEMENTED_CATEGORY(CATID_TRiASObjectPropertyRO)
	END_CATEGORY_MAP()
#endif // defined(_REGISTER_OBJECT_PROPERTIES)

		CObjPropIdent (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Objektklassenschlüssel 
class ATL_NO_VTABLE CObjPropObjClassCode : 
	public CBaseObjectProperty,
	public CComCoClass<CObjPropObjClassCode, &CLSID_ObjPropObjClassCode>
{
public:
	DECLARE_AGGREGATABLE(CObjPropObjClassCode)		// class factory
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjPropObjClassCode)
	
#if defined(_REGISTER_OBJECT_PROPERTIES)
	DECLARE_REGISTRY_RESOURCEID(IDR_OJPROP_OKS)
	BEGIN_CATEGORY_MAP(CObjPropObjClassCode)
		IMPLEMENTED_CATEGORY(CATID_TRiASObjectPropertyRO)
	END_CATEGORY_MAP()
#endif // defined(_REGISTER_OBJECT_PROPERTIES)

		CObjPropObjClassCode (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für Objekteigenschaft, die Objekttyp liefert -------------------
class ATL_NO_VTABLE CObjPropObjTyp : 
	public CBaseObjectProperty
{
protected:
	ULONG m_ulP;	// Punkte zählen
	ULONG m_ulL;	// Linien zählen
	ULONG m_ulF;	// Flächen zählen
	ULONG m_ulT;	// Texte zählen
	ULONG m_ulK;	// KO's zählen

public:
		CObjPropObjTyp (LPCSTR pcName, ResID resHelp);

// *** IObjectProperty specific functions ***
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Langform des Objekttyps als Zeichenkette ---------------------------
class ATL_NO_VTABLE CObjPropObjTypLong : 
	public CObjPropObjTyp,
	public CComCoClass<CObjPropObjTypLong, &CLSID_ObjPropObjTypLong>
{
public:
	DECLARE_AGGREGATABLE(CObjPropObjTypLong)		// class factory
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjPropObjTypLong)

#if defined(_REGISTER_OBJECT_PROPERTIES)
	DECLARE_REGISTRY_RESOURCEID(IDR_OJPROP_OBJTYPLONG)
	BEGIN_CATEGORY_MAP(CObjPropObjTypLong)
		IMPLEMENTED_CATEGORY(CATID_TRiASObjectPropertyRO)
	END_CATEGORY_MAP()
#endif // defined(_REGISTER_OBJECT_PROPERTIES)

		CObjPropObjTypLong (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

#if defined(_FORCE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
// Liefert Kurzform des Objekttypes als Einzelzeichen -------------------------
class ATL_NO_VTABLE CObjPropObjTypShort : 
	public CObjPropObjTyp,
	public CComCoClass<CObjPropObjTypShort, &CLSID_ObjPropObjTypShort>
{
public:
	DECLARE_AGGREGATABLE(CObjPropObjTypShort)		// class factory
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjPropObjTypShort)

#if defined(_REGISTER_OBJECT_PROPERTIES)
	DECLARE_REGISTRY_RESOURCEID(IDR_OJPROP_OBJTYPSHORT)
	BEGIN_CATEGORY_MAP(CObjPropObjTypShort)
		IMPLEMENTED_CATEGORY(CATID_TRiASObjectPropertyRO)
	END_CATEGORY_MAP()
#endif // defined(_REGISTER_OBJECT_PROPERTIES)

		CObjPropObjTypShort (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};
#endif // defined(_FORCE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// Liefert Eingabetext als Objekteigenschaft ----------------------------------
class ATL_NO_VTABLE CObjPropQueryField : 
	public CBaseObjectProperty,
	public IInitObjPropQueryField,
	public IConfigObjectProperty,
	public CComCoClass<CObjPropQueryField, &CLSID_ObjPropQueryField>
{
private:
	string m_strFText;	// letzter eingegebener Text
	int m_iNumber;		// lfde. Nummer dieser OPF
	HWND m_hWnd;		// ParentFenster für Dialog
	LONG m_lCum;		// kumulativer Index

	bool m_fUseForAll;	// für alle weiteren benutzen
	bool m_fFirst;		// das erste mal seit Reset gerufen
	bool m_fInitialized;

public:
	BEGIN_COM_MAP(CObjPropQueryField)
		COM_INTERFACE_ENTRY(IInitObjPropQueryField)
		COM_INTERFACE_ENTRY(IConfigObjectProperty)
		COM_INTERFACE_ENTRY_CHAIN(CBaseObjectProperty)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CObjPropQueryField)		// class factory
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjPropQueryField)
	
#if defined(_REGISTER_OBJECT_PROPERTIES)
	DECLARE_REGISTRY_RESOURCEID(IDR_OJPROP_QUERYFIELD)
	BEGIN_CATEGORY_MAP(CObjPropQueryField)
		IMPLEMENTED_CATEGORY(CATID_TRiASObjectPropertyRO)
	END_CATEGORY_MAP()
#endif // defined(_REGISTER_OBJECT_PROPERTIES)

		CObjPropQueryField (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IInitObjPropQueryField specific methods
	STDMETHOD(Init)(THIS_ HWND hWnd, int iNumber);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// IConfigObjectProperty
	STDMETHOD(ConfigObjectProperty) (THIS_ HWND hWndParent);
	STDMETHOD(get_IsConfigured) (VARIANT_BOOL *pfConfigState);

// sonstige member
	void SetInitialized (bool fInit = true) { m_fInitialized = fInit; }
	void SetParent (HWND hParent) { m_hWnd = hParent; }
	void SetNumber (int iNumber) { m_iNumber = iNumber ; }
};

// Objekteigenschaft für TRiAS-interne Merkmale
#include "ObjPropFeature.h"

#endif // _INTOPROP_HXX
