/*Translated by FOR_C, v3.1, on 02/21/91 at 12:41:35 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * Uebergibt Koordinaten von Punkten auf Linienobjekten          *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75010
 *       Autor:                Major,Walter
 *       Datum:                02-Mai-90
 *       Modulname:            *** GETGIL ***
 *       Routinenummer:        3004
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         GETKAN
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETGIL (ZVGI,FEX,FEY)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             GETGIL   Funktion                       I*4
 *
 *       Parameter:            ZVGI   - Zeiger auf Verb.liste ON-Li    I*4
 *                             FEX    - Nummer des dyn. Feldes X       I*4
 *                             FEY    - Nummer des dyn. Feldes Y       I*4
 *       Aufgabenstellung:
 *          Uebernimmt den Zeiger ZVGI auf die Verbindungsliste VOL; ruft
 *          kantenweise GETKAN, um die Koordinaten X und Y des Linien-
 *          objektes zu sammeln.
 *       Fehlerbehandlung:
 *          Fehler:
 *          EOKAY   i.O.
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

static long FUNCTYPE GetKantenCont (HPROJECT hPr, long lFirst, long *cont);

long FUNCTYPE getgil (HPROJECT hPr, long *zvgi, long *fex, long *fey, 
		      long *cont, long *window) 
{
DB_ADDR dbavol(hPr);
struct vol vol;
ErrCode RC;
long int wdh, zkl, zvgihi;

/* *** Anfangswerte setzen: */
	dbavol.file_no = VOL;
	zvgihi = *zvgi;

	// evtl. Container mit Window vergleichen 
	if (cont && window) {
		DBASSERT (GetKantenCont (hPr, zvgihi, cont));
		if (cont[1] < window[0] || cont[0] > window[1] ||
		    cont[3] < window[2] || cont[2] > window[3])
		{
			return ENOFIT;
		}
	}

/* *** Auffinden der einzelnen Kanten: */
	do {
		dbavol.rec_no = zvgihi;
		__Read (dbavol, vol);
		zkl = vol.zvolk;

	// Zeiger auf KAL (+oder-) 
		zvgihi = vol.znvol;

	// Zeiger naechste Kante auf VOL
		if (zvgihi != 0) wdh = WDHLG;
		else		 wdh = 0;
	
		DBASSERT (getkan (hPr, &zkl, &wdh, fex, fey, cont));
	} while (zvgihi != 0);

return EC_OKAY;
}

static long FUNCTYPE GetKantenCont (HPROJECT hPr, long lFirst, long *cont)
{
DB_ADDR dbavol(hPr), dbakal(hPr);
struct vol vol;
struct kal kal;
ErrCode RC;
long zkfn;

	dbavol.file_no = VOL;
	dbavol.rec_no = lFirst;
	dbakal.file_no = KAL;
	do {
		__Read (dbavol, vol);	// Verweis auf nächste Kante
		zkfn = vol.znvol;

	/* Zeiger naechste Kante aus KFM */
		dbakal.rec_no = labs (vol.zvolk);	// Zeiger auf KAL (+oder-)
		__Read (dbakal, kal);			// Kante lesen

	/* Container aktualisieren */
		if (cont[0] > kal.kcont.kxmin) cont[0] = kal.kcont.kxmin;
		if (cont[1] < kal.kcont.kxmax) cont[1] = kal.kcont.kxmax;
		if (cont[2] > kal.kcont.kymin) cont[2] = kal.kcont.kymin;
		if (cont[3] < kal.kcont.kymax) cont[3] = kal.kcont.kymax;
	} while	((dbavol.rec_no = zkfn) != 0);

return EC_OKAY;
}
