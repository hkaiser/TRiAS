/*Translated by FOR_C, v3.1, on 02/25/91 at 10:17:51 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * prueft, ob Kante im Container                                 *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75021
 *       Autor:                Major, Walter
 *       Datum:                06-Jun-90
 *       Modulname:            *** FNDKA ***
 *       Routinenummer:        3024
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         STINFL
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=FNDKA (LTEST,DBAKAL,CONT)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                             FNDKA   - Funktion                      I*4
 *
 *       Parameter:            LTEST   - Kante im Cont. = .TRUE.       L
 *                             DBAKAL  - enthaehlt NKAL und ZKAL       I*4
 *                             CONT    - Feld der Containerkoo.        I*4
 *                             CONT(1) - XMIN  linke obere Ecke
 *                             CONT(2) - XMAX  rechte untere Ecke
 *                             CONT(3) - YMIN linke obere Ecke
 *                             CONT(4) - YMAX rechte untere Ecke
 *       Aufgabenstellung:
 *          prueft, ob der Schnitt einer Stuetzpunktstrecke einer Kante
 *          mit dem Container nicht leer ist; in diesem Fall wird
 *          LTEST=.TRUE. gesetzt und das UP verlassen.
 *       Fehlerbehandlung:
 *          FNDKA # 0 Fehler bei ZREAD
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" 
long FUNCTYPE fndka (HPROJECT hPr, long *ltest, DB_ADDR *pdbakal, long *cont)
{
bool fLast = false;
DB_ADDR dbakpl(hPr), dbaspl(hPr);
struct kal kal;
struct kpl kpl;
ErrCode RC;

// Anfangswerte setzen
	TX_ASSERT(pdbakal -> file_no == KAL);
	dbakpl.file_no = KPL;
	*ltest = FALSE;

// Beginn der Kante, Kantensatz einlesen
	__Read (*pdbakal, kal);

long zspl = kal.zksp;		// Verweis auf Stützpunktliste
	
// Koordinaten von ZAP
	dbakpl.rec_no = kal.zap;
	__Read (dbakpl, kpl);

long ix1 = kpl.pkrd.kpx;	// erster Stützpunkt (Knotenpunkt)
long iy1 = kpl.pkrd.kpy;

	if (VERSION05000010 <= GetDBVersion(hPr)) {
	struct longspl SPLSatz;

		dbaspl.file_no = SPL_NEW;
		do {
			if (zspl > 0) {		// SPL
				dbaspl.rec_no = zspl;
				__Read (dbaspl, SPLSatz);

				for (long i = 0; i < NUMSPLCOORDS; i++) {
					if (0 == SPLSatz.spxl[i] && 0 == SPLSatz.spyl[i]) {
						TX_ASSERT(i > 0);				// wenigstens eine Koordinate muß in diesem Satz sein
						TX_ASSERT(0 == SPLSatz.znspl);	// muß der letzte der Kette sein
						break;	/* for */				// SPLSatz nicht vollständig gefüllt
					}

				long ix2 = SPLSatz.spxl[i];
				long iy2 = SPLSatz.spyl[i];

				// Prüfen, ob Stützpunktstrecke im Container
					*ltest = stinfl (&ix1, &iy1, &ix2, &iy2, &cont[0L], &cont[2L], &cont[1L], &cont[3L]);
					if (*ltest) 
						return EC_OKAY;	// Objekt im Container

					ix1 = ix2;	// neuer erster Punkt
					iy1 = iy2;
				}
				zspl = SPLSatz.znspl;
			}
			else {				// ZEP
				dbakpl.rec_no = kal.zep;
				__Read (dbakpl, kpl);

			// Prüfen, ob Stützpunktstrecke im Container
				*ltest = stinfl (&ix1, &iy1, &kpl.pkrd.kpx, &kpl.pkrd.kpy, &cont[0L], &cont[2L], &cont[1L], &cont[3L]);
				if (*ltest) 
					return EC_OKAY;	// Objekt im Container 

				fLast = true;		// Ende der Kante erreicht, do ... while abbrechen
			}

		} while (!fLast);	// noch weitere Punkte vorhanden
		
		return EC_OKAY;
	}
	
// ansonsten mit alter Struktur arbeiten
// Beginn Kante, Koordinaten des nächsten Stuetzpunktes bzw. des ZEP
struct spl spl;

	dbaspl.file_no = SPL_OLD;
	do {
	long ix2, iy2;

		if (zspl > 0) {		/* SPL */
			dbaspl.rec_no = zspl;
			__Read (dbaspl, spl);
			ix2 = spl.spx;
			iy2 = spl.spy;
			zspl = spl.znsp;
		}
		else {			/* ZEP */
			dbakpl.rec_no = kal.zep;
			__Read (dbakpl, kpl);
			ix2 = kpl.pkrd.kpx;
			iy2 = kpl.pkrd.kpy;
			fLast = true;		/* Ende Kante */
		}

	/* *** Prüfen, ob Stützpunktstrecke im Container: */
		*ltest = stinfl (&ix1, &iy1, &ix2, &iy2, &cont[0L], &cont[2L], 
				 &cont[1L], &cont[3L]);
		if (*ltest) return EC_OKAY;	/* Objekt im Container */

		ix1 = ix2;
		iy1 = iy2;

	} while (!fLast);	// noch weitere Punkte vorhanden

	return EC_OKAY;
}


