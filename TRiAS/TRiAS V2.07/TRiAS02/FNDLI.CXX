/*Translated by FOR_C, v3.1, on 02/25/91 at 11:39:09 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * prueft, ob Linienobjekt im Container                          *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75021
 *       Autor:                Major, Walter
 *       Datum:                07-Jun-90
 *       Modulname:            *** FNDLI ***
 *       Routinenummer:        3010
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         IABS
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         FNDKA
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=FNDLI (LTEST,ZVOG,CONT)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                             FNDLI  - Funktion               I*4
 *
 *       Parameter:            LTEST   - Linienobj. im Cont. = .TRUE.  L
 *                             ZVOG    - Zeiger auf VOL                I*4
 *                             CONT    - Feld der Containerkoo.        I*4
 *                             CONT(1) - X linke obere Ecke
 *                             CONT(2) - X rechte untere Ecke
 *                             CONT(3) - Y linke obere Ecke
 *                             CONT(4) - Y rechte untere Ecke
 *       Aufgabenstellung:
 *          prueft, ob der Schnitt einer Kante des Linienobjektes mit dem
 *          Container nicht leer ist; in diesem Fall wird LTEST=.TRUE.
 *          gesetzt und das UP verlassen.
 *       Fehlerbehandlung:
 *          IRC # 0 Fehler bei ZREAD
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

extern "C" long FUNCTYPE fndli (HPROJECT hPr, long *ltest, long *zvog, long *cont)
{
DB_ADDR dbakal(hPr), dbavol(hPr);
ErrCode RC;
struct kal kal;
struct vol vol;
long zkl, zvg, zvgn;

/* *** Anfangswerte setzen: */
	dbakal.file_no = KAL;
	dbavol.file_no = VOL;
	*ltest = FALSE;
	zvg = *zvog;

/* *** Kanten suchen: */
	do {
		dbavol.rec_no = zvg;
		__Read (dbavol, vol);
		zkl = vol.zvolk;
		zvgn = vol.znvol;

	/* Zeiger auf nächste Kante */
		dbakal.rec_no = labs (zkl);
		__Read (dbakal, kal);

	/* *** wird Container von Kantencontainer geschnitten ?: */
		if ((kal.kcont.kxmax < cont[0]) || (kal.kcont.kxmin > cont[1]) || 
		    (kal.kcont.kymax < cont[2]) || (kal.kcont.kymin > cont[3])) 
		{ /* keine Ueberlappung X,Y-MIN,MAX aus KL mit Container */
			zvg = zvgn;
			continue;		/* naechste Kante ? */
		}

	/* *** umschließt Container völlig Kantencontainer ?: */
		if ((cont[0] <= kal.kcont.kxmin) && (cont[1] >= kal.kcont.kxmax) && 
		    (cont[2] <= kal.kcont.kymin) && (cont[3] >= kal.kcont.kymax))
		{
			*ltest = TRUE;
			return EC_OKAY;	/* Ende - Linienobj. im Container */
		}

	/* *** Uebergabe an FNDKA: */
		DBASSERT (fndka (hPr, ltest, &dbakal, cont));
		if (*ltest) return EC_OKAY;	/* Ende - Linienobj. im Container */

		zvg = zvgn;			/* nächste Kante */
	} while (zvgn != 0);

return EC_OKAY;
}

