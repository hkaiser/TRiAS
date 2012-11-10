/*Translated by FOR_C, v3.1, on 02/25/91 at 10:00:36 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * sucht Geometrierelationen fuer ein Linienobjekt               *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75016
 *       Autor:                Major, Walter
 *       Datum:                11-Jul-90
 *       Modulname:            *** GETRIL ***
 *       Routinenummer:        3028
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         IABS,MOD
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         RIGKP
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,SETERR
 *       Common-Bloecke:       -
 *       SAVE:                 ZVOLRE : Zeiger auf VOL
 *                             ZKPLE  : Zeiger auf KPL (Kantenendpunkt)
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETRIL (NL,ON,ZVOL,FERIG,X,Y)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             GETRIL - Funktion                       I*4
 *
 *       Parameter:  Input:    NL     - wenn 0, Neueingang             I*4
 *                                    - wenn WFORT, naechster Knotenpkt.
 *                   Output:   NL     - wenn 0, erfolgreiches Ende
 *                                    - wenn WFORT, noch Knotenpkt. vorh.
 *                   Input:    ON     - Objektnummer                   I*4
 *                             ZVOL   - Zeiger auf VOL                 I*4
 *                             FERIG  - Nummer des dyn. Feldes RIG     I*4
 *                   Output:   X,Y    - Koo. des Knotenpunktes         I*4
 *       Aufgabenstellung:
 *          sucht Objekte, die mit dem gegebenen Linienobjekt verbunden
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
 *                       11 - Flaechenobjekt ueberdeckt Knotenpunkt
 *       Fehlerbehandlung:
 *          GETRIL=  EOKAY  i.O.
 *                =  WFORT  noch weitere Knotenpunkte vorhanden
 *                =  EZKAL  Zeiger auf KAL darf nicht Null sein
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

long FUNCTYPE getril (HPROJECT hPr, long *nl, long *on, long *zvol, long *ferig, long *x, long *y)
{
DB_ADDR dbakal(hPr), dbavol(hPr);
struct kal kal; 
struct vol vol;
long zkl, zkpla;
ErrCode RC;
static long int zkple = 0, zvolre = 0;

/* *** Anfangswerte setzen: */
	dbavol.file_no = VOL;
	dbakal.file_no = KAL;

/* *** 1. oder naechster Knotenpunkt: */
	if (*nl == WFORT) {		// nächster Knotenpunkt
		*zvol = zvolre;
		zkpla = zkple;
		zkple = 0L;
		if (*zvol != 0) goto L_10;
		if (zkpla != 0)	goto L_20;
	}

/* *** 1. Kante oder Einsprung naechste Kante aus VOL: */
L_10:
	dbavol.rec_no = *zvol;
	__Read (dbavol, vol);
	zkl = vol.zvolk;
	zvolre = vol.znvol; 		// merken nächster ZVOL 

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
		return db_error (EZKAL, 3028L);

/* *** Koo. des Knotenpunktes, Einsprung letzter Knoten letzte Kante: */
L_20:
	DBASSERT (rigkp (hPr, on, &zkpla, ferig, x, y));

/* *** Ende: */
	if (zvolre != 0 || zkple != 0) {
		*nl = WFORT;
		return WFORT;
	}
	else
		*nl = 0L;

return EC_OKAY;
} /* end of function */

