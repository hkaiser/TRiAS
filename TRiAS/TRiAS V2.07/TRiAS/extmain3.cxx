// Hauptfenster, Erweiterungen und deren Verwaltung, sonstiges ----------------
// File: EXTMAIN3.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <ospace/com/iterenum.h>	// IEnum<T>
#include <shellapi.h>
#include <xtensnxx.h>
#include <funcs03.h>

#include <olectl.h>
#include <triastlb.h>
#include <TRiASHelper.h>

#include <initguid.h>
#define _TriasTLB_H_
#include <dirisole.h>
#include <xtsnguid.h>
#include <undoguid.h>
#include <oprpguid.h>
#include <propguid.h>
#include <TrCatIDs.h>
#include <gentguid.h>

#undef NAKEDEVT

#include "menuitem.hxx"

#include <registry.hxx>
#include "extmain3.hxx"
#include "extqnfy2.hxx"
#include "tools.hxx"

#include <istatus.h>
#include <iunredo.hxx>
#include <undohelp.hxx>

#include <olectl.h>

#include "strings.h"

#include <ienumobj.hxx>

// #include "ienumonr.hxx"
#include "objprop.hxx"
#include "eallprop.hxx"
#include "eallcprp.hxx"
#include "alloprop.hxx"

#include "selectid.hxx"
#include "license.hxx"
#include "rechres.hxx"
#include "bildobj.hxx"
#include "signon.hxx"
#include "ManageExtDlg.h"

#include "TraceTRiAS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// PriorityLoad
#define MIN_PRIORITYLOAD	0
#define MAX_PRIORITYLOAD	7

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(InitDTRiASExtension);
DefineSmartInterface(TriasXtensionSite);
DefineSmartInterface(ObjectProps);
DefineSmartInterface(EnumObjProps);
//DefineSmartInterface(ObjectProperty);
DefineEnumIIDWrapper(LONG);
DefineSmartEnumerator(LONG);

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern HINSTANCE hInstance;
extern short g_iHideFlags;
extern bool g_fMenu;					// Menu's anzeigen
extern bool g_fHSB;						// HSB-Farbmodell verwenden
extern bool CloseEFlag;					// Projekt schlieáen
extern short g_iMinutes;

extern class ExtDirisWindow *CurrActDirisW;

///////////////////////////////////////////////////////////////////////////////
// PreTranslateMsgProc
// bool App_PreTranslateMessage (MSG *pMsg);
// extern bool (*g_pPreTransMsgProcChain)(MSG *);

extern CSignOnDlg *g_pSODlg;			// SignOnDlg

HWND __hWndM;		// HauptfensterHandle (für alle möglichen Messages)

///////////////////////////////////////////////////////////////////////////////
// Funktionsdeklarationen -----------------------------------------------------
void MenuEnable (pMenu, int, bool);
void AddMenuOffset (HMENU, short);

extern "C" _TRIAS01_ENTRY void FUNCTYPE InitTrias01 (HWND, UINT, UINT, UINT);
extern "C" _TRIAS02_ENTRY void FUNCTYPE InitTrias02 (HWND, UINT, UINT, UINT);

// Registrierte Messages/HauptFensterHandle -----------------------------------
UINT __DexCmd = 0;			// MessageWert für allgemeine Schnittstelle
UINT __DexReg = 0;			// MessageWert für NotificationMessages
UINT __DexUnReg = 0;		// MessageWert für Notification abmelden
UINT __DexxCmd = 0;			// MessageWert für C++ Schnittstelle
UINT __DexNotify = 0;		// MessageWert für NotifikationsMeldung

HWND WendtWnd;

// Konstruktor/Destruktor der neuen HauptfensterKlasse ------------------------
ExtDirisWindow::ExtDirisWindow (Rectangle &rcMWnd)
		: m_pView(NULL), m_pQNH(NULL), m_pEL(NULL), // !!
		  StrobeWindow (0, g_cbFrameClass),
		  m_eiExt (EC_EXTINITFAILURE, ReportExtError),
		  StartMenu (STARTMENU), IrisMenu (IRISMENU),
		  IrisIcon (ResID (IRISICON)),
		  StartAcc (STARTACCELS), IrisAcc (IRISACCELS),
		  m_brushBK (Color ((Colors)128,(Colors)128,(Colors)128))
{
///////////////////////////////////////////////////////////////////////////////
// 'Sichere' Initialisierungen
// FensterEigenschaften setzen
	if (g_fMenu) {
		EnableSysMenu ();				// Systemmenu anzeigen
		EnableMaxBox ();				// MinMaxButtons anzeigen
		EnableMinBox ();
	}

	EnableBorder();						// Rahmen anzeigen
	SetIcon (&IrisIcon);				// Icon setzen

	SetCaption (FakeTRiASName (IDS_CAPTION, g_cbTRiAS).c_str());		// Titelzeile einlesen
	
	ChangeBackground (&m_brushBK);		// Hintergrund setzen
	CanvasErase();						// Fenster löschen

// Flags initialisieren
	m_fToShow = true;
	m_fIsShown = false;
	m_fMustInitOPFs = true;
	m_fHoldZoom = false;
	m_fCleanedUp = false;

// globale Variablen nullsetzen
	__DexCmd = 0;
	__DexxCmd = 0;
	__DexNotify = 0;
	__DexReg = 0;
	__DexUnReg = 0;
	__hWndM = 0;

// Daten initialisieren
	m_iMenuOffset = DEX_FIRSTMENUOFFSET - DEX_MENUOFFSETDELTA;
	m_lEnableCnt = -1L;

// Kein Document eröffnet
	m_pView = NULL;

// Dragging initialisieren, wenn ales andere initialisiert wurde
#if defined(_OLD_DRAGNDROP)
	DragAcceptFiles (Handle (API_WINDOW_HWND), true);
#endif // _OLD_DRAGNDROP

///////////////////////////////////////////////////////////////////////////////
// 'Unsichere' Initialisierungen
// Sprungverteiler Initialisieren
	if (!FInitDexProcs() || !FInitDexProcsNfy()) return;
	if (!InitGlobals()) return;

// ExtensionList anlegen
	m_pEL = ExtensionList::CreateInstance();
	if (m_pEL == NULL) {
 		db_error (EC_NOMEMORY, RC_ctExtDirisWindow);
	  	return;
	}  

// einlesen sonstiger RegistryInfos
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser regCfg (g_cbRegConfig);
	char cbBuffer[64];
	DWORD dwLen = sizeof(cbBuffer);

		if (regCfg.GetSubSZ (g_cbShowObjProp, cbBuffer, dwLen))
			m_pEL -> SetActObjProp (cbBuffer);

	DWORD dwData = 0;

		if (regCfg.GetDWORD (g_cbHoldZoom, dwData))
			m_fHoldZoom = dwData ? true : false;
	}

// MessageHash anlegen
	m_pQNH = new QueryNotifyHash (*m_pEL);
	if (m_pQNH == NULL) {
		db_error (EC_NOMEMORY, RC_ctExtDirisWindow);
		return;
	}

// UndoredoVerwaltung
	m_pUndoRedo = CManageUndoRedo::CreateInstance (DEFAULTUNDOCNT);
	if (m_pUndoRedo == NULL) {
		db_error (EC_NOMEMORY, RC_ctExtDirisWindow);
		return;
	}

// MRU-Menu initialisieren
	m_pMRU = CreateMruMenu (NBMRUMENUSHOW, NBMRUMENU, _MAX_PATH, IDMRU);
	if (!m_pMRU) {
		db_error (EC_NOMEMORY, RC_ctExtDirisWindow);
		return;
	}

	{	// alle zu ladenden Extensions laden
	ErrInstall EI (EC_EXTINITFAILURE);	// Fehlermeldung unterdrücken
	ResString Profile (IDS_PROFILE, 15);

		LoadAllExtensions (Profile);
		DEXN_ExtensionsLoaded();		// alle Erweiterungen fertig geladen
	}

// Dummy MenuPunkt entfernen
	MainMenu() -> DeleteItem (IDM_DUMMY);

// initiale Größe und Lage festlegen
	MOrig = Point (rcMWnd.Left(), rcMWnd.Bottom());
	MSize = Dimension (rcMWnd.Right()-rcMWnd.Left(), rcMWnd.Top()-rcMWnd.Bottom());
	
	ChangePosition (MOrig);
	ChangeSize (MSize);

	DEXN_UIReady();		// UI ist bereits zum Config
}

ExtDirisWindow::~ExtDirisWindow (void) 
{
// Document spätestens hier schließen
	DELETE(m_pView);
	DELETE(m_pUndoRedo);	// UndoRedoVerwaltung

#if defined(_OLD_DRAGNDROP)
// Dragging wieder ausschalten
	DragAcceptFiles (Handle(API_WINDOW_HWND), false);
#endif // _OLD_DRAGNDROP

// Extensions abkopplen und freigeben
	SaveExtStatus();

	DELETE(m_pQNH);		// HashTabelle freigeben

// MRU-Menu wegschreiben
	if (m_pMRU) {
#if defined(ENABLE_WIN32S_CODE)
		if (IsWin32s())
			SaveMruInIni (m_pMRU, g_cbIniOpenMRU, ResString (IDS_PROFILE, 20).Addr());
		else
#endif // ENABLE_WIN32S_CODE
			SaveMruInReg (m_pMRU, g_cbRegOpenMRU);

		DeleteMruMenu (m_pMRU);
		m_pMRU = NULL;
	}

// Sprungverteiler freigeben
	DELETE_VEC(m_cbDexProcs/*, m_iDexProcsNum*/);
	DELETE_VEC(m_cbDexProcsNfy/*, m_iDexProcsNum*/);
#if defined(_DEBUG)
	DELETE_VEC(m_pDumpInfos);
#endif // _DEBUG

// erst nach der letzten Message die Pointer Ausnullen
	CurrActDirisW = NULL;

// globale Variablen nullsetzen
	__DexCmd = 0;
	__DexxCmd = 0;
	__DexNotify = 0;
	__DexReg = 0;
	__DexUnReg = 0;
	__hWndM = 0;
}

// globale Variablen entsprechend initialisieren ------------------------------
bool ExtDirisWindow::InitGlobals (void)
{
// allgemeine SchnittstellenMessage
	__DexCmd = RegisterWindowMessage (ResString (IDS_DEXMESSAGE, 30));

// NotificationSchnittstellenMessages
	__DexReg = RegisterWindowMessage (ResString (IDS_QNFYMESSAGE, 30));
	__DexUnReg = RegisterWindowMessage (ResString (IDS_QNFYUNREGMESSAGE, 30));
	__DexNotify = RegisterWindowMessage (ResString (IDS_NOTIFICATION, 30));

// C++ - SchnittstellenMessage
	__DexxCmd = RegisterWindowMessage (ResString (IDS_DEXXMESSAGE, 30));
	if (__DexCmd == 0 || __DexReg == 0 || 
	    __DexUnReg == 0 || __DexNotify == 0 || __DexxCmd == 0) 
	{
		db_error (EC_NODEXMESSAGE, RC_ctExtDirisWindow);
		return false;
	}
	
	__hWndM = Handle (API_WINDOW_HWND);
	TX_ASSERT(__hWndM != NULL && ::IsWindow(__hWndM));

// alle anderen Module von TRIAS(R) initialisieren ----------------------------
WendtWnd = __hWndM;
	InitTrias01 (__hWndM, __DexCmd, __DexxCmd, __DexNotify);
	InitTrias02 (__hWndM, __DexCmd, __DexxCmd, __DexNotify);
	InitTrias03 (__hWndM, __DexCmd, __DexxCmd, __DexNotify);

return true;
}

// Neues Dokument eröffnen ----------------------------------------------------
CREATEVIEW_RESULT ExtDirisWindow::CreateView (
	LPCSTR pcName, LPCSTR pcUser, LPCSTR pcPwd, short gfMode, DWORD dwMode)
{
	if (NULL != m_pView) {
	// nur bereits geöffnetes Projekt aktivieren
	HPROJECT hPr = m_pView -> IsOpened (pcName);

		if (NULL != hPr) {
			DEX_MakeProjectActive(hPr);
			if (!(gfMode & OM_HideWindow)) {	// nur wenn anzuzeigen ist
				if (isIconic()) 
					Show (Iconized);	// Anzeigen und hochholen
				else 
					ToTop();		// nur hochholen
			}
			return CREATEVIEW_RESULT(CREATEVIEW_RESULT_OK|CREATEVIEW_RESULT_NOREPAINT);
		}

	// jetzt alte GeoDB schließen
		if (!doCloseDocument()) 
			return CREATEVIEW_RESULT_OK;	// da ja nicht Open fehlgeschlagen ist
	}
	
	TX_ASSERT(NULL == m_pView);
	m_pView = IrisWind::CreateInstance (this, m_pView, pcName, pcUser, pcPwd, gfMode, dwMode);
	if (NULL == m_pView) return CREATEVIEW_RESULT_FAILED;

// Projektspezifische Erweiterungen laden
	LoadLocalExtensions();
	ReReadCaption();

// alle Objekteigenschaften und Klasseneigenschaften installieren
	try {
	WObjectProps IOP((ITriasXtensionSite *)m_pEL);	// throws hr

		IOP -> OnNewReferenceObject(-1L);
		if (SUCCEEDED(IOP -> OnNewReferenceObject(0L)))	// alle OPF's installieren
			m_fMustInitOPFs = false;

//		pIOP -> OnNewReferenceClass (NULL);	// alle ClsProps installieren
	} catch (_com_error&) {
		;	// no error
	}

// jetzt das neue Fenster anzeigen
	if (!(gfMode & OM_HideWindow)) {
		RepositionBars (0, 0xffff, ID_TRIASVIEW_GEODB);
		m_pView -> Show();
	}
	if (m_pView -> isVisible())
		DEXN_ViewCreated (m_pView -> Handle(API_WINDOW_HWND));

return CREATEVIEW_RESULT_OK;
}

// Caption aus zugehörigem DBHeader lesen -------------------------------------
bool ExtDirisWindow::ReReadCaption (bool fDelay)
{
	if (m_pView && m_pView -> IsValidView()) {
	string strCap;

		if (m_pView -> ReReadCaption (strCap, fDelay) && !fDelay) 
			SetCaption (strCap.c_str());
		return true;
	}

// 'TRiAS® Raumbezogenes Informationssystem'
	SetCaption (FakeTRiASName (IDS_CAPTION, g_cbTRiAS).c_str());
	return false;
}

bool ExtDirisWindow::RetrieveBasicCaption (string &rStrCaption, bool fExpand, bool fPureCaption)
{
	if (m_pView) 
		return m_pView -> RetrieveBasicCaption (rStrCaption, fExpand, fPureCaption);

// 'TRiAS® Raumbezogenes Informationssystem'
	rStrCaption = FakeTRiASName (IDS_CAPTION, g_cbTRiAS);
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// MenuFunktionen 

// Initialiserungen -----------------------------------------------------------
bool ExtDirisWindow::InitMenues (void)
{
	if (g_fMenu) {
		TX_ASSERT(m_pMRU);

#if defined(ENABLE_WIN32S_CODE)
        if (IsWin32s())
			LoadMruInIni (m_pMRU, g_cbIniOpenMRU, ResString(IDS_PROFILE, 20).Addr());
        else
#endif // ENABLE_WIN32S_CODE
			LoadMruInReg (m_pMRU, g_cbRegOpenMRU);
        PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(StartMenu.Handle(), 0), IDM_EXIT);

		ChangeMenu (&StartMenu);                // Menu einschalten
		ChangeAccel (&StartAcc);                // Acceleratortabelle setzen

		return true;
	}

return false;
}

bool ExtDirisWindow::InitProjectMenu (void)
{
	if (g_fMenu) {
		TX_ASSERT(m_pMRU);

#if defined(ENABLE_WIN32S_CODE)
        if (IsWin32s())
			LoadMruInIni (m_pMRU, g_cbIniOpenMRU, ResString(IDS_PROFILE, 20).Addr());
        else
#endif // ENABLE_WIN32S_CODE
			LoadMruInReg (m_pMRU, g_cbRegOpenMRU);
        PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(IrisMenu.Handle(), 0), IDM_EXIT);

		ChangeMenu (&IrisMenu);
		ChangeAccel (&IrisAcc);

		return true;
	}

return false;
}


// Memberfunktionen der neuen Hauptfensterklasse ------------------------------
// Laden aller Projektbesogenen Erweiterungen --------------------------------
bool ExtDirisWindow::LoadLocalExtensions (void)
{
char cbActProject[_MAX_PATH];
char *pIni = DEX_GetActiveProject (cbActProject);
		
	if (pIni) {
	char *pDrive = new char [_MAX_DRIVE];
	char *pPath = new char [_MAX_PATH];
	char *pFName = new char [_MAX_FNAME];
		
	// Pfad der lokalen INI-Datei zusammenbauen
		_splitpath (pIni, pDrive, pPath, pFName, NULL);
		_makepath (pIni, pDrive, pPath, pFName, ResString (IDS_EXTPROFILE, 5));
		LoadAllExtensionsINI (pIni, false);

	// Speicher wieder freigeben
		DELETE (pDrive);
		DELETE (pPath);
		DELETE (pFName);
		return true;
	}

return false;
}


// MenuPunkt wurde ausgewählt (nicht selektiert) ------------------------------
void ExtDirisWindow::MenuSelect (MenuSelectEvt e) 
{
// MenuEvents aus NutzerMenu herausfiltern
CTable r (*m_pEL);
short iItem = e.GetItemID();

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l) continue;
		if (l -> isMyID (iItem)) {
			l -> MenuSelect (e);
			return;		// ok, weiter
		}
	}

// MenuSelect der aktiven View rufen
	if (m_pView) m_pView -> MenuSelect (e);
}

void ExtDirisWindow::MenuInit (MenuInitEvt e) 
{
	DELETE (g_pSODlg);		// evtl. SignOn ausblenden

	if (!g_fMenu || NULL == ::GetMenu (Handle (API_WINDOW_HWND))) 
		return;

// erstmal alle Erweiterungen fragen, ob dieser MenuPunkt zu ihnen gehört
CTable r (*m_pEL);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l) continue;

	short iRet = 0;

		if ((iRet = l -> isMyMenu (e)) != 0) {
		// wenn Menu gefunden wurde
			l -> MenuInit (e);
			if (iRet == 1) return;			// ok, Ende der Vorstellung
		}
	}	

Menu *pM = e.GetMenu();

	if (&StartMenu == pM) 
		return;	// nicht weiterleiten, war nur für uns

	if (&IrisMenu == pM) {
	// Undo/Redo verwalten
	LPTSTR pDesc = NULL;
	HMENU hMenu = pM -> Handle (API_MENU_HMENU);
	char cbItem[_MAX_PATH];

	// UndoMenuPunkt behandeln
		if (m_pUndoRedo -> GetNextUndoDesc (&pDesc) & UNDOREDOCAPS_CANUNDO) {
		char *pAnsi = strtok (pDesc, g_cbUndoDel);	// nur erste Phrase

			if (pAnsi == NULL) pAnsi = pDesc;

		ResString resTmpl (IDS_UNDOTEMPL, 30);

			TX_ASSERT(strlen(pAnsi) + resTmpl.Len() < sizeof(cbItem));
			if (pAnsi) wsprintf (cbItem, resTmpl, pAnsi);
			else	   strcpy (cbItem, ResString (IDS_UNDOUNKNOWN, 30));

			ModifyMenu (hMenu, IDM_UNDO, MF_BYCOMMAND|MF_ENABLED, IDM_UNDO, cbItem);
		} else {
			ModifyMenu (hMenu, IDM_UNDO, MF_BYCOMMAND|MF_GRAYED, 
					IDM_UNDO, ResString (IDS_UNDONOTHING, 40).Addr());
		}
		if (pDesc) {
			CoTaskMemFree (pDesc);
			pDesc = NULL;
		}

	// RedoMenuPunkt behandeln
		if (m_pUndoRedo -> GetNextRedoDesc (&pDesc) & UNDOREDOCAPS_CANREDO) {
		char *pAnsi = strtok (pDesc, g_cbUndoDel);	// nur erste Phrase

			if (pAnsi == NULL) pAnsi = pDesc;

		ResString resTmpl (IDS_REDOTEMPL, 30);

			TX_ASSERT(strlen(pAnsi) + resTmpl.Len() < sizeof(cbItem));
			if (pAnsi) wsprintf (cbItem, resTmpl, pAnsi);
			else	   strcpy (cbItem, ResString (IDS_REDOUNKNOWN, 30));

			ModifyMenu (hMenu, IDM_REDO, MF_BYCOMMAND|MF_ENABLED, IDM_REDO, cbItem);
		} else {
			ModifyMenu (hMenu, IDM_REDO, MF_BYCOMMAND|MF_GRAYED, 
					IDM_REDO, ResString (IDS_REDONOTHING, 40).Addr());
		}
		if (pDesc) CoTaskMemFree (pDesc);

		MenuEnable (pM, IDM_CLOSE, CloseEFlag);         // ProjectClose
	}

// alle anderen muß IrisWind regeln	
	if (m_pView) m_pView -> MenuInit (e);
}


// eigener Event-Dispatcher, der Anforderungen der Erweiterung an Diris abfängt
LRESULT EXPORTTRIAS ExtDirisWindow::Dispatch (Event e) 
{
LRESULT R;

// interne NotifikationsVerarbeitung
	if (e.Msg() == __DexNotify) {
		if (0 != (R = DispatchNotification (e.WParam(), e.LParam())))
			return R;
	}

	if (WM_NCLBUTTONDOWN == e.Msg() || WM_NCRBUTTONDOWN == e.Msg()) 
		DELETE(g_pSODlg);
		
// an alle Erweiterungen verschicken, die es wollen
	try {
		if (0 != (R = DispatchThroughXtensions (m_pEL ? Handle() : NULL, e)))
			return R;

	} catch (LRESULT lResult) {
		return lResult;
	}

	if (e.Msg() == __DexCmd) {
	// diese Meldung ist für uns
		return FullFillWill (NULL, e.WParam(), e.LParam());
	} else if (e.Msg() == __DexxCmd) {
		return FullFillCPPWill (NULL, e.WParam(), e.LParam());
	} else if (e.Msg() == __DexReg) {	// Notifikation anfordern
		if (m_pQNH) {
		Extension *pExt = m_pEL -> FindExt ((HDEX)e.WParam());

			if (pExt == NULL) return false;
			return m_pQNH -> RegisterQNFY (*pExt, __hWndM, e.LParam());
		} else
			return false;
	} else if (e.Msg() == __DexUnReg) {	// Notifikation abmelden
		if (m_pQNH) {
		Extension *pExt = m_pEL -> FindExt ((HDEX)e.WParam());

			if (pExt == NULL) return false;
			return m_pQNH -> UnRegisterQNFY (*pExt, e.LParam());
		} else
			return false;
	} 

// StandardBehandlung
return TopAppWindow::Dispatch (e);	// weiterleiten
}

extern "C" 
_TF_ENTRY32 LRESULT WINAPI EventDispatcher (HWND, UINT, WPARAM, LPARAM);

extern "C" 
LRESULT EXPORTTRIAS WINAPI DexDispatchProc (HWND hWnd, UINT uiMsg, WPARAM w, LPARAM l)
{
	if (CurrActDirisW) {
	ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
	LRESULT R;
	
	// an alle Erweiterungen verschicken, die es wollen
		try {
			if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (uiMsg, w, l)) != 0)
				return R;

		} catch (LRESULT lResult) {
			return lResult;
		}
	}

return EventDispatcher (hWnd, uiMsg, w, l);
}

#if defined(NEWXTENSIONPROC)
extern "C" 
LRESULT EXPORTTRIAS WINAPI DexExtensionProcOld (WPARAM w, LPARAM l)
#else
LRESULT EXPORTTRIAS WINAPI DexExtensionProc (WPARAM w, LPARAM l)
#endif
{
	if (CurrActDirisW) {
	ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
	LRESULT R;
	
	// an alle Erweiterungen verschicken, die es wollen
		try {
			if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexCmd, w, l)) != 0)
				return R;

		} catch (LRESULT lResult) {
			return lResult;
		}

		return pW -> FullFillWill (NULL, w, l);
	}
		
return SendMessage(__hWndM, __DexCmd, w, l);
}

extern "C" 
LRESULT EXPORTTRIAS WINAPI DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	TX_ASSERT(NULL != CurrActDirisW);

ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
LRESULT R;
	
// an alle Erweiterungen verschicken, die es wollen
	try {
		if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexCmd, w, l)) != 0)
			return R;

	} catch (LRESULT lResult) {
		return lResult;
	}

	return pW -> FullFillWill (hPr, w, l);
}

extern "C"
LRESULT EXPORTTRIAS WINAPI DexxExtensionProc (WPARAM w, LPARAM l)
{
	if (CurrActDirisW) {
	ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
	LRESULT R;
	
	// an alle Erweiterungen verschicken, die es wollen
		try {
			if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexxCmd, w, l)) != 0)
				return R;

		} catch (LRESULT lResult) {
			return lResult;
		}
		return pW -> FullFillCPPWill (NULL, w, l);
	}
		
return SendMessage(__hWndM, __DexxCmd, w, l);
}

extern "C"
LRESULT EXPORTTRIAS WINAPI DexxExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	TX_ASSERT(NULL != CurrActDirisW);

ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
LRESULT R;

// an alle Erweiterungen verschicken, die es wollen
	try {
		if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexxCmd, w, l)) != 0)
			return R;

	} catch (LRESULT lResult) {
		return lResult;
	}
	return pW -> FullFillCPPWill (hPr, w, l);
}

extern "C"
LRESULT EXPORTTRIAS WINAPI DexPostNotificationProc (WPARAM w, LPARAM l)
{	// Message muß gepostet werden
	if (__hWndM)
		return PostMessage (__hWndM, __DexNotify, w, l);

return false;
}

extern "C"
LRESULT EXPORTTRIAS WINAPI DexNotificationProc (WPARAM w, LPARAM l)
{
LRESULT R = false;

	if (CurrActDirisW) {
	ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
	
		R = pW -> DispatchNotification (w, l);	// interne NotifikationsVerarbeitung
		if (0 != R)	return R;

	// an alle Erweiterungen verschicken, die es wollen
		if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexNotify, w, l)) != 0)
			return R;
	} else if (NULL != __hWndM) // Notanker
		return SendMessage(__hWndM, __DexNotify, w, l);

return R;
}

extern "C" 
LRESULT EXPORTTRIAS WINAPI DexNotificationProcEx (WPARAM w, LPARAM l, bool fPost)
{
	if (fPost)
		return PostMessage (__hWndM, __DexNotify, w, l);
		
LRESULT R = false;

	if (CurrActDirisW) {
	ExtDirisWindow *pW = (ExtDirisWindow *)CurrActDirisW;
	
		R = pW -> DispatchNotification (w, l);	// interne NotifikationsVerarbeitung
		if (0 != R) return R;

	// an alle Erweiterungen verschicken, die es wollen
		if (pW -> m_pQNH && (R = pW -> m_pQNH -> Dispatch (__DexNotify, w, l)) != 0)
			return R;
	} else if (NULL != __hWndM) 	// Notanker
		return SendMessage(__hWndM, __DexNotify, w, l);

return R;
}


// Laden und freigeben einer Erweiterung --------------------------------------
extern "C" 
_TRIAS_ENTRY DWORD EXPORTTRIAS WINAPI DefTriasExtensionProc (HDEX, UINT, WPARAM, LPARAM);

static HRESULT CLSIDFromRegistry (LPCSTR pcPseudoProgID, CLSID *pClsId)
{
string strExt (g_cbRegExtensions);

	strExt += string(g_cbDel) + pcPseudoProgID;

CCurrentUser regExt (strExt.c_str());
char cbBuffer[_MAX_PATH];
LONG dwLen = _MAX_PATH;

	if (!regExt.isValid() || !regExt.GetSZ (g_cbClsId, cbBuffer, dwLen))
		return HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND);

	USES_CONVERSION;
	return CLSIDFromString (A2OLE(cbBuffer), pClsId);
}

///////////////////////////////////////////////////////////////////////////////
// Eintrag: "ToolBoxBitmap" = dword:iIndex
UINT ExtensionList::GetToolBoxBitmapDWORD (LPCSTR pcPseudoProgID)
{
string strExt (g_cbRegExtensions);

	strExt += string(g_cbDel) + pcPseudoProgID;

	{	
	// evtl. BitmapEintrag vorhanden (Index in existierende ImageList.
	// Nachtragen ist daher nicht notwendig
		strExt += string(g_cbDel) + g_cbConfig;

	CCurrentUser regBmp (strExt.c_str());
	DWORD dwBmp = 0;

		if (regBmp.isValid() && regBmp.GetDWORD (g_cbToolboxBitmap, dwBmp))
			return dwBmp;
	}
	return 0;
}

// Eintrag CLSID\{...}\"ToolBoxBitmap" = "FileName,Index"
UINT ExtensionList::GetToolBoxBitmapSZ (LPCSTR pcPseudoProgID)
{
	USES_CONVERSION;

LPOLESTR poleClsId = NULL;
UINT uiBmp = 0;

	try {	
	CLSID clsID;
	
		THROW_FAILED_HRESULT(CLSIDFromProgID (A2OLE(pcPseudoProgID), &clsID));
		THROW_FAILED_HRESULT(StringFromCLSID (clsID, &poleClsId));

	string strExt (string(g_cbClsId) + g_cbDel + OLE2A(poleClsId));
	CClassesRoot regBmp (strExt.c_str());
	char cbBuffer[_MAX_PATH+32];
	LONG lLen = sizeof(cbBuffer);

		if (!regBmp.isValid() || !regBmp.GetSZ (g_cbToolboxBitmap, cbBuffer, lLen))
			_com_issue_error(E_FAIL);

	// Versuchen gegebenes Icon zu laden
		strExt = cbBuffer;
	
	size_t pos = strExt.find_last_of (",;");
	UINT uiResID = 0;

		if (pos != NPOS)	// Position in ResourceFile
			uiResID = (UINT)strtoul (strExt.substr(pos+1).c_str(), NULL, 10);
	
	// Bitmap zur ImageList hinzufügen
		{
		DLLBind dll (strExt.substr(0, pos).c_str(), IsWinNT() ? LOAD_LIBRARY_AS_DATAFILE : 0);

			if (NULL == dll.hLib())
				_com_issue_error(E_UNEXPECTED);

		HBITMAP hBitmap = ::LoadBitmap (dll.hLib(), MAKEINTRESOURCE(uiResID));

			if (NULL != hBitmap) {
			Bitmap bmp (hBitmap);
			int iIndex = m_ilExtIcons.Add (&bmp, RGB(255, 0, 255));		// Magenta

				if (iIndex >= 0)
					uiBmp = (UINT)iIndex;
			}
		}

	} catch (_com_error &) {
		if (NULL != poleClsId) CoTaskMemFree (poleClsId);
		return uiBmp;		// keinen Eintrag gefunden
	}
	if (NULL != poleClsId) 
		CoTaskMemFree (poleClsId);

	return uiBmp;	// entweder Index in ImageList oder 0 (bei Fehler)
}

UINT ExtensionList::InitToolboxBitmap (LPCSTR pcPseudoProgID, EXTENSIONFLAG rgFlags)
{
UINT uiBmp = GetBmp (pcPseudoProgID);

	if (0 != uiBmp) return uiBmp;	// bereits installiert: gefunden und raus

	uiBmp = GetToolBoxBitmapSZ (pcPseudoProgID);
	if (0 != uiBmp) return uiBmp;	// gefunden und raus

	uiBmp = GetToolBoxBitmapDWORD (pcPseudoProgID);
	if (0 != uiBmp) return uiBmp;	// gefunden und raus

// nichts gefunden, Standard verwenden, diese sind bereits in 
// ImageList vorhanden
	if (rgFlags & EF_Global) 
		uiBmp = IMG_EXTENSION;
	else
		uiBmp = IMG_EXTENSION_PRJ;

	if (rgFlags & EF_CanImport)
		uiBmp = IMG_EXTENSION_IMPORT;

	if (!(rgFlags & EF_Visible))
		uiBmp++;		// systeminterne sind jeweils die nächsten

	return uiBmp;
}

///////////////////////////////////////////////////////////////////////////////
// ClsID der Erweiterung besorgen
HRESULT ExtensionList::RetrieveCLSID (
	LPCSTR pDLLName, EXTENSIONFLAG rgFlags, CLSID *pclsID)
{
	TEST_E_POINTER("ExtensionList::RetrieveCLSID", pclsID);

HRESULT hr = GetCLSID (pDLLName, pclsID);

	if (SUCCEEDED(hr)) return S_OK;

	USES_CONVERSION;

LPOLESTR pwDLLName = A2OLE(pDLLName);

	hr = CLSIDFromProgID (pwDLLName, pclsID);
	if (FAILED(hr)) {	
	// ist kein ProgId
		if (rgFlags & EF_Global) 
			return CLSIDFromRegistry (pDLLName, pclsID);
		else
			return CLSIDFromString (pwDLLName, pclsID);
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Erweiterung laden
HDEX ExtDirisWindow::LoadExtension (
		LPCSTR pExtName, LPCSTR pDLLName, short toLoad, 
		EXTENSIONFLAG rgFlags, LPCSTR pcRegKey, IUnknown *pIXtsn)
{
// wenn Erweiterung bereits geladen ist, dann nicht mehr laden
short isLoaded = 0;

	{
	HDEX hDex = 0;
	
		if (toLoad && 
		    (isLoaded = m_pEL -> isLoaded (pDLLName, hDex)) >= toLoad) {
			m_pEL -> AddRef (pDLLName);
			return hDex;
		}
	}

// wenn kein Name gegeben ist, dann Versuchen diesen zu finden
char *pLocExtName = NULL;

	if (pExtName == NULL) {
		pLocExtName = m_pEL -> RetrieveExtName (pDLLName);
		if (pLocExtName == NULL) {
		// zusätzlich in die Liste aufnehmen
			pLocExtName = StrDup (pDLLName, RC_LoadExtension);
			if (pLocExtName == NULL) 
				return 0;		// Fehler
			rgFlags = EXTENSIONFLAG(rgFlags & ~EF_Global);
		}
		pExtName = pLocExtName;
	}

// Extension bilden und in Baum reinhängen
Extension *pExt;

// Flags mit evtl. bekannter Extension mergen
	rgFlags = EXTENSIONFLAG(rgFlags | m_pEL -> GetFlags (pDLLName));

#if defined(OLDEXTENSIONTYPE)
// Testen, ob der pDLLName ein Dateiname ist, oder ob es ein ProdID ist.
// Wenn pDLLName als Datei existiert, dann annehmen, daß es kein ProgID ist.
#if defined(WIN32)
DLLBind *pDLL = DLLBind::CreateInstance (pDLLName, 
			DONT_RESOLVE_DLL_REFERENCES|LOAD_LIBRARY_AS_DATAFILE);
#else
DLLBind *pDLL = DLLBind::CreateInstance (pDLLName);
#endif

// neue Extension anlegen, wenn sie noch nicht da ist
	if (pDLL != NULL) {
		delete pDLL;	// wieder freigeben
		if ((pExt = new CDirectExtension (Handle (API_CLIENT_HWND), 
					pExtName, pDLLName, toLoad)) == NULL) 
		{
			DELETE (pLocExtName);
			db_error (EC_NOMEMORY, RC_LoadExtension);
			return 0;
		}
	} else 
#endif // OLDEXTENSIONTYPE
	{
	// pDLLName ist ProgID
	CLSID clsID;
	UINT uiBmp = m_pEL -> InitToolboxBitmap (pDLLName, rgFlags);
	HRESULT hr = m_pEL -> RetrieveCLSID (pDLLName, rgFlags, &clsID);

		if (FAILED(hr)) {
		// ist kein CLSID/ProgID und auch kein Pseudo-ProgID, also Fehler
			DELETE (pLocExtName);
			db_error (EC_EXTINITFAILURE, RC_LoadExtension, pExtName ? pExtName : pDLLName);
			return 0;
		}

		if ((pExt = new COleExtension (Handle (API_CLIENT_HWND),
				pExtName, pDLLName, clsID, toLoad, uiBmp, pcRegKey)) == NULL) 
		{
			DELETE (pLocExtName);
			db_error (EC_NOMEMORY, RC_LoadExtension);
			return 0;
		}

	// aggregierte Erweiterungen dürfen kein DragDrop handeln (recursion !)
		if (rgFlags & EF_Aggregate) {
			((COleExtension *)pExt) -> SetAggregated (true);
			((COleExtension *)pExt) -> DisableDragDrop();
		} else
			((COleExtension *)pExt) -> SetAggregated (false);
	}
	pExt -> SetGlobal (rgFlags & EF_Global);
	pExt -> SetUnLoadable (rgFlags & EF_UnLoadable);
	pExt -> SetVisible (rgFlags & EF_Visible);
	pExt -> SetCanImport (rgFlags & EF_CanImport);
	pExt -> SetDynImportCfg (rgFlags & EF_DynImportCfg);

// MenuOffset neu berechnen und an Extension weiterleiten
TRIASLOADEX DLoad;
HDEX hDex = NULL;

	if (toLoad) {
		if (!isLoaded) {
		// Extension zum ersten mal zu laden
			m_iMenuOffset += DEX_MENUOFFSETDELTA;

			memset (&DLoad, '\0', sizeof (TRIASLOADEX));
			DLoad.m_dwSize = sizeof (TRIASLOADEX);
			DLoad.m_wMenuDelta = m_iMenuOffset;
//			DLoad.m_fcDef = m_pEL -> DefaultProc();
			DLoad.m_fcDef = (DEXCALLBACK)DefTriasExtensionProc;
			DLoad.m_iMode = toLoad;
		
		HPROJECT hPr = NULL;

			if (!(rgFlags & EF_Global) && IsValidActiveView())
				hPr = DBO().DB().DBDesc();

			hDex = pExt -> Load (DLoad, (rgFlags & EF_Aggregate) ? (ITriasXtensionSite *)m_pEL : NULL, hPr, pIXtsn);
			if (NULL == hDex) {
				TX_TRACE1("TRiAS:%s wurde nicht geladen\r\n", pDLLName);

				DELETE (pLocExtName);

			LPCSTR pName = pExt -> ExtName().c_str();

				if (0 == strlen(pName))
					pName = pExt -> DLLName().c_str();
				db_error (EC_EXTINITFAILURE, RC_LoadExtension, pName);
				DELETE (pExt);
				return 0;
			}
			TX_TRACE2("TRiAS:%s wurde geladen: %08lx\r\n", pDLLName, hDex);

			pExt -> MenuOffset() = m_iMenuOffset;	// MenuOffset eintragen
			pExt -> MenuHandle() = DLoad.m_hMenu;	// MenuHandle merken
			pExt -> MenuString().assign (DLoad.m_szMenuName, DEX_MENUNAMELEN);
			pExt -> ORMenuHandle() = DLoad.m_hORMenu;
			pExt -> ORMenuString().assign (DLoad.m_szORMenuName, DEX_MENUNAMELEN);
		} else {
		// ist bereits geladen, soll sichtbar werden
		CTable r (*m_pEL);
		string strKey = pExtName;

			if (r.Find (&strKey)) {
			ExtensionLock l(r);

				TX_ASSERT(NULL != (Extension *)l);

				pExt -> MenuOffset() = l -> MenuOffset();
				pExt -> MenuHandle() = l -> MenuHandle();
				pExt -> MenuString() = l -> MenuString();
				pExt -> ORMenuHandle() = l -> ORMenuHandle();
				pExt -> ORMenuString() = l -> ORMenuString();
			}
		}
	} 

// Extension rausnehmen, um sie neu reinhängen zu können
	UnLoadExtension (pExtName, false);

// Extension in Liste einhängen
Extension *pNewExt;

	{
	ExtensionCreator EC (*m_pEL);

#if defined(OLDEXTENSIONTYPE)
		if (pExt -> isA() == Extension::DirectExt) {
			pNewExt = Create (EC, CDirectExtension)(*(CDirectExtension *)pExt); 
		} else 
#endif // OLDEXTENSIONTYPE
		{
			pNewExt = ContCreate (EC, COleExtension)(*(COleExtension *)pExt); 
		}

		DELETE (pExt);	// altes 'template' freigeben
		if (pNewExt == NULL) 
		{
			db_error (EC_NOMEMORY, RC_LoadExtension);
			DELETE (pLocExtName);
			return 0;
		}

		EC.Insert();	// wirklich in den Baum speichern
	}

// wenn nicht geladen werden soll, dann raus
	if (!toLoad) {
		DELETE (pLocExtName);
		return 0;
	}

// Menu mit MENUOFFSET korrigieren
	if (!isLoaded) {
		AddMenuOffset (pNewExt -> MenuHandle(), m_iMenuOffset);
		AddMenuOffset (pNewExt -> ORMenuHandle(), m_iMenuOffset);
	}

// Menu in Hauptfenster einhängen, wenn eines gegeben ist, wenn's gefordert ist
	if (toLoad == LEFullLoad && pNewExt ->MenuHandle() != 0) {
	int nCount = GetMenuItemCount (MainMenu() -> Handle(API_MENU_HMENU));

		pNewExt -> MenuIndex() = nCount -1;	// Position im Menu merken

		InsertMenu (MainMenu() -> Handle(API_MENU_HMENU), nCount -1,
				MF_POPUP|MF_BYPOSITION, (UINT)DLoad.m_hMenu, 
				DLoad.m_szMenuName);
		DrawMenuBar (Handle (API_CLIENT_HWND));
	} else
		pNewExt -> MenuIndex() = -1;

	pNewExt -> AddRef();				// Zähler hochsetzen
	m_fMustInitOPFs = true;

	if (m_pView) m_pView -> LoadExtension (*pNewExt);
	DELETE (pLocExtName);

// Erweiterung vom Erfolg des Einbindens in Kenntnis setzen
	if (!pNewExt -> Init (toLoad, m_pEL)) {	
	// wenn's nun aber doch noch fehlgeschlagen ist
		UnLoadExtension (pExtName, true);		// doch wieder entladen

		db_error (EC_EXTINITFAILURE, RC_LoadExtension, pExtName ? pExtName : pDLLName);
		return NULL;
	}

	return pNewExt -> hLib();		// liefert Handle der geladenen DLL
}

// Extension gezielt freigeben ------------------------------------------------
bool ExtDirisWindow::UnLoadExtension (const char *pExtName, bool fForce) 
{
// wenn Parameter NULL ist, dann gleich mit Fehler wieder raus
	if (pExtName == NULL) return false;

// Extension in der Liste wiederfinden und rauswerfen
CTable r (*m_pEL);
UINT oldMenuIndex = UINT_MAX;
string strSrch (pExtName);

	for (r.First(); r.Valid(); ) {
	bool toDelete = false;
		{
		ExtensionLock l(r);

			if (!l) continue;
			if (strSrch == l -> ExtName()) {
				if (!fForce && l -> Release() > 0) 
					return true;
					
				if (l -> isLoaded()) {		// DLL rausnehmen
				HDEX hDex = l -> hLib();

					if (l -> UnLoad()) {
					// darf entladen werden 
						if (l -> MenuHandle() != 0) {
					// HauptMenu behandlen
	
							oldMenuIndex = l -> MenuIndex();
							if (oldMenuIndex != -1) {
							// gefunden: PopupMenu rausnehmen
								RemoveMenu (MainMenu() -> Handle (API_MENU_HMENU), 
									    oldMenuIndex, MF_BYPOSITION);
								DrawMenuBar (Handle (API_CLIENT_HWND));
							}
						}
						
					// Extension aus ORMenu herausnehmen
						if (m_pView) 
							m_pView -> UnLoadExtension (*l);
	
					// alle NotifikationsAnforderungen rauswerfen
						if (m_pQNH) m_pQNH -> UnRegisterAllQNFYs (hDex);

						TX_TRACE1("TRiAS:%s wurde entladen\r\n", strSrch.c_str());
					} else 
        					return false;
				}
				toDelete = true;	// löschen
				m_fMustInitOPFs = true;
			}
		}
		if (toDelete) { 
		// Extension löschen und freigeben
#if defined(WIN32)
			m_pEL -> ResetObjProps();	// Liste der Objekteigenschaften freigeben
			m_pEL -> ResetClsProps();
#endif // WIN32
			r.Delete(); 
			break; 
		} else if (!r.Next()) 
			return false; 
	}

// wenn kein Menu da war, dann erfolgreich raus
	if (oldMenuIndex == -1) return true;

// alle nachfolgenden MenuPunkte wieder vorziehen
	if (oldMenuIndex != UINT_MAX) {
		for (r.First(); r.Valid(); r.Next()) {
		ExtensionLock l(r);

			if (l && (UINT)l -> MenuIndex() > oldMenuIndex)
				(l -> MenuIndex()) --;
		}
	} else 
		return false;

return true;
}

// Nachfragen, ob die Sitzung wirklich beendet werden soll --------------------
bool ExtDirisWindow::QueryClose (Event e) 
{
	if (DEXN_ServerIsClosing()) 
		return false;	// jemand hat was dagegen

// kein Dokument geöffnet oder niemand etwas dagegen
	if (NULL == m_pView || m_pView -> myQueryClose(true)) {
		Show(HideWindow);	// sofort alles ausblenden
		return true;
	}

return false;		// nicht rausgehen
}

// Diese Routine wird kurz vor Ende des Programms abgearbeitet
bool ExtDirisWindow::CleanUpFrame (void) 
{
	if (m_fCleanedUp) return false;	// breits erledigt

	m_fCleanedUp = true;

// PreTransMsg wieder umschalten
// bool (*pF)(MSG *) = DEX_AttachPreTranslateMsgProc (g_pPreTransMsgProcChain);

//	TX_ASSERT(App_PreTranslateMessage == pF);

// aktuelle Parameter in ProfileDatei schreiben
// 1. Haupfenstergröße
Bool ZoomedFlag = isZoomed();
Bool IconFlag = isIconic();
char PStr[_MAX_PATH];

	if (IconFlag || ZoomedFlag) {
	// wenn Ikone, dann alte CanvasKoordinaten merken
		wsprintf (PStr, "%d,%d,%d,%d,%d,%d", ZoomedFlag, IconFlag,
				MOrig.Y()+MSize.Height(), MOrig.X(),
				MOrig.Y(), MOrig.X()+MSize.Width());
	} else {
	// sonst aktuelle FensterKoordinaten wegschreiben
	Rectangle MWnd = WindowRect ();

		wsprintf (PStr, "0,0,%d,%d,%d,%d",
//				MOrig.Y()+MSize.Height(), MOrig.X(),
//				MOrig.Y(), MOrig.X()+MSize.Width());
				MWnd.Top(), MWnd.Left(),
				MWnd.Bottom(), MWnd.Right());
	}

// RegistryEinträge wegschreiben
ResString SizeOrg (IDS_SIZEORG, 13);
ResString resSaveDelta (IDS_SAVEDELTA, 20);

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	// Verwendetes Farbmodell
	CCurrentUser regCfg (g_cbRegConfig);
	DWORD dwData = g_fHSB;

		regCfg.SetDWORD (g_cbHSBColors, dwData);

	// Speichern aller x Minuten
		dwData = g_iMinutes;
		regCfg.SetDWORD (resSaveDelta, dwData);

	// Größe und Lage
		regCfg.SetSubSZ (SizeOrg, PStr);	

	// Ausschnitt beibehalten
		dwData = m_fHoldZoom ? true : false;
		regCfg.SetDWORD (g_cbHoldZoom, dwData);
	}
#if defined(ENABLE_WIN32S_CODE)
	else {
	// Speichern aller x Minuten
	ResString Profile (IDS_PROFILE, 13);
	ResString IrisPars (IDS_IRISPARS, 13);

		ltoa (g_iMinutes, PStr, 10);
		WritePrivateProfileString (IrisPars,
				resSaveDelta, PStr, Profile);

	ResString IrisStartUp (IDS_STARTUP, 13);

		WritePrivateProfileString (IrisStartUp, SizeOrg, PStr, Profile);
	}
#endif // ENABLE_WIN32S_CODE

return true;
}

// Aktuellen Status der Erweiterungen wegschreiben ----------------------------
bool SavePreloadStatus (const string &strProgID, bool fPreload);
DWORD GetPriorityLoadStatus (const string &strProgID);

void ExtDirisWindow::SaveExtStatus (void)
{
	if (!CleanUpFrame())	// diverse Einstellungen speichern
		return;				// bereits geschehen

// Liste der Erweiterungen durchgehen und PreLoadStatus wegschreiben
#if defined(ENABLE_WIN32S_CODE)
ProFile PF (ResString (IDS_PROFILE, 20));
#endif // ENABLE_WIN32S_CODE
WUnknown ExtList((ITriasXtensionSite *)m_pEL);	// einfach mal festhalten

	if (NULL != m_pEL) {
	CTable r (*m_pEL);

	// Extension-Zustand in INI-Datei merken
		for (r.First(); r.Valid(); r.Next()) {
		ExtensionLock l(r);

			TX_ASSERT(NULL != (Extension *)l);
			if (
#if defined(ENABLE_WIN32S_CODE)
				!IsWin32s() && 
#endif // ENABLE_WIN32S_CODE
				l -> isA() == Extension::OleExt) 
			{
				SavePreloadStatus (l -> DLLName(), l -> isLoaded());
			} 
#if defined(ENABLE_WIN32S_CODE)
			else {
			EXTENSIONFLAG rgFlags = l -> GetFlags();
			int iFlag = l -> isLoaded() ? 1 : 0;

				if (!(rgFlags & EF_UnLoadable)) iFlag += EF_UnLoadable;
				if (!(rgFlags & EF_Visible)) iFlag += EF_Visible;
				if (rgFlags & EF_CanImport) iFlag += EF_CanImport;
				if (rgFlags & EF_DynImportCfg) iFlag += EF_DynImportCfg;

				PF.SetPreLoad ((char *)l -> ExtName().c_str(), iFlag);
			}
#endif // ENABLE_WIN32S_CODE
		}
			
	// jetzt Extensions abkoppeln und freigeben
#if defined(_DEBUG)
	HDEX hDex = NULL;
#endif // _DEBUG

		for (DWORD i = MIN_PRIORITYLOAD; i <= MAX_PRIORITYLOAD; i++) {
		// zuerstdie normalen, dann der Reihe nach alle PriorityLoad-Erweiterungen
			for (r.First(); r.Valid(); ) {
			string strExtName;

				{
				ExtensionLock l(r);

					if (!l) continue;

				// nur die entladen, deren PriorityLoadSTatus richtig ist
				DWORD dwLS = GetPriorityLoadStatus (l -> DLLName());

					TX_ASSERT(dwLS <= MAX_PRIORITYLOAD && dwLS >= MIN_PRIORITYLOAD);
					if (i != dwLS) {
						r.Next();
						continue;		// PriorityLoad am Schluß bearbeiten
					}
					strExtName = l -> ExtName();
#if defined(_DEBUG)
					hDex = l -> hLib();
#endif // _DEBUG
				} // lock goes out of scope

				UnLoadExtension (strExtName.c_str(), true);	// entladen
			// r.Next() erfolgt implizit in UnLoadExtension !
				TX_ASSERT(!m_pQNH -> ExtHasRegisteredNfys(hDex));
			}
		} // for (i...)
	} // CTable muß out of scope gehen

	if (NULL != m_pEL) {
	ExtensionList *pEL = m_pEL;

		m_pEL = NULL;		// erst NULL setzen

		pEL -> EveryDelete();	// alle geladenen Extensions rauswerfen
		pEL -> Release();		// letztes (hoffentlich) Release()
	}
}

// Fenster wird geschlossen ---------------------------------------------------
void ExtDirisWindow::Close (Event e) 
{
// Extensions abkopplen und freigeben
	DEXN_ServerClosed();		// das letzte vom Tage
	SaveExtStatus();

	CurrActDirisW = NULL;
	App::Quit();
}

// ----------------------------------------------------------------------------
// ExtensionList - Memberfunktionen -------------------------------------------
void *Extension::GetExtName (void *pObj)
{
	TX_ASSERT(NULL != pObj);

	return & ((Extension *)pObj) -> ExtName();
}

int Extension::CmpExtNames (void *pObj1, void *pObj2)
{
	TX_ASSERT(NULL != pObj1);
	TX_ASSERT(NULL != pObj2);

string *pStr1 = (string *)pObj1;
string *pStr2 = (string *)pObj2;

	return strcmp (pStr1 -> c_str(), pStr2 -> c_str());
}

ExtensionList *ExtensionList::CreateInstance (void)
{
ExtensionList *pEL = new ExtensionList();

	if (NULL == pEL || !pEL -> FInit()) {
		DELETE (pEL);
		return NULL;
	}
	pEL -> AddRef();

return pEL;
}

#pragma warning (disable: 4355)	// 'this' : used in base member initializer list

ExtensionList::ExtensionList (void) 
	: m_cp (this), m_cpSys (this)
{
	_Module.Lock();		// _ATL
//	FinalConstruct();

	m_dwRefCnt = 0;
	m_pMIL = NULL;
	m_pProps = NULL;

	m_lIsDropSourceInst = -1L;
}

#pragma warning (default: 4355)

ExtensionList::~ExtensionList (void) 
{
	DELETE (m_pMIL);
	DELETE (m_pProps);

	_Module.Unlock();	// _ATL
}

bool ExtensionList::FInit (void)
{
	m_pProps = CAllProperties::CreateInstance (this);
	if (NULL == m_pProps) return false;

	m_strActOProp = TEXT ("");

// ImageList generieren
	if (!m_ilExtIcons.CreateList (IDB_HEADERSTRIP, 16, 0, RGB(255, 0, 255))) {
		TX_TRACE("Couldnt create imagelist for ExtensionList");
		return false;
	}

	return true;
}

HRESULT ExtensionList::InvokeActObjProp (
		LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (0 == m_strActOProp.length())
		return ResultFromScode (S_FALSE);

WEnumObjProps EnumProp;
WObjectProperty ObjProp;
HRESULT hr = m_pProps -> EnumObjectProps (EnumProp.ppi());

	if (FAILED(hr)) return hr;

	hr = EnumProp -> FindByName (m_strActOProp.c_str(), ObjProp.ppi());
	if (FAILED(hr)) return hr;

	return ObjProp -> Eval (lONr, pBuffer, ulLen, pulWritten);
}

HRESULT ExtensionList::QueryActObjProp (IObjectProperty **ppIObjProp)
{
	TEST_E_POINTER("ExtensionList::QueryActObjProp", ppIObjProp);

	if (0 == m_strActOProp.length())
		return S_FALSE;

WEnumObjProps EnumProp;
WObjectProperty ObjProp;
HRESULT hr = m_pProps -> EnumObjectProps (EnumProp.ppi());

	if (FAILED(hr)) return hr;

	hr = EnumProp -> FindByName (m_strActOProp.c_str(), ObjProp.ppi());
	if (FAILED(hr)) return hr;

	*ppIObjProp = ObjProp.detach();
	return S_OK;
}

HRESULT ExtensionList::ResetActObjProp (void)
{
	if (0 == m_strActOProp.length())
		return ResultFromScode (S_FALSE);

WEnumObjProps EnumProp;
WObjectProperty ObjProp;
HRESULT hr = m_pProps -> EnumObjectProps (EnumProp.ppi());

	if (FAILED(hr)) return hr;

	hr = EnumProp -> FindByName (m_strActOProp.c_str(), ObjProp.ppi());
	if (FAILED(hr)) return hr;

return ObjProp -> Reset();
}

void ExtensionList::SetActObjProp (LPCSTR pOPName)
{
	m_strActOProp = pOPName;
}

void ExtensionList::ResetObjProps (void)
{
	m_pProps -> RemoveAllObjPropertyFunctions(); 
//	m_strActOProp.remove();
}

void ExtensionList::ResetClsProps (void)
{
	m_pProps -> RemoveAllClsPropertyFunctions(); 
}


void ExtensionList::EveryDelete (void)
{
	ResetObjProps();
	ResetClsProps();

	m_Exts.EveryDelete();
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP ExtensionList::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;
	if (riid == IID_IUnknown || riid == IID_ITriasXtensionSite)
		*ppvObj = (ITriasXtensionSite *)this;
 	else if (riid == IID_IObjectProps) 
		*ppvObj = (IObjectProps *)m_pProps;
 	else if (riid == IID_IObjectProps2) 
		*ppvObj = (IObjectProps2 *)m_pProps;
	else if (riid == IID_IConnectionPointContainer) 
		*ppvObj = (IConnectionPointContainer *)this;
	else if (riid == IID_ITRiASDropTarget)
		*ppvObj = (IDropTarget *)this;
	else if (riid == IID_IDragDropAction)
		*ppvObj = (IDragDropAction *)this;

	if (NULL == *ppvObj) {
	// alle aggregierten Erweiterungen fragen, ob sie das 
	// gesuchte Interface unterstützen
	CTable t(*this);

		for (t.First(); t.Valid(); t.Next()) {
		ExtensionLock l(t);

			if (!l || !l -> IsAggregated())
				continue;		// nicht aggregiert

		Extension *pExt = (Extension *)l;

			if (SUCCEEDED(((COleExtension *)pExt) -> QueryInterface (riid, ppvObj)))
				return S_OK;
		}	

	// nichts gefunden
		return ResultFromScode (E_NOINTERFACE);
	}

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) ExtensionList::AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) ExtensionList::Release (void)
{
	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}


// *** ITriasXtensionSite methods *** -----------------------------------------
STDMETHODIMP ExtensionList::GetXtension (REFCLSID rClsID, REFIID rIID, LPVOID *ppIUnk)
{
CTable t(*this);
bool fLoadExt = false;
EXTENSIONFLAG rgFlags = EF_NoFlags;
string strDLLName;

// erstmal feststellen, ob diese Erweiterung geladen ist
	for (t.First(); t.Valid(); t.Next()) {
	ExtensionLock l(t);
	Extension *pExt = (Extension *)l;

		TX_ASSERT(NULL != pExt);
		if (Extension::DirectExt == pExt -> isA())
			continue;

		if (((COleExtension *)pExt) -> IsExtension (rClsID)) {
			if (((COleExtension *)pExt) -> isLoaded())
				return ((COleExtension *)pExt) -> QueryInterface (rIID, ppIUnk);
			else {
				strDLLName = pExt -> DLLName();
				rgFlags = pExt -> GetFlags();
				fLoadExt = true;
				break;
			}
		}
	}

// wenn Erweiterung nicht registriert ist, dann wieder raus
	if (!fLoadExt) return ResultFromScode (E_FAIL);

// jetzt die Erweiterung laden und ...
LOADEXTENSIONEX LE;

	LE.m_pDesc = NULL;
	LE.m_pName = (char *)strDLLName.c_str();
	LE.m_iMode = LEInitOnly;		// nur initialisieren
	LE.m_fGlobal = true;

	if (NULL == DEX_ExternalLoadExtensionEx(LE))
		return ResultFromScode (E_FAIL);

// ... und wiederfinden
	for (t.First(); t.Valid(); t.Next()) {
	ExtensionLock l(t);
	Extension *pExt = (Extension *)l;

		TX_ASSERT(NULL != pExt);
		if (Extension::DirectExt == pExt -> isA())
			continue;

		if (((COleExtension *)pExt) -> IsExtension (rClsID)) {
			if (((COleExtension *)pExt) -> isLoaded())
				return ((COleExtension *)pExt) -> QueryInterface (rIID, ppIUnk);
		}
	}

return ResultFromScode(E_FAIL);		// nicht bekannt
}

// Sonstige Objekte erzeugen, die TRiAS unterstützt, aber nicht über eine 
// Erweiterung oder über QueryInterface erreichbar sind
STDMETHODIMP ExtensionList::CreateInstance (LPUNKNOWN pUnkOuter, REFCLSID rClsID, 
					      REFIID riid, LPVOID *ppUnk) 
{
	if (rClsID == CLSID_ProgressIndicator) {
		if (NULL != pUnkOuter)
			return ResultFromScode (CLASS_E_NOAGGREGATION);
		return PiCreateInstance (riid, ppUnk);
	}
	else if (rClsID == CLSID_UndoRedoObject) {
		if (NULL != pUnkOuter)
			return ResultFromScode (CLASS_E_NOAGGREGATION);
		return UndoCreateInstance (riid, ppUnk);
	} 
	else 
		return ObjPropCreateInstance (pUnkOuter, rClsID, riid, ppUnk);

return ResultFromScode (E_NOINTERFACE);
}


ExtensionList::CExtTree::~CExtTree (void)
{
	EveryDelete();
}

void EXPORTTRIAS ExtensionList::CExtTree::UserDelete (void *pObj)
{
	TX_ASSERT(NULL != pObj);
	((Extension *)pObj) -> ~Extension();
}

Extension *ExtensionList::FindExt (HDEX hDex)
{
CTable r (*this);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && l -> hLib() == hDex)
			return (Extension *)l;
	}

return NULL;
}

short ExtensionList::CountLoaded (short *piNotUnLoadable)
{
CTable r (*this);
short iCnt = 0;

	if (piNotUnLoadable) 
		*piNotUnLoadable = 0;	// zählt geladene, nicht entladbare Extensions

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && l -> isLoaded() && l -> isGlobal()) {
			iCnt++;
			if (!l -> isUnLoadable() && piNotUnLoadable) 
				(*piNotUnLoadable)++;
		}
	}

return iCnt;
}

char *ExtensionList::RetrieveDLLName (LPCSTR pExtName) 
{
CTable r (*this);
string strSrch (pExtName);

	if (r.Find (&strSrch)) {
	ExtensionLock l(r);

		TX_ASSERT(NULL != (Extension *)l);
		return StrDup (l -> DLLName().c_str(), RC_RetrieveDLLName);
	}

return NULL;	// nichts gefunden
}

char *ExtensionList::RetrieveExtName (LPCSTR pDLLName) 
{
CTable r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());		// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return StrDup (l -> ExtName().c_str(), RC_RetrieveExtName);
	}

return NULL;	// nichts gefunden
}

// Prüft, ob eine Erweiterung bereits geladen ist -----------------------------
short ExtensionList::isLoaded (LPCSTR pDLLName, HDEX &hDex) 
{
CTable r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) {	// gefunden
			hDex = (HDEX)l -> hLib();	// HDEX liefern
			return l -> isLoaded();
		}
	}

return 0;	// nichts gefunden
}

string ExtensionList::GetRegKey (LPCSTR pDLLName) 
{
CTable r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) {		// gefunden
			TX_ASSERT(l -> isA() == Extension::OleExt);
			return ((COleExtension *)(Extension *)l) -> GetRegKey();
		}
	}
	return string(g_cbNil);	// nichts gefunden
}

HRESULT ExtensionList::GetCLSID (LPCSTR pDLLName, CLSID *pclsID)
{
CTable r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) {	// gefunden
			TX_ASSERT(l -> isA() == Extension::OleExt);
			return ((COleExtension *)(Extension *)l) -> GetCLSID(pclsID);
		}
	}
	return E_FAIL;	// nichts gefunden
}

UINT ExtensionList::GetBmp (LPCSTR pDLLName)
{
CTable r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) {	// gefunden
			TX_ASSERT(l -> isA() == Extension::OleExt);
			return ((COleExtension *)(Extension *)l) -> GetBmp();
		}
	}
	return 0;	// nichts gefunden
}

EXTENSIONFLAG ExtensionList::GetFlags (LPCSTR pDLLName) 
{
CTable r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return l -> GetFlags();
	}

return (EXTENSIONFLAG)0;	// nichts gefunden
}


// ReferenzZähler für eine Erweiterung richten --------------------------------
long ExtensionList::AddRef (LPCSTR pDLLName) 
{
CTable r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) // gefunden
			return l -> AddRef();
	}

return -1;	// nichts gefunden
}


long ExtensionList::Release (LPCSTR pDLLName) 
{
CTable r (*this);
string strSrch (pDLLName);

	strupr ((char *)strSrch.c_str());	// GroßBuchstaben

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) 	// gefunden
			return l -> Release();
	}

return -1;	// nichts gefunden
}



// überprüft, ob ein MenuEvent zu einer Extenson gehört und leitet diesen ggf.
// entsprechend weiter
bool ExtensionList::DispatchMenuCommand (MenuCommandEvt e, HWND iORMenu)
{
short iItem = e.GetItemID();
CTable r (*this);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l) continue;
		if (l -> isMyID (iItem)) {
			l -> MenuCommand (e, iORMenu);
			return true;		// ok, weiter
		}
	}

return false;
}

// Memberfunktionen für die Extension selbst ----------------------------------
// Konstruktoren/Destruktoren -------------------------------------------------
Extension::Extension (HWND hWnd, LPCSTR pExtName, LPCSTR pDLLName, int toLoad)
	   : m_strExtName (pExtName),
	     m_strDLLName (pDLLName),
	     m_iToLoad (toLoad)
{
	strupr ((LPSTR)m_strDLLName.c_str());		// GroßBuchstaben

	m_hWnd = hWnd;		// FensterHandle
	m_uiMenuOffset = 0;
	m_hMenuHandle = 0;
	m_iMenuIndex = 0;
	m_hORMenuHandle = 0;
	m_iORMenuIndex = -1;
	m_fIsGlobal = true;
	m_fUnLoadable = true;
#if defined(WIN32)
	m_fVisible = true;
#endif // WIN32
	m_fCanImport = false;
	m_fDynImportCfg = false;
		
	m_ulRefCnt = 0;
}

Extension::Extension (Extension &Ext) 
	   : m_strExtName (Ext.m_strExtName),
	     m_strDLLName (Ext.m_strDLLName),
	     m_strMenuString (Ext.m_strMenuString),
	     m_strORMenuString (Ext.m_strORMenuString)
{
// Werte aus alter Extension kopieren
	m_hWnd = Ext.hWnd();
	m_uiMenuOffset = Ext.m_uiMenuOffset;

	m_hMenuHandle = Ext.m_hMenuHandle;
	m_hORMenuHandle = Ext.m_hORMenuHandle;
	m_iMenuIndex = Ext.m_iMenuIndex;
	m_iORMenuIndex = Ext.m_iORMenuIndex;

	m_iToLoad = Ext.m_iToLoad;
	m_fIsGlobal = Ext.m_fIsGlobal;
	m_fUnLoadable = Ext.m_fUnLoadable;
#if defined(WIN32)
	m_fVisible = Ext.m_fVisible;
#endif // WIN32
	m_fCanImport = Ext.m_fCanImport;
	m_fDynImportCfg = Ext.m_fDynImportCfg;
	
	m_ulRefCnt = Ext.m_ulRefCnt;

// Pointer in alter Extension ausnullen, um doppeltes delete zu vermeiden
	Ext.m_hMenuHandle = 0;
	Ext.m_hORMenuHandle = 0;
	Ext.m_iToLoad = 0;
	Ext.m_ulRefCnt = 0;
	Ext.m_strMenuString.remove();
	Ext.m_strORMenuString.remove();
}

Extension::~Extension (void) 
{
	m_hMenuHandle = 0;
	m_hORMenuHandle = 0;
}

EXTENSIONFLAG Extension::GetFlags (void)
{
EXTENSIONFLAG rgFlags = isGlobal() ? EF_Global : 0;

	if (isUnLoadable()) rgFlags = EXTENSIONFLAG(rgFlags | EF_UnLoadable);
	if (isVisible()) rgFlags = EXTENSIONFLAG(rgFlags | EF_Visible);
	if (FCanImport()) rgFlags = EXTENSIONFLAG(rgFlags | EF_CanImport);
	if (FDynImportCfg()) rgFlags = EXTENSIONFLAG(rgFlags | EF_DynImportCfg);

return rgFlags;
}

// Erweiterung alten Typs -----------------------------------------------------
Extension::ExtensionType COleExtension::isA (void) { return OleExt; }

// Erweiterung, die über OLE geladen wird -------------------------------------
COleExtension::COleExtension (HWND hWnd, LPCSTR pExtName, LPCSTR pProgID, 
				REFCLSID rClsId, bool toLoad, UINT uiBmp, LPCSTR pcRegKey)
	       : Extension (hWnd, pExtName, pProgID, toLoad),
	         m_ClsId (rClsId), m_uiBmp(uiBmp)
{
	m_pIUnk = NULL;
	m_pTE = NULL;
	m_pOPs = NULL;
	m_fHasOPs = true;	// erst mal für Angeklagten entscheiden
	m_fHasCOPs = true;
	m_fAggregated = false;
	m_fNoDragDropTarget = false;
	m_fNoDragDropSource = false;
	m_hDex = NULL;

	if (NULL != pcRegKey)
		m_strRegKey = pcRegKey;
}

COleExtension::COleExtension (COleExtension &rExt)
	       : Extension (rExt), m_ClsId (rExt.m_ClsId), m_hDex (rExt.m_hDex), 
		     m_strRegKey (rExt.GetRegKey()), m_uiBmp(rExt.GetBmp())
{
	m_pIUnk = rExt.m_pIUnk;
	if (m_pIUnk) m_pIUnk -> AddRef();

	m_pTE = rExt.m_pTE;
	if (m_pTE) m_pTE -> AddRef();

	m_pOPs = rExt.m_pOPs;
	if (m_pOPs) m_pOPs -> AddRef();

	m_fHasOPs = rExt.m_fHasOPs;
	m_fHasCOPs = rExt.m_fHasCOPs;
	m_fAggregated = rExt.m_fAggregated;
	m_fNoDragDropTarget = rExt.m_fNoDragDropTarget;
	m_fNoDragDropSource = rExt.m_fNoDragDropSource;
}

COleExtension::~COleExtension (void)
{
// wenn DLL noch geladen ist, dann UnLoad() abarbeiten
	if (hLib() != 0) 
		UnLoad();
	if (m_pOPs) m_pOPs -> Release();
	if (m_pTE) m_pTE -> Release();
	if (m_pIUnk) m_pIUnk -> Release();

	if (m_pTE != NULL || m_pOPs != NULL) {
		CoFreeUnusedLibraries();	// DLL freigeben
		m_pTE = NULL;
		m_pOPs = NULL;
		m_pIUnk = NULL;
	}
	m_hDex = NULL;
}


// virtuelle Funkltionen ------------------------------------------------------
HDEX COleExtension::Load (TRIASLOADEX &DL, IUnknown *pIUnkOut, HPROJECT hPr, IUnknown *pIXtsn) 
{
	if (!isLoaded() || m_pTE == NULL) {
	// DLL noch nicht angebunden
		TX_ASSERT(NULL == pIUnkOut || IsAggregated());		// wenn aggregiert, dann muß pIUnk gegeben sein

	WUnknown UnkExt (pIXtsn);

		try {
		HRESULT hr = S_OK;

			if (!UnkExt.IsValid())
				hr = UnkExt.CreateInstance (m_ClsId, CLSCTX_INPROC_SERVER, pIUnkOut);

			if (CLASS_E_NOTLICENSED == GetScode(hr))
				hr = HandleLicense (pIUnkOut);		// Lizensierung behandeln
			if (FAILED(hr)) _com_issue_error(hr);

			hr = UnkExt -> QueryInterface (IID_ITriasXtension, (LPVOID *)&m_pTE);
			if (FAILED(hr)) {					// evtl. externe Erweiterung
				TX_ASSERT(!IsAggregated());		// externe Erweiterungen nicht aggregieren

			WInitDTRiASExtension ExtInit (CLSID_WrapperExtension);
			
				THROW_FAILED_HRESULT(ExtInit -> InitDTRiASExtension (UnkExt, reinterpret_cast<long>(hPr)));
				
			// eigentliche Erweiterung speichern
				THROW_FAILED_HRESULT(ExtInit -> QueryInterface (IID_ITriasXtension, (LPVOID *)&m_pTE));
				UnkExt = ExtInit;		// throws hr
	
			} else {
			// wenn diese Erweiterung zusätzlich initialisiert werden will
			WInitDTRiASExtension ExtInit;
				
				hr = UnkExt -> QueryInterface (IID_IInitDTRiASExtension, ExtInit.ppv());
				if (SUCCEEDED(hr)) {
				CComBSTR bstrRegKey (GetRegKey().c_str());

					THROW_FAILED_HRESULT(ExtInit -> InitDTRiASExtensionRegKey (bstrRegKey, reinterpret_cast<long>(hPr)));
				}
			}

		} catch (_com_error&) {
			SetLoaded (0);
			return NULL;			// Fehler, nicht ladbar
		}

		m_pIUnk = UnkExt.detach();
		SetLoaded (DL.m_iMode);
	}
	if (NULL == m_pTE || (m_hDex = m_pTE -> LoadExtension (&DL, hWnd())) == NULL) {
		SetLoaded(0);
		return NULL;
	}

	return m_hDex;
}

///////////////////////////////////////////////////////////////////////////////
// globale Funktionen, die bequem eine Messagebox anzeigen
static char s_cbOut[4*_MAX_PATH];

StdMessBoxReply VMessageBox (
	Window *pW, LPCSTR pcCaption, StdMessBox rgType, ResID uiText, ...)
{
ResString resFormat (uiText, 2*_MAX_PATH); 
va_list params;

	va_start (params, uiText);
	wvsprintf (s_cbOut, resFormat, params);
	va_end (params);

MessBox mb (pcCaption, s_cbOut, pW);

	mb.SetType (rgType);
	return mb.Show();
}

StdMessBoxReply VMessageBox (
	Window *pW, ResID uiCaption, StdMessBox rgType, ResID uiText, ...)
{
ResString resCaption (uiCaption, _MAX_PATH);
ResString resFormat (uiText, 2*_MAX_PATH); 
va_list params;

	va_start (params, uiText);
	wvsprintf (s_cbOut, resFormat, params);
	va_end (params);

MessBox mb (resCaption, s_cbOut, pW);

	mb.SetType (rgType);
	return mb.Show();
}

string FakeTRiASName (UINT resID, ...)
{
	try {
	ResString resTempl (resID, _MAX_PATH);
	va_list params;

		va_start (params, resID);
		wvsprintf (s_cbOut, resTempl, params);
		va_end (params);

		return string(s_cbOut);
	
	} catch (...) {
	// irgendein Fehler
		return string(g_cbNil);
	}
}

string FakeTRiASName (LPCSTR pcTempl, ...)
{
	try {
	va_list params;

		va_start (params, pcTempl);
		wvsprintf (s_cbOut, pcTempl, params);
		va_end (params);

		return string(s_cbOut);
	
	} catch (...) {
	// irgendein Fehler
		return string(g_cbNil);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
HRESULT COleExtension::HandleLicense (IUnknown *pIUnk)
{
// versuchen, Erweiterung doch noch zu laden
LPCLASSFACTORY2 pCF2 = NULL;
HRESULT hr = CoGetClassObject (m_ClsId, CLSCTX_INPROC_SERVER, NULL, 
			       IID_IClassFactory2, (LPVOID *)&pCF2);

	if (FAILED(hr)) return hr;	// not available

// ok, jetzt Key abfragen
BSTR bKey;
Window Wnd (m_hWnd);

	{
	CLicenseDlg LDlg (&Wnd, ExtName());

		LDlg.Show (Centre);
		if (0 == LDlg.Result()) {
			VMessageBox (&Wnd, IDS_LICENSING, ExclamationIcon|OkayButton, IDS_NOTLICENSED, ExtName().c_str());
			pCF2 -> Release();
			return ResultFromScode (CLASS_E_NOTLICENSED);
		}
		bKey = LDlg.GetKey();
	}

// jetzt versuchen, mit Lizenz zu laden
	hr = pCF2 -> CreateInstanceLic (pIUnk, NULL, IID_IUnknown, 
					bKey, (LPVOID *)&m_pIUnk);
	pCF2 -> Release();
	SysFreeString (bKey);

// wenn Lizenz nicht verifiziert werden konnte
	if (CLASS_E_NOTLICENSED == GetScode(hr))
		VMessageBox (&Wnd, IDS_LICENSING, ExclamationIcon|OkayButton, IDS_NOTLICENSED, ExtName().c_str());

return hr;
}

bool COleExtension::UnLoad (void) 
{
	if (isLoaded() && m_pTE != NULL) {
	bool fResult = m_pTE -> UnLoadExtension();
	
		SetLoaded (fResult ? 0 : isLoaded());
		if (!isLoaded())
			m_hDex = NULL;
		return fResult;
	}

return false;
}

// Extension wurde erfolgreich geladen, selbiges kundtun ----------------------
bool COleExtension::Init (short iMode, ITriasXtensionSite *pXtnSite) 
{
	if (isLoaded() && m_pTE != NULL) {
	ITriasXtension2 *pXtn2 = NULL;

	// VOR InitExtension muß Basisklasse der Erweiterung fertig initialisiert sein
		if (SUCCEEDED(QueryInterface (IID_ITriasXtension2, (LPVOID *)&pXtn2))) {
			pXtn2 -> SetXtensionSite (pXtnSite);
			pXtn2 -> Release();
		}

		return m_pTE -> InitExtension (iMode);
	}

return false;
}

LRESULT COleExtension::Notify (HWND, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_pTE == NULL) return false;

	if (uiMsg == __DexNotify)	// interne Message
		return m_pTE -> Notification (wParam, lParam);

return m_pTE -> WindowsNotification (uiMsg, wParam, lParam);
}

HRESULT COleExtension::GetImportIF (LPIMPORTGEODATA *ppIImport) 
{
	if (m_pIUnk == NULL) ResultFromScode (E_FAIL);

return QueryInterface (IID_IImportGeoData, (LPVOID *)ppIImport);
}

// Liefert sonstiges Interface einer Erweiterung ------------------------------
HRESULT COleExtension::QueryInterface (REFIID riid, LPVOID *ppIUnk) 
{
	TX_ASSERT(NULL != m_pIUnk);
	if (m_pIUnk == NULL) ResultFromScode (E_FAIL);

return m_pIUnk -> QueryInterface (riid, ppIUnk);
}

// liefert ConfigInfo einer ImportErweiterung ---------------------------------
HRESULT COleExtension::GetConfigInfo (IEnumString **ppIStr)
{
IImportGeoData *pIImport = NULL;
HRESULT hr = QueryInterface (IID_IImportGeoData, (LPVOID *)&pIImport);

	if (FAILED(hr)) return hr;

	hr = pIImport -> GetConfigInfo (ppIStr, 0L);
	pIImport -> Release();

return hr;
}

// überprüfen, ob diese MenuMeldung für uns ist -------------------------------
bool Extension::isMyID (UINT wItem) 
{
	return (isLoaded() && wItem > MenuOffset() && 
		wItem <= MenuOffset() + DEX_MENUOFFSETDELTA);
}

// überprüfen, ob unser PopupMenu gerufen wird --------------------------------
short Extension::isMyMenu (MenuInitEvt e) 
{
	if (!isLoaded()) return 0;

// wenn es kein MenuInit für ein PopupMenu ist
	if (e.Msg() != WM_INITMENUPOPUP) return 0;

// wenn es mein PopupMenu ist
	if (((HMENU)e.WParam() == ORMenuHandle() || 
	     (HMENU)e.WParam() == MenuHandle()))
		return 1;

// wenn es ein Popupmenu ist, in welchem ich meine MenuPunkte habe
	if (hasMenuItems (LOWORD (e.LParam())))
		return 2;

return 0;
}


// Feststellen, ob in diesem PopupMenu MenuItems dieser Extension hängen
bool Extension::hasMenuItems (short /*iPopupCnt*/)
{
	return true;	// erstmal immer wahr liefern
}

class CBlinkOff
{
public:
	CBlinkOff() { DEX_CancelMode (true); }
	~CBlinkOff() { DEX_CancelMode (false); }
};

// Initialisieren der MenuItems in der Nutzer-DLL -----------------------------
bool COleExtension::MenuInit (MenuInitEvt e, HWND hWnd) 
{
	if (m_pTE) {
	CBlinkOff BOff;

		return m_pTE -> MenuInit ((HMENU)e.WParam(), e.LParam(), hWnd);
	}

return false;
}

// Auswählender MenuCommands in de Nutzer-DLL ---------------------------------
bool COleExtension::MenuSelect (MenuSelectEvt e, HWND hWnd) 
{
	if (m_pTE) {
	HMENU hMenu = (HMENU)e.LParam();
	CBlinkOff BOff;

		return m_pTE -> MenuSelect (LOWORD(e.WParam())-MenuOffset(), 
					    hMenu, hWnd);
	}

return false;
}

// Auslösen der MenuCommands in de Nutzer-DLL ---------------------------------
bool COleExtension::MenuCommand (MenuCommandEvt e, HWND hORWnd) 
{
	if (m_pTE != NULL) {
	CBlinkOff BOff;

		return m_pTE -> MenuCommand (LOWORD(e.WParam())-MenuOffset(), hORWnd);
	}

return false;
}


// Abfragen einer ErweiterungsEigenschaft ------------------------------------
int COleExtension::GetCapability (WPARAM iCapType)
{
	if (m_pTE) return (int)m_pTE -> GetCapabilities (iCapType);

return 0;
}	

// Enumeration der EnumPropFunctionen einer Erweiterung ----------------------
bool COleExtension::EnumObjPropFuncs (ENUMOBJPROPDATA *pEOPD, LONG lRefONr)
{
	if (!m_fHasOPs || NULL == m_pTE) return true;

	if (NULL == m_pOPs) {
	HRESULT hr = QueryInterface (IID_IObjectProps, (LPVOID *)&m_pOPs);

		if (FAILED(hr)) {
			m_fHasOPs = false;
			return true;
		}
	}

// Objekteigenschaften neu generieren (für lRefONr) und Enum liefern
LPENUMOBJPROPS pIEnumOPs = NULL;
LPOBJECTPROPERTY pIOP = NULL;
bool fR = true;

//	if (0 != lRefONr)
		m_pOPs -> OnNewReferenceObject (lRefONr);

	if (FAILED(m_pOPs -> EnumObjectProps (&pIEnumOPs))) {
//		m_fHasOPs = false;	// vielleicht nur diesmal keine OProps
		return true;
	}
	for (pIEnumOPs -> Reset(); 
	     S_OK == pIEnumOPs -> Next(1, (LPUNKNOWN *)&pIOP, NULL); )
	{
	char cbBuffer[_MAX_PATH];

		pIOP -> GetPropInfo(cbBuffer, _MAX_PATH, NULL);

	// neue Erweiterungen haben hier keinen FuncID (alles geht über den Namen -
	// nomen est omen)
		fR = (*pEOPD -> pFunc)(cbBuffer, 0, true, pEOPD -> pPtr);
		if (pIOP) pIOP -> Release();
		if (!fR) break;
	}
	pIEnumOPs -> Release();

return fR;
}

HRESULT COleExtension::EnumObjPropFuncs (
	LONG lRefONr, LPENUMOBJPROPS *ppIEnumOPs, LPOBJECTPROPS *ppIObjProps)
{
	if (!m_fHasOPs || NULL == m_pTE) 
		return S_FALSE;

	if (NULL == m_pOPs) {
		if (FAILED(QueryInterface (IID_IObjectProps, (LPVOID *)&m_pOPs))) {
			m_fHasOPs = false;
			return S_FALSE;
		}
	}

#if defined(WIN32)
// Objekteigenschaften neu generieren (für lRefONr) und Enum liefern
//	if (0 != lRefONr)
		m_pOPs -> OnNewReferenceObject (lRefONr);
#endif // WIN32

	if (NULL != ppIObjProps) {
		*ppIObjProps = m_pOPs;
		LPUNKNOWN(*ppIObjProps) -> AddRef();
	}

	if (NULL != ppIEnumOPs) {
	HRESULT hr = m_pOPs -> EnumObjectProps (ppIEnumOPs);

		if (FAILED(hr) && (NULL != ppIObjProps)) {
			LPUNKNOWN(*ppIObjProps) -> Release();
			*ppIObjProps = NULL;
		}
		return hr;
	}
			
	return S_OK;
}


HRESULT COleExtension::EnumClsPropFuncs (
	IEnumLONG *pEnumObj, LPENUMCLASSPROPS *ppIEnumOPs, LPOBJECTPROPS *ppIObjProps)
{
	if (!m_fHasCOPs || NULL == m_pTE) 
		return ResultFromScode(S_FALSE);

	if (NULL == m_pOPs) {
		if (FAILED(QueryInterface (IID_IObjectProps, (LPVOID *)&m_pOPs))) {
			m_fHasCOPs = false;
			return ResultFromScode(S_FALSE);
		}
	}

#if defined(WIN32)
// Objekteigenschaften neu generieren (für pEnumObj) und Enum liefern
	m_pOPs -> OnNewReferenceClass (pEnumObj);
#endif // WIN32

	if (NULL != ppIObjProps) {
		*ppIObjProps = m_pOPs;
		LPUNKNOWN(*ppIObjProps) -> AddRef();
	}

HRESULT hr = m_pOPs -> EnumClassProps (ppIEnumOPs);

	if (FAILED(hr) && (NULL != ppIObjProps)) {
		LPUNKNOWN(*ppIObjProps) -> Release();
		*ppIObjProps = NULL;
	}
		
return hr;
}

char *COleExtension::InvokePropFunc (INVOKEOBJPROPDATA *pIOPD)
{
	if (!m_fHasOPs) return NULL;	// hat keine OPF's

	if (m_pOPs == NULL) {	
	HRESULT hr = QueryInterface (IID_IObjectProps, (LPVOID *)&m_pOPs);

		if (FAILED(hr)) {
			m_fHasOPs = false;
			return NULL;	// hat keine OPF's
		}
	}

LPOBJECTPROPERTY pIObjProp = NULL;
LPENUMOBJPROPS pIEnumProps = NULL;
HRESULT hr = m_pOPs -> EnumObjectProps (&pIEnumProps);

	if (FAILED(hr)) return NULL;

	if (0 == pIOPD -> iFuncID) {
		if (pIOPD -> dwSize != sizeof(INVOKEOBJPROPDATAEX)) 
			hr = ResultFromScode (E_FAIL);
		else
			hr = pIEnumProps -> FindByName (((INVOKEOBJPROPDATAEX *)pIOPD) -> pFName, &pIObjProp);
	} else
		hr = ResultFromScode (E_FAIL);

	pIEnumProps -> Release();
	if (FAILED(hr)) return NULL;

	if (0 < pIOPD -> lONr) {
		hr = pIObjProp -> Eval (pIOPD -> lONr, pIOPD -> pBuff, 
					pIOPD -> iBuffLen, NULL);
	} else switch (OBJPROPTYPE(pIOPD -> lONr)) {
	case OBJPROP_RESET:
		hr = pIObjProp -> Reset();
		break;

	case OBJPROP_COUNT:
		{
		ULONG ulCnt = pIObjProp -> Count();

			hr = NOERROR;
			ultoa (pIObjProp -> Count(), pIOPD -> pBuff, 10);
		}
		break;

	case OBJPROP_CUMULATION:
		hr = pIObjProp -> Cumulation (pIOPD -> pBuff, 
					      pIOPD -> iBuffLen, NULL);
		break;

	case OBJPROP_GETHELPTEXT:	// hier verboten
	case OBJPROP_EVAL:		// bereits behandelt
	default:
		TX_ASSERT(false);
		hr = ResultFromScode (E_FAIL);
		break;
	}
	pIObjProp -> Release();

return SUCCEEDED(hr) ? pIOPD -> pBuff : NULL;
}

char *COleExtension::GetHelpText (GETHELPTEXTDATA *pGHTD)
{
	if (!m_fHasOPs) return NULL;	// hat keine OPF's

	if (m_pOPs == NULL) {
	HRESULT hr = QueryInterface (IID_IObjectProps, (LPVOID *)&m_pOPs);

		if (FAILED(hr)) {
			m_fHasOPs = false;
			return NULL;	// hat keine OPF's
		}
	}

LPOBJECTPROPERTY pIObjProp = NULL;
LPENUMOBJPROPS pIEnumProps = NULL;
HRESULT hr = m_pOPs -> EnumObjectProps (&pIEnumProps);

	if (FAILED(hr)) return NULL;

	if (0 == pGHTD -> iFuncID) {
		if (pGHTD -> dwSize != sizeof(GETHELPTEXTDATAEX)) 
			hr = ResultFromScode (E_FAIL);
		else
			hr = pIEnumProps -> FindByName (((GETHELPTEXTDATAEX *)pGHTD) -> pFName, &pIObjProp);
	} else
		hr = ResultFromScode (E_FAIL);

	pIEnumProps -> Release();
	if (FAILED(hr)) return NULL;

	if (pGHTD -> dwSize == sizeof(GETHELPTEXTDATA)) {
		hr = pIObjProp -> HelpInfo (pGHTD -> pBuff, pGHTD -> iBuffLen, 
					    NULL, NULL);
	} else if (pGHTD -> dwSize == sizeof(GETHELPTEXTDATAEX)) {
	GETHELPTEXTDATAEX *pGHTDEx = (GETHELPTEXTDATAEX *)pGHTD;

		hr = pIObjProp -> HelpInfo (pGHTDEx -> pBuff, pGHTDEx -> iBuffLen, 
					    pGHTDEx -> pHelpFile, &pGHTDEx -> ulHelpCtx);
	}
	pIObjProp -> Release();

return SUCCEEDED(hr) ? pGHTD -> pBuff : NULL;
}

HDEX COleExtension::hLib (void) 
{ 
	TX_ASSERT(!isLoaded() || NULL != m_hDex); 
	return m_hDex; 
}

// Einlesen der TRIAS-Erweiterungen ------------------------------------------
ErrCode ExtDirisWindow::LoadAllExtensions (const char *pIni, bool isGlobal) 
{
ErrInstall EI (EC_EXTINITFAILURE);		// keine Fehler melden

	LoadAllExtensionsRegistry();		// erst aus Registry

return LoadAllExtensionsINI (pIni, isGlobal);		// dann aus INI
}

// Aus der SystemRegistry ----------------------------------------------------
bool ExtDirisWindow::LoadAllExtensionsRegistry (void)
{
#if defined(WIN32)
#if defined(ENABLE_WIN32S_CODE)
	if (IsWin32s()) return true;
#endif // ENABLE_WIN32S_CODE

HKEY hKey = NULL;
char cbTriasKey[_MAX_PATH];
DWORD retCode = RegOpenKey (HKEY_CURRENT_USER, g_cbRegExtensions, &hKey);

	if (retCode != ERROR_SUCCESS) return false;

// alle Erweiterungen entsprechend Priorität laden (zuerst die wichtigen, dann alle anderen)
	for (LONG dwLS = MAX_PRIORITYLOAD; dwLS >= MIN_PRIORITYLOAD; dwLS--) {
	DWORD i = 0;

		while (RegEnumKey (hKey, i++, cbTriasKey, _MAX_PATH) == ERROR_SUCCESS) {
		string strTriasKey = cbTriasKey;

			LoadExtensionRegistry (strTriasKey, (DWORD)dwLS);
		}
	}

// Schlüssel wieder abschließen
	RegCloseKey (hKey);   // Close the key handle.

#endif // WIN32
return true;
}

#if defined(WIN32)

bool ExtDirisWindow::LoadExtensionRegistry (string &strProgID, DWORD dwPriority)
{
// auswerten der Registry
string strExtKey (g_cbRegExtensions);
string strName (strProgID);

	{
	CCurrentUser regExt (strExtKey.c_str());

		if (regExt.isValid()) {
		TCHAR cbName [_MAX_PATH];
		LONG lLen = _MAX_PATH;

			if (regExt.GetSZ (strProgID.c_str(), cbName, lLen))
				strName = cbName;
		}
	}
	strExtKey += string(g_cbDel) + strProgID + g_cbDel + g_cbConfig;

CCurrentUser regCfg (strExtKey.c_str());
int fToLoad = LENoLoad;
EXTENSIONFLAG rgFlags = EF_Global;

	if (regCfg.isValid()) {
	DWORD dwData = 0L;

		regCfg.GetDWORD (g_cbPriorityLoad, dwData);
		TX_ASSERT(dwData <= MAX_PRIORITYLOAD && dwData >= MIN_PRIORITYLOAD);
		
		if (dwPriority != dwData)
			return true;		// noch nicht oder nicht mehr dran
			
		if (regCfg.GetDWORD (g_cbPreLoad, dwData))
			fToLoad = dwData ? LEFullLoad : LENoLoad;
		if (regCfg.GetDWORD (g_cbUnLoadable, dwData))
			if (dwData) rgFlags = EXTENSIONFLAG(rgFlags | EF_UnLoadable);
		if (regCfg.GetDWORD (g_cbVisible, dwData))
			if (dwData) rgFlags = EXTENSIONFLAG(rgFlags | EF_Visible);
		if (regCfg.GetDWORD (g_cbCanImport, dwData) && dwData != 0) {
			rgFlags = EXTENSIONFLAG(rgFlags | EF_CanImport);
			rgFlags = EXTENSIONFLAG(rgFlags | EF_DynImportCfg);
		}
		if (regCfg.GetDWORD (g_cbAggregate, dwData) && dwData != 0) {
			TX_ASSERT(LEFullLoad == fToLoad);		// zu aggregierende Erweiterungen müssen PreLoad sein
			rgFlags = EXTENSIONFLAG(rgFlags | EF_Aggregate);
		}
	}

// eigentliches Laden
string strRegKey (g_cbRegExtensions);

	strRegKey += string(g_cbDel) + strProgID;
	LoadExtension (strName.c_str(), strProgID.c_str(), fToLoad, rgFlags, strRegKey.c_str());

return true;
}

bool SavePreloadStatus (const string &strProgID, bool fPreload)
{
string strKey = g_cbRegExtensions;
DWORD dwData = fPreload ? true : false;

	strKey += string(g_cbDel) + strProgID + g_cbDel + g_cbConfig;

CCurrentUser regCfg (strKey.c_str());

	return regCfg.SetDWORD (g_cbPreLoad, dwData);
}

DWORD GetPriorityLoadStatus (const string &strProgID)
{
string strKey = g_cbRegExtensions;

	strKey += string(g_cbDel) + strProgID + g_cbDel + g_cbConfig;

CCurrentUser regCfg (strKey.c_str());
DWORD dwData = 0L;

	if (regCfg.GetDWORD (g_cbPriorityLoad, dwData)) 
		return dwData;

	return 0;		// kein Eintrag vorhanden
}

#endif

// Aus der gegebenen INI -----------------------------------------------------
ErrCode ExtDirisWindow::LoadAllExtensionsINI (const char *pIni, bool isGlobal) 
{
ResString Params (IDS_IRISPARS, 15);
ResString Extension (IDS_EXTENSION, 15);

// evtl. Erweiterungen laden
int ExtNums = GetPrivateProfileInt (Params, 
				    ResString (IDS_EXTNUMS, 32), 
				    0, pIni);

	if (ExtNums > 0) {
	// wenn Extensionen gegeben sind
	char *ExtNamesStr = new char [ExtNums*80+1];
	char **ExtNames = new char *[ExtNums];

		if (ExtNamesStr == NULL || ExtNames == NULL) {
			DELETE (ExtNamesStr);
			return (ErrCode)db_error (EC_NOMEMORY, RC_LoadAllExtensions);
		}
		GetPrivateProfileString (Extension, NULL, "", ExtNamesStr,
						    ExtNums*80+1, pIni);
		ExtNames[0] = ExtNamesStr;

	int len = 0;

		for (int i = 1; i < ExtNums; i++)
			ExtNames[i] = &ExtNamesStr[len += strlen(ExtNames[i-1])+1];

	// Laden der beim Start zu ladenden Extensionen
		for (i = 0; i < ExtNums; i++) {
		char currExt[80];

		// Beschreibung der Extension lesen
			GetPrivateProfileString (Extension, ExtNames[i], "",
						 currExt, 80, pIni);

		// Wenn Extension geladen werden soll, dann selbiges auch tun
		char *pDLLName = strtok (currExt, ",;");
		char *pFlags = strtok (NULL, ",;");
		int toLoad = (NULL != pFlags) ? atoi (pFlags) : 1;
		EXTENSIONFLAG rgFlags = (EXTENSIONFLAG)0;
		
			if (!(toLoad & 0x02)) rgFlags = EXTENSIONFLAG(rgFlags | EF_UnLoadable);
			if (!(toLoad & 0x04)) rgFlags = EXTENSIONFLAG(rgFlags | EF_Visible);
			if (toLoad & 0x08) rgFlags = EXTENSIONFLAG(rgFlags | EF_CanImport);
			if (toLoad & 0x10) rgFlags = EXTENSIONFLAG(rgFlags | EF_DynImportCfg);

			if (isGlobal) rgFlags = EXTENSIONFLAG(rgFlags | EF_Global);
			else {
				toLoad = 1;
				rgFlags = EXTENSIONFLAG(rgFlags & ~EF_Global);
			}

			LoadExtension (ExtNames[i], pDLLName, 
				       (toLoad & 0x1) ? LEFullLoad : LENoLoad, 
				       rgFlags, ExtNames[i]);
		}

	// Speicher wieder freigeben
		DELETE (ExtNames);
		DELETE (ExtNamesStr);
	}

return EC_OKAY;
}

/*
bool ExtDirisWindow::doLoadExtension (void)
{
CManageExtDlg *pDlg = CManageExtDlg::CreateInstance (this, *m_pEL);

	if (pDlg == NULL) return false;
	
	pDlg -> Show (Centre);
	if (pDlg -> Result()) {
	CEierUhr Wait (this);		// kann etwas dauern

	// alles, was zu entladen ist, entladen
		if (pDlg -> GetFirstExtName()) {
			do {
				if (pDlg -> toUnload()) {
					ReUnLoadExtension (pDlg -> GetExtName(), 
							   pDlg -> GetDLLName());
				}
			} while (pDlg -> GetNextExtName());
		}
	// alles, was zu laden ist, laden
		if (pDlg -> GetFirstExtName()) {
			do {
				if (pDlg -> toLoad()) {
					LoadExtension (pDlg -> GetExtName(), 
						       pDlg -> GetDLLName(), 
						       LEFullLoad, pDlg -> GetFlags());
				}
			} while (pDlg -> GetNextExtName());
		}
		delete pDlg;
		return true;
	}
	delete pDlg;

return false;
}
*/
bool ExtDirisWindow::ReUnLoadExtension (
		const char *pExtName, const char *pDLLName, short iMode)
{
// das Ganze nur machen, wenn diese Erweiterung wirklich geladen ist
HDEX hDex = 0;

	if (!m_pEL -> isLoaded (pDLLName, hDex) || 
	    (iMode != LEFullLoad && m_pEL -> Release (pDLLName) > 0)) 
	{
		return false;
	}

EXTENSIONFLAG rgFlags = m_pEL -> GetFlags (pDLLName);
string strRegKey = m_pEL -> GetRegKey (pDLLName);

// Erweiterung rausnehmen und gleich wieder reinbauen
	if (UnLoadExtension (pExtName, true)) 
		LoadExtension (pExtName, pDLLName, 0, rgFlags, strRegKey.c_str());

return true;
}


bool ExtDirisWindow::UnLoadLocalExtensions (void)
{
	if (m_pEL == NULL) return false;
	
CTable r (*m_pEL);
HDEX hDex = NULL;

	for (r.First(); r.Valid(); r.Next()) {
	bool toDelete = false;
	string strExtName;

		{
		ExtensionLock l(r);

			if (l && !l -> isGlobal()) {
				toDelete = true;
				strExtName = l -> ExtName();
				hDex = l -> hLib();
			}
		}
		if (toDelete) {
			UnLoadExtension (strExtName.c_str(), true);
			TX_ASSERT(!m_pQNH -> ExtHasRegisteredNfys (hDex));
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// Erweiterungen enumerieren
extern "C"
inline BOOL EnumExtensionProc (ENUMNOKEYPROC pF, LPCSTR pExtName, BOOL fNotLast, void *pPtr)
{
	return ((BOOL (CALLBACK *)(char *, BOOL, void *))pF)((char *)pExtName, fNotLast, pPtr);
}

LRESULT ExtDirisWindow::EnumExtensions (ENUMNOKEY *pK)
{
	if (m_pEL == NULL) return FALSE;

CTable r (*m_pEL);

	for (r.First(); r.Valid(); /**/) {
	string strExtName;
	ExtensionLock l(r);
	BOOL fNotLast = r.Next();

		if (l) {
			strExtName = l -> DLLName();
			if (!EnumExtensionProc (pK -> eFcn, strExtName.c_str(), fNotLast, pK -> ePtr))
				return FALSE;		// enumeration abbrechen
		}
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Alle Info's einer Extension abfragen
LRESULT ExtDirisWindow::GetExtensionInfo (EXTENSIONINFO *pInfo)
{
	if (m_pEL == NULL) return false;
	
CTable r (*m_pEL);
string strSrch (pInfo -> pcDLLName);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) {	// gefunden
			pInfo -> hDex = (HDEX)l -> hLib();	// HDEX liefern

#if _MSC_VER < 1100
		int iLen = min(l -> ExtName().length(), (size_t)(pInfo -> iLen-1));
#else
		int iLen = min(l -> ExtName().size(), (size_t)(pInfo -> iLen-1));
#endif // _MSC_VER < 1100
	
			strncpy (pInfo -> pName, l -> ExtName().c_str(), iLen);
			pInfo -> pName[iLen] = '\0';
			pInfo -> iLen = iLen;

			pInfo -> rgFlags = l -> GetFlags();
			pInfo -> iLoadState = l -> isLoaded();
			return TRUE;	// gefunden
		}
	}
	return FALSE;	// nicht gefunden
}

/////////////////////////////////////////////////////////////////////////////
// Alle Info's einer Extension abfragen
LRESULT ExtDirisWindow::GetExtensionPtr (EXTENSIONPTR *pInfo)
{
	if (m_pEL == NULL) return false;

CTable r (*m_pEL);
string strSrch (pInfo -> pcDLLName);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && (l -> DLLName() == strSrch)) {	// gefunden
		Extension *pExt = (Extension *)l;

			return SUCCEEDED(((COleExtension *)pExt) -> QueryInterface (IID_ITriasXtension, (LPVOID *)pInfo -> ppIUnk));
		}
	}
	return FALSE;
}

// Modifikation eines Menu's (addieren des Menuoffsets) -----------------------
void AddMenuOffset (HMENU hMenu, short iOffset)
{
	if (hMenu == 0) return;		// nur für gültige Menu's

WORD nCount = (WORD)GetMenuItemCount (hMenu);
char MenuEntry[_MAX_PATH+1];

	for (WORD wItem = 0; wItem < nCount; wItem++) {
	UINT MenuState = GetMenuState (hMenu, wItem, MF_BYPOSITION);
	UINT MenuID = GetMenuItemID (hMenu, wItem);

		if (MenuID == -1) {	// PopUpMenu
			AddMenuOffset (GetSubMenu (hMenu, wItem), iOffset);	
			continue;
		}
		if (MenuState & (MF_MENUBARBREAK | MF_MENUBREAK | MF_SEPARATOR))
			continue;
		GetMenuString (hMenu, wItem, MenuEntry, _MAX_PATH, MF_BYPOSITION);
		ModifyMenu (hMenu, wItem, MF_BYPOSITION | MenuState, MenuID+iOffset, MenuEntry);
	}
}


// ----------------------------------------------------------------------------
// DefaultProcedure zur Verwaltung nicht bearbeiteter Messages an die 
// Erweiterungen
extern "C" 
DWORD EXPORTTRIAS WINAPI DefTriasExtensionProc (HDEX, UINT, WPARAM, LPARAM)
{
	return false;
}

// Generieren eines ObjektrechercheFensters -----------------------------------
HWND ExtDirisWindow::CreateObjektInfo (DEXXCREATEOBJEKTINFO *pcrOI)
{
	if (m_pView) {
		try {
		WObjectProps IOP((ITriasXtensionSite *)m_pEL);		// throws HRESULT

			if (m_fMustInitOPFs) {
				IOP -> OnNewReferenceObject(-1L);
				if (SUCCEEDED(IOP -> OnNewReferenceObject(0L)))	// alle OPF's anzeigen
					m_fMustInitOPFs = false;
			}
		} catch (...) {
			m_fMustInitOPFs = true;
		}
		return m_pView -> CreateObjektInfo (pcrOI, *m_pEL);
	}

return NULL;
}

// Das gleiche aber für C-Schnittstelle ---------------------------------------
HWND ExtDirisWindow::CreateObjektInfo (CREATEOBJEKTINFO *pcrOI)
{
	if (m_pView) {
		try {
		WObjectProps IOP((ITriasXtensionSite *)m_pEL);		// throws HRESULT

			if (m_fMustInitOPFs) {
				IOP -> OnNewReferenceObject(-1L);
				if (SUCCEEDED(IOP -> OnNewReferenceObject(0L)))	// alle OPF's anzeigen
					m_fMustInitOPFs = false;
			}
		} catch (...) {
			m_fMustInitOPFs = true;
		}
		return m_pView -> CreateObjektInfo (pcrOI, *m_pEL);
	}

return NULL;
}

// MenuPunkt installieren -----------------------------------------------------
HMENU ExtDirisWindow::InstallMenuItem (INSTALLMENUITEM *pIMI)
{
	if (m_pEL == NULL) return NULL;	// Fehler

CTable r (*m_pEL);
bool iFound = false;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (!l || l -> hLib() != pIMI -> hDex)
			continue;

	// Extension gefunden
		if (!(pIMI -> iFlag & IMIOrigMenuItem)) 
			pIMI -> iMenuID += l -> MenuOffset();	// Offset drauftun
		iFound = true;
		break;
	}

	if (!iFound) return NULL;		// Extension nicht wiedergefunden

	if (pIMI -> iFlag & IMIObjWnd) {
	// in ORFenster einhängen
		if (m_pEL -> m_pMIL == NULL) {
			m_pEL -> m_pMIL = new MenuItemList();
			if (m_pEL -> m_pMIL == NULL)
				return NULL;
		}

	// MenuItem erzeugen ...
	MenuItemCreator MICr (*(m_pEL -> m_pMIL));
	MenuItem *pMI =	ContCreate (MICr, MenuItem)(
								pIMI -> pMenuText,
								pIMI -> hDex,
								pIMI -> iMenuID,
								pIMI -> iMenuNum
							);

		if (NULL == m_pView)
			return NULL;		// nur hier speichern

	// ... und in alle offenen Fenster einbauen
		return m_pView -> InstallMenuItem (pIMI -> iMenuID, 
					     pIMI -> iMenuNum,
					     pIMI -> pMenuText);
	} else {
	// sofort ins Hauptfenster einhängen
	HMENU hMenu = NULL;

		if (pIMI -> iFlag & IMIStartUpMenu)
			hMenu = StartUpMenu() -> Handle (API_MENU_HMENU);
		else
			hMenu = MainMenu() -> Handle (API_MENU_HMENU);

	HMENU hSubMenu = GetSubMenu (hMenu, pIMI -> iMenuNum);

		if (NULL == hSubMenu) return NULL;	// Error

	// wenn MenuPosition gegeben ist, dann dort einhängen
		if (pIMI -> dwSize == sizeof (INSTALLMENUITEM) && 
		    pIMI -> iMenuPos != -1)
		{	// neue Struktur und Wert gegeben
		// normalen MenuPunkt einfügen
			InsertMenu (hSubMenu, 
				    pIMI -> iMenuPos,		// insert
				    MF_BYPOSITION|MF_STRING, 
				    pIMI -> iMenuID, 
				    pIMI -> pMenuText);
			DrawMenuBar (Handle (API_CLIENT_HWND));
			return hSubMenu;		// hier fertig
		}
 
	// überprüfen, ob dieser Punkt der erste zusätzliche für dieses SubMenu ist
		{
		Menu TestMenu ((pIMI -> iFlag & IMIStartUpMenu) ? STARTMENU : IRISMENU);	// Menu für VergleichsZwecke
		HMENU hTestMenu = TestMenu.Handle (API_MENU_HMENU);
		HMENU hTestSubMenu = GetSubMenu (hTestMenu, pIMI -> iMenuNum);

			if (GetMenuItemCount (hTestSubMenu) == GetMenuItemCount (hSubMenu))
			// wenn es der erste ist, dann Separator einfügen
				InsertMenu (hSubMenu, (uint)-1, MF_BYPOSITION|MF_SEPARATOR, 0, NULL);
		}

	// normalen MenuPunkt einfügen
		InsertMenu (hSubMenu, (uint)-1,	// append
			    MF_BYPOSITION|MF_STRING, 
			    pIMI -> iMenuID, 
			    pIMI -> pMenuText);
		DrawMenuBar (Handle (API_CLIENT_HWND));
		return hSubMenu;
	}
}

// MenuPunkt wieder entfernen -------------------------------------------------
bool ExtDirisWindow::RemoveMenuItem (REMOVEMENUITEM *pRMI)
{
	if (m_pEL == NULL || (pRMI -> iFlag & IMIObjWnd && NULL == m_pEL -> m_pMIL)) 
		return false;	// Fehler oder noch keine Menuitems da

CTable r (*m_pEL);
bool iFound = false;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		TX_ASSERT(NULL != (Extension *)l);

		if (l -> hLib() == pRMI -> hDex) {
		// Extension gefunden
			if (!(pRMI -> iFlag & IMIOrigMenuItem)) 
				pRMI -> iMenuID += l -> MenuOffset();	// Offset drauftun
			iFound = true;
			break;
		}
	}
	if (!iFound) return false;		// Extension nicht wiedergefunden
	
	if (pRMI -> iFlag & IMIObjWnd) {
	// in ORFenstern entfernen
		if (m_pView)
			m_pView -> RemoveMenuItem (pRMI -> iMenuID, pRMI -> iMenuNum);

	// aus der Liste entfernen
		return m_pEL -> m_pMIL -> RemoveMenuItem (pRMI -> iMenuID);
	} else {
	// sofort im Hauptfenster rausnehmen
	HMENU hMenu;

		if (pRMI -> iFlag & IMIStartUpMenu)
			hMenu = StartUpMenu() -> Handle (API_MENU_HMENU);
		else
			hMenu = MainMenu() -> Handle (API_MENU_HMENU);

		if (!DeleteMenu (hMenu, pRMI -> iMenuID, MF_BYCOMMAND)) {
			TX_ASSERT(false);
			return false;
		}

	// wenn dieser Punkt der letzte zusätzliche in diesem SubMenu war, dann
	// noch den Separator rausnehmen
		{
		Menu TestMenu ((pRMI -> iFlag & IMIStartUpMenu) ? STARTMENU : IRISMENU);	// Menu für VergleichsZwecke
		HMENU hSubMenu = GetSubMenu (hMenu, pRMI -> iMenuNum);
		HMENU hTestMenu = TestMenu.Handle (API_MENU_HMENU);
		HMENU hTestSubMenu = GetSubMenu (hTestMenu, pRMI -> iMenuNum);
		short iLast = GetMenuItemCount (hSubMenu);

			if (GetMenuItemCount (hTestSubMenu) == iLast)		// nicht '-1', da wir schon einen rausgelöscht haben
			// wenn es der letzte war, dann Separator löschen
				DeleteMenu (hSubMenu, iLast, MF_BYPOSITION);
		}
		DrawMenuBar (Handle (API_CLIENT_HWND));
	}

return true;
}

#if defined(OLD_TOOLBOX)
// Werkzeug einhängen/entfernen -----------------------------------------------
extern ToolWind *pToolBox;	// Werkzeugfenster
extern bool ToolBoxCFlag;

#if defined(WIN32)
#define TOOLMAINPOPUP	4
#define TOOLPOPUP	3
#else
#define TOOLMAINPOPUP	4
#define TOOLPOPUP	1
#endif // WIN32

short ExtDirisWindow::InstallTool (INSTALLTOOL *pIT)
{
short iToolID = -1;	// für den FehlerFall
pBitmap pBmp = new Bitmap (pIT -> hBmp);

// in Werkzeugfenster einhängen
	if (!pToolBox)		// evtl. ToolFenster neu bilden
		pToolBox = new ToolWind (this);

	if (pToolBox) iToolID = pToolBox -> AddTool (pBmp);

	if (iToolID == -1) {
		DELETE (pBmp);
		return -1;	// Fehler		
	}

// zusätzlichen Punkt im Menu etablieren
HMENU hMenu = MainMenu() -> Handle (API_MENU_HMENU);
HMENU hSubMenu = GetSubMenu (hMenu, TOOLMAINPOPUP);

	hSubMenu = GetSubMenu (hSubMenu, TOOLPOPUP);	// ToolMenu besorgen
	AppendMenu (hSubMenu, MF_STRING, IDM_ARROW+iToolID, pIT -> pDesc);
	DrawMenuBar (Handle (API_WINDOW_HWND));
	
return iToolID;
}


bool ExtDirisWindow::RemoveTool (short iToolID)
{
// im Werkzeugfenster entfernen
bool fResult = false;

	if (pToolBox) {
		fResult = pToolBox -> RemoveTool (iToolID);
		TX_ASSERT(fResult);
	
	// im Menu rausnehmen
		if (fResult) {
		HMENU hMenu = MainMenu() -> Handle (API_MENU_HMENU);

			DeleteMenu (hMenu, IDM_ARROW+iToolID, MF_BYCOMMAND);
			DrawMenuBar (Handle (API_WINDOW_HWND));
		}
	}

return fResult;
}
#else
// nur der Kompatibilität zur Liebe ...
short ExtDirisWindow::InstallTool (INSTALLTOOL *pIT)
{
	return -1;
}

bool ExtDirisWindow::RemoveTool (short iToolID)
{
	return false;
}
#endif // OLDTOOLBOX

// Funktion, die das Fenster anzeigt bzw. ausblendet --------------------------
void ExtDirisWindow::Show (ShowState s)
{
	if (s == HideWindow) {
		if (m_fIsShown) {
			ShowORWindows(s);
			Hide();
			m_fIsShown = false;
		}
		return;
	}

// soll angezeigt werden
	m_fIsShown = true;
	Window::Show (s);		// weiterreichen
	ShowORWindows(s);
}

void ExtDirisWindow::Expose (ExposeEvt e)
{
	if (FIsShown() && NULL != m_pView) 	// nur wenn angezeigt, dann zeichnen
		m_pView -> RePaint();
}


// Dragging einer Datei auf das TriasFenster ist erfolgt ----------------------
bool IrisWind::DragFunc (WPARAM wParam)
{
#if defined(_OLD_DRAGNDROP)
WORD cFiles = DragQueryFile ((HDROP)wParam, UINT_MAX, NULL, 0);
char *pPath = new char [_MAX_PATH];
ResString StbExt (IDS_REGSTBEXTENSION, 6);
ResString RisExt (IDS_REGRISEXTENSION, 6);
char pExt[_MAX_EXT];

	if (pPath == NULL) return false;
	for (WORD i = 0; i < cFiles; i++) {
		DragQueryFile ((HDROP)wParam, i, pPath, _MAX_PATH);
		strlwr (pPath);
		_splitpath (pPath, NULL, NULL, NULL, pExt);
		if (strcmp (pExt, StbExt) && strcmp (pExt, RisExt))
			continue;

	// Projekt öffnen
	TRIAS_OPEN TO;
	char *pUser = new char [_MAX_FNAME];

		_splitpath (pPath, NULL, NULL, pUser, NULL);
		TO.dwSize = sizeof (TRIAS_OPEN);
		TO.lpProject = pPath;
		TO.lpUser = pUser;
		TO.lpPassWord = NULL;
		TO.iMode = OM_Normal;
		DEX_OpenProject (TO);	// Projekt eröffnen

		DELETE (pUser);
		break;			// nur das erste Projekt
	}
	DragFinish ((HDROP)wParam);
	DELETE (pPath);
#endif // _OLD_DRAGNDROP

return true;
}


// Initialisierung des Sprungverteilers für die externen Messages -------------

#include "extfcns.tab"		// Sprungverteiler-Template	(DEX_...)
#include "extfcnsn.tab"		// Sprungverteiler-Template	(DEXN_...)

bool ExtDirisWindow::FInitDexProcs (void)
{
// allgemeine Initialisierungen
	m_cbDexProcs = NULL;		// Sprungverteiler
	m_i1stDexProc = 0;			// erste Funktion
	m_iDexProcsNum = 0;			// Anzahl der Funktionen in Tabelle
#if defined(_DEBUG)
	m_pDumpInfos = NULL;		// Liste der MessageDumpInfos
#endif // _DEBUG

// größten und kleinsten MessageID suchen
unsigned int iFirst = UINT_MAX;
unsigned int iLast = 0;
const DEXMESSAGE_ENTRY *pDME = DexMessageEntries;

	for (short i = 0; i < DEXMESSAGE_ENTRYNUM; i++, pDME++) {
	UINT uiMsg = pDME -> m_uiMsg;
	
		if (iFirst > uiMsg) iFirst = uiMsg;
		if (iLast < uiMsg) iLast = uiMsg;
	}
	if (iFirst == USHRT_MAX || iLast == 0)
		return false;
	
	m_iDexProcsNum = iLast-iFirst+1;
	m_i1stDexProc = iFirst;

	TX_ASSERT(m_iDexProcsNum >= 1);
					
// Tabelle anlegen und initialisieren
	try {
		m_cbDexProcs = new DEXMESSAGE_PROC [m_iDexProcsNum];
		for (unsigned short j = 0; j < m_iDexProcsNum; j++) 
			 m_cbDexProcs[j] = ExtDirisWindow::OnNotDefinedMessage;

#if defined(_DEBUG)
		if (TRACE_NOTRACE < g_dwTraceLevel) {
			m_pDumpInfos = new DEXMSGDUMP_INFO [m_iDexProcsNum];
			for (unsigned short jj = 0; jj < m_iDexProcsNum; jj++) {
				m_pDumpInfos[jj].m_pcMsgName = NULL;
				m_pDumpInfos[jj].m_pDumpProc = ExtDirisWindow::DefaultMsgDumper;
				m_pDumpInfos[jj].m_iTraceLevel = TRACE_NOTRACE;
			}
		}
#endif // _DEBUG
	} catch (bad_alloc) {
		return false;
	}

// Funktionen eintragen
	pDME = DexMessageEntries;
	for (i = 0; i < DEXMESSAGE_ENTRYNUM; i++, pDME++) {
	// erste Zuweisung ?
		TX_ASSERT(ExtDirisWindow::OnNotDefinedMessage == m_cbDexProcs[(pDME -> m_uiMsg) - iFirst]);
		m_cbDexProcs[(pDME -> m_uiMsg) - iFirst] = pDME -> m_pProc;

#if defined(_DEBUG)
	// evtl. TraceStrukturen füllen
		if (TRACE_NOTRACE < g_dwTraceLevel) {
			TX_ASSERT(NULL == m_pDumpInfos[(pDME -> m_uiMsg) - iFirst].m_pcMsgName);
			m_pDumpInfos[(pDME -> m_uiMsg) - iFirst].m_pcMsgName = pDME -> m_pcMsgName;
			m_pDumpInfos[(pDME -> m_uiMsg) - iFirst].m_iTraceLevel = pDME -> m_iTraceLevel;
			if (NULL != pDME -> m_pDumpProc)
				m_pDumpInfos[(pDME -> m_uiMsg) - iFirst].m_pDumpProc = pDME -> m_pDumpProc;
		}
#endif // _DEBUG
	}

return true;
}

// Sprungverteiler für Notifications initialisieren ---------------------------
bool ExtDirisWindow::FInitDexProcsNfy (void)
{
// allgemeine Initialisierungen
	m_cbDexProcsNfy = NULL;		// Sprungverteiler
	m_i1stDexProcNfy = 0;		// erste Funktion
	m_iDexProcsNumNfy = 0;		// Anzahl der Funktionen in Tabelle

// größten und kleinsten MessageID suchen
unsigned int iFirst = UINT_MAX;
unsigned int iLast = 0;
const DEXNOTIFY_ENTRY *pDME = DexMessageEntriesNfy;

	for (short i = 0; i < DEXMESSAGE_ENTRYNUM_NFY; i++, pDME++) {
	UINT uiMsg = pDME -> m_uiMsg;
	
		if (iFirst > uiMsg) iFirst = uiMsg;
		if (iLast < uiMsg) iLast = uiMsg;
	}
	if (iFirst == USHRT_MAX || iLast == 0)
		return false;
	
	m_iDexProcsNumNfy = iLast-iFirst+1;
	m_i1stDexProcNfy = iFirst;

	TX_ASSERT(m_iDexProcsNumNfy >= 1);
					
// Tabelle anlegen und initialisieren
	m_cbDexProcsNfy = new DEXMESSAGE_PROC [m_iDexProcsNumNfy];
	if (m_cbDexProcsNfy == NULL) return false;

	for (unsigned short j = 0; j < m_iDexProcsNumNfy; j++) 
		 m_cbDexProcsNfy[j] = ExtDirisWindow::OnNotUsedNotification;
	
// Funktionen eintragen
	pDME = DexMessageEntriesNfy;
	for (i = 0; i < DEXMESSAGE_ENTRYNUM_NFY; i++, pDME++) {
	// erste Zuweisung ?
		TX_ASSERT(ExtDirisWindow::OnNotUsedNotification == m_cbDexProcsNfy[(pDME -> m_uiMsg) - iFirst]);
		m_cbDexProcsNfy[(pDME -> m_uiMsg) - iFirst] = pDME -> m_pProc;
	}

return true;
}

///////////////////////////////////////////////////////////////////////////////
//
extern "C" {

typedef struct tagFILLONRENUMEX {
	IEnum<LONG> *m_pEnum;
	DWORD m_dwTypes;
} FILLONRENUMEX;

bool EXPORTTRIAS WINAPI FillONrEnumEx (long lONr, DWORD dwType, void *pData)
{
FILLONRENUMEX *pFOE = (FILLONRENUMEX *)pData;

	if (dwType & pFOE -> m_dwTypes)		// dieser ObjektTyp ist gefragt
		return SUCCEEDED(pFOE -> m_pEnum -> AddItem (lONr));

return true;	// ansonsten weitermachen
}

} // extern "C"

// Enumerator typrichtig mit allen Objekten des Idents/ObjTyps füllen ---------
static bool AddObjectsToEnum (IEnum<LONG> *pEnum, long lIdent, short iOTyp)
{
ENUMLONGKEYEX ELK;
FILLONRENUMEX FOE;

	FOE.m_pEnum = pEnum;
	FOE.m_dwTypes = (DWORD)iOTyp;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)FillONrEnumEx;
	ELK.ePtr = &FOE;
	ELK.eData = (DWORD)iOTyp;

return DEX_EnumIdentObjectsEx (ELK);
}

bool ExtDirisWindow::GenObjectProperties (void)
{
CSelectIdentDlg *pDlg = CSelectIdentDlg::CreateInstance (this, 
				IDD_OBJPROPIDENTDLG, IDL_OBJPROPIDENTSLIST);

	if (pDlg == NULL) return false;

	pDlg -> Show (Centre);
	if (pDlg -> Result()) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);
	long lIdent = -1L;
	short iOTyp = 0;
	WEnumLONG Enum;
	HRESULT hr = CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER,
								   IID_IEnumLONG, Enum.ppv());
		
		if (FAILED(hr)) return false;
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
				if (!AddObjectsToEnum (Enum, lIdent, iOTyp))
					break;
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));
		}

		{
		ObjectPropertyDlg OPDlg (this, m_pEL, Enum);

			Wait.Hide();
			OPDlg.Show (Centre);
		}
	}
	DELETE (pDlg);

return true;
}

bool ExtDirisWindow::EnterRechResults (void)
{
WEnumObjProps EnumObj;
long lIdent = -1L;
short iOTyp = 0;
CRechResultDlg *pRRDlg = NULL;

	{
	CEierUhr Wait (this);

		try {
		WObjectProps IOP((ITriasXtensionSite *)m_pEL);		// throws HRESULT

			if (m_fMustInitOPFs) {
				IOP -> OnNewReferenceObject(-1L);
				if (SUCCEEDED(IOP -> OnNewReferenceObject(0L))) 	// alle OPF's anzeigen
					m_fMustInitOPFs = false;
			}
			if (!m_fMustInitOPFs)
				IOP -> EnumObjectProps (EnumObj.ppi());
		} catch (_com_error&) {
			m_fMustInitOPFs = true;
			return false;
		}

		pRRDlg = CRechResultDlg::CreateInstance (this, DBO(), EnumObj);
		if (NULL == pRRDlg) return false;

	// voreinstellen des aktuellen Zustandes
	CTable t(DBO().Idents().IdentTree());

		for (t.First(); t.Valid(); t.Next()) {
		CIdentifikatorLock l(t);
		CIdentifikator *pId = (CIdentifikator *)l;

			TX_ASSERT (NULL != pId);
			if (!pId -> toPaint())
				continue;	// gehört nicht zur Ansicht

			pRRDlg -> SelectIdents (pId -> Id(), pId -> GetSearchAble());
		}

	} // WaitCursor

string actProp = m_pEL -> GetActOProp();

	pRRDlg -> SetActOProp (actProp.c_str());
	pRRDlg -> SetHideFlags (g_iHideFlags);

// jetzt Dialog anzeigen
	pRRDlg -> Show (Centre);
	if (pRRDlg -> Result()) {
	CEierUhr Wait (this);
	
	// Hide&SortFlags merken
	short iHideFlags = pRRDlg -> GetHideFlags();

		if (g_iHideFlags != iHideFlags) {
			g_iHideFlags = iHideFlags;
			DEX_SetDirtyGeoDB (true);
		}

	string newProp = pRRDlg -> GetActOProp();

		if (actProp != newProp) {
			m_pEL -> SetActObjProp (newProp.c_str());
			DEX_SetDirtyGeoDB (true);
		}
		
	// alle Identifikatoren auswerten
	CTable t(DBO().Idents().IdentTree());

		for (t.First(); t.Valid(); t.Next()) {
		CIdentifikatorLock l(t);
		
			TX_ASSERT (NULL != (CIdentifikator *)l);
			l -> SetSearchAble (0);	// für alle löschen
		}
		if (pRRDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
				if (t.Find(&lIdent)) {
				CIdentifikatorLock l(t);
				
					TX_ASSERT (NULL != (CIdentifikator *)l);
					l -> SetSearchAble (iOTyp);
				}
			} while (pRRDlg -> GetNextIdent (lIdent, iOTyp));
		}
	}
	delete pRRDlg;

return true;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige MRU-Befehle
void ExtDirisWindow::AddNewItem (bool fStartUp, LPCSTR pcStr, bool fRO)
{
	if (NULL != m_pMRU) {
		::AddNewItem (m_pMRU, pcStr, fRO);
		if (fStartUp)
			::PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(IrisMenu.Handle(), 0), IDM_EXIT);
		else
			::PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(StartMenu.Handle(), 0), IDM_EXIT);

	// zurückschreiben des neuen Zustandes (für Andreas)
		SaveMruInReg (m_pMRU, g_cbRegOpenMRU);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Reposition aller ChildFenster

// Reposition a window
void WINAPI RepositionWindow (SIZEPARENTPARAMS* lpLayout,
	HWND hWnd, LPCRECT lpRect)
{
	TX_ASSERT(hWnd != NULL);
	TX_ASSERT(lpRect != NULL);

HWND hWndParent = ::GetParent(hWnd);

	TX_ASSERT(hWndParent != NULL);

	if (lpLayout != NULL && lpLayout->hDWP == NULL)
		return;

// first check if the new rectangle is the same as the current
RECT rectOld;

	::GetWindowRect(hWnd, &rectOld);
	::ScreenToClient(hWndParent, (POINT *)&rectOld.left);
	::ScreenToClient(hWndParent, (POINT *)&rectOld.right);
	
	if (::EqualRect(&rectOld, lpRect))
		return;     // nothing to do

// try to use DeferWindowPos for speed, otherwise use SetWindowPos
	if (lpLayout != NULL) {
		lpLayout->hDWP = ::DeferWindowPos (lpLayout->hDWP, hWnd, NULL,
			lpRect->left, lpRect->top,  lpRect->right - lpRect->left,
			lpRect->bottom - lpRect->top, SWP_NOACTIVATE|SWP_NOZORDER);
	} else {
		::SetWindowPos(hWnd, NULL, lpRect->left, lpRect->top,
			lpRect->right - lpRect->left, lpRect->bottom - lpRect->top,
			SWP_NOACTIVATE|SWP_NOZORDER);
	}
}

/////////////////////////////////////////////////////////////////////////////
// minimal layout support
void ExtDirisWindow::RepositionBars (
	UINT nIDFirst, UINT nIDLast, UINT nIDLeftOver,
	UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, BOOL bStretch)
{
	TX_ASSERT(nFlags == 0 || nFlags == reposQuery || nFlags == reposExtra);

// walk kids in order, control bars get the resize notification
// which allow them to shrink the client area
// remaining size goes to the 'nIDLeftOver' pane
// NOTE: nIDFirst->nIDLast are usually 0->0xffff
SIZEPARENTPARAMS layout;
HWND hWndLeftOver = NULL;
HWND hWnd = Handle(API_WINDOW_HWND);

	layout.bStretch = bStretch;
	layout.sizeTotal.cx = layout.sizeTotal.cy = 0;
	if (lpRectClient != NULL)
		layout.rect = *lpRectClient;    // starting rect comes from parameter
	else
		::GetClientRect (hWnd, &layout.rect);    // starting rect comes from client rect

	if (nFlags != reposQuery)
		layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
	else
		layout.hDWP = NULL; // not actually doing layout

		for (HWND hWndChild = ::GetTopWindow(hWnd); hWndChild != NULL;
		 hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
	{
	UINT nIDC = ::GetDlgCtrlID (hWndChild);

		if (nIDC == nIDLeftOver)
			hWndLeftOver = hWndChild;
		else if (nIDC >= nIDFirst && nIDC <= nIDLast)
			::SendMessage (hWndChild, WM_SIZEPARENT, 0, (LPARAM)&layout);
	}

// if just getting the available rectangle, return it now...
	if (nFlags == reposQuery) {
		TX_ASSERT(lpRectParam != NULL);

		if (bStretch)
			::CopyRect(lpRectParam, &layout.rect);
		else {
			lpRectParam->left = lpRectParam->top = 0;
			lpRectParam->right = layout.sizeTotal.cx;
			lpRectParam->bottom = layout.sizeTotal.cy;
		}
		return;
	}

// the rest is the client size of the left-over pane
	if (nIDLeftOver != 0 && hWndLeftOver != NULL) {
	// allow extra space as specified by lpRectBorder
		if (nFlags == reposExtra) {
			TX_ASSERT(lpRectParam != NULL);

			layout.rect.left += lpRectParam->left;
			layout.rect.top += lpRectParam->top;
			layout.rect.right -= lpRectParam->right;
			layout.rect.bottom -= lpRectParam->bottom;
		}

	// reposition the window
//	CWnd* pLeftOver = CWnd::FromHandle(hWndLeftOver);

//		pLeftOver->CalcWindowRect(&layout.rect);
		RepositionWindow(&layout, hWndLeftOver, &layout.rect);
	}

// move and resize all the windows at once!
	if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
		TX_TRACE0("Warning: DeferWindowPos failed - low system resources.\n");
}

///////////////////////////////////////////////////////////////////////////////
// PreTranslateMsgProc
/*
bool App_PreTranslateMessage (MSG *pMsg)
{
OwnerDrawListBoxEx *pW = (OwnerDrawListBoxEx *)CurrActDirisW->GetORListBox (pMsg->hwnd);

	if (NULL != pW && pW -> PreTranslateMsg (pMsg))
		return true;	// bearbeitet

	TX_ASSERT(NULL != g_pPreTransMsgProcChain);
	return g_pPreTransMsgProcChain (pMsg);		// weiterreichen
}
*/
