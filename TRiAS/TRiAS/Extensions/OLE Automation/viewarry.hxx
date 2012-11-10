// ArrayContainer, der View Collection hält -------------
// File: VIEWARRY.HXX

#if !defined(_VIEWARRY_HXX)
#define _VIEWARRY_HXX

class CGeoView;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef CArrayContainer CGeoViewsArrayBase;
typedef CRing CGeoViewsArrayRing;
typedef CSyncThread CGeoViewsArraySync;
typedef CLock CGeoViewLock;
#else
typedef container_wrappers::CArrayOnStl<CGeoView *> CGeoViewsArrayBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

class CGeoViewsArray : 
	public CGeoViewsArrayBase 
{
private:
	INITVIEWCOLLECTIONPROC m_pICProc;

protected:
	void UserDelete (void *);
	
public:
		CGeoViewsArray (void);
		~CGeoViewsArray (void) { EveryDelete(); }
		
static CGeoViewsArray *CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
			 						   INITVIEWCOLLECTIONPROC pICProc, DWORD dwData);

	BOOL FInit (void);

	CGeoViewsArray *Copy (void);	// Array kopieren
	
// sonstige Member
	char *Value (ULONG lIndex);	// liefert Views eines Elements
	char *Value (LPCSTR bstrName);	// liefert Views über Text
	
	HRESULT GetViewDisp (ULONG lIndex, LPVOID *ppDisp);
	HRESULT GetViewDisp (LPCSTR pViewStr, LPVOID *ppDisp);
	HRESULT Refresh();
		
	long hasView (LPCSTR bName);	// returns valid index
	bool DeleteView (LPCSTR bName);

	long Count (void);			// returns number of valid Views
};

//typedef IDispatch CGeoViewDispatch;
//DeclareLock (CGeoViewsArray, CGeoViewDispatch);
DeclareLockStl (CGeoViewsArray, CGeoView);

#endif // _VIEWARRY_HXX
