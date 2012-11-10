// Definitions, classes, and prototypes for a DLL that provides objects to any 
// other object user.
// File: DCUSTVIS.HXX

#if !defined(_DCUSTVIS_HXX)
#define _DCUSTVIS_HXX

// object-destroyed-callback --------------------------------------------------
extern "C" {
	void FAR PASCAL ObjectDestroyed(void);
}

// This class factory object creates VisModule objects.
class CVisModuleClassFactory : public IClassFactory {
protected:
	ULONG	m_cRef;         // Reference count on class object

public:
		CVisModuleClassFactory (void);
		~CVisModuleClassFactory (void);

// IUnknown members
	STDMETHODIMP QueryInterface (REFIID, LPVOID FAR *);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

// IClassFactory members
	STDMETHODIMP CreateInstance (LPUNKNOWN, REFIID, LPVOID FAR *);
        STDMETHODIMP LockServer (BOOL);
};
typedef CVisModuleClassFactory *LPCVisModuleClassFactory;


#endif // _DCUSTVIS_HXX
