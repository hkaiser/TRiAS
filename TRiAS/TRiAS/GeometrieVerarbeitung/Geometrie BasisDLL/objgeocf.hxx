// Definitions, classes, and prototypes for a DLL that provides objects to any 
// other object user.
// File: OBJGEOCF.HXX
// H. Kaiser

#if !defined(_OBJGEOCF_HXX)
#define _OBJGEOCF_HXX

// object-destroyed-callback --------------------------------------------------
extern DESTROYNOTIFYPROC ObjectDestroyed;

// This class factory object creates PropertySheetHandler objects.
class ObjektGeometrieCF : public IClassFactory {
private:
	ULONG		m_dwRefCnt;		// Reference count on class object

protected:	
	HRESULT CreateAnObject (LPUNKNOWN punkOuter, 
			REFIID riid, LPVOID FAR *ppvObj);

public:
		ObjektGeometrieCF (void);
		~ObjektGeometrieCF (void);

// IUnknown members
	STDMETHODIMP QueryInterface (REFIID, LPVOID FAR *);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

// IClassFactory members
	STDMETHODIMP CreateInstance (LPUNKNOWN, REFIID, LPVOID FAR *);
	STDMETHODIMP LockServer (BOOL);
};

#endif // _OBJGEOCF_HXX
