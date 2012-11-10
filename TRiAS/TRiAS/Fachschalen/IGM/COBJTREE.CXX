// Baum, die zu einem Flächenobjekt alle innenliegenden Objekte 
// einer vorgegeben Klasse speichert ------------------------
// File: COBJTREE.CXX

#include "kompp.hxx"
#include "kompaktr.h"

#include "kompdef.h"
#include <igeometr.hxx>
#include "triasdef.h"

#include "cobjtree.hxx"

// Member für Klasse CObjTree ----------------------------------------------
CTop_Obj :: CTop_Obj (long Object, short iGiTyp)

{
	_lPObject = 0L;
	_plSObject = NULL;
	_lPLaenge = 0L;
	_lSLaenge = 0L;
	_lPFlaeche = 0L;
	_lSFlaeche = 0L;
	_iGiTyp = -1;
	_rRelTyp = REL_UNKLAR;
	_lPObject = Object;
	_iGiTyp = iGiTyp;
}

CTop_Obj :: ~CTop_Obj (void) {
	DELETE_OBJ ( _plSObject);
}
//----------------------------------------------------------------
void CTop_Obj :: SetSObject ( long *plONr )
{
			
	if ( plONr && *plONr > 0L ) {
		if ( _plSObject)
			DELETE_OBJ ( _plSObject);
		_plSObject = plONr;
	}
}
//----------------------------------------------------------------
void CTop_Obj :: SetPLaenge ( long lLen )
{
	if ( lLen > 0 )
		_lPLaenge = lLen;
}
//----------------------------------------------------------------
void CTop_Obj :: SetSLaenge ( long lLen )
{
	if ( lLen > 0 )
		_lSLaenge = lLen;
}
//----------------------------------------------------------------
void CTop_Obj :: SetPFlaeche ( long lFl )
{
	if ( lFl > 0 )
		_lPFlaeche = lFl;
}
//----------------------------------------------------------------
void CTop_Obj :: SetSFlaeche ( long lFl )
{
	if ( lFl > 0 )
		_lSFlaeche = lFl;
}
///////////////////////////////////////////////////////////////////
void CTop_Obj :: SetRelTyp ( Relat iTyp )
{

		_rRelTyp = iTyp;
}
///////////////////////////////////////////////////////////////////
void CTop_Obj :: SetGiTyp ( short iTyp )
{
	if (0 >= iTyp )
		_iGiTyp = iTyp;
}

//----------------------------------------------------------------
// Memberfunktionen für CObjTree ---------------------------------
CTop_ObjTree :: CTop_ObjTree (void) 
	 : CTree (GetCObj, CmpCObjs)
{
	// nothing else to do
}

CTop_ObjTree :: ~CTop_ObjTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT CTop_ObjTree :: UserDelete (void *pObj) 
{
	((CTop_Obj *)pObj) -> CTop_Obj :: ~CTop_Obj();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetCObj (void *pObj) 
{
	return (void*)& (((CTop_Obj *)pObj) -> PObject());
}

int _XTENSN_EXPORT CmpCObjs (void *pObj1, void *pObj2) 
{
long l1 = ((CTop_Obj *)pObj1) -> PObject();
long l2 = ((CTop_Obj *)pObj2) -> PObject();

	if ((ulong) l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
//--------------------------------------------------------------------------
// COBJTREE.CXX/////////////////////////////////////////////////////////////
