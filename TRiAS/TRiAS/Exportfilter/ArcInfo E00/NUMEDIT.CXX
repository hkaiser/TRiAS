/*
File: NUMEDIT.HXX
reelisiert die Verwaltung eines SingleLineEdit, die die Eingabe
auf Ziffer beschränkt.

erarbeitet : J. Benkenstein				 Begonnen am 9. Juni 1993
*/

#include "stdafx.h"               

extern "C" {
	#include <ctype.h>		  	// isdigit ()
}

#include "numedit.hxx"		  	// zugeh. Header-File

//  NumEdit ---------------------------------------------------------------
NumEdit :: NumEdit (pDialogWindow pDW , ResID rID)
: ControlWindow (new SingleLineEdit (pDW, rID)) {
	SetStyle (ES_LEFT | WS_BORDER);
}

NumEdit :: ~ NumEdit (void) {
	SingleLineEdit *pSE = (SingleLineEdit *) GetControl ();
	DELETE_OBJ (pSE);
}

void EXPORTFLT NumEdit :: KeyDown (KeyEvt KE) {
	char ch = KE.ASCIIChar ();
	if (ch == NULL				  	// nicht druckbar oder keine Control-Taste
		|| iscntrl (ch)			 	// Control-Taste
		|| isdigit (ch))			// Zahl

	Default ((Event &) KE);	 		// Ausgabe des Zeichen durch WINDOWS
	else
		MessageBeep (MB_ICONHAND);
}

void NumEdit :: GetText (pchar pText, short MaxLen) {
	if (pText)
		((SingleLineEdit *) GetControl ()) -> GetText (pText, MaxLen);
}

Bool NumEdit :: isModified (void) {
	return ((SingleLineEdit *) GetControl ()) -> isModified ();
}

void NumEdit :: SetText (pchar pText) {
	if (pText && *pText)
		((SingleLineEdit *) GetControl ()) -> SetText (pText);
}
