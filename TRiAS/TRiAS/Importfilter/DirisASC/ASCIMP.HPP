// Import aus dem DIRIS-ASC Austaschformat ------------------------------------
// File: IMPASC.HXX

#if !defined(_IMPASC_HXX)
#define _IMPASC_HXX

///////////////////////////////////////////////////////////////////////////////
// LizensierungsKlasse
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

class CMyLicense
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR bstrKey;

		USES_CONVERSION;
		if ((GetLicenseKey (0, &bstrKey) && !wcscmp (bstrKey, bstr)) ||
			 ::SetLicensed (OLE2A(bstr)))
		{
			return TRUE;
		}
		return FALSE;
	}

	static BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static BOOL IsLicenseValid() { return g_fGlobalLic || ::GetLicensed(); }
};

///////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
#import	"tlb/TRiASCS.tlb" \
	raw_interfaces_only raw_native_types no_namespace named_guids 

///////////////////////////////////////////////////////////////////////////////
// Eigentliche Erweiterung
EXTERN_C const GUID IID_IImportGeoData;
EXTERN_C const GUID IID_IImportGeoDataWithResult;
EXTERN_C const GUID CLSID_ImpAscExtension;

class CImpAscExtension : 
	public CTriasExtension,
	public CImportGeoData,
	public CComCoClass<CImpAscExtension, &CLSID_ImpAscExtension>
{
private:
	HWND m_hWnd;
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> m_CS;

public:
		CImpAscExtension (void);
		~CImpAscExtension (void);

	BEGIN_COM_MAP(CImpAscExtension)
		COM_INTERFACE_ENTRY(IImportGeoData)				// aus CImportGeoData
		COM_INTERFACE_ENTRY(IImportGeoDataWithResult)	// aus CImportGeoData
		COM_INTERFACE_ENTRY(IImportGeoDataSelectCS)	// aus CImportGeoData
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CImpAscExtension, g_pTE)
	DECLARE_CLASSFACTORY2(CMyLicense)

// *** ITriasExtension2
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

// *** IImportGeoData methods
	STDMETHOD_(DWORD, Capabilities)(THIS);
	STDMETHOD(Configure) (THIS_ HWND hWnd);
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags);

// *** IImportGeoDataWithResult methods
	STDMETHOD(ImportDataWithResult) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags, IProgressIndicator *pIStatus, IEnumLONG **ppIObjs);

// *** IImportGeoDataSelectCS methods
	STDMETHOD(put_CS) (THIS_ IUnknown *pICS);

	STDMETHODIMP ImportASC (char *pFile);

// Access the stored coord system
	IUnknown *get_CS() const { return m_CS; }
};

#endif // _IMPASC_HXX
