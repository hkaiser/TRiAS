// Methoden für ObjektLise -- die Verwaltung der Objekte im Speicher
// File: OLISTE.CXX

#include "trias02p.hxx"

#if !defined(WIN32)
#include <toolhelp.h>		// TIMERINFO
#endif // !WIN32

#include <xtensnd.h>

#include <drawobj.hxx>
#include <dcreator.hxx>
#include <deltree.hxx>
#if defined(_FORCE_LEGACY_CODE)
#include <ident.hxx>
#endif // defined(_FORCE_LEGACY_CODE)

#define NOTRANSFORM
#include <transfrm.hxx>
#include <objliste.hxx>

#include "objmtree.hxx"
#include "objmtree.inl"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

ObjTyp BitsToObjTyp (DWORD dwBits);

#if !defined(_USE_MAP_FOR_OBJEKTLISTE)
#if !defined(LONGCOMP)
#define LONGCOMP
// Funktionen für ObjektListe : Tree (Zugriffs- und Vergleichsfunktionen) -----
inline int LongCmp (void *Key1, void *Key2) 
{
long Par1 = *(long *)Key1, Par2 = *(long *)Key2;
	if (Par1 > Par2)        return 1;
	else if (Par1 < Par2)   return -1;
	else                    return 0;
}
#endif // LONGCOMP
#endif // !defined(_USE_MAP_FOR_OBJEKTLISTE)

// Platzhalter für Destruktor -------------------------------------------------
EXPORT02 ExtShapeObject::~ExtShapeObject (void) 
{
	DELETE_OBJ (m_pFT);
}


CFeature * EXPORT02 ExtShapeObject::FFindFeature (long lMCode)
{
	if (m_pFT == NULL) return NULL;		// kein Cache vorhanden

return m_pFT -> FFindItem (lMCode);		// Baum befragen
}

BOOL EXPORT02 ExtShapeObject::FAddFeature (long lMCode, char *pMWert)
{
// Wenn Merkmal nicht gegeben ist, dann wieder raus
	if (pMWert == NULL) return false;
	
// wenn kein Baum da ist, dann diesen erzeugen
	if (m_pFT == NULL) {
		m_pFT = new CFeatureTree;
		if (m_pFT == NULL) return false;	// nicht schön, aber nicht zu ändern
	} else 
		m_pFT -> FDeleteItem (lMCode);		// evtl. alten Eintrag löschen
	
	return m_pFT -> FAddItem (lMCode, pMWert);	// Merkmal im Baum einhängen
}


BOOL EXPORT02 ExtShapeObject::FDeleteFeature (long lMCode)
{
// wenn kein Baum da ist, dann diesen erzeugen
	if (m_pFT == NULL) 
		return true;
	return m_pFT -> FDeleteItem (lMCode);		// alten Eintrag löschen
}


// Elemente der Objektliste ---------------------------------------------------
// Platzhalter für überladene Funktionen
VisInfo *ExtShapeObject::SetAttributes (DatenBasisObjekt *pDBO, CIdentifikator *, CONrTable &, VisType, short) { return NULL; }
void ExtShapeObject::ResetAttributes (void) {}
void ExtShapeObject::TypeDependendDraw (CIdentifikator *, CONrTable &, Dimension) {}

Rectangle EXPORT02 ExtShapeObject::BoundingBox (void) { return ShapeObject::BoundingBox(); }

INT_PTR __auxLong__ = 0;	// Hilfsvariable für die folgenden Funktionen
INT_PTR & EXPORT02 ExtShapeObject::ObjNr (void) { return __auxLong__; }
INT_PTR & EXPORT02 ExtShapeObject::Id (void) { return __auxLong__; }

// Typkonvertierung von ExtShapeObject --> GeoObjekt
// Achtung: liefert nur dann gültigen Wert, wenn ein Geometrie -
//          Elementarobjekt vorliegt.
ExtShapeObject::operator GeoObjekt * () { return NULL; }
GeoObjekt *ExtShapeObject::operator -> () { return NULL; }

// ObjektListe ----------------------------------------------------------------
#if !defined(_USE_MAP_FOR_OBJEKTLISTE)
// Funktion für ObjektListe : Tree (Zugriff auf Schlüsselinfo ObjNum) --------
void *GetObjNum (void *pItem) {	return & ((ExtShapeObject *)pItem) -> ObjNr(); }

// Funktion für ObjektListe : Tree (Zugriff auf Schlüsselinfo Ident) ---------
void *GetObjId (void *pItem) 
{ 
ExtShapeObject *pESO = (ExtShapeObject *)pItem;

	return & pESO -> Id();
// return & ((ExtShapeObject *)pItem) -> Id(); 
}

// ObjektListe1 -- TeilContainer für die ObjektNummern ------------------------
ObjektListe1::ObjektListe1 (void) 
	: COptTree (GetObjNum, LongCmp, CONTFLAG(CFDefault|CFUniqueKey))
{
	// nothing to do
}

ObjektListe1::~ObjektListe1 (void) 
{
	EveryDelete ();
}

void EXPORT02 ObjektListe1::UserDelete (void * pObj) 
{
	((ExtShapeObject *)pObj) -> /*ExtShapeObject ::*/ ~ExtShapeObject ();	// virtuellen Destruktor rufen
}
#else
bool ObjektListe1::Insert (ExtShapeObject *pESO, iterator *pit)
{
pair<iterator, bool> p = insert (value_type (pESO -> ObjNr(), pESO));

	if (NULL != pit)
		*pit = p.first;
	return p.second;
}

bool ObjektListe1::Delete (ExtShapeObject *pESO)
{
iterator it = find (pESO -> ObjNr());

	if (it != end())
		return Delete (it, false);
	return true;
}

bool ObjektListe1::Delete (iterator it, bool fDelete)
{
	if (it != end()) {
		if (fDelete)
			delete (*it).second;
		erase (it);
		return true;
	}
	return false;
}

bool ObjektListe1::EveryDelete()
{ 
	for (iterator it = begin(); it != end(); ++it)	// alles freigeben
		delete (*it).second;

	clear();				// und aus map löschen
	return true;
}

bool ObjektListe1::ReInsert (INT_PTR *pKey, iterator *pit)
{
	if (*pit == end())
		return false;

// mit altem Schlüssel aus Tree löschen
ExtShapeObject *pESO = (**pit).second;

	_ASSERTE(NULL != pESO);
	if (!Delete (*pit, false)) 
		return false;
	pESO -> ObjNr() = *pKey;		// Objektnummer austauschen
	return Insert (pESO, pit); 
}
#endif // !defined(_USE_MAP_FOR_OBJEKTLISTE)

// ObjektListe2 -- TeilContainer für die Identifikatoren
#if !defined(_USE_MAP_FOR_OBJEKTLISTE)
ObjektListe2::ObjektListe2 (void) 
	: COptTree (GetObjId, ULongCmp, CFNoSpecial)
{
	// nothing to do
}

ObjektListe2::~ObjektListe2 (void) 
{
	EveryDelete();
}

void EXPORT02 ObjektListe2::UserDelete (void * pObj) 
{
	((ExtShapeObject *)pObj) -> /*ExtShapeObject ::*/ ~ExtShapeObject ();	// virtuellen Destruktor rufen
}
#else
bool ObjektListe2::Insert (ExtShapeObject *pESO, iterator *pit) 
{
iterator it = insert (value_type (pESO -> Id(), pESO));

	if (NULL != pit)
		*pit = it;
	return it != end();
}

bool ObjektListe2::Delete (iterator it)
{
	if (it != end()) {
		erase (it);
		return true;
	}
	return false;
}

bool ObjektListe2::ReInsert (INT_PTR *pKey, iterator *pit) 
{
	if (*pit == end())
		return false;

// mit altem Schlüssel aus Tree löschen
ExtShapeObject *pESO = (**pit).second;

	_ASSERTE(NULL != pESO);
	if (!Delete (*pit)) 
		return false;

	pESO -> Id() = *pKey;		// neuen Ident setzen
	return Insert (pESO, pit);	// neu im Baum einfügen
}
#endif // !defined(_USE_MAP_FOR_OBJEKTLISTE)

// GesamtContainer -- ObjektListe
ObjektListe::ObjektListe (void) 
{
	m_lPCnt = 0;	// Zähler der geladenen Objekttypen
	m_lLCnt = 0;
	m_lFCnt = 0;
	m_lTCnt = 0;
	m_lKCnt = 0;
}

ObjektListe::~ObjektListe (void)
{
	// nothing to do
}

#if defined(_USE_MAP_FOR_OBJEKTLISTE)
bool ObjektListe::Insert (ExtShapeObject *pESO)
{
	if (!ObjNumTree().Insert (pESO))
		return false;

	if (!ObjIdTree().Insert (pESO)) {
		ObjNumTree().Delete (pESO);
		return false;
	}
	return true;
}
#endif // defined(_USE_MAP_FOR_OBJEKTLISTE)

// Löschen aller Elemente im DoppelContainer
BOOL ObjektListe::EveryDelete (void) 
{
	return ObjektListe2::EveryDelete() && ObjektListe1::EveryDelete();
}

// ein vorgegebenes Objekt herauslöschen --------------------------------------
BOOL ObjektListe::DeleteObjekt (long ON) 
{
CIdentTable tabId (ObjIdTree());
CONrTable tabObj (ObjNumTree());
long Ident = -1L;		// Identifikator dieses Objektes

	if (tabObj.Find (&ON)) {
	// Objekt ist wirklich geladen
	ExtShapeObjectONrLock l(tabObj);

		if (l) Ident = l -> Id();	// Identifikator holen
		else return false;
	} else
		return false;

// zugehörigen Eintrag im Identifikatorbaum finden
ObjTyp rgOTyp = OT_UNKNOWN;

	for (tabId.FindFirst(&Ident); tabId.Valid(); tabId.FindNext(&Ident)) {
	ExtShapeObjectIdentLock l(tabId);

		if (l) {
			if (l -> ObjNr() == ON) {
				rgOTyp = l -> isTyp();
				break;
			}
		} else {
			return false;
		}
	}

// Wenn beide Einträge gefunden sind, dann diese herauslöschen
	if (tabId.Valid()) {
		tabObj.Delete();
		tabId.Delete();

		DecrementObjectCount (rgOTyp);
	} else
		return false;

	return true;
}

// Modifikation des Identifikators eines Objektes -----------------------------
BOOL ObjektListe::ModIdent (long lONr, long Ident, long newId) 
{
CIdentTable tabId (ObjIdTree());	// SubBaum der Identifikatoren

// zugehörigen Eintrag im Identifikatorbaum finden
	for (tabId.FindFirst(&Ident); tabId.Valid(); tabId.FindNext(&Ident)) {
	ExtShapeObjectIdentLock l(tabId);

		if (!l) continue;
		if (l -> ObjNr() == lONr) 
			break;
	}

// Wenn Eintrag gefunden ist, dann diesen im Baum unhängen
	if (tabId.Valid())
		return tabId.ReInsert (&newId, sizeof(newId));
	return false;
}

// Finden eines SchriftObjektes unter dem MausClick ---------------------------
BOOL ObjektListe::FindSchriftObjekt (Point Pt, long &rONr, Rectangle &R) 
{
CONrTable tabON (ObjNumTree());	// SubBaum über ObjektNummern

	for (tabON.First(); tabON.Valid(); tabON.Next()) {
	ExtShapeObjectONrLock l(tabON);

		if (!l) continue;
		if (l -> isTyp() == OT_TEXT || l -> isTyp() == OT_LABEL) {
		// SchriftObjekt

			if (l -> HitTest (Pt) && l -> isVisible()) {
			// SchriftObjekt gefunden
				rONr = l -> ObjNr();
				R = l -> BoundingBox();
				return true;	// erstes Schriftobjekt
			}
		}
	}
	return false;	// nichts gefunden
}


// Finden aller Objekte entsprechend vorgegegebenen Typ unterhalb eines Punktes
extern "C"
inline BOOL FOFcn (BOOL (*eFcn)(long, RECT, void *), long lONr, Rectangle R, void *pData)
{
	return ((FINDOBJECTCALLBACK)eFcn)(lONr, *(RECT *)&R, pData);
}

BOOL ObjektListe::FindObjectsFromPoint (
	Point Pt, short iMode, BOOL (*eFcn)(long, RECT, void *), void *pData)
{
CONrTable tabON (ObjNumTree());	// SubBaum über ObjektNummern

	for (tabON.First(); tabON.Valid(); tabON.Next()) {
	ExtShapeObjectONrLock l(tabON);

		if (!l) continue;
		switch (l -> isTyp()) {
		case OT_PUNKT:		
			if (!(iMode & FOPunkt)) continue;
			break;

		case OT_KANTE:		
			if (!(iMode & FOKante)) continue;
			break;

		case OT_FLAECHE:	
			if (!(iMode & FOFlaeche)) continue;
			break;

		case OT_LABEL:
		case OT_TEXT:		
			if (!(iMode & FOText)) continue;
			break;

		default:
			continue;	
		}
		if (l -> HitTest (Pt)) {
		// Gesuchtes Objekt gefunden
			if (FOFcn (eFcn, l -> ObjNr(), l -> BoundingBox(), pData) == false)
				return false;
		}
	}

return true;	// fertig iteriert
}


// Verändern der Geometrie eines GeoObjektes ----------------------------------
BOOL ObjektListe::ModGIText (long ONr, Punkt &Pt) 
{
CONrTable tabON (ObjNumTree());

	if (tabON.Find (&ONr)) {
	ExtShapeObjectONrLock l(tabON);

		if (!l) return false;	// Fehler
		if (l -> isTyp() != OT_TEXT && l -> isTyp() != OT_LABEL) 
			return false;	// Fehler

	BasicGeoText *pGT;
	TextObjTyp ToTyp = ((BasicGeoText *)(l -> operator GeoObjekt *())) -> isText();

		if (ToTyp == TOT_TEXT)
			pGT = new GeoText (*(GeoText *)(l -> operator GeoObjekt *()));
#if defined(_USE_LEGACY_CODE)
		else if (TOT_TEXTIND == ToTyp)
			pGT = new GeoTextInd (*(GeoTextInd *)(l -> operator GeoObjekt *()));
#endif // defined(_USE_LEGACY_CODE)
		else {
			TX_ASSERT(TOT_TEXTINDOBJPROP == ToTyp);
			pGT = new GeoTextIndOP (*(GeoTextIndOP *)(l -> operator GeoObjekt *()));
		}

		if (pGT != NULL) {
		// neue Geometrie einhängen
			pGT -> SetX(Pt.GetX());
			pGT -> SetY(Pt.GetY());
			if ((pGT = (BasicGeoText *)(l -> NewGI (pGT))) != NULL)
				DELETE_OBJ (pGT);	// alten Text löschen
		} else
			return false;
	} 
	return true;
}

// Modifikation der Geometrie eines Punktes -----------------------------------
BOOL ObjektListe::ModGIPunkt (long ONr, Punkt &Pt) 
{
CONrTable tabON (ObjNumTree());

	if (tabON.Find (&ONr)) {
	ExtShapeObjectONrLock l(tabON);

		if (!l) return false;	// Fehler
		if (l -> isTyp() != OT_PUNKT) return false;	// Fehler

	GeoPunkt *pGP = new GeoPunkt (*(GeoPunkt *)(l -> operator GeoObjekt *()));

		if (pGP != NULL) {
		// neue Geometrie einhängen
			pGP -> SetX(Pt.GetX());
			pGP -> SetY(Pt.GetY());
			if ((pGP = (GeoPunkt *)(l -> NewGI (pGP))) != NULL)
				DELETE_OBJ (pGP);	// alten Text löschen
		} else
			return false;
	} 
	
return true;
}

ObjTyp ObjektListe::RetrieveObjTyp (GeoDB &rDB, long ONr) 
{
	TX_ASSERT(0 < ONr);

CONrTable tabON (ObjNumTree());

	if (tabON.Find (&ONr)) {
	ExtShapeObjectONrLock l(tabON);

		TX_ASSERT(NULL != (ExtShapeObject *)l);

		return l -> isTyp(); 
	} else {
	// Objekt nicht geladen, in Datenbasis nachsehen
	int iOType = OT_UNKNOWN;

		if (SUCCEEDED(rDB.GetObjectType (ONr, &iOType)))
			return BitsToObjTyp(iOType);

	// ansonsten hier durchfallen
	}
	return OT_UNKNOWN;
}

BOOL ObjektListe::isObjectVisible (long lONr) 
{
	TX_ASSERT(lONr > 0);

CONrTable tabON (ObjNumTree());

	if (tabON.Find (&lONr)) {
	ExtShapeObjectONrLock l(tabON);

		TX_ASSERT(NULL != (ExtShapeObject *)l);
		return l -> isVisible(); 
	} 

// Objekt nicht geladen, also nicht sichtbar
	return false;
}

short ObjektListe::RetrieveObjStatus (long lONr)
{
	TX_ASSERT(lONr > 0);

CONrTable tabON (ObjNumTree());

	if (tabON.Find (&lONr)) {
	ExtShapeObjectONrLock l(tabON);

		TX_ASSERT(NULL != (ExtShapeObject *)l);
		return l -> Status();
	}

	return OS_Normal;	// nicht geladen, also normal
}

#if defined(_USE_LEGACY_CODE)
// diese Funktion liefert den interenen RelationsCode eines KomplexObjektes ---
long ObjektListe::GetRCode (long lONr) 
{
	TX_ASSERT(0 < lONr);

CONrTable tabON (ObjNumTree());

	if (tabON.Find (&lONr)) {
	ExtShapeObjectONrLock l(tabON);

		TX_ASSERT(NULL != (ExtShapeObject *)l);

		if (l -> isTyp() != OT_KO) 
			return -1L;

	KomplexObjekt *pKO = (KomplexObjekt *)(l -> operator GeoObjekt *());

		TX_ASSERT(NULL != pKO);
		return pKO -> RCode(); 	// RelationsCode liefern
	}

	return -1L;
}


BOOL ObjektListe::EnumKObjects (long ONr, BOOL (*fcn)(long, BOOL, void *), void *pData)
{
	TX_ASSERT(0 < ONr);
	TX_ASSERT(NULL != fcn);

CONrTable tabON (ObjNumTree());

	if (tabON.Find (&ONr)) {
	ExtShapeObjectONrLock l(tabON);

		TX_ASSERT(NULL != (ExtShapeObject *)l);

		if (l -> isTyp() == OT_KO) {
		KomplexObjekt *pKO = (KomplexObjekt *)(l -> operator GeoObjekt *());

			TX_ASSERT(NULL != pKO);
			return pKO -> EnumKObjects (fcn, pData);
		}
	}

return false;
}
#endif // defined(_USE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// Optimieren und Einfügen 
long ObjektListe::IncrementObjectCount (ObjTyp rgOTyp)
{
	switch (rgOTyp) {
	case OT_PUNKT:	return ++m_lPCnt;
	case OT_KANTE:	return ++m_lLCnt;
	case OT_FLAECHE:
	case OT_KREIS:	return ++m_lFCnt;
	case OT_LABEL:
	case OT_TEXT:	return ++m_lTCnt;
	case OT_KO:		return ++m_lKCnt;
	default:
		TX_ASSERT(false);
		return false;
	}
	return true;
}

long ObjektListe::DecrementObjectCount (ObjTyp rgOTyp)
{
	switch (rgOTyp) {
	case OT_PUNKT:	m_lPCnt--; /*TX_ASSERT(m_lPCnt >= 0); */return m_lPCnt;
	case OT_KANTE:	m_lLCnt--; /*TX_ASSERT(m_lLCnt >= 0); */return m_lLCnt;
	case OT_FLAECHE:
	case OT_KREIS:	m_lFCnt--; /*TX_ASSERT(m_lFCnt >= 0); */return m_lFCnt;
	case OT_LABEL:
	case OT_TEXT:	m_lTCnt--; /*TX_ASSERT(m_lTCnt >= 0); */return m_lTCnt;
	case OT_KO:		m_lKCnt--; /*TX_ASSERT(m_lKCnt >= 0); */return m_lKCnt;
	default:
		TX_ASSERT(false);
		return 0L;
	}
}

long ObjektListe::GetObjectCount (ObjTyp rgOTyp)
{
	switch (rgOTyp) {
	case OT_PUNKT:	return m_lPCnt;
	case OT_KANTE:	return m_lLCnt;
	case OT_FLAECHE:
	case OT_KREIS:	return m_lFCnt;
	case OT_LABEL:
	case OT_TEXT:	return m_lTCnt;
	case OT_KO:		return m_lKCnt;
	default:
		TX_ASSERT(false);
		break;
	}
	return 0L;
}

#if !defined(_USE_MAP_FOR_OBJEKTLISTE)
ULARGE_INTEGER ObjektListe::TimedInsert (
	ExtShapeObjectDCreator &rDOC, ObjTyp rgOTyp)
{
	rDOC.Insert();
	IncrementObjectCount (rgOTyp);

LONGLONG llT = ObjektListe1::GetLastInsertTime() + ObjektListe2::GetLastInsertTime();
ULARGE_INTEGER uli;

	uli.QuadPart = llT;
	return uli;
}
#endif // !defined(_USE_MAP_FOR_OBJEKTLISTE)

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für RechercheObjFeld 
ObjFeld::ObjFeld (void)
	 : CListContainer () 
{
	// nothing to do 
}

ObjFeld::~ObjFeld (void) 
{
	EveryDelete ();		// alle Elemente des Baumes löschen
}

// ein Element des Baumes löschen 
void EXPORT02 ObjFeld::UserDelete (void *pObj) 
{
	TX_ASSERT_POINTER(pObj, ObjNummer);

	((ObjNummer *)pObj) -> ~ObjNummer ();
}

// diese 'virtual' - Funktion ist von der Wirkung her für die Klasse der
// Elemente, die gerade im ObjFeld gespeichert sind, ein 'virtual constructor'
ObjNummer *ObjFeld::NewObj (ObjNummerCreator &ONC, long ON) 
{
	TX_ASSERT(ON > 0);

	return ContCreate (ONC, ObjNummer)(ON);
}

ObjFeldTyp ObjFeld::isA (void) { return OFTObjFeld; }

// Berechnen des Gemeinsamen Containers der gegebenen Objekte -----------------
ObjContainer ObjFeld::CalcCont (void) 
{
CRing r(*this);
ObjContainer OC (MAXKOORD, 0, MAXKOORD, 0);
ObjContainer locOC (0, 0, 0, 0);

	for (r.First(); r.Valid(); r.Next()) {
	ObjNummerLock l(r);

		TX_ASSERT(NULL != (ObjNummer *)l);
		TX_ASSERT(l -> _ON > 0);

	// ObjContainer dieses Objektes holen
		if (DEX_GetObjContainer (l -> _ON, locOC)) 
			OC += locOC;
		else
			TX_ASSERT(false);
	}
	return OC;
}
		
extern "C" {

inline BOOL peFcn (BOOL (*eFcn)(long, BOOL, void *), 
		   long lONr, BOOL iF, void *pData)
{
	return ((ENUMLONGKEYCALLBACK)eFcn)(lONr, iF, pData);
}

}


BOOL ObjFeld::Enumerate (BOOL (*eFcn)(long, BOOL, void *), void *pData)
{
	TX_ASSERT(eFcn != NULL);

CRing r(*this);

	for (r.First(); r.Valid(); ) {
	ObjNummerLock l(r);
	BOOL iNotLast = r.Next();

		TX_ASSERT(NULL != (ObjNummer *)l);
		TX_ASSERT(l -> _ON > 0);

		if (peFcn (eFcn, l -> _ON, iNotLast, pData) == false)
			return false;
	}
	return true;
}

// Ein bestimmtes Objekt aus dem Container herauslöschen ----------------------
BOOL EXPORT02 ObjFeld::DeleteObj (long lONr)
{
CRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	BOOL fToDelete = false;

		{
		ObjNummerLock l(r);

			TX_ASSERT(NULL != (ObjNummer *)l);

			if (l -> _ON == lONr)
				fToDelete = true;
		}
		if (fToDelete) {	// Objekt wiedergefunden
			r.Delete();
			return true;
		}
	}
	return false;	
}

///////////////////////////////////////////////////////////////////////////////
// Lediglich feststellen, ob ein gegebenes Objekt hier enthalten ist
BOOL ObjFeld::ContainsObject (long lONr)
{
CRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	ObjNummerLock l(r);

		TX_ASSERT(NULL != (ObjNummer *)l);
		if (l -> _ON == lONr)
			return true;
	}
	return false;
}
