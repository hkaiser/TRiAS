/*Translated by FOR_C, v3.2 (B), on 06/20/91 at 14:54:52 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
#include <fcrt.h>
/*+
 *       *****************************************************************
 *       * welche Objekte sind im Container ?                            *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75019
 *       Autor:                Major, Walter
 *       Datum:                18-Jun-91
 *       Modulname:            *** FNDTO ***
 *       Routinenummer:        3054
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         FNDPU,FNDLI,FNDMA,QTFUNC,HTFUNC
 *       libdbr.a    :         -
 *       libzipedb.a :         QTWIND,HTWIND,ZREAD,SETERR,ERRFKT
 *                             FLQSRT,FLREDN,FELEN,FEGET,FEPUT,FEWRIT
 *                             FEINI,FEREL
 *       Common-Bloecke:       FENR   - enthaelt Nr. des dyn. Feldes
 *                             WOHER  - GETGI-Variante GIFND waehlen
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=FNDTO (ON,CONT,LENON,FERIG)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                             FNDTO   - Funktion                      I*4
 *
 *       Parameter: Input:    ON       - vorgegebene Objektnummer      I*4
 *                            CONT(1)  - Xmin                          I*4
 *                            CONT(2)  - Xmax                          I*4
 *                            CONT(3)  - Ymin                          I*4
 *                            CONT(4)  - Ymax                          I*4
 *                  In/Out:   LENON    - Anzahl der Objekte            I*4
 *                  Output:   FERIG    - dyn. Feld fuer Objektnummern  I*4
 *       Aufgabenstellung:
 *          Sucht Elementarobjekte, die den Container beruehren, schnei-
 *          den bzw. in ihm enthalten sind.
 *          Wenn LENON=0, werden alle Objekte gesucht, die den Container,
 *          der aus Xmin,Xmax,Ymin,Ymax gebildet wird, beruehren, schnei-
 *          den oder in ihm enthalten sind. Diese Objektnummern werden
 *          im dynamischen Feld FERIG gespeichert.
 *          Wenn LENON>0, werden alle Objekte, die in FERIG angegeben
 *          sind, wie oben geprueft und wiederum ins Feld FERIG einge-
 *          schrieben, wenn sie den Container schneiden.
 *          Achtung !: LENON als Rueckgabewert gibt die Feldlaenge der
 *                     signifikanten Objekte an!
 *          Achtung !: bei Flaechen, die Loecher enthalten (die den aeus-
 *                     seren Rand bzw. sich selbst nicht beruehren bzw.
 *                     schneiden duerfen), muss die Aussenumrandung zu-
 *                     erst gespeichert sein !
 *       Fehlerbehandlung:
 *          FNDTO =  EOKAY   i.O.
 *                   WNOON   keine Objekte gefunden
 *                   WNORIG  keine top. Relation vorhanden
 *       -----------------------------------------------------------------
 *- */
	/* PARAMETER translations */
#define	I40	0L
#define	I41	1L
#define	LV	(-1L)
#define	SHDIDN	6
#define	WNRECW	1018
	/* end of PARAMETER translations */

#include "ris.h"
#include "zipedb.h"
#include "zforc.h"

	/* COMMON translations */
extern struct t_fenr {
	long int feon;
	}	fenr;
extern struct t_woher {
	char rout[4];
	}	woher;
	/* end of COMMON translations */
long /*FUNCTION*/ fndto(on, cont, lenon, ferig)
long int *on, cont[], *lenon, *ferig;
{
LOGICAL32 ltest;
long int _do0, _do1, _do2, _l0, _l1, anzon, dbamal[2], dbaobl[2], 
	 fndto_v, iende, irc, izaehl, izaehl_, j, j_, krc, len, obl[SIZOBL], 
	 onr, zvog;
	/*                               ! Leervariable - Parameter nicht noetig
	 *
	 * *** Anfangswerte, Pruefungen: */
	fndto_v = EOKAY;
	irc = EOKAY;
	krc = EOKAY;
	strcpy( woher.rout, "FND" );
	dbaobl[0L] = NOBL;
	dbamal[0L] = NMAL;

	if (*lenon > I40) 
		goto L_100;
	/*                                       ! FERIG ist Eingabefeld */
	len = 0L;

	/* *** bei Neueingang evtl. noch offenes dyn. Feld loeschen, initial.: */
	irc = errfkt( ADR(_l0,EFLEX), ADR(_l1,0L) );
	if (irc != EOKAY) {
		fndto_v = irc;
		return( fndto_v );
	}
	irc = ferel( &fenr.feon );
	if (irc != EOKAY) {
		if (irc != EFLEX) {
			fndto_v = irc;
			return( fndto_v );
		}
	}
	irc = errfkt( ADR(_l0,EFLEX), ADR(_l1,1L) );
	if (irc != EOKAY) {
		fndto_v = irc;
		return( fndto_v );
	}

	fenr.feon = 0L;
	irc = feini( &fenr.feon );
	if (irc != EOKAY) {
		fndto_v = irc;
		return( fndto_v );
	}

	/* *** 'kein Schluessel (WNTFND) gefunden' ignorieren: */
	irc = errfkt( ADR(_l0,WNTFND), ADR(_l1,0L) );
	if (irc != EOKAY) {
		krc = irc;
		goto L_70;
	}
	/* *** Punkte suchen: */

	irc = qtwind( cont, qtfunc, ADR(_l0,SKPKRD) );

	if (irc != EOKAY) {
		if (irc != WNTFND) {
			krc = irc;
			goto L_70;
		}
	}
	/* *** Kanten suchen: */

	irc = htwind( cont, htfunc, ADR(_l0,SKCONT) );

	if (irc != EOKAY) {
		if (irc != WNTFND) {
			krc = irc;
			goto L_70;
		}
	}
	/* *** Fehlerbehandlung auf Standard setzen: */
	irc = errfkt( ADR(_l0,WNTFND), ADR(_l1,1L) );
	if (irc != EOKAY) {
		krc = irc;
		goto L_70;
	}
	/* *** keine Objekte gefunden: */
	irc = felen( &fenr.feon, &len );
	if (irc != EOKAY) {
		krc = irc;
		goto L_70;
	}
	if (len == I40) {
		irc = errfkt( ADR(_l0,WNOON), ADR(_l1,0L) );
		if (irc != EOKAY) {
			krc = irc;
			goto L_70;
		}
		irc = seterr( ADR(_l0,WNOON), ADR(_l1,3054L) );
		irc = errfkt( ADR(_l0,WNOON), ADR(_l1,1L) );
		if (irc != EOKAY) {
			krc = irc;
			goto L_70;
		}
		krc = WNOON;
		goto L_70;
		/*                       ! Ende, keine ON gefunden */
	}

	/* *** dyn.Feld der Obj.nr.sortieren,redundanzbefreien: */
	irc = flqsrt( &fenr.feon );
	if (irc != EOKAY) {
		krc = irc;
		goto L_70;
	}
	irc = flredn( &fenr.feon, &len );
	if (irc != EOKAY) {
		krc = irc;
		goto L_70;
	}

	/* *** Objektnummern ins dyn. Feld FERIG uebernehmen: */
	for (izaehl = 1L, _do0 = len; izaehl <= _do0; izaehl++) {
		izaehl_ = izaehl - 1;
		irc = feget( &fenr.feon, &izaehl, &onr );
		if (irc != EOKAY) {
			krc = irc;
			goto L_70;
		}
		if (onr != *on) {
			irc = feput( ferig, &onr );
			if (irc < I40) {
				krc = irc;
				goto L_70;
			}
		} else{
			*lenon = len - 1L;
		}
	}
	if (*lenon == I40) 
		krc = WNORIG;

	/* *** dynamisches Feld der Objektnummern freigeben: */
L_70:
	irc = ferel( &fenr.feon );
	fenr.feon = 0L;
	if (irc != EOKAY) {
		fndto_v = irc;
		return( fndto_v );
	}
	fndto_v = krc;

	/* *** Ende bei LENON=0: */
	return( fndto_v );


	/**** ON-Feld als Objekteingabe: */
L_100:
	izaehl = 1L;
	iende = *lenon;
	anzon = 0L;

	for (j = I41, _do1 = iende; j <= _do1; j++) {
		j_ = j - 1;
		irc = feget( ferig, &j, &onr );
		if (irc != EOKAY) {
			fndto_v = irc;
			return( fndto_v );
		}
		if (onr == *on) 
			goto L_150;
		dbaobl[1L] = onr;
		irc = zread( dbaobl, obl );
		if (irc != EOKAY) {
			fndto_v = ENOON;
			return( fndto_v );
		}
		if (obl[ZOKP - 1L] > I40) {
			/*                                       ! Punktobjekt */
			zvog = obl[ZOKP - 1L];
			irc = fndpu( &ltest, &zvog, cont, ADR(_l0,LV), ADR(_l1,LV) );
			if (irc != EOKAY) {
				fndto_v = irc;
				return( fndto_v );
			}
		} else if (obl[ZOVOL - 1L] > I40) {
			/*                                       ! Linienobjekt */
			zvog = obl[ZOVOL - 1L];
			irc = fndli( &ltest, &zvog, cont );
			if (irc != EOKAY) {
				fndto_v = irc;
				return( fndto_v );
			}
		} else if (obl[ZOVOMA - 1L] > I40) {
			/*                                       ! Flaechenobjekt */
			dbamal[1L] = obl[ZOVOMA - 1L];
			irc = fndma( &ltest, dbamal, cont );
			if (irc != EOKAY) {
				fndto_v = irc;
				return( fndto_v );
			}
		} else{
			goto L_150;
		}
		if (ltest) {
			anzon = anzon + I41;
			/*                                       ! Strecke oder Pkt.in Container */
			irc = fewrit( ferig, &izaehl, ADR(_l0,1L), &onr );
			if (irc != EOKAY) {
				fndto_v = irc;
				return( fndto_v );
			}
			izaehl = izaehl + I41;
		}
L_150:
		;
	}

	/* *** keine Objekte im Container: */
	if (anzon == I40) {
		irc = errfkt( ADR(_l0,WNORIG), ADR(_l1,0L) );
		if (irc != EOKAY) {
			fndto_v = irc;
			return( fndto_v );
		}
		irc = seterr( ADR(_l0,WNORIG), ADR(_l1,3054L) );
		irc = errfkt( ADR(_l0,WNORIG), ADR(_l1,1L) );
		if (irc != EOKAY) {
			fndto_v = irc;
			return( fndto_v );
		}
		fndto_v = WNORIG;
		/*                       ! Ende, keine ON gefunden */
		return( fndto_v );
	}

	/* *** nicht im Container enthaltene Objekte beseitigen: */
	if (anzon < *lenon) {
		for (j = izaehl, _do2 = iende; j <= _do2; j++) {
			j_ = j - 1;
			irc = fewrit( ferig, &izaehl, ADR(_l0,1L), &onr );
			if (irc != EOKAY) {
				fndto_v = irc;
				return( fndto_v );
			}
		}
		/* ---- dyn.Feld der Obj.nr.sortieren,redundanzbefreien: */
		irc = flqsrt( ferig );
		if (irc != EOKAY) {
			fndto_v = irc;
			return( fndto_v );
		}
		irc = flredn( ferig, lenon );
		if (irc != EOKAY) {
			fndto_v = irc;
			return( fndto_v );
		}
	}

	/* *** Ende bei LENON#0: */
	return( fndto_v );
} /* end of function */

