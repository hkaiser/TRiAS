// StandardDialog zum festlegen des ExportFormates ----------------------------
// File: IMPDLGS.HXX

#if !defined(_IMPDLGS_HXX)
#define _IMPDLGS_HXX

extern "C" UINT EXPORTTRIAS CALLBACK ImportFmtHookFcn (HWND, UINT, WPARAM, LPARAM);
#if !defined(WIN16)
extern "C" UINT EXPORTTRIAS APIENTRY ImportFmt40HookFcn (HWND, UINT, WPARAM, LPARAM);
#endif

// Struktur zur Beschreibung der ImportFilter ---------------------------------
typedef struct tagIMPORTFILTERINFO {
	string m_strProgID;	// ProgID des Filters
	string m_strFilterName;	// Bezeichnung des ImportFilters
	string m_strShortName;	// Formatbezeichner
	string m_strFilterExt;	// StandardExtension der Ausgabedatei
} IMPORTFILTERINFO;

class CImportDlg : public COpenDialog {
private:
	ExtensionList &m_rEL;

	char *m_pInFile;		// EingabeDateiName
	char *m_pInitPath;		// Anfangsverzeichnis
	char *m_pFileTypes;		// BeschreibungsString für Dialog
	
	char **m_ppFiles;		// alle EingabeDateien auf einen Blick
	int m_iCnt;

	int m_iNumFilters;		// Anzahl der installierten Filter
	int m_iIndex;

	IMPORTFILTERINFO *m_pFilterInfo; // Beschreibung dieser Filter
	LPIMPORTGEODATA m_pIImport;

	unsigned int m_fGeometry : 1;
	unsigned int m_fFeatures : 1;
	unsigned int m_fRelations : 1;
	unsigned int m_fVisualisation : 1;
	unsigned int m_fAnsiOem : 1;

	unsigned int m_fCanGeometry : 1;
	unsigned int m_fCanFeatures : 1;
	unsigned int m_fCanRelations : 1;
	unsigned int m_fCanVisualisation : 1;
	unsigned int m_fCanAnsiOem : 1;

	unsigned int m_fCanConfig : 1;
	unsigned int m_fMultiSel : 1;

	unsigned int m_fValid : 1;

	pWindow m_pParent;
	UINT m_iFileOKMessage;		// registrierte OK-Message

#if !defined(WIN16)
	LONG m_lSem;
#endif

	DatenBasisObjekt &m_rDBO;
	CoordTrans *m_pCTF;
	Window *m_pW;
			
protected:
// interne Initialisierungsfunktionen
	bool ReadFormats (ExtensionList &);	// Einlesen der FilterInfo's
	char *RetrieveAvailImportFormats (ExtensionList &);	// EingabeFormate lesen

	bool ReadFileName (void);	// Dateinamen holen
	int FindFilterExt (void);	// Filter über Erweiterung finden

	void UnLoadExtension (void);
	void UnLoadExtension (string &rstrProgID, string &rstrName);
	COleExtension *LoadExtension (string &rstrProgID, string &rstrName);

public:
// Konstruktor (Initialisierung des Dialogfensters)
		CImportDlg (pWindow, ExtensionList &rEL, DatenBasisObjekt &rDBO);
		~CImportDlg (void);

static CImportDlg *CreateInstance (pWindow, ExtensionList &, DatenBasisObjekt &);

	bool FInit (void);

// Memberfunktionen
	HRESULT GetImportIF (LPIMPORTGEODATA *pIImport);
	HRESULT GetStrings (LPENUMSTRING *pIStrings);

	DWORD GetFlags (void);
	void SetFlags (DWORD rgFlags);
	bool UpdateControls (int iIndex);
	void InitControls (HWND hDlg);

	LRESULT OnWmCommand (HWND, WPARAM, LPARAM);
	LRESULT OnWmInitDialog (HWND, HWND);
	LRESULT OnCdnTypeChange (HWND hDlg);

	bool isValid (void) { return m_fValid ? true : false; }

	bool FImportGeometry (void) { return m_fGeometry ? true : false; }
	bool FImportFeatures (void) { return m_fFeatures ? true : false; }
	bool FImportRelations (void) { return m_fRelations ? true : false; }
	bool FImportVisualisation (void) { return m_fVisualisation ? true : false; }
	bool FImportAnsiOem (void) { return m_fAnsiOem ? true : false; }

	void SetGeometry (bool fFlag) { m_fGeometry = fFlag ? true : false; }
	void SetFeatures (bool fFlag) { m_fFeatures = fFlag ? true : false; }
	void SetRelations (bool fFlag) { m_fRelations = fFlag ? true : false; }
	void SetVisualisation (bool fFlag) { m_fVisualisation = fFlag ? true : false; }
	void SetAnsiOem (bool fFlag) { m_fAnsiOem = fFlag ? true : false; }

	bool FCanGeometry (void) { return m_fCanGeometry ? true : false; }
	bool FCanFeatures (void) { return m_fCanFeatures ? true : false; }
	bool FCanRelations (void) { return m_fCanRelations ? true : false; }
	bool FCanVisualisation (void) { return m_fCanVisualisation ? true : false; }
	bool FCanAnsiOem (void) { return m_fCanAnsiOem ? true : false; }

	void SetCanGeometry (bool fFlag) { m_fCanGeometry = fFlag ? true : false; }
	void SetCanFeatures (bool fFlag) { m_fCanFeatures = fFlag ? true : false; }
	void SetCanRelations (bool fFlag) { m_fCanRelations = fFlag ? true : false; }
	void SetCanVisualisation (bool fFlag) { m_fCanVisualisation = fFlag ? true : false; }
	void SetCanAnsiOem (bool fFlag) { m_fCanAnsiOem = fFlag ? true : false; }

	bool FCanConfig (void) { return m_fCanConfig ? true : false; }
	void SetCanConfig (bool fFlag) { m_fCanConfig = fFlag ? true : false; }

	bool FMultiSel (void) { return m_fMultiSel ? true : false; }
	void SetMultiSel (bool fFlag) { m_fMultiSel = fFlag ? true : false; }

	bool FlagsInvalid (void);

friend LRESULT SelectCoordSysParams (Window *pW, UINT uiID, DatenBasisObjekt &rDBO, CoordTrans *pCTF = NULL);
friend UINT EXPORTTRIAS CALLBACK ImportFmtHookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam);
#if !defined(WIN16)
friend UINT EXPORTTRIAS APIENTRY ImportFmt40HookFcn (HWND, UINT, WPARAM, LPARAM);
#endif

	Window *GetParent (void) { return m_pW; }
	DatenBasisObjekt &DBO() { return m_rDBO; }
};

#endif // _IMPDLGS_HXX
