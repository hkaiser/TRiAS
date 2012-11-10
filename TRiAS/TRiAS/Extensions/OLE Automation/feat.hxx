// Eine Feature (Controlling Unknown) ------------------------------------
// File: FEAT.HXX

#if !defined(_FEAT_HXX)
#define _FEAT_HXX

#include "obj.hxx"

///////////////////////////////////////////////////////////////////////////////
// forward declarations
class CTriasApp;
class CGeoDoc;

class CGeoFeatureBase : 
	public CComDualImpl<DGeoFeature, &IID_DGeoFeature, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DGeoFeature>,
	public CComObjectRoot
{
protected:
	CTriasApp *m_pApp;			// Trias.Application
	CGeoDoc *m_pDoc;			// Trias.Project
	LPUNKNOWN m_pUnk;			// controlling unknown

	char *m_pFCstr;				// Feature Code as string
	char *m_pName;				// KurzText
	char *m_pFullName;			// LangText
	char *m_pFeat;				// FEATURE
	bool m_fValid;				// object exists

	CGeoFeatureBase (void);
	virtual ~CGeoFeatureBase (void);

	void Invalidate (void) { m_fValid = false; }
	BOOL FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc);

public:
		
///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CGeoFeatureBase)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DGeoFeature)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CGeoFeatureBase)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// *** _IGeoFeature methods 
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);
		
	STDMETHOD(get_Properties) (THIS_ _DTRiASProperties **ppIProps);
	STDMETHOD(CreateProperty) (THIS_ VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp);

	STDMETHOD(get_Value)(THIS_ BSTR *pbstrValue);
	STDMETHOD(get_Name)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_Name)(THIS_ BSTR bstrValue);
    STDMETHOD(get_FullName)(THIS_ BSTR *pbstrValue);
   	STDMETHOD(put_FullName)(THIS_ BSTR bstrValue);
    STDMETHOD(get_Feature)(THIS_ BSTR *pbstrValue);
    STDMETHOD(put_Feature)(THIS_ BSTR bstrValue);
    STDMETHOD(get_Flags)(THIS_ PROPERTYCAPS *pdwValue);
    STDMETHOD(put_Flags)(THIS_ PROPERTYCAPS dwValue);
 
	STDMETHOD(GetViews)(THIS_ DViews **ppIViews);

    STDMETHOD(GetClasses)(THIS_ VARIANT vClss, VARIANT vLogMode, DGeoClasses **ppIClss);
    STDMETHOD(GetObjects)(THIS_ VARIANT vObjTypes, VARIANT vLogMode, DGeoObjects **ppIObjs);

///////////////////////////////////////////////////////////////////////////////
// sonstige Member
inline void Validate (void) { m_fValid = true;}
inline bool IsValid  (void) { return m_fValid ? true : false; }

virtual char *GetValue (void) = 0;
virtual char *GetName (bool fForce = false) = 0;
virtual bool  SetName (const char *pName, bool fIgnoreValid = false) = 0;
virtual char *GetFullName (void) = 0;
virtual bool  SetFullName (const char *pFullName) = 0;
virtual char *GetFeat (bool fForce = false) = 0;
virtual HRESULT SetFeat (const char *pFeat, BOOL fForce = FALSE) = 0;
virtual bool Remove (void) = 0;

///////////////////////////////////////////////////////////////////////////////
// for the tree's
	LPCSTR FGetBSTR (void);				// liefert SuchSchlüssel
friend int FCmpBSTR (LPCSTR, LPCSTR);	// vergleicht 2 Schlüssel

friend class CFeatClsTree;
friend class CFeatViewTree;
friend class CFeatObjTree;
};

///////////////////////////////////////////////////////////////////////////////
// View, Class Features 
class CGeoFeatureVC : 
	public CGeoFeatureBase 
{
private:
	short m_iTType;				// TargetType: TT_Sicht, TT_Identifikator  
	DWORD m_dwTarget;			// Target: pViewName, lIdent
	LONG m_lFCd;				// FeatureCode

protected:
	BOOL FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		FEATUREMODE rgMode, LPCSTR bName, short iTType, DWORD dwTarget);

public:
		CGeoFeatureVC (void);
		~CGeoFeatureVC (void);
		
static CGeoFeatureVC *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp,  CGeoDoc *pDoc, LPCSTR bName, 
		short iTType, DWORD dwTarget, FEATUREMODE rgMode = FEATUREMODE_Get);


///////////////////////////////////////////////////////////////////////////////
// *** _IGeoFeature methods 
	STDMETHOD(get_ConfigData)(VARIANT *pvOptData);

///////////////////////////////////////////////////////////////////////////////
// sonstige Member
	char *GetValue (void);
	char *GetName (bool fForce = false);
	bool SetName (const char *pName, bool fIgnoreValid = false);
	
	char *GetFullName (void);
	bool SetFullName (const char *pFullName);
	char *GetFeat (bool fForce = false);
	HRESULT SetFeat (const char *pFeat, BOOL fForce = FALSE);
	bool Remove (void);

friend class CFeatClsTree;
friend class CFeatViewTree;
};

///////////////////////////////////////////////////////////////////////////////
// Object Features 
DefineSmartInterface(ObjectProperty);

class CGeoFeatureObj : 
	public CGeoFeatureBase 
{
private:
	LONG m_lONrOrIdent; 
	PROPERTYCAPS m_rgProps;
	WObjectProperty m_ObjProp;

protected:
	BOOL FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		FEATUREMODE rgMode, LPCSTR bName, LONG lONr, 
		PROPCAPS rgProps, VARIANT *pvOptData, IObjectProperty *pIObjProp);

public:
		CGeoFeatureObj (void);
		~CGeoFeatureObj (void);
		
static CGeoFeatureObj *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp,  CGeoDoc *pDoc, LPCSTR bName, 
		LONG lONr, FEATUREMODE rgMode = FEATUREMODE_Get, 
		PROPCAPS rgProps = PROPCAPS_UNKNOWN, VARIANT *pvOptData = NULL, 
		IObjectProperty *pIObjProp = NULL);

///////////////////////////////////////////////////////////////////////////////
// *** _IGeoFeature methods (partailly)
    STDMETHOD(get_Flags)(THIS_ PROPERTYCAPS *pdwValue);
    STDMETHOD(put_Flags)(THIS_ PROPERTYCAPS dwValue);
	STDMETHOD(get_ConfigData)(VARIANT *pvOptData);

    STDMETHOD(GetObjects)(THIS_ VARIANT vObjTypes, VARIANT vLogMode, DGeoObjects **ppIObjs);

///////////////////////////////////////////////////////////////////////////////
// sonstige Member
	char *GetValue (void);
	char *GetName (bool fForce = false);
	bool SetName (const char *pName, bool fIgnoreValid = false);
	char *GetFullName (void);
	bool SetFullName (const char *pFullName);
	char *GetFeat (bool fForce = false);
	HRESULT SetFeat (const char *pFeat, BOOL fForce = FALSE);
	bool Remove (void);

	inline HRESULT IsGeoObject()
	{
	CGeoObject *pObj = NULL;

		return m_pUnk -> QueryInterface (CLSID_GeoObject, (LPVOID *)&pObj);
	}
	friend class CFeatObjTree;
};

#endif // _FEAT_HXX
