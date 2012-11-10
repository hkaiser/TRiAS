/*Translated by FOR_C, v3.2 (B), on 06/20/91 at 14:55:54 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
#include <fcrt.h>
/*+
 *       *****************************************************************
 *       * sucht verbundene Objekte zu einem Punktobjekt                 *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75015
 *       Autor:                Major, Walter
 *       Datum:                18-Jun-91
 *       Modulname:            *** GETTOP ***
 *       Routinenummer:        3051
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         FNDTO
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETTOP (ON,ZPOL,LENON,FERIG)
 *
 *                             GETTOP - Funktion                       I*4
 *                             IRC    - Rueckkehrcode                  I*4
 *
 *       Parameter:  Input:    ON     - Objektnummer                   I*4
 *                             ZPOL   - Zeiger auf POL                 I*4
 *                   In/Out:   LENON  - Laenge des dyn. Feldes         I*4
 *                             FERIG  - Nummer des dyn. Feldes RIG     I*4
 *       Aufgabenstellung:
 *          sucht Objekte, die mit dem gegebenen Punktobjekt verbunden
 *          sind. Die Objektnummern der verbundenen Objekte werden im
 *          dynamischen Feld gespeichert.
 *          Ist LENON>0 werden nur diese Objekte geprueft.
 *       Fehlerbehandlung:
 *          GETTOP =  EOKAY  i.O.
 *                 =  WNOON  keine Objekte gefunden (aus FNDTO)
 *                 =  WNORIG keine top. Relation (aus FNDTO)
 *       -----------------------------------------------------------------
 *- */
	/* PARAMETER translations */
#define	SHDIDN	6
#define	WNRECW	1018
	/* end of PARAMETER translations */

#include "ris.h"
#include "zipedb.h"
#include "zforc.h"

long /*FUNCTION*/ FUNCTYPE
gettop(on, zpol, lenon, ferig)
long int *on, *zpol, *lenon, *ferig;
{
long int cont[4], dbapol[2], gettop_v, irc, pol[SIZPOL], x, y

	/* *** Anfangswerte setzen: */
	gettop_v = EOKAY;
	irc = EOKAY;
	dbapol[0L] = NPOL;

	/* *** Punktkoordinaten bereitstellen: */
	dbapol[1L] = *zpol;
	irc = zread( dbapol, pol );
	if (irc != EOKAY) {
		gettop_v = irc;
		return( gettop_v );
	}
	x = pol[PX - 1L];
	y = pol[PY - 1L];
	cont[0L] = x;
	cont[1L] = x;
	cont[2L] = y;
	cont[3L] = y;

	/* *** Objekte im Nullcontainer suchen: */
	irc = fndto( on, cont, lenon, ferig );
	if (irc != EOKAY) 
		gettop_v = irc;

	/* *** Ende: */
	return( gettop_v );
} /* end of function */

