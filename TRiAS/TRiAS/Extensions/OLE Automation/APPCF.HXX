// ApplicationClassFactory ----------------------------------------------------
// File: APPCF.HXX

#if !defined(_APPCF_HXX)
#define _APPCF_HXX

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface2(_DApplication, IID_DApplication);

class CTriasAppCF : 
	public IClassFactory 
{
private:
	ULONG m_dwRefCnt;
	W_DApplication m_App;

public:
		CTriasAppCF (CTriasApp *pApp);
		~CTriasAppCF (void);

static IClassFactory *CreateInstance (CTriasApp *pApp);

// ***IClassFactory methods
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);
	STDMETHOD_(ULONG, AddRef)(void);
	STDMETHOD_(ULONG, Release)(void);

	STDMETHOD(CreateInstance)(IUnknown *punkOuter, REFIID riid, void **ppv);
	STDMETHOD(LockServer)(BOOL fLock);
};

#endif // _APPCF_HXX
