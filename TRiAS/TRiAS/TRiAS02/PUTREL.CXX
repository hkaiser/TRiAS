// Einspeichern einer Relation ------------------------------------------------
// File: PUTREL.C

#include "trias02p.hxx"

// Funktionsprototypen --------------------------------------------------------
static long FUNCTYPE TestOBL (HPROJECT hPr, long ONr);
static long FUNCTYPE RelMaske (HPROJECT hPr, long ONr, short RelTyp, short iFlag);
static long FUNCTYPE RelSet (HPROJECT hPr, long OPrim, long OSek, long RelCode, 
			     short RelTyp, long *pRelSatz);
static long FUNCTYPE RelKett (HPROJECT hPr, long ONr, long RelSatz, short RelTyp);
static long FUNCTYPE BRelSet (HPROJECT hPr, long OPrim, long OSek);


// Schreiben einer ElementarRelation ------------------------------------------
extern "C" 
long EXPORT02 FUNCTYPE PutRelation (HPROJECT hPr, long OPrim, long OSek, long RelCode, short RelTyp) 
{
long RelSatz = 0;		// Nummer des RELSatzes
ErrCode RC;

// DatenBasisVersion Testen
	if (GetDBVersion(hPr) < NEWDBVERSION)
		return db_error (E_BADDIRISVERSION, RC_PutRel);

// Prüfen, ob Objekte existieren
	DBASSERT (TestOBL (hPr, OPrim));
	DBASSERT (TestOBL (hPr, OSek));

	DEX_SetDirtyGeoDB (true);

	if (BREL (RelTyp)) {
	// wenn BegleitRelation aufgebaut werden soll

		DBASSERT (BRelSet (hPr, OPrim, OSek));
	} else {
	// RelationsSatz aufbauen
	short locRelTyp = RelTyp & (OUREL | GREL);

		DBASSERT (RelSet (hPr, OPrim, OSek, RelCode, locRelTyp, &RelSatz));

	// Relation für Primärobjekt verketten
		DBASSERT (RelKett (hPr, OPrim, RelSatz, locRelTyp));

	// Relation für Sekundärobjekt verketten
		DBASSERT (RelKett (hPr, OSek, RelSatz, locRelTyp ^ OUREL));
	}

// RelationsTyp in ObjektSätzen schreiben
	DBASSERT (RelMaske (hPr, OPrim, RelTyp, TRUE));
	DBASSERT (RelMaske (hPr, OSek, RelTyp, FALSE));

return S_OKAY;
}

// Testen, ob ObjektSatz existiert --------------------------------------------
static long FUNCTYPE TestOBL (HPROJECT hPr, long ONr) 
{
DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;
int (*e_noon)(int, int, ...);
int (*dummy)(int, int, ...);
long RC, EC;

// Fehlermeldung unterdrücken
	DBASSERT (err_install (S_INVADDR, E_IGNORE, &e_noon));

// ObjektSatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	EC = z_readrec (&dbaOBL, &OBLSatz);	

// Fehlermeldung wieder zuschalten
	DBASSERT (err_install (S_INVADDR, e_noon, &dummy));

return EC;
}

// Setzen der Relationsmasken -------------------------------------------------
static long FUNCTYPE RelMaske (HPROJECT hPr, long ONr, short RelTyp, short iFlag) {
short hrel = HREL (RelTyp);
short vrel = VREL (RelTyp);
short brel = BREL (RelTyp);

DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;
long RC;

// ObjektSatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	__Read (dbaOBL, OBLSatz);

// Relationstyp im ObjektSatz korrigieren
	OBLSatz.rmaske |= hrel;
	if (iFlag) {
		OBLSatz.rmaske |= vrel;
		OBLSatz.rmaske |= brel;
	} else {
		if (vrel) OBLSatz.rmaske |= vrel ^ OUREL;
		if (brel) OBLSatz.rmaske |= brel ^ BRELAP;
	}
	if (vrel || hrel || brel) 
		__Write (dbaOBL, OBLSatz);

return S_OKAY;
}

// Setzen des RelationsCodes in der GeoDB -------------------------------------
static long FUNCTYPE RelSet (HPROJECT hPr, long OPrim, long OSek, long RelCode, 
			     short RelTyp, long *pRelSatz)
{
int (*w_notfound)(int, int, ...);
int (*dummy)(int, int, ...);
DB_ADDR dbaRAL(hPr);
struct ral RALSatz;
long RC;

// Fehlermeldung unterdrücken
	DBASSERT (err_install (S_NOTFOUND, E_IGNORE, &w_notfound));

// RelCode als Schlüssel suchen und ggf. neuen Schlüsseleintrag machen
	dbaRAL.file_no = RAL;
	if ((RC = z_keyfind (&dbaRAL, RAT, &RelCode)) != S_OKAY) {
	long EC = RC;

		if (RC == S_NOTFOUND) {
		// RelCode existiert noch nicht
		// Fehlermeldung wieder zuschalten
			DBASSERT (err_install (S_NOTFOUND, w_notfound, &dummy));

			memset (&RALSatz, '\0', sizeof(RALSatz));
			RALSatz.rat = RelCode;	// RelationsCode setzen
			RALSatz.maske = RelTyp;
			__New (dbaRAL, RALSatz);
		} else {
			DBASSERT (err_install (S_NOTFOUND, w_notfound, &dummy));
			return EC;	// Fehler
		}
	} else {
	// RelCode existiert bereits, einlesen
	// Fehlermeldung wieder zuschalten
		DBASSERT (err_install (S_NOTFOUND, w_notfound, &dummy));
		__Read (dbaRAL, RALSatz);

	// prüfen, ob RelTyp übereinstimmt
		if (RALSatz.maske != RelTyp)
			return db_error (W_BADRELTYP, RC_PutRel);
	}

// Aufbauen des RELSatzes
	if (!FindRelation (hPr, OPrim, OSek, RelCode, RelTyp, NULL)) {
	DB_ADDR dbaREL(hPr);
	struct rel RELSatz;

		dbaREL.file_no = REL;
		memset (&RELSatz, '\0', sizeof(RELSatz));

		RELSatz.zrera = dbaRAL.rec_no;
		RELSatz.zol1 = OPrim;
		RELSatz.zol2 = OSek;
		__New (dbaREL, RELSatz);
		*pRelSatz = dbaREL.rec_no;

	// RALSatz in VerbindungsDatei einketten
		DBASSERT (PutLink (hPr, VRE, &RALSatz.zravre, *pRelSatz));
		__Write (dbaRAL, RALSatz);
	} else 
		return db_error (S_DUPLREL, RC_RelSet);

return S_OKAY;
}

// Verketten der Relation in einer der drei Relationsketten -------------------
static long FUNCTYPE RelKett (HPROJECT hPr, long ONr, long RelSatz, short RelTyp) 
{
DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;
DB_ADDR dbaVRT(hPr);
struct reltyp VRTSatz;
long RC;

// ObjektSatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	__Read (dbaOBL, OBLSatz);

// verlängerten ObjektSatz lesen/neu bilden
	dbaVRT.file_no = RELTYP;
	if (OBLSatz.zovor) {
	// RELTYPSatz einlesen
		dbaVRT.rec_no = OBLSatz.zovor;
		__Read (dbaVRT, VRTSatz);
	} else {
	// selbigen neu generieren
		memset (&VRTSatz, '\0', sizeof(VRTSatz));
		__New (dbaVRT, VRTSatz);
		OBLSatz.zovor = dbaVRT.rec_no;
		__Write (dbaOBL, OBLSatz);
	}

// RelTyp-abhängiges einketten
	{
	short vrel = VREL (RelTyp);
	short hrel = HREL (RelTyp);

		if (hrel) {
			DBASSERT (PutLink (hPr, VOR, &VRTSatz.zhrel, RelSatz));
			__Write (dbaVRT, VRTSatz);
		} else if (vrel & UREL) {
			DBASSERT (PutLink (hPr, VOR, &VRTSatz.zvrelu, RelSatz));
			__Write (dbaVRT, VRTSatz);
		} else if (vrel & OREL) {
			DBASSERT (PutLink (hPr, VOR, &VRTSatz.zvrelo, RelSatz));
			__Write (dbaVRT, VRTSatz);
		}
	}

return S_OKAY;
}

// BegleitRelation zwischen zwei existierenden Objekten aufbauen --------------
static long FUNCTYPE BRelSet (HPROJECT hPr, long OPrim, long OSek) 
{
DB_ADDR_OBL dbaOBLP(hPr), dbaOBLS(hPr);
struct obl OBLSatzP, OBLSatzS;
long RC;

// ObjektSätze einlesen
//	dbaOBLP.file_no = dbaOBLS.file_no = OBL;
	dbaOBLP.rec_no = OPrim;
	__Read (dbaOBLP, OBLSatzP);
	dbaOBLS.rec_no = OSek;
	__Read (dbaOBLS, OBLSatzS);

// wenn Primärobjekt TextObjekt ist, dann Fehler
	if (OBLSatzP.status & SB_TEXTOBJ)
		return db_error (S_BADPRIMOBJ, RC_BRelSet);

// wenn noch keine ObjektRelation exitiert
	if (!BREL(OBLSatzP.rmaske) && !BREL(OBLSatzS.rmaske)) {
	DB_ADDR dbaVRTP(hPr), dbaVRTS(hPr);
	struct reltyp VRTSatzP, VRTSatzS;

		dbaVRTP.file_no = dbaVRTS.file_no = RELTYP;

	// RELTYPSatz für PrimärObjekt behandeln
		if (OBLSatzP.zovor == 0) {
		// RELTYPSatz existiert noch nicht
			memset (&VRTSatzP, '\0', sizeof(VRTSatzP));
			VRTSatzP.zbrela = OSek;
			__New (dbaVRTP, VRTSatzP);

		// ObjektSatz korrigieren
			OBLSatzP.zovor = dbaVRTP.rec_no;
			__Write (dbaOBLP, OBLSatzP);
		} else {
		// RELTYPSatz einlesen und BRel neu setzen
			dbaVRTP.rec_no = OBLSatzP.zovor;
			__Read (dbaVRTP, VRTSatzP);

			VRTSatzP.zbrela = OSek;
			__Write (dbaVRTP, VRTSatzP);
		}

	// RELTYPSatz für SekundärObjekt behandeln
		if (OBLSatzS.zovor == 0) {
		// RELTYPSatz existiert noch nicht
			memset (&VRTSatzS, '\0', sizeof(VRTSatzS));
			VRTSatzS.zbrelp = OPrim;
			__New (dbaVRTS, VRTSatzS);

		// ObjektSatz korrigieren
			OBLSatzS.zovor = dbaVRTS.rec_no;
			__Write (dbaOBLS, OBLSatzS);
		} else {
		// RELTYPSatz einlesen und BRel neu setzen
			dbaVRTS.rec_no = OBLSatzS.zovor;
			__Read (dbaVRTS, VRTSatzS);

			VRTSatzS.zbrelp = OPrim;
			__Write (dbaVRTS, VRTSatzS);
		}
	} else 
		return db_error (W_DUPLBREL, RC_BRelSet);

return S_OKAY;
}
