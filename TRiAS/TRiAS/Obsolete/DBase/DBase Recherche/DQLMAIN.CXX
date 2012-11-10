// EInsprungroutine (StartUp) fuer DQL - Recherchemodul -----------------------
// File: DQLMAIN.CXX  

#include "pheader.h"

#include "dqlmain.htp"
#include <commonvu.hxx>
#include <containr.hxx>
		
extern "C" {
	#include "dql.h"
	#include "komplexr.hr"	   	// Resourcen-Defines		   
}

#include <clipbrd.hxx>		  	// ClipBoard-Klasse
#include <objfeld.hxx>		  	// ObjNummer
#include <dbliste.hxx>		  	// DBaseObjFeld
#include <ristypes.hxx>		 	// Koord
#include <geo_obj.hxx>		  	// ObjContainer
#include <dbasekey.hxx>		 	// lokale Header
#include <dqlexprt.h>		   	// exportierte Funktionen

#include "yystype.hxx"
#include "rechstat.hxx"
#include <ixtensn.hxx>          // Interfaces einer Erweiterung
#include <xtencunk.hxx>         // InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include "komplexr.hxx"		 	// KomplexrExtension

// globale Variablen ----------------------------------------------------------
CodeBase *pCB = NULL;		   	// CodeBaseKlasse

extern const char *ScriptBuff;  // LEX - EingabeBuffer
extern const char *ScriptEnd;
extern const char *ActChar;

extern KEYWORD *keywords;	   	// aktuelle KeywordTabelle
extern KEYWORD SearchKeys[];

extern YYSTYPE *yyv;			// YACC - Stack
extern YYSTYPE *pyyval;		 	// aktualles YACC - Token
extern YYSTYPE *pyylval;		// aktuelles LEX - Token
extern Bool fSyntaxTestOnly;	// Actions ausführen

extern DBaseFiles *pDBFs;	   	// DBaseDateien
extern char *pExprBuff;		 	// Buffer für ParameterExpansion
extern "C" HINSTANCE g_hInstance;
extern ResourceFile *pRF;
extern pWindow pW;			  	// TRIAS-MainWindow
extern KomplexrExtension *pKE;  // Basisklasse der Erweiterung
extern int yylineno;

RechercheStatus *pRStat = NULL; // Recherche-Status-Fenster
RMode actRechMode = RMUnknown;
long ActCount = 0;
short GroupCount = 0;
pchar pScriptName = NULL;	   	// Dateiname des akt. Scriptes
short RechSem = 0;			  	// RechercheSemaphor

//  lokale Funktionen
ErrCode doRecherche (const char *, RMode, BOOL bParseOnly = FALSE);
char *ReadScript (const char *);

// eigentliche RechercheFunktionen ---------------------------------------
extern "C" {
//  Recherche aus Datei durchführen
ErrCode FAR PASCAL __export doFileRecherche (pchar pFileName, BOOL bParseOnly) {
//  prüfe Pararmeter
	if (!pFileName || !*pFileName) {
		DEX_Error (RC_doRecherche, EC_ILLPARS);
		return EC_ILLPARS;
	}

//  Scriptnamen speichern
	if (! (pScriptName = new char [_MAX_PATH])) {
		DEX_Error (RC_doRecherche, EC_NOMEMORY);
		return EC_NOMEMORY;
	}
	lstrcpy (pScriptName, pFileName);

	char *inScript = ReadScript (pScriptName);	// Script einlesen
	ErrCode EC = doRecherche (inScript, RMFile, bParseOnly); // Recherche

	DELETE_VEC (inScript);  // Speicher freigeben
	DELETE_VEC (pScriptName);

	return EC;
}

//  Recherche aus DatenPuffer durchführen
ErrCode FAR PASCAL __export doBufferRecherche (pchar pScriptBuffer, BOOL bParseOnly) {
//  prüfe Parameter
	if (!pScriptBuffer || !*pScriptBuffer) {
		DEX_Error (RC_doRecherche, EC_ILLPARS);
		return EC_ILLPARS;
	}

//  Script kopieren
	char *pScript = new char [lstrlen (pScriptBuffer) + 1];
	if (!pScript) {
		DEX_Error (RC_doRecherche, EC_NOMEMORY);
		return EC_NOMEMORY;
	}
	lstrcpy (pScript, pScriptBuffer);
	ErrCode EC = doRecherche (pScript, RMBuffer, bParseOnly); // Recherche

	DELETE_VEC (pScript);

	return EC;
}

//  Recherche aus Clipboard durchführen
ErrCode FAR PASCAL __export doClipBoardRecherche (BOOL bParseOnly) {
//  Script aus ClipBoard lesen
	CClipboard DCB;			   // Clipboard-Objekt
	long Size = DCB.GetItemSize (CClipboard :: FmtText);
	short Len = (short) Size;
	if (!Len) {
		DEX_Error (RC_doRecherche, EC_ILLPARS);
		return EC_ILLPARS;
	}
	char *pScript = new char [Len + 1];
	if (!pScript) {
		DEX_Error (RC_doRecherche, EC_NOMEMORY);
		return EC_NOMEMORY;
	}
	if (! DCB.Retrieve (pScript, Len)) {		// Script lesen
		DELETE_VEC (pScript);
		DEX_Error (RC_doRecherche, EC_SYSERROR);
		return EC_SYSERROR;
	}

	*(pScript + Len) = '\0';
	ErrCode EC = doRecherche (pScript, RMClipboard, bParseOnly); // Recherche

	DELETE_VEC (pScript);

	return EC;
}
}	   // extern "C"

// Diese Funktion wird in jedem Fall gerufen, unabhängig davon, ob der Script
// aus einer Datei, einem SpeicherBuffer oder dem ClipBoard gelesen wurde
ErrCode doRecherche (const char *ScrBuff, RMode RechMode, BOOL bParseOnly) {
	if (RechSem) {
		DEX_Error (RC_doRecherche, EC_RECHAKTIV);
		return EC_RECHAKTIV;	// keine doppelte Recherche zulassen
	}
	RechSem++;

//  Parse-Flag setzen
	fSyntaxTestOnly = bParseOnly;

//  ParameterTest
	if (! ScrBuff || !*ScrBuff) {
		DEX_Error (RC_doRecherche, EC_ILLPARS);
		return EC_ILLPARS;
	}

//  Recherche-Daten init.
	if (!pKE) {
		DEX_Error (RC_doRecherche, EC_SYSERROR);
		return EC_SYSERROR;
	}
	ErrCode EC = pKE -> InitRecherche ();
	if (EC != EC_OKAY)
		return EC;

//  CodeBaseKlase initialisieren
	if (! (pCB = CreateCodeBaseObj (g_hInstance))) {
		DEX_Error (RC_doRecherche, EC_NOMEMORY);
		RechSem--;
		return EC_NOMEMORY;
	}

//  YACC - Stack anlegen
	yyv = new YYSTYPE [YYMAXDEPTH];
	pyyval = new YYSTYPE;
	pyylval = new YYSTYPE;
	if (yyv == NULL || pyyval == NULL || pyylval == NULL) {
	//  wieder aufräumen
		if (yyv)
			delete [YYMAXDEPTH] yyv;
		DELETE_OBJ (pyyval);
		DELETE_OBJ (pyylval);
		RechSem--;
		DeleteCodeBaseObj ();

	//  Fehlermeldung und raus
		DEX_Error (RC_doRecherche, EC_NOMEMORY);
		return EC_NOMEMORY;
	}

//  LEX - EingabeBuffer initialisieren
	ScriptBuff = ScrBuff;
	ScriptEnd = &ScriptBuff [lstrlen (ScriptBuff)];
	ActChar = ScriptBuff;
	keywords = SearchKeys;			  // erstmal Suchspezifikation

	yylineno = 1;					   // Zeilenzähler zurücksetzen

	actRechMode = RechMode;			 // Quelle des Scriptes

//  ggf. Status-Anzeige init.
	if (bParseOnly == FALSE) {
		ActCount = 0;
		GroupCount = 0;
		pRStat = new RechercheStatus (pW, *pRF);
		if (!pRStat) {
			RechSem--;
			DeleteCodeBaseObj ();
			DEX_Error (RC_doRecherche, EC_NOMEMORY);
			return EC_NOMEMORY;
		}

		char OldCaption [80] = "";
		char NewCaption [80] = "";
		char Drive [_MAX_DRIVE] = "";
		char Dir [_MAX_DIR] = "";
		char FName [_MAX_FNAME] = "";
		char Ext [_MAX_EXT] = "";

		pRStat -> GetCaption (OldCaption, sizeof (OldCaption) - 1);
		if (RechMode == RMFile && pScriptName && *pScriptName)
			_splitpath (pScriptName, Drive, Dir, FName, Ext);
		else {
			ResString Untitled (ResID (IDS_UNBENANNT, pRF), 20);
			lstrcpy (FName, Untitled.Addr ());
		}
		wsprintf (NewCaption, OldCaption, FName);
		pRStat -> SetCaption (NewCaption);
		pRStat -> Show ();
	}

//  Parser Starten
	EC = yyparse () == 0 ? EC_OKAY : EC_SYNTAX;

	actRechMode = RMUnknown;

//  Speicher wieder freigeben
	DELETE_OBJ (pyylval);				   // diese Pointer müssen gültig sein
	DELETE_OBJ (pyyval);					// sonst wären wir nicht hier
	if (yyv)
		delete [YYMAXDEPTH] yyv;
	DELETE_OBJ (pRStat);

	DELETE_OBJ (pDBFs);			 // DBaseDateien freigeben
	DELETE_VEC (pExprBuff);		 // ExpansionsBuffer

	DeleteCodeBaseObj ();
	pCB = NULL;

//  Recherche wieder freigeben
	RechSem--;

	return EC == EC_OKAY ? pKE -> OutputRecherche (bParseOnly) : EC;
}

// Funktion, die ASCII-Datei in einen Buffer einliest -------------------------
// ACHTUNG: geht davon aus, daß Datei ein ASCII-File ist
char *ReadScript (const char *FileName) {
unsigned int fd;
OFSTRUCT of;

// Datei eröffnen
		if ((fd = OpenFile (FileName, &of, OF_READ)) < 0) {
				DEX_Error (RC_ReadScript, EC_NOFILE);
				return NULL;
		}
// DateiGröße feststellen
long FileLen = _llseek (fd, 0L, 2);	 // EOF
char *inScript = new char [FileLen+1];
		if (inScript == NULL) {
				DEX_Error (RC_ReadScript, EC_NOMEMORY);
				_lclose (fd);
				return NULL;
		}
		*inScript = '\0';	   // sicherheitshalber
// wieder auf Dateianfang positionieren
		_llseek (fd, 0L, 0);
// Datei einlesen
		if (_lread (fd, inScript, (uint) FileLen) != (uint) FileLen) {
				DEX_Error (RC_ReadScript, EC_NOREAD);
				DELETE_VEC (inScript);
				_lclose (fd);
				return NULL;
		}
// Datei schließen
		_lclose (fd);
// String ordnungsgemäß abschließen
		inScript[FileLen] = '\0';

return inScript;
}
