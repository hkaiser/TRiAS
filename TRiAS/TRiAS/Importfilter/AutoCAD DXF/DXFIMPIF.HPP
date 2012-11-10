// ImportInterface-Implementation für den Import von DXF-Daten -----------
// File: DXFIMPIF.HPP

#if !defined(_DXFIMPIF_HPP)
#define _DXFIMPIF_HPP

///////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
#import	"tlb/TRiASCS.tlb" \
	raw_interfaces_only raw_native_types no_namespace named_guids 

///////////////////////////////////////////////////////////////////////////////
// Importinterface
class CImportAutoCadDxf : public CImportGeoData {
private:
	HWND m_hWnd;		// ParentFenster für evtl. Dialoge etc.
	ITRiASCSPtr m_CS;

public:
    CImportAutoCadDxf (LPUNKNOWN pUnk);
    ~CImportAutoCadDxf (void);

    STDMETHODIMP ImportDXF (char *pFile, BOOL bFirst);

// *** IImportGeoData methods
	STDMETHOD_(DWORD, Capabilities)(THIS);
	STDMETHOD(Configure) (THIS_ HWND hWnd);
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags);  
	STDMETHODIMP GetConfigInfo (IEnumString **ppEnumCfg, DWORD dwReserved);

// *** IImportGeoDataSelectCS methods
	STDMETHOD(put_CS) (THIS_ IUnknown *pICS);

	IUnknown *get_CS() const { return m_CS; }
};

#endif // _DXFIMPIF_HPP
