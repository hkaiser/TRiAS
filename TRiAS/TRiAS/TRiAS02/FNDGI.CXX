/*Translated by FOR_C, v3.1, on 02/25/91 at 11:38:43 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * welche Objekte sind im Container ?                            *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75019
 *       Autor:                Major, Walter
 *       Datum:                26-Nov-90
 *       Modulname:            *** FNDGI ***
 *       Routinenummer:        3008
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         FNDPU,FNDLI,FNDMA,QTFUNC,HTFUNC
 *       libdbr.a    :         -
 *       libzipedb.a :         QTWIND,HTWIND,ZREAD,SETERR,ERRFKT,FEINI
 *                             FEREL,FLQSRT,FLREDN,FEREAD,FELEN
 *       Common-Bloecke:       FENR   - enthaelt Nr. des dyn. Feldes
 *                             WOHER  - GETGI-Variante GIFND waehlen
 *       SAVE       :          FEZAE  - Feldzaehler, jeweiliger Beginn bei
 *                                      Nachladen
 *                             LEN    - Laenge des dyn. Feldes
 *                             /FENR/ - Feldnummercommon
 *                             /WOHER/- Common WOHER
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=FNDGI (NL,CONT,ON)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                                       IRC=WDHLG bei notw. Wiederholung
 *                             FNDGI   - Funktion                      I*4
 *
 *       Parameter:            NL      - Nachladecode                  I*4
 *                                       bei 1.Aufruf=0, bei Wieder-
 *                                       holung=WDHLG
 *                            CONT(1)  - Xmin                          I*4
 *                            CONT(2)  - Xmax                          I*4
 *                            CONT(3)  - Ymin                          I*4
 *                            CONT(4)  - Ymax                          I*4
 *                             ON      - Feld fuer Objektnummern       I*4
 *                             ON(1)   - max. Laenge
 *                             ON(2)   - akt. Laenge
 *                             ON(3)   - Objektnummer usw.
 *       Aufgabenstellung:
 *          Sucht Elementarobjekte, die den Container beruehren, schnei-
 *          den bzw. in ihm enthalten sind.
 *          Wenn ON(2)=0, werden alle Objekte sequentiell geprueft, ob
 *          sie den Container, der aus Xmin,Xmax,Ymin,Ymax gebildet wird,
 *          beruehren,schneiden oder ob sie in ihm enthalten sind. Diese
 *          Objektnummern werden im Feld ON ab ON(3) gespeichert.
 *          Wenn ON(2)>0, werden alle Objekte, die im ON-Feld angegeben
 *          sind, wie oben geprueft und wiederum ab ON(3) ins ON-Feld
 *          eingeschrieben.
 *          ON(2) gibt jeweils die Anzahl der gefundenen Objekte an.
 *          Achtung !: bei Flaechen, die Loecher enthalten (die den aeus-
 *                     seren Rand bzw. sich selbst nicht beruehren bzw.
 *                     schneiden duerfen), muss die Aussenumrandung zu-
 *                     erst gespeichert sein !
 *       Fehlerbehandlung:
 *          FNDGI =  EOKAY   i.O.
 *                   WDHLG   bei notwendiger Wiederholung
 *                   WNOON   keine Objekte gefunden
 *                   ENODIM  ON-Feld < 3
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

	/* COMMON translations */
struct t_fenr {
	long int feon;
	}	fenr = { 0 };
extern struct t_woher {
	char rout[4];
	}	woher;
	/* end of COMMON translations */


extern "C" 
long EXPORT02 FUNCTYPE fndgi (HPROJECT hPr, long *nl, long *cont, long *on)
{
long ltest;
DB_ADDR dbamal(hPr);
DB_ADDR_OBL dbaobl(hPr);
struct obl obl;
ErrCode RC;
long int _do0, _l0, _l1, iende, izaehl, j, j_, lenakt, lenmax, zvog;
static long int fezae = 0, len = 0;

/**** bei ON(2)=0: NL bei 1. Eingang gleich 0, bei wiederholtem Eingang
 ****                                                    gleich WDHLG
 **** bei ON(2) ungleich 0: ON-Feld als Objekteingabefeld verwenden
 * */
/* *** Anfangswerte, Pruefungen: */
	strcpy (woher.rout, "FND");

//	dbaobl.file_no = OBL;
	dbamal.file_no = MAL;

	if (on[0] < 3) return (long)db_error ((short)ENODIM, 3008);

	if (*nl == WDHLG) goto L_50;

/* restl. Werte holen */
	if (on[1] > 0L)	goto L_100;

/* ON ist Eingabefeld */
	fezae = 1L;
	len = 0L;

/* *** bei Neueingang evtl. noch offenes dyn. Feld loeschen, initial.: */
	{
	ErrInstall EFlex ((ErrCode)EFLEX);
	
		if ((RC = (ErrCode)ferel (&fenr.feon)) != EC_OKAY && RC != (ErrCode)EFLEX)
			return RC;
	}

	fenr.feon = 0L;
	DBASSERT (feini (&fenr.feon));

/* *** 'kein Schluessel (WNTFND) gefunden' ignorieren: */
	{
	ErrInstall EI ((ErrCode)WNTFND);
	
	/* *** Punkte suchen: */
		if ((RC = (ErrCode)qtwind (hPr, cont, qtfunc, ADR(_l0, KPKRD))) != EC_OKAY && RC != (ErrCode)WNTFND)
			return RC;

	/* *** Kanten suchen: */
		if ((RC = (ErrCode)htwind (hPr, cont, htfunc, ADR(_l0, KCONT))) != EC_OKAY && RC != (ErrCode)WNTFND)
			return RC;
	}


/* *** keine Objekte gefunden: */
	DBASSERT (felen (&fenr.feon, &len));
	if (len == 0) return (long)db_error ((short)WNOON, 3008, "");

/* *** dyn.Feld der Obj.nr.sortieren,redundanzbefreien: */
	DBASSERT (flqsrt (&fenr.feon));
	DBASSERT (flredn (&fenr.feon, &len));

/* *** Uebergabe des dyn. Feldes: */
L_50:
	on[1] = 0L;
	*nl = 0L;
	lenmax = on[0] - 2;
	lenakt = len - fezae + 1;
	if (lenakt <= lenmax) {
		DBASSERT (feread (&fenr.feon, &fezae, &lenakt, &on[2]));
		on[1] = lenakt;
	} else {
		DBASSERT (feread (&fenr.feon, &fezae, &lenmax, &on[2]));
		on[1L] = lenmax;
		*nl = WDHLG;
		fezae = fezae + lenmax;
		return WDHLG;	/* Ende mit erforderlichem Nachladen */
	}

/* *** dynamisches Feld der Objektnummern freigeben: */
	DBASSERT (ferel (&fenr.feon));
	fenr.feon = 0L;
	return EC_OKAY;

/* *** ON-Feld als Objekteingabe: */
L_100:
	izaehl = 3L;
	iende = on[1];
	on[1L] = 0L;
	for (j = 1, _do0 = iende; j <= _do0; j++) {
		j_ = j - 1;
		dbaobl.rec_no = on[j_ + 2];
		__Read (dbaobl, obl);
		if (obl.zokp > 0){			/* Punktobjekt */
			zvog = obl.zokp;
			DBASSERT (fndpu (hPr, &ltest, &zvog, cont, ADR(_l0, -1), ADR(_l1, -1)));
		}
		else if (obl.zovol > 0) {		/* Linienobjekt */
			zvog = obl.zovol;
			DBASSERT (fndli (hPr, &ltest, &zvog, cont));
		}
		else if (obl.zovoma > 0) {		/* Flaechenobjekt */
			dbamal.rec_no = obl.zovoma;
			DBASSERT (fndma (hPr, &ltest, &dbamal, cont));
		}
		if (ltest) {
			on[1] = on[1] + 1;
		/* Strecke oder Pkt.in Container */
			on[izaehl - 1] = on[j_ + 2];
			izaehl++;
		}
	}

return EC_OKAY;
} /* end of function */
