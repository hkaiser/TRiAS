// Generieren eines ObjektTemplates -------------------------------------------
// File: PUTTEMPL.C

#include "trias02p.hxx"

// Generiert ein neues Punktobjekt --------------------------------------------
extern "C" 
long EXPORT02 FUNCTYPE PutObjTemplate (HPROJECT hPr, long *pOBL, long Ident) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;                 // FehlerVariable
long newON = -1L;

	DEX_SetDirtyGeoDB (true);

// Objektsatz lesen/generieren
//	dbaOBL.file_no = OBL;
	if (*pOBL <= 0) {
	// neuen ObjektSatz generieren
		memset (&OBLSatz, '\0', sizeof (OBLSatz));

		if (VERSION0500000E <= GetDBVersion (hPr))	// evtl. GUID generieren
			CoCreateGuid (&OBLSatz.guid);

		__New (dbaOBL, OBLSatz);
		newON = dbaOBL.rec_no;
	} else {
	// ObjektSatz einlesen, Objekt neu bilden
		newON = dbaOBL.rec_no = *pOBL;
		__Read (dbaOBL, OBLSatz);

	int iOType = TPUnknown; 

		DBASSERT (delid (hPr, newON, &iOType));		// alten Ident löschen
	}
	
// Identifikator in IDL eintragen
	DBASSERT (PutIdent (hPr, newON, Ident, TPUnknown, &OBLSatz.zoid));
	__Write (dbaOBL, OBLSatz);	// ObjektSatz nochmal wegschreiben

// ObjektNummer liefern
	*pOBL = newON;
	return S_OKAY;
}

