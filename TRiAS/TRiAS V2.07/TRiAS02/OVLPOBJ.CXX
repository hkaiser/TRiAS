// Generieren eines PunktObjektes durch Overlay mit einem anderen
// File: OVLPOBJ.C

#include "trias02p.hxx"

// Generiert ein neues Punktobjekt --------------------------------------------
long FUNCTYPE OvlPunktObject (HPROJECT hPr, long *pOBL, long Ident, long TONr) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;                 // FehlerVariable
long newON = -1L;
long lKpNr = 0;

// wenn identische Objekte überlagert werden sollen, dann raus
	if (TONr == *pOBL) return S_OKAY;

// BezugsObjektsatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = TONr;
	__Read (dbaOBL, OBLSatz);
	if (OBLSatz.zokp == 0) 	// ObjektTyp stimmt nicht
		return (long)db_error (S_BADOBJTYP, RC_OvlPunkt);

	lKpNr = OBLSatz.zokp;	// PunktSatzNr

// Objektsatz lesen/generieren
	DEX_SetDirtyGeoDB (true);

	if (*pOBL <= 0) {
	// Objekt existiert noch nicht: generieren
		memset (&OBLSatz, '\0', sizeof (OBLSatz));

		if (VERSION0500000E <= GetDBVersion (hPr))	// evtl. GUID generieren
			CoCreateGuid (&OBLSatz.guid);

		__New (dbaOBL, OBLSatz);
		newON = dbaOBL.rec_no;

	// Identifikator bei Bedarf in IDL eintragen
		DBASSERT (PutIdent (hPr, newON, Ident, TPPunkt, &OBLSatz.zoid));
		__Write (dbaOBL, OBLSatz);
	} else {
	// bestehendes Objekt lesen
		newON = dbaOBL.rec_no = *pOBL;
		*pOBL = 0;		// sicherheitshalber
		__Read (dbaOBL, OBLSatz);
		if (OBLSatz.zokp == 0) 	// ObjektTyp stimmt nicht
			return (long)db_error (S_BADOBJTYP, RC_OvlPunkt);

	// IdentifikatorSatz richten
		DBASSERT(VerifyIdent(hPr, newON, OBLSatz.zoid, TPPunkt));

	// alten Geometrieverweis löschen
		DBASSERT (delgip (hPr, newON));

		OBLSatz.zokp = lKpNr;		// ObjektSatz mitführen
		__Write (dbaOBL, OBLSatz);	// wegschreiben
	}

// KoordinatenSatz überlagern
	DBASSERT (OvlPunkt (hPr, newON, OBLSatz.zokp));

// ObjektNummer liefern
	*pOBL = newON;

return S_OKAY;
}


// PunktSatz für ein Objekt überlagern ----------------------------------------
long FUNCTYPE OvlPunkt (HPROJECT hPr, long ONr, long PolNr)
{
struct pol POLSatz;
DB_ADDR dbaPOL(hPr);
ErrCode RC;

// POLSatz einlesen
	dbaPOL.file_no = POL;
	dbaPOL.rec_no = PolNr;
	__Read (dbaPOL, POLSatz);

// Objekt in die Rückverkettung dieses Punktes einhängen
	DBASSERT (PutLink (hPr, VGO, &POLSatz.zpvgo, ONr));
	__Write (dbaPOL, POLSatz);

return S_OKAY;
}

