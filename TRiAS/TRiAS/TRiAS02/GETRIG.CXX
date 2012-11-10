/*Translated by FOR_C, v3.1, on 02/25/91 at 09:59:25 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * sucht Geometrierelationen                                     *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75014
 *       Autor:                Major, Walter
 *       Datum:                04-Okt-90
 *       Modulname:            *** GETRIG ***
 *       Routinenummer:        3026
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         MOD
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         GETRIP,GETRIL,GETRIF
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEINI,FEREL,FELEN,FEREAD,SETERR
 *                             ERRFKT,LADR
 *       Common-Bloecke:       /WOHER/ - GETGI-Variante GIRIG waehlen
 *       SAVE:                 FEZAE  - Beginn der Zaehlung im dyn. Feld
 *                                      bei der jeweiligen Uebergabe
 *                             LEN    - Laenge des dyn. Feldes
 *                             NLHI   - noch Knotenpkt. vorhanden - WFORT
 *                             FERIG  - Nummer des dyn. Feldes
 *                             /WOHER/- Common WOHER
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GETRIG (NL,ON,X,Y,RIG)
 *
 *                             IRC    - Rueckkehrcode                  I*4
 *                             GETRIG - Funktion                       I*4
 *
 *       Parameter:  Input:    NL     - Nachladeparameter              I*4
 *                                      =0 beim 1. Eingang
 *                                      =WDHLG, wenn RIG-Feld voll
 *                                      =WFORT, naechster Knotenpkt. (nach
 *                                       WFORTR auf neuem Rand)
 *                                      =WFORTR, vor letztem Pkt. eines
 *                                       Randes bei F-obj.,dann letzter
 *                                       Pkt., danach neuer Innenrand
 *                                      =WFORTI, es folgen bei F-obj.
 *                                       voellig innen liegende Obj., bzw.
 *                                       die Flaeche voll ueberdeck. Fl.
 *                   Output:   NL     - =0 bei erfogreichem Ende
 *                                      =WDHLG zum Nachladen RIG-Feld
 *                                      =WFORT, s. oben
 *                                      =WFORTR, s. oben
 *                                      =WFORTI, s. oben
 *                   Input:    ON     - Objektnummer                   I*4
 *                   Output:   X      - X-Koo. des Knotenpunktes       I*4
 *                             Y      - Y-Koo. des Knotenpunktes       I*4
 *                                      X,Y=-1023998976, d.h. unbestimmte
 *                                      Koo., kein Knotenpunkt
 *                             RIG    - Feld fuer Relationen           I*4
 *                   Input:    RIG(1) - max. Laenge
 *                   Output:   RIG(2) - akt. Laenge
 *                             RIG(3) - Objektnr. des verbundenen Objektes
 *                             RIG(4) - Relationsart  (3 bis 4 zyklisch)
 *       Aufgabenstellung:
 *          sucht Objekte, die mit dem gegebenen Objekt verbunden sind.
 *          Gibt die Koordinaten des Punktes bei P.obj.,des jeweiligen
 *          Knotenpkt. bei L.obj. bzw. des jeweiligen Knotenpkt. des Flae-
 *          chenrandes bei F.obj. sowie die Objektnummern der verbundenen
 *          Objekte und die Relationsarten an. Falls ein Flaechenobjekt
 *          keine top.Relationen hat bzw. bei der Angabe der voellig in
 *          der Flaeche liegenden Objekte oder bei der Angabe der die
 *          Flaeche voll ueberdeckenden Flaechen sind X und Y unbestimmt
 *          (siehe bei Parameter).
 *          ACHTUNG!: Wenn Funktionswert gleich WNORIG, Nachladeparameter
 *                    pruefen (knotenpunktweise Uebergabe !)
 *          Ruft entweder GETRIP (fuer ein Punktobjekt), GETRIL (fuer ein
 *          Linienobjekt) oder GETRIF (fuer ein Flaechenobjekt).
 *          Mit dem Nachladeparameter NL werden die Fortsetzungsarten
 *          gesteuert (siehe bei Parameter).
 *          Relationsart: 1 - L.obj. einseitig an Knotenpkt. ohne Ueberl.
 *                        2 - L.obj. durch K.pkt ohne Ueberl. (1+1)
 *                        3 - L.obj. ueberlagert 1 Kante
 *                        4 - L.obj. 1 Kante ueberl., 1 Kante frei (1+3)
 *                        5 - P.obj. ueberlagert K.pkt.
 *                        6 - L.obj. ueberlagert 2 Kanten (3+3)
 *                        7 - P.obj. auf P.obj.
 *                        8 - L.obj. einseitig an P.obj.
 *                        9 - L.obj. zweiseitig an P.obj.
 *                       10 - F.obj. beruehrt Knotenpkt.
 *                       11 - F.obj. bedeckt Knotenpkt.
 *                       12 - Objekt voellig in F.obj.
 *                       13 - F.obj. bedeckt voellig F.obj.
 *       Fehlerbehandlung:
 *          GETRIG = EOKAY  - i.O.
 *                 = ENOON  - Objekt nicht vorhanden
 *                 = ENODIM - Dimension RIG-Feld < 4
 *                 = WNOEOK - kein Elementarobjekt
 *                 = WNORIG - keine topol. Relationen, NL ist zu pruefen
 *                 = WDHLG  - noch Informationen zum Knotenpkt. vorhanden
 *                 = WFORT  - Fortsetzung mit naechstem Knotenpunkt
 *                       wenn WNORIG auftritt, wird dies als Funktions-
 *                       wert zurueckgegeben, auch wenn WFORT im Nachlade-
 *                       parameter NL gesetzt ist !
 *                = WFORTR  - s. oben */
/*                = WFORTI  - s. oben
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

	/* COMMON translations */
extern struct t_woher {
	char rout[4];
}	woher;
	/* end of COMMON translations */


extern "C" 
long EXPORT02 FUNCTYPE getrig (HPROJECT hPr, long *nl, long *on, long *x, long *y, long *rig)
{
long int lenakt, lenmax;
DB_ADDR_OBL dbaobl(hPr);
struct obl obl;
static long int ferig = 0, fezae = 0, len = 0, nlhi = 0;
ErrCode RC;

/* *** Anfangswerte setzen, Testung: */
	rig[1] = 0;
	strcpy (woher.rout, "RIG");

	if (rig[0] < 4) 	// Dim. RIG-Feld < 4
		return db_error (ENODIM, 3026);

	if (*nl != WDHLG) {
	/*                                       ! restl. Werte holen
	 * *** Objektnummer pruefen: */
		if ((*on <= 0) || (*on > ladr (hPr, &dbaobl.file_no, true)))
		// Objektnr. ausserhalb Bereich
			return db_error (ENOON, 3026);
	
	/* *** Erstwerte setzen: */
		fezae = 1L;
		len = 0L;
	
	/* *** dynamisches Feld fuer topolog. Relationen initialisieren:
	 * *** bei Neueingang evtl. noch offenes dyn. Feld loeschen: */
		if (*nl == 0) {
		ErrInstall EI ((ErrCode)EFLEX);
		
			RC = (ErrCode)ferel (&ferig);
			if (RC != EC_OKAY && RC != EFLEX) 
				return RC;
		}
		ferig = 0;
		DBASSERT (feini (&ferig));
	
	/* *** Punkt-, Linien- oder Flaechenobjekt: */
//		dbaobl.file_no = OBL;
		dbaobl.rec_no = *on;
		__Read (dbaobl, obl);
	
		if (obl.zovor >= 2147483647) 	// gelöschtes Objekt
			return db_error (ENOON, 3026);
	
		if (obl.zokp != 0) {		// Punktobjekt
			DBASSERT (getrip (hPr, on, &obl.zokp, &ferig, x, y));
		}
		else if (obl.zovol != 0) {	// Linienobjekt
			RC = (ErrCode)getril (hPr, nl, on, &obl.zovol, &ferig, x, y);
			if (RC != (ErrCode)EC_OKAY && RC != (ErrCode)*nl)
				return RC;
		}
		else if (obl.zovoma != 0) {	// Flächenobjekt 
			RC = (ErrCode)getrif (hPr, nl, on, &obl.zovoma, &ferig, x, y);
			if (RC != (ErrCode)EC_OKAY && RC != (ErrCode)*nl)
				return RC;
		}
		else
			return db_error (WNOEOK, 3026);
		nlhi = *nl;
	/*                               ! Nachladeparameter retten
	 * *** keine RIG gefunden: */
		DBASSERT (felen (&ferig, &len));
		if (len == 0) {
			DBASSERT (ferel (&ferig));
			ferig = 0;
			if (nlhi != 0) {	// Fortsetzung nächster Knotenpunkt
				*nl = nlhi;
				return *nl;
			} else			// Ende des Objekts (Gesamtende)
				*nl = 0L;
			return db_error (WNORIG, 3026);
		}
	}
	
/* *** Uebergabe des dyn. Feldes, Einsprung Nachladen: */
	lenmax = rig[0L] - 2;
	lenakt = len - fezae + 1;
	if (lenakt <= lenmax) {
		DBASSERT (feread (&ferig, &fezae, &lenakt, &rig[2L]));
		rig[1L] = lenakt;
	}
	else {
		if ((lenmax % 2) != 0)
			lenmax = lenmax - 1;
		DBASSERT (feread (&ferig, &fezae, &lenmax, &rig[2L]));
		rig[1L] = lenmax;
		*nl = WDHLG;
		fezae = fezae + lenmax;
		return WDHLG;		// Ende mit erforderlichem Nachladen
	}

/* *** dynamisches Feld der RIG freigeben: */
	DBASSERT (ferel (&ferig));
	ferig = 0L;
	if (nlhi != 0) {		// Fortsetzung nächster Knotenpunkt
		*nl = nlhi;
		return *nl;
	} else				// Ende des Objekts (Gesamtende)
		*nl = 0L;

return EC_OKAY;
}

