// Einspeichern von Merkmalen (Merkmalswerten) in die DB
// File: PUTMIN.C

#include "trias02p.hxx"

// RoutinenKode
#define RoutCD  	2030

extern "C" long EXPORT02 FUNCTYPE PutMiTxt (long ON, long MKode, char *lpText) 
{
struct obl OBLSatz;
struct vom VOMSatz;
struct mkl MKLSatz;
DB_ADDR_OBL dbaOBL;
DB_ADDR dbaVOM;
DB_ADDR dbaMKL;
long VOMPrev = 0;       // vorhergehender VOMSatz
long VOMNext;           // nächster Satz
long RC;		// FehlerVariable

// Objektsatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	__Read (dbaOBL, OBLSatz);

// Verbindungsdatei zu Merkmalen (VOM) einlesen und überprüfen, ob dieses
// Objekt den gewünschten MKode bereits besitzt
	dbaVOM.file_no = VOM;
	dbaMKL.file_no = MKL;
	dbaVOM.rec_no = 0;
	VOMNext = OBLSatz.zovom;        // erster Satz

	do {
	// VOMSatz lesen
//		VOMPrev = dbaVOM.rec_no;
		if (VOMNext == 0)
			break;		// Objekt hat diesen MKode nicht
		VOMPrev = dbaVOM.rec_no;
		dbaVOM.rec_no = VOMNext;
		__Read (dbaVOM, VOMSatz);
	// MKLSatz lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__Read (dbaMKL, MKLSatz);
	// nächster VOMSatz
		VOMNext = VOMSatz.znmk;
	} while (MKLSatz.mk != MKode);          // bis MKode gefunden

// wenn dieser MKode bereits belegt ist -> Fehler, da TextMerkmal
	if (VOMNext != 0) 
		return db_error (WC_MCODEEXISTS, RoutCD);

// alles OK, VMOSatz bilden, MKLSatz bilden, VOMSatz bilden
	if ((RC = putvbd (VMO, &MKLSatz.zmkvmo, ON)) != S_OKAY) return RC;

	MKLSatz.typ = 0;	// TextMerkmal
	MKLSatz.mk = MKode;	// MerkmalsCode
	New (dbaMKL, MKLSatz);		// neuen MKLSatz bilden

	if (dbaVOM.rec_no == 0) {
	// erstes Merkmal dieses Objektes
		OBLSatz.zovom = dbaMKL.rec_no;
		Write (dbaOBL, OBLSatz);	// ObjektSatz modifizieren
	} else {
	// nicht erstes Merkmal
		Read (dbaVOM, VOMSatz);		// letzten VOMSatz einlesen
		VOMSatz.zvommk = dbaMKL.rec_no;
		New (dbaVOM, VOMSatz);
		dbaVOM.rec_no = VOMPrev;
		New (dbaVOM)
	}
}
