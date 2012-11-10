// Collection der Object Windows (Controlling Unknown) ------------------
// File: OBJWINS.HXX

#if !defined(_OBJWINS_HXX)
#define _OBJWINS_HXX

class CTriasApp;
class CGeoDoc;
class CGeoObjWinArray;
class CEnumGeoObjWins;

class CGeoObjectWins : 
	public CComDualImpl<DGeoObjectWins, &IID_DGeoObjectWins, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DGeoObjectWins>,
	public CComObjectRoot
{
private:
	LPUNKNOWN m_pUnk;			// controlling unknown
	CTriasApp *m_pApp;			// Trias.Application
	CGeoDoc	*m_pDoc;			// Trias.Project
	
	CEnumGeoObjWins	*m_pEnumOWins;	// ObjWins dieser Collection

	INITOBJWINCOLLECTIONPROC m_pICProc;		// Routine, die Collection füllt
	DWORD m_dwData;							// additional data
	DELETEOBJWINCOLLECTIONPROC m_pDCProc;	// delete ObjWin from collection

	bool m_fValid;

public:
		CGeoObjectWins (void);
	   ~CGeoObjectWins (void);
		
static CGeoObjectWins *CreateInstance (
		LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		INITOBJWINCOLLECTIONPROC pICFunc, DWORD dwData,
		DELETEOBJWINCOLLECTIONPROC pDCProc );

	bool FInit (LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		INITOBJWINCOLLECTIONPROC pICFunc, DWORD dwData,
		DELETEOBJWINCOLLECTIONPROC pDCProc); 

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CGeoObjectWins)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DGeoObjectWins)
		COM_INTERFACE_ENTRY(DTRiASCollection)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CGeoObjectWins)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// _IGeoObects methods
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);

	STDMETHOD(get_Count)(THIS_ long *plCount);
	STDMETHOD(Item)(THIS_ VARIANT vCode, IDispatch **ppIDisp);
	STDMETHOD(_NewEnum)(THIS_ IUnknown **ppIUnk);
	
    STDMETHOD(Add)(THIS_ VARIANT vObjWin, IDispatch **ppIDisp);
    STDMETHOD(Remove)(THIS_ VARIANT vObjWin);
    STDMETHOD(Refresh)(THIS);

	STDMETHOD(get_ActGeoObjectWin)(THIS_ DGeoObjectWin **ppIWin);

///////////////////////////////////////////////////////////////////////////////
// ZugriffsFunktionen
inline ULONG Count (void) { return m_pEnumOWins -> m_pOWArray -> Count(); }

// Enumerator verwalten
inline bool CanRegenerate (void) { return NULL != m_pICProc && 0L != m_dwData; }
	bool Regenerate (void);

inline HWND GetObjectWin (ULONG lIndex) { return m_pEnumOWins -> m_pOWArray -> Value (lIndex); }
inline HWND GetObjectWin (LPCSTR pName) { return m_pEnumOWins -> m_pOWArray -> Value (pName); }
	
inline HRESULT GetObjectWinDisp (ULONG lIndex, LPVOID *ppDisp) { return m_pEnumOWins -> GetObjectWinDisp (lIndex, ppDisp); }
inline HRESULT GetObjectWinDisp (LPCSTR pObWinStr, LPVOID *ppDisp) { return m_pEnumOWins -> GetObjectWinDisp (pObWinStr, ppDisp); }
inline HRESULT GetObjectWinDispValue (HWND hWnd, LPVOID *ppDisp) { return m_pEnumOWins -> GetObjectWinDispValue (hWnd, ppDisp); }

inline void Validate (bool fFlag = true) { m_fValid = fFlag; }
};


#endif // _OBJWINS_HXX
