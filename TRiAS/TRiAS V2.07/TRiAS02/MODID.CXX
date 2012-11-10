// Modifikation des Identifikators eines Objektes -----------------------------
// File: MODID.C

#include "trias02p.hxx"

extern "C" long FUNCTYPE EXPORT02 modid (HPROJECT hPr, long ONr, long newID) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;		// FehlerCode

// Identifikator für gegebenes Objekt löschen
	DEX_SetDirtyGeoDB (true);

int iOType = TPUnknown; 

	DBASSERT (delid (hPr, ONr, &iOType));

// Neuen Identifikatorsatz schreiben
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	__Read (dbaOBL, OBLSatz);

	DBASSERT (PutIdent (hPr, ONr, newID, iOType, &OBLSatz.zoid));
	__Write (dbaOBL, OBLSatz);
	
return S_OKAY;
}
