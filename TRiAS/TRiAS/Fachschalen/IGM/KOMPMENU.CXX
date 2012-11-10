// KOMPIAS-MEMBER 
// File: KOMPMENU.CXX

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
#include "triasdef.h"

#include "kompdll.hxx" 
#include "kompwin.hxx"
#include "komphead.hxx"
#include "kompgew.hxx"
#include "gewbaum.hxx"
#include "kompprof.hxx"
#include "kpstatus.hxx"


#include "cobjtree.hxx"
#include "ctopobj.hxx"

#include "kompias.hxx"

//#include "igmdef.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32
//------------------------------------------------------------------
void CKompiasExtension :: TRiASKompaktLoader(void)
{
	ResString ExtStatistik (ResID (IDS_LOADSTATISTIK,&RF()),30);
	short fGlobal = EFUnLoadable|EFVisible;
	LOADEXTENSIONEX LE;
	LE.m_pDesc = NULL;
	LE.m_pName = ExtStatistik.Addr();
	LE.m_iMode = LEFullLoad;
	LE.m_fGlobal = (bool)fGlobal;

//	DEX_ExternalLoadExtensionEx (LE);
	DEX_ExternalLoadExtensionEx (LE);	// KK011129 - rückgängig, da sonst OE nicht ladbar


	ResString ExtAbstand (ResID (IDS_LOADABSTAND,&RF()),30);
//	DEX_ExternalLoadExtension (ExtAbstand.Addr());

	ResString ExtObjOp (ResID (IDS_LOADOBJOP,&RF()),30);
//	DEX_ExternalLoadExtension (ExtObjOp.Addr());

	ResString ExtTopologie (ResID (IDS_LOADTOPOLOGIE,&RF()),30);
//	DEX_ExternalLoadExtension (ExtTopologie.Addr());

	ResString ExtPuffer (ResID (IDS_LOADPUFFER,&RF()),30);
//	DEX_ExternalLoadExtension (ExtPuffer.Addr());

	ResString ExtOleAuto (ResID (IDS_LOADOLEAUTO,&RF()),30);
//	DEX_ExternalLoadExtension (ExtOleAuto.Addr());

	ResString ExtMacro (ResID (IDS_LOADMACROSCRIPT,&RF()),30);
//	DEX_ExternalLoadExtension (ExtMacro.Addr());

}
//-----------------------------------------------------------------
#if _MSC_VER >= 1100
bool CKompiasExtension :: GetKompaktInformation (HPROJECT _hPr)
{
	bool iFlag = false;

	GEODBHDRENTRYEX hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRYEX);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADKOMPAKTIDENT,&RF()),HEADERKEYSIZE +1),HEADERKEYSIZE);
	hdrEntry.lphdrText = new char [HEADERSIZE+1];
	hdrEntry.hdrTextLen = HEADERSIZE;
	hdrEntry.dwFlags = HEADER_READONLY;



	if (DEX_ReadGeoDBHdrEntryEx (_hPr,hdrEntry) == EC_OKAY) {

	// HeaderEintrag existiert
		iFlag = true;	
	
	}
	DELETE_OBJ (  hdrEntry.lphdrText);
	return iFlag;
}
#endif
//-------------------------------------------------------------------
short CKompiasExtension :: KompaktMenu ( short iFlag )
{

	short iFct = -1;


//--------------Erweiterungen und Interface-------------------
	if (!LadeAbstandsErweiterung()) {
//		MessageBox (__hWndM, 
//		 ResString (ResID(IDS_ERRKEINABSTAND, &RF()),80),
//		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
//		 MB_OK);
	}

	if (!LadeTopRel()) {
//		MessageBox (__hWndM, 
//		 ResString (ResID(IDS_ERRKEINETOPOLOGIE, &RF()),80),
//		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
//		 MB_OK);
	}
	if (!LadePuffer()) {
//		MessageBox (__hWndM, 
//		 ResString (ResID(IDS_ERRKEINPUFFER, &RF()),80),
//		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
//		 MB_OK);
	}

	if (!LadeObjOp()) {
//		MessageBox (__hWndM, 
//		 ResString (ResID(IDS_ERRKEINEOBJEKTOPERATION, &RF()),80),
//		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
//		 MB_OK);
	}

	if (!LadeObjektEigenschaft()) {

		ResString ExtStatistik (ResID (IDS_LOADSTATISTIK,&RF()),30);
		short fGlobal = EFUnLoadable|EFVisible;
		LOADEXTENSIONEX LE;
		LE.m_pDesc = NULL;
		LE.m_pName = ExtStatistik.Addr();
		LE.m_iMode = LEFullLoad;
		LE.m_fGlobal = (bool)fGlobal;

		DEX_ExternalLoadExtensionEx (LE);
		LadeObjektEigenschaft();

//		MessageBox (__hWndM, 
//		 ResString (ResID(IDS_ERRKEINEPROPERTY, &RF()),80),
//		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
//		 MB_OK);
	}


	// aktuelles Projektverzeichnis besorgen

	if ( !m_pLocDir) {
		m_pLocDir = new char [_MAX_PATH];
		if ( m_pLocDir != NULL ) {
			if (DEX_GetActiveProject (m_pLocDir) == NULL) {
				// Projekt nicht eröffnet
				DELETE_OBJ ( m_pLocDir);
				iFct = -10;	// Projekt noch nicht offen - noch einen Versuch !
				return iFct;
			}

			ErfasseTempDaten();

			CreateGraphicInformation();
//---------------BasicDocument 
			if (m_pLocDir) {


				LadeBasicScript();

				if ( !m_pDoc)
					LadeBasicDocument();
			}


		//	KOMPAKT1.DLL holen
			if ( !m_hLib) {
				char *pLibrary = NULL;
				{
					KompaktProFile KPF ( &RF());

				// KK010921
				// IGM32.INI nicht da
					if ( !KPF.isValid()) {
						MessageBox ( __hWndM,
						 ResString (ResID(IDS_STRKEINEINI, &RF()),80),
						 ResString (ResID(IDS_STRCAPTION, &RF()),80),
						MB_ICONSTOP);
						m_isActive = false;
						return iFct;
					}


					pLibrary = KPF.GetPathLibrary();
		// DatenPfad Gewässerkataster/Kompakt
					char *pRef = KPF.GetPathDaten();

					char *pData = KPF.GetDataPath();

					if (pData && ExistDataPath(pData)) {
						if ( !m_pDataPath)
							m_pDataPath = new char [_MAX_PATH];

						if ( m_pDataPath)
							strcpy(m_pDataPath,pData);
					} else {

						MessageBox ( __hWndM,
						 ResString (ResID(IDS_WBVDATERROR, &RF()),80),
						 ResString (ResID(IDS_STRCAPTION, &RF()),80),
						MB_ICONSTOP);
		//				m_isActive = false;
		//				return iFct;

		//	KompaktPrivate bei geöffneten Projekt
						Datenquelle();		// GewKataster einstellen

						if (m_pLocDir ) 
							SetzeKompaktDatenPfad(m_pLocDir);

					}

					m_iDefSchritt = (short)SCHRITTWEITE;

					if ( m_pKH)
						m_iDefSchritt = m_pKH->GewSchrittweite();




					m_iDefPuffer = (short)PUFFERZONE;

					if ( m_pKH)

						m_iDefPuffer = m_pKH->GewPuffer();


				
					char *pSoftPath = NULL;
					pSoftPath = KPF.GetSoftPath();
					if ( pSoftPath && '\0' != *pSoftPath)
						KompaktKomponentenTest(pSoftPath);

					// Nur , falls Protokoll gewünscht
					if ( m_dKPP != KP_Default ) {
						char *pP = NULL;
						pP = KPF.GetPathDaten();
						if ( pP ) {
							if (*pP != '\0') {
								remove(pP);
								if ( !m_pLocProt) 
									m_pLocProt = new char [_MAX_PATH];
								if (m_pLocProt)
									strcpy (m_pLocProt,pP);
							}
							if ( m_pLocProt) {
								*pP = '\0';
								wsprintf (pP,"Standardschrittweite = %ld - Standardpuffer = %ld \n",SCHRITTWEITE,PUFFERZONE);
								KompaktProtokoll (m_pLocProt,pP);
							}

							DELETE_OBJ (pP);
						}
					}
				}

				TX_ASSERT(NULL != pLibrary);
//---------------------------------------------------------
// Test ohne Kompakt1.dll

				if ( m_dKPA == KP_NoAll) {	// In Registrierung NoKompaktDLL eingestellt
					DELETE_OBJ (pLibrary);
					m_isActive = true;
					return iFct;

				}
//------------------------------------------------------------------

				if ( pLibrary ) {

					m_hLib = NULL;

					if ( Kompakt1Existenz(pLibrary)) {

						try {

							m_hLib = new CKompaktDLL ((DWORD)this, hWnd(), (const char *)pLibrary);

						} catch (...) {
							MessageBox (__hWndM, 
							 ResString (ResID(IDS_ERRKPNOLOAD, &g_pTE->RF()),80),
							 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
							 MB_OK|MB_ICONHAND);
	
						}

						if (!m_hLib->isValid()) 
							DELETE_OBJ ( m_hLib);
					}



					DELETE_OBJ (pLibrary);

					if ( !m_hLib ) {
						MessageBox ( __hWndM,
						 ResString (ResID(IDS_STRKEINEDLL, &RF()),80),
						 ResString (ResID(IDS_STRCAPTION, &RF()),80),
						MB_ICONSTOP);
						m_isActive = false;
					
						return iFct;
					} else {
						m_isActive = true;
					}

		//	KompaktPrivate bei geöffneten Projekt
					if (m_pLocDir ) {
						SetzeKompaktDatenPfad(m_pLocDir);
					}					

				} else {
					DELETE_OBJ ( m_hLib);
					MessageBox ( __hWndM,
					 ResString (ResID(IDS_STRKEINEDLL, &RF()),80),
					 ResString (ResID(IDS_STRCAPTION, &RF()),80),
					MB_ICONSTOP);
					m_isActive = false;
					return iFct;
				}
			}
			m_isActive = true;
//			if ( m_dKPA == KP_Default)
//				TeSys();

		}
	}

	iFct = 0;	// Bedingungen abschwächen

////////////////////////////////////////////////////////////////////////////////////
   
	char *pSight = new char [_MAX_PATH];
	if ( !DEX_GetActiveSight(pSight)) {
		DELETE_OBJ (pSight);
		return iFct;
	}

	DELETE_OBJ ( pSight);

	if ( iFlag ) {
	{
	KompaktInformation KI ( MVWind(),CKOMPAKTINFORMATION, RF());
	KI.Show(Centre);
	iFct = KI.Result();
	}
	}

	return iFct;
}
///////////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: ExistDataPath (char *pData)
{
	if ( !pData || *pData == '\0') 
		return false;
	struct _stat ST;

	if ( _stat ( pData, &ST) != 0 )
		return false;
	return true;
}
//---------------------------------------------------------------------------
char *CKompiasExtension :: HoleKompaktDatenPfad(void)
{
	char *pDataPath = NULL;
	
	{
		KompaktProFile KPF ( &RF());
				 
	// DatenPfad Gewässerkataster/Kompakt
		char *pRef = KPF.GetPathDaten();
		char *pData = KPF.GetDataPath();
		if (pData) {
			pDataPath = new char [_MAX_PATH];

			if ( pDataPath)
				strcpy(pDataPath,pData);

		}

	}
	return pDataPath;
}
//-----------------------------------------------------------------------------
bool CKompiasExtension :: SetzeKompaktDatenPfad ( char *pLocDir)
{
	if (!pLocDir || *pLocDir == '\0')
		return false;

	if ( m_dKPA == KP_NoAll) 	// In Registrierung NoKompaktDLL eingestellt
		return false;

	{
		KompaktPrivateProFile KPF ( &RF(),pLocDir);
		char *pLibrary = KPF.GetPathDaten();
		char *pData = KPF.GetDataPath();
		if (pData  && ExistDataPath(pData) && m_hLib && m_pDataPath)
			strcpy(m_pDataPath,pData);
		if (pData && ExistDataPath(pData) && m_hLib) {
			m_hLib->KompaktDatenPfad (pData);
		}

		if ( m_pKH) {
			m_iDefSchritt = m_pKH->GewSchrittweite();
			m_iDefPuffer = m_pKH->GewPuffer();
		}

	}

	return true;
}

//---------------------------------------------------------------------------
bool CKompiasExtension :: Kompakt1Existenz ( char *pPath )
{
	if (!pPath || *pPath == '\0')
		return false;


	struct _stat ST;
	if ( _stat ( pPath, &ST) != 0 ) 
		return false;

	return true;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool CKompiasExtension :: KompaktKomponentenTest ( char *pPath )
{
	if (!pPath || *pPath == '\0')
		return false;

	char * pRefPath = new char [_MAX_PATH];

	if ( !pRefPath)
		return false;

	*pRefPath = '\0';

	strcat (pRefPath,pPath);
	strcat ( pRefPath,ResString (ResID (IDS_KOMPAKTABFLUSS, &RF()), 50));

	struct _stat ST;
	if ( _stat ( pRefPath, &ST) != 0 ) 
		m_iAbfluss = false;
	else
		m_iAbfluss = true;


	*pRefPath = '\0';

	strcat (pRefPath,pPath);
	strcat ( pRefPath,ResString (ResID (IDS_KOMPAKTPROFILE, &RF()), 50));

	if ( _stat ( pRefPath, &ST) != 0 ) 
		m_iProfile = false;
	else
		m_iProfile = true;

	return true;

}
//---------------------------------------------------------------------------
bool CKompiasExtension :: KatasterAnlegen (void)
{

	int flag = MessageBox ( __hWndM,
	 ResString (ResID(IDS_STROPENKATASTER, &RF()),80),
	 ResString (ResID(IDS_STRCAPTION, &RF()),80),
	MB_YESNO|MB_ICONEXCLAMATION);

	if ( IDNO == flag) {
		m_isActive = false;
		return false;
	} else {
		KompaktProtokoll ( m_pLocProt, " Anlegen des Gewässerkatasters \n");

	// Welches Projekt ???
	// Enumeration der ProjektHandle und Festlegen Handle Kataster

		m_pKH->SetValidation(m_pLocProt);
		m_isActive = true;

		if ( !m_pKH->GewClass() ) {
			KompaktKlassenAuswahl PA ( MVWind(), OBJCLASSAUSWAHL, RF(),m_pKH, PM_GEWAESSER);
			PA.Show(Centre);
		}

//	KompaktKomponenten überprüfen !!!
		{
			KompaktProFile KPF ( &RF());
			char *pLibrary = KPF.GetPathLibrary();
			char *pSoftPath = NULL;
			pSoftPath = KPF.GetSoftPath();
			if ( pSoftPath)
				KompaktKomponentenTest(pSoftPath);
		}


	}

	return true;
}

//---------------------------------------------------------------------------
bool CKompiasExtension :: KatasterLaden ( bool iFlag )
{

	if ( !m_isActive)	// Maltes Kompakt nicht da !
		return false;

	if ( m_pKH && m_pKH->isValid()) {
		return true;
	}

	CEierUhr Wait (MVWind());
	// KompaktHeader aufbauen
	if ( !m_pKH) {

	#if _MSC_VER >= 1100


		if ( iFlag )	{		// Keine Datenquelle geladen !!!
//		if ( iFlag && !Datenquelle())
			if ( !Datenquelle())
				return false;
		}
	#endif

		m_pKH = new KompaktHeader ( &RF());

	}


	if ( !m_pKH->isValid()) {

// Neu 17.6.99
		if (!KatasterAnlegen()) {
			if (!m_isActive)			// Keiner will
				return false;

		}


	} else {
		m_isActive = true;
	}


// KK 010906
// Aktuelles HPROJECT (m_hPr) aus Datenquelle() an Header abgeben !!!
	m_pKH->SetKompaktProject(m_hPr);

	if ( !m_pKH->GewClass() ) {
			m_pKH->Aktualisieren(PM_GEWAESSER);
			if ( !m_pKH->GewClass()) {
				MessageBox (__hWndM,
				 ResString (ResID(IDS_GEWNICHTDEFINIERT, &RF()),80),
				 ResString (ResID(IDS_GEWAESSERUEBERSICHT, &RF()),80),
				 MB_OK|MB_ICONEXCLAMATION);


				KompaktKlassenAuswahl PA ( MVWind(), OBJCLASSAUSWAHL, RF(),m_pKH, PM_GEWAESSER);
				PA.Show(Centre);

			}
	}

	// KK010809
	// Nun die Korrektur aus dem Header
	m_iDefSchritt = m_pKH->GewSchrittweite();
	m_iDefPuffer = m_pKH->GewPuffer();

	//KK010921 - WBVDAT in DQ-Ini eintragen !

	SetGewaesserKatasterPfad ( m_hPr);

	return true;
}
//------------------------------------------------------------------
//KK010921
// Über DQ-Handle Pfad der WBVDAT in Ini eintragen
void CKompiasExtension :: SetGewaesserKatasterPfad ( HPROJECT hPr)
{
	if (!m_pDataPath || '\0' == *m_pDataPath)
		return;

	char cbBuffer[_MAX_PATH];
	 
	if (NULL != DEX_GetDataSourceName (hPr, cbBuffer)) {

		if (m_pLocDir)
			strcpy ( m_pLocDir,cbBuffer);

		{
			KompaktPrivateProFile KPF ( &RF(),m_pLocDir);
			KPF.SetDataConfiguration ( m_pDataPath);
		}
	}

	return;
}
//-------------------------------------------------------------------
bool CKompiasExtension :: LeistungsBearbeitung ( short iFct )
{

	if ( !m_hLib || !m_pKH) 
		return false;

	
	KPTree *pGew = HoleLeistungenVonKompakt(iFct);
	if ( pGew && pGew->Count() > 0) {

		if ( ! m_pGewAlle) 
			m_pGewAlle = GesamtGewaesser();
		if ( !m_pGewAlle) {
			DELETE_OBJ ( pGew);
			return false;
		}
		AbgleichGewKataster( pGew,m_pGewAlle);

		if ( SpeichereLeistungInTrias ( pGew)) {
			DEX_RebuildSight();
		}
	}

	DELETE_OBJ ( pGew);


	return true;
}
//---------------------------------------------------------------------------
//-------------------------------------------------------------------
bool CKompiasExtension :: BauwerkeBearbeitung ( short iFct )
{
	if ( !m_hLib || !m_pKH) 
		return false;

	
	KPTree *pGew = HoleBauwerkeVonKompakt(iFct);

	if ( pGew && pGew->Count() > 0) {
		if ( ! m_pGewAlle) 
			m_pGewAlle = GesamtGewaesser();
		if ( !m_pGewAlle) {
			DELETE_OBJ ( pGew);
			return false;
		}
		AbgleichGewKataster( pGew,m_pGewAlle);

		if ( SpeichereBauwerkeInTrias ( pGew)) {
			DEX_RebuildSight();
			m_pKH->Aktualisieren (PM_BAUWERKE);
		}
	}

	DELETE_OBJ ( pGew);
	return true;
}
//////////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: AbgleichGewKataster ( KPTree *pGew , KPTree *pGewAlle)
{
	bool iFlag = false;

	if ( !pGew || pGew->Count() == 0L || !pGewAlle || pGewAlle->Count() == 0L)
		return iFlag;

//	CEierUhr Wait (MWind());

	CTable t (*pGew);
	CTable d (*pGewAlle);
	long lCount = pGew->Count();

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);

	m_pStatus = new CStatus ( MVWind(), &RF(), lCount,ResString (ResID(IDS_DATENABGLEICH, &RF()),50).Addr() );
	m_pStatus->Show();
	lCount = 0L;
	for ( t.First(); t.Valid(); t.Next()) {
		KP_GEWLock l(t);
		if ( !l)
			continue;
		
		if ( m_pStatus->Break()) {

			MessageBox ( __hWndM ,
			 ResString (ResID(IDS_STOPABGLEICH, &RF()),80),
			 ResString (ResID(IDS_CAPTIONKOMPAKT, &RF()),80),
			 MB_OK|MB_ICONEXCLAMATION);

			DELETE_OBJ ( m_pStatus);
			return false;
		}


		lCount++;


		if ( d.Find ( l->GewNr())) {
			KP_GEWLock m(d);
			l->SpeichereObjekt(m->Objekt());
			l->SpeichereObjektLaenge ( m->Ende() );
			l->SetKompaktLen ( m->EndeKompakt());
			iFlag = true;
		}

		if ( m_pStatus) {
			m_pStatus->SetValue( lCount, l->Objekt());
		}

	}

	if ( m_pStatus)
		DELETE_OBJ ( m_pStatus);
	return iFlag;
}
//////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
bool CKompiasExtension :: KompaktFunktion ( short iFct , HWND hWnd)
{
	if ( !m_hLib && iFct == -10)
		return true;

	if ( !m_hLib )
		return false;

	if ( iFct < 0 )
		return false;

	if ( iFct == 0 && !m_isActive)
		return true;

	if ( iFct == KP_TRIAS) {	// Gewaesser fuer Malte
		BringWindowToTop( hWnd);

		bool iFlag = m_hLib->IGMMenuCommand ( iFct,hWnd);
//		bool iFlag = m_hLib->KompaktMenuCommand ( iFct,hWnd);
		if ( !m_hLib->Operation()) {
			MessageBox ( __hWndM,
			 ResString (ResID(IDS_STRKEINKOMMANDO, &RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &RF()),80),
			MB_ICONSTOP);
			return false;
		}
//-------------------------------------------------------
		return iFlag;
	}
//---------GewVergleich--------------------------
	if ( iFct == KP_KOMPAKT) {
		BringWindowToTop( hWnd);
		GewaesserVergleich(true);
		return true;
	}
//////////////////Abgleich/////////////////////////////
	if ( iFct == KP_KOMPAKTABGLEICH) {
		BringWindowToTop( hWnd);
		GewaesserAbgleich();
		return true;
	}

	if ( iFct == KP_UNTERHALTUNG || iFct == KP_AUSSCHREIBUNG ||
		iFct == KP_AUFTRAG || iFct == KP_AUFMASS ) {

		LeistungsBearbeitung (iFct);
		return true;
	}

	if ( iFct == KP_BAUWERKE ) {

		BauwerkeBearbeitung (iFct);
		return true;
	}

	if ( iFct == KP_HYDRAULIK) {
		if ( m_pGewHyd)
			DELETE_OBJ ( m_pGewHyd);
		m_pGewHyd = new KPTree;

		bool iFlag = m_hLib->IGMMenuCommand (iFct,hWnd );
//		bool iFlag = m_hLib->KompaktMenuCommand (iFct,hWnd );
		if ( !m_hLib->Operation()) {
			MessageBox ( __hWndM,
			 ResString (ResID(IDS_STRKEINKOMMANDO, &RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &RF()),80),
			MB_ICONSTOP);
			return false;
		}

		return iFlag;
	}
	if ( iFct == KP_KATASTER) {
//		m_hLib->KompaktMenuCommand ( iFct,hWnd);
		bool iFlag = m_hLib->IGMMenuCommand ( 1, hWnd);
//		bool iFlag = m_hLib->KompaktMenuCommand ( 1, hWnd);
		if ( !m_hLib->Operation()) {
			MessageBox ( __hWndM,
			 ResString (ResID(IDS_STRKEINKOMMANDO, &RF()),80),
			 ResString (ResID(IDS_STRCAPTION, &RF()),80),
			MB_ICONSTOP);
			return false;
		}
		return iFlag;
	}

	bool iFlag = m_hLib->IGMMenuCommand ( iFct, hWnd);
//	bool iFlag = m_hLib->KompaktMenuCommand ( iFct, hWnd);
	if ( !m_hLib->Operation()) {
		MessageBox ( __hWndM,
		 ResString (ResID(IDS_STRKEINKOMMANDO, &RF()),80),
		 ResString (ResID(IDS_STRCAPTION, &RF()),80),
		MB_ICONSTOP);
		return false;
	}

	return iFlag;
}
//--------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////
void CKompiasExtension :: AktualisiereGesamtGewaesser ( long lONr, char *pGewNr, long lLen)
{
	if ( lONr == -1L || lONr == 0L)
		return;
	if ( !pGewNr || *pGewNr == '\0')
		return;
	if ( !m_pGewAlle)
		return;
	CTable t(*m_pGewAlle);
	if ( !t.Find ( pGewNr)){
		GEWAESSER GW;
		memset (&GW, '\0', sizeof(GEWAESSER));
		GW.dwSize = sizeof(GEWAESSER);
		GW.pcGewaesserNr = pGewNr;
		GW.pcGewaesserName = NULL;
		GW.lBeginn = lLen;
		GW.lEnde = lLen;

		KP_GEWCreator KPCr ( *m_pGewAlle);
		ContCreate (KPCr,KP_GEW) (&GW, NULL);
	} else {
		KP_GEWLock l(t);
		l->SpeichereObjekt(lONr);
		l->SpeichereObjektLaenge(lLen);
		l->SetKompaktLen(lLen);
	}
}

//--------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////
KPTree *CKompiasExtension :: GesamtGewaesser (void)
{

	if ( !m_pKH || !m_pKH->GewClass())
		return NULL;

	if ( m_pModObj) {
		CTreeLoeschen ( m_pModObj);
		DELETE_OBJ ( m_pModObj);
	}

		
	KPTree *pGewAlle;

	short iTyp = 0;

//-----------Kompakt-Gewaesser
	KPTree *pGew = HoleGewaesserVonKompakt(iTyp);
//-----------Trias-Gewaesser
	LadeObjektKlasse ( OTLinie, m_pKH->GewClass());
//-----------Trias-Gewaesser mit Laenge + Nr
	pGewAlle = SpeichernGewaesserNummer ( m_pKH->CodeGewNr(),m_pKH->CodeGewName(),m_pKH->GewClass());
	if ( !pGewAlle)
		return NULL;
	pGewAlle->Optimize();
	MischeGewKataster( pGewAlle,pGew);	// Alle GewNr
	DELETE_OBJ ( pGew);
	pGewAlle->Optimize();
	return pGewAlle;
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
bool CKompiasExtension :: EinzelGewaesser (KPTree *pGewP)
{

	if ( !m_pKH || !m_pKH->GewClass())
		return false;

	if ( !pGewP || pGewP->Count() == 0L)
		return false;

	if ( m_pKH->CodeGewNr() == 0L)
		return false;

	CTable t (*pGewP);
	short iFlag = false;

	for (t.First();t.Valid();t.Next()) {
		KP_GEWLock l(t);
		char *pGewNr = l->GewNr();
		if ( !pGewNr || *pGewNr	== '\0')
			continue;



//-----------Trias-Gewaesser mit Laenge + Nr

		long lONr = HoleEinzelGewaesser ( m_pKH->CodeGewNr(),pGewNr);
		if ( lONr == -1L || lONr == 0L) {
			char *pError = new char [_MAX_PATH];
			if ( pError ) {
//				wsprintf (pError,"Zum Gewässer '%s' existiert kein Datenbankobjekt !");
				wsprintf (pError, ResString (ResID(IDS_ERRNOGEWAESSEROBJEKT, &RF()),80),pGewNr);
				MessageBox (__hWndM, 
				 pError,
				 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
				 MB_OK|MB_ICONHAND);
				DELETE_OBJ(pError);
			} else 
				MessageBox (__hWndM, 
				 ResString (ResID(IDS_KEINEGEWAESSER, &RF()),180),
				 ResString (ResID(IDS_STRHYDRAULIK, &RF()),180),
				 MB_OK|MB_ICONHAND);

			continue;
		}

		l->SpeichereObjekt(lONr);

		long lLen = 0L;

		lLen = LinienLaenge ( lONr);
		if ( lLen > 0L) {
			l->SpeichereObjektLaenge ( lLen );
			iFlag = true;
		}
	}

	return iFlag;
}
///////////////////////////////////////////////////////////////////////////
long CKompiasExtension :: HoleEinzelGewaesser ( long lMCode, char *pMText)
{
	if ( !pMText || *pMText == '\0')
		return 0L;
	long lONr = 0L;

	if ( m_pGewAlle) {
		CTable t (*m_pGewAlle);
		if (t.Find(pMText)) {
			KP_GEWLock l(t);
			lONr = l->Objekt();
			return lONr;
		}
	}


	MERKMALSRECHERCHE MR;
	memset (&MR, '\0', sizeof(MERKMALSRECHERCHE));
	MR.pObj = &lONr;
	MR.pMWert = pMText;
	MR.lMCode = lMCode;
	MR.pClass = m_pKH->GewClass();

	CEierUhr Wait ( MVWind());


	ENUMRECHTEXTMERKMAL EM;
	memset (&EM, '\0', sizeof(ENUMRECHTEXTMERKMAL));
	EM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
	EM.lMCode = lMCode;
	EM.pMWert = pMText;
	EM.iMode = SMExactMatch;
	EM.eFcn = (RECHTEXTMERKMALCALLBACK) FindeEinzelObjekt;
	EM.pData = &MR;
	DEX_EnumRechTextMerkmal(EM);

	return lONr;
}
///////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
void CKompiasExtension :: GewaesserVergleich ( short iFlag )
{
	if ( !m_pKH || !m_pKH->GewClass())
		return;

	short iTyp = 0;

	CEierUhr Wait(MVWind());

	char *pData = HoleKompaktDatenPfad();
//	if (pData && m_pDataPath) {		// KK020522
	if (pData && ExistDataPath(pData) && m_pDataPath) {
		if ( strcmp(pData,m_pDataPath) != 0 ) {	//Pfad hat sich geändert
			strcpy (m_pDataPath,pData);
			DELETE_OBJ(m_pGewAlle);
		}
	}

	DELETE_OBJ(pData);

	if ( !m_pGewAlle ) {
		m_pGewAlle = GesamtGewaesser();
		if ( !m_pGewAlle)
			return;
		{
			GewaesserStatistik GS ( MVWind(),IDD_GEWSTATISTIK, RF(), m_pKH->GewDiffLaenge(),m_pGewAlle);
			GS.Show(Centre);  
		}
	}
	
	{
		TriasGewaesser TG ( MVWind(),GEWAESSERUEBERSICHT, RF(), m_pGewAlle, m_hLib,m_pKH->GewDiffLaenge(),iFlag);

		TG.Show(Centre);  
		if (TG.Result() == 1) {
			long *pObjS = TG.Obj();

	// KK010829 - Objekte, die nicht in Sicht definiert wurden !!!
			long * pObj = ViewHasIdent ( pObjS);

			short Flag = ROSortObjNr;
			if ( pObj) {
				CreateORWindow ( Flag, 80, 100, pObj,ResString (ResID(IDS_GEWNUMMER, &RF()),50).Addr(), 0, 255, 255);
				m_isShow = KP_ALL;
			}

			DELETE_OBJ(pObj);
		}
	}

}
//--------------------------------------------------------------------------
long * CKompiasExtension :: ViewHasIdent ( long * pObj)
{
	long * pOB = new long [*pObj+1];
	
	if ( !pOB )
		return NULL;

	long lNumber = 0L;
	*pOB = lNumber;

	for ( long i = 0; i < *pObj; i++ ) {

		long lONr = *(pObj+i+1);

		VIEWIDENTOBJECT VIO;
		memset (&VIO, '\0', sizeof(VIEWIDENTOBJECT));
		VIO.dwSize = sizeof(VIEWIDENTOBJECT);
		VIO.m_pView = NULL;
		VIO.m_lIdent = DEX_GetObjIdent(lONr);
//		VIO.m_lONr=lONr;
		VIO.m_iOTyp=OTLinie|OTPunkt;

		if (DEX_ViewHasIdent(VIO)) {
			lNumber++;
			*(pOB+lNumber) = lONr;
			*pOB = lNumber;
		}
	}

	if ( *pOB < *pObj)
		MessageBox (__hWndM, 
		 ResString (ResID(IDS_KEINEGEWAESSERINSICHT, &RF()),180),
		 ResString (ResID(IDS_KOMPPAGECAPTIONX, &RF()),180),
		 MB_OK|MB_ICONHAND);

	if ( 0L == lNumber )
		DELETE_OBJ(pOB);

	return pOB;

}
///////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
void CKompiasExtension :: GewaesserAbgleich (void )
{
	if ( !m_pKH || !m_pKH->GewClass())
		return;

	DELETE_OBJ (m_pGewAlle);

//-----------Trias-Gewaesser
	LadeObjektKlasse ( OTLinie, m_pKH->GewClass());

//-----------Trias-Gewaesser mit Name

	AbgleichGewaesserDaten(m_pKH->CodeGewNr(),m_pKH->CodeGewName(),m_pKH->GewClass());
}
//--------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
char * CKompiasExtension :: FSTest (void )
{
	char *pTest = new char [_MAX_PATH];
	if ( !pTest)
		return NULL;
	*pTest = '\0';
	strcat ( pTest, "Meine Extension");
	return pTest;
}
//--------------------------------------------------------------------------


//---------------------------------------------------------------------------
// File: KOMPMENU.CXX
