/*Translated by FOR_C, v3.1, on 02/25/91 at 09:57:15 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * prueft, ob Masche (Flaeche) im Container                      *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75021
 *       Autor:                Major, Walter
 *       Datum:                06-Jul-90
 *       Modulname:            *** FNDMA ***
 *       Routinenummer:        3025
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         FNDKA,PUINFL
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=FNDMA (LTEST,DBAMAL,CONT)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                             FNDMA   - Funktion                      I*4
 *
 *       Parameter:            LTEST   - Kante im Cont. = .TRUE.       L
 *                             DBAMAL  - enthaelt NMAL und ZMAL        I*4
 *                             CONT    - Feld der Containerkoo.        I*4
 *                             CONT(1) - Xmin
 *                             CONT(2) - Xmax
 *                             CONT(3) - Ymin
 *                             CONT(4) - Ymax
 *       Aufgabenstellung:
 *          prueft, ob die Masche (Flaeche) den Container schneidet;
 *          in diesem Fall wird LTEST=.TRUE. gesetzt und das UP verlassen.
 *          Achtung !: bei Flaechen, die Loecher enthalten (die den aeus-
 *                     seren Rand bzw. sich selbst nicht beruehren bzw.
 *                     schneiden duerfen), muss die Aussenumrandung zu-
 *                     erst gespeichert sein !
 *       Fehlerbehandlung:
 *          FNDMA # 0 Fehler bei ZREAD oder PUINFL
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

extern "C" long FUNCTYPE fndma (HPROJECT hPr, long *ltest, DB_ADDR *pdbamal, long *cont)
{
DB_ADDR dbakal(hPr), dbakfm(hPr);
ErrCode RC;
struct kal kal;
struct kfm kfm;
struct mal mal;
long on, pktla;

/* *** Anfangswerte setzen: */
	*ltest = FALSE;
	dbakfm.file_no = KFM;
	dbakal.file_no = KAL;

/* *** Prüfung, ob Container völlig Flächencontainer umschließt */
	__Read (*pdbamal, mal);
	if((cont[0] <= mal.mcont.mxmin) && (cont[1] >= mal.mcont.mxmax) && 
	   (cont[2] <= mal.mcont.mymin) && (cont[3] >= mal.mcont.mymax))
	{
		*ltest = TRUE;
		return EC_OKAY;
	}

/* *** Prüfung, ob Flächenumrandung Container schneidet */
	dbakfm.rec_no = mal.zmkfm;
	do {
		__Read (dbakfm, kfm);
		dbakal.rec_no = labs (kfm.zkfmk);	/* Zeiger auf KAL (+oder-) */
		__Read (dbakal, kal);

	/* Container umschließt völlig Kantencontainer */
		if ((cont[0] <= kal.kcont.kxmin) && (cont[1] >= kal.kcont.kxmax) && 
		    (cont[2] <= kal.kcont.kymin) && (cont[3] >= kal.kcont.kymax))
		{
			*ltest = TRUE;
			return EC_OKAY;
		}

	/* Bearbeitung einer Kante: */
		DBASSERT (fndka (hPr, ltest, &dbakal, cont));
		if (*ltest)
			return EC_OKAY;
	} while ((dbakfm.rec_no = kfm.znkfm) != 0);	/* Zeiger wieder auf KFM */

/* *** Prüfung, ob 1 Eckpunkt des Containers in Flaechenumrandung: */
	on = mal.zmvgo;
	DBASSERT (puinfl (hPr, &pktla, &cont[0L], &cont[2L], &on));
	if (pktla == 0)
		*ltest = TRUE;

return EC_OKAY;
} 
