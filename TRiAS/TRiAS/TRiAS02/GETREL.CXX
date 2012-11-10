// Finden aller Objekte, die in einer bestimmten Relation zu einem gegbenen
// Objekt stehen und finden aller übergeordneten Objekte
// File: GETREL.CXX

#include "trias02p.hxx"

#include <objfeld.hxx>

#include "relliste.hxx"
#include "getrcode.hxx"


// Liefert alle Objekte, die in der gegebenen Relation zu einem Ausgangsobjekt
// stehen.
ErrCode BFindRel (HPROJECT hPr, long lONr, ObjFeld &Objekte);

ErrCode GetRelation (HPROJECT hPr, long ONr, long RCode, ObjFeld &OF) 
{
	if (GetDBVersion(hPr) < NEWDBVERSION) return EC_OKAY;

// wenn Begleitrelation gesucht ist, dann diese hier suchen
	if (RCode == -1L) return BFindRel (hPr, ONr, OF);

DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;
ErrCode RC;

// ObjektSatz lesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	__Read (dbaOBL, OBLSatz);

// Testen, ob überhaupt Relationen existieren
	if (!HREL(OBLSatz.rmaske) && !VREL(OBLSatz.rmaske)) 
		return (ErrCode)db_error (WC_NOTFOUND, RC_GetRelation);

// Finden der gegebenen Relation
DB_ADDR dbaRAL(hPr);
struct ral RALSatz;

	dbaRAL.file_no = RAL;
	DBASSERT (z_keyfind (&dbaRAL, RAT, &RCode));
	__Read (dbaRAL, RALSatz);

// Aufsammeln der gesuchten Objekte entlang der VREKette
DB_ADDR dbaVRE(hPr);
struct vre VRESatz;
DB_ADDR dbaREL(hPr);
struct rel RELSatz;
long Next = RALSatz.zravre;
ObjNummerCreator ONC (OF);

	dbaVRE.file_no = VRE;
	dbaREL.file_no = REL;
	while (dbaVRE.rec_no = Next) {
	// VRESatz lesen
		__Read (dbaVRE, VRESatz);
		Next = VRESatz.znvre;		// nächster Satz

	// RELSatz lesen
		dbaREL.rec_no = VRESatz.zvrere;
		__Read (dbaREL, RELSatz);

	// überprüfen, ob gegebenes Objekt dabei ist
	ObjRelNummer *pORN;

		if (RELSatz.zol1 == ONr) {
		// Primärobjekt
			if ((pORN = (ObjRelNummer *)OF.NewObj (ONC, RELSatz.zol2)) == NULL)
				return (ErrCode)db_error (EC_NOMEMORY, RC_GetRelation);

		// wenn RelationsFeld, dann noch Relationen eintragen
			if (OF.isA() == OFTObjRelFeld) {
				pORN -> RelCode() = RCode;
				pORN -> RelTyp() = RALSatz.maske;
			}
			ONC.Insert();
		} else if (RELSatz.zol2 == ONr) {
		// SekundärObjekt
			if ((pORN = (ObjRelNummer *)OF.NewObj (ONC, RELSatz.zol1)) == NULL)
				return (ErrCode)db_error (EC_NOMEMORY, RC_GetRelation);

		// wenn RelationsFeld, dann noch Relationen eintragen
			if (OF.isA() == OFTObjRelFeld) {
				pORN -> RelCode() = RCode;
				pORN -> RelTyp() = RALSatz.maske;
			}
			ONC.Insert();
		}
	}

// Fehlermeldung, wenn keine Relationen gefunden wurden
	if (OF.Count() == 0)
	// DAS sollte nicht passieren
		return (ErrCode)db_error (EC_SYSERROR, RC_GetRelation);

return EC_OKAY;
}

// Auffinden des Objektes einer Begleitrelation -------------------------------
ErrCode BFindRel (HPROJECT hPr, long lONr, ObjFeld &OF)
{
long lAssocONr = AssociatedObjekt (hPr, lONr);
ObjNummerCreator ONC (OF);
ObjRelNummer *pORN;

	if (lAssocONr < 0) {
		if ((pORN = (ObjRelNummer *)OF.NewObj (ONC, -lAssocONr)) == NULL)
			return (ErrCode)db_error (EC_NOMEMORY, RC_BFindRel);

	// wenn RelationsFeld, dann noch Relationen eintragen
		if (OF.isA() == OFTObjRelFeld) {
			pORN -> RelCode() = -1;
			pORN -> RelTyp() = BRELA;
		}
		ONC.Insert();
	} else if (lAssocONr > 0) {
		if ((pORN = (ObjRelNummer *)OF.NewObj (ONC, lAssocONr)) == NULL)
			return (ErrCode)db_error (EC_NOMEMORY, RC_BFindRel);

	// wenn RelationsFeld, dann noch Relationen eintragen
		if (OF.isA() == OFTObjRelFeld) {
			pORN -> RelCode() = -1;
			pORN -> RelTyp() = BRELP;
		}
		ONC.Insert();
	} else if (lAssocONr == 0)
		return (ErrCode)db_error (EC_SYSERROR, RC_BFindRel);

return EC_OKAY;
}


extern "C" {

// Finden aller Objekte, die in der Hierarchie über dem gegebenen stehen ------
long FUNCTYPE GetKomplexObjects (HPROJECT hPr, long ONr, long Feld) 
{
// bei alten DBVersionen so tun als ob es keine Komplexobjekte gäbe
	if (GetDBVersion(hPr) < NEWDBVERSION) return (long)EC_OKAY;

ErrCode RC;
RCodes RelC;

	{
	ErrInstall EI (WC_NOTFOUND);

		if ((RC = GetRelationsCodes (hPr, ONr, RelC, UREL)) != EC_OKAY) {
			if (RC == WC_NOTFOUND) 	return (long)EC_OKAY;
			else 			return (long)RC;
		}
	}
	
CTable t(RelC);

	for (t.First(); t.Valid(); t.Next()) {
	RCodeLock l(t);
	ObjRelFeld OF;

		if (!l) continue;
		DBASSERT (GetRelation (hPr, ONr, l -> RelCode(), OF));

	CRing r(OF);

		for (r.First(); r.Valid(); r.Next()) {
		ObjRelNummerLock lr(r);

			if (!lr) continue;
			DBASSERTM (feput_ (&Feld, &(lr -> _ON)));
		}
	}

return EC_OKAY;
}

} 	// extern "C"

// Memberfunktionen für ObjRelNummer und ObjRelFeld ---------------------------
ObjRelNummer :: ObjRelNummer (long ONr) 
	      : ObjNummer (ONr)
{
	// nothing to do
}

ObjRelNummer :: ~ObjRelNummer (void) 
{
	// nothing to do
}

ObjRelFeld :: ObjRelFeld (void)
	    : ObjFeld ()
{
	// nothing else to do
}

ObjRelFeld :: ~ObjRelFeld (void) 
{
	EveryDelete ();
}

void EXPORT02 ObjRelFeld :: UserDelete (void *pObj)
{
	((ObjRelNummer *)pObj) -> /*ObjRelNummer ::*/ ~ObjRelNummer ();
}

ObjFeldTyp ObjRelFeld :: isA (void) { return OFTObjRelFeld; }

// virtueller Konstruktor
ObjNummer *ObjRelFeld :: NewObj (ObjNummerCreator &ONC, long ONr) 
{	
	return ContCreate (ONC, ObjRelNummer)(ONr);
}
