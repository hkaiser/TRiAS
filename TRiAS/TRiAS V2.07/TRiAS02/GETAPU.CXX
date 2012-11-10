/*Translated by FOR_C, v3.1, on 02/25/91 at 09:58:36 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * Ausgabe der Koo. des Anfangspunktes eines Objektes            *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, Bereich 2
 *       Dokumentationsnummer: AE0-610-A6?
 *       Autor:                Major, W.
 *       Datum:                11-Jul-90
 *       Modulname:            *** GETAPU ***
 *       Routinenummer:        3035
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         IABS
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         -
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,SETERR
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf: 
 *
 *        IRC=GETAPU (ON,STAF,XP,YP)
 *
 *                 IRC    - Rueckkehrcode                              I*4
 *                 GETAPU  - Funktion                                  I*4
 *
 *       Parameter:
 *       INPUT     ON  - Nummer des Objektes                           I*4
 *       OUTPUT    STAF- STATUS - Feld                                 I*4
 *                       STAF(1)=1 PO, LO oder FO; STAF(2)=1, 2, oder 3
 *                       STAF(1)=2 uebergeordnetes Obj. ohne GI; STAF(2)=0
 *                 XP  - X-Koo. des Anfangspunktes                     I*4
 *                 YP  - Y-Koo. des Anfangspunktes                     I*4
 *
 *------------------------------------------------------------------------
 *       Aufgabenstellung:
 *          GETAPU liefert den Status und die Koordinaten  (nur bei EOK)
 *          des Anfangspunktes von einem vorgegebenen Objekt.
 *
 *       Fehlerbehandlung:
 *          GETAPU= EOKAY    i.O.
 *                  ESTAT    Statusfehler
 *                  ENOON    ON-Nr. nicht gefunden
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

long FUNCTYPE getapu (HPROJECT hPr, long *on, long *staf, long *xp, long *yp)
{
DB_ADDR dbakal(hPr), dbakfm(hPr), dbakpl(hPr);
DB_ADDR dbamal(hPr), dbapol(hPr), dbavol(hPr);
DB_ADDR_OBL dbaobl(hPr);
long zkl;
struct kal kal;
struct kfm kfm; 
struct kpl kpl;
struct mal mal;
struct obl obl;
struct pol pol;
struct vol vol;
ErrCode RC;

/* *** Status bestimmen, Anfangskoo. lesen: */
//	dbaobl.file_no = OBL;
	dbaobl.rec_no = *on;
	__Read (dbaobl, obl);

// wenn Komplexobjekt, dann ohne Geometrie wieder raus
	if (obl.rmaske & OREL) {
		staf[0] = 2;		// Komplexobjekt
		staf[1] = 0;
		*xp = -1023998976;	// Koordinaten unbestimmt
		*yp = -1023998976;
		return EC_OKAY;
	}

	if (obl.zokp > 0) {		// Punktobjekt
		staf[0] = 1;
		staf[1] = 1;

		dbapol.file_no = POL;
		dbapol.rec_no = obl.zokp;
		__Read (dbapol, pol);

		*xp = pol.kpkrd.px;
		*yp = pol.kpkrd.py;
	}
	else if (obl.zovol > 0) {	// Linienobjekt
		staf[0] = 1;
		staf[1] = 2;
		
		dbavol.file_no = VOL;
		dbavol.rec_no = obl.zovol;
		__Read (dbavol, vol);

		zkl = vol.zvolk;
		dbakal.file_no = KAL;
		dbakal.rec_no = labs (zkl);
		__Read (dbakal, kal);

		dbakpl.file_no = KPL;
		if (zkl < 0) dbakpl.rec_no = kal.zep;
		else	     dbakpl.rec_no = kal.zap;
		__Read (dbakpl, kpl);

		*xp = kpl.pkrd.kpx;
		*yp = kpl.pkrd.kpy;
	}
	else if (obl.zovoma > 0) {	// Flaechenobjekt
		staf[0] = 1;
		staf[1] = 3;
		
		dbamal.file_no = MAL;
		dbamal.rec_no = obl.zovoma;
		__Read (dbamal, mal);

		dbakfm.file_no = KFM;
		dbakfm.rec_no = mal.zmkfm;
		__Read (dbakfm, kfm);

		zkl = kfm.zkfmk;
		dbakal.file_no = KAL;
		dbakal.rec_no = labs (zkl);
		__Read (dbakal, kal);

		dbakpl.file_no = KPL;
		if (zkl < 0) dbakpl.rec_no = kal.zep;
		else	     dbakpl.rec_no = kal.zap;
		__Read (dbakpl, kpl);

		*xp = kpl.pkrd.kpx;
		*yp = kpl.pkrd.kpy;
	}
	else {		// Statusfehler
		staf[0] = 0;
		staf[1] = 0;
		return db_error (ESTAT, 3035);
	}

return EC_OKAY;
}


