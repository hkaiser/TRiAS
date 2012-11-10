/*Translated by FOR_C, v3.1, on 02/25/91 at 10:16:03 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * Wiederauffinden eines Objektes in der DB                      *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, Bereich 2
 *       Dokumentationsnummer: AE0-610-A64403
 *       Autor:                Major, W.
 *       Datum:                17-Jul-90
 *       Modulname:            *** GIRIG ***
 *                             entspricht GETGI, hier Ruf aus GETRIG
 *       Routinenummer:        3038
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
 *        IRC=GIRIG (NL,ON,ID,STAF,LMX,LGI,X,Y)
 *
 *                 IRC    - Rueckkehrcode                              I*4
 *                          bei notwendigem Nachladen ist IRC=WDHLG als
 *                          Output, bzw. WFORT fuer folgende Innenkanten
 *                 GIRIG  - Funktion                                   I*4
 *
 *       Parameter:
 *                 NL  - Nachladeparameter                             I*4
 *                 = 0 - 1.Eingang; bzw. als Output, wenn alle Koo.
 *                       geliefert sind
 *                 =WDHLG - wiederholter Aufruf der GIRIG-Funktion zum
 *                          Nachladen der Koordinaten (Output=Input)
 *                 =WFORT - wiederholter Aufruf der GIRIG-Funktion zum
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
 *          GIRIG liefert den Identifikator,den Status und die Geometrie
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
	/* PARAMETER translations */
#define	SHDIDN	6
#define	WNRECW	1018
	/* end of PARAMETER translations */

#if defined(MSWIND)
#include <windows.h>
#endif
#include <string.h>

#include <dbtypes.h>
#include <errdef.h>
#include <zipedb.h>
#include <zforc.h>
#include <risdb.h>   

long FUNCTYPE girig (long *nl, long *on, long *id, long *staf, 
		     long *lmx, long *lgi, long *fex, long *fey)
{
long anz, irc, krc, lenx, leny, zaehi, zael, zkfn, zvgi;
static long int akzae = 0, lendyn = 0, lrc = 0, zkfnre = 0;
DB_ADDR dbaidl, dbaobl;
struct idl idl;
struct obl obl;
ErrCode RC;

/* *** Anfangswerte setzen: */
	irc = EOKAY;
	if (*nl == 0) lrc = EOKAY;
	if (*nl == WFORT)
		zkfn = zkfnre;
	*lgi = 0L;
/*                               ! akt. Laenge X,Y-Feld=0 setzen
 * *** Nachladen, Pruefen max. Felddimension, evtl X-,Y-Felder init.: */
	if (*nl == WDHLG) {
	// Nachladen 
		zael = akzae;
		goto L_100;
	} else
		zael = 1L;

	if ((*lmx < 1) && (*lmx != -1))
		return db_error (ENODIM, 3038);		// LMX falsch

	if (*lmx > 0) {		// X-,Y-Felder initialisieren
		*fex = 0L;
		DBASSERT (feini (fex));
		*fey = 0L;
		DBASSERT (feini (fey));
	}

// Identifikator lesen, Status bestimmen, bei LMX > 0 GI laden
	dbaobl.file_no = OBL;
	dbaobl.rec_no = *on;
	Read (dbaobl, obl);

	dbaidl.file_no = IDL;
	dbaidl.rec_no = obl.zoid;
	Read (dbaidl, idl);
	*id = idl.idn;

	if (obl.zokp > 0) {		// Punktobjekt
		staf[0L] = 1L;
		staf[1L] = 1L;
		if (*lmx > 0) {
			zvgi = obl.zokp;
			DBASSERT (getgip (&zvgi, fex, fey, NULL, NULL));
		} else
			return EOKAY;
	} else if (obl.zovol) {	// Linienobjekt
		staf[0L] = 1L;
		staf[1L] = 2L;
		if (*lmx > 0) {
			zvgi = obl.zovol;
			DBASSERT (getgil (&zvgi, fex, fey, NULL, NULL));
		} else 
			return EOKAY;
	} else if (obl.zovoma > 0) {	// Flaechenobjekt
		staf[0L] = 1L;
		staf[1L] = 3L;
		if (*lmx > 0) {
			zvgi = obl.zovoma;
			lrc = getgif (nl, &zvgi, fex, fey, &zkfn, NULL, NULL);
			if (RC != EOKAY && RC != WFORT)
				return RC;
			zkfnre = zkfn;
		} else
			return EOKAY;
	} else {
	// übergeordnetes Objekt ohne GI */
		if (obl.zovor <= 0)	// Statusfehler
			return db_error (ESTAT, 3038);

		staf[0L] = 2L;
		staf[1L] = 0L;
		return EOKAY;
	}

// GI-Uebergabe bzw. -Nachlieferung, Anzahl der Koordinatenpaare
	DBASSERT (felen (fex, &lenx));
	DBASSERT (felen (fey, &leny));
	if (lenx != leny)		// Laenge X != Laenge Y
		return db_error (EZAEL, 3038);
	
	lendyn = lenx;

#if 0 // ======================================================================	
// Koordinaten von dynamischen Feldern auf Felder ohne Nachladen kopieren
	if (lendyn <= *lmx && x != NULL && y != NULL) {
		DBASSERT (feread (&fex, ADR(_l0,1L), &lendyn, x));
		DBASSERT (feread (&fey, ADR(_l0,1L), &lendyn, y));
		*lgi = lendyn;

	// X-,Y-Felder freigeben
		DBASSERT (ferel (&fex));
		DBASSERT (ferel (&fey));
		if (lrc == WFORT) {
			*nl = WFORT;
			return WFORT;
		}
		return EOKAY;	// Ende ohne Nachladen, bzw. Innenrand nachholen
	}
#endif // =====================================================================

// Koordinaten von dynamischen Feldern auf Felder mit Nachladen
L_100:
	zaehi = lendyn - zael + 1L;
//	if (zaehi <= *lmx) {
		anz = zaehi;
		*lgi = zaehi;
		krc = EOKAY;
		*nl = 0L;
//	} else {
//		anz = *lmx;
//		*lgi = *lmx;
//		akzae = zael + *lmx;
//		krc = WDHLG;
//		*nl = WDHLG;
//	}

#if 0 // ======================================================================	
	if (x != NULL && y != NULL) {
		DBASSERT (feread (&fex, &zael, &anz, x));
		DBASSERT (feread (&fey, &zael, &anz, y));
		if (krc == EOKAY) {
		// X-,Y-Felder freigeben
			DBASSERT (ferel (&fex));
			DBASSERT (ferel (&fey));
			if (lrc == WFORT) {
				*nl = WFORT;
				return WFORT;
			}
		}
	}
#endif // =====================================================================
	
return krc;
} /* end of function */

