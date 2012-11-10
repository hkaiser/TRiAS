// @doc
// @module PutTextMerkmal.cpp | Schreiben eines ausgewaehlten TextMerkmales fuer ein Objekt

#include "trias01p.hxx"
#include <NativeObject.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PUTLINK erzeugt einen neuen Satz am Kopf einer gegebenen VerbindungsKette.
HRESULT CreateLink (HPROJECT hPr, long FileNo, long *Begin, long Wert) 
{
DB_ADDR dba(hPr);	// neue Datenbankadresse
long Data[4];
ErrCode RC;	// FehlerCode 

// Neuen Satz erzeugen und am Anfang der gegebenen Kette einfügen
	dba.file_no = (short)FileNo;

// Satz neu zusammensetzen
	Data[0] = Wert;		// TargetSatz eintragen
	Data[1] = *Begin;	// altes erstes Element
	Data[2] = 0;		// evtl. drittes/viertes Element ausnullen
	Data[3] = 0;

// Satz neu bilden
	*Begin = 0;		// für alle Fälle Nullsetzen
	__NewHREx(dba, Data);	// Satz neu anfordern
	*Begin = dba.rec_no;	// neues erstes Element
	return S_OKAY;
}

/////////////////////////////////////////////////////////////////////////////
// PUTLINK erzeugt einen neuen Satz am Kopf einer gegebenen VerbindungsKette.
static HRESULT CreateLinkVMO (HPROJECT hPr, long *pBegin, long lWert, long lMCode) 
{
long lVersion = LocGetDBVersion(hPr);

	if (VERSION0500000F <= lVersion) {
	// Rückverkettung Merkmal --> Objekt ist jetzt indiziert (MCODEBSatz)
	DB_ADDR dbaMCODEB (hPr);
	long RC;

		if (VERSION05000011 <= lVersion) {
		// Elemente im Key jetzt getauscht
		struct mcodex MCODEBSatz;

			dbaMCODEB.file_no = VMO_NEW;
			MCODEBSatz.mcodexkey.zvmoox = lWert;		// TargetSatz 
			MCODEBSatz.mcodexkey.mcodex = lMCode;		// MerkmalsCode
			MCODEBSatz.zvmonk = *pBegin;	// altes erstes Element
	//		MCODEBSatz.zvmopk = 0L;			// vorhergehendes Element existiert nicht
		
			*pBegin = 0;					// für alle Fälle Nullsetzen
			__NewHR (dbaMCODEB, MCODEBSatz);	// neues Satz generieren (incl. Index)
			*pBegin = dbaMCODEB.rec_no;		// neues erstes Element

			if (0 != MCODEBSatz.zvmonk) {
			// Rückverkettung eintragen
				dbaMCODEB.rec_no = MCODEBSatz.zvmonk;
				__ReadHR(dbaMCODEB, MCODEBSatz);

				TX_ASSERT(0 == MCODEBSatz.zvmopk);
				MCODEBSatz.zvmopk = *pBegin;
				__WriteHR(dbaMCODEB, MCODEBSatz);
			}
		} else {
		// bisherige Variante
		struct mcodeb MCODEBSatz;

			dbaMCODEB.file_no = VMO_NEW;
			MCODEBSatz.mcodebkey.zvmook = lWert;		// TargetSatz 
			MCODEBSatz.mcodebkey.mcodek = lMCode;		// MerkmalsCode
			MCODEBSatz.zvmonk = *pBegin;	// altes erstes Element
	//		MCODEBSatz.zvmopk = 0L;			// vorhergehendes Element existiert nicht

			*pBegin = 0;					// für alle Fälle Nullsetzen
			__NewHR (dbaMCODEB, MCODEBSatz);	// neues Satz generieren (incl. Index)
			*pBegin = dbaMCODEB.rec_no;		// neues erstes Element

			if (0 != MCODEBSatz.zvmonk) {
			// Rückverkettung eintragen
				dbaMCODEB.rec_no = MCODEBSatz.zvmonk;
				__ReadHR(dbaMCODEB, MCODEBSatz);

				TX_ASSERT(0 == MCODEBSatz.zvmopk);
				MCODEBSatz.zvmopk = *pBegin;
				__WriteHR(dbaMCODEB, MCODEBSatz);
			}
		}
		return S_OK;
	}

// ansonsten alles beim Alten
	return CreateLink (hPr, VMO_OLD, pBegin, lWert);
}

/////////////////////////////////////////////////////////////////////////////
// Schreibt ein TextMerkmal für das vorgegebene Objekt.
HRESULT PutTextMerkmal (
	HPROJECT hPr, long MKode, long lTarget, short iTyp, const char *pMText, BOOL fTextMCode) 
{
struct obl OBLSatz;
struct vom VOMSatz;
struct mkl MKLSatz;
struct idl IDLSatz;
struct sicht SICHTSatz;
DB_ADDR_IDL dbaIDL(hPr);
DB_ADDR dbaSICHT(hPr);
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR dbaVOM(hPr);
DB_ADDR dbaMKL(hPr);
long VOMPrev = 0;       // vorhergehender VOMSatz
long VOMNext;           // nächster Satz
long zvommi = 0;        // Zeiger auf MISatz
long RC;                // FehlerVariable
bool fText = false;
long lVersion = LocGetDBVersion(hPr);

	switch (iTyp) {
	case OBL_OLD:
		{
		// Objektsatz einlesen
//			dbaOBL.file_no = OBL;
			dbaOBL.rec_no = lTarget;
			__ReadHR (dbaOBL, OBLSatz);

			if (lVersion < VERSION05000008 && OBLSatz.status & SB_TEXTOBJ)
			// alte DB und Textobjekt
				return S_OK;

			if ((OBLSatz.status & SB_TEXTOBJIND) && fTextMCode)
				fText = true;

			VOMNext = OBLSatz.zovom;        // erster Satz
		}
		break;

	case IDL_OLD:
		{
			if (lVersion < VERSION05000007) 
				return S_FALSE;

//			dbaIDL.file_no = IDL;
			dbaIDL.rec_no = lTarget;
			__ReadHR (dbaIDL, IDLSatz);
			VOMNext = IDLSatz.zmerki;

			lTarget |= IDL_MERKMAL;
		}
		break;

	case SICHT:
		{
			if (lVersion < VERSION05000007) 
				return S_FALSE;

			dbaSICHT.file_no = SICHT;
			dbaSICHT.rec_no = lTarget;
			__ReadHR (dbaSICHT, SICHTSatz);
			VOMNext = SICHTSatz.zmerkm;

			lTarget |= SICHT_MERKMAL;
		}
		break;

	default:
		return E_INVALIDARG;
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
		__ReadHR (dbaVOM, VOMSatz);

	// MKLSatz lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__ReadHR (dbaMKL, MKLSatz);

	// nächster VOMSatz
		VOMNext = VOMSatz.znmk;
	} while (MKLSatz.mk != MKode);          // bis MKode gefunden

// wenn für dieses Objekt MCode exitiert: wieder raus mit Warnung
	if (MKLSatz.mk == MKode)
		return HRESULT_FROM_ERRCODE(S_MKODEEXISTS);

	SetDirty (hPr, true);

// überprüfen, ob dieser MKode überhaupt schon existiert
	{
	int (*w_notfound)(int, int, ...);

	// Fehlermeldung unterdrücken
		DBASSERTHR (err_install (S_NOTFOUND, E_IGNORE, &w_notfound));

	// MKode als Schlüssel suchen und ggf. neuen Schlüsseleintrag machen
		if ((RC = (ErrCode)z_keyfind (&dbaMKL, MK, &MKode)) != S_OKAY) {
		long EC = RC;

			DBASSERTHR (err_install (S_NOTFOUND, w_notfound, NULL));
			if (EC == S_NOTFOUND) {
			// MKode existiert noch nicht
				memset (&MKLSatz, '\0', sizeof(MKLSatz));
				MKLSatz.typ = 0;	// TextInformation
				MKLSatz.mk = MKode;	// MerkmalsCode
				__NewHR (dbaMKL, MKLSatz);
			} else 
				return EC;	// Fehler
		} else {
		// MKode existiert bereits, einlesen
		// Fehlermeldung wieder zuschalten
			DBASSERTHR (err_install (S_NOTFOUND, w_notfound, NULL));
			__ReadHR (dbaMKL, MKLSatz);
		
		// Prüfen, ob MerkmalsTyp stimmt
			if (MKLSatz.typ != 0)
			// kein TextMerkmal
				return HRESULT_FROM_ERRCODE(S_BADMKTYP);
		}
	}

// jetzt wirklich MerkmalsInfo zusammensetzen
// TextInfo wegschreiben
	memset (&VOMSatz, '\0', sizeof(VOMSatz));	// wegen Versionen ausnullen
	__NewHR (dbaVOM, VOMSatz);	// neuen VOMSatz erzeugen

char *pText = NULL;

	try {
		ATLTRY(pText = new char[strlen(pMText)+1]);
		if (NULL == pText)
			return E_OUTOFMEMORY;

		AnsiToOem (pMText, pText);
		THROW_FAILED_HRESULT(PutTextToDBT (hPr, pText, (strlen (pText) +3)/4, &VOMSatz.zvommi, dbaVOM.rec_no, fText));

	} catch (_com_error &e) {
		DELETE_VEC(pText);
		return _COM_ERROR(e);
	}
	DELETE_VEC(pText);

// Verbindung zu Objekten herstellen, MKLSatz vervollständigen
	DBASSERTHR (CreateLinkVMO (hPr, &MKLSatz.zmkvmo, lTarget, MKode));
	__WriteHR (dbaMKL, MKLSatz);	// korrigierten MKLSatz wegschreiben

// VOMSatz vervollständigen
	VOMSatz.zvommk = dbaMKL.rec_no;	// MerkmalsKodeSatz

// neuen VOMSatz am Anfang der VOMKette einfügen
	switch (iTyp) {
	case OBL_OLD:
		VOMSatz.znmk = OBLSatz.zovom;
		if (lVersion >= VERSION0500000B)
			VOMSatz.zvomo = dbaOBL.rec_no;		// Rückverweis eintragen
		__WriteHR (dbaVOM, VOMSatz);
		OBLSatz.zovom = dbaVOM.rec_no;
		__WriteHR (dbaOBL, OBLSatz);	// ObjektSatz wieder wegschreiben
		break;

	case IDL_OLD:
		VOMSatz.znmk = IDLSatz.zmerki;
		if (lVersion >= VERSION0500000B)	// Rückverweis eintragen
			VOMSatz.zvomo = dbaIDL.rec_no | IDL_MERKMAL;
		__WriteHR (dbaVOM, VOMSatz);
		IDLSatz.zmerki = dbaVOM.rec_no;
		__WriteHR (dbaIDL, IDLSatz);
		break;

	case SICHT:
		VOMSatz.znmk = SICHTSatz.zmerkm;
		if (lVersion >= VERSION0500000B)	// Rückverweis eintragen
			VOMSatz.zvomo = dbaSICHT.rec_no | SICHT_MERKMAL;
		__WriteHR (dbaVOM, VOMSatz);
		SICHTSatz.zmerkm = dbaVOM.rec_no;
		__WriteHR (dbaSICHT, SICHTSatz);
		break;
	}
	return S_OK;
}

