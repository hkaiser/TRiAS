/*Translated by FOR_C, v3.1, on 02/25/91 at 10:14:55 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * speichert Objektnr., die auf Punkt liegen, ins dyn. Feld      *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75?
 *       Autor:                Major, Walter
 *       Datum:                04-Mai-90
 *       Modulname:            *** QTFUNC ***
 *       Routinenummer:        3022
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         -
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEPUT
 *       Common-Bloecke:       FENR   - enthaelt Nr. des dyn. Feldes
 *       SAVE                  /FENR/ - Feldnummercommon
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=QTFUNC (DBAPOL)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                             QTFUNC   - Funktion                     I*4
 *
 *       Parameter:            DBAPOL  - enthaehlt NPOL und ZPOL       I*4
 *       Aufgabenstellung:
 *          speichert alle Objektnummern, die auf einem Punkt liegen, ins
 *          dynamische Feld.
 *       Fehlerbehandlung:
 *          QTFUNC # 0  Fehler bei ZREAD - RETURN
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxX"

/* COMMON translations */
extern struct t_fenr {
	long int feon;
} fenr;
/* end of COMMON translations */

extern "C" long __cdecl EXPORT02 qtfunc (DB_ADDR *pdbapol, ...)
{
DB_ADDR dbavgo(pdbapol->db_no);
ErrCode RC;
struct pol pol;
struct vgo vgo;

/* *** Anfangswerte: */
	dbavgo.file_no = VGO;

/* *** Punktobjekt gefunden: */
	__Read (*pdbapol, pol);
	dbavgo.rec_no = pol.zpvgo;

/* *** Objektnummern ins dynamische Feld speichern: */
	do {
		__Read (dbavgo, vgo);
		DBASSERTM (feput (&fenr.feon, &vgo.zvgoo));
		DBASSERT (GetKomplexObjects (pdbapol->db_no, vgo.zvgoo, fenr.feon));
	} while ((dbavgo.rec_no = vgo.znvgo) > 0);

return EC_OKAY;
} /* end of function */

