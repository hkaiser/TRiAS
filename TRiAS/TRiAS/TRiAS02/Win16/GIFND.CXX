/*Translated by FOR_C, v3.1, on 02/25/91 at 10:15:29 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * Wiederauffinden eines Objektes in der DB                      *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, Bereich 2
 *       Dokumentationsnummer: AE0-610-A64403
 *       Autor:                Major, W.
 *       Datum:                17-Jul-90
 *       Modulname:            *** GIFND ***
 *                             entspricht GETGI, hier Ruf aus FNDGI
 *       Routinenummer:        3039
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         GETGIP,GETGIL,GETGIF
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEINI,FEREL,FELEN,FEREAD,SETERR
 *       Common-Bloecke:       -
 *       SAVE                  AKZAE  - akt. Zaehler zur Uebergabe der
 *                                     dynamischen Felder bei Nachladen
 *                             LENDYN - Laenge der dyn. Felder
 *                             FEX    - Nummer des dyn. Feldes X
 *                             FEY    - Nummer des dyn. Feldes Y
 *                             LRC    - um WFORT beim Ueberlauf der GI-
 *                                      Felder zu retten
 *                             ZKFNRE - naechste Kante in KFM
 *       -----------------------------------------------------------------
 *       Aufruf: 
 *
 *        IRC=GIFND (NL,ON,ID,STAF,LMX,LGI,X,Y)
 *
 *                 IRC    - Rueckkehrcode                              I*4
 *                          bei notwendigem Nachladen ist IRC=WDHLG als
 *                          Output, bzw. WFORT fuer folgende Innenkanten
 *                 GIFND  - Funktion                                   I*4
 *
 *       Parameter:
 *                 NL  - Nachladeparameter                             I*4
 *                 = 0 - 1.Eingang; bzw. als Output, wenn alle Koo.
 *                       geliefert sind
 *                 =WDHLG - wiederholter Aufruf der GIFND-Funktion zum
 *                          Nachladen der Koordinaten (Output=Input)
 *                 =WFORT - wiederholter Aufruf der GIFND-Funktion zum
 *                          Nachladen der Koordinaten eines evtl. Innen-
 *                          randes (Output=Input)
 * A C H T U N G : NL ist vom Anwender beim ersten Aufruf =0 zu setzen,
 *                 Nachlieferung durch wiederh.Aufruf mit NL=WDHLG bzw.
 *                 WFORT (ist auch Output)
 *       INPUT     ON  - Nummer des Objektes                           I*4
 *                 LMX - Dimension des X-und Y-Vektors im rufenden     I*4
 *                        Programm; -1 bedeutet, keine GI gewuenscht
 *       OUTPUT    ID  - Identifikatornummer                           I*4
 *               Parameter fu_er die Geometrieinformationen:
 *                 STAF- STATUS - Feld                                 I*4
 *                       STAF(1)=1 PO, LO oder FO; STAF(2)=1, 2, oder 3
 *                       STAF(1)=2 uebergeordnetes Obj. ohne GI; STAF(2)=0
 *                 LGI - Zahl der belegten Feldelemente von X und Y    I*4
 *                 X   - Feld fuer X-Koo. (Spaltennummern)             I*4
 *                 Y   - Feld fuer Y-Koo. (Zeilennummern)              I*4
 *
 *------------------------------------------------------------------------
 *       Aufgabenstellung:
 *          GIFND liefert den Identifikator,den Status und die Geometrie
 *          zu einem vorgegebenen Objekt (Geometrie wahlweise nur bei EOK).
 *
 *       Fehlerbehandlung:
 *
 *       Fehler : EOKAY    i.O.
 *                ESTAT    Statusfehler
 *                ENODIM   Dimension LMX GI-Felder falsch
 *                ENOON    ON-Nr. nicht gefunden
 *                EZAEL    Laenge X-Feld ungleich Laenge Y-Feld
 *                weitere Fehler aus gerufenen Funktionen moeglich, sie
 *                werden weitergegeben
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

extern "C" 
long EXPORT02 FUNCTYPE gifnd(long *nl, long *on, long *id, long *staf, long *lmx, 
			     long *lgi, long *x, long *y)
{
static long int fex = 0, fey = 0;
long lendyn = 0, lrc = 0;
long _l0;

	*lgi = 0L;
	if ((*lmx < 1) && (*lmx != -1)) {
		return (long)db_error (ENODIM, 3039);

	} else if (*lmx > 0) {
	// X-,Y-Felder initialisieren 
		fex = 0L;
		DBASSERT (feini (&fex));
		fey = 0L;
		DBASSERT (feini (&fey));
	}
	lrc = getgi (nl, on, id, staf, lmx, &lendyn, &fex, &fey, NULL, NULL);
	
/*    *** Koo. von dyn. Feldern auf Fortran-Felder ohne Nachladen: */
	if (lendyn <= *lmx) {
		DBASSERT (feread (&fex, ADR(_l0, 1L), &lendyn, x));
		DBASSERT (feread (&fey, ADR(_l0, 1L), &lendyn, y));
		*lgi = lendyn;

	/*    ---***  X-,Y-Felder freigeben: */
		DBASSERT (ferel (&fex));
		DBASSERT (ferel (&fey));
		if (lrc == WFORT) {
			*nl = WFORT;
			return WFORT;
		}
	}

/* Ende ohne Nachladen, bzw. Innenrand nachholen */
return EOKAY;
} 


