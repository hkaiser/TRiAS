// Memberfunktionen zur Verwaltung der Relationen innerhalb des BNAPARSERS
// File: RELCONT.CXX

#include "bnaimpp.hpp"

#include <containr.hxx>

#include "relcont.hpp"

// RelationsBaum und -Liste werden als dynamische Objekte zur Laufzeit angelegt
CRelTree *g_pRTree = NULL;
CRelList *g_pRList = NULL;
CRelListIterator *g_pRIter = NULL;

// BaumStruktur zur Verwaltung der Zuordnung ONr <--> SatzNr ------------------
CONr_SNr :: CONr_SNr (long ONr, long SNr) 
{
	m_lONr = ONr;
	m_lSNr = SNr;
}

// Vergleichsfunktion für Baumzugriff 
int SNrCmp (void *pObj1, void *pObj2) 
{
long lSNr1 = *(long *)pObj1;
long lSNr2 = *(long *)pObj2;

	if (lSNr1 < lSNr2) return -1;
	if (lSNr1 > lSNr2) return 1;
	return 0;
}

// SchlüsselExtraktionsFunktion für Baumzugriff
void *SNrGet (void *pObj) 
{
	return &( ((CONr_SNr *)pObj) -> SNr() );
}

void CRelTree :: UserDelete (void *pObj)
{
	((CONr_SNr *)pObj) -> ~CONr_SNr ();
}

CRelTree :: CRelTree (void)
	  : CTree (SNrGet, SNrCmp)
{
	// nothing else to do
}

CRelTree :: ~CRelTree (void) 
{
	EveryDelete ();
}

// Funktionen für den Zugriff aus 'C' auf den RelationsBaum -------------------
// Einspeichern eines ONr - SNr Paares in den Baum
int StoreInTree (long lONr, long lSNr) 
{
	if (g_pRTree == NULL) {
	// erstes Element: Baum muß angelegt werden

		g_pRTree = new CRelTree();
		if (g_pRTree == NULL) return false;
	}

CONr_SNrCreator OSCr (*g_pRTree);

	return ContCreate(OSCr, CONr_SNr)(lONr, lSNr) != NULL;
}

// Wiederauffinden einer ObjektNummer an Hand einer gegebenen SatzNummer
LONG RetrieveFromTree (long SNr) 
{
	if (g_pRTree == NULL) return -1L;

CTable t (*g_pRTree);

	if (t.Find (&SNr)) {
	CONr_SNrLock l(t);

		if (l) return l -> ONr();
	}

return -1L;
}

// Baum wieder zurücksetzen
void ResetTree (void) 
{
	DELETE_OBJ(g_pRTree);
}



// Verwaltung der Relationen eines Objektes -----------------------------------
CRelData :: CRelData (long lONr, long lRCode, short iRTyp) 
{
	m_lONr = lONr;
	m_lRCode = lRCode;
	m_iRTyp = iRTyp;
}

CRelList :: CRelList (void)
	  : CListContainer ()
{
	// nothing else to do
}

CRelList :: ~CRelList (void) 
{
	EveryDelete ();
}

void CRelList :: UserDelete (void *pObj) 
{
	((CRelData *)pObj) -> ~CRelData ();
}

// IteratorKlasse für den sequentiellen Zugriff auf die einzelnen ListenElemente
CRelListIterator :: CRelListIterator (CRelList &RT)
		  : CRing (RT)
{
	First();	// auf erstes Element positionieren
}

// liefert aktuell selektiertes Listenelement und stellt eins weiter
BOOL CRelListIterator :: RetrieveNext (long &rlONr, long &rlRCode, short &riRTyp) 
{
BOOL iRetVal = false;

	if (Valid()) {		
	CRelDataLock l(*this);

		if (!l) return false;

	// Daten liefern
		rlONr = l -> ONr();
		rlRCode = l -> RCode();
		riRTyp = l -> RTyp();

		iRetVal = true;
	}

// Iterator weitersetzen
	if (iRetVal) Next();

return iRetVal;
}


// Zugriffsfunktionen aus 'C' heraus auf die ListenDaten
BOOL StoreInList (long lONr, long lRCode, long lRTyp) 
{
	if (g_pRList == NULL) {
	// erstes Element: Liste anlegen
		g_pRList = new CRelList();
		if (g_pRList == NULL) return false;	// kein Speicher mehr
		
		g_pRIter = new CRelListIterator (*g_pRList);
		if (g_pRIter == NULL) {
			DELETE_OBJ(g_pRList);
			return false;
		}
	}

CRelDataCreator RDCr (*g_pRList);

	return ContCreate (RDCr, CRelData)(lONr, lRCode, short(lRTyp)) != NULL;
}

// liefert die Anzahl der Relationen, die dieses Objekt eingehen soll
long RelCount (void) 
{
	if (g_pRList == NULL) return 0;
	return g_pRList -> Count();
}

// setzt Liste auf erstes Element 
BOOL ResetList (void) 
{
	if (g_pRList && g_pRIter)
		return g_pRIter -> Reset();

return false;
}

// löschen der Liste, freigeben der EInzelEinträge
void ClearList (void)
{
	DELETE_OBJ(g_pRIter);
	DELETE_OBJ(g_pRList);
}

// liefert den nächsten Eintrag der Liste
BOOL RetrieveNextFromList (long *plONr, long *plRCode, short *piRTyp) 
{
	if (g_pRList && g_pRIter)
		return g_pRIter -> RetrieveNext (*plONr, *plRCode, *piRTyp);

return false;
}

