// Anzeige diverser statistischer Informationen zu einem selektierten Objekt
// File: GEOSTAT.CXX

#include "statistp.hxx"

#include <shellapi.h>

#include <oleguid.h>
#include <dirisole.h>

#define _MIDL_USE_GUIDDEF_
//#include <triashelper.h>
//#include <triashelper_i.c>

//#include <eonrguid.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>


#include <xtsnaux.hxx>
#include <xtsnguid.h>
#include <initguid.h>
#include <istatus.h>
#include <igeometr.hxx>
#include <objgguid.h>	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include "geosguid.h" 
//---GUIDS---------------------
#include <statguid.h>
#include <trelguid.h>
#include <operguid.h>

#include "version.h"
#include "geostat.h" 
#include "about.h"
#include "dirmath.h"


#include "about.hxx"
#include "trfkoord.hxx"
#include "trfvect.hxx"
#include "idkey.hxx"    
#include "objkey.hxx"
#include "classkey.hxx"
#include "dbclass.hxx"
#include "classgi.hxx"
#include "stohwnd.hxx"
#include "dbinfo.hxx"
#include "geostat.hxx"


#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32



#if _MSC_VER >= 1100
EXTERN_C const IID __declspec(selectany) IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
EXTERN_C const IID __declspec(selectany) IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
#endif // _MSC_VER >= 1100

// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
CTriasExtension *NewExtension (void)
{
	return new StatistExtension ();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_GeoStatistik, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
//
// ACHTUNG: Im VersionsRC-File (*.rcv) nicht den Eintrag "TRiASSelfRegister" 
// vergessen. Ohne diesen Eintrag wird die Funktion UpdateRegistry nie gerufen.

BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_GeoStatistik, 
				TEXT("TRiAS.Statistik.1"), IDS_LONGCLASSNAME,
				GEOSTAT_MAJORVERSION, GEOSTAT_MINORVERSION,
				EFUnLoadable|EFVisible);

		{
//		CCurrentUser rgMASS("Software\\fez\\TRiAS\\Extensions\\TRiAS.Statistik.1\\Config", true);
		CCurrentUser rgMASS("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.Statistik.1\\Config", true);
		
			rgMASS.SetDWORD ( "FlächenMaß", FLM_QuadratMeter);
			rgMASS.SetDWORD ( "LängenMaß", LM_Meter);
		}
		return fSuccess;
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_GeoStatistik, 
				TEXT("TRiAS.Statistik.1"));
	}

return true;	// alles ok
}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muá von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuhängeneden Menu's übergeben bekommt.

StatistExtension :: StatistExtension (void)
//		  : CTriasExtension (STATISTEXTENSIONMENU, STATISTORMENU)
// Korrektur 02.02.99
//		  : CTriasExtension (0, STATISTORMENU)
		  : CTriasExtension ()

{

	m_pDoc = NULL;
	m_pScript = NULL;
	m_pTop = NULL;
	m_pObjOp = NULL;

	m_pIDM = NULL;		//	ID-Verzeichnis
	m_pIDC = NULL;
	m_pObjProp = NULL;	// Objekteigenschaften

#if !defined (WIN32)
	m_pHUGE = NULL;
#endif
	m_pGICLA = NULL;	// GI_Classification
	m_pOBJ = NULL;		//	Obj-Verzeichnis
	m_pClaObj = NULL;	// Objekte aus GI-Class.
	m_pHWNDTree = NULL;
	m_pCTF = NULL;		// Koordinaten - CTF
	m_pInfo = NULL;
	m_pEinheit = NULL;
	m_pOCL = NULL;		// ObjClassListContainer
	m_lRechMkode = 0L;	//	Mkode aus SightInfo
	m_isExtremum = FALSE;
	m_iObjCount = 0L;	// Objektzähler
	m_dStartTime=0;
	m_dStopTime=0;
	HideSightInfo();
	HideORHwnd();

	m_dFLM = FLM_Default;
	m_dLM = LM_Default;
	m_dON = ON_Default;

// Korrektur 02.02.99
	m_pPopupMenu = NULL;
	m_pPopupORMenu = NULL;

}

// Destruktor -----------------------------------------------------------------
StatistExtension :: ~StatistExtension (void) 
{

		DELETE_OBJ ( m_pIDM );

		DELETE_OBJ ( m_pIDC );

#if !defined (WIN32)
		delete ( long __huge *) m_pHUGE;
#endif

		DELETE_OBJ ( m_pGICLA );

		DELETE_OBJ ( m_pOBJ );

		DELETE_OBJ ( m_pOCL );

		DELETE_OBJ ( m_pClaObj );

		DELETE_OBJ ( m_pCTF );

		DELETE_OBJ ( m_pHWNDTree );

		DELETE_OBJ ( m_pInfo );

		DELETE_OBJ ( m_pEinheit );

		DELETE_OBJ (m_pObjProp);	// fully contained

// Korrektur 02.02.99
		DELETE_OBJ(m_pPopupMenu);
		DELETE_OBJ(m_pPopupORMenu);


		ReleaseInterface();
}
// ----------------------------------------------------------------------------

// da wir ein zusätzliches Interface dazugenommen haben, muß ein modifiziertes 
// QueryInterface gegeben sein
HRESULT StatistExtension :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IObjectProps)
		*ppvObj = m_pObjProp;	// ImportInterface liefern
	else
	// alles andere überlassen wir der BasisKlassse
		return CTriasExtension :: QueryInterface (riid, ppvObj);

// AddRef nicht vergessen
	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

// ----------------------------------------------------------------------------
// Virtuelle Funktionen, die bei bestimmten Events gerufen werden -------------

// Initialisierung der Erweiterung --------------------------------------------

// Diese Funktion wird (einmalig) gerufen, wenn die Erweiterung vollständig
// installiert ist
STDMETHODIMP_(BOOL) StatistExtension :: InitExtension ( short iMode)
{

	if (!CTriasExtension :: InitExtension (iMode))
		return false;


	try {
		m_pPopupMenu = new Menu (ResID(STATISTEXTENSIONMENU, &RF()));

	} catch (std::bad_alloc) {
		return FALSE;
	}

	try {
		m_pPopupORMenu = new Menu (ResID(STATISTORMENU, &RF()));

	} catch (std::bad_alloc) {
		return FALSE;
	}

	m_pObjProp = CObjectProperties :: CreateInstance (m_pUnk ? m_pUnk : this,  ResString (ResID(IDS_OBJPROPCLASSNAME,&RF()),50));
	if (NULL == m_pObjProp) 
		return false;

//-------------Statistik-Maáe-------------------------------------
#if defined(WIN32)
	{
//	CCurrentUser rgMASS("Software\\fez\\TRiAS\\Extensions\\TRiAS.Statistik.1\\Config", true);
	CCurrentUser rgMASS("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.Statistik.1\\Config", true);
	rgMASS.GetDWORD ( "FlächenMaß",m_dFLM);
	rgMASS.GetDWORD ( "LängenMaß",m_dLM);
	rgMASS.GetDWORD ( "Objektnummer",m_dON);
	}
#endif
	

	if ( !m_pCTF ) {
		// aktuelles Projektverzeichnis besorgen
		char *pLocDir = new char [_MAX_PATH];
		if ( pLocDir != NULL ) {
			if (DEX_GetActiveProject (pLocDir) != NULL) 
			// Projekt eröffnet
				m_pCTF = new CoordTransX;
			DELETE_OBJ (pLocDir);
		}
	}
// ObjPropertyFunktionen installieren

	m_iOPArea = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPAREA, &RF()), 30),
					 OPFlaechenInhalt,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_DOUBLE);
	m_iOPRange = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPRANGE, &RF()), 30),
					 OPFlaechenUmfang,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_DOUBLE);
	m_iOPBRange = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPBIGRANGE, &RF()), 30),
					 OPFlaechenUmrandung,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_DOUBLE);
	m_iOPRadius = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPAREARADIUS, &RF()), 30),
					 OPFlaechenRadius,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_DOUBLE);
	m_iOPDiff = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPDIFF, &RF()), 30),
					 OPFlaechenDifferenz,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_DOUBLE);
	m_iOPLine = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPLINE, &RF()), 30),
					 OPLinienLaenge,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_DOUBLE);
	m_iOPRPointX = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPRPOINTX, &RF()), 30),
					 OPReferenzPunktX,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_STRING);
	m_iOPRPointY = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPRPOINTY, &RF()), 30),
					 OPReferenzPunktY,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_STRING);
	m_iOPRText = AddPropertyFunction (ResString (ResID (IDS_OBJPROPRTEXT, &RF()), 30),
					 OPBegleitText);
	m_iOPRSPointX = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPRSPOINTX, &RF()), 30),
					 OPSchwerPunktX,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_STRING);
	m_iOPRSPointY = AddPropertyFunctionEx (ResString (ResID (IDS_OBJPROPRSPOINTY, &RF()), 30),
					 OPSchwerPunktY,(DWORD)this, NULL, PROPCAPS_OBJPROPTYPE_STRING);
// Neu
	m_iOPRObjekt = AddPropertyFunction (ResString (ResID (IDS_OBJPROPROBJEKT, &RF()), 30),
					 OPBegleitObjekt);



// Notifikation anfordern, die bei ObjektSelektieren/-deselektieren ausgelöst
// wird


// hier zusätzlichen MenuPunkt anhängen

	RegisterNotification (DEX_PROJECTOPEN);	
	RegisterNotification (DEX_N_PROJECTTOCLOSE);
	RegisterNotification (DEX_SIGHTSELECTED);
	RegisterNotification (DEX_CREATEOBJEKTINFO);
	RegisterNotification (DEX_OBJWNDCLOSED);
	RegisterNotification (DEX_HEADERREREAD);

// Korrektur 02.02.99
// Menu's einbauen
	if (!InstallPopupMenu(0))
		return FALSE;

	if (!InstallPopupORMenu(0))
		return FALSE;

	return TRUE;

}

// Korrektur 02.02.99
// Menues einbauen
bool StatistExtension::InstallPopupMenu (int iIndex)
{
INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex();
	imi.iMenuID = -1;
	imi.iFlag = IMINormalMenu;
	imi.iMenuNum = OBJCLASS_MENU_POS;

	imi.iMenuPos = -1;

// PopUpMenu und MenuText holen
	char cbBuffer[64];
	HMENU hMenu = m_pPopupMenu -> Handle(API_MENU_HMENU);

	imi.hMenu = GetSubMenu (hMenu, iIndex);
	TX_ASSERT(NULL != imi.hMenu);
	GetMenuString (hMenu, iIndex, cbBuffer, sizeof(cbBuffer), MF_SEPARATOR|MF_BYPOSITION);

	imi.pMenuText = cbBuffer;

	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
}
//------------------------------------------------------------------------------------------
// Menues einbauen
bool StatistExtension::InstallPopupORMenu (int iIndex)
{
INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex();
	imi.iMenuID = -1;
	imi.iFlag = IMIObjWnd;
	imi.iMenuNum = OR_OBJECT_MENU_POS;
	imi.iMenuPos = -1;

// PopUpMenu und MenuText holen
	char cbBuffer[64];
	HMENU hMenu = m_pPopupORMenu -> Handle(API_MENU_HMENU);

	imi.hMenu = GetSubMenu (hMenu, iIndex);
	TX_ASSERT(NULL != imi.hMenu);
	GetMenuString (hMenu, iIndex, cbBuffer, sizeof(cbBuffer), MF_SEPARATOR|MF_BYPOSITION);

	imi.pMenuText = cbBuffer;

	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------------------
void StatistExtension::RemovePopupMenus()
{
	REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex();
	rmi.iMenuID = -1;
	rmi.iMenuNum = OBJCLASS_MENU_POS;
	rmi.iFlag = IMINormalMenu;
	rmi.iMenuPos = -1;

	DEX_RemoveMenuItem (rmi);

}
//-----------------------------------------------------------------------------------------
void StatistExtension::RemovePopupORMenus()
{
	REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex();
	rmi.iMenuID = -1;
	rmi.iFlag = IMIObjWnd;		//OR-Fenster
	rmi.iMenuNum = OR_OBJECT_MENU_POS;
	rmi.iMenuPos = -1;
	DEX_RemoveMenuItem ( rmi);

}
//---------------------------------------------------------------------------
// Diese Funktion wird gerufen, bevor die Erweiterung freigeben werden soll
STDMETHODIMP_(BOOL) StatistExtension :: UnLoadExtension (void)
{

// Korrektur 02.02.99
// Menu's rauswerfen
	RemovePopupMenus();
	RemovePopupORMenus();
// PropertyFunctionen freigeben

	RemovePropertyFunction (m_iOPArea);
	RemovePropertyFunction (m_iOPRange);
	RemovePropertyFunction (m_iOPBRange);
	RemovePropertyFunction (m_iOPRadius);
	RemovePropertyFunction (m_iOPDiff);
	RemovePropertyFunction (m_iOPLine);
	RemovePropertyFunction (m_iOPRPointX);
	RemovePropertyFunction (m_iOPRPointY);
	RemovePropertyFunction (m_iOPRText);
	RemovePropertyFunction (m_iOPRSPointX);
	RemovePropertyFunction (m_iOPRSPointY);

// MenuPunkt natürlich wieder ausbauen

	HideSightInfo();
	HideORHwnd();

// Notifikationen wieder abmelden
	UnRegisterNotification (DEX_PROJECTOPEN);	
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);
	UnRegisterNotification (DEX_SIGHTSELECTED);
	UnRegisterNotification (DEX_CREATEOBJEKTINFO);
	UnRegisterNotification (DEX_OBJWNDCLOSED);
	UnRegisterNotification (DEX_HEADERREREAD);

return CTriasExtension :: UnLoadExtension();	// kein Fehler

}
// Korrektur 02.02.99

// Diese Funktion initialisiert das Menu --------------------------------------
bool StatistExtension::FindMenuItem (HMENU hMenu, UINT uiID)
{
UINT uiCnt = GetMenuItemCount(hMenu);

	uiID += MenuOffset();
	for (UINT uiLoop = 0; uiLoop < uiCnt; uiLoop++) {
		if (uiID == GetMenuItemID (hMenu, uiLoop))
			return true;
	}

	return false;		// nichts gefunden
}


//------------------------------------------------------------------------
// Diese Funktion initialisiert das Menu --------------------------------------
STDMETHODIMP_(BOOL) StatistExtension :: MenuInit (HMENU hMenu , LPARAM, HWND hWnd )
{
	if (pExtMenu() == NULL) return false;

	if ( hWnd == 0 && hMenu == MenuHandle() ) {	// Mein Kopf
		char * pPText = new char [_MAX_PATH];
		if ( !pPText )
			return false;

		if ( !DEX_GetActiveSight(pPText) ) {
			pExtMenu() -> DisableItem (IDM_SICHTINFO+MenuOffset());
			pExtMenu() -> DisableItem (IDM_SICHTPART+MenuOffset());
			pExtMenu() -> DisableItem (IDM_SICHTORWIND+MenuOffset());
			pExtMenu() -> DisableItem (IDM_SICHTPARAM+MenuOffset());
		} else {
			pExtMenu() -> EnableItem (IDM_SICHTINFO+MenuOffset());
			pExtMenu() -> EnableItem (IDM_SICHTPART+MenuOffset());
			pExtMenu() -> EnableItem (IDM_SICHTORWIND+MenuOffset());
			pExtMenu() -> EnableItem (IDM_SICHTPARAM+MenuOffset());
		}
		DELETE_OBJ ( pPText);

		if ( m_pHWNDTree != NULL && m_pHWNDTree->Count() > 0 ) 
			pExtMenu() -> EnableItem (IDM_SICHTORWIND+MenuOffset());
		else
			pExtMenu() -> DisableItem (IDM_SICHTORWIND+MenuOffset());
		return TRUE;
	}
//--------------neu----------------------
	if ( hWnd != 0 && hMenu == ORMenuHandle()) {	// mein ORFenster
		if ( m_pHWNDTree == NULL ) 
			m_pHWNDTree = new SHWNDTree;
		bool Flag = false;
		{
		CTable t(*m_pHWNDTree);
		if ( (!t.Find ( (void *)&hWnd ))) {
			SHWNDCreator SHWNDCr ( *m_pHWNDTree );
			ContCreate (SHWNDCr, SHWND) ( hWnd );
			Flag = true;
		}
		}
		if ( Flag)
			AddORHwnd();

//	ObjektContainer
		UINT iMenuID1 = IDM_DEFOBJCONT + MenuOffset();

//	ObjektTopologie
		UINT iMenuID2 = IDM_DEFOBJTOPOL + MenuOffset();

//	ObjektTopologie-Basic
		UINT iMenuID3 = IDM_ORWINOBJTOPOL + MenuOffset();

//	ObjektTopologie-WM-Top
		UINT iMenuID4 = IDM_ORWINOBJTOPOLOG + MenuOffset();

		OBJSTATISTIK OS;
	   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);
		OS.lONr =  DEX_GetActiveObject ( hWnd );

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
			if ( OS.iObjTyp == OT_FLAECHE ) {
				EnableMenuItem (hMenu, iMenuID1, MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, iMenuID2, MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, iMenuID3, MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, iMenuID4, MF_BYCOMMAND|MF_ENABLED);
			} else {
				EnableMenuItem (hMenu, iMenuID1, MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, iMenuID2, MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, iMenuID3, MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, iMenuID4, MF_BYCOMMAND|MF_GRAYED);
			}
		} else {
			EnableMenuItem ( hMenu, iMenuID1, MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem ( hMenu, iMenuID2, MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem ( hMenu, iMenuID3, MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem ( hMenu, iMenuID4, MF_BYCOMMAND|MF_GRAYED);
		}
//------------------------------------------------------------------------
//---------------GeometrieTypen der selektierten Objekte eines Fensters,
//---------------um MenuPunkte zu aktivieren/deaktivieren
//
//		short Type = GetObjectsInHwndType ( hWnd );
		short Type;
		DEXOR_QuerySelectedObjectTypes ( hWnd , Type );
		if ( (Type & OTFlaeche) > 0 || (Type & OTLinie) > 0 ) {
				EnableMenuItem (hMenu, IDM_DEFMINMAX+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_DEFMEDIAN+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_DEFMITTELWERT+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_DEFKLASSIFIZ+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
		} else {
				EnableMenuItem (hMenu, IDM_DEFMINMAX+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_DEFMEDIAN+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_DEFMITTELWERT+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_DEFKLASSIFIZ+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		}

	}
	return TRUE;
}

//Korrektur 02.02.99
STDMETHODIMP_(BOOL) StatistExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	if (NULL != hWnd) return false;		// nicht für uns
	
// Stringsladen und an TRiAS schicken
UINT uiRes = 0L;

	switch (uiMenuID) {
	case IDM_SICHTINFO:
	uiRes = ID_STAT_SICHTINFO; 
	break;
	case IDM_SICHTPART:
	uiRes = ID_STAT_SICHTPART; 
	break;
	case IDM_SICHTORWIND:
	uiRes = ID_STAT_SICHTORWIND; 
	break;
	case IDM_SICHTPARAM:
	uiRes = ID_STAT_SICHTPARAM;
	break;

// OR -Fenster
	case IDM_DEFORWIND:
	uiRes = ID_STAT_ORWIND; 
	break;
	case IDM_DEFKLASSIFIZ:
	uiRes = ID_STAT_KLASSIFIZ; 
	break;
	case IDM_DEFMINMAX:
	uiRes = ID_STAT_MINMAX; 
	break;
	case IDM_DEFMEDIAN:
	uiRes = ID_STAT_MEDIAN;
	break;
	case IDM_DEFOBJCONT:
	uiRes = ID_STAT_OBJCONT; 
	break;
	case IDM_ORWINOBJTOPOL:
	uiRes = ID_STAT_TOPOL; 
	break;
	case IDM_ORWINOBJTOPOLOG:
	uiRes = ID_STAT_TOPOLOG;
	break;
	default:
		break;
	}	

	if (uiRes != 0L) {
	ResString resMsg (ResID (uiRes, &RF()), _MAX_PATH);
	char cbString[_MAX_PATH];
	
		strcpy (cbString, resMsg);
		strtok (cbString, "\n");
		DEX_SetMessageString (cbString);
		return true;
	}

return false;
}

// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(BOOL) StatistExtension :: MenuCommand (WPARAM MenuItemID, HWND hWnd)
{

	switch (MenuItemID) {	

//-----------------ABOUT-Fenster-----------------------------------------
		case IDM_ABOUT:		// AboutBox
		{
		AboutBox AB (MVWind(), ResID (STATISTABOUT, &RF()));
		AB.Show();
		return TRUE;
		} 

//-----------------Datenbankinformation-----------------------------------------
		case IDM_GEOALLDBINFO:		
		{
		if ( ObjektTest())
			return TRUE;
		SetTreeInformation();
		short Typ = (short) OKlDataBase;
		m_isSightInfo = Typ;
		if ( BuildObjClassInfo ( Typ) )

	// Start DataBaseObjClass
			ShowObjectClassInformation ( Typ);
		return TRUE;
		} 


//-----------------Sichtinformation-----------------------------------------
//	ganze Sicht
		case IDM_SICHTINFO:
       		{    
		CEierUhr Wait ( MVWind());
		SetTreeInformation();
		short Typ = (short) OKlAttribut;
		m_isSightInfo = Typ;
		BuildObjClassInfo ( Typ);

		// Start DataBaseObjClass
		ShowObjectClassInformation (Typ);
		return TRUE;
		}

//	Sichtausschnitt
		case IDM_SICHTPART:
		{
		CEierUhr Wait ( MVWind());
		short Typ = (short) OKlAttributSegment;
		m_isSightInfo = Typ;

		SetTreeInformation();

		long Cont[4];
		if ( !DEX_GetActiveSelection ( Cont ))
			DEX_GetActiveSightContainer ( Cont );

//Korr 27.1.95
		{
			OBJPOINT OB;
			OB.pOBJ = m_pOBJ;
			OB.lRange = 0;
			OB.lCount = 0;
			OB.pCTF = m_pCTF;
			long lRange = 100;
			if ( m_pInfo != NULL )
				DELETE_OBJ ( m_pInfo);
			pWindow pW = MVWind();
			char * pBuf = new char [_MAX_PATH];
			if ( pBuf == NULL ) 
				return TRUE;
			*pBuf = '\0';
			strcat ( pBuf , ResString (ResID(IDS_CREATEDBOBJECTS,&RF()),50));
			m_pInfo = new IdentInformation ( pW, SHOWIDENTIFIKATOR, RF(),m_pIDM,pBuf,lRange);
			OB.pStatus = m_pInfo;
			m_pInfo->SetStart();
			m_pInfo->Disable();

			m_pInfo->Show();

			m_pInfo->Update();
		        if ( m_pInfo->Break()) {
				HWND hwnd = m_pInfo->Handle();
				MessageBox ( hwnd ,
				 ResString ( ResID ( IDS_GICLASSSTOPWORK,&RF()),50), 
				 ResString ( ResID ( IDS_CREATEDBOBJECTS,&RF()),50), 
				 MB_OK|MB_ICONEXCLAMATION);
				DELETE_OBJ ( m_pInfo);
				return TRUE;
			}
			
			DELETE_OBJ ( pBuf );

			ENUMRECHGEOMETRIE ERGI;
			memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
			ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
			ERGI.lCont = &Cont[0];
			ERGI.iMode = ERGActSight;
		//	Objekte zählen
			ERGI.eFcn = (RECHGEOMETRIEPROC) EnumObjectsWithStatus;
//Korr 27.1		ERGI.pData = m_pOBJ;
			ERGI.pData = &OB;
			DEX_EnumRechGeometrie( ERGI );
			if ( OB.lCount == -1 )	{	// Abgebrochen
				HWND hwnd = m_pInfo->Handle();
				MessageBox ( hwnd ,
				 ResString ( ResID ( IDS_GICLASSSTOPWORK,&RF()),50), 
				 ResString ( ResID ( IDS_CREATEDBOBJECTS,&RF()),50), 
				 MB_OK|MB_ICONEXCLAMATION);
				DELETE_OBJ ( m_pInfo);
				return TRUE;
			}
			DELETE_OBJ ( m_pInfo);
		}

		CreateObjClassFromObjects (Typ);
		Wait.Hide();

		// Start DataBaseObjClass
		ShowObjectClassInformation ( Typ);

		return TRUE;
		}


//--------------- Parameter --------------------------------------
		case IDM_SICHTPARAM:
        	{    
		SetTreeInformation();
		short Typ = (short) OKlParameter;
		m_isSightInfo = Typ;

		BuildObjClassInfo ( Typ);
		
		BuildObjClassContainer();	// ListContainer

		// Start DataBaseObjClass
		{
			pWindow pW = MVWind(); 
			short MFlag = TRUE;
			DataBaseObjClass DBO ( pW,SHOWOBJECTCLASS, RF(),MFlag, m_pIDM, m_pOCL);
			DBO.Show();
		}

		DELETE_OBJ ( m_pOCL);	//ListContainer raus

		return TRUE;
		}

//----------------------alle OR-Fenster-----------------------------

		case IDM_SICHTORWIND:
		{

		CEierUhr Wait ( MVWind());

//		 Objekte aus aktuellem Fenster

		SetTreeInformation();

		GetFL_ObjectsFromAllORWindow( FALSE);
		if ( m_isBreak ) {
			m_isBreak = FALSE;
			return TRUE;
		}
// 		Objekte bestimmt und geordnet abgelegt
		short Typ = (short) OKlAttributWindow;
		m_isSightInfo = Typ;


		CreateObjClassFromObjects (Typ);

		Wait.Hide();

		// Start DataBaseObjClass
		ShowObjectClassInformation (Typ);

		return TRUE;
		}

//-----------------------EXTRA----------------------------------------
//--------------	Minimum/Maximum	---------------------------

		case IDM_DEFMINMAX:
		{

		CEierUhr Wait ( MVWind());
		if ( m_pOBJ != NULL)
			DELETE_OBJ ( m_pOBJ);
		m_pOBJ = new OBJTree;
		GetFL_ObjectsFromORWindow (TRUE,hWnd);	// ObjektBaum
		if ( m_isBreak ) {
			m_isBreak = FALSE;
			return TRUE;
		}
		
		m_pIDC = GetExtremum ( m_pOBJ );

		if ( m_pIDC != NULL ) {
			m_isExtremum = TRUE;
			short Flag = -1;
			char * pBuf = new char [_MAX_PATH];
			if ( pBuf != NULL )  {
				*pBuf = '\0';
				strcat ( pBuf , ResString (ResID(IDS_MINIMUMMAXIMUM,&RF()),50));
				CreateORWindow ( Flag, 350, 10, m_pIDC, pBuf,0,255,255);
				DELETE_OBJ ( pBuf);
			}
			DELETE_OBJ ( m_pIDC );
			m_isExtremum = FALSE;
		}
		return TRUE;
		}

//-----------------------Mittelwert---------------------------------
		case IDM_DEFMITTELWERT:
		{
		CEierUhr Wait ( MVWind());

		if ( m_pOBJ != NULL)
			DELETE_OBJ ( m_pOBJ);
		m_pOBJ = new OBJTree;
		m_hWnd = hWnd;

		GetFL_ObjectsFromORWindow( TRUE,hWnd);
		if ( m_isBreak ) {
			m_isBreak = FALSE;
			return TRUE;
		}

		char * pBuffer = MittelWert ();

		if ( pBuffer == NULL || *pBuffer == NULL ) {
			DELETE_OBJ ( pBuffer);
			return TRUE;
		}

		Wait.Hide();

		MessageBox ( m_hWnd , pBuffer ,
			 ResString ( ResID ( IDS_ARITHMITTEL,&RF()),60),
			 MB_OK|MB_ICONINFORMATION);
				 
		DELETE_OBJ ( pBuffer );

		return TRUE;
		}

//-----------------MedianWert--------------------------------------
		case IDM_DEFMEDIAN:
		{

		CEierUhr Wait (MVWind());

		if ( m_pOBJ != NULL)
			DELETE_OBJ ( m_pOBJ);
		m_pOBJ = new OBJTree;
		m_hWnd = hWnd;
		GetFL_ObjectsFromORWindow(TRUE,hWnd);
		if ( m_isBreak ) {
			m_isBreak = FALSE;
			return TRUE;
		}

		char * pBuffer = MedianWert ();

		if ( pBuffer == NULL || *pBuffer == NULL ) {
			DELETE_OBJ ( pBuffer);
			return FALSE;
		}

		Wait.Hide();

		MessageBox ( m_hWnd , pBuffer ,
			 ResString ( ResID ( IDS_MEDIANWERT,&RF()),60),
			 MB_OK|MB_ICONINFORMATION);
				 
		DELETE_OBJ ( pBuffer );

		return TRUE;
		}

//------------------Klassifizierung----------------------------

		case IDM_DEFKLASSIFIZ:
	
		{
		CEierUhr Wait ( MVWind());

//		 Objekte aus aktuellem Fenster
		m_hWnd = hWnd;
		SetTreeInformation();
		GetFL_ObjectsFromORWindow( TRUE,hWnd);
		if ( m_isBreak ) {
			m_isBreak = FALSE;
			return TRUE;
		}

// 		Objekte bestimmt und geordnet abgelegt

		short Typ = (short) OKlGeometrieTyp;
		m_isSightInfo = Typ;
		CreateObjClassFromObjects (Typ);

		Wait.Hide();

		ShowClassification ();

		return TRUE;
		}

//----------------------aktives OR-Fenster-----------------------------

		case IDM_DEFORWIND:
		{
		CEierUhr Wait ( MVWind());

//		 Objekte aus aktuellem Fenster
		m_hWnd = hWnd;
		SetTreeInformation();

		GetFL_ObjectsFromORWindow( FALSE,hWnd);
		if ( m_isBreak ) {
			m_isBreak = FALSE;
			return TRUE;
		}

// 		Objekte bestimmt und geordnet abgelegt
		short Typ = (short) OKlAttributWindow;
		m_isSightInfo = Typ;

		CreateObjClassFromObjects (Typ);

		Wait.Hide();

		// Start DataBaseObjClass
		ShowObjectClassInformation( Typ);
		return TRUE;
		}

//----------------------ObjektContainer--------------------------------
		case IDM_DEFOBJCONT:
		
		{
		CEierUhr Wait ( MVWind());

		m_hWnd = hWnd;
		SetTreeInformation();
		//	ON definiert ????
		OBJSTATISTIK OS;
   		memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);

		OS.lONr =  DEX_GetActiveObject ( hWnd );

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS)) {

			if ( OS.iObjTyp == OT_FLAECHE ) {
				long *pCont = ObjectContainer ( OS.lONr, OS.iObjTyp);

//Korr 27.1.95
				{
				OBJPOINT OB;
				OB.pOBJ = m_pOBJ;
				OB.lRange = 0;
				OB.lCount = 0;
				OB.pCTF = m_pCTF;
				long lRange = 100;
				if ( m_pInfo != NULL )
					DELETE_OBJ ( m_pInfo);
				pWindow pW = ORWind( m_hWnd);
				char * pBuf = new char [_MAX_PATH];
				if ( pBuf == NULL ) 
					return TRUE;
				*pBuf = '\0';
				strcat ( pBuf , ResString (ResID(IDS_CREATEDBOBJECTS,&RF()),50));

				m_pInfo = new IdentInformation ( pW, SHOWIDENTIFIKATOR, RF(),m_pIDM,pBuf,lRange);
				OB.pStatus = m_pInfo;
				m_pInfo->SetStart();
				m_pInfo->Update();
				m_pInfo->Show();
				DELETE_OBJ ( pBuf);

				ENUMRECHGEOMETRIE ERGI;
				memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
				ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
				ERGI.lCont = pCont;
				ERGI.iMode = ERGActSight;
//				Objekte zählen
				ERGI.eFcn = (RECHGEOMETRIEPROC) EnumObjectsWithStatus;
				ERGI.pData = &OB;
				DEX_EnumRechGeometrie( ERGI );
				if ( OB.lCount == -1 )	{	// Abgebrochen
					HWND hwnd = m_pInfo->Handle();
					MessageBox ( hwnd ,
					ResString ( ResID( IDS_GICLASSSTOPWORK,&RF()),50),
					ResString ( ResID ( IDS_CREATEDBOBJECTS,&RF()),60),
					 MB_OK|MB_ICONEXCLAMATION);
					DELETE_OBJ ( m_pInfo);
					return TRUE;
				}
				DELETE_OBJ ( m_pInfo);

				} //	ENDE Status

				long ONr = OS.lONr;			
				short Typ = (short )OKlObjectContainer;
				m_isSightInfo = Typ;
				m_lRechKey = OS.lONr;
				DELETE_OBJ ( pCont );


// 		Objekte bestimmt und geordnet abgelegt

				CreateObjClassFromObjects (Typ);
				// Start DataBaseObjClass
				ShowObjectClassInformation ( Typ);
			}
				
		} // IF

		return TRUE;

		} // CASE

///////////////////////////////////////////////////////////////////////

//------------------Top in -ObjektContainer--------------------------------
		case IDM_ORWINOBJTOPOLOG:
		
		{
		CEierUhr Wait ( MVWind());

		m_hWnd = hWnd;
		SetTreeInformation();
		//	ON definiert ????
		OBJSTATISTIK OS;
   		memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);

		OS.lONr =  DEX_GetActiveObject ( hWnd );

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS)) {

			if ( OS.iObjTyp == OT_FLAECHE ) {
				if ( !m_pTop) 
					LadeTopRel();

				long *pCont = ObjectContainer ( OS.lONr, OS.iObjTyp);

//Korr 27.1.95
				{
				OBJPOINT OB;
				OB.m_pTop = m_pTop;
				OB.lBezObj = OS.lONr;
				OB.pOBJ = m_pOBJ;
				OB.lRange = 0;
				OB.lCount = 0;
				OB.pCTF = m_pCTF;
				long lRange = 100;
				if ( m_pInfo != NULL )
					DELETE_OBJ ( m_pInfo);
				pWindow pW = ORWind( m_hWnd);
				char * pBuf = new char [_MAX_PATH];
				if ( pBuf == NULL ) 
					return TRUE;
				*pBuf = '\0';
				strcat ( pBuf , ResString (ResID(IDS_CREATEDBOBJECTS,&RF()),50));

				m_pInfo = new IdentInformation ( pW, SHOWIDENTIFIKATOR, RF(),m_pIDM,pBuf,lRange);
				OB.pStatus = m_pInfo;
				m_pInfo->SetStart();
				m_pInfo->Update();
				m_pInfo->Show();
				DELETE_OBJ ( pBuf);

				ENUMRECHGEOMETRIE ERGI;
				memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
				ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
				ERGI.lCont = pCont;
				ERGI.iMode = ERGActSight;
//				Objekte zählen
				ERGI.eFcn = (RECHGEOMETRIEPROC) EnumObjectsWithTopo;
				ERGI.pData = &OB;
				DEX_EnumRechGeometrie( ERGI );
				if ( OB.lCount == -1 )	{	// Abgebrochen
					HWND hwnd = m_pInfo->Handle();
					MessageBox ( hwnd ,
					ResString ( ResID( IDS_GICLASSSTOPWORK,&RF()),50),
					ResString ( ResID ( IDS_CREATEDBOBJECTS,&RF()),60),
					 MB_OK|MB_ICONEXCLAMATION);
					DELETE_OBJ ( m_pInfo);
					return TRUE;
				}
				DELETE_OBJ ( m_pInfo);

				} //	ENDE Status

				long ONr = OS.lONr;			
				short Typ = (short) OKlObjectRelation;
//				short Typ = (short )OKlObjectContainer;
				m_isSightInfo = Typ;
				m_lRechKey = OS.lONr;
				DELETE_OBJ ( pCont );


// 		Objekte bestimmt und geordnet abgelegt

				CreateObjClassFromObjects (Typ);
				// Start DataBaseObjClass
				ShowObjectClassInformation ( Typ);
			}
				
		} // IF

		return TRUE;

		} // CASE

///////////////////////////////////////////////////////////////////////
//----------------------ObjektTopologie--------------------------------
		case IDM_ORWINOBJTOPOL:
		
		{
			long lONr =  DEX_GetActiveObject ( hWnd );
			if ( 0L >= lONr )
			return true;

			LoescheStatistikFlaechen();

			if ( !m_pDoc )
				LadeBasicDocument();
			if (!m_pScript)
				LadeBasicScript();

// Basic hilf mir
			_DGeoObject *pIObj = NULL;
			if ( GetGeoObjectFromONr (lONr,&pIObj)) {

// Für 3.0 DatenQuelle auftreiben

				char *pQuelle = new char [_MAX_PATH];
				if (!pQuelle)
					return false;
				long lIdent = DEX_GetObjIdent(lONr);
				*pQuelle = '\0';
#if _MSC_VER >= 1100
				HPROJECT hPr = DEX_GetObjectsProject(lIdent);

				DEX_GetDataSourceShortName (hPr, pQuelle);

#endif
				ebPARAM PA[3];

				PA[0].wType = 0;
				PA[0].szExtType[0] = '\0';

				PA[1].wType = TYP_APPOBJECT;
				strcpy (PA[1].szExtType, "GeoObject");

				//DatenQuelle
				PA[2].wType = TYP_STRING;
				strcpy ( PA[2].szExtType,pQuelle);

				LPVOID pTyp = NULL;

				LPVOID pVals[3] = { NULL, &pIObj ,pQuelle};

				BSPARAM BS;
				BS.pTypes = PA;
				BS.pValues = pVals;

				if ( m_pScript) 
					m_pScript->RunCode(g_hInstance,IDR_SCRIPTTOPO,"TOPOLOG",2,&BS);

				pIObj->Release();

				DELETE_OBJ(pQuelle);

			}

		}
		return true;

#if _TRiAS_VER < 0x0300
	//----------------------ObjektTopologie--------------------------------
		case IDM_DEFOBJTOPOL:
		
		{

		CEierUhr Wait ( MVWind());
		m_hWnd = hWnd;
		SetTreeInformation();
		//	ON definiert ????
		OBJSTATISTIK OS;
	   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);

		OS.lONr =  DEX_GetActiveObject ( hWnd );

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS)) {

			if ( OS.iObjTyp == OT_FLAECHE ) {

				ENUMTOPRELS ETR;
				OBJPOINT OB;
				OB.pOBJ = m_pOBJ;
				OB.pCTF = m_pCTF;
		   		memset (&ETR,'\0',sizeof(ENUMTOPRELS));
				ETR.m_dwSize = sizeof(ENUMTOPRELS);
				ETR.m_lONr = OS.lONr;
				ETR.m_eFcn = ( ENUMLONGKEYPROC) EnumObjectsWithAL;
				ETR.m_dwData = (DWORD ) &OB;
				ETR.m_iMode = ETRAnalyzeView;
				ETR.m_pView = NULL;
				DEX_EnumTopRelations(&ETR);
				m_lRechKey = OS.lONr;
			}

		} // IF
//-----------------Fenster---------------------------------------

// 		Objekte bestimmt und geordnet abgelegt
		short Typ = (short) OKlObjectRelation;
		m_isSightInfo = Typ;

		CreateObjClassFromObjects (Typ);
	
		// Start DataBaseObjClass
		ShowObjectClassInformation(Typ);

		return TRUE;

		} // CASE
#endif // _TRiAS_VER < 0x0300

//---------------------default-------------------------------------
		default:
		return FALSE;

	} // SWITCH
	return FALSE;
}

STDMETHODIMP_(LRESULT) StatistExtension :: Notification (WPARAM iMsg, LPARAM p)
{

	switch (iMsg) {

	case DEX_QUERYRECHOBJECT:

	{
	if ( m_isSightInfo == OKlGeometrieTyp ) {
//	GIClassGruppen
	if ( m_pGICLA != NULL && m_pClaObj != NULL ) {
	    if ( !GetObjectTypes( p )) return TRUE;
	    if ( m_pIDM == NULL ) return FALSE;
	    CTable f( *m_pIDM );
	    if ( !f.Find (&m_lRechKey))
			return FALSE;
	    IDMLock g(f);
	    OBJTree * pOBJ = g->pObjects();
	    if ( pOBJ == NULL) return FALSE;
//-----------------------TIMER---------------------------------
//------------------------------------------------------------
	    if ( m_lRechMkode == 0 ) {
		char * pBuffer0 = new char [_MAX_PATH];
		char * pBuffer1 = new char [_MAX_PATH];
	        if ( pBuffer0 == NULL || pBuffer1 == NULL )
		         return FALSE;
		*pBuffer0 = '\0';
		*pBuffer1 = '\0';


double Wert = 0.0;
	      CTable t(*pOBJ);
	      long ON = ((RECHOBJECT *)p)->lONr;
	      if ( t.Find (&ON) ) {

	        ((RECHOBJECT *)p)->iFlags=((RECHOBJECT *)p)->iFlags|ROHideIdent;
		OBJLock l(t);

		CTable d(*m_pGICLA);
		long Intervall = l->Intervall();
		if ( Intervall == -1) {		// Einzelkriterium
			d.First();
			GICLALock m(d);
			if ( m->GiTyp() == OTFlaeche )
				Wert = l->FlInhalt();
			else
				Wert = l->LinLaenge(); 
			Wert = Wert / (double) m->Einheit();

			strcat ( pBuffer0, " [ ");
			ST_DtoA ( pBuffer1, "%10.3f", Wert);
			strcat ( pBuffer0,pBuffer1);
			strcat ( pBuffer0, " ");
			if ( m_pEinheit != NULL)
				strcat ( pBuffer0, m_pEinheit +1);
		       ((RECHOBJECT *)p)->iFlags=0;
		}				

		if ( d.Find(&Intervall)) {
			GICLALock m(d);
			strcat ( pBuffer0, "Intervall ");
			wsprintf ( pBuffer1, "%3ld",m->Group());
			strcat ( pBuffer0,pBuffer1);
			strcat ( pBuffer0, " : [");
			ST_DtoA (pBuffer1, "%10.3f", m->VglWert1());
			strcat (pBuffer0,pBuffer1);
			strcat ( pBuffer0, " , ");
			ST_DtoA (pBuffer1, "%10.3f", m->VglWert2());
			strcat (pBuffer0,pBuffer1);
			strcat ( pBuffer0, "]");

		}
		if ( *pBuffer0 == '\0' ) {
			DELETE_OBJ ( pBuffer0 );
			DELETE_OBJ ( pBuffer1 );
			return FALSE;		// Objekt nicht anzeigen
		}

		if ( *pBuffer0 != '\0' ) 
			strcpy( (( RECHOBJECT *)p)->lpText, pBuffer0);

		DELETE_OBJ ( pBuffer0 );
		DELETE_OBJ ( pBuffer1 );
		
		}
	   } else {
	//	RechMKode > 0

	
		TARGETMERKMAL TM;
		memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
		TM.dwSize = sizeof (TARGETMERKMAL);
		TM.lTarget = ((RECHOBJECT *)p)->lONr;
		TM.lMCode = m_lRechMkode;
		TM.imaxLen = (( RECHOBJECT *)p)->iTextLen;
		TM.iTTyp = TT_Objekt;
		TM.pMText = (( RECHOBJECT *)p)->lpText;
		DEX_GetTextMerkmal ( TM );

	   }
	}	

	}	// Ende GeometrieTyp


//	TextMerkmal
	if ( m_isSightInfo != OKlGeometrieTyp ) {

	if ( m_pIDM != NULL && m_pIDC != NULL ) {
	    if ( !GetObjectTypes( p ))
		 return FALSE;
//-----------Mkode-Text anzeigen
  	    if ( m_lRechMkode > 0L  ) { 		// Mkode-Text: holen

	
		TARGETMERKMAL TM;
		memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
		TM.dwSize = sizeof (TARGETMERKMAL);
		TM.lTarget = ((RECHOBJECT *)p)->lONr;
		TM.lMCode = m_lRechMkode;
		TM.imaxLen = (( RECHOBJECT *)p)->iTextLen;
		TM.iTTyp = TT_Objekt;
		TM.pMText = (( RECHOBJECT *)p)->lpText;
		DEX_GetTextMerkmal ( TM );

	    }
//--------------------TIMER--------------------------------------------
	    if ( !m_pInfo) {
	       m_dStopTime = timeGetTime();
	       m_iRange++;
	       if ( (m_dStopTime - m_dStartTime ) > (DWORD) MAXSECONDS ) {

		char * pBuf = new char [_MAX_PATH];
		if ( pBuf != NULL ) {
			*pBuf = '\0';
			wsprintf (pBuf, ResString( ResID( IDS_TIMERCAPTION,&RF()),50),m_iObjCount);
			pWindow pWin = MVWind();
			m_pInfo = new IdentInformation ( pWin, SHOWIDENTIFIKATOR, RF(),m_pIDM,pBuf,m_iObjCount);
			m_pInfo->Show();
			m_pInfo->Update();
			DELETE_OBJ ( pBuf );
		}
	       }
	     } else {
		    m_iRange++;
		    m_pInfo->SetObjectText( m_iRange );
		    m_pInfo->SetPosition( m_iRange );
		    if ( m_pInfo->Break()) 
			return TRUE;
	     }

	}
//------------Minimum/Maximum
	if ( m_isExtremum  ) { 		// Mkode-Text: holen
		if ( *(m_pIDC+1) == ((RECHOBJECT *)p)->lONr ||
		     *(m_pIDC+3) == ((RECHOBJECT *)p)->lONr )
			strcpy( (( RECHOBJECT *)p)->lpText, ResString(ResID(IDS_CLIPMINIMUM,&RF()),50));
		if ( *(m_pIDC+2) == ((RECHOBJECT *)p)->lONr ||
		     *(m_pIDC+4) == ((RECHOBJECT *)p)->lONr )
			strcpy( (( RECHOBJECT *)p)->lpText, ResString(ResID(IDS_CLIPMAXIMUM,&RF()),50));
	}

	}
	}	// Ende Case
	break;


	case DEX_PROJECTOPEN:
	{
	if ( !m_pCTF ) {
	// aktuelles Projektverzeichnis besorgen
		char *pLocDir = new char [_MAX_PATH];
		if ( pLocDir != NULL ) {
			if (DEX_GetActiveProject (pLocDir) != NULL) 
			// Projekt eröffnet
				m_pCTF = new CoordTransX;
			DELETE_OBJ (pLocDir);
		}
	}
	HideSightInfo();
	HideORHwnd();
	LoescheStatistikFlaechen();
	}
	break;

	case DEX_N_PROJECTTOCLOSE:
		DELETE_OBJ ( m_pCTF);	// Koord. raus
		HideSightInfo();
		HideORHwnd();
		DELETE_OBJ (m_pHWNDTree);
		ReleaseInterface();
		LoescheStatistikFlaechen();
	break;

	case DEX_OBJWNDCLOSED:

	// Objektfenster wird geschlossen
	{
//	if ( m_pHWNDTree != NULL ) {
	if ( m_pHWNDTree != NULL && m_pHWNDTree->Count() > 0 ) {

		CTable t(*m_pHWNDTree); 
		HWND Rmich = HWND ( p );
		if ( (t.Find ( (void *)&Rmich ))) {
			t.Delete();
			DeleteORHwnd();
		}
		if ( isORHwnd() ) { 
			  t.First();
			 SHWNDLock l(t);
			Rmich = l->Shwnd();
			 SetFocus ( Rmich );
		}
	}
	}
	break;

	case DEX_SIGHTSELECTED:
	// Sicht wird gewechselt
	{
		HideSightInfo();
		HideORHwnd();
		SichtInfo();
	}
	break;

	case DEX_HEADERREREAD:
	// CTF wird gewechselt
	{
		if ( NULL != m_pCTF) {
			if (m_pCTF->Reload(true)) {
				DELETE_OBJ ( m_pCTF);
				m_pCTF = new CoordTransX();
			}
		}
	}
	break;

//	case DEX_OBJECTSELECTED:
//	{
//	}
//	break;

//	case DEX_OBJECTUNSELECTED:
	// ein Objekt wurde deselektiert
//	{
//	}
//	break;

	case DEX_CREATEOBJEKTINFO:
	// ein Fenster wurde aufgezogen
//-------------- Handle in Baum -----------------------------------------------
	{

	if ( m_pHWNDTree == NULL ) 
		m_pHWNDTree = new SHWNDTree;
	{
	CTable t(*m_pHWNDTree);

	SHWNDCreator SHWNDCr ( *m_pHWNDTree );
	ContCreate (SHWNDCr, SHWND) ( (HWND) p );
	}
	AddORHwnd();
	}
//---------------------------------------------------------------------------
	break;

	default:
	break;

	}	//Switch

//	return FALSE;	//weiterreichen
	return CTriasExtension :: Notification( iMsg,p);		// kein Fehler

}
//-------------------------------------------------------------------
// --------------------- Memberfunktionen ---------------------------
//-------------------------------------------------------------------
bool StatistExtension :: ObjektTest (void) 
{
//-----------------------Nur für uns --------------------------------
	if ( m_dON == ON_Default )
		return false;
	long *pONr = new long[2];
	*pONr = 1;
	{
	DataBaseObject DBO (MVWind(),SHOWDATABASEOBJECT, RF() );
	DBO.Show();
	if ( DBO.Result() == 1)	{	//ON
		*(pONr+1) = DBO.Object();
	} else
		return false;
	}
	if ( *(pONr+1) != 0L) {
//		short Flag = ROSortObjNr;
// KK010313
		short Flag = ROSortObjNr | ROForceNoCallback;
		CreateORWindow ( Flag, 350, 10, pONr, "Gesuchtes Objekt",0,255,255);
	}
	DELETE_OBJ ( pONr);

	return true;
}

//---------------------------------------------------------------------
Bool StatistExtension :: HideSightInfo (void) 
{

	if ( m_pIDC != NULL )
		DELETE_OBJ ( m_pIDC );

	if ( m_pGICLA != NULL )
		DELETE_OBJ ( m_pGICLA );

	if ( m_pOBJ != NULL )
		DELETE_OBJ ( m_pOBJ );

	if ( m_pClaObj != NULL )
		DELETE_OBJ ( m_pClaObj );

	if ( m_pIDM != NULL )
		DELETE_OBJ ( m_pIDM);

	m_ShowObjType = 0;

return TRUE;
}

Bool StatistExtension :: HideORHwnd (void) 
{

//	if ( m_pHWNDTree != NULL )
//		DELETE_OBJ ( m_pHWNDTree );

	if ( m_pHWNDTree != NULL && m_pHWNDTree->Count() > 0 ) {
		CTable t(*m_pHWNDTree);
		for ( t.First();t.Valid();t.Next())
			t.Delete();
	}

	m_isORHwnd = 0;
	m_ShowObjType = 0;

return TRUE;
}

//--------------------MemberFunktionen------------------------------------

void StatistExtension :: SetTreeInformation ( void )
{
	if ( m_pIDM != NULL )
		DELETE_OBJ ( m_pIDM);
	m_pIDM = new IDMTree;

	if ( m_pOBJ != NULL )
		DELETE_OBJ ( m_pOBJ);
	m_pOBJ = new OBJTree;
	return;
}
//-------------------------------------------------------------------------
//---------------------------Anzeigen Objclass-Fenster----------------
void StatistExtension :: ShowObjectClassInformation ( short Typ )
{
// Start DataBaseObjClass

	CEierUhr Wait ( MVWind());

char *pPText = new char [_MAX_PATH];
char *pOut = new char [_MAX_PATH];

	if ( pPText == NULL || pOut == NULL ) {
		DELETE_OBJ ( pPText );
		DELETE_OBJ ( pOut );
		return;
	}
	*pOut = '\0';
	*pPText = '\0';
pWindow pW;
	if ( isDataBase(Typ)) {
		strcat ( pOut , ResString( ResID(IDS_DBUEBERSICHT,&RF()),35));
		pW = MVWind();
	}
	if ( isGeometrieTyp(Typ) ) {
			// GeometrieKlasse
		PBDDATA pbdData;
		*pOut = '\0';
		memset (&pbdData, '\0', sizeof(PBDDATA));
		pbdData.dwSize = sizeof(PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = m_lRechKey;
		pbdData.pbdKText = pOut;
		pbdData.pbdKTextLen = MAXFCTNAME;
		pbdData.pbdLTextLen = 0;
		DEX_GetPBDData (pbdData);
		pW = ORWind(m_hWnd);
		*(pOut+MAXFCTNAME) = '\0';
	}

	if ( isObjContainer(Typ) ) {
		wsprintf ( pOut, ResString (ResID(IDS_OBJEKTCONTAINER,&RF()),80),m_lRechKey);
		pW = ORWind(m_hWnd);
	}
	if ( isObjRelation(Typ) ) {
		wsprintf ( pOut,ResString (ResID(IDS_OBJEKTTOPOLOGIE,&RF()),80) ,m_lRechKey);
		pW = ORWind(m_hWnd);
	}

	if ( isAttribut(Typ)  || isAttributSegment(Typ)  || isAttributWindow(Typ) ) {
//------	Sichtname
		pW = MVWind();

		pPText = DEX_GetActiveSight (pPText);

		if (*pPText == NULL ) {
			strcat ( pPText, ResString ( ResID( IDS_KEINEANSICHT,&RF()),50));
		}
		wsprintf ( pOut, pPText);

	}

	if ( isAttributSegment(Typ) ) {
		strcat ( pOut, ResString ( ResID(IDS_SICHTAUSSCHNITT,&RF()),50));
	}

	if ( isAttributWindow(Typ) ) {
		strcat ( pOut, ResString ( ResID(IDS_SICHTAUSSCHNITT,&RF()),50));
		pW = ORWind(m_hWnd);
	}

	if ( m_isBreak ) {
		strcat ( pOut, "- abgebrochen !");
		m_isBreak = FALSE;
	};

	if ( isGeometrieTyp(Typ) ) {
		DBClassification DBOC ( pW, SHOWOBJECTCLASSVIEW, RF(), m_pCTF, pOut, m_pGICLA, Typ, m_pOBJ);
		DBOC.Show();
		if ( DBOC.Result() == 0 || DBOC.Result() == 1)	{	//Abbrechen
			DELETE_OBJ ( pPText );
			DELETE_OBJ ( pOut );
			DELETE_OBJ ( m_pClaObj);
			return;
		}
//------------------------Objekte anzeigen-------------------------
		if ( DBOC.Result() == -1 ) {	// Anzeigen der Objekte
			m_lRechMkode = DBOC.GetMKode();
	//	Bits ( Zulässigkeit ) holen !!!
			m_ShowObjType = DBOC.GetShowObjTyp();
			DELETE_OBJ (  m_pClaObj);
			m_pClaObj = DBOC.GetObjListe();
			if ( DBOC.ShowMKWert() == FALSE )	// nur GI-Kurztext anzeigen
				m_lRechMkode = 0;
			DELETE_OBJ ( pPText );
			DELETE_OBJ ( pOut );
			return;
		}
	}
#if !defined(WIN32)
	m_isHuge = false;
#endif

	if ( m_pIDM->Count() == 0 )
		return;

	DBClassification DBOC ( pW, SHOWOBJECTCLASSVIEW, RF(), m_pCTF, pOut, m_pIDM, Typ, m_pOBJ);
	DBOC.Show();

	if ( DBOC.Result() == 0 || DBOC.Result() == 1)	{	//Abbrechen
		DELETE_OBJ ( pPText );
		DELETE_OBJ ( pOut );
		 return;
	}
//------------------------Objekte anzeigen-------------------------
	if ( DBOC.Result() == -1 ) {	// Anzeigen der Objekte
		m_lRechMkode = DBOC.GetMKode();
//	Bits ( Zulässigkeit ) holen !!!
		m_ShowObjType = DBOC.GetShowObjTyp();

#if !defined(WIN32)
		m_isHuge = DBOC.isHuge();
		if ( m_isHuge ) {
			m_pHUGE = DBOC.GetHugeObjListe();
		} else {
			m_pIDC = DBOC.GetObjListe();
		}
#else
		m_pIDC = DBOC.GetObjListe();
#endif

		long NumObj = DBOC.NumberObjects();
		if ( DBOC.ShowMKWert() == FALSE )	// nur ID-Kurztext anzeigen
			m_lRechMkode = 0;
	        m_iObjCount =  NumObj;
		m_dStartTime = timeGetTime();
		m_iRange = 0;
		if ( m_pInfo != NULL )
			DELETE_OBJ ( m_pInfo);

//-------------------------------------------------------------------

#if !defined(WIN32)
		if ( m_isHuge ) {	
		   if ( m_pHUGE != NULL ) {
//			short Flag = ROSortObjTyp;
//			short Flag = ROSortObjNr;
// KK010313
			short Flag = ROSortObjNr| ROForceNoCallback;
			char * pBuff = new char [50];
			if ( pBuff == NULL )
				return;
			*pBuff = '\0';
			strcat ( pBuff, ResString ( ResID(IDS_ORWINDOWTEXT,&RF()),50));
			short PX =10;
			short PY = 10;
			if ( isGeometrieTyp(Typ) )
				PX = 350;
			CreateORWindow ( Flag, PX, PY, m_pHUGE, pBuff,0,255,255);

			delete (long __huge *) m_pHUGE;
			DELETE_OBJ ( pBuff );
		   }
		} else {
		   if ( m_pIDC != NULL ) {
//			short Flag = ROSortObjTyp;
//			short Flag = ROSortObjNr;
// KK010313
			short Flag = ROSortObjNr| ROForceNoCallback;

			char * pBuff = new char [_MAX_PATH];
			if ( pBuff == NULL )
				return;
			*pBuff = '\0';
			strcat ( pBuff, ResString ( ResID(IDS_ORWINDOWTEXT,&RF()),50));
			short PX =10;
			short PY = 10;
			if ( isGeometrieTyp(Typ) )
				PX = 350;
			CreateORWindow ( Flag, PX, PY, m_pIDC, pBuff,0,255,255);
			DELETE_OBJ ( m_pIDC );
			DELETE_OBJ ( pBuff );
		   }
		}
#else
		if ( m_pIDC != NULL ) {
//			short Flag = ROSortObjTyp;
//			short Flag = ROSortObjNr;
// KK010313
			short Flag = ROSortObjNr| ROForceNoCallback;

			char * pBuff = new char [50];
			if ( pBuff == NULL )
				return;
			*pBuff = '\0';
			strcat ( pBuff, ResString ( ResID(IDS_ORWINDOWTEXT,&RF()),50));
			short PX =10;
			short PY = 10;
			if ( isGeometrieTyp(Typ) )
				PX = 350;
			CreateORWindow ( Flag, PX, PY, m_pIDC, pBuff,0,255,255);
			DELETE_OBJ ( m_pIDC );
			DELETE_OBJ ( pBuff );
		}
#endif
		m_lRechMkode = 0L;	//zurcksetzen		
	}
	DELETE_OBJ ( pPText );
	DELETE_OBJ ( pOut );
	return;	
}
//-------------------------------------------------------------------------
//------------------------------------------------------------------

Bool StatistExtension :: ShowClassification ( void )

{
	if ( m_pOBJ == NULL || m_pIDM == NULL )
		return FALSE;
	m_lRechMkode = 0;
	short OCL_Flag = FALSE;
	short OCL_Linie;
	long OCL_Einheit;
	{
	CEierUhr Wait ( MVWind());

		if ( m_pGICLA != NULL )
			DELETE_OBJ ( m_pGICLA );

		if ( m_pClaObj != NULL )
			DELETE_OBJ ( m_pClaObj );

		m_pGICLA = new GICLATree;

		if ( m_pGICLA == NULL )
			return FALSE;
		pWindow pW = ORWind( m_hWnd);
		ObjectClassification OCL (pW, GICLASSIFICATION, RF(), m_pIDM, m_pOBJ, m_pGICLA);
		Wait.Hide();
		OCL.Show();

				
		if ( OCL.Result() == 1 ) {	// Anzeigen der Objekte

			m_pClaObj = OCL.GetGIClassObjects();
			m_lRechKey = OCL.GetObjClass();
			SichtGeometrieKlasse();
			OCL_Flag = OCL.isClassification();
			OCL_Linie = OCL.isLinie();
			OCL_Einheit = OCL.GetEinheit(); 	
		} else
			DELETE_OBJ ( m_pClaObj);
	}
//-Korr 29.3.95
//			if ( OCL.isClassification() ) {		//Intervalle
	if ( OCL_Flag ) {		//Intervalle
		short Typ = ( short ) OKlGeometrieTyp;
		ShowObjectClassInformation( Typ);
	}
	if (m_pClaObj != NULL && *m_pClaObj > 0 ) {
		CEierUhr Wait ( MVWind());
			char *pBuf = new char [_MAX_PATH];
			if ( pBuf != NULL ) {
				*pBuf = '\0';
				m_pEinheit = new char [20];
				if ( m_pEinheit == NULL )
					return TRUE;
				*m_pEinheit = '\0';
				if ( OCL_Linie ) {
					strcat ( pBuf, ResString(ResID(IDS_LINIENKLASSE,&RF()),40));
					if ( OCL_Einheit == (long) KiloMeter ) {
						strcat ( pBuf, ResString ( ResID(IDT_UNITKM,&RF()),15));
						strcat ( m_pEinheit, ResString ( ResID(IDT_UNITKM,&RF()),15));
					} else {
						strcat ( pBuf, ResString ( ResID(IDT_UNITM,&RF()),15));
						strcat ( m_pEinheit, ResString ( ResID(IDT_UNITM,&RF()),15));
					}
					strcat ( pBuf, "  ");
				} else {
					strcat ( pBuf, ResString(ResID(IDS_FLAECHENKLASSE,&RF()),40));
					if ( OCL_Einheit == (long) QuadratKiloMeter ) {
						strcat ( pBuf, ResString ( ResID(IDT_UNITQKM,&RF()),15));
						strcat ( m_pEinheit, ResString ( ResID(IDT_UNITQKM,&RF()),15));
					}
					if ( OCL_Einheit == (long) QuadratMeter ) {
						strcat ( pBuf, ResString ( ResID(IDT_UNITQM,&RF()),15));
						strcat ( m_pEinheit, ResString ( ResID(IDT_UNITQM,&RF()),15));
					}
					if ( OCL_Einheit == (long) Hektar ) {
						strcat ( pBuf, ResString ( ResID(IDT_UNITHA,&RF()),15));
						strcat ( m_pEinheit, ResString ( ResID(IDT_UNITHA,&RF()),15));
					}
					strcat ( pBuf, "  ");
				}

//				short Flag = ROSortText;	
// KK010313
				short Flag = ROSortText| ROForceNoCallback;	

				CreateORWindow ( Flag, 350, 10, m_pClaObj, pBuf,100,255,255);
				DELETE_OBJ ( pBuf);
				DELETE_OBJ ( m_pEinheit);
			}
	}
		
	if ( m_isBreak )
		m_isBreak = FALSE;
	DELETE_OBJ ( m_pGICLA );
	DELETE_OBJ ( m_pClaObj);
	DELETE_OBJ ( m_pOBJ );
	
	return TRUE;
}

//------------------------------------------------------------------
void StatistExtension :: AddORHwnd (void) 
{

	if ( !m_pHWNDTree )
		m_isORHwnd = 0;
	else {
		if ( m_pHWNDTree->Count() == 0 )
			m_isORHwnd = 0;
		else
			m_isORHwnd++;
	}

return;
}

void StatistExtension :: DeleteORHwnd (void) 
{
	if ( m_pHWNDTree == NULL )
		m_isORHwnd = 0;
	else {
		if ( m_pHWNDTree->Count() == 0 )
			m_isORHwnd = 0;
		else
			m_isORHwnd--;
	}

	if ( m_isORHwnd <= 0 ) {
		HideORHwnd( );
	}
		
return;
}

void StatistExtension :: SichtInfo (void) 
{
	m_isSightInfo = OKlAttribut;		// Alle Objekte eines Identifikators
	m_ShowObjType = 0;

return;
}

void StatistExtension :: SichtAusschnitt ( short OKLTyp) 
{
	m_isSightInfo = OKLTyp;		// Objekte eines ID's im Segment
	m_ShowObjType = 0;

return;
}

void StatistExtension :: SichtGeometrieKlasse ( void )
{
	m_isSightInfo = OKlGeometrieTyp;
	m_ShowObjType = 0;
}

//-------------------------------------------------------------------

//---------------------------13.5.94------------------------------------
// -------Nur "gewnschte" Objekttypen in ObjFenster  -------------------
Bool StatistExtension :: GetObjectTypes ( LPARAM p )
{
	if ( m_ShowObjType == 0 ) return TRUE;

	long Onr = (( RECHOBJECT *)p)->lONr;

	short TstGiTyp = LogObjectType ( Onr );

	return TstGiTyp & m_ShowObjType;
}

//	ORFenster erstellen-----------------------------------------
void StatistExtension :: CreateORWindow ( short Flag, short PX, short PY, long *pObjL, char *pCaption, short RF, short GF, short BF)
{
	if ( *pObjL <= 0 )
		return;

	POINT PNT;
	PNT.x = PX;
	PNT.y = PY;


	CREATEOBJEKTINFOEX3 COI;
	memset ( &COI, '\0', sizeof (COI) );
	COI.dwSize = sizeof(COI);
	COI.lpCaption = pCaption;
#if !defined(WIN32)
	if ( m_isHuge && m_pHUGE ) {
		COI.plObjs = m_pHUGE+1;
		COI.iNumObjs = 0;
//		COI.iNumObjs = short( *m_pHUGE);
		COI.lNumObjs = *m_pHUGE;
	} else {
		COI.plObjs = pObjL+1;
		COI.lNumObjs = *pObjL;
		COI.iNumObjs = 0;
//		COI.iNumObjs = short( *pObjL);
	}
#else
	COI.plObjs = pObjL+1;
	COI.lNumObjs = *pObjL;
	COI.iNumObjs = 0;
//	COI.iNumObjs = short( *pObjL);
#endif
	COI.cMColor = RGB(RF,GF,BF);
	COI.pntPos = PNT;
	if ( Flag == -1 ) {
//		COI.m_iFlags = ROSortObjTyp;
// KK010313
		COI.m_iFlags = ROSortObjTyp| ROForceNoCallback ;
		COI.m_pCmpProc = ( CMPONRPROC ) CompareMinMax;
		COI.m_dwData = (DWORD ) m_pIDC;
	} else
		COI.m_iFlags = Flag|ROShowHidden;

//	RegisterNotification (DEX_CREATEOBJEKTINFO);
	RegisterNotification (DEX_QUERYRECHOBJECT);

	DEX_CreateObjektInfo( COI );

//	UnRegisterNotification (DEX_CREATEOBJEKTINFO);
	UnRegisterNotification (DEX_QUERYRECHOBJECT);


	if ( m_pInfo != NULL )
		DELETE_OBJ ( m_pInfo);
}


//-----------------NEUE MEMBER --------------------------------------------------
//Objekte eines Fensters in Baum sammeln
void StatistExtension :: GetFL_ObjectsFromORWindow ( Bool fGenerate, HWND hWnd )

{
	if ( m_pOBJ == NULL )
		return;
	long Count = 0L;
	m_iObjCount = 0;
	DEXOR_SelectedObjectsCount ( hWnd , &Count);
	m_iObjCount = Count;

	OBJPOINT OB;
	OB.pOBJ = m_pOBJ;
	OB.lRange = 0;
	OB.lCount = 0;
	OB.pCTF = m_pCTF;
	if ( m_pInfo != NULL )
		DELETE_OBJ ( m_pInfo);
	pWindow pW = ORWind( hWnd);
	char * pBuf = new char [_MAX_PATH];
	if ( pBuf == NULL ) 
		return ;
	m_isBreak = FALSE;
	*pBuf = '\0';
	wsprintf (pBuf, ResString( ResID( IDS_TIMERCAPTION,&RF()),50),m_iObjCount);
	m_pInfo = new IdentInformation ( pW, SHOWIDENTIFIKATOR, RF(),m_pIDM,pBuf,m_iObjCount);
	OB.pStatus = m_pInfo;
	m_pInfo->Show();
	m_pInfo->Update();
	DELETE_OBJ ( pBuf );

	ENUMLONGKEY ENL;
	if ( fGenerate )
		ENL.eFcn = ( ENUMLONGKEYPROC ) EnumFL_ObjectsWithAL;
	else
		ENL.eFcn = ( ENUMLONGKEYPROC ) Enum_ObjectsWithAL;

	ENL.eKey = (long ) (void *)hWnd;

//	ENL.ePtr = m_pOBJ;
	ENL.ePtr = &OB;
	DEX_EnumSelectedObjects (ENL);
	if ( OB.lCount == -1 )	{	// Abgebrochen
		m_isBreak = TRUE;
		HWND hwnd = m_pInfo->Handle();
		MessageBox ( hwnd ,
		 ResString ( ResID ( IDS_GICLASSSTOPWORK,&RF()),50), 
		 ResString ( ResID ( IDS_CREATEDBOBJECTS,&RF()),50), 
		 MB_OK|MB_ICONEXCLAMATION);
		DELETE_OBJ ( m_pInfo);
		return ;
	}
	DELETE_OBJ ( m_pInfo);

	return;

}
//-----------------------Alle-Fenster-------------------------------
void StatistExtension :: GetFL_ObjectsFromAllORWindow ( Bool fGenerate )

{
	if ( m_pOBJ == NULL )
		return;

	if ( !m_pHWNDTree || m_pHWNDTree->Count() == 0 ) 
		return ;

	CTable t(*m_pHWNDTree);

	for (t.First(); t.Valid() ; t.Next()  ) { 
		SHWNDLock l(t);
		m_hWnd = ( HWND ) l->Shwnd(); 
		GetFL_ObjectsFromORWindow ( fGenerate, HWND ( l->Shwnd()) );
		if ( m_isBreak)
			return;
	}
	return ;
}

//-------------------------------------------------------------------------
// Objektklassen aus Objekten in ORFenster bestimmen
void StatistExtension :: CreateObjClassFromObjects ( short Typ )
{
	if ( m_pOBJ == NULL )
		return;

	m_pOBJ->Optimize();

	ulong uCount = m_pOBJ->Count();

	if ( m_pIDM != NULL )
		DELETE_OBJ ( m_pIDM );
	m_pIDM = new IDMTree; 

	pWindow pW = GetRightpWindow(Typ);

	CTable t(*m_pOBJ);

	long NIDI = 0;
	m_isBreak = FALSE;

	long lRange =  uCount;
	if ( m_pInfo != NULL )
		DELETE_OBJ ( m_pInfo);

	char * pBuf = new char [_MAX_PATH];
	if ( pBuf == NULL ) 
		return;
	*pBuf = '\0';
	strcat ( pBuf , ResString (ResID(IDS_CREATEOBJCLASS,&RF()),50));
	m_pInfo = new IdentInformation ( pW, SHOWIDENTIFIKATOR, RF(),m_pIDM,pBuf,lRange);
	m_pInfo->Show();
	m_pInfo->Update();
	DELETE_OBJ ( pBuf);
	lRange = 0L;

	for ( t.First(); t.Valid(); t.Next() ) {

		OBJLock l(t);
		long ONr = l->Object();
		long Ident = l->Ident();
		short Typ = l->ObjectTyp();
		Bool Flag = TRUE;
		lRange++;
		CTable s(*m_pIDM);

		if ( !s.Find (&Ident) ) {
			IDGITYP InStr;
			SetZero ( &InStr );	
			InStr.lMCode = 0L;

			if ( Typ == OTPunkt || Typ == OTLinie || Typ == OTFlaeche || Typ == OTText ) {
				if ( Typ == OTPunkt )
					InStr.lPoint = 1;
				if ( Typ == OTLinie )
					InStr.lLine = 1;
				if ( Typ == OTFlaeche )
					InStr.lArea = 1;
				if ( Typ == OTText )
					InStr.lText = 1;
			} else
				InStr.lNoname = 1;

			InStr.lCount = InStr.lPoint 
					+ InStr.lLine 
					+ InStr.lArea 
					+ InStr.lText
					+ InStr.lNoname;

			InStr.iITyp = l->ObjectTyp();

			InStr.lYmax = l->LoHoch();
			InStr.lYmin = l->RuHoch();
			InStr.lXmin = l->LoRechts();
			InStr.lXmax = l->RuRechts();
			InStr.rArea= l->FlInhalt();
			InStr.rAreaMax= l->FlInhalt();
			InStr.rAreaMin= l->FlInhalt();
			InStr.rPolyLen = l->LinLaenge();
			InStr.rPolyLenMax = l->LinLaenge();
			InStr.rPolyLenMin = l->LinLaenge();

		  	OBJTree *pObj = new OBJTree;
			OBJPOINT OB;
			OB.pOBJ = pObj;
			OB.pCTF = m_pCTF;
			try {
				EnumObjectsWithAL ( ONr, Flag, &OB);
			} catch ( ... ){

				char * pONR = new char [_MAX_PATH];
				if ( pONR ) {
					*pONR = '\0';
					wsprintf (pONR, ResString( ResID( IDS_CATCHKLASSEN,&RF()),50),ONr);

					MessageBox ( 0,
						pONR,
						ResString ( ResID ( IDS_CATCHCAPTION,&RF()),60),
						MB_OK);
					DELETE_OBJ (pONR);
				}
				break;
			}
			InStr.pObj = pObj;
			IDMCreator IDMCr ( *m_pIDM );
		  	ContCreate ( IDMCr, IDM ) ( Ident, &InStr );
			m_pInfo->ModifyWindow(Ident);
			NIDI++;
			if ( m_pInfo->Break() ) {
				m_isBreak = TRUE;
				HWND hwnd = m_pInfo->Handle();
				MessageBox ( hwnd ,
				 ResString( ResID ( IDS_OCLSTOPWORK,&RF()),90), 
				 ResString ( ResID ( IDS_CREATEOBJCLASS,&RF()),60),
				 MB_OK|MB_ICONEXCLAMATION);
				break;
			}
		} else {
	
			IDMLock k(s);
	
			k->IdentGiTyp() = k->IdentGiTyp() | l->ObjectTyp();		// Gi-Typ sammeln

			if ( Typ == OTPunkt || Typ == OTLinie || Typ == OTFlaeche || Typ == OTText ) {
				if ( Typ == OTPunkt )
					k->Punkt() = k->Punkt() + 1;
				if ( Typ == OTLinie )
					k->Linie() = k->Linie() + 1;
				if ( Typ == OTFlaeche )
					k->Flaeche() = k->Flaeche() + 1;
				if ( Typ == OTText )
					k->Text() = k->Text() + 1;
			} else
				k->Sonstige() = k->Sonstige() + 1;

			k->Count() = k->Punkt() + k->Linie() 
				+ k->Flaeche() + k->Text() + k->Sonstige();
			k->FlInhalt() = k->FlInhalt() + l->FlInhalt();
			k->LinLaenge() = k->LinLaenge() + l->LinLaenge(); 

//---------------Blindheit 30.8.96------------------------------------
			if ( OTLinie == Typ ) {
				if ( k->rPolyLenMax() < l->LinLaenge() )
					k->rPolyLenMax() = l->LinLaenge();
				if ( k->rPolyLenMin() > l->LinLaenge())
					k->rPolyLenMin() = l->LinLaenge();
			}
//--------------------------------------------------------------------
			if ( OTFlaeche == Typ ) {
				if ( k->rAreaMax() < l->FlInhalt() )
					k->rAreaMax() = l->FlInhalt();
				if ( k->rAreaMin() > l->FlInhalt() )
					k->rAreaMin() = l->FlInhalt();
			}
//----------------Korrektur am 30.8.96--------------------------------

//----------------Container----------------------------------

			if ( l->RuHoch() < k->RuHoch() ) 
				k->LoHoch() = l->LoHoch();
			if ( l->LoRechts() < k->LoRechts() ) 
				k->LoRechts() = l->LoRechts();
//------------------Maxima-------------------------------------
			if ( l->LoHoch() > k->LoHoch() )
				k->RuHoch() = l->RuHoch();
			if ( l->RuRechts() > k->RuRechts() )
				k->RuRechts() = l->RuRechts();

			OBJTree *pObj = k->pObjects();
			OBJPOINT OB;
			OB.pOBJ = pObj;
			OB.pCTF = m_pCTF;

			try {
				EnumObjectsWithAL ( ONr, Flag, &OB);
			} catch ( ... ){
				char * pONR = new char [_MAX_PATH];
				if ( pONR ) {
					*pONR = '\0';
					wsprintf (pONR, ResString( ResID( IDS_CATCHDATEN,&RF()),50),ONr);

					MessageBox ( 0,
						pONR,
						 ResString ( ResID ( IDS_CATCHCAPTION,&RF()),60),
						MB_OK);
					DELETE_OBJ (pONR);
				}
				break;
			}
		}
		m_pInfo->SetPosition ( lRange);
	}
	m_pIDM->Optimize();
	DELETE_OBJ ( m_pInfo );

	return; 

}
//-----------------------------------------------------------------------
//Laden von ObjektKlassen und für Fenster aufbereiten
Bool StatistExtension :: BuildObjClassInfo ( short Typ)
{
	CEierUhr Wait ( MVWind());

//	Alle Objektklassen der Datenbank durchzählen und in Baum anlegen
	short NumId = AddObjectClassInTree (Typ, m_pIDM);
	m_lDBIdCount = (long) NumId;			
//--------------Info-Fenster
	if ( Typ == (short) OKlDataBase ) {
		Bool Flag =  ShowDataBaseInfo();	 // Result = OK
		if ( !Flag )
			return FALSE;	// Result = CANCEL
	}

	{	// Start IDI
		CTable t(*m_pIDM);
		pWindow pW = GetRightpWindow ( Typ);
		long Ident = 0;
		char *pCaption = new char [_MAX_PATH];
		if ( pCaption == NULL )
			return TRUE;

		wsprintf ( pCaption ,ResString (ResID(IDS_OBJCLASSCAPTION,&RF()),50),m_lDBIdCount);
		m_isBreak = FALSE;

		long lRange = m_lDBIdCount;	// ObjZahl aus Add..??
		if ( m_pInfo != NULL )
			DELETE_OBJ ( m_pInfo);
		m_pInfo = new IdentInformation ( pW, SHOWIDENTIFIKATOR, RF(),m_pIDM,pCaption,lRange);
		m_pInfo->Show();
		m_pInfo->Update();
		m_lDBIdCount = 0;
		short iCnt = 0;


		for (t.First(); t.Valid() ; t.Next()  ) {

			IDMLock l(t);
			Ident = l->Ident();
			if ( !l)
				continue;
			
			{
			DefineObjectClassInTree ( Typ, Ident, m_pIDM, m_pCTF);
			m_pInfo->ModifyWindow(Ident);
			iCnt++;
			m_pInfo->SetPosition( iCnt );
			m_lDBIdCount++;
			}

			if ( m_pInfo->Break() ) {
				m_isBreak = TRUE;
				HWND hwnd = m_pInfo->Handle();
				MessageBox ( hwnd ,
				 ResString( ResID( IDS_OCLSTOPWORK,&RF()),90), 
				 ResString( ResID ( IDS_OCLASSRECHERCHE,&RF()),60),
				 MB_OK|MB_ICONEXCLAMATION);
				break;
			}
		}
		m_pIDM->Optimize();
		DELETE_OBJ ( pCaption);
		DELETE_OBJ ( m_pInfo );

	}	// Ende IDI

	return TRUE;	

}
//---------------------------------------------------------------
//Laden von ObjektKlassen und für ContainerListe aufbereiten
Bool StatistExtension :: BuildObjClassContainer ( void )
{
	if ( m_pIDM == NULL )
		return FALSE;
	if ( m_pOCL != NULL )
		DELETE_OBJ ( m_pOCL );
	m_pOCL = new OBJCLList;
	if ( m_pOCL == NULL )
		return FALSE;

	CEierUhr Wait ( MVWind());

	CTable t(*m_pIDM);
	CRing r(*m_pOCL);
	long IdCounter = 0;	// Id-Zaehler
	for (t.First(); t.Valid() ; t.Next()  ) {
	   IdCounter++;
	   if ( IdCounter <= m_lDBIdCount  ) { // bei evtl. Abbruch
		IDMLock l(t);
		long Ident = l->Ident();
		short DevTyp = l->IdentGiTyp();

		PBDDATA pbdData;
		char KText[MAXFCTNAME+1];
		char GITyp[5];
		short GiTyp = 0;
		GITyp[0] = '\0';
		KText[0] = '\0';
		strcpy ( GITyp, "____");

		memset (&pbdData, '\0', sizeof(PBDDATA));

		pbdData.dwSize = sizeof(PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = Ident;
		pbdData.pbdKText = KText;
		pbdData.pbdKTextLen = sizeof(KText) -1;
		pbdData.pbdLTextLen = 0;
		DEX_GetPBDData (pbdData);

		char outBuff[TEXTLEN+20];
		if ( KText[0] == NULL )
			strcat ( KText , ResString( ResID(IDS_NODEFOBJCLASS,&RF()),50) );
		KText[MAXFCTNAME] = '\0';

//--------------Id in Sicht zugeordnete Gi-Typen
		GiTyp = OTPunkt;
		if ( (GiTyp & DevTyp) > 0) GITyp[0] = 'P';
		GiTyp = OTLinie;
		if ( (GiTyp & DevTyp) > 0) GITyp[1] = 'L';
		GiTyp = OTFlaeche;
		if ( (GiTyp & DevTyp) > 0) GITyp[2] = 'F';
		GiTyp = OTText;
		if ( (GiTyp & DevTyp) > 0) GITyp[3] = 'T';

		char NewIdent[MAX_OKS_LENX+1];

		for ( short i = 0; i < 4 ; i++ ) {
	 	   if ( GITyp[i] == 'L' || GITyp[i] == 'F' ) {

		ClassFromIdentX ( Ident, NewIdent);

		wsprintf (outBuff, "%s:%c:%s", NewIdent, GITyp[i], KText);

/*------22.1.97
			if ( DEX_GetIdBase() == 16 ) {
				wsprintf (outBuff, "%08lx:%c:%s", Ident, GITyp[i], KText);
			} else {
				wsprintf (outBuff, "%08ld:%c:%s", Ident, GITyp[i], KText);
			}
--------------*/
			OBJCLCreator OBJCLCr ( *m_pOCL );
			ContCreate ( OBJCLCr, OBJCL ) ( TRUE, Ident,outBuff );
		   }
		}
	   } // Id-Counter
	   if ( m_isBreak )
		m_isBreak = FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------
// Richtigen Pointer für Fenster finden
pWindow StatistExtension :: GetRightpWindow ( short Typ )
{
pWindow pW;
	if ( isDataBase(Typ)) {
		pW = MVWind();
	}
	if ( isGeometrieTyp(Typ) ) {
		pW = ORWind(m_hWnd);
	}

	if ( isObjContainer(Typ) ) {
		pW = ORWind(m_hWnd);
	}
	if ( isObjRelation(Typ) ) {
		pW = ORWind(m_hWnd);
	}

	if ( isAttribut(Typ) || isAttributSegment(Typ) ) {
		pW = MVWind();
	}

	if ( isAttributWindow(Typ) ) {
		pW = ORWind(m_hWnd);
	}

	if ( isObjParameter(Typ) ) {
		pW = MVWind();
	}
	return pW;
}
//---------------------------------------------------------------
// Datenbankübersicht anzeigen
Bool StatistExtension :: ShowDataBaseInfo ( void )

{	//Start DBI
	DataBaseInformation DBI ( MVWind(), SHOWDATABASE, RF(), m_pIDM);
	DBI.Show();
			
	if ( DBI.Result() == 0)		//Abbrechen
		return FALSE;
			
	if ( DBI.Result() == 1)	//weitere Informationen
		return TRUE;
	return FALSE;
}

//---------------------Mittelwert / Medianwert---------------------------
char *StatistExtension :: MittelWert ( void )
{

	if (m_pOBJ == NULL )
		return NULL;
	m_pOBJ->Optimize();

double *pMWert;
				
double	MWFlaeche,MWLinie;

	pMWert = MittelWertBerechnung ( m_pOBJ);
	if ( pMWert == NULL)
		return NULL;
	if ( *pMWert == -1 && *(pMWert+1) == -1 ) {
		DELETE_OBJ ( pMWert);
		return NULL;     
	}

	MWFlaeche = *pMWert;
	MWLinie = *(pMWert+1);
	DELETE_OBJ ( pMWert);
	char *pBuf = WerteInBuffer ( &MWFlaeche, &MWLinie);
	return pBuf;
}
//-------------------------------------------------------------------

//----------------------------------MEDIANWERT------------------------
//------------------------------------------------------------------------
char *StatistExtension :: MedianWert ( void )
{

	if ( m_pOBJ == NULL )
		return NULL;

	if ( m_iObjCount == 0 )
		return NULL;
	m_pOBJ->Optimize();

double *pMWert;
				
double	MWFlaeche,MWLinie;

	pMWert = MedianWertBestimmung ( m_iObjCount, m_pOBJ);
	if ( pMWert == NULL)
		return NULL;
	if ( *pMWert == -1 && *(pMWert+1) == -1 ) {
		DELETE_OBJ ( pMWert);
		return NULL;     
	}

	MWFlaeche = *pMWert;
	MWLinie = *(pMWert+1);
	DELETE_OBJ ( pMWert);
	char *pBuf = WerteInBuffer ( &MWFlaeche, &MWLinie);
	return pBuf;
}
//------------------------------------------------------------------------
void  SetObjZero ( struct OBJECTTYP *p )
{
	if ( p == NULL ) return;
	p->lIdent = 0L;
	p->lMCode = 0L;
	p->lIntervall = 0L;
	p->iGITyp=0;
	p->lXmin=MAXKOORD;
	p->lXmax=0L;
	p->lYmin=MAXKOORD;
	p->lYmax=0L;
	p->rPolyLen=0.0;
	p->rArea=0.0;

}
//------------------------------------------------------------------------
void  SetGIKlassZero ( struct GICLASS *p )
{
	if ( p == NULL ) return;
	p->lGroupNr=0;
	p->lEinheit=0;
	p->lOperate1=0;
	p->lOperate2=0;
	p->iGiTyp=0;
	p->lCount=0;
	p->lXmin=MAXKOORD;
	p->lXmax=0L;
	p->lYmin=MAXKOORD;
	p->lYmax=0L;
	p->rVglWert1=0.0;
	p->rVglWert2=0.0;
	p->rKumul=0.0;
	p->rKumulMin=MaxDouble;
	p->rKumulMax=0.0;
	p->pObj = NULL;
}

//---------------------------------------------------------------------------
/*__________________________________________________________________________
short GetObjectsInHwndType ( HWND hWnd )
{
short Type = 0;

	ENUMLONGKEY ENL;
	ENL.eFcn = ( ENUMLONGKEYPROC ) SetObjectsType;

	ENL.eKey = (long ) (void *)hWnd;

	ENL.ePtr = &Type;
	DEX_EnumSelectedObjects (ENL);

	return Type;
}
----------------------------------------------*/
//------------------------------------------------------
//---------------------------------------------------------------------------
//----------------QuickSort------------------------------------------
void QuickSort ( double *pWERT, long *pON, short l, short r )
{

short i,j;
double wert;
long onr;     
	if ( r > l +1 ) {
		for ( j = l +1 ; j < r ; j++ ) {
		   for ( i = j ; i < r ; i++ ) {
			if ( *(pWERT+j-1) > *(pWERT +i) ) {
				wert = *(pWERT+j-1);
				onr = *(pON+j-1);
				*(pWERT+j-1) = *(pWERT+i);
				*(pON+j-1) = *(pON+i);
				*(pWERT+i) = wert;
				*(pON+i) = onr;
			}
		   }
		}

	}
}

//------------------------------------------------------

//------------------------------------------------------

//------------------------NEUE NICHTMEMBER ----------------------------

//-----------IDM-Baum aufbauen-----------------------------------------------
//-----------------------------------------------------------------
short AddObjectClassInTree ( short Typ, IDMTree *pIDM )
{
//--------------------Identifikatoren-----------------------------------------
	if ( pIDM == NULL )
		pIDM = new IDMTree;
	short Num = 0;

	IDPOINT ID;
	ID.pID = pIDM;
	ID.Number = 0L;

	if ( Typ == (short ) OKlDataBase ) {
		ENUMNOKEYLONG ENL;
//	Alle O'Klassen der DB formal durchzählen und Baum anlegen
		ENL.eFcn = ( ENUMNOKEYLONGPROC) NumerateIdents;
		ENL.ePtr = &ID;
		DEX_EnumIdents(ENL);
	} else {
//	Alle O'Klassen der Sicht formal durchzählen und Baum anlegen
		ENUMTEXTKEY ENT;
		ENT.eKey = NULL;	// NULL = aktuelle Sicht
//	Bestimmen der Anzahl der Objektklassen
		ENT.eFcn = ( ENUMTEXTKEYPROC) NumerateIdents;
		ENT.ePtr = &ID;
		DEX_EnumSightIdents(ENT);
	}
	Num = (short)ID.Number;
	return Num;
}
//--------------------------------------------------------------------
//-----IDM-Baum mit P,L,F,T und Sonstige,GiTyp pro Ident untersetzen -----------------------------------------------
//-----------------------------------------------------------------
//-------------------------------------------------------------------
void DefineObjectClassInTree (short Typ, long Ident , IDMTree * pIDM , CoordTransX *pCTF)
{
	if ( pIDM == NULL || pCTF == NULL)
		return;

	IDGITYP InStr;

	ENUMLONGKEY ELK;

	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) NumerateObjects;
	Bool DelFlag = FALSE;

	if ( Typ == ( short ) OKlParameter )
		ELK.eFcn = ( ENUMLONGKEYPROC) EnumFLObjectsWithAL;

	{

	CTable t(*pIDM);

	DelFlag = FALSE;
	ELK.eKey = Ident;
	SetZero ( &InStr );	
	InStr.lMCode = 0L;

	ELK.ePtr = &InStr;


	if ( t.Find ( &Ident )) {

		if ( Typ == (short) OKlParameter ) {
			InStr.iITyp = DEX_GetIdentObjTypesActView( Ident);
			if ( (InStr.iITyp & OTFlaeche) == 0 &&
				(InStr.iITyp & OTLinie) == 0 )  {
			//	t.Delete();
				return;
			}
		}

//	   {
		IDMLock l(t);

		if ( Typ == (short) OKlDataBase ) 
			InStr.iITyp = DEX_GetIdentObjTypes( Ident);
		if ( Typ == (short) OKlAttribut ) 
			InStr.iITyp = DEX_GetIdentObjTypesActView( Ident);
		if ( Typ == (short) OKlParameter ) {
			InStr.iITyp = DEX_GetIdentObjTypesActView( Ident);
			if ( (InStr.iITyp & OTFlaeche) == 0 &&
				(InStr.iITyp & OTLinie) == 0 )  {
				DelFlag = TRUE;
			} else {

				OBJTree *pOBJ = new OBJTree;
				if ( pOBJ == NULL )
					return;
				OBJPOINT OP;
				OP.pOBJ = pOBJ;
				OP.pCTF = pCTF;
				ELK.ePtr = &OP;
				DEX_EnumIdentObjects(ELK);


				l->StoreObjTree ( pOBJ);

				{
				CTable s(*pOBJ);
	
				IDGITYP Kstr;
				IDGITYP Estr;
				SetZero (&Kstr);

				for ( s.First(); s.Valid(); s.Next() ) {
					OBJLock k(s);
					SetZero(&Estr);
					Estr.rArea =  k->FlInhalt();
					Estr.rPolyLen =  k->LinLaenge();
					Estr.rAreaMin =  k->FlInhalt();
					Estr.rPolyLenMin =  k->LinLaenge();
					Estr.rAreaMax =  k->FlInhalt();
					Estr.rPolyLenMax =  k->LinLaenge();

					Estr.lYmax = k->LoHoch();
					Estr.lXmin = k->LoRechts();
					Estr.lYmin = k->RuHoch();
					Estr.lXmax = k->RuRechts();

					CumulateObjects( &Kstr,&Estr);

					if ( k->ObjectTyp() == OTFlaeche )
						l->Flaeche() = l->Flaeche() + 1;
					if ( k->ObjectTyp() == OTLinie )
						l->Linie() = l->Linie() + 1;
				}
				

				l->StoreObjParam(&Kstr);
				}

			}	// Ende OKlParameter
		} else {
//-----------------------------andere-----------------------------
			DEX_EnumIdentObjects(ELK);
			l->Punkt() = InStr.lPoint;
			l->Linie() = InStr.lLine;
			l->Flaeche() = InStr.lArea;
			l->Text() = InStr.lText;
			l->Sonstige() = InStr.lNoname;

			short TTyp = 0;
			if ( InStr.lPoint )
				TTyp = TTyp | OTPunkt;
			if ( InStr.lLine )
				TTyp = TTyp | OTLinie;
			if ( InStr.lArea )
				TTyp = TTyp | OTFlaeche;
			if ( InStr.lText )
				TTyp = TTyp | OTText;
			if ( InStr.lComplex )
				TTyp = TTyp | OTKO;

			InStr.iITyp = InStr.iITyp & TTyp;		// Gi-Typ-Abgleich
			l->IdentGiTyp() = InStr.iITyp;
		}
		
	  // }
//	   if (DelFlag)
//		t.Delete();
	}
	}
	return;
}


//-----------Minimum/Maximum aus ObjektBaum
//		Minimum/Maximum
long * GetExtremum ( void *pOBJ )
{
	if ( pOBJ == NULL )
		return NULL;
	((OBJTree *)pOBJ)->Optimize();

	long MinMax[4];
//----Flaechen-----------
	MinMax[0] = -1;
	MinMax[1] = -1;
//----Linien-------------
	MinMax[2] = -1;
	MinMax[3] = -1;
	double MinFL=0.0,MaxFL=0.0,MinL=0.0,MaxL=0.0;
//-------------------------Flaechen----------------------------------
	CTable t(*(OBJTree*)pOBJ);
	for ( t.First(); t.Valid(); t.Next() ) {
	    OBJLock l(t);
	    long ONr = l->Object();
	    short Typ = l->ObjectTyp();
	    if ( Typ == OTFlaeche ) {
		double FL = l->FlInhalt();
		if ( FL > 0.0 ) {
			if ( MinMax[0] == -1 ) {
				MinFL = FL;
				MaxFL = FL;
				MinMax[0] = ONr;
				MinMax[1] = ONr;
			} else {
				if ( FL > MaxFL ){
					 MaxFL = FL;
					 MinMax[1] = ONr;
				}
				if ( FL < MinFL ){
					 MinFL = FL;
					 MinMax[0] = ONr;
				}
			}
		}
	    } else {	// OTLINIE
		    if ( Typ == OTLinie ) {

//-----------------------Linien-------------------------------
			double FL = l->LinLaenge();
			if ( FL > 0.0 ) {
				if ( MinMax[2] == -1 ) {
					MinL = FL;
					MaxL = FL;
					MinMax[2] = ONr;
					MinMax[3] = ONr;
				} else {
					if ( FL > MaxL ){
						 MaxL = FL;
						 MinMax[3] = ONr;
					}
					if ( FL < MinL ){
						 MinL = FL;
						 MinMax[2] = ONr;
					}
				}
			}

		    }	// OT_LINIE
	    }
	}
//------------------------------------------------------------------			
	long *pMinMax = new long [5];    
	if (pMinMax == NULL )
		return NULL;  
	long Number = 0;

	for ( long i = 0; i < 4; i++) {
		if ( MinMax[i] > 0 ) {
			*(pMinMax+1+Number) = MinMax[i];
			Number++;
		}
	}

	if ( Number == 0 ) {
		DELETE_OBJ ( pMinMax );
		return NULL;
	}

	*pMinMax = Number;
	return pMinMax;
}
//--------------------------------------------------------------------
//Kumulieren von Objektinformationen
//------------------------------------------------------------------
void CumulateObjects ( struct IDGITYP *s , struct IDGITYP *p)
{
	if ( s == NULL || p == NULL ) return;

	s->lPoint = s->lPoint + p->lPoint;
	s->lLine = s->lLine + p->lLine;
	s->lArea = s->lArea + p->lArea;
	s->lText = s->lText + p->lText;
	s->lComplex = s->lComplex + p->lComplex;
	s->lNoname = s->lNoname + p->lNoname;

	s->iITyp = s->iITyp | p->iITyp;

	s->rArea = s->rArea + p->rArea;
	s->rPolyLen = s->rPolyLen + p->rPolyLen; 

//---------------Extrema------------------------------------

	if ( p->rPolyLenMax > 0.0 ) {
		if ( s->rPolyLenMax < p->rPolyLenMax )
			s->rPolyLenMax = p->rPolyLenMax;
	}

	if ( p->rPolyLenMin > 0.0 ) {
		if ( s->rPolyLenMin > p->rPolyLenMin)
			s->rPolyLenMin = p->rPolyLenMin;
	}

	if ( p->rAreaMax > 0.0 ) {
		if ( s->rAreaMax < p->rAreaMax )
			s->rAreaMax = p->rAreaMax;
	}	

	if ( p->rAreaMin > 0.0 ) {
		if ( s->rAreaMin > p->rAreaMin)
			s->rAreaMin = p->rAreaMin;
	}

//----------------Container----------------------------------

	if ( s->lYmin > p->lYmin ) 
		s->lYmin = p->lYmin;
	if ( s->lXmin >  p->lXmin ) 
		s->lXmin = p->lXmin;
	if ( s->lYmax < p->lYmax )
		s->lYmax = p->lYmax;
	if ( s->lXmax < p->lXmax )
		s->lXmax = p->lXmax;

	return ;
}
//---------------------------------------------------------------------

//------------------ObjektKlassenArten------------------------------------
Bool isAttribut ( short Typ ) 
{
	if ( Typ == OKlAttribut )
		return TRUE;
	else
		return FALSE;
}

Bool isAttributSegment ( short Typ ) 
{
	if ( Typ == OKlAttributSegment )
		return TRUE;
	else
		return FALSE;
}

Bool isAttributWindow ( short Typ ) 
{
	if ( Typ == OKlAttributWindow )
		return TRUE;
	else
		return FALSE;
}

Bool isObjParameter ( short Typ ) 
{
	if ( Typ == OKlParameter )
		return TRUE;
	else
		return FALSE;
}

Bool isObjContainer ( short Typ ) 
{
	if ( Typ == OKlObjectContainer )
		return TRUE;
	else
		return FALSE;
}

Bool isObjRelation ( short Typ ) 
{
	if ( Typ == OKlObjectRelation )
		return TRUE;
	else
		return FALSE;
}

Bool isDataBase ( short Typ ) 
{
	if ( Typ == OKlDataBase )
		return TRUE;
	else
		return FALSE;
}

Bool isGeometrieTyp ( short Typ ) 
{
	if ( Typ == OKlGeometrieTyp )
		return TRUE;
	else
		return FALSE;
}

//---------------------------------------------------------------------
//Globale Enumerationsfunktionen

//-------------------Anzahl der Objekte in einem Container----------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT EnumFL_ObjectsWithAL ( long ONr, BOOL , void *pData)
  {

	CTable t( * ((OBJPOINT * ) pData)->pOBJ );
	class IdentInformation  *pInfo = ((OBJPOINT *)pData)->pStatus;
	class CoordTransX  *pCTF = ((OBJPOINT *)pData)->pCTF;
	DWORD dCTF = (DWORD)pCTF;

	((OBJPOINT *)pData)->lRange++;
   	long lRange = ((OBJPOINT *)pData)->lRange;
	if ( pInfo->Break() ) {
		((OBJPOINT *)pData)->lCount = -1;
	   	return FALSE;
	}

	short Type = DEX_GetObjectType(ONr);
//	Nur Linien und Flaechen
	if ( Type == OGLinie || Type == OGFlaeche ) {
	   if ( !t.Find (&ONr) ) {
		IDGITYP InStr;
		OBJECTTYP ObjStr;
		SetZero ( &InStr );	
		InStr.lMCode = 0L;
		SetObjZero ( &ObjStr );
		InStr.iITyp = OTPunkt | OTLinie | OTFlaeche | OTText | OTKO;
		Bool Flag = true;
		GetIdentsDate ( ONr, Flag, dCTF, &InStr );
		ObjStr.lIdent = DEX_GetObjIdent ( ONr );
		ObjStr.iGITyp =LogObjectType ( ONr );
		ObjStr.lXmin = InStr.lXmin;
		ObjStr.lXmax = InStr.lXmax;
		ObjStr.lYmin = InStr.lYmin;
		ObjStr.lYmax = InStr.lYmax;
		ObjStr.rPolyLen = InStr.rPolyLen;
		ObjStr.rArea = InStr.rArea;
	
		OBJCreator OBJCr (  * ((OBJPOINT * )pData)->pOBJ );
		ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
		pInfo->SetObjectText( (short)lRange );
		pInfo->SetPosition( (short) lRange );
	   }
	}
	return TRUE;
  }
//---------------------------------------------------------------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT EnumFLObjectsWithAL ( long ONr, BOOL , void *pData)
  {

	short Type = DEX_GetObjectType(ONr);
//	Nur Linien und Flaechen
	if ( Type == OGLinie || Type == OGFlaeche ) {
		CTable t( * ((OBJPOINT * ) pData)->pOBJ );
		class CoordTransX  *pCTF = ((OBJPOINT *)pData)->pCTF;
		DWORD dCTF = (DWORD)pCTF;

	   if ( !t.Find (&ONr) ) {
		IDGITYP InStr;
		OBJECTTYP ObjStr;
		SetZero ( &InStr );	
		InStr.lMCode = 0L;
		SetObjZero ( &ObjStr );
		InStr.iITyp = OTPunkt | OTLinie | OTFlaeche | OTText | OTKO;
		Bool Flag = true;
		GetIdentsDate ( ONr, Flag, dCTF, &InStr );
		ObjStr.lIdent = DEX_GetObjIdent ( ONr );
		ObjStr.iGITyp =LogObjectType ( ONr );
		ObjStr.lXmin = InStr.lXmin;
		ObjStr.lXmax = InStr.lXmax;
		ObjStr.lYmin = InStr.lYmin;
		ObjStr.lYmax = InStr.lYmax;
		ObjStr.rPolyLen = InStr.rPolyLen;
		ObjStr.rArea = InStr.rArea;
	
		OBJCreator OBJCr ( *((OBJPOINT * )pData)->pOBJ );
		ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
	   }
	}
	return TRUE;
  }
//---------------------------------------------------------------------------

//-------------------Anzahl der Objekte in einem Container----------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT CompareMinMax ( long ONr1, long ONr2 ,DWORD dwData)
  {
	long MinF =*( ( long *) dwData+1);
	long MaxF = *( (long *) dwData+2);
	long MinL =*( ( long *) dwData+3);
	long MaxL = *( (long *) dwData+4);

	if ( ONr1 == MinF ) 
		return -1;

	if ( ONr1 == MaxF ) {
		if ( ONr2 == MinF )
			return 1;
		else 
			return -1; 
	}

	if ( ONr1 == MinL ) {
		if ( ONr2 == MaxL)
			return -1;
		else 
			return 1; 
	}

	if ( ONr1 == MaxL ) 
		return 1; 
	return 0;		
  }

//-------------------Anzahl der Objekte in einem Container----------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT EnumObjectsWithAL ( long ONr, BOOL , void *pData)
  {


	   CTable t( * ((OBJPOINT * ) pData)->pOBJ );
	   class CoordTransX  *pCTF = ((OBJPOINT *)pData)->pCTF;
	   DWORD dCTF = (DWORD)pCTF;

	   if ( !t.Find (&ONr) ) {
			IDGITYP InStr;
			OBJECTTYP ObjStr;
			SetZero ( &InStr );	
			InStr.lMCode = 0L;
			SetObjZero ( &ObjStr );
			InStr.iITyp = OTPunkt | OTLinie | OTFlaeche | OTText | OTKO;
			Bool Flag = true;
			GetIdentsDate ( ONr, Flag, dCTF, &InStr );
			ObjStr.lIdent = DEX_GetObjIdent ( ONr );
			ObjStr.iGITyp =LogObjectType ( ONr );
			ObjStr.lXmin = InStr.lXmin;
			ObjStr.lXmax = InStr.lXmax;
			ObjStr.lYmin = InStr.lYmin;
			ObjStr.lYmax = InStr.lYmax;
			ObjStr.rPolyLen = InStr.rPolyLen;
			ObjStr.rArea = InStr.rArea;
	
			OBJCreator OBJCr ( *((OBJPOINT * )pData)->pOBJ );
			ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
	   }
	return TRUE;
  }
extern "C"  BOOL PASCAL _XTENSN_EXPORT Enum_ObjectsWithAL ( long ONr, BOOL , void *pData)
  {

	CTable t( * ((OBJPOINT * ) pData)->pOBJ );
	class IdentInformation  *pInfo = ((OBJPOINT *)pData)->pStatus;
	class CoordTransX  *pCTF = ((OBJPOINT *)pData)->pCTF;
	DWORD dCTF = (DWORD)pCTF;

	((OBJPOINT *)pData)->lRange++;
   	long lRange = ((OBJPOINT *)pData)->lRange;
	if ( pInfo->Break() ) {
		((OBJPOINT *)pData)->lCount = -1;
	   	return FALSE;
	}
//	   CTable t(*( OBJTree * )pData);
	   if ( !t.Find (&ONr) ) {
			IDGITYP InStr;
			OBJECTTYP ObjStr;
			SetZero ( &InStr );	
			InStr.lMCode = 0L;
			SetObjZero ( &ObjStr );
			InStr.iITyp = OTPunkt | OTLinie | OTFlaeche | OTText | OTKO;
			Bool Flag = true;
			GetIdentsDate ( ONr, Flag, dCTF, &InStr );
			ObjStr.lIdent = DEX_GetObjIdent ( ONr );
			ObjStr.iGITyp =LogObjectType ( ONr );
			ObjStr.lXmin = InStr.lXmin;
			ObjStr.lXmax = InStr.lXmax;
			ObjStr.lYmin = InStr.lYmin;
			ObjStr.lYmax = InStr.lYmax;
			ObjStr.rPolyLen = InStr.rPolyLen;
			ObjStr.rArea = InStr.rArea;
	
			OBJCreator OBJCr ( *((OBJPOINT * )pData)->pOBJ );
			ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
			pInfo->SetObjectText ( (short)lRange );
			pInfo->SetPosition ((short)lRange);
	   }
	return TRUE;
  }

//-------------------Anzahl der Objekte entsprechend vorgeg. GiTyp----------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT EnumObjectsWithTyp ( long ONr, BOOL , void *pData)
  {


	CTable t( * ((OBJPOINT * ) pData)->pOBJ );
	class IdentInformation  *pInfo = ((OBJPOINT *)pData)->pStatus;
	class CoordTransX  *pCTF = ((OBJPOINT *)pData)->pCTF;
	DWORD dCTF = (DWORD)pCTF;

	((OBJPOINT *)pData)->lRange++;
   	long lRange = ((OBJPOINT *)pData)->lRange;
//	pInfo->SetText ( iRange );
	if ( pInfo->Break() ) {
		((OBJPOINT *)pData)->lCount = -1;
	   	return FALSE;
	}
	if ( !t.Find (&ONr) ) {
		IDGITYP InStr;
		OBJECTTYP ObjStr;
		SetZero ( &InStr );	
		InStr.lMCode = 0L;
		SetObjZero ( &ObjStr );
		InStr.iITyp =  ((OBJPOINT *)pData)->GiTyp;
		Bool Flag = true;
		ObjStr.lIdent = DEX_GetObjIdent ( ONr );
		ObjStr.iGITyp =LogObjectType ( ONr );
		if ( (InStr.iITyp & ObjStr.iGITyp) == 0 ) 
			return TRUE;
		GetIdentsDate ( ONr, Flag, dCTF, &InStr );
		ObjStr.lXmin = InStr.lXmin;
		ObjStr.lXmax = InStr.lXmax;
		ObjStr.lYmin = InStr.lYmin;
		ObjStr.lYmax = InStr.lYmax;
		ObjStr.rPolyLen = InStr.rPolyLen;
		ObjStr.rArea = InStr.rArea;
		
		OBJCreator OBJCr ( * ((OBJPOINT * )pData)->pOBJ );
		ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
		pInfo->SetPosition( (short)lRange );

	}
	return TRUE;
  }
//-------------------Anzahl der Objekte entsprechend vorgeg. GiTyp----------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT EnumOnlyObjects ( long ONr, BOOL , void *pData)
  {
	CTable t( * ((OBJPOINT * ) pData)->pOBJ );
	class IdentInformation  *pInfo = ((OBJPOINT *)pData)->pStatus;
	class CoordTransX  *pCTF = ((OBJPOINT *)pData)->pCTF;
	DWORD dCTF = (DWORD)pCTF;

	((OBJPOINT *)pData)->lRange++;
   	long lRange = ((OBJPOINT *)pData)->lRange;
	if ( pInfo->Break() ) {
		((OBJPOINT *)pData)->lCount = -1;
	   	return FALSE;
	}
	if ( !t.Find (&ONr) ) {
		IDGITYP InStr;
		OBJECTTYP ObjStr;
		SetZero ( &InStr );	
		InStr.lMCode = 0L;
		SetObjZero ( &ObjStr );
		InStr.iITyp =  ((OBJPOINT *)pData)->GiTyp;
		Bool Flag = true;
		ObjStr.lIdent = DEX_GetObjIdent ( ONr );
		ObjStr.iGITyp =LogObjectType ( ONr );
		if ( (InStr.iITyp & ObjStr.iGITyp) == 0 ) 
			return TRUE;
		GetObjIdent ( ONr, Flag, dCTF, &InStr );
		
		OBJCreator OBJCr ( * ((OBJPOINT * )pData)->pOBJ );
		ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
		pInfo->SetPosition( (short)lRange );

	}
	return TRUE;
  }
///////////////////////////////////////////////////////////////////////////////
//-------------------Anzahl der Objekte in einem Container ( + Statusfenster)----------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT EnumObjectsWithStatus ( long ONr, BOOL , void *pData)
  {

	   CTable t( * ((OBJPOINT * ) pData)->pOBJ );
	   class IdentInformation  *pInfo = ((OBJPOINT *)pData)->pStatus;
	   class CoordTransX  *pCTF = ((OBJPOINT *)pData)->pCTF;
	   DWORD dCTF = (DWORD)pCTF;

	   ((OBJPOINT *)pData)->lRange++;
	   ((OBJPOINT *)pData)->lCount++;
   	   long lCount = ((OBJPOINT *)pData)->lCount;
	   if ( lCount == 1 )
		pInfo->Enable();

	   pInfo->SetText ( (short)lCount );

	   if ( pInfo->Break() ) {
	   	((OBJPOINT *)pData)->lCount = -1;
	   	return FALSE;
	   }
	   long lRange = ((OBJPOINT *)pData)->lRange;
	   if ( lRange > 100 ) {
		lRange = 1;
		((OBJPOINT *)pData)->lRange = lRange;
	   }
	   if ( !t.Find (&ONr) ) {
			IDGITYP InStr;
			OBJECTTYP ObjStr;
			SetZero ( &InStr );	
			InStr.lMCode = 0L;
			SetObjZero ( &ObjStr );
			InStr.iITyp = OTPunkt | OTLinie | OTFlaeche | OTText | OTKO;
			Bool Flag = true;
			GetIdentsDate ( ONr, Flag, dCTF, &InStr );
			ObjStr.lIdent = DEX_GetObjIdent ( ONr );
			ObjStr.iGITyp =LogObjectType ( ONr );
			ObjStr.lXmin = InStr.lXmin;
			ObjStr.lXmax = InStr.lXmax;
			ObjStr.lYmin = InStr.lYmin;
			ObjStr.lYmax = InStr.lYmax;
			ObjStr.rPolyLen = InStr.rPolyLen;
			ObjStr.rArea = InStr.rArea;
	
			OBJCreator OBJCr ( * ((OBJPOINT * )pData)->pOBJ );
			ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
			pInfo->SetPosition( (short)lRange );
	   }
	return TRUE;
  }
///////////////////////////////////////////////////////////////////////////////
//-------------------Anzahl der Objekte in einem Container ( + Statusfenster)----------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT EnumObjectsWithTopo ( long ONr, BOOL , void *pData)
  {


	   CTable t( * ((OBJPOINT * ) pData)->pOBJ );

	IExtendTopRel2 *m_pTop =  ((OBJPOINT *)pData)->m_pTop;
   	   long ONF = ((OBJPOINT *)pData)->lBezObj;

	   class IdentInformation  *pInfo = ((OBJPOINT *)pData)->pStatus;
	   class CoordTransX  *pCTF = ((OBJPOINT *)pData)->pCTF;
	   DWORD dCTF = (DWORD)pCTF;

	   ((OBJPOINT *)pData)->lRange++;
	   ((OBJPOINT *)pData)->lCount++;
   	   long lCount = ((OBJPOINT *)pData)->lCount;
	   if ( lCount == 1 )
		pInfo->Enable();

	   pInfo->SetText ( lCount );

	   if ( pInfo->Break() ) {
	   	((OBJPOINT *)pData)->lCount = -1;
	   	return FALSE;
	   }
	   long lRange = ((OBJPOINT *)pData)->lRange;
	   if ( lRange > 100 ) {
		lRange = 1;
		((OBJPOINT *)pData)->lRange = lRange;
	   }

		pInfo->SetPosition( lRange );

	if ( m_pTop ) {
		try {
			Relat Rel;
			HRESULT hr = m_pTop->TopoRelationObjObj_ONr ( ONF,ONr,&Rel);
			if (FAILED(hr)) {
				return true;
			}
			if ( Rel != REL_INN && Rel != REL_INAUS)
				return true;
		} catch ( ... ) {
				char * pONR = new char [_MAX_PATH];
				if ( pONR ) {
					*pONR = '\0';
					wsprintf (pONR, ResString( ResID( IDS_CATCHTOPTEST,&g_pTE->RF()),50),ONr);

				MessageBox ( 0, 
					pONR,
					 ResString ( ResID ( IDS_CATCHCAPTION,&g_pTE->RF()),60),
					MB_OK);
					DELETE_OBJ (pONR);
				}
				return true;
		}

	}
	   if ( !t.Find (&ONr) ) {

			IDGITYP InStr;
			OBJECTTYP ObjStr;
			SetZero ( &InStr );	
			InStr.lMCode = 0L;
			SetObjZero ( &ObjStr );
			InStr.iITyp = OTPunkt | OTLinie | OTFlaeche | OTText | OTKO;
			Bool Flag = true;

			try {
				GetIdentsDate ( ONr, Flag, dCTF, &InStr );
			} catch ( ... ){
				char * pONR = new char [_MAX_PATH];
				if ( pONR ) {
					*pONR = '\0';
					wsprintf (pONR, ResString( ResID( IDS_CATCHDATEN,&g_pTE->RF()),50),ONr);

					MessageBox ( 0,
						pONR,
						 ResString ( ResID ( IDS_CATCHCAPTION,&g_pTE->RF()),60),
						MB_OK);
						DELETE_OBJ (pONR);
				}
				return true;
				
			}

			ObjStr.lIdent = DEX_GetObjIdent ( ONr );
			ObjStr.iGITyp =LogObjectType ( ONr );
			ObjStr.lXmin = InStr.lXmin;
			ObjStr.lXmax = InStr.lXmax;
			ObjStr.lYmin = InStr.lYmin;
			ObjStr.lYmax = InStr.lYmax;
			ObjStr.rPolyLen = InStr.rPolyLen;
			ObjStr.rArea = InStr.rArea;
	
			OBJCreator OBJCr ( * ((OBJPOINT * )pData)->pOBJ );
			ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
//			pInfo->SetPosition( (short)lRange );
	   }
	return TRUE;
  }
//----------------------------Daten enumerieren-------------------------
//-------------------Objektanzahl pro Klasse-----------------
//------------------------------------------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT NumerateObjects ( long ONr, short iObjTyp, void *pData)
  {

	if ( (((IDGITYP *)pData)->iITyp & iObjTyp) == 0 )
			return TRUE;

//---------------------------------------
	short Status = DEX_GetObjectStatus ( ONr );
	
	if ( Status != -1 && Status != OSNormal && Status != OSModified ) {
		((IDGITYP *)pData)->lNoname++;
		return TRUE;
	}

// allgemeine Info's zu ONr ranholen
	if (iObjTyp == OTPunkt ) {
		((IDGITYP *)pData)->lPoint++;
	} else if (iObjTyp == OTLinie ) {
		((IDGITYP *)pData)->lLine++;
	} else if (iObjTyp == OTFlaeche ) {
		((IDGITYP *)pData)->lArea++;
	} else if (iObjTyp == OTText ) {
		((IDGITYP *)pData)->lText++;
	} else {
		if (iObjTyp == OTKO )
			((IDGITYP *)pData)->lComplex++;
		((IDGITYP *)pData)->lNoname++;
	}

/*--------------zu zeitaufwendig-------------------------
	long* pObCont = ObjectContainer ( ONr, iObjTyp );

	if ( pObCont ) {
		if( ((IDGITYP *)pData)->lXmin > *pObCont) 
			((IDGITYP *)pData)->lXmin=*pObCont;
		if( ((IDGITYP *)pData)->lXmax < *(pObCont+1))
			((IDGITYP *)pData)->lXmax=*(pObCont+1);
		if( ((IDGITYP *)pData)->lYmin > *(pObCont+2))
			((IDGITYP *)pData)->lYmin=*(pObCont+2);
		if ( ((IDGITYP *)pData)->lYmax < *(pObCont+3))
 			((IDGITYP *)pData)->lYmax=*(pObCont+3);
	}
	DELETE_OBJ ( pObCont );
-------------------------------------------------------------*/

	return TRUE;
  }
//-----------------------------------------------------------------------

//------------------------------------------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT GetIdentsDate ( long ONr, BOOL , DWORD dCTF, void *pData)
  {
	if ( ONr <= 0L )
		return TRUE;
// zugelassener GiTyp
	short DevTyp = ((IDGITYP *)pData)->iITyp;
	short OTyp = LogObjectType ( ONr );

	if ( (((IDGITYP *)pData)->iITyp & LogObjectType ( ONr )) == 0 )

			return TRUE;

//---------------------------------------
	short Status = DEX_GetObjectStatus ( ONr );
	if ( Status != -1 && Status != OSNormal && Status != OSModified ) {
		((IDGITYP *)pData)->lNoname++;
		return TRUE;
	}


//	ON definiert ????
OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr = ONr;
	if (!DEX_GetObjStatistik (OS)) {
		((IDGITYP *)pData)->lNoname++;
		return TRUE;
	}

	CoordTransX *pCTF = (CoordTransX *) dCTF;

//	KomplexObjekte
	if (OS.iObjTyp == OT_KO ) {
		((IDGITYP *)pData)->lComplex++;
		((IDGITYP *)pData)->lNoname++;
		return TRUE;
	}

	long* pObCont = ObjectContainer ( ONr, OS.iObjTyp);

	if ( pObCont ) {
		if( ((IDGITYP *)pData)->lXmin > *pObCont) 
			((IDGITYP *)pData)->lXmin=*pObCont;
		if( ((IDGITYP *)pData)->lXmax < *(pObCont+1))
			((IDGITYP *)pData)->lXmax=*(pObCont+1);
		if( ((IDGITYP *)pData)->lYmin > *(pObCont+2))
			((IDGITYP *)pData)->lYmin=*(pObCont+2);
		if ( ((IDGITYP *)pData)->lYmax < *(pObCont+3))
 			((IDGITYP *)pData)->lYmax=*(pObCont+3);
	}
	DELETE_OBJ ( pObCont );

	if ( OS.iObjTyp == OT_TEXT) {
			((IDGITYP *)pData)->lText++;
	}

	if (OS.iObjTyp == OT_PUNKT) {
		((IDGITYP *)pData)->lPoint++;
	}
	if (OS.iObjTyp != OT_KANTE && OS.iObjTyp != OT_FLAECHE &&
	    OS.iObjTyp != OT_PUNKT && OS.iObjTyp != OT_TEXT ) {
		((IDGITYP *)pData)->lNoname++;
	}

	if (OS.iObjTyp == OT_KANTE) {
		try {
			double Len = GetLinienParams( ONr,pCTF);
			((IDGITYP *)pData)->rPolyLen=((IDGITYP *)pData)->rPolyLen + Len;
			((IDGITYP *)pData)->lLine++;
			if ( ((IDGITYP *)pData)->rPolyLenMax < Len )
				((IDGITYP *)pData)->rPolyLenMax = Len;
			if ( ((IDGITYP *)pData)->rPolyLenMin > Len )
				((IDGITYP *)pData)->rPolyLenMin = Len;
		} catch ( ... ) {
			char *pONR = new char [_MAX_PATH];
			if (pONR ) {
				*pONR = '\0';
				wsprintf (pONR, ResString( ResID( IDS_CATCHLINIE,&g_pTE->RF()),50),ONr);

				MessageBox ( 0,
					pONR,
					 ResString ( ResID ( IDS_CATCHCAPTION,&g_pTE->RF()),60),
					MB_OK);
				DELETE_OBJ ( pONR);
			}
			return true;

		}
	}

	if (OS.iObjTyp == OT_FLAECHE ) {
		try {
			double FLI = GetFlaechenParams ( ONr , pCTF);
	    		((IDGITYP *)pData)->rArea=((IDGITYP *)pData)->rArea + FLI;
		
			((IDGITYP *)pData)->lArea++;

			if ( ((IDGITYP *)pData)->rAreaMax < FLI )
				((IDGITYP *)pData)->rAreaMax = FLI;
			if ( ((IDGITYP *)pData)->rAreaMin > FLI )
				((IDGITYP *)pData)->rAreaMin = FLI;
		} catch ( ... ) {
				char * pONR = new char [_MAX_PATH];
				if ( pONR ) {
					*pONR = '\0';
					wsprintf (pONR, ResString( ResID( IDS_CATCHFLAECHE,&g_pTE->RF()),50),ONr);

					MessageBox ( 0,
						pONR,
						 ResString ( ResID ( IDS_CATCHCAPTION,&g_pTE->RF()),60),
						MB_OK);
					DELETE_OBJ (pONR);
				}
			return true;
		}

	}
	return TRUE;
  }
//-------------------------------------------------------------------
//------------------------------------------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT DelStatObjects ( long lONr, BOOL ,void *pData) 
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = lONr;

	{
	ErrInstall EI ( EC_DELRECORD);
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		DEX_DeleteObject(lONr);
	}
	}
	return true;

}
//------------------------------------------------------
extern "C"  BOOL PASCAL _XTENSN_EXPORT GetObjIdent ( long ONr, BOOL , DWORD dCTF, void *pData)
  {
	if ( ONr <= 0L )
		return TRUE;
// zugelassener GiTyp
	short DevTyp = ((IDGITYP *)pData)->iITyp;
	short OTyp = LogObjectType ( ONr );

	if ( (((IDGITYP *)pData)->iITyp & LogObjectType ( ONr )) == 0 )

			return TRUE;

//---------------------------------------
	short Status = DEX_GetObjectStatus ( ONr );
	if ( Status != -1 && Status != OSNormal && Status != OSModified ) {
		((IDGITYP *)pData)->lNoname++;
		return TRUE;
	}


//	ON definiert ????
OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr = ONr;
	if (!DEX_GetObjStatistik (OS)) {
		((IDGITYP *)pData)->lNoname++;
		return TRUE;
	}

//	CoordTransX *pCTF = (CoordTransX *) dCTF;

//	KomplexObjekte
	if (OS.iObjTyp == OT_KO ) {
		((IDGITYP *)pData)->lComplex++;
		((IDGITYP *)pData)->lNoname++;
		return TRUE;
	}

	if ( OS.iObjTyp == OT_TEXT) {
			((IDGITYP *)pData)->lText++;
	}

	if (OS.iObjTyp == OT_PUNKT) {
		((IDGITYP *)pData)->lPoint++;
	}
	if (OS.iObjTyp != OT_KANTE && OS.iObjTyp != OT_FLAECHE &&
	    OS.iObjTyp != OT_PUNKT && OS.iObjTyp != OT_TEXT ) {
		((IDGITYP *)pData)->lNoname++;
	}

	if (OS.iObjTyp == OT_KANTE) {
		((IDGITYP *)pData)->lLine++;
	}

	if (OS.iObjTyp == OT_FLAECHE ) {
		((IDGITYP *)pData)->lArea++;
	}
	return TRUE;
  }
//-------------------------------------------------------------------
//---------Werte aus Median- bzw. Mittelwertbestimmung in Buffer
char *WerteInBuffer ( double *pF, double *pL) 
{
	char * pBuffer0 = new char [_MAX_PATH];
	char * pBuffer1 = new char [_MAX_PATH];
	char * pBuffer2 = new char [_MAX_PATH];
	char * pBuffer3 = new char [_MAX_PATH];
        if ( pBuffer0 == NULL || pBuffer1 == NULL || pBuffer2 == NULL  || pBuffer3 == NULL  )
                 return NULL;

	unsigned short resID = 0;

	*pBuffer0 = '\0';
	*pBuffer1 = '\0';
	*pBuffer2 = '\0'; 
	*pBuffer3 = '\0'; 
	double MWFlaeche = *pF;

	if ( MWFlaeche > 0.0 ) {
		strcat ( pBuffer0 , ResString(ResID(IDS_FLAECHENTEXT,&g_pTE->RF()),100));            
		
		if ( MWFlaeche > (double) Hektar) {
			if (*pF > (double) QuadratKiloMeter) {	// QKilometer
				MWFlaeche = MWFlaeche / (double) QuadratKiloMeter;
				resID = IDT_UNITQKM;
			} else {
				MWFlaeche = MWFlaeche / (double) Hektar;	// Hektar
				resID = IDT_UNITHA;
			}
		} else
			resID = IDT_UNITQM;		// Quadratmeter

		ST_DtoA (pBuffer1, "%8.3f", MWFlaeche);
		strcat (pBuffer1, " ");
		strcat (pBuffer1, ResString (ResID (resID, &g_pTE -> RF()), 10));
		strcat ( pBuffer0, pBuffer1);
	}
	double MWLinie = *pL;
	if ( MWLinie > 0.0 ) {

		if (MWLinie > (double) KiloMeter) {		// Kilometer
			MWLinie = MWLinie / (double) KiloMeter;
			resID = IDT_UNITKM;
		} else
			resID = IDT_UNITM;		// Meter

		strcat ( pBuffer2 , ResString(ResID(IDS_LINIENTEXT,&g_pTE->RF()),100));
		ST_DtoA (pBuffer3, " %8.3f", MWLinie);
		strcat (pBuffer3, " ");
		strcat (pBuffer3, ResString (ResID (resID, &g_pTE -> RF()), 10));
		strcat (pBuffer2,pBuffer3); 
		strcat ( pBuffer0,pBuffer2);
	}
	DELETE_OBJ ( pBuffer1 );
	DELETE_OBJ ( pBuffer2 );
	DELETE_OBJ ( pBuffer3 );

	return pBuffer0;
}
//---------------------------------------------------------------------

double * MedianWertBestimmung ( long Count, OBJTree * pOBJ , long *pMCode)
{


	if ( pOBJ == NULL )
		return NULL;
	CTable t( *pOBJ);

short FCount=0,LCount=0, Start = 0;

double * pMedian = new double [ 2];
double * pF = new double [ Count];
double * pL = new double [ Count];
long * pFO = new long [ Count];
long * pLO = new long [ Count];

	if ( pMedian == NULL || pF == NULL || pL == NULL || pFO == NULL || pLO == NULL ) {
		DELETE_OBJ (pMedian);
		DELETE_OBJ (pF);
		DELETE_OBJ (pL);
		DELETE_OBJ (pFO);
		DELETE_OBJ (pLO);
		return NULL;
	}
	int Flag = TRUE;
	if ( pMCode != NULL )
		Flag = FALSE;

	for (t.First(); t.Valid() ; t.Next()  ) {
	
		OBJLock l(t);
		short Typ = l->ObjectTyp();
		if ( Flag ) {
			if ( Typ == OTLinie ) {
				LCount++;
				*(pL+LCount -1 ) = l->LinLaenge();
				*(pLO+LCount -1 ) = l->Object();
			}

			if ( Typ == OTFlaeche ) {
				FCount++;
				*(pF+FCount -1 ) = l->FlInhalt();
				*(pFO+FCount -1 ) = l->Object();
			}
		} else {
			long MKode = l->MCode();
			if ( MKode == *pMCode ) {
				if ( Typ == OTLinie ) {
					LCount++;
					*(pL+LCount -1 ) = l->LinLaenge();
					*(pLO+LCount -1 ) = l->Object();
				}

				if ( Typ == OTFlaeche ) {
					FCount++;
					*(pF+FCount -1 ) = l->FlInhalt();
					*(pFO+FCount -1 ) = l->Object();
				}
			}
		}
	}
	if ( LCount == 0 && FCount == 0 ) {
		DELETE_OBJ (pMedian);
		DELETE_OBJ (pF);
		DELETE_OBJ (pL);
		DELETE_OBJ (pFO);
		DELETE_OBJ (pLO);
		return NULL;
	}

//	Definition des Medians

	if ( FCount > 0 ) {
		Start = 0;
		QuickSort ( pF, pFO, Start, FCount );
		Start = FCount/2;
		if ( FCount - Start * 2 > 0 ) {		// ungerade
			Start = (FCount + 1)/2;
			*pMedian = *(pF+Start-1);
		} else {
			*pMedian = ( *(pF+Start-1) + *(pF+Start) )/2.0;
		}
	} else
		*pMedian = -1.0;

	if ( LCount > 0 ) {
		Start = 0;
		QuickSort ( pL, pLO, Start, LCount );
		Start = LCount/2;
		if ( LCount - Start * 2 > 0 ) {		// ungerade
			Start = (LCount + 1)/2;
			*(pMedian+1) = *(pL+Start-1);
		} else {
			*(pMedian+1) = ( *(pL+Start-1) + *(pL+Start) )/2.0;
		}
	} else
		*(pMedian+1) = -1.0;

	DELETE_OBJ ( pF);
	DELETE_OBJ ( pFO);
	DELETE_OBJ ( pL);
	DELETE_OBJ ( pLO);
	return pMedian;
}

//Mittelwert------------------------------------------------------------
double * MittelWertBerechnung ( OBJTree * pOBJ, long * pMCode)
{
               
     if ( pOBJ == NULL )
     		return NULL;
               
double Flaeche=0.0, Linie=0.0;
short FCount=0,LCount=0;
double	*pMWert = new double[2];

	if ( pMWert == NULL )
		return NULL;
		
	*pMWert = -1.0;
	*(pMWert+1) = -1.0;

	int Flag = TRUE;
	if ( pMCode != NULL )
		Flag = FALSE;

	CTable t(*pOBJ );

	for (t.First(); t.Valid() ; t.Next()  ) {
	
		OBJLock l(t);
		if ( Flag ) {
			if ( OTLinie & l->ObjectTyp() ) {
				Linie = Linie + l->LinLaenge();
				LCount++;
			}
			if ( OTFlaeche & l->ObjectTyp() ) {
				Flaeche = Flaeche + l->FlInhalt();
				FCount++;
			}
		} else {
			long MKode = l->MCode();
			if ( MKode == *pMCode ) {
				if ( OTLinie & l->ObjectTyp() ) {
					Linie = Linie + l->LinLaenge();
					LCount++;
				}
				if ( OTFlaeche & l->ObjectTyp() ) {
					Flaeche = Flaeche + l->FlInhalt();
					FCount++;
				}
			}
		}
	}

	if ( FCount == 0 && LCount == 0 )
		return pMWert;

	if ( FCount > 0 ) 
		*pMWert = Flaeche / (double) FCount ;
	if ( LCount > 0 )
		*(pMWert+1) = Linie / (double) LCount ;
	return pMWert;
}
//-------------------------------ENDE NEUE NICHTMEMBER---------------------
