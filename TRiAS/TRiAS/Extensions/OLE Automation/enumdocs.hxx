// Enumerator der Docs --------------------------
// File: ENUMDOCS.HXX

#if !defined(_ENUMDOCS_HXX)
#define _ENUMDOCS_HXX

class CGeoDocsArray;


class CEnumDocs : public IEnumVARIANT {

private:
	DWORD m_dwRefCnt;			// ReferenceCount
	ULONG m_iCurrent;			// aktuelle Doc
	ULONG m_ulCount;			// Gesamtanzahl im Enum
	class CGeoDocsArray *m_pDocsArray;	// alle Docs im Array

public:
		CEnumDocs (void);
		~CEnumDocs (void);
			
static CEnumDocs *CreateInstance (CGeoDocsArray *pArr);
static CEnumDocs *CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp,
			INITDOCCOLLECTIONPROC pICProc, DWORD dwData);

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
inline	void InitCount (void) { m_ulCount = m_pDocsArray -> Count(); }

inline	char * GetDoc (ULONG lIndex) { return m_pDocsArray -> Value (lIndex); }
inline 	char * GetDoc (LPCSTR bstrName) { return m_pDocsArray -> Value (bstrName); }

inline  HRESULT GetDocDisp (ULONG lIndex, DDocument **ppDoc) { return m_pDocsArray->GetDocDisp (lIndex, ppDoc); }
inline  HRESULT GetDocDisp (LPCSTR pIdStr, DDocument **ppDoc) { return m_pDocsArray->GetDocDisp (pIdStr, ppDoc); }

inline	bool DeleteDoc (LPCSTR bName) { return m_pDocsArray -> DeleteDoc (bName); }

friend class CGeoDocs;
friend class CGeoDocsPro;
};

#endif //_ENUMDOCS_HXX
