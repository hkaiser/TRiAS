/*
File: NUMEDIT.CXX
reelisiert die Verwaltung eines SingleLineEdit, die die Eingabe
auf Ziffer beschränkt.

erarbeitet : J. Benkenstein				 Begonnen am 9. Juni 1993
										 Stand vom 10. Mai 1995	
*/

#include "pheader.h"

extern "C" {
	#include <ctype.h>		  	// isdigit ()
}

#include "numedit.hxx"		  // zugeh. Header-File

//  NumEdit ---------------------------------------------------------------
NumEdit :: NumEdit (pDialogWindow pDW , ResID rID, short sBaseIn)
: ControlWindow (new SingleLineEdit (pDW, rID)) {
	sBase = sBaseIn;				// Zahlenbasis speichern
	SetStyle (ES_LEFT | WS_BORDER);
}

NumEdit :: ~ NumEdit (void) {
	SingleLineEdit *pSE = (SingleLineEdit *) GetControl ();		
        DELETE_OBJ (pSE);
}

void __export NumEdit :: KeyDown (KeyEvt KE) {
	char ch = KE.ASCIIChar ();
	if ((ch == NULL				 // nicht druckbar oder keine Control-Taste
		 || iscntrl (ch)		 // Control-Taste
		 || isdigit (ch))		 // Zahl
		|| ((sBase == 16) && isxdigit (ch)))		
		Default ((Event &) KE);	 // Ausgabe des Zeichen durch WINDOWS
	else
		MessageBeep (MB_ICONHAND);
}

pchar NumEdit :: GetText (pchar pText, short MaxLen) {
	if (pText)
		((SingleLineEdit *) GetControl ()) -> GetText (pText, MaxLen);
	return pText;
}

Bool NumEdit :: isModified (void) {
	return ((SingleLineEdit *) GetControl ()) -> isModified ();
}

void NumEdit :: SetText (pchar pText) {
	if (pText && *pText)
		((SingleLineEdit *) GetControl ()) -> SetText (pText);
}

void NumEdit :: SetTextLimit (short Limit) {
	((SingleLineEdit *) GetControl ()) -> SetTextLimit (Limit);
}

