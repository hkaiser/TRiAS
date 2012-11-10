/*Translated by FOR_C, v3.1, on 02/25/91 at 11:40:06 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * prueft, ob Punkt im Container                                 *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75020
 *       Autor:                Major, Walter
 *       Datum:                27-Apr-90
 *       Modulname:            *** FNDPU ***
 *       Routinenummer:        3009
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         -
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=FNDPU (LTEST,ZVOG,CONT,X1,Y1)
 *
 *                             IRC     - Rueckkehrcode                 I*4
 *                             FNDPU  - Funktion               I*4
 *
 *       Parameter:            LTEST   - Pkt. im Container = .TRUE.    L
 *                             ZVOG    - Zeiger auf POL                I*4
 *                             CONT    - Feld der Containerkoo.        I*4
 *                             CONT(1) - X linke obere Ecke
 *                             CONT(2) - X rechte untere Ecke
 *                             CONT(3) - Y linke obere Ecke
 *                             CONT(4) - Y rechte untere Ecke
 *                             X1      - Ausgabe Punktkoo. X           I*4
 *                             Y1      - Ausgabe Punktkoo. Y           I*4
 *       Aufgabenstellung:
 *          wenn das Punktobjekt im Container enthalten ist (einschl.
 *          Rand), wird LTEST=.TRUE. gesetzt, sonst .FALSE.. Sind X1 und
 *          Y1 beim Aufruf nicht -1, werden die Punktkoordinaten zurueck-
 *          gegeben.
 *       Fehlerbehandlung:
 *          IRC # 0  Fehler bei ZREAD - RETURN
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

extern "C" long FUNCTYPE fndpu (HPROJECT hPr, 
		long *ltest, long *zvog, long *cont, long *x1, long *y1)
{
DB_ADDR dbapol(hPr);
struct pol pol;
ErrCode RC;
long x, y;

	dbapol.file_no = POL;
	dbapol.rec_no = *zvog;
	__Read (dbapol, pol);

	x = pol.kpkrd.px;		// Punktkoordinaten
	y = pol.kpkrd.py;
	
	if ((x >= cont[0L]) && (x <= cont[1L]) && 
	    (y >= cont[2L]) && (y <= cont[3L])) 
	{
		*ltest = TRUE;		// Punkt im Container
	}
	else {
		*ltest = FALSE;		// Punkt außerhalb des Containers
	}
	if ((*x1 != -1) && (*y1 != -1)){
		*x1 = x;
		*y1 = y;
	}

return EC_OKAY;
} /* end of function */

