// Loeschen der Geometrie eines Punktobjektes ---------------------------------
// File: DELGIP.C

#include "trias02p.hxx"

#define RoutCD	2040

extern "C" long FUNCTYPE delgip (HPROJECT hPr, long ON) 
{
struct obl OBLSatz;
struct pol POLSatz;
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR dbaPOL(hPr);
ErrCode RC;	// FehlerCode

// Objektsatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	__Read (dbaOBL, OBLSatz);

// PunktSatz einlesen
	dbaPOL.file_no = POL;
	dbaPOL.rec_no = OBLSatz.zokp;
	__Read (dbaPOL, POLSatz);

// diverse Tests
	if (POLSatz.zpvgo == 0)
		return db_error (S_BADPOLVGO, RoutCD);

// Verweis zum Objekt rauslöschen
	DBASSERT (DelLink (hPr, VGO, &POLSatz.zpvgo, ON));
	if (POLSatz.zpvgo != 0) {
	// nicht einziges Objekt, wegschreiben und raus
		__Write (dbaPOL, POLSatz);

	// ObjektSatz aktualisieren: keine Punktgeometrie mehr
		OBLSatz.zokp = 0;
		__Write (dbaOBL, OBLSatz);
		return S_OKAY;
	}

// PunktObjekt muá gleichzeitig KnotenPunkt sein
	if (POLSatz.zpkfk != 0) {
	// PunktObjekt ist KnotenPunkt, also als Knoten ablegen
		__Dispose (dbaPOL);
		dbaPOL.file_no = KPL;	// jetzt KnotenPunkt
		__New (dbaPOL, POLSatz);

	// ObjektSatz aktualisieren: keine Punktgeometrie mehr
		OBLSatz.zokp = 0;
		__Write (dbaOBL, OBLSatz);
		return S_OKAY;
	}

// PunktSatz kann nun gelöscht werden
	__Dispose (dbaPOL);

// ObjektSatz aktualisieren: keine Punktgeometrie mehr
	OBLSatz.zokp = 0;
	__Write (dbaOBL, OBLSatz);

return S_OKAY;
}
