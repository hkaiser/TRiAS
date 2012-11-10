// Zusammenstellen aller Objekte, die in thematischer Relation zu gegebenen
// Objekt stehen
// File: RELATION.CXX

#include "triaspre.hxx"

// globale Daten
extern Window *CurrActW;
extern App *CurrApp;

// Größe des Objektfeldes
#define OBJNUM 40

// Diese Funktion untersucht ein vorgegebenes Objekt und liefert alle
// Objektnummern, die mit diesem Objekt in thematischer Relation stehen
ErrCode GeoDB :: RelInfo (long ON, ObjFeld &Objekte) {
// Überprüfen, ob DB eröffnet ist
	if (!isOpened())
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_RelInfo);

long RelFeld[OBJNUM+2];         // Feld für Relationen
long NachLaden = 0;             // Nachladeparameter
ObjNummerCreator ONC (Objekte);

	do {
		RelFeld[0] = OBJNUM;
		RelFeld[1] = 0;
	// Relationen lesen
	ErrCode EC = (ErrCode)getri (&NachLaden, &ON, RelFeld);
		if (EC != EC_OKAY && EC != WC_WDHLG)
			return EC;              // Fehler aufgetreten
	
	// Windows abfragen
		App :: Exec (ExecWhileEvent);

	// Objekt in Container einspeichern
		for (register int i = 0; i < RelFeld[1]; i += 2)
			Create (ONC, ObjNummer)(RelFeld[i+2]);
	} while (NachLaden);

return EC_OKAY;
}

