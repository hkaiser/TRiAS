// File: TPROJECT.CXX

#include "tprojp.hxx"

#include <shellapi.h>

#include <xtsnaux.hxx>
#include <xtsnguid.h>
#include <initguid.h>

#include "tprjguid.h" 
#include "version.h"

#include "defproj.h"
#include "tproject.h"
#include "about.h"

#include "about.hxx"
#include "menukey.hxx"
#include "projprof.hxx" 
#include "txtedit.hxx"
#include "teprodef.hxx"
#include "tpmcode.hxx"
#include "tproject.hxx"		// Klasse für diese Erweiterung

#if _MSC_VER >= 1100
EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
EXTERN_C const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
#endif // _MSC_VER >= 1100


// Map für MerkmalsCodes
typedef map<HPROJECT, os_string, less<HPROJECT> > CMCodeMap;
CMCodeMap g_MCodes;

static LPCTSTR g_cbNameKey	= TEXT("Software\\%s\\%s\\Config");
static LPCTSTR g_cbSecKey	= TEXT("Software\\%s\\%s\\Extensions\\TRiAS.Teilprojekte.1\\Config");


//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//

CTriasExtension *NewExtension (void)
{
	return new CProjectExtension ();
}


//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_Projektverkettung, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
//
// ACHTUNG: Im VersionsRC-File (*.rcv) nicht den Eintrag "TRiASSelfRegister" 
// vergessen. Ohne diesen EIntrag wird die Funktion UpdateRegistry nie gerufen.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_Projektverkettung, 
				TEXT("TRiAS.Teilprojekte.1"), IDS_LONGCLASSNAME,
				TPROJECT_MAJORVERSION, TPROJECT_MINORVERSION,
				EFUnLoadable|EFVisible);
		return fSuccess;
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_Projektverkettung, 
				TEXT("TRiAS.Teilprojekte.1"));
	}

return true;	// alles ok

}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muá von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuhängenden Menu's übergeben bekommt.
CProjectExtension :: CProjectExtension (void)
		   : CTriasExtension (CPROJECTEXTENSIONMENU)	// Menu's

{
	m_iActive = false;
//--------------------HauptProjekt-----------------------
	m_pMainProject = NULL;
	m_pMainUser = NULL;
	m_pMainSight = NULL;

	m_iLevel = 0;
	m_iLowLevel = 0;
	m_iHighLevel = 0;

	m_MenuID1 = UINT ( IDM_TPROJECT);
	m_MenuID2 = UINT ( IDM_TPROJECT);

//------------------------------------------------------------

	m_pPrevDir = NULL;	// vorheriges lokales Projektverzeichnis
	m_pLocDir = NULL;	// lokales Projektverzeichnis
	m_pMainDir = NULL;	// globales Projektverzeichnis
	m_pProjectName = NULL;	// neues Projekt
	m_pProjectKey = NULL;	// neuer Projektschlssel
	m_pOwnerCheck = NULL;	// obere Hierarchie

	m_hWnd = 0;		// FensterHandle des aktiven ORFensters
	m_hMenu = 0;		// Menu der Erweiterung
	m_lONr = 0L;		// ObjektNummer
	m_lIdent = 0L;		// Identifikator
	m_hPr = 0;
	m_lHeadMCode = 0L;
	m_isSwitchTP = false;	// kein TP-Aufruf
	m_iSetCont = FALSE;

// KK010522
// Temp-ini
	_pIniOriginal = NULL;
	_pIniTemp = NULL;
	m_bTPUndef= false;
	m_isTempINI = false;

	m_pPROJ = NULL;		// ProjektBaum
	m_pTPRJ = NULL;		// Kette von Teilprojekten;
	m_pMenu = NULL;		// Kette von MenuPunkten;

	m_iMenu = false;	// Kein Menu aufgebaut
	m_iMain = false;	// Kein Main vorhanden

	m_iActMenuPoint = -1;
	m_NumMenuPoints = -1;

	m_iObjCount = 0;

//	Container	- 23.08.94
	m_lMainSightContainer[0] = 0L;
	m_lMainSightContainer[1] = 0L;
	m_lMainSightContainer[2] = 0L;
	m_lMainSightContainer[3] = 0L;

	m_isSearch = FALSE;


// KK010112
	_pTRiNam = NULL;

	_pTRiNam = new char [_MAX_PATH];
	if ( _pTRiNam) 
	{
	DWORD d = _MAX_PATH;

	TCHAR szKey[_MAX_PATH];
	wsprintf(szKey,g_cbNameKey,REG_COMPANY_KEY,REG_PRODUCT_KEY);

//	CCurrentUser rgMASS("Software\\TRiAS\\TRiAS\\Config", true);

	CCurrentUser rgMASS(szKey, true);
	rgMASS.GetSubSZ ("TRiASName", _pTRiNam,d);
	}

}

// Destruktor -----------------------------------------------------------------
CProjectExtension :: ~CProjectExtension (void) 
{
	
	DELETE_OBJ ( _pTRiNam);

	DELETE_OBJ (m_pMainProject);
	DELETE_OBJ (m_pMainUser);
	DELETE_OBJ (m_pMainSight);
	
	DELETE_OBJ (m_pLocDir);
	DELETE_OBJ (m_pPrevDir);
	DELETE_OBJ (m_pMainDir);
	DELETE_OBJ (m_pProjectName);
	DELETE_OBJ (m_pProjectKey);
	DELETE_OBJ (m_pOwnerCheck);

	DELETE_OBJ (m_pPROJ);
//	DELETE (m_pTPRJ);
	DELETE_OBJ (m_pMenu);

	// Temp-ini
	DELETE_OBJ(_pIniOriginal);
	DELETE_OBJ (_pIniTemp);


}

// ----------------------------------------------------------------------------

// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
STDMETHODIMP_(BOOL) CProjectExtension :: InitExtension (THIS_ short iMode) 
{

	if (!CTriasExtension :: InitExtension (iMode))
		return false;

// hier zusätzlichen MenuPunkt anhängen
//	InstallMenuItem (IDM_SHOWPROJECT, IDS_PROJECTMENUITEM, TRUE, 0);
//	InstallMenuItem (IDM_DEFWNDPROJECT, IDS_PROJECTDEF, TRUE, 1);

// KK010313 - Auf Wunsch
	InstallMenuItem (IDM_SHOWPROJECT, IDS_PROJECTMENUITEM, TRUE, 1);
	InstallMenuItem (IDM_DEFWNDPROJECT, IDS_PROJECTDEF, TRUE, 0);


	m_wMsg1 = RegisterWindowMessage ("HILFEOPENPROJECT");
	m_wMsg2 = RegisterWindowMessage ("OPENPREVIOUSPROJECT");
	m_wMsg3 = RegisterWindowMessage ("OPENPREVIOUSLEVEL");

// Notifikationen anfordern
	RegisterNotification (DEX_PROJECTOPEN);
//	RegisterNotification (DEX_ISCLOSEDPROJECT);
	RegisterNotification (DEX_N_PROJECTTOCLOSE);
	RegisterNotification (m_wMsg1,false);
	RegisterNotification (m_wMsg2,false);
	RegisterNotification (m_wMsg3,false);

	m_iActive = true;

//-----27.08.97------
	DefinitionAusschnitt();

// aktuelles Projektverzeichnis besorgen
	if ( m_pLocDir == NULL ) 
		m_pLocDir = new char [_MAX_PATH];
	if ( m_pLocDir != NULL ) {
		if (DEX_GetActiveProject (m_pLocDir) == NULL) {
		// noch kein Projekt eröffnet

			DELETE_OBJ (m_pLocDir);
		} else {
			strupr( m_pLocDir);
			if ( m_pMainDir == NULL ) 
				m_pMainDir = new char [_MAX_PATH];
			if ( m_pMainDir != NULL ) {
				if (DEX_GetActiveProject (m_pMainDir) == NULL) {
				// noch kein Projekt eröffnet

					DELETE_OBJ (m_pMainDir);
				} else {
					strupr ( m_pMainDir);
					m_iMain = TRUE;
					StoreMainProject();
				}
			}
			//	MCode TProject
			m_hPr = DEX_GetDataSourceHandle();
			GetHeaderMCodeEx();

		}
	}

return TRUE;
}
/////////////////////////////////////////////////////////////////////
STDMETHODIMP_(BOOL) CProjectExtension :: UnLoadExtension (THIS)
{
// MenuPunkt natürlich wieder ausbauen
//	RemoveMenuItem (IDM_SHOWPROJECT, TRUE, 0);
//	RemoveMenuItem (IDM_DEFWNDPROJECT, TRUE, 1);

// KK010313
	RemoveMenuItem (IDM_SHOWPROJECT, TRUE, 1);
	RemoveMenuItem (IDM_DEFWNDPROJECT, TRUE, 0);

// Notifikationen wieder abmelden
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);
//	UnRegisterNotification (DEX_ISCLOSEDPROJECT);
	UnRegisterNotification (m_wMsg1,false);
	UnRegisterNotification (m_wMsg2,false);
	UnRegisterNotification (m_wMsg3,false);

	m_iActive = false;
	if ( m_pPROJ) {
    	CTable t ( *m_pPROJ);
		if ( t.Find(m_pLocDir))  {
			PROJLock l(t);
			m_pTPRJ = l->pTPRJ();
			DeleteTPMenu ( m_hMenu);
		}
	}

	DefineStartParameter();

	return CTriasExtension :: UnLoadExtension();	// kein Fehler

}

// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(BOOL) CProjectExtension :: MenuCommand (WPARAM MenuItemID, HWND hWnd)
{

	switch (MenuItemID) {	

	case IDM_SHOWPROJECT:
	{
	if ( m_pProjectKey)
		PostMessage ( __hWndM,m_wMsg1,0,0);
//		ZeigeProject();
	return TRUE;
	}

//--------------------------------------------------------------------
	case IDM_OPENPREVIOUSPROJECT:
	{

	PostMessage ( __hWndM,m_wMsg2,0,0);

//	GoToPreviousProject(TRUE);

	return TRUE;

	}

	case IDM_OPENPREVIOUSLEVEL:
	{

	PostMessage ( __hWndM,m_wMsg3,0,0);

//	GoToPreviousProject(FALSE);
		
	return TRUE;
	}

//-----------------------------------------------------------------------
	case IDM_SETCONT:
	{

	TCHAR szKey[_MAX_PATH];
	wsprintf(szKey,g_cbSecKey,REG_COMPANY_KEY,REG_PRODUCT_KEY);
	DWORD dSTest;


	if ( m_iSetCont ) {
		pExtMenu()->unCheckItem( UINT ( IDM_SETCONT ) + MenuOffset());
		m_iSetCont = FALSE;
		m_lMainSightContainer[0] = 0L;
		m_lMainSightContainer[1] = 0L;
		m_lMainSightContainer[2] = 0L;
		m_lMainSightContainer[3] = 0L;
		dSTest = 0L;
	} else {
		m_iSetCont = TRUE;
		pExtMenu()->CheckItem( UINT ( IDM_SETCONT ) + MenuOffset());
		DEX_GetActiveSightContainer( m_lMainSightContainer );
		dSTest = 1L;

	}

	{
		CCurrentUser rgMASS(szKey, true);
//		CCurrentUser rgMASS("Software\\TRiAS\\TRiAS\\Extensions\\TRiAS.Teilprojekte.1\\Config", true);
		rgMASS.SetDWORD ( "SightCont",dSTest);
	}

	return TRUE;
	}


/*	case IDM_ABOUT:
	{
		AboutBox AB (MWind(), ResID (PROJECTABOUT, &RF()));

		AB.Show();
		return TRUE;
	} 
*/
	case IDM_DEFPROJECT:
	{
	if ( !m_pPROJ)
		return TRUE;
	m_lONr = 0L;

	CTable t( *m_pPROJ );
	if ( m_pLocDir && t.Find( m_pLocDir )) {
		{
		PROJLock l(t);
		m_pTPRJ = l->pTPRJ();
		if ( !m_pTPRJ )
			m_NumMenuPoints = 0;
		else
			m_NumMenuPoints = (int) m_pTPRJ->Count();


		m_iLevel = l->Level();
		}
		if ( m_pMenu)
			DELETE_OBJ ( m_pMenu);
		m_pMenu = new MMenuTree;
		if ( !m_pMenu )
			return TRUE;

		{
		TProjectDefine TPD ( MVWind(),TPROJECTDEFINITION, RF(), m_pLocDir,m_pPROJ,m_pMenu);
		TPD.Show();
		if ( TPD.Result() == 1 ) {
			if ( TPD.isModifiedProFile() ) {
				m_pTPRJ = GetTPAktuell(m_pLocDir);
				if ( !m_pTPRJ )
					m_NumMenuPoints = 0;
				else
					m_NumMenuPoints = (int) m_pTPRJ->Count();
			// Zusammenstellen eines neuen pTPRJ / VerarbKZ
				ModifyMenu ( m_hMenu );
				ModifyProjectProFile();
				CreateTPPartMenu ( m_hMenu );
			} 
		}
		}

	}
	return TRUE;
	}

	case IDM_DEFWNDPROJECT:
	{

	m_lONr = DEX_GetActiveObject (hWnd);	// 1. ObjektNummer besorgen

	if ( 0L == m_lONr)
		return TRUE;

	m_hPr = DEX_GetObjectProject(m_lONr);	// aktuelle Datenquelle

	GetHeaderMCode();

	if ( m_lHeadMCode == 0L ) {
		long lMHandle = DEX_GetUniqueSysMCode();
		m_lHeadMCode = DEX_MapHandleToMCode(lMHandle);
			
/*
		TPMCodeDef TPM ( ORWind(hWnd),TPROJECTMCODE, RF());
		TPM.Show();
		if ( TPM.Result() == 1 ) {

			if ( DEX_GetMkBase() == 16 )
				m_lHeadMCode = strtoul ( TPM.GetTPMCode (),NULL,16);
			else
				m_lHeadMCode = atol ( TPM.GetTPMCode ());

  */

//			SetHeaderMCode ( TPM.GetTPMCode());

			char Buf[30];	
			ULONG uMCode = (ULONG) m_lHeadMCode;
			wsprintf (Buf, "%lx",uMCode);

			SetHeaderMCode ( DEX_GetObjectProject(m_lONr),&Buf[0] );
			SetPBDMCode (m_lONr, m_lHeadMCode );
//		} else
//			return TRUE;
	}

	if ( !m_pPROJ)
		return TRUE;

	CTable t( *m_pPROJ );
	if ( m_pLocDir && t.Find( m_pLocDir )) {
		{
		PROJLock l(t);
		m_pTPRJ = l->pTPRJ();

		if ( !m_pTPRJ)
			m_NumMenuPoints = 0;
		else
			m_NumMenuPoints = (int) m_pTPRJ->Count();

		m_iLevel = l->Level();
		}
		if ( m_pMenu)
			DELETE_OBJ ( m_pMenu);
		m_pMenu = new MMenuTree;
		if ( !m_pMenu )
			return TRUE;
		if ( !m_pProjectKey ) {
			m_pProjectKey = new char [_MAX_PATH];
			if ( !m_pProjectKey)
				return TRUE;
			*m_pProjectKey = '\0';
		}

		{
		TProjectDefine TPD ( ORWind(hWnd),TPROJECTDEFINITION, RF(), m_pLocDir,m_pPROJ,m_pMenu,m_pProjectKey);
		TPD.Show();
		if ( TPD.Result() != 0 ) {
			char *pProjectKey = TPD.GetNewKey();
			if ( TPD.isModifiedProFile() ) {
				m_pTPRJ = GetTPAktuell(m_pLocDir);
				if ( !m_pTPRJ)
					m_NumMenuPoints = 0;
				else
					m_NumMenuPoints = (int) m_pTPRJ->Count();
		// Zusammenstellen eines neuen pTPRJ / VerarbKZ
				ModifyMenu ( m_hMenu );
				ModifyProjectProFile();
				CreateTPPartMenu ( m_hMenu );
			} 
//------------Objekt modifizieren---------------------------
			// MerkmalsWert holen

		// KK010114
			if(!pProjectKey || *pProjectKey == NULL)
				pProjectKey = TPD.RefTP();

			TARGETMERKMAL tm;

			tm.dwSize = sizeof(TARGETMERKMAL);
			tm.lTarget = m_lONr;		// ObjektNummer
			tm.lMCode = m_lHeadMCode;		// MerkmalsCode
			if ( TPD.Result() == -1 ) {	// Loeschen
				tm.imaxLen = NULL;
				tm.pMText = NULL;
				*pProjectKey = '\0';
			} else {
				tm.imaxLen = _MAX_PATH;
				if ( pProjectKey == NULL || *pProjectKey == '\0' )
					return TRUE;
				char inChar = *pProjectKey;
				if ( islower(inChar) ) {
					inChar = toupper(inChar);
					*pProjectKey = inChar;
				}
				tm.pMText =pProjectKey;		// Puffer
			}
			tm.iTTyp = TT_Objekt;
			DEX_ModTextMerkmal (tm);
			
		}
		}
	}

	return TRUE;
	}


	case IDM_SEARCHPROJECT:
	{
	GetHeaderMCode();


//---09.6.95------
	if (!m_pPROJ)
		return TRUE;

	CTable d( *m_pPROJ);
	if ( !d.Find( m_pLocDir))
		return TRUE;
	m_iActMenuPoint = -1;
	PROJLock k(d);
	m_pTPRJ = k->pTPRJ();
	if ( !m_pTPRJ) {
		m_NumMenuPoints = 0;
	} else {
		m_NumMenuPoints = (int) m_pTPRJ->Count();
	}
//------------------------------------------------

	if ( m_lHeadMCode != 0 ) {

		long NrObj = NumberTProjects();
		if ( NrObj == 0L)
			return TRUE;

		TPPOINT TP;
		TP.pTPRJ = m_pTPRJ;
		long *pObjPos = new long [ NrObj + 1];
		if ( !pObjPos)
			return TRUE;

		long *pObjNeg = new long [ NrObj + 1];
		if ( !pObjNeg) {
			DELETE_OBJ ( pObjPos);
			return TRUE;
		}

		*pObjPos = 0L;
		*pObjNeg = 0L;
		TP.pObjPos = pObjPos;
		TP.pObjNeg = pObjNeg;

		CEierUhr Wait ( MWind());
//---------------------------------------------------------------------

		CMCodeMap::iterator it;
		char cbBuffer[_MAX_PATH];

		for (it = g_MCodes.begin(); it != g_MCodes.end(); ++it) {
			m_hPr = (*it).first;

			wsprintf (cbBuffer, "%s", (*it).second.c_str());

			ULONG lHeadMCode = 0L;
			lHeadMCode = strtoul ( cbBuffer, NULL, 16 );
			if ( 0L != lHeadMCode)
			m_lHeadMCode = DEX_MapMCodeToHandle(m_hPr,lHeadMCode);
	
			TP.TPMCode = m_lHeadMCode;


			ENUMRECHTEXTMERKMAL EM;
			memset (&EM, '\0', sizeof(ENUMRECHTEXTMERKMAL));
			EM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
			EM.lMCode = m_lHeadMCode;
			EM.iMode = SMExistanceOnly;
			EM.eFcn = (RECHTEXTMERKMALCALLBACK) NumTPObjects;
			EM.pData = &TP;
			DEX_EnumRechTextMerkmal(EM);
		}
//------------------------------------------------------------------------

		char * pCaption = new char [_MAX_PATH];
		if ( pCaption ) {
			*pCaption = '\0';
			strcat ( pCaption, ResString(ResID(IDS_TPORWINDOWCAPTION,&RF()),50));
		}
		if ( *pObjPos > 0L ) {
			short Flag = ROSortText;	
			if ( pCaption)
				CreateORWindow ( Flag, 10, 10, pObjPos, pCaption,255,0,255);
			else
				CreateORWindow ( Flag, 10, 10, pObjPos, "Teilprojekte",255,0,255);
		}
		DELETE_OBJ ( pObjPos);

		if ( *pObjNeg > 0L ) {
			short Flag = ROSortText;
			if ( pCaption ) {
				strcat ( pCaption, ResString(ResID(IDS_TPORWINDOWFALSE,&RF()),50));
				CreateORWindow ( Flag, 320, 10, pObjNeg, pCaption,255,255,0);
			} else 
				CreateORWindow ( Flag, 320, 10, pObjNeg, "Teilprojekte-fehlerhafte Zuordnung",255,255,0);
		}
		DELETE_OBJ ( pObjNeg);
		DELETE_OBJ ( pCaption);
	}
	return TRUE;
	}

	default:
	{
	if ( MenuItemID > ((WPARAM) (m_MenuID1 + MaxExtension)) )
		return FALSE;		// gehört mir nicht
	if ( !m_pPROJ)
		return FALSE;
	if ( !m_pLocDir)
		return FALSE;
	CTable d( *m_pPROJ);
	if (!d.Find( m_pLocDir))
		return FALSE;
	PROJLock k(d);
	m_pTPRJ = k->pTPRJ();
	if ( !m_pTPRJ)
		return TRUE;

	if ( !m_pProjectName )
		m_pProjectName = new char [_MAX_PATH];
	if ( m_pProjectName == NULL )
		return TRUE;
	*m_pProjectName = '\0';        

	if ( !m_pProjectKey )
		m_pProjectKey = new char [_MAX_PATH];
	if ( m_pProjectKey == NULL )
		return TRUE;
	*m_pProjectKey = '\0';        

	if ( m_iActMenuPoint != (int ( MenuItemID) - int(IDM_TPROJECT) + 1) ) {
		m_iActMenuPoint =int ( MenuItemID) - int(IDM_TPROJECT) + 1;

//----------------Baum her-----------------------------------------------
//	Eigentlich Zugriff über TPROJ -> l->pTPRJ
//		Name über l->DBname,DBUser.....
		
		if ( m_iActMenuPoint > m_NumMenuPoints )
			FindSecondLevel((UINT) MenuItemID);
		else
			FindFirstLevel();

		PostMessage ( __hWndM,m_wMsg1,0,0);
//		ZeigeProject();
//-------------------------------------------------------------------------

	}
	return TRUE;
	}	// default

	}	// SWITCH
return FALSE;
}

// Herausfinden, ob das aktive Objekt ein Projekt hat, Menu entsprechend richten
STDMETHODIMP_(BOOL) CProjectExtension :: MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{

// Mein Menu ???

	if (hWnd == NULL && hMenu != MenuHandle()) return FALSE;


//	if (hWnd != NULL && hMenu != ORMenuHandle()) return FALSE;
//	Gilt nur bei EXTRAS !!!!!!!!

// aktuelles Projektverzeichnis besorgen
	if ( m_pLocDir == NULL || *m_pLocDir == NULL ) 
		return FALSE;		//weiter

	CEierUhr Wait ( MWind());

	SetDQ();	// Datenquellen sammeln

// Mein Menu im Kopf
	if ( hWnd == 0 && hMenu == MenuHandle() ) {
		m_iActive = true;
		if ( !m_iMenu ) {
			if ( m_pPROJ != NULL )
				DELETE_OBJ ( m_pPROJ);

			m_pPROJ = new PROJTree;
			m_pTPRJ = NULL;

			if ( m_pPROJ == NULL )
				return FALSE;

			m_hMenu = hMenu;
			m_iMenu = true;
			pExtMenu()->DisableItem ( UINT( IDM_OPENPREVIOUSPROJECT ) + MenuOffset() );
			pExtMenu()->DisableItem ( UINT( IDM_OPENPREVIOUSLEVEL ) + MenuOffset() );

			CreateTPMenu(m_hMenu);
		}

//---------------Teilprojekte in MKode ???
	  
		//	MCode TProject
		m_hPr = DEX_GetDataSourceHandle();
		GetHeaderMCodeEx();
		pExtMenu()->DisableItem ( UINT( IDM_SEARCHPROJECT ) + MenuOffset() );

//---09.06.95------
	  	if ( !m_pPROJ)
			return FALSE;
	  	CTable d( *m_pPROJ);
	  	if ( !d.Find( m_pLocDir))
			return FALSE;
		m_iActMenuPoint = -1;

		PROJLock k(d);

		m_pTPRJ = k->pTPRJ();
		if ( !m_pTPRJ) {
			m_NumMenuPoints = 0;
	  	}

	  	if ( m_lHeadMCode != 0 ) {
			long NrObj = NumberTProjects();
			if ( NrObj > 0L) {
				pExtMenu()->EnableItem ( UINT( IDM_SEARCHPROJECT ) + MenuOffset() );
			}
		}

	}
//-------------------war mein Kopf-----------------------------

	if ( m_iActive && hWnd != 0 ) {		//ORFenster!!
// Menu im ORFenster initialisieren
		if ( !m_iMenu ) {
			if ( m_pPROJ != NULL )
				DELETE_OBJ ( m_pPROJ);

			m_pPROJ = new PROJTree;
			m_pTPRJ = NULL;
			if ( m_pPROJ == NULL )
				return FALSE;
			m_hMenu = MenuHandle();
			m_iMenu = true;
			pExtMenu()->DisableItem ( UINT( IDM_OPENPREVIOUSPROJECT ) + MenuOffset() );
			pExtMenu()->DisableItem ( UINT( IDM_OPENPREVIOUSLEVEL ) + MenuOffset() );

			CreateTPMenu(m_hMenu);

		}

		uint iMenuID = IDM_SHOWPROJECT + MenuOffset();
		EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);
//----------------Fenster
		m_lONr = DEX_GetActiveObject (hWnd);	// 1. ObjektNummer besorgen

		if ( 0L == m_lONr ) {
			EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);
			return FALSE;
		}
		m_hPr = DEX_GetObjectProject(m_lONr);	// aktuelle Datenquelle
//---------------------------------------
		short Status = DEX_GetObjectStatus ( m_lONr );
		if ( Status != OSNormal && Status != OSModified ) {
			m_lONr = 0L;
			EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);
			return FALSE;
		}

// 3. in INI-Datei des Projektes nach ProjectMCode suchen

		GetHeaderMCode ();

	 	if ( m_lHeadMCode == 0L ) {
			EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);
			return FALSE; 
		}

// 4. wenn Merkmal existiert, dann hat Objekt ein angehängtes Projekt

		EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);



		DELETE_OBJ ( m_pProjectKey);
		m_pProjectKey = new char [_MAX_PATH];
		if ( !m_pProjectKey)
			return FALSE;
		*m_pProjectKey = '\0';

	// MerkmalsWert holen
		TARGETMERKMAL tm;

		char * pPuffer = new char [_MAX_PATH];
		if ( !pPuffer)
			return TRUE;
		*pPuffer = '\0';
		tm.dwSize = sizeof(TARGETMERKMAL);
		tm.lTarget = m_lONr;		// ObjektNummer
		tm.lMCode = m_lHeadMCode;		// MerkmalsCode
		tm.imaxLen = _MAX_PATH;
		tm.pMText = pPuffer;		// Puffer
		tm.iTTyp = TT_Objekt;
		DEX_GetTextMerkmal (tm);

		if ( *pPuffer == '\0') {
			DELETE_OBJ ( pPuffer);
			return FALSE;
		}
		strtok ( pPuffer , ";,\t");
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		m_pTPRJ = GetTPAktuell ( m_pLocDir);

		if ( !m_pTPRJ ) {
			DELETE_OBJ ( pPuffer);
			return FALSE;
		}

		CTable t( *m_pTPRJ);

		if ( t.Find(pPuffer)){
			EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_ENABLED);
			strcpy ( m_pProjectKey, pPuffer );
		} else 
			EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);

		DELETE_OBJ ( pPuffer );
	}
	return FALSE;
}

// Diese Funktion wird bei Systemereignissen diverser Natur gerufen -----------
STDMETHODIMP_(LRESULT) CProjectExtension :: Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg) {

	case DEX_QUERYRECHOBJECT:
	
		{

		if ( m_isSearch ) {
			if ( !m_pTPRJ ) 
				return FALSE;
			m_lONr = ((RECHOBJECT * ) p)->lONr;
			if ( m_lONr == 0L )
				return FALSE;

			m_hPr = DEX_GetObjectProject(m_lONr);	// aktuelle Datenquelle
			GetHeaderMCode();

			m_lIdent = DEX_GetObjIdent ( ((RECHOBJECT * ) p)->lONr);
	// MerkmalsWert holen
			TARGETMERKMAL tm;

			short iTextLen = (( RECHOBJECT *)p)->iTextLen;
			char * pPuffer = new char [iTextLen+1];

			if ( !pPuffer )
				return FALSE;
			*pPuffer = '\0';
			tm.dwSize = sizeof(TARGETMERKMAL);
			tm.lTarget = m_lONr;		// ObjektNummer
			tm.lMCode = m_lHeadMCode;		// MerkmalsCode
			tm.imaxLen =  (( RECHOBJECT *)p)->iTextLen;
			tm.pMText = pPuffer;		// Puffer
			tm.iTTyp = TT_Objekt;
			DEX_GetTextMerkmal (tm);

			if ( *pPuffer == '\0') {
				DELETE_OBJ ( pPuffer);
				return FALSE;
			}
			strtok ( pPuffer , ";,\t");
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			if ( !m_pTPRJ ) {
				DELETE_OBJ ( pPuffer);
				return FALSE;
			}

			CTable t( *m_pTPRJ);
			if ( t.Find(pPuffer)){
				strcpy ((( RECHOBJECT *) p)->lpText , pPuffer );
			}
			DELETE_OBJ ( pPuffer);

		}
		}
		
		break;


	case DEX_PROJECTOPEN:		// neues Projekt wurde eröffnet
		{			// Projektverzeichnis merken
		SetDQ();
		m_isSwitchTP = false;
		m_iActive = true;
		m_isTempINI = false;
		DELETE_OBJ(_pIniTemp);

		if ( m_pPrevDir == NULL ) 
			m_pPrevDir = new char [_MAX_PATH];
		if ( m_pPrevDir != NULL ) {
			if ( m_pLocDir != NULL ) {
				*m_pPrevDir = '\0';
				strcpy ( m_pPrevDir, m_pLocDir);
				strupr( m_pPrevDir);
			} else
				DELETE_OBJ ( m_pPrevDir);
		}
// aktuelles Projektverzeichnis besorgen
		if ( m_pLocDir == NULL ) 
			m_pLocDir = new char [_MAX_PATH];
		if ( m_pLocDir != NULL ) {
			*m_pLocDir = '\0';
			if (DEX_GetActiveProject (m_pLocDir) == NULL) {
			// noch kein Projekt eröffnet

				DELETE_OBJ (m_pLocDir);
			} else {
				strupr ( m_pLocDir);
				if ( !m_iMain ) {
					if ( m_pMainDir == NULL ) 
						m_pMainDir = new char [_MAX_PATH];
					if ( m_pMainDir != NULL ) {
						if (DEX_GetActiveProject (m_pMainDir) == NULL) {
						// noch kein Projekt eröffnet

							DELETE_OBJ (m_pMainDir);
						} else {
							strupr ( m_pMainDir);
							m_iMain = true;
							StoreMainProject();
						}
					}
				}
				m_hPr = DEX_GetDataSourceHandle();
				GetHeaderMCode();
			}
		}
		if ( m_pPROJ ) {
			CTable t( *m_pPROJ);
			if ( m_pLocDir && t.Find ( m_pLocDir )) {
				PROJLock l(t);
				m_iLevel = l->Level();
				if ( m_pMainDir && strcmp ( m_pLocDir,m_pMainDir) == 0 ) 
					m_pTPRJ = l->pTPRJ();
			}
		} else
			m_iLevel = 0;

		DefinitionAusschnitt();

		}
		break;

	case DEX_N_PROJECTTOCLOSE:		// dieses Projekt soll geschlossen werden
		{

// KK010517
// Hier geänderte TP-Verweise abspeichern ???
		if (!WritePrivateIniFile())
			break;		
		if ( !m_isSwitchTP) {
			if ( m_pPROJ) {
		    		CTable t ( *m_pPROJ);
				if ( t.Find(m_pLocDir))  {
					PROJLock l(t);
					m_pTPRJ = l->pTPRJ();
					DeleteTPMenu ( m_hMenu);
				}
			}
			m_iActive = false;
			DefineStartParameter();
		} else {
			pExtMenu()->EnableItem ( UINT( IDM_OPENPREVIOUSPROJECT ) + MenuOffset() );
			pExtMenu()->EnableItem ( UINT( IDM_OPENPREVIOUSLEVEL ) + MenuOffset() );
		}
		}
		break;
/*-----

	case DEX_ISCLOSEDPROJECT:		// dieses Projekt soll geschlossen werden
		{

// ProjectClose  nötig ??
		m_iActive = false;
		if ( m_pPROJ) {
	    	CTable t ( *m_pPROJ);
			if ( t.Find(m_pLocDir))  {
				PROJLock l(t);
				m_pTPRJ = l->pTPRJ();
				DeleteTPMenu ( m_hMenu);
			}
		}
		DELETE_OBJ( m_pPROJ);
		}
		break;
-------------------------------------------*/

	default:
		break;

	}	//SWITCH

//	return FALSE;	// alles andere ignorieren
	return CTriasExtension :: Notification( iMsg,p);		// kein Fehler

}
////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------

STDMETHODIMP_(LRESULT) CProjectExtension ::  WindowsNotification (UINT wMsg, WPARAM, LPARAM p)
{
	CEierUhr Wait ( MWind());

	if ( m_wMsg1 == wMsg ) {
		ZeigeProject();		
	}
	if ( m_wMsg2 == wMsg ) {
		GoToPreviousProject(TRUE);
	}
	if ( m_wMsg3 == wMsg ) {
		GoToPreviousProject(FALSE);
	}

	return false;

}

//-----------------------Member-----------------------------------------
void CProjectExtension :: DefinitionAusschnitt(void)
{
	if ( !m_iSetCont) {
	//-----27.08.97------
		DWORD dSTest;
		dSTest = 0L;
		{
		CCurrentUser rgMASS("Software\\TRiAS\\TRiAS\\Extensions\\TRiAS.Teilprojekte.1\\Config", true);
		rgMASS.GetDWORD ( "SightCont",dSTest);
		if (dSTest > 0){
			m_iSetCont = TRUE;
			pExtMenu()->CheckItem( UINT ( IDM_SETCONT ) + MenuOffset());
			DEX_GetActiveSightContainer( m_lMainSightContainer );

		}
	}
	}
	return;
}
//-------------------------------------------------------------------------
void CProjectExtension :: ZeigeProject ( void)
{
//	CEierUhr Wait ( MWind());

	if (!m_pTPRJ)
		return;
	if (!m_pPROJ)
		return;
	CTable t ( *m_pTPRJ);
	CTable d ( *m_pPROJ);
	if ( !t.Find ( m_pProjectKey )) 
		return ;
	TPRJLock l(t);

	if ( !m_pProjectName )
		m_pProjectName = new char [_MAX_PATH];
	if ( m_pProjectName == NULL )
		return;
	*m_pProjectName = '\0';        
	strcat ( m_pProjectName, l->Drive());
	strcat ( m_pProjectName, l->Path());								
	strcat ( m_pProjectName, l->DBName());
	strcat ( m_pProjectName, l->Ext());
	strupr(m_pProjectName);

	m_iLevel = l->Level();

	bool Flag = SwitchToProject ( m_pProjectName, l->UserName(),l->SightName());
        
	if ( Flag ) {	// Projekt ist umgeschaltet
		if (!m_pLocDir || *m_pLocDir == '\0')
			return;
		if ( !d.Find( m_pLocDir )) {
			DBPROJECT DB;
			SetZero ( &DB);
			DB.pDBName = l->DBName();
			DB.pDrive = l->Drive();
			DB.pUserName = l->UserName();
			DB.pPath = l->Path();
			DB.pExt = l->Ext();
			DB.pOwner = l->Owner();
			strupr( m_pPrevDir);
			DB.pPrev = m_pPrevDir;
			DB.iLevel = l->Level();
			char * pSight = new char [ _MAX_PATH];
			if ( l->SightName() == NULL ) {	
				if ( pSight != NULL ){
					if (DEX_GetActiveSight (pSight) != NULL) { 
						DB.pSightName = pSight;
						l->StoreSightName ( pSight);
					}
				}
			}
			PROJCreator PROJCr ( *m_pPROJ );
			ContCreate ( PROJCr, PROJ ) ( m_pLocDir, &DB );
			m_iLevel = l->Level();
			DELETE_OBJ ( pSight);
		} else {
			PROJLock k(d);
			strupr( m_pPrevDir);
			if ( k->SightName() == NULL ) {
				char * pSight = new char [ _MAX_PATH];
				if ( pSight != NULL ){
					if ( DEX_GetActiveSight (pSight) != NULL) { 
						k->StoreSightName (pSight);
						l->StoreSightName ( pSight);
					}
					DELETE_OBJ ( pSight);
				}
			}
			k->StoreOwner ( l->Owner());
			k->StorePreviousProject( m_pPrevDir);
			k->Level() = l->Level();
			m_iLevel = k->Level();
		}

	} else {
	
		MessageBox ( __hWndM ,
		 m_pProjectName,
		ResString ( ResID ( IDS_TPNORELATION,&RF()),60),
//		ResString (ResID(IDT_TPCAPTION,&_RF),50),
		 MB_OK|MB_ICONEXCLAMATION);
	
		DELETE_OBJ ( m_pProjectName);
	}
	return;
}
//-----------------------------------------------------------------------
void CProjectExtension :: DefineStartParameter ( void )
{
	
	DELETE_OBJ (m_pMainProject);
	DELETE_OBJ (m_pMainUser);
	DELETE_OBJ (m_pMainSight);

	m_iLevel = 0;
	m_iHighLevel = 0;
	m_iLowLevel = 0;

	m_MenuID1 = UINT ( IDM_TPROJECT);
	m_MenuID2 = UINT ( IDM_TPROJECT);

	DELETE_OBJ (m_pPrevDir);
	DELETE_OBJ (m_pLocDir);
	DELETE_OBJ (m_pMainDir);
	DELETE_OBJ (m_pProjectName);
	DELETE_OBJ (m_pProjectKey);
	DELETE_OBJ (m_pOwnerCheck);

	m_hWnd = 0;		// FensterHandle des aktiven ORFensters
	m_hMenu = 0;		// Menu der Erweiterung
	m_lONr = 0L;		// ObjektNummer
	m_lIdent = 0L;		// Identifikator
	m_lHeadMCode = 0L;
	m_iSetCont = FALSE;	// 25.1.96

	DELETE_OBJ (m_pPROJ);
	m_pTPRJ = NULL;
	DELETE_OBJ (m_pMenu);

	m_iMenu = false;	// Kein Menu aufgebaut
	m_iMain = false;	// Kein Main vorhanden

	m_iActMenuPoint = -1;
	m_NumMenuPoints = -1;

	m_iObjCount = 0;	//25.1.95

//	Container	- 23.08.94
	m_lMainSightContainer[0] = 0L;
	m_lMainSightContainer[1] = 0L;
	m_lMainSightContainer[2] = 0L;
	m_lMainSightContainer[3] = 0L;

	m_isSearch = FALSE;
}
//------------------------------------------------------------------
void CProjectExtension :: CreateTPMenu ( HMENU hMenu )
{

	if ( m_pLocDir == NULL || m_pPROJ == NULL )
		return;
	if ( hMenu == NULL || hMenu != MenuHandle() )
		return;

	SetSightInformation();
// Achtung - TP können verschoben worden sein !!!
	m_NumMenuPoints = ReadProjectProFile();

	
	m_pTPRJ = GetTPAktuell ( m_pLocDir);


	short Flag;
	if ( m_pTPRJ && m_NumMenuPoints > 0 ) {
		m_MenuID1 = (UINT) m_NumMenuPoints + (UINT) IDM_TPROJECT;
		m_MenuID2 = m_MenuID1;

//----------------Baum her-----------------------------------------------

		CTable t(*m_pTPRJ );
		int i = 0;		// Zaehler in HauptMenue TeilProjekte
		if ( !m_pProjectName)
			m_pProjectName = new char [_MAX_PATH];
		if ( !m_pProjectName)
			return;

		for (t.First(); t.Valid() ; t.Next()  ) {
	
			TPRJLock l(t);

			if ( i == 0 ) {
				InsertMenu ( hMenu, UINT(START), MF_BYPOSITION|MF_SEPARATOR, UINT( IDM_TPROJECT )+MenuOffset(), l->Menu());
				m_iHighLevel = l->Level() - 1;
				m_iLowLevel = l->Level() + 1;
			}
		// Projekte laden
			{
			*m_pProjectName = '\0';
			strcat ( m_pProjectName, l->Drive());
			strcat ( m_pProjectName, l->Path());								
			strcat ( m_pProjectName, l->DBName());
			strcat ( m_pProjectName, l->Ext());
			strupr(m_pProjectName);

			Flag = false;
			int NumMenuPoints = 0;
			{
			ProjectProFile PF (m_pProjectName, &RF(), m_pPROJ, m_iLevel+1);

			NumMenuPoints = PF.GetProjectFile();
			}

			if ( NumMenuPoints > 0 )
				Flag = true;
        		}
	            
			if ( Flag) {		// UnterMenues
				if ( !m_pPROJ)
					return;
				CTable d( *m_pPROJ);
				if ( d.Find(m_pProjectName)) {
					HMENU _hMenu = CreateMenu();
 					if ( !_hMenu) continue;
					PROJLock k(d);
 					k->StoreTPMenu( _hMenu);
 					k->StoreOwner( l->Owner());
					if ( k->pTPRJ() ) { 
					   TPRJTree *pTP = k->pTPRJ();
					   CTable e( *pTP);
					   int j = 0;		// Zaehler UnterMenu TeilProjekt
					   for (e.First(); e.Valid() ; e.Next()  ) {
						TPRJLock m(e);
						char * pKey = m->Menu();
						if ( j == 0 ) {
							AppendMenu ( _hMenu,MF_STRING,UINT(IDM_TPROJECT+i )+MenuOffset(), ResString(ResID(IDS_TPOPENPOPUP,&RF()),30) );
							AppendMenu ( _hMenu,MF_SEPARATOR,UINT(IDM_TPROJECT+i )+MenuOffset(), ResString(ResID(IDS_TPOPENPOPUP,&RF()),30) );
						}
						j++;
						AppendMenu ( _hMenu,MF_STRING,UINT(m_MenuID2+j )+MenuOffset(),pKey);
						m->StoreMenuID ( m_MenuID2 + j);
					   }
					   m_MenuID2 = m_MenuID2 + j;					   
					   k->StoreMenuID ( m_MenuID2 );
					   l->StoreMenuID ( m_MenuID2 );
					   InsertMenu ( hMenu, UINT(i+1+START), MF_POPUP|MF_BYPOSITION, (UINT) _hMenu, l->Menu());
					}
				}
			} else
				InsertMenu ( hMenu, UINT(i+1+START), MF_BYPOSITION, UINT( IDM_TPROJECT+i )+MenuOffset(), l->Menu());
	
			pExtMenu()->EnableItem ( UINT ( IDM_TPROJECT +i ) + MenuOffset());
			i++;
			
		}
	}
	return ;
}
//----------------------------------------------------------------------------
void CProjectExtension :: CreateTPPartMenu ( HMENU hMenu )
{

	if ( m_pLocDir == NULL || m_pPROJ == NULL )
		return;

	if ( hMenu == NULL || hMenu != MenuHandle() )
		return;

//---12.4.95------
	if ( !m_pPROJ)
		return;

	CTable d( *m_pPROJ);
	if ( !d.Find( m_pLocDir))
		return;
	m_iActMenuPoint = -1;
	PROJLock k(d);
	m_pTPRJ = k->pTPRJ();
	if ( !m_pTPRJ) {
		m_NumMenuPoints = 0;
		return;
	}
//------------------------------------------------
	ulong Count = m_pTPRJ->Count();
	m_NumMenuPoints = (int) Count;
	m_MenuID1 = (UINT) m_NumMenuPoints + (UINT) IDM_TPROJECT;
	m_MenuID2 = m_MenuID1;


//----------------Baum her-----------------------------------------------

	CTable t(*m_pTPRJ );
	int i = 0;		// Zaehler in HauptMenue TeilProjekte
	char *pProjectName = new char [_MAX_PATH];
	if ( !pProjectName)
		return;

	for (t.First(); t.Valid() ; t.Next()  ) {
	
		TPRJLock l(t);

		if ( i == 0 ) {
			InsertMenu ( hMenu, UINT(START), MF_BYPOSITION|MF_SEPARATOR, UINT( IDM_TPROJECT )+MenuOffset(), l->Menu());
			m_iHighLevel = l->Level() - 1;
			m_iLowLevel = l->Level() + 1;
		}
	// Projekte laden
		*pProjectName = '\0';
		strcat ( pProjectName, l->Drive());
		strcat ( pProjectName, l->Path());								
		strcat ( pProjectName, l->DBName());
		strcat ( pProjectName, l->Ext());
		strupr(pProjectName);

		if ( !d.Find(pProjectName)) {
			DBPROJECT DB;
			SetZero ( &DB);
			DB.pDBName = l->DBName();
			DB.pDrive = l->Drive();
			DB.pUserName = l->UserName();
			DB.pPath = l->Path();
			DB.pExt = l->Ext();
			DB.pOwner = l->Owner();
			DB.iLevel = l->Level();
			DB.pSightName = l->SightName();
			PROJCreator PROJCr ( *m_pPROJ );
			ContCreate ( PROJCr, PROJ ) ( pProjectName, &DB );
		}

		if ( d.Find(pProjectName)) {
		   PROJLock k(d);
		   short iLevel = k->Level();		
		   if ( k->pTPRJ() != NULL ) {

			HMENU _hMenu = CreateMenu();
			if ( !_hMenu) continue;
			k->StoreTPMenu( _hMenu);
			TPRJTree *pTP = k->pTPRJ();
			CTable e( *pTP);
			int j = 0;		// Zaehler UnterMenu TeilProjekt
			for (e.First(); e.Valid() ; e.Next()  ) {
				TPRJLock m(e);
				char * pKey = m->Menu();
				if ( j == 0 ) {
//					AppendMenu ( _hMenu,MF_STRING,UINT(IDM_TPROJECT+i )+MenuOffset()," .. ");
					AppendMenu ( _hMenu,MF_STRING,UINT(IDM_TPROJECT+i )+MenuOffset(), ResString(ResID(IDS_TPOPENPOPUP,&RF()),30) );
					AppendMenu ( _hMenu,MF_SEPARATOR,UINT(IDM_TPROJECT+i )+MenuOffset(), ResString(ResID(IDS_TPOPENPOPUP,&RF()),30) );
				}
				j++;
				AppendMenu ( _hMenu,MF_STRING,UINT(m_MenuID2+j )+MenuOffset(),pKey);
				m->StoreMenuID ( m_MenuID2 + j);
			}
			m_MenuID2 = m_MenuID2 + j;					   
			k->StoreMenuID ( m_MenuID2 );
			l->StoreMenuID ( m_MenuID2 );
			InsertMenu ( hMenu, UINT(i+1+START), MF_POPUP|MF_BYPOSITION, (UINT) _hMenu, l->Menu());

		    } else {

			int NumMenuPoints = 0;

			{
			ProjectProFile PF (pProjectName, &RF(), m_pPROJ, iLevel );

			NumMenuPoints = PF.GetProjectFile();
			}

			if ( NumMenuPoints > 0 ) {

				HMENU _hMenu = CreateMenu();
				if ( !_hMenu) continue;
				k->StoreTPMenu( _hMenu);
				TPRJTree *pTP = k->pTPRJ();
				if ( !pTP ) 
					return;
				CTable e( *pTP);
				int j = 0;		// Zaehler UnterMenu TeilProjekt
				for (e.First(); e.Valid() ; e.Next()  ) {
					TPRJLock m(e);
					char * pKey = m->Menu();
					if ( j == 0 ) {
//						AppendMenu ( _hMenu,MF_STRING,UINT(IDM_TPROJECT+i )+MenuOffset()," .. ");
						AppendMenu ( _hMenu,MF_STRING,UINT(IDM_TPROJECT+i )+MenuOffset(), ResString(ResID(IDS_TPOPENPOPUP,&RF()),30) );
						AppendMenu ( _hMenu,MF_SEPARATOR,UINT(IDM_TPROJECT+i )+MenuOffset(), ResString(ResID(IDS_TPOPENPOPUP,&RF()),30) );
					}
					j++;
					AppendMenu ( _hMenu,MF_STRING,UINT(m_MenuID2+j )+MenuOffset(),pKey);
					m->StoreMenuID ( m_MenuID2 + j);
				}
				m_MenuID2 = m_MenuID2 + j;					   
				k->StoreMenuID ( m_MenuID2 );
				l->StoreMenuID ( m_MenuID2 );
				InsertMenu ( hMenu, UINT(i+1+START), MF_POPUP|MF_BYPOSITION, (UINT) _hMenu, l->Menu());

			} else
				InsertMenu ( hMenu, UINT(i+1+START), MF_BYPOSITION, UINT( IDM_TPROJECT+i )+MenuOffset(), l->Menu());

		    }
		}
	
		pExtMenu()->EnableItem ( UINT ( IDM_TPROJECT +i ) + MenuOffset());
		i++;
			
	}
//-----------------------------------------------------------------------
	DELETE_OBJ ( pProjectName);
	m_NumMenuPoints = i;
	return ;
}

//-----------------------12.4.95
void CProjectExtension :: DeleteTPMenu ( HMENU hMenu )
{
	if ( !m_pTPRJ )
		return;

	ulong Count = m_pTPRJ->Count();
	if ( Count <= 0 )
		return;

	char *pProjectName = new char [_MAX_PATH];

	if ( !pProjectName)
		return;

	DeleteMenu ( hMenu, UINT(START), MF_BYPOSITION|MF_SEPARATOR);
	if ( !m_pTPRJ || !m_pPROJ)
		return;
	CTable t(*m_pTPRJ);
	CTable d (*m_pPROJ);

	for (t.First(); t.Valid() ; t.Next()  ) {	// TP 1.Ordnung
		TPRJLock l(t);
		*pProjectName = '\0';
		strcat ( pProjectName, l->Drive());
		strcat ( pProjectName, l->Path());								
		strcat ( pProjectName, l->DBName());
		strcat ( pProjectName, l->Ext());
		strupr(pProjectName);

		if ( d.Find(pProjectName)) {
			PROJLock k(d);
			HMENU MyMenu = k->hMenu();
			if (MyMenu )
				DestroyMenu ( MyMenu);
			k->StoreTPMenu(0);
			l->StoreMenuID(0);
			k->StoreMenuID (0);
    			DeleteMenu ( hMenu, UINT(START), MF_BYPOSITION);
		}
	}
	DELETE_OBJ ( pProjectName);
}
//------------------------12.4.95

void CProjectExtension :: ModifyMenu ( HMENU hMenu )
{

	if ( !m_pLocDir || !m_pPROJ || !m_pTPRJ ) 
		return;

	if ( !m_pProjectName)
		m_pProjectName = new char [_MAX_PATH];

	if ( !m_pProjectName)
		return;

	CTable t(*m_pTPRJ);
	ulong UCount = m_pTPRJ->Count();
	m_NumMenuPoints = (int) UCount;
	if ( m_NumMenuPoints <= 0 )
		return;

	DeleteMenu ( hMenu, UINT(START), MF_BYPOSITION|MF_SEPARATOR);
	CTable d(*m_pPROJ);

	for (t.First(); t.Valid() ; t.Next()  ) {	// TP 1.Ordnung
		TPRJLock l(t);
		*m_pProjectName = '\0';
		strcat ( m_pProjectName, l->Drive());
		strcat ( m_pProjectName, l->Path());								
		strcat ( m_pProjectName, l->DBName());
		strcat ( m_pProjectName, l->Ext());
		strupr(m_pProjectName);

		if ( d.Find(m_pProjectName)) {
			PROJLock k(d);
			HMENU MyMenu = k->hMenu();
			if (MyMenu )
				DestroyMenu ( MyMenu);
			k->StoreTPMenu(0);
			l->StoreMenuID(0);
			k->StoreMenuID (0);
    			DeleteMenu ( hMenu, UINT(START), MF_BYPOSITION);
		}
	}

	return ;
}
//----------------------------------------------------------------------------
//---------------------------------------------------------
void CProjectExtension :: ModifyProjectProFile ( void )
{
	//	INI 
	if ( !m_pLocDir || !m_pPROJ || !m_pMenu) 
		return;

	char * pIni = new char [_MAX_PATH];
	if ( !pIni )
		return;
	strcpy ( pIni,m_pLocDir);
	char *ptr = strrchr( pIni , '.');
	if ( !ptr ) {
		DELETE_OBJ ( pIni);
		return;
	}
	*ptr = '\0';
	strcat ( pIni, ResString(ResID(IDS_PROFILEEXT,&RF()),5));

	CTable m( *m_pMenu);
	CTable t( *m_pPROJ);

	for ( m.First(); m.Valid(); m.Next()) {
		MMenuLock u(m);
		if ( u->ModKZ()) {
			StoreProjectProFile ( u->ModKZ(),pIni,u->Menu(),u->DBName(),u->Referenz());
		}
	}

	DELETE_OBJ ( pIni);
	if ( t.Find( m_pLocDir) ) {
		PROJLock l(t);
		m_iLevel = l->Level();
		{
		ProjectProFile PF (m_pLocDir, &RF(), m_pPROJ, m_iLevel);
		m_NumMenuPoints = PF.GetProjectFile();
		m_pTPRJ = PF.pTPRJ();
		}

	}
		
	return;
}
//--------------------------------------------------------------------
void CProjectExtension :: StoreProjectProFile ( short iFctn, char *pIni, char *pKey, char *pProject , char * pLastKey)
{
	if ( !m_pPROJ)
		return;

	char *pOem = new char [_MAX_PATH];
	if ( !pOem)
		return;

	ResString Projects (ResID (IDS_PROJECTS,&RF()), 13);

	if ( iFctn == (short)MF_AddKey ) {		// Neu anlegen !
//		AnsiToOem ( pKey, pOem );
		strcpy(pOem,pKey);
// KK 010515
//		int ii = WritePrivateProfileString (Projects, pOem, pProject, pIni);
		int ii = WriteIniFile (Projects, pOem, pProject, pIni);
	} else {
		if ( iFctn == (short) MF_ModKey ) {
//			AnsiToOem ( pKey, pOem );
			strcpy(pOem,pKey);
//			int ii = WritePrivateProfileString (Projects, pOem, NULL, pIni);
			int ii = WriteIniFile (Projects, pOem, NULL, pIni);
//			AnsiToOem ( pKey, pOem );
//			WritePrivateProfileString (Projects, pOem, pProject, pIni);
		}
		if ( iFctn == (short) MF_ModProject ) {
			if ( pLastKey ) {
				strupr ( pLastKey);	// altes Projekt
				CTable t(*m_pPROJ);
				if ( t.Find(pLastKey))
					t.Delete();
			}
//			AnsiToOem ( pKey, pOem );
			strcpy(pOem,pKey);
//			int ii = WritePrivateProfileString (Projects, pOem, NULL, pIni);
			int ii = WriteIniFile (Projects, pOem, NULL, pIni);
//			ii = WritePrivateProfileString (Projects, pOem, pProject, pIni);
			ii = WriteIniFile(Projects, pOem, pProject, pIni);
		}
		if ( iFctn == (short) MF_DeleteKey ) {
			char *pProj = new char [_MAX_PATH];
			strcpy(pOem,pKey);
//			AnsiToOem ( pKey, pOem );
			if ( pProj ) {
				GetPrivateProfileString (Projects, pOem, "",pProj, _MAX_PATH, pIni);
			}

//			int ii = WritePrivateProfileString (Projects, pOem, NULL, pIni);
			// KK 010514
			int ii = WriteIniFile (Projects, pOem, NULL, pIni);

			if ( !pProj) {
				DELETE_OBJ ( pOem);
				return;
			}
			strupr ( pProj);
			CTable t(*m_pPROJ);
			if ( t.Find(pProj))
				t.Delete();
		}
	}
	DELETE_OBJ ( pOem);
	return;
}

//----------------------------------------------------------------------------
// Umschalten des Projektes ---------------------------------------------------
BOOL CProjectExtension :: SwitchToProject (char *pProj, char *pUser, char *pSight)
{
	if (!m_pPROJ)
		return false;

	if ( !pProj || *pProj == '\0' )
		return FALSE;
	if ( !m_pLocDir)
		return FALSE;
	char *pOwnerCheck = new char [_MAX_PATH];
	if ( !pOwnerCheck )
		return FALSE;

	strcpy ( pOwnerCheck, m_pLocDir);
	strupr ( pOwnerCheck);

	m_isSwitchTP = true;	// TP-Aufruf

//	if ( m_iSetCont)
//		DEX_GetActiveSightContainer( m_lMainSightContainer );

	OFSTRUCT of;
	if (OpenFile (pProj, &of, OF_EXIST|OF_READ) < 0) {
		DELETE_OBJ (pOwnerCheck);
		return FALSE;
	}

Bool toDeleteUser = FALSE;

	if (!pUser || *pUser == '\0') {		// kein Nutzername gegeben
	// Nutzernamen (Standard) generieren
		DELETE_OBJ ( pUser);
		pUser = new char [_MAX_PATH];
		if ( !pUser ) {
			DELETE_OBJ (pOwnerCheck);
			return FALSE;
		}

		_splitpath (pProj, NULL, NULL, pUser, NULL);
		toDeleteUser = TRUE;
	}

	if (!pSight || *pSight == '\0') 
		DELETE_OBJ ( pSight);


// KK010522
// Vorher Projekt schließen

/*
	if (_pIniTemp && *_pIniTemp != '\0' && !m_bTPUndef) {

		int flag = MessageBox (__hWndM,
			ResString ( ResID ( IDS_ERRININOWRITABLE,&g_pTE->RF()),260),
			ResString (ResID(IDT_TPCAPTION,&g_pTE->RF()),50),
//			MB_YESNO|MB_ICONEXCLAMATION);
			MB_YESNO|MB_ICONQUESTION);

		if ( flag == IDNO ) 
			return false;
	}
*/

	m_bTPUndef= false;	// Fehlermeldung zu undef. TP wieder zulassen

	DEX_CloseProject(0);
	DEX_KickIdle();

	// TempIni loeschen

	DeleteFile(_pIniTemp);

	DELETE_OBJ(_pIniOriginal);
	DELETE_OBJ (_pIniTemp);
//---------------------------------------------------------

// Projekt öffnen
TRIAS_OPEN TO;

	TO.dwSize = sizeof (TRIAS_OPEN);
	TO.lpProject = strupr (pProj);
	TO.lpUser = strlwr(pUser);
	TO.lpPassWord = NULL;
	TO.iMode = pSight ? OM_NoStandard | OM_Normal : OM_Normal;
// KK010112
//	if (DEX_OpenProject (TO)) {

	if (!DEX_OpenProject (TO)) {
		if (toDeleteUser) DELETE_OBJ (pUser);
		DELETE_OBJ (pOwnerCheck);
		return FALSE;
	}

	if (toDeleteUser) 
		DELETE_OBJ (pUser);


// Sicht einstellen, wenn gegeben
	if (pSight) DEX_SelectNewSight (pSight);

	m_isSwitchTP = false;	
//	Altes Menu raus
	CTable t ( *m_pPROJ);
	if ( t.Find(pOwnerCheck))  {
		PROJLock l(t);
		m_pTPRJ = l->pTPRJ();
		DeleteTPMenu ( m_hMenu);
	}
	if ( !t.Find(pProj)) 
		strupr( pProj);

	if ( t.Find(pProj)) { 
		PROJLock l(t);
		m_pTPRJ = l->pTPRJ();
		l->StorePreviousProject( pOwnerCheck);
		if ( !pSight ) {
			if ( l->SightName() == NULL ) {
				char * pNewSight = new char [ _MAX_PATH];
				if ( pNewSight != NULL ){
					if ( DEX_GetActiveSight (pNewSight) != NULL) 
						l->StoreSightName ( pNewSight);
					DELETE_OBJ ( pNewSight);
				}
			}
		}
		CreateTPPartMenu ( m_hMenu);
	} else {
		{
			ProjectProFile PF (pProj, &RF(), m_pPROJ, m_iLevel);
			m_NumMenuPoints = PF.GetProjectFile();
		}
		CreateTPPartMenu ( m_hMenu);
	}

	DELETE_OBJ (pOwnerCheck);
// Und nun Container prüfen
	if ( m_iSetCont )  {
//		long lMSCont[4];		// MainSichtContainer

/*
		DEX_GetActiveSightContainer( lMSCont );
		if ( m_lMainSightContainer[0] >= lMSCont[0] &&
		     m_lMainSightContainer[1] <= lMSCont[1] &&
		     m_lMainSightContainer[2] >= lMSCont[2] &&
		     m_lMainSightContainer[3] <= lMSCont[3]  )
*/

				DEX_SetActiveSightContainer( m_lMainSightContainer);

	}

	DEX_RePaint();

return TRUE;

}

// Merken/Speichern des Projektes ---------------------------------------------------
void CProjectExtension :: StoreMainProject ( void )
{
	if ( m_pMainProject == NULL ) 
		m_pMainProject = new char [_MAX_PATH];
	if ( m_pMainProject != NULL ) {
		if (DEX_GetActiveProject (m_pMainProject) == NULL) {
		// noch kein Projekt eröffnet
			DELETE_OBJ (m_pMainProject);
			return;
		} else {
			strupr( m_pMainProject);
			if ( m_pMainUser == NULL ) 
				m_pMainUser = new char [_MAX_PATH];
			if ( m_pMainUser != NULL ) {
				if (DEX_GetActiveUser (m_pMainUser) == NULL)  {
					DELETE_OBJ (m_pMainUser);
				} else {
					strupr ( m_pMainUser);
				}
			}
			if ( m_pMainSight == NULL ) 
				m_pMainSight = new char [_MAX_PATH];
			if ( m_pMainSight != NULL ) {
				if (DEX_GetActiveSight (m_pMainSight) == NULL) 
					DELETE_OBJ (m_pMainSight);
			}
			
		}
	}
	return;
}

// Vorheriges Projektes ---------------------------------------------------
void CProjectExtension :: GoToPreviousProject ( bool Flag )
{
	if ( !m_pLocDir || !m_pPROJ )
		return;

//	Flag =  TRUE -> Previous;
//		FALSE -> Hierarchie

	char *pProjectName = new char [_MAX_PATH];
	if ( pProjectName == NULL )
		return ;
	*pProjectName = '\0';        

	CTable t ( *m_pPROJ);
	if ( t.Find ( m_pLocDir )) {
		PROJLock l(t);
		if ( Flag ) {
			if ( l->Prev())
				strcpy(pProjectName,l->Prev());
		} else {
			if ( l->Owner())
				strcpy(pProjectName,l->Owner());
		}

		if ( *pProjectName == '\0' ) {
			DELETE_OBJ ( pProjectName);
			return;
		}
	} 
	
	if ( !t.Find ( pProjectName ))
		strupr ( pProjectName);

	if ( !t.Find ( pProjectName )) {
		DELETE_OBJ ( pProjectName);
		return;                     
	}

	PROJLock l(t);	
	m_iLevel = l->Level();						
	bool flag = SwitchToProject ( pProjectName, l->UserName(),l->SightName());
	if (!flag) {
		DELETE_OBJ ( pProjectName);
		return;               
	}

	if ( t.Find ( pProjectName )) {

		PROJLock l(t);

		if ( !l->Owner()) 
			pExtMenu()->DisableItem ( UINT( IDM_OPENPREVIOUSLEVEL ) + MenuOffset() );
		else
			pExtMenu()->EnableItem ( UINT( IDM_OPENPREVIOUSLEVEL ) + MenuOffset() );

		if ( !l->Prev())
			pExtMenu()->DisableItem ( UINT( IDM_OPENPREVIOUSPROJECT ) + MenuOffset() );
		else
			pExtMenu()->EnableItem ( UINT( IDM_OPENPREVIOUSPROJECT ) + MenuOffset() );

		m_iLevel = l->Level();

	}
	DELETE_OBJ ( pProjectName);

	return;
}
//------------------------------------------------------------------------

// Sprung zum 1.Level ---------------------------------------------------
void CProjectExtension :: FindFirstLevel ( void )
{

	if ( !m_pTPRJ )
		return;

	CTable t(*m_pTPRJ );	// HauptMenu - TeilProjekte
	int i = 0;

	for (t.First(); t.Valid() ; t.Next()  ) {
	
		TPRJLock l(t);
		i++;
		if ( i > m_iActMenuPoint ) {
			DELETE_OBJ ( m_pProjectName);
			return ;
		}
				
		if ( i == m_iActMenuPoint ) {
			strcat ( m_pProjectName, l->Drive());
			strcat ( m_pProjectName, l->Path());								
			strcat ( m_pProjectName, l->DBName());
			strcat ( m_pProjectName, l->Ext());
			strupr(m_pProjectName);
			strcpy ( m_pProjectKey , l->Menu());
			return;
		}

	}

}

// Sprung zum 2.Level ---------------------------------------------------
void CProjectExtension :: FindSecondLevel ( UINT MenuItemID )
{
	if ( !m_pTPRJ)
		return;

	CTable t(*m_pTPRJ );	// HauptMenu - TeilProjekte

	for (t.First(); t.Valid() ; t.Next()  ) {
		TPRJLock l(t);
		if ( l->MenuID() > 0 ) {
		  if ( l->MenuID() >=  MenuItemID) {
			strcat ( m_pProjectName, l->Drive());
			strcat ( m_pProjectName, l->Path());								
			strcat ( m_pProjectName, l->DBName());
			strcat ( m_pProjectName, l->Ext());
			strupr(m_pProjectName);
	
			CTable d(*m_pPROJ);
			if ( d.Find( m_pProjectName )) {
				PROJLock k(d);
				TPRJTree *pTPRJ = k->pTPRJ();
				CTable e( *pTPRJ);
				for (e.First(); e.Valid() ; e.Next()  ) {
					TPRJLock f(e);
					if ( f->MenuID() > (UINT) MenuItemID ) {
						DELETE_OBJ ( m_pProjectName);
						return ;
					}
					if ( f->MenuID() == (UINT) MenuItemID ) {
						*m_pProjectName = '\0';
						strcat ( m_pProjectName, f->Drive());
						strcat ( m_pProjectName, f->Path());								
						strcat ( m_pProjectName, f->DBName());
						strcat ( m_pProjectName, f->Ext());
						strupr(m_pProjectName);
						strcpy ( m_pProjectKey , f->Menu());
						m_pTPRJ = k->pTPRJ();
						m_iActMenuPoint = f->MenuID()-m_MenuID1;
						return;
					}
				}
			}
		   }
		}
	}

}
//------------------------------------------------------------------
// MCode für TeilProjekte besorgen
//-------------------------------------------------------------------
void CProjectExtension :: GetHeaderMCode (void)
{

	m_lHeadMCode = 0L;

	GEODBHDRENTRY hdrEntry;
	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDT_HEADTPMCODEIDENT,&RF()),17),16);
	hdrEntry.lphdrText = new char [MCODESIZE +1];
	hdrEntry.hdrTextLen = MCODESIZE;

	if ( 0 != m_hPr) {
		if (DEX_ReadGeoDBHdrEntryEx (m_hPr,hdrEntry) == EC_OKAY) {
		// HeaderEintrag existiert
			ULONG lHeadMCode = 0L;
			lHeadMCode = strtoul ( hdrEntry.lphdrText, NULL, 16 );
			if ( 0L != lHeadMCode)
				m_lHeadMCode = DEX_MapMCodeToHandle(m_hPr,lHeadMCode);

		// KK010115
			CMCodeMap::iterator it = g_MCodes.find(m_hPr);

			if (it == g_MCodes.end())
				g_MCodes.insert(CMCodeMap::value_type(m_hPr, os_string(hdrEntry.lphdrText)));

		} else  {
			m_lHeadMCode = 0L;

		}
	}

	DELETE_OBJ (hdrEntry.lphdrText);

}
//------------------------------------------------------------------
void CProjectExtension :: GetHeaderMCodeEx (void)
{
	long lIdent = 0L;
//	Alle O'Klassen der Sicht formal durchzählen und Baum anlegen
		ENUMTEXTKEY ENT;
		ENT.eKey = NULL;	// NULL = aktuelle Sicht
//	Bestimmen der Anzahl der Objektklassen
		ENT.eFcn = ( ENUMTEXTKEYPROC) SucheSichtDQ;
		ENT.ePtr = (void *) &lIdent;
		DEX_EnumSightIdents(ENT);

		m_hPr = DEX_GetObjectsProject(lIdent);	// aktuelle Datenquelle

		GetHeaderMCode();
}
//------------------------------------------------------------------
//------------------------------------------------------------------
// MCode für TeilProjekte setzen
//-------------------------------------------------------------------
void CProjectExtension :: SetHeaderMCode ( HPROJECT hPr,char *pMCode)
{
GEODBHDRENTRY hdrEntry;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (ResID(IDT_HEADTPMCODEIDENT,&RF()),17),16);
	hdrEntry.lphdrText = new char [MCODESIZE +1];
	hdrEntry.hdrTextLen = MCODESIZE;
	strncpy( hdrEntry.lphdrText, pMCode,10);
	DEX_WriteGeoDBHdrEntryEx (hPr,hdrEntry);

	// KK010115
	CMCodeMap::iterator it = g_MCodes.find(hPr);

	if (it == g_MCodes.end())
		g_MCodes.insert(CMCodeMap::value_type(m_hPr, os_string(hdrEntry.lphdrText)));

}
//------------------------------------------------------------------
// MCode für TeilProjekte in PBD setzen
//-------------------------------------------------------------------
void CProjectExtension :: SetPBDMCode ( long lONr,long MCode)
{

	HPROJECT hPr = DEX_GetObjectProject(lONr);	// aktuelle Datenquelle

	PBDMERKMALEX pbdData;
	char KText[MCODESIZE+1];

	memset (&pbdData, '\0', sizeof(PBDMERKMALEX));
	
	pbdData.dwSize = sizeof(PBDMERKMALEX);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = MCode;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	strncpy ( KText,  ResString (ResID(IDT_HEADTPMCODETEXT,&RF()),40) , sizeof(KText)-1);
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.ipbdMTyp = MPObjectFeature | PBDMERKMAL_SYSTEMFLAG | PBDMERKMAL_READONLY;	// so tun, als ob's nur für Objekte wär
//	pbdData.ipbdMTyp = 'a' | PBDMERKMAL_SYSTEMFLAG;	// so tun, als ob's nur für Objekte wär
	pbdData.ipbdMLen = 256;
	pbdData.lIdent = DEX_GetObjIdent(lONr);


	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDDataEx (hPr,pbdData) != EC_OKAY)
			return;
		else
			DEXN_PBDMCodeChanged (MCode);
	}

}
//------------------------------------------------------------------------

//	ORFenster erstellen-----------------------------------------
void CProjectExtension :: CreateORWindow ( short Flag, short PX, short PY, long *pObjL, char *pCaption, short RF, short GF, short BF)
{
	if ( *pObjL <= 0 )
		return;
	m_isSearch = TRUE;
	POINT PNT;
	PNT.x = PX;
	PNT.y = PY;


	CREATEOBJEKTINFOEX COI;
	memset ( &COI, '\0', sizeof (COI) );
	COI.dwSize = sizeof(COI);
	COI.lpCaption = pCaption;
	COI.plObjs = pObjL+1;
	COI.iNumObjs = short( *pObjL);
	COI.cMColor = RGB(RF,GF,BF);
	COI.pntPos = PNT;
	COI.m_iFlags = Flag;
	RegisterNotification (DEX_CREATEOBJEKTINFO);
	RegisterNotification (DEX_QUERYRECHOBJECT);
	DEX_CreateObjektInfo( COI );
	UnRegisterNotification (DEX_CREATEOBJEKTINFO);
	UnRegisterNotification (DEX_QUERYRECHOBJECT);
	m_isSearch = FALSE;

}
//------------------------------------------------------------------------
long CProjectExtension :: NumberTProjects ( void )
{

	long NrObj = 0L;

	CMCodeMap::iterator it;
	char cbBuffer[_MAX_PATH];

	for ( it = g_MCodes.begin(); it != g_MCodes.end(); ++it) {
		m_hPr = (*it).first;

		wsprintf (cbBuffer, "%s", (*it).second.c_str());

		ULONG lHeadMCode = 0L;
		lHeadMCode = strtoul ( cbBuffer, NULL, 16 );
		if ( 0L != lHeadMCode)
			m_lHeadMCode = DEX_MapMCodeToHandle(m_hPr,lHeadMCode);

		ENUMRECHTEXTMERKMAL EM;
		memset (&EM, '\0', sizeof(ENUMRECHTEXTMERKMAL));
		EM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
	//	EM.pView = NULL;
		EM.lMCode = m_lHeadMCode;
	//	EM.iMode = SMExactMatch;
		EM.iMode = SMExistanceOnly;
		EM.eFcn = (RECHTEXTMERKMALCALLBACK) EnumTPMCode;
		EM.pData = &NrObj;
		DEX_EnumRechTextMerkmal(EM);

	}

	return NrObj;
}
//-----------------------NICHTMEMBER---------------------------------------

//------------------------------------------------------------------------
void  SetZero ( struct DBPROJECT *p )
{
	if ( p == NULL ) return;
	p->pKey = NULL;
	p->pDBName = NULL;
	p->pUserName = NULL;
	p->pSightName = NULL;
	p->pDrive = NULL;
	p->pPath = NULL;
	p->pExt = NULL;
	p->pOwner = NULL;
	p->pPrev = NULL;
	p->pNext = NULL;
	p->iStatus = 0;
	p->iLevel = 0;
	p->iPrevMenuPoint = 0;
	p->lXmin=0L;
	p->lXmax=0L;
	p->lYmin=0L;
	p->lYmax=0L;
	p->pTPRJ = NULL;
}

//------------------------------------------------------------------------
void  SetModZero ( struct MODMENU *p )
{
	if ( p == NULL ) return;
	p->pKey = NULL;
	p->pDBName = NULL;
	p->pReferenz = NULL;
	p->iMenuNr = 0;
	p->iStatus = 0;
	p->iModKZ = 0;
}
//-------------------------------------------------------------
char *StrDuplicat ( char *cptr ) 
{
char *newPtr = NULL;

	if (cptr != NULL) {
		newPtr = new char [strlen(cptr)+1];
		if (newPtr != NULL) 
			strcpy (newPtr, cptr);

	}

return newPtr;
}
//---------------------------------------------------------------------------
void MyStrupr ( char *cptr , short iLevel) 
{
	if ( !cptr)
		return;

	char * pLevel = new char[10];
	if ( !pLevel )
		return;

	if (cptr != NULL) {
		wsprintf ( pLevel,"%d",iLevel);
		strcat ( cptr, pLevel);
		strupr ( cptr);
	}

	return;
}
//---------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// KK 010608
Bool FileExist ( const char *pProject)
{
	if (!pProject || *pProject == '\0')
		return false;

	struct _stat ST;
	if( _stat ( pProject, &ST) != 0 )
		return false;
	return true;
}
////////////////////////////////////////////////////////////////////////////////
// KK 010514
Bool WriteIniFile ( ResString Projects, char *pOem, char *pProject, char *pIni )
{
	if ( !pOem || !pIni )
		return false;
	if (!Projects)
		return false;

	char * pTempIni = ((CProjectExtension *)g_pTE)->GetTempIni();
	if (!pTempIni || *pTempIni == '\0')
		((CProjectExtension *)g_pTE)->SetTempIniFile(pIni);


	WriteIniFileEx ( Projects, pOem, pProject, ((CProjectExtension *)g_pTE)->GetTempIni() );
//	WriteIniFileEx ( Projects, pOem, pProject, pIni );

	return true;
}

////////////////////////////////////////////////////////////////////////////////
// KK 010514
Bool WriteIniFileEx ( ResString Projects, char *pOem, char *pProject, char *pIni )
{
	if ( !pOem || !pIni )
		return false;
	if (!Projects)
		return false;

// Hier kommt die TempIni
	if ( WritePrivateProfileString (Projects, pOem, pProject, pIni))
		return true;


// INI ist wohl schreibgeschützt ?!

	MessageBox ( __hWndM ,
		ResString ( ResID ( IDS_ININOWRITABLE,&g_pTE->RF()),260),
		ResString (ResID(IDT_TPCAPTION,&g_pTE->RF()),50),
		 MB_OK|MB_ICONEXCLAMATION);
//	return false;


	DWORD dAttr = GetFileAttributes((LPCTSTR) pIni);
	// FILE_ATTRIBUT_READONLY
	// FILE_ATTRIBUT_NORMAL

	if ( (dAttr & FILE_ATTRIBUTE_READONLY) != 0 )
		dAttr = dAttr & ~FILE_ATTRIBUTE_READONLY;

	SetFileAttributes((LPCTSTR) pIni,dAttr);

	OFSTRUCT *pInsertStruct = NULL;				// Insert-Datei
	pInsertStruct = new OFSTRUCT;

	HFILE fh = OpenFile (pIni, pInsertStruct, OF_READWRITE);
	if ( fh == HFILE_ERROR) 
		return false;

	_lclose(fh);

	return WritePrivateProfileString (Projects, pOem, pProject, pIni);

}
/////////////////////////////////////////////////////////////////////////////////
Bool WritePrivateIniFile (void) 
{

	if (!((CProjectExtension *)g_pTE)->isTempINI()) 		// Keine Temp-INI-normal weiterarbeitem
		return true;

	ResString Projects (ResID (IDS_PROJECTS,&g_pTE->RF()), 13);

	ResString DefaultProject (ResID (IDS_DEFAULTPROJECT,&g_pTE->RF()), 13);

	ResString DefaultProjects (ResID (IDS_DEFAULTPROJECTS,&g_pTE->RF()), 13);

// aktuelles Projektverzeichnis besorgen
	char *pLocDir = new char [_MAX_PATH];

	if ( pLocDir ) {
		if (DEX_GetActiveProject (pLocDir) == NULL) {
			DELETE_OBJ(pLocDir);
			return false;
		}
	}

	char * pIni = new char [_MAX_PATH];
	if ( !pIni ) {
		DELETE_OBJ(pLocDir);
		return false;
	}

	strcpy ( pIni,pLocDir);

	char *ptr = strrchr( pIni , '.');

	if ( !ptr ) {
		DELETE_OBJ(pLocDir);
		DELETE_OBJ ( pIni);
		return false;
	}

	*ptr = '\0';
	strcat ( pIni, ResString(ResID(IDS_PROFILEEXT,&g_pTE->RF()),5));

//	DELETE_OBJ(pLocDir);

	char *pTempIni = ((CProjectExtension *)g_pTE)->GetTempIni();
	if ( pTempIni && *pTempIni != '\0') {

	// Richtige TempIni ???
		if ( !IniEqualToTemp(pTempIni, pIni) ){
			DELETE_OBJ(pIni);
			return true;
		}

	// Ist datei auch da ???
		struct _stat ST;
		if ( _stat ( pTempIni, &ST) != 0 ) {
			DELETE_OBJ(pLocDir);
			MessageBox ( __hWndM ,
//			ResString ( ResID ( IDS_NOMOVINGINI,&g_pTE->RF()),260),
			"Einträge zur Teilprojektverkettung in die Projekt-INI fehlgeschlagen! ",
			ResString (ResID(IDT_TPCAPTION,&g_pTE->RF()),50),
			MB_OK|MB_ICONEXCLAMATION);
			return true;
		}


	// Ini aus Temp kopieren !!!

		short MaxString = MaxExtension*MaxKey;
		char *pString = new char [MaxString];

		if (pString) {

			if ( !WritePrivateProfileSection (Projects,NULL,pIni)) {
		// INI ist wohl schreibgeschützt ?!

				MessageBox ( __hWndM ,
				ResString ( ResID ( IDS_ININOWRITABLE,&g_pTE->RF()),260),
				ResString (ResID(IDT_TPCAPTION,&g_pTE->RF()),50),
				MB_OK|MB_ICONEXCLAMATION);

				DELETE_OBJ(pString);

				DELETE_OBJ(pLocDir);

				return false;
			}

			WritePrivateProfileSection (DefaultProjects,NULL,pIni);

			GetPrivateProfileSection (Projects,pString,MaxString,pTempIni);

			if (pString && *pString != '\0') {

				WritePrivateProfileSection (Projects,pString,pIni);

	// KK 010529
	// Default - Pfad vom Main Project abspeichern
				WritePrivateProfileString (DefaultProjects,DefaultProject,pLocDir,pIni);
			}

			DELETE_OBJ(pLocDir);
			DELETE_OBJ(pString);
			DeleteFile(pTempIni);

		} else {

			DWORD dwFlags = MOVEFILE_WRITE_THROUGH | MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED;
			if ( !MoveFileEx (pTempIni,pIni, dwFlags)) {
				MessageBox ( __hWndM ,
//				ResString ( ResID ( IDS_NOMOVINGINI,&g_pTE->RF()),260),
				"Einträge zur Teilprojektverkettung in die Projekt-INI fehlgeschlagen! ",
				ResString (ResID(IDT_TPCAPTION,&g_pTE->RF()),50),
				MB_OK|MB_ICONEXCLAMATION);
			}
				

		}
	}

	DELETE_OBJ(pIni);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
Bool IniEqualToTemp( char *pTempIni, char *pIni) 
{
	if ( !pTempIni || *pTempIni == '\0')
		return false;

	if ( !pIni || *pIni == '\0')
		return false;

	if (strcmp (pTempIni,pIni) == 0)
		return true;

	char *pDrive = new char [_MAX_DRIVE];
	char *pPath = new char [_MAX_DIR];
	char *pDBName = new char [_MAX_FNAME];
	char *pExt = new char [ _MAX_EXT];

	if ( pDrive == NULL || pPath == NULL || pDBName == NULL || pExt == NULL) {
		DELETE_OBJ ( pDrive);
		DELETE_OBJ ( pPath);
		DELETE_OBJ ( pDBName);
		DELETE_OBJ ( pExt);
		return false;
	}

	TCHAR pTemp[_MAX_PATH];
	TCHAR pOri[_MAX_PATH];

// Dateinamen der ProfileDatei neu generieren
	_splitpath (pTempIni, pDrive, pPath, pDBName, pExt);
	_makepath (pTemp, NULL, NULL, pDBName, pExt);

	_splitpath (pIni, pDrive, pPath, pDBName, pExt);

	_makepath (pOri, NULL, NULL, pDBName, pExt);

	DELETE_OBJ ( pDrive);
	DELETE_OBJ ( pPath);
	DELETE_OBJ ( pDBName);
	DELETE_OBJ ( pExt);

	if ( strcmp(pTemp,pOri) == 0)
		return true;
	return false;


}
/////////////////////////////////////////////////////////////////////////////////
//-----Objekte pro TP-Merkmal--------
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumTPMCode ( long, Bool , void *pData)
  {
	(* (long *)pData)++;
	return TRUE;
  }

//------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT NumTPObjects ( long Object, Bool , void *pData)
{
	class TPRJTree *pTPRJ = ((TPPOINT *)pData)->pTPRJ;
	long *pObjPos = ((TPPOINT *)pData)->pObjPos;
	long *pObjNeg = ((TPPOINT *)pData)->pObjNeg;
	long MCode = ((TPPOINT *)pData)->TPMCode;
	long Number;
	
	if ( !pTPRJ || pTPRJ->Count() == 0) {
		Number= *pObjNeg;
		Number++;
		*pObjNeg = Number;
		*(pObjNeg + Number ) = Object;
		return TRUE;
	}

	char * pPuffer = new char [_MAX_PATH];
	if ( !pPuffer)
		return TRUE;
	*pPuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = Object;		// ObjektNummer
	tm.lMCode = MCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText = pPuffer;		// Puffer
	tm.iTTyp = TT_Objekt;
	DEX_GetTextMerkmal (tm);
	if ( *pPuffer == '\0') {
		DELETE_OBJ ( pPuffer);
		return TRUE;
	}

	strtok ( pPuffer , ";,\t");

	CTable t( *pTPRJ);
	ulong uCount = pTPRJ->Count();
	if ( uCount > 0 && t.Find(pPuffer)){
		Number= *pObjPos;
		Number++;
		*pObjPos = Number ;
		*(pObjPos + Number ) = Object;
	} else {
		Number= *pObjNeg;
		Number++;
		*pObjNeg = Number;
		*(pObjNeg + Number ) = Object;
	}

	DELETE_OBJ ( pPuffer);
	return TRUE;

}
/////////////////////////////////////////////////////////////////////////////
bool CProjectExtension :: DuplicatTempIni(char *pFullName)
{
	if ( !pFullName || *pFullName == '\0')
		return false;

	if (!_pIniTemp) 
		return false;

	char *pDrive = new char [_MAX_DRIVE];
	char *pPath = new char [_MAX_DIR];
	char *pDBName = new char [_MAX_FNAME];
	char *pExt = new char [ _MAX_EXT];

	if ( pDrive == NULL || pPath == NULL || pDBName == NULL || pExt == NULL) {
		DELETE_OBJ ( pDrive);
		DELETE_OBJ ( pPath);
		DELETE_OBJ ( pDBName);
		DELETE_OBJ ( pExt);
		return false;
	}

	char *pNewName = new char [ _MAX_PATH];
	if ( !pNewName) {
		DELETE_OBJ ( pDrive);
		DELETE_OBJ ( pPath);
		DELETE_OBJ ( pDBName);
		DELETE_OBJ ( pExt);
		return false;
	}

// Dateinamen der ProfileDatei neu generieren
	_splitpath (pFullName, pDrive, pPath, pDBName, pExt);
	_splitpath (_pIniTemp, pDrive, pPath, NULL, NULL);

	_makepath (pNewName, pDrive, pPath, pDBName, pExt);
	
	bool iFlag = false;

	if ( strcmp(_pIniTemp,pNewName) == 0)
		iFlag = true;

	DELETE_OBJ ( pDrive);
	DELETE_OBJ ( pPath);
	DELETE_OBJ ( pDBName);
	DELETE_OBJ ( pExt);
	DELETE_OBJ ( pNewName);
	return iFlag;

}

/////////////////////////////////////////////////////////////////////////////
void CProjectExtension :: SetTempIniFile(char * pPath)
{
	if (!pPath || *pPath == '\0')
		return;
// Temp suchen
	if (!_pIniOriginal) {
	
		_pIniOriginal = new char [_MAX_PATH];
		if (!_pIniOriginal)
			return;
		strcpy(_pIniOriginal,pPath);
	}

	if (!_pIniTemp) {

		_pIniTemp = new char [_MAX_PATH];
		if (!_pIniTemp) 
			return;
	}

	char * pTempDat = new char [_MAX_PATH];
	if ( pTempDat ) {
		DWORD TD = 0;
		TD = GetTempPath(_MAX_PATH, pTempDat);
		if ( TD > 0 ) {		// Temp-Bereich gefunden
			if ( TD > MAX_PATH) {
				DELETE_OBJ(pTempDat);
				pTempDat = new char [TD + 1];
				if ( pTempDat)
					DWORD TTD = GetTempPath(TD +1, pTempDat);
			}
		}

		if ( pTempDat) {
			char FName [_MAX_FNAME] = "";
			char Ext   [_MAX_EXT] = "";
			char Drive [_MAX_DRIVE] = "";
		    char Dir   [_MAX_DIR] = "";
  		    _splitpath (pPath, Drive, Dir, FName, Ext);
		    _splitpath (pTempDat, Drive, Dir, NULL, NULL);
			_makepath (_pIniTemp, Drive, Dir, FName, Ext);
		}


		CopyFile (pPath, _pIniTemp, false);
		m_isTempINI = true;

		DELETE_OBJ (pTempDat);
	}
}
/////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// KK010115
//-----------------------------------------------------------------------------
BOOL  CProjectExtension:: SetDQ(void)

{

	g_MCodes.clear();	// Verzeichnis der Datenquellen (HPROJECT,DATEI)

	ENUMNOKEY EN;
//	Bestimmen der Anzahl der Datenquellen

	EN.eFcn = ( ENUMNOKEYPROC) SucheDatenQuellen;
	EN.ePtr = (void *)&g_MCodes;
	DEX_EnumDataSources(EN);

	return true;
}
//------------------------------------------------------------------------------
//---------------------------------------------------------------------
extern "C" 
BOOL PASCAL _XTENSN_EXPORT SucheDatenQuellen (char *pName, bool , void *pData)
{

	CMCodeMap* pMCodes = (CMCodeMap *)pData;

	HPROJECT hPr = DEX_GetDataSourceHandleEx(pName);

	if ( 0 != hPr) {
		CMCodeMap::iterator it = pMCodes->find(hPr);

		if (it == pMCodes->end()){

			GEODBHDRENTRY hdrEntry;
			hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
			strncpy (hdrEntry.hdrKey, ResString (ResID(IDT_HEADTPMCODEIDENT,&g_pTE->RF()),17),16);
			hdrEntry.lphdrText = new char [MCODESIZE +1];
			hdrEntry.hdrTextLen = MCODESIZE;

			if (DEX_ReadGeoDBHdrEntryEx (hPr,hdrEntry) == EC_OKAY) {
		// HeaderEintrag existiert
				pMCodes->insert(CMCodeMap::value_type(hPr, os_string(hdrEntry.lphdrText)));
			}
		}
	}

	return TRUE;

}
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
extern "C" 
BOOL PASCAL _XTENSN_EXPORT SucheSichtDQ ( long lIdent, Bool bNotLast, void *pData ) 
{

	HPROJECT hPr = DEX_GetObjectsProject(lIdent);	// aktuelle Datenquelle

	if ( 0 != hPr) {

		GEODBHDRENTRY hdrEntry;
		hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
		strncpy (hdrEntry.hdrKey, ResString (ResID(IDT_HEADTPMCODEIDENT,&g_pTE->RF()),17),16);
		hdrEntry.lphdrText = new char [MCODESIZE +1];
		hdrEntry.hdrTextLen = MCODESIZE;

		if (DEX_ReadGeoDBHdrEntryEx (hPr,hdrEntry) == EC_OKAY) {
		// HeaderEintrag existiert
			(* (long *)pData) = lIdent;
			return FALSE;
		}
	}

	return TRUE;

}
///////////////////////////////////////////////////////////////////////////

//-----------TPPROJECT.CXX--------------------------------------------------
