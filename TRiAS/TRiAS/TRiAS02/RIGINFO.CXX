// Finden aller Objekte, die mit einem vorgegebenen Objekt etwas zu tun haben
// File: RIGINFO.CXX

#include "trias02p.hxx"

#include <objfeld.hxx>
#include <pbd.hxx>

// Größe des Objektfeldes
const long OBJNUM = 40;

// GeoDB :: RigInfo untersucht ein vorgegebenes Objekt und liefert zu
// diesem alle Objektnummern, die mit dem vorgegebenen Objekt in topo-
// logischer Beziehung stehen
ErrCode GeoDB :: RigInfo (long ON, ObjFeld &Objekte) 
{
// überprüfen, ob DB eröffnet ist
	if (!isOpened())
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_RigInfo);

// DB aktivieren
CActDB ActDB (*this);
long *RigFeld;
int num;
ObjNummerCreator ONC (Objekte);

// RIG-Info anfordern
ErrCode EC = GetRigObj (ON, &num, &RigFeld);

	if (EC != EC_OKAY) return EC;              // Fehler aufgetreten

	for (register int i = 0; i < num; i++)
		Objekte.NewObj (ONC, RigFeld[i]);

	DELETE_OBJ(RigFeld);         // Feld wieder freigeben

return EC_OKAY;
}


// Eigentliche Funktion zur Extraktion der topologoischen Information
ErrCode GeoDB :: GetRigObj (long ON, int *num, long **Result) {
long NachLaden = 0;             // Nachladeparameter
long RigFeld[OBJNUM+2];
long X, Y;                      // Koordinaten des aktuellen Knotenpunktes
long FlexNum = 0;               // FlexNummer
long Irc;
CActDB ActDB (*this);

	*num = 0;
	if ((Irc = feini_ (&FlexNum)) != 0)     // Flex initialisieren
		return (ErrCode)Irc;
	do {
		RigFeld[0] = OBJNUM;    // max. mögliche RIG-Anzahl
		RigFeld[1] = 0;         // Feld ist leer

	ErrCode EC = (ErrCode)getrig (DBDesc(), &NachLaden, &ON, &X, &Y, RigFeld);

		if (EC == WC_NORIG && NachLaden == 0)
			break;
		if (EC != EC_OKAY && EC != WC_NORIG && EC != WC_WDHLG &&
		    EC != WC_FORT && EC != WC_FORTR && EC != WC_FORTI)
		// Fehler
			return EC;
	// Windows - Events abfragen
		App :: Exec (ExecWhileEvent);		
		ActDB.ReActivate();	// sicherheitshalber wieder aktivieren

	// Objektnummern in Flex abspeichern
		for (register int i = 0; i < RigFeld[1]; i += 2)
			if ((Irc = feput_ (&FlexNum, &RigFeld[i+2])) < 0)
				return (ErrCode)Irc;
	} while (NachLaden);

// Objekte in Flex sortieren
	flqsrt_ (&FlexNum);             // Objekte sortieren
long Begin = 1, Len;
	flredn_ (&FlexNum, &Len);       // doppelte ObjNummern entfernen

// Objekte in Resultatfeld umkopieren
	*Result = new long [Len];
	if (*Result == NULL)
		return (ErrCode)db_error ((int)EC_NOMEMORY, (int)RC_GetRigObj);
	feread_ (&FlexNum, &Begin, &Len, *Result);
					// Daten auslesen
// Flex wieder freigeben
	ferel_ (&FlexNum);              // Flex wieder l”schen
	*num = (int)Len;                // L„nge liefern

return EC_OKAY;
}


