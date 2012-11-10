// ArrayContainer, der die Idents einer GeoClassesCollection hält -------------
// File: CLSARRAY.HXX

#if !defined(_CLSARRAY_HXX)
#define _CLSARRAY_HXX

class CClass;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef CArrayContainer CIdentArrayBase;
typedef CRing CIdentArrayRing;
typedef CSyncThread CIdentArraySync;
typedef CLock CClassLock;
#else
typedef container_wrappers::CArrayOnStl<CClass *> CIdentArrayBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

class CIdentArray : 
	public CIdentArrayBase 
{ 
private:
	INITCLASSCOLLECTIONPROC m_pICProc;

protected:
	void UserDelete (void *);
	
public:
		CIdentArray (void);
		~CIdentArray (void) { EveryDelete(); }
		
static CIdentArray *CreateInstance (
	LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	INITCLASSCOLLECTIONPROC pICProc, DWORD dwData);
	bool FInit (void);

	CIdentArray *Copy (void);	// Array kopieren
	
// sonstige Member
//	HRESULT Item (ULONG lIndex, LPVOID *ppdisp);	// liefert IDispatch eines Elements

	ULONG Value (ULONG lIndex);	// liefert Ident eines Elements
	ULONG Value (LPCSTR bstrName);	// liefert Ident über KurzText
	
	HRESULT GetClassDisp (ULONG lIndex, LPVOID *ppDisp);
	HRESULT GetClassDisp (LPCSTR pIdStr, LPVOID *ppDisp);
	HRESULT GetClassDispValue (ULONG lIdent, LPVOID *ppDisp);

	HRESULT Refresh (void);

	long hasIdent (ULONG lIdent);	// returns valid index
	bool DeleteClass (ULONG lIdent);

	long Count (void);			// returns number of valid GeoClasses
};
DeclareLockStl (CIdentArray, CClass);

#endif // _CLSARRAY_HXX
