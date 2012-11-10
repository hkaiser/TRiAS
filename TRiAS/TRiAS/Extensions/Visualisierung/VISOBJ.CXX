// Objektbezogene Visualiserung -----------------------------------------------
// File: VISOBJ.CXX

#include "visobjp.hxx"

#include <xtsnaux.hxx>

#define INITGUIDS

#include "visobj.h"	// ResourceKonstanten für dieses Beispiel
#include "resource.h"

#include "Strings.h"
#include "colcntrl.hxx"

#if defined(EXTVIS)
#include <icustom.hxx>
#include <vismguid.h>
#include "vismtree.hxx"
#endif

#include "yy1stype.hxx"
#include "VisInfoObj.h"

#define _TriasTLB_H_
#include <dirisole.h>
#include "version.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Funktionsprototypen
short OTypToBits (short iOTyp);
bool IsNotInPbd (long lMCode, long lIdent);

//EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
EXTERN_C const IID IID_IRawVisInfo = {0x4BAB20A3,0xA922,0x11D1,{0x85,0x88,0x00,0x60,0x08,0x75,0x13,0x8A}};
//#if _MSC_VER >= 1100
//EXTERN_C const CLSID CLSID_TRiASCSRectangleGeometry = {0xCF648167,0x9E24,0x11D1,{0xBA,0x1C,0x08,0x00,0x36,0xD6,0x38,0x03}};
//EXTERN_C const CLSID CLSID_TRiASCSPointGeometry = {0x3327AD94,0xA2B1,0x11D1,{0xA0,0x51,0x00,0x60,0x97,0x55,0x66,0xB4}};
//#endif // _MSC_VER >= 1100

// globale Daten
const ResID resMissing ((LPCSTR)NULL, NULL);

// 
// NEU: Die folgende Funktion KANN vom Nutzer bereitgestellt werden, wenn eine
// TypeLib registriert werden soll. Auch die TypeLib muß einen eigenen GUID
// besitzen !
//
BOOL GetTypeLibGUID (GUID &guidTLib)
{
	memcpy (&guidTLib, &LIBID_VisInfoLib, sizeof (GUID));
	return true;		// TypeLib registrieren/deregistrieren
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_ObjVisInfoExtension, 
				TEXT("TRiAS.ObjVisInfo.1"), IDS_LONGCLASSNAME,
				VISINFO_MAJORVERSION, VISINFO_MINORVERSION, EFPreLoad|EFPriorityLoad7);
		return fSuccess;
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_ObjVisInfoExtension, 
				TEXT("TRiAS.ObjVisInfo.1"));
	}

return true;	// alles ok
}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als die beiden Parameter die ResID's der
// im Hauptfenster und im ObjektRechercheFenster einzuhängeneden Menu's 
// übergeben bekommt.
#pragma warning (disable: 4355)

CVisObjExtension::CVisObjExtension (void)
	: CTriasExtension()
#if _ATL_VER < 0x0200
		  , m_cp(this)
#endif // _ATL_VER
{
	m_pActProject = NULL;
	m_pActSight = NULL;

	m_lSichtVisMCode = -1L;
//	m_lObjVisMCode = -1L;

	m_lSichtLegMCode = -1L;

	m_fAllVisErrIgnore = false;	// Visualisierungsfehler bearbeiten
	ResetAutoColors();			// im weiteren Farben automatisch zuweisen
	m_fModifyAllSelected = false;	// nur aktiviertes Objekt beeinflussen
	m_fFullVisInfo = false;		// nur Änderung in VisInfo speichern
	m_fShowHidden = false;		// versteckte Objekte nicht anzeigen
	m_fRebuildView = false;	

	m_fIsDrawing = false;
				
	m_lIdentHandled = -1L;		// keine Fehlerbehandlung aktiv
				
	m_pVIE = new CIgnoreVisErrorTree;

#if defined(EXTVIS)
	m_pVMT = new CVisModuleTree;
	m_hDC = 0;
	m_hTargetDC = 0;
	m_fOleInitialized = false;
	m_fForceShutdown = false;	// darf nicht entladen werden, wenn OLE initialisiert wurde
#endif	

	m_pMWert = new char [MWERTSIZE+1];

	m_CCDlg = NULL;	
	m_pMenu = NULL;
}

#pragma warning (default: 4355)

// Destruktor -----------------------------------------------------------------
CVisObjExtension::~CVisObjExtension (void) 
{
	DELETE_OBJ (m_pActProject);
	DELETE_OBJ (m_pActSight);
	DELETE_OBJ (m_pVIE);
#if defined(EXTVIS)
	DELETE_OBJ (m_pVMT);
#endif
	DELETE_OBJ (m_pMWert);

	DELETE_OBJ (m_CCDlg);
	DELETE_OBJ(m_pMenu);
}


// Im folgenden müssen alle durch diese Erweiterung überladenen virtuellen
// Funktionen definiert werden.

// Diese Funktion wird (einmalig) gerufen, wenn die Erweiterung vollständig
// installiert ist

STDMETHODIMP_(BOOL) CVisObjExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return false;

// aktuellen TRiAS-Namen aus Registry besorgen
CCurrentUser regCfg (KEY_READ, g_cbRegConfig);
DWORD dwSize = _MAX_PATH;

	if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize))
		strcpy (g_cbTRiAS, g_cbCopyrightName);		// default

// Menupunkt im Hauptfenster installieren
	if (iMode == LEFullLoad) {
		InstallMenuItem (IDM_IGNOREALLERRORS, IDS_IGNOREALLERRORS, IMINormalMenu, STYLE_MENU_POS);

	// Darstellungsparameter/Ausblenden rücksetzen
		InstallMenuItem ((UINT)-1, 0, IMINormalMenu, STYLE_MENU_POS, 4);
		InstallMenuItem (IDM_REVOKEHIDE, IDS_REVOKEHIDE, IMINormalMenu, STYLE_MENU_POS, 4);
		InstallMenuItem (IDM_VISOBJREMOVE, IDS_VISOBJREMOVE, IMINormalMenu, STYLE_MENU_POS, 4);

	// Darstellungsparameter importieren/exportieren
		InstallMenuItem ((UINT)-1, 0, IMINormalMenu, STYLE_MENU_POS, 4);
		InstallMenuItem (IDM_VISINFOEXPORT, IDS_VISINFOEXPORT, IMINormalMenu, STYLE_MENU_POS, 4);
		InstallMenuItem (IDM_VISINFOIMPORT, IDS_VISINFOIMPORT, IMINormalMenu, STYLE_MENU_POS, 4);

	// Farbregelung
		InstallMenuItem (IDM_COLORCONTROL, IDS_COLORCONTROL, IMINormalMenu, STYLE_MENU_POS, 3);

	// Ausgeblendete Objekte Anzeigen
		InstallMenuItem (IDM_SHOWHIDDEN, IDS_SHOWHIDDEN, IMINormalMenu, THEMA_MENU_POS, 13);

	// MenuItemMap für VMD's initialisieren
		m_VMDMap.FInit(MenuOffset());		// liefert false, wenn keine VMD's installiert sind
	}

// Menu in ORWnds installieren
	if (NULL == m_pMenu) {
		ATLTRY(m_pMenu = new Menu(ResID(OBJEXTENSIONMENU, &RF())));
		if (NULL == m_pMenu) return FALSE;
	}

INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex();
	imi.iFlag = IMIObjWnd|IMITopLevel;
	imi.iMenuNum = OR_STYLE_MENU_POS;
	imi.iMenuID = -1;

// PopUpMenu und MenuText holen
char cbBuffer[_MAX_PATH];
HMENU hMenu = m_pMenu -> Handle(API_MENU_HMENU);

	imi.hMenu = GetSubMenu (hMenu, 0);
	TX_ASSERT(NULL != imi.hMenu);
	GetMenuString (hMenu, 0, cbBuffer, sizeof(cbBuffer), MF_BYPOSITION);
	imi.pMenuText = cbBuffer;
	DEX_InstallMenuItem (imi);

	if (iMode != LoadState()) return true;

// FehlerNotifikation
	RegisterNotification (DEX_ERRORMESSAGE);

// Notifikationen bei ProjektWechsel
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_N_PROJECTTOCLOSE);

// Notifikationen bei SichtWechsel/Sicht löschen/Sicht erzeugen
	RegisterNotification (DEX_SIGHTTOSELECT);
	RegisterNotification (DEX_DELETEVIEW);
	RegisterNotification (DEX_VIEWCREATED);
	RegisterNotification (DEX_N_COPYVISINFO);

// Notifikation bei Objekt löschen
	RegisterNotification (DEX_OBJECTTODELETE);
	
// Notifikation aus RechercheFenster
	RegisterNotification (DEX_QUERYRECHOBJECT);

// Notifikation beim laden eines Identifikators/Objektes um zu entscheiden, 
// ob eine Einmischung in den Prozeß des Zeichnens notwendig ist.
	RegisterNotification (DEX_DRAWIDENT);
	RegisterNotification (DEX_DRAWIDENTEX);
	RegisterNotification (DEX_DRAWOBJECT);
#if defined(EXTVIS)
	RegisterNotification (DEX_ERASEBKGND);
	RegisterNotification (DEX_SIGHTSELECTED);
	RegisterNotification (DEX_SERVERCLOSED);	// Informieren lassen, wenn TRiAS geschlossen wird
#endif
// Palette zuleiten
	RegisterNotification (DEX_SETNEWPALETTE);

// vor/nach dem zeichnen
	RegisterNotification (DEX_PAINTTOPLAYER);

// evtl. bereits offenes Projekt/VisObjMCode holen
	if (InitMCodes ()) DEX_RebuildSight();

#if defined(EXTVIS)
#if defined(WIN32)
	if (OleInitialize (NULL) == NOERROR)
		m_fOleInitialized = true;
	else
		m_fOleInitialized = false;
#else
/*
 * Check if our host did CoInitialize by trying CoGetMalloc.
 * If it doesn't work, then we'll CoInitialize ourselves.
 */
LPMALLOC pIMalloc = NULL;
HRESULT hr = CoGetMalloc(MEMCTX_TASK, &pIMalloc);

	if (SUCCEEDED(hr))
		pIMalloc -> Release();
	else {
		hr = OleInitialize (NULL);
		if (FAILED(hr)) return false;
		m_fOleInitialized = true;
	}
#endif // WIN32
#endif // EXTVIS

// ObjektParser initialisieren
	if (!InitYY1Parse()) return false;
	
return true;
}

// Diese Funktion wird gerufen, bevor die Erweiterung freigeben werden soll
STDMETHODIMP_(BOOL) CVisObjExtension::UnLoadExtension (void)
{
#if defined(EXTVIS)
// wenn OLE initialisiert wurde, dann nur ganz am Ende wirklich entladen
	if (m_fOleInitialized && !m_fForceShutdown)
		return false;
#endif	// EXTVIS
		
// Menupunkt rausnehmen
	if (LoadState() == LEFullLoad) {
		RemoveMenuItem (IDM_IGNOREALLERRORS, IMINormalMenu, STYLE_MENU_POS);

	// Darstellungsparameter importieren/exportieren
		RemoveMenuItem (IDM_VISINFOIMPORT, IMINormalMenu, STYLE_MENU_POS);
		RemoveMenuItem (IDM_VISINFOEXPORT, IMINormalMenu, STYLE_MENU_POS);
		RemoveMenuItem ((UINT)-1, IMINormalMenu, STYLE_MENU_POS, 4);			// MF_SEPARATOR

	// Darstellungsparameter/Ausblenden rücksetzen
		RemoveMenuItem (IDM_REVOKEHIDE, IMINormalMenu, STYLE_MENU_POS);
		RemoveMenuItem (IDM_VISOBJREMOVE, IMINormalMenu, STYLE_MENU_POS);
		RemoveMenuItem ((UINT)-1, IMINormalMenu, STYLE_MENU_POS, 4);			// MF_SEPARATOR

	// Farbregelung
		RemoveMenuItem (IDM_COLORCONTROL, IMINormalMenu, STYLE_MENU_POS);

	// Ausgeblendete Objekte Anzeigen
		RemoveMenuItem (IDM_SHOWHIDDEN, IMINormalMenu, THEMA_MENU_POS);
	}

// Notifikationen freigeben
// vor/nach dem zeichnen
	UnRegisterNotification (DEX_PAINTTOPLAYER);
	UnRegisterNotification (DEX_SETNEWPALETTE);	// Palette abmelden
	UnRegisterNotification (DEX_QUERYRECHOBJECT);
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);
	UnRegisterNotification (DEX_OBJECTTODELETE);
	UnRegisterNotification (DEX_N_COPYVISINFO);
	UnRegisterNotification (DEX_VIEWCREATED);
	UnRegisterNotification (DEX_DELETEVIEW);
	UnRegisterNotification (DEX_SIGHTTOSELECT);
	UnRegisterNotification (DEX_DRAWIDENTEX);
	UnRegisterNotification (DEX_DRAWIDENT);
	UnRegisterNotification (DEX_DRAWOBJECT);
#if defined(EXTVIS)
	UnRegisterNotification (DEX_SERVERCLOSED);
	UnRegisterNotification (DEX_SIGHTSELECTED);
	UnRegisterNotification (DEX_ERASEBKGND);
#endif
	UnRegisterNotification (DEX_ERRORMESSAGE);	// FehlerNotifikation
//	if (m_fRebuildView)	// wenn notwendig, dann auch diese Message abmelden
//		UnRegisterNotification (DEX_PAINTTOPLAYER);

// Sicht ohne uns neu aufbauen
	if (m_pActProject)	// wenn Projekt geöffnet ist
		DEX_PostRebuildSight();

	EndYY1Parse();		// ObjektParser wieder deinitialisieren
	
#if defined(EXTVIS)
	if (m_fOleInitialized)
		OleUninitialize();
#endif

	return CTriasExtension::UnLoadExtension();
}


// Die folgende Funktion wird gerufen, wenn eine der angeforderten 
// Notifikationen ankommt.
STDMETHODIMP_(LRESULT) CVisObjExtension::Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg) {
	case DEX_PROJECTOPEN:
		{
		short iDesc = (short)p;

			DELETE_OBJ (m_pActProject);
			m_pActProject = new char [_MAX_PATH +1];
			if (DEX_GetActiveProject (m_pActProject) == NULL) {
				DELETE_OBJ (m_pActProject);
				break;
			} 
		// MerkmalsCodes initialisieren
			m_lSichtVisMCode = GetViewMCode();
			m_lSichtLegMCode = GetViewLegMCode();

#if defined(EXTVIS)
		// Visualisierungsmodule bedienen
			if (m_pVMT) 
				m_pVMT -> OnProjectChange (__hWndM, PROJECTCHANGE_OPENED, m_pActProject);
#endif
		}
		break;

	case DEX_SIGHTTOSELECT:
		{
		char *cptr = (char *)p;

			DELETE_OBJ (m_pActSight);
			if (cptr != NULL) {
				m_pActSight = new char [_MAX_PATH +1];
				if (m_pActSight) {
					strcpy (m_pActSight, cptr);
					m_lSichtVisMCode = GetViewMCode(m_pActSight);
					m_lSichtLegMCode = GetViewLegMCode();
				}
			}

		// Visualisierungsfehler wieder melden
			m_fAllVisErrIgnore = false;
			if (m_pVIE) 
				m_pVIE -> EveryDelete();
			ResetAutoColors();
		}
		break;

#if defined(EXTVIS)
	case DEX_SIGHTSELECTED:
		if (m_pVMT) m_pVMT -> OnViewChange (__hWndM, VIEWCHANGE_SELECTED, (char *)p);
		break;

	case DEX_ERASEBKGND:
		m_hDC = ((HDC *)p)[0];			// to draw on
		m_hTargetDC = ((HDC *)p)[1];	// drawtarget
		m_fIsDrawing = true;			// #HK011114
		break;
		
	case DEX_SERVERCLOSED:
		m_fForceShutdown = true;
		break;		// jetzt darf dieser Erweiterung entladen werden, selbst, wenn
				// OLE initialisert wurde
#endif
		
	case DEX_DELETEVIEW:
#if defined(EXTVIS)
		if (m_pVMT) {
			m_pVMT -> OnViewChange (__hWndM, VIEWCHANGE_DELETED, 
						(char *)p);
		}
#endif
		return HandleDeleteSight ((char *)p);
		
	case DEX_VIEWCREATED:
		return HandleViewCreated ((VIEWCREATED *)p);

	case DEX_N_COPYVISINFO:
		return HandleViewCreatedIdentEx(((COPYVISINFO *)p) -> lIdent, (COPYVISINFO *)p, ((COPYVISINFO *)p) -> iOTyp);

	case DEX_N_PROJECTTOCLOSE:
#if defined(EXTVIS)
		if (m_pVMT) {
			m_pVMT -> OnProjectChange (__hWndM, PROJECTCHANGE_CLOSED,
						   m_pActProject);
		}
		if (m_pVMT) {
		// alles, was nicht mehr gebraucht wird, wieder loslassen
			m_pVMT -> EveryDelete();	// VMD's freigeben
			CoFreeUnusedLibraries();
		}
#endif
		DELETE_OBJ (m_pActProject);
		m_fAllVisErrIgnore = false;
		if (m_pVIE) 
			m_pVIE -> EveryDelete();
		ResetAutoColors();
		DeInitMCodes();
		break;

	case DEX_DRAWIDENT:
#if defined(_USE_DEFAULTVIEW_FOR_TEXTS)
		return (LRESULT)(GetIDMode ((long)p) | GetIDMode ((long)p, g_cbDefaultVisInfo));
#else
		return (LRESULT)GetIDMode ((long)p);
#endif // defined(_USE_DEFAULTVIEW_FOR_TEXTS)

	case DEX_DRAWIDENTEX:
		{
		DRAWIDENTEX *pDI = (DRAWIDENTEX *)p;

#if defined(_USE_DEFAULTVIEW_FOR_TEXTS)
			pDI -> m_lResult |= (LRESULT)(GetIDMode (pDI -> m_lIdent) | GetIDMode (pDI -> m_lIdent, g_cbDefaultVisInfo));
#else
			pDI -> m_lResult |= (LRESULT)GetIDMode (pDI -> m_lIdent);
#endif // defined(_USE_DEFAULTVIEW_FOR_TEXTS)
			return false;		// unbedingt weiterreichen
		}

	case DEX_DRAWOBJECT:
		{
		DRAWOBJECT *pDO = (DRAWOBJECT *)p;

			if (pDO -> dwSize == sizeof(DRAWOBJECT)) {
			// behandeln, wie bisher
				return (LRESULT)GetNewVI (pDO -> lObjNr, pDO -> pNewVI, 
						  false, -1L, pDO -> m_fFlags);
			} else {
				TX_ASSERT(pDO -> dwSize == sizeof(DRAWOBJECTEX));

			// Resultate zu bereits existierenden hinzufügen
				((DRAWOBJECTEX *)pDO) -> m_lResult |= (LRESULT)GetNewVI (
							pDO -> lObjNr, pDO -> pNewVI, 
							false, -1L, pDO -> m_fFlags);
				return false;		// unbedingt weiterreichen
			}
		}
		
	case DEX_ERRORMESSAGE:
		return (LRESULT)HandleErrorMessage ((ERRORMESSAGE *)p);
		
	case DEX_QUERYRECHOBJECT:	// Strings in ORFenster beeinflussen
		return HandleQueryRechObject ((RECHOBJECT *)p);
		
	case DEX_SETNEWPALETTE:		// PaletteHandling in ColorControlDlg
		if (m_CCDlg) m_CCDlg -> SetNewPalette (*(HPALETTE *)p);
		if (m_pVMT) m_pVMT -> OnPaletteChange (__hWndM, *(HPALETTE *)p);
		break;

	case DEX_PAINTTOPLAYER:		// Zeichnen beendet
		if (m_fRebuildView) {
			m_fRebuildView = false;
			DEX_PostRebuildSight();	// noch mal abschicken, aber als Post
//			UnRegisterNotification (DEX_PAINTTOPLAYER);	// nur einmal
		}
		m_fIsDrawing = false;	// #HK011114
		break;

	default:
		break;		// alle anderen interessieren nicht
	}
	return CTriasExtension::Notification(iMsg, p);	// Notifikationen weiterreichen 
}


// Diese Funktion initialisiert das Menu --------------------------------------
bool CVisObjExtension::FindMenuItem (HMENU hMenu, UINT uiID)
{
UINT uiCnt = GetMenuItemCount(hMenu);

	uiID += MenuOffset();
	for (UINT uiLoop = 0; uiLoop < uiCnt; uiLoop++) {
		if (uiID == GetMenuItemID (hMenu, uiLoop))
			return true;
	}
	return false;		// nichts gefunden
}

STDMETHODIMP_(BOOL) CVisObjExtension::MenuInit (HMENU hMenu, LPARAM lData, HWND hWnd)
{
	if (NULL == hWnd) {
		if (FindMenuItem (hMenu, IDM_SHOWHIDDEN))
			CheckMenuItem (hMenu, IDM_SHOWHIDDEN+MenuOffset(), MF_BYCOMMAND|(m_fShowHidden ? MF_CHECKED : MF_UNCHECKED)); 	

		if (NULL != m_pActProject && FindMenuItem (hMenu, IDM_IGNOREALLERRORS))
			CheckMenuItem (hMenu, IDM_IGNOREALLERRORS+MenuOffset(), MF_BYCOMMAND|(m_fAllVisErrIgnore ? MF_CHECKED : MF_UNCHECKED)); 	

		if (FindMenuItem (hMenu, IDM_VISOBJREMOVE))
			EnableMenuItem (hMenu, IDM_VISOBJREMOVE+MenuOffset(), MF_BYCOMMAND|((m_lSichtVisMCode == -1) ? MF_GRAYED : MF_ENABLED)); 	
		if (FindMenuItem (hMenu, IDM_REVOKEHIDE))
			EnableMenuItem (hMenu, IDM_REVOKEHIDE+MenuOffset(), MF_BYCOMMAND|((m_lSichtVisMCode == -1) ? MF_GRAYED : MF_ENABLED)); 	

		if (FindMenuItem (hMenu, IDM_VISINFOIMPORT))	// #HK011114
			EnableMenuItem (hMenu, IDM_VISINFOIMPORT+MenuOffset(), MF_BYCOMMAND|(m_fIsDrawing ? MF_GRAYED : MF_ENABLED)); 	

		return true;
	}

	if (NULL != hWnd && 2 == LOWORD(lData) && FindMenuItem (hMenu, IDM_RESETVISINFO)) {
	// wenn es das zusätzliche Popupmenu dieser Erweiterung ist
	short iCnt = 0;

		DEXOR_SelectedObjectsCount (hWnd, &iCnt);

	// dynamische Menueinträge für VMD's einbauen
	// zuerst alle evtl. existierenden rausnehmen
		RemoveMenu (hMenu, IDM_VMDSEPARATOR+MenuOffset(), MF_BYCOMMAND);
		for (CVMDMenuMap::iterator it = m_VMDMap.begin(); it != m_VMDMap.end(); ++it)
			RemoveMenu (hMenu, (*it).first, MF_BYCOMMAND);

	// danach alle zum aktivierten Objekt gehörenden wieder reinhängen
		if (iCnt > 0) {
		long lActObj = DEX_GetActiveObject (hWnd);

			TX_ASSERT(-1 != lActObj && 0 != lActObj);	// aktiviertes Objekt muß hier existieren
			if (!DEX_GetROModeIdent (DEX_GetObjIdent(lActObj))) {
			// Tabelle dieses Objektes ist nicht schreibgeschützt
			short Status = DEX_GetObjectStatus (lActObj);

				if (Status == OSNormal || Status == OSModified) {		// Objekt existiert und ist nicht temporär
				int dwType = OTypToBits(DEX_GetObjectType(lActObj));
				int iMICnt = 0;
				UINT uiBefore = IDM_RESETVISINFO+MenuOffset();

					for (CVMDMenuMap::iterator it = m_VMDMap.begin(); it != m_VMDMap.end(); ++it) {
						if ((dwType & (*it).second.GetType()) &&
							InsertMenu (hMenu, uiBefore, MF_BYCOMMAND, (*it).first, (*it).second.GetMenuString()))
						{
							iMICnt++;
						}
					}

				// wenn wenigstens einer dazugekommen ist, dann Separator einbauen
					if (iMICnt > 0)
						InsertMenu (hMenu, uiBefore, MF_BYCOMMAND|MF_SEPARATOR, IDM_VMDSEPARATOR+MenuOffset(), NULL);
				}
			} else
				iCnt = 0;		// Tabelle schreibgeschützt, keine Aktion zulassen
		}

	// alle festen Menueinträge richten
		EnableMenuItem (hMenu, IDM_SHOWOBJECTS+MenuOffset(), MF_BYCOMMAND|((iCnt > 0) ? MF_ENABLED : MF_GRAYED));
		EnableMenuItem (hMenu, IDM_RESETVISINFO+MenuOffset(), MF_BYCOMMAND|((iCnt > 0) ? MF_ENABLED : MF_GRAYED));
		
	UINT uiObjHide = IDM_HIDEOBJECTS+MenuOffset();

		if (iCnt > 1) {
		// nicht nur ein Objekt selektiert
			ModifyMenu (hMenu, uiObjHide, MF_BYCOMMAND|MF_STRING, uiObjHide, ResString(ResID(IDS_HIDESELECTEDOBJECTS, &RF()), 30));
		} else {
		// genau ein Objekt aktiviert/selektiert
			ModifyMenu (hMenu, uiObjHide, MF_BYCOMMAND|MF_STRING, uiObjHide, ResString(ResID(IDS_HIDEACTIVATEDOBJECT, &RF()), 30));
		}
		EnableMenuItem (hMenu, uiObjHide, MF_BYCOMMAND|((iCnt > 0) ? MF_ENABLED : MF_GRAYED));
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Menuselektion (Texte in Statuszeile etc.)
STDMETHODIMP_(BOOL) CVisObjExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd)
{
	return TRUE;
}

// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(BOOL) CVisObjExtension::MenuCommand (UINT MenuItemID, HWND hORWnd)
{
	switch (MenuItemID) {	
	// Hauptmenupunkte
#if !defined(WIN32)
	case IDM_EXTABOUT:		// InfoBox anzeigen		
		{
		AboutBox AB (MWind(), ResID (DEFIDABOUT, &RF()));
		
			AB.Show (Centre);
		} 
		return true;
#endif // !WIN32

	case IDM_SAVECOMPLETE:		// gesamte VisInfo speichern
		m_fFullVisInfo = !m_fFullVisInfo;
		break;
		
	case IDM_VISOBJREMOVE:		// VisInfoMerkmale löschen
		if (RemoveVisInfo()) 
			DEX_RePaintWait();
		break;
		
	case IDM_SHOWHIDDEN:		// versteckte Objekte anzeigen
		m_fShowHidden = !m_fShowHidden;
		DEX_RePaintWait();
		break;
		
	case IDM_REVOKEHIDE:		// Ausblenden rückgängig
		if (RemoveShowInfo()) 
			DEX_RePaintWait();
		break;

	case IDM_VISINFOEXPORT:		// Erzeugen der VisAsc
		ExportVisInfo();
		break;
		
	case IDM_VISINFOIMPORT:
		ImportVisInfo();	// Einlesen einer VisAsc
		break;
		
	// ObjektRechercheFensterMenu
	case IDM_CHANGEVISINFO:
	// neue VisInfo für dieses Objekt einstellen
		if (hORWnd) 
			return ChangeVisInfo (hORWnd, GetKeyState (VK_CONTROL) < 0);
		break;
		
	case IDM_RESETVISINFO:
		if (hORWnd) {
			if (ResetVisInfo (hORWnd))
				DEX_RePaintWait();
		}				
		break;

	case IDM_HIDEOBJECTS:
		if (hORWnd) 
			HideObjects (hORWnd);
		break;

	case IDM_SHOWOBJECTS:
		if (hORWnd) {
			if (ShowObjects (hORWnd))
				DEX_RePaintWait();
		}
		break;

	case IDM_COLORCONTROL:
		ControlColors();
		break;
		
	// zusätzlicher MenuPunkt
	case IDM_IGNOREALLERRORS:
		if (m_fAllVisErrIgnore || (m_pVIE && m_pVIE -> Count())) {
			m_fAllVisErrIgnore = false;
			if (m_pVIE) m_pVIE -> EveryDelete();
		} else
			m_fAllVisErrIgnore = true;
		break;

	default:
		if (NULL != hORWnd) {
		CVMDMenuMap::iterator it = m_VMDMap.find(MenuItemID+MenuOffset());
			
			if (it != m_VMDMap.end()) 
				return DefineSymbol (hORWnd, &(*it).second);
		}
		break;
	}
	return false;
}

// Initialisieren der internen Strukturen für objektbezogene Visualisierung ---
bool CVisObjExtension::InitMCodes (void)
{
	DELETE_OBJ (m_pActProject);
	m_pActProject = new char [_MAX_PATH +1];

	if (DEX_GetActiveProject (m_pActProject) != NULL) {
		DELETE_OBJ (m_pActSight);
		m_pActSight = new char [_MAX_PATH +1];

		if (NULL != DEX_GetActiveSight (m_pActSight)) {
			m_lSichtVisMCode = GetViewMCode (m_pActSight);	// VisObjMCode holen
			m_lSichtLegMCode = GetViewLegMCode();	// LegObjMCode holen
		} else {
			m_lSichtVisMCode = -1L;
			m_lSichtLegMCode = -1L;
		}

	} else {
		DELETE_OBJ (m_pActProject);
		m_lSichtVisMCode = -1L;
		m_lSichtLegMCode = -1L;
	}
	return m_lSichtVisMCode != -1L/* && m_lObjVisMCode != -1L*/;
}

void CVisObjExtension::DeInitMCodes (void)
{
	DELETE_OBJ (m_pActProject);
	DELETE_OBJ (m_pActSight);

	m_lSichtVisMCode = -1L;
	m_lSichtLegMCode = -1L;
}

// Holen des MCodes, unter dem an einer Sicht der MCode für die Visualisierung
// hängt
long CVisObjExtension::GetViewMCode (LPCSTR pcView, bool fGenerate)
{
	if (m_pActProject == NULL || *m_pActProject == '\0') {
	// in StartupAnsicht kommt ProjektOpened erst nach SightToSelect
		DELETE_OBJ (m_pActProject);
		m_pActProject = new char [_MAX_PATH +1];
		if (DEX_GetActiveProject (m_pActProject) == NULL) 
		{
			DELETE_OBJ (m_pActProject);
			return -1L;		// wirklich kein Projekt
		} 
	}

	if (NULL == pcView) {
		if (NULL == m_pActSight) {
			m_pActSight = new char [_MAX_PATH +1];
			if (NULL == DEX_GetActiveSight (m_pActSight)) {
				DELETE_OBJ(m_pActSight);
			} else {
				pcView = m_pActSight;
			}
		} else
			pcView = m_pActSight;
	}
	return GetHeaderMCode (fGenerate, IDS_OBJVISINFO, IDS_OBJVISINFOKTEXT, IDS_OBJVISINFOLTEXT, pcView);
}


// Holen des MCodes, unter dem an einer Sicht der MCode für die Legende hängt
long CVisObjExtension::GetViewLegMCode (void)
{
	if (m_pActProject == NULL || *m_pActProject == '\0') {
		DELETE_OBJ (m_pActProject);
		m_pActProject = new char [_MAX_PATH +1];
		if (DEX_GetActiveProject (m_pActProject) == NULL) 
		{
			DELETE_OBJ (m_pActProject);
			return -1L;		// wirklich kein Projekt
		} 
	}
	return GetHeaderMCode (false, IDS_LEGENDINFOMCODE, IDS_LEGENDINFOKTEXT, IDS_LEGENDINFOLTEXT);
}

void MakeKText (LPSTR pKText, LPCSTR pcFormat, LPCSTR pcView)
{
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (NULL == DEX_GetActiveSight(cbBuffer)) 
			cbBuffer[0] = '\0';		// keine aktive Sicht
		pcView = cbBuffer;
	}
	TX_ASSERT(NULL != pcView);

	wsprintf (pKText, pcFormat ? pcFormat : "%s", pcView);
	if (strlen (pKText) > 31) {	// länger als max. KurzText
		pKText[31] = ')';	// SichtNamen abschneiden
		pKText[32] = '\0';
	}
}

long GetHeaderMCode (bool fGenerate, ResID resID, ResID resKT, ResID resLT, LPCSTR pcView)
{
GEODBHDRENTRY hdrEntry;
long result = -1L;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (resID, 17), 16);
	hdrEntry.lphdrText = new char [MCODESIZE +1];
	hdrEntry.hdrTextLen = MCODESIZE;

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
	// HeaderEintrag existiert
		result = atol (hdrEntry.lphdrText);
	} 
	else if (fGenerate) {
	// bei Bedarf neu generieren
	long lMCode = DEX_GetUniqueSysMCode();	// neuen MCode besorgen
	
		if (lMCode != -1) {		// und wegschreiben
			hdrEntry.hdrTextLen = MCODESIZE;
			ltoa (lMCode, hdrEntry.lphdrText, 10);

			if (DEX_WriteGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
				result = lMCode;

			// neuen Eintrag in PBD generieren
			ResString KFormat (resKT, 33);
			ResString LFormat (resLT, 256);

				SaveMCodeInPbd (result, pcView, KFormat, LFormat, true);
			}
		}
	}
	DELETE_OBJ (hdrEntry.lphdrText);
	return result;
}

// Abfragen des Merkmals der aktuellen Sicht, das MCode fuer die objektbezogene
// Visualisierung an den Objektklassen enthält
long CVisObjExtension::GetIdentMCode (bool fGenerate, const char *pView, LONG lIdent) 
{
	/*if (m_lSichtVisMCode == -1L) */{		// jetzt Grundsätzlich neu einlesen (evtl. andere Ansicht)
		m_lSichtVisMCode = GetViewMCode (pView, true);
		if (m_lSichtVisMCode == -1L)
			return -1L;
	}
	if (pView == NULL && (m_pActSight == NULL || *m_pActSight == '\0'))
		return -1L;

	return GetObjMCodeView (pView ? pView : m_pActSight, m_lSichtVisMCode, 
					ResID (IDS_PBDKURZTEXT, &RF()), ResID (IDS_PBDLANGTEXT, &RF()), 
					fGenerate, lIdent);
}

long CVisObjExtension::FindFeatureInDataSource (HPROJECT hPr, LPCSTR pcKText)
{
long lMCode = DEX_GetMCodeFromFeatureNameEx (hPr, pcKText);

	return (0L == lMCode) ? -1L : lMCode;
}

// Abfragen des Merkmals der aktuellen Sicht, das MCode fuer die objektbezogene
// Visualisierung an den Objekten einer Objektklasse enthält
long CVisObjExtension::GetObjMCode (bool fGenerate, const char *pcView, LONG lIdent) 
{
// Dieser MCode ist jetzt mit an der jeweiligen Objektklasse gespeichert
long lIdentMCode = GetIdentMCode (fGenerate, pcView, lIdent);
DWORD iMode = 0L;

	if (-1 == lIdentMCode)
		return -1L;

long lMCode = -1L;
ResString KFormat (ResID (IDS_PBDKURZTEXT, &RF()), 33);
char cbBuffer[_MAX_PATH];
HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	MakeKText (cbBuffer, KFormat, pcView); 
	if (ReadTextMerkmal (TT_Identifikator, lIdent, lIdentMCode, m_pMWert, -1, pcView) && 
		0 != (iMode = StringToIdMode (m_pMWert, &lMCode)) && -1L != lMCode)
	{
	// überprüfen, ob evtl. Altlasten drin sind
		if (!(iMode & OVMCodeCorrected)) {
		// Der MCode wurde noch nicht getestet/korrigiert
		long lMCodeT = FindFeatureInDataSource (hPr, cbBuffer);

			if (-1 != lMCodeT && lMCode != lMCodeT) {
//				TX_ASSERT(lMCode == lMCodeT);			// max. einmal je Ansicht 

			// uff..., MCode korrigieren
			char *pIdM = IdModeToString (iMode|OVMCodeCorrected, lMCodeT);

				lMCode = lMCodeT;
				WriteTextMerkmal (TT_Identifikator, lIdent, lIdentMCode, pIdM, pcView);
				DELETE_OBJ (pIdM);
			} else {
			// jetzt dürfte der MCode gültig sein
			char *pIdM = IdModeToString (iMode|OVMCodeCorrected, lMCode);

				WriteTextMerkmal (TT_Identifikator, lIdent, lIdentMCode, pIdM, pcView);
				DELETE_OBJ (pIdM);
			}
		}

	// evtl. in Pbd nachtragen
		if (IsNotInPbd (lMCode, lIdent)) {
		ResString LFormat (ResID (IDS_PBDLANGTEXT, &RF()), 256);

			SaveMCodeInPbd (lMCode, pcView, KFormat, LFormat, false, lIdent);
		}
		return lMCode;
	}

// evtl. neuen MCode erzeugen
	if (-1L == lMCode) {
	// im Header nicht gegeben, nachsehen, ob ein derartiges Merkmal in der 
	// Datenquelle definiert ist
		if (-1L == lMCode && fGenerate) {
		// erstmal versuchen, über Namen wiederzufinden
			lMCode = FindFeatureInDataSource (hPr, cbBuffer);
			if (-1 == lMCode)
				lMCode = DEX_GetUniqueSysMCode();
		}

		if (-1L != lMCode) {
		// neuen Eintrag in PBD generieren bzw. alten auffrischen (systemflag setzen etc.)
		ResString LFormat (ResID (IDS_PBDLANGTEXT, &RF()), 256);

			SaveMCodeInPbd (lMCode, pcView, KFormat, LFormat, false, lIdent);
		
		// in jedem Fall am Ident neu wegschreiben (fürs nächste mal)
		char *pIdM = IdModeToString (iMode|OVMCodeCorrected, lMCode);

			WriteTextMerkmal (TT_Identifikator, lIdent, lIdentMCode, pIdM, pcView);
			DELETE_OBJ (pIdM);
		}
	}
	return lMCode;
}


// Für eine bestimmte Sicht MCode für Objekte besorgen ------------------------
long GetObjMCodeView (
	const char *pView, long lSichtMCode, ResID resKT, ResID resLT, 
	bool fGenerate, LONG lIdent)
{
	if (lSichtMCode == -1L) return -1L;
	
TARGETMERKMAL gm;
long result = -1L;

	INITSTRUCT(gm, TARGETMERKMAL);
	gm.lTarget = (LPARAM)pView;
	gm.lMCode = lSichtMCode;
	gm.imaxLen = MCODESIZE;
	gm.pMText = new char [MCODESIZE+1];
	gm.iTTyp = TT_Sicht;

	if (DEX_GetTextMerkmal (gm) != NULL) {
		if (gm.pMText)
			result = atol (gm.pMText);
	} else if (fGenerate) {
	// neu generieren
	long lMCode = DEX_GetUniqueSysMCode();
	
		if (lMCode != -1 && gm.pMText) {	// und wegschreiben
			gm.imaxLen = MCODESIZE;
			ltoa (lMCode, gm.pMText, 10);

			if (DEX_ModTextMerkmal (gm) == EC_OKAY) {
				result = lMCode;

//			// neuen Eintrag in PBD generieren
//			ResString KFormat (resKT, 33);
//			ResString LFormat (resLT, 256);
//
//				SaveMCodeInPbd (result, pView, KFormat, LFormat, true, lIdent);
			}
		}
	}
	DELETE_OBJ (gm.pMText);
	return result;
}

// Heranholen und Merken des Modes für diesen Identifikator -------------------
DWORD CVisObjExtension::GetIDMode (long lIdent, const char *pView)
{
// externe Behandlung
IDENTVISMODE rgVisMode = IDENTVISMODE_NoAction;

#if _ATL_VER >= 0x200
	{
	CComBSTR bstrView;

		if (NULL != pView)
			bstrView = pView;
		else 
			bstrView = m_pActSight;

		if (S_OK == Fire_GetIdentMode (lIdent, bstrView, &rgVisMode))
			return rgVisMode;
	}
#else
	USES_CONVERSION;
	if (!m_cp.empty()) {
	CComBSTR bstrView;

		if (NULL != pView)
			bstrView = A2OLE(pView);
		else 
			bstrView = A2OLE(m_pActSight);

		if (S_OK == m_cp.Fire_GetIdentMode (lIdent, bstrView, &rgVisMode))
			return rgVisMode;
	}
#endif // _ATL_VER

// eigene Behandlung
DWORD result = rgVisMode;
long lObjMCode = GetIdentMCode (false, pView, lIdent);

// permanente Sicht ausgewählt
	if (lObjMCode == -1L || 0 == lObjMCode) 
		return result;
	
	if (ReadTextMerkmal (TT_Identifikator, lIdent, lObjMCode, m_pMWert, -1, pView)) 
		result = StringToIdMode (m_pMWert);

	return result;
}


// Heranholen einer VisInfo für ein bestimmtes Objekt -------------------------
short CVisObjExtension::GetNewVI (
	HANDLEVISINFO *pHVI, long lMCode, short fFlags, char **cbModuleInfo)
{
	if (lMCode == -1) 
		lMCode = GetObjMCode (false, m_pActSight, pHVI -> m_lIdent);
	
	if (lMCode == -1) return DO_UnChanged;

VisInfo *pVI = VisInfoFromC (*pHVI -> m_pVI, (VisType)pHVI -> m_iVTyp);
short iResult = 0;

	if ((iResult = GetNewVI (pHVI -> m_lONr, pVI, false, lMCode, fFlags, cbModuleInfo)) != 0) 
	{
		DELETE_OBJ (pHVI -> m_pVI);
		pHVI -> m_pVI = VISINFOFromCPP (pVI);
		pHVI -> m_fFlags = iResult;
	}
	DELETE_OBJ (pVI);

return iResult;
}

// Lesen und interpretieren eines VisualisierungsStrings ----------------------
HRESULT CreateVisInfo (VisInfo *pVis, CVisInfoInterfaceBase **ppIVis)
{
	if (NULL == pVis) return E_FAIL;
	TEST_E_POINTER("CreateVisInfo", ppIVis);

CVisInfoInterfaceBase *pBase = NULL;

	try {
		switch (pVis -> isA()) {
		case VT_Punkt:
			{
			CComObject<CPVisInfoObject> *pNewVis = NULL;

				THROW_FAILED_HRESULT(CComObject<CPVisInfoObject>::CreateInstance(&pNewVis));
				pBase = pNewVis;
			}
			break;

		case VT_Linie:
			{
			CComObject<CLVisInfoObject> *pNewVis = NULL;

				THROW_FAILED_HRESULT(CComObject<CLVisInfoObject>::CreateInstance(&pNewVis));
				pBase = pNewVis;
			}
			break;

		case VT_Flaeche:
			{
			CComObject<CFVisInfoObject> *pNewVis = NULL;

				THROW_FAILED_HRESULT(CComObject<CFVisInfoObject>::CreateInstance(&pNewVis));
				pBase = pNewVis;
			}
			break;

		case VT_Text:
			{
			CComObject<CTVisInfoObject> *pNewVis = NULL;

				THROW_FAILED_HRESULT(CComObject<CTVisInfoObject>::CreateInstance(&pNewVis));
				pBase = pNewVis;
			}
			break;

		default:
			return E_UNEXPECTED;
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

	pBase -> SetVisInfo (pVis);
	*ppIVis = pBase;
	return S_OK;
}

short CVisObjExtension::GetNewVI (long lONr, VisInfo * & rpVI, 
	bool fHidden, long lMCode, short fFlags, char **cbModuleInfo)
{
// externe Behandlung
#if _ATL_VER >= 0x200
	{
	CVisInfoInterfaceBase *pBase = NULL;

		if (SUCCEEDED(CreateVisInfo (rpVI, &pBase))) {
		WDVisInfo Vis;

			if (SUCCEEDED(pBase -> GetDVisInfo (Vis.ppi())) &&
				S_OK == Fire_GetObjectVis (lONr, &Vis.p)) 
			{
			// zurück kopieren ...
				DELETE_OBJ(rpVI);
				rpVI = (VisInfo *)pBase -> GetVisInfo() -> Copy();

			int iResult = DO_UnChanged;

				Vis -> get_Changed (&iResult);
				return iResult;
			}
		}
	}
#else
	if (!m_cp.empty()) {
	CVisInfoInterfaceBase *pBase = NULL;

		if (SUCCEEDED(CreateVisInfo (rpVI, &pBase))) {
		WDVisInfo Vis;

			if (SUCCEEDED(pBase -> GetDVisInfo (Vis.ppi())) &&
				S_OK == m_cp.Fire_GetObjectVis (lONr, &Vis.p)) 
			{
			// zurück kopieren ...
				DELETE_OBJ(rpVI);
				rpVI = (VisInfo *)pBase -> GetVisInfo() -> Copy();

			int iResult = DO_UnChanged;

				Vis -> get_Changed (&iResult);
				return iResult;
			}
		}
	}
#endif // _ATL_VER

// eigene Behandlung 
LONG lIdent = DEX_GetObjIdent(lONr);
HPROJECT hPr = DEX_GetObjectProject(lONr);
short iResult = GetNewVIFromView (hPr, lONr, lIdent, lMCode, fFlags, fHidden, m_pActSight, rpVI, cbModuleInfo);

#if defined(_USE_DEFAULTVIEW_FOR_TEXTS)
	if (DO_UnChanged == iResult)	// evtl. nochmal in StandardAnsicht nachsehen
		iResult = GetNewVIFromView (hPr, lONr, lIdent, lMCode, fFlags, fHidden, g_cbDefaultVisInfo, rpVI, cbModuleInfo);
#endif // defined(_USE_DEFAULTVIEW_FOR_TEXTS)
	return iResult;
}

short CVisObjExtension::GetNewVIFromView (
	HPROJECT hPr, LONG lONr, LONG lIdent, LONG lMCode, 
	short fFlags, bool fHidden, LPCSTR pcView, VisInfo *& rpVI, char **cbModuleInfo)
{
	if (lMCode == -1) 
		lMCode = GetObjMCode (false, pcView, lIdent);
	
	if (lMCode == -1 || m_pMWert == NULL) 
		return DO_UnChanged;

// MWert vom aktuellen Objekt holen
short iResult = DO_UnChanged;
bool fHasFeature = true;
HPROJECT hMCodeProject = DEX_GetFeatureProject(lMCode);

	if (NULL == hMCodeProject || hPr != hMCodeProject ||
		!ReadTextMerkmal (TT_Objekt, lONr, lMCode, m_pMWert)) 
	{
	LONG lMCodeMapped = DEX_MapMCodeToHandle (hPr, lMCode);

		if (-1 == lMCodeMapped || 0 == lMCodeMapped || lMCodeMapped == lMCode)
			return DO_UnChanged;
		lMCode = lMCodeMapped;
		fHasFeature = false;
	}

	if (fHasFeature || ReadTextMerkmal (TT_Objekt, lONr, lMCode, m_pMWert)) {
		pActChar = m_pMWert;
		pBuffEnd = pActChar + strlen (pActChar);

	// MWert als VI interpretieren
		if (m_fShowHidden)
			fFlags |= DF_ShowHidden;
		else
			fFlags &= ~DF_ShowHidden;

		iResult = ParseVisString (lONr, rpVI, fFlags, cbModuleInfo);
		if ((fHidden || !m_fShowHidden) && (iResult & (DO_Tagged|DT_WillDrawComplete)))
			iResult |= DT_NoDrawing;
		if ((fFlags & DF_Analyze) && !(fFlags & DF_Export)) 
			iResult &= ~DO_Tagged;	// nur Analyse, nicht zeichnen
	}
	return iResult;		// ÄnderungsStatus liefern
}

// Behandeln der FehlerNotifikationen -----------------------------------------
short CVisObjExtension::HandleErrorMessage (ERRORMESSAGE *pEM) 
{
	switch (pEM -> emiErrCode) {
	case WC_NOVISINFOPUNKT:
	case WC_NOVISINFOLINIE:
	case WC_NOVISINFOFLAECHE:
	case WC_NOVISINFOTEXT:
		{
		Pointer *pOldPointer = MWind() -> GetPointer();	// aktuellen Pointer merken
		short RC = HandleVisInfoError ((CVisError *)pEM -> empData);

			MWind() -> ChangePointer (pOldPointer);
			return RC;
		}

	case WC_SYMBOLNOTFOUND:
		if (m_fAllVisErrIgnore) return 2;
		break;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ein Eintrag in der Pbd existiert
bool IsNotInPbd (long lMCode, long lIdent)
{
PBDMERKMALEX TM;

	if (0 != lIdent) {
		INITSTRUCT(TM, PBDMERKMALEX);
	} else {
		INITSTRUCT(TM, PBDMERKMAL);
	}
	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	TM.lIdent = lIdent;
	return (EC_OKAY == DEX_GetPBDData(TM)) ? false : true;
}

///////////////////////////////////////////////////////////////////////////////
// Eintrag für ObjMCode in PBD generieren 
bool SaveMCodeInPbd (
	long lMCode, const char *pcView, const char *KFormat, const char *LFormat, 
	bool fView, LONG lIdent)
{
// Container als Merkmal an aktueller Sicht wegschreiben
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (NULL == DEX_GetActiveSight(cbBuffer)) 
			return false;		// keine aktive Sicht
		pcView = cbBuffer;
	}
	TX_ASSERT(NULL != pcView);

// PBDEintrag zusammenstellen
char pKText[_MAX_PATH];
char pLText[_MAX_PATH];

// Kurztext zusammenbauen
	MakeKText (pKText, KFormat, pcView);
	wsprintf (pLText, LFormat, pcView);

PBDMERKMALEX TM;
bool iResult = true;

	if (0 != lIdent) {
		INITSTRUCT(TM, PBDMERKMALEX);
	} else {
		INITSTRUCT(TM, PBDMERKMAL);
	}

	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	TM.pbdKText = pKText;
	TM.pbdLText = pLText;	
	TM.pbdKTextLen = strlen (pKText);
	TM.pbdLTextLen = strlen (pLText);
	TM.ipbdMTyp = (fView ? 'b' : 'a') | PBDMERKMAL_SYSTEMFLAG|PBDMERKMAL_READONLY;	// so tun, als ob's nur für Objekte wär
	TM.ipbdMLen = 256;
	TM.lIdent = lIdent;
	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (TM) != EC_OKAY)
			iResult = false;
		else
			DEXN_PBDMCodeChanged (lMCode);
	}
	return iResult; 
}

#if defined(EXTVIS)
// Zeichnen eines Objektes entsprechend Vorgaben ------------------------------
DWORD CVisObjExtension::DrawCustom (long lONr, char *pVisModule, short &fFlags,
				      VisInfo *pVI, char *pVisInfoString)
{
	if (m_pVMT == NULL || m_hDC == 0) 
		return (DWORD)ResultFromScode (VISMODULE_E_GENERALERROR);

// sicherstellen, daß dieser VisModule geladen ist
CVisModule *pVM = m_pVMT -> FFindOrAdd (pVisModule, m_pActProject);

	if (pVM == NULL)
		return (DWORD)ResultFromScode (VISMODULE_E_GENERALERROR);

OldVisInfo *pOldVI = GetOldVI (pVI);

// VisModule auffordern, das Objekt zu behandeln
DWORD dwRet = (DWORD)pVM -> m_pIVisModule -> DrawObject (
			hWnd(), m_hDC, m_hTargetDC, lONr, 
			fFlags, reinterpret_cast<VisInfo *>(pOldVI), pVisInfoString
	      );

	DELETE_OBJ(pOldVI);
	return dwRet;
}
#endif
