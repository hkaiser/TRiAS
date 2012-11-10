
// Anzeige diverser Projektinformationen 
// File: KOMPIAS.CXX

#include "kompp.hxx"
#include "version.h"
#include "kompaktr.h"

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include <shellapi.h>

#include <oleguid.h>
#include <dirisole.h>


#include "kompdef.h"
#include <xtsnaux.hxx>
#include <initguid.h>
#include <istatus.h>
#include <buffguid.h>

#include <igeometr.hxx>
#include "triasdef.h"

#include "kompdll.hxx" 
#include "kompprof.hxx"
#include "kompwin.hxx"
#include "komphead.hxx"
#include "kompgew.hxx"
#include "txtedit.hxx"
#include "kompsimu.hxx"
#include "gewbaum.hxx"
#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "kpstatus.hxx"

//---GUIDS---------------------

#include "kompguid.h"  
#include <objgguid.h>
#include <abstguid.h>
//#include <trelguid.h>
#include <statguid.h>

#include "kompias.hxx"

#if _MSC_VER >= 1100
EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
EXTERN_C const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
#endif // _MSC_VER >= 1100

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32

static LPCTSTR g_cbIGMKey	= TEXT("Software\\%s\\%s\\Config");

// Die folgende Funktion muá vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
CTriasExtension *NewExtension ( void )
{
	return new CKompiasExtension ();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_KompaktExtension2, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
//
// ACHTUNG: Im VersionsRC-File (*.rcv) nicht den Eintrag "TRiASSelfRegister" 
// vergessen. Ohne diesen EIntrag wird die Funktion UpdateRegistry nie gerufen.


BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{

//
	if (fRegister) {
	// RegDB initialisieren
		bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_KompaktExtension2, 

#if _MSC_VER >= 1100
			TEXT("TRiAS.GewaesserExtension.1"), IDS_LONGCLASSNAMEX,
//				TEXT("TRiAS.KompaktExtension2.1"), IDS_LONGCLASSNAMEX,
#else
			TEXT("TRiAS.GewaesserExtension.1"), IDS_LONGCLASSNAME,
//				TEXT("TRiAS.KompaktExtension2.1"), IDS_LONGCLASSNAME,
#endif

			KOMPAKT_MAJORVERSION, KOMPAKT_MINORVERSION,
			EFUnLoadable|EFVisible|EFRegisterToolBitmap);


// KK011011

		TCHAR szIGMKey[_MAX_PATH];
		wsprintf(szIGMKey,g_cbIGMKey,REG_COMPANY_KEY,REG_PRODUCT_KEY);
		{	

		CCurrentUser rgMASS(szIGMKey, true);

		// KK 020320 - fachlich absoluter Blödsinn
		if ( g_pTE) {
			ResString IGMKey (ResID(IDS_IGMKEY, &g_pTE->RF()),80);
			ResString IGMCaption (ResID(IDS_IGMCAPTION, &g_pTE->RF()),80);

			rgMASS.SetSubSZ (IGMKey ,IGMCaption);

		} else {

			rgMASS.SetSubSZ ( "InstalledProduct","Integriertes Gewässermanagement");

		}

		}


		return fSuccess;
	} else {

// KK011024
		TCHAR szIGMKey[_MAX_PATH];
		wsprintf(szIGMKey,g_cbIGMKey,REG_COMPANY_KEY,REG_PRODUCT_KEY);
		{	

		CCurrentUser rgMASS(szIGMKey, true);

		if ( g_pTE) {
	
			ResString IGMKey (ResID(IDS_IGMKEY, &g_pTE->RF()),80);

			rgMASS.DeleteValue (IGMKey);

		} else {

			rgMASS.DeleteValue ( "InstalledProduct");

		}

		}

	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_KompaktExtension2, 
				TEXT("TRiAS.GewaesserExtension.1"));
//				TEXT("TRiAS.KompaktExtension2.1"));
	}

return true;	// alles ok

}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muá von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuhängeneden Menu's übergeben bekommt.
CKompiasExtension :: CKompiasExtension (void)

#if _MSC_VER >= 1100
		  : CTriasExtension (IDR_MENU1, IDR_MENU2)
#else
		  : CTriasExtension (CKOMPAKTEXTENSIONMENU, CKOMPAKTEXTENSIONORMENU)
#endif

{
			m_isInit = false;
//			CreateStandardInformation();
}

// Destruktor -----------------------------------------------------------------
CKompiasExtension :: ~CKompiasExtension (void) 
{
	if (m_isInit)
		DeleteStandardInformation();
}

// ----------------------------------------------------------------------------
// Virtuelle Funktionen, die bei bestimmten Events gerufen werden -------------

// Diese Funktion wird (einmalig) gerufen, wenn die Erweiterung vollständig
// installiert ist
STDMETHODIMP_(BOOL) CKompiasExtension :: InitExtension (short iMode)
{

// KK011011
/*---
	TCHAR szIGMKey[_MAX_PATH];
	wsprintf(szIGMKey,g_cbIGMKey,REG_COMPANY_KEY,REG_PRODUCT_KEY);
	{	

	CCurrentUser rgMASS(szIGMKey, true);

	ResString IGMKey (ResID(IDS_IGMKEY, &RF()),80);
	ResString IGMCaption (ResID(IDS_IGMCAPTION, &RF()),80);

//	rgMASS.SetSubSZ ( "InstalledProduct","Integriertes Gewässermanagement");
	rgMASS.SetSubSZ (IGMKey ,IGMCaption);

	}

  ----------------------------------*/

	if (!CTriasExtension :: InitExtension (iMode))
		return false;


//	CreateKompDataToolBar ();

// Notifikation anfordern, die bei ObjektSelektieren/-deselektieren ausgelöst
// wird
// Notifikationen anfordern


//--------------------------------------------------------
	m_wMsg1 = RegisterWindowMessage ("MALTESHYDRAULIKPUNKT");
	m_wMsg2 = RegisterWindowMessage ("GEWAESSERABGLEICH");
	m_wMsg3 = RegisterWindowMessage ("GEWAESSERKATASTER");
	m_wMsg4 = RegisterWindowMessage ("MALTESHYDRAULIKPUNKTE");
	m_wMsg5 = RegisterWindowMessage ("HYDRAULIKABGLEICH");
//--------------------------------------------------------

	m_isInit = false;
	CreateStandardInformation();

	RegisterNotification (DEX_GOTOBJWNDFOCUS);
	RegisterNotification (DEX_DELOBJECT);
	RegisterNotification (DEX_N_HANDSOFFSTORAGE);
	RegisterNotification (DEX_N_SAVECOMPLETED);
	RegisterNotification (DEX_N_SAVEOTHERSTORAGE);
	RegisterNotification (DEX_N_SAVESAMESTORAGE);
	RegisterNotification (DEX_N_PROJECTTOCLOSE);

	RegisterNotification (DEX_PROJECTOPEN);

	MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);

//	MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
	RegisterNotification (DEX_OBJECTSELECTED);
//	RegisterNotification (DEX_OBJECTUNSELECTED);
	//
	RegisterNotification (DEX_N_OBJECTCREATED);
	//
	RegisterNotification (DEX_OBJWNDCLOSED);

	RegisterNotification (m_wMsg1,false);
	RegisterNotification (m_wMsg2,false);
	RegisterNotification (m_wMsg3,false);
	RegisterNotification (m_wMsg4,false);
	RegisterNotification (m_wMsg5,false);

	TRiASKompaktLoader();

	m_iFunction = KompaktMenu(false);
	HWND hWnd = 0;

//  Toolbar aktivieren
	CreateKompDataToolBar ();

// Test ohne Kompakt1.dll

	if ( m_dKPA == KP_NoAll) {	// In Registrierung NoKompaktDLL eingestellt
		return true;
	}

	
	return KompaktFunktion ( m_iFunction,hWnd);

}

// Diese Funktion wird gerufen, bevor die Erweiterung freigeben werden soll
STDMETHODIMP_(BOOL) CKompiasExtension :: UnLoadExtension (void)
{

// Notifikationen wieder abmelden
	UnRegisterNotification (DEX_GOTOBJWNDFOCUS);
	UnRegisterNotification (DEX_DELOBJECT);
	UnRegisterNotification (DEX_N_HANDSOFFSTORAGE);
	UnRegisterNotification (DEX_N_SAVECOMPLETED);
	UnRegisterNotification (DEX_N_SAVEOTHERSTORAGE);
	UnRegisterNotification (DEX_N_SAVESAMESTORAGE);
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);

	MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//	MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
	//
	UnRegisterNotification (DEX_N_OBJECTCREATED);
	//
	UnRegisterNotification (DEX_OBJECTSELECTED);
//	UnRegisterNotification (DEX_OBJECTUNSELECTED);
	UnRegisterNotification (DEX_OBJWNDCLOSED);
	UnRegisterNotification (m_wMsg1,false);
	UnRegisterNotification (m_wMsg2,false);
	UnRegisterNotification (m_wMsg3,false);
	UnRegisterNotification (m_wMsg4,false);
	UnRegisterNotification (m_wMsg5,false);

	if ( m_isInit)
		DeleteStandardInformation();

	RemoveKompDataToolBar ();

// KK011024
/*-----
	TCHAR szIGMKey[_MAX_PATH];
	wsprintf(szIGMKey,g_cbIGMKey,REG_COMPANY_KEY,REG_PRODUCT_KEY);
	{	

	CCurrentUser rgMASS(szIGMKey, true);

	ResString IGMKey (ResID(IDS_IGMKEY, &RF()),80);

	rgMASS.DeleteValue (IGMKey);

	}
-----------------*/
//------------------------------------------------------------------

	return CTriasExtension :: UnLoadExtension();		// kein Fehler

}


// Diese Funktion initialisiert das Menu --------------------------------------
STDMETHODIMP_(BOOL) CKompiasExtension :: MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{

// Mein Menu ???
	if (hWnd == NULL && hMenu != MenuHandle()) return FALSE;

	if (hWnd != NULL && hMenu != ORMenuHandle()) return FALSE;

//----------------------------------------------------------------
	m_hMenu = hMenu;
	m_hWnd = hWnd;
	m_isBauw = false;
                            
// Mein Menu im Kopf
	if ( hWnd == 0 && hMenu == MenuHandle() ) {
		if (!KatasterLaden()) {
			EnableMenuItem (hMenu, IDM_BAUWERKEPUT + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_BAUWERKEGET + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_BAUWERKEZUKP + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

			EnableMenuItem (hMenu, IDM_UNTERHALTUNG + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_AUSSCHREIBUNG + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_AUFTRAG + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_AUFMASS + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

			EnableMenuItem (hMenu, IDM_KATASTER + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_VERBAND + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_PROJEKTE + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

			EnableMenuItem (hMenu, IDM_HYDRAULIK + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

			EnableMenuItem (hMenu, IDM_KOMPAKT + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

#if _MSC_VER >= 1100
			EnableMenuItem (hMenu, IDM_KOMPAKTQUELLE + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
#endif

			EnableMenuItem (hMenu, IDM_KOMPAKTABGLEICH + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

			EnableMenuItem (hMenu, IDM_KOMPAKTTESTEN + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_KOMPAKTDIFFERENZ + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_TRIAS + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

			return false;

		} else {

			EnableMenuItem (hMenu, IDM_BAUWERKEPUT + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem (hMenu, IDM_BAUWERKEGET + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem (hMenu, IDM_BAUWERKEZUKP + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);

			EnableMenuItem (hMenu, IDM_UNTERHALTUNG + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem (hMenu, IDM_AUSSCHREIBUNG + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem (hMenu, IDM_AUFTRAG + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem (hMenu, IDM_AUFMASS + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);

			EnableMenuItem (hMenu, IDM_KATASTER + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);

			if ( !m_iProfile) {
				EnableMenuItem (hMenu, IDM_VERBAND + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_PROJEKTE + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			} else {
				EnableMenuItem (hMenu, IDM_VERBAND + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_PROJEKTE + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			}

			if ( !m_iAbfluss) 
				EnableMenuItem (hMenu, IDM_HYDRAULIK + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			else
				EnableMenuItem (hMenu, IDM_HYDRAULIK + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);



			if ( m_pKH->GewClass() && m_pKH->GewClass()->Count() > 0 ) {
				EnableMenuItem (hMenu, IDM_BAUWERKEPUT + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
		
				EnableMenuItem (hMenu, IDM_KOMPAKT + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
#if _MSC_VER >= 1100
				EnableMenuItem (hMenu, IDM_KOMPAKTQUELLE + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
#endif
				EnableMenuItem (hMenu, IDM_KOMPAKTABGLEICH + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);

				EnableMenuItem (hMenu, IDM_KOMPAKTTESTEN + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_KOMPAKTDIFFERENZ + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_TRIAS + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			} else {
				EnableMenuItem (hMenu, IDM_BAUWERKEPUT + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

				EnableMenuItem (hMenu, IDM_KOMPAKT + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
#if _MSC_VER >= 1100
				EnableMenuItem (hMenu, IDM_KOMPAKTQUELLE + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
#endif
				EnableMenuItem (hMenu, IDM_KOMPAKTABGLEICH + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

				EnableMenuItem (hMenu, IDM_KOMPAKTTESTEN + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_KOMPAKTDIFFERENZ + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_TRIAS + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

			}

			if ( m_pKH->BauwClass() && m_pKH->BauwClass()->Count() > 0 ) {
				EnableMenuItem (hMenu, IDM_ORWINSHOWKOMPATTRIBUT + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_BAUWERKEGET + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_BAUWERKEZUKP + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			} else {
				EnableMenuItem (hMenu, IDM_BAUWERKEGET + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_BAUWERKEZUKP + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			}
			if (!isBauwerk()) {
				EnableMenuItem (hMenu, IDM_BAUWERKEGET + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_BAUWERKEZUKP + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			}
			if (!isGewaesser()) {
				EnableMenuItem (hMenu, IDM_BAUWERKEPUT + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_BAUWERKEGET + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_BAUWERKEZUKP + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

				EnableMenuItem (hMenu, IDM_HYDRAULIK + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

				EnableMenuItem (hMenu, IDM_UNTERHALTUNG + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_AUSSCHREIBUNG + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_AUFTRAG + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_AUFMASS + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			}
		}

	}
// Mein Fenster ??
	if ( hWnd != 0 && hMenu == ORMenuHandle() ) {

		KatasterLaden();


		EnableMenuItem (hMenu, IDM_ORWINTOPOLOGIE + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINBAUTOPOLOGIE + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINBAUSPEICHERN + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINLAUFRICHTUNG + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINUMKEHR + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINTOPTEST + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINSHOWKATASTER + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINSHOWKOMPATTRIBUT + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINKATASTERMOD + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINTRIASMOD + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_ORWINFLAECHENTOP + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

		if ( isActive()) {

		OBJSTATISTIK OS;
	   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);
		OS.lONr =  DEX_GetActiveObject ( hWnd );

//		EnableMenuItem (hMenu, IDM_ORWINSHOWKOMPATTRIBUT + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);

		m_lONr = -1L;

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
			if ( OS.iObjTyp == OT_FLAECHE) {
				if ( !isActive()) {
					EnableMenuItem (hMenu, IDM_ORWINTOPOLOGIE + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				} else {
					if ( m_pKH->GewClass())
						EnableMenuItem (hMenu, IDM_ORWINTOPOLOGIE + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				}

//Erweiterte Flächenanalyse
// KK020522
//				EnableMenuItem (hMenu, IDM_ORWINFLAECHENTOP + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_ORWINFLAECHENTOP + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_ORWINTOPTEST + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				m_lONr = OS.lONr;
			} else {
				EnableMenuItem (hMenu, IDM_ORWINTOPOLOGIE + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_ORWINTOPTEST + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			}

			if ( OS.iObjTyp == OT_KANTE) {
				if ( !isActive()) 
					return false;

				if ( ObjektIstBauwerk (OS.lONr)) {
					m_lONr = OS.lONr;
					EnableMenuItem (hMenu, IDM_ORWINSHOWKOMPATTRIBUT + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				}
					

				if ( !ObjektIstGewaesser ( OS.lONr))
					return false;


//				if ( m_isShow == KP_ALL && m_pGewAlle)
//						EnableMenuItem (hMenu, IDM_ORWINTOPOLOGIE + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);

				if ( m_isShow == KP_PART && m_pGewPart)
						EnableMenuItem (hMenu, IDM_ORWINTOPOLOGIE + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);

				if (isBauwerk()) {
					EnableMenuItem (hMenu, IDM_ORWINBAUTOPOLOGIE + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
					EnableMenuItem (hMenu, IDM_ORWINBAUSPEICHERN + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				}

				EnableMenuItem (hMenu, IDM_ORWINLAUFRICHTUNG + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_ORWINUMKEHR + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_ORWINKATASTER + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_ORWINSHOWKATASTER + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_ORWINSHOWKOMPATTRIBUT + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_ORWINKATASTERMOD + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				EnableMenuItem (hMenu, IDM_ORWINTRIASMOD + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				m_lONr = OS.lONr;
			} else {
				EnableMenuItem (hMenu, IDM_ORWINKATASTER + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_ORWINSHOWKATASTER + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
//				EnableMenuItem (hMenu, IDM_ORWINSHOWKOMPATTRIBUT + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_ORWINKATASTERMOD + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
				EnableMenuItem (hMenu, IDM_ORWINTRIASMOD + MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			}

			if ( OS.iObjTyp == OT_PUNKT) {
				if ( !isActive()) 
					return false;
				if ( ObjektIstBauwerk (OS.lONr)) {
					m_lONr = OS.lONr;
					EnableMenuItem (hMenu, IDM_ORWINSHOWKOMPATTRIBUT + MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
				}
			}					

		}
		}	// nur , falls Kompakt vorhanden
//----------------------Ab zur Topologie----------------------------------

	}
	return false;
}


// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(BOOL) CKompiasExtension :: MenuCommand (WPARAM MenuItemID, HWND hWnd)
{
	if ( m_lONrDel > 0L) {
		DEX_DeleteObject(m_lONrDel);
		m_lONrDel = -1L;
	}


	switch ( MenuItemID ) {
		m_hWnd = hWnd;
// Bauwerke
	case IDM_BAUWERKEPUT:
		{
		MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		m_iFunction = KP_BAUWERKE;
		m_isWork = false;
		KompaktFunktion ( m_iFunction,hWnd);
		MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//		MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
		if (!isWork())
			MessageBox (__hWndM,
			 ResString (ResID(IDS_ERRKPNOEREIGNISSE, &RF()),80),
			 ResString (ResID(IDS_BILDEEREIGNISSE, &RF()),80),
			 MB_OK|MB_ICONHAND);
		

		} 

		return TRUE;


	case IDM_BAUWERKEGET:
		{
		CEierUhr Wait (MVWind());
		TR_OCLTree *pBauw = LadeBauwerkeKlassen();

		if ( !pBauw || pBauw->Count() == 0) {
			MessageBox (__hWndM,
			 ResString (ResID(IDS_KEINEBAUWERKE, &RF()),80),
			 ResString (ResID(IDS_CAPTIONEREIGNIS, &RF()),80),
			 MB_OK|MB_ICONHAND);
	
			DELETE_OBJ ( pBauw);
			return TRUE;
		}

		{
			BauwerkeStatistik BS ( MVWind(), IDD_BAUWSTATISTIK, RF(),pBauw);
			BS.Show(Centre);

			if ( BS.Result() == 1 ) {

				long *pObjS = BS.Obj();

	// KK010829 - Objekte, die nicht in Sicht definiert wurden !!!

				long * pObj = ViewHasIdent ( pObjS);

				short Flag = ROSortObjNr;

				if ( pObj) {
					CreateORWindow ( Flag, 80, 100, pObj,ResString (ResID(IDS_BAUWNUMMER, &RF()),50).Addr(), 0, 255, 255);
					DELETE_OBJ(pObj);
				}

			}
		}

		DELETE_OBJ ( pBauw); 

		}
		return TRUE;


// Bauwerke an Kompakt
	case IDM_BAUWERKEZUKP:
		{

		m_iFunction = KP_BAUWZUKOMPAKT;
		m_lONrBauw = -1L;

		m_lGlobalBW = m_lGlobalGW = 0L;

// Kommentar Gewässerkataster ausschalten
		m_iComment = 0;
		if ( m_hLib)
			m_hLib->BemerkungenBauwerkGewaesserEinAus(m_iComment);

		KompaktFunktion ( m_iFunction,hWnd);


// Kommentar Gewässerkataster einschalten
		m_iComment = 1;
		if ( m_hLib)
			m_hLib->BemerkungenBauwerkGewaesserEinAus(m_iComment);

		char *pCode = new char [_MAX_PATH];
		if ( pCode ) {
			wsprintf( pCode, ResString( ResID( IDS_COUNTERSTOREBWEX,&g_pTE->RF()),100),m_lGlobalBW);
			MessageBox (__hWndM,
				pCode,
				 ResString (ResID(IDS_CAPTIONEREIGNIS, &RF()),50),
				 MB_OK|MB_ICONHAND);
			DELETE_OBJ(pCode);
		} else {

			MessageBox (__hWndM,
				 ResString (ResID(IDS_COUNTERBAUWERKE, &RF()),100),
				 ResString (ResID(IDS_CAPTIONEREIGNIS, &RF()),50),
				 MB_OK|MB_ICONHAND);
		}

		} 
		return TRUE;


// LeistungsArten

	case IDM_UNTERHALTUNG:
		{
		m_iFunction = KP_UNTERHALTUNG;

		KompaktProtokoll(m_pLocProt,"\n Unterhaltung :\n");


		KompaktFunktion ( m_iFunction,hWnd);
		} 

		return TRUE;

	case IDM_AUSSCHREIBUNG:
		{
		m_iFunction = KP_AUSSCHREIBUNG;

		KompaktProtokoll(m_pLocProt,"\n Ausschreibung :\n");

		KompaktFunktion ( m_iFunction,hWnd);
		} 

		return TRUE;

	case IDM_AUFTRAG:
		{
		m_iFunction = KP_AUFTRAG;

		KompaktProtokoll(m_pLocProt,"\n Auftrag :\n");

		KompaktFunktion ( m_iFunction,hWnd);
		} 
		return TRUE;

	case IDM_AUFMASS:
		{
		m_iFunction = KP_AUFMASS;


		KompaktProtokoll(m_pLocProt,"\n Aufmaß :\n");


		KompaktFunktion ( m_iFunction,hWnd);
		} 
		return TRUE;

// Fachprogramme

	case IDM_HYDRAULIK:
		{
		if ( !m_pKH || !m_pKH->HydrClass()) {
			MessageBox ( __hWndM,
			 ResString (ResID(IDS_DEFNOUEBERSCHWEMMUNG, &RF()),180),
			 ResString (ResID(IDS_STRCAPTION, &RF()),180),
			MB_ICONSTOP);
		} else {
			m_iFunction = KP_HYDRAULIK;
			if ( KompaktFunktion ( m_iFunction,hWnd)) {

	// Hier HydraulikAuswertung
				CEierUhr Wait(MVWind());
				MischeHydraulik();
			}
		}

		} 
		return TRUE;

	case IDM_KATASTER:
		{
		m_iFunction = KP_KATASTER;
		KompaktFunktion ( m_iFunction,hWnd);
		} 
		return TRUE;

	case IDM_VERBAND:
		{
		m_iFunction = KP_VERBAND;
		KompaktFunktion ( m_iFunction,hWnd);
		} 
		return TRUE;

	case IDM_PROJEKTE:
		{
		m_iFunction = KP_PROJEKTE;
		KompaktFunktion ( m_iFunction,hWnd);
		} 
		return TRUE;

// GewaesserVergleich
	case IDM_KOMPAKT:	// Alle Gewaesser
		{
		
		m_iFunction = KP_KOMPAKT;
		if ( m_pGew)
			DELETE_OBJ ( m_pGew);
		if ( m_pModObj) {
			CTreeLoeschen ( m_pModObj);
			DELETE_OBJ ( m_pModObj);
		}

		KompaktFunktion ( m_iFunction,hWnd);
		} 
		return TRUE;

// Neue DatenQuelle

	case IDM_KOMPAKTQUELLE :
		{
	//	Datenquelle wechseln ??
		
	#if _MSC_VER >= 1100
			DatenQuelleWechseln();

	#endif

		}
		return TRUE;

// GewaesserAbgleich
	case IDM_KOMPAKTABGLEICH:	// Alle Gewaesser
		{
		m_iFunction = KP_KOMPAKTABGLEICH;
		if ( m_pGew)
			DELETE_OBJ ( m_pGew);
		if ( m_pModObj) {
			CTreeLoeschen ( m_pModObj);
			DELETE_OBJ ( m_pModObj);
		}

		KompaktFunktion ( m_iFunction,hWnd);
		} 
		return TRUE;

// Gewaesser an Kompakt
	case IDM_TRIAS:
		{
		m_iFunction = KP_TRIAS;

		if ( m_pGew)
			DELETE_OBJ ( m_pGew);

		if ( m_pModObj) {
			CTreeLoeschen ( m_pModObj);
			DELETE_OBJ ( m_pModObj);
		}

		KompaktFunktion ( m_iFunction,hWnd);
		} 
		return TRUE;


	case IDM_KOMPAKTTESTEN:		// Kataster->Graphik

		{

			if ( m_pGew)
				DELETE_OBJ ( m_pGew);

			if ( m_pModObj) {
				CTreeLoeschen ( m_pModObj);
				DELETE_OBJ ( m_pModObj);
			}

			GewaesserVergleich(false);	// Nur Kompakt
		} 
		return TRUE;


//----------------------- GewaesserAbgleich------------------------

	case IDM_KOMPAKTDIFFERENZ:
		{
		if ( m_pKH && m_pKH->GewClass()) {
			if ( m_pGew)
				DELETE_OBJ ( m_pGew);

			if ( m_pModObj) {
				CTreeLoeschen ( m_pModObj);
				DELETE_OBJ ( m_pModObj);
			}

//---------------Objekte an Ident hängen
			LadeObjektKlasse ( OTLinie, m_pKH->GewClass());

			m_pGew = SpeichernGewaesserNummer ( m_pKH->CodeGewNr(),m_pKH->CodeGewName(),m_pKH->GewClass());

			if ( !m_pGew ||  0 == m_pGew->Count() )  {
				DELETE_OBJ ( m_pGew);
				return true;
			}

			AktualisiereGewKataster( m_pGew,m_pKH->GewClass());

			if (!SucheDifferenzGewaesser ( m_pGew)) {
			MessageBox (__hWndM, 
			 ResString (ResID(IDS_KEINEDIFFLAENGE, &RF()),50),
			 ResString (ResID(IDS_DIFFLAENGE, &RF()),50),
			 MB_OK|MB_ICONHAND);
		

				return true;
			}

			{
			TriasGewaesser TG ( MVWind(),GEWAESSERUEBERSICHT, RF(), m_pGew,m_hLib,m_pKH->GewDiffLaenge(),true);
			TG.Show(Centre);  
			if (TG.Result() == 1) {
				long *pObj = TG.Obj();
				short Flag = ROSortObjNr;
				CreateORWindow ( Flag, 80, 100, pObj, ResString (ResID(IDS_GEWNUMMER, &RF()),50).Addr(), 0, 255, 255);
			}
			}
		}

		}

	case IDM_KOMPDATA:
		{
		MessageBox (__hWndM,
		 "Hallo Malte!",
		 "My ToolBar",
		 MB_OK);
		
		}
		return true;
//////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------
//-------------------------Fenster-Befehle------------------------------
//----------------------------------------------------------------------

	case IDM_ORWINKATASTERMOD:
		{
		long lCount = GewaesserInWindowZuKataster(hWnd);
		if ( 1 == lCount ) {
			if ( m_lONr == -1L || m_lONr == 0L )
				return TRUE;
			char *pGewNr = HoleGewaesserNummer (  m_lONr, m_pKH->CodeGewNr());
			if ( pGewNr )
				m_hLib->IGMEinzelGewaesser(hWnd,pGewNr);
//				m_hLib->KompaktEinzelGewaesser(hWnd,pGewNr);
			DELETE_OBJ ( pGewNr);

		}
		if ( m_isShow == KP_ALL && m_pGewAlle ) {
			DEX_RemoveORWnd(hWnd);
			TriasGewaesser TG ( MVWind(),GEWAESSERUEBERSICHT, RF(), m_pGewAlle,m_hLib,m_pKH->GewDiffLaenge(),true);
			TG.Show(Centre);  
			if (TG.Result() == 1) {
				long *pObj = TG.Obj();
				short Flag = ROSortObjNr;
				CreateORWindow ( Flag, 80, 100, pObj, ResString (ResID(IDS_GEWNUMMER, &RF()),50).Addr(), 0, 255, 255);
				m_isShow = KP_ALL;
			} else {
				m_isShow = KP_NOTHING;
			}
		}

		}
		return TRUE;
////////////////////////////////////////////////////////////////////////

	case IDM_ORWINTRIASMOD:
		{
		long lCount = ModGewaesserInWindow(hWnd);
		if ( 1 == lCount ) {
			if (m_lONr == -1L || m_lONr == 0L )
				return TRUE;
			char *pGewNr = HoleGewaesserNummer (  m_lONr, m_pKH->CodeGewNr());
			if ( pGewNr )
				m_hLib->IGMEinzelGewaesser(hWnd,pGewNr);
//				m_hLib->KompaktEinzelGewaesser(hWnd,pGewNr);
			DELETE_OBJ ( pGewNr);

		}
		if ( m_isShow == KP_ALL && m_pGewAlle ) {
			DEX_RemoveORWnd(hWnd);
			TriasGewaesser TG ( MVWind(),GEWAESSERUEBERSICHT, RF(), m_pGewAlle,m_hLib,m_pKH->GewDiffLaenge(),true);
			TG.Show(Centre);  
			if (TG.Result() == 1) {
				long *pObj = TG.Obj();
				short Flag = ROSortObjNr;
				CreateORWindow ( Flag, 80, 100, pObj, ResString (ResID(IDS_GEWNUMMER, &RF()),50).Addr(), 0, 255, 255);
				m_isShow = KP_ALL;
			} else {
				m_isShow = KP_NOTHING;
			}
		}

		DEX_RePaint();
		
		}
		return TRUE;
////////////////////////////////////////////////////////////////////////
	case IDM_ORWINSHOWKATASTER:
		{

		if (m_lONr == -1L || m_lONr == 0L )
			return TRUE;
		char *pGewNr = HoleGewaesserNummer (  m_lONr, m_pKH->CodeGewNr());
		if ( pGewNr )
			m_hLib->IGMEinzelGewaesser(hWnd,pGewNr);
//			m_hLib->KompaktEinzelGewaesser(hWnd,pGewNr);
		DELETE_OBJ ( pGewNr);
		}

		return TRUE;

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
	case IDM_ORWINSHOWKOMPATTRIBUT:
		{

			DefineObjektEigenschaft();
		}

		return TRUE;

////////////////////////////////////////////////////////////////////////

	case IDM_ORWINTOPTEST:
		{
		if (m_lONr == -1L || m_lONr == 0L )
			return TRUE;
		long lONF = m_lONr;
		m_isCreate = false;	// Keine neue Geometrie

// Geht in die Hosen
//		TopologieRecherche(m_lONr);
		CEierUhr Wait(MVWind());

		FlaechenAnalyse ( m_lONr);

		m_isCreate = true;	// wieder einstellen

		}
		return TRUE;
////////////////////////////////////////////////////////////////////////

	case IDM_ORWINFLAECHENTOP:
		{
		if (m_lONr == -1L || m_lONr == 0L)
			return TRUE;
		long lONF = m_lONr;
		m_isCreate = false;	// Keine neue Geometrie

		CEierUhr Wait(MVWind());

		GrossFlaechenAnalyse ( m_lONr,hWnd);	// Objekte innerhalb Fläche

		m_isCreate = true;	// wieder einstellen

		}
		return TRUE;
///////////////////////////////////////////////////////////////////////
	case IDM_ORWINBAUTOPOLOGIE:
		{

		CEierUhr Wait (MVWind());

		if ( m_lONr == -1L || m_lONr == 0L )
			return true;

		if ( m_pModObj) {
			CTreeLoeschen ( m_pModObj);
			DELETE_OBJ ( m_pModObj);
		}

		if ( ObjektIstGewaesser ( m_lONr)) {
			
			char *pGewNr = HoleGewaesserNummer ( m_lONr, m_pKH->CodeGewNr());
			if ( pGewNr) {
				TR_OCLTree *pBauw = LadeBauwerkeTeilKlassen(pGewNr);
				DELETE_OBJ ( pGewNr);

				if ( !pBauw || pBauw->Count() == 0) {
					MessageBox (__hWndM,
					 ResString (ResID(IDS_KEINEBAUWERKE, &RF()),50),
					 ResString (ResID(IDS_CAPTIONEREIGNIS, &RF()),50),
					 MB_OK|MB_ICONHAND);
			
					DELETE_OBJ ( pBauw);
					return true;
				}

				{
				BauwerkeStatistik BS ( ORWind(hWnd), IDD_BAUWSTATISTIK, RF(),pBauw);
				BS.Show(Centre);

				if ( BS.Result() == 1 ) {

					long *pObjS = BS.Obj();

	// KK010829 - Objekte, die nicht in Sicht definiert wurden !!!

					long * pObj = ViewHasIdent ( pObjS);

					short Flag = ROSortObjNr;
					if ( pObj) {
						CreateORWindow ( Flag, 80, 100, pObj,ResString (ResID(IDS_BAUWNUMMER, &RF()),50).Addr(), 0, 255, 255);
						DELETE_OBJ(pObj);
					}

				}
				}
				DELETE_OBJ ( pBauw); 
			}
		}

		}

		return TRUE;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
	case IDM_ORWINBAUSPEICHERN:
		{

		CEierUhr Wait (MVWind());
// KK010914 - mehrere Gewässer
		long lCount = 0L;

		DEXOR_SelectedObjectsCount ( hWnd , &lCount);

		if ( lCount > 1L) {
			BauwerksBearbeitung(hWnd);
			return true;
		}


		if ( m_lONr == -1L || m_lONr == 0L )
			return true;

		if ( m_pModObj) {
			CTreeLoeschen ( m_pModObj);
			DELETE_OBJ ( m_pModObj);
		}

		if ( ObjektIstGewaesser ( m_lONr)) {
			
			char *pGewNr = HoleGewaesserNummer ( m_lONr, m_pKH->CodeGewNr());

			if ( pGewNr) {
///*-------------------------
//	Über m_lONr RealBuffering aufrufen + BauwKlassen suchen (10 Meter-Bereich)
				long lGewNr = m_lONr;
				TR_OBJTree *pBauw = FindeBauwerkeTeilKlassen(pGewNr,m_lONr);
				if ( !pBauw || pBauw->Count() == 0) {
					MessageBox (__hWndM,
					 ResString (ResID(IDS_KEINEBAUWERKE, &RF()),50),
					 ResString (ResID(IDS_CAPTIONEREIGNIS, &RF()),50),
					 MB_OK);
					DELETE_OBJ ( pBauw);
					DELETE_OBJ ( pGewNr);
					return true;
				}
//	Verschnitt testen - notfalls korrigieren + ab zu Malte
//		Verarbeiten
				{

				CTable t ( *pBauw);
				long lCount = pBauw->Count();
				long *pObj = new long [ lCount + 1 ];
				*pObj = lCount;
				long i = 0;

// Kommentar Gewässerkataster einschalten
//				m_iComment = 0;
				m_iComment = 1;
				if ( m_hLib)
					m_hLib->BemerkungenBauwerkGewaesserEinAus(m_iComment);

				for ( t.First(); t.Valid(); t.Next()){
					TR_OBJLock l(t);
					i++;
					*(pObj+i) = l->Object();
	// KK010808
	// Definieren in Kompakt1.DLL
					SetInBauwerksKataster(*(pObj+i), lGewNr);
				}

// Kommentar Gewässerkataster ausschalten
				m_iComment = 0;
				//m_iComment = 1;
				if ( m_hLib)
					m_hLib->BemerkungenBauwerkGewaesserEinAus(m_iComment);
				

				short Flag = ROSortObjNr;
				CreateORWindow ( Flag, 80, 100, pObj,ResString (ResID(IDS_EREIGNISRECHERCHE, &RF()),50) , 0, 255, 255);
//				CreateORWindow ( Flag, 80, 100, pObj, "Recherchierte Ereignisse", 0, 255, 255);

				DELETE_OBJ (pObj);
				}

				DELETE_OBJ ( pBauw);

//-------------------------------------------------*/

				DELETE_OBJ ( pGewNr);


			}
		}

		}

		return TRUE;

///////////////////////////////////////////////////////////////////////
	case IDM_ORWINLAUFRICHTUNG:
		{

		if ( m_lONr == -1L || m_lONr == 0L )
			return true;

		if ( ObjektIstGewaesser ( m_lONr)) {
			ObjektBearbeitung ( true,hWnd);
			DEX_RePaint();
		}
		}
		return true;


///////////////////////////////////////////////////////////////////////
	case IDM_ORWINUMKEHR:
		{

		if ( m_lONr == -1L || m_lONr == 0L)
			return true;


		if ( ObjektIstGewaesser ( m_lONr)) {
			ObjektBearbeitung ( false,hWnd);
			DEX_RePaint();
		}
		}
		return true;

///////////////////////////////////////////////////////////////////////
	case IDM_ORWINTOPOLOGIE:
		{

		if ( m_lONr == -1L || m_lONr == 0L )
			return true;

		if ( ObjektIstGewaesser ( m_lONr)) {


			if ( m_isShow == KP_PART && m_pGewPart ) {
				if ( m_hWndPart == 0)
					return true;
				DEX_RemoveORWnd(hWnd);
				TriasGewaesser TG ( ORWind(m_hWndPart),GEWAESSERUEBERSICHT, RF(), m_pGewPart,m_hLib,m_pKH->GewDiffLaenge(),false);
				TG.Show(Centre);  
				if (TG.Result() == 1) {
					long *pObj = TG.Obj();
					short Flag = ROSortObjNr;
					CreateORWindow ( Flag, 80, 100, pObj, ResString (ResID(IDS_GEWNUMMER, &RF()),50).Addr(), 0, 255, 255);
					m_isShow = KP_PART;
				} else {
						m_isShow = KP_NOTHING;
				}
				return true;
			}
		}
		

		if ( m_pGew)
			DELETE_OBJ ( m_pGew);

		if ( m_pGewPart)
			DELETE_OBJ ( m_pGewPart);

		CEierUhr Wait(MVWind());

		if ( m_pKH && m_pKH->GewClass()) {

//---------------Objekte an Ident hängen
//--------------------nur Objekte ( Cloned ), die in lONr
			short iTyp = OTLinie;
			long lONF = m_lONr;
			m_isCreate = false;		// Keine Geometriebildung-Change!
			
			if ( m_pGewAlle && m_pGewAlle->Count() > 0L) {
				m_pGewPart = HoleGewaesserNummer_Flaeche ( lONF, m_pKH->CodeGewNr(),m_pKH->CodeGewName(),m_pGewAlle);
			} else {
				TR_OBJTree *pModON = LadeObjektTeilKlasse ( iTyp, lONF, m_pKH->GewClass());

				m_pGewPart = SpeichernGewaesserNummer_Flaeche ( lONF, m_pKH->CodeGewNr(),m_pKH->CodeGewName(),m_pKH->GewClass(), pModON);
			
				DELETE_OBJ ( pModON);
			}

			m_isCreate = true;	 //wieder einstellen

			if ( !m_pGewPart || 0 == m_pGewPart->Count()) {
		
				MessageBox (hWnd, 
				 ResString (ResID(IDS_KEINEGEWAESSER, &RF()),50),
				 ResString (ResID(IDS_GEWAESSERANALYSE, &RF()),50),
				 MB_OK|MB_ICONHAND);
		

				DELETE_OBJ ( m_pGewPart);
				return TRUE;
			}
			
			{
			m_hWndPart = 0;
			TriasGewaesser TG ( ORWind(hWnd),GEWAESSERUEBERSICHT, RF(), m_pGewPart,m_hLib,m_pKH->GewDiffLaenge(),false);
			TG.Show(Centre);  
			if (TG.Result() == 1) {
				m_hWndPart = hWnd;
				long *pObj = TG.Obj();
				short Flag = ROSortObjNr;
				CreateORWindow ( Flag, 80, 100, pObj, ResString (ResID(IDS_GEWNUMMER, &RF()),50).Addr(), 0, 255, 255);
				m_isShow = KP_PART;
			}
			}
		}

		}
		return TRUE;

	default:
		break;
	}

	return FALSE;
}
//----------------------------------------------------------------------
STDMETHODIMP_(LRESULT) CKompiasExtension :: Notification (WPARAM iMsg, LPARAM p)
{


	switch (iMsg) {

		case DEX_GOTOBJWNDFOCUS :
		{
		m_hWnd = (HWND) p;
 
		}
		break;


		case DEX_N_PROJECTTOCLOSE:
		
		{
		if ( m_pLocProt)
			KompaktProtokoll(m_pLocProt,"\n\t==> Abschluß Project ==>\n");

		if ( m_lONrDel > 0L) {
			DEX_DeleteObject(m_lONrDel);
			m_lONrDel = -1L;
		}

		if ( m_isInit)
			DeleteStandardInformation();
		}
		break;

		case DEX_PROJECTOPEN:
		{

		if ( !m_isInit)
			CreateStandardInformation();

//		LoeschenKompaktKlassen ( );	// Leistungen und Hydraulik
		TRiASKompaktLoader();

		m_iFunction = KompaktMenu(false);


	// aktuelles Projektverzeichnis besorgen
		if ( !m_pLocDir) {
			m_pLocDir = new char [_MAX_PATH];
			if ( m_pLocDir != NULL ) {
				if (DEX_GetActiveProject (m_pLocDir) == NULL) {
					// Projekt nicht eröffnet
					DELETE_OBJ ( m_pLocDir);
					break;
				}
			}
		}

		SetzeKompaktDatenPfad(m_pLocDir);

		HWND hWnd = __hWndM;


		KompaktFunktion ( m_iFunction,hWnd);

		}
		break;

//////////////////////////////////////////////////////////////////
		case DEX_DELOBJECT:
		{

		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		if ( m_pModObj ) {
			long lONr = (long)p;
			CTable t (*m_pModObj);
			if (t.Find(&lONr))
				t.Delete();
		}
		if ( m_pGewText) {
			long lONr = (long)p;
			CTable t (*m_pGewText);
			if (t.Find(&lONr))
				t.Delete();
		}
		if ( m_lONr != -1L) {
			m_lONrBauw = -1L;
			m_lONrGew = -1L;
			m_lONr = -1L;
		}

		MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		}
		break;

	//////////////////////////////////////////////////////////////////
		case DEX_N_SAVECOMPLETED:
		{


		if ( m_pModObj) {
			CTreeLoeschen ( m_pModObj);
			DELETE_OBJ ( m_pModObj);
		}
		if ( m_pGewText) {
			CTextLoeschen ();
		}

//		LoeschenKompaktKlassen ( );	// Leistungen und Hydraulik

		}
		break;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
		case DEX_N_SAVEOTHERSTORAGE:
		{
		if ( m_pModObj) {
			CTreeLoeschen ( m_pModObj);
			DELETE_OBJ ( m_pModObj);
		}
		if ( m_pGewText) {
			CTextLoeschen ();
		}

//		LoeschenKompaktKlassen ( );	// Leistungen und Hydraulik
		}
		break;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
		case DEX_N_SAVESAMESTORAGE:
		{
		if ( m_pModObj) {
			CTreeLoeschen ( m_pModObj);
			DELETE_OBJ ( m_pModObj);
		}
		if ( m_pGewText) {
			CTextLoeschen ();
		}

//		LoeschenKompaktKlassen ( );	// Leistungen und Hydraulik

		}

		break;
//////////////////////////////////////////////////////////////////
		case DEX_N_HANDSOFFSTORAGE:
		{
		if ( m_pModObj) {
			CTreeLoeschen ( m_pModObj);
			DELETE_OBJ ( m_pModObj);
		}
		if ( m_pGewText) {
			CTextLoeschen ();
		}

//		LoeschenKompaktKlassen ( );	// Leistungen und Hydraulik

		}
		break;
//////////////////////////////////////////////////////////////////
		case DEX_OBJWNDCLOSED :
		{
		if ( m_hWndPart == (HWND) p)
			m_hWndPart = 0;
		if ( m_hWnd == (HWND)p)
			m_isShow = KP_NOTHING;
		}
		break;
///////////////////////////////////////////////////////////////////////
		case DEX_MODIFYMERKMAL:
		{
		CEierUhr Wait ( MVWind());

		MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

		m_lONr = KompaktGewaesser(p);
		if ( m_lONr != -1) {

			char *pGewNr = AktualisiereGewaesserNummer (  m_lONr, m_pKH->CodeGewNr());
			if ( pGewNr ) {
				char *pMalte = m_hLib->GewaesserNameHolen ( pGewNr);
				if ( pMalte && *pMalte != '\0') {
					SetObjektWert( m_lONr, m_pKH->CodeGewName(), pMalte);
					m_lONr = -1L;
					
				} else {
// Völlig neu
//--------------------> GewNr existiert in KompaktKataster nicht- anlegen !

					char *pBuffer = new char [_MAX_PATH];
					if (pBuffer) {
						long lIdent = DEX_GetObjIdent ( m_lONr);
						ulong lSMCode = DEX_GetObjNameMCode(lIdent);
						GetStandardMCode ( m_lONr, lSMCode, pBuffer);
					}

					long lLaenge = 0L;
					lLaenge = LinienLaenge(m_lONr);
					char *pGewName = TRiASGewaesserName ( m_lONr,m_pKH->CodeGewName());
					if ( pGewName ) {

						if ( m_hLib->GewaesserNeuAnlegen ( pGewNr, pGewName, lLaenge)) {
							DELETE_OBJ ( pGewName);
						} else {
							RestoreGewNr(m_lONr,pBuffer);
							DELETE_OBJ ( pGewName);
						}

					} else {
						if ( !m_hLib->GewaesserNeuAnlegen ( pGewNr, pGewNr, lLaenge))
							RestoreGewNr(m_lONr,pBuffer);

					}
					DELETE_OBJ(pBuffer);

//					if ( m_pGewAlle)
//						AktualisiereGesamtGewaesser(m_lONr,pGewNr,lLaenge);
				}

				DELETE_OBJ ( m_pGewAlle);
				DELETE_OBJ ( pGewNr);
			
			}
		} else {
	//  Bauwerke abfragen !!!!
			if ( m_isBauw ) {
				m_lONr = KompaktBauwerk(p);
				if ( m_lONr != -1 ) {
	// KK991123
//					if ( m_lONrGew) {
					if ( m_lONrGew != 0L && m_lONrGew != -1L) {
						m_lONrBauw = m_lONr;
						m_isBauw = false;
	
						MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//						MyUnRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
						if(!BestimmeBauwerk(m_hWnd,false)) {

//							UnRegisterNotification (DEX_DELOBJECT);
//							DEX_DeleteObject(m_lONrBauw);
//							if ( m_lONrDel > 0L) {
//								DEX_DeleteObject(m_lONrDel);
//								m_lONrDel = -1L;
//							}

//							m_lONrDel = m_lONrBauw;

//							RegisterNotification (DEX_DELOBJECT);
							{
							ErrInstall EI (EC_INVADDR);

							DEX_DeleteObject(m_lONr);
							}
							m_lONrBauw = -1L;
							m_lONrGew = -1L;
							m_lONr = -1L;
							m_isBauw = false;
						}
						MyRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
//						MyRegisterNotification (DEX_N_OBJECTCREATED,m_bChange);
					}
			
				} else {
				// Höhenabgleich bei Überschwemmungsgebiet ( Objektname - Höhenwert
					m_lONr = KompaktUeberschwemmung(p);
					if ( m_lONr != -1) {
						MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
						AktualisiereHoehenWert(m_lONr);
						MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
						m_lONr = -1L;
					}
				}
			}
		}

		}
		break;
///////////////////////////////////////////////////////////////////////////////////
		case DEX_N_OBJECTCREATED :

		{
			KatasterLaden();

			m_isNewOR = true;		//Fenster bilden

			m_isBauw = false;
			m_lONr = KompaktGewaesser(p);
			if ( m_lONr != -1 ) {
				MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
				if (SetzeKompaktName (m_lONr,0)) {
					m_lONrGew = m_lONr; 
					MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
				} else {
//					RegisterNotification (DEX_DELOBJECT);
					{
					ErrInstall EI (EC_INVADDR);

					DEX_DeleteObject(m_lONr);
					}
					m_lONr = -1;
					m_lONrGew = -1;
				}
			// RICHTIG ???
				MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
			} else {

			#if _MSC_VER >= 1100
				m_lONrBauw = -1;
			#endif

				m_lONr = KompaktBauwerkEx(p);
				if ( m_lONr != -1 ) {
					
					if ( m_lONrGew == -1L) {
						if ( DEX_GetActiveORWnd() == m_hWnd) {

							long lONr1 =  DEX_GetActiveObject ( m_hWnd );

							long lONr2 = KompaktGewaesser(LPARAM(lONr1));
							if ( lONr2 != -1 ) {
								MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
								m_lONrGew = lONr2; 
		// Prüfung, ob Gewässer im KompaktKataster
								if (!KompaktKatasterDefiniert_ONr (m_lONrGew))
									RestoreBauwAnlegen(true);
							} else {
								RestoreBauwAnlegen(true);
						
								break;
							}
						} else {
							RestoreBauwAnlegen(true);

							break;
						}

					}

					if ( m_lONrBauw != m_lONr) {
						MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
						m_isBauw = true;
						if ( SetzeKompaktName (m_lONr,1)) {
							m_lONrBauw = m_lONr;
							m_isBauw = true;

			#if _MSC_VER >= 1100
//	27.6.99						MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
		
							if(!BestimmeBauwerk(m_hWnd,false)) {
								m_lONrGew = -1L;
								m_lONr = -1L;
								m_isBauw = false;
							}

			#endif

						} else {
							RestoreBauwAnlegen(false);
						}

						MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

					} else {
						m_lONrBauw = -1L;
					}
				}
			}
		}
		break;

		case DEX_OBJECTCHANGED:
		{

			KatasterLaden();

			m_isNewOR = false;		//kein Fenster bilden

//neu
			m_lONr = KompaktGewaesser(p);
			if ( m_lONr != -1 ) {
				MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
			} else {

				m_lONrBauw = -1L;
				m_lONrGew = -1L;
				m_lONr = -1L;
				m_isBauw = false;

				m_lONr = KompaktBauwerk(p);

				if ( m_lONr != -1 ) {
						MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
// Versuch
						m_lONrBauw = m_lONr;

						char *pGewNr = HoleTRiASGewaesserNummer (m_lONr,m_pKH->CodeGewNr());

						if ( pGewNr ) {
							if ( strncmp ( pGewNr, "Noname",6) != 0 ) {
								if ( KompaktKatasterDefiniert(pGewNr)) {
									m_lONrGew = HoleEinzelGewaesser(m_pKH->CodeGewNr(),pGewNr);
									if (m_lONrGew > 0L) {
										m_isBauw = true;

										MyUnRegisterNotification (DEX_OBJECTCHANGED,m_bChange);
			
										if(!BestimmeBauwerk(m_hWnd,false)) {
											m_lONrGew = -1L;
											m_lONr = -1L;
											m_isBauw = false;
										}

									} else {
										m_lONrBauw = -1L;
									}
								} else {
									m_lONrBauw = -1L;
								}
							} else {
								m_lONrBauw = -1L;
							}
							DELETE_OBJ ( pGewNr);

						} else {
							m_lONrBauw = -1L;
							m_lONrGew = -1L;
							m_lONr = -1L;
							m_isBauw = false;
						}

				
				}
			}
//neu
/*------------------------------------
			m_isBauw = false;
			m_lONr = KompaktGewaesser(p);
			if ( m_lONr != -1 ) {
				MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
				if (SetzeKompaktName (m_lONr,0)) {
					m_lONrGew = m_lONr; 
				} else {
					m_lONrDel = m_lONrGew;
					RegisterNotification (DEX_DELOBJECT);
//					DEX_DeleteObject(m_lONrGew);
					m_lONrGew = -1;
				}
//				MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
			} else {
				m_lONr = KompaktBauwerk(p);
				if ( m_lONr != -1 ) {
					if ( m_lONrGew == -1L) {
						long lONr1 =  DEX_GetActiveObject ( m_hWnd );
						long lONr2 = KompaktGewaesser(LPARAM(lONr1));
						if ( lONr2 != -1 ) {
							MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
							m_lONrGew = lONr2; 
						}

					}
					if ( m_lONrBauw != m_lONr) {
						MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
						if ( SetzeKompaktName (m_lONr,1)) {
							m_lONrBauw = m_lONr;
							m_isBauw = true;
						} else {
							m_lONrDel = m_lONrBauw;
							RegisterNotification (DEX_DELOBJECT);
	//						DEX_DeleteObject(m_lONrBauw);
							m_lONrBauw = -1;
							m_isBauw = false;
						}
//						MyUnRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);

					} else {
						m_lONrBauw = -1L;
					}
				}
			}
		-------------------------------------------------*/
		}
		break;

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//		case DEX_OBJECTUNSELECTED:
//		{
//#if _MSC_VER >= 1100
//#pragma message ("KOMPIAS.CXX:==> OBJECTUNSELECTED als MODIFYMERKMAL-Ersatz !!!")

//		if (0L < m_lONr && m_lONr == m_lONrGew) {
//			AbgleichFeature(m_lONr);
//		}
//#endif

//		}
//		break;
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
		case DEX_OBJECTSELECTED:
		{

		m_lONrBauw = -1L;
		m_lONrGew = -1L;
		m_lONr = KompaktGewaesser(p);
		if ( m_lONr != -1 ) {
			MyRegisterNotification (DEX_MODIFYMERKMAL,m_bMerkmal);
			m_lONrGew = m_lONr;
		}

		}
		break;
////////////////////////////////////////////////////////////////////////
		case DEX_QUERYRECHOBJECT:
		{
//---------------GEWNR- anzeigen ---------------------------
		if ( m_pKH && m_pKH->CodeGewNr()) {
			TARGETMERKMAL TM;
			memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
			TM.dwSize = sizeof (TARGETMERKMAL);
			TM.lTarget = ((RECHOBJECT *)p)->lONr;
			TM.lMCode = m_pKH->CodeGewNr();
			TM.imaxLen = (( RECHOBJECT *)p)->iTextLen;
			TM.iTTyp = TT_Objekt;
			TM.pMText = (( RECHOBJECT *)p)->lpText;
			DEX_GetTextMerkmal ( TM );
		}
		}
		break;
//-----------------------------------------------------------------------
		default:
		break;

	}
	return CTriasExtension :: Notification( iMsg,p);		// kein Fehler

}
//-------------------------------------------------------------------------

STDMETHODIMP_(LRESULT) CKompiasExtension ::  WindowsNotification (UINT wMsg, WPARAM, LPARAM p)
{


		if ( m_wMsg1 == wMsg ) {
// Achtung - TESTEN - real = 4 , double = 8, long double = 10;

//--------------Hier kommt Malte -----------
//	"MALTESHYDRAULIKPUNKT"
//------------Versuch Hydraulik-Test-----------------------
		// Maltes Punkt holen !

		HYDRAULIK HD;
	   	memset (&HD,'\0',sizeof(HYDRAULIK));
		HD.dwSize = sizeof(HYDRAULIK);

		HD.pcGewaesserNr = ((HYDRAULIK *)p)->pcGewaesserNr;
		HD.lPos = ((HYDRAULIK *)p)->lPos;
		HD.dHoehe =((HYDRAULIK *)p)->dHoehe;

		BringWindowToTop ( hWnd());

//		if (!HydraulikPunkt (p)) {
		if (!HydraulikPunkt (LPARAM(&HD))) {
			MessageBox (__hWndM,
			 ResString (ResID(IDS_KEINEUEBERSCHWEMMUNG, &RF()),90),
//			 "Kein Überschwemmungsgebiet angelegt !",
			 ResString (ResID(IDS_STRHYDRAULIK, &RF()),90),
			 MB_OK|MB_ICONHAND);
		
		} else {
			ZeigeUeberschwemmungsPunkt ();
		}
		
	}

//	"GEWAESSERABGLEICH"
	if ( m_wMsg2 == wMsg ) {

//------------Versuch GewaesserAbgleich------------------------
		AbgleichGewaesserNummer();
	}

//	"GEWAESSERKATASTER"
	if ( m_wMsg3 == wMsg ) {
		if ( m_pLocDir)
			DELETE_OBJ ( m_pLocDir);
//------------Versuch GewaesserKatasterAnlegen------------------------
		m_iFunction = KompaktMenu(false);

		KompaktFunktion ( m_iFunction,hWnd());

	}

	if ( m_wMsg4 == wMsg ) {
		MischeHydraulik();
	}

	if ( m_wMsg5 == wMsg ) {
		//	Objektname in Höhe übertragen
		AbgleichHydraulikFlaechen();
	}
	return false;
}

//------------------------------------------------------------------------
HRESULT CKompiasExtension :: DefineWasser ( void)

{
		KatasterLaden();

		if ( !isActive()) 
			return S_FALSE;

		OBJSTATISTIK OS;
   		memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);
		OS.lONr =  DEX_GetActiveObject ( m_hWnd );

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
			if ( OS.iObjTyp == OT_KANTE) {

				if ( !ObjektIstGewaesser ( OS.lONr))
					return S_FALSE;
				m_lONr = OS.lONr;
			} else {
					return S_FALSE;
			}
		} else {
					return S_FALSE;
		}
	

		return DefineObjektEigenschaft();
}
//======================================================================================
HRESULT CKompiasExtension :: DefineEreignis ( void)

{
		KatasterLaden();

		if ( !isActive()) 
			return S_FALSE;

		if ( m_pKH ) {
			if ( !m_pKH->BauwClass())
				m_pKH->Aktualisieren (PM_BAUWERKE);
		}

		OBJSTATISTIK OS;
   		memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);
		OS.lONr =  DEX_GetActiveObject ( m_hWnd );

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {

			if ( OS.iObjTyp == OT_PUNKT) {

				if ( ObjektIstBauwerk (OS.lONr)) {
					m_lONr = OS.lONr;
					return DefineObjektEigenschaft();
				} else {
					return S_FALSE;
				}
			}

			if ( OS.iObjTyp == OT_KANTE) {

				if ( !ObjektIstBauwerk ( OS.lONr))
					return S_FALSE;
				m_lONr = OS.lONr;
				return DefineObjektEigenschaft();
			} else {
				return S_FALSE;
			}
		}
		return S_FALSE;

}
//-----------------------------------------------------------------
HRESULT CKompiasExtension :: DefineObjektEigenschaft ( void)

{

		if ( m_lONr == -1L || m_lONr == 0L)
			return S_FALSE;

		if ( !m_pKH || m_pKH->CodeGewNr() == 0L)
			return S_FALSE;

		BAUWERKE BW;
	   	memset (&BW,'\0',sizeof(BAUWERKE));
		BW.dwSize = sizeof(BAUWERKE);
		BW.iIdentNrZuordnung = 0;
		BW.pcGewaesserNr = NULL;
		BW.lBeginn = 0L;
		BW.lEnde = 0;

		if ( ObjektIstGewaesser(m_lONr)) {
			char *pGewNr = HoleGewaesserNummer (  m_lONr, m_pKH->CodeGewNr());
			if ( pGewNr ) {
	// Test, ob in Kataster vorhanden !!!!
				if ( !KompaktKatasterDefiniert(pGewNr)) {
					DELETE_OBJ ( pGewNr);
					return S_FALSE;
				}

				BW.pcGewaesserNr = pGewNr;
				try {
					m_hLib->KompaktObjektEigenschaft(m_hWnd,&BW);
				} catch (...) {
					MessageBox (__hWndM, 
					 ResString (ResID(IDS_ERRORKOMPAKT, &g_pTE->RF()),80),
					 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
					 MB_OK|MB_ICONHAND);

				}
				DELETE_OBJ ( pGewNr);
				return S_OK;
			}
			return S_FALSE;
		}

		if ( ObjektIstBauwerk(m_lONr)) {

			long lMGewNr = m_pKH->CodeGewNr();
			long lMVon = m_pKH->CodeBauwAnfStat();
			long lMBis = m_pKH->CodeBauwEndStat();
			long lIdent = DEX_GetObjIdent(m_lONr);
			long lBauw =  m_pKH->CodeBauwBez();


			BW.iIdentNrZuordnung = BauwerkeTyp(lIdent);
			char *pGewNr = HoleTRiASGewaesserNummer (  m_lONr, m_pKH->CodeGewNr());
			if ( pGewNr ) {
	// Test, ob in Kataster vorhanden !!!!
				if ( !KompaktKatasterDefiniert(pGewNr)) {
					DELETE_OBJ ( pGewNr);
					return S_FALSE;
				}

				BW.pcGewaesserNr = pGewNr;

				char *pBuff = new char [_MAX_PATH];
				char *pBauw = new char [_MAX_PATH];
				if ( !pBuff || !pBauw) {
					DELETE_OBJ ( pBauw);
					DELETE_OBJ ( pBuff);
					DELETE_OBJ ( pGewNr);
					return S_FALSE;
				}

				// MerkmalsWert holen

				TARGETMERKMAL tm;
				tm.dwSize = sizeof(TARGETMERKMAL);
				tm.iTTyp = TT_Objekt;

				tm.lMCode = lBauw;		// MerkmalsCode
				*pBauw = '\0';		
				tm.lTarget = m_lONr;		// Objekt
				tm.imaxLen = _MAX_PATH;
				tm.pMText =pBauw;		// Puffer

				{
				ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
				DEX_GetTextMerkmal ( tm );
				}

				BW.pcBauwerksBezeichnung = pBauw;



				tm.lMCode = lMVon;		// MerkmalsCode
				*pBuff = '\0';		
				tm.lTarget = m_lONr;		// Objekt
				tm.imaxLen = _MAX_PATH;
				tm.pMText =pBuff;		// Puffer

				{
				ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
				DEX_GetTextMerkmal ( tm );
				}
				if (*pBuff != '\0') 
				BW.lBeginn = atol ( pBuff);

				tm.lMCode = lMBis;		// MerkmalsCode
				*pBuff = '\0';		
				tm.lTarget = m_lONr;		// Objekt
				tm.imaxLen = _MAX_PATH;
				tm.pMText =pBuff;		// Puffer

				{
				ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
				DEX_GetTextMerkmal ( tm );
				}
				if (*pBuff != '\0') 
				BW.lEnde = atol ( pBuff);

				DELETE_OBJ ( pBuff);

				try {
					m_hLib->KompaktObjektEigenschaft(m_hWnd,&BW);
				} catch (...) {
					MessageBox (__hWndM, 
					 ResString (ResID(IDS_ERRORKOMPAKT, &g_pTE->RF()),80),
					 ResString (ResID(IDS_STRCAPTION, &g_pTE->RF()),80),
					 MB_OK|MB_ICONHAND);

				}

				DELETE_OBJ ( pGewNr);
				DELETE_OBJ ( pBauw);
				return S_OK;
			}

		}
		return S_FALSE;

}
//---------------------------------------------------------------------------
// File: KOMPIAS.CXX
