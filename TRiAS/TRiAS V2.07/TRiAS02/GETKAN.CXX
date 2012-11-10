/*Translated by FOR_C, v3.1, on 02/21/91 at 14:05:09 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * Sucht Koordinaten von Punkten einer Kante                     *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75?
 *       Autor:                Major,Walter
 *       Datum:                02-Mai-90
 *       Modulname:            *** GETKAN ***
 *       Routinenummer:        3013
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         IABS
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         -
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEINI,FEREL,FEPUT,FEGET,SETERR
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETKAN (ZKL,WDH,FEX,FEY)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             GETKAN - Funktion                       I*4
 *
 *       Parameter:            ZKL    - Zeiger auf KAL                 I*4
 *                             WDH    - bei Wiederholung muss WDHLG stehen
 *                                      (ZEP wird nicht gespeichert)   I*4
 *                             FEX    - Nummer des dyn. Feldes X       I*4
 *                             FEY    - Nummer des dyn. Feldes Y       I*4
 *       Aufgabenstellung:
 *          Uebernimmt den Zeiger ZKL auf die Kantenliste KAL, speichert
 *          die Koordinaten der Kantenpunkte in den dynamischen Feldern
 *          FEX und FEY in geordneter Reihenfolge (bei negativen Zeiger
 *          auf die KAL in umgekehrter Folge). Der Endpunkt der Kante wird
 *          nicht gespeichert, wenn WDH=WDHLG.
 *       Fehlerbehandlung:
 *          Fehler:
 *          EOKAY   i.O.
 *          EZKAL   Zeiger auf Kantenliste darf nicht Null sein
 *          EZSPL   Zeiger Stuetzpunktliste darf nicht Null sein
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

long FUNCTYPE getkan (HPROJECT hPr, long *zkl, long *wdh, long *fex, long *fey, long *cont) 
{
DB_ADDR dbakal(hPr), dbakpl(hPr), dbaspl(hPr);
ErrCode RC;
struct kal kal;
struct kpl kpl;

// Anfangswerte setzen
	dbakal.file_no = KAL;
	dbakpl.file_no = KPL;

// Beginn Kante
	dbakal.rec_no = labs (*zkl);
	__Read (dbakal, kal);
	
// Container korrigieren
	if (cont != NULL) {
		if (cont[0] > kal.kcont.kxmin) cont[0] = kal.kcont.kxmin;
		if (cont[1] < kal.kcont.kxmax) cont[1] = kal.kcont.kxmax;
		if (cont[2] > kal.kcont.kymin) cont[2] = kal.kcont.kymin;
		if (cont[3] < kal.kcont.kymax) cont[3] = kal.kcont.kymax;
	}

long izap, izep;

	if (*zkl < 0) {
	// Vertauschen Anfangs- und Endpunkt
		izep = kal.zap;		/* Zeiger Endpkt. auf KPL */
		izap = kal.zep;		/* Zeiger Anf.pkt. auf KPL */
	} else if (*zkl > 0) {
	/* Anf. u. Endpkt. richt. Folge */
		izap = kal.zap;
		izep = kal.zep;
	} else 
		return db_error ((short)EZKAL, 3013); /* Zeiger ZKL darf nicht 0 sein */

long zspl = kal.zksp;		// Zeiger Stützpunkt KL -> SPL
long iasp = kal.asp;

// Anzahl Stützpunkte, Anfangspunktbearbeitung einer Kante
	dbakpl.rec_no = izap;
	__Read (dbakpl, kpl);
	DBASSERTM (feput (fex, &kpl.pkrd.kpx));		// AnfangsPunkt X
	DBASSERTM (feput (fey, &kpl.pkrd.kpy));		// AnfangsPunkt Y

	if (iasp != 0) {
	// ab hier ist es versionsspezifisch
		if (VERSION05000010 <= GetDBVersion(hPr)) {
		struct longspl SPLSatz;

		// Stützpunktbearbeitung
			dbaspl.file_no = SPL_NEW;
			if (*zkl > 0) {
			// Stützpkt. in Kantenrichtung
				for (long j = 0; j < iasp; /**/) {
					if (zspl == 0)
						return db_error ((short)EZSPL, 3013);

					dbaspl.rec_no = zspl;
					__Read (dbaspl, SPLSatz);
					for (long i = 0; i < NUMSPLCOORDS && j < iasp; i++, j++) {
						DBASSERTM (feput (fex, &SPLSatz.spxl[i]));
						DBASSERTM (feput (fey, &SPLSatz.spyl[i]));
					}

				// Zeiger auf nächsten Satz
					zspl = SPLSatz.znspl;
				}
			} else {
			// Stützpunkt entgegen Kantenrichtung, Zeiger auf SPL speichern
			long fezspl = 0L;

				DBASSERT (feini (&fezspl));	// Feld FEZSPL initialisieren
				while (0 != zspl) {
					dbaspl.rec_no = zspl;
					__Read (dbaspl, SPLSatz);

					DBASSERTM (feput (&fezspl, &zspl));
					zspl = SPLSatz.znspl;
				}
			
			// Zeiger ZSPL von hinten abarbeiten
			long lCnt = iasp;	// Anzahl der Stützpunkte
			long k = 0;			// Anzahl der SPLSätze

				DBASSERT(felen (&fezspl, &k));
				for (/**/; k >= 1; k--) {
				// vorhergehenden Satz einlesen
					DBASSERT (feget (&fezspl, &k, &zspl));
					dbaspl.rec_no = zspl;
					__Read (dbaspl, SPLSatz);

				// Koordinaten speichern
					for (long i = lCnt % NUMSPLCOORDS; i >= 0 && lCnt >= 0; i--, lCnt--) {
						DBASSERTM (feput (fex, &SPLSatz.spxl[i]));
						DBASSERTM (feput (fey, &SPLSatz.spyl[i]));
					}
				}

			// Feld FEZSPL freigeben
				DBASSERT (ferel (&fezspl));
			}
		} else {
		// ansonsten mit alter Struktur arbeiten
		struct spl spl;

		// Stützpunktbearbeitung
			dbaspl.file_no = SPL_OLD;
			if (*zkl > 0) {
			// Stützpkt. in Kantenrichtung
				for (long j = 0; j < iasp; j++) {
					if (zspl <= 0)
						return db_error ((short)EZSPL, 3013);
					dbaspl.rec_no = zspl;
					__Read (dbaspl, spl);
					DBASSERTM (feput (fex, &spl.spx));
					DBASSERTM (feput (fey, &spl.spy));
					zspl = spl.znsp;
				}
			} else {
			// Stützpunkt entgegen Kantenrichtung, Zeiger auf SPL speichern
			long fezspl = 0L;

				DBASSERT (feini (&fezspl)); /* Feld FEZSPL initialisieren */
				for (long j = 0; j < iasp; j++) {
					if (zspl <= 0)
						return db_error ((short)EZSPL, 3013);
					DBASSERTM (feput (&fezspl, &zspl));

					dbaspl.rec_no = zspl;
					__Read (dbaspl, spl);
					zspl = spl.znsp;
				}
			
			// Zeiger ZSPL von hinten abarbeiten
				for (long k = iasp; k >= 1; k--) {
					DBASSERT (feget (&fezspl, &k, &zspl));

					dbaspl.rec_no = zspl;
					__Read (dbaspl, spl);
					DBASSERTM (feput (fex, &spl.spx));
					DBASSERTM (feput (fey, &spl.spy));
				}

			// Feld FEZSPL freigeben
				DBASSERT (ferel (&fezspl));
			}
		}
	}

// Endpunkt bearbeiten
	if (*wdh != WDHLG) {
	// Endpunkt speichern, es kommen keine Kanten mehr
		dbakpl.rec_no = izep;
		__Read (dbakpl, kpl);
		DBASSERTM (feput (fex, &kpl.pkrd.kpx));	// EndPunkt X
		DBASSERTM (feput (fey, &kpl.pkrd.kpy));	// EndPunkt Y
	}
	return EC_OKAY;
} 

