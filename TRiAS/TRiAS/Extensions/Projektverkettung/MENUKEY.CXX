// Einlesen einer Datei, die Menu-Klassen definiert
// File: MENUKEY.CXX

  
#include "tprojp.hxx"
#include "tproject.h"
#include "defproj.h"
#include "menukey.hxx"

// Member für Klasse PROJ ------------------------------------------------------
PROJ :: PROJ ( char *pKey, struct DBPROJECT *p )

{
	_pProj = _pDBName = _pSightName =_pUserName = _pDrive = _pPath = _pExt = NULL;
	_pOwner = _pPrev = _pNext = NULL;
	_lXmin = _lXmax = _lYmin = _lYmax = 0L;
	_iStatus = _iLevel = 0;
	_hMenu = 0;
	_MenuID = 0;
	_pTPRJ = NULL;	// Kette der Teilprojekte
	if ( pKey )
		strupr ( pKey);
	_pProj = StrDuplicat ( pKey);
	_pDBName = StrDuplicat(p->pDBName);
	_pUserName = StrDuplicat(p->pUserName);
	_pSightName = StrDuplicat(p->pSightName);
	_pDrive = StrDuplicat(p->pDrive);
	_pPath = StrDuplicat(p->pPath);
	_pExt = StrDuplicat(p->pExt);
	_pOwner = StrDuplicat(p->pOwner);
	_pPrev = StrDuplicat(p->pPrev);
	_pNext = StrDuplicat(p->pNext);

//	Status 
//	: keine TP
//	: TP - in INI unverändert
//	: TP - in INI modifiziert
	_iStatus = p->iStatus;
	_iLevel = p->iLevel;
	_iPrevMenuPoint = p->iPrevMenuPoint;

	_lYmin = p->lYmin;
	_lXmin = p->lXmin;
	_lYmax = p->lYmax;
	_lXmax = p->lXmax;
	_pTPRJ = p->pTPRJ;
}

PROJ :: ~PROJ (void) {

	DELETE_OBJ ( _pTPRJ);	// TPRJTree wieder raus
	if ( _hMenu != 0 )
		DestroyMenu ( _hMenu);

}

void PROJ :: StoreTProjects ( TPRJTree * pTPRJ) {

	if ( pTPRJ ) {
		if (_pTPRJ)
			DELETE_OBJ ( _pTPRJ);
		_pTPRJ = pTPRJ;
	}

}

void PROJ :: DeleteTProjects ( void ) {

	if (_pTPRJ)
		DELETE_OBJ ( _pTPRJ);

}

void PROJ :: StoreTPMenu ( HMENU hMenu) {

	_hMenu = hMenu;

}

void PROJ :: StoreMenuID ( UINT MenuID) {

	_MenuID = MenuID;

}

void PROJ :: StorePreviousProject ( char * pPrev) {
	if ( pPrev ) {
		if ( _pPrev)
			DELETE_OBJ ( _pPrev);
		_pPrev = StrDuplicat( pPrev);
		strupr( _pPrev);
	}

}


void PROJ :: StoreSightName (char * pSight) {

	if ( !pSight) return;
	if ( _pSightName)
		DELETE_OBJ ( _pSightName);

   	_pSightName = StrDuplicat(pSight);
   	return;
}

void PROJ :: StoreOwner (char * pOwner) {

	if ( !pOwner) return;
	if( _pOwner)
		DELETE_OBJ ( _pOwner);
   	_pOwner = StrDuplicat(pOwner);
	strupr ( _pOwner);
   	return;
}

// Memberfunktionen für PROJTree -----------------------------------------------
PROJTree :: PROJTree (void) 
	 : CTree (GetProj, CmpProjs)
{
	// nothing else to do
}

PROJTree :: ~PROJTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT PROJTree :: UserDelete (void *pProj) 
{
	((PROJ *)pProj) -> PROJ :: ~PROJ();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetProj (void *pProj) 
{
	return (void*) (((PROJ *)pProj) -> Proj());
}

int _XTENSN_EXPORT CmpProjs (void *pProj1, void *pProj2) 
{
//char *l1 = ((PROJ *)pProj1) -> Proj();
//char *l2 = ((PROJ *)pProj2) -> Proj();

	char *l1 = (char *) pProj1;
	char *l2 = (char *) pProj2;

	if (strcmp(l1,l2) < 0) return -1;
	if (strcmp(l1,l2) > 0) return 1;
	return 0;
}
//------------------------------------------------------------------------

// Member für Klasse TPRJ ------------------------------------------------------
TPRJ :: TPRJ ( char *pKey, struct DBPROJECT *p )

{
	_pMenu = _pDBName = _pSightName = _pUserName = NULL;
	_pDrive = _pPath = _pExt = _pOwner = NULL;
	_lXmin=_lXmax=_lYmin = _lYmax = 0L;
	_iStatus = _iLevel = 0;
	_MenuID = 0;
	_pMenu = StrDuplicat(pKey);
	_pDBName = StrDuplicat(p->pDBName);
	_pUserName = StrDuplicat(p->pUserName);
	_pSightName = StrDuplicat(p->pSightName);
	_pDrive = StrDuplicat(p->pDrive);
	_pPath = StrDuplicat(p->pPath);
	_pExt = StrDuplicat(p->pExt);
	_pOwner = StrDuplicat(p->pOwner);

	_iStatus = p->iStatus;
	_iLevel = p->iLevel;
	_lYmin = p->lYmin;
	_lXmin = p->lXmin;
	_lYmax = p->lYmax;
	_lXmax = p->lXmax;

}

TPRJ :: ~TPRJ (void) {


}

void TPRJ :: StoreNewTPAddress (char * pDrive, char *pPath, char *pDBName, char *pExt)
{

	if ( !pDrive || !pPath || !pDBName || !pExt)
		return;
	if ( _pDBName )
		DELETE_OBJ ( _pDBName);
	_pDBName = StrDuplicat(pDBName);

	if ( _pUserName )
		DELETE_OBJ ( _pUserName);
	_pUserName = StrDuplicat(pDBName);

	if ( _pDrive )
		DELETE_OBJ ( _pDrive);
	_pDrive = StrDuplicat(pDrive);

	if ( _pPath )
		DELETE_OBJ ( _pPath);
	_pPath = StrDuplicat(pPath);

	if ( _pExt )
		DELETE_OBJ ( _pExt);
	_pExt = StrDuplicat(pExt);

   	return;
}

void TPRJ :: StoreSightName (char * pSight) {

	if ( !pSight) return;
	
	if ( _pSightName)
		DELETE_OBJ ( _pSightName);
   	_pSightName = StrDuplicat(pSight);
   	return;
}

void TPRJ :: StoreMenuID ( UINT MenuID) {

	_MenuID = MenuID;

}


// Memberfunktionen für TPRJTree -----------------------------------------------
TPRJTree :: TPRJTree (void) 
	 : CTree (GetMenu, CmpMenus)
{
	// nothing else to do
}

TPRJTree :: ~TPRJTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TPRJTree :: UserDelete (void *pMenu) 
{
	((TPRJ *)pMenu) -> TPRJ :: ~TPRJ();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetMenu (void *pMenu) 
{
	return (void*) (((TPRJ *)pMenu) -> Menu());
}

int _XTENSN_EXPORT CmpMenus (void *pMenu1, void *pMenu2) 
{
//char *l1 = ((TPRJ *)pMenu1) -> Menu();
//char *l2 = ((TPRJ *)pMenu2) -> Menu();
  
  	char *l1 = ( char * ) pMenu1;
  	char *l2 = ( char * ) pMenu2;
  	
	if (strcmp(l1,l2) < 0) return -1;
	if (strcmp(l1,l2) > 0) return 1;
	return 0;
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------

// Member für Klasse MMenu ------------------------------------------------------
MMenu :: MMenu ( char *pKey, struct MODMENU *p )

{
	_pMenu = _pDBName = _pReferenz = NULL;
	_iStatus = _iMenuNr = _iModKZ = 0;
	_pMenu = StrDuplicat(pKey);
	_pDBName = StrDuplicat(p->pDBName);
	_pReferenz = StrDuplicat(p->pReferenz);

	_iModKZ = p->iModKZ;
	_iStatus = p->iStatus;
	_iMenuNr = p->iMenuNr;
}
//----------------------------------------------
MMenu :: ~MMenu (void)
{

}

void MMenu :: StoreReferenz (char * pProject, char *pReferenz) {
	if ( _pDBName)
		DELETE_OBJ ( _pDBName );
	if ( _pReferenz)
		DELETE_OBJ ( _pReferenz);

   	_pDBName = StrDuplicat(pProject);
   	_pReferenz = StrDuplicat(pReferenz);
   	return;
}

// Memberfunktionen für TPRJTree -----------------------------------------------
MMenuTree :: MMenuTree (void) 
	 : CTree (GetMNr, CmpMNrs)
{
	// nothing else to do
}

MMenuTree :: ~MMenuTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT MMenuTree :: UserDelete (void *pMenu) 
{
	((MMenu *)pMenu) -> MMenu :: ~MMenu();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetMNr (void *pMenu) 
{
	return (void*) (((MMenu *)pMenu) -> Menu());
}

int _XTENSN_EXPORT CmpMNrs (void *pMenu1, void *pMenu2) 
{
  
  	char *l1 = ( char * ) pMenu1;
  	char *l2 = ( char * ) pMenu2;
  	
	if (strcmp(l1,l2) < 0) return -1;
	if (strcmp(l1,l2) > 0) return 1;
	return 0;
}
//------------MENUKEY.CXX------------------------------------------------------
