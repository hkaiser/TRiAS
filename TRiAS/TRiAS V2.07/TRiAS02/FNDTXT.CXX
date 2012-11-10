/*Translated by FOR_C, v3.1, on 06/27/91 at 18:17:41 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
/*+
 *       *****************************************************************
 *       * FUNCTION FNDTXT                                               *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: ?
 *       Autor:                Kurth,Klaus
 *       Datum:                12.06.91
 *       Aenderungsdatum:      12.06.91
 *       Modulname:            *** FNDTXT ***
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *                             Fkt.:gettxt
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=FNDTXT(NLP,MKO,TEXT,ONF)
 *       Parameter:            
 *               INPUT    MKO   - Merkmalskode
 *			  NLP   - Nachladeparameter
 *                        TEXT  - Textfeld
 *               OUTPUT   ONF   - Feld der gefundenen Objekte der DB
 *                        IRC   = EOKAY :  Funktion i.O.
 *
 *       Aufgabenstellung:
 *            Recherche nach einem Textfeld
 *            (spezielle Merkmalsinformationen eines Objekts)
 *
 *       Fehlerbehandlung:
 *               siehe Fehlerb. ZIPEDB
 *       -----------------------------------------------------------------
 *- */
#include "trias02p.hxx"

	/* PARAMETER translations */
#define	RoutCode	6070
	/* end of PARAMETER translations */

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C"
long FUNCTYPE FindPatternIndex (
	HPROJECT hPr, long lMCode, char *pPattern, short mode, long *pflObj)
{
// ansonsten alles beim Alten
DB_ADDR dbaMKL(hPr);
struct mkl MKLSatz;
long lTarget = 0;
char *pText = NULL;	// wegen DELETE()
ErrCode RC;

// AnfangsInitialisierung
	dbaMKL.file_no = MKL;

	if (*pflObj == 0) {
		DBASSERT (feini (pflObj));
	}

// Finden des MCodes 
	DBASSERT (z_keyfind (&dbaMKL, MK, &lMCode));
	__Read (dbaMKL, MKLSatz);		// MK-INF AUS MKL 
	if (MKLSatz.typ != 0) 			// kein Textmerkmal
		return db_error (ETYP, RoutCode);

DB_ADDR dbaVMO(hPr);
struct mcodeb::mcodebkey key;

	key.mcodebkey.mcodek = lMCode;		// alle Objekte mit diesem MCode
	key.mcodebkey.zvmook = 0L;
	dbaVMO.file_no = VMO_NEW;
	{
	ErrInstall EI (WC_NOTFOUND);

		RC = (ErrCode)z_keyfind (&dbaVMO, MCODEB, &key);
	}
	if (WC_NOTFOUND == RC) {
	// auf den vorhergehenden positioniert
		RC = (ErrCode)z_keynext (&dbaVMO, MCODEB);
		if (EC_OKAY != RC)
			return db_error (WC_NOTFOUND, RoutCode);

	// ersten Treffer lesen
		DBASSERT(z_keyread (hPr, &key));
		if (key.mcodek != lMCode)
			return db_error (WC_NOTFOUND, RoutCode);
	}

ErrInstall EI (WC_NOTFOUND);		// jetzt global zuschalten
BOOL fFound;

	do {		// für alle gefundenen Sätze
	// wenn was gefunden wurde
		if (!(key.zvmook & (IDL_MERKMAL|SICHT_MERKMAL))) {
		// Text muß existieren
			DBASSERT (GetMiText (hPr, lMCode, key.zvmook, OBL_OLD, &pText));
		
		// eigendliche Suchroutine
			if (pPattern) {
				switch (mode) {
				default:
				case 1:		// exakte Suche
					fFound = (strcmp (pPattern, pText) == 0);
					break;
		
				case 2:		// unexakte Suche
					fFound = isalike (pPattern, pText);
					break;
		
				case 3:		// Teilbegriffe suchen
					fFound = (strstr (pText, pPattern) != NULL);
					break;
				}
			} else 
				fFound = TRUE;	// nur Merkmal abfragen
		
			DELETE (pText);

		/* fFound == FALSE: nichts gefunden */
			if (fFound) {
				DBASSERTM (feput (pflObj, &key.zvmook));
			}
		}

	// nächsten Schlüssel suchen
		if ((RC = (ErrCode)z_keynext (&dbaVMO, MCODEB)) != EC_OKAY) {
			if (RC == WC_NOTFOUND) 
				RC = EC_OKAY;
			return RC;
		}

	// wenn Suchtext gegeben ist, dann genauer hinsehen
		DBASSERT(z_keyread (hPr, &key));	// Schlüssel lesen
		if (key.mcodek != lMCode)
			return EC_OKAY;			// kein  Merkmal mehr

	} while (TRUE);
	return EC_OKAY;
}

extern "C" 
long EXPORT02 FUNCTYPE FindPattern (
	HPROJECT hPr, long lMCode, char *pPattern, short mode, long *pflObj)
{
	if (VERSION0500000F <= GetDBVersion(hPr))	// Rückverkettung Merkmal --> Objekt jetzt indiziert 
		return FindPatternIndex(hPr, lMCode, pPattern, mode, pflObj);

// ansonsten alles beim Alten
DB_ADDR dbaMKL(hPr), dbaVMO(hPr); 
struct mkl MKLSatz;
struct vmo VMOSatz;
long lTarget = 0;
char *pText = NULL;	// wegen DELETE()
ErrCode RC;
BOOL fFound;

// AnfangsInitialisierung
	dbaMKL.file_no = MKL;
	dbaVMO.file_no = VMO_OLD;

	if (*pflObj == 0) {
		DBASSERT (feini (pflObj));
	}

/* Finden des MCodes */
	DBASSERT (z_keyfind (&dbaMKL, MK, &lMCode));
	__Read (dbaMKL, MKLSatz);		// MK-INF AUS MKL 
	if (MKLSatz.typ != 0) 			// kein Textmerkmal
		return db_error (ETYP, RoutCode);

	dbaVMO.rec_no = MKLSatz.zmkvmo;	// Objektnummer in VerbindungsListe
	__Read (dbaVMO, VMOSatz);		// Verweis in VerbindungsListe
	lTarget = VMOSatz.zvmoo;		// erstes Objekt
	do {
		if (!(lTarget & (IDL_MERKMAL|SICHT_MERKMAL))) {
		// Text muß existieren
			DBASSERT (GetMiText (hPr, lMCode, lTarget, OBL_OLD, &pText));
		
		// eigendliche Suchroutine
			if (pPattern) {
				switch (mode) {
				default:
				case 1:		// exakte Suche
					fFound = (strcmp (pPattern, pText) == 0);
					break;
		
				case 2:		// unexakte Suche
					fFound = isalike (pPattern, pText);
					break;
		
				case 3:		// Teilbegriffe suchen
					fFound = (strstr (pText, pPattern) != NULL);
					break;
				}
			} else 
				fFound = TRUE;	// nur Merkmal abfragen
		
			DELETE (pText);

		/* fFound == FALSE: nichts gefunden */
			if (fFound) {
				DBASSERTM (feput (pflObj, &lTarget));
			}
		}

		if ((dbaVMO.rec_no = VMOSatz.znvmo) == 0)
			break;	// Ende der Kette

		__Read (dbaVMO, VMOSatz);
	} while ((lTarget = VMOSatz.zvmoo) != 0);
	return EC_OKAY;
}

