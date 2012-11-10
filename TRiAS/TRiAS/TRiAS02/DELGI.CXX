// Loeschen der Geometrie eines vorgegebenen Objektes -------------------------
// File: DELGI.C

#include "trias02p.hxx"

#define EStat	-9
#define RoutCD	2035

extern "C" long EXPORT02 FUNCTYPE delgi (HPROJECT hPr, long ON) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;		// FehlerCode

	DEX_SetDirtyGeoDB (true);

// Objektsatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	__Read (dbaOBL, OBLSatz);

// je nach Typ, Löschfunktionen rufen
	if (OBLSatz.zokp != 0) {
		DBASSERT (delgip (hPr, ON));
	}
	if (OBLSatz.zovol != 0) {
		DBASSERT (delgil (hPr, ON));
	}
	if (OBLSatz.zovoma != 0) {
		DBASSERT (delgif (hPr, ON));
	}

return S_OKAY;
}
