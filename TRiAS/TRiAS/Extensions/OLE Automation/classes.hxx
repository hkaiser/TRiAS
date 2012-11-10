// Collection von ObjektKlassen (Controlling Unknown) -------------------------
// File: CLASSES.HXX

#if !defined(_CLASSES_HXX)
#define _CLASSES_HXX

class CTriasApp;
class CIdentArray;
class CEnumClasses;

class CClasses : 
	public CComDualImpl<DGeoClasses, &IID_DGeoClasses, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DGeoClasses>,
	public CComObjectRoot
{
private:
	LPUNKNOWN m_pUnk;			// controlling unknown
	CTriasApp *m_pApp;			// Trias.Application
	CGeoDoc	*m_pDoc;			// Trias.Project

	CEnumClasses *m_pIdents;			// Identifikatoren dieser Collection 
	INITCLASSCOLLECTIONPROC m_pICProc;	// Routine, die Collection füllt
	DELETECLSCOLLECTIONPROC m_pDCProc;	// Delete Class from Collection
	DWORD		m_dwData;				// additional data

	bool m_fValid;

public:
		CClasses (void);
		~CClasses (void);
		
static CClasses *CreateInstance (
			LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
			INITCLASSCOLLECTIONPROC pICFunc, DWORD dwData,
			DELETECLSCOLLECTIONPROC pDCProc);

	bool FInit (LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
			INITCLASSCOLLECTIONPROC pICFunc, DWORD dwData,
			DELETECLSCOLLECTIONPROC pDCProc);

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CClasses)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DGeoClasses)
		COM_INTERFACE_ENTRY(DTRiASCollection)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CClasses)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// _IGeoClasses methods
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);

	STDMETHOD(get_Count)(THIS_ long *plCount);
	STDMETHOD(Item)(THIS_ VARIANT vCode, IDispatch **pIDisp);
	STDMETHOD(_NewEnum)(THIS_ IUnknown **ppIUnk);
	
    STDMETHOD(Add)(THIS_ VARIANT vCls, IDispatch **ppIDisp);
    STDMETHOD(Remove)(THIS_ VARIANT vCls);
    STDMETHOD(Refresh)(THIS);

    STDMETHOD(Dummy)(THIS) { return E_NOTIMPL; }

///////////////////////////////////////////////////////////////////////////////
// ZugriffsFunktionen
inline ULONG Count (void) { return m_pIdents -> m_pIdArray -> Count(); }

// Enumerator verwalten
inline bool CanRegenerate (void) { return NULL != m_pICProc && 0L != m_dwData; }
	bool Regenerate (void);

inline ULONG GetIdent (ULONG lIndex) { return m_pIdents -> m_pIdArray -> Value (lIndex); }
inline ULONG GetIdent (LPCSTR bstrName) { return m_pIdents -> m_pIdArray -> Value (bstrName); }

inline HRESULT GetClassDisp (ULONG lIndex, LPVOID *ppDisp) { return m_pIdents->GetClassDisp (lIndex, ppDisp); }
inline HRESULT GetClassDisp (LPCSTR pIdStr, LPVOID *ppDisp) { return m_pIdents->GetClassDisp (pIdStr, ppDisp); }
inline HRESULT GetClassDispValue (ULONG lIdent, LPVOID *ppDisp) { return m_pIdents->GetClassDispValue (lIdent, ppDisp); }

inline void Validate (bool fFlag = true) { m_fValid = fFlag; }
};


#endif // _CLASSES_HXX
