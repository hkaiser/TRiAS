// Objektliste separiert, um unnötige Header zu vermeiden ---------------------
// File: LISTOBJ.HXX

#if !defined(_LISTOBJ_HXX)
#define _LISTOBJ_HXX

void *GetObjNum (void *);
inline int LongCmp (void *, void *);

#include <copttree.hxx>

// Liste der bereits extrahierten GeoObjekte ----------------------------------
class _TRIAS02_ENTRY ObjektListe1 : 
	public COptTree // UniqueTree
{	// enthält ObjektNummern
protected:
	void UserDelete (void *pObj);	// Beseitigen des Listenelementes

public:
// Konstruktor
		ObjektListe1 (void);
// Destruktor
		~ObjektListe1 (void);

	LONGLONG GetLastInsertTime() { return m_liLastInsertTime.QuadPart; }
};

class _TRIAS02_ENTRY ObjektListe2 : 
	public COptTree  // DelTree
{		// enthält Identifikatoren
private:
	void UserDelete (void *pObj) {}	// nothing to do (never called)

public:
// Konstruktor
		ObjektListe2 (void);
// Destruktor
		~ObjektListe2 (void);

	LONGLONG GetLastInsertTime() { return m_liLastInsertTime.QuadPart; }
};

typedef struct tagFINDOBJECT FINDOBJECT;	// forward decl only
class ExtShapeObjectDCreator;

class _TRIAS02_ENTRY ObjektListe : 
	public ObjektListe1, 
	public ObjektListe2 
{
private:
	GeoDB &m_rDB;	// zugehörige GeoDB

#if defined(WIN32)
	long m_lPCnt;	// Zähler der geladenen Objekttypen
	long m_lLCnt;
	long m_lFCnt;
	long m_lTCnt;
	long m_lKCnt;
#endif // WIN32

public:
// Konstruktor
		EXPORT02 ObjektListe (GeoDB &rDB);

// Memberfunktionen
	Bool EveryDelete (void);
	Bool EXPORT02 DeleteObjekt (long ON);	// Objekt ON herauslöschen
	Bool EXPORT02 ModIdent (long ON, long oldId, long newId);

	Bool EXPORT02 ModGIText (long ONr, Punkt &);
	Bool EXPORT02 FindSchriftObjekt (Point Pt, long &ON, Rectangle &R);
	Bool CorrectPosition (long ONr, Point &Pt);

	Bool EXPORT02 FindObjectsFromPoint (Point Pt, short iMode, BOOL (*eFcn)(long, RECT, void *), void *pData);
	Bool FindObjectsFromPointEx (FINDOBJECT *pFO);

	Bool EXPORT02 ModGIPunkt (long ONr, Punkt &);

	ObjTyp EXPORT02 RetrieveObjTyp (long ON);	// liefert ObjektTyp
	short EXPORT02 RetrieveObjStatus (long ON);	// liefert ObjektStatus
	BOOL EXPORT02 isObjectVisible (long lONr);	// Objekt ist sichtbar

	VisInfo *RetrieveVisInfo (long lONr);	// liefert VisInfo

	long EXPORT02 GetRCode (long ONr);	// liefert RCode von KObjekten
	long MergeKObjects (long O1, long O2, long Ident, long RCode, Bool iMerge);
						// faát Objekte zusammen
	long DeleteONFromKObject (long KONr, long ONr);
	Bool EXPORT02 EnumKObjects (long ONr, BOOL (*fcn)(long, BOOL, void *), void *pData);

	bool CondOptimize (ULARGE_INTEGER liInsertTime) { return true; }
	ULARGE_INTEGER TimedInsert (ExtShapeObjectDCreator &rDOC, ObjTyp rgOTyp);	// liefert Zeit des Einbauens/optimiert
	
// TypKonvertierung
	CTree & EXPORT02 ObjNumTree (void);
	CTree & EXPORT02 ObjIdTree (void);

inline GeoDB &DB() { return m_rDB; }
#if defined(WIN32)
inline long GetPointCount (void) { return m_lPCnt; }
inline long GetLineCount (void) { return m_lLCnt; }
inline long GetAreaCount (void) { return m_lFCnt; }
inline long GetTextCount (void) { return m_lTCnt; }
inline long GetComplexCount (void) { return m_lKCnt; }
		
	long GetObjectCount (ObjTyp rgOTyp);

	long IncrementObjectCount (ObjTyp rgTyp);
	long DecrementObjectCount (ObjTyp rgTyp);
#endif // WIN32

// Destruktor 
		EXPORT02 ~ObjektListe (void);
};

// Deklaration der zusätzlich notwendigen Klassen -----------------------------
// (ExtShapeObjectDCreator und ExtShapeObjectLock)
DeclareDLock (ObjektListe, ExtShapeObject);

#endif // _LISTOBJ_HXX
