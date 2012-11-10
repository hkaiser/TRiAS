/*
DATEI: dbtools.hxx

Die Datei beinhaltet allgemeine Funktionen zu Arbeit mit dBase

Erarbeitet: J. Benkenstein              Begonnen am:    2. Sept. 1993
										Stand vom:      11. Sept. 1995
*/

#ifndef _DBTOOLS_HXX
#define _DBTOOLS_HXX

//  lese Zeichen-Konvertierungsflag aus Projekt-Ini-Datei
E4EXPORT_FCT Bool GetOemToAnsiiFlag (void);
     
//	lese Anzeige dBASE-AliasFeld-Namen-Flag aus Projekt-Ini-Datei    
// Bool GetAliasNameFlag (void);

//	Schreibe Anzeige dBASE-AliasFeld-Namen-Flag aus Projekt-Ini-Datei    
// Bool WriteAliasNameFlag (Bool Show); 

// setze lokales/globales dBase-Verzeichnis
E4EXPORT_FCT void SetdBasePfad (void);

class E4EXPORT CodeBase;
class E4EXPORT Data;
class Window;
//  dBase-Expression prüfen
E4EXPORT_FCT Bool CheckdBaseExpression (CodeBase &, Data &, pchar pExpr, // Expression
			   Bool Convert = True,             // AnsiiToOem-Flag
			   Window *pParent = NULL);         // InfoBox-Ausgabe,
							    // wenn Ausdruck fehlerfrei

//  lesen zu einem geg. Alias-Namen den vollst. dBASE-Dateinamen,
//  der übergebene Zeiger ist explizit freizugeben
E4EXPORT_FCT pchar GetFulldBaseName (pchar pAliasName);

// Index-Datei verwenden/nicht verwenden
E4EXPORT_FCT Bool GetUseIndex (void);

//	lese AliasFieldFileName über AliasName der dBase-Datei 
//	Speicher ist explizit freizugeben
E4EXPORT_FCT char *GetAliasFileName (char *pAliasName);
       
//	Namen des akt. TRIAS-Editors lesen       
E4EXPORT_FCT char * GetEditName (char *Editor, short Size); 

//	TriasE-Editor ausführen: Fehlermeldung ggf. erzeugen
class Window;
E4EXPORT_FCT void RunTriasEdit (Window *pParent, char *pCmdLine, uint uiMode);

#endif  // _DBTOOLS_HXX
