/*Translated by FOR_C, v3.1, on 02/25/91 at 10:00:59 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * sucht Geometrierelationen fuer ein Punktobjekt                *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75015
 *       Autor:                Major, Walter
 *       Datum:                17-Jul-90
 *       Modulname:            *** GETRIP ***
 *       Routinenummer:        3027
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         IABS,MOD
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         HTMANR
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEINI,FEREL,FEPUT,FELEN,FEGET,FLQSRT
 *                             FLREDN,HTWIND,SETERR,ERRFKT
 *       Common-Bloecke:       RIFENR   -  fuer dyn. Feldnr. Maschenobj.
 *       SAVE:                 /RIFENR/ - Feldnummercommon
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETRIP (ON,ZPOL,FERIG,X,Y)
 *
 *                             GETRIP - Funktion                       I*4
 *                             IRC    - Rueckkehrcode                  I*4
 *
 *       Parameter:  Input:    ON     - Objektnummer                   I*4
 *                             ZPOL   - Zeiger auf POL                 I*4
 *                             FERIG  - Nummer des dyn. Feldes RIG     I*4
 *                   Output:   X      - X-Koo. des Punktes             I*4
 *                             Y      - Y-Koo. des Punktes             I*4
 *       Aufgabenstellung:
 *          sucht Objekte, die mit dem gegebenen Punktobjekt verbunden
 *          sind. Die Koordinaten des Punktes werden zurueckgegeben. Die
 *          Objektnummern der verbundenen Objekte und die Relationsarten
 *          werden im dynamischen Feld gespeichert.
 *          Relationsart: 7 - Punktobjekt auf Punktobjekt
 *                        8 - Linienobjekt einseitig an Punktobjekt
 *                        9 - Linienobjekt zweiseitig an Punktobjekt
 *                       10 - Flaechenobjekt beruehrt Punktobj.
 *                       11 - Flaechenobjekt bedeckt Punktobj.
 *       Fehlerbehandlung:
 *          GETRIP =  EOKAY  i.O.
 *                 =  EKANT  3 Kanten mit gleicher ON-Nr. schneiden sich
 *                 =  EANZON Anzahl der Maschenobj. um Knotenpkt. falsch
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

/* COMMON translations */
extern struct t_rifenr {
	long int rifeon;
} rifenr; 
/* end of COMMON translations */

long FUNCTYPE getrip (HPROJECT hPr, long *on, long *zpol, long *ferig, long *x, long *y)
{
long int _l0, anzka, cont[4];
DB_ADDR dbakal(hPr), dbakfk(hPr), dbamal(hPr), dbapol(hPr), dbavgo(hPr), dbavzo(hPr);  
long feka, fema, izae, izaehl;
long testma;
long lenka, lenma, lenon;
long on1, on2, on3;
struct kal kal;
struct kfk kfk;
struct mal mal;
struct pol pol;
struct vgo vgo;
struct vzo vzo;
ErrCode RC;

/* *** Anfangswerte setzen: */
	dbapol.file_no = POL;
	dbavgo.file_no = VGO;
	dbakfk.file_no = KFK;
	dbakal.file_no = KAL;
	dbamal.file_no = MAL;
	dbavzo.file_no = VZO;
	testma = 0;

/* *** Punktkoordinaten bereitstellen: */
	dbapol.rec_no = *zpol;
	__Read (dbapol, pol);
	*x = pol.kpkrd.px;
	*y = pol.kpkrd.py;

/* *** Bearbeitung ZVGO aus POL: */
	dbavgo.rec_no = pol.zpvgo;

	do {
		__Read (dbavgo, vgo);
		if (vgo.zvgoo != *on) {
			DBASSERTM (feput (ferig, &vgo.zvgoo));
			DBASSERTM (feput (ferig, ADR (_l0, 7)));	// Pkt. auf Pkt. */
		}
		dbavgo.rec_no = vgo.znvgo;
	} while (vgo.znvgo != 0);	// nächster Satz

/* *** Bearbeitung ZVGO aus KFK: */
	if (pol.zpkfk == 0) {		// keine Kante am Punkt, zu Fläche auf Punkt
		lenma = 0;
		testma = 1;
		goto L_50;
	}

/* ***--- Feld fuer Kantenobjekte initialisieren: */
	feka = 0;
	DBASSERT (feini (&feka));

/* ***--- Feld fuer Maschenobjekte initialisieren: */
	fema = 0;
	DBASSERT (feini (&fema));

/* ***--- Kanten durchgehen: */
	anzka = 0;
	dbakfk.rec_no = pol.zpkfk;

	do {		// Einsprung nächste Kante
		anzka++;
		__Read (dbakfk, kfk);

		dbakal.rec_no = labs (kfk.zkfkk);
		__Read (dbakal, kal);

	/* ***---*** Objektnummern von Kantenobjekten: */
		dbavgo.rec_no = kal.zkvgo;
		while (dbavgo.rec_no != 0) {
			__Read (dbavgo, vgo);
			DBASSERTM (feput (&feka, &vgo.zvgoo));
			dbavgo.rec_no = vgo.znvgo;
		}

	/* ***---*** Objektnummern von Maschenobjekten: */
		dbavzo.rec_no = kal.zlm;
		while (dbavzo.rec_no != 0) {
			__Read (dbavzo, vzo);
			dbamal.rec_no = vzo.zvzoo;
			__Read (dbamal, mal);
			DBASSERTM (feput (&fema, &mal.zmvgo));
			dbavzo.rec_no = vzo.znvzo;
		}
		dbavzo.rec_no = kal.zrm;
		while (dbavzo.rec_no != 0) {
			__Read (dbavzo, vzo);
			dbamal.rec_no = vzo.zvzoo;
			__Read (dbamal, mal);
			DBASSERTM (feput (&fema, &mal.zmvgo));
			dbavzo.rec_no = vzo.znvzo;
		}
		dbakfk.rec_no = kfk.znkfk;
	} while (dbakfk.rec_no != 0);	// nächste Kante


/* ***--- dyn. Feld Kantenobjekte Laenge, sortieren: */
	DBASSERT (felen (&feka, &lenka));
	if (lenka != 0) {
		DBASSERT (flqsrt (&feka));	// sortieren

	/* ***--- Objektnr. sowie Rel.-arten 8 oder 9 ins dyn. Uebergabefeld: */
		izaehl = 1L;
		do {
			DBASSERT (feget (&feka, &izaehl, &on1));
			if ((izaehl + 2) <= lenka) {
				DBASSERT (feget (&feka, ADR (_l0, izaehl + 2), &on3));
				if (on1 == on3) // 3 Kanten mit gleicher ON-Nr. schneiden sich 
					return db_error (EKANT, 3027);
			}
			DBASSERTM (feput (ferig, &on1));
			if ((izaehl + 1) <= lenka) {
				DBASSERT (feget (&feka, ADR(_l0, izaehl + 1), &on2));
				if (on1 != on2) {	// Linienobj. berührt Punkt
					DBASSERTM (feput (ferig, ADR(_l0, 8L)));
					izaehl = izaehl + 1;
				}
				else {			// Linienobj. schneidet Punkt
					DBASSERTM (feput (ferig, ADR(_l0, 9L)));
					izaehl = izaehl + 2;
				}
			}
			else {		// Linienobj. beruehrt Punkt
				DBASSERTM (feput (ferig, ADR(_l0, 8)));
				izaehl = izaehl + 1;
			}
		} while (izaehl <= lenka);
	}
	
	DBASSERT (ferel (&feka));

/* ***--- dyn. Feld Maschenobjekte Laenge, sortieren, Red. befreien: */
	DBASSERT (felen (&fema, &lenma));
	if (lenma != 0) {
		if ((lenma % 2) != 0) 	// Anzahl der Maschenobj. um Knotenpkt. falsch
			return db_error (EANZON, 3027);
	
		DBASSERT (flqsrt (&fema));		// sortieren
		DBASSERT (flredn (&fema, &lenma));	// Redundanz befreien

	/* ***--- Objektnr. sowie Rel.-art 10 ins dyn. Uebergabefeld: */
		for (izaehl = 1; izaehl <= lenma; izaehl++) {
			DBASSERT (feget (&fema, &izaehl, &on1));
			DBASSERTM (feput (ferig, &on1));	// Flaechenobj. beruehrt Punkt
			DBASSERTM (feput (ferig, ADR(_l0, 10)));
		}
	}
	
L_50:
	rifenr.rifeon = 0L;
	DBASSERT (feini (&rifenr.rifeon));

/* ***--- WNTFND ignorieren: */
	{
	ErrInstall EI ((ErrCode)WNTFND);
	
		cont[0L] = *x;
		cont[1L] = *x;
		cont[2L] = *y;
		cont[3L] = *y;
		RC = (ErrCode)htwind (hPr, cont, htmanr, ADR(_l0, MCONT));
		if (RC != (ErrCode)EC_OKAY && RC != (ErrCode)WNTFND)
			return RC;
	}

/* ***--- beruehrende Maschenobjekte abspalten:
 * ---*** dyn. Feld Maschenobjekte Laenge, sortieren, Red. befreien: */
	DBASSERT (felen (&rifenr.rifeon, &lenon));
	if (lenon != 0) {
		DBASSERT (flqsrt (&rifenr.rifeon));
		DBASSERT (flredn (&rifenr.rifeon, &lenon));

	/* ---*** Rel.art 11 von 10 abspalten: */
		for (izaehl = 1; izaehl <= lenon; izaehl++) {
		BOOL fFlag = FALSE;
		
			DBASSERT (feget (&rifenr.rifeon, &izaehl, &on1));
			if (lenma != 0) {
				for (izae = 1; izae <= lenma; izae++) {
					DBASSERT (feget (&fema, &izae, &on2));
					if (on1 == on2) {
						fFlag = TRUE;
						break;
					}	// ON1 schon vorhanden
				}
			}
			if (!fFlag) {
				DBASSERTM (feput (ferig, &on1));	// Flaechenobj. bedeckt Punkt
				DBASSERTM (feput (ferig, ADR (_l0, 11)));
			}
		}
	}
	
// ***--- Felder für Maschenobjekte wieder freigeben
	if (testma == 0) {
		DBASSERT (ferel (&fema));
	}
	DBASSERT (ferel (&rifenr.rifeon));

return EC_OKAY;
} /* end of function */

