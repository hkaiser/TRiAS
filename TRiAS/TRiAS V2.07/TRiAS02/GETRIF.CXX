/*Translated by FOR_C, v3.1, on 02/25/91 at 09:59:00 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * sucht Geometrierelat. fuer ein Flaechenobj.                   *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75026
 *       Autor:                Major, Walter
 *       Datum:                04-Okt-90
 *       Modulname:            *** GETRIF ***
 *       Routinenummer:        3029
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         IABS
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         RIGKP,RIGIN,QTFUNC,HTFUNC
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEINI,FEREL,FELEN,FEGET,FEWRIT,FLQSRT
 *                             FLREDN,QTWIND,HTWIND,SETERR,ERRFKT
 *       Common-Bloecke:       FENR   - enthaelt Nr. des dyn. Feldes
 *       SAVE:                 /FENR/ - Feldnummercommon
 *                             LENON  - Laenge des dyn. Feldes
 *                             ZKFMRE - naechster Zeiger auf KFM
 *                             ZKPLE  - Zeiger auf ZEP
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETRIF (NL,ON,ZMAL,FERIG,X,Y)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             GETRIF - Funktion                       I*4
 *
 *       Parameter:  Input:    NL     - 0     -  Neueingang            I*4
 *                                      WFORT - naechster Knotenpkt. (nach
 *                                              WFORTR auf neuem Rand)
 *                                      WFORTR- vor letztem Pkt. eines
 *                                              Randes bei F.obj., dann
 *                                              letzter Pkt., danach neuer
 *                                              Innenrand
 *                                      WFORTI- es folgen bei F.obj. voel-
 *                                              lig innen liegende Obj.,
 *                                              bzw. die Fl. voll ueber-
 *                                              deckende Flaechen
 *                   Output:   NL     - 0     - erfolgreiches Ende
 *                                      WFORT - s. oben
 *                                      WFORTR- s. oben
 *                                      WFORTI- s. oben
 *                   Input:    ON     - Objektnummer                   I*4
 *                             ZMAL   - Zeiger auf MAL                 I*4
 *                             FERIG  - Nr. des dyn. Feldes            I*4
 *                   Output:   X,Y    - Koo. eines Knotenpunktes des   I*4
 *                                      Flaechenrandes; X,Y=-1023998976,
 *                                      d.h. unbestimmte Koo.(kein K.pkt.)
 *       Aufgabenstellung:
 *          sucht Objekte, die mit dem gegebenen F.-Objekt verbunden sind.
 *          Gibt die Koordinaten des Knotenpunktes an. Die Objektnummern
 *          der verbundenen Objekte und die Relationsart werden im dyn.
 *          Feld FERIG uebergeben.
 *          Relationsart: 1 - L.obj. einseitig an Knotenpkt. ohne Ueberl.
 *                        2 - L.obj. durch K.pkt. ohne Ueberl. (1+1)
 *                        3 - L.obj. ueberlagert 1 Kante
 *                        4 - L.obj. 1 Kante ueberl., 1 Kante frei (1+3)
 *                        5 - P.obj. ueberlagert Knotenpunkt
 *                        6 - L.obj. ueberlagert 2 Kanten (3+3)
 *                       10 - F.obj. beruehrt Knotenpkt.
 *                       11 - F.obj. bedeckt Knotenpkt.
 *                       12 - Objekt voellig in F.obj.
 *                       13 - F.obj. bedeckt voellig F.obj.
 *       Logik:
 *          mit QTWIND und HTWIND werden zuerst alle Objekte ermittelt,
 *          die im Flaechencontainer liegen (dyn. Feld FEON). Danach
 *          werden knotenpunktweise (RIGKP) alle Objekte gesucht, die mit
 *          dem Rand verbunden sind (auch bei Innenraendern); sie werden
 *          aus FEON gestrichen (ausser Rel. 11). Fuer die in FEON ver-
 *          bliebenen Objekte wird nun mit RIGIN entschieden, ob sie
 *          voellig in der Flaeche liegen oder ob Flaechenobjekte die
 *          gegebene Flaeche voll ueberdecken.
 *       Fehlerbehandlung:
 *          GETRIF =  EOKAY  i.O.
 *                 =  ENOON  eigene Obj.nr. nicht gefunden
 *                 =  EZKAL  Zeiger auf KAL darf nicht 0 sein
 *                 =  WFORT  es folgt naechster Knotenpunkt
 *                 =  WFORTR letzter Kn.pkt. eines Randes, dann neuer Rand
 *                 =  WFORTI voellig innen liegende Obj. bzw. voll ueber-
 *                           deckende Flaechen folgen
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

/* COMMON translations */
extern struct t_fenr {
	long int feon;
	}	fenr;
/* end of COMMON translations */

long FUNCTYPE getrif (HPROJECT hPr, long *nl, long *on, long *zmal, long *ferig, long *x, long *y)
{
long int _l0, cont[5];
DB_ADDR dbakal(hPr), dbakfm(hPr), dbamal(hPr);
long ilen,  izaehl, izaeri, lenrig;
struct kal kal;
struct kfm kfm;
struct mal mal;
long onhi, onri, riart, wert, zkfm, zkl, zkln, zkpla, zkplan;
ErrCode RC;
static long int lenon = 0, zkfmre = 0, zkple = 0;

/* *** Anfangswerte setzen: */
	dbamal.file_no = MAL;
	dbakfm.file_no = KFM;
	dbakal.file_no = KAL;

	ilen = 1L;
	wert = 0L;

/* *** Fortsetzung nächster Knotenpunkt der Flaechenumrandung
 *     oder innere Objekte: */
	if (*nl == WFORT) {
		zkfm = zkfmre;
		zkpla = zkple;
		zkple = 0L;
		if (zkfm != 0) goto L_10;
		if (zkpla != 0)	goto L_20;
	}
	else if (*nl == WFORTR) {
		zkpla = zkple;
		zkple = 0L;
		*nl = WFORT;
		goto L_20;
	}
	else if (*nl == WFORTI) {
		*x = -1023998976;	// Koordinaten unbestimmt
		*y = -1023998976;
		DBASSERT (rigin (hPr, on, ferig));	// ob restl. Obj. voellig innen oder voll ueberdeckt
		*nl = 0L;
		DBASSERT (ferel (&fenr.feon));
		fenr.feon = 0L;
		return EC_OKAY;
	}

/* *** Flächencontainer bilden: */
	dbamal.rec_no = *zmal;
	__Read (dbamal, mal);
	cont[0L] = mal.mcont.mxmin;
	cont[1L] = mal.mcont.mxmax;
	cont[2L] = mal.mcont.mymin;
	cont[3L] = mal.mcont.mymax;
	cont[4] = 1;		// exakt suchen
	
/* *** Objekte im Flächencontainer suchen:
 * ---*** dynamisches Feld der Objektnummern initialisieren: */
	if (*nl == 0) {
	ErrInstall EI ((ErrCode)EFLEX);

		RC = (ErrCode)ferel (&fenr.feon);
		if (RC != (ErrCode)EC_OKAY && RC != (ErrCode)EFLEX)
			return RC;
	}
	fenr.feon = 0L;
	DBASSERT (feini (&fenr.feon));

/* ---*** 'kein Schluessel (WNTFND) gefunden' ignorieren: */
	{
	ErrInstall EI ((ErrCode)WNTFND);

	/* ---*** Punkte suchen: */
		RC = (ErrCode)qtwind (hPr, cont, qtfunc, ADR (_l0, KPKRD));
		if (RC != (ErrCode)EC_OKAY && RC != (ErrCode)WNTFND)
			return RC;

	/* ---*** Kanten suchen: */
		RC = (ErrCode)htwind (hPr, cont, htfunc, ADR (_l0, KCONT));
		if (RC != (ErrCode)EC_OKAY && RC != (ErrCode)WNTFND)
			return RC;
	}

/* ---*** keine Objekte gefunden: */
	DBASSERT (felen (&fenr.feon, &lenon));
	if (lenon == 0)		// eigene lONr nicht gefunden
		return db_error (ENOON, 3029L);

	if (lenon == 1) {
		*nl = 0L;
		*x = -1023998976;	// Koordinaten unbestimmt
		*y = -1023998976;
		DBASSERT (ferel (&fenr.feon));
		fenr.feon = 0L;
		return EC_OKAY;
	}

/* ---*** dyn.Feld der Obj.nr.sortieren,redundanzbefreien: */
	DBASSERT (flqsrt (&fenr.feon));
	DBASSERT (flredn (&fenr.feon, &lenon));

/* ---*** vorgegebene Objektnummer im dyn. Feld 0 setzen: */
	for (izaehl = 1; izaehl <= lenon; izaehl++) {
		DBASSERT (feget (&fenr.feon, &izaehl, &onhi));
		if (*on == onhi) {
			DBASSERT (fewrit (&fenr.feon, &izaehl, &ilen, &wert));
			break;
		}
	}
	DBASSERT (flqsrt (&fenr.feon));

/* *** Knotenpunkte der Flächenumrandung bearbeiten: */
	zkfm = mal.zmkfm;

L_10:
	dbakfm.rec_no = zkfm;
	__Read (dbakfm, kfm);
	zkl = kfm.zkfmk;
	zkfmre = kfm.znkfm;		// merken nächster ZKFM
	
	dbakal.rec_no = labs (zkl);
	__Read (dbakal, kal);
	if (zkl < 0) {
		zkpla = kal.zep;
		zkple = kal.zap;
	}
	else if (zkl > 0) {
		zkpla = kal.zap;
		zkple = kal.zep;
	}
	else				// Zeiger auf KAL darf nicht 0 sein
		return db_error (EZKAL, 3029L);

/* ---*** Pruefung, ob Innenrand folgt: */
	if (zkfmre != 0) {
		dbakfm.rec_no = zkfmre;
		__Read (dbakfm, kfm);
		zkln = kfm.zkfmk;	// Zeiger nächste Kante aus KFM

		dbakal.rec_no = labs (zkln);
		__Read (dbakal, kal);
		if (zkln < 0) zkplan = kal.zep;
		else          zkplan = kal.zap;
		if (zkplan == zkple) 
			*nl = WFORT;
		else
			*nl = WFORTR;
	}

/* ---*** Koo. des Knotenpkt., Einsprung letzter Knoten letzte Kante: */
L_20:
	DBASSERT (rigkp (hPr, on, &zkpla, ferig, x, y));

/* *** Objektnummern von FERIG in FEON 0 setzen: */
	DBASSERT (felen (ferig, &lenrig));
	if (lenrig == 0 || lenon <= 1)	// keine Objekte am Knotenpunkt
		goto L_100;

	for (izaeri = 1; izaeri <= lenrig; izaeri += 2) {
	// Schrittweite 2, weil immer Nr. + Art folgt
		DBASSERT (feget (ferig, &izaeri, &onri));
		DBASSERT (feget (ferig, ADR (_l0, izaeri + 1), &riart));
		if (riart != 11) {
		/* Knotenpkt. voll ueberdeckende Fl.; spätere
		 * Prüfung, ob Relationsart 13 zutrifft */
			for (izaehl = 2; izaehl <= lenon; izaehl++) {
				DBASSERT (feget (&fenr.feon, &izaehl, &onhi));
				if (onri == onhi) {
					DBASSERT (fewrit (&fenr.feon, &izaehl, &ilen, &wert));
					break;
				}
			}
		}
	}

/* ---*** dyn.Feld der Obj.nr.sortieren, redundanzbefreien: */
	DBASSERT (flqsrt (&fenr.feon));
	DBASSERT (flredn (&fenr.feon, &lenon));

/* *** weitere Knotenpunkte ?: */
L_100:
	if (zkfmre != 0) {
		if (*nl == 0) {
			DBASSERT (ferel (&fenr.feon));
			fenr.feon = 0L;
		}
		return *nl;
	}
	else if (zkple != 0) {
		*nl = WFORT;
		return WFORT;
	}
	else {
		if (lenon > 1)
			*nl = WFORTI;	// völlig innere Obj. oder voll ueberd. Fl.
		else
			*nl = 0L;	// Ende */
	}

	if (*nl == 0) {
		DBASSERT (ferel (&fenr.feon));
		fenr.feon = 0L;
	}

return EC_OKAY;
} /* end of function */

