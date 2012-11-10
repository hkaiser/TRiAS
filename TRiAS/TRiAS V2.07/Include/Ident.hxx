// Klassen für die Beschreibung diverser Identifikatorstrukturen
// File: IDENT.HXX

#if !defined(_IDENT_HXX)
#define _IDENT_HXX

// Funktionsprototypen --------------------------------------------------------
extern "C" {
	_TRIAS02_ENTRY bool EXPORT02 isDBTextObjekt (HPROJECT hPr, long ONr);
	_TRIAS02_ENTRY bool EXPORT02 isDBSubTextObjekt (HPROJECT hPr, long ONr);
	_TRIAS02_ENTRY bool EXPORT02 isDBSubTextObjektInd (HPROJECT hPr, long ONr);
}

#if !defined(NOIDENT)

#if !defined(MARKER1)
#define MARKER1 	170
#define FIRSTFILLBMP	1992
#endif

// TreeContainer von Identifikatoren ------------------------------------------
#define VI_NotChanged	(VisInfo *)1
#define VI_Changed	(VisInfo *)2
#define VI_OtherType	(VisInfo *)3


#if !defined(TPPunkt)
#define TPCustomized	0x00		// nicht DefaultVisInfo
#define TPDefaultInfo	0x80		// DefaultVisInfo

#define TPUnknown	0x00

#define TPPunkt		0x01
#define TPLinie		0x02
#define TPFlaeche	0x04
#define TPText		0x08

#define TPKO		0x10
#define TPSO		0x20

#define TPAll		(TPPunkt|TPLinie|TPFlaeche|TPText|TPKO)

#endif

class CIdTree;			// deklarieren
class CIgnoreVisErrorTree;
class VisInfo;

#if defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// ObjektListe
#include <ospace/std/set>
typedef set<long, less<long> > CIdentObjects;
#endif // WIn32

class CIdentifikator 
{
private:
// Member
	long m_lIdent;		// Ident

// diverse StatusBits
	unsigned int m_fIdPaint : 4;		// gehört zu aktueller Sicht
	unsigned int m_fIdIsDrawn : 4;		// im aktuellen Ausschnitt vertreten

	unsigned int m_fIdLoaded : 1;		// Objekte (teilweise) geladen
	unsigned int m_fIdTemp : 1;			// temporärer Identifikator
	unsigned int m_fIdModified : 1;		// IdentInfo ist modifiziert
	unsigned int m_fIdNotAllLoaded : 1;	// Nicht alle Objekte sind geladen
	unsigned int m_fhasColor : 1;		// Farbe gesetzt
	unsigned int m_fhasPen : 1;			// Pen ist generiert
	unsigned int m_fhasBrush : 1;		// Brush ist generiert
	unsigned int m_fhasFont : 1;		// Font ist generiert

	unsigned int m_fSpecial : 4;		// keine VisInfo gegeben
	unsigned int m_fOTypes : 5;			// Objekte in DatenBank
	unsigned int m_fSearchAble : 4;		// Objekte werden recherchiert
	
	unsigned int m_fObjectsDrawn : 4;	// für diesen Ident wurden Objekte
										// eines Typs gezeichnet
						
	unsigned int m_fMovedAway : 1;		// einige Objekte wurden temporär umklassifiziert,
										// d.h. dieser Ident gilt für die aktuelle Sicht
										// als vollständig geladen, bei Sichtwechsel wird
										// der Ident jedoch als nicht vollständig geladen
										// markiert.
	unsigned int m_fMetaDC : 1;			// derzeit Ausgabe in MetaDC
	unsigned int m_fhasKO : 1;			// es existieren Komplexobjkete für diesen Ident
	unsigned int m_fOTypesSet : 1;		// OTypes sind gültig

	pPen m_pP;              // Pointer auf Pen für diese Objekte
	pBrush m_pB;            // Pointer auf Brush für diese Objekte
	pBitmap m_pBM;			// Pointer auf Bitmap für Brush
	pFont m_pF;				// Pointer auf Font von TextObjekten

	VisInfo *m_pPVI;		// VisInfo (Punkt) für diesen ID
	VisInfo *m_pLVI;		// VisInfo (Linie) für diesen ID
	VisInfo *m_pFVI;		// VisInfo (Fläche) für diesen ID
	VisInfo *m_pTVI;		// VisInfo (Text) für diesen ID

	HPALETTE m_hPalette;	// verwendete Farbpalette

	Dimension m_FontSize;	// Größe des aktuellen Fonts
	short m_Width;			// aktuelle Liniendicke
	short m_DrawType;		// Art des Zeichnens

	long m_lPCnt;			// Zähler der geladenen Objekte
	long m_lLCnt;
	long m_lFCnt;
	long m_lTCnt;
	long m_lKCnt;
#if defined(WIN32)
	CIdentObjects *m_pObjs;	// Liste der Objekte mit diesem Ident
#endif // WIN32

	void ChangeMainColor (VisInfo *pVI);

static 	CIgnoreVisErrorTree *m_pIVET;

public:
// Konstruktor/Destruktor
	_TRIAS02_ENTRY EXPORT02 CIdentifikator (long Id, VisInfo *ppVI[4], 
											short fSpec, HPALETTE hPal = NULL);
	_TRIAS02_ENTRY EXPORT02 ~CIdentifikator (void);

_TRIAS02_ENTRY short EXPORT02 GetCompleteVisInfo (VisInfo **, short iBits, short *piGot = NULL);

_TRIAS02_ENTRY VisInfo * EXPORT02 ChangeVisInfo (VisInfo *pVI, VisType = VT_Default);
_TRIAS02_ENTRY VisInfo * EXPORT02 GetVisInfo (VisType);
_TRIAS02_ENTRY VisInfo * CopyVisInfo (VisInfo *pVI);

_TRIAS02_ENTRY ErrCode EXPORT02 ReportVisInfoError (ErrCode EC, RoutCode RC, short iVTyp);
	
_TRIAS02_ENTRY bool EXPORT02 hasVI (VisType); 
_TRIAS02_ENTRY VisInfo & EXPORT02 VI (VisType);	// Abfragefunktionen

	PVisInfo &PVI (void) { return (PVisInfo &)*m_pPVI; }
	LVisInfo &LVI (void) { return (LVisInfo &)*m_pLVI; }
	FVisInfo &FVI (void) { return (FVisInfo &)*m_pFVI; }
	TVisInfo &TVI (void) { return (TVisInfo &)*m_pTVI; }

_TRIAS02_ENTRY Color EXPORT02 GetColor (VisType, Colors = BLACK);
_TRIAS02_ENTRY Color EXPORT02 GetBkColor (void);
_TRIAS02_ENTRY Color EXPORT02 Get2ndColor (void);
_TRIAS02_ENTRY bool EXPORT02 isOpaque (void);
_TRIAS02_ENTRY bool EXPORT02 isBkConture (void);
_TRIAS02_ENTRY pPen EXPORT02 GetPen (VisType, short locWidth = 0);
_TRIAS02_ENTRY pBrush EXPORT02 GetBrush (HDC hDC, bool fForceOpaque = false, Bitmap **ppBmp = NULL);
_TRIAS02_ENTRY pFont EXPORT02 GetFont (Dimension);
_TRIAS02_ENTRY pFont EXPORT02 GetFont (void);

_TRIAS02_ENTRY short EXPORT02 BKMode (VisType);
_TRIAS02_ENTRY bool EXPORT02 FrameMode (void);
_TRIAS02_ENTRY bool EXPORT02 RoundFrame (void);
_TRIAS02_ENTRY short EXPORT02 AlignStyle (void);

	bool hasColor (void) { return m_fhasColor; }
	bool hasPen (void) { return m_fhasPen; }
	bool hasBrush (void) { return m_fhasBrush; }
	bool hasFont (void) { return m_fhasFont; }

	void hasColor (bool newVal) { m_fhasColor = newVal; }
	void hasPen (bool newVal) { m_fhasPen = newVal; }
	void hasBrush (bool newVal) { m_fhasBrush = newVal; }
	void hasFont (bool newVal) { m_fhasFont = newVal; }

	short toPaint (short iMsk = TPAll) { return m_fIdPaint & iMsk; }
	void EnablePainting (short fToPaint) { m_fIdPaint = fToPaint; }
	void DisablePainting (void) { m_fIdPaint = 0; }

	bool loaded (void) { return m_fIdLoaded; }
	void Load (void) { m_fIdLoaded = true; }
	void UnLoad (void) { m_fIdLoaded = false; m_fIdNotAllLoaded = true; m_fMovedAway = false; }

	bool AreAllLoaded (void) { return ! m_fIdNotAllLoaded; }
	void NotAllLoaded (void) { m_fIdNotAllLoaded = true; }
	void AllLoaded (void) { m_fIdNotAllLoaded = false; }

	bool MovedAway (void) { return m_fMovedAway; }
	void MovedAway (bool fFlag) { if (fFlag) m_fMovedAway = true; else m_fMovedAway = false; }

	bool isTemp (void) { return m_fIdTemp; }
	void Temp (void) { m_fIdTemp = true; }
	void Perm (void) { m_fIdTemp = false; }

	bool isModified (void) { return m_fIdModified; }
	void Modified (void) { m_fIdModified = true; }
	void UnModified (void) { m_fIdModified = false; }

	bool isVisible (short iMsk = TPAll) { return m_fIdIsDrawn & iMsk; }
	void SetVisible (short newF = TPAll) { m_fIdIsDrawn |= newF; }
	void SetInvisible (void) { m_fIdIsDrawn = 0; }

	void SetSpecial (short newV = TPAll) { m_fSpecial = newV; }
	short GetSpecial (short iMsk = TPAll) { return m_fSpecial & iMsk; }

	short isCustomized (short iMsk = TPAll) 
				{ return (m_fIdPaint & ~m_fSpecial) & iMsk; }

	void SetOTypes (short newOTypes = TPAll) { m_fOTypes = newOTypes; m_fOTypesSet = true; }
	short GetOTypes (short iMsk = TPAll) { return m_fOTypes & iMsk; }
	void ResetInit (void) { m_fOTypesSet = false; }
	bool GetOTypesSet (void) { return m_fOTypesSet ? true : false; }

_TRIAS02_ENTRY short EXPORT02 GetOTypes (GeoDB &rDB);
#if defined(WIN32)
_TRIAS02_ENTRY bool EXPORT02 GetOTypesEx (GeoDB &rDB, short &rOTypes);
_TRIAS02_ENTRY bool SetObjectList (long lFlexNum);
_TRIAS02_ENTRY void ResetObjectList (void);
_TRIAS02_ENTRY bool AddObjectToList (GeoDB &rDB, long lONr);
_TRIAS02_ENTRY bool RemoveObjectFromList (GeoDB &rDB, long lONr);
_TRIAS02_ENTRY bool IsObjectInList (long lONr);
_TRIAS02_ENTRY bool GetObjectList (CIdentObjects &rObjs);
_TRIAS02_ENTRY bool FindId (GeoDB &rDB, long *plFlex, short *pOTypes = NULL);
	
	CIdentObjects *DetachObjList (void) { CIdentObjects *pObjs = m_pObjs; m_pObjs = NULL; return pObjs; }
	CIdentObjects *AttachObjList (CIdentObjects *pObjs) { CIdentObjects *pT = m_pObjs; m_pObjs = pObjs; return pT; }
#endif // WIN32

	void SetSearchAble (short newS) { m_fSearchAble = newS; }
	short GetSearchAble (short iMsk = TPAll) { return m_fSearchAble & iMsk; }

	void SetObjectDrawn (short newF) { m_fObjectsDrawn = newF; }
	void AddObjectDrawn (short newF) { m_fObjectsDrawn |= newF; }
	bool GetObjectDrawn (short iMsk = TPAll) { return m_fObjectsDrawn & iMsk; }

	bool GetMetaDCFlag (void) { return m_fMetaDC ? true : false; }

	void SetHasKO (bool fFlag = true) { m_fhasKO = fFlag ? true : false; }
	bool hasKO (void) { return m_fhasKO ? true : false; }

_TRIAS02_ENTRY short EXPORT02 toFill (VisType);
	int Marker (void) { return toFill (VT_Punkt) + MARKER1 -1; }

	long &Id (void) { return m_lIdent; }
_TRIAS02_ENTRY short & EXPORT02 Priority (VisType = VT_Default);
_TRIAS02_ENTRY Dimension & EXPORT02 Size (VisType);
_TRIAS02_ENTRY short & EXPORT02 Width (void);

_TRIAS02_ENTRY short EXPORT02 FrameWidth (void);
_TRIAS02_ENTRY short EXPORT02 FillMode (void);

_TRIAS02_ENTRY short EXPORT02 Escapement (void);	// Textdrehung
_TRIAS02_ENTRY short EXPORT02 Rotation (void);		// Punktsymbol
	
	HPALETTE hPal (void) { return m_hPalette; }
	short &DType (void) { return m_DrawType; }

_TRIAS02_ENTRY void EXPORT02 ResetResources (void);
_TRIAS02_ENTRY static void EXPORT02 ReleaseIgnoreTree (void);
_TRIAS02_ENTRY bool EXPORT02 SetMetaDC (bool fMetaDC);

inline long GetPointCount (void) { return m_lPCnt; }
inline long GetLineCount (void) { return m_lLCnt; }
inline long GetAreaCount (void) { return m_lFCnt; }
inline long GetTextCount (void) { return m_lTCnt; }
inline long GetComplexCount (void) { return m_lKCnt; }

_TRIAS02_ENTRY long GetObjectCount (ObjTyp rgOTyp);
_TRIAS02_ENTRY long IncrementObjectCount (ObjTyp rgOTyp);
_TRIAS02_ENTRY long DecrementObjectCount (ObjTyp rgOTyp);

inline long InitPointCount (long lPCnt = 0) { return m_lPCnt = lPCnt; }
inline long InitLineCount (long lLCnt = 0) { return m_lLCnt = lLCnt; }
inline long InitAreaCount (long lFCnt = 0) { return m_lFCnt = lFCnt; }
inline long InitTextCount (long lTCnt = 0) { return m_lTCnt = lTCnt; }
inline long InitComplexCount (long lKCnt = 0) { return m_lKCnt = lKCnt; }
	
_TRIAS02_ENTRY long EXPORT02 InitObjectCount (ObjTyp rgOTyp, long lObjCnt = 0);

// Member/Friends
_TRIAS02_ENTRY friend void *GetIdent (void *pObj);
};

inline int LongCmp (void *, void *);
inline int ULongCmp (void *, void *);

#if !defined(NOIDTREE)

class _TRIAS02_ENTRY CIdTree1 : 
	public UniqueTree 
{	// enthält Identifikatoren
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CIdTree1 (void);
		~CIdTree1 (void);
};
DeclareLock (CIdTree1, CIdentifikator);

// Zweiter Baum - enthält Verweise auf CIdentifikator-Objekte -----------------
class _TRIAS02_ENTRY CIdRef 
{			// Klasse mit Verweisen auf CIdent's
protected:
	VisType m_iVTyp;		// VisualisierungsTyp
	short m_iPriority;		// zugehörige Priorität
	CIdentifikator &m_rCId;		// Verweis auf entsprechenden CIdentifikator

public:
// Konstruktor/Destruktor
		CIdRef (CIdentifikator &rCId, VisType iVTyp);
		CIdRef (CIdentifikator &rCId, VisType iVTyp, short iPrio);
		~CIdRef (void);

	short & FPriority (void) { return m_iPriority; }
	VisType FVisTyp (void) { return m_iVTyp; }
	CIdentifikator &rCId (void) { return m_rCId; }
	int GetLayerCount (double dScale);

// friends 
_TRIAS02_ENTRY friend void *GetPriority (void *pObj);
};


class _TRIAS02_ENTRY CIdTree2 : 
	public CTree 
{		// enthält Prioritäten
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CIdTree2 (void);
		~CIdTree2 (void);

	bool EXPORT02 AddEntry (CIdentifikator &, VisInfo *pVI);
};

// DeclareLock (CIdTree2, CIdRef); - aber zu Fuß, da andere operator's --------
// gebraucht werden
class CIdRefLock : 
	public CLock 
{
public:
	CIdRefLock (CNavigator &nav) : CLock (nav) {}
#if !defined(WIN32)
	CIdRefLock (CFreeStore *pfs, FSHandle h) : CLock (pfs, h) {}
#endif

	operator CIdRef * (void) { return (CIdRef *)CLock :: P(); }
	operator CIdentifikator * (void) { return & ((CIdRef *)CLock :: P()) -> rCId(); }
	CIdentifikator * operator -> (void) { return & ((CIdRef *)CLock :: P()) -> rCId(); }
	bool operator ! (void) { return ((CIdRef *)CLock :: P()) == NULL; }
	bool isValid (void) { return ((CIdRef *)CLock :: P()) != NULL; }
};

class CIdRefCreator : public CCreator {
public:
	CIdRefCreator (CIdTree2 &c) : CCreator (c) {}

	operator CIdRef * (void) { return (CIdRef *)CLock :: P(); }
	CIdentifikator * operator -> (void) { return & ((CIdRef *)CLock :: P()) -> rCId(); }
};

inline void *operator new (size_t iSize, CIdRefCreator &cr, CIdRef *)
{
	return cr.Alloc (iSize);
}


typedef struct tagVISINFO VISINFO;

class _TRIAS02_ENTRY CIdTree : 
	public CIdTree1, 
	public CIdTree2 
{
private:
	GeoDB &m_rDB;

protected:
	void DeletePriority (CTable &t, short iPrio, VisType iVTyp, long lIdent);
	bool hasIdent (CTable &tPr, long lIdent);
	ErrCode WriteBackVisInfo (CIdentifikator *pId, Sicht &s, VisType iVTyp);

public:
// Konstruktor
		EXPORT02 CIdTree (GeoDB &rDB);

// Funktionen liefern Verweise auf die beiden Bäume
	CIdTree1 & IdentTree (void) { return *(CIdTree1 *)this; }
	CIdTree2 & PrioTree (void) { return *(CIdTree2 *)this; }

// Funktionen zum überprüfen und löschen eines Idents aus dem DoppelBaum
	bool EXPORT02 DeleteIdent (long lIdent, short iVTyp = TPAll);
	bool AddNewIdent (long lIdent, HPALETTE hPalette, short = 0, short = TPAll, long lTargetId = -1L);
	bool EXPORT02 AddIdent (long lIdent, VisInfo *ppVI[4], short fSpec, HPALETTE hPal = NULL);

	bool EXPORT02 ChangePriority (long Ident, short newPrio, VisType iVTyp, bool isChanged);
	short EXPORT02 toPaint (long Ident, short iMsk = TPAll);
	Color EXPORT02 GetColor (long Ident, VisType iVTyp = VT_Default);
	bool EXPORT02 isUsed (GeoDB &rDB, long Ident);
	ErrCode EXPORT02 WriteBack (char *pSichtName);

	bool EXPORT02 RetrieveVisInfo (long lONr, short iVTyp, VISINFO &rVI);
	
	void EXPORT02 AllDelete (void);
	void EXPORT02 ReleaseIgnoreTree (void);
	void EXPORT02 ResetAllLoaded (void);

	bool EXPORT02 hasIdentVType (long lIdent, VisType iVTyp);

	long EXPORT02 GetPointCount (long lIdent);
	long EXPORT02 GetLineCount (long lIdent);
	long EXPORT02 GetAreaCount (long lIdent);
	long EXPORT02 GetTextCount (long lIdent);
	long EXPORT02 GetComplexCount (long lIdent);
	long EXPORT02 GetObjectCount (long lIdent, ObjTyp rgOTyp);

	long EXPORT02 InitPointCount (long lIdent, long lPCnt = 0);
	long EXPORT02 InitLineCount (long lIdent, long lLCnt = 0);
	long EXPORT02 InitAreaCount (long lIdent, long lFCnt = 0);
	long EXPORT02 InitTextCount (long lIdent, long lTCnt = 0);
	long EXPORT02 InitComplexCount (long lIdent, long lKCnt = 0);
	long EXPORT02 InitObjectCount (long lIdent, ObjTyp rgOTyp, long lObjCnt = 0);

	long EXPORT02 IncrementObjectCount (GeoDB &rDB, long lIdent, ObjTyp rgOTyp, long lONr = 0L);
	long EXPORT02 DecrementObjectCount (GeoDB &rDB, long lIdent, ObjTyp rgOTyp, long lONr = 0L);

#if defined(WIN32)
	bool FindId (GeoDB &rDB, long lIdent, long *plFlex, short *pOTypes = NULL);
	bool ModifyIdent (GeoDB &rDB, long lONr, long lNewId, long lOldId);
#endif // WIN32

// Destruktor
		EXPORT02 ~CIdTree (void);
};

#if !defined(LONGCOMP)
#define LONGCOMP
// Funktionen für ObjektListe : Tree (Zugriffs- und Vergleichsfunktionen) -----
inline int LongCmp (void *Key1, void *Key2) 
{
long Par1 = *(long *)Key1, Par2 = *(long *)Key2;
	if (Par1 > Par2) 	return 1;
	else if (Par1 < Par2) 	return -1;
	else 			return 0;
}
inline int ULongCmp (void *Key1, void *Key2) 
{
unsigned long Par1 = *(long *)Key1, Par2 = *(long *)Key2;

	if (Par1 > Par2) 	return 1;
	else if (Par1 < Par2) 	return -1;
	else 			return 0;
}
#endif // LONGCOMP

#endif // NOIDTREE
#endif // NOIDENT

#endif // _IDENT_HXX
