// Definitions, classes, and prototypes for a DLL that provides objects to any 
// other object user.
// File: IMPXTCF.HXX

#if !defined(_IMPXTCF_HXX)
#define _IMPXTCF_HXX

// object-destroyed-callback --------------------------------------------------
extern DESTROYNOTIFYPROC ObjectDestroyed;

#include "syncthrd.hxx"

// This class factory object creates VisModule objects.
class CXtensionClassFactory : public IClassFactory2, public CSyncMonitor {
private:
	ULONG		m_dwRefCnt;		// Reference count on class object

protected:	
	HRESULT CreateAnObject (LPUNKNOWN punkOuter, 
			REFIID riid, LPVOID FAR *ppvObj);

public:
		CXtensionClassFactory (void);
		~CXtensionClassFactory (void);

// IUnknown members
	STDMETHODIMP QueryInterface (REFIID, LPVOID FAR *);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

// IClassFactory members
	STDMETHODIMP CreateInstance (LPUNKNOWN, REFIID, LPVOID FAR *);
        STDMETHODIMP LockServer (BOOL);

//  IClassFactory2 methods
	STDMETHOD(GetLicInfo)(THIS_ LPLICINFO pLicInfo);
	STDMETHOD(RequestLicKey)(THIS_ DWORD dwResrved, BSTR FAR* pbstrKey);
	STDMETHOD(CreateInstanceLic)(THIS_ LPUNKNOWN pUnkOuter,
		LPUNKNOWN pUnkReserved, REFIID riid, BSTR bstrKey,
		LPVOID FAR* ppvObject);
};
typedef CXtensionClassFactory *LPXTENSIONCF;

#endif // _IMPXTCF_HXX
