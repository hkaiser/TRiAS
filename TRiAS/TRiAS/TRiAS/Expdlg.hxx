// StandardDialog zum festlegen des ExportFormates ----------------------------
// File: EXPDLGS.HXX

#if !defined(_EXPDLGS_HXX)
#define _EXPDLGS_HXX

extern "C" UINT EXPORTTRIAS CALLBACK ExportFmtHookFcn (HWND, UINT, WPARAM, LPARAM);
#if !defined(WIN16)
extern "C" UINT EXPORTTRIAS APIENTRY ExportFmt40HookFcn (HWND, UINT, WPARAM, LPARAM);
#endif

// Struktur zur Beschreibung der Filter
typedef struct tagFILTERINFO {
	char *m_pFilterName;	// Bezeichnung des ExportFilters
	char *m_pDLLName;	// Name der FilterDLL
	char *m_pShortName;	// Kürzel für Namen der DLL Funktionen
	char *m_pFilterExt;	// StandardExtension der Ausgabedatei
} FILTERINFO;

class ExportDlg : public CSaveAsDialog {
private:
	char *m_pOutFile;		// AusgabeDateiName
	char *m_pInitPath;		// Anfangsverzeichnis

	int m_iNumFilters;		// Anzahl der installierten Filter
	FILTERINFO *m_pFilterInfo;	// Beschreibung dieser Filter
	char *m_pFileTypes;		// BeschreibungsString für Dialog

	unsigned int m_fPos : 1;	// PositionsRahmen exportieren
	unsigned int m_fAppend : 1;	// an Datei anhängen statt überschreiben
	unsigned int m_fValid : 1;
#if !defined(WIN16)
	unsigned int m_fAllObjects : 1;	// alle Objekte exportieren
	unsigned int m_fProject : 1;	// ProjektExport
	unsigned int m_fEnableActView : 1;
#endif

	CoordTrans *m_pCTF;			// zugehörige CoordTransform
	Window *m_pW;				// ParentWindow
	DatenBasisObjekt &m_rDBO;	// zugehöriges Projekt

protected:
	bool ReadFormats (void);	// Einlesen der FilterInfo's
	char *RetrieveAvailExportFormats (void);	// AusgabeFormate lesen
	int ReadFileName (void);	// Dateinamen holen
	int FindFilterExt (void);	// Filter über Erweiterung finden

public:
// Konstruktor (Initialisierung des Dialogfensters)
		ExportDlg (pWindow, CoordTrans *pCTF, DatenBasisObjekt &rDBO, bool fProject = true);
		~ExportDlg (void);

// Memberfunktionen
	char *GetFileSpec (char *cptr = NULL, short len = 0);
	char *GetDLLName (char *cptr = NULL, short len = 0);
	char *GetShortName (char *pc = NULL, short iLen = 0);
	char *GetSight (char *cptr = NULL, short len = 0);
	OutMode OMFlag (void) const { return m_fAppend ? OMConcatinate : OMOverwrite; }
	bool ExportPosition (void) { return m_fPos ? true : false; }

	bool isValid (void) { return m_fValid ? true : false; }
#if !defined(WIN16)
	bool FAllObjects (void) { return m_fAllObjects ? true : false; }
	bool GetObjPropsForExport (void);
#else
	bool FAllObjects (void) { return false; }
#endif // WIN16

friend LRESULT SelectCoordSysParams (Window *pW, UINT uiID, DatenBasisObjekt &rDBO, CoordTrans *pCTF = NULL);

	LRESULT OnWmCommand (HWND, WPARAM, LPARAM);
	LRESULT OnWmInitDialog (HWND, HWND);

	Window *GetParent (void) { return m_pW; }
	DatenBasisObjekt &DBO() { return m_rDBO; }
};

#endif // _EXPDLGS_HXX
