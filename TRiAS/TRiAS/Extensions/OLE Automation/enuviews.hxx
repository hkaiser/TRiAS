// Enumerator der Views --------------------------
// File: ENUVIEWS.HXX

#if !defined(_ENUVIEWS_HXX)
#define _ENUVIEWS_HXX

class CEnumViews : 
	public IEnumVARIANT 
{
private:
	DWORD m_dwRefCnt;			// ReferenceCount
	ULONG m_iCurrent;			// aktuelle View
	class CGeoViewsArray *m_pViewsArray;	// alle Wiews im Array

public:
		CEnumViews (void);
		~CEnumViews (void);
			
static CEnumViews *CreateInstance (CGeoViewsArray *pArr);
static CEnumViews *CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
								   INITVIEWCOLLECTIONPROC pICProc, DWORD dwData);

/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppv);
	STDMETHOD_(ULONG, AddRef)(void);
	STDMETHOD_(ULONG, Release)(void);

/* IEnumVARIANT methods */
	STDMETHOD(Next)(ULONG celt, VARIANT *rgvar, ULONG *pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(LPENUMVARIANT *ppenum);
	
inline 	ULONG Count (void) { return m_pViewsArray -> Count(); }

inline	char * GetView (ULONG lIndex) { return m_pViewsArray -> Value (lIndex); }
inline 	char * GetView (LPCSTR bstrName) { return m_pViewsArray -> Value (bstrName); }

inline  HRESULT GetViewDisp (ULONG lIndex, LPVOID *ppDisp) { return m_pViewsArray->GetViewDisp (lIndex, ppDisp); }
inline  HRESULT GetViewDisp (LPCSTR pIdStr, LPVOID *ppDisp) { return m_pViewsArray->GetViewDisp (pIdStr, ppDisp); }

inline	bool DeleteView (LPCSTR bName) { return m_pViewsArray -> DeleteView (bName); }

friend class CGeoViews;
friend class CGeoViewsPro;
};

#endif //_ENUVIEWS_HXX
