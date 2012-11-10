// EventHandler für FrameWindow -----------------------------------------------
// File: FRAMEEVT.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <shellapi.h>
#include <xtensnxx.h>
#include <funcs03.h>
#include <fnamestr.h>
#include <ScopeVar.h>

#undef NAKEDEVT

#include "menuitem.hxx"

#include <registry.hxx>

#include <dirisole.h>
#include <xtsnguid.h>
#include <undoguid.h>
#include <iunredo.hxx>
#include <undohelp.hxx>
#include <oprpguid.h>

#include <istatus.h>
#include <statguid.h>
#include <olectl.h>

#include "strings.h"

#include "extmain3.hxx"
#include "extqnfy2.hxx"
#if defined(OLD_TOOLBOX)
#include "tools.hxx"
#endif // OLD_TOOLBOX
#include "opendb.hxx"
#include "bildobj.hxx"
#include "SignOnDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern HelpDisplay *IrisHD;
extern bool wasHelpEvt;
extern bool g_fPendingSave;				// Speichern muß gemacht werden

extern char cbDefaultDir[_MAX_PATH+1];	// StandardWurzelVerzeichnis der Projekte

extern HINSTANCE hInstance;				// Handle dieser Programminstanz

extern short g_iMinutes;				// TimerTicks zählen
extern short g_iTicks;
extern short g_iSignOnTicks;

extern CSignOnDlg *g_pSODlg;			// SignOnDlg

///////////////////////////////////////////////////////////////////////////////
// EventHandler
//
// EventHandler für den Fall, daß das Fenster vom Nutzer verschoben wird
void ExtDirisWindow::Move (MoveEvt e)		// neuen FensterUrsprung merken
{	
	if (!isIconic())
		MOrig = e.NewOrigin();
//	RepositionBars (0, 0xffff, ID_TRIASVIEW_GEODB);
}

// EventHandler für den Fall, daß Fenstergröße vom Nutzer verändert wird ------
void ExtDirisWindow::ReSize (ReSizeEvt e) 
{
	if (!isIconic())
		MSize = e.GetNewSize();		// neue FensterGröße merken
//	RepositionBars (0, 0xffff, ID_TRIASVIEW_GEODB);
}

// Key-Events - direkt an evtl. exitierende View weiterleiten -----------------
void ExtDirisWindow::KeyDown (KeyEvt e)
{
	DELETE_OBJ (g_pSODlg);		// evtl. SignOn ausblenden
	if (m_pView) m_pView -> KeyDown(e);
}

void ExtDirisWindow::KeyUp (KeyEvt e)
{
	DELETE_OBJ (g_pSODlg);		// evtl. SignOn ausblenden
	if (m_pView) m_pView -> KeyUp(e);
}

// MouseEvt abfangen ----------------------------------------------------------
void ExtDirisWindow::MouseButtonDn (MouseEvt e) 
{
	DELETE_OBJ (g_pSODlg);		// evtl. SignOn ausblenden
}

// TimerEvts auswerten --------------------------------------------------------
void ExtDirisWindow::Strobe (StrobeEvt e)
{
	switch (e.GetStrobeID()) { 	// TimerEvent kommt jede Minute, FlushDB auslösen
	case TIMER_HALFSECOND:	
		{
		// SignOn nach spätestens 5 Sekunden ausblenden
			if (g_iSignOnTicks == 10) {
				DELETE_OBJ (g_pSODlg);
			} else if (g_iSignOnTicks < 10)
				g_iSignOnTicks++;
		}
		break;

	case TIMER_MINUTE:
		if (0 < g_iMinutes) {	
		// nur, wenn wirklich was sinnvolles eingestellt ist
			if ((g_iTicks++/10) < g_iMinutes)
				break;
			g_iTicks = 0;
			if (IsValidActiveView() && !DBO().GetTempMode() && !DBO().GetROMode()) {
			// Speichern, nur, wenn nicht das erste mal und kein Schreibschutz
				g_fPendingSave = true;
			}
		}
		break;

	default:
		break;
	}

// an ViewFenster schicken (blinken etc.)
	if (m_pView) m_pView -> Strobe(e);
}

// MenuBefehl wurde ausgelöst -------------------------------------------------
void ExtDirisWindow::MenuCommand (MenuCommandEvt e) 
{
// evtl. SignOn ausblenden
	DELETE_OBJ (g_pSODlg);

// MenuEvents aus NutzerMenu herausfiltern
	if (m_pEL -> DispatchMenuCommand(e))
		return;

	if (wasHelpEvt) {
	// wenn zu diesem Item Hilfe gerufen wird, dann Menupunkt nicht
	// bearbeiten
		wasHelpEvt = false;
		return;
	}

// MenuEvents für ExtDirisWindow herausfiltern 
	BEGIN_COMMANDS(e.GetItemID()) 
		ON_COMMAND_ID(IDM_LOADEXTENSION, doLoadExtension);	// eine Extension laden/freigeben
		ON_COMMAND_ID(IDM_LOADEXTENSION_CUST, doLoadExtensionCust);	// Customize Page anzeigen
//		ON_COMMAND_ID(IDM_SAVEOPT, doSaveOpt);				// SpeicherOptionen auswählen
		ON_COMMAND(IDM_NEWDB, doCreateNewGeoDB, e);			// neue GeoDB anlegen (dbinit)
		ON_COMMAND_ID(IDM_OPEN, doOpenDocument);			// existierende GeoDB eröffnen
		ON_COMMAND_ID(IDM_CLOSE, doCloseDocument);			// aktuelle GeoDB schließen
		ON_COMMAND_ID(IDM_ABOUT, doAbout);					// AbouFenster anzeigen
		ON_COMMAND_ID(IDM_IMPORT, doImport);				// Import von Daten aus anderen Formaten
		ON_COMMAND_ID(IDM_UNDO, doUndo);					// Undo/Redo bearbeiten
		ON_COMMAND_ID(IDM_REDO, doRedo);
		ON_COMMAND_ID(IDM_OBJPROPERTIES, GenObjectProperties);
		ON_COMMAND_ID(IDM_RECHRESULTS, EnterRechResults);	// Anzuzeigende RechercheErgebnisse auswählen
		ON_COMMAND_ID(IDM_LOADOBJECTCOLLECTION, doLoadObjColl);	// Objektmenge laden
		ON_COMMAND(IDM_EXIT, doExit, e);					// Programm beenden

	// HilfeKommandos
		ON_COMMAND_ID(IDM_HELP, doHelpID);					// HilfeMenu
		ON_COMMAND_ID(IDM_INDEX, doHelpIndex);
		ON_COMMAND(IDM_MOUSE, doHelpMenu, e);
		ON_COMMAND(IDM_GLOSSAR, doHelpMenu, e);
		ON_COMMAND(IDM_KEYBOARD, doHelpMenu, e);

		DEFAULT_COMMANDS(doDefault, e);
	END_COMMANDS;
}

///////////////////////////////////////////////////////////////////////////////
// MenuBefehle
//
// Erzeugen eines neuen Dokumentes --------------------------------------------
bool ExtDirisWindow::doCreateNewGeoDB (MenuCommandEvt e)
{
#if defined(_USE_LEGACY_CODE)
int rgMode = e.LParam() ? OM_16BitCompatible : 0;
CREATEVIEW_RESULT rgRes = CreateView (NULL, NULL, NULL, rgMode);

	if (CREATEVIEW_RESULT_FAILED != rgRes) {
		m_fMustInitOPFs = true;
		if (!(CREATEVIEW_RESULT_NOREPAINT & rgRes))
			RePaint();
		return true;
	}
#endif // defined(_USE_LEGACY_CODE)
	return false;
}

// alte DB öffnen -------------------------------------------------------------
bool ExtDirisWindow::doOpenOld (MenuCommandEvt e)
{
#if defined(_USE_LEGACY_CODE)
CREATEVIEW_RESULT rgRes = CREATEVIEW_RESULT_FAILED;

	if (m_fHandleMRU) {
	CEierUhr Wait (this, CursorPath(g_cbCursorLoad));	// EierUhr anzeigen
	BOOL fRO = false;
	ErrCode EC = EC_NOOPEN;
	UINT uiMenuItem = e.GetItemID();
	string strF;

		if (::GetMenuItem (m_pMRU, uiMenuItem, true, strF, fRO)) {
		// nur wenn wirklich was sinnvolles im Menu steht
		char cbBuffer[_MAX_PATH];

			strcpy (cbBuffer, get_name(strF).c_str());
			strlwr (cbBuffer);

		string strUser (cbBuffer);

			rgRes = CreateView (strF.c_str(), 
					(char *)strUser.c_str(), NULL, 
					fRO ? OM_RO|OM_ActivateDBO : OM_Normal|OM_ActivateDBO);
			if (CREATEVIEW_RESULT_FAILED == rgRes)
			{
			// diesen Eintrag erstmal aus StartMenu rausnehmen
				DelMenuItem (uiMenuItem, true);
				return false;
			}
		} else {
			MessageBeep (MB_ICONEXCLAMATION);	// nicht existierender MenuPunkt
			TX_ASSERT(false/*!GetMRUMenuItem()*/);
			return false;
		}
	} else
		return false;

	m_fMustInitOPFs = true;
	if (!(CREATEVIEW_RESULT_NOREPAINT & rgRes))
		RePaint();

	return true;
#else
	return false;
#endif // defined(_USE_LEGACY_CODE)
}

// Eröffnen eines anderen Dokumentes ------------------------------------------
bool ExtDirisWindow::doOpenDocument (void)
{
#if defined(_USE_LEGACY_CODE)
COpenDBDlg ODlg (this, FakeTRiASName(IDS_DBOPENTEMPLATE, g_cbTRiAS, g_cbTRiAS).c_str());		// Dialogfenster Anzeigen
string strInitDir = cbDefaultDir;
ResString resCap (IDS_OPENPROJECTCAP, 64);

	ODlg.SetCaption (resCap);

// evtl. letztes OpenVerzeichnis aus Registry lesen
// einlesen sonstiger RegistryInfos
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser regCfg (g_cbRegOpenMRU);
	char cbBuffer[_MAX_PATH];
	DWORD dwLen = sizeof(cbBuffer);

		if (regCfg.GetSubSZ (g_cbLastOpenDir, cbBuffer, dwLen))
			strInitDir = cbBuffer;
	}

	ODlg.SetInitialDir (strInitDir.c_str());
	ODlg.Show();

CREATEVIEW_RESULT rgRes = CREATEVIEW_RESULT_FAILED;

	if (ODlg.Result ()) {	// Resultate verarbeiten
	CEierUhr Wait (this, CursorPath(g_cbCursorLoad));	// EierUhr anzeigen
	char lDBName[_MAX_PATH+1];

	// LastOpenDir speichern
		ODlg.GetFileSpec (lDBName, _MAX_PATH+1);

#if defined(ENABLE_WIN32S_CODE)
		if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
		{
		CCurrentUser regCfg (g_cbRegOpenMRU);
		string strName (lDBName);
		string strPath (get_drive(strName) + get_path(strName)); 

			regCfg.SetSubSZ (g_cbLastOpenDir, strPath.c_str());
		}

	// DB eröffnen
		rgRes = CreateView (lDBName, ODlg.GetUserName(), ODlg.GetPassWord(),	
			 ODlg.GetROMode() ? OM_RO|OM_ActivateDBO : OM_Normal|OM_ActivateDBO);
		if (CREATEVIEW_RESULT_FAILED == rgRes)
		{
			return false;
		}
	}

	m_fMustInitOPFs = true;
	if (!(CREATEVIEW_RESULT_NOREPAINT & rgRes))
		RePaint ();		// neue DB zeichnen

	return true;
#else
	return false;
#endif // defined(_USE_LEGACY_CODE)
}

bool ExtDirisWindow::doCloseDocument (void)
{
	return DEX_CloseProject (HACTPROJECT);
}

bool ExtDirisWindow::doCloseDocumentNow (void)
{
	if (m_pView) {		// doppeltes Abarbeiten verhindern
	CScopeVar<bool> fClosing (m_fClosingDocument, true);

		if (bool(fClosing)) {
			if (!m_pView -> CloseDocument()) 
				return false;		// wenn nicht geschlossen wurde, dann weiter
			DELETE_OBJ(m_pView);
			RestoreStartConfig();
		}
	}
	return true;
}

void ExtDirisWindow::RestoreStartConfig(void)
{
	DEX_SetActObjPropName(g_cbNil);

	TX_ASSERT(NULL != m_pEL);
	m_pEL -> ResetObjProps(true);	// Liste der Objekteigenschaften freigeben
	m_pEL -> ResetClsProps();

	ReReadCaption();
	InitMenues();
	UnLoadLocalExtensions();
	m_pUndoRedo -> EveryDelete();
}

///////////////////////////////////////////////////////////////////////////////
bool ExtDirisWindow::doUndo (void)
{
	if (GetKeyState (VK_CONTROL) >= 0) {
	CEierUhr Wait (this);
	DWORD dwCaps = m_pUndoRedo -> GetNextUndoDesc (NULL);

		m_pUndoRedo -> Undo();
		if (dwCaps & UNDOREDOCAPS_REPAINT)
			DEX_RePaint();
	} else 
		ShowUndoList();

	return true;
}

bool ExtDirisWindow::doRedo (void)
{
	if (GetKeyState (VK_CONTROL) >= 0) {
	CEierUhr Wait (this);
	DWORD dwCaps = m_pUndoRedo -> GetNextRedoDesc (NULL);

		m_pUndoRedo -> Redo();
		if (dwCaps & UNDOREDOCAPS_REPAINT)
			DEX_RePaint();
	} else
		ShowRedoList();

	return true;
}

bool ExtDirisWindow::doExit (MenuCommandEvt e)
{
Event eQuit;

	eQuit.Msg() = WM_CLOSE;
	eQuit.WParam() = 0L;
	eQuit.LParam() = 0L;
	PostEvent (eQuit);
	return true;
}

// AboutBox anzeigen ----------------------------------------------------------
bool ExtDirisWindow::doAbout (void)
{
CSignOnDlg *pAbout = CSignOnDlg::CreateInstance (this, hInstance, true);

	if (pAbout) {
		pAbout -> Show (Centre);
		delete pAbout;
		return true;
	}
	return false;
}

// HilfeMenu -------------------------------------------------------------------
bool ExtDirisWindow::doHelpMenu (MenuCommandEvt e)
{
	if (IrisHD) 
		IrisHD -> Show (e.GetItemID());

	return true;
}

bool ExtDirisWindow::doHelpIndex (void)
{
	if (IrisHD) 
		IrisHD -> Show ("HelpIndex");

	return true;
}

bool ExtDirisWindow::doHelpID (void)
{
	if (IrisHD) 
		IrisHD -> Show ("HelpOnHelp");
	return true;
}

// sonstige Kommandos ausführen -----------------------------------------------
bool ExtDirisWindow::doDefault (MenuCommandEvt e)
{
uint iItemID = e.GetItemID();

	if (iItemID > IDMRU && iItemID <= IDMRU+9)
		return doOpenOld (e);

// nichts gefunden, also weiterleiten
	if (m_pView) {
		m_pView -> MenuCommand (e);
		return true;
	}
	return false;
}

