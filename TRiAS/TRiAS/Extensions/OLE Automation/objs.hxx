// Collection der Objects (Controlling Unknown) ------------------
// File: OBJS.HXX

#if !defined(_OBJS_HXX)
#define _OBJS_HXX

class CTriasApp;
class CGeoObjArray;
class CEnumGeoObjs;

class CGeoObjects : 
	public CComDualImpl<DGeoObjects, &IID_DGeoObjects, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DGeoObjects>,
	public IQueryEnumLONG,
	public CComObjectRoot
{
private:
	LPUNKNOWN m_pUnk;			// controlling unknown
	CTriasApp *m_pApp;			// Trias.Application
	CGeoDoc	*m_pDoc;			// Trias.Project
	
	CEnumGeoObjs *m_pObjs;				// Objects dieser Collection
	INITOBJCOLLECTIONPROC m_pICProc;	// Routine, die Collection füllt
	DELETEOBJCOLLECTIONPROC m_pDCProc;	// delete object from collection

	bool m_fValid;

protected:
	HRESULT HandleAddObject (long lONr, IDispatch **ppIDisp);

public:
	DWORD m_dwData;				// additional data
	
public:
		CGeoObjects (void);
		~CGeoObjects (void);
		
static CGeoObjects *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		INITOBJCOLLECTIONPROC pICFunc, DWORD dwData,
		DELETEOBJCOLLECTIONPROC pDCProc);

	bool FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		INITOBJCOLLECTIONPROC pICFunc, DWORD dwData,
		DELETEOBJCOLLECTIONPROC pDCProc); 

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CGeoObjects)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DGeoObjects)
		COM_INTERFACE_ENTRY(DTRiASCollection)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IQueryEnumLONG)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CGeoObjects)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// *** IQueryEnumLONG methods
	STDMETHOD (QueryEnumLONG) (THIS_ IEnumLONG **ppenm);

///////////////////////////////////////////////////////////////////////////////
// *** _IGeoObects methods
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);

	STDMETHOD(get_Count)(THIS_ long *plCount);
	STDMETHOD(Item)(THIS_ VARIANT vCode, IDispatch **pIDisp);
	STDMETHOD(_NewEnum)(THIS_ IUnknown **ppIUnk);
	
    STDMETHOD(Add)(THIS_ VARIANT vObj, IDispatch **ppIDisp);
    STDMETHOD(Remove)(THIS_ VARIANT vObj);
    STDMETHOD(Refresh)(THIS);

	STDMETHOD(CreateGeoObjectWin)(THIS_ VARIANT vFlags, DGeoObjectWin **ppIWin);

	STDMETHOD(GeometryIntersection)(THIS_ DGeoClass *pICls, DGeoObjects **ppIObjs);
	STDMETHOD(GeometryUnion)(THIS_ DGeoClass *pICls, DGeoObjects **ppIObjs);

    STDMETHOD(Intersection)(THIS_ DGeoObjects *pIObjs, DGeoObjects **ppIObjs);
    STDMETHOD(Union)(THIS_ DGeoObjects *pIObjs, DGeoObjects **ppIObjs);
    STDMETHOD(Difference)(THIS_ DGeoObjects *pIObjs, DGeoObjects **ppIObjs);
    STDMETHOD(SymmetricDifference)(THIS_ DGeoObjects *pIObjs, DGeoObjects **ppIObjs);

    STDMETHOD(_GeometryLinesUnion)(DGeoClass *pICls, VARIANT vFillGap, VARIANT vAsArea, DGeoObjects **ppIObjs);
	STDMETHOD(GetObjectsInRect)(THIS_ double dX1, double dY1, VARIANT vX2, VARIANT vY2, DGeoObjects **ppIObjs);

	STDMETHOD(MakeGeoClass)(THIS_ BSTR bstrNameOrOks, DGeoClass **ppIClass);

///////////////////////////////////////////////////////////////////////////////
// ZugriffsFunktionen
inline ULONG Count (void) { return m_pObjs -> m_pGeoObjArray -> Count(); }

// Enumerator verwalten
inline bool CanRegenerate (void) { return NULL != m_pICProc && 0L != m_dwData; }
	bool Regenerate (void);

inline ULONG GetObject (ULONG lIndex) { return m_pObjs -> m_pGeoObjArray -> Value (lIndex); }
inline ULONG GetObject (LPCSTR bstrName) { return m_pObjs -> m_pGeoObjArray -> Value (bstrName); }
	
inline HRESULT GetObjectDisp (ULONG lIndex, LPVOID *ppDisp) { return m_pObjs ->GetObjectDisp (lIndex, ppDisp); }
inline HRESULT GetObjectDisp (LPCSTR pObStr, LPVOID *ppDisp) { return m_pObjs->GetObjectDisp (pObStr, ppDisp); }
inline HRESULT GetObjectDispValue (LONG lONr, LPVOID *ppDisp) { return m_pObjs->GetObjectDispValue (lONr, ppDisp); }

inline CGeoObject *GetGeoObject (LONG lONr) { return m_pObjs -> m_pGeoObjArray -> GetGeoObject (lONr); }
inline HOBJECT *GetObjectsAsArray (void) { return m_pObjs -> m_pGeoObjArray -> GetObjectsAsArray(); }

inline void Validate (bool fFlag = true) { m_fValid = fFlag; }

// friends
friend HRESULT GetEnumLongFromGeoObjects (_DGeoObjects *pIObjs, IEnumLONG **ppIEnum);
};

// Datenstruktur, um bei der Enumeration für GetObjects die entsprechenden Objettypen
// berücksichtigen zu könne
typedef struct tagGETOBJECTSDATA {
	DWORD dwSize;
	DWORD dwData;	// generische Daten
	int iObjBits;	// gewünschte Objettypen
} GETOBJECTSDATA;

///////////////////////////////////////////////////////////////////////////////
// InitCollectionProc für IEnumLONG 
extern "C" 
INITOBJSTATUS PASCAL GetObjectsFromEnum (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr);


#endif // _OBJS_HXX
