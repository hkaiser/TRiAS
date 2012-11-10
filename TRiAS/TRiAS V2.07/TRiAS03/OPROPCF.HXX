// ClassFactory für ObjektEigenschaften ---------------------------------------
// File: OPROPCF.HXX

#if !defined(_OPROPCF_HXX)
#define _OPROPCF_HXX

class CObjPropCF : public IClassFactory {
protected:
	ULONG m_cRef;
	CLSID m_clsID;

public:
		CObjPropCF (REFCLSID rClsID);
		~CObjPropCF (void);

// IUnknown members
	STDMETHODIMP QueryInterface (REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef (void);
        STDMETHODIMP_(ULONG) Release (void);

// IClassFactory members
        STDMETHODIMP CreateInstance (LPUNKNOWN, REFIID, LPVOID *);
        STDMETHODIMP LockServer (bool);
};

#endif // _OPROPCF_HXX
