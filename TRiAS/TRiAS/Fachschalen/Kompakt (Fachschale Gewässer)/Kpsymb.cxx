//-----------KOMPAKT-MEMBER : Symboldefinition Kompakt/Trias----------
// File: KPSYMB.CXX


#include "kompp.hxx"

#include <shellapi.h>


//#include <triastlb_i.c>
#include <triastlb.h>

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
#include "triasdef.h"

#include "kompdll.hxx" 
#include "kompwin.hxx"
#include "komphead.hxx"
#include "kompgew.hxx"
#include "gewbaum.hxx"

#include "kpstatus.hxx"

#include "version.h"
#include "kompias.h"
#include "about.h"

#include "about.hxx"
#include "cobjtree.hxx"
#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
bool CKompiasExtension :: ObjektBearbeitung (bool fGenerate, HWND hWnd)
{

	long lCount = 0L;

	DEXOR_SelectedObjectsCount ( hWnd , &lCount);
	if ( lCount <= 0L)
		return false;

	long * pObj = new long [ lCount + 1 ];
	*pObj = 0L;

	ENUMLONGKEY ENL;
	ENL.eFcn = ( ENUMLONGKEYPROC ) SelektierteObjekte;
	ENL.eKey = (long ) (void *)hWnd;

	ENL.ePtr = pObj;
	DEX_EnumSelectedObjects (ENL);
	if ( *pObj == 0L) {
		DELETE_OBJ ( pObj);
		return false;
	}
	
	for ( long i = 0L; i < *pObj; i++) {
		long lONr = *(pObj+i+1);
		if ( !ObjektIstGewaesser (lONr))
			continue;
		if ( fGenerate)
			GewaesserParameter(lONr);
		else
			GewaesserUmkehr(lONr);
	}

	DELETE_OBJ ( pObj);
	return true;
}
//------------------------------------------------------------
bool CKompiasExtension :: GewaesserParameter (long lONr)
{

	if ( !LadeObjektGeometrie ( lONr)) {
		MessageBox ( __hWndM,
		 ResString (ResID(IDS_STRKEINOBJEKT, &RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
		MB_ICONSTOP);
		return false;
	}

	// als Anfangspunkt für den 1. Stützpunkt, als Endpunkt den letzten
	// Stützpunkt von pIOG vorgeben
	KoOrd *plXK, *plYK;
	long lSPAnz;

	m_pIOG -> GetX ((void**)&plXK);
	m_pIOG -> GetY ((void**)&plYK);
	m_pIOG -> GetCnt (&lSPAnz);

// Gewaesser allgemein
	long lGXA = plXK [0];
	long lGYA = plYK [0];
	long lGXE = plXK [lSPAnz-1];
	long lGYE = plYK [lSPAnz-1];

	long lStart = ObjektStartPunkt(lONr,m_pKH->CodeBauwAnfStat());
	long lEnde = LinienLaenge (lONr)+lStart;

// Alt
//	long lStart = 0L;

	long lIdent = DEX_GetObjIdent ( lONr);

	if (isCloned(lONr)) {
		lStart = StartWertClone(lONr,m_pKH->CodeBauwAnfStat());
		lEnde = EndeWertClone(lONr,m_pKH->CodeBauwEndStat());
	}

	m_lONrStart = BildeTextObjekt (lIdent,lStart,&lGXA,&lGYA);

	m_lONrEnde = BildeTextObjekt (lIdent,lEnde,&lGXE,&lGYE);

	m_lONrVis = lONr;

	CTextLaden (lONr,m_lONrStart, m_lONrEnde);

	LinienVisualisierung ( lONr);

	return true;
}
//------------------------------------------------------------
long CKompiasExtension :: BildeTextObjekt (long lIdent,long lPos,long *pX,long *pY)
{

	long lONr = 0L;
	long lCnt = 1L;

	OBJGEOMETRIE OG;
	memset (&OG,'\0',sizeof(OBJGEOMETRIE));
	OG.dwSize = sizeof(OBJGEOMETRIE);
	OG.lIdent = lIdent;
	OG.lONr = lONr;
	OG.lCnt = lCnt;
	OG.iObjTyp = OT_TEXT;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.iFlags = OGNewObject;

//  Object an TRIAS ausgeben      
#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( !DEX_ModObjGeometrieEx (hPr,OG)) 
#else
	if ( !DEX_ModObjGeometrie (OG)) 
#endif
		return -1;

//-------Neue ON merken !!!
	lONr = OG.lONr;

	SpeichereText(lONr,lPos);

	ulong lMCode = GetClonedCode(lONr);
	if ( 0L != lMCode ) {
		SetObjektCloned(lONr,lMCode);
	}
	return lONr;
}
//------------------------------------------------------------------
bool CKompiasExtension :: SpeichereText ( long lONr,long lPos)
{

	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return false;

	wsprintf ( pBuff,"%ld",lPos);
	

// Wegschreiben eines neuen Textes für ein Textobjekt (DEX_PUTTEXTOBJECTTEXT)
	PUTTEXTDATA PTD;
	PTD.dwSize = sizeof(PUTTEXTDATA);
	PTD.m_lONr = lONr;
	PTD.m_pcText = pBuff;

	DEX_PutTextObjectText ( PTD );

	DELETE_OBJ ( pBuff);
	return true;

}
//////////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: LinienVisualisierung ( long lONr)
{
// Basic hilf mir
	_DGeoObject *pIObj = NULL;

	if ( GetGeoObjectFromONr (lONr,&pIObj)) {

		ebPARAM PA[2];

		PA[0].wType = 0;
		PA[0].szExtType[0] = '\0';

		PA[1].wType = TYP_APPOBJECT;
		strcpy (PA[1].szExtType, "GeoObject");

		LPVOID pTyp = NULL;

		LPVOID pVals[2] = { NULL, &pIObj };

		BSPARAM BS;
		BS.pTypes = PA;
		BS.pValues = pVals;

		if ( m_pScript) 
			m_pScript->RunCode(g_hInstance,IDR_SCRIPTCOL,"COLOR",1,&BS);

		pIObj->Release();
		return true;
	}
	return false;

}
//////////////////////////////////////////////////////////////////
bool CKompiasExtension :: GetGeoObjectFromONr( long lONr, _DGeoObject **ppIObj)
{
	if ( !m_pDoc)
		LadeBasicDocument();

	if ( !m_pDoc )
		return false;


// 3. Vom aktiven Dokument ein konkretes Objekt geben lassen
	CComVariant vONr;
	CComVariant vMode;

	V_VT(&vONr) = VT_I4;		// ObjektNummer ist immer LONG
	V_I4(&vONr) = lONr;
	V_VT(&vMode) = VT_I2;		// Mode ist immer GEOOBJECTMODE_Get
	V_I2(&vMode) = GEOOBJECTMODE_Get;

	HRESULT hr = m_pDoc -> GetObject (vONr, vMode, ppIObj);
	if (FAILED(hr)) 
		return false;

	return true;

}
//////////////////////////////////////////////////////////////////
bool CKompiasExtension :: GewaesserUmkehr (long lONr)
{

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  lONr;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE ) 
			return false;
	}

	OBJGEOMETRIE OG;
	long *pX = new long [OS.lCnt];
	long *pY = new long [OS.lCnt];
    
	if (pX == NULL || pY == NULL) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return false;
	}

	memset (&OG,'\0',sizeof(OBJGEOMETRIE));
	OG.dwSize = sizeof(OBJGEOMETRIE);
	OG.lONr = lONr;
	OG.lCnt = OS.lCnt;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.iFlags = ~OGConverted;
	if (!DEX_GetObjGeometrie (OG)) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return false;
	}

	long lNum = OS.lCnt/2;
	long lRef;
	for ( long i = 0; i < lNum; i++) {

		lRef = *(pX+i);
		*(pX+i) = *(pX+OS.lCnt-1-i);
		*(pX+OS.lCnt-1-i) = lRef;


		lRef = *(pY+i);
		*(pY+i) = *(pY+OS.lCnt-1-i);
		*(pY+OS.lCnt-1-i) = lRef;

	}

	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);


	OG.lONr = lONr;
	OG.iObjTyp = OT_KANTE;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.iFlags = OGModObject;

	DEX_ModObjGeometrie (OG);
	long lGXA = *pX;
	long lGYA = *pY;
	long lGXE = *(pX+OS.lCnt-1);
	long lGYE = *(pY+OS.lCnt-1);

	DELETE_OBJ (pX);
	DELETE_OBJ (pY);

	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);


	long lStart = ObjektStartPunkt(lONr,m_pKH->CodeBauwAnfStat());
	long lEnde = LinienLaenge (lONr)+lStart;

//	long lStart = 0L;

	long lIdent = DEX_GetObjIdent ( lONr);

	m_lONrStart = BildeTextObjekt (lIdent,lStart,&lGXA,&lGYA);

	m_lONrEnde = BildeTextObjekt (lIdent,lEnde,&lGXE,&lGYE);

	m_lONrVis = lONr;

	CTextLaden (lONr,m_lONrStart, m_lONrEnde);

	LinienVisualisierung ( lONr);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: isCloned ( long lONr)
{
	char *pCode = new char [_MAX_PATH];
	if ( !pCode ) {
		return false;
	}

	wsprintf( pCode, ResString( ResID( IDS_OBJEKTSYSCODE,&g_pTE->RF()),40));


#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	ulong lMCode = DEX_GetMCodeFromFeatureNameEx ( hPr,pCode );
#else
	ulong lMCode = DEX_GetMCodeFromFeatureName ( pCode );
#endif

	*pCode = '\0';
	if ( 0L == lMCode ) {
		DELETE_OBJ ( pCode);
		return false;
	}

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// Objekt
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pCode;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)lMCode;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm )) {
		DELETE_OBJ ( pCode);
		return false;
	}

	}

	DELETE_OBJ ( pCode);
	return true;
}
//////////////////////////////////////////////////////////////////////////
long CKompiasExtension :: StartWertClone (long lONr,long lMCode)
{
	
	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return 0L;

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  lONr;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE ) 
			return 0L;
	}

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// Objekt
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = lMCode;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm )) {
		DELETE_OBJ ( pBuff);
		return 0L;
	}

	}
	long lPos = atol ( pBuff);
	DELETE_OBJ ( pBuff);
	return lPos;
}
//////////////////////////////////////////////////////////////////////////
long CKompiasExtension :: EndeWertClone (long lONr,long lMCode)
{
	
	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return LinienLaenge(lONr);

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  lONr;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE ) 
			return LinienLaenge (lONr);
	}

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// Objekt
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = lMCode;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm )) {
		DELETE_OBJ ( pBuff);
		return LinienLaenge(lONr);
	}

	}

	long lPos = atol ( pBuff);
	DELETE_OBJ ( pBuff);
	return lPos;
}
//////////////////////////////////////////////////////////////////////////
// KPSYMB.CXX
