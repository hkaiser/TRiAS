// Basisklasse für GeoDataImport-Interface in einer Erweiterung ---------------
// File: XTSNIMP.HXX

#if !defined(_XTSNIMP_HXX)
#define _XTSNIMP_HXX

class CImportGeoData 
:	public IImportGeoData,
	public IImportGeoDataSelectCS
{
private:
	DWORD 		m_dwRefCnt;	// reference count (debugging purposes only)
	LPUNKNOWN 	m_pUnk;		// controlling unknown

public:
		CImportGeoData (LPUNKNOWN pUnk);
		~CImportGeoData (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IImportGeoData methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS);
	STDMETHOD(Configure) (THIS_ HWND hWnd);
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags);
	STDMETHOD(GetConfigInfo) (THIS_ IEnumString **ppEnumCfg, DWORD dwReserved);

// *** IImportGeoDataSelectCS methods
	STDMETHOD(put_CS) (THIS_ IUnknown *pICS);
};

#endif // _XTSNIMP_HXX
