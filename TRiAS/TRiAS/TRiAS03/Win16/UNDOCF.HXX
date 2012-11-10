// ClasFactory für Undo/Redo-Objekte ------------------------------------------
// File: UNDOCF.HXX

#if !defined(_UNDOCF_HXX)
#define _UNDOCF_HXX

class CUndoRedoClassFactory : public IClassFactory {
protected:
	ULONG m_cRef;

public:
		CUndoRedoClassFactory (void);
		~CUndoRedoClassFactory (void);

// IUnknown members
	STDMETHODIMP QueryInterface (REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef (void);
        STDMETHODIMP_(ULONG) Release (void);

// IClassFactory members
        STDMETHODIMP CreateInstance (LPUNKNOWN, REFIID, LPVOID *);
        STDMETHODIMP LockServer (bool);
};
typedef CUndoRedoClassFactory  *LPUNDOREDOCLASSFACTORY;

#endif // _UNDOCF_HXX
