// Schreiben eines ausgewaehlten TextMerkmales fuer ein Objekt
// File: PUTMIT.C

#include "trias02p.hxx"

// RoutinenKode
#define RC_PutMiTxt  	1020

// Schreibt ein TextMerkmal für das vorgegebene Objekt.
long FUNCTYPE EXPORT02 PutMiText (
	HPROJECT hPr, long MKode, long lTarget, short iTyp, char *MText, BOOL fTextMCode) 
{
struct obl OBLSatz;
struct vom VOMSatz;
struct mkl MKLSatz;
struct idl IDLSatz;
struct sicht SICHTSatz;
DB_ADDR dbaIDL(hPr);
DB_ADDR dbaSICHT(hPr);
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR dbaVOM(hPr);
DB_ADDR dbaMKL(hPr);
long VOMPrev = 0;       // vorhergehender VOMSatz
long VOMNext;           // nächster Satz
long zvommi = 0;        // Zeiger auf MISatz
ErrCode RC;                // FehlerVariable
bool fText = false;
long lVersion = GetDBVersion(hPr);

	switch (iTyp) {
	case OBL_OLD:
		{
		// Objektsatz einlesen
//			dbaOBL.file_no = OBL;
			dbaOBL.rec_no = lTarget;
			__Read (dbaOBL, OBLSatz);

			if (lVersion < VERSION05000008 && OBLSatz.status & SB_TEXTOBJ)
			// alte DB und Textobjekt
				return S_OKAY;

			if (OBLSatz.status & SB_TEXTOBJIND && fTextMCode)
				fText = true;

			VOMNext = OBLSatz.zovom;        // erster Satz
		}
		break;

	case IDL:
		{
			if (lVersion < VERSION05000007) return S_OKAY;

			dbaIDL.file_no = IDL;
			dbaIDL.rec_no = lTarget;
			__Read (dbaIDL, IDLSatz);
			VOMNext = IDLSatz.zmerki;

			lTarget |= IDL_MERKMAL;
		}
		break;

	case SICHT:
		{
			if (lVersion < VERSION05000007) return S_OKAY;

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

// Verbindungsdatei zu Merkmalen (VOM) lesen und entspr. Satz suchen
	dbaVOM.file_no = VOM;
	dbaMKL.file_no = MKL;
	dbaVOM.rec_no = 0;

	do {
	// VOMSatz lesen
		VOMPrev = dbaVOM.rec_no;
		if ((dbaVOM.rec_no = VOMNext) == 0)
			break;	// Ende der Kette: MCode nicht vorhanden
		__Read (dbaVOM, VOMSatz);
	// MKLSatz lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__Read (dbaMKL, MKLSatz);
	// nächster VOMSatz
		VOMNext = VOMSatz.znmk;
	} while (MKLSatz.mk != MKode);          // bis MKode gefunden

// wenn für dieses Objekt MCode exitiert: wieder raus mit Warnung
	if (MKLSatz.mk == MKode)
		return db_error (S_MKODEEXISTS, RC_PutMiTxt);

	DEX_SetDirtyGeoDB (true);

// überprüfen, ob dieser MKode überhaupt schon existiert
	{
	int (*w_notfound)(int, int, ...);

	// Fehlermeldung unterdrücken
		DBASSERT (err_install (S_NOTFOUND, E_IGNORE, &w_notfound));

	// MKode als Schlüssel suchen und ggf. neuen Schlüsseleintrag machen
		if ((RC = (ErrCode)z_keyfind (&dbaMKL, MK, &MKode)) != S_OKAY) {
		ErrCode EC = RC;

			DBASSERT (err_install (S_NOTFOUND, w_notfound, NULL));
			if (EC == S_NOTFOUND) {
			// MKode existiert noch nicht
				memset (&MKLSatz, '\0', sizeof(MKLSatz));
				MKLSatz.typ = 0;	// TextInformation
				MKLSatz.mk = MKode;	// MerkmalsCode
				__New (dbaMKL, MKLSatz);
			} else 
				return EC;	// Fehler
		} else {
		// MKode existiert bereits, einlesen
		// Fehlermeldung wieder zuschalten
			DBASSERT (err_install (S_NOTFOUND, w_notfound, NULL));
			__Read (dbaMKL, MKLSatz);
		// Prüfen, ob MerkmalsTyp stimmt
			if (MKLSatz.typ != 0)
			// kein TextMerkmal
				return db_error (S_BADMKTYP, RC_PutMiTxt);
		}
	}

// jetzt wirklich MerkmalsInfo zusammensetzen
// TextInfo wegschreiben
	memset (&VOMSatz, '\0', sizeof(VOMSatz));	// wegen Versionen ausnullen
	__New (dbaVOM, VOMSatz);	// neuen VOMSatz erzeugen
	DBASSERT (PutTextEx (hPr, MText, (strlen (MText) +3)/4, &VOMSatz.zvommi, dbaVOM.rec_no, fText));

// Verbindung zu Objekten herstellen, MKLSatz vervollständigen
	DBASSERT (PutLinkVMO (hPr, &MKLSatz.zmkvmo, lTarget, MKode));
	__Write (dbaMKL, MKLSatz);	// korrigierten MKLSatz wegschreiben

// VOMSatz vervollständigen
	VOMSatz.zvommk = dbaMKL.rec_no;	// MerkmalsKodeSatz

// neuen VOMSatz am Anfang der VOMKette einfügen
	switch (iTyp) {
	case OBL_OLD:
		VOMSatz.znmk = OBLSatz.zovom;
		if (lVersion >= VERSION0500000B)
			VOMSatz.zvomo = dbaOBL.rec_no;		// Rückverweis eintragen
		__Write (dbaVOM, VOMSatz);
		OBLSatz.zovom = dbaVOM.rec_no;
		__Write (dbaOBL, OBLSatz);	// ObjektSatz wieder wegschreiben
		break;

	case IDL:
		VOMSatz.znmk = IDLSatz.zmerki;
		if (lVersion >= VERSION0500000B)	// Rückverweis eintragen
			VOMSatz.zvomo = dbaIDL.rec_no | IDL_MERKMAL;
		__Write (dbaVOM, VOMSatz);
		IDLSatz.zmerki = dbaVOM.rec_no;
		__Write (dbaIDL, IDLSatz);
		break;

	case SICHT:
		VOMSatz.znmk = SICHTSatz.zmerkm;
		if (lVersion >= VERSION0500000B)	// Rückverweis eintragen
			VOMSatz.zvomo = dbaSICHT.rec_no | SICHT_MERKMAL;
		__Write (dbaVOM, VOMSatz);
		SICHTSatz.zmerkm = dbaVOM.rec_no;
		__Write (dbaSICHT, SICHTSatz);
		break;
	}

return S_OKAY;
}

