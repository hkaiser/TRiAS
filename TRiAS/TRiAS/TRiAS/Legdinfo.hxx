// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT
// File: LEGDINFO.HXX

#if !defined(_LEGDINFO_HXX)
#define _LEGDINFO_HXX

#include <ospace/std/set>

///////////////////////////////////////////////////////////////////////////////
// Klasse, die im Baum hängen soll 
typedef enum tagLEGENTRYTYPE {
	LEGENTRYTYPE_UNKNOWN = 0,
	LEGENTRYTYPE_IDENT = 1,
	LEGENTRYTYPE_OBJECT = 2,
	LEGENTRYTYPE_TEXT = 3,
	LEGENTRYTYPE_SPACELINE = 4,		// same as LEGENTRYTYPE_TEXT, but no text
} LEGENTRYTYPE;

// Anzahl der möglichen verschiedenen Legenden-Eintragstypen
const int LEGENTRYTYPE_CNT = 5;

// Verschlüsselung der Attribute eines LegendenEintrages im Merkmal -----------
const short LEShown = 0x01;
const short LESpace = 0x02;

class CLegendInfoEntry 
{
private:
	WORD m_Key;			// Suchschlüssel (Reihenfolge)
	enum VisType m_rgType;			// Typ des Eintrages
	unsigned short m_fShow : 1;		// in Legende Anzeigen
	unsigned short m_fEnterSpace : 1;	// Leerzeile einfügen
	unsigned short m_fDirty : 1;	// wurde geändert
	unsigned short m_fCustText : 1;	// Text wurde geändert
	
protected:
	char *m_pText;			// das ist der andere Text (wenn != NULL)

private:
	long m_lPosition;		// aktuell links oben
	long m_lHeight;			// Höhe des Eintrages
	
public:
	CLegendInfoEntry (WORD iSrt, BOOL fShow, BOOL fSpace, VisType rgType);
	virtual ~CLegendInfoEntry (void);

virtual	bool SaveLegendEntry (class CLegEntryParser &rP, long lMCode) = 0;
virtual LEGENTRYTYPE isA (void) = 0;	// Typ dieses Eintrages

	VisType GetVType (void) { return m_rgType; }
	bool isShown (void) { return m_fShow ? true : false; }
	void isShown (bool fShow, bool fSetDirty = true)  
	{ 
		if (fShow) m_fShow = true; else m_fShow = false; 
		if (fSetDirty) m_fDirty = true;
	}
	bool hasSpace (void) { return m_fEnterSpace ? true : false; }
	void hasSpace (bool fSpace, bool fSetDirty = true)  
	{ 
		if (fSpace) m_fEnterSpace = true; else m_fEnterSpace = false; 
		if (fSetDirty) m_fDirty = true;
	}
	bool isDirty (void) { return m_fDirty ? true : false; }
	void SetDirty (bool fDirty = true) { m_fDirty = fDirty ? true : false; }

virtual bool CustomizedText (void) { return m_fCustText ? true : false; }
virtual void CustomizedText (bool fCust) { if (fCust) m_fCustText = true; else m_fCustText = false; }
virtual	char *GetText (bool = true) = 0;

	void SetText (LPCSTR pText);
	void ResetText (void);

	void SetPosition (long lNewPos) { m_lPosition = lNewPos; }
	long GetPosition (void) { return m_lPosition; }
	void SetHeight (long lNewHeight) { m_lHeight = lNewHeight; }
	long GetHeight (void) { return m_lHeight; }
	bool HitTest (long lPos) { return (lPos >= m_lPosition && lPos < m_lPosition + m_lHeight); }
	char *GetTextRef (void) const { return m_pText; }
	
// Funktionen zur SuchSchlüsselVerwaltung
	WORD & FGetWORD (void);		// liefert SuchSchlüssel
friend int FCmpWORD (WORD &, WORD &);	// vergleicht 2 Schlüssel
};

class CLegendInfoIdent : 
	public CLegendInfoEntry 
{
private:
	INT_PTR m_lIdent;	// Identifikator

public:
		CLegendInfoIdent (WORD iSrt, BOOL fShow, BOOL fSpace,
				  VisType rgType, INT_PTR lIdent);
		~CLegendInfoIdent (void);

	char *GetText (bool = true);
	bool SaveLegendEntry (class CLegEntryParser &rP, long lMCode);
	
	LEGENTRYTYPE isA (void) { return LEGENTRYTYPE_IDENT; }
	INT_PTR GetIdent (void) { return m_lIdent; }
};

class CLegendInfoObject : 
	public CLegendInfoEntry 
{
private:
	INT_PTR m_lONr;	// ObjektNummer
	short m_iIconWidth;
	
public:
		CLegendInfoObject (WORD iSrt, BOOL fShow, BOOL fSpace,
				   VisType rgType, INT_PTR lONr);
		~CLegendInfoObject (void);

	char *GetText (bool = true);
	bool SaveLegendEntry (class CLegEntryParser &rP, long lMCode);
	
	LEGENTRYTYPE isA (void) { return LEGENTRYTYPE_OBJECT; }
	INT_PTR GetONr (void) { return m_lONr; }
	short &IconWidth (void) { return m_iIconWidth; }
};

class CLegendInfoText : 
	public CLegendInfoEntry 
{
private:
	INT_PTR m_lMCode;
	os_string m_strView;
	
public:
		CLegendInfoText (WORD iSrt, BOOL fSpace, LPCSTR pcView, INT_PTR lMCode);
		~CLegendInfoText (void);

	char *GetText (bool = true);
	bool SaveLegendEntry (class CLegEntryParser &rP, long lMCode);
	bool OnRemoveEntry (INT_PTR lMCode);

	LEGENTRYTYPE isA (void) { return LEGENTRYTYPE_TEXT; }
	INT_PTR GetMCode() { return m_lMCode; }
	LPCSTR GetView() { return m_strView.c_str(); }
};

///////////////////////////////////////////////////////////////////////////////
// ZwischenZeile ist im Prinzip eine leere Zwischenüberschrift
class CLegendInfoSpaceLine :
	public CLegendInfoText
{
public:
	CLegendInfoSpaceLine (WORD iSrt, LPCSTR pcView, INT_PTR lMCode)
		: CLegendInfoText(iSrt, FALSE, pcView, lMCode) {}
	~CLegendInfoSpaceLine (void) {}

// überladene Member
	char *GetText (bool = true);
	LEGENTRYTYPE isA (void) { return LEGENTRYTYPE_SPACELINE; }
};

///////////////////////////////////////////////////////////////////////////////
// Eigentliche typspezifische TreeKlasse 

// Funktionstypen, die Schlüsselverwaltung realisieren 
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
	DatenBasisObjekt &m_rDBO;
				
	WORD m_iLast;		// iOrder für fehlende Infos

	bool m_fActArea;
	bool m_fSizesLikeScaling;	// Größen wie im Bild darstellen
	
protected:
	void UserDelete (void *pObj);
	bool MakeMCodes (long &rlVMCode, long &rlMCode, const char *pView = NULL, INT_PTR lONr = 0);

public:
	typedef set<INT_PTR, less<INT_PTR> > CMCodes;
	
// Konstruktor/Destruktor
		CLegendInfo (CLegEntryParser &rP, DatenBasisObjekt &rDBO, long lMCode);
		~CLegendInfo (void);

static CLegendInfo *CreateInstance (CLegEntryParser &rP, DatenBasisObjekt &rDBO, long lMCode);

	bool FInit (CIdTree &rIDs);

// Elementarfunktionen
	bool FAddItem (LEGENTRYTYPE rgType, WORD iSrt, VisType rgVType, 
		       INT_PTR lTarget, LPCSTR pText, bool fShow = true,
		       bool fSpace = false, INT_PTR lMCode = NULL);	// Element hinzufügen
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
	bool AddText (WORD &riOrder, INT_PTR lMCode, LPCSTR pcText = NULL, bool fInsertBefore = false);

static int ExtractMCodes (char *pMWert, CMCodes &rMCodes);
static int WriteMCodes (CMCodes &rMCodes, char *pMWert, int iLen);

	bool GetSortOrder (WORD &riOrder, bool &rfShow, bool &rfSpace, 
			   char *& pText, VisType iVTyp, INT_PTR lTarget, 
			   short iTType, long lMCode = 0L);
	void FSetDirty (WORD &iOrder);
	bool SaveLegend (void);
	bool ResetLegend (char *pView);
	bool ViewSelected (LPCSTR pcView);

	bool MoveUp (WORD &iActSel, bool fShowAll);
	bool MoveDown (WORD &iActSel, bool fShowAll);
	bool FPasteEntry (LEGENTRYTYPE, VisType, INT_PTR lTarget, INT_PTR lMCode, char *pText, WORD iOrder);
	
	bool RemoveEntry (WORD iActSel);
	bool InsertHeadLine (WORD iActSel, LPCSTR pcText, bool fInsertBefore = false);
	
	bool isFirstEntry (WORD iOrder);
	bool isLastEntry (WORD iOrder);
	
	bool hasSpace (WORD iOrder, bool fSpace);

	int RetrieveMode (bool &rfAreaMode, bool &rfScaleMode);		// aus Sicht einlesen
	void SaveMode (LPCSTR);

	DatenBasisObjekt &DBO() { return m_rDBO; }

inline	bool ShowAreaOnly (void) { return m_fActArea ? true : false; }
inline	void SetAreaOnly (bool fActArea) { m_fActArea = fActArea ? true : false; }

inline	bool GetScaleMode (void) { return m_fSizesLikeScaling ? true : false; }
inline	void SetScaleMode (bool fScaleMode) { m_fSizesLikeScaling = fScaleMode ? true : false; }
};

///////////////////////////////////////////////////////////////////////////////
// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareLock (CLegendInfo, CLegendInfoEntry);

///////////////////////////////////////////////////////////////////////////////
// sonstige FunktonsPrototypen 
bool FormatString (char *pBuffer, CLegendInfoEntry *[LEGENTRYTYPE_CNT]);
bool FormatString (char *pBuffer, CLegendInfoEntry *);
char *GetPBDText (long lIdent, char *pText, int iLen);

///////////////////////////////////////////////////////////////////////////////
// Enumerationsfunktionen
extern "C" BOOL EXPORTTRIAS WINAPI HandleIdentOnResetLegend (long lIdent, BOOL, void *pData);
extern "C" BOOL EXPORTTRIAS WINAPI HandleObjectOnResetLegend (long lONr, BOOL, void *pData);

#endif // _LEGDINFO_HXX

