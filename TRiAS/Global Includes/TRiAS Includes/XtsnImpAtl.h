// Basisklasse für GeoDataImport-Interface in einer Erweiterung ---------------
// File: XTSNIMPATL.H

#if !defined(_XTSNIMPATL_H)
#define _XTSNIMPATL_H

class CImportGeoData : 
	public IImportGeoData, 
	public IImportGeoDataWithResult,
	public IImportGeoDataSelectCS
{
public:
		CImportGeoData (void) {}
		~CImportGeoData (void) {}

// IImportGeoData methods 
	STDMETHOD_(DWORD, Capabilities)(THIS);
	STDMETHOD(Configure) (THIS_ HWND hWnd);
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags);
	STDMETHOD(GetConfigInfo) (THIS_ IEnumString **ppEnumCfg, DWORD dwReserved);

// IImportGeoDataWithResult methods 
	STDMETHOD(ImportDataWithResult) (THIS_ IEnumString *pEnumFiles, 
		DWORD dwFlags, IProgressIndicator *pIStatus, IEnumLONG **ppIObjs);

// IImportGeoDataSelectCS methods
	STDMETHOD(put_CS) (THIS_ IUnknown *pICS);
};

#endif // _XTSNIMPATL_H
