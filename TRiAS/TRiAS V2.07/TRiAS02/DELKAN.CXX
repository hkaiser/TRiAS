// Loeschen der Geometrie einer Kante -----------------------------------------
// File: DELKAN.C

#include "trias02p.hxx"

#define RoutCD	2055

long FUNCTYPE delkan (HPROJECT hPr, long Kante, long ON) 
{
struct kal KALSatz;
DB_ADDR dbaKAL(hPr);
ErrCode RC;	// FehlerCode

// KantenSatz einlesen
	dbaKAL.file_no = KAL;
	dbaKAL.rec_no = Kante;
	__Read (dbaKAL, KALSatz);

// ObjektSatz aus Verbindung zur OBL löschen 
	DBASSERT (DelLink (hPr, VGO, &KALSatz.zkvgo, ON));
	if (KALSatz.zkvgo != 0) {
	// war nicht das letzte Objekt
		__Write (dbaKAL, KALSatz);
	} else if (KALSatz.zlm != 0 || KALSatz.zrm != 0) {
	// war das letzte LinienObjekt, aber Kante gehört noch zu Fläche
		__Write (dbaKAL, KALSatz);
	} else {
	// Kante muß gelöscht werden, Stützpunktfolge löschen
		DBASSERT (DeletePoints (hPr, KALSatz.zksp));
	// Anfangs und Endpunkt der Kante behandeln
		DBASSERT (DeleteNode (hPr, KALSatz.zap, Kante));
		DBASSERT (DeleteNode (hPr, KALSatz.zep, Kante));
	// KantenSatz freigeben 
		__Dispose (dbaKAL);
	}

return S_OKAY;
}


// Löschen der StützpunktFolge einer Kante ------------------------------------
long FUNCTYPE DeletePoints (HPROJECT hPr, long lPunkt) 
{
DB_ADDR dbaSPL(hPr);
ErrCode RC;	// FehlerCode

	if (VERSION05000010 <= GetDBVersion(hPr)) {
	struct longspl SPLSatz;

		dbaSPL.file_no = SPL_NEW;
		dbaSPL.rec_no = lPunkt;

	// jetzt einfach alles freigeben
		while (dbaSPL.rec_no > 0) {
			__Read (dbaSPL, SPLSatz);		// Satz lesen
			__Dispose (dbaSPL);		// freigeben
			dbaSPL.rec_no = SPLSatz.znspl;	// nächster Satz
		}
		return EC_OKAY;
	}

// ansonsten mit alter Struktur arbeiten
struct spl SPLSatz;

	dbaSPL.file_no = SPL_OLD;
	dbaSPL.rec_no = lPunkt;
	while (dbaSPL.rec_no > 0) {
		__Read (dbaSPL, SPLSatz);		// Satz lesen
		__Dispose (dbaSPL);		// freigeben
		dbaSPL.rec_no = SPLSatz.znsp;	// nächster Satz
	}
	return S_OKAY;
}

// Behandeln eines Knotenpunktes ----------------------------------------------
long FUNCTYPE DeleteNode (HPROJECT hPr, long Node, long Kante) 
{
struct kpl KPLSatz;
DB_ADDR dbaKPL(hPr);
long RC;	// FehlerCode

// EInlesen des KnotenSatzes
	dbaKPL.file_no = KPL;
	dbaKPL.rec_no = Node;
	__Read (dbaKPL, KPLSatz);

// Herauslöschen der Kante aus Kantenfolge
	DBASSERT (DelLink (hPr, KFK, &KPLSatz.zkpkfk, Kante));
	if (KPLSatz.zkpkfk != 0) {
	// es sind noch Kanten auf diesem KnotenPunkt
		__Write (dbaKPL, KPLSatz);
	} else if (KPLSatz.zkpvgo != 0) {
	// es war die letzte Kante, aber es sitzt noch ein PunktO drauf
		__Write (dbaKPL, KPLSatz);
	} else {
	// das war die letzte Kante dieses Knotens, und kein PunktO mehr
		__Dispose (dbaKPL);
	}

return S_OKAY;
}
