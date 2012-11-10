/*Translated by FOR_C, v3.1, on 02/27/91 at 18:35:16 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
/*+
 *       *****************************************************************
 *       * Wiederauffinden eines Objektes in der DB                      *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, Bereich 2
 *       Dokumentationsnummer: AE0-610-A64403
 *       Autor:                Major, W.
 *       Datum:                04-Okt-90
 *       Modulname:            *** GETGI ***
 *       Routinenummer:        3002
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         -
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         GETGIP,GETGIL,GETGIF
 *       libdbr.a    :         -
 *       libzipedb.a :         ZREAD,FEINI,FEREL,FELEN,FEREAD,SETERR,LADR
 *                             ERRFKT
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
 *        IRC=GETGI (NL,ON,ID,STAF,LMX,LGI,X,Y)
 *
 *                 IRC    - Rueckkehrcode                              I*4
 *                          bei notwendigem Nachladen ist IRC=WDHLG als
 *                          Output, bzw. WFORT fuer folgende Innenkanten
 *                 GETGI  - Funktion                                   I*4
 *
 *       Parameter:
 *                 NL  - Nachladeparameter                             I*4
 *                 = 0 - 1.Eingang; bzw. als Output, wenn alle Koo.
 *                       geliefert sind
 *                 =WDHLG - wiederholter Aufruf der GETGI-Funktion zum
 *                          Nachladen der Koordinaten (Output=Input)
 *                 =WFORT - wiederholter Aufruf der GETGI-Funktion zum
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
 *          GETGI liefert den Identifikator,den Status und die Geometrie
 *          zu einem vorgegebenen Objekt (Geometrie wahlweise nur bei EOK).
 *          Loescht bei Neieingang (NL=0) evtl. noch offene dyn. Felder.
 *
 *       Fehlerbehandlung:
 *
 *       Fehler : EOKAY    i.O.
 *                ESTAT    Statusfehler
 *                ENODIM   Dimension LMX GI-Felder falsch
 *                ENOON    ON-Nr. nicht vorhanden
 *                EZAEL    Laenge X-Feld ungleich Laenge Y-Feld
 *                weitere Fehler aus gerufenen Funktionen moeglich, sie
 *                werden weitergegeben
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

extern "C"
long EXPORT02 FUNCTYPE getgi(HPROJECT hPr, 
			long *nl, long *on, long *id, long *staf, long *lmx, long *lgi, 
			long *fex, long *fey, long *cont, long *window)
{
long int lrc = 0, lenx, leny, zkfn;
DB_ADDR dbaidl(hPr);
DB_ADDR_OBL dbaobl(hPr);
struct idl idl;
struct obl objekt;
static long int zkfnre = 0;
ErrCode RC;

	/* *** Anfangswerte setzen: */
	if (cont != NULL) {
		cont[0] = MAXKOORD;
		cont[1] = -1;
		cont[2] = MAXKOORD;
		cont[3] = -1;
	}
	if (*nl == 0)
		lrc = EC_OKAY;
	if (*nl == WFORT)	// weiterer InnenRand vorhanden
		zkfn = zkfnre;
	else 
		zkfn = 0;
	*lgi = 0L;

	if ((*on <= 0) || (*on > ladr (hPr, &dbaobl.file_no, true))) 
	/* Objektnr. ausserhalb Bereich */
		return db_error ((short)ENOON, 3002);

	if ((*lmx < 1) && (*lmx != (-1))) 
	/* LMX falsch */
		return db_error ((short)ENODIM, 3002);

	if (*lmx > 0) {
	/* X-,Y-Felder initialisieren: */
		*fex = 0L;
		DBASSERT (feini (fex));
		*fey = 0L;
		DBASSERT (feini (fey));
	}

/* *** Identifikator lesen, Status bestimmen, bei LMX > 0 GI laden: */
//	dbaobl.file_no = OBL;
	dbaobl.rec_no = *on;
	memset (&objekt, '\0', sizeof(objekt));		// VersionsKontrolle
	__Read (dbaobl, objekt);
	if (objekt.zovor >= MAXPOSLONG) 		/* geloeschtes Objekt */
		return db_error ((short)ENOON, 3002);

	dbaidl.file_no = IDL;
	dbaidl.rec_no = objekt.zoid;
	__Read (dbaidl, idl);
	*id = idl.idn;

// wenn Komplexobjekt, dann ohne Geometrie wieder raus
	if (objekt.rmaske & OREL) {
		staf[0] = 2;	// Komplexobjekt
		staf[1] = 0;
		return EC_OKAY;
	}

// Elementarobjekt
	staf[0] = 1;
	if (objekt.zokp > 0) {
	/* Punktobjekt oder TextObjekt */
		if (objekt.status & (SB_TEXTOBJ|SB_TEXTOBJIND)) 
		// TextObjekt
			staf[1] = 4;
		else
			staf[1] = 1;
		if (*lmx > 0) {
			DBASSERT (getgip (hPr, &objekt.zokp, fex, fey, cont, window));
		} else 
			return EC_OKAY;
	} else if (objekt.zovol > 0) {
	// Linienobjekt 
		staf[1] = 2;
		if (*lmx > 0) {
			DBASSERT (getgil (hPr, &objekt.zovol, fex, fey, cont, window));
		} else
			return EC_OKAY;
	} else if (objekt.zovoma > 0) {
	// Flaechenobjekt
		staf[1] = 3;
		if (*lmx > 0) {
			lrc = getgif (hPr, nl, &objekt.zovoma, fex, fey, &zkfn, cont, window);
			if (lrc != EC_OKAY && lrc != WFORT) 
				return lrc;
			zkfnre = zkfn;
		} else
			return EC_OKAY;
	} else {
	// Statusfehler
		staf[0] = 0;
		staf[1] = 0;
		return db_error ((short)ESTAT ,3002);
	}

/**** GI-Uebergabe bzw. -Nachlieferung:
 *    *** Anzahl der Koordinatenpaare: */
	DBASSERT (felen (fex, &lenx));
	DBASSERT (felen (fey, &leny));
	if (lenx != leny) 	/* Laenge X # Laenge Y */
		return db_error ((short)EZAEL, 3002);

	*lgi = lenx;		// Größe der Geometriefelder

	if (lrc == WFORT) {	// wenn Innenrand folgt
		*nl = WFORT;
		return lrc;
	}

return EC_OKAY;
} 

