// ImportInterface-Implementation für den Import von DirisAsc-Daten -----------
// File: ASCIMPIF.HPP

#if !defined(_ASCIMPIF_HPP)
#define _ASCIMPIF_HPP

class CImportDirisAsc : public CImportGeoData {
private:
	HWND m_hWnd;		// ParentFenster für evtl. Dialoge etc.

public:
		CImportDirisAsc (LPUNKNOWN pUnk);
		~CImportDirisAsc (void);

	STDMETHODIMP ImportASC (char *pFile);

// *** IImportGeoData methods
	STDMETHOD_(DWORD, Capabilities)(THIS);
	STDMETHOD(Configure) (THIS_ HWND hWnd);
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags);
};

#endif // _ASCIMPIF_HPP
