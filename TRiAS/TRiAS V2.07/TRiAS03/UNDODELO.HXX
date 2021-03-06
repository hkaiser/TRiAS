// Undo/Redo f�r TextObjekt l�schen -------------------------------------------
// File: UNDODELT.HXX

#if !defined(_UNDODELO_HXX)
#define _UNDODELO_HXX

class CUndoRedoDeleteObject : public IUndoRedoDeleteObject {
private:
	DWORD m_dwRefCnt;

	LPFNDESTROYED m_pfnDestroy;
	unsigned int m_fInitialized : 1;

	CObjGeometrie m_ogObj;
	string m_strText;
	RECT m_rcObj;
	unsigned int m_fRect : 1;

protected:
	BOOL FInit (LONG lONr, LPCRECT prc);

		~CUndoRedoDeleteObject (void);

public:
		CUndoRedoDeleteObject (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoDeleteText ***
	STDMETHOD(Init)(THIS_ LONG lONr, LPCRECT prc /* = NULL */);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDODELO_HXX
