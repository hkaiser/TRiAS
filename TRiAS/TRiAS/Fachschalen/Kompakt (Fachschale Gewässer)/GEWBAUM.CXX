// Einlesen einer Datei, die Idents und MKode definiert
// File: GEWBAUM.CXX

#include "kompp.hxx"

#include "kompias.h"   
#include "about.h"
#include "kompdef.h"
#include "about.hxx"
#include "igeometr.hxx"
#include "triasdef.h"
#include "gewbaum.hxx"


///////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_OCL -----------------------------------------------
TR_OCL :: TR_OCL (long Ident, long MCode, short isValid, TR_OBJTree *pObj )

{
	_lMCode =_lIdent = 0L;
	_pOBJ = NULL;
	_lIdent = Ident;
	_lMCode = MCode;
	_isValid = isValid;
	_iDefine = isValid;
	if ( pObj)
		_pOBJ = pObj;
}

TR_OCL :: ~TR_OCL (void) {
	DELETE_OBJ ( _pOBJ);
}
// Member 
void TR_OCL :: StoreObj ( TR_OBJTree *pOBJ )
{   

	if ( _pOBJ )
		DELETE_OBJ ( _pOBJ);

	if ( pOBJ )
		_pOBJ = pOBJ;
	else
		_pOBJ = NULL;
			
}
//////////////////////////////////////////////////////////////////////////
void TR_OCL :: DeleteObj ( void )
{   

	if ( _pOBJ )
		DELETE_OBJ ( _pOBJ);

}
//////////////////////////////////////////////////////////////////////////
// Memberfunktionen für TR_OCLTree -----------------------------------------------
TR_OCLTree :: TR_OCLTree (void) 
	 : CTree (GetID, CmpIDs)
{
	// nothing else to do
}

TR_OCLTree :: ~TR_OCLTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TR_OCLTree :: UserDelete (void *pObj) 
{
	((TR_OCL *)pObj) -> TR_OCL :: ~TR_OCL();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetID (void *pObj) 
{
	return (void*)& (((TR_OCL *)pObj) -> Ident());
}

int _XTENSN_EXPORT CmpIDs (void *pObj1, void *pObj2) 
{
long l1 = ((TR_OCL *)pObj1) -> Ident();
long l2 = ((TR_OCL *)pObj2) -> Ident();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
//--------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_OBJ ------------------------------------------------
TR_OBJ :: TR_OBJ (long Object, char *pGewNr , short iTyp)

{
	_lObject = 0L;
	_lLaenge = 0L;
	_lObjectIdent = 0L;
	_lVon = _lBis = -1L;
	_lRechts = _lHoch = -1L;
	_pBez = NULL;
	_pGewNr = NULL;
	_pGewName = NULL;
	_lObject = Object;
	_iTyp = 0;
	if ( pGewNr ) 
		_pGewNr = StrDuplicat( pGewNr);
	_iTyp = iTyp;
}

TR_OBJ :: ~TR_OBJ (void) {
	DELETE_OBJ ( _pBez);
	DELETE_OBJ ( _pGewNr);
	DELETE_OBJ ( _pGewName);
}
//----------------------------------------------------------------
void TR_OBJ :: StoreObjLaenge ( long lLen )
{
	if ( lLen > 0 )
		_lLaenge = lLen;
}
//----------------------------------------------------------------
void TR_OBJ :: SetObjectIdent ( long lIdent )
{
	if ( lIdent > 0 )
		_lObjectIdent = lIdent;
}
//----------------------------------------------------------------
void TR_OBJ :: SpeichernGewaesserNummer ( char *pGewNr )
{
	if ( pGewNr ) {
		if ( _pGewNr )
			DELETE_OBJ ( _pGewNr);
		_pGewNr = StrDuplicat (pGewNr);
	
	}
	
}
//----------------------------------------------------------------
void TR_OBJ :: SpeichernGewaesserName ( char *pGewName )
{
	if ( pGewName ) {
		if ( _pGewName )
			DELETE_OBJ ( _pGewName);
		_pGewName = StrDuplicat (pGewName);
	
	}
	
}
///////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
void TR_OBJ :: SpeichernBezeichnung ( char *pBez )
{
	if ( pBez ) {
		if ( _pBez )
			DELETE_OBJ ( _pBez);
		_pBez = StrDuplicat (pBez);
	
	}
	
}
///////////////////////////////////////////////////////////////////
void TR_OBJ :: SetIntervall ( long lVon, long lBis) 
{
	if ( 0L <= lVon && 0L <= lBis ) {
			_lVon = lVon;
			_lBis = lBis;
			_lLaenge = lBis - lVon;
	}
}
///////////////////////////////////////////////////////////////////
void TR_OBJ :: SetKoordinate ( long lR, long lH) 
{
	if ( 0L <= lR || 0L <= lH ) {
			_lRechts = lR;
			_lHoch = lH;
	}
}
////////////////////////////////////////////////////////////////////
bool TR_OBJ :: GetIntervall ( long *lpVon, long *lpBis)
{
	if ( _lVon != -1L && _lBis != -1L ) {
			*lpVon = _lVon;
			*lpBis = _lBis;
			return true;
	} else
		return false;
}
//////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
// Memberfunktionen für TR_OCLTree ---------------------------------
TR_OBJTree :: TR_OBJTree (void) 
	 : CTree (GetObject, CmpObjects)
{
	// nothing else to do
}

TR_OBJTree :: ~TR_OBJTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TR_OBJTree :: UserDelete (void *pObj) 
{
	((TR_OBJ *)pObj) -> TR_OBJ :: ~TR_OBJ();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetObject (void *pObj) 
{
	return (void*)& (((TR_OBJ *)pObj) -> Object());
}

int _XTENSN_EXPORT CmpObjects (void *pObj1, void *pObj2) 
{
long l1 = ((TR_OBJ *)pObj1) -> Object();
long l2 = ((TR_OBJ *)pObj2) -> Object();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
////////////////////////////////////////////////////////////////////////////
// Member für Klasse TS_OBJ ------------------------------------------------
TS_OBJ :: TS_OBJ (long lObject, long lStart, long lEnde)

{
	_lObject = _lStart = _lEnde = 0L;
	if ( lObject > 0L)
		_lObject = lObject;
	if ( lStart > 0L)
		_lStart = lStart;
	if ( lEnde > 0L)
		_lEnde = lEnde;
}
/////////////////////////////////////////////////////////////////////
TS_OBJ :: ~TS_OBJ (void) {


	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  _lStart;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_TEXT ) {
			DEX_DeleteObject(OS.lONr);
		}
	}

	OS.lONr =  _lEnde;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_TEXT ) {
			DEX_DeleteObject(OS.lONr);
		}
	}


	return;

}
//////////////////////////////////////////////////////////////////
void TS_OBJ :: SetTextInformation ( long lStart, long lEnde) 
{

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  _lStart;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_TEXT ) {
			DEX_DeleteObject(OS.lONr);
			if ( lStart > 0L)
				_lStart = lStart;
			
		}
	}

	OS.lONr =  _lEnde;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_TEXT ) {
			DEX_DeleteObject(OS.lONr);
			if ( lEnde > 0L)
				_lEnde = lEnde;
		}
	}

	return;
}
//////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
// Memberfunktionen für TS_OCLTree ---------------------------------
TS_OBJTree :: TS_OBJTree (void) 
	 : CTree (GetTObject, CmpTObjects)
{
	// nothing else to do
}

TS_OBJTree :: ~TS_OBJTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TS_OBJTree :: UserDelete (void *pObj) 
{
	((TS_OBJ *)pObj) -> TS_OBJ :: ~TS_OBJ();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetTObject (void *pObj) 
{
	return (void*)& (((TS_OBJ *)pObj) -> Object());
}

int _XTENSN_EXPORT CmpTObjects (void *pObj1, void *pObj2) 
{
long l1 = ((TS_OBJ *)pObj1) -> Object();
long l2 = ((TS_OBJ *)pObj2) -> Object();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
//--------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////
// GewaesserBereiche
///////////////////////////////////////////////////////////////////////////
// Member für Klasse KP_GEB -----------------------------------------------
KP_GEB :: KP_GEB ( long lPos, long lONr, FLAECHENANABSCHNITTEN *l)
{
	_pGewNr = _pObjKlasse = _pObjBez = NULL;
	_lPos = _lONr = _lBeginn = _lEnde = 0L;
	_iIdentNr = _iLRBeide = 0;
	_dFlaeche = 0.0;
	if (!l)
		return;

	_lPos = lPos;
	_lONr = lONr;

	if ( l->pcGewaesserNr ) 
		_pGewNr = StrDuplicat( l->pcGewaesserNr);
	if ( l->pObjektKlasse ) 
		_pObjKlasse = StrDuplicat( l->pObjektKlasse);
	if ( l->pObjektBezeichnung ) 
		_pObjBez = StrDuplicat( l->pObjektBezeichnung);
	_iIdentNr = l->iIdentNr;
	_lBeginn = l->lBeginn;
	_lEnde = l->lEnde;
	_iLRBeide = l->iLinksRechtsBeide;
	_dFlaeche = l->dQuadratMeter;

}

KP_GEB :: ~KP_GEB (void) 
{
	DELETE_OBJ (_pGewNr);
	DELETE_OBJ (_pObjKlasse);
	DELETE_OBJ (_pObjBez);

}
/////////////////////////////////////////////////////////////////////////////

// Memberfunktionen für KPTree -----------------------------------------------
KPBTree :: KPBTree (void) 
	 : CTree (GetArea, CmpAreas)
{
	// nothing else to do
}

KPBTree :: ~KPBTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT KPBTree :: UserDelete (void *pObj) 
{
	((KP_GEB *)pObj) -> KP_GEB :: ~KP_GEB();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetArea (void *pObj) 
{
	return (void*)& (((KP_GEB *)pObj) -> Pos());
}

int _XTENSN_EXPORT CmpAreas (void *pObj1, void *pObj2) 
{

long *l1 = (long *)pObj1;
long *l2 = (long *)pObj2;

//long l1 = ((KP_GEB *)pObj1) -> Pos();
//long l2 = ((KP_GEB *)pObj2) -> Pos();
	if (*l1 < *l2) return -1;
	if ( *l1 > *l2) return 1;

	return 0;
}
//------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////
// GewaesserKlasse
///////////////////////////////////////////////////////////////////////////
// Member für Klasse KP_GEW -----------------------------------------------
KP_GEW :: KP_GEW ( GEWAESSER *l, KP_LATree *pLA)

{
	_pGewNr = _pGewName = NULL;
	_lONr = _lBeginn = _lEnde = _lBeginnKompakt = _lEndeKompakt = 0L;
	_lCount = _lCountKompakt = 0L;
	_iHerkunft = _iZuordnung = 0;
	_pLA = NULL;	// Baum der Leistungsarten
	_pPA = NULL;	// Baum der Punktarten
	_pOBJ = NULL;	// Baum der TRiAS - Objekte
	_iPos = -1;	// 1.Position in Liste
	if (!l)
		return;

	if ( pLA)
		_pLA = pLA;

	if ( l->pcGewaesserNr ) 
		_pGewNr = StrDuplicat( l->pcGewaesserNr);

	if ( l->pcGewaesserName ) 
		_pGewName = StrDuplicat( l->pcGewaesserName);
	
	_lBeginn = l->lBeginn;
	_lEnde = l->lEnde;
		
}

KP_GEW :: ~KP_GEW (void) 
{
	DELETE_OBJ (_pGewNr);
	DELETE_OBJ (_pGewName);
	DELETE_OBJ (_pLA);
	DELETE_OBJ (_pPA);
	DELETE_OBJ ( _pOBJ);

}
// Member KP_GEW
void KP_GEW :: SpeichereLeistung (KP_LATree * pLA) 
{
	if (!pLA)
		return;
	if ( _pLA )
		DELETE_OBJ ( _pLA);
	_pLA = pLA;
}
void KP_GEW :: SpeicherePunkt (KP_LATree * pPA) 
{
	if (!pPA)
		return;
	if ( _pPA )
		DELETE_OBJ ( _pPA);
	_pPA = pPA;
}
void KP_GEW :: SpeichereObjekt ( long lONr) 
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE ) 
			return;
	}

	if ( _lONr > 0L) {
		if ( !_pOBJ)
			_pOBJ = new TR_OBJTree;
		CTable t (*_pOBJ);

		if ( !t.Find ( &_lONr) ) {
			TR_OBJCreator OCr ( *_pOBJ);
			ContCreate ( OCr, TR_OBJ ) (_lONr,NULL);
		}

	}
	_lONr = lONr;

}
void KP_GEW :: SpeichereObjektLaenge ( long lLen) 
{
	if ( lLen >= 0L ) {
		_lEnde = lLen;
		_lBeginn = 0L;
	}
}
void KP_GEW :: SetStartEndPunkt ( long lStart,long lEnde) 
{
	if ( lStart <= lEnde ) {
		_lEnde = lEnde;
		_lBeginn = lStart;
	}
}
void KP_GEW :: TauscheZuKompakt (void) 
{
	_lBeginnKompakt = _lBeginn;
	_lBeginn = 0L;
	_lEndeKompakt = _lEnde;
	_lEnde = 0L;
}
void KP_GEW :: TauscheZuTRiAS (void) 
{
	_lBeginn = _lBeginnKompakt;
	_lBeginnKompakt = 0L;
	_lEnde = _lEndeKompakt;
	_lEndeKompakt = 0L;
}
void KP_GEW :: TRiASKompaktAbgleich (void) 
{
	_lBeginnKompakt = _lBeginn;
	_lEndeKompakt = _lEnde;

}
void KP_GEW :: KompaktTRiASAbgleich (void) 
{
	_lBeginn = _lBeginnKompakt;
	_lEnde = _lEndeKompakt;
}
void KP_GEW :: SetKompaktLen (long lLen) 
{
	if ( lLen > 0L) {
		_lBeginnKompakt = 0L;
		_lEndeKompakt = lLen;
	}
}
///////////////////////////////////////////////////////////////////////////////
void KP_GEW :: StoreGewName ( char *pName)
{
	if ( !pName)
		return;

	if ( _pGewName )
		DELETE_OBJ ( _pGewName);

	if (pName ) 
		_pGewName = StrDuplicat( pName);
	
}
//////////////////////////////////////////////////////////////////////////////
void KP_GEW :: SetOBJ ( TR_OBJTree *pOBJ)
{
	if ( pOBJ ) {
		if ( _pOBJ )
			DELETE_OBJ ( _pOBJ);
		_pOBJ = pOBJ;
	}
		
}
void KP_GEW :: SetPosition ( short iPos )
{
	if (iPos >= 0 )
		_iPos = iPos;
}
/////////////////////////////////////////////////////////////////////////////

// Memberfunktionen für KPTree -----------------------------------------------
KPTree :: KPTree (void) 
	 : CTree (GetIdent, CmpIdents)
{
	// nothing else to do
}

KPTree :: ~KPTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT KPTree :: UserDelete (void *pObj) 
{
	((KP_GEW *)pObj) -> KP_GEW :: ~KP_GEW();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetIdent (void *pObj) 
{
	return (void*) (((KP_GEW *)pObj) -> GewNr());
}

int _XTENSN_EXPORT CmpIdents (void *pObj1, void *pObj2) 
{
	char *l1 = (char * )pObj1;
	char *l2 = (char * )pObj2;

	if (strcmp(l1,l2) < 0 ) return -1;
	if (strcmp ( l1,l2 ) > 0 ) return 1;
	return 0;
}
//------------------------------------------------------------

// Member für Klasse KP_LA ------------------------------------------------------
KP_LA :: KP_LA ( long lCount, KOMPAKTDATEN *l)

{
	_pGewNr = _pLeistung = _pZuordnung = _pKurzText = _pLangText = _pComment = NULL;
	_lCount = _lONr = _lBeginn = _lEnde = _lMeterOffen = 0L;
	_dHoehe = _dKostet = 0.0;
	_iRechnNr = _iHerkunft = _iZuordnung = 0;
	_iLinksRechtsMitte = Leist_Mitte;

//----Bauwerke
	_pBauwBez = _pBez1 = _pBez2 = NULL;
	_lHoch = _lRechts = _lAnlageNr = 0L;
	_lObjectIdent = 0L;
	_dBauwHoehe = _dWasserSpDiff = 0.0;
//--------------------------------------------------------------
	if ( lCount <= 0L)
		return;

	if (!l)
		return;

	_lCount = lCount;

	if ( l->pcGewaesserNr ) 
		_pGewNr = StrDuplicat( l->pcGewaesserNr);

	_iHerkunft = l->iIdentNrHerkunft;
	_iZuordnung = l->iIdentNrZuordnung;
	_iLinksRechtsMitte = l->iLinksRechtsMitte;

	_lBeginn = l->lBeginn;
	_lEnde = l->lEnde;
	_lMeterOffen = l->lMeterOffen;
	_lObjectIdent = l->lObjectIdent;

	_dKostet = l->dKostetDM;
	_iRechnNr = l->iRechnungsNr;
 // Legende
	if ( l->pcKurzText )
		_pKurzText = StrDuplicat(l->pcKurzText );
	if ( l->pcLangText )
		_pLangText = StrDuplicat(l->pcLangText );
	if ( l->pcComment )
		_pComment = StrDuplicat(l->pcComment );

	if ( l->pcZuordnung )
		_pZuordnung = StrDuplicat(l->pcZuordnung );
	if ( l->pcLeistung )
		_pLeistung = StrDuplicat(l->pcLeistung );

//--------noch Bauwerke-----------------------------------
	_lHoch = l->lHoch;
	_lRechts = l->lRechts;
	_lAnlageNr = l->lAnlageNr;
	_dBauwHoehe = l->dBauwHoehe;
	_dWasserSpDiff = l->dWasserSpDiff;
	
	if ( l->pcBauwerksBezeichnung )
		_pBauwBez = StrDuplicat(l->pcBauwerksBezeichnung );

	if ( l->pcBezeichner1 )
		_pBez1 = StrDuplicat(l->pcBezeichner1 );

	if ( l->pcBezeichner2 )
		_pBez2 = StrDuplicat(l->pcBezeichner2 );

// KK010222 - Trick
// Sortierfolge wird von sequ. Eingabe aus Kompakt(lCount) auf Beginn geändert !!!
// d.h. - Sortierung aufsteigend nach Kilometrierung - Start
	if ( 0L == _lBeginn)
		_lCount = 1;
	else
		_lCount = _lBeginn;


}

KP_LA :: ~KP_LA (void) 
{
	DELETE_OBJ (_pGewNr);
	DELETE_OBJ (_pLeistung);
	DELETE_OBJ (_pZuordnung);
	DELETE_OBJ (_pKurzText);
	DELETE_OBJ (_pLangText);
	DELETE_OBJ (_pComment);

//______BAUWERKE________________

	DELETE_OBJ ( _pBez1);
	DELETE_OBJ ( _pBez2);
	DELETE_OBJ ( _pBauwBez);
}
// Member KP_LA

void KP_LA :: SpeichereObjekt ( long lONr) 
{
	if ( lONr > 0L)
		_lONr = lONr;
}
//----------------------------------------------------------------------
void KP_LA :: SetLinksRechtsMitte ( short iPos)
{
	_iLinksRechtsMitte = Leist_Mitte;
	if (iPos >= Leist_Links && iPos <= Leist_Beide)
	_iLinksRechtsMitte = iPos;

}
//------------------------------------------------------------------------
// Memberfunktionen für KP_LATree ----------------------------------------
KP_LATree :: KP_LATree (void) 
	 : CTree (GetArt, CmpArts)
{
	// nothing else to do
}

KP_LATree :: ~KP_LATree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT KP_LATree :: UserDelete (void *pObj) 
{
	((KP_LA *)pObj) -> KP_LA :: ~KP_LA();
}

// Zugriffsfunktionen auf Baumelemente -------------------------------------
void _XTENSN_EXPORT *GetArt (void *pObj) 
{
	return (void*)& (((KP_LA *)pObj) -> Count());
}

int _XTENSN_EXPORT CmpArts (void *pObj1, void *pObj2) 
{

	long l1 = ((KP_LA *)pObj1) -> Count();
	long l2 = ((KP_LA *)pObj2) -> Count();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
//--------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_IDM -----------------------------------------------
TR_IDM :: TR_IDM (long Ident , short iTyp)
{
	_lIdent = 0L;
	_iTyp = 0;
	_pOBJP = _pOBJLI = _pOBJLIA = _pOBJFI = _pOBJFIA = NULL;
	_lIdent = Ident;
	_iTyp = iTyp;
}
/////////////////////////////////////////////////////////////////////////
TR_IDM :: ~TR_IDM (void) {
	DELETE_OBJ ( _pOBJP);
	DELETE_OBJ ( _pOBJLI);
	DELETE_OBJ ( _pOBJLIA);
	DELETE_OBJ ( _pOBJFI);
	DELETE_OBJ ( _pOBJFIA);
}
//////////////////////////////////////////////////////////////////////////
// Member 
void TR_IDM :: StoreObject(long lONr,Relat iPos)
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_KANTE ) {
			if ( iPos == REL_INN )
				StoreKanteInnen ( lONr);
			else 
				StoreKanteInAus (lONr);
		}

		if ( OS.iObjTyp == OT_PUNKT ) {
				StorePunktInnen(lONr);
		}

		if ( OS.iObjTyp == OT_FLAECHE ) {
			if ( iPos == REL_INN )
				StoreFlaecheInnen ( lONr);
			else 
				StoreFlaecheInAus (lONr);
		}

	}

}
///////////////////////////////////////////////////////////////////////
void TR_IDM :: StoreKanteInnen(long lONr)
{
	if ( !_pOBJLI)
		_pOBJLI = new TR_IDOTree;
	
	CTable t(*_pOBJLI);

	if ( !t.Find ( &lONr) ) {
		TR_IDOCreator OCr ( *_pOBJLI);
		ContCreate ( OCr, TR_IDO ) (lONr);
	}

}
///////////////////////////////////////////////////////////////////////
void TR_IDM :: StoreKanteInAus(long lONr)
{
	if ( !_pOBJLIA)
		_pOBJLIA = new TR_IDOTree;
	
	CTable t(*_pOBJLIA);

	if ( !t.Find ( &lONr) ) {
		TR_IDOCreator OCr ( *_pOBJLIA);
		ContCreate ( OCr, TR_IDO ) (lONr);
	}

}
///////////////////////////////////////////////////////////////////////
void TR_IDM :: StoreFlaecheInnen(long lONr)
{
	if ( !_pOBJFI)
		_pOBJFI = new TR_IDOTree;
	
	CTable t(*_pOBJFI);

	if ( !t.Find ( &lONr) ) {
		TR_IDOCreator OCr ( *_pOBJFI);
		ContCreate ( OCr, TR_IDO ) (lONr);
	}

}
///////////////////////////////////////////////////////////////////////
void TR_IDM :: StoreFlaecheInAus(long lONr)
{
	if ( !_pOBJFIA)
		_pOBJFIA = new TR_IDOTree;
	
	CTable t(*_pOBJFIA);

	if ( !t.Find ( &lONr) ) {
		TR_IDOCreator OCr ( *_pOBJFIA);
		ContCreate ( OCr, TR_IDO ) (lONr);
	}

}
///////////////////////////////////////////////////////////////////////
void TR_IDM :: StorePunktInnen(long lONr)
{
	if ( !_pOBJP)
		_pOBJP = new TR_IDOTree;
	
	CTable t(*_pOBJP);

	if ( !t.Find ( &lONr) ) {
		TR_IDOCreator OCr ( *_pOBJP);
		ContCreate ( OCr, TR_IDO ) (lONr);
	}

}
//////////////////////////////////////////////////////////////////////////
void TR_IDM :: SetTyp(short iTyp)
{
	_iTyp = _iTyp & iTyp;
}
//////////////////////////////////////////////////////////////////////////

// Memberfunktionen für TR_IDMTree -----------------------------------------------
TR_IDMTree :: TR_IDMTree (void) 
	 : CTree (GetIDM, CmpIDMs)
{
	// nothing else to do
}

TR_IDMTree :: ~TR_IDMTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TR_IDMTree :: UserDelete (void *pObj) 
{
	((TR_IDM *)pObj) -> TR_IDM :: ~TR_IDM();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetIDM (void *pObj) 
{
	return (void*)& (((TR_IDM *)pObj) -> Ident());
}

int _XTENSN_EXPORT CmpIDMs (void *pObj1, void *pObj2) 
{
long l1 = ((TR_IDM *)pObj1) -> Ident();
long l2 = ((TR_IDM *)pObj2) -> Ident();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
//--------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_IDO ------------------------------------------------
TR_IDO :: TR_IDO (long lObject)

{
	_lObject = 0L;
	_pIDM = NULL;
	_lObject = lObject;
}

TR_IDO :: ~TR_IDO (void) {
	DELETE_OBJ ( _pIDM);
}
//----------------------------------------------------------------
//////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
// Memberfunktionen für TR_IDOTree ---------------------------------
TR_IDOTree :: TR_IDOTree (void) 
	 : CTree (GetIDO, CmpIDOs)
{
	// nothing else to do
}

TR_IDOTree :: ~TR_IDOTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TR_IDOTree :: UserDelete (void *pObj) 
{
	((TR_IDO *)pObj) -> TR_IDO :: ~TR_IDO();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetIDO (void *pObj) 
{
	return (void*)& (((TR_IDO *)pObj) -> Object());
}

int _XTENSN_EXPORT CmpIDOs (void *pObj1, void *pObj2) 
{
long l1 = ((TR_IDO *)pObj1) -> Object();
long l2 = ((TR_IDO *)pObj2) -> Object();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_OKS ------------------------------------------------
TR_OKS :: TR_OKS (char *pOKS,ulong lIdent)

{
	_pOKS = NULL;
	
	_lIdent1 = 0L;
	_lIdent2 = 0L;

	if ( pOKS) {
		_pOKS = new char [_MAX_PATH];
		if (_pOKS) {
			strcpy(_pOKS,pOKS);
			_lIdent1 = lIdent;
		}
	}

}

TR_OKS :: ~TR_OKS (void) {
	DELETE_OBJ ( _pOKS);
}


//----------------------------------------------------------------
//////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
// Memberfunktionen für TR_OKSTree ---------------------------------
TR_OKSTree :: TR_OKSTree (void) 
	 : CTree (GetOKS, CmpOKSs)
{
	// nothing else to do
}

TR_OKSTree :: ~TR_OKSTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TR_OKSTree :: UserDelete (void *pObj) 
{
	((TR_OKS *)pObj) -> TR_OKS :: ~TR_OKS();
}

// Zugriffsfunktionen auf Baumelemente ----------------------------------------
void _XTENSN_EXPORT *GetOKS (void *pObj) 
{
	return (void*) (((TR_OKS *)pObj) -> OKS());
}

int _XTENSN_EXPORT CmpOKSs (void *pObj1, void *pObj2) 
{
char *p1 = (char *)pObj1;
char *p2 = (char *)pObj2;

	if ( strcmp(p1,p2) < 0 ) return -1;
	if ( strcmp(p1,p2) > 0 ) return 1;

	return 0;
}
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
// Verschiedene Datenquellen
//------------------------------ListContainer-----------------------------

//  DATACL ------------------------------------------------------------
DATACL :: DATACL ( short Typ, char *pLong, char * pShort ,HPROJECT hPr) 
{
	_DATATyp = 0;

	_DATAhPr = hPr;

	_DATALong[0] = NULL;
	_DATAShort[0] = NULL;

	if ( pLong)
		strcat (_DATALong,pLong);

	if ( pShort)
		strcat (_DATAShort,pShort);


	return;
}
DATACL :: ~DATACL ( void ) 
{
}

//  Verwaltung der Daten ObjClass-Liste
//   ---------------------------------------------------------
DATACLList :: DATACLList (void)
	: CListContainer () 
{
	// nothing else to do
}

DATACLList :: ~ DATACLList (void) 
{
	EveryDelete ();
}

void _XTENSN_EXPORT DATACLList :: UserDelete (void *pObj) 
{
	((DATACL *) pObj) -> DATACL :: ~DATACL ();
}

//

///////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// File: GEWBAUM.CXX
