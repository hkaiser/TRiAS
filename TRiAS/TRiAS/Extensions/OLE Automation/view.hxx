// Eine View (Controlling Unknown) ------------------------------------
// File: VIEW.HXX

#if !defined(_VIEW_HXX)
#define _VIEW_HXX

class CTriasApp;
class CGeoDoc;
class CFeatViewTree;
class CGeoFeatureBase;

class CGeoView : 
	public CComDualImpl<DView, &IID_DView, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DView>,
	public CComObjectRoot
{
	D_CLASS(CGeoView);

private:
	LPUNKNOWN m_pUnk;		// controlling unknown
	CTriasApp *m_pApp;		// Trias.Application
	CGeoDoc *m_pDoc;		// Trias.Project

	CFeatViewTree *m_pFeatViewTree;	// View GeoFeatures Tree
	char *m_pName;			// Text

	bool m_fValid;			// object exists
	
	void Invalidate (void);

protected:
	HRESULT HandleGeoObject (CGeoObject *pObject, GEOOBJECTMODE rgMode);
	HRESULT HandleClass (CClass *pClass, OBJECTTYPE rgOTypes, GEOCLASSMODE rgMode);

public:
		CGeoView (void);
		~CGeoView (void);
		
static CGeoView *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		LPCSTR bName, VIEWMODE rgMode = VIEWMODE_Get);

	BOOL FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		VIEWMODE rgMode, LPCSTR bName);

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CGeoView)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DView)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CGeoView)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// _IView methods 
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);

	STDMETHOD(get_Properties) (THIS_ _DTRiASProperties **ppIProps);
	STDMETHOD(CreateProperty) (THIS_ VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp);

 	STDMETHOD(get_Value)(THIS_ BSTR *bstrValue);
		
	STDMETHOD(get_Name)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_Name)(THIS_ BSTR bstrValue);
	STDMETHOD(GetClipObject)(THIS_ DGeoObject **ppIObj);
	STDMETHOD(SetClipObject)(THIS_ DGeoObject *pIObj);
	STDMETHOD(ResetClipObject)(THIS);
	
    STDMETHOD(GetClasses)(THIS_ VARIANT vClss, VARIANT vLogMode, DGeoClasses **ppIClss);
    STDMETHOD(GetClass)(THIS_ VARIANT vCls, VARIANT vOTypes, VARIANT vMode, DGeoClass **ppICls);
    	
    STDMETHOD(GetObjects)(THIS_ VARIANT vObjs, VARIANT vLogMode, DGeoObjects **ppIObjs);
    STDMETHOD(GetObject)(THIS_ VARIANT vObj, VARIANT vMode, DGeoObject **ppIObj);
    	
    STDMETHOD(GetFeatures)(THIS_ VARIANT vFeatures, VARIANT vLogMode, DGeoFeatures **ppIFeats);
    STDMETHOD(GetFeature)(THIS_ VARIANT vFeature, VARIANT vMode, DGeoFeature **ppIFeat);

	STDMETHOD(GetObjectsInRect)(THIS_ double dX1, double dY1, VARIANT vX2, VARIANT vY2, DGeoObjects **ppIObjs);

	STDMETHOD(get_RefScale)(THIS_ long *plRefScale);
	STDMETHOD(put_RefScale)(THIS_ long lRefScale);
	STDMETHOD(get_Scale)(THIS_ long *plScale);
	STDMETHOD(put_Scale)(THIS_ long lScale);

	STDMETHOD(get_Description)(THIS_ BSTR *pbstrDesc);
	STDMETHOD(put_Description)(THIS_ BSTR bstrDesc);

	STDMETHOD(GetActRect)(THIS_ double *pdX, double *pdY, VARIANT *pvX, VARIANT *pvY);
	STDMETHOD(SetActRect)(THIS_ double dX1, double dY1, VARIANT vX2, VARIANT vY2);
	STDMETHOD(GetConstraintRect)(THIS_ double *pdX, double *pdY, VARIANT *pvX, VARIANT *pvY);
	STDMETHOD(SetConstraintRect)(THIS_ double dX1, double dY1, VARIANT vX2, VARIANT vY2);

///////////////////////////////////////////////////////////////////////////////
// sonstige Member 
inline const char *GetValue (void) const { return m_pName;}

	char *GetName (bool fForce = false);	// fForce == true --> internal use only !!
	bool SetName (const char *pName, bool fIgnoreValid = false);
	
	bool FAddIdentToView (CClass *pClass, OBJECTTYPE rgOTypes);
	bool FRemoveIdentFromView (ULONG lIdent, OBJECTTYPE rgOTypes);

	bool ClassIsMemberOfView (CClass *pClass, OBJECTTYPE rgOTypes);
	bool ObjectIsMemberOfView (CGeoObject *pObject);

	bool Remove (void);	// remove physically
	
inline void Validate (void) { m_fValid = true; }
inline bool IsValid (void) { return m_fValid ? true : false; }

///////////////////////////////////////////////////////////////////////////////
// for the tree's
	LPCSTR FGetBSTR (void);				// liefert SuchSchlüssel
friend int FCmpBSTR (LPCSTR, LPCSTR);	// vergleicht 2 Schlüssel

// Functions for  GeoFeatures Tree 
	CGeoFeatureBase *FGetFeatureDisp (LPCSTR bName, DGeoFeature **ppIFeat = NULL, 
				    			  FEATUREMODE rgMode = FEATUREMODE_Get)
		{ return m_pFeatViewTree ? m_pFeatViewTree -> FAddItem (bName, ppIFeat, rgMode) : NULL; }
	bool FDelFeature (LPCSTR bName) 
		{ return m_pFeatViewTree ? m_pFeatViewTree -> FDeleteItem (bName) : false; }
	bool FInvFeature (LPCSTR pName) 
		{ return m_pFeatViewTree ? m_pFeatViewTree -> FInvalidateItem (pName) : false; }
	bool SetFeatureName (LPCSTR bOldName, LPCSTR bNewName) 
		{ return m_pFeatViewTree ? m_pFeatViewTree -> SetFeatureName (bOldName, bNewName) : false; }

friend class CViewTree;
};

#endif // _VIEW_HXX
