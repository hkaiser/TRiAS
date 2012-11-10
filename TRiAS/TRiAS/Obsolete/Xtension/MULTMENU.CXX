/**************************************************************************
 *  Projekt Multi-Menn-Erweiterung
 **************************************************************************
 *  Datei:	       multmenu.cxx
 *  Stand vom:	       05.05.94
 *                     (c) 1994 uve GmbH Potsdam
 **************************************************************************
 * Basisklasse TRIAS-Erweiterung mit dynamisch ver_nderbarem Menn
 *
 * Variante:           Menndefinition in INI-Datei
 * Entwicklung:        05.05.94 Beginn der Kodierung
 **************************************************************************/


#include "xtensnp.hxx"

#include "multmenu.hxx"

FUNC_TABENTRY FunctionTable[] = {
	{ "ABOUT",	AboutFunc, 	"" },
	{ "FUNCLIST",	FunctionList,	NULL },
	{ "",		NULL,		NULL }
};	/* FunctionTable */


/**************************************************************************
 *  Pflichtfunktionen fnr jede TRIAS-Erweiterung
 **************************************************************************/

/*  NewExtension  *********************************************************
 *                Typrichtige Erzeugung des (von TriasExtension abgeleite-
 *                ten) Extension-Objektes.
 **************************************************************************
TriasExtension *NewExtension( TRIAS_LOAD * )
{
	return new MultiMenuExtension( EXTENSIONMENU, EXTENSIONOBJRECHMENU,
			NULL, &FunctionTable[0] );
}
*/

/*  DeleteExtension  ******************************************************
 *                   Typrichtige Freigabge des oben erzeugten Extension-
 *                   Objektes (nur aus Symmetriegrnnden, ein virtueller
 *  Destruktor wnrde es auch tun).
 **************************************************************************
void DeleteExtension( TriasExtension *pTE )
{
	delete (MultiMenuExtension *)pTE;
}
*/


/*  Konstruktor  **********************************************************/
MultiMenuExtension :: MultiMenuExtension( UINT iMenuID, UINT iORMenuID,
							LPSTR lpIniFile, FUNCTIONTABLE pFTab )
 : TriasExtension( iMenuID, iORMenuID )
{
	LPSTR lpText = new char[MAX_PATH_LEN];

	GetModuleFileName( hInstance, lpText, MAX_PATH_LEN );
	lpIniFileName = NULL;
	if ( lpIniFile ) IniFile( lpIniFile, false );
	if (!IniFile())  IniFile( lpText, true );
	ModuleName( lpText );
	if ( lpIniFile && lstrlen( lpIniFile ))		// #HK940603 added lpIniFile != NULL
	{	lpIniFileName = new char[lstrlen(lpIniFile)+1];
		strcpy( lpIniFileName, lpIniFile );
	}
	pFuncTab = pFTab;
	for ( short i = 0; i < MAX_MENU_COUNT; pMenuListe[i++] = NULL )
		;
	MainMenuExist( iMenuID );
	ORMenuExist( iORMenuID );
	iMenuEntrCnt = 0;
	
	ConfigMenu();

	DELETE( lpText );
}


/*  Destruktor  ***********************************************************/
MultiMenuExtension :: ~MultiMenuExtension()
{
	for ( short i = 0; i < MAX_MENU_COUNT; i++ )
		DELETE( pMenuListe[i] );
	DELETE( lpIniFileName );
}


/*  IniFile  **************************************************************/
void MultiMenuExtension :: IniFile( LPSTR file, bool ohne_pfad )
{
	LPSTR x;

	DELETE( lpIniFileName );
	if ( !file ) return;
	if ( !lstrlen( file )) return;
	if ( ohne_pfad )
	{
		x = file + lstrlen( file ) - 1;
		while (( *x != '\\' ) && ( x >= file )) x--;
		lpIniFileName = new char[lstrlen( x )+4];
		strcpy( lpIniFileName, ++x );
		x = lpIniFileName + lstrlen( lpIniFileName );
		if ( *(x-1) != '.' ) x--;
		if ( *(x-1) != '.' ) x--;
		if ( *(x-1) != '.' ) x--;
		if ( *(x-1) != '.' ) { x += 4; x[-1] = '.'; }
		x[0] = 'I'; x[1] = 'N'; x[2] = 'I';
	}
	else
	{
		lpIniFileName = new char[lstrlen(file) + 1 ];
		strcpy( lpIniFileName, file );
	}
}


/*  ModuleName  ***********************************************************/
void MultiMenuExtension :: ModuleName( LPSTR file )
{
	LPSTR x, i;
	short n;
	
	if (!file) return;
	if (!lstrlen( file )) return;
	i = x = file + lstrlen( file ) - 1;
	while (( *i != '\\' ) && ( i >= file )) i--;
	x = ++i;
	n = 0;
	while (( *i != '.' ) && ( *i != '\0' )) { i++; n++; }
	strncpy( modulename, x, n );
	modulename[n] = '\0';
}


/*  ConfigMenu  ***********************************************************/
bool MultiMenuExtension :: ConfigMenu( void )
{
	if ( !MainMenuExist() && !ORMenuExist()) return true;
	if ( !IniFile()) return true;
	if ( !lstrlen( IniFile())) return true;
	
	LPSTR Text = new char[MAX_PATH_LEN];
	LPSTR lpSektion = new char[MAX_PATH_LEN];

	wsprintf( lpSektion, "%s.MENU", ModuleName());

	if ( MainMenuExist())
	{
		GetPrivateProfileString( lpSektion, "KOPF", "",
				Text, MAX_PATH_LEN, IniFile());

		if ( lstrlen( Text ))
		{
			EmptyMenu();
			LiesMenu( MenuHandle(), lpSektion, Text, MenuEntry());
	}	}

	if ( ORMenuExist())
	{
		GetPrivateProfileString( lpSektion, "OR", "",
				Text, MAX_PATH_LEN, IniFile());

		if ( lstrlen( Text ))
		{
			EmptyORMenu();
			LiesMenu( ORMenuHandle(), lpSektion, Text, ORMenuEntry());
	}	}

	DELETE ( lpSektion );
	DELETE ( Text );
	return true;
}


/*  LiesMenu  *************************************************************/
HMENU MultiMenuExtension :: LiesMenu( HMENU hOldMenu, LPSTR lpSek,
				LPSTR lpName, LPSTR lpZiel )
{
	HMENU hMenu = hOldMenu;
	LPSTR lpSektion = new char[MAX_PATH_LEN];
	LPSTR Text = new char[MAX_PATH_LEN];
	LPSTR Name = new char[MAX_PATH_LEN];
	LPSTR Numm = new char[10];
	LPSTR Param = new char[BUFFER_LEN];
	short i;

	wsprintf( lpSektion, "%s.%s", lpSek, lpName );
	GetPrivateProfileString( lpSektion, "NAME", "",
			Text, MAX_PATH_LEN, IniFile());

	if ( lstrlen( Text ) > DEX_MENUNAMELEN ) Text[DEX_MENUNAMELEN] = '\0';
	if ( lstrlen( Text )) strcpy( lpZiel, Text );
	else
	{
		if ( lstrlen( lpName ) > DEX_MENUNAMELEN )
		{	strncpy( lpZiel, lpName, DEX_MENUNAMELEN );
			lpZiel[DEX_MENUNAMELEN] = '\0';
		}
		else
			strcpy( lpZiel, lpName );
	}

	GetPrivateProfileString( lpSektion, "FuncID", "",
			Text, MAX_PATH_LEN, IniFile());
	if ( lstrlen( Text )) 
		goto ErrLabel;	//return hMenu;

	if ( !hMenu ) hMenu = CreatePopupMenu();
	GetPrivateProfileString( lpSektion, "1", "", Text, MAX_PATH_LEN,
				IniFile());
	i = 2;
	while ( lstrlen( Text ))
	{
		if ( *Text == '-' )
			AppendMenu( hMenu, MF_SEPARATOR, NULL, NULL );
		else
		{
			HMENU hSubMenu = LiesMenu( (HMENU)NULL, lpSektion, Text, Name );
			UINT  iCode;
			if ( hSubMenu )
				AppendMenu( hMenu, MF_ENABLED | MF_POPUP | MF_STRING,
					   (UINT)hSubMenu, Name );
			else
			{
				iCode = LiesMenuPunkt( lpSektion, Text, Name, Param );
				if ( iCode )
					AppendMenu( hMenu, MF_ENABLED | MF_STRING,
							iCode, Name );
				else
					NeuerPunkt( hMenu, Name, Text, Param );
		}	}

		wsprintf( Numm, "%d", i++ );
		GetPrivateProfileString( lpSektion, Numm, "", Text,
				MAX_PATH_LEN, IniFile());
	}

ErrLabel:
	DELETE( Param );
	DELETE( Numm );
	DELETE( Name );
	DELETE( Text );
	DELETE( lpSektion );
	return hMenu;
}


/*  LiesMenuPunkt  ********************************************************/
UINT MultiMenuExtension :: LiesMenuPunkt( LPSTR lpSek, LPSTR lpText,
				LPSTR lpName, LPSTR lpPara )
{
	UINT	iCode = 0;
	LPSTR	lpSektion = new char[MAX_PATH_LEN];
	LPSTR	Text = new char[MAX_PATH_LEN];
	LPSTR	lpFelder = new char[BUFFER_LEN];
	LPSTR	lpFeld;

	wsprintf( lpSektion, "%s.%s", lpSek, lpText );
	GetPrivateProfileString( lpSektion, "FuncID", "", Text,
				MAX_PATH_LEN, IniFile());

	lpPara[0] = '\0';
	if ( !lstrlen( Text ))
	{
		lpName[0] = '\0';
		goto ErrLabel;		// return iCode;
	}

	if ( !pFuncTab )
	{
		iCode = atoi( Text );
		if (( iCode < 1 ) || ( iCode > 99 )) iCode = 0;
		if ( !iCode ) lpName[0] = '\0';
		goto ErrLabel;		// return iCode;
	}

	GetPrivateProfileString( lpSektion, NULL, "",
		lpFelder, BUFFER_LEN, IniFile());

	if ( lstrlen( lpFelder ))
	{
		lpFeld = lpFelder;
		while( *lpFeld )
		{
			GetPrivateProfileString( lpSektion, lpFeld, "",
				Text, MAX_PATH_LEN, IniFile());

			if ( lstrlen( Text ))
			{
				if ( strcmp( lpFeld, "Name" ) == 0 )
				{
					strcpy( lpName, Text );
					*Text = '\0';
				}

				if ( strcmp( lpFeld, "FuncID" ) == 0 )
				{
					strcpy( lpText, Text );
					*Text = '\0';
				}

				if ( lstrlen( Text ))
					wsprintf( lpPara + lstrlen( lpPara ),
						"%s=%s\n", lpFeld, Text );
			}
			lpFeld += lstrlen( lpFeld ) + 1;
		}
	}

	lpFeld = lpPara;
	if ( lstrlen( lpPara ))
		while ( *lpFeld )
		{
			if ( *lpFeld == '\n' ) *lpFeld = '\0';
			lpFeld++;
		}

ErrLabel:
	DELETE( lpFelder );
	DELETE( Text );
	DELETE( lpSektion );
	return iCode;
}	/* LiesMenuPunkt */


/*  NeuerPunkt  ***********************************************************/
bool MultiMenuExtension :: NeuerPunkt( HMENU hMenu, LPSTR lpName,
			LPSTR lpText, LPSTR lpParam )
{
	MenuElement* pME;
	bool found = false;
	if ( !lpName ) return false;
	if ( !lstrlen( lpName )) return false;
	if ( !pFuncTab ) return false;

	short i = 0;
	FUNC_TABENTRY *pFTE = &pFuncTab[i++];
	while ( pFTE && !found )
	{
		if ( lstrlen( pFTE -> lpFuncID ))
		{
			if ( !strcmp( pFTE -> lpFuncID, lpText ))
				found = true;
			else
				pFTE = &pFuncTab[i++];
		}
		else pFTE = NULL;
	}

	if ( !found ) return false;

	pME = new MenuElement();
	pME -> Bezeichnung( lpName );
	pME -> Code( pFTE );
	pME -> Parameter( lpParam );
	pMenuListe[iMenuEntrCnt++] = pME;
	AppendMenu( hMenu, MF_ENABLED | MF_STRING,
			iMenuEntrCnt, lpName );
	pME -> ID( iMenuEntrCnt );

	return true;
}	/* NeuerPunkt */


LPSTR MultiMenuExtension :: SetMenuParameter( LPSTR lpID, LPSTR lpPara )
{
	LPSTR txt = NULL;
	bool  found = false;
	if ( !lpID ) return NULL;
	if ( !lstrlen( lpID )) return NULL;
	if ( !pFuncTab ) return NULL;

	short i = 0;
	FUNC_TABENTRY *pFTE = &pFuncTab[i++];
	while ( pFTE && !found )
	{
		if ( lstrlen( pFTE -> lpFuncID ))
		{
			if ( !strcmp( pFTE -> lpFuncID, lpID ))
				found = true;
			else
				pFTE = &pFuncTab[i++];

			if ( found )
			{
				txt = pFTE -> lParam;
				pFTE -> lParam = lpPara;
		}	}
		else pFTE = NULL;
	}

	return txt;
}


/*  MenuCommand  **********************************************************/
bool MultiMenuExtension :: MenuCommand( WPARAM wParam, HWND /* hWnd */ )
{
	short		i;
	MenuElement*	pME;
	bool		result = false;

	for ( i = 0; i < iMenuEntrCnt; i++ )
	{
		pME = pMenuListe[i];
		if ( wParam == pME -> ID())
			result = pME -> Execute();
	}

	return result;
}


/**************************************************************************
 *  MenuElement
 **************************************************************************/

/*  Konstruktor  **********************************************************/
MenuElement :: MenuElement( LPSTR b, LPSTR c, LPSTR p )
{
    bez       = b;
    para      = p;
    id        = 0;
}   /* Konstruktor */

/*  Destruktor  ***********************************************************/
MenuElement :: ~MenuElement()
{
    DELETE( bez );
    DELETE( para );
}

/*  Bezeichnung  **********************************************************/
void MenuElement :: Bezeichnung( LPSTR b )
{
    LPSTR txt = NULL;

    if ( b ) if ( lstrlen( b ))
    {
	txt = new char[lstrlen( b ) + 1];
	strcpy( txt, b );
    }

    DELETE( bez );
    bez = txt;
}   /* Bezeichnung */

/*  Code  *****************************************************************/
LPSTR MenuElement :: Code()
{
	LPSTR txt = NULL;

	if ( pTabEntry )
		txt = pTabEntry -> lpFuncID;

	return txt;
}   /* Code */

/*  Parameter  ************************************************************/
void MenuElement :: Parameter( LPSTR p )
{
    LPSTR txt = NULL;

    if ( p ) if ( lstrlen( p ))
    {
	txt = new char[BUFFER_LEN];
	memcpy( txt, p, BUFFER_LEN );
    }

    DELETE( para );
    para = txt;
}   /* Parameter */

/*  AddParam  *************************************************************/
void MenuElement :: AddParam( LPSTR f, LPSTR p )
{
    LPSTR txt;
    short i;

    if ( !f ) return;
    if ( !p ) return;
    if ( !lstrlen( f )) return;

    i = lstrlen( f ) + 5;
    if ( p ) i += lstrlen( p );
    if ( para ) i += lstrlen( para );
    txt = new char[i];
    memset( txt, NULL, i );
    if ( para )
    {	strcpy( txt, para );
	txt[lstrlen( txt )] = '\n';
    }
    strcpy( txt + lstrlen( txt ), f );
    if ( p ) if ( lstrlen( p ))
    {
	txt[lstrlen( txt )] = '=';
	strcpy( txt + lstrlen( txt ), p );
    }

    DELETE( para );
    para = txt;
}


/*  Execute  **************************************************************/
bool MenuElement :: Execute()
{
	LPSTR p1 = para;
	LPSTR p2 = pTabEntry -> lParam;

	return (*pTabEntry -> pMenuFunc)( p1, p2 );
}	/* Execute */


bool AboutFunc( LPSTR, LPSTR )
{
	return true;
}	/* AboutFunc */

bool FunctionList( LPSTR, LPSTR )
{
	return true;
}	/* FunctionList */

