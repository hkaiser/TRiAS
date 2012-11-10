// HashTablle der bereits ueberstzten GDB-Elemente
// File: HASHTABS.CXX

#include "stdafx.h"

#include "gdb.h"

#include "dgeoobj.hxx"
#include "hashtabs.hxx"

uint LongPairHash (void *pObj) {

	return (*(long *)pObj + (*(long *)pObj >> 16)) & 0xffff;
}

void *GetLongPairKey (void *pObj) {

	return & ((GDBElement *)pObj) -> GDBNr();
}

int LongPairCmp (void *pPrimKey, void *pSecKey) {
long Key1 = *(long *)pPrimKey;
long Key2 = *(long *)pSecKey;

	if (Key1 > Key2) return 1;
	else if (Key1 < Key2) return -1;
	else {
	Key1 = ((long *)pPrimKey)[1];
	Key2 = ((long *)pSecKey)[1];

		if (Key1 > Key2) return 1;
		else if (Key1 < Key2) return -1;
		else return 0;
	}
}

// Memberfunktionen fr GDBElement --------------------------------------------
GDBElement :: GDBElement (long Nr, long Nr2, DGeoObj *pDGO) {

// ElementNummer merken
	_Nr = Nr;
	_Nr2 = Nr2;

// wenn PunktObjekt, dann Koordinaten merken
	if (pDGO) 
		_pDGO = pDGO -> Copy();
	else 
		_pDGO = NULL;
}

GDBElement :: ~GDBElement (void) 
{
	if (_pDGO) { delete _pDGO; _pDGO = NULL; }
}

// Memberfunktionen für HashTable
GDBElementTab :: GDBElementTab (void)
	       : CHashTable (GetLongPairKey, LongPairCmp, 
			    LongPairHash, HASHSIZE)
{
	// nothing else to do
}

GDBElementTab :: ~GDBElementTab (void) {

	EveryDelete ();		// gesamte Tabelle löschen
}

GDBElementTab :: FindOrEnter (long newNr, long newNr2, DGeoObj *pDGO) {
CTable t(*this);
long lKey[2];

	lKey[0] = newNr;
	lKey[1] = newNr2;
	if (t.Find (lKey)) return TRUE;	// bereits geladen

GDBElementCreator Cr(*this);

	Create (Cr, GDBElement) (newNr, newNr2, pDGO);	// ElementNr laden

return FALSE;
}

void GDBElementTab :: UserDelete (void *pObj) {

	((GDBElement *)pObj) -> GDBElement :: ~GDBElement ();
}

DGeoObj *GDBElementTab :: GetDGeoObj (long Nr, long Nr2) {
CTable t(*this);
long lKey[2];

	lKey[0] = Nr;
	lKey[1] = Nr2;
// nachsehen, ob Element bereits existiert
	if (!t.Find (lKey)) return NULL;		// nicht gefunden

	{
	GDBElementLock l(t);

		if (l) return l -> CopyDGeoObj();
	}

return NULL;	// kein DGeoObj oder sonstiger Fehler
}

DGeoObj *GDBElement :: CopyDGeoObj (void) {

	if (_pDGO) return _pDGO -> Copy();

return NULL;
}

