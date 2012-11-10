// Generieren eines LinienObjektes durch Overlay
// File: OVLLOBJ.C

#include "trias02p.hxx"

// Generiert ein neues Punktobjekt --------------------------------------------
long FUNCTYPE OvlLineObject (HPROJECT hPr, long *pOBL, long Ident, long TONr) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;                 // FehlerVariable
long newON = -1L;
long lVolNr = 0;

// wenn identische Objekte überlagert werden sollen, dann raus
	if (TONr == *pOBL) return S_OKAY;

// BezugsObjektsatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = TONr;
	__Read (dbaOBL, OBLSatz);
	if (OBLSatz.zovol == 0) 	// ObjektTyp stimmt nicht
		return (long)db_error (S_BADOBJTYP, RC_OvlLinie);

	lVolNr = OBLSatz.zovol;		// BezugsKantenFolge

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
		DBASSERT (PutIdent (hPr, newON, Ident, TPLinie, &OBLSatz.zoid));
		__Write (dbaOBL, OBLSatz);
	} else {
	// bestehendes Objekt lesen
		newON = dbaOBL.rec_no = *pOBL;
		*pOBL = 0;		// sicherheitshalber
		__Read (dbaOBL, OBLSatz);
		if (OBLSatz.zovol == 0) 	// ObjektTyp stimmt nicht
			return (long)db_error (S_BADOBJTYP, RC_OvlLinie);

	// IdentifikatorSatz richten
		DBASSERT(VerifyIdent(hPr, newON, OBLSatz.zoid, TPLinie));

	// alten Geometrieverweis entfernen
		DBASSERT (delgil (hPr, newON));
		OBLSatz.zovol = 0;		// OBLSatz mitführen
	}

// Liste der Kanten überlagern
	DBASSERT (OvlLinie (hPr, newON, &OBLSatz.zovol, lVolNr));
	__Write (dbaOBL, OBLSatz);

// ObjektNummer liefern
	*pOBL = newON;

return S_OKAY;
}

// Kantenfolge einer Linie doppeln und an neues Objekt anhängen ---------------
long FUNCTYPE OvlLinie (HPROJECT hPr, long ONr, long *pNewChain, long lVolNr)
{
struct vol VOLSatz;
DB_ADDR dbaVOL(hPr);
long lNext = lVolNr;
ErrCode RC;

	dbaVOL.file_no = VOL;

	while (lNext) {
	// Element der BezugsKette lesen
		dbaVOL.rec_no = lNext;
		__Read (dbaVOL, VOLSatz);

	// neues Element in Kette bilden, in Kante eintragen
		DBASSERT (PutChainEnd (hPr, VOL, pNewChain, VOLSatz.zvolk));
		DBASSERT (OvlKante (hPr, ONr, labs (VOLSatz.zvolk)));

	// nächster VOLSatz
		lNext = VOLSatz.znvol;		// nächster Satz
	}

return S_OKAY;
}


// Eine Kante mit Objekt überlagern -------------------------------------------
long FUNCTYPE OvlKante (HPROJECT hPr, long ONr, long KalNr)
{
struct kal KALSatz;
DB_ADDR dbaKAL(hPr);
ErrCode RC;

// KantenSatz einlesen
	dbaKAL.file_no = KAL;
	dbaKAL.rec_no = KalNr;
	__Read (dbaKAL, KALSatz);

// diese Kante mit gegebenen Objekt überlagern (Objekt in Rückverkettung eintragen)
	DBASSERT (PutLink (hPr, VGO, &KALSatz.zkvgo, ONr));
	__Write (dbaKAL, KALSatz);

return S_OKAY;
}
