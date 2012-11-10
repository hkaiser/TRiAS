// Enumerator der Objektklassen in einem CIDentArray --------------------------
// File: ENUMCLSS.HXX

#if !defined(_ENUMCLSS_HXX)
#define _ENUMCLSS_HXX

class CEnumClasses : public IEnumVARIANT {
private:
	DWORD m_dwRefCnt;			// ReferenceCount
	ULONG m_iCurrent;			// aktuelle Objektklasse
	ULONG m_ulCount;			// GesamtAnzahl im Enum
	CIdentArray *m_pIdArray;	// alle Objektklassen im Array

public:
		CEnumClasses (void);
		~CEnumClasses (void);
			
static CEnumClasses *CreateInstance (CIdentArray *pArr);
static CEnumClasses *CreateInstance (LPUNKNOWN  pUnk, 
									 CTriasApp *pApp,
									 CGeoDoc   *pDoc, 
						INITCLASSCOLLECTIONPROC pICProc, 
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
inline	void InitCount (void) { m_ulCount = m_pIdArray -> Count(); }

inline  HRESULT GetClassDisp (ULONG lIndex, LPVOID *ppDisp) { return m_pIdArray->GetClassDisp (lIndex, ppDisp); }
inline  HRESULT GetClassDisp (LPCSTR pIdStr, LPVOID *ppDisp) { return m_pIdArray->GetClassDisp (pIdStr, ppDisp); }
inline  HRESULT GetClassDispValue (ULONG lIdent, LPVOID *ppDisp) { return m_pIdArray->GetClassDispValue (lIdent, ppDisp); }

friend class CClasses;
friend class CClassesPro;
};

#endif _ENUMCLSS_HXX
