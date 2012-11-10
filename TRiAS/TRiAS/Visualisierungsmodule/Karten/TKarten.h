/////////////////////////////////////////////////////////////////////////////
// CKartenCtrl : See TKarten.cpp for implementation.

//#define	_NEWCODE

///////////////////////////////////////////////////////////////////////////////
// string konstanten
// Klassische Hallöchen - Header - Definitionen ///////////////////////////////////

TCHAR __declspec(selectany) szTKPdbEntry[]		= TEXT("@TopKartMCode");
TCHAR __declspec(selectany) szViewPdbEntry[]	= TEXT("@TopKartVCode");
TCHAR __declspec(selectany) szMatchPdbEntry[]	= TEXT("@TopKartMatch");
TCHAR __declspec(selectany) szDataPdbEntry[]	= TEXT("@TopKartData");

TCHAR __declspec(selectany) szOldPdbEntry[] = TEXT("@TopKart");


// KK001221
extern "C"  BOOL PASCAL _XTENSN_EXPORT SucheDatenQuellen ( char *, bool , void *);

///////// KK000305 ///////////////////////////////////////////////////

typedef vector<long> CCodesFromProject;

//------------------------------------------------------------------------------
class CPrjVec :
	public map<HPROJECT, CCodesFromProject, less<HPROJECT> >
{
public:

	bool InsertObject (HPROJECT hPr, long lMCode);
	void Clear() { erase(); }
	size_t Count() 
	{
	size_t lCnt = 0;

		for (iterator it = begin(); it != end(); ++it) 
			lCnt += (*it).second.size();
		return lCnt;
	}

};
//------------------------------------------------------------------------------

//typedef list<string> CCardsFromProject;

class CCardsFromProject :
	public list<string>
{
public:
	CCardsFromProject(HPROJECT hPr) :
		m_bMatchMapName(FALSE)
	{
	CString	strHdrValue;

		CTriasVMD::GetGeoDBEntry (hPr, szMatchPdbEntry, strHdrValue);
		m_bMatchMapName = strHdrValue.IsEmpty() ? FALSE : (BOOL)atol(strHdrValue);
	}
	~CCardsFromProject() {}

	BOOL GetMatchMapName() { return m_bMatchMapName; }

private:
	BOOL m_bMatchMapName;
};

//------------------------------------------------------------------------------

class CPrjMap :
	public map<HPROJECT, CCardsFromProject, less<HPROJECT> >
{
public:

	bool InsertObject (const char *pName);
	bool InsertKVObject (HPROJECT hPr,const char *pName);
	void Clear() { erase(); }
	size_t Count() 
	{
	size_t lCnt = 0;

		for (iterator it = begin(); it != end(); ++it) 
			lCnt += (*it).second.size();
		return lCnt;
	}

	BOOL GetMatchMapName(DWORD lONr);
};

//----------------------------------------------------------------------------
// imput iterator für for_each
class CPrjMapInputIter : 
	public input_iterator<string, size_t>
{
public:
	typedef CPrjMapInputIter self;

protected:
	CPrjMap *m_pPrjMap;
	CPrjMap::iterator m_it;
	CCardsFromProject::iterator m_itl;

	string value;
	HPROJECT hProject;

	bool end_marker;

	void read (void) throw() 
	{
		if (m_it == m_pPrjMap -> end()) {
			end_marker = true;
			return;
		}
			
		if (m_itl != (*m_it).second.end()) {
			value = *m_itl;
			hProject = (*m_it).first;
			++m_itl;

			if (m_itl == (*m_it).second.end()) {
				++m_it;
				if (m_it != m_pPrjMap -> end())
					m_itl = (*m_it).second.begin();
			}

			end_marker = false; 

		} else
			end_marker = true ; 
	}

public:
	CPrjMapInputIter (void) throw() : m_pPrjMap(NULL), end_marker(true) {}
	CPrjMapInputIter (CPrjMap *pPrjMap) throw() : m_pPrjMap(pPrjMap), end_marker(false) 
	{ 
		m_it = m_pPrjMap -> begin(); 

		if (m_it != m_pPrjMap -> end()) {
			m_itl = (*m_it).second.begin();
			read(); 
		} else
			end_marker = true;
	}

	const char *operator *(void) const throw() { return value.c_str(); }

	self& operator++ (void)	throw() { read(); return *this; }
	self operator++ (int) throw() { self tmp = *this; read(); return tmp; }

	bool operator== (const self & x_) const throw() 
	{ 
		return (m_pPrjMap == x_.m_pPrjMap && end_marker == x_.end_marker) ||
			   (end_marker == true && x_.end_marker == true);
	}
	bool operator!= (const self & x_) const throw() 
		{ return !(*this == x_); }

// KK010105
	bool EndMarker (void) { return end_marker;}
	HPROJECT HProject (void) { return hProject;}

// herauslöschen des aktuellen Elementes
	void erase_act() 
	{
		if (m_it == m_pPrjMap -> end()) {
			end_marker = true;
			return;
		}

	CPrjMap::iterator it = m_it;

		++m_it;
		m_pPrjMap -> erase(it);

		if (m_it == m_pPrjMap -> end()) 
			end_marker = true;
		else {
			m_itl = (*m_it).second.begin();
			read();
		}
	}
};

// output iterator (für copy)
class CPrjMapOutputIter : 
	public output_iterator
{
public:
	typedef CPrjMapOutputIter self;

protected:
	CPrjMap *m_pPrjMap;

public:
	CPrjMapOutputIter (void) throw() : m_pPrjMap(NULL) {}
	CPrjMapOutputIter (CPrjMap *pPrjMap) throw() : m_pPrjMap(pPrjMap) {}
	CPrjMapOutputIter (const self &iter) throw() : m_pPrjMap(iter.m_pPrjMap) {}

    self& operator = (const char *value) throw() 
		{ m_pPrjMap -> InsertObject(value); return *this; }
	self& operator * (void) throw() { return *this; }
	self& operator++ (void)	throw() { return *this; }
	self operator++ (int) throw() { return *this; }
};

///////////////////////////////////////////////////////////////////////////////
// ein GeoCodedPoint (Referenzpunkt)
class CGCP : 
	public CObject
{
public:
	CGCP();
	void Clear();

#ifdef _NEWCODE
	//////////////////////////////////////////
	// neuer Code (erstmal testweise)
	DPOINT	m_ptlPict;
	DPOINT	m_ptlCoord;
	// ...neuer Code (erstmal testweise)
	//////////////////////////////////////////
#else
	POINTL	m_ptlPict;
	POINTL	m_ptlCoord;
#endif
};

#define	N_PALETTETYPES	3

class CRGBClut : 
	public CObject 
{
public:
	CRGBClut();
	void Clear();
	void	SetPalette( CPicture *pPicture );
	LPRGBQUAD	GetPalette( int nPalIndex );
	int		m_nColors[N_PALETTETYPES];
	RGBQUAD	m_cluTables[N_PALETTETYPES][256];
};

class CInfoForMap : 
	public CObject 
{
public:
	CInfoForMap();
	virtual ~CInfoForMap();
	
	CObArray	*m_pListOfGCP;		// Liste der Referenzpunkte

#ifdef _NEWCODE
	//////////////////////////////////////////
	// neuer Code (erstmal testweise)
	CDSize		m_szPicture;	// Bildgröße
	// ...neuer Code (erstmal testweise)
	//////////////////////////////////////////
#else
	CSize		m_szPicture;		// Bildgröße
#endif
	CString		m_strPictName;		// Bilddateiname
	CString		m_strPictPath;
	CString		m_strMapUID;
	CRuntimeClass	*m_pRTPicture;	// Typ des Bildes (RUNTIME_INFO)
	CRGBClut	m_clut;
	int			m_nSubfile;
	BOOL		m_bHaveSubFiles;
	int			m_nSampleRate;
	char		m_chAddChar;		// an Dateinamen anzuhängender Buchstabe ('a' .. 'e')
	int			m_nCropBorder;		// zusätzlicher Beschnitt, um schwarzen Rand verschwinden zu lassen

	BOOL		m_bUsesSubDirs;		// BildTyp ist in Unterverzeichnisses verteilt (z.B. für PolyGIS)
	BOOL		m_bModifiesSubDirs;	// Unterverzeichnissnamen werden modifiziert (nicht Bildnamen)
	CString		m_strBaseDir;		// Basisverzeichnis 
	CString		m_strSubDir;		// '\\' + Prefix der Verzeichnisnamen (z.B. '\raster')
	CString		m_strDirSuffix;		// Basisverzeichnis\Verzeichnisname##Suffix für Hauptverzeichnis (z.B. '1')
	CString		m_strCoordSys;		// Name des zu verwendenden Koordinatensystemes

	int			m_nSubLevels;		// Anzahl der Auflösungsstufen (wenn == 0, dann normal)

	void ClearGCPList();
	BOOL SubDirFits(LPCTSTR);		// Testet, ob letzter Teil des gegebenen Pfages == m_strSubDir ist
};

//////////////////////////////////////////////////////////////////
// Palettentypen
// (0) ... Standardfarben
// (1) ... Farbpalette für den einen Rostock-Satz
// (2) ... s/w - Karten (z.B. Berlin, K5 RD)
//
// Status:
//	FALSE ... noch nicht eingemischt
//  TRUE  ... eingemischt

class CKartenCtrl : 
	public CTriasVMD 
{
	DECLARE_DYNCREATE(CKartenCtrl)

#ifdef _NEWCODE
	//////////////////////////////////////////
	// neuer Code (erstmal testweise)
	DPOINT D_OCtoDC( const POINTL& ptOC );
	DPOINT D_OCtoDC( const DPOINT& ptOC );
	DPOINT D_DCtoOC( const DPOINT& ptDC );
	DPOINT D_DCtoOC( const POINTL& ptDC );
	DPOINT D_DCtoOC( const POINT& ptDC );
	// ...neuer Code (erstmal testweise)
	//////////////////////////////////////////
#endif

// Constructor
public:
	CKartenCtrl();

// Overrides

// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
//	double		m_mysticFactor;
//	double		m_scaleX;
	double		m_minSize;
	int			m_nTranspChannel;
	long			m_lPalMCode;		// MCode, an dem gespeichert wird, ob Palette für die Sicht verwendet werden soll
	long			m_lMapIdent;		// Identifikator für topographische Karten
	long			m_lMapMCode;		// Merkmalscode mit Darstellungsparametern
//	BOOL			m_bMapsVisible;		// Ein/Ausblenden von Karten
	long			m_lMapONr;			// Objektnummer für topographische Karten

    VisInfo        *m_pVI;
	CMemBlock*		m_pMemBlock;
	CMapPtrToPtr	m_pictTypes;
	CPicture*		m_pPicture;

	CMapStringToOb	m_listOfMaps;
	CMapStringToPtr	m_listOfPalTypes;

	CInfoForMap*		m_pCurrMap;
	BOOL ParseVisInfoString( DWORD dwObjNr, LPCTSTR pszVI );
	BOOL SelectSubFile( );

	virtual LPCTSTR GetProgIdent();		// liefert ProgIdent "TRiAS.VM...."

#ifdef _NEWCODE
//////////////////////////////////////////
// neuer Code (erstmal testweise)
	CDRect	CalculateDstArea(CDC* pDC);
	CDRect	CalculateSrcArea(CDC* pDC, CDRect& rcDst, BOOL fReSize);
// ...neuer Code (erstmal testweise)
//////////////////////////////////////////
#else
	CRect	CalculateDstArea(CDC* pDC, CDC* pTarget,CRect& rcDst);
	CRect	CalculateSrcArea(CDC* pDC, CRect& rcDst, BOOL fReSize);
#endif // _DEBUG

	BOOL m_bPalRealized;
	BOOL m_bMatchMapName;
// KK010111
	BOOL m_bMatchMapData;

	int		m_nPalType;
	CString	m_strViewPalette;			// nicht leer, wenn globale Palette in der Sicht 
//	BOOL	GetPalettes();
//	BOOL	GetPalette( LPCTSTR pszSchemaName, LPCTSTR pszPalTypes, int nPalSchema );
//	BOOL	RetrievePalSchema();

	BOOL			m_bProjDrawn;
	BOOL			m_bViewDrawn;
	CMapStringToPtr	m_listOfSights;		// Marker, ob in der Sicht schon mal gezeichnet wurde (NULL != ptr)

	CStringArray	m_strMapDirs;		// Suchverzeichnisse für Karten

// KK 211200
	CPrjMap	m_strDQ;					// Verzeichnis der Datenquellen
// KK 010105
	CPrjMap m_strKVZ;					// Verzeichnis der Rasterkarten
	HPROJECT m_hPr;						// aktuelle Datenquelle
	CPrjVec m_strKVZCodes;				// MCodes zu Kartenverzeichnisse

	CMapStringToOb	m_listOfPalettes;	// Liste aller verfügbaren Paletten

	~CKartenCtrl();

	DECLARE_OLECREATE_EX(CKartenCtrl)   // Class factory and guid

	DECLARE_PROPPAGEIDS(CKartenCtrl)    // Property page IDs
	DECLARE_OLECTLTYPE(CKartenCtrl)		// Type name and misc status

	virtual	void	DeleteContents( );

	virtual	BOOL	OnProjectOpen( LPCTSTR pszNewProject );
	virtual	void	OnProjectClose( );
	virtual	BOOL	OnViewOpen( LPCTSTR pszView );
	virtual	void	OnViewClose( );

	virtual	BOOL	OnChangePalette( CDC *pDC, HPALETTE hPal );

	virtual	BOOL	OnQueryParameters(
						CWnd *pParentWnd,
						const DWORD lONr, 
						class VisInfo * pVI, 
						LPCTSTR pszVisStr, 
						LPSTR pBuffer, 
						short iLen,
						short * piOTypes);
	virtual	BOOL	OnDrawObject(
						CDC *pDC,
						CDC *pTarget,
						const DWORD lObjNr, 
						class VisInfo * pVI, 
						LPCTSTR pszVisString, 
						short& fDrawFlags );
// Message maps
	//{{AFX_MSG(CKartenCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CKartenCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CKartenCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	DECLARE_OLETYPELIB(CKartenCtrl)      // GetTypeInfo
	DECLARE_INTERFACE_MAP()
	DECLARE_VISMOD_INTERFACE()

	// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CKartenCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};

// KK001220
	BOOL	SetDQ(void );

// KK010105
	BOOL	SetKVZ(void );
	BOOL	SetKVZCodes(void );
	BOOL	ModKVZ(void );
	void	OnDQClose(void );
	BOOL	LoadSection(HPROJECT, CPrjMap *);
	BOOL	LoadHeader(HPROJECT);

	bool ModMapList (const char *value);
	bool MapList (const char *value);
	bool FindMapList( long *phRef, const char *pName);
	bool MapUnique(int i, const char *);
	long MapMCode (HPROJECT);
	long PalMCode(HPROJECT);

// Palette behandeln
    BOOL __stdcall HandlePalette(CPicture *pPicture);
};

