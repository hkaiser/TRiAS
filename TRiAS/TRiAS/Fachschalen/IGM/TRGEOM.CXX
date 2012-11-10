//-----------KOMPAKT-MEMBER : Objektdefinition Trias----------
// File: TRGEOM.CXX


#include "kompp.hxx"
#include "version.h"
#include "kompaktr.h"

#include <shellapi.h>

#include <oleguid.h>
#include <dirisole.h>
// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>


#include "kompdef.h"
#include <xtsnaux.hxx>
#include <initguid.h>
#include <istatus.h>
#include <igeometr.hxx>
#include <hdrentrx.hxx>


#include "triasdef.h"
#include "kompdll.hxx" 
#include "kompwin.hxx"
#include "komphead.hxx"
#include "kompgew.hxx"
#include "gewbaum.hxx"

#include "kpstatus.hxx"

#include "cobjtree.hxx"
#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
void CKompiasExtension :: GewaesserKuerzen ( long lONr, long lDist)
{
	if ( lONr == -1L || lONr == 0L || lDist <= 0L)
		return;

	if (!TesteTRiASObjekt (lONr))
		return;

	CEierUhr Wait (MVWind());
	GEWSTRUKTUR GW;
   	memset (&GW,'\0',sizeof(GEWSTRUKTUR));
	GW.dwSize = sizeof(GEWSTRUKTUR);
	GW.lMCode = m_pKH->CodeGewNr();
	GW.lONr = lONr;
	GW.dDist = (double ) lDist;
	if (!HoleTRiASObjekt(&GW))
		return;
	if (!BildeNeueLaenge (&GW))
		return;
	return;
}
//------------------------------------------------------------
void CKompiasExtension :: GewaesserVerlaengern ( long lONr, long lDist)
{
	if (  lONr == -1L || lONr == 0L || lDist <= 0L)
		return;

	if (!TesteTRiASObjekt (lONr))
		return;

	CEierUhr Wait (MVWind());
	GEWSTRUKTUR GW;
   	memset (&GW,'\0',sizeof(GEWSTRUKTUR));
	GW.dwSize = sizeof(GEWSTRUKTUR);
	GW.lMCode = m_pKH->CodeGewNr();
	GW.lONr = lONr;
	GW.dDist = (double ) lDist;
	if (!HoleTRiASObjekt(&GW))
		return;
	if (!ErweitereLaenge (&GW))
		return;
	return;
}
//------------------------------------------------------------

bool CKompiasExtension :: TesteTRiASObjekt ( long lONr)
{
	if (  lONr == -1L || lONr == 0L )
		return false;

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE) 
		return false;
	}
	if ( OS.lCnt > 0L )
		return true;
	else
		return false;
}
//------------------------------------------------------------------
bool CKompiasExtension :: HoleTRiASObjekt ( GEWSTRUKTUR *p)
{
	if ( !p || p->lONr == 0L || p->lONr == -1L)
		return false;

	if ( !LadeObjektGeometrie ( p->lONr)) {
		MessageBox ( __hWndM,
		 ResString (ResID(IDS_STRKEINOBJEKT, &RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
		MB_ICONSTOP);
		return false;
	}

	// als Anfangspunkt für die Kilometrierung den 1. Stützpunkt, als Endpunkt den letzten
	// Stützpunkt von pIOG vorgeben
	KoOrd *plXK, *plYK;
	long lSPAnz;

	m_pIOG -> GetX ((void**)&plXK);
	m_pIOG -> GetY ((void**)&plYK);
	m_pIOG -> GetCnt (&lSPAnz);

	p->lXA = plXK [0];
	p->lYA = plYK [0];
	p->lXE = plXK [lSPAnz-1];
	p->lYE = plYK [lSPAnz-1];

	return true;

}
//------------------------------------------------------------------
bool CKompiasExtension :: BildeNeueLaenge ( GEWSTRUKTUR *p)
{
    if ( !p || !m_pAbst)
    	return false;
    	

	IObjektGeometrie *pIOG = NULL;

	HRESULT hr = m_pAbst->LinePart ( m_pIOG,p->lXA,p->lYA,p->lXE,p->lYE,p->dDist, &pIOG);

	if (FAILED(hr)) 
		return false;

	bool iFlag = true;

	if (!ModifiziereTRiASObjekt( pIOG))
		iFlag = false;
	
	pIOG->Release();
	return iFlag;
}
//------------------------------------------------------------------------
//-------------------------------------------------------------
bool CKompiasExtension :: ModifiziereTRiASObjekt ( IObjektGeometrie *pIOG)
{
	if ( !pIOG || !m_pIOG)
		return false;
/////////////////////////////////////////////////////////////////////
	KoOrd *plXO, *plYO;
	KoOrd *plXM, *plYM;
	long lSPAnzO;
	long lSPAnzM;

	m_pIOG -> GetCnt (&lSPAnzO);	//STP IST
	pIOG -> GetCnt (&lSPAnzM);	// STP SOLL
	if ( lSPAnzM > lSPAnzO)
		return false;

	m_pIOG -> GetX ((void**)&plXO);
	m_pIOG -> GetY ((void**)&plYO);

	pIOG -> GetX ((void**)&plXM);
	pIOG -> GetY ((void**)&plYM);

	long lDiffK = lSPAnzO - lSPAnzM;

	short Number = 0;
	long lPos = -1;		// Letzter STP


	if ( lDiffK == 0L) {		// Nur letzter STP
		m_pIOG->SubPunkt ( lSPAnzO-1,&Number);
		m_pIOG->AddPunkt( plXM[lSPAnzM-1], plYM[lSPAnzM-1], lPos, Number);
	} else {
		for ( long i = 0; i < lDiffK+1; i++ ) {
			m_pIOG->SubPunkt(lSPAnzO-1-i,&Number);
		}
		m_pIOG->AddPunkt( plXM[lSPAnzM-1], plYM[lSPAnzM-1], lPos, Number);
	}

/////////////////////////////////////////////////////////////////////
	short iFlag = OGModObject;		// Objekt behalten, GI ändern
	m_pIOG->SetFlags(iFlag);

	#if _MSC_VER < 1100
		HRESULT hr = m_pIOG->GeometrieAnTRiAS ( true, NULL);	// Undo
	#else
		ulong lIdent = 0L;
		m_pIOG->GetIdent (&lIdent);
		HPROJECT hPr = DEX_GetObjectsProject(lIdent);
		HRESULT hr = m_pIOG->GeometrieAnTRiASEx (INT_PTR(hPr), true, NULL);
	#endif

	if ( hr != S_OK )
		return false;

	return true;
}
//------------------------------------------------------------------
//-------------------------------------------------------------
bool CKompiasExtension :: ErweitereLaenge ( GEWSTRUKTUR *p)
{
	if ( !p || !m_pIOG)
		return false;

	if (p->dDist <= 0.0)
		return false;

/////////////////////////////////////////////////////////////////////
	KoOrd *plXO, *plYO;
	long lSPAnzO;

	m_pIOG -> GetCnt (&lSPAnzO);	//STP IST

	m_pIOG -> GetX ((void**)&plXO);
	m_pIOG -> GetY ((void**)&plYO);

	CoordTransX *pCT = new CoordTransX;
	if ( !pCT )
		return false;

	double dX1;
	double dY1;

	pCT -> UnScale (plXO[lSPAnzO-1],plYO[lSPAnzO-1] , &dX1, &dY1);	// DB-Koordinaten in ASC-Format transformieren


	long lDX = plXO[lSPAnzO-1] - plXO[lSPAnzO-2];
	long lDY = plYO[lSPAnzO-1] - plYO[lSPAnzO-2];


	// Neu : Nullstellen beachten !!!
	double M;
	double MQ;
	double DQ = p->dDist * p->dDist;
	double X;
	double Y;
	long XN;
	long YN;

	if ( lDY != 0.0 && lDX != 0.0 ) {

		M = (double)lDY / (double)lDX;	//Anstieg

///////////////////////////////////////////////////////

		MQ = ( 1.0 +M*M);
	
		X = sqrt ( DQ /  MQ );

		if (lDX < 0L)
			X = -X;

		Y = M * X;

	/////////////////////// UmrechnungsFaktor einsetzen
	/////////////////////// KorrigiereLaenge
		DoublePair WP = KorrigiereLaenge(plXO[lSPAnzO-1] ,plXO[lSPAnzO-2],
			plYO[lSPAnzO-1] ,plYO[lSPAnzO-2]);
	///////////////////////////////////////////////////////
		if ( WP.X() == 0.0 && WP.Y() == 0.0 )
			return false;

		X = X * WP.X();
		Y = Y * WP.Y();
	
		X = X + 0.5;
		Y = Y + 0.5;

		XN = plXO[lSPAnzO-1] + (long) X;
		YN = plYO[lSPAnzO-1] + (long) Y;

	} else {

		if ( lDX == 0.0 ) {
			dY1 = dY1 + p->dDist;
		}
		if ( lDY == 0.0 ) {
			dX1 = dX1 + p->dDist;
		}

		pCT -> Scale ( dX1, dY1, &XN, &YN);	// DB-Koordinaten in ASC-Format transformieren
		
	}

	short Number = 0;
	long lPos = -1;

	HRESULT hra = m_pIOG->AddPunkt( XN, YN, lPos, Number);

/////////////////////////////////////////////////////////////////////

	short iFlag = OGModObject;		// Objekt behalten, GI ändern
	m_pIOG->SetFlags(iFlag);

	UnRegisterNotification(DEX_OBJECTCHANGED);
	#if _MSC_VER < 1100
		HRESULT hr = m_pIOG->GeometrieAnTRiAS ( true, NULL);	// Undo
	#else
		ulong lIdent = 0L;
		m_pIOG->GetIdent (&lIdent);
		HPROJECT hPr = DEX_GetObjectsProject(lIdent);
		HRESULT hr = m_pIOG->GeometrieAnTRiASEx (INT_PTR(hPr), true, NULL);
	#endif
	RegisterNotification(DEX_OBJECTCHANGED);
	if ( hr != S_OK )
		return false;
	
	return true;
}
/////////////////////////////////////////////////////////////////////
DoublePair CKompiasExtension :: KorrigiereLaenge ( long lXa, long lXe, long lYa, long lYe)
{

	double dUFX = 0.0;
	double dUFY = 0.0;	// Umrechnungsfaktor in x- bzw. y-Richtung

	CoordTransX *pCTF = new CoordTransX;
	if ( !pCTF )
		return DoublePair (dUFX, dUFY);

	if ( lXa < 0L || lXe < 0L || lYa < 0L || lYe < 0L)
		return DoublePair (dUFX, dUFY);

	Punkt P1,P2;

#if _MSC_VER >= 1100
	HRESULT hr = P1.SetX(lXa);
	hr = P2.SetX(lXe);
	hr = P1.SetY(lYa);
	hr = P2.SetY(lYe);
#else
	P1.X() = lXa;
	P2.X() = lXe;
	P1.Y() = lYa;
	P2.Y() = lYe;
#endif

	return UmrechnungsFaktor ( P1, P2, pCTF);

}

///////////////////////////////////////////////////////////////////
//------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////
//-----TRGEOM.CXX
//////////////////////////////////////////////////////////////////////
