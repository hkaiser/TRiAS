/*Translated by FOR_C, v3.2 (B), on 06/04/91 at 15:07:10 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
/*+
 *       *****************************************************************
 *       * Wiederauffinden von thematischen Relationen eines Objektes    *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, Bereich 2
 *       Dokumentationsnummer: AE0-610-A64402
 *       Autor:                Kurth, K.             
 *       Datum:                17-April-1990
 *       Aenderungsdatum:      17.04.90
 *       Modulname:            *** GETRI ***
 *       Routinenummer:       6005
 *       Programmiersprache:   Fortran-77
 *
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETRI(NLP,ON,RIK)
 *       Parameter:            
 *              INPUT -> ON -  Objekt
 *             OUTPUT -> IRC - Fehlerkode
 *                             IRC = 0   ohne Fehler
 *                             IRC > 0   Fehler 
 *                             IRC < 0   Warnung
 *                       NLP - Nachladeparameter(wiederh. Aufruf der Fkt.)
 *                       RIK - Feld der thematischen Relationen
 *       ------------------------------------------------------------------
 *       Aufgabenstellung:
 *          Diese Funktion liefert im RIK-Feld alle thematischen Beziehungen,
 *          die ein vorgegebenes Objekt ON mit anderen Objekten der Datenbasis
 *          besitzt.
 *          Das RIK-Feld ist folgendermaszen aufgebaut:
 *          RIK(1) : Dimension des Feldes (vom Anwender anzugeben)
 *          RIK(2) : Anzahl der ab RIK(3) belegten Feldelemente
 *          RIK(3) : Nummer des Objektes,mit dem ON eine Relation eingeht
 *          RIK(4) : Relationsart- Stellung von ON in der Relation 
 *                   primaer    -> Relationsart positiv
 *                   sekundaer  -> Relationsart negativ
 *          RIK(5) analog RIK(3) ff.
 *
 *       Fehlerbehandlung:
 *          Fehlermeldungen erfolgen bei:
 *          - nicht definierter Objektnummer 
 *       Fehler : aus DBV ZIPEDB
 *
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

#include "ris.h"

long FUNCTYPE getri (long *nlp, long *on, long *rik)
{
long int dbaobl[2], dbaral[2], dbarel[2], dbavor[2], 
	 i, irc, obl[SIZOBL], ral[SIZRAL], rel[SIZREL], vor[SIZVOR], zvor;
static long int znext;
int (*e_nodba)(int, int, ...);
int (*dummy)(int, int, ...);

	dbaobl[0L] = NOBL;
	dbavor[0L] = NVOR;
	dbarel[0L] = NREL;
	dbaral[0L] = NRAL;
	irc = EOKAY;
	if (rik[0] < 4L) 
		return db_error (ENODIM, ROUTCD);
	if (*nlp != 0L) {
		zvor = znext;
	} else{
		dbaobl[1L] = *on;
		err_install (ENDBA, (int(*)(int,int,...))0, &e_nodba);
		irc = zread (dbaobl, obl);
		err_install (ENDBA, e_nodba, &dummy);
		if (irc != EOKAY) {
			if (irc == ENDBA) db_error (ENOON, ROUTCD);
			return irc;
		}
		/*       *** Satz geloescht *** */
		if (obl[0L] == 2147483647) 
			return db_error (ENOON, ROUTCD);

		zvor = obl[ZOVOR - 1L];
		if (zvor == 0L) 
			return db_error (WOBKTR, ROUTCD);
	}
	rik[1L] = 0L;
	i = 4L;
	do {
L_10:
		dbavor[1L] = zvor;
		/*       verweis auf relation     */
		irc = zread (dbavor, vor);
		if (irc != EOKAY) 
			return irc;
		dbarel[1L] = vor[ZVOREL - 1L];
		/*       lesen der relation */
		irc = zread (dbarel, rel);
		if (irc != EOKAY) 
			return irc;
		/*       feststellen ra-schluessel */
		dbaral[1L] = rel[ZRERA - 1L];
		irc = zread (dbaral, ral);
		if (irc != EOKAY) 
			return irc;
		if (rel[ZOL1 - 1L] == *on) {
			/*       on ist in rel primaerobjekt */
			rik[i - 2L] = rel[ZOL2 - 1L];
			rik[i - 1L] = ral[RAT - 1L];
		} else{
			rik[i - 2L] = rel[ZOL1 - 1L];
			rik[i - 1L] = -ral[RAT - 1L];
		}
		zvor = vor[ZNVOR - 1L];
		rik[1L] = i - 2L;
		/*       relationenkette zu ende ? */
		if (zvor == 0L) {
			*nlp = 0L;
			return EOKAY;
		}
		i = i + 2L;
	} while (i <= rik[0L]); 
	*nlp = -1L;
	znext = zvor;

return WDHLG;
} /* end of function */

