/* Routinen fuer ASCII-Parser					*/
/* File: ASCPARSC.C						*/

#include "StdAfx.h"

#include "ascbna.h"
#include "ascerrs.h"

#include "input.h"

/* lokale Prototypen */
static int next_line (void);

/* Object bearbeiten */
int end_previous_object (void) 
{
	lgi++;		/* Geometriezaehler korrigieren */
	if (lgi < koord_paare)
		return (db_error (EGCNT, ASCPARSER, yylineno));

// auswerten ob Komplexobjekt 
	if (lgi == 0) {
		sta[0] = K_OBJEKT;	// Status setzen
		sta[1] = 0;		
	}

	putbna (cbOKS, sta, mi, lgi, gxi, gyi);
	return 0;
}

/* Objekt neu initialisieren */
void init_new_object (void) {

	lgi = -1;  	/* noch keine Geometrie gelesen */
	mi[0] = MAXMI;	/* Merkmalsfeldgroesse */
	mi[1] = 0;	/* noch keine Merkmale gelesen */
	curr_mi = &mi[-1];	/* aktuelle Merkmalswerte */
	curr_mi_text = (char *)&curr_mi[3];
	koord_paare = 0;	/* Anzahl der Stuetzpunkte */
	mi_count = 3;		/* Zaehler der Merkmalswerte */
	mi_werte = 0;		/* Anzahl der Merkmalswerte */
	satz_nr = on = 0;

	sta[0] = E_OBJEKT;	// fr alle F„lle wieder auf ElementarObjekt
}

/* Objekt ueberspringen */
int error_skip_lines (char *pattern, int error_code) 
{
/* Fehlermeldung ausgeben */

	db_error (error_code, ASCPARSER, yylineno);
	satz_nr = 0;			/* Objekt nicht speichern */
	skip_lines (pattern);	/* Satz suchen */

return (error_code);
}

// Umkonvertieren einer dezimalzahl in eine HexZahl ---------------------------
unsigned long MakeHex (unsigned long lPseudoHex)
{
char pTmp[40];

	ultoa (lPseudoHex, pTmp, 10);
	return strtoul (pTmp, NULL, 16);
}
