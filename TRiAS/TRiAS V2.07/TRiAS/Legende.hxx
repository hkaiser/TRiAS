// Klassendefinitionen fuer das Zeichnen einer Legende ------------------------
// File: LEGENDE.HXX

#if !defined(_LEGENDE_HXX)
#define _LEGENDE_HXX

#if !defined(NOLEGENDEITEM)

// sonstige Datentypen --------------------------------------------------------
typedef struct tagDRAGDROPLEGENTRY {
	DWORD m_dwSize;
	LEGENTRYTYPE m_rgLEType;	// Typ des LegendenEintrages
	VisType m_rgVType;		// VisualisierungsTyp
	long m_lTarget;			// ObjektNummer oder Ident
	char m_cbLegDesc[1];		// muß das letzte Feld sein
} DRAGDROPLEGENTRY;
typedef DRAGDROPLEGENTRY * LPDRAGDROPLEGENTRY;

class CIdRef;

// Klassen, die die LegendenEinträge repräsentieren ---------------------------
class CLegendeItem : 
	public DrawObject 
{	// steht für gesamten LegendenEintrag
protected:
	pWindow m_pW;
	DatenBasisObjekt &m_rDBO;	// zugehörige Datenbank
	CIdentifikator &m_ID;	// darzustellender Identifikator

	Point m_Pt;		// Größe der EintragsFläche
	Dimension m_Dim;

	Dimension m_DotsPerMM;	// Geräteauflösung
	CoOrd m_TextX;
	VisType m_iVTyp;
	char *m_pText;
	long m_lONr;		// evtl. ObjektNummer
	class CLegSizeCache &m_rCache;
		
	unsigned int m_fShown : 1;	// aktuell angezeigt
	unsigned int m_fScaleMode : 1;
	
public:
// Konstruktor/Destruktor
		CLegendeItem (pWindow pW, DatenBasisObjekt &rDBO, CIdentifikator &rID,
			VisType iVTyp, Point Pt, Dimension Dim, Dimension DotsPerMM, 
			bool fShown, char *pText, long lONr, CLegSizeCache &rCache,
			short iTextX, bool fScaleMode);
		~CLegendeItem (void);
	
inline	CoOrd Height (void) { return m_Dim.Height(); }
inline	bool GetScaleMode (void) { return m_fScaleMode ? true : false; }

protected:
// sonstige Memberfunktionen
	void Draw (void);		// Zeichnet gesamten Eintrag

	void LDrawPunkt (Dimension &);	// zeichnet typspezifisch
	void LDrawLinie (Dimension &);
	void LDrawFlaeche (Dimension &);
	bool LDrawText (Dimension &);
	
	void LDrawDescText (Dimension &);	// malt Text dazu

	HRGN SelectClipRegion (HDC hDC, Dimension &rDim);

inline	PBD_DB &PbdDB (void) { return m_rDBO.PbdDB(); }
inline	CIdTree & IDs (void) { return m_rDBO.Idents(); }
inline DatenBasisObjekt &DBO() { return m_rDBO; }
};
#endif // NOLEGENDEITEM

#if !defined(NOLEGENDEOBJEKT)
// gesamte Legende, ist ein zeichenbares Objekt -------------------------------
class CLegendInfo;

class CLegendeObjekt : public DrawObject {
private:
	pWindow m_pW;
	DatenBasisObjekt &m_rDBO;	// zugehörige Datenbank
	
	int m_iFontH;			// zu verwendender Font
	bool m_fBold;
	bool m_fItalic;
	bool m_fUnderline;
	string m_strFontName;
	int m_iFamily;
	int m_iFontOrg;			// erste Näherung der FontGröße

	short m_iIdCnt;		// Anzahl der LegendenEinträge
	short m_iLine;		// Höhe einer TextZeile
	
	long m_lMCode;		// LegendInfoMCode
	class CLegendInfo *m_pItems;			// Baum aller LegEntries
	class CLegEntryParser *m_pParser;	// Parser für LegEntryDesc
	
	char *m_pBuffer;

	CLegSizeCache m_PrLayout;	// LegendenGrößen 

	unsigned short m_fDirty : 1;
	unsigned short m_fShowAllEntries : 1;
			
public:
	Rectangle *m_pR;	// Außenabmessungen der Legende
	Point m_ptOrg;		// AnfangsPunkt beim zeichnen

protected:
	void DrawEx (DWORD dwData);

	bool GetIdentEntrySize (HDC hDC, CIdentifikator &rId,
		long &rlHeight, long lWidth, bool &rfFitWidth, bool fBreak,
		short iBits, char *pText = NULL, long lONr = -1L, 
		short *piNewWidth = NULL);
	short GetItemHeight (HDC hDC, CIdentifikator &rCId, 
			     long lWidth, char *pText);
	short GenLegEntry (CIdentifikator &, Point &, Dimension &, 
			   Dimension &, VisType, bool = true, char * = NULL,
			   long lONr = -1L, short iText = 0);

	bool GetViewDesc (string &rstr);

public:
// Konstruktor/Destruktor
		CLegendeObjekt (pWindow pW, DatenBasisObjekt &rDBO);
		~CLegendeObjekt (void);

static CLegendeObjekt *CreateInstance (pWindow pW, DatenBasisObjekt &rDBO,
			Rectangle *pRc = NULL, PrinterPars *pPP = NULL);

	bool FInit (Rectangle *pRc, PrinterPars *pPP);
	void SetBaseValues (Rectangle &rRC, HDC hDC);

// Memberfunktionen
	Dimension FitLegendSize (Rectangle *pRc, HDC hDefDC = NULL);
	Dimension GetRealSize (Rectangle *pRc, bool &fFitWidth);

	bool GetLegendSize (HDC hDC, long lWidth, Dimension &mm, 
			    short iFont, bool fFitWidth, long &rlHeight);
	bool RefreshLegend (void);

	WORD FindEntry (short lPos);		// finden eines Eintrages
	bool GetEntrySize (WORD iOrder, Range &rR);	// Größe feststellen
	bool GetEntryDesc (WORD iOrder, char *pBuffer, LEGENTRYTYPE &, VisType &, long &);
	
	bool isShown (WORD iOrder);		// Wrapper für Baum
	bool isShown (WORD iOrder, bool fShow);
	bool hasSpace (WORD iOrder);
	LEGENTRYTYPE isA (WORD iOrder);
	bool CustomizedText (WORD iOrder);
	
	VisType GetVType (WORD iOrder);
	long GetIdent (WORD iOrder);
	char *GetText (WORD iOrder);
	void SetText (WORD iOrder, char *pText);
	bool ResetText (WORD iOrder);
	bool RemoveEntry (WORD iOrder);
	
	bool MoveUp (WORD &iActSel, bool fShowAll);
	bool MoveDown (WORD &iActSel, bool fShowAll);
	
inline	bool FPasteEntry (LPDRAGDROPLEGENTRY pDDLE, WORD iOrder);
inline	bool FClipEntry (WORD iOrder);

	bool AddObject (long lONr);		// Objekt hinzufügen
				
	bool EnterSpace (WORD iOrder);
	bool RemoveSpace (WORD iOrder);

// alle Anzeigen setzen
inline 	void ShowAll (bool fShow) { m_fShowAllEntries = fShow ? true : false; }	
inline 	bool ShowAll (void) { return m_fShowAllEntries ? true : false; }

inline	bool isDirty (void) { return m_fDirty ? true : false; }
inline	void SetDirty (bool fDirty = true) { m_fDirty = fDirty ? true : false; }

inline	bool ShowAreaOnly (void) { return m_pItems -> ShowAreaOnly(); }
inline	void SetAreaOnly (bool fActArea) { m_pItems -> SetAreaOnly (fActArea); }

inline	bool GetScaleMode (void) { return m_pItems -> GetScaleMode(); }
inline	void SetScaleMode (bool fScaleMode) { m_pItems -> SetScaleMode (fScaleMode); }

inline	bool SaveLegend (void) 
	{ 
		if (!DEX_GetROMode()) {
			if (m_pItems -> SaveLegend()) 
				SetDirty (false);
			else 
				return false;
		}
		return true; 
	}
	bool ResetLegend (char *pView);
	
inline	bool isLastEntry (WORD iOrder) { return m_pItems -> isLastEntry (iOrder); }
inline	bool isFirstEntry (WORD iOrder) { return m_pItems -> isFirstEntry (iOrder); }

inline	PBD_DB &PbdDB (void) { return m_rDBO.PbdDB(); }
inline	CIdTree & IDs (void) { return m_rDBO.Idents(); }
inline DatenBasisObjekt &DBO() { return m_rDBO; }
};

inline bool CLegendeObjekt :: FPasteEntry (LPDRAGDROPLEGENTRY pDDLE, WORD iOrder)
{
bool fRet = m_pItems -> FPasteEntry (
			pDDLE -> m_rgLEType, pDDLE -> m_rgVType, 
			pDDLE -> m_lTarget, pDDLE -> m_cbLegDesc, iOrder);
	SetDirty();
		
return fRet;
}

inline	bool CLegendeObjekt :: FClipEntry (WORD iOrder)
{ 	
bool fRet = m_pItems -> FDeleteItem (iOrder);

	SetDirty();

return fRet;
}

#endif // NOLEGENDEOBJEKT

#define BOUND(x,min,max) ((x)<(min)?(min):((x)>(max)?(max):(x)))

short HandleIcon (HDC hDC, DatenBasisObjekt &rDBO, CIdentifikator &rId, 
		long lONr, short iBits, Point pt, char *pBuffer, CoOrd iHeight, 
		long &rlIconWidth, bool fDraw);

#endif // _LEGENDE_HXX
