// Collection von Docs (Controlling Unknown) -------------------------
// File: DOCS.HXX

#if !defined(_DOCS_HXX)
#define _DOCS_HXX

class CTriasApp;
class CEnumDocs;
class CGeoDocsArray;

class CGeoDocs : 
	public CComDualImpl<DDocuments, &IID_DDocuments, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DDocuments>,
	public CComObjectRoot
{
private:
	LPUNKNOWN m_pUnk;			// controlling unknown
	CTriasApp *m_pApp;			// Trias.Application

	CEnumDocs *m_pEnumDocs;				// Dokumente dieser Collection
	INITDOCCOLLECTIONPROC m_pICProc;	// Routine, die Collection füllt
	DELETEDOCCOLLECTIONPROC m_pDCProc;
	DWORD m_dwData;

	bool m_fValid;

public:
		CGeoDocs (void);
		~CGeoDocs (void);
		
static CGeoDocs *CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, 
				 INITDOCCOLLECTIONPROC pICFunc, DWORD dwData,
				 DELETEDOCCOLLECTIONPROC pDCProc);

	bool FInit (LPUNKNOWN pUnk, CTriasApp *pApp, 
				INITDOCCOLLECTIONPROC pICFunc, DWORD dwData,
				DELETEDOCCOLLECTIONPROC pDCProc);

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CGeoDocs)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DDocuments)
		COM_INTERFACE_ENTRY(DTRiASCollection)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CGeoDocs)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// _IDocuments methods
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);

	STDMETHOD(get_Count)(THIS_ long *plCount);
	STDMETHOD(Item)(THIS_ VARIANT vt, IDispatch **ppIDisp);
	STDMETHOD(_NewEnum)(THIS_ IUnknown **ppIUnk);

    STDMETHOD(Add)(THIS_ VARIANT vDoc, IDispatch **ppIDisp);
    STDMETHOD(Remove)(THIS_ VARIANT vDoc);
    STDMETHOD(Refresh)(THIS);
	STDMETHOD(New)(THIS_ BSTR bstrName, VARIANT vUser, VARIANT vPassWd, VARIANT vMode, DDocument **ppIDoc);
	STDMETHOD(Open)(THIS_ BSTR bstrName, VARIANT vUser, VARIANT vPassWd, VARIANT vMode, DDocument **ppIDoc);

///////////////////////////////////////////////////////////////////////////////
// ZugriffsFunktionen
inline ULONG Count (void) { return m_pEnumDocs -> m_pDocsArray -> Count(); }

// Enumerator verwalten
inline bool CanRegenerate (void) { return NULL != m_pICProc && 0L != m_dwData; }
	bool Regenerate (void);

inline char *GetDoc (ULONG lIndex) { return m_pEnumDocs-> m_pDocsArray -> Value (lIndex); }
inline char *GetDoc (LPCSTR bstrName) { return m_pEnumDocs -> m_pDocsArray -> Value (bstrName); }

inline HRESULT GetDocDisp (ULONG lIndex, DDocument **ppDoc) { return m_pEnumDocs->GetDocDisp (lIndex, ppDoc); }
inline HRESULT GetDocDisp (LPCSTR pDocStr, DDocument **ppDoc) { return m_pEnumDocs->GetDocDisp (pDocStr, ppDoc); }

inline void Validate (bool fFlag = true) { m_fValid = fFlag; }
};

#endif // _DOCS_HXX
