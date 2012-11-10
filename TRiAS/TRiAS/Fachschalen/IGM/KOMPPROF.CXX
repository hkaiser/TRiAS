///////////////////////////////////////////////////////////////////////
// Routinen, die aus einer INI-Datei die gewuenschten Info's rausholen
// File: KOMPPROF.CXX
#include "kompp.hxx"
#include "version.h"
#include "kompaktr.h"

//#include "triasdef.h"  
#include "kompdef.h"  

#include "kompprof.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32

/// --------------------



#pragma warning (disable: 4355)


// Konstruktor ----------------------------------------------------------------
KompaktProFile :: KompaktProFile ( ResourceFile *pResTarget ) 
{

	_pFullName = NULL;		// für alle Fälle
	_pSoftPath = NULL;
	_pDataPath = NULL;
	_isValid = false;
	
	_pFullName = new char [_MAX_PATH];
	if ( _pFullName == NULL) 
		return;
	_pSoftPath = new char [_MAX_PATH];
	if ( _pSoftPath == NULL) 
		return;

	// etvl. ResourceFile merken
	_pResTarget = pResTarget;


	WORD wReturn = GetWindowsDirectory ( (LPSTR) _pFullName, _MAX_PATH );
	if ( wReturn == 0 || wReturn > _MAX_PATH )
		return;

	// vollen ProFileNamen zusammenbauen  
//-------Win\Kompoff
	strcat ( _pFullName,ResString (ResID (IDS_KOMPAKTINI, _pResTarget), 30));

//-------Win\Kompoff.ini
	strcat ( _pFullName,ResString (ResID (IDS_KOMPAKTEXTENSION, _pResTarget), 5));

	//Validation

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return;
	}
	_isValid = true;

	DELETE_OBJ ( pFileName);

	
}

#pragma warning (default: 4355)

// Destruktor
KompaktProFile :: ~KompaktProFile (void) 
{
	DELETE_OBJ ( _pFullName);
	DELETE_OBJ ( _pSoftPath);
	DELETE_OBJ ( _pDataPath);

}
////////////////////////////////////////////////////////////////////
// -----------------Liefert alle Datenbankschlüssel ------------
char *KompaktProFile :: GetPathDaten ( void )
{
	if (_pFullName == NULL) 
		return NULL;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return NULL;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return NULL;
	}
	_isValid = true;

//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		DELETE_OBJ ( pFileName);
		return NULL;
	}

	char *aptr = &pFileName[0];
	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_KOMPAKTDATEN, _pResTarget), 50));

	while ( *aptr != NULL ) {
		char *ptr = strrchr (aptr, '\0');
		if ( ptr != NULL ) {
			if ( strcmp ( pKey,aptr) == 0) {
				*pComm = '\0';
				GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);

				if ( *pComm != '\0') {

					// Existenz des Datenpfades !!!
					if ( !ExistDataPath(pComm) ){

					//	*pComm = '\0';

						WritePrivateProfileString (Projects, pKey, NULL,_pFullName);

						DELETE_OBJ (pKey);
						DELETE_OBJ ( pFileName);
						DELETE_OBJ ( pComm);
						return NULL;
	
					}


					DELETE_OBJ (pKey);
					DELETE_OBJ ( pFileName);

					if (!_pDataPath) 
						_pDataPath = new char [_MAX_PATH];

					if ( _pDataPath) 
						strcpy(_pDataPath,pComm);

					if ( *(pComm+strlen(pComm)-1) == '\\') {
						strcat ( pComm,ResString (ResID (IDS_KOMPAKTPROTOKOLL, _pResTarget), 50));
					} else {
						strcat ( pComm,"\\");
						strcat ( pComm,ResString (ResID (IDS_KOMPAKTPROTOKOLL, _pResTarget), 50));
					}
					return pComm;
				} else {

					DELETE_OBJ (pKey);
					DELETE_OBJ ( pFileName);
					DELETE_OBJ ( pComm);
					return NULL;
				}
			}
				
		}
		aptr = ptr+1;
	}

	DELETE_OBJ (pKey);
	DELETE_OBJ ( pFileName);
	DELETE_OBJ ( pComm);

	return NULL;
}
//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
bool KompaktProFile  :: ExistDataPath (char *pData)
{
	if ( !pData || *pData == '\0') 
		return false;
	struct _stat ST;

	if ( _stat ( pData, &ST) != 0 )
		return false;
	return true;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
char *KompaktProFile :: GetPathLibrary ( void )
{
	if (_pFullName == NULL) 
		return NULL;

	if (!_isValid)
		return NULL;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return NULL;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return NULL;
	}
//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		DELETE_OBJ ( pFileName);
		return NULL;
	}

	char *aptr = &pFileName[0];
	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_KOMPAKTKEY, _pResTarget), 50));

	while ( *aptr != NULL ) {
		char *ptr = strrchr (aptr, '\0');
		if ( ptr != NULL ) {
			if ( strcmp ( pKey,aptr) == 0) {
				*pComm = '\0';
				GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);
				DELETE_OBJ (pKey);
				DELETE_OBJ ( pFileName);
				if ( *pComm != '\0') {

					if ( _pSoftPath)
						strcpy ( _pSoftPath,pComm);

					if ( *(pComm+strlen(pComm)-1) == '\\') 
						*(pComm+strlen(pComm)-1) = '\0';

					strcat ( pComm,ResString (ResID (IDS_KOMPAKTLIBRARY, _pResTarget), 50));
					return pComm;
				} else {
					DELETE_OBJ ( pComm);
					return NULL;
				}
			}
				
		}
		aptr = ptr+1;
	}

	DELETE_OBJ (pKey);
	DELETE_OBJ ( pFileName);
	DELETE_OBJ ( pComm);

	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void KompaktProFile :: SetLeistungsSchrittweite ( short iS )
{
	if (_pFullName == NULL) 
		return;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		return;
	}

	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_LEISTUNGSSCHRITT, _pResTarget), 50));
	wsprintf(pComm,"%d",iS);

	WritePrivateProfileString (Projects, pKey, pComm,_pFullName);


	DELETE_OBJ (pKey);
	DELETE_OBJ (pComm);

	return;
}
//-----------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
char *KompaktProFile :: GetLeistungsSchrittweite ( void )
{
	if (!_isValid)
		return NULL;

	if (_pFullName == NULL) 
		return NULL;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return NULL;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return NULL;
	}
//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		DELETE_OBJ ( pFileName);
		return NULL;
	}

	char *aptr = &pFileName[0];
	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_LEISTUNGSSCHRITT, _pResTarget), 50));

	while ( *aptr != NULL ) {
		char *ptr = strrchr (aptr, '\0');
		if ( ptr != NULL ) {
			if ( strcmp ( pKey,aptr) == 0) {
				*pComm = '\0';
				GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);
				DELETE_OBJ (pKey);
				DELETE_OBJ ( pFileName);
				if ( *pComm != '\0' ) {
					return pComm;
				} else {
					DELETE_OBJ (pComm);
					return NULL;
				}
			} else {
				char * pRefKey = new char [_MAX_PATH];
				if ( pRefKey) {
					*pRefKey = '\0';
					strcpy ( pRefKey,ResString (ResID (IDS_LEISTUNGSABSTAND, _pResTarget), 50));
					if ( strcmp ( pKey,aptr) == 0) {
						*pComm = '\0';
						GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);
						DELETE_OBJ (pKey);
						DELETE_OBJ (pRefKey);
						DELETE_OBJ ( pFileName);
						if ( *pComm != '\0' ) {
							return pComm;
						} else {
							DELETE_OBJ (pComm);
							return NULL;
						}
					}

					DELETE_OBJ (pRefKey);

				}
			}
		}
		aptr = ptr+1;
	}

	DELETE_OBJ (pKey);
	DELETE_OBJ (pComm);
	DELETE_OBJ ( pFileName);

	return NULL;
}
//---------------------------------------------------------------------------
void KompaktProFile :: SetPufferZone ( short iS )
{
	if (_pFullName == NULL) 
		return;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		return;
	}

	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_PUFFERZONE, _pResTarget), 50));
	wsprintf(pComm,"%d",iS);

	WritePrivateProfileString (Projects, pKey, pComm,_pFullName);


	DELETE_OBJ (pKey);
	DELETE_OBJ (pComm);

	return;
}
//-----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
char *KompaktProFile :: GetPufferZone ( void )
{
	if (!_isValid)
		return NULL;

	if (_pFullName == NULL) 
		return NULL;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return NULL;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return NULL;
	}
//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		DELETE_OBJ ( pFileName);
		return NULL;
	}

	char *aptr = &pFileName[0];
	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_PUFFERZONE, _pResTarget), 50));

	while ( *aptr != NULL ) {
		char *ptr = strrchr (aptr, '\0');
		if ( ptr != NULL ) {
			if ( strcmp ( pKey,aptr) == 0) {
				*pComm = '\0';
				GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);
				DELETE_OBJ (pKey);
				DELETE_OBJ ( pFileName);
				if ( *pComm != '\0' ) {
					return pComm;
				} else {
					DELETE_OBJ (pComm);
					return NULL;
				}
			}
		}
		aptr = ptr+1;
	}

	DELETE_OBJ (pKey);
	DELETE_OBJ (pComm);
	DELETE_OBJ ( pFileName);

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Projekt.Ini
// Konstruktor ----------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

KompaktPrivateProFile :: KompaktPrivateProFile ( ResourceFile *pResTarget ,char *pProject) 
{

	_pFullName = NULL;		// für alle Fälle
	_pSoftPath = NULL;
	_pDataPath = NULL;
	_isValid = false;

	if (pProject == NULL )
		return;
	
	// etvl. ResourceFile merken
	_pResTarget = pResTarget;

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
	_splitpath (pProject, pDrive, pPath, pDBName, NULL);
	
	_pFullName = new char [_MAX_PATH];
	if ( _pFullName == NULL) 
		return;
	_pSoftPath = new char [_MAX_PATH];
	if ( _pSoftPath == NULL) 
		return;

	if (_pFullName ) {

	// vollen ProFileNamen zusammenbauen  
		char *pExt = new char [ _MAX_EXT];
		if ( pExt == NULL ) {
			DELETE_OBJ (pDrive);
			DELETE_OBJ (pPath);
			DELETE_OBJ (pDBName);
			return;
		}

	// vollen ProFileNamen zusammenbauen  
		*pExt = '\0';
		strcat ( pExt,ResString (ResID (IDS_KOMPAKTEXTENSION, _pResTarget), 5));
		_makepath (_pFullName, pDrive, pPath, pDBName, pExt);
	}

	//Validation

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return ;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return;
	}
	_isValid = true;

	DELETE_OBJ ( pFileName);


}

#pragma warning (default: 4355)

// Destruktor
KompaktPrivateProFile :: ~KompaktPrivateProFile (void) 
{
	DELETE_OBJ ( _pFullName);
	DELETE_OBJ ( _pSoftPath);
	DELETE_OBJ ( _pDataPath);

}
////////////////////////////////////////////////////////////////////
// -----------------Liefert alle Datenbankschlüssel ------------
char *KompaktPrivateProFile :: GetPathDaten ( void )
{
	if (_pFullName == NULL) 
		return NULL;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return NULL;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return NULL;
	}

	_isValid = true;

//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		DELETE_OBJ ( pFileName);
		return NULL;
	}

	char *aptr = &pFileName[0];
	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_KOMPAKTDATEN, _pResTarget), 50));

	while ( *aptr != NULL ) {
		char *ptr = strrchr (aptr, '\0');
		if ( ptr != NULL ) {
			if ( strcmp ( pKey,aptr) == 0) {

				GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);


				if ( *pComm != '\0') {

/////////////////////////////////////////////////////////////////////////////////////////////
					// Existenz des Datenpfades !!!
					if ( !ExistDataPath(pComm)) {

						WritePrivateProfileString (Projects, pKey, NULL,_pFullName);	// Löschen

						DELETE_OBJ (pKey);
						DELETE_OBJ ( pFileName);
						DELETE_OBJ ( pComm);
						return NULL;
	
					}
/////////////////////////////////////////////////////////////////////////////////////////////
					DELETE_OBJ (pKey);
					DELETE_OBJ ( pFileName);

					if (!_pDataPath) 
						_pDataPath = new char [_MAX_PATH];
					if (_pDataPath)
						strcpy (_pDataPath,pComm);
					if ( *(pComm+strlen(pComm)-1) == '\\') {
						strcat ( pComm,ResString (ResID (IDS_KOMPAKTPROTOKOLL, _pResTarget), 50));
					} else {
						strcat ( pComm,"\\");
						strcat ( pComm,ResString (ResID (IDS_KOMPAKTPROTOKOLL, _pResTarget), 50));
					}

					return pComm;

				} else {

					DELETE_OBJ (pKey);
					DELETE_OBJ ( pFileName);
					DELETE_OBJ ( pComm);
					return NULL;
				}
			}
				
		}
		aptr = ptr+1;
	}

	DELETE_OBJ (pKey);
	DELETE_OBJ ( pFileName);
	DELETE_OBJ ( pComm);

	return NULL;
}
//////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
char *KompaktPrivateProFile :: GetPathLibrary ( void )
{
	if (!_isValid)
		return NULL;

	if (_pFullName == NULL) 
		return NULL;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return NULL;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return NULL;
	}
//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		DELETE_OBJ ( pFileName);
		return NULL;
	}

	char *aptr = &pFileName[0];
	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_KOMPAKTKEY, _pResTarget), 50));

	while ( *aptr != NULL ) {
		char *ptr = strrchr (aptr, '\0');
		if ( ptr != NULL ) {
			if ( strcmp ( pKey,aptr) == 0) {
				*pComm = '\0';
				GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);
				DELETE_OBJ (pKey);
				DELETE_OBJ ( pFileName);
				if ( *pComm != '\0') {
					if ( _pSoftPath)
						strcpy ( _pSoftPath,pComm);

					if ( *(pComm+strlen(pComm)-1) == '\\') 
						*(pComm+strlen(pComm)-1) = '\0';

					strcat ( pComm,ResString (ResID (IDS_KOMPAKTLIBRARY, _pResTarget), 50));
					return pComm;
				} else {
					DELETE_OBJ ( pComm);
					return NULL;
				}
			}
				
		}
		aptr = ptr+1;
	}

	DELETE_OBJ (pKey);
	DELETE_OBJ ( pFileName);
	DELETE_OBJ ( pComm);

	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
char *KompaktPrivateProFile :: GetLeistungsSchrittweite ( void )
{
	if (!_isValid)
		return NULL;

	if (_pFullName == NULL) 
		return NULL;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return NULL;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return NULL;
	}
//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		DELETE_OBJ ( pFileName);
		return NULL;
	}

	char *aptr = &pFileName[0];
	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_LEISTUNGSSCHRITT, _pResTarget), 50));

	while ( *aptr != NULL ) {
		char *ptr = strrchr (aptr, '\0');
		if ( ptr != NULL ) {
			if ( strcmp ( pKey,aptr) == 0) {
				*pComm = '\0';

				GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);

				DELETE_OBJ (pKey);
				DELETE_OBJ ( pFileName);
				if ( *pComm != '\0' ) {
					return pComm;
				} else {
					DELETE_OBJ (pComm);
					return NULL;
				}
			} else {
				char * pRefKey = new char [_MAX_PATH];
				if ( pRefKey) {
					*pRefKey = '\0';
					strcpy ( pRefKey,ResString (ResID (IDS_LEISTUNGSABSTAND, _pResTarget), 50));
					if ( strcmp ( pKey,aptr) == 0) {
						*pComm = '\0';
						GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);
						DELETE_OBJ (pKey);
						DELETE_OBJ (pRefKey);
						DELETE_OBJ ( pFileName);
						if ( *pComm != '\0' ) {
							return pComm;
						} else {
							DELETE_OBJ (pComm);
							return NULL;
						}
					}

					DELETE_OBJ (pRefKey);

				}
			}
		}
		aptr = ptr+1;
	}

	DELETE_OBJ (pKey);
	DELETE_OBJ (pComm);
	DELETE_OBJ ( pFileName);

	return NULL;
}
//////////////////////////////////////////////////////////////////////////////
char *KompaktPrivateProFile :: GetPufferZone ( void )
{
	if (!_isValid)
		return NULL;

	if (_pFullName == NULL) 
		return NULL;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
	char *pFileName = new char [ _MAX_PATH];

	if ( pFileName == NULL ) 
		return NULL;	

//	Füllen von pFileName mit allen DB-Schlüsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, _MAX_PATH, _pFullName);

	if (*pFileName == '\0') {	// nichts gefunden
		DELETE_OBJ ( pFileName);
		return NULL;
	}
//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	char * pComm = new char [_MAX_PATH];
	if ( !pKey || !pComm ) {
		DELETE_OBJ ( pComm);
		DELETE_OBJ ( pKey);
		DELETE_OBJ ( pFileName);
		return NULL;
	}

	char *aptr = &pFileName[0];
	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_PUFFERZONE, _pResTarget), 50));

	while ( *aptr != NULL ) {
		char *ptr = strrchr (aptr, '\0');
		if ( ptr != NULL ) {
			if ( strcmp ( pKey,aptr) == 0) {
				*pComm = '\0';
				GetPrivateProfileString (Projects, pKey, "", pComm, _MAX_PATH,_pFullName);
				DELETE_OBJ (pKey);
				DELETE_OBJ ( pFileName);
				if ( *pComm != '\0' ) {
					return pComm;
				} else {
					DELETE_OBJ (pComm);
					return NULL;
				}
			}
		}
		aptr = ptr+1;
	}

	DELETE_OBJ (pKey);
	DELETE_OBJ (pComm);
	DELETE_OBJ ( pFileName);

	return NULL;
}
///////////////////////////////////////////////////////////////////////////
bool KompaktPrivateProFile  :: ExistDataPath (char *pData)
{
	if ( !pData || *pData == '\0') 
		return false;
	struct _stat ST;

	if ( _stat ( pData, &ST) != 0 )
		return false;
	return true;
}
//---------------------------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////
void KompaktPrivateProFile :: SetDataConfiguration ( char *pComm )
{
	if (_pFullName == NULL) 
		return;

	ResString Projects (ResID (IDS_KOMPAKTAPPLIKATION, _pResTarget), 30);
		
//----------------------------------------------------
	char * pKey = new char [_MAX_PATH];
	if ( !pKey ) {
		return;
	}
	*pKey = '\0';
	strcpy ( pKey,ResString (ResID (IDS_KOMPAKTDATEN, _pResTarget), 50));

	WritePrivateProfileString (Projects, pKey, pComm,_pFullName);


	DELETE_OBJ (pKey);

	return;
}
//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//	ENDE KOMPPROF.CXX
