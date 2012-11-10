// Eine ObjektKlasse (Controlling Unknown) ------------------------------------
// File: CLASS.HXX

#if !defined(_CLASS_HXX)
#define _CLASS_HXX

#include <Atl/CieThis.h>

///////////////////////////////////////////////////////////////////////////////
// forward declarations
class CTriasApp;
class CGeoDoc;

class CFeatClsTree;
class CFeatObjTree;
class CGeoFeatureBase;

// {9268505F-8271-475A-9885-C37330068933}
extern "C" const IID __declspec(selectany) CLSID_GeoClass = 
	{0x9268505f,0x8271,0x475a,{0x98,0x85,0xc3,0x73,0x30,0x06,0x89,0x33}};

class CClass : 
	public CComDualImpl<DGeoClass, &IID_DGeoClass, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DGeoClass>,
	public CComObjectRoot
{
	D_CLASS(CClass);

private:
	LPUNKNOWN m_pUnk;			// controlling unknown
	CTriasApp *m_pApp;			// Trias.Application
	CGeoDoc *m_pDoc;			// Trias.Project

	CFeatClsTree *m_pFeatClsTree;	// Class GeoFeatures Tree
	CFeatObjTree *m_pFeatObjTree;	// Object GeoFeatures Tree

	ULONG m_lIdent;				// Identifikator
	char *m_pName;				// KurzText
	char *m_pFullName;			// LangText

	unsigned int m_fValid : 1;	// Class exists
	
	void Invalidate (void);
	
protected:
	HRESULT HandleGeoObject (CGeoObject *pObject, GEOOBJECTMODE rgMode);
	HRESULT GetVisInfoClsId (OBJECTTYPE rgOTyp, CLSID *pClsId);

public:
		 CClass (void);
		~CClass (void);
		
static CClass *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, ULONG lIdent, 
		GEOCLASSMODE rgMode = GEOCLASSMODE_Get, LPCSTR pcSrc = NULL);

static CClass *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, LPCSTR bName, 
		GEOCLASSMODE rgMode = GEOCLASSMODE_Get, LPCSTR pcSrc = NULL);

	bool FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		    	GEOCLASSMODE rgMode, ULONG lIdent, LPCSTR pcSrc);
	bool FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		    	GEOCLASSMODE rgMode, LPCSTR bName, LPCSTR pcSrc);

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CClass)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DGeoClass)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_THIS_EX(CLSID_GeoClass)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CClass)

///////////////////////////////////////////////////////////////////////////////
// _IGeoClass methods 
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch *pIApp);

	STDMETHOD(get_Properties) (THIS_ _DTRiASProperties **ppIProps);
	STDMETHOD(CreateProperty) (THIS_ VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp);

 	STDMETHOD(get_Value)(THIS_ BSTR *pbstrValue);
 	STDMETHOD(put_Value)(THIS_ BSTR bstrValue);
	STDMETHOD(get_Name)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_Name)(THIS_ BSTR bstrValue);
	STDMETHOD(get_FullName)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_FullName)(THIS_ BSTR bstrFullName);
	STDMETHOD(GetViews)(THIS_ VARIANT vObjType, DViews **ppIViews);
    STDMETHOD(GetObjects)(THIS_ VARIANT vObjs, VARIANT vLogMode, DGeoObjects **ppIObjs);
    STDMETHOD(GetObject)(THIS_ VARIANT vObj, VARIANT vMode, DGeoObject **ppIObj);
    STDMETHOD(GetFeatures)(THIS_ VARIANT vFeatures, VARIANT vLogMode, DGeoFeatures **ppIFeats);
    STDMETHOD(GetFeature)(THIS_ VARIANT vFeature, VARIANT vMode, DGeoFeature **ppIFeat);
	STDMETHOD(GetObjectsInRect)(THIS_ double dX1, double dY1, VARIANT vX2, VARIANT vY2, DGeoObjects **ppIObjs);
    STDMETHOD(GetVisInfo)(THIS_ OBJECTTYPE rgOTyp, VARIANT vView, DVisInfo **ppIVisInfo);
    STDMETHOD(SetVisInfo)(THIS_ DVisInfo *pIVisInfo, VARIANT vView);
	STDMETHOD(ResetVisInfo)(THIS_ OBJECTTYPE rgOTyp, VARIANT vView);
 	STDMETHOD(get_Code)(THIS_ LONG *pulIdent);

	STDMETHOD(get_Connection)(THIS_ ITRiASConnection **ppIConn);
	STDMETHOD(get_Updatable)(THIS_ VARIANT_BOOL *pfValue);
	STDMETHOD(put_Updatable)(THIS_ VARIANT_BOOL fValue);

    STDMETHOD(GetObjectFeatures)(THIS_ VARIANT vFeatures, VARIANT vLogMode, DGeoFeatures **ppIFeats);
    STDMETHOD(GetObjectFeature)(THIS_ VARIANT vFeature, VARIANT vMode, DGeoFeature **ppIFeat);

	STDMETHOD(get_IsQueryDef)(THIS_ VARIANT_BOOL *pfValue);

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// sonstige Member 
	char *GetName (bool fInitDefault = true, HPROJECT hPr = HACTCONNECTION);
	bool  SetName (const char *pName, bool fCreate = true, bool fIgnoreValid = false, HPROJECT hPr = HACTCONNECTION);

	void RefreshNames (void);
	bool Remove (void);

	char *GetFullName (HPROJECT hPr = HACTCONNECTION);
	void  SetFullName (const char *pFullName);

inline	ULONG GetValue (bool fForce = false) { return !fForce && !m_fValid ? 0L : m_lIdent; }
inline	void Validate (void) { m_fValid = true; }
inline  bool IsValid  (void) { return m_fValid ? true : false; }

///////////////////////////////////////////////////////////////////////////////
// Functions for  GeoFeatures Tree 
	CGeoFeatureBase *FGetFeatureDisp (
		LPCSTR bName, DGeoFeature **ppIFeat = NULL, FEATUREMODE rgMode = FEATUREMODE_Get)
		{ return m_pFeatClsTree ? m_pFeatClsTree -> FAddItem (bName, ppIFeat, rgMode) : NULL; }
	bool FDelFeature (LPCSTR bName) 
		{ return m_pFeatClsTree ? m_pFeatClsTree -> FDeleteItem (bName) : false; }
	bool FInvFeature (LPCSTR pName) 
		{ return m_pFeatClsTree ? m_pFeatClsTree -> FInvalidateItem (pName) : false; }
	bool SetFeatureName (LPCSTR bOldName, LPCSTR bNewName) 
		{ return m_pFeatClsTree ? m_pFeatClsTree -> SetFeatureName (bOldName, bNewName) : false; }

///////////////////////////////////////////////////////////////////////////////
// Functions for GeoObjectFeatures Tree 
	CGeoFeatureBase *FGetObjectFeatureDisp (LPCSTR bName, DGeoFeature **ppIFeat = NULL, 
		PROPCAPS rgProps = PROPCAPS_UNKNOWN, FEATUREMODE rgMode = FEATUREMODE_Get, 
		VARIANT *pvOptData = NULL, IObjectProperty *pIObjProp = NULL)
	{ return m_pFeatObjTree ? m_pFeatObjTree -> FAddItem (bName, ppIFeat, rgMode, rgProps, pvOptData, pIObjProp) : NULL; }

	bool FDelObjectFeature (LPCSTR bName) 
		{ return m_pFeatObjTree ? m_pFeatObjTree -> FDeleteItem (bName) : false; }
	bool FInvObjectFeature (LPCSTR pName) 
		{ return m_pFeatObjTree ? m_pFeatObjTree -> FInvalidateItem (pName) : false; }
	bool SetObjectFeatureName (LPCSTR bOldName, LPCSTR bNewName) 
		{ return m_pFeatObjTree ? m_pFeatObjTree -> SetFeatureName (bOldName, bNewName) : false; }

	CFeatObjTree *GetObjectFeatureTree() { return m_pFeatObjTree; }

///////////////////////////////////////////////////////////////////////////////
// 
	HRESULT GetDispatchIF (IDispatch **ppIDisp)
		{ return ((_DGeoClass *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp); }
	
///////////////////////////////////////////////////////////////////////////////
// for the tree's
	ULONG & FGetULONG (void);		// liefert SuchSchlüssel
	LPCSTR FGetBSTR (void);			// liefert SuchSchlüssel

friend int FCmpULONG (const ULONG &, const ULONG &);	// vergleicht 2 Schlüssel
friend int FCmpBSTR (LPCSTR, LPCSTR);		// vergleicht 2 Schlüssel
	
friend class CClassPro;
friend class CClsTrees;
friend class CIDTree;
friend class CClsNameTree;
};

///////////////////////////////////////////////////////////////////////////////
// Class::get_Value liefert OKS in folgende Zeichen eingepackt
#define OKS_SCOPE_BEGIN		TEXT("[")
#define OKS_SCOPE_END		TEXT("]")
#define OKS_SCOPE_BEGIN_LEN	1
#define OKS_SCOPE_END_LEN	1

#endif // _CLASS_HXX
