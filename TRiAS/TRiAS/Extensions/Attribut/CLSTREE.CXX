
// Einlesen einer Datei, die MK zu Id zuordnet
// File: CLSTREE.CXX

#include "attribp.hxx"
#include <igeometr.hxx>
#include <shellapi.h>


// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "attribut.h"
#include "define.h"   
#include "idkey.hxx"
#include "objkey.hxx" 
#include "stohwnd.hxx"
#include "clstree.hxx"
#include "attribut.hxx"


// Member für Klasse CLS ------------------------------------------------------
CLS :: CLS (char *pMerkmal, long Ident, char *pKurzText)

{
	_pMerkmal = _pKurzText = NULL;
	_lIdent = 0L;

	if ( pMerkmal ) 
		_pMerkmal = StrDuplicat( pMerkmal);

	if ( pKurzText ) 
		_pKurzText = StrDuplicat( pKurzText);

	_lIdent = Ident;
}

CLS :: ~CLS (void) 
{
	DELETE (_pMerkmal);

}
// Memberfunktionen für CLSTree -----------------------------------------------
CLSTree :: CLSTree (void) 
	 : CTree (GetClass, CmpClasses)
{
	// nothing else to do
}

CLSTree :: ~CLSTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT CLSTree :: UserDelete (void *pObj) 
{
	((CLS *)pObj) -> CLS :: ~CLS();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetClass (void *pObj) 
{
	return (void*) (((CLS *)pObj) -> Merkmal());
}

int _XTENSN_EXPORT CmpClasses (void *pObj1, void *pObj2) 
{
	char *l1 = (char * )pObj1;
	char *l2 = (char * )pObj2;

	if (strcmp(l1,l2) < 0 ) return -1;
	if (strcmp ( l1,l2 ) > 0 ) return 1;
	return 0;
}
//------------------------------------------------------------


// Member für Klasse VClass ------------------------------------------------------
VClass :: VClass (char *pMerkmal)

{
	_pMerkmal = NULL;
	_pObj = NULL;

	if ( pMerkmal ) 
		_pMerkmal = StrDuplicat( pMerkmal);

}

VClass :: ~VClass (void) 
{
	DELETE (_pMerkmal);
	DELETE (_pObj);

}
void VClass :: StoreObjTree ( OBJTree *pObj)
{
	if ( !pObj)
		return;
	if ( _pObj )
		DELETE ( _pObj);
	_pObj = pObj;
	return;
}
// Memberfunktionen für CLSTree -----------------------------------------------
VClassTree :: VClassTree (void) 
	 : CTree (GetVClass, CmpVClasses)
{
	// nothing else to do
}

VClassTree :: ~VClassTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT VClassTree :: UserDelete (void *pObj) 
{
	((VClass *)pObj) -> VClass :: ~VClass();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetVClass (void *pObj) 
{
	return (void*) (((VClass *)pObj) -> Merkmal());
}

int _XTENSN_EXPORT CmpVClasses (void *pObj1, void *pObj2) 
{
	char *l1 = (char * )pObj1;
	char *l2 = (char * )pObj2;

	if (strcmp(l1,l2) < 0 ) return -1;
	if (strcmp ( l1,l2 ) > 0 ) return 1;
	return 0;
}
//------------------------------------------------------------

// File: CLSTREE.CXX
