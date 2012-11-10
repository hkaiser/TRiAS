// ArrayContainer, Object Windows Collection -------------
// File: OBWARRAY.HXX

#if !defined(_OBWARRAY_HXX)
#define _OBWARRAY_HXX

class CGeoObjectWin;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef CArrayContainer CGeoObjWinArrayBase;
typedef CRing CGeoObjWinArrayRing;
typedef CSyncThread CGeoObjWinArraySync;
typedef CLock CGeoObjectWinLock;
#else
typedef container_wrappers::CArrayOnStl<CGeoObjectWin *> CGeoObjWinArrayBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

class CGeoObjWinArray : 
	public CGeoObjWinArrayBase 
{
private:
	INITOBJWINCOLLECTIONPROC m_pICProc;

protected:
	void UserDelete (void *);
	
public:
		 CGeoObjWinArray (void);
		~CGeoObjWinArray (void) { EveryDelete(); }
		
static CGeoObjWinArray *CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	INITOBJWINCOLLECTIONPROC pICProc, DWORD dwData);
	BOOL FInit (void);

	CGeoObjWinArray *Copy (void);	// Array kopieren

// sonstige Member
	HWND Value (LONG lIndex);		// liefert eines Elements
	HWND Value (LPCSTR pName);		// liefert über KurzText

	HRESULT GetObjectWinDisp (long lIndex, LPVOID *ppDisp);
	HRESULT GetObjectWinDisp (LPCSTR pObWinStr, LPVOID *ppDisp); 
	HRESULT GetObjectWinDispValue (HWND hWnd, LPVOID *ppDisp);
	HRESULT Refresh();

	long hasObjectWin (HWND hWnd);		// returns valid index
	bool DeleteObjectWin (HWND hWnd);

	long Count (void);			// returns number of valid Windows
};
DeclareLockStl (CGeoObjWinArray, CGeoObjectWin);

#endif // _OBWARRAY_HXX
