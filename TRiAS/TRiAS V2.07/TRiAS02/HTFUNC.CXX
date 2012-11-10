/*Translated by FOR_C, v3.1, on 02/26/91 at 09:34:52 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
/*+
 *       *****************************************************************
 *       * speichert Obj.nr., die auf Kante/Masche liegen, ins dyn. Feld *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75?
 *       Autor:                Major, Walter
 *       Datum:                07-Jun-90
 *       Modulname:            *** HTFUNC ***
 *       Routinenummer:        3023
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         FNDKA,FNDMA
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEPUT,SETERR
 *       Common-Bloecke:       FENR   - enthaelt Nr. des dyn. Feldes
 *       SAVE:                 /FENR/ - Feldnummercommon
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=HTFUNC (DBA,CONT)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                             HTFUNC  - Funktion                      I*4
 *
 *       Parameter:            DBA     - enthaehlt NKAL und ZKAL bzw.
 *                                                 NMAL und ZMAL       I*4
 *                             CONT    - gegebener Container           I*4
 *                             CONT(1) - XMIN
 *                             CONT(2) - XMAX
 *                             CONT(3) - YMIN
 *                             CONT(4) - YMAX
 *       Aufgabenstellung:
 *          speichert alle Objektnummern, die auf einer Kante bzw. Masche
 *          (Flaeche) liegen,wenn diese den Container schneidet, ins dyna-
 *          mische Feld.
 *       Fehlerbehandlung:
 *          HTFUNC # 0  Fehler - RETURN
 *                 = EKAMA - falsche Liste, NKAL, bzw. NMAL nicht gefunden
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

/* COMMON translations */
extern struct t_fenr {
	long int feon;
} fenr;
/* end of COMMON translations */

extern "C" long __cdecl EXPORT02 htfunc (DB_ADDR *pDBA, long *cont)
{
long ltest = FALSE;
DB_ADDR dbavgo(pDBA->db_no);
ErrCode RC;
struct kal kal;
struct mal mal;
struct vgo vgo;

// ACHTUNG: Erweiterung für TRIAS:
// 	    cont[4] enthält Flag, welches vorgibt, ob exakt gesucht werden soll,
//          oder ob es ausreicht, alle vom SuchContainer betroffenen Objekte
//	    zu liefern

/* *** Kante oder Masche (Flaeche) gefunden: Kante */
	if (pDBA -> file_no == KAL) {
		__Read (*pDBA, kal);
		if (kal.zkvgo == 0) 
			return EC_OKAY;	/* Kante gehört zu Flächenumrandung */

	/* Container umschließt voellig Kantencontainer: */
		if ((cont[0] <= kal.kcont.kxmin) && (cont[1] >= kal.kcont.kxmax) && 
		    (cont[2] <= kal.kcont.kymin) && (cont[3] >= kal.kcont.kymax)) 
		{
			ltest = TRUE;
		}

	/* FNDKA rufen: */
		if (!ltest) {
			DBASSERT (fndka (pDBA->db_no, &ltest, pDBA, cont));
		} 

		if (ltest) {
			dbavgo.file_no = VGO;
			dbavgo.rec_no = kal.zkvgo;

		/* Objektnummern der Kante ins dynamische Feld speichern: */
			do {
				__Read (dbavgo, vgo);
				DBASSERTM (feput (&fenr.feon, &vgo.zvgoo));
				DBASSERT (GetKomplexObjects (pDBA->db_no, vgo.zvgoo, fenr.feon));
			} while ((dbavgo.rec_no = vgo.znvgo) > 0);
		}
		return EC_OKAY;		/* Ende Kante */

	} else if (pDBA -> file_no == MAL) {		/* Masche */
		if (cont[4]) {
		// nur wenn exakt gesucht werden soll
			DBASSERT (fndma (pDBA->db_no, &ltest, pDBA, cont));
		} else
			ltest = TRUE;

		if (ltest) {
		// gefundene Objektnummer ins Feld einspeichern
			__Read (*pDBA, mal);
			DBASSERTM (feput (&fenr.feon, &mal.zmvgo));
			DBASSERT (GetKomplexObjects (pDBA->db_no, mal.zmvgo, fenr.feon));
		}
		return EC_OKAY;		/* Ende Masche (Flaeche) */
	} else 	// falsche Liste
		return (long)db_error ((short)EKAMA, 3023);

return EC_OKAY;
} 

