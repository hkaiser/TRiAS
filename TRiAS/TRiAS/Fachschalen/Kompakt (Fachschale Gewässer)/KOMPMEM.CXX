// KOMPIAS-MEMBER 
// File: KOMPMEM.CXX

#include "kompp.hxx"

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

#include "cobjtree.hxx"
#include "txtedit.hxx"
#include "kompsimu.hxx"
#include "about.hxx"
#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32

static LPCTSTR g_cbSecKey	= TEXT("Software\\%s\\%s\\Extensions\\TRiAS.GewaesserExtension.1\\Config");
//static LPCTSTR g_cbSecKey	= TEXT("Software\\%s\\%s\\Extensions\\TRiAS.KompaktExtension2.1\\Config");

//-------------------------------------------------------------------

void CKompiasExtension :: CreateStandardInformation (void)
{ 
//------Interface----------------------------
	m_pIOG = NULL;		//ObjektGeometrie
	m_pAbst = NULL;		//AbstandsErweiterung
	m_pTop = NULL;		//TopRel-Erweiterung
	m_pPuf = NULL;		//Puffer-Erweiterung
	m_pObjOp = NULL;	//ObjektOperationen-Erweiterung
//-------------------------------------------
	m_pScript = NULL;	// Basic-Script
	m_pDoc = NULL;		// DBEingang- Basic

	m_pObjPropL = NULL;
	m_pObjPropF = NULL;

	m_pObjRechts = NULL;
	m_pObjHoch = NULL;

	m_pStatus = NULL;

//------------------------------------------
	m_pGew = NULL;		// GewaesserKataster(Objekte)
	m_pGewKomp = NULL;		// GewaesserKataster(Objekte)
	m_pGewHyd = NULL;		// GewaesserKataster(Hydraulik)
	m_pGewPart = NULL;		// GewaesserKataster(Objekte)
	m_pGewAlle = NULL;		// GewaesserKataster(Objekte)

	m_pTRGew = NULL;		// GewaesserKataster(TRiAS-Objekte)
	m_pCTF = NULL;		// KoordSystem

	m_pKH = NULL;		// KompaktHeader
	m_hLib = NULL;		// Adresse Kompakt_DLL
	m_iCount = 0;
	m_pModObj = NULL;	// Obj-Vector modifizierter ( neuer ) Objekte
	m_pGewText = NULL;	// Obj-Vector GewaesserTexte
	m_isNewOR = false;	// Neues ORFenster anlegen

	m_pLocDir = NULL;	// Projekt
	m_pLocProt = NULL;	// Projekt-Protokoll
	m_pDataPath = NULL;	// DatenPfad Gewässerkataster
	m_isActive = false;	// Kompakt passiviert

	m_isCreate = true;	// neue Geometrie bilden
	m_isInit = true;	// GewKataster initialisiert

	m_lONr = -1L;
	m_lONrGew = -1L;
	m_lONrBauw = -1L;
	m_lONrDel = -1L;
	m_hWnd = 0;

	m_lONrStart = -1L;
	m_lONrEnde = -1L;
	m_lONrVis = -1L;

//	KompaktKomponenten
	m_iAbfluss = false;		// ohne Hydraulik
	m_iProfile = false;		// ohne Profile etc.

// Notifikationen
	m_bChange = false;
	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);

	m_bMerkmal = false;
	MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);


	m_dKPP = KP_Default;	// Kein Protokoll
	m_dKPA = KP_Default;	// Kompakt1.DLL verwenden

	m_isWork = false;

	//Parameter aus Registrierung

#if _MSC_VER >= 1100

	m_hPr = 0;				// ProjektHandle

	TCHAR szKey[_MAX_PATH];
	wsprintf(szKey,g_cbSecKey,REG_COMPANY_KEY,REG_PRODUCT_KEY);

	{	

	CCurrentUser rgMASS(szKey, true);

//	CCurrentUser rgMASS("Software\\TRiAS\\InterTRiAS\\Extensions\\TRiAS.KompaktExtension2.1\\Config", true);
	rgMASS.GetDWORD ( "Protokoll",m_dKPP);
	rgMASS.GetDWORD ( "NoKompaktDLL",m_dKPA);

	}

#else
	{	
	CCurrentUser rgMASS("Software\\uve\\TRiAS\\Extensions\\TRiAS.KompaktExtension2.1\\Config", true);
	rgMASS.GetDWORD ( "Protokoll",m_dKPP);
	}
	{	
	CCurrentUser rgMASS("Software\\uve\\TRiAS\\Extensions\\TRiAS.KompaktExtension2.1\\Config", true);
	rgMASS.GetDWORD ( "NoKompaktDLL",m_dKPA);
	}
#endif

	if ( m_dKPA != KP_Default)
		MessageBox ( 0, "Parameter *NoKompaktDLL* ist eingestellt","KompiasRegistratur",MB_OK);


}
//-------------------------------------------------------------------
void CKompiasExtension :: DeleteStandardInformation (void)
{ 
	if (m_pLocProt)
			KompaktProtokoll ( m_pLocProt, "\n\t ==> Löschen der StandardEinträge ==>\n");

	ReleaseInterface();

	if (m_pLocProt)
			KompaktProtokoll ( m_pLocProt, "\n\t ==> Interface gelöscht ==>\n");

	DELETE_OBJ ( m_pCTF);


	if (m_pLocProt)
			KompaktProtokoll ( m_pLocProt, "\n\t ==> Abhängen Kompakt1.dll ==>\n");
	try {
		DELETE_OBJ ( m_hLib);
	} catch (...) {
		MessageBox ( __hWndM,
//		 "Kompakt1.dll läßt sich nicht entladen!",
		 ResString (ResID(IDS_ERRNODELKOMPAKTDLL, &RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
		MB_ICONSTOP);

	}
	if (m_pLocProt)
			KompaktProtokoll ( m_pLocProt, "\n\t ==> Kompakt1.dll abgehängt ==>\n");


	DELETE_OBJ ( m_pLocDir);
	DELETE_OBJ ( m_pKH);
	DELETE_OBJ ( m_pGew);
	DELETE_OBJ ( m_pGewKomp);
	DELETE_OBJ ( m_pGewHyd);
	DELETE_OBJ ( m_pGewPart);
	DELETE_OBJ ( m_pGewAlle);

	DELETE_OBJ ( m_pTRGew);
	DELETE_OBJ (m_pStatus);
	DELETE_OBJ ( m_pDataPath);
	CTextLoeschen();
	CTreeLoeschen ( m_pModObj);	// Obj-Vector modifizierter ( neuer ) Objekte
	DELETE_OBJ ( m_pModObj);
//	LoeschenKompaktKlassen ( );	// Leistungen und Hydraulik
	m_isInit = false;
	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	if (m_pLocProt)
			KompaktProtokoll ( m_pLocProt, "\n\t ==> StandardEinträge gelöscht ==>\n");

	DELETE_OBJ ( m_pLocProt);

}
//-------------------------------------------------------------------
void CKompiasExtension :: CreateGraphicInformation (void)
{
	GEODBHDRENTRY hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADGRAPHICINFO,&RF()),HEADERKEYSIZE+1),HEADERKEYSIZE);
	hdrEntry.lphdrText = new char [HEADERSIZE +1];
	hdrEntry.hdrTextLen = HEADERSIZE;

#if _MSC_VER >= 1100
	HPROJECT hPr = HandleKompaktProject();
	if (DEX_ReadGeoDBHdrEntryEx (hPr,hdrEntry) == EC_OKAY) {
#else
	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
#endif
	// HeaderEintrag existiert
		DELETE_OBJ ( hdrEntry.lphdrText);
		return;
	}

	strcpy( hdrEntry.lphdrText, "1");

#if _MSC_VER >= 1100
	DEX_WriteGeoDBHdrEntryEx (hPr,hdrEntry); 
#else
	DEX_WriteGeoDBHdrEntry (hdrEntry);
#endif

	DELETE_OBJ ( hdrEntry.lphdrText);

	return;
}
//---------------------------------------------------------------------
// KK010810
HPROJECT CKompiasExtension :: HandleKompaktProject(void)
{
	if (m_pKH)
		return m_pKH->HKompaktProject();
	else 
		return AktuellesProjekt();

}

//---------------------------------------------------------------------
bool CKompiasExtension :: AbgleichFeature ( long lONr)
{

	m_lONr = -1;
	m_lONrGew = -1;

//	MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	char *pGewNr = AktualisiereGewaesserNummer (  lONr, m_pKH->CodeGewNr());


	if ( pGewNr ) {
		char *pMalte = m_hLib->GewaesserNameHolen ( pGewNr);
		if ( pMalte && *pMalte != '\0') {
			SetObjektWert( lONr, m_pKH->CodeGewName(), pMalte);
			m_lONr = -1L;
			MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
			return true;		
		} else {
// Völlig neu
//--------------------> GewNr existiert in KompaktKataster nicht- anlegen !

			char *pBuffer = new char [_MAX_PATH];
			if (pBuffer) {
				long lIdent = DEX_GetObjIdent ( lONr);
				ulong lSMCode = DEX_GetObjNameMCode(lIdent);
				GetStandardMCode ( lONr, lSMCode, pBuffer);
			}

			long lLaenge = 0L;
			lLaenge = LinienLaenge(lONr);
			char *pGewName = TRiASGewaesserName ( lONr,m_pKH->CodeGewName());
			if ( pGewName ) {

				if ( m_hLib->GewaesserNeuAnlegen ( pGewNr, pGewName, lLaenge)) {
					DELETE_OBJ ( pGewName);
				} else {
					RestoreGewNr(lONr,pBuffer);
					DELETE_OBJ(pGewName);
				}


			} else {
				if ( !m_hLib->GewaesserNeuAnlegen ( pGewNr, pGewNr, lLaenge))
					RestoreGewNr(lONr,pBuffer);

			}

		DELETE_OBJ(pBuffer);
		}
		DELETE_OBJ(pGewNr);
		MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		return true;
	}
	MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	return false;

}
//---------------------------------------------------------------------
void CKompiasExtension :: ErfasseTempDaten ( void )
{
	CEierUhr Wait ( MVWind());

	if ( m_pModObj) {
		CTreeLoeschen(m_pModObj);
		DELETE_OBJ ( m_pModObj);
	}

	m_pModObj = new TR_OBJTree;
	if ( !m_pModObj)
		return;

	char *pCode = new char [_MAX_PATH];
	if ( !pCode ) {
		DELETE_OBJ ( m_pModObj);
		return;
	}

	wsprintf( pCode, ResString( ResID( IDS_OBJEKTSYSCODE,&g_pTE->RF()),40));

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	ulong lMCode = DEX_GetMCodeFromFeatureNameEx ( hPr,pCode );
#else
	ulong lMCode = DEX_GetMCodeFromFeatureName ( pCode );
#endif


	DELETE_OBJ ( pCode);
	if ( lMCode == 0L) {
		DELETE_OBJ ( m_pModObj);
		return;
	}

	if ( DEX_isMCodeUsed(lMCode)) {

		ENUMRECHTEXTMERKMAL EM;
		memset (&EM, '\0', sizeof(ENUMRECHTEXTMERKMAL));
		EM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
		EM.lMCode = (long)lMCode;
		EM.iMode = SMExactMatch;
		EM.eFcn = (RECHTEXTMERKMALCALLBACK) FindeTempObjekt;
		EM.pData = m_pModObj;
		DEX_EnumRechTextMerkmal(EM);
	}


	if ( m_pModObj && m_pModObj->Count() > 0L) {
		CTreeLoeschen(m_pModObj);
		DELETE_OBJ ( m_pModObj);
	} else {
		DELETE_OBJ ( m_pModObj);
	}
}
//---------------------------------------------------------------------
KPTree * CKompiasExtension :: HoleLeistungenVonKompakt ( short iTyp )
{
//	CEierUhr Wait (MVWind());
	KPTree *pGew = new KPTree;
	if ( !pGew) 
		return NULL;


	// Anpassung an Philosophie Bauwerke : bei neuen L pro Art+Gewässer löschen
	TR_OCLTree *pIdent = new TR_OCLTree;
	if ( !pIdent)
		return NULL;


	LEISTUNGPROC pFcn = ( LEISTUNGPROC) UebergebeLeistungen;

//	Neuer DatenPool analog Bauwerke
	{
	BAUWERKSINPUT BI;
	BI.pGew = pGew;
	BI.pIdent = pIdent;
	BI.lCount = 0L;

//	m_hLib->EnumeriereLeistung ( iTyp, pFcn, DWORD(pGew) );
	m_hLib->EnumeriereLeistung ( iTyp, pFcn, DWORD(&BI) );

	}

//	Alte Leistungen entfernen
	if ( pGew->Count() > 0L) {
		CEierUhr Wait (MVWind());
		CTable t (*pIdent);
		for ( t.First(); t.Valid(); t.Next()){
			TR_OCLLock l(t);
			if (!l)
				continue;
			TR_OBJTree *pObj = l->OBJ();
			if ( !pObj) 
				DEX_DeleteAllIdentObjects(l->Ident());
			else
				LoeschenEinzelBauwerke(pObj);
		}
	}
	DELETE_OBJ ( pIdent);


	return pGew;
}
//---------------------------------------------------------------------

//---------------------------------------------------------------------
KPTree * CKompiasExtension :: HoleBauwerkeVonKompakt ( short iTyp )
{
//	CEierUhr Wait (MWind());

		
	KPTree *pGew = new KPTree;
	if ( !pGew) 
		return NULL;

	TR_OCLTree *pIdent = new TR_OCLTree;
	if ( !pIdent)
		return NULL;


	BAUWERKEPROC pFcn = ( BAUWERKEPROC) UebergebeBauwerke;

	{
	BAUWERKSINPUT BI;
	BI.pGew = pGew;
	BI.pIdent = pIdent;
	BI.lCount = 0L;
	KompaktProtokoll ( m_pLocProt,"\t # Anforderung : Bauwerke von Kompakt\n\n");

//	m_hLib->EnumeriereBauwerke ( iTyp, pFcn, DWORD(pGew) );
	m_hLib->EnumeriereBauwerke ( iTyp, pFcn, DWORD(&BI) );

	}

	KompaktProtokoll ( m_pLocProt,"\t # TRiAS : Bauwerke von Kompakt-Start der Abarbeitung\n\n");

	if ( pGew->Count() > 0L) {
		CEierUhr Wait (MVWind());

		if ( 0L == pIdent->Count()) {
			DELETE_OBJ(pIdent);
			return pGew;
		}

		CTable t (*pIdent);
		long lNum = pIdent->Count();

		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
		UnRegisterNotification (DEX_OBJECTSELECTED);
		UnRegisterNotification (DEX_N_OBJECTCREATED);
		UnRegisterNotification (DEX_DELOBJECT);
		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		ResString resCaption (ResID(IDS_CPTDELBAUWERKE, &RF()), 50);

		m_pStatus = new CStatus ( MVWind(), &RF(), lNum, resCaption);

//		m_pStatus = new CStatus ( MVWind(), &RF(), lNum, "Leistungen/Ereignisse löschen");
		m_pStatus->Show();

		m_iCount = 0;

		for ( t.First(); t.Valid(); t.Next()){

		   if ( m_pStatus->Break()) {
		
				MessageBox ( __hWndM ,
				"Löschen abgebrochen", 
	//			 ResString (ResID(IDS_SPEICHERNSTOP, &RF()),80),
				 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
				 MB_OK|MB_ICONEXCLAMATION);

				DELETE_OBJ ( m_pStatus);
				DELETE_OBJ ( pIdent);
				return pGew;

			}

			TR_OCLLock l(t);
			if (!l)
				continue;
			TR_OBJTree *pObj = l->OBJ();
			if ( !pObj)
				DEX_DeleteAllIdentObjects(l->Ident());
			else

				LoeschenEinzelBauwerke(pObj);

			m_iCount++;

			if ( m_pStatus) 
				m_pStatus->SetValue((long)m_iCount, l->Ident());


		}

		MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
		RegisterNotification (DEX_DELOBJECT);
		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
		RegisterNotification (DEX_OBJECTSELECTED);
		RegisterNotification (DEX_N_OBJECTCREATED);

	}

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	DELETE_OBJ ( pIdent);

	return pGew;
}

//---------------------------------------------------------------------
void CKompiasExtension :: LoeschenEinzelBauwerke ( TR_OBJTree *pObj )
{

	if ( !pObj || pObj->Count() == 0L)
		return;

	CTable t(*pObj);

//	CEierUhr Wait (MVWind());

	char *pT = new char [_MAX_PATH];

	long lNum = pObj->Count();

	CStatus *pStatus = new CStatus ( MVWind(), &RF(), lNum, "Leistungen/Ereignisse löschen");
	pStatus->Show();

	short iCount = 0;


	for ( t.First(); t.Valid(); t.Next()) {

		TR_OBJLock l(t);
		if (!l)
			continue;
		if ( pT) {
			wsprintf (pT, " \t Löschen Leistung/Ereignis ON %ld\n",l->Object());
		}

		iCount++;

		if ( pStatus) 
			pStatus->SetValue((long)iCount, l->Object());

		DEX_DeleteObject(l->Object());


	}

	DELETE_OBJ(pStatus);
	DELETE_OBJ(pT);
}

//---------------------------------------------------------------------
KPTree * CKompiasExtension :: HoleGewaesserVonKompakt ( short iTyp )
{
	CEierUhr Wait (MVWind());
	KPTree *pGew = new KPTree;
	if ( !pGew) 
		return NULL;
	
	GEWAESSERPROC pFcn = ( GEWAESSERPROC) UebergebeGewaesser;
	m_hLib->EnumeriereGewaesser ( iTyp, pFcn, DWORD(pGew) );
	if ( pGew->Count() == 0) {
		DELETE_OBJ ( pGew);
		return NULL;
	}
	CTable t (*pGew);
	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);
		if (!l)
			continue;
		l->TauscheZuKompakt();
	}
	return pGew;
}
//----------------------------------------------------------------------
//---------------------------------------------------------------------
KPTree * CKompiasExtension :: HolePunktVonKompakt ( LPARAM p )
{
	CEierUhr Wait (MVWind());
	KPTree *pGew = new KPTree;
	if ( !pGew) 
		return NULL;

	char *pGewNr = ((HYDRAULIK *)p)->pcGewaesserNr;
	long lPos = ((HYDRAULIK *)p)->lPos;
	double dHoehe =((HYDRAULIK *)p)->dHoehe;
	CTable t (*pGew);

	if ( !t.Find( pGewNr)) {
		KP_LATree *pLA = new KP_LATree;
		if (!pLA)
			return NULL;

		LEISTUNGEN LS;
		memset (&LS, '\0', sizeof(LEISTUNGEN));
		LS.dwSize = sizeof(LEISTUNGEN);
		LS.pcGewaesserNr = pGewNr;
		LS.iIdentNrHerkunft = cHydraulikHochwasser ;
		LS.iIdentNrZuordnung = cUeberschwemmungsPunkt;
		LS.lEnde = lPos;
		LS.dKostetDM = dHoehe;

		KOMPAKTDATEN KD;
		if (!LeistungenInKompakt ( &LS, &KD) )
			return NULL;

		GEWAESSER GW;
		memset (&GW, '\0', sizeof(GEWAESSER));
		GW.dwSize = sizeof(GEWAESSER);
		GW.pcGewaesserNr = pGewNr;
		GW.lEnde = lPos;

		KP_LACreator KPLACr ( *pLA);
		ContCreate (KPLACr, KP_LA) ( 1, &KD);
		KP_GEWCreator KPCr ( *pGew);
		ContCreate (KPCr,KP_GEW) (&GW, pLA);
	}
	return pGew;
}
//--------------------------------------------------------------------
//---------------------------------------------------------------------
bool CKompiasExtension :: HolePunkteVonKompakt (KPTree *pGew, LPARAM p )
{
	CEierUhr Wait (MVWind());

	if ( !pGew) 
		return false;

	char *pGewNr = ((HYDRAULIK *)p)->pcGewaesserNr;
	long lPos = ((HYDRAULIK *)p)->lPos;
	double dHoehe =((HYDRAULIK *)p)->dHoehe;

	CTable t (*pGew);
	KOMPAKTDATEN KD;

	if ( !t.Find( pGewNr)) {

		KP_LATree *pLA = new KP_LATree;
		if (!pLA)
			return NULL;

		LEISTUNGEN LS;
		memset (&LS, '\0', sizeof(LEISTUNGEN));
		LS.dwSize = sizeof(LEISTUNGEN);
		LS.pcGewaesserNr = pGewNr;
		LS.iIdentNrHerkunft = cHydraulikHochwasser ;
		LS.iIdentNrZuordnung = cUeberschwemmungsPunkt;
		LS.lEnde = lPos;
		LS.dKostetDM = dHoehe;

		if (!LeistungenInKompakt ( &LS, &KD) )
			return NULL;

		GEWAESSER GW;
		memset (&GW, '\0', sizeof(GEWAESSER));
		GW.dwSize = sizeof(GEWAESSER);
		GW.pcGewaesserNr = pGewNr;
		GW.lEnde = lPos;

		KP_LACreator KPLACr ( *pLA);
		ContCreate (KPLACr, KP_LA) ( 1, &KD);
		KP_GEWCreator KPCr ( *pGew);
		ContCreate (KPCr,KP_GEW) (&GW, pLA);

	} else {

		KP_GEWLock l(t);
		KP_LATree *pLA = l->LA();
		if (!pLA)
			return false;
		long lCount = (long) pLA->Count() + 1;

		LEISTUNGEN LS;
		memset (&LS, '\0', sizeof(LEISTUNGEN));
		LS.dwSize = sizeof(LEISTUNGEN);
		LS.pcGewaesserNr = pGewNr;
		LS.iIdentNrHerkunft = cHydraulikHochwasser ;
		LS.iIdentNrZuordnung = cUeberschwemmungsPunkt;
		LS.lEnde = lPos;
		LS.dKostetDM = dHoehe;

		if (!LeistungenInKompakt ( &LS, &KD) )
			return NULL;

		KP_LACreator KPLACr ( *pLA);
		ContCreate (KPLACr, KP_LA) ( lCount, &KD);
	}
	return true;
}

//---------------------------------------------------------------------
void CKompiasExtension :: HoleGewaesserVonTRiAS ( void )
{
	CEierUhr Wait (MVWind());

	KPTree *pGew = new KPTree;
	if ( !pGew) 
		return;
	LadeObjektKlasse ( OTLinie, m_pKH->GewClass());

	m_pGew = SpeichernGewaesserNummer ( m_pKH->CodeGewNr(),m_pKH->CodeGewName(),m_pKH->GewClass());

	return;
}
//----------------------------------------------------------------------
//---------------------------------------------------------------------
void CKompiasExtension :: HoleBauwerkeVonTRiAS ( void )
{

	CEierUhr Wait (MVWind());

	TR_OCLTree *pBauw = LadeBauwerkeKlassen();

	if ( !pBauw || pBauw->Count() == 0L) {
		DELETE_OBJ ( pBauw);
		return;
	}

	if ( m_pTRGew)
		DELETE_OBJ ( m_pTRGew);

	m_pTRGew = SammeleAlleBauwerke ( pBauw);

	if ( !m_pTRGew) {
		DELETE_OBJ ( pBauw);
		return;
	}

	if(!DefiniereBauwerksParameter(m_pTRGew)) 
		DELETE_OBJ (m_pTRGew);

	DELETE_OBJ ( pBauw);

	return;
}
//----------------------------------------------------------------------
TR_OBJTree *CKompiasExtension :: SammeleAlleBauwerke ( TR_OCLTree *pBauw)
{
	if ( !pBauw || pBauw->Count() == 0L)
		return NULL;

	TR_OBJTree *pTRGew = new TR_OBJTree;

	if ( !pTRGew) 
		return NULL;

	CTable t(*pBauw);

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheBauwObjekt;

	OBJEKTKLASSENTYP OT;
	OT.iTyp = OTLinie | OTPunkt;
	OT.pOBJ = pTRGew;
	OT.lONr = -1L;
	if ( m_lONrBauw > 0L ) {			// Einzelbauwerk aus Geometrieeditierung
		OT.lONr = m_lONrBauw;
		ELK.eFcn = ( ENUMLONGKEYPROC) SucheBauwEinzelObjekt;
		SucheBauwEinzelObjekt(m_lONrBauw,true,&OT);
	} else {

		for ( t.First(); t.Valid(); t.Next()) {
			TR_OCLLock l(t);
			if (!l) continue;
			long Ident = l->Ident();
			ELK.eKey = Ident;
			ELK.ePtr = &OT;
			DEX_EnumIdentObjects(ELK);
		}   
	
	}

    if ( pTRGew->Count() == 0L)
		DELETE_OBJ ( pTRGew);

	return pTRGew;
}
//////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: DefiniereBauwerksParameter ( TR_OBJTree *pBauwO)
{
	if ( !pBauwO || pBauwO->Count() == 0L)
		return false;

	if ( !m_pKH || m_pKH->CodeGewNr() <= 0L)
		return false;

	long lMGewNr = m_pKH->CodeGewNr();
	long lMVon = m_pKH->CodeBauwAnfStat();
	long lMBis = m_pKH->CodeBauwEndStat();
	long lMBez = m_pKH->CodeBauwBez();
	long lMName = m_pKH->CodeBauwName();
	

	if ( lMVon == 0L || lMBis == 0L || lMBez == 0L )
		return false;

	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return false;

	CTable t (*pBauwO);
	
	long RW = 0;
	long HW = 0;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.iTTyp = TT_Objekt;
	tm.lMCode = lMGewNr;		// MerkmalsCode

	// nur für GeometrieObjekte
	OBJSTATISTIK OS;
	INITSTRUCT(OS, OBJSTATISTIK);

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OBJLock l(t);
		if (!l) continue;
		long lONr = l->Object();
		long lIdent = DEX_GetObjIdent(lONr);
		short iBauTyp = BauwerkeTyp(lIdent);
		l->SetTyp( iBauTyp);

		int iOTyp = DEX_GetObjectType(lONr);

		OS.lONr = lONr;
		if (!DEX_GetObjStatistik(OS))
			return false;		// irgend was ist faul

		if (OGPunkt == iOTyp ) {

			if ( m_pObjRechts ) {
				char *pName = new char [_MAX_PATH];
				if ( pName ) {
					m_pObjRechts->Eval(l->Object(),pName,64,NULL);
					RW = atol(pName);
					DELETE_OBJ ( pName);
				}
			}

			if ( m_pObjHoch ) {
				char *pName = new char [_MAX_PATH];
				if ( pName ) {
					m_pObjHoch->Eval(l->Object(),pName,64,NULL);
					HW = atol(pName);
					DELETE_OBJ ( pName);
				}
			}

		} else {

			OBJGEOMETRIE OG;

			double *dXV = new double [OS.lCnt];
			double *dYV = new double [OS.lCnt];

			if (!dXV || !dYV ) {
				DELETE_OBJ(dXV);
				DELETE_OBJ(dYV);
				return false;
			}

			INITSTRUCT(OG, OBJGEOMETRIE);
			OG.lONr = lONr;
			OG.lCnt = OS.lCnt;
			OG.pdblX = dXV;
			OG.pdblY = dYV;
			OG.iFlags = OGConverted;

			if (!DEX_GetObjGeometrie(OG)) {
				DELETE_OBJ(dXV);
				DELETE_OBJ(dYV);
				return false;		// irgend was ist faul
			}

			RW = (long) *dXV;
			HW = (long) *dYV;

			DELETE_OBJ(dXV);
			DELETE_OBJ(dYV);

		}

		l->SetKoordinate ( RW,HW);

		tm.lMCode = lMGewNr;		// MerkmalsCode
		*pBuff = '\0';		
		tm.lTarget = l->Object();		// Objekt
		tm.imaxLen = _MAX_PATH;
		tm.pMText =pBuff;		// Puffer

		{
		ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
		DEX_GetTextMerkmal ( tm );
		}
		if (*pBuff != '\0') {
			l->SpeichernGewaesserNummer(pBuff);
		}


		tm.lMCode = lMBez;		// MerkmalsCode
		*pBuff = '\0';		
		tm.lTarget = l->Object();		// Objekt
		tm.imaxLen = _MAX_PATH;
		tm.pMText =pBuff;		// Puffer

		{
		ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
		DEX_GetTextMerkmal ( tm );
		}
		if (*pBuff != '\0') {
			l->SpeichernBezeichnung(pBuff);
		} else {
			strcat (pBuff,"TuellPointer");	 // G.P. bei Malte, wenn Bezeichner nicht belegt
			l->SpeichernBezeichnung(pBuff);	 // auf Wunsch von Malte nur Umgehenen des Fehlers - Kompakt1 tickt !!!
		}

// Unique auflösen und ObjectIdent bilden

		#if _MSC_VER < 1100
				tm.lMCode = DEX_GetUniqueIdentMCode();		// MerkmalsCode
		#else
				HPROJECT hPr = DEX_GetObjectsProject(lIdent);
				tm.lMCode = DEX_GetUniqueIdentMCodeEx(hPr);		// MerkmalsCode
		#endif

		*pBuff = '\0';		
		tm.lTarget = l->Object();		// Objekt
		tm.imaxLen = _MAX_PATH;
		tm.pMText =pBuff;		// Puffer

		{
		ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
		DEX_GetTextMerkmal ( tm );
		}
		if (*pBuff != '\0') {
			long lObjIdent = 0L;
			if ( strncmp ("BWIdent-",pBuff,6) == 0) {	// Bei NeuAnlage Ident = 0 übergeben !
				char *ptr = strrchr(pBuff,'_');
				if (ptr)
					lObjIdent = atol(ptr+1);
			}

			l->SetObjectIdent(lObjIdent);
		}
		
		
		// Und nun noch der Name

		tm.lMCode = lMName;		// MerkmalsCode
		*pBuff = '\0';		
		tm.lTarget = l->Object();		// Objekt
		tm.imaxLen = _MAX_PATH;
		tm.pMText =pBuff;		// Puffer

		{
		ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
		DEX_GetTextMerkmal ( tm );
		}
		if (*pBuff != '\0') 
			l->SpeichernGewaesserName(pBuff);
//--------------------------------------------------------------
		
		long lRVon = 0L;
		long lRBis = 0L;

		tm.lMCode = lMVon;		// MerkmalsCode
		*pBuff = '\0';		
		tm.lTarget = l->Object();		// Objekt
		tm.imaxLen = _MAX_PATH;
		tm.pMText =pBuff;		// Puffer

		{
		ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
		DEX_GetTextMerkmal ( tm );
		}
		if (*pBuff != '\0') 
			lRVon = atol ( pBuff);
		tm.lMCode = lMBis;		// MerkmalsCode
		*pBuff = '\0';		
		tm.lTarget = l->Object();		// Objekt
		tm.imaxLen = _MAX_PATH;
		tm.pMText =pBuff;		// Puffer

		{
		ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
		DEX_GetTextMerkmal ( tm );
		}

		if (*pBuff != '\0') 
			lRBis = atol ( pBuff);

		l->SetIntervall(lRVon,lRBis);


	}             

	DELETE_OBJ ( pBuff);

	return true;

}

//////////////////////////////////////////////////////////////////////
short CKompiasExtension :: BauwerkeTyp ( long lIdent) 
{
	if (lIdent == 0L)
		return -1;
	ulong ulRef = lIdent;
	char NewIdent[MAX_OKS_LENX];

	#if _MSC_VER < 1100
		ClassFromIdentX ( ulRef, NewIdent);
	#else
		HPROJECT hPr = DEX_GetObjectsProject(ulRef);
		ClassFromIdentX ( hPr,ulRef, NewIdent);
	#endif

//	long lRef = atol(NewIdent);
	long lRef = atol(NewIdent+1);

	long lRef1 = cBauwerkeIdent * 1000;
	lRef1 = lRef - lRef1;
	short iZuo = (short) lRef1;
	return iZuo;

}
/////////////////////////////////////////////////////////////////////
void CKompiasExtension :: ZeigeObjektVonTRiAS ( HWND hWnd, KOORDINATEN *p) 
{

	if (!p)
		return;

	if (!m_pKH)
		return;

	LadeEinzelGewaesser ( hWnd, p, OTLinie, m_pKH->GewClass());

	if (!m_pTRGew)
		return;


	CTable t(*m_pTRGew);

	t.First();
	TR_OBJLock l(t);
	if (!l)
		return;

	long lONr = l->Object();

	long Cont[4];

	DEX_GetObjContainer(lONr,Cont[0]);

	DEX_SetActiveSightContainer (Cont);

	long *pObj = new long [2];
	*pObj = 1L;
	*(pObj+1) = lONr;
	short Flag = ROSortObjNr;
	CreateORWindow ( Flag, 80, 100, pObj, ResString (ResID(IDS_GEWNUMMER, &RF()),50).Addr(), 0, 255, 255);
	DELETE_OBJ ( pObj);
	DEX_RebuildSight();

	return;	
}
//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
void CKompiasExtension :: HoleKoordinatenVonTRiAS ( HWND hWnd, KOORDINATEN *p) 
{

	if (!p)
		return;

	if (!m_pKH)
		return;

	if (!m_pKH->GewClass() )
		return;

	if (m_pKH->GewClass()->Count() == 0L)
		return;

	p->lError = 0L;

	p->lAbstand = 0L;

	try {

		CEierUhr Wait (MVWind());


//	Hier müßte Station mit Länge Gewässer verglichen werden !

		LadeEinzelGewaesser ( hWnd, p, OTLinie, m_pKH->GewClass());

	} catch ( ... ) {

		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRTRNOGEWLOAD, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cGewaesserNichtVorhanden;

		return;

	}

	if (!m_pTRGew){
		p->lError = cGewaesserNichtVorhanden;
		return;
	}
	if ( m_pTRGew->Count() == 0L){
		p->lError = cGewaesserNichtVorhanden;
		return;
	}

	if ( m_pTRGew->Count() > 1L)
		p->lError = cMultiGewaesser;

	if ( lfctGibKoordinate == p->lIdent )
		SetzeKoordinate(p);

	if ( lfctGibStation == p->lIdent )
		SetzeStation(p);

	return;
}
//------------------------------------------------------------------------------
void CKompiasExtension :: SetzeKoordinate ( KOORDINATEN *p)
{
	if ( ! m_pTRGew || m_pTRGew->Count() == 0L)
		return;

	CTable t(*m_pTRGew);

	t.First();
	TR_OBJLock l(t);
	if (!l)
		return;

	long lStartPunkt =  ObjektStartPunkt(l->Object(),m_pKH->CodeBauwAnfStat());
	

	if ( p->lStation < lStartPunkt) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRKPNOSTATION, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cFehlerhafteDaten;

		return;
	}

	if ( m_pObjPropL ) {

/*------------------------------------------
		char * pName = new char [_MAX_PATH];
		if ( !pName)
			return;
		m_pObjPropL->Eval(l->Object(),pName,64,NULL);

		long lLen = atol ( pName);
		// km oder m
		double dLen;
		char *ptr = strchr(pName,'[');
		double dFak = 1.0;
		if (ptr) {
			ptr++;
			if ('k' == *ptr)
				dFak = 1000.0;
		}

		dLen = atof ( pName);
		dLen = dLen * dFak;
		dLen = dLen + 0.5;


		DELETE_OBJ ( pName);
------------------------------------------------*/
	// Hier relative Stationen bei Verschiebungen ausrechnen
		long lLen = LinienLaenge(l->Object());

		if (p->lStation > lLen +lStartPunkt) {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_ERRKPNOSTATION, &g_pTE->RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
			 MB_OK|MB_ICONHAND);
			p->lError = cFehlerhafteDaten;
			return;
		}
	}


	GEWSTRUKTUR GW;
   	memset (&GW,'\0',sizeof(GEWSTRUKTUR));
	GW.dwSize = sizeof(GEWSTRUKTUR);
	GW.lMCode = m_pKH->CodeGewNr();
	GW.lONr = l->Object();
	GW.pMText = p->pcGewaesserNr;
	long lIdent = DEX_GetObjIdent(l->Object());

	if ( !PruefeTriasObjekt ( &GW))
			return;
	if ( !LadeTriasObjekt(&GW))
		return;
	if (!BildeKompaktObjekt (&GW,p->lStation,p->lStation))
		return;

	GW.lIdent = lIdent;

	if ( !BildePunkt(&GW)) 
		return;

	if ( m_pObjRechts ) {
		if ( p->pcRechtsWert) {
			char *pRechts = new char [_MAX_PATH];
			m_pObjRechts->Eval(GW.lNewONr,pRechts,64,NULL);
			strncpy(p->pcRechtsWert,pRechts,strlen(p->pcRechtsWert));

/*----
			try {
				strncpy(p->pcRechtsWert,pRechts,7);
			} catch (...) {
				MessageBox (__hWndM, 
				"Kompakt : fehlender Speicher",
				 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
				 MB_OK|MB_ICONHAND);
			}
----------------------*/

			DELETE_OBJ ( pRechts);
		}
	}

	if ( m_pObjHoch ) {
		if (p->pcHochWert) {
			char *pHoch = new char [_MAX_PATH];
			m_pObjHoch->Eval(GW.lNewONr,pHoch,64,NULL);
			strncpy(p->pcHochWert,pHoch,strlen(p->pcHochWert));

	/*-------------------------------
			try {
				strncpy(p->pcHochWert,pHoch,7);
			} catch (...) {
				MessageBox (__hWndM, 
				"Kompakt : fehlender Speicher",
				 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
				 MB_OK|MB_ICONHAND);
			}
	------------------------------*/

			DELETE_OBJ ( pHoch);
		}
	}

	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	DEX_DeleteObject(GW.lNewONr);

	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
	MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	return;	
}
//////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
void CKompiasExtension :: SetzeStation ( KOORDINATEN *p)
{
	if ( ! m_pTRGew || m_pTRGew->Count() == 0L)
		return;

	CTable t(*m_pTRGew);

	t.First();
	TR_OBJLock l(t);
	if (!l)
		return;

	long lNewONr = SetzeKompaktPunkt(p,l->Object());
	if ( lNewONr == -1L || lNewONr == 0L) {
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_ERRORKOORDINATE, &g_pTE->RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
		 MB_OK|MB_ICONHAND);
		p->lError = cKoordinatenFalsch;

		return;
	}

	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	DEX_DeleteObject(lNewONr);

	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
	MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

	return;	
}
//////////////////////////////////////////////////////////////////////
long CKompiasExtension :: SetzeKompaktPunkt (KOORDINATEN *p, long lGewNr)
{
	long lONr = 0L;
	long lCnt = 1L;

	long *pX = new long[2];
	long *pY = new long[2];

	long lRechts;
	long lHoch;

	lRechts = atol(p->pcRechtsWert);
	lHoch = atol(p->pcHochWert);

	if ( !m_pCTF)
		m_pCTF = new CoordTransX;

	double Min,Max;
	if ( m_pCTF == NULL ) {
		return 0L;
	}

	Punkt P;
	Punkt B;

	Min = (double)lRechts;
	Max = (double)lHoch;

	m_pCTF->Native (Min, Max, P);
//	m_pCTF->Scale ( Min, Max, P);

#if _MSC_VER >= 1100
	*pX = P.GetX();
	*pY = P.GetY();
#else
	*pX = P.X();
	*pY = P.Y();

#endif

//	lRechts = P.X();
//	lHoch = P.Y();


	long lIdent = DEX_GetObjIdent(lGewNr);

	OBJGEOMETRIE OG;
	memset (&OG,'\0',sizeof(OBJGEOMETRIE));
	OG.dwSize = sizeof(OBJGEOMETRIE);
	OG.lIdent = lIdent;
	OG.lONr = lONr;
	OG.lCnt = lCnt;
	OG.iObjTyp = OT_PUNKT;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.iFlags = OGNewObject | OGIgnoreIdent;

	if ( !DEX_ModObjGeometrie (OG)) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return 0L;
	}

	lONr = OG.lONr;

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  lGewNr;
	{
	ErrInstall EI ( EC_DELRECORD);
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE ) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//			MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
			MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

			DEX_DeleteObject(lONr);

			MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//			MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
			MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

			return 0L;
		}
		if ( !ObjektIstGewaesser(OS.lONr)) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//			MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
			MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

			DEX_DeleteObject(lONr);

			MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//			MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
			MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

			return 0L;
		}

	} else {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		DEX_DeleteObject(lONr);

		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		return 0L;
	}
	}

//------------Interface ------------------------------------
//	ObjektGeometrie der Kante holen - m_pIOG
	if ( !LadeObjektGeometrie ( lGewNr)) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		DEX_DeleteObject(lONr);

		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		return 0L;
	}
	
	double dAbstand = 0.0;
	if (!m_pAbst) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		DEX_DeleteObject(lONr);

		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
		return 0L;
	}

	HRESULT hr = m_pAbst->DistanceFromOrigin_Geom(m_pIOG,pX,pY,&dAbstand);
	if (FAILED(hr)) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		DEX_DeleteObject(lONr);

		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
		return 0L;
	}

#if _MSC_VER >= 1100
	HRESULT ho = B.SetX(*pX);
	ho = B.SetY(*pY);
#else
	B.X() = *pX;
	B.Y() = *pY;
#endif

	dAbstand = dAbstand + 0.5;

	long lStartPunkt =  ObjektStartPunkt(lGewNr,m_pKH->CodeBauwAnfStat());

	p->lStation = (long)dAbstand + lStartPunkt;

	double dA1;
	double dE1;

	double dA2;
	double dE2;

	m_pCTF->UnScale(P,&dA1,&dE1);

	m_pCTF->UnScale(B,&dA2,&dE2);

	DoublePair AP,EP;

	AP = DoublePair ( dA1, dE1);
	EP = DoublePair ( dA2, dE2);

	double dDiff = m_pCTF->CoordTransDistance(&AP,&EP);
	dDiff = dDiff + 0.5;

	p->lAbstand = (long)dDiff;

	DELETE_OBJ (pX);
	DELETE_OBJ (pY);

	return lONr;
}
//---------------------------------------------------------------------
void CKompiasExtension :: LadeEinzelGewaesser ( HWND hWnd, KOORDINATEN *p, short iTyp, TR_OCLTree *pGewClass)
{
	if ( m_pTRGew)
		DELETE_OBJ ( m_pTRGew);

	if ( !pGewClass)
		return;

	if ( p->lStation < 0L)
		return;

	m_pTRGew = new TR_OBJTree;

	CTable t (*pGewClass);

	CEierUhr Wait (MVWind());

	long lCount = 0L;

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	pWindow pW = ORWind(hWnd);

	lCount = pGewClass->Count();

	ResString resCaption (ResID(IDS_CPTGEWAESSER, &RF()), 50);

	m_pStatus = new CStatus ( pW, &RF(), lCount, resCaption);

//	m_pStatus = new CStatus ( pW, &RF(),lCount, "Gewässer");
	m_pStatus->Show();

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheEinzelGewaesserObjekt;
	lCount = 0;
	OBJEKTKLASSENTYP OT;
	OT.pOBJ = m_pTRGew;
	OT.iTyp = iTyp;
	OT.lMCode = m_pKH->CodeGewNr();
	OT.pMWert = p->pcGewaesserNr;

//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();

		ELK.eKey = Ident;
		ELK.ePtr = &OT;

		DEX_EnumIdentObjects(ELK);

		lCount ++;

		if ( m_pStatus) {
			m_pStatus->SetValue( lCount, Ident);
		}

	}

	DELETE_OBJ (m_pStatus);
	if ( m_pTRGew->Count() == 0L)
		DELETE_OBJ ( m_pTRGew);

	return ;
}

/////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
void CKompiasExtension :: LadeObjektKlasse ( short iTyp, TR_OCLTree *pGewClass)
{
	if ( !pGewClass)
		return;


	CTable t (*pGewClass);

	CEierUhr Wait (MVWind());

	long lCount = 0L;

	lCount = pGewClass->Count();

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheGewaesserObjekt;
	lCount = 0;
	OBJEKTKLASSENTYP OT;
	OT.iTyp = iTyp;

//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();

		TR_OBJTree *pOBJ = new TR_OBJTree;
		ELK.eKey = Ident;
		OT.pOBJ = pOBJ;
		ELK.ePtr = &OT;
		DEX_EnumIdentObjects(ELK);
		lCount ++;

		if ( pOBJ->Count() == 0 )  {
			DELETE_OBJ ( pOBJ);
		} else {

			pOBJ->Optimize();

			l->StoreObj( pOBJ);
		}

	}


	return ;
}
	
//----------------------------------------------------------------------
//---------------------------------------------------------------------
TR_OCLTree *CKompiasExtension :: LadeBauwerkeKlassen ( void )
{

	if ( !m_pKH)
		return NULL;

	TR_OCLTree *pBWClass = new TR_OCLTree;

	if ( !pBWClass)
		return NULL;

//------------BauwerkeKlassen laden ----------------------------

//	Alle O'Klassen formal durchzählen und Baum anlegen

	GEWAESSERKLASSE GK;
	GK.pTRGew = pBWClass;
	GK.lGewCode = m_pKH->CodeBauwKl();
	GK.iTyp = PM_BAUWERKE;

	ENUMNOKEYLONG ENL;
//	Bestimmen der Anzahl der Objektklassen
//	ENL.eFcn = ( ENUMNOKEYLONGPROC) SucheBauwKlassen;
	ENL.eFcn = ( ENUMNOKEYLONGPROC) SucheKompaktKlassen;
	ENL.ePtr = &GK;
	DEX_EnumIdents(ENL);

	if ( pBWClass->Count() == 0) {
		DELETE_OBJ ( pBWClass);
		return NULL;
	}

	return pBWClass;
}
	
//----------------------------------------------------------------------
//---------------------------------------------------------------------
TR_OCLTree *CKompiasExtension :: LadeBauwerkeTeilKlassen ( char *pGewNr )
{

	if ( !m_pKH)
		return NULL;
	if (!pGewNr || *pGewNr == '\0')
		return NULL;

	TR_OCLTree *pBWClass = new TR_OCLTree;

	if ( !pBWClass)
		return NULL;

//------------BauwerkeKlassen laden ----------------------------

//	Alle O'Klassen formal durchzählen und Baum anlegen

	GEWAESSERKLASSE GK;
	GK.pTRGew = pBWClass;
	GK.lGewCode = m_pKH->CodeBauwKl();
	GK.lGewNrCode = m_pKH->CodeGewNr();
	GK.pGewNr = pGewNr;
	GK.iTyp = PM_BAUWERKE;

	ENUMNOKEYLONG ENL;
//	Bestimmen der Anzahl der Objektklassen
	ENL.eFcn = ( ENUMNOKEYLONGPROC) SucheBauwEinzelKlassen;
	ENL.ePtr = &GK;
	DEX_EnumIdents(ENL);

	if ( pBWClass->Count() == 0) {
		DELETE_OBJ ( pBWClass);
		return NULL;
	}

	return pBWClass;
}
	
//---------------------------------------------------------------------
TR_OBJTree *CKompiasExtension :: FindeBauwerkeTeilKlassen ( char *pGewNr , long lONr)
{

	if ( !m_pKH)
		return NULL;

	if (!pGewNr || *pGewNr == '\0')
		return NULL;

	if ( lONr == -1L || lONr == 0L )
			return NULL;


	//	ON definiert ????
	OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  lONr;
	long lFONr = 0L;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS)) {

			if ( OS.iObjTyp != OT_KANTE ) 
					return NULL;

			if ( !m_pTop) 
					LadeTopRel();

			if ( !m_pPuf) 
					LadePuffer();

			lFONr = ObjektPuffer ( lONr);

			if ( lFONr == -1L || lFONr == 0L)
				return NULL;


	}


	TR_OCLTree *pBWClass = m_pKH->BauwClass();

	if ( !pBWClass)
		return NULL;

	TR_OBJTree *pObj = new TR_OBJTree;

	if ( !pObj)
		return NULL;


	long *pCont = ObjectContainer ( lFONr, OT_FLAECHE);

	EREIGNISTYP ET;
	ET.pBauw = pBWClass;
	ET.pObj = pObj;
	ET.lONF = lFONr;
	ET.pTop = m_pTop;
	
	ENUMRECHGEOMETRIE ERGI;
	memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
	ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
	ERGI.lCont = pCont;
	ERGI.iMode = ERGActSight;
//	Objekte zählen
	ERGI.eFcn = (RECHGEOMETRIEPROC) EnumBauwerke;
	ERGI.pData = &ET;
	DEX_EnumRechGeometrie( ERGI );

	DELETE_OBJ ( pCont);

	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
	DEX_DeleteObject(lFONr);
	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
	MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
	

	if ( pObj->Count() == 0) {
		DELETE_OBJ ( pObj);
		return NULL;
	}

	return pObj;
}
	
//----------------------------------------------------------------------
//----------------------------------------------------------------------
bool CKompiasExtension :: LadeGewaesserNummer ( ulong lMCode, ulong lMCodeN, TR_OCLTree *pTRGew )
{
	
	if ( !pTRGew || lMCode == 0L || lMCodeN == 0L) 
		return false;

	CEierUhr Wait (MVWind());

	if ( m_pStatus)
		DELETE_OBJ (m_pStatus);

	long lNum = pTRGew->Count();
	long lNr = lNum * 100L;
	long lCount = 0L;

	ResString resCaption (ResID(IDS_CPTGEWABGLEICH, &RF()), 50);

	m_pStatus = new CStatus ( MVWind(), &RF(), lNr, resCaption);

//	m_pStatus = new CStatus ( MVWind(), &RF(), lNr, "Gewässerabgleich");
	m_pStatus->Show();

	CTable t (*pTRGew);

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if ( !l)
			continue;
		TR_OBJTree * pOBJ = l->OBJ();
		if ( !pOBJ)
			continue;
		long lRef = pOBJ->Count();
		if ( lRef == 0L)
				continue;

		if ( m_pStatus->Break()) {

			MessageBox ( __hWndM ,
			 ResString (ResID(IDS_STOPANALYSE, &g_pTE->RF()),80),
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);

			DELETE_OBJ ( m_pStatus);
			return false;
		}


		CTable e (*pOBJ);
		for (e.First(); e.Valid(); e.Next() ) {
			TR_OBJLock n(e);
			long ONr = n->Object();

			if ( m_pStatus->Break()) {

				MessageBox ( __hWndM ,
				 ResString (ResID(IDS_STOPANALYSE, &g_pTE->RF()),80),
				 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
				 MB_OK|MB_ICONEXCLAMATION);

				DELETE_OBJ ( m_pStatus);
				return false;
			}

			lCount++;
			long lZahl = lCount * lNr / lRef; 
			if ( m_pStatus) 
				m_pStatus->SetValue( lZahl, ONr);
			char *pGewNr = HoleGewaesserNummer ( ONr, lMCode);
			if (!pGewNr) 
				continue;
//--------Hier könnte auch der GewaesserNameabgleich rein
			DELETE_OBJ ( pGewNr);
		}
	}

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	return true;
}
//--------------------------------------------------------------------------
//KK010814
// Gewässeranzahl bestimmen

long CKompiasExtension :: GesamtGewaesserCount ( TR_OCLTree *pTRGew)
{

	if ( !pTRGew ) 
		return 0;

	CEierUhr Wait (MVWind());

	long lCount = 0L;

	CTable t (*pTRGew);

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if ( !l)
			continue;
		TR_OBJTree * pOBJ = l->OBJ();
		if ( !pOBJ)
			continue;
		long lRef = pOBJ->Count();
		if ( lRef == 0L)
			continue;

		CTable e (*pOBJ);
		for (e.First(); e.Valid(); e.Next() ) {
			TR_OBJLock n(e);
			long ONr = n->Object();
			if ( ONr == -1L || ONr == 0L)
				continue;

			short Status = DEX_GetObjectType (ONr);

	//--------------Zuordnung----------------------------
			if ( Status != OGLinie )
				continue;
			lCount++;
		}
	}

	return lCount;

}

//---------------------------------------------------------------------
KPTree *CKompiasExtension :: SpeichernGewaesserNummer ( ulong lMCode, ulong lMCodeN, TR_OCLTree *pTRGew )
{
	
	if ( !pTRGew || lMCode == 0L || lMCodeN == 0L) 
		return NULL;

	KPTree *pGew = new KPTree;
	if ( !pGew)
		return NULL;


	CEierUhr Wait (MVWind());

	if ( m_pStatus)
		DELETE_OBJ (m_pStatus);

	//KK010814
	// Gewässeranzahl bestimmen

	long lNr = GesamtGewaesserCount ( pTRGew);

//	long lNum = pTRGew->Count();

//	long lNr = lNum * 100L;
	long lCount = 0L;

	ResString resCaption (ResID(IDS_CPTGEWANALYSE, &RF()), 50);

	m_pStatus = new CStatus ( MVWind(), &RF(), lNr, resCaption);

//	m_pStatus = new CStatus ( MVWind(), &RF(), lNr, "Gewässeranalyse");
	m_pStatus->Show();

	CTable t (*pTRGew);

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if ( !l)
			continue;
		TR_OBJTree * pOBJ = l->OBJ();
		if ( !pOBJ)
			continue;
		long lRef = pOBJ->Count();
		if ( lRef == 0L)
			continue;

	    if ( m_pStatus->Break()) {

			MessageBox ( __hWndM ,
			 ResString (ResID(IDS_STOPANALYSE, &g_pTE->RF()),80),
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);

			DELETE_OBJ ( m_pStatus);
			DELETE_OBJ ( pGew);
			return NULL;
		}


		CTable e (*pOBJ);
		for (e.First(); e.Valid(); e.Next() ) {
			TR_OBJLock n(e);
			long ONr = n->Object();
			if ( ONr == -1L || ONr == 0L)
				continue;

			short Status = DEX_GetObjectType (ONr);

	//--------------Zuordnung----------------------------
			if ( Status != OGLinie )
				continue;

		    if ( m_pStatus->Break()) {

				MessageBox ( __hWndM ,
				 ResString (ResID(IDS_STOPANALYSE, &g_pTE->RF()),80),
				 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
				 MB_OK|MB_ICONEXCLAMATION);

				DELETE_OBJ ( m_pStatus);
				DELETE_OBJ ( pGew);
				return NULL;
			}

			lCount++;
//			long lZahl = lCount * lNr / lRef; 
			if ( m_pStatus) 
//				m_pStatus->SetValue( lZahl, ONr);
				m_pStatus->SetValue( lCount, ONr);
			
			char *pGewNr = HoleGewaesserNummer ( ONr, lMCode);
			if (!pGewNr) 
				continue;
			n->SpeichernGewaesserNummer (pGewNr);

			char *pGewName = HoleGewaesserName ( ONr, lMCodeN,pGewNr,false);	// Ohne Malte
//			char *pGewName = HoleGewaesserName ( ONr, lMCodeN,pGewNr,true);	// mit Malte
			if (pGewName && *pGewName != '\0')
				n->SpeichernGewaesserName (pGewName);

			LadeGewaesserKataster (pGewNr, pGewName, pGew);

			CTable f (*pGew);
			if ( f.Find (pGewNr)) {
				KP_GEWLock g(f);
				if (!g)
					continue;
				g->SpeichereObjekt(ONr);
				long lLen = LinienLaenge ( ONr);
				g->SpeichereObjektLaenge ( lLen );
				long lStartPunkt =  ObjektStartPunkt(ONr,m_pKH->CodeBauwAnfStat());
				if ( lStartPunkt != 0L)
					g->SetStartEndPunkt(lStartPunkt,lLen+lStartPunkt);
			}
			DELETE_OBJ ( pGewNr);
			DELETE_OBJ ( pGewName);
		}
	}

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	return pGew;
}
//--------------------------------------------------------------------------

//---------------------------------------------------------------------
void CKompiasExtension :: AbgleichGewaesserDaten ( ulong lMCode, ulong lMCodeN, TR_OCLTree *pTRGew )
{
	
	if ( !pTRGew || lMCode == 0L || lMCodeN == 0L) 
		return;


	CEierUhr Wait (MVWind());

	if ( m_pStatus)
		DELETE_OBJ (m_pStatus);

	long lNum = pTRGew->Count();
	long lNr = lNum * 100L;
	long lCount = 0L;

	ResString resCaption (ResID(IDS_CPTGEWABGLEICH, &RF()), 50);

	m_pStatus = new CStatus ( MVWind(), &RF(), lNr, resCaption);
//	m_pStatus = new CStatus ( MWind(), &RF(), lNr, "Gewässerdatenabgleich");
	m_pStatus->Show();

	CTable t (*pTRGew);

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if ( !l)
			continue;
		TR_OBJTree * pOBJ = l->OBJ();
		if ( !pOBJ)
			continue;
		long lRef = pOBJ->Count();
		if ( lRef == 0L)
			continue;

	    if ( m_pStatus->Break()) {

			MessageBox ( __hWndM ,
			 ResString (ResID(IDS_STOPANALYSE, &g_pTE->RF()),80),
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);

			DELETE_OBJ ( m_pStatus);
			return;
		}


		CTable e (*pOBJ);
		for (e.First(); e.Valid(); e.Next() ) {
			TR_OBJLock n(e);
			long ONr = n->Object();
			if ( ONr == -1L || ONr == 0L)
				continue;

			short Status = DEX_GetObjectType (ONr);

	//--------------Zuordnung----------------------------
			if ( Status != OGLinie )
				continue;

		    if ( m_pStatus->Break()) {

				MessageBox ( __hWndM ,
				 ResString (ResID(IDS_STOPANALYSE, &g_pTE->RF()),80),
				 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
				 MB_OK|MB_ICONEXCLAMATION);

				DELETE_OBJ ( m_pStatus);
				return;
			}

			lCount++;
			long lZahl = lCount * lNr / lRef; 
			if ( m_pStatus) 
				m_pStatus->SetValue( lZahl, ONr);
			
			char *pGewNr = HoleGewaesserNummer ( ONr, lMCode);
			if (!pGewNr) 
				continue;

			char *pGewName = HoleGewaesserName ( ONr, lMCodeN,pGewNr,true);	// mit Malte
			DELETE_OBJ ( pGewNr);
			DELETE_OBJ ( pGewName);
		}
	}

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	char *pText = new char [_MAX_PATH];
	if ( pText ) {
		wsprintf ( pText,ResString (ResID(IDS_ABGLEICHCOUNT, &g_pTE->RF()),80),lCount);
		MessageBox ( __hWndM ,
			 pText,
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
		 MB_OK|MB_ICONEXCLAMATION);
		DELETE_OBJ(pText);
	} else {
		MessageBox ( __hWndM ,
			 ResString (ResID(IDS_ABGLEICHNOCOUNT, &g_pTE->RF()),80),
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
		 MB_OK|MB_ICONEXCLAMATION);
	}

	return;
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void CKompiasExtension :: LadeGewaesserKataster ( char *pGewNr,char *pGewName ,KPTree *pGew )
{

	if ( !pGew )
		return;
	if ( !pGewNr || *pGewNr == '\0')
		return;


	CTable tkat(*pGew);

	GEWAESSER GW;
	memset (&GW, '\0', sizeof(GEWAESSER));
	GW.dwSize = sizeof(GEWAESSER);
	GW.pcGewaesserNr = pGewNr;
	GW.pcGewaesserName = pGewName;

	if (!tkat.Find(pGewNr)){
		KP_GEWCreator KPCr ( *pGew);
		ContCreate (KPCr,KP_GEW) (&GW, NULL);
	} else {
		KP_GEWLock lkat(tkat);
		lkat->AddCount();
	}
	return;

}	
//----------------------------------------------------------------------
long CKompiasExtension :: KompaktGewaesser ( LPARAM p)
{

	short Status = DEX_GetObjectType ((long)p);

	long lONr = -1L;
	if ( Status == OGLinie ) {
		if ( ObjektIstGewaesser((long)p)) {
			lONr = (long) p;	// ON wurde angefasst
		}
/*
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  p;
	long lONr = -1L;
	{
	ErrInstall EI (EC_DELRECORD);
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_KANTE) {
			if ( ObjektIstGewaesser(OS.lONr)) {
				lONr = OS.lONr;	// ON wurde angefasst
			}
		}
	}

  -*/
	}
	return lONr;
}
//---------------------------------------------------------------------
long CKompiasExtension :: KompaktUeberschwemmung ( LPARAM p)
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  p;
	long lONr = -1L;
	{
	ErrInstall EI (EC_DELRECORD);
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_FLAECHE) {
			if ( ObjektIstUeberschwemmung(OS.lONr)) {
				lONr = OS.lONr;	// ON wurde angefasst
			}
		}
	}
	}
	return lONr;
}
//---------------------------------------------------------------------
//----------------------------------------------------------------------
//---------------------------------------------------------------------
bool CKompiasExtension :: AktualisiereGewKataster ( KPTree *pGew, TR_OCLTree *pTRGew )
{
	bool iFlag = false;

	if ( !pTRGew || !pGew)
		return iFlag;

	CEierUhr Wait (MVWind());

	CTable t (*pTRGew);
	CTable d (*pGew);

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if ( !l)
			continue;
		TR_OBJTree * pOBJ = l->OBJ();
		if ( !pOBJ)
			continue;
		CTable e (*pOBJ);
		for (e.First(); e.Valid(); e.Next() ) {
			TR_OBJLock n(e);
			char *pGewNr = n->GewNr();			
			if (!pGewNr || *pGewNr == '\0')
				continue;

			long lLen = LinienLaenge ( n->Object());
			n->StoreObjLaenge ( lLen );

			if ( d.Find ( pGewNr)) {
				KP_GEWLock m(d);
				m->SpeichereObjekt(n->Object());
				m->SpeichereObjektLaenge ( lLen );
	// Auf zu Malte !!!
				long lLaenge = 0L;
				long lEta = 0L;
				long lLen = 0L;
				try {
					lLaenge = m_hLib->GewaesserKatasterLaengeHolen ( pGewNr, lLen, lEta);
				} catch (...) {
					MessageBox (m_hWnd, 
//					 "Fehler beim Zugriff auf Kompakt-Kataster(Katasterlänge)",
					 ResString (ResID(IDS_ERRNOKATASTERLEN, &RF()),50),
					 ResString (ResID(IDS_GEWAESSERANALYSE, &RF()),50),
					 MB_OK|MB_ICONHAND);

				}
				if ( lLaenge > 0L ) 
					m->SetKompaktLen ( lLaenge );

				iFlag = true;
			}
		}
	}

	return iFlag;
}
///////////////////////////////////////////////////////////////////////
void CKompiasExtension :: RestoreBauwAnlegen(bool iFlag)
{
	if ( iFlag ) {
		MessageBox (__hWndM,
		 ResString (ResID(IDS_KEINEGEWAESSER, &RF()),90),
		 ResString (ResID(IDS_BILDEEREIGNISSE, &RF()),90),
		 MB_OK|MB_ICONHAND);
	}

	RegisterNotification (DEX_DELOBJECT);
	{
		ErrInstall EI (EC_INVADDR);
		DEX_DeleteObject(m_lONr);
	}
	m_lONrBauw = -1;
	m_lONr = -1;
	m_isBauw = false;
}

///////////////////////////////////////////////////////////////////////

bool CKompiasExtension :: KompaktKatasterDefiniert_ONr ( long lONr)
{
	if (lONr <= 0L)
		return false;

	char *pGewNr = HoleGewaesserNummer ( lONr, m_pKH->CodeGewNr());
	if (!pGewNr) 
		return false;

	bool iFlag = KompaktKatasterDefiniert(pGewNr);
	DELETE_OBJ(pGewNr);
	return iFlag;

}
///////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: KompaktKatasterDefiniert ( char *pGewNr)
{
	if ( !pGewNr || *pGewNr == '\0')
		return false;

	// Auf zu Malte !!!
	long lLaenge = 0L;
	long lEta = 0L;
	long lLen = 0L;
	try {
		lLaenge = m_hLib->GewaesserKatasterLaengeHolen ( pGewNr, lLen, lEta);
	} catch (...) {
		MessageBox (m_hWnd, 
//		 "Fehler beim Zugriff auf Kompakt-Kataster(Katasterlänge)",
		 ResString (ResID(IDS_ERRNOKATASTERLEN, &RF()),50),
		 ResString (ResID(IDS_GEWAESSERANALYSE, &RF()),50),
		 MB_OK|MB_ICONHAND);
	}
	if ( lLaenge > 0L )
		return true;
	char *pMText = new char [_MAX_PATH];
	if ( pMText ) {
		wsprintf ( pMText,ResString (ResID(IDS_ERRKPGEWDEF, &g_pTE->RF()),80),pGewNr);
		MessageBox (__hWndM, 
			 pMText,
			 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
			 MB_OK|MB_ICONHAND);
		DELETE_OBJ(pMText);
	}

	return false;
}
///////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: AbgleichGewaesserNummer (void)
{
	if ( !m_pKH)
		return false;

	m_pKH->Aktualisieren(PM_GEWAESSER);

	if ( m_pKH && m_pKH->GewClass()) {

//---------------Objekte an Ident hängen
		LadeObjektKlasse ( OTLinie, m_pKH->GewClass());

		return LadeGewaesserNummer ( m_pKH->CodeGewNr(),m_pKH->CodeGewName(),m_pKH->GewClass());

	}
	return false;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: AbgleichHydraulikFlaechen (void)
{
	if ( !m_pKH)
		return false;

	m_pKH->Aktualisieren(PM_HYDRAULIK);

	if ( m_pKH && m_pKH->HydrClass()) {

//---------------Objekte an Ident hängen
		LadeObjektKlasse ( OTFlaeche, m_pKH->HydrClass());

		return LadeHydraulikHoehe ( m_pKH->CodeHydrHoehe(),m_pKH->HydrClass());

	}
	return false;
}
///////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: LadeHydraulikHoehe ( long lMCode,TR_OCLTree *pHydr)
{
	if ( lMCode == 0L || !pHydr )
		return false;

	CEierUhr Wait (MVWind());

	if ( m_pStatus)
		DELETE_OBJ (m_pStatus);

	long lNum = pHydr->Count();
	long lNr = lNum * 100L;
	long lCount = 0L;

	ResString resCaption (ResID(IDS_HOEHENABGLEICH, &RF()), 50);

	m_pStatus = new CStatus ( MVWind(), &RF(), lNr, resCaption);
//	m_pStatus = new CStatus ( MVWind(), &RF(), lNr, "Höhenabgleich");
	m_pStatus->Show();

	CTable t (*pHydr);

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if ( !l)
			continue;
		TR_OBJTree * pOBJ = l->OBJ();
		if ( !pOBJ)
			continue;
		long lRef = pOBJ->Count();
		if ( lRef == 0L)
				continue;

		if ( m_pStatus->Break()) {

			MessageBox ( __hWndM ,
			 ResString (ResID(IDS_STOPANALYSE, &g_pTE->RF()),80),
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);

			DELETE_OBJ ( m_pStatus);
			return false;
		}


		CTable e (*pOBJ);
		for (e.First(); e.Valid(); e.Next() ) {
			TR_OBJLock n(e);
			long ONr = n->Object();

			if ( m_pStatus->Break()) {

				MessageBox ( __hWndM ,
				 ResString (ResID(IDS_STOPANALYSE, &g_pTE->RF()),80),
				 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
				 MB_OK|MB_ICONEXCLAMATION);

				DELETE_OBJ ( m_pStatus);
				return false;
			}

			lCount++;
			long lZahl = lCount * lNr / lRef; 
			if ( m_pStatus) 
				m_pStatus->SetValue( lZahl, ONr);
			char *pH = HoleHydraulikHoehe ( ONr, lMCode);
			if (!pH) 
				continue;

			DELETE_OBJ ( pH);

		}
	}

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	return true;

}
///////////////////////////////////////////////////////////////////////

bool CKompiasExtension :: CheckOriginalObjekt ( long lONr )
{
	if ( lONr == -1L || lONr == 0L)
		return false;

	char *pCode = new char [_MAX_PATH];
	if ( !pCode ) {
		return false;
	}

	wsprintf( pCode, ResString( ResID( IDS_OBJEKTSYSCODE,&g_pTE->RF()),90));

#if _MSC_VER >= 1100

	long Ident = DEX_GetObjIdent(lONr);
	HPROJECT hPr = DEX_GetObjectsProject(Ident);
	ulong lMCode = DEX_GetMCodeFromFeatureNameEx (hPr, pCode );
#else
	ulong lMCode = DEX_GetMCodeFromFeatureName ( pCode );
#endif

	DELETE_OBJ(pCode);

	if ( lMCode == 0 )
		return true;

	if ( !ClonedObject ( lONr, lMCode ))
		return true;

	return false;
}

///////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: OriginalObjekt ( long lONr , TR_OBJTree *pOBJ, long lLaenge)
{
	if ( lONr == -1L || lONr == 0L)
		return false;

	char *pCode = new char [_MAX_PATH];
	if ( !pCode ) {
		return false;
	}

	wsprintf( pCode, ResString( ResID( IDS_OBJEKTSYSCODE,&g_pTE->RF()),90));

#if _MSC_VER >= 1100

	long Ident = DEX_GetObjIdent(lONr);
	HPROJECT hPr = DEX_GetObjectsProject(Ident);
	ulong lMCode = DEX_GetMCodeFromFeatureNameEx (hPr, pCode );
#else
	ulong lMCode = DEX_GetMCodeFromFeatureName ( pCode );
#endif

	DELETE_OBJ(pCode);

	if ( lMCode == 0 )
		return true;

	if ( !ClonedObject ( lONr, lMCode ))
		return true;

	CTable t(*pOBJ);
	{	
	if ( !t.Find ( &lONr) ) {
		TR_OBJCreator OCr ( *pOBJ);
		ContCreate ( OCr, TR_OBJ ) (lONr,NULL);
	}
	}
	if ( t.Find ( &lONr) ) {
		TR_OBJLock l(t);
		l->SetIntervall( 0,lLaenge);
	}
	
	return false;
}	
//----------------------------------------------------------------------
bool CKompiasExtension :: ClonedObject ( long lONr, ulong lMCode)
{
	if ( lMCode == 0 )
		return false;

	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = lONr;
	TM.lMCode = (long) lMCode;
	TM.imaxLen = NULL;
	TM.iTTyp = TT_Objekt;
	TM.pMText = NULL;

	if ( DEX_GetTextMerkmal ( TM )) 	// Merkmal gefunden
		return true;
	else
		return false;
}
//---------------------------------------------------------------------
void CKompiasExtension :: MischeGewKataster ( KPTree *pTRGew, KPTree *pKOGew )
{
	if ( !pTRGew || !pKOGew)
		return;

	CEierUhr Wait (MVWind());

	CTable t (*pKOGew);
	CTable d (*pTRGew);


	GEWAESSER GW;
	memset (&GW, '\0', sizeof(GEWAESSER));
	GW.dwSize = sizeof(GEWAESSER);


	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	long lCount = pKOGew->Count();

	
	ResString resCaption (ResID(IDS_KATASTERANALYSE, &RF()), 50);

	m_pStatus = new CStatus ( MVWind(), &RF(), lCount, resCaption);
//	m_pStatus = new CStatus ( MVWind(), &RF(), lCount, "Katasteranalyse");
	m_pStatus->Show();
	lCount = 0L;

	for ( t.First(); t.Valid(); t.Next()) {		//KOMPAKT
		KP_GEWLock l(t);
		if ( !l)
			continue;
		if ( m_pStatus->Break()) {

			MessageBox ( __hWndM ,
			 ResString (ResID(IDS_STOPANALYSE, &g_pTE->RF()),80),
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);

			DELETE_OBJ ( m_pStatus);
			return;
		}

		lCount++;

		
		if (d.Find( l->GewNr())) {			//TRiAS
			KP_GEWLock e(d);
			e->StoreCountKompakt(l->CountKompakt());
			e->StoreBeginnKompakt(l->BeginnKompakt());
			e->StoreEndeKompakt(l->EndeKompakt());
			e->StoreGewName ( l->GewName());
		} else {
			GW.pcGewaesserNr = l->GewNr();
			GW.pcGewaesserName = l->GewName();
			GW.lBeginn = -999999L;
			GW.lEnde = l->EndeKompakt();
			KP_GEWCreator KPCr ( *pTRGew);
			ContCreate (KPCr,KP_GEW) (&GW, NULL);
		}

		if ( m_pStatus) {
			m_pStatus->SetValue( lCount, lCount);
		}

	}

	for ( d.First(); d.Valid(); d.Next()) {
		KP_GEWLock e(d);
		if ( !e)
			continue;
		if ( e->Beginn() == -999999L) {
			e->TauscheZuKompakt();
//			e->StoreCountKompakt( e->Count());
			e->StoreBeginnKompakt(0L);
//			e->StoreEndeKompakt(e->Ende());

		}
	}
	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	return;
}
//---------------------------------------------------------------------
void CKompiasExtension :: BildeGewKataster ( KPTree *pTRGew, KPTree *pKOGew )
{
	if ( !pTRGew || !pKOGew)
		return;

	CEierUhr Wait (MVWind());

	CTable d (*pKOGew);
	CTable t (*pTRGew);


	GEWAESSER GW;
	memset (&GW, '\0', sizeof(GEWAESSER));
	GW.dwSize = sizeof(GEWAESSER);

	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);
		if ( !l)
			continue;
		if (d.Find( l->GewNr())) {
			KP_GEWLock e(d);
			e->SpeichereObjekt(l->Objekt());
			e->SetStartEndPunkt(l->Beginn(),l->Ende());
//			e->SpeichereObjektLaenge(l->Ende());
		}
	}


	return;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: isGewaesser ( void)
{
	if ( !m_pKH)
		return false;
	if ( !m_pKH->GewClass())
		return false;

	bool iFlag = false;
	long lCount = 0L;
	long lCountP = 0L;
	
	{

	TR_OCLTree *pGewClass = m_pKH->GewClass();

	CTable t (*pGewClass);

//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		lCount++;
		if (!l) continue;
		long Ident = l->Ident();
		if ( DEX_isIdentUsed(Ident)) 
			lCountP++;
	}

	}

// Es werden alle Gewässer durchsucht, besser wäre es , nur spezielle Idents!

	if ( lCount == lCountP)
		iFlag = true;
	else
 		m_pKH->Aktualisieren(PM_GEWAESSER);

	if ( lCountP > 0L)
		iFlag = true;

	return iFlag;
}
////////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: isBauwerk ( void)
{
	if ( !m_pKH)
		return false;
	if ( !m_pKH->BauwClass())
		return false;

	TR_OCLTree *pBauwClass = m_pKH->BauwClass();

	CTable t (*pBauwClass);
	bool iFlag = false;
	long lCount = 0L;
	long lCountP = 0L;

//------------BauwerkeKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		lCount++;
		if (!l) continue;
		long Ident = l->Ident();
		if ( DEX_isIdentUsed(Ident)) 
			lCountP++;
	}
	if ( lCount == lCountP)
		iFlag = true;
//	else
//		m_pKH->Aktualisieren(PM_BAUWERKE);

	if ( lCountP > 0L)
		iFlag = true;

	return iFlag;
}

////////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: DefineGewaesserObjekt ( long lONr)
{
		m_lONr = -1;

		if ( lONr == -1L || lONr == 0L )
			return false;

		OBJSTATISTIK OS;
   		memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);
		OS.lONr =  lONr;

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {

			if ( OS.iObjTyp == OT_KANTE) {

#if _MSC_VER >= 1100
				HPROJECT hPr = NULL;
				long lIdent = DEX_GetObjIdent(lONr);
				hPr = DEX_GetObjectsProject(lIdent);

				if ( !GetKompaktInformation (hPr))			// Kein Kataster angelegt
					return false;

				if ( m_pKH) {
					if ( hPr != m_pKH->HKompaktProject() )
						DELETE_OBJ(m_pKH);
				}
	
				m_hPr = hPr;		// Handle an Ext -> an Header
				if (!m_pKH)
					m_pKH = new KompaktHeader ( &RF());
#endif


				KatasterLaden();

				if ( !ObjektIstGewaesser ( OS.lONr))
					return false;
				m_lONr = OS.lONr;
				return true;
			}
		}

		return false;

}
////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
bool CKompiasExtension :: ObjektIstGewaesser ( long lONr)
{
	if ( lONr == -1L || lONr == 0L )
		return false;
	if ( !m_pKH)
		return false;
	if ( !m_pKH->GewClass())
		return false;

	long lIdent = DEX_GetObjIdent ( lONr);

	TR_OCLTree *pGewClass = m_pKH->GewClass();

	CTable t (*pGewClass);

//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		if ( lIdent == Ident)
			return true;
	}
	return false;
}
//----------------------------------------------------------------------
bool CKompiasExtension :: ObjektIstUeberschwemmung ( long lONr)
{
	if (lONr == -1L || lONr == 0L )
		return false;
	if ( !m_pKH)
		return false;
	if ( !m_pKH->HydrClass())
		return false;

	long lIdent = DEX_GetObjIdent ( lONr);

	TR_OCLTree *pHydrClass = m_pKH->HydrClass();

	CTable t (*pHydrClass);

//------------GewaesserKlassen laden ----------------------------
	for ( t.First(); t.Valid(); t.Next()) {
		TR_OCLLock l(t);
		if (!l) continue;
		long Ident = l->Ident();
		if ( lIdent == Ident)
			return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
char * CKompiasExtension :: HoleGewaesserNummer ( long lONr, ulong lMCode )
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if ( lONr == -1L || lONr == 0L || lMCode == 0L )
		return NULL;

	if ( !DEX_GetObjStatistik (OS) ) 
		return NULL;

	if ( OS.iObjTyp != OT_KANTE ) 
			return NULL;


	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return NULL;

	*pBuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.lMCode = (long)lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	if( DEX_GetTextMerkmal ( tm ))  {
		if ( *pBuffer != '\0')
			return pBuffer;
		DELETE_OBJ ( pBuffer);
		return NULL;
	} else {
		long lIdent = DEX_GetObjIdent ( lONr);
		ulong lSMCode = DEX_GetObjNameMCode(lIdent);
		GetStandardMCode ( lONr, lSMCode, pBuffer);
		if ( pBuffer && *pBuffer != '\0')
			SetObjektWert ( lONr,lMCode,pBuffer);
		else
			DELETE_OBJ ( pBuffer);
	}

	return pBuffer;

}
/////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: RestoreGewNr( long lONr, char *pBuffer)
{
	if (lONr <= 0L)
		return;

	if (pBuffer) {
		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		long lIdent = DEX_GetObjIdent ( lONr);
		ulong lSMCode = DEX_GetObjNameMCode(lIdent);
		SetObjektWert ( lONr,lSMCode,pBuffer);
		SetObjektWert ( lONr,m_pKH->CodeGewNr(),pBuffer);

		MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
	}

	return;

}

/////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
char * CKompiasExtension :: HoleHydraulikHoehe ( long lONr, ulong lMCode )
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if ( (-1L == lONr || lONr == 0L) || lMCode == 0L )
		return NULL;

	if ( !DEX_GetObjStatistik (OS) ) 
		return NULL;

	if ( OS.iObjTyp != OT_FLAECHE ) 
			return NULL;


	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return NULL;

	*pBuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.lMCode = (long)lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	if( DEX_GetTextMerkmal ( tm ))  {
		if ( *pBuffer != '\0')
			return pBuffer;
		DELETE_OBJ ( pBuffer);
		return NULL;
	} else {
		long lIdent = DEX_GetObjIdent ( lONr);
		ulong lSMCode = DEX_GetObjNameMCode(lIdent);
		GetStandardMCode ( lONr, lSMCode, pBuffer);
		if ( pBuffer && *pBuffer != '\0')
			SetObjektWert ( lONr,lMCode,pBuffer);
		else
			DELETE_OBJ ( pBuffer);
	}

	return pBuffer;

}
/////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
char * CKompiasExtension :: HoleTRiASGewaesserNummer ( long lONr, ulong lMCode )
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if (lONr == -1L || lONr == 0L || lMCode == 0L )
		return NULL;

	if ( !DEX_GetObjStatistik (OS) ) 
		return NULL;

	if ( OS.iObjTyp != OT_KANTE && OS.iObjTyp != OT_PUNKT) 
			return NULL;


	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return NULL;

	*pBuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.lMCode = (long)lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	if( DEX_GetTextMerkmal ( tm ))  {
		if ( *pBuffer != '\0')
			return pBuffer;
		DELETE_OBJ ( pBuffer);
		return NULL;
	} else {
		long lIdent = DEX_GetObjIdent ( lONr);
		ulong lSMCode = DEX_GetObjNameMCode(lIdent);
		GetStandardMCode ( lONr, lSMCode, pBuffer);
		if ( pBuffer && *pBuffer != '\0')
			SetObjektWert ( lONr,lMCode,pBuffer);
		else
			DELETE_OBJ ( pBuffer);
	}

	return pBuffer;

}
/////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------
char * CKompiasExtension :: AktualisiereGewaesserNummer ( long lONr, ulong lMCode )
{
	if ( lONr == -1L || lONr == 0L || lMCode == 0L )
		return NULL;

	long lIdent = DEX_GetObjIdent ( lONr);
	ulong lSMCode = DEX_GetObjNameMCode(lIdent);

	if ( lSMCode == 0L)
		return NULL;

	char *pBuffer = new char [_MAX_PATH];
	char *pPuffer = new char [_MAX_PATH];

	if ( !pBuffer || !pPuffer) {
		DELETE_OBJ ( pBuffer);
		DELETE_OBJ ( pPuffer);
		return NULL;
	}
	*pBuffer = '\0';
	*pPuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.lMCode = (long)lSMCode;		// MerkmalsCode ObjektName
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;


	if( !DEX_GetTextMerkmal ( tm ) || *pBuffer == '\0') {	// Kein ObjektName !!!
		wsprintf(pBuffer, "Noname%ld",lONr);
		SetObjektWert ( lONr,lSMCode,pBuffer);
		SetObjektWert ( lONr,lMCode,pBuffer);
		DELETE_OBJ ( pPuffer);
		return pBuffer;
	}

	if ( *pBuffer == ' ') {
		*pBuffer = '\0';
		wsprintf(pBuffer, "Noname%ld",lONr);
		SetObjektWert ( lONr,lSMCode,pBuffer);
		SetObjektWert ( lONr,lMCode,pBuffer);
		DELETE_OBJ ( pPuffer);
		return pBuffer;
	}

	tm.lTarget = lONr;		// ObjektNummer
	tm.lMCode = (long)lMCode;		// MerkmalsCode GewNr
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pPuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	if( !DEX_GetTextMerkmal ( tm )) {
		tm.imaxLen = _MAX_PATH - 1;
		tm.pMText =pBuffer;		// ObjektName uebernehmen
		DEX_ModTextMerkmal(tm);
		DELETE_OBJ ( pPuffer);
		return pBuffer;
	}

	if ( strcmp (pBuffer,pPuffer) == 0) {
		DELETE_OBJ ( pPuffer);
	} else {
		tm.imaxLen = _MAX_PATH - 1;
		tm.pMText =pBuffer;		// ObjektName uebernehmen
		DEX_ModTextMerkmal(tm);
		DELETE_OBJ ( pPuffer);
	}

	return pBuffer;

}
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
char * CKompiasExtension :: HoleGewaesserName ( long lONr, ulong lMCode, char *pGewNr, short iFlag)
{
	if ( !pGewNr || *pGewNr == '\0')
		return NULL;

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if (lONr == -1L || lONr == 0L || lMCode == 0L )
		return NULL;

	if ( !DEX_GetObjStatistik (OS) ) 
		return NULL;

	if ( OS.iObjTyp != OT_KANTE ) 
			return NULL;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return NULL;

	*pBuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.lMCode = (long)lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	char * pMalte;
	if ( iFlag) {
		try {
			pMalte = m_hLib->GewaesserNameHolen ( pGewNr);
		} catch (...) {
			MessageBox (m_hWnd, 
//			 "Fehler beim Zugriff auf Gewässer-Kataster(GewässerNameHolen)",
			 ResString (ResID(IDS_ERRORGEWAESSERNAMEHOLEN, &RF()),50),
			 ResString (ResID(IDS_GEWAESSERANALYSE, &RF()),50),
			 MB_OK|MB_ICONHAND);

		}
	}

	if( DEX_GetTextMerkmal ( tm ))  {
		if ( *pBuffer != '\0') {
			if ( iFlag ) {
				if ( !pMalte || *pMalte == '\0') {
					return pBuffer;
				} else {
					if ( strcmp(pBuffer,pMalte) == 0) {
						return pBuffer;
					} else {
						strcpy (pBuffer,pMalte);

						MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

						SetObjektWert( lONr, lMCode, pBuffer);
						MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
				}
		
				}
			}
			return pBuffer;
		}


	}
	if ( iFlag) {

		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		if ( !pMalte || *pMalte == '\0') {
			long lIdent = DEX_GetObjIdent ( lONr);
			ulong lSMCode = DEX_GetObjNameMCode(lIdent);
			GetStandardMCode ( lONr, lSMCode, pBuffer);
			if ( *pBuffer != '\0')
				SetObjektWert ( lONr,lMCode,pBuffer);
			else
				DELETE_OBJ ( pBuffer);
		} else {
			strcpy (pBuffer,pMalte);
			SetObjektWert( lONr, lMCode, pBuffer);
		}
		MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
	}
	return pBuffer;

}
/////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
char * CKompiasExtension :: TRiASGewaesserName ( long lONr, ulong lMCode )
{

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if (lONr == -1L || lONr == 0L || lMCode == 0L )
		return NULL;

	if ( !DEX_GetObjStatistik (OS) ) 
		return NULL;

	if ( OS.iObjTyp != OT_KANTE ) 
			return NULL;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return NULL;

	*pBuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.lMCode = (long)lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	DEX_GetTextMerkmal ( tm );

	if ( *pBuffer == '\0') {
		DELETE_OBJ (pBuffer);
	}
	return pBuffer;

}

//////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: GetStandardMCode ( long lONr, ulong lMCode, char *pBuffer)
{
	if (lONr == -1L || lONr == 0L || lMCode == 0L )
		return ;
	if ( !pBuffer)
		return;

	*pBuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.lMCode = (long)lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	DEX_GetTextMerkmal ( tm );

	if ( *pBuffer != '\0') {
		return ;
	} else {
		wsprintf(pBuffer, "Noname%ld",lONr);
	}

	return ;

}
//----------------------------------------------------------------------
bool CKompiasExtension :: SetzeKompaktName ( long lONr, short iTyp)
{


	if ( lONr == 0L )
		return false;

	long lIdent = DEX_GetObjIdent ( lONr);
	ulong lMCode = DEX_GetObjNameMCode(lIdent);

	// Fenster für Objektnamevergabe
	MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
	ulong lMCode1;
	ulong lMCode2;
	uint res;
	// Vorsicht : Ereignis Einmündungen sind wie Gewässer zu behandeln !

	if ( iTyp == 0 ) {	//Gewässer
		lMCode1 = m_pKH->CodeGewNr();
		lMCode2 = m_pKH->CodeGewName();
		res = IDD_KOMPAKTNAME;

		{

			KompaktName KN ( MVWind(),res,RF(),lONr,iTyp);

			KN.Show(Centre);
			if ( KN.Result() == 1 ) {
				char *pName = KN.GetObjektName();
				if (pName ) {
					if (*pName == '\0')
						return false;
					SetObjektWert( lONr, lMCode, pName);	// Objektname
					char *pBez = KN.GetObjektBezeichnung();
					if ( pBez && *pBez != '\0')
						SetObjektWert( lONr, lMCode2, pBez);
					MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
					SetObjektWert( lONr, lMCode1, pName);
				} else {
					MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
					return false;
				}

			} else {
				MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
				return false;
			}
		}


	} else {

		lMCode1 = m_pKH->CodeBauwBez();
		lMCode2 = m_pKH->CodeBauwName();
		res = IDD_EREIGNISNAME;
		if ( Einmuendung(lONr)) {
			short Status = DEX_GetObjectType (lONr);

	//--------------Zuordnung----------------------------
			if ( Status != OGPunkt )
				return false;


			res = IDD_KOMPAKTNAME;

			{

			KompaktName KN ( MVWind(),res,RF(),lONr,iTyp);

			KN.Show(Centre);
			if ( KN.Result() == 1 ) {
				char *pName = KN.GetObjektName();
				if (pName ) {
					if (*pName == '\0')
						return false;
					SetObjektWert( lONr, lMCode, pName);	// Objektname
					char *pBez = KN.GetObjektBezeichnung();
					if ( pBez && *pBez != '\0')
						SetObjektWert( lONr, lMCode2, pBez);
					MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
					SetObjektWert( lONr, lMCode1, pName);
				} else {
					MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
					return false;
				}
			} else {
				MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
				return false;
			}

			}

		} else {

			{
	
			EreignisName KN ( MVWind(),res,RF(),lONr,iTyp);
			if ( KN.GetKatalogCount() > -1 ) {
				KN.Show(Centre);
				if ( KN.Result() == 1 ) {
					char *pName = KN.GetObjektName();
					if (pName ) {
						if (*pName == '\0')
							return false;
						SetObjektWert( lONr, lMCode, pName);	// Objektname
						char *pBez = KN.GetObjektBezeichnung();
						if ( pBez && *pBez != '\0')
							SetObjektWert( lONr, lMCode2, pBez);
						MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
						SetObjektWert( lONr, lMCode1, pName);
					} else {
						MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
						return false;
					}

				} else {
					MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
					return false;
				}
			} else {
				MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
				return false;
			}

			}
		}
	}

	return true;
}

//--------------------------------------------------------------------
bool CKompiasExtension :: Einmuendung ( long lONr)
{

	bool iFlag = false;

	if (lONr == -1L || lONr == 0L )
		return iFlag;

	long lIdent = DEX_GetObjIdent ( lONr);

	char NewIdent[MAX_OKS_LENX+1];


#if _MSC_VER < 1100
	ClassFromIdentX ( lIdent, NewIdent);
#else
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
	ClassFromIdentX ( hPr,lIdent, NewIdent);
#endif

	
	long RefIdent = atol(NewIdent+1);	

	RefIdent = RefIdent/1000L;

	if ( (short)RefIdent != cBauwerkeIdent) {
		return iFlag;
	}

	RefIdent = atol(NewIdent+2);	

	if ( RefIdent == cBauwerkeEinmuendung)
		iFlag = true;
	return iFlag;
}
//-------------------------------------------------------------------


//------------------------------------------------------------------
// MCode für Objekte setzen
//-------------------------------------------------------------------
void CKompiasExtension :: SetObjektWert ( long lONr, ulong MCode, char *pMText)
{

	// MerkmalsWert setzen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pMText;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)MCode;		// MerkmalsCode

	DEX_ModTextMerkmal ( tm );

	return;
}
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------
//	ORFenster erstellen-----------------------------------------
void CKompiasExtension :: CreateORWindow ( short Flag, short PX, short PY, long *pObjL, const char *pCaption, short RF, short GF, short BF)
{
	if ( *pObjL <= 0 )
		return;

	POINT PNT;
	PNT.x = PX;
	PNT.y = PY;


	CREATEOBJEKTINFOEX COI;
	memset ( &COI, '\0', sizeof (COI) );
	COI.dwSize = sizeof(COI);
	COI.lpCaption = (char *)pCaption;
	COI.plObjs = pObjL+1;
	COI.iNumObjs = short( *pObjL);
	COI.cMColor = RGB(RF,GF,BF);
	COI.pntPos = PNT;
	COI.m_iFlags = Flag;

	RegisterNotification (DEX_QUERYRECHOBJECT);
	DEX_CreateObjektInfo( COI );
	UnRegisterNotification (DEX_QUERYRECHOBJECT);

}

//---------------------------------------------------------------------------
// File: KOMPMEM.CXX
