// Klassendeklaration fuer Den Export von DIRIS-Daten
// File: EXPORT.HXX

#if !defined(_EXPORT_HXX)
#define _EXPORT_HXX

// Eigentliche ExportFunktionen -----------------------------------------------

class GeoDB;

class Export : 
	public DLLBind 
{
private:
	char _ExportName[50];	// Name (Kürzel) des Ein-/AusgabeFormates
	short _NameLen;
	OFSTRUCT _of;		// FileBeschreibungsStruktur für OpenFile
	DatenBasisObjekt &m_rDBO;
	GeoDB &_DB;

// Funktionspointer auf DLL-Funktionen
	EXPDATAFUNC _ExpData;

	char *ExpName (unsigned int);

// Koeffizienten zur KoordinatenTransformation
	double K11, K12, K21, K22;
	double OX, OY;

// Koeffizienten für die zusätzliche Koordinatentransformation
	double KX, KY;
	double OffsetX, OffsetY;
	bool _2ndTransform;

	bool m_fConvert;		// Koordinaten nicht konvertieren
	CoordTrans *m_pCTF;		// zu verwendende KoordinatenTransformation

protected:
	ErrCode ExportBegin (HWND hWnd, char *FileName, OutMode OutFlag);
	ErrCode ExportEnd (void);

	void ConvertDCtoRC (KoOrd *, KoOrd *, GSTRUCT &);

	ErrCode ExportHeaderEntry (uint resID, DWORD dwStyle = HEADER_NORMAL);

public:
	ErrCode ExportGeoDBHeader (void);
	ErrCode ExportObjekt (DatenBasisObjekt &rDBO, CTable &t, 
			      long ON, char * = NULL, bool fForceText = false);
	ErrCode ExportDBContainer (GeoDB &rDB, long Ident, ObjContainer &);

	char *GetUniqueIdent (GeoObjekt &, MerkmalsListe &);

	short GetExportCaps (ExportCapability ExpCap);

	void SetTransParams (double, double, double, double);

// Konstruktor
		Export (HWND hWnd, LPCSTR pcFormatName, LPCSTR pcDLLName, LPCSTR pcOutName, 
				DatenBasisObjekt &rDBO, OutMode OutFlag = OMOverwrite);

// Memberfunktionen
	ErrCode ExportDescription (LPCSTR KeyInfo = NULL, LPCSTR DescInfo = NULL, DWORD dwStyle = HEADER_NORMAL);
	ErrCode ExportHeader (const char *HeaderInfo = NULL);
	ErrCode ExportComment (const char *CommentString = NULL);
	ErrCode ExportData (GeoObjekt &GO, MerkmalsListe &ML, char *, bool fForceText = false);
	ErrCode ExportTrailer (const char *TrailerInfo = NULL);
	ErrCode ExportIdentDescription (IdentDescription &);
	ErrCode ExportMerkmalDescription (MerkmalDescription &);
	ErrCode ExportBreak (void);

// Destruktor
		~Export (void);

inline DatenBasisObjekt &DBO() { return m_rDBO; }

// friends
friend ErrCode doExport (HWND hWnd, ObjFeld &Objekte);	// Export starten
friend BOOL EXPORTTRIAS ExportIdent (void *, void *);	// Idents exportieren
friend BOOL EXPORTTRIAS ExportMerkmal (void *, void *);	// Merkmale exportieren
};

#if defined(_FORCE_LEGACY_CODE)
ErrCode FillMerkmale (DatenBasisObjekt &rDBO, MerkmalsListe &rML);
#endif // defined(_FORCE_LEGACY_CODE)

typedef struct tagEXPORTIDENT {
	DatenBasisObjekt *m_pDBO;
	Export *m_pExp;
	short m_iActSightNumIDs;
	long *m_pActSightIDs;
} EXPORTIDENT;

#endif // _EXPORT_HXX
