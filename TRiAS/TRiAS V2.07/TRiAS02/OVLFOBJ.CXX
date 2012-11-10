// Generieren eines FlaechenObjektes durch Overlay
// File: OVLFOBJ.C

#include "trias02p.hxx"

// Generiert ein neues Flächenobjekt ------------------------------------------
long FUNCTYPE EXPORT02 OvlAreaObject (HPROJECT hPr, long *pOBL, long Ident, long TONr) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;                 // FehlerVariable
long newON = -1L;
long lVomaNr = 0;

// wenn identische Objekte überlagert werden sollen, dann raus
	if (TONr == *pOBL) return S_OKAY;

// BezugsObjektsatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = TONr;
	__Read (dbaOBL, OBLSatz);
	if (OBLSatz.zovoma == 0) 	// ObjektTyp stimmt nicht
		return (long)db_error (S_BADOBJTYP, RC_OvlLinie);

	lVomaNr = OBLSatz.zovoma;		// BezugsKantenFolge

// Objektsatz generieren
	DEX_SetDirtyGeoDB (true);

	if (*pOBL <= 0) {
	// Objekt existiert noch nicht: generieren
		OBLSatz.zovol = 0;

		if (VERSION0500000E <= GetDBVersion (hPr))	// evtl. GUID generieren
			CoCreateGuid (&OBLSatz.guid);

		__New (dbaOBL, OBLSatz);
		newON = dbaOBL.rec_no;

	// Identifikator bei Bedarf in IDL eintragen
		DBASSERT (PutIdent (hPr, newON, Ident, TPFlaeche, &OBLSatz.zoid));
		__Write (dbaOBL, OBLSatz);
	} else {
	// bestehendes Objekt lesen
		newON = dbaOBL.rec_no = *pOBL;
		*pOBL = 0;		// sicherheitshalber
		__Read (dbaOBL, OBLSatz);
		if (OBLSatz.zovoma == 0) 	// ObjektTyp stimmt nicht
			return (long)db_error (S_BADOBJTYP, RC_OvlFlaeche);

	// IdentifikatorSatz richten
		DBASSERT(VerifyIdent(hPr, newON, OBLSatz.zoid, TPFlaeche));

	// alten Geometrieverweis entfernen
		DBASSERT (delgif (hPr, newON));
		OBLSatz.zovoma = 0;		// OBLSatz mitführen
	}

// neuen KoordinatenSatz generieren
	DBASSERT (OvlArea (hPr, newON, &OBLSatz.zovoma, lVomaNr));
	__Write (dbaOBL, OBLSatz);	// ObjektSatz nochmal wegschreiben

// ObjektNummer liefern
	*pOBL = newON;

return S_OKAY;
}


long FUNCTYPE OvlArea (HPROJECT hPr, long ONr, long *pNewChain, long lVomaNr)
{
struct mal MALSatz;
struct kfm KFMSatz;
DB_ADDR dbaMAL(hPr);
DB_ADDR dbaKFM(hPr);
long lNext = 0;
long lNewMasche;
ErrCode RC;

// neuen MALSatz generieren
	dbaMAL.file_no = MAL;
	dbaMAL.rec_no = lVomaNr;
	__Read (dbaMAL, MALSatz);

	lNext = MALSatz.zmkfm;		// erster zu kopierender Satz

	MALSatz.zmkfm = 0;		// noch keine Geometrie
	MALSatz.zmvgo = ONr;		// Rückverweis in ObjektListe
	__New (dbaMAL, MALSatz);		// neuen Satz generieren
	*pNewChain = lNewMasche = dbaMAL.rec_no;

// VerbindungsKette zu KantenListe kopieren
	dbaKFM.file_no = KFM;
	while (lNext) {
	// Element der BezugsKette lesen
		dbaKFM.rec_no = lNext;
		__Read (dbaKFM, KFMSatz);

	// neues Element in Kette bilden, in Kante eintragen
		DBASSERT (PutChainEnd (hPr, KFM, &MALSatz.zmkfm, KFMSatz.zkfmk));
		__Write (dbaMAL, MALSatz);

		DBASSERT (OvlMasche (hPr, lNewMasche, KFMSatz.zkfmk));

	// nächster KFMSatz
		lNext = KFMSatz.znkfm;		// nächster Satz
	}

return S_OKAY;
}


// Eine Kante mit Objekt (Masche) überlagern ----------------------------------
long FUNCTYPE OvlMasche (HPROJECT hPr, long lMasche, long lKalNr)
{
struct kal KALSatz;
DB_ADDR dbaKAL(hPr);
ErrCode RC;

// KantenSatz einlesen
	dbaKAL.file_no = KAL;
	dbaKAL.rec_no = labs (lKalNr);
	__Read (dbaKAL, KALSatz);

// diese Kante mit gegebener Masche überlagern (Objekt in die Folge der 
// rechten/linken Maschen eintragen)
	if (lKalNr > 0) {
		DBASSERT (PutLink (hPr, VZO, &KALSatz.zlm, lMasche));
	} else {
		DBASSERT (PutLink (hPr, VZO, &KALSatz.zrm, lMasche));
	}
	__Write (dbaKAL, KALSatz);

return S_OKAY;
}

