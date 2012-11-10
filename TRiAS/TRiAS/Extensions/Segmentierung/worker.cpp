// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 19.07.2002 09:47:45
//
// @doc
// @module Strecken.cpp | Implementation of the <c CStrecken> class

#include "stdafx.h"


#include <TRiASHelper.h>

#include <xtsnguid.h>

#include <objgguid.h>		// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie ...
#include <operguid.h>		// CLSID_GeometrieOperationen
#include <Igeometr.hxx>

#include "segguids.h"

#include "Segment.h"
#include "Strecken.h"

#include <KoOrd.h>
#include <Ristypes.hxx>

#include <Errcodes.hxx>
#include <errinstx.hxx>
#include "worker.h"

#include <xtencatl.hxx>

#include <Xtensnn.h>


DefineSmartInterface (InitObjektGeometrie);		// WInitObjektGeometrie
DefineSmartInterface (ObjektGeometrie);			// WObjektGeometrie

typedef map<INT_PTR, os_string, less<INT_PTR> > CMCodeMap;
//////////////////////////////////////////////////////////////////////////////////

BOOL FAR PASCAL EnumObjektMerkmale( long lMCode, BOOL bNotLast, void* pVoid ) ;
BOOL FAR PASCAL OnEnumObjektMerkmale( long lMCode, BOOL bNotLast, void* pVoid );
ErrCode  CreateFeatureInPBD (ulong ulMCode, string sMText, short iMaxLen,bool bSystemMerkmal, bool bReadOnly, ulong ulIdent);


//////////////////////////////////////////////////////////////////////////////////

void CStreckenWorker :: operator() (LONG lONr)

{

	TX_ASSERT (lONr != 0);
	TX_ASSERT (lONr != -1);

	_ASSERTE(NULL != m_pPA);

	m_pPA -> Tick();			// ProgressIndikator weitersetzen
	if (FAILED(m_pPA -> GoOn()))
		_com_issue_error(E_ABORT);

////////////////////////////////////////////////////////////////////////////////



	int m_bKnoten = m_rStreckenAction.ActionDlg()->bKnoten();
	int m_bKanten = m_rStreckenAction.ActionDlg()->bKanten();
	m_hPr = m_rStreckenAction.ActionDlg()->bProjectHandle();


// Segmentierungsparameter //////////////////////////////////////////////////////

	SEGMENTPARTS SP;
   	memset (&SP,'\0',sizeof(SEGMENTPARTS));
	SP.dwSize = sizeof(SEGMENTPARTS);

	if ( m_bKnoten )
		SP.iMode = SP.iMode | SEGMENT_AP | SEGMENT_EP;

	if ( m_bKanten )
		SP.iMode = SP.iMode | SEGMENT_Kante;

	SP.lONr = lONr;

	SP.hPr = DEX_GetObjectProject (lONr);
	SP.lIdent = DEX_GetObjIdent (lONr);

	long lNewAP = -1L;
	long lNewEP = -1L;
	long lNewKante = -1L;
	SP.plNewAP = &lNewAP;
	SP.plNewEP = &lNewEP;
	SP.plNewKante = &lNewKante;

/////////////////////////////////////////////////////////////////////////////////

//	OE ( hPr,Ident ... ) für Splitting + Knoten/Kanten festlegen
	SEGMENTGUIDS *pSG = m_rStreckenAction.GetConfigGuid(SP.lIdent);


	if ( pSG->hPr != SP.hPr)
		return;

// Definierte MCodes sammeln
	if (m_bKnoten || m_bKanten) {
		if (!m_iMCodes ) 
			m_iMCodes = DefineFeatures(SP.lIdent);
	}



//	Zuordung für Knoten/Kanten
	SP.hPr = pSG->hPartPr;
	SP.lIdent = pSG->lPartIdent;
	
	//

	THROW_FAILED_HRESULT (StreckenObjekte ( &SP, pSG))

	StreckenGuidFeature (&SP, pSG);


}
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------------------------------
// sMText in ulMCode-Merkmal des lONr-Objektes schreiben; für sMText == "" wird der
// Merkmalstext gelöscht
bool WriteGuidText (long lONr, long ulMCode, int iTTyp, CString sMText)
{


	TX_ASSERT (ulMCode != 0);
	TX_ASSERT ((long)-1 != ulMCode);

	TX_ASSERT (lONr != 0);
	TX_ASSERT (lONr != -1);


	if (0 == lONr || -1 == lONr || 0 == ulMCode || (long)-1 == ulMCode)
		return false;


#if _TRiAS_VER >= 0x0300
HPROJECT hPr = DEX_GetObjectProject (lONr);

	if (DEX_GetROModeFeatureEx (hPr, ulMCode))	// Objekteigenschaft schreibgeschützt
	{
		return false;
	}
#endif // _TRiAS_VER >= 0x0300



TARGETMERKMAL TM;

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = (LPARAM)lONr;
	TM.lMCode = ulMCode;
	TM.iTTyp = iTTyp;

	char *pMText = new char [_MAX_PATH];
	*pMText = NULL;
	TM.pMText = pMText;
	TM.imaxLen = _MAX_PATH-1;


	if ( DEX_GetTextMerkmal (TM)) {

		if ( NULL != *pMText) {
			CString TT (pMText);
			sMText += "|" + TT;
		} 

	}

	DELETE_OBJ(pMText);


	if ("" != sMText)	// Merkmalstext schreiben
	{
		if (sMText.GetLength() <= SHRT_MAX - 3)
		{
			TM.imaxLen = sMText.GetLength();
			TM.pMText = (char *)(LPCTSTR) sMText;
		}
		else
		{
			TX_ASSERT (sMText.GetLength() <= SHRT_MAX - 3);

		// Anfang von sMText, wenn sMText zu lang ist
			CString sAnfang = sMText.Left (SHRT_MAX-7) + " ...";

			TM.imaxLen = sAnfang.GetLength();
			TM.pMText = (char*)(LPCTSTR)sAnfang;
		}
	}
	else				// Merkmalstext löschen
	{
		TM.imaxLen = 0;
		TM.pMText = 0;
	}


	if (EC_OKAY != DEX_ModTextMerkmal (TM))
		return false;

	return true;

} // WriteGuidText
///////////////////////////////////////////////////////////////////////////////
// alle Objekteigenschaften

BOOL FAR PASCAL OnEnumObjektMerkmale( long lMCode, BOOL bNotLast, void* pVoid ) 

{

	TX_ASSERT (lMCode != 0);
	TX_ASSERT ((long)-1 != lMCode);

	//UniqueIdent übergehen
	if (lMCode == DEX_GetUniqueIdentMCodeEx (DEX_GetFeatureProject(lMCode)) ||
		lMCode == DEX_GetOldUniqueIdentMCodeEx(DEX_GetFeatureProject(lMCode)))
		return TRUE;
	
	CMCodeMap* g_MCodes = (CMCodeMap*)pVoid;


// Systemmerkmal ausklinken
	PBDMERKMAL Data;
	char cbBuffer[64];

	INITSTRUCT(Data, PBDMERKMAL); 
	Data.pbdTyp = 'm';                          // Merkmal
	Data.pbdCode = lMCode;
	Data.pbdKText = cbBuffer;
	Data.pbdKTextLen = sizeof(cbBuffer);
	
	ErrCode EC = DEX_GetPBDData (Data);

	if (EC != EC_OKAY && EC != WC_RETURN)
		return TRUE;

	short locMTyp = toupper(Data.ipbdMTyp & ~(PBDMERKMAL_SYSTEMFLAG|PBDMERKMAL_READONLY));

	if ('A' != locMTyp && 'I' != locMTyp && 'F' != locMTyp) {
		_ASSERTE('A' == locMTyp || 'I' == locMTyp || 'F' != locMTyp);
		return TRUE;	// unbekannter Datentyp
	}

	if (Data.ipbdMTyp & PBDMERKMAL_SYSTEMFLAG)
		return TRUE;	// keine systeminternen Attribute exportieren


	long lRefCode = DEX_MapHandleToMCode(lMCode);
	CMCodeMap::iterator it = g_MCodes->find(lMCode);

	if (it == g_MCodes->end())
		g_MCodes->insert(CMCodeMap::value_type(lRefCode, os_string(cbBuffer)));

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////

short CStreckenWorker ::DefineFeatures ( long lIdent)
{
	TX_ASSERT (lIdent != 0);
	TX_ASSERT (lIdent != -1);

		short iCode = 0;

		ENUMLONGKEYEX ELKE;

		memset (&ELKE, 0, sizeof (ENUMLONGKEYEX));
		ELKE.eFcn = (ENUMLONGKEYEXPROC)OnEnumObjektMerkmale;
		ELKE.ePtr = (void*) &g_MCodes;
		ELKE.eData = MPObjectFeature;	// nur Objektmerkmale übernehmen (in xtension.h definiert),
		ELKE.eKey = lIdent;
		DEX_EnumObjektMerkmaleClassEx(ELKE);
		iCode = 1;
		return iCode;
	
}
//////////////////////////////////////////////////////////////////////////////////
long CStreckenWorker :: StreckenKnoten (SEGMENTPARTS *pSP, KoOrd lXP, KoOrd lYP)
{

	long lON = -1L;

//	Knoten im Baum suchen
	CString Key1;
	Key1.Format("%ld",lXP);
	CString Key2;
	Key2.Format("%ld",lYP);
	CString Key = Key1 + Key2;

	// Knoten anlegen
	if (!m_rStreckenAction.AddConfigKnoten ( (LPCTSTR) Key))		// Error
		return lON;

	// Knoten bereits vorhanden - ONr holen
	lON = m_rStreckenAction.GetConfigKnoten ((LPCTSTR) Key);
	if ( -1L != lON )
		return lON;

//  Knoten aus den wObj-Stützpunkten aufbauen
	WObjektGeometrie wMoveObj;	// ObjektGeometrie der zu verschiebenden Kante
					
	try
	{
	// neue IObjektGeometrie erzeugen und ...
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

	// ... initialisieren
	THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lXP, lYP, OT_PUNKT))

		wMoveObj = wIObj;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	wMoveObj->SetIdent (pSP->lIdent);


	wMoveObj->SetFlags (OGNewObject | OGForceGeoError | OGForceGeometry);

	INT_PTR ihPr = reinterpret_cast<INT_PTR>(pSP->hPr);
	HRESULT hr = wMoveObj->GeometrieAnTRiASEx (ihPr, true, NULL);

	// wenn Objekt in DB eingespeichert wurde, dann Objektname und UniqueIdent vergeben
	if (S_OK == hr)
		wMoveObj->GetONr (&lON);

	TX_ASSERT (lON != 0);
	TX_ASSERT (lON != -1);

	if ( -1 == lON ) 
		return lON;
	

	// ONr für neuen Knoten speichern

	m_rStreckenAction.SetConfigKnoten ((LPCTSTR) Key, lON);

	StreckenBasisFeature (lON,STRECKEN_Point);		// UniqueIdent für Knoten

	CopyFeature (pSP->lONr,lON);					// OE des Ursprungsobjektes ( Segment)

	return lON;

}

//////////////////////////////////////////////////////////////////////////////////

long CStreckenWorker :: StreckenKante (SEGMENTPARTS *pSP, KoOrd lXA, KoOrd lYA, KoOrd lXE, KoOrd lYE)
{

	long lON = -1L;

//  Kante aus den wObj-Stützpunkten aufbauen
	WObjektGeometrie wMoveObj;	// ObjektGeometrie der zu verschiebenden Kante
					
	try
	{
	// neue IObjektGeometrie erzeugen und ...
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

	// ... initialisieren
	THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lXA, lYA, OT_KANTE))

		wMoveObj = wIObj;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	wMoveObj->AddPunkt (lXE, lYE, -1, -1);
	wMoveObj->SetIdent (pSP->lIdent);


	wMoveObj->SetFlags (OGNewObject | OGForceGeoError | OGForceGeometry);

	INT_PTR ihPr = reinterpret_cast<INT_PTR>(pSP->hPr);
	HRESULT hr = wMoveObj->GeometrieAnTRiASEx (ihPr, true, NULL);

	// wenn Objekt in DB eingespeichert wurde, dann Objektname und UniqueIdent vergeben
	if (S_OK == hr)
		wMoveObj->GetONr (&lON);

	TX_ASSERT (lON != 0);
	TX_ASSERT (lON != -1);

	if ( -1 == lON)
		return lON;

	StreckenBasisFeature (lON,STRECKEN_Kante);
	CopyFeature (pSP->lONr,lON);

	return lON;

}
///////////////////////////////////////////////////////////////////////////////

bool CStreckenWorker :: CopyFeature (long lQuelle, long lZiel)
{
	if ( lQuelle == 0 || lQuelle == -1 || lZiel == 0 || lZiel == -1 )
		return false;


	COPYFEAT CF;
   	memset (&CF,'\0',sizeof(COPYFEAT));
	CF.dwSize = sizeof(COPYFEAT);
	CF.lQuelle = lQuelle;
	CF.lZiel = lZiel;
	CF.hPr = m_hPr;
	CF.m_Codes = &g_MCodes;

	ENUMLONGKEYEX ELKE;

	memset (&ELKE, 0, sizeof (ENUMLONGKEYEX));
	ELKE.eFcn = (ENUMLONGKEYEXPROC)EnumObjektMerkmale;
	ELKE.ePtr = &CF;
	ELKE.eData = MPObjectFeature;	// nur Objektmerkmale übernehmen (in xtension.h definiert),
	ELKE.eKey = lQuelle;
	DEX_EnumObjektMerkmaleEx(ELKE);


	return true;
}

/////////////////////////////////////////////////////////////////////////////////

HRESULT CStreckenWorker :: StreckenObjekte (SEGMENTPARTS *pSP, SEGMENTGUIDS *pSG)
{

WObjektGeometrie wObj;		// ObjektGeometrie des lONr-Objektes

	try
	{
	// neue IObjektGeometrie erzeugen und ...
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

	// ... initialisieren
		THROW_FAILED_HRESULT (wIObj->InitObjGeometry (pSP->lONr));

		wObj = wIObj;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

short iOT;
KoOrd* plXK; KoOrd* plYK;
long lAnz;			// wenn wObj eine Linie ist: Gesamtstützpunktanzhl

	wObj->GetObjTyp (&iOT);

	TX_ASSERT (iOT == OT_KANTE );

	wObj->GetCnt (&lAnz);
	wObj->GetX ((void**)&plXK);
	wObj->GetY ((void**)&plYK);

	KoOrd lXA;
	KoOrd lYA;
	KoOrd lXE;
	KoOrd lYE;

	lXA = plXK [0];
	lYA = plYK [0];

	lXE = plXK [lAnz-1];
	lYE = plYK [lAnz-1];

	HRESULT hr = S_OK;

	try
	{

	if ( pSP->iMode & SEGMENT_AP ) {
		*pSP->plNewAP = StreckenKnoten (pSP,lXA,lYA);
		if ( -1 == *pSP->plNewAP ) {
			hr = StreckenError (pSP->lONr, SEGMENT_AP,pSG);
		}
	}

	if ( pSP->iMode & SEGMENT_EP ) {
		*pSP->plNewEP = StreckenKnoten (pSP,lXE,lYE);
		if ( -1 == *pSP->plNewEP ) {
			hr = StreckenError ( pSP->lONr,SEGMENT_EP, pSG);
		}

	}

	if ( pSP->iMode & SEGMENT_Kante ) {
		*pSP->plNewKante = StreckenKante (pSP,lXA,lYA,lXE,lYE);
		if ( -1 == *pSP->plNewKante ) {
			hr = StreckenError ( pSP->lONr,SEGMENT_Kante, pSG);
		}

	}

	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}



	return hr;
}


///////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------------------------
// sMText in ulMCode-Merkmal des lONr-Objektes schreiben; für sMText == "" wird der
// Merkmalstext gelöscht
bool WriteFeatureText (long lONr, long ulMCode, int iTTyp, CString sMText)
{
	TX_ASSERT (ulMCode != 0);
	TX_ASSERT ((long)-1 != ulMCode);

	TX_ASSERT (lONr != 0);
	TX_ASSERT (lONr != -1);


	if (0 == lONr || -1 == lONr || 0 == ulMCode || (long)-1 == ulMCode)
		return false;


#if _TRiAS_VER >= 0x0300
HPROJECT hPr = DEX_GetObjectProject (lONr);

	if (DEX_GetROModeFeatureEx (hPr, ulMCode))	// Objekteigenschaft schreibgeschützt
	{
		return false;
	}
#endif // _TRiAS_VER >= 0x0300



TARGETMERKMAL TM;

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = (LPARAM)lONr;
	TM.lMCode = ulMCode;
	TM.iTTyp = iTTyp;

	char *pMText = new char [_MAX_PATH];
	*pMText = NULL;
	TM.pMText = pMText;
	TM.imaxLen = _MAX_PATH-1;


	if ( DEX_GetTextMerkmal (TM)) {

		if ( NULL != *pMText) {
			DELETE_OBJ(pMText);
			return true;
		}

	}

	DELETE_OBJ(pMText);

	if ("" != sMText)	// Merkmalstext schreiben
	{
		if (sMText.GetLength() <= SHRT_MAX - 3)
		{
			TM.imaxLen = sMText.GetLength();
			TM.pMText = (char *)(LPCTSTR) sMText;
		}
		else
		{
			TX_ASSERT (sMText.GetLength() <= SHRT_MAX - 3);

		// Anfang von sMText, wenn sMText zu lang ist
		CString sAnfang = sMText.Left (SHRT_MAX-7) + " ...";

			TM.imaxLen = sAnfang.GetLength();
			TM.pMText = (char*)(LPCTSTR)sAnfang;
		}
	}
	else				// Merkmalstext löschen
	{
		TM.imaxLen = 0;
		TM.pMText = 0;
	}



	if (EC_OKAY != DEX_ModTextMerkmal (TM))
		return false;

	return true;

} // WriteFeatureText


///////////////////////////////////////////////////////////////////////////////
HRESULT CStreckenWorker :: StreckenError (long lONr,short iTyp, SEGMENTGUIDS *pSG)
{
	
HRESULT	hr = E_FAIL;


	if ( 0 == pSG->lErrorMode ) 
		pSG->lErrorMode = LoadErrorMode (pSG);
	
	if ( 0 == pSG->lErrorMode ) 
		return hr;

	CString strError;
	CString strKnotenAP;
	CString strKnotenEP;
	CString strKante;

	VERIFY(strError.LoadString(IDS_NODATEN));
	VERIFY(strKnotenAP.LoadString(IDS_KNOTENAP));
	VERIFY(strKnotenEP.LoadString(IDS_KNOTENEP));
	VERIFY(strKante.LoadString(IDS_KANTEN));

	switch (iTyp) {
	case SEGMENT_AP: 
		{
			strError += strKnotenAP;
		}
		break;

	case SEGMENT_EP: 
		{
			strError += strKnotenEP;
		}
		break;

	case SEGMENT_Kante: 
		{
			strError += strKante;
		}
		break;

	default:
		break;
	}

	if (!WriteGuidText (lONr, pSG->lErrorMode, TT_Objekt, strError))
		return hr;

	return S_OK;

}

///////////////////////////////////////////////////////////////////////////////
long CStreckenWorker:: LoadErrorMode(SEGMENTGUIDS *pSG)
{

	PBDMERKMALEX pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMALEX));
	
	pbdData.dwSize = sizeof(PBDMERKMALEX);

	ulong lMCode = DEX_GetMCodeFromFeatureNameEx (pSG->hPr, pSG->sErrorMode );

	if ( 0 != lMCode ) {
		return lMCode;
	}
		
	long lMHandle = DEX_GetUniqueSysMCode();
	lMCode = DEX_MapHandleToMCode(lMHandle);

	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKTextLen = strlen (pSG->sErrorMode) -1;
	pbdData.pbdLTextLen = 0;

	pbdData.pbdKText = pSG->sErrorMode;
	pbdData.ipbdMTyp = MPObjectFeature;	
	pbdData.ipbdMLen = 256;
	pbdData.lIdent = pSG->lIdent;

	{
	ErrInstall EI (WC_NOMERKMAL);
	if (DEX_ModPBDDataEx (pSG->hPr,pbdData) != EC_OKAY) {
		return 0;
	} else {
		DEXN_PBDMCodeChanged (lMCode);

	}
	}

	return lMCode;
}
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

bool CStreckenWorker :: StreckenBasisFeature (long lONr, short iTyp)
{

	if ( -1 == lONr)
		return false;

CString SUnique;

	if ( iTyp == STRECKEN_Point )
		SUnique.LoadString(IDS_BASISPOINTUNIQUE);

	if ( iTyp == STRECKEN_Kante )
		SUnique.LoadString(IDS_BASISUNIQUE);

		
	CString SUni;
	SUni.Format("%s%ld", (LPCTSTR)SUnique, lONr);   // Attention: str is also used in the parameter list.

	return WriteFeatureText (lONr, DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(lONr)),
						  TT_Objekt, SUni);

}


///////////////////////////////////////////////////////////////////////////////

bool CStreckenWorker :: StreckenGuidFeature (SEGMENTPARTS *pSP, SEGMENTGUIDS *pSG)
{

// evtl. ObjektGuid exportieren

//	LPCTSTR	lpszGUIDKante;
	LPCTSTR	lpszGUIDAP;
	LPCTSTR	lpszGUIDEP;
	LPCTSTR	lpszGUIDOriginal;

	short iMode = 0;
//	iMode = SEGMENT_Kante | SEGMENT_AP | SEGMENT_EP;
	iMode = SEGMENT_AP | SEGMENT_EP;

	if ( pSP->iMode & iMode ) {

		USES_CONVERSION;

		OBJECTGUID OGUID;
		INITSTRUCT(OGUID, OGUID);

		OGUID.lONr = pSP->lONr;
		if ( OGUID.lONr != -1) {
	
			if( SUCCEEDED(DEX_GetObjectGuid(OGUID)) ) {
				CComBSTR	strGUID(OGUID.guid);
				lpszGUIDOriginal = W2A(strGUID);
			}
		}

/*
		OGUID.lONr = *pSP->plNewKante;
		if ( OGUID.lONr != -1) {
	
			if( SUCCEEDED(DEX_GetObjectGuid(OGUID)) ) {
				CComBSTR	strGUID(OGUID.guid);
				lpszGUIDKante = W2A(strGUID);
			}
		}
*/

		OGUID.lONr = *pSP->plNewAP;
		if ( OGUID.lONr != -1) {
	
			if( SUCCEEDED(DEX_GetObjectGuid(OGUID)) ) {
				CComBSTR	strGUID(OGUID.guid);
				lpszGUIDAP = W2A(strGUID);
			}
		}

		OGUID.lONr = *pSP->plNewEP;
		if ( OGUID.lONr != -1) {
	
			if( SUCCEEDED(DEX_GetObjectGuid(OGUID)) ) {
				CComBSTR	strGUID(OGUID.guid);
				lpszGUIDEP = W2A(strGUID);
			}
		}


		CString sUni;


//   GUIDS für die Kante
		if ( *pSP->plNewAP != -1 && *pSP->plNewEP != -1 ) {
			sUni.Format ( "%s | %s",lpszGUIDAP,lpszGUIDEP);

			if ( *pSP->plNewAP == *pSP->plNewEP )		// Geschlossener Polygonzug : AP == EP
				sUni.Format ( "%s",lpszGUIDAP);


// KnotenGuids als Kanteninfo
			if (pSG->lGuid_Knoten_Orig != 0)
				WriteGuidText (pSP->lONr, pSG->lGuid_Knoten_Orig,
						  TT_Objekt, sUni);


//			if (pSG->lGuid_Knoten != 0)
//				WriteGuidText (*pSP->plNewKante, pSG->lGuid_Knoten,
//						  TT_Objekt, sUni);


			if ( *pSP->plNewAP != *pSP->plNewEP ) {		//  : AP != EP

				sUni.Format ( "%s",lpszGUIDEP);
				WriteGuidText (*pSP->plNewAP, pSG->lGuid_Knoten,
					  TT_Objekt, sUni);



				sUni.Format ( "%s",lpszGUIDAP);
				WriteGuidText (*pSP->plNewEP, pSG->lGuid_Knoten,
					  TT_Objekt, sUni);
			}


		}


// OriginalSegment_Guid an Kante
		if ( pSP->lONr != -1 ) {
			sUni.Format ( "%s",lpszGUIDOriginal);
			if (pSG->lGuid_Original != 0) {

				WriteGuidText (*pSP->plNewAP, pSG->lGuid_Original,
						  TT_Objekt, sUni);

				if ( *pSP->plNewAP != *pSP->plNewEP ) 		// AP != EP
					WriteGuidText (*pSP->plNewEP, pSG->lGuid_Original,
						  TT_Objekt, sUni);

			}


//				WriteGuidText (*pSP->plNewKante, pSG->lGuid_Original,
//						  TT_Objekt, sUni);
		}


/*
		if ( *pSP->plNewKante != -1  ) {
			sUni.Format ( "%s",lpszGUIDKante);

// KantenGuid an Knoten
			if ( pSG->lGuid_Kante != 0) {
				WriteGuidText (*pSP->plNewAP, pSG->lGuid_Kante,
						  TT_Objekt, sUni);

				WriteGuidText (*pSP->plNewEP, pSG->lGuid_Kante,
						  TT_Objekt, sUni);
			}
		}
 */

		return true;
	}

	return false;
}
/////////////////////////////////////////////////////////////////////////////////

// neues Merkmal in der PBD erzeugen (falls noch nicht vorhanden)
ErrCode  CreateFeatureInPBD (ulong ulMCode, string sMText, short iMaxLen,
											bool bSystemMerkmal, bool bReadOnly, ulong ulIdent)
{
	TX_ASSERT (0 != ulMCode);
	TX_ASSERT ((ulong)-1 != ulMCode);

#if _TRiAS_VER >= 0x0300
HPROJECT hPr = DEX_GetObjectsProject (ulIdent);

	if (DEX_GetROModeFeatureEx (hPr, ulMCode))	// Objekteigenschaft schreibgeschützt
	{
		return WC_FEATURE_ISRO;
	}
#endif // _TRiAS_VER >= 0x0300

	TX_ASSERT (sMText.length() > 0);
	TX_ASSERT (iMaxLen > 0);

// Abschalten einer evtl. Fehlermeldung beim nachfolgenden Test, ob Merkmal schon in PBD
// vorhanden ist
ErrInstall EI (WC_NOMERKMAL);


#if _TRiAS_VER < 0x0300
PBDMERKMAL PM;

	INITSTRUCT (PM, PBDMERKMAL);
#else
PBDMERKMALEX PM;

	INITSTRUCT (PM, PBDMERKMALEX);
	PM.lIdent = ulIdent;
#endif // _TRiAS_VER < 0x0300

	PM.pbdTyp = 'm';			// Merkmal
	PM.pbdCode = ulMCode;

ErrCode EC = DEX_GetPBDData (PM);

	if (EC == EC_OKAY && iMaxLen <= PM.ipbdMLen)	// wenn bereits vorhanden,
		return EC_OKAY;								// dann zurück

	if (EC != EC_OKAY)		// noch nicht vorhanden
	{
	short iLen = 0;

		while (((iLen = sMText.length()) > 0) && (' ' == sMText[iLen-1]))
			sMText.remove (iLen-1);	// Text ggf. trimmen

		// LangText setzen
		iLen = sMText.length();
		PM.pbdLTextLen = iLen;
		PM.pbdLText = (char*)sMText.c_str();

		// KurzText setzen
		iLen = sMText.length();
		PM.pbdKTextLen = iLen;
		PM.pbdKText = (char*)sMText.c_str();
		PM.ipbdMTyp = 'a';				// Objekt-Merkmal
		if (bSystemMerkmal)
			PM.ipbdMTyp |= PBDMERKMAL_SYSTEMFLAG;
		if (bReadOnly)
			PM.ipbdMTyp |= PBDMERKMAL_READONLY;
	}

	// diese Länge ggf. max. Länge des Merkmals vergrößern
	PM.ipbdMLen = iMaxLen;


	{
	ErrInstall EI (WC_NOMERKMAL);
	EC = DEX_ModPBDDataEx (hPr,PM);

	if ( EC != EC_OKAY)
		return EC;
	else 
		DEXN_PBDMCodeChanged (ulMCode);


	}

	return EC;

} // CreateFeatureInPBD


////////////////////////////////////////////////////////////////////////////////

BOOL FAR PASCAL EnumObjektMerkmale( long lMCode, BOOL bNotLast, void* pvData ) 

{

	COPYFEAT* pFeat = (COPYFEAT*)pvData;

	long lQuelle = pFeat->lQuelle;				// Quelle-Objektnummer 
	long lZiel = pFeat->lZiel;				// Ziel-Objektnummer
	HPROJECT hPr = pFeat->hPr;				// Zieldatenquelle

	CMCodeMap * g_MCodes = (CMCodeMap *)pFeat->m_Codes;

	TARGETMERKMAL TM;

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = lQuelle;
	TM.lMCode = lMCode;
	TM.iTTyp = TT_Objekt;		//nur von Objekten !!!
	TM.pMText = NULL;
	TM.imaxLen = 0;

///////////////////////////////////////////////////////////////////////////////
// ... und jetzt aber richtig ...

	char cBuffer[_MAX_PATH];
	TM.pMText = cBuffer;
	TM.imaxLen = sizeof(cBuffer);

	if (NULL ==	DEX_GetTextMerkmal(TM))
		return TRUE;
		

	long lRefCode = DEX_MapHandleToMCode(lMCode);

	CMCodeMap::iterator it = g_MCodes->find(lRefCode);

	if (it == g_MCodes->end())
		return TRUE;

	ErrCode EC = EC_OKAY;

	string	sKText = (*it).second;	// MerkmalsKurzText

//	ulong ulMCode = DEX_GetMCodeFromFeatureNameEx (DEX_GetObjectsProject(lZiel), sKText.c_str());
	ulong ulMCode = DEX_GetMCodeFromFeatureNameEx (hPr, sKText.c_str());

	// Merkmal sKText existiert noch nicht in der Ziel-Datenquelle
	if (0 == ulMCode || (ulong)-1 == ulMCode)
	{
			// neuen Merkmalscode geben lassen und Merkmal in PBD anlegen
		ulMCode = DEX_GetUniqueMCode();
		EC = CreateFeatureInPBD (ulMCode, sKText, sKText.length()+1, false, false,
									 DEX_GetObjIdent(lZiel));
	}

	if (EC_OKAY == EC)
		WriteFeatureText (lZiel, ulMCode, TT_Objekt, cBuffer);

	return TRUE;

}


/////////////////////////////////////////////////////////////////////////////////
