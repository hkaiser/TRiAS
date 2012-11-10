// Loeschen eines Objektes der DatenBasis -------------------------------------
// File: DEL.C

#include "trias02p.hxx"

// löscht das vorgegebene Objekt vollständig und unwiderrufbar aus der DB -----
extern "C" long EXPORT02 FUNCTYPE del (HPROJECT hPr, long ON) 
{
ErrCode RC;		// FehlerCode
DB_ADDR_OBL dbaOBL(hPr);

	DEX_SetDirtyGeoDB(true);

// Relationen behandeln
// 1. evtl. Textobjekt rauswerfen
	{
	long AssocON = AssociatedObjekt (hPr, ON);

		if (AssocON < 0) {
		// BegleitRelation auflösen
			DBASSERT (DelRelation (hPr, ON, -AssocON, 0, BRELA));
		// TextObjekt löschen
			DBASSERT (del (hPr, -AssocON));
		} else if (AssocON > 0) {
		// Objekt ist abhängiges Begleitobjekt
			DBASSERT (DelRelation (hPr, ON, AssocON, 0, BRELP));
		}
	}

// 2. alle anderen Relationen, die dieses Objekt hat löschen
	DBASSERT (DelAllRelations (hPr, ON));

// Merkmale löschen 
	while ((RC = (ErrCode)delmi (hPr, -1L, ON, dbaOBL.file_no)) == S_OKAY)
		;
	if (RC != S_DUMMY) return RC;

// Identifikator löschen
int iOType = TPUnknown; 

	DBASSERT (delid (hPr, ON, &iOType));

// Geometrie löschen 
	DBASSERT (delgi (hPr, ON));

// ObjektSatz löschen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	__Dispose (dbaOBL);

return S_OKAY;
}

