// Memberfunktionen fuer SchrankFachanzeige
// File: SCHRANK.CXX

#include "triaspre.hxx"

#include <stdio.h>

#include "schrank.hxx"

extern SchrankSchnulli *pSchrank;
extern Bool SchrankCFlag;
extern pWindow CurrActW;

extern Bool Nomen10CFlag, Nomen25CFlag, Nomen50CFlag;

void IrisWind :: MenuSelectSchrank (void) {

	if (!(Nomen10CFlag || Nomen25CFlag || Nomen50CFlag))
		return;          // nur mit Nomenklatur erlaubt
	SchrankCFlag = !SchrankCFlag;
	if (SchrankCFlag) {
		if (!pSchrank)   
			pSchrank = new SchrankSchnulli (this);
		pSchrank -> Show();      // anzeigen
		SetFocus();             // Focus im Hauptfenster lassen
		ValidateWindow ();      // Kein RePaint 
	} else if (pSchrank) {
		pSchrank -> Hide();      // nicht mehr anzeigen
		delete pSchrank;         // Speicher freigeben
		pSchrank = NULL;
	}
}

// Konstruktor ----------------------------------------------------------------
SchrankSchnulli :: SchrankSchnulli (pWindow pW)
		 : ModeLessDialog (pW, ResID (SCHRANK))
{
// RadioButtons generieren
	for (short i = 0; i < NUMFACH; i++) {
		_Fach[i] = new RadioButton (this, IDT_FACH01+i);
		if (_Fach[i] == NULL) {
			db_error (EC_NOMEMORY, RC_ctSchrankSchnulli);
			return;
		}
	}
// Position festlegen
	ChangePosition (Point (0, 135));
}


// Destruktor -----------------------------------------------------------------
SchrankSchnulli :: ~SchrankSchnulli (void) {

	for (short i = 0; i < NUMFACH; i++) 
		DELETE (_Fach[i]);
}


// Abfrage vor l”schen --------------------------------------------------------
Bool SchrankSchnulli :: QueryClose (Event) {

	SchrankCFlag = FALSE;

return TRUE;		// auf jeden Fall raus
}

// FocusEvent -----------------------------------------------------------------
void SchrankSchnulli :: FocusChange (FocusChangeEvt /* e */) {}
#if 0
	if (!e.gotFocus()) {	// hat Focus abgegeben
		CurrActW -> SetFocus();
//		((IrisWind *)CurrActW) -> ValidateWindow();
	}
}
#endif

// Schrankfach anzeigen -------------------------------------------------------
void SchrankSchnulli :: SetFach (char *Nomenklatur) {
short NM = 0, A, B;
static short FachNummer = 0;
short newNum;

	sscanf (Nomenklatur, "%c-%d-%d", &NM, &A, &B);
	if (FachNummer != (newNum = GetFachNummer (NM, A, B) -1)) {
		for (short i = 0; i < NUMFACH; i++)
			Fach(i).SetState (FALSE);
		Fach(newNum).SetState (TRUE);
		FachNummer = newNum;
	}
}

// Zuordnen der Nomenklatur zu einem Schrankfach ------------------------------
short SchrankSchnulli :: GetFachNummer (short NM, short A, short B) {

	if (NM == 'N') {		// obere H„lfte
		if (A == 32) {		// linker Streifen
			if (B <= 96) 
				return FACH_MECKLENBURG;
			else 
				return FACH_SACHSENANHALT;
		} else {		// rechter Streifen
			if (B <= 96)
				return FACH_MECKLENBURG;
			else if (B == 97 || B == 109 || B == 121 || B == 133) 
				return FACH_SACHSENANHALT;
			else 
				return FACH_BRANDENBURG;
		}
	} else {			// untere H„lfte
		if (A == 32) {		// linker Streifen
			if (B <= 24)
				return FACH_SACHSENANHALT;
			else
				return FACH_THUERINGEN;
		} else {
			if (B == 1 || B == 13)
				return FACH_SACHSENANHALT;
			else if (B <= 24)
				return FACH_BRANDENBURG;
			else
				return FACH_SACHSEN;
		}
	}
}
