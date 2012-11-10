/*
DATEI: dbtools.cxx

Die Datei beinhaltet allgemeine Funktionen zu Arbeit mit dBase

Erarbeitet: J. Benkenstein			  Begonnen am:	2. Sept. 1993
										Stand vom:	29.6.1995
*/

#include <d4all.h>

extern "C" {
	#include <direct.h>	 	// _getdrive () u.a.
    #include "dbasedll.hr"   // Resourcen-Defines
}

#include "dbtools.htp"	  	// Klassenselektion
#ifdef WIN32
#include <bool.h>
#endif
#include <commonvu.hxx>
#include <d4data.h>		 	// für meisten die CodeBase-Klassen
#include <e4expr.h>		 	// für Klasse Klasse Expr
#ifndef WIN32
#include <storage.h>		// LPSTORAGE
#endif
#include <xtension.h>	   	// für DEX_Error (), DEX_SetError ()
#include <xtensnx.h>
#include <protos.h>			// DELETE ()
#include <dbtools.hxx>	  	// zugeh. Header

const uint WinExecRetOk = 31;

//  externe Variablen		  
extern "C" {
	extern char pDLLName [_MAX_PATH];	// Name der Bibliothek
}

//  Prototypen
char *DelLastBSlash (char *pSt);
void ChangeOldPath (int OldDrive, char *pOldDir);

// lösche letzten '\' in String
char *DelLastBSlash (char *pSt) 
{
	if (!pSt || !*pSt)
		return NULL;

	char *pLastChar = pSt + lstrlen (pSt) - 1;
	if (*pLastChar == '\\')
		*pLastChar = '\0';

	return pSt;
}

//  alten Pfad wieder einstellen
void ChangeOldPath (int OldDrive, char *pOldDir) 
{
	_chdrive (OldDrive);
	chdir (DelLastBSlash (pOldDir));
}

//  lese Zeichen-Konvertierungsflag aus Projekt-Ini-Datei
Bool __export GetOemToAnsiiFlag (void) 
{
	char IniFile [_MAX_PATH] = "";
	char Drive [_MAX_DRIVE] = "";
	char Dir [_MAX_DIR] = "";
	char FName [_MAX_FNAME] = "";
	char Flag [2] = "";
	ResourceFile RF (pDLLName);

	ResString Section (ResID (IDS_DBASEKEY, &RF), 7);
	ResString Search (ResID (IDS_OEMTOANSII, &RF), 13);
	ResString Ext (ResID (IDS_INIEXT, &RF), _MAX_EXT);
	DEX_GetActiveProject (IniFile);
	_splitpath (IniFile, Drive, Dir, FName, NULL);
	_makepath (IniFile, Drive, Dir, FName, Ext.Addr ());

	return (GetPrivateProfileString (Section.Addr (), Search.Addr (), "1",
					Flag, sizeof (Flag), IniFile) && (lstrcmp (Flag, "1") == 0));
}

// setze lokales/globales dBase-Verzeichnis
void __export SetdBasePfad (void) 
{
	char Drive [_MAX_DRIVE] = "";
	char Dir [_MAX_DIR] = "";
	char FName [_MAX_FNAME] = "";
	char oldCwd [_MAX_PATH] = "";
	char LokalPath [_MAX_PATH] = "";
	char GlobalPath [_MAX_PATH] = "";

	ResourceFile RF (pDLLName);

//  lokales Verzeichnis lesen
	DEX_GetActiveProject (LokalPath);

//  globales Verzeichnis lesen
	char IniFile [_MAX_PATH] = "";
	DEX_GetMainIniName (IniFile);
	ResString Search (ResID (IDS_DBASEKEY, &RF), 20);
	ResString Section (ResID (IDS_PFADSECTION, &RF), 20);
	GetPrivateProfileString (Section.Addr (), Search.Addr (), "",
							 GlobalPath, _MAX_PATH, IniFile);

//  Prüfen, ob Unterverzeichnis ".\DBASE" zu GeoDBPath existiert
//  wenn nicht wird globales Verzeichnis als Voreinstellung verwendet
	int oldDrive = _getdrive ();
	getcwd (oldCwd, _MAX_PATH);
	_splitpath (LokalPath, Drive, Dir, NULL, NULL);
	if (_chdrive (toupper (Drive [0] ) - 'A' + 1) == 0)    // Lw. OK
	{
		if (chdir (DelLastBSlash (Dir)) == 0) 			 // Verz. OK
		{
			_makepath (oldCwd, Drive, Dir, NULL, NULL);
			lstrcat (oldCwd, ResString (ResID (IDS_DBASESUBDIR, &RF), 10));
			if (chdir (DelLastBSlash (oldCwd)))  // bei Fehler gl. Verz.
				ChangeOldPath (oldDrive, GlobalPath);
		} else
			ChangeOldPath (oldDrive, oldCwd);
	} 
}

//  dBase-Expression prüfen
//  Expression liegt im ANSII-Format vor
Bool __export CheckdBaseExpression (CodeBase &CB, Data &DataFile, pchar pExpr,
						   Bool Convert,		 	// OemToAnsii-Flag
						   pWindow  pParent)    	// Ausgabe einer OK-Meldung
{						   
//  prüfe Parameter
	if (!pExpr || !*pExpr) 
	{
		DEX_Error (RC_dBase, EC_ILLPARS)
		return False;
	}
	if (CB.error ())
		return False;

	if (Convert)
		AnsiToOem (pExpr, pExpr);

//  Expression prüfen
	Expr Expression (&DataFile);		  // Expression-Objekt erzeugen
	Expression.source = pExpr;			  // dBase-Expression laden
	Expression.source.add (StrChar (0));  // null termination	

	short Ret = Expression.parse ();	  // Expr. prüfen
	Expression.free ();					  // Expr. freigeben	

	if (Ret == r4success && pParent) 	  // OK-Meldung ggf. ausgeben
	{
		ResourceFile RF (pDLLName);
		ResString Caption (ResID (IDS_EXPROKCAPT, &RF), 10);
		ResString Text (ResID (IDS_EXPROKTEXT, &RF), 40);
		InfoBox IB (Caption.Addr (), Text.Addr (), pParent);
		IB.Show ();
	}

	return (Ret == r4success ? True : False);
}

//  lesen zu einem geg. Alias-Namen den vollst. dBASE-Dateinamen,
//  1. Alternative: suche im zur DB lokalen dBase-Verzeichnis
//  2. Alternative: suche im in der TRIAS-INI angeg. dBase-Verzeichnis
//  der übergebene Zeiger ist explizit freizugeben
//	Zeiger ist NULL, wenn
//	a) kein dyn. Speicher mehr vorhanden ist oder
//	b) die Datei nicht geöffnet werden konnte
pchar __export GetFulldBaseName (pchar pAliasName) 
{
//  prüfe Parameter
	if (! pAliasName || ! *pAliasName) 
	{
		DEX_Error (RC_GetFulldBaseName, EC_SYSERROR)
		return NULL;
	}

	pchar pFullName = new char [_MAX_PATH];
	if (! pFullName) 
	{
		DEX_Error (RC_GetFulldBaseName, EC_NOMEMORY);
		return NULL;
	}
	*pFullName = '\0';

//  Ini-Dateinamen bilden
	char IniFile [_MAX_PATH] = "";
	char Drive [_MAX_DRIVE] = "";
	char FName [_MAX_FNAME] = "";
	char Dir [_MAX_DIR] = "";

	ResourceFile RF (pDLLName);
	ResString Ext (ResID (IDS_INIEXT, &RF), _MAX_EXT);
	ResString dBaseExt (ResID (IDS_DBASEEXT, &RF), _MAX_EXT);
	DEX_GetActiveProject (IniFile);
	_splitpath (IniFile, Drive, Dir, FName, NULL);
	_makepath (IniFile, Drive, Dir, FName, Ext.Addr ());

//  zugeh. Eintrag lesen
	OFSTRUCT of;
	ResString Section (ResID (IDS_ALIASNAMES, &RF), 20);
	if (GetPrivateProfileString (Section.Addr (), pAliasName, "",
							 pFullName, _MAX_PATH, IniFile))
	{
		_splitpath (pFullName, Drive, Dir, FName, NULL);
		_makepath (pFullName, Drive, Dir, FName, dBaseExt.Addr ());
		if (OpenFile (pFullName, &of, OF_EXIST) == HFILE_ERROR)
		{
			DELETE_VEC (pFullName);
			return NULL;
		}	
		return pFullName;
	}

//  wenn kein Alias-Eintrag gefunden, suche Datei im lokalen dBASE-Verzeichnis 
	_makepath (pFullName, Drive, Dir, NULL, NULL);
	lstrcat (pFullName, ResString (ResID (IDS_DBASESUBDIR, &RF), 13));
	lstrcat (pFullName, "\\");
	lstrcat (pFullName, pAliasName);
	lstrcat (pFullName, dBaseExt.Addr ());

//  Dateiname OK ?
	if (OpenFile (pFullName, &of, OF_EXIST) == HFILE_ERROR ) 
	{
	// 	Datei steht nicht lokal zu dieser DatenBasis: zentralen Namen
	// 	generieren
		DEX_GetMainIniName (IniFile);
		ResString Search (ResID (IDS_DBASEKEY, &RF), 20);
		Section = ResString (ResID (IDS_PFADSECTION, &RF), 20);
		if (GetPrivateProfileString (Section.Addr (), Search.Addr (), "",
									 pFullName, _MAX_PATH, IniFile) == 0) 
		{
			DELETE_VEC (pFullName);
			return NULL;
		}                  
		_splitpath (pFullName, Drive, Dir, NULL, NULL);
		_makepath (pFullName, Drive, Dir, pAliasName, dBaseExt.Addr ());
		if (OpenFile (pFullName, &of, OF_EXIST) == HFILE_ERROR ) 
		{
			DELETE_VEC (pFullName);
			return NULL;
		}                  
		return pFullName;
	}

	return pFullName;
}

// Index-Datei verwenden/nicht verwenden
Bool __export GetUseIndex (void)
{
	char IniFile [_MAX_PATH] = "";
	char Drive [_MAX_DRIVE] = "";
	char Dir [_MAX_DIR] = "";
	char FName [_MAX_FNAME] = "";
	char Flag [2] = "";
	ResourceFile RF (pDLLName);

		ResString Section (ResID (IDS_DBASEKEY, &RF), 7);
	ResString Search (ResID (IDS_USEINDEX, &RF), 10);
	ResString Ext (ResID (IDS_INIEXT, &RF), _MAX_EXT);
	DEX_GetActiveProject (IniFile);
	_splitpath (IniFile, Drive, Dir, FName, NULL);
	_makepath (IniFile, Drive, Dir, FName, Ext.Addr ());
	return (GetPrivateProfileString (Section.Addr (), Search.Addr (), "1",
					Flag, sizeof (Flag), IniFile) && (lstrcmp (Flag, "1") == 0));
}

/*
//  lese Anzeige AliasNamen-Flag aus Projekt-Ini-Datei
Bool __export GetAliasNameFlag (void) 
{
	char IniFile [_MAX_PATH] = "";
	char Drive [_MAX_DRIVE] = "";
	char Dir [_MAX_DIR] = "";
	char FName [_MAX_FNAME] = "";
	char Flag [2] = "";
	ResourceFile RF (pDLLName);

	ResString Section (ResID (IDS_DBASEKEY, &RF), 7);
	ResString Search (ResID (IDS_AL_FIELD_NAMES, &RF), 20);
	ResString Ext (ResID (IDS_INIEXT, &RF), _MAX_EXT);
	DEX_GetActiveProject (IniFile);
	_splitpath (IniFile, Drive, Dir, FName, NULL);
	_makepath (IniFile, Drive, Dir, FName, Ext.Addr ());

	return (GetPrivateProfileString (Section.Addr (), Search.Addr (), "0",
					Flag, sizeof (Flag), IniFile) && (lstrcmp (Flag, "1") == 0));
}
  
Bool __export WriteAliasNameFlag (Bool bShow)
{
	char IniFile [_MAX_PATH] = "";
	char Drive [_MAX_DRIVE] = "";
	char Dir [_MAX_DIR] = "";
	char FName [_MAX_FNAME] = "";
	char Flag [3] = "";
	if (bShow)
		lstrcpy (Flag, "1");
	else		
		lstrcpy (Flag, "0");
	ResourceFile RF (pDLLName);

	ResString Section (ResID (IDS_DBASEKEY, &RF), 7);
	ResString Search (ResID (IDS_AL_FIELD_NAMES, &RF), 20);
	ResString Ext (ResID (IDS_INIEXT, &RF), _MAX_EXT);
	DEX_GetActiveProject (IniFile);
	_splitpath (IniFile, Drive, Dir, FName, NULL);
	_makepath (IniFile, Drive, Dir, FName, Ext.Addr ());	
	return WritePrivateProfileString (Section.Addr (), Search.Addr (), Flag, IniFile);
}  
*/

//  den vollständigen Namen des DQL-Editors lesen
char * __export GetEditName (char *Editor, short Size) 
{
	char IniFileName [_MAX_PATH] = "";
	if (! DEX_GetMainIniName (IniFileName))
		return NULL;            

	ResourceFile RF (pDLLName);
	ResString EdKey (ResID (IDS_EDKEY, &RF), 12);
	ResString DefEd (ResID (IDS_DEFED, &RF), 8);
	ResString EdSection (ResID (IDS_EDSECTION, &RF), 10);

	GetPrivateProfileString (EdSection.Addr (), EdKey.Addr (), DefEd.Addr (),
							 Editor, Size, IniFileName);

	return Editor;
}

void __export RunTriasEdit (Window *pParent, char *pCmdLine, uint uiMode)
{
// 	prüfe Parameter
	if (!pCmdLine || !pParent)
		return;		

	uint uiRet = WinExec (pCmdLine, uiMode);
	if (uiRet > WinExecRetOk)
		return;

//	Fehlermeldung ausgeben
	ResourceFile RF (pDLLName);	
	ResString strErr (ResID (IDS_EDSECTION, &RF), 20);				// Dummy-Text
	ResString strCaption (ResID (IDS_LOAD_EDIT_CAPTION, &RF), 30);
	switch (uiRet)
	{
		case 0:
			strErr = ResString (ResID (IDS_SYSTEM_ERROR, &RF), 50);			
		break;                                 
#ifdef WIN32		
		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
#else 
		case 2:                 // ERROR_FILE_NOT_FOUND
		case 3:                 // ERROR_PATH_NOT_FOUND
#endif		
			strErr = ResString (ResID (IDS_EDIT_NOT_FOUND, &RF), 50);			
		break;
#ifdef WIN32		
		case ERROR_BAD_FORMAT:
#else 
		case 11:             	// ERROR_BAD_FORMAT
#endif			
			strErr = ResString (ResID (IDS_BAD_FORMAT, &RF), 50);			
		break;
		default:
			strErr = ResString (ResID (IDS_GEN_ERROR, &RF), 50);			
		break;
	}		

	MessBox mb (strCaption.Addr (), strErr.Addr (), pParent);
	mb.SetType (OkayButton | ExclamationIcon);
	mb.Show();
}

