/*
File: REALEDIT.CPP
reelisiert die Verwaltung eines SingleLineEdit, das die Eingabe
auf eine Real-Zahl beschränkt.

erarbeitet : J. Benkenstein                     Stand vom 1.9.1995
														 Stand vom 11. Mai 1995
*/

#include "pheader.hpp"

extern "C" {
	#include <ctype.h>          // isdigit ()
}

#include "numedit.hpp"           // NumEdit
#include "realedit.hpp"          // zugeh. Header

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
