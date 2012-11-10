/*
DGEO_OBJ.CPP -

beinhaltet allgemeine Klasse für den DXF-Import.

Erarbeitet : J. Benkenstein		Stand vom 21. August 1995
								Erweitert am 5. Mai 1998
*/

#include "pheader.hpp"

#include "dxfimp.h"				//	Ressource-Konstanten

#include <new>

// #HK960812
	#include <math.h>		  	// für sin, cos u.a.
	#include <float.h>		  	// für DBL_MAX
	#include <assert.h>			// assert ()	

#include "tools.hpp"		  	// TRIAS-Ausgabe	
#include "punktli.hpp"	  	  	// PunktListe
#include "tmerkmal.hpp"	  	  	// zugeh. TextMerkmalsListe
#include "merkmal.hpp"		  	// MerkmalsBaum	
#include "bogen.hpp"		  	// GetBogenparam ()	
#include "optparam.hpp" 		// OptParam
#include "block.hpp"			// CBlockTree

#include "dgeo_obj.hpp"	 	  	// zugeh. Header-File

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

//	Konstanten
const char MerkmalsSeparator [] = ":";		
const char WinkelFormat [] = "%.2lf";

// externe Variablen
extern Params OptParams;  		// opt. Paramter-Objekt
extern MerkmalsBaum *g_pMB;		// Merkmals-Beschreibungs-Baum
extern char CommentBuffer [];	// Puffer für akt. Kommentar	
extern CBlockTree *g_pBlockTree;	//	Blockbaum

// externe Funktionen
extern void yyerror (short);
extern void IncCounter (long ObjNr = 0);
char *DtoA (double Val, char *pBuffer, char *pFormat = NULL);

// DGeoObj --------------------------------------------------------------
DGeoObj :: DGeoObj ()
{ 
	_ID = 0; 
	_DGT = DGT_Unknown; 
	_pPL = NULL; 
	_BogenParam = 0.0; 
	_pTML = NULL; 
	m_dWinkel = 0.0;
	m_lExpectedVertices = 0;
}

DGeoObj :: ~DGeoObj (void)
{
	DELETE_OBJ (_pTML);
	DELETE_OBJ (_pPL);
}

//	operatoren
Bool DGeoObj :: operator = (const DGeoObj &Obj)
{
	try
	{
	//	prüfe Parameter
		assert (&Obj != this);
		if (&Obj == this)	
		{
			yyerror (IDS_SYSERROR);
			return False;
		}

	//	Werte umkopieren
		_DGT = Obj._DGT;					// Typ
		_ID = Obj._ID;						// Identifikator
		_BogenParam = Obj._BogenParam;		// BogenParameter bei Vertex-Elementen	
		m_lExpectedVertices = Obj.m_lExpectedVertices;

	//	Symbol-oder Textdrehwinkel				
		m_dWinkel = Obj.m_dWinkel;
		
	//	neue Liste erzeugen			
		if (!_pTML)
			_pTML = new TextMerkmalsListe;
			
	//	Liste umkopieren
		if (Obj._pTML)
		{
			if (!(*_pTML = *Obj._pTML))
				return False;
		}			

	//	Punktliste
	//	prüfe neue Liste
		assert (Obj._pPL);
		if (!Obj._pPL)
		{
			yyerror (IDS_SYSERROR);
			return False;
		}

	//	GeoListe umkopieren
		if (!_pPL)
			_pPL = new PunktListe;
		if (!(*_pPL = *Obj._pPL))
			return False;
		
		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return FALSE;
}

Bool DGeoObj :: Init (DGeoTyp DGT, char *pLayerName, long lExpectedVertices)
{
	try {
	//	prüfe Parameter
		if (!pLayerName)
		{
			yyerror (IDS_SYSERROR);
			return False;		
		}	

	//	Typ prüfen
		assert ((DGT >= DGT_Linie) && (DGT <= DGT_Punkt));
		_DGT = DGT;

	//	Punktliste erzeugen
		_pPL = new PunktListe ();
		m_lExpectedVertices = lExpectedVertices;

	//	bei ungültigem LayerNamen	
		if (!*pLayerName)
		{
			_ID = StandardID;
			ResString strStandard (ResID (IDS_ST_ID_KT, &g_pTE -> RF ()), 20);
			CreateIdent (_ID, (char *) strStandard.Addr ());
		}
		else
		{
			if (OptParams.bAnsiiText)	
				OemToAnsi (pLayerName, pLayerName);
	#ifdef WIN32

		#if _MSC_VER < 1100
			if ((_ID = DEX_GetIdentFromClassNameCI (pLayerName)) <= 0)
		#else
			HPROJECT hPr = DEX_GetDataSourceHandle();
			if ((_ID = DEX_GetIdentFromClassNameCIEx (hPr,pLayerName)) <= 0)
		#endif

	#else
			if ((_ID = DEX_GetIdentFromClassName (pLayerName)) <= 0)
	#endif
			{
		#if _MSC_VER < 1100
				_ID = DEX_GetUniqueICode ();
		#else
				_ID = DEX_GetUniqueICodeEx (hPr);
		#endif
				CreateIdent (_ID, pLayerName);
			}
		}

		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return FALSE;
}

//	anormale Init.
Bool DGeoObj ::Init (DGeoTyp DGT, long lIdent, TextMerkmalsListe *pListe)
{
	try
	{
	//	Typ prüfen
		assert ((DGT >= DGT_Linie) && (DGT <= DGT_Punkt));
		_DGT = DGT;
		m_lExpectedVertices = 0;

	//	Ident prüfen
		assert (lIdent != 0);
		_ID = lIdent;

	//	Merkmalsliste übergeben ?
		if (pListe)
		{
		//	ggf. Liste erzeugen
			if (!_pTML)
				_pTML = new TextMerkmalsListe;
		
		//	Liste anhängen
			if (!(*_pTML += *pListe))
				return False;
		}

	//	Punktliste erzeugen
		_pPL = new PunktListe ();

		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return FALSE;
}

// Ausgabe von Geometrie und Merkmalen: mit ObjNr != 0 zurück
long DGeoObj :: Output (char *pVal /*=NULL*/) 
{
	try
	{
	//	prüfe Parameter
		if (!_pPL || !_pPL -> Count ())
		{
			yyerror (IDS_SYSERROR);
			return 0;
		}

		if (0 != m_lExpectedVertices && m_lExpectedVertices != _pPL -> Count())
		{
			yyerror (IDS_SYSERROR);
			return 0;
		}

	//	Speicher anlegen
		double *pX = NULL;
		double *pY = NULL;
		long lCnt = _pPL -> Count ();

		pX = new double [lCnt];
		pY = new double [lCnt];

	//	Geometrie in Speicher ausgeben
		long ObjNr = 0;
		if (_pPL -> OutPunkte (pX, pY))
		{
		//	Geometrie an TRiAS ausgeben
			switch (_DGT) 
			{	
				case DGT_Symbol:
				case DGT_Punkt:
				{
					ObjNr = OutputPunktLinie (pX, pY, _ID);
					if ((0 != ObjNr) && (0 != m_dWinkel))
					{
						char Buffer10 [10] = "";
						DtoA (Buffer10, (char*) WinkelFormat, m_dWinkel);
						if (EC_OKAY != OutputMerkmal (ObjNr, OptParams.m_ulSymWinkel, 
													  Buffer10))
							ObjNr = 0;
					}
				}
				break;
				case DGT_Flaeche:
					if (_pPL -> isFlaeche ())
						ObjNr = OutputFlaeche (pX, pY, lCnt, _ID);
					else		
						ObjNr = OutputPunktLinie (pX, pY, _ID, lCnt, False);												  	
				break;
				case DGT_Linie:
					if (OptParams.bCloseLine && _pPL -> isFlaeche ())
						ObjNr = OutputFlaeche (pX, pY, lCnt, _ID);
					else		
						ObjNr = OutputPunktLinie (pX, pY, _ID, lCnt, False);												  		
				break;
				case DGT_Text:
					ObjNr = OutputText (pVal, *pX, *pY, _ID);
				break;
				default:
				{
					yyerror (IDS_SYSERROR);
//					return EC_OKAY;			//	weiter parsen = 0
					return 0;
				}
			}
		}
		
	//	Speicher freigeben
		DELETE_VEC (pX);
		DELETE_VEC (pY);

// KK991009
		if ((ObjNr == 0) || (ObjNr == -1)) {
//			return 0;
			return ObjNr;
		}
	//	ggf. Merkmale des Ojekts ausgeben
		if (OptParams.bImpMerkmale && (ObjNr != 0))
		{
			if (_pTML && g_pMB)	 // prüfe interne Parameter
				ObjNr = g_pMB -> OutputMerkmale (ObjNr, _pTML) ? ObjNr : -1;				
		}

	//	ggf. Kommentar ausgeben
		ErrCode ec = EC_OKAY;
		if ((ObjNr != -1) && OptParams.m_bImpComment && (CommentBuffer [0] != '\0'))
		{
			ec = OutputMerkmal (ObjNr, OptParams.m_ulComment, CommentBuffer);
			if (EC_OKAY != ec)
				return -1;
		}
		CommentBuffer [0] = '\0';		//	alten Puffer leeren

		return ObjNr;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return -1;
}

//	Objekt transformiert ausgeben
long DGeoObj :: OutputExt (long lIdent,							//	Identifikator
						   TextMerkmalsListe *pListe,			//	Merkmalsliste
						   double dXBasis, double dYBasis,		//	Blockbasispunkt
						   double dXInsert, double dYInsert,	//	Einfügepunkt
						   double dXMasstab, double dYMasstab,	//	Maßstab
						   double dDrehWinkel,					//	Drehwinkel
						   double dXOffset, double dYOffset,	//	zusätz. Verschiebung
						   CDGeoObjListe *pGeoListe)			//	an Liste anhängen 
{
//	prüfe Parameter
	long lObjNr = 0L; 

	assert ((lIdent != 0) && _pPL);
	if ((lIdent == 0) || (!_pPL))
	{
		yyerror (IDS_PARAM_ERROR);
		return lObjNr;
	}

//	setze Ident
	_ID = lIdent;

//	führe Koordinaten-Transformation durch
	PunktListe *pNewPL = _pPL->Transform (dXBasis, dYBasis,
										  dXInsert, dYInsert, 
										  dXMasstab, dYMasstab, 
										  dDrehWinkel,
										  dXOffset, dYOffset);
	if (!pNewPL)
		return lObjNr;

//	Zeiger vertauschen
	PunktListe *pOldPL = _pPL;		//	Zeiger auf alte Liste speichern
	_pPL = pNewPL;

//	ggf. Drehwinkel berücksichtigen
	m_dWinkel += dDrehWinkel;

//	ggf. Objekt erstellen und an GeoListe ausgeben
	if (pGeoListe)
	{
		DGeoObj *pObj = NULL;

		try
		{
		//	zusätzl. Merkmale speichern
			if (pListe)
			{
				if (!_pTML)
					_pTML = new TextMerkmalsListe;
					
				if (!(*_pTML += *pListe))
					throw bad_alloc ();
			}

		//	neues Objekt erzeugen
			if (DGT_Text == _DGT)
			{
				CTextObject *pTObj = new CTextObject;
				if (!(*pTObj = (CTextObject&)*this))
					throw bad_alloc ();
				pObj = pTObj;
			}
			else
			{
				pObj = new DGeoObj;
				if (!(*pObj = *this))
					throw bad_alloc ();
			}

		//	Zeiger wieder zurücksetzen
			_pPL = pOldPL;
			DELETE_OBJ (pNewPL);

			return pGeoListe->AddObject (pObj);
		}
		catch (bad_alloc)
		{
		//	Zeiger wieder zurücksetzen
			_pPL = pOldPL;
			DELETE_OBJ (pNewPL);

			DELETE_OBJ (pObj);
			yyerror (IDS_NOMEMORY);
		}
		return lObjNr;
	}

//	Objekt an Trias ausgeben
	lObjNr = Output ();

//	Zeiger wieder zurücksetzen
	_pPL = pOldPL;
	DELETE_OBJ (pNewPL);

//	prüfe Ausgabeergebnis
//	KK991011
	if (0 == lObjNr || -1 == lObjNr)
//		return lObjNr;
		return 0;
	
//	ggf. zusätzlichen Merkmale ausgeben
	if (OptParams.bImpMerkmale)
	{
		assert (g_pMB);
		if (pListe && g_pMB)	 // prüfe interne Parameter
			lObjNr = g_pMB -> OutputMerkmale (lObjNr, pListe) ? lObjNr : 0;				
	}

	return lObjNr;
}

// neuen Punkt über seine Koordinaten in Liste aufnehmen
Bool DGeoObj :: AddPunkt (double X, double Y)
{
	if (!_pPL)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

	if (_pPL -> AddPunkt (X, Y)) 
		return True;

	return False;
}

// neuen Punkt über seine Referenz in Liste aufnehmen
Bool DGeoObj :: AddPunkt (Punkt *pPt)
{
	if (!pPt || !_pPL)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

	if (_pPL -> AddPunkt (pPt)) 
		return True;

	return False;
}

// den 1. Punkt der Punktliste an das aktuelle Ende dieser kopieren
Bool DGeoObj :: AddFirstPunkt (double dAusBuchtung)
{
	if (!_pPL)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

	double Xl, Yl = 0;
	if (!_pPL -> GetFirstPunkt (Xl, Yl))
		return False;

	if (dAusBuchtung)
		return AddBogen (Xl, Yl, dAusBuchtung);
	else
		return AddPunkt (Xl, Yl);
}

Bool DGeoObj :: AddMerkmal (char *pMName, char *pMValue)
{
//	prüfe interne Parameter
	if (!_pTML || !pMName || !pMValue)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

	return _pTML -> AddMerkmal (pMName, pMValue);
}

// Kreis/Kreisbogen über seine Parameter durch einen Polygonzug
// approximieren (4 Grad) und in PunktListe speichern,
// Funktion bricht Programm ab, wenn kein dyn. Speicher mehr vorhanden
// Bogen am Vertex
Bool DGeoObj :: MakeBogenPolygon (double Radius, double Xm, double Ym,
							 	  double StartWi, double StopWi, Bool Richtung)
{
	double Pi = 2.0 * asin (1.0);
	double ApprWi = (4.0 * Pi) / 180.0;

//	Approx. durchführen
	if (Richtung)  //	math. pos. Drehsinn
	{
		for (; StartWi < StopWi; StartWi += ApprWi)
		{
			if (! AddPunkt (Xm + Radius * cos (StartWi),
							Ym + Radius * sin (StartWi)))
				return False;			
		}
	}
	else
	{
		for (; StartWi > StopWi; StartWi -= ApprWi)
		{
			if (! AddPunkt (Xm + Radius * cos (StartWi),
							Ym + Radius * sin (StartWi)))
				return False;			
		}		
	}
	return True;
}

//	erzeuge Bogen zum letzten Punkt	
Bool DGeoObj :: AddBogen (double P2x, double P2y, double NewBogenParam)
{
//	return AddPunkt (P2x, P2y);

//	prüfe interne Parameter
	if (!_pPL)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}	

//	prüfe übergebene Parameter
	if (!_BogenParam)	
	{
		_BogenParam = NewBogenParam;		// neuen Bogen-Parameter merken
		return AddPunkt (P2x, P2y);
	}

//	letzten Punkt holen
	double P1x, P1y = 0;
	if (! _pPL -> GetLastPunkt (P1x, P1y))
		return False;

	Bool bRet = True;
	Bool Richtung = _BogenParam > 0 ? True : False;	// math. Drehsinn
	double Winkel = 4.0 * atan (_BogenParam);
	_BogenParam = NewBogenParam;		// neuen Bogen-Parameter merken				
	double Xm, Ym, StartWi, StopWi, Radius = 0;
	if (GetBogenParam (P1x, P1y, P2x, P2y, Winkel, Xm, Ym, Radius, 
					   StartWi, StopWi))
		bRet = MakeBogenPolygon (Radius, Xm, Ym, StartWi, StopWi, Richtung);

	return bRet ? AddPunkt (P2x, P2y) : False;
}

// Kreis/Kreisbogen über seine Parameter durch einen Polygonzug
// approximieren (4 Grad) und in PunktListe speichern,
// Funktion bricht Programm ab, wenn kein dyn. Speicher mehr vorhanden
Bool DGeoObj :: MakePolygon (double Radius, double Xm, double Ym,
							 double StartWi, double StopWi)
{
	double Pi = 2.0 * asin (1.0);
	double ApprWi = (4.0 * Pi) / 180.0;

//	Winkel ggf. korrigieren
	if (StartWi > StopWi)
		StopWi += 360.0;

//	Winkel in Bogenmaß konvertieren
	StartWi = (StartWi * Pi) / 180.0;
	StopWi = (StopWi * Pi) / 180.0;		

// 	Approximation durchführen
	for (; StartWi <= StopWi; StartWi += ApprWi) 
	{
		if (! AddPunkt (Xm + Radius * cos (StartWi),
						Ym + Radius * sin (StartWi)))
			return False;
	}

//	letzten Punkt ggf. ergänzen
	if (StartWi != StopWi) 	// beim Kreisbogen
	{
		if (! AddPunkt (Xm + Radius * cos (StopWi),
					    Ym + Radius * sin (StopWi)))
			return False;							
	}

	return True;
}

// CTextObject ----------------------------------------------------------------
CTextObject :: CTextObject ()
{
	m_pHoehe = m_pText = NULL;
}

CTextObject :: ~CTextObject (void)
{
	DELETE_VEC (m_pText);
	DELETE_VEC (m_pHoehe);
}

Bool CTextObject :: Init (DGeoTyp DGT, char *pLayerName, long lExpectedVertices)
{
//	prüfe Parameter
	assert (DGT_Text == DGT);

//	Basisklasse rufen
	return DGeoObj :: Init (DGT_Text, pLayerName, lExpectedVertices);
}

Bool CTextObject :: operator = (const CTextObject &Obj)
{
	try
	{			
	//	zuerst Basisklasse rufen
		if (!DGeoObj::operator=(Obj))
			return False;
	
	//	Texthöhe
		DELETE_VEC (m_pHoehe);		
		if (Obj.m_pHoehe && *Obj.m_pHoehe)
		{
			m_pHoehe = new char [strlen (Obj.m_pHoehe) + 1];
			strcpy (m_pHoehe, Obj.m_pHoehe);
		}

	//	TextWert
		DELETE_VEC (m_pText);		
		if (Obj.m_pText && *Obj.m_pText)
		{
			m_pText = new char [strlen (Obj.m_pText) + 1];
			strcpy (m_pText, Obj.m_pText);
		}

		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return FALSE;
}

//	Textwert speichern
Bool CTextObject :: SetText (char *pText)
{
	try
	{
		if (!pText)
			return False;
		
// KK020508
//	keinen leeren Text speichern
//		if (!*pText)
//			return True;

		if ( !*pText) {
			m_pText = new char [strlen (pText) + 2];
			strcpy (m_pText, "?");
			yyerror (IDS_NOTEXTFIELD);
		} else {
			m_pText = new char [strlen (pText) + 1];
			strcpy (m_pText, pText);
		}

		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}
	
	return False;
}

//	Höhe speichern
Bool CTextObject :: SetHoehe (char *pText)
{
	try
	{
		if (!pText)
			return False;

	//	keinen leeren Text speichern
		if (!*pText)
			return True;

		m_pHoehe = new char [strlen (pText) + 1];
		strcpy (m_pHoehe, pText);
		SetTwoDec (m_pHoehe);
		
		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return False;
}

//	Text an Trias ausgeben
long CTextObject :: Output (char *pVal)
{
//	prüfe notwendige Parameter
	if (!m_pText || !*m_pText)
		return EC_OKAY;			

//	Basisklasse rufen
	long lObjNr = DGeoObj::Output (m_pText);
	
//	weitere Parameter ggf. ausgeben: Hoehe und Winkel	
	if (0 != lObjNr)
	{
		ErrCode ec = EC_OKAY;
		if (OptParams.m_bImpTextHoehe && m_pHoehe && *m_pHoehe)
		{
			ec = OutputMerkmal (lObjNr, OptParams.m_ulTextHoehe, m_pHoehe);
			if (EC_OKAY != ec)				
				return ec;
		}

		if (OptParams.m_bImpTextDrehWi && (0 != m_dWinkel))
		{
			char Buffer10 [10] = "";
			DtoA (Buffer10, (char *)WinkelFormat, m_dWinkel);			
			ec = OutputMerkmal (lObjNr, OptParams.m_ulTextWinkel, Buffer10);
			if (EC_OKAY != ec)
				return ec;
		}
	}
	CommentBuffer [0] = '\0';		//	alten Puffer leeren
	
	return lObjNr;
}

//	CSymbolObject -------------------------------------------------------------
CSymbolObject :: CSymbolObject ()
{
	m_pBlockName = NULL;
	m_dXInsert = m_dYInsert = 0;
	m_dXMasstab = m_dYMasstab = 1.0;
	m_iZeilen = m_iSpalten = 1;
	m_dZeilenAbstand = m_dSpaltenAbstand = 0;
}

CSymbolObject :: ~CSymbolObject ()
{
	DELETE_VEC (m_pBlockName);
}

Bool CSymbolObject :: operator = (const CSymbolObject &Obj)
{
	try
	{			
	//	zuerst Basisklasse rufen
		if (!DGeoObj::operator=(Obj))
			return False;
		
	//	zuerst Blocknamen speichern
		DELETE_VEC (m_pBlockName);			//	alten Namen löschen
		assert (Obj.m_pBlockName && *Obj.m_pBlockName);
		if (!Obj.m_pBlockName || !*Obj.m_pBlockName)
		{
			yyerror (IDS_SYSERROR);
			return False;
		}

	//	Namen umkopieren
		m_pBlockName = new char [strlen (Obj.m_pBlockName) + 1];
		strcpy (m_pBlockName, Obj.m_pBlockName);
		
		m_dXInsert = Obj.m_dXInsert;
		m_dYInsert = Obj.m_dYInsert;
		m_dXMasstab = Obj.m_dXMasstab; 
		m_dYMasstab = Obj.m_dYMasstab;
		m_iZeilen = Obj.m_iZeilen;
		m_iSpalten = Obj.m_iSpalten;
		m_dZeilenAbstand = Obj.m_dZeilenAbstand;
		m_dSpaltenAbstand = Obj.m_dSpaltenAbstand;

		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return FALSE;
}

//	Typ und LayerName übergeben
Bool CSymbolObject :: Init (DGeoTyp DGT, char *pLayerName, long lExpectedVertices)
{
	try
	{
		assert (DGT_Symbol == DGT);

	//	zuerst Basisklasse rufen	
		if (!DGeoObj::Init (DGT_Symbol, pLayerName, lExpectedVertices))
			return False;

	//	ggf. Merkmalsliste anlegen
		if (OptParams.bImpMerkmale)
			_pTML = new TextMerkmalsListe;
		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return False;
}

//	Blocknamen speichern
Bool CSymbolObject :: SetBlockName (char *pBlockName)
{
	try
	{
	//	prüfe interne Parameter
		assert (NULL == m_pBlockName);		//	sollte nicht passieren !!!
		DELETE_VEC (m_pBlockName);			//	zur Sicherheit löschen

	//	prüfe übergebene Parameter
		if (!pBlockName || !*pBlockName)
			return False;

	//	ggf. konvertieren
		if (OptParams.bAnsiiText)		
			OemToAnsi (pBlockName, pBlockName);

		m_pBlockName = new char [strlen (pBlockName) + 1];
		strcpy (m_pBlockName, pBlockName);

	//	ggf. Blocknamen auch als Merkmal speichern
		if (_pTML)
		{
		//	vollst. Blocknamen zusammenbauen
			char *pMerkmal = new char [strlen (OptParams.pFileName) +
									   strlen (m_pBlockName) + 2];
			strcpy (pMerkmal, OptParams.pFileName);
			strcat (pMerkmal, MerkmalsSeparator);
			strcat (pMerkmal, m_pBlockName);

		//	Merkmals-Bezeichung laden
			ResString strBlockName (ResID (IDS_BLOCK_NAME, &g_pTE -> RF ()), 20);

		//	Merkmal speichern
			if (!_pTML -> AddMerkmal ((char *)strBlockName.Addr(), pMerkmal, False))
				return False;

			DELETE_VEC (pMerkmal);
		}			

		return TRUE;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}
	return False;
}

//	Geometrie und Merkmale des Blocks an TRiAS ausgeben
long CSymbolObject :: Output (char *pVal)
{
//	der Blockmanager übernimmt hier die Ausgabe der zugeh. Entities
	assert (g_pBlockTree);
	return g_pBlockTree->Output(this) ? 1 : 0;
}

// CDGeoObjPtr ----------------------------------------------------------------
CDGeoObjPtr :: CDGeoObjPtr ()
{
	m_pDGeoObj = NULL;
}

CDGeoObjPtr :: ~CDGeoObjPtr ()
{
	assert (m_pDGeoObj);
	DELETE_OBJ (m_pDGeoObj);
}

Bool CDGeoObjPtr :: Init (DGeoObj*& pObj)
{
	assert (pObj);

	if (pObj)
	{
		m_pDGeoObj = pObj;
		pObj = NULL;			
		return True;
	}

	yyerror (IDS_PARAM_ERROR);
	return False;
}

// CDGeoObjListe --------------------------------------------------------------
CDGeoObjListe :: CDGeoObjListe ()
{
//	nothing to do
}

CDGeoObjListe :: ~CDGeoObjListe ()
{
	EveryDelete ();
}

void CDGeoObjListe :: UserDelete (void *pObj)
{
	((CDGeoObjPtr *) pObj) -> ~CDGeoObjPtr ();
}

Bool CDGeoObjListe :: AddObject (DGeoObj*& pObj)
{
	try
	{
	//	prüfe Parameter
		assert (pObj);
		if (!pObj)
		{
			yyerror (IDS_PARAM_ERROR);
			return False;
		}

	//	Zeiger speichern
		CDGeoObjPtrCreator Cr (*this);
		CDGeoObjPtr *pObjPtr = ContCreate (Cr, CDGeoObjPtr);
		return (pObjPtr && pObjPtr -> Init (pObj));
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return False;
}

BOOL CDGeoObjListe :: AddObject (const DGeoObj& GeoObj)
{
	try
	{
		DGeoObj *pObj = new DGeoObj;
		if (!(*pObj = GeoObj))
		{
			DELETE_OBJ (pObj);
			return False;
		}
			
		return AddObject (pObj);
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return False;
}
