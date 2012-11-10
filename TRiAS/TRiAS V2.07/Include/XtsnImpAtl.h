// Basisklasse für GeoDataImport-Interface in einer Erweiterung ---------------
// File: XTSNIMPATL.H

#if !defined(_XTSNIMPATL_H)
#define _XTSNIMPATL_H

class CImportGeoData : 
	public IImportGeoData 
{
public:
		CImportGeoData (void) {}
		~CImportGeoData (void) {}

// *** IImportGeoData methods ***
	STDMETHOD_(DWORD, Capabilities)(THIS);
	STDMETHOD(Configure) (THIS_ HWND hWnd);
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags);
	STDMETHOD(GetConfigInfo) (THIS_ IEnumString **ppEnumCfg, DWORD dwReserved);
};

#endif // _XTSNIMPATL_H
