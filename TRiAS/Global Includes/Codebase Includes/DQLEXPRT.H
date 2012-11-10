/*
Datei: DQLEXPRT.H

Die Datei listet alle von der Komplexrecherche-Extension exportierten
Funktionen.

Erabeitet: J. Benkenstein                       Stand vom 13.11.1995
*/

#ifndef _DQLEXPRT_H
#define _DQLEXPRT_H

extern "C" {
//  Start einer Recherche mit übergebenem Script
//  - als vollständigen Dateinamen
ErrCode FAR PASCAL __export doFileRecherche (char *pFileName,
					    BOOL bParseOnly = FALSE);

//  - als Pufferzeiger
ErrCode FAR PASCAL __export doBufferRecherche (char *pScriptBuffer,
					      BOOL bParseOnly = FALSE);

//  - im Clipboard.
ErrCode FAR PASCAL __export doClipBoardRecherche (BOOL bParseOnly = FALSE);

//  "pParseOnly" - prüft den übergebenen Script auf syntaktische Fehler.
//  Der Script wird dabei nicht ausgeführt.

//  DBase-Dateien über ihre AliasNamen auswählen:
class Window;
BOOL FAR PASCAL __export SelectdBaseFiles (Window *pParentWindow);

//  Eingabe eines dBASE-Ausdrucks:
//  - die Funktion sollte unmittelbar nach "CreateDataTree" gerufen werden
//  - der zurückgegebene Ausdruck ist explizit freizugeben
char * FAR PASCAL __export EntrydBaseExpression (
			  Window *pParent,      // Elternfenster
			  pchar pExpr,          // voreingestellter Ausdruck
			  short ExprSize = 0);  // max. Größe des erz. Ausdrucks:
									// 0 heißt keine Einschränkung

//  dBase-Expression im Dialog eingeben
//  Expression ist explizit freizugeben
//  Zusammenfassung der vorigen beiden Funktionen
char* FAR PASCAL __export EntryExprDialog (
		       pWindow pParentWindow,   // ParentWindow
		       short MaxExprSize,       // max. Länge des neuen Expr.
		       pchar pOldExpr = NULL);  // voreingestellter Expr.

}   // extern "C"

#endif  // DQLEXPRT_H
