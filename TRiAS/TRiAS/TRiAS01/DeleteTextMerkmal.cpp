// @doc
// @module DeleteTextMerkmal.cpp | Löschen eines ausgewaehlten Merkmales fuer ein Objekt

#include "trias01p.hxx"
#include <NativeObject.h>

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

HRESULT DeleteLink (HPROJECT hPr, long FileNo, long *Begin, long Wert) 
{
DB_ADDR dba(hPr);
long Data[4];
long Prev = 0;
long Next; 
long RC;	// FehlerCode

// ersten Satz einlesen
	dba.file_no = FileNo;
	dba.rec_no = 0;
	Next = *Begin;

// Suche des vorgegebenen Wertes
	do {
		Prev = dba.rec_no;
		if ((dba.rec_no = Next) <= 0)
		// nichts gefunden --> raus
			return HRESULT_FROM_ERRCODE(S_NOTFOUND);

	// Satz aus VerbindungsDatei einlesen
		__ReadHREx (dba, Data[0]);

	// nächster Satz
		Next = Data[1];
	} while (labs (Data[0]) != Wert);

// gefundenen Satz der VerbindungsDatei freigeben
	__DisposeHREx (dba);
	if (Prev == 0) {
	// der gesuchte Wert ist der Erste
		*Begin = Data[1];	// nächster Satz
		return S_OK;
	} else {
	// VerbindungsKette umhängen (letzter oder in der Mitte)
		dba.rec_no = Prev;
		__ReadHREx (dba, Data[0]);
		Data[1] = Next;
		__WriteHREx (dba, Data[0]);
	}
	return S_OK;
}

HRESULT DeleteLinkVMO (HPROJECT hPr, long *pBegin, long lWert, long lMCode) 
{
long lVersion = LocGetDBVersion(hPr);

	if (VERSION0500000F <= lVersion) {
	// Rückverkettung Merkmal --> Objekt ist jetzt indiziert (MCODEBSatz)
	DB_ADDR dbaMCODEB (hPr);
	struct mcodeb VMOSatz;
	long RC;

		dbaMCODEB.file_no = VMO_NEW;
		if (VERSION05000011 <= lVersion) {
		// jetzt mit getauschten Feldern
		struct mcodex::mcodexkey keyx;

			keyx.zvmoox = lWert;
			keyx.mcodex = lMCode;

		// versuchen den VerbindungsSatz wiederzufinden
			DBASSERTHR(z_keyfind (&dbaMCODEB, MCODEX, &keyx));

		} else {
		// ursprüngliche Feldanordnung
		struct mcodeb::mcodebkey key;

			key.zvmook = lWert;
			key.mcodek = lMCode;

		// versuchen den VerbindungsSatz wiederzufinden
			DBASSERTHR(z_keyfind (&dbaMCODEB, MCODEB, &key));
		}

		__ReadHR (dbaMCODEB, VMOSatz);

	long lPrev = VMOSatz.zvmopk;
	long lNext = VMOSatz.zvmonk;

#if defined(_DEBUG)
	long lCurrent = dbaMCODEB.rec_no;
#endif // _DEBUG

		__DisposeHR(dbaMCODEB, VMOSatz);	// aktuellen Satz freigeben

	// vorhergehenden Satz lesen, korrigieren und wegschreiben
		if (0 != lPrev) {
			dbaMCODEB.rec_no = lPrev;
			__ReadHR(dbaMCODEB, VMOSatz);
		
			TX_ASSERT(VMOSatz.zvmonk == lCurrent);
			VMOSatz.zvmonk = lNext;
			__WriteHR(dbaMCODEB, VMOSatz);
		} else
			*pBegin = lNext;

	// nachfolgenden Satz lesen, korrigieren und wegschreiben
		if (0 != lNext) {
			dbaMCODEB.rec_no = lNext;
			__ReadHR(dbaMCODEB, VMOSatz);
		
			TX_ASSERT(VMOSatz.zvmopk == lCurrent);
			VMOSatz.zvmopk = lPrev;
			__WriteHR(dbaMCODEB, VMOSatz);
		}
		return S_OK;
	}

// ansonsten alles beim Alten
	return DeleteLink (hPr, VMO_OLD, pBegin, lWert);
}

/////////////////////////////////////////////////////////////////////////////
// 
BOOL IDLRecIsEmpty (HPROJECT hPr, struct idl *pIdl)
{
	TX_ASSERT(NULL != pIdl);
	if (0 != pIdl->zmerki || 0 != pIdl->zrelid || 0 != pIdl->zvio)
		return FALSE;

	if (VERSION0500000E <= LocGetDBVersion (hPr)) {
		if (0 != pIdl->zpvio || 0 != pIdl->zlvio || 0 != pIdl->zfvio || 0 != pIdl->ztvio || 0 != pIdl->zkvio)
			return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 
BOOL IDLRecHasObjects (HPROJECT hPr, struct idl *pIdl)
{
	TX_ASSERT(NULL != pIdl);
	if (0 != pIdl->zvio)
		return FALSE;

	if (VERSION0500000E <= LocGetDBVersion (hPr)) {
		if (0 != pIdl->zpvio || 0 != pIdl->zlvio || 0 != pIdl->zfvio || 0 != pIdl->ztvio || 0 != pIdl->zkvio)
			return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Löschen eines MerkmalsTextes aus der DBT - Datei 
HRESULT DeleteTextFromDBT (HPROJECT hPr, long First, BOOL fText) 
{
DB_ADDR dbaDBT(hPr);
struct fdbt DBTSatz;
long RC;

	dbaDBT.file_no = (LocGetDBVersion(hPr) < VERSION0500000B) ? FDBT : KDBT;
	dbaDBT.rec_no = First;
	do {
		__ReadHR (dbaDBT, DBTSatz);	// TextSatz einlesen
		__DisposeHR (dbaDBT, DBTSatz);		// Freigeben dieses Satzes

		dbaDBT.file_no = FDBT;		// FolgeSatz
		dbaDBT.rec_no = DBTSatz.zndbtf;
	} while (dbaDBT.rec_no != 0);           // alle Sätze freigeben
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// löscht einen bestimmten MerkmalsCode (-Wert) für das vorgegebene Objekt,
// Identifikator oder Sicht.
// Ist MKode == -1L, dann wird der erste (und beste) MerkmalsCode gelöscht.
HRESULT DeleteTextMerkmal (HPROJECT hPr, long MKode, long lTarget, short iTyp, BOOL fTextMCode) 
{
struct vom VOMSatz;
struct mkl MKLSatz;
struct idl IDLSatz;
struct obl OBLSatz;
struct sicht SICHTSatz;
DB_ADDR dbaSICHT(hPr);
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR_IDL dbaIDL(hPr);
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
			__ReadHR (dbaOBL, OBLSatz);

		// wenn das Objekt ein Textobjekt ist, und eine alte
		// Datenbasis vorliegt, dann nur Text löschen und raus
			if (OBLSatz.status & SB_TEXTOBJ &&
			    LocGetDBVersion(hPr) < VERSION05000008) 
			{
				RETURN_FAILED_HRESULT(DeleteTextFromDBT (hPr, OBLSatz.zovom, FALSE));
				OBLSatz.status &= ~SB_TEXTOBJ;	// kein TextObjekt mehr
				__WriteHR (dbaOBL, OBLSatz);
				return S_FALSE;					// letztes Merkmal gelöscht
			}

			if ((OBLSatz.status & SB_TEXTOBJIND) && fTextMCode)
				fText = true;
			VOMNext = OBLSatz.zovom;        // erster Satz
		}
		break;

	case IDL_OLD:
		{
			if (LocGetDBVersion(hPr) < VERSION05000007) 
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
			if (LocGetDBVersion(hPr) < VERSION05000007) 
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
			__ReadHR (dbaVOM, VOMSatz);
		
		// MKLSatz lesen
			dbaMKL.rec_no = VOMSatz.zvommk;
			__ReadHR (dbaMKL, MKLSatz);
		
		// nächster VOMSatz
			VOMNext = VOMSatz.znmk;
		} while (MKLSatz.mk != MKode);          // bis MKode gefunden
	} else {
	// ersten MerkmalsKode löschen
	// VOMSatz lesen
		VOMPrev = dbaVOM.rec_no;
		if ((dbaVOM.rec_no = VOMNext) == 0) 
			return S_FALSE;
		__ReadHR (dbaVOM, VOMSatz);
	
	// MKLSatz lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__ReadHR (dbaMKL, MKLSatz);
		
		MKode = MKLSatz.mk;		// MCode rauslesen (wird weiter unter benötigt)

	// nächster VOMSatz
		VOMNext = VOMSatz.znmk;	
	}

	SetDirty (hPr, true);

// VOMSatz aus Kette herauslöschen
	zvommi = VOMSatz.zvommi;
	__DisposeHR (dbaVOM, VOMSatz);  // VOMSatz freigeben
	if (VOMPrev == 0) {
	// 1. Satz in der Kette
		switch (iTyp) {
		case OBL_OLD:
			OBLSatz.zovom = VOMNext;        // Zeiger umhängen
			__WriteHR (dbaOBL, OBLSatz);
			break;

		case IDL_OLD:
			{
			// wenn das das letzte Merkmal war und keine Relationen bzw. Objekte
			// mehr existieren, dann kann dieser IDLSatz freigegeben werden
			// (seit ObjektKlassenschlüsseln können IDLSätze ohne Objekte existieren)
				IDLSatz.zmerki = VOMNext;
				if (IDLRecIsEmpty (hPr, &IDLSatz)) {
					__DisposeHR (dbaIDL, IDLSatz);
				} 
				else {
					__WriteHR (dbaIDL, IDLSatz);
				}
			}
			break;

		case SICHT:
			SICHTSatz.zmerkm = VOMNext;
			__WriteHR (dbaSICHT, SICHTSatz);
			break;
		}
	} else {
	// Mittendrin oder Letzter Satz in Kette
		dbaVOM.rec_no = VOMPrev;
		__ReadHR (dbaVOM, VOMSatz);
		VOMSatz.znmk = VOMNext;
		__WriteHR (dbaVOM, VOMSatz);
	}
	
// löschen MerkmalsInfo
	if (MKLSatz.typ == 0) {                         // TextInfo
		RETURN_FAILED_HRESULT(DeleteTextFromDBT (hPr, zvommi, fText));
	} else {
	// sonstiges Merkmal
	DB_ADDR dbaMI(hPr);
	struct mi MISatz;

		dbaMI.file_no = MI;
		dbaMI.rec_no = zvommi;
		do {
		// MerkmalsInfo einlesen
			__ReadHR (dbaMI, MISatz);
		
		// Freigeben dieses Satzes
			__DisposeHR (dbaMI, MISatz);
			dbaMI.rec_no = MISatz.znmi;
		} while (dbaMI.rec_no != 0);
	}

// Hat sonst noch ein Objekt dieses Merkmal - Nein, dann MKL löschen
// ON aus Verbindungsdatei VMO löschen
	RETURN_FAILED_HRESULT(DeleteLinkVMO (hPr, &MKLSatz.zmkvmo, lTarget, MKode));
	if (MKLSatz.zmkvmo == 0) {
	// einziges Objekt --> MKL freigeben
		__DisposeHR (dbaMKL, MKLSatz);
	} else {
	// modifizierten Satz wegschreiben
		__WriteHR (dbaMKL, MKLSatz);
	}
	return S_OK;
}

