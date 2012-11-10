///////////////////////////////////////////////////////////////////////////
// @doc 
// @module Ident.hxx | Klassen für die Beschreibung diverser Identifikatorstrukturen

#if !defined(_IDENT_HXX__54A03534_1E15_11D2_9E96_006008447800__INCLUDED_)
#define _IDENT_HXX__54A03534_1E15_11D2_9E96_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Funktionsprototypen 
extern "C" {
	_TRIAS02_ENTRY BOOL isDBTextObjekt (HPROJECT hPr, long ONr);
	_TRIAS02_ENTRY BOOL isDBSubTextObjekt (HPROJECT hPr, long ONr);
	_TRIAS02_ENTRY BOOL isDBSubTextObjektInd (HPROJECT hPr, long ONr);
}

#if !defined(NOIDENT)

#if !defined(MARKER1)
#define MARKER1 	170
#define FIRSTFILLBMP	1992
#endif

///////////////////////////////////////////////////////////////////////////////
// TreeContainer von Identifikatoren 
#define VI_NotChanged	((VisInfo *)1)
#define VI_Changed		((VisInfo *)2)
#define VI_OtherType	((VisInfo *)3)

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

///////////////////////////////////////////////////////////////////////////////
//
const int _MAX_KURZTEXT	= _MAX_PATH;		// max. Länge eines Kurztextes

///////////////////////////////////////////////////////////////////////////////
// ObjektListe
#include <ospace/std/set>
typedef set<long, less<long> > CIdentObjects;

///////////////////////////////////////////////////////////////////////////////
// globale Funktion
short VTypToBits (VisType iVTyp);

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

	unsigned int m_fGeometryChanged : 4;	// das zu ladende geometriefeld wurde geändert

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
	CIdentObjects *m_pObjs;	// Liste der Objekte mit diesem Ident

	HPROJECT m_hPr;				// HPROJECT des zugehörigen Objektes
	os_string m_strKurzText;	// Pufferbereiche für Kurz/Langtext
	os_string m_strLangText;
	os_string m_strDataSource;

	long m_lObjNameFeature;	// Zugriffsnummer für Objektnamen für diese Objektklasse

	void ChangeMainColor (VisInfo *pVI);

static 	CIgnoreVisErrorTree *m_pIVET;

public:
// Konstruktor/Destruktor
	_TRIAS02_ENTRY CIdentifikator (
		HPROJECT hPr, long Id, VisInfo *ppVI[4], short fSpec, HPALETTE hPal = NULL);
	_TRIAS02_ENTRY ~CIdentifikator (void);

_TRIAS02_ENTRY short GetCompleteVisInfo (VisInfo **, short iBits, short *piGot = NULL);

_TRIAS02_ENTRY VisInfo * ChangeVisInfo (VisInfo *pVI, VisType = VT_Default);
_TRIAS02_ENTRY VisInfo * GetVisInfo (VisType);
_TRIAS02_ENTRY VisInfo * CopyVisInfo (VisInfo *pVI);

_TRIAS02_ENTRY ErrCode ReportVisInfoError (ErrCode EC, RoutCode RC, short iVTyp);
	
_TRIAS02_ENTRY BOOL hasVI (VisType); 
_TRIAS02_ENTRY VisInfo & VI (VisType);	// Abfragefunktionen

_TRIAS02_ENTRY PVisInfo &PVI (void);
_TRIAS02_ENTRY LVisInfo &LVI (void);
_TRIAS02_ENTRY FVisInfo &FVI (void);
_TRIAS02_ENTRY TVisInfo &TVI (void);

_TRIAS02_ENTRY Color GetColor (VisType, Colors = BLACK);
_TRIAS02_ENTRY Color GetBkColor (void);
_TRIAS02_ENTRY Color Get2ndColor (void);
_TRIAS02_ENTRY BOOL isOpaque (void);
_TRIAS02_ENTRY BOOL isBkConture (void);
_TRIAS02_ENTRY pPen GetPen (VisType, short locWidth = 0);
_TRIAS02_ENTRY pBrush GetBrush (HDC hDC, BOOL fForceOpaque = false, Bitmap **ppBmp = NULL);
_TRIAS02_ENTRY pFont GetFont (Dimension);
_TRIAS02_ENTRY pFont GetFont (void);

_TRIAS02_ENTRY short BKMode (VisType);
_TRIAS02_ENTRY BOOL FrameMode (void);
_TRIAS02_ENTRY BOOL RoundFrame (void);
_TRIAS02_ENTRY short AlignStyle (void);

	BOOL hasColor (void) { return m_fhasColor; }
	BOOL hasPen (void) { return m_fhasPen; }
	BOOL hasBrush (void) { return m_fhasBrush; }
	BOOL hasFont (void) { return m_fhasFont; }

	void hasColor (BOOL newVal) { m_fhasColor = newVal; }
	void hasPen (BOOL newVal) { m_fhasPen = newVal; }
	void hasBrush (BOOL newVal) { m_fhasBrush = newVal; }
	void hasFont (BOOL newVal) { m_fhasFont = newVal; }

	short toPaint (short iMsk = TPAll) { return m_fIdPaint & iMsk; }
	void EnablePainting (short fToPaint) { m_fIdPaint = fToPaint; }
	void DisablePainting (void) { m_fIdPaint = 0; }

	BOOL loaded (void) { return m_fIdLoaded; }
	void Load (void) { m_fIdLoaded = true; }
	void UnLoad (void) { m_fIdLoaded = false; m_fIdNotAllLoaded = true; m_fMovedAway = false; m_fGeometryChanged = 0; }

	BOOL AreAllLoaded (void) { return ! m_fIdNotAllLoaded; }
	void NotAllLoaded (void) { m_fIdNotAllLoaded = true; }
	void AllLoaded (void) { m_fIdNotAllLoaded = false; }

	BOOL MovedAway (void) { return m_fMovedAway; }
	void MovedAway (BOOL fFlag) { if (fFlag) m_fMovedAway = true; else m_fMovedAway = false; }

	BOOL isTemp (void) { return m_fIdTemp; }
	void Temp (void) { m_fIdTemp = true; }
	void Perm (void) { m_fIdTemp = false; }

	BOOL isModified (void) { return m_fIdModified; }
	void Modified (void) { m_fIdModified = true; }
	void UnModified (void) { m_fIdModified = false; }

	BOOL isVisible (short iMsk = TPAll) { return m_fIdIsDrawn & iMsk; }
	void SetVisible (short newF = TPAll) { m_fIdIsDrawn |= newF; }
	void SetInvisible (void) { m_fIdIsDrawn = 0; }

	void SetSpecial (short newV = TPAll) { m_fSpecial = newV; }
	short GetSpecial (short iMsk = TPAll) { return m_fSpecial & iMsk; }

	short isCustomized (short iMsk = TPAll) 
				{ return (m_fIdPaint & ~m_fSpecial) & iMsk; }

	void SetOTypes (short newOTypes = TPAll) { m_fOTypes = newOTypes; m_fOTypesSet = true; }
	short GetOTypes (short iMsk = TPAll) { return m_fOTypes & iMsk; }
	void ResetInit (void) { m_fOTypesSet = false; }
	BOOL GetOTypesSet (void) { return m_fOTypesSet ? true : false; }

_TRIAS02_ENTRY short GetOTypes (GeoDB &rDB);
_TRIAS02_ENTRY BOOL GetOTypesEx (GeoDB &rDB, short &rOTypes);
_TRIAS02_ENTRY BOOL SetObjectList (long lFlexNum);
_TRIAS02_ENTRY void ResetObjectList (void);
_TRIAS02_ENTRY BOOL AddObjectToList (GeoDB &rDB, long lONr);
_TRIAS02_ENTRY BOOL RemoveObjectFromList (GeoDB &rDB, long lONr);
_TRIAS02_ENTRY BOOL IsObjectInList (long lONr);
_TRIAS02_ENTRY BOOL GetObjectList (GeoDB &rDB, CIdentObjects &rObjs);
_TRIAS02_ENTRY BOOL FindId (GeoDB &rDB, long *plFlex = NULL, short *pOTypes = NULL);
_TRIAS02_ENTRY LPCSTR FGetGeomName (VisType rgVType = VT_Default);
	
	CIdentObjects *DetachObjList (void) { CIdentObjects *pObjs = m_pObjs; m_pObjs = NULL; return pObjs; }
	CIdentObjects *AttachObjList (CIdentObjects *pObjs) { CIdentObjects *pT = m_pObjs; m_pObjs = pObjs; return pT; }

_TRIAS02_ENTRY void SetSearchAble (short newS);
_TRIAS02_ENTRY short GetSearchAble (short iMsk = TPAll);

	void SetObjectDrawn (short newF) { m_fObjectsDrawn = newF; }
	void AddObjectDrawn (short newF) { m_fObjectsDrawn |= newF; }
	BOOL GetObjectDrawn (short iMsk = TPAll) { return m_fObjectsDrawn & iMsk; }

	void SetGeometryChanged (short newF) { m_fGeometryChanged = newF; }
	void AddGeometryChanged (short newF) { m_fGeometryChanged |= newF; }
	void RemoveGeometryChanged (short newF) { m_fGeometryChanged &= ~newF; }
	BOOL GetGeometryChanged (VisType iVTyp) { return m_fGeometryChanged & VTypToBits(iVTyp); }

	BOOL GetMetaDCFlag (void) { return m_fMetaDC ? true : false; }

	void SetHasKO (BOOL fFlag = true) { m_fhasKO = fFlag ? true : false; }
	BOOL hasKO (void) { return m_fhasKO ? true : false; }

_TRIAS02_ENTRY short toFill (VisType);
	int Marker (void) { return toFill (VT_Punkt) + MARKER1 -1; }

	long &Id (void) { return m_lIdent; }
_TRIAS02_ENTRY short & Priority (VisType = VT_Default);
_TRIAS02_ENTRY Dimension & Size (VisType);
_TRIAS02_ENTRY short & Width (void);

_TRIAS02_ENTRY short FrameWidth (void);
_TRIAS02_ENTRY short FillMode (void);

_TRIAS02_ENTRY short Escapement (void);	// Textdrehung
_TRIAS02_ENTRY short Rotation (void);		// Punktsymbol
	
	HPALETTE hPal (void) { return m_hPalette; }
	short &DType (void) { return m_DrawType; }

_TRIAS02_ENTRY void ResetResources (void);
_TRIAS02_ENTRY static void ReleaseIgnoreTree (void);
_TRIAS02_ENTRY BOOL SetMetaDC (BOOL fMetaDC);

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
	
_TRIAS02_ENTRY long InitObjectCount (ObjTyp rgOTyp, long lObjCnt = 0);

_TRIAS02_ENTRY HRESULT GetObjNameFeature (GeoDB &rDB, long *plMCode, bool fCreateNew = false);

// TRiASDB ////////////////////////////////////////////////////////////////////
// Pbd-support
_TRIAS02_ENTRY LPCSTR GetKurzText (BOOL fAppendDataSource = FALSE);
_TRIAS02_ENTRY LPCSTR GetLangText();
_TRIAS02_ENTRY LPCSTR GetDataSource();

_TRIAS02_ENTRY HRESULT EnsureLoaded (long lONr, DWORD dwTypes, LPCSTR pcGeomName = NULL, ObjContainer *pOC = NULL, ITRiASObject **ppIObj = NULL);
_TRIAS02_ENTRY HRESULT MayUnload (long lONr);

protected:
	HRESULT GetRelatedObjects (ITRiASObjects **ppIObjs);
	
	void SetSearchAbleTyp (short iOTyp, bool fFlag);
	short GetSearchAbleTyp (short iOTyp);

public:
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

	BOOL GetObjType (char *pBuffer, int iLen);

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

	BOOL AddEntry (CIdentifikator &, VisInfo *pVI);
};

// DeclareLock (CIdTree2, CIdRef); - aber zu Fuß, da andere operator's --------
// gebraucht werden
class CIdRefLock : 
	public CLock 
{
public:
	CIdRefLock (CNavigator &nav) : CLock (nav) {}
#if defined(WIN16)
	CIdRefLock (CFreeStore *pfs, FSHandle h) : CLock (pfs, h) {}
#endif

	operator CIdRef * (void) { return (CIdRef *)CLock :: P(); }
	operator CIdentifikator * (void) { return & ((CIdRef *)CLock :: P()) -> rCId(); }
	CIdentifikator * operator -> (void) { return & ((CIdRef *)CLock :: P()) -> rCId(); }
	BOOL operator ! (void) { return ((CIdRef *)CLock :: P()) == NULL; }
	BOOL isValid (void) { return ((CIdRef *)CLock :: P()) != NULL; }
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
protected:
	void DeletePriority (CTable &t, short iPrio, VisType iVTyp, long lIdent);
	BOOL hasIdent (CTable &tPr, long lIdent);
#if defined(_FORCE_LEGACY_CODE)
	ErrCode WriteBackVisInfo (CIdentifikator *pId, Sicht &s, VisType iVTyp);
#endif // defined(_FORCE_LEGACY_CODE)

public:
// Konstruktor
		CIdTree (void);

// Funktionen liefern Verweise auf die beiden Bäume
	CIdTree1 & IdentTree (void) { return *(CIdTree1 *)this; }
	CIdTree2 & PrioTree (void) { return *(CIdTree2 *)this; }

// Funktionen zum überprüfen und löschen eines Idents aus dem DoppelBaum
	BOOL DeleteIdent (long lIdent, short iVTyp = TPAll);
#if defined(_FORCE_LEGACY_CODE)
	BOOL AddNewIdent (GeoDB &rDB, long lIdent, HPALETTE hPalette, short = 0, short = TPAll, long lTargetId = -1L);
	ErrCode WriteBack (GeoDB &rDB, char *pSichtName);
#endif // defined(_FORCE_LEGACY_CODE)
	BOOL AddIdent (HPROJECT hPr, long lIdent, VisInfo *ppVI[4], short fSpec, HPALETTE hPal = NULL);

	BOOL ChangePriority (long Ident, short newPrio, VisType iVTyp, BOOL isChanged);
	short toPaint (long Ident, short iMsk = TPAll);
	Color GetColor (long Ident, VisType iVTyp = VT_Default);
	BOOL isUsed (GeoDB &rDB, long Ident);

	BOOL RetrieveVisInfo (long lONr, short iVTyp, VISINFO &rVI);
	
	void AllDelete (void);
	void ReleaseIgnoreTree (void);
	void ResetAllLoaded (void);

	BOOL hasIdentVType (long lIdent, VisType iVTyp);

	long GetPointCount (long lIdent);
	long GetLineCount (long lIdent);
	long GetAreaCount (long lIdent);
	long GetTextCount (long lIdent);
	long GetComplexCount (long lIdent);
	long GetObjectCount (long lIdent, ObjTyp rgOTyp);

	long InitPointCount (long lIdent, long lPCnt = 0);
	long InitLineCount (long lIdent, long lLCnt = 0);
	long InitAreaCount (long lIdent, long lFCnt = 0);
	long InitTextCount (long lIdent, long lTCnt = 0);
	long InitComplexCount (long lIdent, long lKCnt = 0);
	long InitObjectCount (long lIdent, ObjTyp rgOTyp, long lObjCnt = 0);

	long IncrementObjectCount (GeoDB &rDB, long lIdent, ObjTyp rgOTyp, long lONr = 0L);
	long DecrementObjectCount (GeoDB &rDB, long lIdent, ObjTyp rgOTyp, long lONr = 0L);

	BOOL FindId (GeoDB &rDB, long lIdent, long *plFlex, short *pOTypes = NULL);
	BOOL ModifyIdent (GeoDB &rDB, long lONr, long lNewId, long lOldId);

	HRESULT GetObjNameFeature (GeoDB &rDB, long lIdent, long *plMCode, bool fCreateNew = false);

// Pbd-support
	LPCSTR GetKurzText(INT_PTR lIdent, BOOL fAppendDataSource = FALSE);
	LPCSTR GetLangText(INT_PTR lIdent);

// Destruktor
		~CIdTree (void);
};

#if !defined(LONGCOMP)
#define LONGCOMP
// Funktionen für ObjektListe : Tree (Zugriffs- und Vergleichsfunktionen) -----
inline int LongCmp (void *Key1, void *Key2) 
{
long Par1 = *(INT_PTR *)Key1, Par2 = *(INT_PTR *)Key2;
	if (Par1 > Par2) 	return 1;
	else if (Par1 < Par2) 	return -1;
	else 			return 0;
}
inline int ULongCmp (void *Key1, void *Key2) 
{
unsigned long Par1 = *(UINT_PTR *)Key1, Par2 = *(UINT_PTR *)Key2;

	if (Par1 > Par2) 	return 1;
	else if (Par1 < Par2) 	return -1;
	else 			return 0;
}
#endif // LONGCOMP

#endif // NOIDTREE
#endif // NOIDENT

#endif // !defined(_IDENT_HXX__54A03534_1E15_11D2_9E96_006008447800__INCLUDED_)
