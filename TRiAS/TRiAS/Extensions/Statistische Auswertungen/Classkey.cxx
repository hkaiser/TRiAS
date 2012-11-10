// Einlesen einer Datei, die GI-OBJ-Klassen definiert
// File: CLASSKEY.CXX


#include "statistp.hxx"
#include "geostat.h"
#include <igeometr.hxx>
#include "dirmath.h"
#include "objkey.hxx"
#include "classkey.hxx"

// Member für Klasse GICLA ------------------------------------------------------
GICLA :: GICLA (long Group, struct GICLASS *p )

{
	_iGiTyp = 0;
	_lCount = _lCountM = 0;
	_lGroupNr=_lEinheit=_lOperate1 = _lOperate2 = 0L;
	_lXmin=_lXmax=_lYmin = _lYmax = 0L;
	_IDNr = _MCode = 0L;
	_rVglWert1 = _rVglWert2 = _rKumul = _rKumulMin = _rKumulMax = 0.0; 
//	OBJTree
	_pObjects = NULL;

	_lGroupNr = Group;
	_lEinheit = p->lEinheit;
	_iGiTyp = p->iGiTyp;
	_lCount = p->lCount;
	_lOperate1 = p->lOperate1;
	_lOperate2 = p->lOperate2;
	_rVglWert1 = p->rVglWert1;
	_rVglWert2 = p->rVglWert2; 
	_rKumul = p->rKumul;
	_rKumulMin = p->rKumulMin;
	_rKumulMax = p->rKumulMax;
	_lYmin = p->lYmin;
	_lXmin = p->lXmin;
	_lYmax = p->lYmax;
	_lXmax = p->lXmax;
	_IDNr = p->IDNr;
	_MCode = p->MCode;
	if ( p->pObj != NULL)
		_pObjects = (OBJTree *) p->pObj;

}

GICLA :: ~GICLA (void) {

	DELETE_OBJ ( _pObjects);	// OBjTree wieder raus

}

void GICLA :: StoreObjTree ( OBJTree *pObj)
{
	_pObjects = pObj;
	
	return;
}


// Memberfunktionen für CICLATree -----------------------------------------------
GICLATree :: GICLATree (void) 
	 : CTree (GetGroup, CmpGroups)
{
	// nothing else to do
}

GICLATree :: ~GICLATree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT GICLATree :: UserDelete (void *pGroup) 
{
	((GICLA *)pGroup) -> GICLA :: ~GICLA();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetGroup (void *pGroup) 
{
	return (void*)& (((GICLA *)pGroup) -> Group());
}

int _XTENSN_EXPORT CmpGroups (void *pGroup1, void *pGroup2) 
{
long l1 = ((GICLA *)pGroup1) -> Group();
long l2 = ((GICLA *)pGroup2) -> Group();

	if (l1 < l2) return -1;
	if (l1 > l2) return 1;
	return 0;
}
