/* Hauptprogramm fuer REPORT - Tabellengenerator                */
/* File: REPTMAIN.C                                             */

#include <stdio.h>

#include "report.h"
 
extern int tot_errs;    /* Fehleranzahl */

void main (int argc, char **argv) {

int Report (char *RScript) {
int EC;		// RÅckkehrKode des YACC-Parsers

// globale Variablen initialisieren
	Script = RScript;			// SteuerProgramm
	ScriptEnd = &Script[strlen(Script)+1];	// ProgrammEnde
	ActChar = Script;			// hier geht's los

// Tabelle generieren
        EC = yyparse();

// interne Variablen des Parsers freigeben
	for (i = 0; i < numVars; i++)
		if (var_table[i].ptr != NULL)
			free (var_table[i].ptr);	// Speicher freigeben

return EC;
}
