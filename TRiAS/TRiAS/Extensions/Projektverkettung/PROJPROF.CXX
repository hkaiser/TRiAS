// Routinen, die aus einer INI-Datei die gewuenschten Info's rausholen
// File: PROJPROF.CXX


#include "tprojp.hxx"
#include "tproject.h"
#include "about.h"

#include "defproj.h"  
#include "menukey.hxx"
#include "txtedit.hxx"
#include "teprodef.hxx"
#include "projprof.hxx"
#include "tproject.hxx"		// Klasse für diese Erweiterung

#include <ospace/file/path.h>

// Konstruktor ----------------------------------------------------------------
ProjectProFile :: ProjectProFile (const char *pProject, ResourceFile *pResTarget, PROJTree * pPROJ, short iLevel) 
{
	_pFullName = NULL;		// für alle Fälle
	_pFileName = NULL;
	_pProfProj = NULL;
	_pTPRJ = NULL;
	_pPROJ = pPROJ;
	_pResTarget = pResTarget;

	_pDrive  = NULL;
	_pPath = NULL;
	_pDBName = NULL;
	_pExt = NULL;
	_pKey = NULL;

	_pNewPath = NULL;
	_pOldPath = NULL;
	_pOldProject = NULL;

	if ( _pPROJ == NULL )
		return;
	if (pProject == NULL )
		return;
	_pProject = new char [_MAX_PATH];
	if ( _pProject == NULL )
		return;

	strcpy ( _pProject, pProject);
	strupr ( _pProject);
	_iLevel = iLevel;

char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_DIR];
char *pDBName = new char [_MAX_FNAME];

	if ( pDrive == NULL || pPath == NULL || pDBName == NULL ) {
		DELETE_OBJ ( pDrive);
		DELETE_OBJ ( pPath);
		DELETE_OBJ ( pDBName);
		return;
	}

// Dateinamen der ProfileDatei neu generieren
	_splitpath (_pProject, pDrive, pPath, pDBName, NULL);
	
	_pFullName = new char [_MAX_PATH];
	if ( _pFullName == NULL) 
		return;
	if (_pFullName != NULL) {

	// vollen ProFileNamen zusammenbauen  
		char *pExt = new char [ _MAX_EXT];
		if ( pExt == NULL ) {
			DELETE_OBJ (pDrive);
			DELETE_OBJ (pPath);
			DELETE_OBJ (pDBName);
			return;
		}
		*pExt = '\0';
		strcat ( pExt,ResString (ResID (IDS_PROFILEEXT, _pResTarget), 5));
		_makepath (_pFullName, pDrive, pPath, pDBName, pExt);

	// Trick - Temp-Ini
	// KK010522

		/*
		char * pTempIni = ((CProjectExtension *)g_pTE)->GetTempIni();
		if (!pTempIni || *pTempIni == '\0')
			((CProjectExtension *)g_pTE)->SetTempIniFile(_pFullName);
		*/


		char * pTempIni = ((CProjectExtension *)g_pTE)->GetTempIni();

		if (pTempIni && *pTempIni != '\0') {
			if (((CProjectExtension *)g_pTE)->DuplicatTempIni(_pFullName))			// Nur für Temp.INI des aktuellen Vater-Projektes
				strcpy (_pFullName,((CProjectExtension *)g_pTE)->GetTempIni());
		}

		*pExt = '\0';
		strcat ( pExt,ResString (ResID (IDS_DATABASEEXT, _pResTarget), 5));

		{
		CTable t( *_pPROJ);
		if ( t.Find ( _pProject )) {
			PROJLock l(t);
			if ( !l->pTPRJ()) {
				_pTPRJ = new TPRJTree;	
				l->StoreTProjects(_pTPRJ);
			} else {
				l->DeleteTProjects();
				_pTPRJ = new TPRJTree;	
				l->StoreTProjects(_pTPRJ);
			}
		} else {
			_pTPRJ = new TPRJTree;	
			DBPROJECT DB;
			SetZero ( &DB);
			DB.pDBName = pDBName;
			DB.pDrive = pDrive;
			pDBName = pDBName;
			DB.pUserName = pDBName;
			DB.pPath = pPath;
			DB.pExt = pExt;		
			DB.pTPRJ = _pTPRJ;
			DB.iLevel = _iLevel;

			PROJCreator PROJCr ( *_pPROJ );
			ContCreate ( PROJCr, PROJ ) ( _pProject, &DB );
		}
		}

		DELETE_OBJ ( pExt);
		
	}

// Speicher freigeben
	DELETE_OBJ (pDrive);
	DELETE_OBJ (pPath);
	DELETE_OBJ (pDBName);
}

// Destruktor
ProjectProFile :: ~ProjectProFile (void) 
{
	DELETE_OBJ ( _pProject);
	DELETE_OBJ ( _pFullName);
	DELETE_OBJ ( _pFileName);
	DELETE_OBJ ( _pProfProj);

	DELETE_OBJ ( _pDrive );
	DELETE_OBJ ( _pPath );
	DELETE_OBJ ( _pDBName );
	DELETE_OBJ ( _pExt );
	DELETE_OBJ ( _pKey);
	DELETE_OBJ ( _pNewPath);
	DELETE_OBJ ( _pOldPath);
	DELETE_OBJ ( _pOldProject);

}
//
bool isCharTest ( char *p)
{

	if ( !p)
		return false;

//      Test auf "Sonderzeichen"                                              
	switch (*p)
	{                                               
		case 'ä':
		case 'Ä':                               
		case 'ö':
		case 'Ö':
		case 'ü':
		case 'Ü':
		case 'ß':
			return true;
		break; 
		default:                                
			return false;
		break;                                  
	}

	
	return false;
}

//Notfallfunktion : soll dafür sorgen, dass nur einmal OemToAnsi ausgeführt wird
bool OemToCharTest ( char *pKey, char *pOem )
{

	
	if ( !pKey || !pOem)
		return false;

	char * pMy = new char [_MAX_PATH];

	if ( pMy) {
		OemToChar ( pKey,pMy);
		char *p = pMy;
		char *s = pKey;

		while ( *p != '\0') {

			if ( *p != *s ) {

		//      Test auf "Sonderzeichen"                                              
				switch (*p)
				{                                               
					case 'ä':
					case 'Ä':                               
					case 'ö':
					case 'Ö':
					case 'ü':
					case 'Ü':
					case 'ß':
						DELETE_OBJ(pMy);
						OemToChar(pKey,pOem);
						return true;
					break; 
					default:                                
						if (isCharTest (s)) {
							DELETE_OBJ(pMy);
							strcpy ( pOem,pKey);
							return false;
						}
					break;                                  
				}

			}

			p++;
			s++;
		}

		DELETE_OBJ(pMy);
		strcpy ( pOem,pKey);

	}
	return false;
}

// Liefert den vollen Pfad einer Datenbank anhand eines Schlüssels ------------
char *ProjectProFile :: GetProjectName (char *pKey)
{

ResString Projects (ResID (IDS_PROJECTS, _pResTarget), 13);

	DELETE_OBJ ( _pDrive );
	DELETE_OBJ ( _pPath );
	DELETE_OBJ ( _pDBName );
	DELETE_OBJ ( _pExt );
	DELETE_OBJ ( _pKey);
	DELETE_OBJ ( _pProfProj);

	if (_pFullName == NULL)
		return NULL;

	if ( pKey == NULL) 
		return NULL;
	
	if ( _pProfProj == NULL ) 
		_pProfProj = new char [_MAX_PATH];
	if ( _pProfProj == NULL) 
		return NULL;

	char *pOem = new char [_MAX_PATH];
	if ( pOem == NULL) {
 		DELETE_OBJ (_pProfProj);
		return NULL;
	}
	
// Nur zum Ersetzen falscher Pfade : Zuordnung OldProject zu NewPath/OldPath
	if ( _pOldProject == NULL ) 
		_pOldProject = new char [_MAX_PATH];


	GetPrivateProfileString (Projects, pKey, "", _pProfProj, _MAX_PATH, _pFullName);

	bool iFlag = false;


	iFlag = OemToCharTest (pKey, pOem );

	char inChar = *pOem;

	if ( islower(inChar) ) 
		iFlag = true;

	if ( iFlag )	{
		int ii = WriteIniFile (Projects, pKey, NULL,_pFullName);		// Satz raus aus ini
		// KK010515
//		int ii = WritePrivateProfileString (Projects, pKey, NULL,_pFullName);
		inChar = toupper(inChar);
//		*pKey = inChar;
		*pOem = inChar;
//		ii = WritePrivateProfileString (Projects, pKey, _pProfProj,_pFullName);
//		ii = WriteIniFile (Projects, pKey, _pProfProj,_pFullName);
		ii = WriteIniFile (Projects, pOem, _pProfProj,_pFullName);
	}

	strcpy (pKey,pOem);


//	Pfad da ????
	_pDrive = new char [_MAX_DRIVE];
	_pPath = new char [_MAX_DIR];
	_pDBName = new char [_MAX_FNAME];
	_pExt = new char [_MAX_EXT];
	_pKey = new char [_MAX_PATH];
	


	if ( _pKey == NULL ||_pDrive == NULL || _pPath == NULL || _pDBName == NULL || _pExt == NULL) {
		DELETE_OBJ( _pKey);
		DELETE_OBJ ( _pDrive);
		DELETE_OBJ ( _pPath);
		DELETE_OBJ ( _pDBName);
		DELETE_OBJ ( _pExt);
		DELETE_OBJ ( pOem);
		return NULL;
	}

// Dateinamen neu generieren

	_splitpath (_pProfProj, _pDrive, _pPath, _pDBName, _pExt);
	if (_pOldProject ) 
		_makepath (_pOldProject, _pDrive, _pPath, NULL, NULL);		//OldPath


	// Fragen, ob Pfad schon bekannt ??

	if ( _pNewPath && *_pNewPath != '\0') {	//Alle Restlichen korrigieren
		if (_pOldPath && _pOldProject) {
			if ( strcmp(_pOldPath,_pOldProject) == 0) {	// Es ist der korrigierte Pfad
				_splitpath (_pNewPath, _pDrive, _pPath, NULL, NULL);
				_makepath (_pProfProj, _pDrive, _pPath, _pDBName, _pExt);	//Pfad tauschen
			} 
		}
	}


//----------Vergleich Vater <-> Tochter ----------------------------------
	strupr ( _pProfProj);
	if ( strcmp ( _pProfProj,_pProject ) == 0 ) {	// Vater = Tochter
		DELETE_OBJ ( _pDrive );
		DELETE_OBJ ( _pPath );
		DELETE_OBJ ( _pDBName );
		DELETE_OBJ ( _pExt );
		DELETE_OBJ ( _pKey);
		DELETE_OBJ ( pOem);
		DELETE_OBJ ( _pProfProj );
		return NULL;
	}

//------------------------------------------------------------------------

// Ex. DB wirklich ???

	struct _stat ST;
	if ( _stat ( _pProfProj, &ST) != 0 ) {

// Pfade verändert ? - Testen und wenn möglich korrigieren !!!

		if ( !PathCorrection()) {
			


// Hier MasterPfad ändern- in TPRJ sammeln ( pDrive,pPath,pDBName+pOem)

			if (!((CProjectExtension *)g_pTE)->GetTPUndef()) {


				if ( !ActualProjectFile(_pProject,_pProfProj,pOem,pKey)) {
					DELETE_OBJ ( _pDrive );
					DELETE_OBJ ( _pPath );
					DELETE_OBJ ( _pDBName );
					DELETE_OBJ ( _pExt );
					DELETE_OBJ ( _pKey);
					DELETE_OBJ ( pOem);
					DELETE_OBJ ( _pProfProj );
			
					return NULL;
				} else {
					_splitpath (_pProfProj, _pDrive, _pPath, _pDBName, _pExt);

					ResString Projects (ResID (IDS_PROJECTS, _pResTarget), 13);

					int ii = WriteIniFile (Projects, pOem, NULL,_pFullName);
					ii = WriteIniFile (Projects, pOem, _pProfProj,_pFullName);

			// TP-Adresse geändert - alle anderen analog versuchen !!
					DELETE_OBJ(_pNewPath);
        	
					int flag = MessageBox (__hWndM,
						ResString (ResID(IDS_TPCREATEOTHER,_pResTarget),100),
						ResString (ResID(IDT_TPCAPTION,_pResTarget),50),
						MB_YESNOCANCEL|MB_ICONQUESTION);


					if ( flag == IDYES ) {
						if (!_pNewPath) {
							_pNewPath = new char [_MAX_PATH];
							_makepath (_pNewPath, _pDrive, _pPath, NULL, NULL);
							if ( _pOldPath == NULL ) 
								_pOldPath = new char [_MAX_PATH];
							if (_pOldPath && _pOldProject) 
								strcpy(_pOldPath,_pOldProject);	// Es ist der korrigierte Pfad
						}

					}


				}

			} else {
				DELETE_OBJ ( _pDrive );
				DELETE_OBJ ( _pPath );
				DELETE_OBJ ( _pDBName );
				DELETE_OBJ ( _pExt );
				DELETE_OBJ ( _pKey);
				DELETE_OBJ ( pOem);
				DELETE_OBJ ( _pProfProj );
			
				return NULL;
			}

		} else {
			_splitpath (_pProfProj, _pDrive, _pPath, _pDBName, _pExt);
			ResString Projects (ResID (IDS_PROJECTS, _pResTarget), 13);

			int ii = WriteIniFile (Projects, pOem, NULL,_pFullName);
			ii = WriteIniFile (Projects, pOem, _pProfProj,_pFullName);
		}


	} else {

		if ( _pNewPath && *_pNewPath != '\0') {

			int ii = WriteIniFile (Projects, pKey, NULL,_pFullName);
		// Erstellen neu
			ii = WriteIniFile (Projects, pKey, _pProfProj,_pFullName);
		}
	}

	strcpy ( _pKey, pOem);
	DELETE_OBJ ( pOem);
	return _pProfProj;
}
//---------------------------------------------------------------------------------
 // Hier erst versuchen, die Pfade aus dem Eintrag [DefaultProject]
 // (Vergleich alter mit neuer project.ini) zu erzeugen !!!
// KK 010601

bool ProjectProFile :: PathCorrection(void) 
{

	os_path path,oldpath,TPPath;

	path = _pProject;		// aktuelles Projekt

	TPPath = _pProfProj;		// Teilproject

	char *pLocDir = new char [_MAX_PATH];
	if ( !pLocDir)
		return false;

	ResString DefaultProjects (ResID (IDS_DEFAULTPROJECTS,&g_pTE->RF()), 13);
	ResString DefaultProject (ResID (IDS_DEFAULTPROJECT,&g_pTE->RF()), 13);

	GetPrivateProfileString (DefaultProjects,DefaultProject,"",pLocDir, _MAX_PATH,_pFullName);
	oldpath = pLocDir;		// Altes Project


	string LS = TPPath.tail();
	string LF = TPPath.filename();

// KK020304
	path.cd(LS);
	path.filename(LF);


	if ( !FileExist((const char *) path )) 
			return false; 

	strcpy(_pProfProj, (const char *)path);

	DELETE_OBJ(pLocDir);

	return true;

}
//---------------------Neuzuordnen DB-Schlüssel -----------------------------------
bool ProjectProFile :: ActualProjectFile ( char *pProject,char *pProfProj, char *pOem, char *pKey)
{

	char *pList = new char [ _MAX_PATH];
       if ( !pList )
        	return false;

	if ( !pKey || *pKey == '\0' || !pProject || *pProject == '\0' || !pProfProj || *pProfProj == '\0' || !pOem || *pOem == '\0')
		return false;

	ResString TPLink (ResID (IDS_TPLINK, _pResTarget), 50);
	ResString TPError (ResID (IDS_TPERROR, _pResTarget), 50);
	ResString TPPfad (ResID (IDS_TPPFAD, _pResTarget), 50);
	ResString TPWork (ResID (IDS_TPWORK, _pResTarget), 50);

	*pList = '\0';
//	strcat ( pList,"Verweis zum Teilprojekt *");
	strcat ( pList,TPLink.Addr());
	strcat ( pList,pOem);
//	strcat (pList,"* fehlerhaft");
	strcat (pList,TPError.Addr());
	strcat ( pList,"\n");
	strcat ( pList,"[ ");
//	strcat ( pList , "Pfad : ");
	strcat ( pList , TPPfad.Addr());
	strcat ( pList,pProfProj);
	strcat ( pList," ]");
	strcat ( pList,"\n");
//	strcat ( pList,"Teilprojekt-Verweis bearbeiten ?");
	strcat ( pList,TPWork.Addr());


   int  len;
   int flag;
 
  len = strlen( pProject );

	ResString Projects (ResID (IDS_PROJECTS, _pResTarget), 13);


 /*
	if (100 > len ) {
   
		flag = MessageBox (__hWndM,
			pList,
			ResString (ResID(IDT_TPCAPTION,_pResTarget),50),
//			pProject,
//		MB_YESNO|MB_ICONEXCLAMATION);
			MB_YESNOCANCEL|MB_ICONQUESTION);
   } else {
		flag = MessageBox (__hWndM,
			pList,
			ResString (ResID(IDT_TPCAPTION,_pResTarget),50),
			MB_YESNOCANCEL|MB_ICONQUESTION);
   }
*/

	flag = MessageBox (__hWndM,
		pList,
		ResString (ResID(IDT_TPCAPTION,_pResTarget),50),
		MB_YESNOCANCEL|MB_ICONQUESTION);


	if ( flag == IDCANCEL ) {
		DELETE_OBJ ( pList);
		return false;
	}

	if ( flag == IDNO ) {
// KK 010515
		int ii = WriteIniFile (Projects, pKey, NULL,_pFullName);
		DELETE_OBJ ( pList);
		return false;
	}
	DELETE_OBJ ( pList);

	{


	TProjectMod TPD ( g_pTE->MVWind(),TPROJECTKORREKTUR, _pResTarget, pProject,pProfProj,pOem);
	TPD.Show();

	if ( TPD.Result() == 1 ) {
		strcpy ( pProfProj,TPD.TProjectNewPfad());
		strcpy ( _pKey,TPD.TProjectKey());
// KK 010515
//		int ii = WritePrivateProfileString (Projects, pKey, NULL,_pFullName);
		// Löschen alt
		int ii = WriteIniFile (Projects, pKey, NULL,_pFullName);
//		ii = WritePrivateProfileString (Projects, pKey, pProfProj,_pFullName);
		// Erstellen neu
		ii = WriteIniFile (Projects, _pKey, pProfProj,_pFullName);
		return true;
	}

	if ( TPD.Result() == -1 ) { 	//	Delete
//		int ii = WritePrivateProfileString (Projects, pKey, NULL,_pFullName);
		int ii = WriteIniFile (Projects, pKey, NULL,_pFullName);
		return false;
	}
	}
	return false;
}

// -----------------Liefert alle Datenbankschlüssel ------------
int ProjectProFile :: GetProjectFile ( void )
{
	if (_pFullName == NULL) 
		return 0;

ResString Projects (ResID (IDS_PROJECTS, _pResTarget), 13);
		
	DELETE_OBJ (_pFileName);
	_iNumMenuPoints = 0;
	short MaxString = MaxExtension*MaxKey;
	_pFileName = new char [MaxString];

	if ( _pFileName == NULL ) {
		return 0;	
	}	

//	Füllen von _pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", _pFileName, MaxString, _pFullName);

	if (*_pFileName == '\0') {	// nichts gefunden
		{
		CTable d ( *_pPROJ);

		if ( d.Find ( _pProject )) {
			PROJLock k(d);
			k->DeleteTProjects( );
			_pTPRJ = NULL;
		}
		}
		DELETE_OBJ (_pFileName);

		return 0;
	}

	_iNumMenuPoints = MaxExtension;

// Zusammenstellen der MenuPunkte

//	Achtung - neu durchzählen !!!

	char *aptr = &_pFileName[0];
    int j = 0;

	{
	CTable t ( *_pTPRJ);
	bool bTPUndef = false;
	while ( *aptr != NULL ) {
		char *ptr = strrchr (aptr, '\0');
		if ( ptr != NULL ) {
			DBPROJECT DB;
			SetZero ( &DB);
			char *pFile = GetProjectName ( aptr );
			if ( pFile != NULL ) {   // DB auch da ???
			   if ( !t.Find ( _pKey)) {
				DB.pKey = _pKey;
				DB.pDBName = _pDBName;
				DB.pDrive = _pDrive;
				DB.pUserName = _pDBName;
				DB.pPath = _pPath;
				DB.pExt = _pExt;
				DB.pOwner = _pProject;
				DB.iLevel = _iLevel + 1;

				TPRJCreator TPRJCr ( *_pTPRJ );
				ContCreate ( TPRJCr, TPRJ ) ( _pKey, &DB );
        		        j++;
			   } else {
				TPRJLock l(t);
				l->StoreNewTPAddress ( _pDrive,_pPath,_pDBName,_pExt);
				j++;
			   }
			} else
				bTPUndef = true;

			DELETE_OBJ ( _pDrive );
			DELETE_OBJ ( _pPath );
			DELETE_OBJ ( _pDBName );
			DELETE_OBJ ( _pExt );
			aptr = ptr +1;
		}
	}

// KK 010528
	if ( bTPUndef )
		((CProjectExtension *)g_pTE)->SetTPUndef();

	}

	_iNumMenuPoints = j;
	
	if ( j == 0 ) {		// Keine TP
		CTable d ( *_pPROJ);

		if ( d.Find ( _pProject )) {
			PROJLock k(d);
			k->DeleteTProjects( );
			_pTPRJ = NULL;
		}
	}
	return _iNumMenuPoints;

}
