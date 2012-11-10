// ArrayContainer, der die Idents einer GeoFeatures Collection hält -------------
// File: FTSARRAY.HXX

#if !defined(_FTSARRAY_HXX)
#define _FTSARRAY_HXX

class CGeoFeatureBase;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef CArrayContainer CGeoFtsArrayBase;
typedef CRing CGeoFtsArrayRing;
typedef CSyncThread CGeoFtsArraySync;
typedef CLock CGeoFeatureBaseLock;
#else
typedef container_wrappers::CArrayOnStl<CGeoFeatureBase *> CGeoFtsArrayBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

class CGeoFtsArray : 
	public CGeoFtsArrayBase 
{ 
protected:
	void UserDelete (void *);
	
public:
		CGeoFtsArray (void);
		~CGeoFtsArray (void) { EveryDelete(); }
		
static CGeoFtsArray *CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, void *pViewClsObj, 
	INITFEATCOLLECTIONPROC pICProc, DWORD dwData, DWORD dwFlags = PROPCAPS_NONE);

	BOOL FInit (void);

	CGeoFtsArray *Copy (void);	// Array kopieren
	
// sonstige Member
	char *Value (ULONG lIndex);		// liefert Ident eines Elements
	char *Value (LPCSTR bstrName);	// liefert Ident über KurzText

	HRESULT GetFeatureDisp (ULONG lIndex, DGeoFeature **ppIFeat);
	HRESULT GetFeatureDisp (LPCSTR pFtStr, DGeoFeature **ppIFeat); 

	HRESULT Refresh();

	long hasFeature (LPCSTR bName);	// returns valid index
	bool DeleteFeature (LPCSTR bName);

	long Count (void);			// returns number of valid GeoFeatures
};

//typedef IDispatch CGeoFeatureDispatch;
//DeclareLock (CGeoFtsArray, CGeoFeatureDispatch);
DeclareLockStl (CGeoFtsArray, CGeoFeatureBase);

#endif // _FTSARRAY_HXX
