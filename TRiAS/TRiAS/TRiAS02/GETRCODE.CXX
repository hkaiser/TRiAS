// Liefert fuer ein Objekt alle zugehoerigen RelationsCodes incl. RelTyp
// File: GETRCODE.CXX

#include "trias02p.hxx"

#include "getrcode.hxx"

// RelationsCode --------------------------------------------------------------
RCode :: RCode (long RCode, short RTyp) 
{
	_RelCode = RCode;
	_RelTyp = RTyp;
}

RCode :: RCode (RCode &RC) 
{
	_RelCode = RC.RelCode();
	_RelTyp = RC.RelTyp();
}

// eigentliche Funktion  ------------------------------------------------------
ErrCode GetCodes (HPROJECT hPr, long ONr, long Start, RCodes &RelC);
ErrCode BGetRel (HPROJECT hPr, long lONr, RCodes &RelC);

ErrCode GetRelationsCodes (HPROJECT hPr, long ONr, RCodes &RelC, short iMaske) 
{
	if (GetDBVersion(hPr) < NEWDBVERSION) return EC_OKAY;

DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;
ErrCode RC;

// ObjektSatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	__Read (dbaOBL, OBLSatz);

// Maske testen
Bool fBFound = FALSE;

	if (BREL(iMaske)) {	// Begleitrelation
		DBASSERT (BGetRel (hPr, ONr, RelC));
		fBFound = TRUE;
	}

	if (!KREL(iMaske)) return EC_OKAY;	// nichts gesucht - nichts gefunden
	if (VREL(iMaske)) {
		if (HREL(iMaske)) {
			if (!HREL(OBLSatz.rmaske) && !VREL(OBLSatz.rmaske)) {
			// beides gesucht aber keine da
				if (fBFound) return EC_OKAY;
				return (ErrCode)db_error (WC_NOTFOUND, RC_GetRelCode);
			}
		} else {
			if (!VREL(OBLSatz.rmaske)) {
			// nur VREL's gesucht aber keine da
				if (fBFound) return EC_OKAY;
				return (ErrCode)db_error (WC_NOTFOUND, RC_GetRelCode);
			}
		}
	} else if (HREL(iMaske) && !HREL(OBLSatz.rmaske)) {
	// nur HREL's gesucht aber keine da
		if (fBFound) return EC_OKAY;
		return (ErrCode)db_error (WC_NOTFOUND, RC_GetRelCode);
	}

DB_ADDR dbaVRT(hPr);
struct reltyp VRTSatz;

	dbaVRT.file_no = RELTYP;
	dbaVRT.rec_no = OBLSatz.zovor;
	__Read (dbaVRT, VRTSatz);

// Einlesen der RelCodes
	if (HREL(iMaske) && HREL(OBLSatz.rmaske))
		DBASSERT (GetCodes (hPr, ONr, VRTSatz.zhrel, RelC));
	if (VREL(iMaske) && VRELU(OBLSatz.rmaske))
		DBASSERT (GetCodes (hPr, ONr, VRTSatz.zvrelu, RelC));
	if (VREL(iMaske) && VRELO(OBLSatz.rmaske))
		DBASSERT (GetCodes (hPr, ONr, VRTSatz.zvrelo, RelC));

	if (RelC.Count() == 0)
	// das sollte nicht passieren
		return (ErrCode)db_error (EC_SYSERROR, RC_GetRelCode);

return EC_OKAY;
}

// Einlesen aller RelationsCodes einer logischen Klasse
ErrCode GetCodes (HPROJECT hPr, long ONr, long Start, RCodes &RelC) 
{
	if (GetDBVersion(hPr) < NEWDBVERSION) return EC_OKAY;

DB_ADDR dbaVOR(hPr), dbaREL(hPr), dbaRAL(hPr);
struct vor VORSatz;
struct rel RELSatz;
struct ral RALSatz;

// DBAdressen initialisieren
	dbaVOR.file_no = VOR;
	dbaREL.file_no = REL;
	dbaRAL.file_no = RAL;

// für jeden Satz der VOR-Kette
long Next = Start;
CTable t(RelC);
RCodeCreator RelCCr (RelC);	// Creator für den RCodeBaum
ErrCode RC;

	while (dbaVOR.rec_no = Next) {
	// Verbindungskette lesen
		__Read (dbaVOR, VORSatz);
		Next = VORSatz.znvor;	// nächster Satz

	// einlesen des RELSatzes
		dbaREL.rec_no = VORSatz.zvorel;
		__Read (dbaREL, RELSatz);

	// einlesen des RALSatzes
		dbaRAL.rec_no = RELSatz.zrera;
		__Read (dbaRAL, RALSatz);

	// einhängen in den Baum
		if (RELSatz.zol1 == ONr) {
		// Primärobjekt
			if (!t.Find(&RALSatz.rat) &&
			    ContCreate (RelCCr, RCode)(RALSatz.rat, RALSatz.maske))
				RelCCr.Insert();
		} else if (RELSatz.zol2 == ONr) {
		// SekundärObjekt
			if (!t.Find(&RALSatz.rat) &&
			    ContCreate (RelCCr, RCode)(RALSatz.rat, RALSatz.maske ^ OUREL))
				RelCCr.Insert();
		} else
		// das sollte nicht passieren
			return (ErrCode)db_error (EC_SYSERROR, RC_GetCodes);
	}

return EC_OKAY;
}

// Begleitrelation finden -----------------------------------------------------
ErrCode BGetRel (HPROJECT hPr, long lONr, RCodes &RelC)
{
long lAssocONr = AssociatedObjekt (hPr, lONr);
RCodeCreator RelCCr (RelC);	// Creator für den RCodeBaum

	// abhängiges Textobjekt ist da
	if (lAssocONr < 0 && (ContCreate (RelCCr, RCode)(-1L, BRELA) != NULL)) {
		RelCCr.Insert();
		return EC_OKAY;
	} else if (lAssocONr > 0 && (ContCreate (RelCCr, RCode)(-1L, BRELP) != NULL)) {
		RelCCr.Insert();
		return EC_OKAY;
	} else if (lAssocONr == 0) 
		return EC_OKAY;

return (ErrCode)db_error (EC_SYSERROR, RC_BGetRel);
}


// Holen einer Komplexrelation (Relation von Oben eines Komplexobjektes) ------
ErrCode RetrieveORCode (HPROJECT hPr, INT_PTR ONr, INT_PTR &RCode) 
{
	if (GetDBVersion(hPr) < NEWDBVERSION) return EC_OKAY;

RCodes RelC;
ErrCode RC;

	RCode = -1L;

// alle KomplexRelationen dieses Komplexobjektes lesen
	DBASSERT (GetRelationsCodes (hPr, ONr, RelC, OREL));

// Finden der KomplexRelation
CTable t(RelC);

	for (t.First(); t.Valid(); t.Next()) {
	RCodeLock l(t);

		if (!l) continue;
		if (l -> RelTyp() & OREL) {
			if (RCode != -1L) 
				return (ErrCode)db_error (WC_MULTIPLEREL, RC_RetrieveORCode);
			RCode = l -> RelCode();
		}
	}
	if (RCode == -1L) 
		return (ErrCode)db_error (WC_NOKO, RC_RetrieveORCode);

return EC_OKAY;
}
