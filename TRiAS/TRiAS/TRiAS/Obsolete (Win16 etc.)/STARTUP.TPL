// Modul, der IRIS (Windows) von der DOS-Kommandozeile aus startet
// File: STARTUP.C

#include <stdio.h>
#include <conio.h>
#include "exec.h"

static char *Titel = "\r\n"
		     "TRIAS(R) - Territoriales Raumbezogenes Informations- und Abfragesystem\r\n"
		     "Copyright (C) 1991 - 1995 uve GmbH Fernerkundungszentrum Potsdam\r\n"
		     "V@A.@B.@C, #@D\r\n";

void main (int argc, char **argv) 
{
char Line[129];
register int i;

// BildSchirm l”schen, sch”ne Meldung ausgeben
	cputs (Titel);
// Kommandozeile generieren
	strcpy (Line, "/3");
	for (i = 0; i < argc; i++) {
		strcat (Line, " ");
		strcat (Line, argv[i]);
	}
	do_exec ("win", Line, 0, 0, NULL);
}
