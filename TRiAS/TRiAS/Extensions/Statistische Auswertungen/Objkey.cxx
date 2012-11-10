// Einlesen einer Datei, die DB_Objecte definiert
// File: OBJKEY.CXX


#include "statistp.hxx"
#include "geostat.h"
#include <igeometr.hxx>

#include "dirmath.h"

#include "objkey.hxx"



// Member für Klasse OBJ ------------------------------------------------------
OBJ :: OBJ (long Object, struct OBJECTTYP *p )

{
	_iObjGiTyp = 0;
	_lIntervall = 0L;
	_lIdent=_lMCode=_lObject=_lLoHoch = _lLoRechts = _lRuHoch = _lRuRechts = 0L;
	_rFlInhalt = _rLinLaenge = 0.0; 
	_lObject = Object;
	_lIdent = p->lIdent;
	_lIntervall = p->lIntervall;
	_iObjGiTyp = p->iGITyp;
	_lLoHoch = p->lYmax;
	_lLoRechts = p->lXmin;
	_lRuHoch = p->lYmin;
	_lRuRechts = p->lXmax;
	_rFlInhalt = p->rArea;
	_rLinLaenge = p->rPolyLen; 

}

OBJ :: ~OBJ (void) {

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
