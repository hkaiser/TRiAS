/*Translated by FOR_C, v3.1, on 02/21/91 at 12:42:57 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * Uebergibt Koordinaten der Umrandung von Flaechenobjekten      *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75010
 *       Autor:                Major,Walter
 *       Datum:                17-Jul-90
 *       Modulname:            *** GETGIF ***
 *       Routinenummer:        3005
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         GETKAN
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETGIF (NL,ZVGI,FEX,FEY,ZKFN)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             GETGIF   Funktion                       I*4
 *
 *       Parameter:  Input:    NL     - 0 bei erstem Eingang,          I*4
 *                                      WFORT bei erforderlichem Nach-
 *                                      laden fuer Innenkanten
 *                   Output:            0 bei erfolgreichem Ende,
 *                                      WFORT bei erforderlichem Nach-
 *                                      laden fuer Innenkanten
 *                   Input:    ZVGI   - Zeiger auf Maschenliste MAL    I*4
 *                             FEX    - Nummer des dyn. Feldes X       I*4
 *                             FEY    - Nummer des dyn. Feldes Y       I*4
 *                   In-/Outp. ZKFN   - naechste Kante in KFM          I*4
 *       Aufgabenstellung:
 *          Uebernimmt den Zeiger ZVGI auf die Maschenliste MAL; ruft
 *          kantenweise GETKAN, um die Koordinaten X und Y der Flaechen-
 *          umrandung zu sammeln. Folgen Kanten eines Innenrandes, wird
 *          GETGIF auf WFORT gesetzt (Nachladen ist erforderlich).
 *       Fehlerbehandlung:
 *          Fehler:
 *          EOKAY   i.O.
 *          WFORT   Nachladen der Koo. fuer Innenkanten
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

static long FUNCTYPE GetMaschenCont (HPROJECT hPr, long lFirst, long *cont);

long FUNCTYPE getgif (HPROJECT hPr, long *nl, long *zvgi, long *fex, long *fey, 
		      long *zkfn, long *cont, long *window) 
{
DB_ADDR dbakal(hPr), dbakfm(hPr), dbamal(hPr);
ErrCode RC;
struct kal kal;
struct mal mal;
struct kfm kfm;
long izap, izep, wdh, zkl, zkln;

/* *** Anfangswerte setzen: */
	dbamal.file_no = MAL;
	dbakfm.file_no = KFM;
	dbakal.file_no = KAL;

/* *** Innenkanten bearbeiten ?: */
	if (*nl == WFORT) {
		dbakfm.rec_no = *zkfn;
		*nl = 0;
	} else {
	/* *** Auffinden der einzelnen Kanten: */
		dbamal.rec_no = *zvgi;
		__Read (dbamal, mal);
		dbakfm.rec_no = mal.zmkfm;

	// evtl. Container mit Window vergleichen 
		if (cont && window) {
			DBASSERT (GetMaschenCont (hPr, dbakfm.rec_no, cont));
			if (cont[1] < window[0] || cont[0] > window[1] ||
			    cont[3] < window[2] || cont[2] > window[3])
			{
				return ENOFIT;
			}
		}
	}

// Geometrie einer Masche einlesen
	do {
		__Read (dbakfm, kfm);		// nächste Kante
		zkl = kfm.zkfmk;		/* Zeiger auf KAL (+oder-) */
		*zkfn = kfm.znkfm;

	/* Zeiger wieder auf KFM
	 * *** Prüfung, ob Kante des gleichen Randes folgt: */
		if (*zkfn != 0) {
			dbakfm.rec_no = *zkfn;
			__Read (dbakfm, kfm);
			zkln = kfm.zkfmk;

		/* Zeiger naechste Kante aus KFM */
			dbakal.rec_no = labs (zkl);
			__Read (dbakal, kal);		// Kante lesen
			if (zkl < 0)  izep = kal.zap;
			else	      izep = kal.zep;

			dbakal.rec_no = labs (zkln);
			__Read (dbakal, kal);		// folgende Kante
			if (zkln < 0) izap = kal.zep;
			else	      izap = kal.zap;

			if (izap == izep)
				wdh = WDHLG;
			else {
				wdh = 0;	// Beginn einer neuen Masche
				*nl = WFORT;
			}
		} else
			wdh = 0;

	/* *** Bearbeitung einer Kante: */
		DBASSERT (getkan (hPr, &zkl, &wdh, fex, fey, cont));

	/* *** weitere Kante vorhanden ?: */
		if (*zkfn != 0) {
			if (*nl == WFORT)
				return WFORT;
			else
				dbakfm.rec_no = *zkfn;
		} else
			return EC_OKAY;	// fertig, alles eingelesen
	} while (1);

return EC_OKAY;
}

static long FUNCTYPE GetMaschenCont (HPROJECT hPr, long lFirst, long *cont)
{
DB_ADDR dbakfm(hPr), dbakal(hPr);
struct kfm kfm;
struct kal kal;
ErrCode RC;
long izap, izep, zkl, zkln, zkfn;

	dbakfm.file_no = KFM;
	dbakfm.rec_no = lFirst;
	dbakal.file_no = KAL;
	do {
		__Read (dbakfm, kfm);		// nächste Kante
		zkl = kfm.zkfmk;		/* Zeiger auf KAL (+oder-) */
		zkfn = kfm.znkfm;

	/* Zeiger wieder auf KFM
	 * *** Prüfung, ob Kante des gleichen Randes folgt: */
		if (zkfn != 0) {
			dbakfm.rec_no = zkfn;
			__Read (dbakfm, kfm);
			zkln = kfm.zkfmk;

		/* Zeiger naechste Kante aus KFM */
			dbakal.rec_no = labs (zkl);
			__Read (dbakal, kal);			// Kante lesen
			if (zkl < 0) izep = kal.zap;
			else	     izep = kal.zep;

		/* Container aktualisieren */
			if (cont[0] > kal.kcont.kxmin) cont[0] = kal.kcont.kxmin;
			if (cont[1] < kal.kcont.kxmax) cont[1] = kal.kcont.kxmax;
			if (cont[2] > kal.kcont.kymin) cont[2] = kal.kcont.kymin;
			if (cont[3] < kal.kcont.kymax) cont[3] = kal.kcont.kymax;

			dbakal.rec_no = labs (zkln);
			__Read (dbakal, kal);			// folgende Kante
			if (zkln < 0) izap = kal.zep;
			else	      izap = kal.zap;

			if (izap != izep) 
				break;	// Ende dieser Masche
		} else {
		// nur eine Kante
			dbakal.rec_no = labs (zkl);
			__Read (dbakal, kal);			// Kante lesen

		/* Container aktualisieren */
			if (cont[0] > kal.kcont.kxmin) cont[0] = kal.kcont.kxmin;
			if (cont[1] < kal.kcont.kxmax) cont[1] = kal.kcont.kxmax;
			if (cont[2] > kal.kcont.kymin) cont[2] = kal.kcont.kymin;
			if (cont[3] < kal.kcont.kymax) cont[3] = kal.kcont.kymax;
			break;				// Ende dieser Kante
		}
		dbakfm.rec_no = zkfn;
	} while (TRUE);

return EC_OKAY;
}
