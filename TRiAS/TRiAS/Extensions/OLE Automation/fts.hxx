// Collection der Features (Controlling Unknown) ------------------
// File: FTS.HXX

#if !defined(_FTS_HXX)
#define _FTS_HXX

class CTriasApp;
class CGeoFtsArray;
class CEnumGeoFts;

class CGeoFeatures : 
	public CComDualImpl<DGeoFeatures, &IID_DGeoFeatures, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DGeoFeatures>,
	public CComObjectRoot
{
private:
	LPUNKNOWN m_pUnk;			// controlling unknown
	CTriasApp *m_pApp;			// Trias.Application
	CGeoDoc *m_pDoc;			// Trias.Project

	CEnumGeoFts *m_pEnumFts;			// Features dieser Collection
	INITFEATCOLLECTIONPROC m_pICProc;	// Routine, die Collection füllt
	DELETEFEATCOLLECTIONPROC m_pDCProc;	// Delete Feature from Collection
	DWORD m_dwData;						// additional data
	DWORD m_dwFlags;

	void *m_pViewClsObj;		// Save calling context: GeoView, Class, GeoObject
	bool m_fValid;

public:
		CGeoFeatures (void);
		~CGeoFeatures (void);
		
static CGeoFeatures *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, void *pViewClsObj,
		INITFEATCOLLECTIONPROC pICFunc, DWORD dwData,
		DELETEFEATCOLLECTIONPROC pDCProc, DWORD dwFlags = PROPCAPS_NONE);

	bool FInit (
		LPUNKNOWN pUnk, CTriasApp *pApp,  CGeoDoc *pDoc, void *pViewClsObj,
		INITFEATCOLLECTIONPROC pICFunc, DWORD dwData,
		DELETEFEATCOLLECTIONPROC pDCProc, DWORD dwFlags = PROPCAPS_NONE);

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CGeoFeatures)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DGeoFeatures)
		COM_INTERFACE_ENTRY(DTRiASCollection)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CGeoFeatures)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// *** _IGeoFeatures methods
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);

	STDMETHOD(get_Count)(THIS_ long *plCount);
	
	STDMETHOD(Item)(THIS_ VARIANT vCode, IDispatch **pIDisp);
	STDMETHOD(_NewEnum)(THIS_ IUnknown **ppIUnk);
	
   	STDMETHOD(Add)(THIS_ VARIANT vFeature, IDispatch **ppIDisp);
   	STDMETHOD(Remove)(THIS_ VARIANT vFeature);
    STDMETHOD(Refresh)(THIS);

    STDMETHOD(Dummy)(THIS) { return E_NOTIMPL; }

///////////////////////////////////////////////////////////////////////////////
// ZugriffsFunktionen
	inline ULONG Count (void) { return m_pEnumFts -> m_pGeoFtsArray -> Count(); }

// Enumerator verwalten
	inline bool CanRegenerate (void) { return NULL != m_pICProc && 0L != m_dwData; }

	bool Regenerate (void);

	inline char *GetFeature (ULONG lIndex) { return m_pEnumFts -> m_pGeoFtsArray -> Value (lIndex); }
	inline char *GetFeature (LPCSTR bstrName) { return m_pEnumFts -> m_pGeoFtsArray -> Value (bstrName); }
	inline HRESULT GetFeatureDisp (ULONG lIndex, DGeoFeature **ppIFeat) { return m_pEnumFts ->GetFeatureDisp (lIndex, ppIFeat); }
	inline HRESULT GetFeatureDisp (LPCSTR pFtStr, DGeoFeature **ppIFeat) { return m_pEnumFts->GetFeatureDisp (pFtStr, ppIFeat); }
	inline void Validate (bool fFlag = true) { m_fValid = fFlag; }
};


#endif // _FTS_HXX
