// Methoden für ObjektLise -- die Verwaltung der Objekte im Speicher
// File: OLISTEM.CXX

#include "triaspre.hxx"

#include "relobj.hxx"
#include "schrift.hxx"

// Zusammenfassen zweier Objekte zu einem Komplexobjekt -----------------------
// Liefert die ObjektNummer des neuen Objektes
#if defined(WIN32)
#pragma warning (disable: 4273)
#endif

long ObjektListe :: MergeKObjects (long ONr, long newONr, 
				   long Ident, long RCode, Bool iMerge)
{
CTable tabON (ObjNumTree());

// erstes Objekt suchen
	if (tabON.Find (&ONr)) {
	ExtShapeObjectLock l1(tabON);

		if (!l1) return -1L;	// Fehler

	ObjTyp OTyp = l1 -> isTyp();

		if (OTyp == OT_UNKNOWN) return -1L;

		DEX_SetDirtyGeoDB(true);
		if (OTyp != OT_KO || 
		    (OTyp == OT_KO && !iMerge)) {
		// Objekt 1 ist ElementarObjekt oder KObjekt und neues 
		// KomplexObjekt bilden
		KomplexObjekt *pKO = new KomplexObjekt (DB(), ONr, Ident, RCode);

			if (pKO == NULL) {
				db_error (EC_NOMEMORY, RC_MergeKObjects);
				return -1L;
			}
			if (newONr != -1L && pKO -> AddObject (newONr) != EC_OKAY)
				return -1L;

		// neues RelationsObjekt bilden
		ExtShapeObjectDCreator DOC (*this);

			if (ContCreate (DOC, RelationsObjekt)(*pKO) == NULL) {
				db_error (EC_NOMEMORY, RC_MergeKObjects);
				return -1L;
			}
			return pKO -> ObjNr();	// (neue) ObjektNummer
		} else if (OTyp == OT_KO && iMerge) {
		// Objekt 1 ist bereits KomplexObjekt und Objekte zusammenfassen
		KomplexObjekt *pKO = (KomplexObjekt *)(l1 -> operator GeoObjekt *());

		// RelationsCode vergleichen
			if (pKO == NULL || pKO -> RCode() != RCode) 
				return -1L;
			if (newONr == -1L || pKO -> AddObject (newONr) == EC_OKAY)
				return pKO -> ObjNr();	
					// alte ObjektNummer liefern
		}
	}

return -1L;	// irgendwas ist schiefgelaufen
}

// Herauslösen eines Objektes aus einem Komplexobjekt -------------------------
long ObjektListe :: DeleteONFromKObject (long KONr, long ONr)
{
CTable tabON (ObjNumTree());
long lAssocObj = AssociatedTextObjekt (DB().DBDesc(), KONr);

// KomplexObjekt suchen
	if (tabON.Find (&KONr)) {
	ExtShapeObjectLock l1(tabON);

		if (!l1) return -1L;	// Fehler

	ObjTyp OTyp = l1 -> isTyp();

		if (OTyp != OT_KO || OTyp == OT_UNKNOWN) return -1L;

	// Objekt aus KO herauslöschen
	KomplexObjekt *pKO = (KomplexObjekt *)(l1 -> operator GeoObjekt *());

		if (pKO == NULL) return -1L;

	ErrCode RC;

		DEX_SetDirtyGeoDB(true);
		if ((RC = pKO -> DeleteObject (ONr)) == EC_OKAY) {
		// ok, war nicht letztes Teilobjekt
			return pKO -> ObjNr();	// alte ObjektNummer liefern
		} else if (RC == WC_RETURN) {
		// das war das letzte Objekt des KO's --> herauslöschen

			DeleteObjekt (KONr);	// aus Baum & DB löschen
			if ((ErrCode)del (DB().DBDesc(), KONr) != EC_OKAY) 
				return -1L;

		// evtl. zugehöriges Textobjekt mit rausnehmen
			if (lAssocObj != -1L && !DeleteObjekt (lAssocObj)) 
				return -1L;

			return 0L;	// kein KO mehr da
		}
	}

return -1L;	// irgendwas ist schiefgelaufen
}


// Korrigieren der Position eines Objektes ------------------------------------
Bool ObjektListe :: CorrectPosition (long ONr, Point &Pt)
{
CTable tabON (ObjNumTree());

	if (tabON.Find (&ONr)) {
	ExtShapeObjectLock l(tabON);

		if (!l) return FALSE;	// Fehler
		if (l -> isTyp() != OT_TEXT && l -> isTyp() != OT_LABEL) 
			return FALSE;	// Fehler

	// Objekt Bescheid sagen, das es seine Koordinaten hergeben soll
		((SchriftObjekt *)(ExtShapeObject *)l) -> CorrectPosition (Pt);
	}

return TRUE;
}


// Finden aller Objekte unter einem BildshirmPunkt ----------------------------
Bool ObjektListe :: FindObjectsFromPointEx (FINDOBJECT *pFO)
{
	return FindObjectsFromPoint (*(Point *)&pFO -> Pt, pFO -> iFOMode, 
				     pFO -> eFcn, pFO -> pData); 
}


