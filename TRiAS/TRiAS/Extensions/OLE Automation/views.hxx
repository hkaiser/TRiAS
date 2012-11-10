// Collection von Views (Controlling Unknown) -------------------------
// File: VIEWS.HXX

#if !defined(_VIEWS_HXX)
#define _VIEWS_HXX

class CTriasApp;
class CEnumViews;
class CGeoViewsArray;

class CGeoViews : 
	public CComDualImpl<DViews, &IID_DViews, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DViews>,
	public CComObjectRoot
{
private:
	LPUNKNOWN m_pUnk;			// controlling unknown
	CTriasApp *m_pApp;			// Trias.Application
	CGeoDoc *m_pDoc;			// Trias.Project

	CEnumViews *m_pEnumViews;		// Identifikatoren dieser Collection

	INITVIEWCOLLECTIONPROC m_pICProc;	// Routine, die Collection füllt
	DELETEVIEWCOLLECTIONPROC m_pDCProc;	// Delete View from Collection
	DWORD m_dwData;

	bool m_fValid;

public:
		CGeoViews (void);
		~CGeoViews (void);
		
static CGeoViews *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		INITVIEWCOLLECTIONPROC pICFunc, DWORD dwData,
		DELETEVIEWCOLLECTIONPROC pDCProc);

	bool FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		INITVIEWCOLLECTIONPROC pICFunc, DWORD dwData,
		DELETEVIEWCOLLECTIONPROC pDCProc);

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CGeoViews)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DViews)
		COM_INTERFACE_ENTRY(DTRiASCollection)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CGeoViews)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// *** _IViews methods
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);

	STDMETHOD(get_Count)(THIS_ long *plCount);
	STDMETHOD(Item)(THIS_ VARIANT vCode, IDispatch **ppIDisp);
	STDMETHOD(_NewEnum)(THIS_ IUnknown **ppIUnk);
	
    STDMETHOD(Add)(THIS_ VARIANT vView, IDispatch **ppIDisp);
    STDMETHOD(Remove)(THIS_ VARIANT vView);
    STDMETHOD(Refresh)(THIS);

    STDMETHOD(Dummy)(THIS) { return E_NOTIMPL; }

///////////////////////////////////////////////////////////////////////////////
// ZugriffsFunktionen
inline ULONG Count (void) { return m_pEnumViews -> m_pViewsArray -> Count(); }

// Enumerator verwalten
inline bool CanRegenerate (void) { return NULL != m_pICProc && 0L != m_dwData; }
	bool Regenerate (void);

inline char * GetView (ULONG lIndex) { return m_pEnumViews-> m_pViewsArray -> Value (lIndex); }
inline char * GetView (LPCSTR bstrName) { return m_pEnumViews -> m_pViewsArray -> Value (bstrName); }

inline HRESULT GetViewDisp (ULONG lIndex, LPVOID *ppDisp) { return m_pEnumViews->GetViewDisp (lIndex, ppDisp); }
inline HRESULT GetViewDisp (LPCSTR pViewStr, LPVOID *ppDisp) { return m_pEnumViews->GetViewDisp (pViewStr, ppDisp); }

inline void Validate (bool fFlag = true) { m_fValid = fFlag; }
};

#endif // _VIEWS_HXX
