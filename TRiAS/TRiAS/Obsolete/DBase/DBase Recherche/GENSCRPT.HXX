/*
Datei: GENSCRPT.HXX

Das Modul stellt ein allgemeines Interface zur Generierung eines DQL-Scriptes
bereit.

Erarbeitet: J. Benkenstein                  Stand vom: 19.10.1993
*/

#ifndef GENSCRPT_HXX
#define GENSCRPT_HXX

//  Aktionen, die ausgeführt werden können/müssen, um einen DQL-Script
//  zu erzeugen
enum EnumScriptAction {
	OpenScript,         // Script-Objekt erzeugen,
			    // ParamType wird nicht ausgewertet,
			    // als "pchar" in pParam übergebener Kommentar,
			    // wenn pParam = NULL - Standard-Kommentar gener.
	FensterSpec,        // Fenster-Spezifikation setzen,
			    // ParamType ist identisch mit EnumSichtSpec (s.u.),
			    // pParam wird enstrechend ausgewertet (s.u.)
	GebietsSpec,        // Gebiets-Spezifikation setzen,
			    // ParamType ist identisch mit EnumGebietsSpec (s.u.),
			    // pParam wird enstrechend ausgewertet (s.u.)
	GenerateScript,     // Script generieren
	ExecuteScript,      // ausführen des generierten Scriptes
	GetScript,          // für die in pParam übergebene "pchar &" wird eine
			    // Kopie des generierten Scriptes erzeugt
	DeleteScript        // freigeben (löschen) des generierten Scriptes
};

extern "C" {
//  exportierte Funktion
//  diese Funktion könnte von TRIAS gerufen werden
BOOL FAR PASCAL __export GenerateDQLScript (
			EnumScriptAction ESA,       // durchzuführende Aktion
			short ParamType = -1,       // Parameter-Typ
			void *pParam = NULL);       // Parameter
}   //	extern "C"

//  Parameter der Sicht-Spezifikation
enum EnumSichtSpec {
	DefaultSicht,       // aktuell in TRIAS dargestellte Sicht
			    // pParam wird nicht ausgwertet
	StringSicht,        // als "pchar" in "pParam" übergebener Sichtname
	IdentList,          // als long* in pParam übergebene ID-Liste,
			    // letzte ID ist 0L
	SelectedObjects,    // pParam wird nicht ausgwertet
	SingleObject	    // als long* in pParam übergebene Objekt-Nummer
};

//  Parameter der Gebiets-Spezifikation
enum EnumGebietsSpec {
	DefaultGebiet,      // aktuell in TRIAS selektierte Fenster
			    // pParam wird nicht ausgwertet
	ActualUmkreis,      // im aktuellen Umkreis
			    // pParam wird nicht ausgwertet
	ActualBuffer	    // im aktuellen Buffer
			    // pParam wird nicht ausgwertet
};

#ifndef NODQLSCRIPT
// Die Klasse speichert alle Informationen um einen DQL-Script zu generieren.
class DQLScript {
private:
//  Attribute
    Bool _Result;                       //  Konstruktor-Flag
//  pchar _pScript;                     //  generierte Script
    pchar _pComment;                    //  Eingangs-Kommentar
    EnumSichtSpec _SichtSpecType;       //  Sicht-Spezifikations-Typ
    EnumGebietsSpec _GebietSpecType;	//  Gebiets-Spezifikations-Typ
public:
//  Konstruktor/Destruktor
    DQLScript (pchar pComment = NULL);	 //  Script anlegen, Kommentar ggf. sp.
    ~DQLScript (void);			 //  alle erzeugten Variablen löschen

//  weitere Member-Funktionen
    Bool SetSichtSpec (EnumSichtSpec ESS, void *pParam = NULL);
    Bool SetGebietsSpec (EnumGebietsSpec EGS, void *pParam = NULL);

//  pchar GetScript (void) { return _pScript; }
    Bool Result (void) { return _Result; }
};
#endif  //  NOSCRIPT

#endif  //  GENSCRPT_HXX
