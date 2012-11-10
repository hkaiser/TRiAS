/*
File: REALEDIT.CXX
reelisiert die Verwaltung eines SingleLineEdit, das die Eingabe
auf eine Real-Zahl beschränkt.

erarbeitet : J. Benkenstein                              Begonnen am 9. Juni 1993
														 Stand vom 11. Mai 1995
*/

#include "pheader.h"

extern "C" {
	#include <ctype.h>          // isdigit ()
}

#include "numedit.hxx"           // NumEdit
#include "realedit.hxx"          // zugeh. Header

void __export RealEdit :: KeyDown (KeyEvt KE) {
	char ch = KE.ASCIIChar ();
	if (ch == NULL                            // nicht druckbar oder keine Control-Taste
		|| iscntrl (ch)                  // Control-Taste
		|| isdigit (ch)                  // Zahl
		|| (ch == '+')                    // Vorzeichen
		|| (ch == '-')
		|| (ch == '.')                    // Dezimal-Punkt
		|| (ch == 'e')                    // Exponential-Darstellung    
		|| (ch == 'E'))          

	Default ((Event &) KE);  // Ausgabe des Zeichen durch WINDOWS
	else
		MessageBeep (MB_ICONHAND);
}
