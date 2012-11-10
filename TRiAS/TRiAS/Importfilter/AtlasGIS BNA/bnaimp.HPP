// Import aus dem PolyGIS-BNA Austaschformat ------------------------------------
// File: IMPBNA.HXX

#if !defined(_IMPBNA_HXX)
#define _IMPBNA_HXX

///////////////////////////////////////////////////////////////////////////////
#include "bnaimp.h"
#include "status.hxx"

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

//////////////////////////////////////////////////////////////////////////////
// Eigentliche Erweiterung
EXTERN_C const GUID IID_IImportGeoData;
EXTERN_C const GUID IID_IImportGeoDataWithResult;
EXTERN_C const GUID CLSID_ImpBnaExtension;

class CImpBnaExtension : 
	public CTriasExtension,
	public CImportGeoData,
	public CComCoClass<CImpBnaExtension, &CLSID_ImpBnaExtension>
{
public:
	CImpBnaExtension (void);
	~CImpBnaExtension (void);

	BEGIN_COM_MAP(CImpBnaExtension)
		COM_INTERFACE_ENTRY(IImportGeoData)				// aus CImportGeoData
		COM_INTERFACE_ENTRY(IImportGeoDataWithResult)	// aus CImportGeoData
		COM_INTERFACE_ENTRY(IImportGeoDataSelectCS)	// aus CImportGeoData
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

	static HRESULT WINAPI UpdateRegistry(BOOL bRegister);
//	DECLARE_REGISTRY_RESOURCEID(IDR_POLYGISFEATURE_REG)	// registry
	DECLARE_NOT_AGGREGATABLE_SINGLE(CImpBnaExtension, g_pTE)
	DECLARE_CLASSFACTORY2(CMyLicense)

// *** ITriasExtension2
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

// *** IImportGeoData methods
	STDMETHOD_(DWORD, Capabilities)(THIS);
	STDMETHOD(Configure) (THIS_ HWND hWnd);
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags);
	// Neu ??
	STDMETHOD(GetConfigInfo) (THIS_ IEnumString **ppEnumCfg, DWORD dwReserved);

// *** IImportGeoDataWithResult methods
	STDMETHOD(ImportDataWithResult) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags, IProgressIndicator *pIStatus, IEnumLONG **ppIObjs);

// *** IImportGeoDataSelectCS methods
	STDMETHOD(put_CS) (THIS_ IUnknown *pICS);

private:
//KK021024
	TCHAR szDataType[3];
	DWORD m_dwFlags;
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> m_CS;

	char *DataType(void) { return szDataType;} 


	HRESULT ImportBNA (char const *pFile);
	HRESULT TestImportBNA (char *pFile, CStatusDlg *pDlg = NULL);

	HRESULT ImportRegistry (int iTyp);
	HRESULT ImportRegistryStandard (int iTyp, char const * pKey);
	HRESULT DefineRegistryStandard();
	HRESULT ImportRegistryType (int iTyp, UINT uiThemaId);
	HRESULT ImportRegistryType (int iTyp, UINT uiThemaId, UINT uiDefaultId);

	HRESULT DATImportRegistry (int iTyp);
	HRESULT ImportRegistryDATType (int iTyp, UINT uiThemaId, UINT uiDefaultId);
	HRESULT ImportRegistryDATStandard (int iTyp, char const * pKey);

	HRESULT PolyParse (FILE *pFile);

	//KK020904-NOT ===========================================================
	HRESULT PolyParseDat (FILE *pFile);
	//KK020904-NOT ===========================================================
	HRESULT VideoParseDat (FILE *pFile, LPCSTR pcFile);

	HRESULT GCAParseDat (FILE *pFile, LPCSTR pcFile);

	HRESULT PolyParseHeader (FILE *pFile, CStatusDlg *);
	bool SkipObject(FILE *pFile);

public:
	HRESULT InitConfigDataFromRegistry();

// Access the stored coord system
	IUnknown *get_CS() const { return m_CS; }
};

#endif // _IMPBNA_HXX
