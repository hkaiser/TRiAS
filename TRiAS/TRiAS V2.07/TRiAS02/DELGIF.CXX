// Loeschen der Geometrie eines Flaechenobjektes ------------------------------
// File: DELGIF.C

#include "trias02p.hxx"

#define RoutCD	2060

extern "C" long EXPORT02 FUNCTYPE delgif (HPROJECT hPr, long ON) 
{
struct obl OBLSatz;
struct mal MALSatz;
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR dbaMAL(hPr);
ErrCode RC;	// FehlerCode

// Objektsatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	__Read (dbaOBL, OBLSatz);

// FlächenListe einlesen
	dbaMAL.file_no = MAL;
	dbaMAL.rec_no = OBLSatz.zovoma;
	__Read (dbaMAL, MALSatz);

// Verbindung Geometrie -> Objekt auflösen
	{
	struct kfm KFMSatz;
	DB_ADDR dbaKFM(hPr);

	// Kantenfolge der Fläche abklappern
		dbaKFM.file_no = KFM;
		dbaKFM.rec_no = MALSatz.zmkfm;
		while (dbaKFM.rec_no != 0) {
		// Kante einlesen
			__Read (dbaKFM, KFMSatz);
		// Kante herauslöschen (behandeln)
			DBASSERT (delkanf (hPr, KFMSatz.zkfmk, OBLSatz.zovoma));
		// Satz löschen
			__Dispose (dbaKFM);
		// nächster Satz
			dbaKFM.rec_no = KFMSatz.znkfm;
		}
	} 

// FlächenSatz freigeben
	__Dispose (dbaMAL);

// ObjektSatz aktualisieren: keine FlächenGeometrie mehr
	OBLSatz.zovoma = 0;
	__Write (dbaOBL, OBLSatz);

return S_OKAY;
}
