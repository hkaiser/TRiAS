// Finden des zu O1/O2/RelCode gehoerenden RELSatzes --------------------------
// File: FINDREL.C

#include "trias02p.hxx"

short FUNCTYPE FindRelSatz (HPROJECT hPr, long Begin, long *Wert, long RelCode, long O1, long O2); 

// Feststellen, ob eine bestimmte Relation existiert --------------------------
short FUNCTYPE FindRelation (HPROJECT hPr, long ON1, long ON2, long RelCode, 
			     short RelTyp, long *Wert) 
{
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR dbaVRT(hPr);
struct obl OBLSatz;
struct reltyp VRTSatz;
long RelSatz = 0;
ErrCode RC;

// ObjektSatz lesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON1;
	__Read (dbaOBL, OBLSatz);

	if (Wert != NULL) *Wert = 0;

// Maske auswerten
	if (!(OBLSatz.rmaske & RelTyp)) return FALSE;

// VRTSatz lesen
	dbaVRT.file_no = RELTYP;
	dbaVRT.rec_no = OBLSatz.zovor;
	__Read (dbaVRT, VRTSatz);

	if (HREL(OBLSatz.rmaske)) {
	// horizontale Relation prüfen
		DBASSERT (FindRelSatz (hPr, VRTSatz.zhrel, &RelSatz, RelCode, ON1, ON2));
	} else if (VRELO(OBLSatz.rmaske)) {
	// vertikal nach oben prüfen
		DBASSERT (FindRelSatz (hPr, VRTSatz.zvrelo, &RelSatz, RelCode, ON1, ON2));
	} else if (VRELU(OBLSatz.rmaske)) {
	// vertikal nach unten prüfen
		DBASSERT (FindRelSatz (hPr, VRTSatz.zvrelu, &RelSatz, RelCode, ON1, ON2));
	}
	if (RelSatz == 0) return FALSE;

// RELSatzNr liefern
	if (Wert != NULL)
		*Wert = RelSatz;

return TRUE;
}


short FUNCTYPE FindRelSatz (HPROJECT hPr, long Begin, long *Wert, 
			   long RelCode, long O1, long O2) 
{
DB_ADDR dbaVOR(hPr), dbaREL(hPr), dbaRAL(hPr);
struct vor VORSatz;
struct rel RELSatz;
struct ral RALSatz;
short RC;	// FehlerCode
long Next;

	dbaVOR.file_no = VOR;
	dbaREL.file_no = REL;
	dbaRAL.file_no = RAL;
	Next = Begin;
	*Wert = 0;
	while (dbaVOR.rec_no = Next) {
	// VORSatz einlesen
		__Read (dbaVOR, VORSatz);
		Next = VORSatz.znvor;		// nächster Satz	

	// RELSatz einlesen
		dbaREL.rec_no = VORSatz.zvorel;
		__Read (dbaREL, RELSatz);

	// RALSatz lesen
		dbaRAL.rec_no = RELSatz.zrera;
		__Read (dbaRAL, RALSatz);

	// Vergleichen, ob der gesuchte Satz gefunden wurde
		if (RelCode == RALSatz.rat && 	// RelationsCode
		    O1 == RELSatz.zol1 &&	// PrimärObjekt
		    O2 == RELSatz.zol2)	{	// SekundärObjekt
			*Wert = dbaREL.rec_no;
			break;
		}
	}	

return S_OKAY;
}
