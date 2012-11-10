// Einlesen einer Datei, die DB_Objecte definiert
// File: OBJKEY.CXX


#include "attribp.hxx"

#include <triastlb_i.c>
#include <triastlb.h>

#include <oleguid.h>
#include <dirisole.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include <shellapi.h>
#include <igeometr.hxx>

#include <xtsnaux.hxx>
#include <initguid.h>
#include <istatus.h>

#include <igeometr.hxx>

#include "attribut.h"
#include "define.h"   
#include "stohwnd.hxx"
#include "idkey.hxx"
#include "objkey.hxx"
#include "clstree.hxx"
#include "attribut.hxx"


// Member für Klasse OBJ ------------------------------------------------------
OBJ :: OBJ (long Object, struct OBJECTTYP *p )

{
	_iObjGiTyp = 0;
	_lIdent=_lMCode= _lPartner = 0L;
	_lObject = Object;
	_lIdent = p->lIdent;
	_iObjGiTyp = p->iGITyp;
	_iFlag = FALSE;
}

OBJ :: ~OBJ (void) {

}
void OBJ :: SetFlag ( void )
{
	_iFlag = TRUE;
}

void OBJ :: SetPartner ( long lPartner )
{
	_lPartner = lPartner;
}

// Memberfunktionen für OBJTree -----------------------------------------------
OBJTree :: OBJTree (void) 
	 : CTree (GetObject, CmpObjects)
{
	// nothing else to do
}

OBJTree :: ~OBJTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT OBJTree :: UserDelete (void *pObj) 
{
	((OBJ *)pObj) -> OBJ :: ~OBJ();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetObject (void *pObj) 
{
	return (void*)& (((OBJ *)pObj) -> Object());
}

int _XTENSN_EXPORT CmpObjects (void *pObj1, void *pObj2) 
{
long l1 = ((OBJ *)pObj1) -> Object();
long l2 = ((OBJ *)pObj2) -> Object();

	if (l1 < l2) return -1;
	if (l1 > l2) return 1;
	return 0;
}
