// Enumerator for Object Windows -----------------------------------------
// File: ENUMOBWS.HXX

#if !defined(_ENUMOBWS_HXX)
#define _ENUMOBWS_HXX


class CEnumGeoObjWins : public IEnumVARIANT {

private:
			   DWORD m_dwRefCnt;		// ReferenceCount
			   ULONG m_iCurrent;		// actual Object Window Index 
	CGeoObjWinArray *m_pOWArray;		// all Object Windows  in Array	

public:
	   CEnumGeoObjWins (void);
	  ~CEnumGeoObjWins (void);
	
static CEnumGeoObjWins *CreateInstance (CGeoObjWinArray *pArr);
static CEnumGeoObjWins *CreateInstance (LPUNKNOWN  pUnk, 
										CTriasApp *pApp, 
										CGeoDoc   *pDoc, 
						  INITOBJWINCOLLECTIONPROC pICProc, 
										DWORD      dwData);

/* IUnknown methods */
	STDMETHOD (QueryInterface)(REFIID riid, LPVOID *ppv);
	STDMETHOD_(ULONG, AddRef )(void);
	STDMETHOD_(ULONG, Release)(void);

/* IEnumVARIANT methods */
	STDMETHOD(Next )(ULONG celt, VARIANT *rgvar, ULONG *pceltFetched);
	STDMETHOD(Skip )(ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(LPENUMVARIANT *ppenum);
	
inline 	ULONG Count (void) { return m_pOWArray -> Count(); }
 
inline	HRESULT GetObjectWinDisp (ULONG lIndex, LPVOID *ppDisp)     { return m_pOWArray -> GetObjectWinDisp (lIndex, ppDisp); }
inline  HRESULT GetObjectWinDisp (LPCSTR pObWinStr, LPVOID *ppDisp) { return m_pOWArray -> GetObjectWinDisp (pObWinStr, ppDisp); }
inline  HRESULT GetObjectWinDispValue (HWND hWnd, LPVOID *ppDisp)   { return m_pOWArray -> GetObjectWinDispValue (hWnd, ppDisp); }

friend class CGeoObjectWins;
friend class CGeoObjectWinsPro;
};

#endif //_ENUMOBWS_HXX
