/*
File: NAMEEDIT.CXX
reelisiert die Verwaltung eines SingleLineEdit, die die Eingabe
auf alphanumerische Zeichen und den Unterstrich "_" beschränkt.

erarbeitet : J. Benkenstein				 Begonnen am 24. Mai 1993
*/

#include "stdafx.h"               

extern "C" {
	#include <ctype.h>		  // isalnum ()
}

#include "nameedit.hxx"		 // zugeh. Header-File

//  NameEdit ---------------------------------------------------------------
NameEdit :: NameEdit (pDialogWindow pDW , ResID rID)
: ControlWindow (new SingleLineEdit (pDW, rID)) {
	SetStyle (ES_LEFT | WS_BORDER);
}

NameEdit :: ~ NameEdit (void) {
	SingleLineEdit *pSE = (SingleLineEdit *) GetControl ();
	DELETE_OBJ (pSE);
}


void EXPORTFLT NameEdit :: KeyDown (KeyEvt KE) {
	char ch = toupper (KE.ASCIIChar ());
	if (ch == NULL				  // nicht druckbar oder keine Control-Taste
		|| iscntrl (ch)			 // Control-Taste
		|| isdigit (ch)			 // Zahl
		|| (ch >= 'A' && ch <= 'Z') // Großbuchstabe
		|| ch == '_')

	Default ((Event &) KE);	 // Ausgabe des Zeichen durch WINDOWS
	else
		MessageBeep (MB_ICONHAND);
}

//  Aktionen auf das enthaltene Control anwenden
void NameEdit :: SetTextLimit (short Limit) {
	((SingleLineEdit *) GetControl ()) -> SetTextLimit (Limit);
}

void NameEdit :: SetText (pchar pText) {
	if (pText && *pText)
		((SingleLineEdit *) GetControl ()) -> SetText (pText);
}

void NameEdit :: GetText (pchar pText, short MaxLen) {
	if (pText)
		((SingleLineEdit *) GetControl ()) -> GetText (pText, MaxLen);
}

Bool NameEdit :: isModified (void) {
	return ((SingleLineEdit *) GetControl ()) -> isModified ();
}
