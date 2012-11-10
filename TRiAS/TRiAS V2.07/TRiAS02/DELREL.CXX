// Loeschen einer ElementarRelation zwischen zwei Objekten --------------------
// File: DELREL.C

#include "trias02p.hxx"

// Funktionsprototypen --------------------------------------------------------
static long FUNCTYPE TestOBL (HPROJECT hPr, long ONr, short RelTyp);
static long FUNCTYPE DelVorSatz (HPROJECT hPr, long ONr, short RelTyp, long RelSatz);
static long FUNCTYPE BDelRel (HPROJECT hPr, long OPrim, long OSek);

// löscht die gegebene ElementarRelation zwischen zwei Objekten ---------------
extern "C" long EXPORT02 FUNCTYPE DelRelation (HPROJECT hPr, 
		long OPrim, long OSek, long RelCode, short RelTyp) 
{
ErrCode RC;
DB_ADDR dbaRAL(hPr), dbaREL(hPr);
struct ral RALSatz;
long RelSatz;

// DatenBasisVersion testen
	if (GetDBVersion(hPr) < NEWDBVERSION)
		return db_error (E_BADDIRISVERSION, RC_DelRel);

// Prüfen, ob Objekte existieren
	DBASSERT (TestOBL (hPr, OPrim, RelTyp));
	DBASSERT (TestOBL (hPr, OSek, RelTyp ^ (OUREL | BRELAP)));

// wenn Begleitrelation, dann gesondert behandlen
	DEX_SetDirtyGeoDB (true);

	if (BREL (RelTyp)) {
		if (RelTyp & BRELA) 
			return BDelRel (hPr, OPrim, OSek);
		else	
			return BDelRel (hPr, OSek, OPrim);	// RückRelation auflösen
	}	

// in VORKette entsprechende Sätze löschen, OBLSatz und VRTSatz korrigieren
	if (!FindRelation (hPr, OPrim, OSek, RelCode, RelTyp, &RelSatz))
		return db_error (W_NORELATION, RC_DelRel);

	DBASSERT (DelVorSatz (hPr, OPrim, RelTyp, RelSatz));
	DBASSERT (DelVorSatz (hPr, OSek, RelTyp ^ OUREL, RelSatz));

// RALSatz finden
	dbaRAL.file_no = RAL;
	DBASSERT (z_keyfind (&dbaRAL, RAT, &RelCode));
	__Read (dbaRAL, RALSatz);

// VRESatz aus Kette herauslösen
	DBASSERT (DelLink (hPr, VRE, &RALSatz.zravre, RelSatz));
	if (RALSatz.zravre) {
		__Write (dbaRAL, RALSatz);
	} else {
		__Dispose (dbaRAL);
	}

// RELSatz löschen
	dbaREL.file_no = REL;
	dbaREL.rec_no = RelSatz;
	__Dispose (dbaREL);

return S_OKAY;
}

// Testen, ob ObjektSatz existiert --------------------------------------------
static long FUNCTYPE TestOBL (HPROJECT hPr, long ONr, short RMaske) 
{
DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;
int (*e_noon)(int, int, ...);
int (*dummy)(int, int, ...);
long RC, EC;

// Fehlermeldung unterdrücken
	DBASSERT (err_install (S_INVADDR, E_IGNORE, &e_noon));

	memset (&OBLSatz, '\0', sizeof (struct obl));
	
// ObjektSatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	EC = z_readrec (&dbaOBL, &OBLSatz);	

// Fehlermeldung wieder zuschalten
	DBASSERT (err_install (S_INVADDR, e_noon, &dummy));

// Testen, ob gesuchte Relation überhaupt existiert 
	if (!(OBLSatz.rmaske & RMaske))
		return db_error (W_BADRELTYP, RC_DelRel);

return EC;
}

// Herauslösen des Relationssatzes aus der VORKette ---------------------------
// korrigieren der RelationsInfo im OBLSatz und VRTSatz
static long FUNCTYPE DelVorSatz (HPROJECT hPr, long ONr, short RelTyp, long RelSatz) 
{
ErrCode RC;
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR dbaVRT(hPr);
struct obl OBLSatz;
struct reltyp VRTSatz;

// ObjektSatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	__Read (dbaOBL, OBLSatz);

// zugehörigen VRTSatz lesen
	dbaVRT.file_no = RELTYP;
	dbaVRT.rec_no = OBLSatz.zovor;
	__Read (dbaVRT, VRTSatz);

// VORSatz aus entsprechender Kette herauslöschen
	if (HREL(RelTyp)) {		// gleichrangige Relation
		DBASSERT (DelLink (hPr, VOR, &VRTSatz.zhrel, RelSatz));
		if (VRTSatz.zhrel == 0)	{
		// letzte Relation dieses Typs gelöscht
			OBLSatz.rmaske &= ~GREL;	// Maske korrigieren
			__Write (dbaOBL, OBLSatz);
		}
	} else if (VRELO(RelTyp)) {	// Relation nach oben
		DBASSERT (DelLink (hPr, VOR, &VRTSatz.zvrelo, RelSatz));
		if (VRTSatz.zvrelo == 0) {
		// letzte Relation dieses Typs gelöscht
			OBLSatz.rmaske &= ~OREL;
			__Write (dbaOBL, OBLSatz);
		}
	} else if (VRELU(RelTyp)) {	// Relation nach unten
		DBASSERT (DelLink (hPr, VOR, &VRTSatz.zvrelu, RelSatz));
		if (VRTSatz.zvrelu == 0) {
		// letzte Relation dieses Typs gelöscht
			OBLSatz.rmaske &= ~UREL;	// Maske korrigieren
			__Write (dbaOBL, OBLSatz);
		}
	}

// VRTSatz wegschreiben oder auflösen
	if (OBLSatz.rmaske != 0) { 	// noch Relationen vorhanden
		__Write (dbaVRT, VRTSatz);
	} else {			// letzte Relation wurde gelöscht
		__Dispose (dbaVRT);
		OBLSatz.zovor = 0;	// ObjektSatz richten und wegschreiben
		__Write (dbaOBL, OBLSatz);
	}

return S_OKAY;
}

// Löschen einer Begleitrelation ----------------------------------------------
static long FUNCTYPE BDelRel (HPROJECT hPr, long OPrim, long OSek) 
{
DB_ADDR_OBL dbaOBLP(hPr), dbaOBLS(hPr);
struct obl OBLSatzP, OBLSatzS;
ErrCode RC;

// ObjektSätze einlesen
//	dbaOBLP.file_no = dbaOBLS.file_no = OBL;
	dbaOBLP.rec_no = OPrim;
	__Read (dbaOBLP, OBLSatzP);
	dbaOBLS.rec_no = OSek;
	__Read (dbaOBLS, OBLSatzS);

// wenn noch keine ObjektRelation exitiert
	if (!BREL(OBLSatzP.rmaske) && !BREL(OBLSatzS.rmaske)) 
		return db_error (W_NOTEXTOBJ, RC_DelRel);

	{
	DB_ADDR dbaVRTP(hPr), dbaVRTS(hPr);
	struct reltyp VRTSatzP, VRTSatzS;

		dbaVRTP.file_no = dbaVRTS.file_no = RELTYP;

	// RELTYPSatz für PrimärObjekt behandeln
		if (OBLSatzP.zovor != 0) {
		// RELTYPSatz einlesen und BRel neu setzen
			dbaVRTP.rec_no = OBLSatzP.zovor;
			__Read (dbaVRTP, VRTSatzP);

			VRTSatzP.zbrela = 0L;	// Relation löschen
			__Write (dbaVRTP, VRTSatzP);

			if ((OBLSatzP.rmaske &= ~BRELA) == 0) {
				__Dispose (dbaVRTP);
				OBLSatzP.zovor = 0L;
			}
			__Write (dbaOBLP, OBLSatzP);
		} else
			return db_error (W_NOTEXTOBJ, RC_DelRel);

	// RELTYPSatz für SekundärObjekt behandeln
		if (OBLSatzS.zovor != 0) {
		// RELTYPSatz einlesen und BRel neu setzen
			dbaVRTS.rec_no = OBLSatzS.zovor;
			__Read (dbaVRTS, VRTSatzS);

			VRTSatzS.zbrelp = 0L;
			__Write (dbaVRTS, VRTSatzS);

			if ((OBLSatzS.rmaske &= ~BRELP) == 0) {
				__Dispose (dbaVRTS);
				OBLSatzS.zovor = 0L;
			}
			__Write (dbaOBLS, OBLSatzS);
		} else 
			return db_error (W_NOTEXTOBJ, RC_DelRel);
	}

return S_OKAY;
}
