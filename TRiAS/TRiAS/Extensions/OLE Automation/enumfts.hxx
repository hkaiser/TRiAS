// Enumerator for Features -----------------------------------------
// File: ENUMFTS.HXX

#if !defined(_ENUMFTS_HXX)
#define _ENUMFTS_HXX


class CEnumGeoFts : 
	public IEnumVARIANT 
{
private:
	DWORD m_dwRefCnt;		// ReferenceCount
	ULONG m_iCurrent;		// actual Feature 
	ULONG m_ulCount;		// Gesamtanzahl im Enum
	CGeoFtsArray *m_pGeoFtsArray;	// all Features in Array	

public:
		 CEnumGeoFts (void);
		~CEnumGeoFts (void);
	
static CEnumGeoFts *CreateInstance (CGeoFtsArray *pArr);
static CEnumGeoFts *CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,	void *pViewClsObj, 
	INITFEATCOLLECTIONPROC pICProc, DWORD dwData, DWORD dwFlags = PROPCAPS_NONE);

/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppv);
	STDMETHOD_(ULONG, AddRef)(void);
	STDMETHOD_(ULONG, Release)(void);

/* IEnumVARIANT methods */
	STDMETHOD(Next)(ULONG celt, VARIANT *rgvar, ULONG *pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(LPENUMVARIANT *ppenum);
	
inline 	ULONG Count (void) { return m_ulCount; }
inline	void InitCount (void) { m_ulCount = m_pGeoFtsArray -> Count(); }
 
inline	char *GetFeature (ULONG lIndex) { return m_pGeoFtsArray -> Value (lIndex); }
inline 	char *GetFeature (LPCSTR bstrName) { return m_pGeoFtsArray -> Value (bstrName); }

inline	HRESULT GetFeatureDisp (ULONG lIndex, DGeoFeature **ppIFeat) 
			{ return m_pGeoFtsArray -> GetFeatureDisp (lIndex, ppIFeat); }
inline  HRESULT GetFeatureDisp (LPCSTR pFtStr, DGeoFeature **ppIFeat) 
			{ return m_pGeoFtsArray -> GetFeatureDisp (pFtStr, ppIFeat); }

inline	bool DeleteFeature (LPCSTR bName) 
			{ return m_pGeoFtsArray -> DeleteFeature (bName); }

friend class CGeoFeatures;
friend class CGeoFtsPro;
};

#endif //_ENUMFTS_HXX
