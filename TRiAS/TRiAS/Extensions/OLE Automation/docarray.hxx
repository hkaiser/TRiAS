// ArrayContainer, der Docs Collection hält -------------
// File: DOCARRAY.HXX

#if !defined(_DOCARRAY_HXX)
#define _DOCARRAY_HXX

class CGeoDoc;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef CArrayContainer CGeoDocsArrayBase;
typedef CRing CGeoDocsArrayRing;
typedef CSyncThread CGeoDocsArraySync;
typedef CLock CGeoDocLock;
#else
typedef container_wrappers::CArrayOnStl<CGeoDoc *> CGeoDocsArrayBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

class CGeoDocsArray : 
	public CGeoDocsArrayBase 
{
private:
	INITDOCCOLLECTIONPROC m_pICProc;

protected:
	void UserDelete (void *);
	
public:
		CGeoDocsArray (void);
		~CGeoDocsArray (void) { EveryDelete(); }
		
static CGeoDocsArray *CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, 
					INITDOCCOLLECTIONPROC pICProc, DWORD dwData);

	BOOL FInit (void);

	CGeoDocsArray *Copy (void);	// Array kopieren
	
// sonstige Member

	char *Value (ULONG lIndex);	// liefert Docs eines Elements
	char *Value (LPCSTR bstrName);	// liefert Docs über Text
	
	HRESULT GetDocDisp (ULONG lIndex, DDocument **ppDoc);
	HRESULT GetDocDisp (LPCSTR pDocStr, DDocument **ppDoc);
	HRESULT Refresh();
		
	long hasDoc (LPCSTR bName);	// returns valid index
	bool DeleteDoc (LPCSTR bName);

	long Count (void);			// returns number of valid documents
};

//typedef IDispatch CGeoDocDispatch;
//DeclareLock (CGeoDocsArray, CGeoDocDispatch);
DeclareLockStl (CGeoDocsArray, CGeoDoc);

#endif // _DOCARRAY_HXX
