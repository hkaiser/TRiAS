/*
DATEI: dbtools.hxx

Die Datei beinhaltet allgemeine Funktionen zu Arbeit mit dBase

Erarbeitet: J. Benkenstein              Begonnen am:    2. Sept. 1993
					Stand vom:      4. Okt.  1993
*/

#ifndef _DBTOOLS_HXX
#define _DBTOOLS_HXX

//  lese Zeichen-Konvertierungsflag aus Projekt-Ini-Datei
Bool GetOemToAnsiiFlag (void);

// setze lokales/globales dBase-Verzeichnis
void SetdBasePfad (void);

class CodeBase;
class Data;
class Window;
//  dBase-Expression prÅfen
Bool CheckdBaseExpression (CodeBase &, Data &, pchar pExpr, // Expression
			   Bool Convert = True,             // AnsiiToOem-Flag
			   Window *pParent = NULL);         // InfoBox-Ausgabe,
							    // wenn Ausdruck fehlerfrei

//  lesen zu einem geg. Alias-Namen den vollst. dBASE-Dateinamen,
//  der Åbergebene Zeiger ist explizit freizugeben
pchar GetFulldBaseName (pchar pAliasName);


#endif  // _DBTOOLS_HXX
