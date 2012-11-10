/*Translated by FOR_C, v3.2 (B), on 06/20/91 at 14:55:22 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
#include <fcrt.h>
/*+
 *       *****************************************************************
 *       * sucht Objekte, die mit vorgegebenem Objekt verbunden sind     *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75014
 *       Autor:                Major, Walter
 *       Datum:                20-Jun-91
 *       Modulname:            *** GETTO ***
 *       Routinenummer:        3050
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         GETTOP,GETTOL,GETTOF
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEINI,FEREL,FEREAD,SETERR
 *                             ERRFKT,LADR
 *       Common-Bloecke:       /WOHER/ - GETGI-Variante GIRIG waehlen
 *       SAVE:                 FEZAE  - Beginn der Zaehlung im dyn. Feld
 *                                      bei der jeweiligen Uebergabe
 *                             LEN    - Laenge des dyn. Feldes
 *                             FERIG  - Nummer des dyn. Feldes
 *                             /WOHER/- Common WOHER
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETTO (NL,ON,CHAR,RIG)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             GETTO - Funktion                        I*4
 *
 *       Parameter:  Input:    NL     - Nachladeparameter              I*4
 *                                      =0 beim 1. Eingang
 *                                      =WDHLG, wenn RIG-Feld voll
 *                   Output:   NL     - =0 bei erfogreichem Ende
 *                                      =WDHLG zum Nachladen RIG-Feld
 *                   Input:    ON     - Objektnummer                   I*4
 *                             CHAR   - von F77 (F) oder C (C) gerufen C*1
 *       bei F !     Output:   RIG    - Feld fuer Relationen           I*4
 *                   Input:    RIG(1) - max. Laenge
 *                   Output:   RIG(2) - akt. Laenge
 *                             RIG(3) - Objektnr. des verbundenen Objektes
 *       bei C !     nur RIG mit Dimension 1 angeben
 *       Aufgabenstellung:
 *          sucht Objekte, die mit dem gegebenen Objekt verbunden sind.
 *          Gibt bei F die Objektnummern der verbundenen Objekte ab RIG(3)
 *          an. In RIG(2) steht die Anzahl der verbundenen Objekte.
 *          Bei C stehen die Objektnummern im dyn.Feld FERIG, in RIG(1)
 *          steht die Nummer des dyn. Feldes.
 *          Ruft entweder GETTOP (fuer ein Punktobjekt), GETTOL (fuer ein
 *          Linienobjekt) oder GETTOF (fuer ein Flaechenobjekt).
 *          Achtung !: CHAR gibt an, ob GETTO von F77 (=F) oder von C (=C)
 *                     gerufen wird; bei F wird Fortran-Feld RIG ueber-
 *                     geben, bei C muessen die Objektnummern vom dyna-
 *                     mischen Feld FERIG abgenommen werden (dabei muss
 *                     aber beim Aufruf trotzdem das Feld RIG wenigstens
 *                     mit Dimension 1 angegeben werden). Bei C muss das
 *                     dyn. Feld FERIG vom Anwender freigegeben werden,
 *                     die dyn. Feldnummer steht in RIG(1) !
 *       Fehlerbehandlung:
 *          GETTO = EOKAY  - i.O.
 *                 = ENOON  - Objekt nicht vorhanden
 *                 = ENODIM - Dimension RIG-Feld < 3
 *                 = WNOEOK - kein Elementarobjekt
 *                 = WNORIG - keine topol. Relationen
 *                 = WDHLG  - noch Informationen vorhanden
 *       -----------------------------------------------------------------
 *- */
	/* PARAMETER translations */
#define	I40	0L
#define	I41	1L
#define	I42	2L
#define	I43	3L
#define	SHDIDN	6L
#define	WNRECW	1018L
	/* end of PARAMETER translations */

#include "ris.h"
#include "zipedb.h"
#include "zforc.h"

	/* COMMON translations */
extern struct t_woher {
	char rout[4];
	}	woher;
	/* end of COMMON translations */

long /*FUNCTION*/ FUNCTYPE
getto (on, rig)
long int *on;		// Objektnummer
long int *rig;		// FlexNummer
{
long int _l0, dbaobl[2], getto_v, irc, lenakt, lenmax, 
	 lenon, obl[SIZOBL];
static long int ferig = 0, fezae = 0, len = 0;
short _s0;

	/* *** Anfangswerte setzen, Testung: */
	getto_v = EOKAY;
	irc = EOKAY;
	*rig = 0L;
	strcpy (woher.rout, "RIG");
	lenon = 0L;
	/*                               ! dyn. Feld wird uebergeben */
	/* *** Objektnummer pruefen: */
	if ((*on <= I40) || (*on >= ladr( ADR(_s0,NOBL) ))) {
		/*                                       ! Objektnr. ausserhalb Bereich */
		return db_error (ENOON, 3050);
	}

	/* *** Erstwerte setzen: */
	fezae = 1L;
	len = 0L;

	ferig = *rig;
	/* *** Punkt-, Linien- oder Flaechenobjekt: */
	dbaobl[0L] = NOBL;
	dbaobl[1L] = *on;
	irc = zread( dbaobl, obl );
	if (irc != EOKAY) {
		getto_v = irc;
		goto L_70;
	}
	if (obl[0L] >= 2147483647) {
		/*                                       ! geloeschtes Objekt */
		getto_v = ENOON;
		irc = db_error (ENOON, 3050);
		goto L_70;
	}

	if (obl[ZOKP - 1L] != I40) {
		/*                                       ! Punktobjekt */
		irc = gettop (on, &obl[ZOKP - 1L], &lenon, &ferig);
		if (irc != EOKAY) {
			getto_v = irc;
			goto L_70;
		}
	} else if (obl[ZOVOL - 1L] != I40) {
		/*                                       ! Linienobjekt */
		irc = gettol (on, &obl[ZOVOL - 1L], &lenon, &ferig);
		if (irc != EOKAY) {
			getto_v = irc;
			goto L_70;
		}
		/*       ELSE IF (OBL(ZOVOMA) .NE. I40) THEN
		 *C                                      ! Flaechenobjekt
		 *          IRC=GETTOF (ON,OBL(ZOVOMA),LENON,FERIG)
		 *          IF (IRC .NE. EOKAY) THEN
		 *               GETTO=IRC
		 *               GOTO 70
		 *          END IF */
	} else{
		getto_v = WNOEOK;
		irc = db_error (WNOEOK, 3050);
		goto L_70;
	}
	len = lenon;
	/* *** dynamisches Feld der RIG freigeben: */
L_70:
	if (irc != EOKAY) {
		irc = ferel( &ferig );
		ferig = 0L;
		if (irc != EOKAY) 
			return irc;
	}

return (getto_v);
} /* end of function */

