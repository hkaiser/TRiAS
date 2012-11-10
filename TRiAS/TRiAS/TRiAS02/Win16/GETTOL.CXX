/*Translated by FOR_C, v3.2 (B), on 06/20/91 at 14:55:44 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
#include <fcrt.h>
/*+
 *       *****************************************************************
 *       * sucht verbundene Objekte zu einem Linienobjekt                *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75016
 *       Autor:                Major, Walter
 *       Datum:                20-Jun-91
 *       Modulname:            *** GETTOL ***
 *       Routinenummer:        3052
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         IABS
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         FNDTO
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,SETERR,FLQSRT,FLREDN
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETTOL (ON,ZVOL,LENON,FERIG)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             GETTOL - Funktion                       I*4
 *
 *       Parameter:  Input:    ON     - Objektnummer                   I*4
 *                             ZVOL   - Zeiger auf VOL                 I*4
 *                   In/Out:   LENON  - Anzahl der verbundenen Objekte I*4
 *                             FERIG  - dyn. Feld fuer verb. Objekte   I*4
 *       Aufgabenstellung:
 *          sucht Objekte, die mit dem gegebenen Linienobjekt verbunden
 *          sind, speichert die Objektnummer im dyn. Feld FERIG.
 *       Fehlerbehandlung:
 *          GETTOL=  EOKAY  i.O.
 *                =  WNOON  keine Objekte vorhanden
 *                =  WNORIG keine top. Relationen vorhanden
 *                =  EZKAL  Zeiger auf KAL darf nicht Null sein
 *       -----------------------------------------------------------------
 *- */
	/* PARAMETER translations */
#define	I40	0
#define	SHDIDN	6
#define	WNRECW	1018
	/* end of PARAMETER translations */

#include "ris.h"
#include "zipedb.h"
#include "zforc.h"

long /*FUNCTION*/ gettol(on, zvol, lenon, ferig)
long int *on, *zvol, *lenon, *ferig;
{
long int _l0, _l1, cont[4], dbakal[2], dbakpl[2], dbavol[2], gettol_v, 
	 irc, kal[SIZKAL], kpl[SIZKPL], krc, 
	 len, nl, vol[SIZVOL], x, y, zkl, zkpla, zkple, 
	 zvolre;

	/* *** Anfangswerte setzen: */
	gettol_v = EOKAY;
	irc = EOKAY;
	krc = EOKAY;
	dbavol[0L] = NVOL;
	dbakal[0L] = NKAL;
	dbakpl[0L] = NKPL;
	len = *lenon;
	nl = 0L;
	/* *** 1. oder naechster Knotenpunkt: */
L_5:
	if (nl == WFORT) {
		/*                                       ! naechster Knotenpkt. */
		*zvol = zvolre;
		zkpla = zkple;
		zkple = 0L;
		if (*zvol != I40) 
			goto L_10;
		if (zkpla != I40) 
			goto L_20;
	}

	/* *** 1. Kante oder Einsprung naechste Kante aus VOL: */
L_10:
	dbavol[1L] = *zvol;
	irc = zread( dbavol, vol );
	if (irc != EOKAY) {
		gettol_v = irc;
		return( gettol_v );
	}
	zkl = vol[ZVOLK - 1L];
	zvolre = vol[ZNVOL - 1L];
	/*                                       ! Retten naechster ZVOL */
	dbakal[1L] = labs( zkl );
	irc = zread( dbakal, kal );
	if (irc != EOKAY) {
		gettol_v = irc;
		return( gettol_v );
	}
	if (zkl < I40) {
		zkpla = kal[ZEP - 1L];
		zkple = kal[ZAP - 1L];
	} else if (zkl > I40) {
		zkpla = kal[ZAP - 1L];
		zkple = kal[ZEP - 1L];
	} else{
		/*                               ! Zeiger auf KAL darf nicht 0 sein */
		irc = db_error (EZKAL, 3052);
		gettol_v = EZKAL;
		return( gettol_v );
	}

	/* *** Koo. des Knotenpunktes, Einsprung letzter Knoten letzte Kante: */
L_20:
	dbakpl[1L] = zkpla;
	irc = zread( dbakpl, kpl );
	if (irc != EOKAY) {
		gettol_v = irc;
		return( gettol_v );
	}
	x = kpl[KPX - 1L];
	y = kpl[KPY - 1L];
	cont[0L] = x;
	cont[1L] = x;
	cont[2L] = y;
	cont[3L] = y;

	/* *** Objekte im Nullcontainer suchen: */
	irc = fndto( on, cont, &len, ferig );
	if (irc != EOKAY) {
		if (irc == WNORIG) {
			krc = irc;
			goto L_100;
		}
	}

	/* *** FERIG sortieren und redundanzbefreien: */
	if (nl == WFORT) {
		/*                               ! 1.Mal nicht sortieren */
		irc = flqsrt( ferig );
		if (irc != EOKAY) {
			gettol_v = irc;
			return( gettol_v );
		}
		irc = flredn( ferig, &len );
		if (irc != EOKAY) {
			gettol_v = irc;
			return( gettol_v );
		}
	}

	/* *** Ende: */
L_100:
	if ((zvolre != I40) || (zkple != I40)) {
		nl = WFORT;
		len = 0L;
		goto L_5;
	} else{
		nl = 0L;
		*lenon = len;
		gettol_v = krc;
	}

	return( gettol_v );
} /* end of function */

