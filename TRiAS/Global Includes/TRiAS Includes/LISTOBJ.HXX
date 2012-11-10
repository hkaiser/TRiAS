///////////////////////////////////////////////////////////////////////////
// @doc 
// @module listobj.hxx | Objektliste separiert, um unnötige Header zu vermeiden

#if !defined(_LISTOBJ_HXX__766329D6_0736_11D2_8657_00600875138A__INCLUDED_)
#define _LISTOBJ_HXX__766329D6_0736_11D2_8657_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(_USE_MAP_FOR_OBJEKTLISTE)

#include <ObjektListe.h>

#else

void *GetObjNum (void *);
inline int LongCmp (void *, void *);

#include <copttree.hxx>

// Liste der bereits extrahierten GeoObjekte 
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
class ExtShapeObject;

class _TRIAS02_ENTRY ObjektListe : 
	public ObjektListe1, 
	public ObjektListe2 
{
private:
#if !defined(WIN16)
	long m_lPCnt;	// Zähler der geladenen Objekttypen
	long m_lLCnt;
	long m_lFCnt;
	long m_lTCnt;
	long m_lKCnt;
#endif // WIN16

public:
// Konstruktor
		EXPORT02 ObjektListe (void);

// Memberfunktionen
	BOOL EveryDelete (void);
	BOOL EXPORT02 DeleteObjekt (long ON);	// Objekt ON herauslöschen
	BOOL EXPORT02 ModIdent (long ON, long oldId, long newId);

	BOOL EXPORT02 ModGIText (long ONr, Punkt &);
	BOOL EXPORT02 FindSchriftObjekt (Point Pt, long &ON, Rectangle &R);
	BOOL CorrectPosition (long ONr, Point &Pt);

	BOOL EXPORT02 FindObjectsFromPoint (Point Pt, short iMode, BOOL (*eFcn)(long, RECT, void *), void *pData);
	BOOL FindObjectsFromPointEx (FINDOBJECT *pFO);

	BOOL EXPORT02 ModGIPunkt (long ONr, Punkt &);

	ObjTyp EXPORT02 RetrieveObjTyp (GeoDB &rDB, long ON);	// liefert ObjektTyp
	short EXPORT02 RetrieveObjStatus (long ON);	// liefert ObjektStatus
	BOOL EXPORT02 isObjectVisible (long lONr);	// Objekt ist sichtbar

	VisInfo *RetrieveVisInfo (long lONr);	// liefert VisInfo

#if defined(_USE_KOMPLEX_OBJECTS)
	long EXPORT02 GetRCode (long ONr);	// liefert RCode von KObjekten
	long MergeKObjects (GeoDB &rDB, long O1, long O2, long Ident, long RCode, BOOL iMerge);
						// faßt Objekte zusammen
	long DeleteONFromKObject (GeoDB &rDB, long KONr, long ONr);
	BOOL EXPORT02 EnumKObjects (long ONr, BOOL (*fcn)(long, BOOL, void *), void *pData);
#endif // defined(_USE_KOMPLEX_OBJECTS)

	BOOL CondOptimize (ULARGE_INTEGER liInsertTime) { return true; }
	ULARGE_INTEGER TimedInsert (ExtShapeObjectDCreator &rDOC, ObjTyp rgOTyp);	// liefert Zeit des Einbauens/optimiert
	
// TypKonvertierung
	CTree & EXPORT02 ObjNumTree (void);
	CTree & EXPORT02 ObjIdTree (void);

#if !defined(WIN16)
inline long GetPointCount (void) { return m_lPCnt; }
inline long GetLineCount (void) { return m_lLCnt; }
inline long GetAreaCount (void) { return m_lFCnt; }
inline long GetTextCount (void) { return m_lTCnt; }
inline long GetComplexCount (void) { return m_lKCnt; }
		
	long GetObjectCount (ObjTyp rgOTyp);

	long IncrementObjectCount (ObjTyp rgTyp);
	long DecrementObjectCount (ObjTyp rgTyp);
#endif // WIN16

// Destruktor 
		EXPORT02 ~ObjektListe (void);
};

// Deklaration der zusätzlich notwendigen Klassen -----------------------------
// (ExtShapeObjectDCreator und ExtShapeObjectLock)
DeclareDLock (ObjektListe, ExtShapeObject);

#define CONrTable	CTable
#define CIdentTable	CTable
#define ExtShapeObjectONrLock	ExtShapeObjectLock
#define ExtShapeObjectIdentLock	ExtShapeObjectLock

#endif // defined(_USE_MAP_FOR_OBJEKTLISTE)

#endif // !defined(_LISTOBJ_HXX__766329D6_0736_11D2_8657_00600875138A__INCLUDED_)
