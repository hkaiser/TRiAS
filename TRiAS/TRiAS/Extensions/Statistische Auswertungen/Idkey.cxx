// Einlesen einer Datei, die Idents und MKode definiert
// File: IDKEY.CXX

#include "statistp.hxx"
#include "geostat.h"
#include <igeometr.hxx>

#include "dirmath.h"

#include "objkey.hxx"
#include "idkey.hxx"



// Member für Klasse IDM ------------------------------------------------------
IDM :: IDM (long Ident, struct IDGITYP *p )

{
	_lCount = _lPunkt = _lLinie = _lFlaeche = _lText = _lSonstige = 0L;
	_iIdGiTyp = 0;
	_lMCode =_lLoHoch = _lLoRechts = _lRuHoch = _lRuRechts = 0L;
	_rFlInhalt = _rLinLaenge = _rPolyLenMax = _rPolyLenMin = _rAreaMax = _rAreaMin = 0.0;
	_rPolyLenMedian = _rPolyLenMittel = _rAreaMedian = _rAreaMittel = 0.0;

//	OBJTree
	_pObjects = NULL;

	_lIdent = Ident;
	_lMCode = p->lMCode;
	_lCount = p->lCount;
	_lPunkt = p->lPoint;
	_lLinie = p->lLine;
	_lFlaeche = p->lArea;
	_lText = p->lText;
	_lKomplex = p->lComplex;
	_lSonstige = p->lNoname;
	_iIdGiTyp = p->iITyp;
	
	_rAreaMax = p->rAreaMax;
	_rAreaMin = p->rAreaMin;
	_rAreaMedian = p->rAreaMedian;
	_rAreaMittel = p->rAreaMittel;
	_rPolyLenMax = p->rPolyLenMax;
	_rPolyLenMin = p->rPolyLenMin;
	_rPolyLenMedian = p->rPolyLenMedian;
	_rPolyLenMittel = p->rPolyLenMittel;

	_lLoHoch = p->lYmax;
	_lLoRechts = p->lXmin;
	_lRuHoch = p->lYmin;
	_lRuRechts = p->lXmax;
	_rFlInhalt = p->rArea;
	_rLinLaenge = p->rPolyLen; 
	if ( p->pObj != NULL)
		_pObjects = (OBJTree *) p->pObj;
}

IDM :: ~IDM (void) {

	DELETE_OBJ ( _pObjects);	// OBjTree wieder raus

}

void IDM :: StoreObjTree ( OBJTree *pObj)
{

	if ( pObj ) {
		if ( _pObjects)
			DELETE_OBJ ( _pObjects);
		_pObjects = pObj;
	}	
	return;
}

void IDM :: DeleteObjTree ( void)
{
	if ( _pObjects )
		DELETE_OBJ ( _pObjects);
	
	return;
}

void IDM :: StoreMCode ( long MCode )
{
	_lMCode = MCode;
	
	return;
}

void IDM :: StoreObjParam ( struct IDGITYP *p)
{
	_rAreaMax = p->rAreaMax;
	_rAreaMin = p->rAreaMin;
	_rAreaMedian = p->rAreaMedian;
	_rAreaMittel = p->rAreaMittel;
	_rPolyLenMax = p->rPolyLenMax;
	_rPolyLenMin = p->rPolyLenMin;
	_rPolyLenMedian = p->rPolyLenMedian;
	_rPolyLenMittel = p->rPolyLenMittel;

	_lLoHoch = p->lYmax;
	_lLoRechts = p->lXmin;
	_lRuHoch = p->lYmin;
	_lRuRechts = p->lXmax;
	_rFlInhalt = p->rArea;
	_rLinLaenge = p->rPolyLen; 
	return;
}

///////////////////////////////////////////////////////////////////////////////
void IDM :: SetFlaechenParam ( struct IDGITYP *p)
{
	_lFlaeche = p->lArea;
	_rFlInhalt = p->rArea;
	_rAreaMax = p->rAreaMax;
	_rAreaMin = p->rAreaMin;
	_rAreaMedian = p->rAreaMedian;
	_rAreaMittel = p->rAreaMittel;
	return;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void IDM :: SetLinienParam ( struct IDGITYP *p)
{
	_lLinie = p->lLine;
	_rLinLaenge = p->rPolyLen; 
	_rPolyLenMax = p->rPolyLenMax;
	_rPolyLenMin = p->rPolyLenMin;
	_rPolyLenMedian = p->rPolyLenMedian;
	_rPolyLenMittel = p->rPolyLenMittel;
	return;
}

// Memberfunktionen für IDMTree -----------------------------------------------
IDMTree :: IDMTree (void) 
	 : CTree (GetIdent, CmpIdents)
{
	// nothing else to do
}

IDMTree :: ~IDMTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT IDMTree :: UserDelete (void *pObj) 
{
	((IDM *)pObj) -> IDM :: ~IDM();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetIdent (void *pObj) 
{
	return (void*)& (((IDM *)pObj) -> Ident());
}

int _XTENSN_EXPORT CmpIdents (void *pObj1, void *pObj2) 
{
long l1 = ((IDM *)pObj1) -> Ident();
long l2 = ((IDM *)pObj2) -> Ident();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
//------------------------------ListContainer-----------------------------

//  OBLCL ------------------------------------------------------------
OBJCL :: OBJCL ( short Typ, long lIdent, char * pLine ) 
{
	_OCLTyp = _OCLBezugsTyp = 0;
	_OCLIdent = 0;

	if ( pLine == NULL || *pLine == NULL )
		return;

	char *ptr = strchr ( pLine, ':' );
	if (!ptr)
		return;

	if ( *(ptr+1) == 'F' )
		_OCLTyp = OTFlaeche;
	if ( *(ptr+1) == 'L' )
		_OCLTyp = OTLinie;
	

	_OCLLine[0] = NULL;
	strcat (_OCLLine,pLine);
	*ptr = '\0';

	
//	ulong uIdent = (ulong)_OCLIdent;
//	IdentFromClassX (pLine,&uIdent);

	_OCLIdent = lIdent;

/*------------22.1.97
	if ( DEX_GetIdBase() == 16 )
		_OCLIdent = strtoul ( pLine, NULL, 16 );
	else
		_OCLIdent = atol(pLine);
------------*/

	_OCLBezugsTyp = Typ;

	return;
}
OBJCL :: ~OBJCL ( void ) 
{
}

//  Verwaltung der Daten ObjClass-Liste
//   ---------------------------------------------------------
OBJCLList :: OBJCLList (void)
	: CListContainer () 
{
	// nothing else to do
}

OBJCLList :: ~ OBJCLList (void) 
{
	EveryDelete ();
}

void _XTENSN_EXPORT OBJCLList :: UserDelete (void *pObj) 
{
	((OBJCL *) pObj) -> OBJCL :: ~OBJCL ();
}
// File: IDKEY.CXX
