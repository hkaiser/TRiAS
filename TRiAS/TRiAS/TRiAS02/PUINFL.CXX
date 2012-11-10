/*Translated by FOR_C, v3.1, on 02/25/91 at 10:02:31 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * Punkt in Flaeche                                              *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A7?
 *       Autor:                Major, Walter
 *       Datum:                26-Nov-90
 *       Modulname:            *** PUINFL ***
 *       Routinenummer:        3033
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         IGPTNL,GIRIG oder GIFND (GETGI-Varianten)
 *       libdbr.a    :         -
 *       libzipedb.a :         SETERR
 *       Common-Bloecke:       /WOHER/ - welche GETGI-Variante waehlen
 *       SAVE:                 /WOHER/ - Woher-Common
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=PUINFL (PKTLA,XP,YP,ONR)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                             PUINFL  - Funktion                      I*4
 *
 *       Parameter:  Output:   PKTLA   - PKTLA= 0 Punkt in Flaeche     I*4
 *                                       PKTLA=-1 Punkt in Loch
 *                                       PKTLA=+1 ausserh. aeusseren Rand
 *                   Input:    XP,YP   - Koo.des Punktes               I*4
 *                             ONR     - Objektnr. der Flaeche         I*4
 *       Aufgabenstellung:
 *          prueft, ob vorgegebener Punkt voellig in der Flaeche liegt;
 *          in diesem Fall wird PKTLA = 0 gesetzt und das UP verlassen.
 *          Achtung !: bei Flaechen, die Loecher enthalten (die den aeus-
 *                     seren Rand bzw. sich selbst nicht beruehren bzw.
 *                     schneiden duerfen), muss die Aussenumrandung zu-
 *                     erst gespeichert sein !
 *       Fehlerbehandlung:
 *          PUINFL = EOKAY  i.O.
 *                 = ENOPAD Variable ROUT aus /WOHHER/ falsch
 *                 # EOKAY  Fehler aus gerufenen Programmen
 *       -----------------------------------------------------------------
 *- */
#include "trias02p.hxx"

	/* COMMON translations */
struct t_woher {
	char rout[4];
	}	woher = { 0 };
	/* end of COMMON translations */

long FUNCTYPE puinfl (HPROJECT hPr, long *pktla, long *xp, long *yp, long *onr)
{
long int id, irc, ist, itest, lgi, lmx, nl, staf[2];
long *pX = NULL;
long *pY = NULL;
long fex = 0, fey = 0;

	
/* *** Anfangswerte setzen: */
	lmx = 3;	// muß größer als 1 sein
	nl = 0;
	itest = 0;	// 1. Runde (AußenKontur)

/* *** Ruf GETGI-Variante: */
	do {
		ist = 1L;
		do {
//			if (strcmp (woher.rout, "FND") == 0) 
			{
				fex = 0;
				fey = 0;
				irc = getgi (hPr, &nl, onr, &id, staf, &lmx, &lgi, &fex, &fey, NULL, NULL);
//				irc = gifnd (&nl, onr, &id, staf, &lmx, &lgi, pX, pY);
			} 
/* ============================================================================
			else if (strcmp (woher.rout, "RIG") == 0) {
				irc = girig (&nl, onr, &id, staf, &lmx, &lgi, &fex, &fey);
				irc = girig (&nl, onr, &id, staf, &lmx, &lgi, pX, pY);
			} 
			else {
				if (fex) ferel_ (&fex); 
				if (fey) ferel_ (&fey);   // Felder freigeben
				return db_error (ENOPAD, 3033);
			}
============================================================================ */
	
			if (irc != EC_OKAY) {
				if (nl == WDHLG) {
					if (ist > 0) ist = 0;
					else 	     ist = -1;
				} else if (nl == WFORT) {
					if (ist < 0) ist = -2;
				} else {
					if (fex) ferel_ (&fex); 
					if (fey) ferel_ (&fey);   // Felder freigeben
					return irc;
				}
			} else if (ist < 0) 
				ist = -2;
	
		/* *** Ruf IGPTNL: */
			FlexAdr ((short)fex, &pX);       // Feldadressen holen
			FlexAdr ((short)fey, &pY);
			irc = igptnl (xp, yp, pX, pY, &lgi, &ist);
			if (fex) ferel_ (&fex); 
			if (fey) ferel_ (&fey);   // Felder freigeben
		} while (nl == WDHLG);

	/* ---*** Auswertung der Lage des Punktes: */
		if (itest == 0) {		// Außenkontur (erster Durchgang)
			if (irc < 0) {
				*pktla = 1L;
				break;		// Punkt außerhalb äußerer Umrandung
			} else
				*pktla = 0L;	// Punkt innerhalb äußerer Umrandung
		} else if (irc > 0) {
			*pktla = -1L;
			break;			// Punkt in Loch
		}

	// für nächste Runde setzen
		itest = 1;
	} while (nl == WFORT);			// Innenkontur bei Flächen

	if (fex) ferel_ (&fex); 
	if (fey) ferel_ (&fey);   // Felder freigeben

return EC_OKAY;
} /* end of function */
