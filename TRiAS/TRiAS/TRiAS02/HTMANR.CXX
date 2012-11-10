/*Translated by FOR_C, v3.1, on 02/25/91 at 10:02:07 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * speichert Obj.nr. von Maschen ins dyn. Feld                   *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75?
 *       Autor:                Major, Walter
 *       Datum:                11-Jul-90
 *       Modulname:            *** HTMANR ***
 *       Routinenummer:        3031
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         FNDMA
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEPUT,SETERR
 *       Common-Bloecke:       RIFENR   - enthaelt Nr. des dyn. Feldes
 *       SAVE:                 /RIFENR/ - Feldnummercommon
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=HTMANR (DBA,CONT)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                             HTMANR  - Funktion                      I*4
 *
 *       Parameter:  Input:    DBA     - enthaehlt NKAL und ZKAL bzw.
 *                                                 NMAL und ZMAL       I*4
 *                             CONT    - gegebener Container           I*4
 *                             CONT(1) - XMIN
 *                             CONT(2) - XMAX
 *                             CONT(3) - YMIN
 *                             CONT(4) - YMAX
 *       Aufgabenstellung:
 *          speichert alle Objektnummern von Maschen (Flaechen), die den
 *          Container schneiden, ins dynamische Feld.
 *       Fehlerbehandlung:
 *          HTMANR # EOKAY  Fehler - RETURN
 *                 = EKAMA - falsche Liste, NKAL, bzw. NMAL nicht gefunden
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

/* COMMON translations */
struct t_rifenr {
	long int rifeon;
} rifenr = { 0 };
/* end of COMMON translations */

extern "C" long __cdecl EXPORT02 htmanr (DB_ADDR *dba, long *cont)
{
long ltest;
struct mal mal;
ErrCode RC;

/* *** Kante oder Masche (Flaeche) gefunden:
 * *** Kante: */
	if (dba -> file_no == KAL) 
		return EC_OKAY;

	else if (dba -> file_no == MAL) {		/* Masche */
		DBASSERT (fndma (dba->db_no, &ltest, dba, cont));
		if (ltest) {	// Objektnummer merken
			__Read (*dba, mal);
			DBASSERTM (feput (&rifenr.rifeon, &mal.zmvgo));
			DBASSERT (GetKomplexObjects (dba->db_no, mal.zmvgo, rifenr.rifeon));
		}
		return EC_OKAY;
	}
	else
		return (long)db_error ((short)EKAMA, 3023);	/* falsche Liste */

return EC_OKAY;
} /* end of function */

