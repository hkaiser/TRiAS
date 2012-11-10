/*Translated by FOR_C, v3.1, on 02/25/91 at 10:02:53 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * liegen Objekte voellig in Flaeche oder ueberdecken sie voll?  *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A7?
 *       Autor:                Major, Walter
 *       Datum:                11-Jul-90
 *       Modulname:            *** RIGIN ***
 *       Routinenummer:        3034
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         GETAPU,PUINFL
 *       libdbr.a    :         -
 *       libzipedb.a :         FELEN,FEGET,FEPUT
 *       Common-Bloecke:       /FENR/ FEON - Feldnummerncommon
 *       SAVE:                 /FENR/ Nr. des dyn. Feldes
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=RIGIN (ON,FERIG)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             RIGIN  - Funktion                       I*4
 *
 *       Parameter:  Input:    ON     - Objektnummer der Flaeche       I*4
 *                             FERIG  - Nummer des dyn. Feldes RIG     I*4
 *       Aufgabenstellung:
 *          sucht mit GETAPU die Anfangskoordinaten des Objekts und prueft
 *          mit PUINFL, ob dieser Punkt in der Flaeche liegt oder nicht.
 *       Fehlerbehandlung:
 *          RIGIN = EOKAY  - i.O.
 *       -----------------------------------------------------------------
 *- */
#include "trias02p.hxx"

extern struct t_fenr {
	long int feon;
} fenr;

long FUNCTYPE rigin (HPROJECT hPr, long *on, long *ferig)
{
long int _l0, izaehl, lenon, onfl, onr, pktla, staf[2], 
	 xp, xpfl, yp, ypfl;
ErrCode RC;

/* *** Anfangswerte setzen: */
	onfl = *on;

/* *** Anfangspunkt der gegebenen Flaeche: */
	DBASSERT (getapu (hPr, &onfl, staf, &xp, &yp));
	xpfl = xp;
	ypfl = yp;

/* *** Laenge des dyn. Feldes: */
	DBASSERT (felen (&fenr.feon, &lenon));

/* *** Objekt voellig in Flaeche ?: - Art 12: */
	for (izaehl = 2; izaehl <= lenon; izaehl++) {
		DBASSERT (feget (&fenr.feon, &izaehl, &onr));
		DBASSERT (getapu (hPr, &onr, staf, &xp, &yp));
		DBASSERT (puinfl (hPr, &pktla, &xp, &yp, &onfl));
		if (pktla == 0) {
			DBASSERTM (feput (ferig, &onr));
			DBASSERTM (feput (ferig, ADR (_l0, 12L)));
		}

	/* ---*** pruefen, ob Flaeche Objekt ganz ueberdeckt!   Art 13: */
		if ((pktla == 1) && (staf[1L] == 3)) {
			DBASSERT (puinfl (hPr, &pktla, &xpfl, &ypfl, &onr));
			if (pktla == 0) {
				DBASSERTM (feput (ferig, &onr));
				DBASSERTM (feput (ferig, ADR (_l0, 13)));
			}
		}
	}

	/* *** Ende: */
return EC_OKAY;
} /* end of function */

