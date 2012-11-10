// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT
// File: LEGDINFO.HXX

#if !defined(_LEGDINFO_HXX)
#define _LEGDINFO_HXX

// Klasse, die im Baum hängen soll --------------------------------------------
typedef enum tagLEGENTRYTYPE {
	LEGENTRYTYPE_UNKNOWN = 0,
	LEGENTRYTYPE_IDENT = 1,
	LEGENTRYTYPE_OBJECT = 2,
	LEGENTRYTYPE_TEXT = 3,
} LEGENTRYTYPE;

// Verschlüsselung der Attribute eines LegendenEintrages im Merkmal -----------
const short LEShown = 0x01;
const short LESpace = 0x02;

class CLegendInfoEntry {
private:
	WORD m_Key;			// Suchschlüssel (Reihenfolge)
	enum VisType m_rgType;		// Typ des Eintrages
	unsigned short m_fShow : 1;	// in Legende Anzeigen
	unsigned short m_fEnterSpace : 1;	// Leerzeile einfügen
	unsigned short m_fDirty : 1;	// wurde geändert
	unsigned short m_fCustText : 1;	// Text wurde geändert
	
protected:
	char *m_pText;			// das ist der andere Text (wenn != NULL)

private:
	long m_lPosition;		// aktuell links oben
	long m_lHeight;			// Höhe des Eintrages
	
public:
		CLegendInfoEntry (WORD iSrt, bool fShow, bool fSpace, VisType rgType);
	virtual ~CLegendInfoEntry (void);

virtual	bool SaveLegendEntry (class CLegEntryParser &rP, long lMCode) = 0;
virtual LEGENTRYTYPE isA (void) = 0;	// Typ dieses Eintrages

inline	VisType GetVType (void) { return m_rgType; }
inline	bool isShown (void) { return m_fShow ? true : false; }
inline	void isShown (bool fShow, bool fSetDirty = true)  
	{ 
		if (fShow) m_fShow = true; else m_fShow = false; 
		if (fSetDirty) m_fDirty = true;
	}
inline	bool hasSpace (void) { return m_fEnterSpace ? true : false; }
inline	void hasSpace (bool fSpace, bool fSetDirty = true)  
	{ 
		if (fSpace) m_fEnterSpace = true; else m_fEnterSpace = false; 
		if (fSetDirty) m_fDirty = true;
	}
inline	bool isDirty (void) { return m_fDirty ? true : false; }
inline	void SetDirty (bool fDirty = true) { m_fDirty = fDirty ? true : false; }

virtual	char *GetText (bool = true) = 0;
	void SetText (char *pText);
	void ResetText (void);
inline	void SetPosition (long lNewPos) { m_lPosition = lNewPos; }
inline	long GetPosition (void) { return m_lPosition; }
inline	void SetHeight (long lNewHeight) { m_lHeight = lNewHeight; }
inline	long GetHeight (void) { return m_lHeight; }
inline	bool HitTest (long lPos) 
	{ return (lPos >= m_lPosition && lPos < m_lPosition + m_lHeight); }
inline	bool CustomizedText (void) { return m_fCustText ? true : false; }
inline	void CustomizedText (bool fCust) { if (fCust) m_fCustText = true; else m_fCustText = false; }
inline	char *GetTextRef (void) const { return m_pText; }
	
// Funktionen zur SuchSchlüsselVerwaltung
	WORD & FGetWORD (void);		// liefert SuchSchlüssel
friend int FCmpWORD (WORD &, WORD &);	// vergleicht 2 Schlüssel
};

class CLegendInfoIdent : public CLegendInfoEntry {
private:
	long m_lIdent;	// Identifikator

public:
		CLegendInfoIdent (WORD iSrt, bool fShow, bool fSpace,
				  VisType rgType, long lIdent);
		~CLegendInfoIdent (void);

	char *GetText (bool = true);
	bool SaveLegendEntry (class CLegEntryParser &rP, long lMCode);
	
inline	LEGENTRYTYPE isA (void) { return LEGENTRYTYPE_IDENT; }
inline	long GetIdent (void) { return m_lIdent; }
};

class CLegendInfoObject : public CLegendInfoEntry {
private:
	long m_lONr;	// ObjektNummer
	short m_iIconWidth;
	
public:
		CLegendInfoObject (WORD iSrt, bool fShow, bool fSpace,
				   VisType rgType, long lONr);
		~CLegendInfoObject (void);

	char *GetText (bool = true);
	bool SaveLegendEntry (class CLegEntryParser &rP, long lMCode);
	
inline	LEGENTRYTYPE isA (void) { return LEGENTRYTYPE_OBJECT; }
inline	long GetONr (void) { return m_lONr; }
inline	short &IconWidth (void) { return m_iIconWidth; }
};

class CLegendInfoText : public CLegendInfoEntry {
public:
		CLegendInfoText (WORD iSrt, bool fSpace);
		~CLegendInfoText (void);

	char *GetText (bool = true);
	bool SaveLegendEntry (class CLegEntryParser &rP, long lMCode);

inline	LEGENTRYTYPE isA (void) { return LEGENTRYTYPE_TEXT; }
};

// Eigentliche typspezifische TreeKlasse --------------------------------------
// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CLegendInfoEntryEnumFunc)(CLegendInfoEntry &, void *);
  
const WORD FIRSTLASTIDENTORDER = 2000;

class CIdTree;		// declaration only

class CLegendInfo : 
	public CTree 
{
private:
	long m_lVMCode;		// allgemeiner AufhängerMCode
	long m_lMCode;		// MCode in der aktuellen Sicht
	char *m_pBuff;		// Zeichenketten-ZwischenSpeicher
	class CLegEntryParser &m_rP;	// Parser für MerkmalsInfos
	char *m_pView;		// Name der aktuellen Sicht
	short m_iMkBase;	// Zahlenbasis des aktuellen Projektes
			
	WORD m_iLast;		// iOrder für fehlende Infos

	bool m_fActArea;
	bool m_fSizesLikeScaling;	// Größen wie im Bild darstellen
	
protected:
	void UserDelete (void *pObj);
	bool MakeMCodes (long &rlVMCode, long &rlMCode, const char *pView = NULL);

public:
// Konstruktor/Destruktor
		CLegendInfo (CLegEntryParser &rP, long lMCode);
		~CLegendInfo (void);

static CLegendInfo *CreateInstance (CLegEntryParser &rP, CIdTree &rIDs, long lMCode);

	bool FInit (CIdTree &rIDs);

// Elementarfunktionen
	bool FAddItem (LEGENTRYTYPE rgType, WORD iSrt, VisType rgVType, 
		       long lTarget, char *pText, bool fShow = true,
		       bool fSpace = false);	// Element hinzufügen
	bool FDeleteItem (WORD &);		// Element löschen
	CLegendInfoEntry *FFindItem (WORD &);	// Element liefern

	bool FReInsert (WORD &oldKey, WORD &newKey);

// EnumerationsFunktionen
	bool FEnumAllItems (CLegendInfoEntryEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (WORD &rKey, CLegendInfoEntryEnumFunc pFcn, void *pEData = NULL);

// SuchSchlüsselVerwaltung
friend WORD *FCTTreeGetWORD (CLegendInfoEntry *pObj);
friend int FCTTreeCmpWORD (WORD *pObj1, WORD *pObj2);

// semantische Funktionen
	bool AddIdent (long lIdent, VisType iVTyp, WORD &riOrder);
	bool AddObjects (WORD &riOrder);
	bool AddObject (long lONr, WORD &riOrder);
	bool AddTexts (WORD &riOrder);
	bool AddText (WORD &riOrder, long lMCode);
	int ExtractMCodes (char *pMWert, ULONG **ppulMCodes);

	bool GetSortOrder (WORD &riOrder, bool &rfShow, bool &rfSpace, 
			   char *& pText, VisType iVTyp, DWORD lTarget, 
			   short iTType, long lMCode = 0L);
	void FSetDirty (WORD &iOrder);
	bool SaveLegend (void);
	bool ResetLegend (char *pView);

	bool MoveUp (WORD &iActSel, bool fShowAll);
	bool MoveDown (WORD &iActSel, bool fShowAll);
	bool FPasteEntry (LEGENTRYTYPE, VisType, long, char *, WORD);
	
	bool RemoveEntry (WORD iActSel);
	
	bool isFirstEntry (WORD iOrder);
	bool isLastEntry (WORD iOrder);
	
	bool hasSpace (WORD iOrder, bool fSpace);

	int RetrieveMode (bool &rfAreaMode, bool &rfScaleMode);		// aus Sicht einlesen
	void SaveMode (LPCSTR);
	
inline	bool ShowAreaOnly (void) { return m_fActArea ? true : false; }
inline	void SetAreaOnly (bool fActArea) { m_fActArea = fActArea ? true : false; }

inline	bool GetScaleMode (void) { return m_fSizesLikeScaling ? true : false; }
inline	void SetScaleMode (bool fScaleMode) { m_fSizesLikeScaling = fScaleMode ? true : false; }
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator ---------------
DeclareLock (CLegendInfo, CLegendInfoEntry);

// sonstige FunktonsPrototypen ------------------------------------------------
long GetHeaderMCode (bool fGenerate, uint resID, LPCSTR pView = NULL,
		    uint uiResKT = 0, uint uiResLT = 0);
long GetObjMCodeView (bool fGenerate, LPCSTR pView, long lVMCode,
			uint uiResKT = 0, uint uiResLT = 0);
long GetIdentMCodeView (bool fGenerate, LPCSTR pView, long lVMCode,
			uint uiResKT = 0, uint uiResLT = 0);

bool ReadTextMerkmal (short iTTyp, DWORD lTarget, long lMCode, char *pText, short iLen);
bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, short iFlags = 0);
bool FormatString (char *pBuffer, CLegendInfoEntry *[4]);
bool FormatString (char *pBuffer, CLegendInfoEntry *);
char *GetPBDText (long lIdent, char *pText, int iLen);

#endif // _LEGDINFO_HXX

