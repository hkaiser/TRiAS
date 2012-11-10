// Undo/Redo für TextObjekt löschen -------------------------------------------
// File: UNDOMODO.HXX

#if !defined(_UNDOMODO_HXX)
#define _UNDOMODO_HXX

class CUndoRedoModifyObject : 
	public IUndoRedoModifyObject 
{
private:
	DWORD m_dwRefCnt;
	LPFNDESTROYED m_pfnDestroy;

	CObjGeometrie m_ogOld;
	CObjGeometrie m_ogNew;

	RECT m_rcObj;

	unsigned int m_fInitialized : 1;
	unsigned int m_fRect : 1;

protected:
	BOOL FInit (LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc);

		~CUndoRedoModifyObject (void);

public:
		CUndoRedoModifyObject (LPFNDESTROYED pfnDestroy);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IUndoRedo methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS_ signed char **pDesc);
	STDMETHOD(Undo)(THIS);
	STDMETHOD(Redo)(THIS);

// *** IUndoRedoModifyObject ***
	STDMETHOD(Init)(THIS_ LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc /* = NULL */);

// sonstige Member
inline	BOOL isInitialized (void) 
		{ return m_fInitialized ? true : false; }
inline	void Initialized (BOOL fInit = true) 
		{ m_fInitialized = fInit ? true : false; }
};

#endif // _UNDOMODO_HXX
