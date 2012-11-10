// Loeschen eines ausgewaehlten Merkmales fuer ein Objekt
// File: DELMI.C

#include "trias02p.hxx"

// RoutinenKode
#define RoutCD  	2030
#define E_NOVOM 	-109

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

extern "C" 
BOOL EXPORT02 IsEmptyIDL (HPROJECT hPr, struct idl *pIdl)
{
	TX_ASSERT(NULL != pIdl);

	if (0 != pIdl->zmerki || 0 != pIdl->zrelid || 0 != pIdl->zvio)
		return FALSE;

	if (VERSION0500000E <= GetDBVersion (hPr)) {
		if (0 != pIdl->zpvio || 0 != pIdl->zlvio || 0 != pIdl->zfvio || 0 != pIdl->ztvio || 0 != pIdl->zkvio)
			return FALSE;
	}
	return TRUE;
}

// löscht einen bestimmten MerkmalsCode (-Wert) für das vorgegebene Objekt,
// Identifikator oder Sicht.
// Ist MKode == -1L, dann wird der erste (und beste) MerkmalsCode gelöscht.
extern "C" 
long EXPORT02 FUNCTYPE delmi (HPROJECT hPr, long MKode, long lTarget, short iTyp) 
{
struct vom VOMSatz;
struct mkl MKLSatz;
struct idl IDLSatz;
struct obl OBLSatz;
struct sicht SICHTSatz;
DB_ADDR dbaSICHT(hPr);
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR dbaIDL(hPr);
DB_ADDR dbaVOM(hPr);
DB_ADDR dbaMKL(hPr);
long VOMPrev = 0;       // vorhergehender VOMSatz
long VOMNext;           // nächster Satz
long zvommi = 0;        // Zeiger auf MISatz
long RC;                 // FehlerVariable
bool fText = false;

	switch (iTyp) {
	case OBL_OLD:
		{
		// Objektsatz einlesen
//			dbaOBL.file_no = OBL;
			dbaOBL.rec_no = lTarget;
			__Read (dbaOBL, OBLSatz);

		// wenn das Objekt ein Textobjekt ist, und eine alte
		// Datenbasis vorliegt, dann nur Text löschen und raus
			if (OBLSatz.status & SB_TEXTOBJ &&
			    GetDBVersion(hPr) < VERSION05000008) {
				DBASSERT (DelText (hPr, OBLSatz.zovom));
				OBLSatz.status &= ~SB_TEXTOBJ;	// kein TextObjekt mehr
				__Write (dbaOBL, OBLSatz);
				return S_DUMMY;		// letztes Merkmal gelöscht
			}

			if (OBLSatz.status & SB_TEXTOBJIND)
				fText = true;

			VOMNext = OBLSatz.zovom;        // erster Satz
		}
		break;

	case IDL:
		{
			if (GetDBVersion(hPr) < VERSION05000007) return S_DUMMY;

			dbaIDL.file_no = IDL;
			dbaIDL.rec_no = lTarget;
			__Read (dbaIDL, IDLSatz);

			VOMNext = IDLSatz.zmerki;
			lTarget |= IDL_MERKMAL;
		}
		break;

	case SICHT:
		{
			if (GetDBVersion(hPr) < VERSION05000007) return S_DUMMY;

			dbaSICHT.file_no = SICHT;
			dbaSICHT.rec_no = lTarget;
			__Read (dbaSICHT, SICHTSatz);

			VOMNext = SICHTSatz.zmerkm;
			lTarget |= SICHT_MERKMAL;
		}
		break;

	default:
		return S_DUMMY;
	}

// Verbindungsdatei zu Merkmalen (VOM) einlesen und entspr. Satz finden
	dbaVOM.file_no = VOM;
	dbaMKL.file_no = MKL;
	dbaVOM.rec_no = 0;

	if (MKode != -1L) {
		do {
		// VOMSatz lesen
			VOMPrev = dbaVOM.rec_no;
			if ((dbaVOM.rec_no = VOMNext) == 0)
				return S_OKAY; // db_error (E_NOVOM, RoutCD);
			__Read (dbaVOM, VOMSatz);
		// MKLSatz lesen
			dbaMKL.rec_no = VOMSatz.zvommk;
			__Read (dbaMKL, MKLSatz);
		// nächster VOMSatz
			VOMNext = VOMSatz.znmk;
		} while (MKLSatz.mk != MKode);          // bis MKode gefunden
	} else {
	// ersten MerkmalsKode löschen
	// VOMSatz lesen
		VOMPrev = dbaVOM.rec_no;
		if ((dbaVOM.rec_no = VOMNext) == 0) return S_DUMMY;
		__Read (dbaVOM, VOMSatz);
	// MKLSatz lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__Read (dbaMKL, MKLSatz);
	// nächster VOMSatz
		VOMNext = VOMSatz.znmk;	
	}

	DEX_SetDirtyGeoDB (true);

// VOMSatz aus Kette herauslöschen
	zvommi = VOMSatz.zvommi;
	__Dispose (dbaVOM);  // VOMSatz freigeben
	if (VOMPrev == 0) {
	// 1. Satz in der Kette
		switch (iTyp) {
		case OBL_OLD:
			OBLSatz.zovom = VOMNext;        // Zeiger umhängen
			__Write (dbaOBL, OBLSatz);
			break;

		case IDL:
			{
			// wenn das das letzte Merkmal war und keine Relationen bzw. Objekte
			// mehr existieren, dann kann dieser IDLSatz freigegeben werden
			// (seit ObjektKlasenschlüsseln können IDLSätze ohne Objekte existieren)
				IDLSatz.zmerki = VOMNext;
				if (IsEmptyIDL (hPr, &IDLSatz)) {
					__Dispose (dbaIDL);
				} 
				else {
					__Write (dbaIDL, IDLSatz);
				}
			}
			break;

		case SICHT:
			SICHTSatz.zmerkm = VOMNext;
			__Write (dbaSICHT, SICHTSatz);
			break;
		}
	} else {
	// Mittendrin oder Letzter Satz in Kette
		dbaVOM.rec_no = VOMPrev;
		__Read (dbaVOM, VOMSatz);
		VOMSatz.znmk = VOMNext;
		__Write (dbaVOM, VOMSatz);
	}
	

// löschen MerkmalsInfo
	if (MKLSatz.typ == 0) {                         // TextInfo
		DBASSERT (DelText (hPr, zvommi, fText));
	} else {
	// sonstiges Merkmal
	DB_ADDR dbaMI(hPr);
	struct mi MISatz;

		dbaMI.file_no = MI;
		dbaMI.rec_no = zvommi;
		do {
		// MerkmalsInfo einlesen
			__Read (dbaMI, MISatz);
		// Freigeben dieses Satzes
			__Dispose (dbaMI);
			dbaMI.rec_no = MISatz.znmi;
		} while (dbaMI.rec_no != 0);
	}

// Hat sonst noch ein Objekt dieses Merkmal - Nein, dann MKL löschen
// ON aus Verbindungsdatei VMO löschen
	DBASSERT (DelLinkVMO (hPr, &MKLSatz.zmkvmo, lTarget, MKode));
	if (MKLSatz.zmkvmo == 0) {
	// einziges Objekt --> MKL freigeben
		__Dispose (dbaMKL);
	} else {
	// modifizierten Satz wegschreiben
		__Write (dbaMKL, MKLSatz);
	}

return S_OKAY;
}


// Löschen eines MerkmalsTextes aus der DBT - Datei ---------------------------
extern "C" long FUNCTYPE EXPORT02 DelText (HPROJECT hPr, long First, BOOL fText) 
{
DB_ADDR dbaDBT(hPr);
struct fdbt DBTSatz;
long RC;

	dbaDBT.file_no = ((GetDBVersion(hPr) < VERSION0500000B) || fText) ? FDBT : KDBT;
	dbaDBT.rec_no = First;
	do {
		__Read (dbaDBT, DBTSatz);	// TextSatz einlesen
		__Dispose (dbaDBT);	// Freigeben dieses Satzes

		dbaDBT.file_no = FDBT;		// FolgeSatz
		dbaDBT.rec_no = DBTSatz.zndbtf;
	} while (dbaDBT.rec_no != 0);           // alle Sätze freigeben

return S_OKAY;
}
