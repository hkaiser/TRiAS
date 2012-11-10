/*Translated by FOR_C, v3.2 (B), on 05/28/91 at 09:26:17 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcrt.h>
/*+
 *       *****************************************************************
 *       * Suchen aller Objekte mit der gleichen Merkmalsinformation     *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, Bereich 2
 *       Dokumentationsnummer: AD2-610-A64300
 *       Autor:                Kupper, P.            
 *       Datum:                29-JUNI-89
 *       Version:              02.04.1990
 *       Modulname:            *** FNDMI ***
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       DBN.OLB   :           LOPEN,LCLOSE,IFND,DATVER,FNDMW,READMK,FINDMK
 *                             ILSATZ,MITST
 *       Common-Bloecke:       DBDAT,DBCOM,SAVE
 *       -----------------------------------------------------------------
 *       Aufruf:               FNDMI(IRC,MKO,[TKZ1],[WI1],[TKZ2],[WI2],ON)
 *       Parameter:            alle Parameter sind I*4 Variablen ausser
 *                             WIi -> REAL*8   
 *       Alle Parameter sind angegeben, bei wahlweiser Angabe der
 *       Parameter   Belegung des Parameters mit -1
 *
 *             INPUT ->   MKO - vorgegebene Merkmalscode
 *                      TKZi - Testkennzeichen(in Verb. mit WI):
 *                                       LT - kleiner als
 *                                       LE - kleiner oder gleich
 *                                       EQ - gleich
 *                                       GE - groesser oder gleich
 *                                       GT - groesser als
 *                       WIi - Wert fuer die Merkmalsinformation(REAL*8)
 *                      ON(1)- Dimension des ON- Feldes, Belegung erfolgt 
 *                             im rufenden Programm
 *            OUTPUT ->  IRC - Fehlercode
 *                      ON(2)- aktuelle Laenge, ergibt sich aus der Anzahl
 *                             der gefundenen Objekte
 *                   ab ON(3)- Abspeicherung der gefundenen Objektnummern     
 *       Aufgabenstellung:
 *          Suchen aller Objekte eines Merkmalscodes mit der gleichen
 *          Merkmalsinformation
 *       Funktion:
 *          Die Basisfunktion FNDMI liefert alle Objektnummern die ein
 *          spezielles Merkmal (definiert durch MK und Merkmalswert)besitzt.
 *          Ist der Parameter der Merkmalsinformation (WI) nicht ange-
 *          geben, ist die Analyse nur auf den Merkmalscode beschraenkt.
 *          Ist der Parameter WI angegeben wird zusaetzlich eine Auswahl
 *          getroffen und nur die gefundenen Objekte abgespeichert, die die
 *          geforderte Merkmalsinformation ( entspr. TKZ ) besitzen. 
 *          Die gefundenen Objekte werden im ON-Feld dem Anwender uebergeben.
 *       Fehlerbehandlung:
 *          Zur Fehler- bzw.Warnungsausgabe wird das Unterprogramm ERREX
 *          gerufen. Dabei sind:
 *       Fehler : IRC n.g. 0  -> Fehler
 *                IRC = 401   -> ON- Feld zu klein definiert
 *                IRC = 433   -> Fehler in der Parameterliste
 *                IRC = 444   -> ges.Merkmal nicht im Wertebereich
 *                IRC < 0     -> Wiederholung,wenn Anzahl der Objekte
 *                               groesser als Dim. des ON-Feldes
 *       -----------------------------------------------------------------
 *- */
	/* PARAMETER translations */
#define	ROUTCD	5000L
#define	SHDIDN	6L
#define	WNRECW	1018L
	/* end of PARAMETER translations */

#include "ris.h"
#include "zipedb.h"
#include "zforc.h"

long /*FUNCTION*/ FUNCTYPE
fndmi(whlg, mko, tkz1, wi1, tkz2, wi2, on)
long int *whlg, *mko;
char *tkz1;
double *wi1;
char *tkz2;
double *wi2;
long int on[];
{
static char tkzr[2][3];
long int _l0, _l1, dbamkl[2], fndmi_v, irc, mkl[SIZMKL], zmk;
static long int ty, zla;
static double miw[2];
int (*w_notfound)(int, int, ...);
int (*dummy)(int, int, ...);

	/*   FNDMI SUCHT OBJEKTNUMMERN EINES MERKMALSKODES
	 *   NACH EINER BESTIMMTEN MERKMALSINFORMATION HERAUS
	 * */

	fndmi_v = EOKAY;
	irc = EOKAY;
	if (*whlg == 0L) {
		miw[0L] = 0.0;
		miw[1L] = 0.0;
	} else{
		*whlg = 0L;
		zmk = zla;
		goto L_15;
	}
	if (on[0L] < 3L) {
		fndmi_v = ENODIM;
		db_error (ENODIM, ROUTCD);
		/*  ON-FELD ZU KLEIN */
		goto L_999;
	}
	if (*wi1 == -1.0) {
		/*  KEIN WI */
		miw[0L] = -1.0;
	} else{
		miw[0L] = *wi1;
		strncpy( tkzr[0L], tkz1, 2 );
	}
	if (*wi2 == -1.0) {
		/*  KEIN WI */
		miw[1L] = -1.0;
	} else{
		miw[1L] = *wi2;
		strncpy( tkzr[1L], tkz2, 2 );
	}
	dbamkl[0L] = NMKL;
	dbamkl[1L] = 0L;
	*whlg = 0L;
	err_install (WNTFND, (int(*)(int,int,...))0, &w_notfound);
	irc = zfind( dbamkl, ADR(_l0,SMK), mko );
	err_install (WNTFND, w_notfound, &dummy);
	if (irc == EOKAY) 
		goto L_44;
	if (irc == WNTFND) {
		zmk = -*mko;
		fndmi_v = WNOMK;
		db_error (WNOMK, ROUTCD);
	} else{
		fndmi_v = irc;
	}
	return( fndmi_v );
L_44:
	;
	/*  MK-INF AUS MKL */
	irc = zread( dbamkl, mkl );
	if (irc != EOKAY) {
		fndmi_v = irc;
		return( fndmi_v );
	}
	zmk = mkl[ZMKVMO - 1L];
	ty = mkl[TYP - 1L];
	if (zmk == 0L) {
		on[1L] = 0L;
		goto L_999;
	}
	if (on[1L] != 0L) {
		irc = EOKAY;
		irc = fndmw( mko, &zmk, &ty, tkzr, miw, on );
		/*  ON VORH.MK+MW(TKZ)TESTEN */
		if (irc == EOKAY) 
			goto L_999;
		fndmi_v = irc;
		return( fndmi_v );
	}
L_15:
	irc = EOKAY;
	irc = readmk( whlg, &zmk, on );
	if (irc != EOKAY) {
		fndmi_v = irc;
		goto L_999;
	}
	if (*whlg == -1L) {
		zla = zmk;
	}
	/*  NUR ANALYSE NACH MK */
	if (miw[0L] == -1.0 && miw[1L] == -1.0) 
		goto L_999;
	irc = fndmw( mko, &zmk, &ty, tkzr, miw, on );
	if (irc != EOKAY) {
		fndmi_v = irc;
		goto L_999;
	}
	if (on[1L] == 0L && irc == *whlg) 
		goto L_15;
L_999:
	;
	return( fndmi_v );
} /* end of function */

