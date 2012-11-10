/*Translated by FOR_C, v3.1, on 02/25/91 at 10:03:16 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * sucht Geometrierelationen fuer einen Knotenpunkt              *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75016
 *       Autor:                Major, Walter
 *       Datum:                12-Jul-90
 *       Modulname:            *** RIGKP ***
 *       Routinenummer:        3032
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         IABS,MOD
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         HTMANR
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEPUT,SETERR,FEINI,FEREL,FELEN
 *                             FEGET,FEWRIT,FLQSRT,FLREDN,HTWIND,ERRFKT
 *       Common-Bloecke:       RIFENR  - enthaelt Nr. des dyn. Feldes
 *       SAVE:                 /RIFENR/ : Feldnummercommon
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=RIGKP (ON,ZKPLA,FERIG,X,Y)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             RIGKP - Funktion                        I*4
 *
 *       Parameter   Input:    ON     - Objektnummer                   I*4
 *                             ZKPLA  - Zeiger auf KPL                 I*4
 *                             FERIG  - Nummer des dyn. Feldes RIG     I*4
 *                   Output:   X,Y    - Koo. des Knotenpunktes         I*4
 *       Aufgabenstellung:
 *          sucht Objekte, die mit dem gegebenen Knotenpunkt verbunden
 *          sind, gibt die Koordinaten des Knotenpunktes, die Objektnummer
 *          des verbundenen Objektes und die Relationsart an.
 *          Relationsart: 1 - Linienobj. beginnt oder endet an Knotenpunkt
 *                            ohne Ueberlagerung
 *                        2 - Linienobj. geht durch Knotenpunkt ohne
 *                            Ueberlagerung
 *                        3 - Linienobj. ueberlagert eine Kante
 *                        4 - Linienobj. ueberlagert eine Kante und laeuft
 *                            in/aus Knotenpunkt
 *                        5 - Punktobj. ueberlagert Knotenpunkt
 *                        6 - Linienobj. ueberlagert zwei Kanten
 *                       10 - Flaechenobjekt beruehrt Knotenpunkt
 *                       11 - Flaechenobjekt ueberlagert Knotenpunkt
 *       Fehlerbehandlung:
 *          RIGKP =  EOKAY   i.O.
 *                =  EANZON  Anzahl der Maschenobj. um Knotenpkt. falsch
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

extern struct t_rifenr {
	long int rifeon;
} rifenr;


long FUNCTYPE rigkp (HPROJECT hPr, long *on, long *zkpla, long *ferig, long *x, long *y)
{
long lotest;
long _l0, cont[4];
DB_ADDR dbakal(hPr), dbakfk(hPr), dbakpl(hPr), dbamal(hPr), dbavgo(hPr), dbavzo(hPr);
long feka, fema, izae, izaehl;
struct kal kal;
struct kfk kfk;
struct kpl kpl;
struct mal mal;
struct vgo vgo;
struct vzo vzo;
ErrCode RC;
long lenka, lenma, lenon, lenwri, on1, on2, rel1, rel2, zaehl1, zaehl2, zvgo;

/* *** Anfangswerte setzen: */
	dbakal.file_no = KAL;
	dbakpl.file_no = KPL;
	dbavgo.file_no = VGO;
	dbakfk.file_no = KFK;
	dbavzo.file_no = VZO;
	dbamal.file_no = MAL;

/* *** Koo. des Knotenpunktes: */
	dbakpl.rec_no = *zkpla;
	__Read (dbakpl, kpl);
	*x = kpl.pkrd.kpx;
	*y = kpl.pkrd.kpy;

/* *** Bearbeitung ZVGO aus KPL fuer Knotenpunkt: */
	zvgo = kpl.zkpvgo;
	if (zvgo != 0) {
		dbavgo.rec_no = zvgo;
		do {
			__Read (dbavgo, vgo);
			DBASSERTM (feput (ferig, &vgo.zvgoo));
			DBASSERTM (feput (ferig, ADR (_l0, 5L)));	// Pkt.obj. auf Knotenpkt.
		} while ((dbavgo.rec_no = vgo.znvgo) != 0);
	}
	
/* *** Bearbeitung ZVGO aus KL um Knotenpunkt:
 * ---*** Felder fuer Kantenobjekte und anliegende Flaechen init.: */
	feka = 0L;
	DBASSERT (feini (&feka));	// Feld fuer Linienobj., die den Knotenpkt. beruehren
	fema = 0L;
	DBASSERT (feini (&fema));	// Feld fuer Maschenobj., die den Knotenpkt. beruehren

/* ---*** gehoert Kante zum Linienobj.?: */
	dbakfk.rec_no = kpl.zkpkfk;
	do {	// für alle Kanten
		__Read (dbakfk, kfk);		// nächste Kante
		dbakal.rec_no = labs (kfk.zkfkk);
		__Read (dbakal, kal);
		lotest = FALSE;
		if (kal.zkvgo != 0) {
			dbavgo.rec_no = kal.zkvgo;	// ist Kante einer Flaechenumrandung
			do {
				__Read (dbavgo, vgo);	// Einsprung nächster ZVGO
				if (vgo.zvgoo == *on) 
					lotest = TRUE;
			} while ((dbavgo.rec_no = vgo.znvgo) != 0);
	
		/* ---*** Nr. schneidender bzw. ueberlagernder Li-Objekte speichern: */
			dbavgo.rec_no = kal.zkvgo;
			do {
				__Read (dbavgo, vgo);		// Einsprung naechster ZVGO
				if (vgo.zvgoo != *on) {
					DBASSERTM (feput (&feka, &vgo.zvgoo));	// Objektnr. speichern
					if (lotest) {
						DBASSERTM (feput (&feka, ADR(_l0, 3L)));	// überlagerndes Objekt
					}
					else {
						DBASSERTM (feput (&feka, ADR(_l0, 1L)));	// schneidendes Objekt
					}
				}
			} while ((dbavgo.rec_no = vgo.znvgo) != 0);
		}

	/* ---*** Objektnummern von Maschenobjekten: */
	/* Einsprung mit Flächenumrandungskante */
		if (kal.zlm != 0) {
		// linke Masche
			dbavzo.rec_no = kal.zlm;
			do {
				__Read (dbavzo, vzo);	// Einsprung naechster ZVZO
				dbamal.rec_no = vzo.zvzoo;
				__Read (dbamal, mal);
				if (mal.zmvgo != *on)	// nicht vorgegebenes Objekt */
					DBASSERTM (feput (&fema, &mal.zmvgo));
			} while ((dbavzo.rec_no = vzo.znvzo) != 0);
		} /* else */
		if (kal.zrm != 0) {
		// rechte Masche
			dbavzo.rec_no = kal.zrm;
			do {
				__Read (dbavzo, vzo);	// Einsprung naechster ZVZO
				dbamal.rec_no = vzo.zvzoo;
				__Read (dbamal, mal);
				if (mal.zmvgo != *on)	// nicht vorgegebenes Objekt */
					DBASSERTM (feput (&fema, &mal.zmvgo));
			} while ((dbavzo.rec_no = vzo.znvzo) != 0);
		}
		dbakfk.rec_no = kfk.znkfk;
	} while (kfk.znkfk != 0);	// nächste Kante

/* *** Objektnummern von Linienobj. ins RIG-Feld:
 * ---*** Laenge des Feldes: */
	DBASSERT (felen (&feka, &lenka));

/* ---*** Relationen der Kanten: */
	if (lenka != 0) {
	/* ---*** Objektnr. sowie Rel.-arten 1,2,3,4,6 ins dyn. Uebergabefeld: */
		lenwri = 1L;		// Laenge fuer FEWRIT
		for (zaehl1 = 1; zaehl1 <= lenka; zaehl1 += 2) {
		BOOL fFlag = FALSE;
		
			DBASSERT (feget (&feka, &zaehl1, &on1));
			if (on1 == 0) 
				continue;
			DBASSERTM (feput (ferig, &on1));
	
			for (zaehl2 = zaehl1 + 2; zaehl2 <= lenka; zaehl2 += 2) {
				DBASSERT (feget (&feka, &zaehl2, &on2));
				if (on1 == on2) {
					DBASSERT (feget (&feka, ADR(_l0, zaehl1 + 1), &rel1));
					DBASSERT (feget (&feka, ADR(_l0, zaehl2 + 1), &rel2));
					DBASSERTM (feput (ferig, ADR(_l0, rel1 + rel2)));
					DBASSERT (fewrit (&feka, &zaehl2, &lenwri, ADR(_l0, 0L)));
					fFlag = TRUE;
					break;
				}
			}

			if (!fFlag) {
				DBASSERT (feget (&feka, ADR(_l0,zaehl1 + 1), &rel1));
				DBASSERTM (feput (ferig, &rel1));
			}
		}
	}
/* ---*** Feld fuer Kantenobjekte wieder freigeben: */
	DBASSERT (ferel (&feka));

/* *** dyn. Feld Maschenobjekte Laenge, sortieren, Red. befreien: */
	DBASSERT (felen (&fema, &lenma));	// Länge des dyn. Feldes 
	if (lenma != 0) {
		if ((lenma % 2) != 0)
			return db_error (EANZON, 3028);	// Anzahl der Maschenobj. um Knotenpkt. falsch
	
		DBASSERT (flqsrt (&fema));		// sortieren
		DBASSERT (flredn (&fema, &lenma));	// Redundanz befreien
	
	/* ***--- Objektnr. sowie Rel.-art 10 ins dyn. Uebergabefeld: */
		for (izaehl = 1; izaehl <= lenma; izaehl++) {
			DBASSERT (feget (&fema, &izaehl, &on1));
			DBASSERTM (feput (ferig, &on1));
			DBASSERTM (feput (ferig, ADR(_l0, 10L)));	// Flächenobj. beruehrt Punkt */
		}
	}

/* *** Maschenobjekte auf Punkt:
 * ***--- Feld fuer Maschenobjekte, die Punkt ueberdecken, init.: */
	rifenr.rifeon = 0L;
	DBASSERT (feini (&rifenr.rifeon));
	{	/* ***--- HTWIND rufen: */
	ErrInstall EI ((ErrCode)WNTFND);

		cont[0L] = *x;
		cont[1L] = *x;
		cont[2L] = *y;
		cont[3L] = *y;
	
		RC = (ErrCode)htwind (hPr, cont, htmanr, ADR(_l0, MCONT));
		if (RC != EC_OKAY && RC != WNTFND)
			return RC;
	}
	
/* ***--- beruehrende Maschenobjekte abspalten:
 * ---*** dyn. Feld Maschenobjekte Laenge, sortieren, Red. befreien: */
	DBASSERT (felen (&rifenr.rifeon, &lenon));	// Länge des dyn. Feldes
	if (lenon != 0) {
		DBASSERT (flqsrt (&rifenr.rifeon));		// sortieren
		DBASSERT (flredn (&rifenr.rifeon, &lenon));	// Redundanz befreien
	
	/* ---*** Relationsart 11 von 10 abspalten: */
		for (izaehl = 1L; izaehl <= lenon; izaehl++) {
		BOOL fFlag = FALSE;
		
			DBASSERT (feget (&rifenr.rifeon, &izaehl, &on1));
			if (on1 == *on)
				continue;		// vorgegebene Objektnummer */
			for (izae = 1; izae <= lenma; izae++) {
				DBASSERT (feget (&fema, &izae, &on2));
				if (on1 == on2) {
					fFlag = TRUE;
					break;	// ON1 schon vorhanden
				}
			}
			if (!fFlag) {
				DBASSERTM (feput (ferig, &on1));
				DBASSERTM (feput (ferig, ADR(_l0, 11L)));	// Flächenobj. bedeckt Punkt
			}
		}
	}
	
/* ***--- Felder für Maschenobjekte wieder freigeben: */
	DBASSERT (ferel (&fema));
	DBASSERT (ferel (&rifenr.rifeon));
	
return EC_OKAY;
} /* end of function */

