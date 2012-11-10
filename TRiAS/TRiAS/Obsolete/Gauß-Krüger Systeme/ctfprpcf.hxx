// Definitions, classes, and prototypes for a DLL that provides objects to any 
// other object user.
// File: CTFPRPCF.HXX

#if !defined(_CTFPRPCF_HXX)
#define _CTFPRPCF_HXX

// object-destroyed-callback --------------------------------------------------
typedef void (FAR PASCAL DESTROYNOTIFYPROC)(void);
typedef DESTROYNOTIFYPROC *DESTROYNOTIFYPROCPTR;

extern DESTROYNOTIFYPROC ObjectDestroyed;

// This class factory object creates PropertySheetHandler objects.
class CCTFPropPageCF : public IClassFactory {
private:
	LONG		m_dwRefCnt;		// Reference count on class object

protected:	
	HRESULT CreateAnObject (LPUNKNOWN punkOuter, 
			REFIID riid, LPVOID FAR *ppvObj);

public:
		CCTFPropPageCF (void);
		~CCTFPropPageCF (void);

// IUnknown members
	STDMETHODIMP QueryInterface (REFIID, LPVOID FAR *);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

// IClassFactory members
	STDMETHODIMP CreateInstance (LPUNKNOWN, REFIID, LPVOID FAR *);
	STDMETHODIMP LockServer (BOOL);
};

#if defined(WIN32)
inline LONG piInterlockedIncrement (LONG *pVal) 
{ 
	if (IsWin32s()) return ++(*pVal);
	else return InterlockedIncrement (pVal); 
}
inline LONG piInterlockedDecrement (LONG *pVal) 
{
	if (IsWin32s()) return --(*pVal);
	else return InterlockedIncrement (pVal); 
}
#else
inline LONG piInterlockedIncrement (LONG *pVal) { return ++(*pVal); }
inline LONG piInterlockedDecrement (LONG *pVal) { return --(*pVal); }
#endif // !WIN32

#endif // _CTFPRPCF_HXX
