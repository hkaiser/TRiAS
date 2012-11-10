// Klassendeklaration fuer Den Export von DIRIS-Daten
// File: EXPORT.HXX

#if !defined(_EXPORT_HXX)
#define _EXPORT_HXX

// Eigentliche ExportFunktionen -----------------------------------------------

//#define	_KOORD_ISDOUBLE
#define	EXPORTTRIAS

class GeoDB;

class Export
	: public DLLBind 
{
private:
	char _ExportName[50];	// Name (Kürzel) des Ein-/AusgabeFormates
	short _NameLen;
	LPTSTR	DtoA( LPTSTR s, LPTSTR lpsFormat, double val );
	OFSTRUCT _of;		// FileBeschreibungsStruktur für OpenFile
//XX	DatenBasisObjekt &m_rDBO;
//XX	GeoDB &_DB;

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
//XX	CoordTrans *m_pCTF;		// zu verwendende KoordinatenTransformation
	
protected:
	ErrCode ExportBegin (HWND hWnd, char *FileName, OutMode OutFlag);
	ErrCode ExportEnd (void);

	void ConvertDCtoRC (KoOrd *, KoOrd *, GSTRUCT &);

	ErrCode ExportHeaderEntry (uint resID, DWORD dwStyle = HEADER_NORMAL);

public:
	ErrCode ExportGeoDBHeader (void);
//XX	ErrCode ExportObjekt (DatenBasisObjekt &rDBO, CTable &t, long ON, char * = NULL, bool fForceText = false);
	/*XX*/	ErrCode ExportObjekt( long ON, char * = NULL, bool fForceText = false);
//XX	ErrCode ExportDBContainer (GeoDB &rDB, long Ident, ObjContainer &);

//XX	char *GetUniqueIdent (GeoObjekt &, MerkmalsListe &);
	char *GetUniqueIdent (long lONr);

	short GetExportCaps (ExportCapability ExpCap);

	void SetTransParams (double, double, double, double);

// Konstruktor
//XX	Export (HWND hWnd, LPCSTR pcFormatName, LPCSTR pcDLLName, LPCSTR pcOutName, DatenBasisObjekt &rDBO, OutMode OutFlag = OMOverwrite);
	/*XX*/	Export( HWND hWnd, LPCTSTR pcFormatname, LPCSTR pcDLLName, LPCSTR pcOutName, OutMode OutFlag = OMOverwrite );

// Memberfunktionen
	ErrCode ExportDescription (LPCSTR KeyInfo = NULL, LPCSTR DescInfo = NULL, DWORD dwStyle = HEADER_NORMAL);
	ErrCode ExportHeader (const char *HeaderInfo = NULL);
	ErrCode ExportComment (const char *CommentString = NULL);
//XX	ErrCode ExportData (GeoObjekt &GO, MerkmalsListe &ML, char *, bool fForceText = false);
	/*XX*/	ErrCode ExportData (long lONr, char *, bool fForceText = false);
	ErrCode ExportTrailer (const char *TrailerInfo = NULL);
	ErrCode ExportIdentDescription (IdentDescription &);
	ErrCode ExportMerkmalDescription (MerkmalDescription &);
	ErrCode ExportBreak (void);

// Destruktor
		~Export (void);

//XX	inline DatenBasisObjekt &DBO() { return m_rDBO; }

// friends
//XX	friend ErrCode doExport (HWND hWnd, ObjFeld &Objekte);	// Export starten
	friend BOOL EXPORTTRIAS ExportIdent (void *, void *);	// Idents exportieren
//XX	friend BOOL EXPORTTRIAS ExportMerkmal (void *, void *);	// Merkmale exportieren
};

#if defined(_USE_LEGACY_CODE)
ErrCode FillMerkmale (DatenBasisObjekt &rDBO, MerkmalsListe &rML);
#endif // defined(_USE_LEGACY_CODE)

typedef struct tagEXPORTIDENT {
//XX	DatenBasisObjekt *m_pDBO;
	Export *m_pExp;
	short m_iActSightNumIDs;
	long *m_pActSightIDs;
} EXPORTIDENT;

#endif // _EXPORT_HXX
