/**************************************************************************
 *  Projekt Multi-Menü-Erweiterung
 **************************************************************************
 *  Datei:	       multmenu.hxx
 *  Stand vom:	       05.05.94
 *                     (c) 1994 uve GmbH Potsdam
 **************************************************************************
 * Basisklasse TRIAS-Erweiterung mit dynamisch ver_nderbarem Menn
 *
 * Variante:           Menndefinition in INI-Datei
 * Entwicklung:        05.05.94 Beginn der Kodierung
 **************************************************************************/

#if !defined( _MULTMENU_HXX )
#define _MULTMENU_HXX

extern "C"
{
extern HINSTANCE hInstance;
}

#define MAX_PATH_LEN 256
#define BUFFER_LEN 2048
#define MAX_MENU_COUNT 100

typedef bool (FAR *MENUFUNC)( LPSTR lpIniParam, LPSTR lpParam );

typedef struct tagFUNC_TABENTRY
{
	LPSTR			lpFuncID;
	MENUFUNC		pMenuFunc;
	LPSTR			lParam;
} FUNC_TABENTRY;

typedef FUNC_TABENTRY* FUNCTIONTABLE;

/**************************************************************************
 *  Deklaration der für die Menüs verfügbaren Funktionen
 **************************************************************************
 *  Hier sollten alle Funktionen deklariert werden, die nber die modi-
 *  fizierbaren Menns erreichbar sein sollen. Sie mnssen vom Typ MENUFUNC
 *  sein.
 *  Beim Aufruf werden zwei Parameter nbergeben:
 *    1. die Einträge aus der INI-Datei
 *    2. der in der Tabelle eingetragene Parameter.
 **************************************************************************/
bool AboutFunc( LPSTR, LPSTR );
bool FunctionList( LPSTR, LPSTR );


/**************************************************************************
 *  MenuElement  * intern *
 **************************************************************************
 *  Klasse zur Aufnahme der Definition eines Menueeintrages.
 **************************************************************************/
class MenuElement
{
private:
	LPSTR		bez;
	LPSTR		para;
	UINT		id;
	FUNC_TABENTRY*	pTabEntry;

public:
			MenuElement( LPSTR = NULL,
				LPSTR = NULL, LPSTR = NULL );
			~MenuElement();
	LPSTR		Bezeichnung() { return bez; }
	LPSTR		Code();
	LPSTR		Parameter()   { return para; }
	UINT		ID()          { return id; }

	void		Bezeichnung( LPSTR );
	void		Code( FUNC_TABENTRY* pF ) { pTabEntry = pF; }
	void		Parameter( LPSTR );
	void		ID( UINT i )       { id = i; }

	void		AddParam( LPSTR, LPSTR );

	bool		Execute();
};


/**************************************************************************
 *  MultiMenuExtension
 **************************************************************************
 *  Variante der TriasExtension mit dynamisch veränderlichen Menüs.
 *  Lädt die aktuelle Menüdefinition beim Laden der Erweiterung aus einer
 *  INI-Datei.
 **************************************************************************/
class MultiMenuExtension : virtual public TriasExtension
{
private:
	MenuElement*	pMenuListe[MAX_MENU_COUNT];
	LPSTR			lpIniFileName;
	char			modulename[9];
	FUNCTIONTABLE	pFuncTab;
	bool			bmainmenu;
	bool			bormenu;
	short			iMenuEntrCnt;

	LPSTR			IniFile() { return lpIniFileName; }
	LPSTR			ModuleName() const { return (char *)modulename; }
	bool			MainMenuExist() { return bmainmenu; }
	bool			ORMenuExist() { return bormenu; }

	void			ModuleName( LPSTR );
	void			MainMenuExist( bool f ) { bmainmenu = f; }
	void			ORMenuExist( bool f ) { bormenu = f; }

	HMENU			LiesMenu( HMENU, LPSTR, LPSTR, LPSTR );
	UINT			LiesMenuPunkt( LPSTR, LPSTR, LPSTR, LPSTR );
	bool			NeuerPunkt( HMENU, LPSTR, LPSTR, LPSTR );

protected:
//  Sucht im IniFile() nach einer Definition der Menues dieser Er-
//  weiterung. Wird automatisch im Konstruktor der Klasse aufgerufen.
//  Kann nach einer Modifikation der INI-Datei oder dem Festlegen einer
//  neuen INI-Datei aufgerufen werden, um zur Laufzeit ein verändertes
//  Menue zu erzeugen.
//  Der Aufruf ist ohne Wirkung, wenn die INI-Datei keine Menüdefinition
//  enthält. (Die Namen der Menüs werden nur beim ersten Aufruf im Kon-
//  struktor beeinflußt.)
	bool			ConfigMenu( void );
//  Dient zum Festlegen einer neuen INI-Datei (z.B. Projekt-INI nach
//  öffnen eines neuen Projektes.
//  Parameter:	1. Dateiname (auch mit Pfad, Endung beliebig)
//            	2. true -> Pfadangabe wird aus dem Dateinamen entfernt
//  Die Endung des übergebenen Dateinamens wird in jedem Fall in .INI
//  geändert.
	void			IniFile( LPSTR datei, bool ohne_pfad );
//  Ändert den in der Funktionstabelle festgelegten Parameter.
//  Damit können die Parameter der Menüfunktionen zur Laufzeit gesetzt
//  werden.
//  Parameter:	1. Identifikator der Menüfunktion in der Funktionstabelle.
//            	2. neuer Parameter
//  Rückgabe:	alter Wert (ggf. zum Freigeben des Speicherplatzes)
	LPSTR			SetMenuParameter( LPSTR, LPSTR );

// Überladene Funktionen
	bool			MenuCommand( WPARAM, HWND = 0 );

public:
					MultiMenuExtension( UINT iMenuID = 0, UINT iORMenuID = 0,
						LPSTR lpIniFile = NULL, FUNCTIONTABLE = NULL );
					~MultiMenuExtension();
};


#endif 	// _MULTMENU_HXX
