// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.09.99 13:32:41 
//
// @doc
// @module ObjektListe.h | Objektliste separiert, um unnötige Header zu vermeiden

#if !defined(_OBJEKTLISTE_H__56C2B31B_27D9_44B6_A99C_C34EDE21D605__INCLUDED_)
#define _OBJEKTLISTE_H__56C2B31B_27D9_44B6_A99C_C34EDE21D605__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>

void *GetObjNum (void *);
inline int LongCmp (void *, void *);

///////////////////////////////////////////////////////////////////////////////
// Liste der bereits extrahierten GeoObjekte: enthält ObjektNummern
class ExtShapeObject;

class _TRIAS02_ENTRY ObjektListe1 :
	public map<INT_PTR, ExtShapeObject *, less<INT_PTR> >
{
public:
	typedef INT_PTR	keytype_t;

	ObjektListe1 (void) {}
	~ObjektListe1 (void) { EveryDelete(); }

	LONGLONG GetLastInsertTime() { return 0L; }
	void Optimize() {}

	bool Delete (iterator it, bool fDelete = true);
	bool Delete (ExtShapeObject *pESO);
	bool EveryDelete();
	bool Find (INT_PTR *pKey, iterator *pit)
	{
	iterator it = find (*pKey);

		*pit = it;
		return it != end();
	}
	bool FindFirst (INT_PTR *pKey, iterator *pit) { return Find (pKey, pit); }
	bool FindNext (INT_PTR *pKey, iterator *pit) { return Find (pKey, pit); }

	bool Insert (ExtShapeObject *pESO, iterator *pit = NULL); 
	bool ReInsert (INT_PTR *pKey, iterator *pit); 
};

// enthält Identifikatoren
class _TRIAS02_ENTRY ObjektListe2 :
	public multimap<INT_PTR, ExtShapeObject *, less<INT_PTR> >
{
public:
	typedef INT_PTR	keytype_t;

	ObjektListe2 (void) {}
	~ObjektListe2 (void) { EveryDelete(); }

	LONGLONG GetLastInsertTime() { return 0L; }
	void Optimize() {}

	bool Delete (iterator it);
	bool EveryDelete() { clear(); return true; }

	bool Find (INT_PTR *pKey, iterator *pit)
	{
		return FindFirst (pKey, pit);
	}
	bool FindFirst (INT_PTR *pKey, iterator *pit)
	{
		*pit = lower_bound (*pKey);
		if (*pit != end()) {
			if ((**pit).first == *pKey) 
				return true;	// Key stimmt, gefunden
			*pit = end();		// doch nichts gefunden
		}
		return false;
	}
	bool FindNext (INT_PTR *pKey, iterator *pit)
	{
		if (++(*pit) == end()) 
			return false;

		if ((**pit).first == *pKey) 
			return true;

		*pit = end();	// nichts mehr gefunden
		return false;
	}

	bool Insert (ExtShapeObject *pESO, iterator *pit = NULL); 
	bool ReInsert (INT_PTR *pKey, iterator *pit);
};

typedef struct tagFINDOBJECT FINDOBJECT;	// forward decl only
class ExtShapeObjectDCreator;
class ExtShapeObject;

class _TRIAS02_ENTRY ObjektListe : 
	public ObjektListe1, 
	public ObjektListe2 
{
private:
	long m_lPCnt;	// Zähler der geladenen Objekttypen
	long m_lLCnt;
	long m_lFCnt;
	long m_lTCnt;
	long m_lKCnt;

public:
// Konstruktor
		ObjektListe (void);
		~ObjektListe (void);

// Memberfunktionen
	BOOL EveryDelete (void);
	BOOL DeleteObjekt (long ON);	// Objekt ON herauslöschen
	BOOL ModIdent (long ON, long oldId, long newId);

	BOOL ModGIText (long ONr, Punkt &);
	BOOL FindSchriftObjekt (Point Pt, long &ON, Rectangle &R);
	BOOL CorrectPosition (long ONr, Point &Pt);

	BOOL FindObjectsFromPoint (Point Pt, short iMode, BOOL (*eFcn)(long, RECT, void *), void *pData);
	BOOL FindObjectsFromPointEx (FINDOBJECT *pFO);

	BOOL ModGIPunkt (long ONr, Punkt &);

	ObjTyp RetrieveObjTyp (GeoDB &rDB, long ON);	// liefert ObjektTyp
	short RetrieveObjStatus (long ON);	// liefert ObjektStatus
	BOOL isObjectVisible (long lONr);	// Objekt ist sichtbar

	VisInfo *RetrieveVisInfo (long lONr);	// liefert VisInfo

#if defined(_USE_LEGACY_CODE)
	long GetRCode (long ONr);	// liefert RCode von KObjekten
	long MergeKObjects (GeoDB &rDB, long O1, long O2, long Ident, long RCode, BOOL iMerge);
						// faßt Objekte zusammen
	long DeleteONFromKObject (GeoDB &rDB, long KONr, long ONr);
	BOOL EnumKObjects (long ONr, BOOL (*fcn)(long, BOOL, void *), void *pData);
#endif // defined(_USE_LEGACY_CODE)

	BOOL CondOptimize (ULARGE_INTEGER liInsertTime) { return true; }
	inline ULARGE_INTEGER TimedInsert (ExtShapeObjectDCreator &rDOC, ObjTyp rgOTyp);	// liefert Zeit des Einbauens/optimiert
	
// TypKonvertierung
	ObjektListe1 &ObjNumTree (void) { return *static_cast<ObjektListe1 *>(this); }
	ObjektListe2 &ObjIdTree (void) { return *static_cast<ObjektListe2 *>(this); }

	inline long GetPointCount (void) { return m_lPCnt; }
	inline long GetLineCount (void) { return m_lLCnt; }
	inline long GetAreaCount (void) { return m_lFCnt; }
	inline long GetTextCount (void) { return m_lTCnt; }
	inline long GetComplexCount (void) { return m_lKCnt; }
		
	long GetObjectCount (ObjTyp rgOTyp);

	long IncrementObjectCount (ObjTyp rgTyp);
	long DecrementObjectCount (ObjTyp rgTyp);

public:
// Navigator-äquivalent
	template<class T>
	class CTableImpl 
	{
	public:
		CTableImpl (T &rCont) : m_rCont(rCont), m_it(rCont.begin()) {}

		void Reset (void) { m_it = m_rCont.begin(); }
		bool First (void) { m_it = m_rCont.begin(); return m_it != m_rCont.end(); }
		bool Valid (void) const { return m_it != m_rCont.end(); }
		bool Next (void) { return ++m_it != m_rCont.end(); }
		bool Delete (void) 
		{ 
		T::iterator it = m_it;		// auf den nächsten Satz zeigen

			++it;
			if (m_rCont.Delete(m_it)) {
				m_it = it; 
				return true;
			}
			return false;
		}

		bool Find (void *pKey) { return m_rCont.Find (reinterpret_cast<T::keytype_t *>(pKey), &m_it); }
		bool FindFirst (void *pKey) { return m_rCont.FindFirst (reinterpret_cast<T::keytype_t *>(pKey), &m_it); }
		bool FindNext (void *pKey) { return m_rCont.FindNext (reinterpret_cast<T::keytype_t *>(pKey), &m_it); }

		bool ReInsert (void *pKey, size_t) { return m_rCont.ReInsert (reinterpret_cast<T::keytype_t *>(pKey), &m_it); }

		ExtShapeObject *lock() { _ASSERTE(Valid()); return (*m_it).second; }

	private:
		T &m_rCont;
		T::iterator m_it;
	};
	typedef CTableImpl<ObjektListe1> CONrTable;
	typedef CTableImpl<ObjektListe2> CIdentTable;

	bool Insert (ExtShapeObject *pESO);
};
typedef ObjektListe::CTableImpl<ObjektListe1> CONrTable;
typedef ObjektListe::CTableImpl<ObjektListe2> CIdentTable;

// Deklaration der zusätzlich notwendigen Klassen 
template<class T>
class ExtShapeObjectLock
{
public:
	ExtShapeObjectLock (ObjektListe::CTableImpl<T> &rNav) : m_rNav(rNav) {}

	ExtShapeObject * operator -> () { return m_rNav.lock(); } 
	operator ExtShapeObject * () { return m_rNav.lock(); } 
	bool operator ! () { return NULL == m_rNav.lock(); }

private:
	ObjektListe::CTableImpl<T> &m_rNav;
};
typedef ExtShapeObjectLock<ObjektListe1> ExtShapeObjectONrLock;
typedef ExtShapeObjectLock<ObjektListe2> ExtShapeObjectIdentLock;

class ExtShapeObjectDCreator
{
public:
	ExtShapeObjectDCreator (ObjektListe &rObjListe) : m_rObjListe(rObjListe), m_pESO(NULL) {}
	~ExtShapeObjectDCreator () { Insert(); }

	template<class X, class Y>
	ExtShapeObject * ItemCreate (X &rObj, Y *)
	{
		if (!Insert())
			return NULL;
		TX_TRY(m_pESO = new Y (rObj));
		return m_pESO;
	}
	bool Insert() 
	{ 
		if (NULL != m_pESO) {
			if (!m_rObjListe.Insert (m_pESO))
				return false;
			m_pESO = NULL;
		}
		return true; 
	}

private:
	ObjektListe &m_rObjListe;
	ExtShapeObject *m_pESO;
};

inline
ULARGE_INTEGER ObjektListe::TimedInsert (ExtShapeObjectDCreator &rDOC, ObjTyp rgOTyp)	// liefert Zeit des Einbauens/optimiert
{ 
ULARGE_INTEGER uli; 

	uli.QuadPart = 0; 
	rDOC.Insert(); 
	return uli; 
}

#endif // !defined(_OBJEKTLISTE_H__56C2B31B_27D9_44B6_A99C_C34EDE21D605__INCLUDED_)
