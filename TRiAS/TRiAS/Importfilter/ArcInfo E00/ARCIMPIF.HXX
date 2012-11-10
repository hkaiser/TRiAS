// ImportInterface-Implementation für den Import von DXF-Daten -----------
// File: ARCIMPIF.HXX

#if !defined(_ARCIMPIF_HXX)
#define _ARCIMPIF_HXX

///////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
#import	"tlb/TRiASCS.tlb" \
	raw_interfaces_only raw_native_types no_namespace named_guids 

///////////////////////////////////////////////////////////////////////////////
// Eigentliches Importinterface
class CImportArcInfo 
:	public CImportGeoData 
{
private:
	FILE *_pTempFile;
	char *_pCoverName;
// KK000328
	char *_pCompName;
	FILE *_pCompFile;

	BOOL m_bIsConfigured;	// wurde konfig.
	DWORD m_dwStartTime;
	BOOL m_bMultipleFiles;	// mehrere Dateien sel.
	Params OptParam;

	ITRiASCSPtr m_CS;
		
public:
    CImportArcInfo (LPUNKNOWN pUnk);
    ~CImportArcInfo (void);

    STDMETHODIMP ImportArcInfo (char *pFile);

// *** IImportGeoData methods
	STDMETHOD_(DWORD, Capabilities)(THIS);
	STDMETHOD(Configure) (THIS_ HWND hWnd);
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags);
	STDMETHOD(GetConfigInfo) (THIS_ IEnumString **ppEnumCfg, DWORD dwReserved);

// *** IImportGeoDataSelectCS methods
	STDMETHOD(put_CS)(THIS_ IUnknown *pICS);

	IUnknown *get_CS() const { return m_CS; }

protected:
	void _Reset (void);		// alle Werte rücksetzen
	Bool _CheckCover (CFileBuffer &Buffer);
	Bool _TransferImportFile (char *);
	ErrCode _OutputInfo (pchar pLine, FILE *pInFile);
	Bool _CreateTrees (void);
	void _DeleteTrees (void);
	Bool _GetDebugOutputFlag (void); 
	void _OutputNotImported (void);
};

#endif // _DXFIMPIF_HXX
