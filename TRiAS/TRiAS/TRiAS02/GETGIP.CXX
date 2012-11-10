/*Translated by FOR_C, v3.1, on 02/21/91 at 12:42:23 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * Ubergabe der Koordinaten eines Punktobjektes                  *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75009
 *       Autor:                Major,Walter
 *       Datum:                02-Mai-90
 *       Modulname:            *** GETGIP ***
 *       Routinenummer:        3003
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         -
 *       libdbr.a    :         -
 *       libzipedb   :         ZREAD,FEPUT
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETGIP (ZVGI,FEX,FEY)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             GETGIP - Funktion                       I*4
 *
 *       Parameter:            ZVGI   - Zeiger auf POL                 I*4
 *                             FEX    - Feldnummer des dyn. Feldes X   I*4
 *                             FEY    - Feldnummer des dyn. Feldes Y   I*4
 *       Aufgabenstellung:
 *          Erhaelt mit ZVGI den Zeiger auf die Punktobjektliste. Schreibt
 *          die  Koordinaten des Punktes in die dynamischen Felder FEX
 *          und FEY.
 *       Fehlerbehandlung:
 *          Fehler:   EOKAY
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

long FUNCTYPE getgip (HPROJECT hPr, long *zvgi, long *fex, long *fey, long *cont, long *window) 
{
DB_ADDR dbapol(hPr);
struct pol pol;
ErrCode RC;

	dbapol.file_no = POL;
	dbapol.rec_no = *zvgi;
	__Read (dbapol, pol);

// Container des Objektes setzen
	if (cont != NULL) {
		cont[0] = cont[1] = pol.kpkrd.px;
		cont[2] = cont[3] = pol.kpkrd.py;
	}

// wenn außerhalb des benötigten Bereiches, dann wieder raus
	if (window != NULL) {
		if (pol.kpkrd.px < window[0] || pol.kpkrd.px > window[1] ||
		    pol.kpkrd.py < window[2] || pol.kpkrd.py > window[3])
		{
			return ENOFIT;
		}
	}

// Koordinaten merken
	DBASSERTM (feput (fex, &pol.kpkrd.px));
	DBASSERTM (feput (fey, &pol.kpkrd.py));

return EC_OKAY;
} /* end of function */
