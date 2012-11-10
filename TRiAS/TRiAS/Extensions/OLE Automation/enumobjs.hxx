// Enumerator for Objects -----------------------------------------
// File: ENUMOBJS.HXX

#if !defined(_ENUMOBJS_HXX)
#define _ENUMOBJS_HXX


class CEnumGeoObjs : 
	public IEnumVARIANT 
{
private:
	DWORD m_dwRefCnt;				// ReferenceCount
	ULONG m_iCurrent;				// actual Object 
	ULONG m_ulCount;				// Gesamtanzahl im Enum
	CGeoObjArray *m_pGeoObjArray;	// all Objects in Array	

public:
		 CEnumGeoObjs (void);
		~CEnumGeoObjs (void);
	
static CEnumGeoObjs *CreateInstance (CGeoObjArray *pArr);
static CEnumGeoObjs *CreateInstance (LPUNKNOWN pUnk, 
									 CTriasApp *pApp, 
									 CGeoDoc *pDoc, 
									 INITOBJCOLLECTIONPROC pICProc, 
									 DWORD dwData);

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
inline	void InitCount (void) { m_ulCount = m_pGeoObjArray -> Count(); }
 
inline	HRESULT GetObjectDisp (ULONG lIndex, LPVOID *ppDisp) { return m_pGeoObjArray -> GetObjectDisp (lIndex, ppDisp); }
inline  HRESULT GetObjectDisp (LPCSTR pObStr, LPVOID *ppDisp) { return m_pGeoObjArray->GetObjectDisp (pObStr, ppDisp); }
inline  HRESULT GetObjectDispValue (LONG lONr, LPVOID *ppDisp) { return m_pGeoObjArray->GetObjectDispValue (lONr, ppDisp); }

inline	bool DeleteObject (LONG lONr) { return m_pGeoObjArray -> DeleteObject (lONr); }

friend class CGeoObjects;
friend class CGeoObjectsPro;
};

#endif //_ENUMOBJS_HXX
