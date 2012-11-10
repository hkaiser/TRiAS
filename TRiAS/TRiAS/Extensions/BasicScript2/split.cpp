// split.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#include <new>

#include <iobjman.h>
#include <afxpriv.h>
#include <registrx.hxx>

#include "macrguid.h"

#include "iscrprop.h"

#include "tmplman.h"
#include "mru.h"
#include "projscr.h"
#include "dummypar.h"
#include "strinfo.h"
#include "conststr.h"
#include "toolbarx.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "runerr.h"
#include "runebobs.h"
#include "DebCtrl.h"
#include "spltree.h"
#include "splitter.h"
#include "split.h"
#include "addfdlg.h"
#include "debfdlg.h"
#include "dbfrmvw.h"
#include "DbFrmVw2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Smarts
DefineSmartInterface(TreeItem);
DefineSmartInterface(StreamInfo);
DefineSmartInterface(ObjManHelper);
DefineSmartInterface(Persist);
DefineSmartInterface(BSProperty);
DefineSmartInterface(ExportImportProject);

//////////////////////////////////////////////////////////////////////////////
// globale Funktionen
CString GetDefaultName(int IDS);
CString GetDefaultScript();

CString GetFileName (CString &rPath, BOOL fExt);
CString GetPathName (LPCSTR pcPath);
BOOL	IsRemoteDir(LPCSTR cbPath);
BOOL	ReadRegSettingsLastOpenFile(char *pc, DWORD dwL);
BOOL	SaveRegSettingsLastOpenFile (LPCSTR pc);
HRESULT MessageNew(HWND hWnd);
HRESULT MessageNoText(HWND hWnd, LPCSTR lpcstr);
HRESULT MessageLink(HWND hWnd);

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

////////////////////////////////////////////////////////////////////////////
// Toolbar ComboBox
static UINT BASED_CODE TBProject[] =
{
	ID_DEBUG_NEWFILE,           
	ID_DEBUG_OPEN,           
	ID_DEBUG_SAVE,
	ID_SEPARATOR,
	ID_DEBUG_CUT,
	ID_DEBUG_COPY,
	ID_DEBUG_PASTE,
	ID_SEPARATOR,
	ID_DEBUG_UNDO,
};

//////////////////////////////////////////////////////////////////////////////
// TOOLBAR
static UINT BASED_CODE buttons[] =
{	// same order as in the bitmap 'toolbar.bmp'
	ID_DEBUG_GO,
	ID_DEBUG_PAUSE,
	ID_DEBUG_SUSPEND,
	ID_SEPARATOR,	
	ID_DEBUG_TRACEIN,
	ID_DEBUG_TRACEOVER,
	ID_SEPARATOR,	
	ID_DEBUG_BREAKPOINT,
	ID_SEPARATOR,	
	ID_DEBUG_ADDWATCH,
	ID_SEPARATOR,	
	ID_DEBUG_CALLSTACK,
};

/////////////////////////////////////////////////////////////////////////////
// Stausbar
static UINT BASED_CODE indicators[] =
{
	ID_STATUSBAR_PANE1,	// Textbereich
	ID_STATUSBAR_PANE2,	// x-Achsenwert
	ID_STATUSBAR_PANE3,	// Wert an sich
	ID_STATUSBAR_PANE4,	// y-Achsenwert
	ID_STATUSBAR_PANE5,	// Wert an sich
};

/////////////////////////////////////////////////////////////////////////////
// CSplit

IMPLEMENT_DYNCREATE(CSplit,  CFrameWnd)

CSplit::CSplit()
{
	m_pISelItem = NULL;
	m_pILoadedItem = NULL;
	m_iFocus = 0;
	m_ID_TIMER = 10000;
	m_fInit = false;
	m_uiMruID = 0;		// MenuID
	m_pMRUMenu = NULL;
	m_uiWMClose = WM_CLOSEDEBUGGERDIALOG;
	m_strStartScript.Empty();
	m_uiStartManID = 0;
}

CSplit::~CSplit()
{
	ResetItems();
}

void CSplit::ResetItems()
{
	if (m_pISelItem) m_pISelItem -> Release();
	m_pISelItem = NULL;
	if (GetInitNew()) {
		try {// muss  auch aus ObjectListen geschmissen werden
			WObjManHelper IOMH = m_pILoadedItem;
			IOMH -> Delete();
		} catch (_com_error&) {
		}
	} else {
		if (m_pILoadedItem) m_pILoadedItem -> Release();
	}
	m_pILoadedItem = NULL;
}

BEGIN_MESSAGE_MAP(CSplit,  CFrameWnd)
	//{{AFX_MSG_MAP(CSplit)
	ON_WM_INITMENUPOPUP()
	ON_WM_INITMENU()
	ON_WM_MENUSELECT()	
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_CLOSE, OnExit)
	ON_COMMAND(ID_DEBUG_NEWFILE, OnDebugNewFile)
	ON_COMMAND(ID_DEBUG_CUT, OnDebugCut)
	ON_COMMAND(ID_DEBUG_COPY, OnDebugCopy)
	ON_COMMAND(ID_DEBUG_BREAKPOINT, OnDebugBreakpoint)
	ON_COMMAND(ID_DEBUG_CALLSTACK, OnDebugCallstack)
	ON_COMMAND(ID_DEBUG_DELETE, OnDebugDelete)
	ON_COMMAND(ID_DEBUG_ADDWATCH, OnDebugAddwatch)
	ON_COMMAND(ID_DEBUG_DELETEWATCH, OnDebugDeletewatch)
	ON_COMMAND(ID_DEBUG_MODIFYDLG, OnDebugModifyDlg)
	ON_COMMAND(ID_DEBUG_HEX, OnDebugHex)
	ON_COMMAND(ID_DEBUG_EDITDIALOG, OnDebugEditdialog)
	ON_COMMAND(ID_DEBUG_FIND, OnDebugFind)
	ON_COMMAND(ID_DEBUG_FINDNEXT, OnDebugFindnext)
	ON_COMMAND(ID_DEBUG_FONTS, OnDebugFonts)
	ON_COMMAND(ID_DEBUG_GO, OnDebugGo)
	ON_COMMAND(ID_DEBUG_PAUSE, OnDebugPause)
	ON_COMMAND(ID_DEBUG_GOTOLINE, OnDebugGotoline)
	ON_COMMAND(ID_DEBUG_NEWDIALOG, OnDebugNewdialog)
	ON_COMMAND(ID_DEBUG_PASTE, OnDebugPaste)
	ON_COMMAND(ID_DEBUG_RECORDING, OnDebugRecording)
	ON_COMMAND(ID_DEBUG_REPLACE, OnDebugReplace)
	ON_COMMAND(ID_DEBUG_SUSPEND, OnDebugSuspend)
	ON_COMMAND(ID_DEBUG_SYNTAX, OnDebugSyntax)
	ON_COMMAND(ID_DEBUG_TRACEIN, OnDebugTracein)
	ON_COMMAND(ID_DEBUG_TRACEOVER, OnDebugTraceover)
	ON_COMMAND(ID_DEBUG_UNDO, OnDebugUndo)
	ON_COMMAND(ID_DEBUG_NEW, OnDebugNew)
	ON_COMMAND(ID_DEBUG_OPEN, OnDebugOpen)
	ON_COMMAND(ID_DEBUG_SAVE, OnDebugSave)
	ON_COMMAND(ID_DEBUG_SAVEAS, OnDebugSaveas)
	ON_COMMAND(ID_DEBUG_IMPORT, OnDebugImport)
	ON_COMMAND(ID_DEBUG_GETHELPON, OnDebugGetHelpOn)	
	ON_COMMAND(ID_DEBUG_EDITORHELP, OnDebugEditorHelp)	
	ON_COMMAND(ID_DEBUG_TRIASHELP, OnDebugTriasHelp)	
	ON_COMMAND(ID_DEBUG_INSERT, OnDebugInsert)
	ON_COMMAND(ID_DEBUG_REMOVE, OnDebugRemove)
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_DEBUG_FUNCTIONINSERT, OnDebugFunctionInsert)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_FUNCTIONINSERT, OnUpdateDebugFunctionInsert)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_NEWFILE, OnUpdateDebugNewFile)
	ON_COMMAND(ID_VIEW_PROJECTBAR, OnViewProjectbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROJECTBAR, OnUpdateViewProjectbar)
	ON_COMMAND(ID_VIEW_DEBUGGERBAR, OnViewDebuggerbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DEBUGGERBAR, OnUpdateViewDebuggerbar)
	ON_COMMAND(ID_VIEW_NOTIFICATIONBAR, OnViewNotificationbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NOTIFICATIONBAR, OnUpdateViewNotificationbar)
	ON_COMMAND(ID_VIEW_STATUSBAR, OnViewStatusbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUSBAR, OnUpdateViewStatusbar)
	ON_COMMAND(ID_DEBUG_EXPORTALL, OnDebugExportall)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_EXPORTALL, OnUpdateDebugExportall)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_PAUSE, OnUpdateDebugPause)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_CUT, OnUpdateDebugCut)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_PASTE, OnUpdateDebugPaste)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_COPY, OnUpdateDebugCopy)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_UNDO, OnUpdateDebugUndo)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_GO, OnUpdateDebugGo)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_SUSPEND, OnUpdateDebugSuspend)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_BREAKPOINT, OnUpdateDebugBreakpoint)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_ADDWATCH, OnUpdateDebugAddwatch)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_DELETEWATCH, OnUpdateDebugDeletewatch)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_CALLSTACK, OnUpdateDebugCallstack)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_TRACEIN, OnUpdateDebugTracein)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_TRACEOVER, OnUpdateDebugTraceover)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_NEW, OnUpdateDebugNew)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_OPEN, OnUpdateDebugOpen)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_SAVE, OnUpdateDebugSave)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_IMPORT, OnUpdateDebugImport)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_SAVEAS, OnUpdateDebugSaveas)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_INSERT, OnUpdateDebugInsert)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_FILTERINSERT, OnUpdateDebugFilterInsert)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_REMOVE, OnUpdateDebugRemove)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_GETHELPON, OnUpdateDebugGetHelpOn)	
	ON_UPDATE_COMMAND_UI(ID_DEBUG_EDITORHELP, OnUpdateDebugEditorHelp)	
	ON_UPDATE_COMMAND_UI(ID_DEBUG_TRIASHELP, OnUpdateDebugTriasHelp)	
	ON_UPDATE_COMMAND_UI(ID_DEBUG_EDITDIALOG, OnUpdateDebugEditdialog)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_FONTS, OnUpdateDebugFonts)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_GOTOLINE, OnUpdateDebugGotoline)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_DELETE, OnUpdateDebugDelete)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_FIND, OnUpdateDebugFind)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_FINDNEXT, OnUpdateDebugFindNext)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_REPLACE, OnUpdateDebugReplace)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_MODIFYDLG, OnUpdateDebugModifyDlg)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_HEX, OnUpdateDebugHex)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_SYNTAX, OnUpdateDebugSyntax)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_NEWDIALOG, OnUpdateDebugNewdialog)
	ON_COMMAND(ID_DEBUG_IMPORTALL, OnDebugImportall)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_IMPORTALL, OnUpdateDebugImportall)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBONOTIFICATION, OnCombo)
	ON_COMMAND(ID_SELGENERALPROJECT, OnSelTabGeneral)
	ON_COMMAND(ID_SELFILTERPROJECT, OnSelTabFilter)
	ON_COMMAND(ID_SELOBJFEATPROJECT, OnSelTabObjFeat)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplit message handlers

BOOL CSplit::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (cs.style & WS_VISIBLE)
		cs.style &= ~WS_VISIBLE;
	return CFrameWnd::PreCreateWindow(cs);
}

BOOL CSplit::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!m_Splitter.CreateStatic(this, 1, 2))
		return FALSE;

	RECT rectDebugger, rectTree, rectFrame;
	ReadRegSettingsWindow (&rectFrame, &rectDebugger, &rectTree);

	int ix = rectTree.right - rectTree.left;
	int iy = rectTree.bottom - rectTree.top;

	if (!m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CDebFormView), CSize(ix, iy), pContext))
		return FALSE;

	ix = rectDebugger.right - rectDebugger.left;
	iy = rectDebugger.bottom - rectDebugger.top;

	if (!m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CDebFormView2), CSize (ix, iy), pContext))
		return FALSE;

	m_Splitter.ShowWindow(SW_SHOWNORMAL);
	m_Splitter.UpdateWindow();
	
	return  CFrameWnd::OnCreateClient(lpcs, pContext);
}

int CSplit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!CreateStatusbar())
		return -1;	
	
	if (!CreateProjectToolbar())
		return -1;

	if (!CreateToolbar())
		return -1;

	if (!CreateNotifBar())
		return -1;

	if (FAILED(CreateMRU()))
		return -1;
	// Toolbar-Docking enable
	EnableDocking(CBRS_ALIGN_ANY);	
	// Toolbar erst default docking
	Dockingbars();
	// Layout aus Reg
	LoadBarState(g_cbBasicScriptLayout);
	
	SetDebuggerIcon();
	SetWindowPosition();
	SetTimer (m_ID_TIMER, 100, NULL);

	return 0;
}

void CSplit::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	if (!bSysMenu)
	{
		ASSERT(pPopupMenu != NULL);
		// check the enabled state of various menu items
		CCmdUI state;        
		state.m_pMenu = pPopupMenu;
		ASSERT(state.m_pOther == NULL);
		
		state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
		for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
			 state.m_nIndex++)
		{
			state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
			if (state.m_nID == 0)
				continue; // menu separator or invalid cmd - ignore it
				
			ASSERT(state.m_pOther == NULL);
			ASSERT(state.m_pMenu != NULL);
			if (state.m_nID == (UINT)-1)
			{
				// possibly a popup menu, route to first item of that popup
				state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
				if (state.m_pSubMenu == NULL ||
				    (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				    state.m_nID == (UINT)-1)
				{				    			 
			        continue; // first item of popup can't be routed to
			    }
			    state.DoUpdate(this, FALSE);  // popups are never auto disabled
			}
			else
			{
				// normal menu item
				// Auto enable/disable if command is _not_ a system command
				state.m_pSubMenu = NULL;
				state.DoUpdate(this, state.m_nID < 0xF000);
				OnUpdateDebugMRU(state.m_pMenu, state.m_nID);
				// Processing MRU
			}
		}
	}
}

void CSplit::OnInitMenu(CMenu* pMenu) 
{
	CFrameWnd::OnInitMenu(pMenu);
	
	// Tree behandeln: Wird gerade ein Item eingefügt ?
	// erzwingt Beenden des Editiervorganges
	if (IsLabelEdit_Selected())	
		GetTreeCtrl() -> SetFocus();
}

void CSplit::OnClose() 
{
	if (!GetDebuggerCtrl() -> DebuggerEnd()) 
		return;

	CFrameWnd::OnClose();
}

void CSplit::OnDestroy() 
{	// Freigabe der Funktionsitems in der Combo
	FixedupSaveBarState (g_cbBasicScriptLayout);
	m_wndNotifBar.OnDestroy ();
	SaveRegSettingsWindow();
	ResetFontStatusbar();
	ResetDebuggerIcon();
// löscht Timer 
	KillTimer (m_ID_TIMER);

	EndMRUHandling ();

//	if (OkToExit()), DestroyDebugger() nach Message
	GetParent() -> PostMessage (m_uiWMClose);

	CFrameWnd::OnDestroy();	
	// TODO: Add your message handler code here	
}

BOOL CSplit::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	UINT uiID = GET_WM_COMMAND_ID (wParam, lParam);
	UINT uiNotifCode = GET_WM_COMMAND_CMD (wParam, lParam);

	if (OnDebugMRU(uiID, uiNotifCode))
	{
		VERIFY(GenerateCaption());
		SetReadyStatusbarText();
		SetFocus(); // auf DebuggerCtrl
		return true;
	}
	
	return CFrameWnd::OnCommand(wParam, lParam);
}


void CSplit::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) 
{
	CFrameWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
	
	if (0xffff != nFlags && nFlags & MF_SYSMENU) 
	return;	// nicht unser Bier

// text fuer StatusBar 
	CString str;

	TRY {                                       
		if (0xffff == nFlags && NULL == hSysMenu) {
			str.LoadString (ID_STATUSBAR_PANE1);	// Menu ausgeblendet
		} else if (nItemID > 0)
			str.LoadString (nItemID);
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return;
	}                  
	END_CATCH

	GetStatusbar() -> SetPaneText (0, str, true);	
}

////////////////////////////////////////////////////////////////
// Für Tooltips
BOOL CSplit::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	switch (((LPNMHDR)lParam) -> code) 
	{
	case TTN_NEEDTEXT:    // Display tool tip text.
		{
			LPTOOLTIPTEXT lpToolTipText = (LPTOOLTIPTEXT)lParam;

			lpToolTipText -> hinst = g_hInstance;
			lpToolTipText -> lpszText = MAKEINTRESOURCE(lpToolTipText->hdr.idFrom+1000);

			*pResult = true;
			return true;
		}

	case TTN_SHOW:	// ToolTip wird eingeblendet
		{
		// StatusZeile richten
			CString str = GetDefaultName(((LPTOOLTIPTEXT)lParam)->hdr.idFrom);
			GetStatusbar() -> SetPaneText (0, str, true);

			*pResult = true;
			return true;
		}
		break;

	case TTN_POP:	// ToolTip wird ausgebelendet
		{
		// StatusZeile richten
			CString str = GetDefaultName(ID_STATUSBAR_PANE1);
			GetStatusbar() -> SetPaneText (0, str, true);

			*pResult = true;
			return true;
		}
		break;

	case TBN_QUERYDELETE:	// Toolbar customization -- can we delete this button?
		*pResult = true;
		return true;

	case TBN_GETBUTTONINFO:	// The toolbar needs information about a button.
		*pResult = false;
		return true;

	case TBN_QUERYINSERT:	// Can this button be inserted? Just say yo.
		*pResult = true;
		return true;

	case TBN_CUSTHELP:	// Need to display custom help.
		MessageBox ("This help is custom.");
		return true;

	case TBN_TOOLBARCHANGE:	// Done dragging a bitmap to the toolbar.
		GetToolbar() -> GetToolBarCtrl().AutoSize();
		return true;

	default:
		break;
	}

	return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

void CSplit::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);

	// hier nur einmal am Anfang
	// SetWindowSize();
	SetToolbarPos();
	m_Splitter.RecalcLayout();
}

void CSplit::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == m_ID_TIMER)
		GetDebuggerCtrl() -> OnTimer();
	CFrameWnd::OnTimer(nIDEvent);
}

void CSplit::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
	GetDebuggerCtrl() -> SetFocus();
}

CDebuggerCtrl* CSplit::GetDebuggerCtrl()
{
	CDebFormView2* p = (CDebFormView2 *) m_Splitter.GetPane(0,1);
	ASSERT (p);
	ASSERT (p -> IsKindOf(RUNTIME_CLASS(CDebFormView2)));

	return p->GetDebuggerCtrl() ? p->GetDebuggerCtrl() : NULL;
}

CRelMacroTreeBox * CSplit::GetTreeCtrl()
{
	CDebFormView * p = (CDebFormView *) m_Splitter.GetPane(0,0);
	ASSERT (p);
	ASSERT (p -> IsKindOf(RUNTIME_CLASS(CDebFormView)));
	
	return p -> GetTreeCtrl() ? p -> GetTreeCtrl() : NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Aufbewahrung der Superitems und Subitems, "long" eigentlich RunningScriptsOrg aus Subitems
/*
CRelScripts * CSplit::GetRelScripts(void) 
{ 
	return GetDebuggerCtrl() -> GetRelScripts(); 
}
*/
void CSplit::SetSelectedItem(ITreeItem* pTI) 
{ 
	if (pTI)// wenn Null, schon freigegeben
	{
		if (m_pISelItem) m_pISelItem -> Release();
		m_pISelItem = pTI; 
		m_pISelItem -> AddRef();
	}
	else
		m_pISelItem = NULL;
}
void CSplit::SetLoadedItem(ITreeItem* pTI) 
{ 
	if (pTI)// wenn Null, schon freigegeben
	{
		if (m_pILoadedItem) m_pILoadedItem -> Release();
		m_pILoadedItem = pTI; 
		m_pILoadedItem -> AddRef(); 
	}
	else
		m_pILoadedItem = NULL;
}
// Loaded und Selected Item PROPERTIES
HRESULT CSplit::GetLoadedItem(ITreeItem** ppI) 
{ 
	if (m_pILoadedItem)
	{
		*ppI = m_pILoadedItem;
		(*ppI) -> AddRef();
		return NOERROR;
	}
	return E_FAIL; 
}
HRESULT CSplit::GetSelectedItem(ITreeItem** ppI) 
{ 
	if (m_pISelItem)
	{
		*ppI = m_pISelItem;
		(*ppI) -> AddRef();
		return NOERROR;
	}
	return E_FAIL; 
}
BOOL CSplit::IsScript_Selected()
{
	try
	{
		WTreeItem IT;
		HRESULT hr = GetSelectedItem(IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		CLSID clsid;
		WPersist IP = IT;
		IP -> GetClassID(&clsid);
		if (
			IsEqualIID(clsid, CLSID_Script) || 
			IsEqualIID(clsid, CLSID_FileScript) ||
			IsEqualIID(clsid, CLSID_CreateObjectFeatureScript) ||
			IsEqualIID(clsid, CLSID_CreateObjectFeatureFileScript) 
			)
			return true;
	}
	catch (_com_error&) {
		return false;
	}
	return false;
}
BOOL CSplit::IsFunction_Selected()
{
	try
	{
		WTreeItem IT;
		HRESULT hr = GetSelectedItem(IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		CLSID clsid;
		WPersist IP = IT;
		IP -> GetClassID(&clsid);
		if (IsEqualIID(clsid, CLSID_FunctionItem))
			return true;
	}
	catch (_com_error&) {
		return false;
	}
	return false;
}
BOOL CSplit::IsFunction()
{
	try
	{
		WTreeItem IT;
		HRESULT hr = GetSelectedItem(IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		CLSID clsid;
		WPersist IP = IT;
		IP -> GetClassID(&clsid);
		if (IsEqualIID(clsid, CLSID_FunctionItem))
			return true;
	}
	catch (_com_error&) {
		return false;
	}
	return false;
}

BOOL CSplit::IsLabelEdit_Selected()
{
	WTreeItem IT;
	if (FAILED(GetSelectedItem(IT.ppi())))	
		return false;// Legt Menü lahm, deshalb true
	
	return IT -> IsLabelEdit();
}

int CSplit::GetPopUpMenuID()
{
	WTreeItem IT;
	if (FAILED(GetSelectedItem(IT.ppi())))	
		return false;// Legt Menü lahm, deshalb true
	
	return IT -> GetPopUpMenuID();
}

CString CSplit::GetScriptName_Selected()
{
	CString strName;
	try
	{
		WTreeItem IT;
		HRESULT hr = GetSelectedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		LPSTR lpstr = strName.GetBuffer(_MAX_PATH);
		if (NULL == lpstr) _com_issue_error(E_POINTER);

		WBSProperty IB = IT;
		IB -> GetScriptName(lpstr, _MAX_PATH);
	}
	catch (_com_error&) {
		return g_cbNil;
	}
	catch(CMemoryException) {
		return g_cbNil;
	} 
	strName.ReleaseBuffer(); 
	return strName;
}

CString CSplit::GetParentName_Selected()
{
	CString strName;
	try
	{
		WTreeItem IT;
		HRESULT hr = GetSelectedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		LPSTR lpstr = strName.GetBuffer(_MAX_PATH);
		if (NULL == lpstr) _com_issue_error(E_POINTER);

		WObjManHelper IOMH = IT;
		IOMH -> GetParentName(lpstr, _MAX_PATH);
	}
	catch (_com_error&) {
		return g_cbNil;
	}
	catch(CMemoryException) {
		return g_cbNil;
	} 
	strName.ReleaseBuffer(); 
	return strName;
}

//////////////////////////////////////////////////////
// Properties Loaded
HRESULT CSplit::SetCode(ebHCODE hCode)
{
	try
	{
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		WBSProperty IBSP = IT;
		IBSP -> SetCode(hCode);
	}
	catch (_com_error& e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}
HRESULT CSplit::GetCode(ebHCODE *phCode)
{
	ASSERT(phCode);
	if (NULL == phCode) return E_POINTER;

	*phCode = NULL;
	try
	{
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		WBSProperty IBSP = IT;
		IBSP -> GetCode(phCode);
	}
	catch (_com_error& e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}
BOOL CSplit::IsScript()
{
	try
	{
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		CLSID clsid;
		WPersist IP = IT;
		IP -> GetClassID(&clsid);
		if (IsEqualIID(clsid, CLSID_Script) || IsEqualIID(clsid, CLSID_FileScript))
			return true;
	}
	catch (_com_error&) {
		return false;
	}
	return false;
}
CString CSplit::GetScriptName()
{
	CString strName;
	try
	{
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		LPSTR lpstr = strName.GetBuffer(_MAX_PATH);
		if (NULL == lpstr) _com_issue_error(E_POINTER);

		WBSProperty IB = IT;
		IB -> GetScriptName(lpstr, _MAX_PATH);
	}
	catch (_com_error&) {
		return g_cbNil;
	}
	catch(CMemoryException)
	{
		return g_cbNil;
	} 
	strName.ReleaseBuffer(); 
	return strName;
}
CString CSplit::GetParentName()
{
	CString strName;
	try
	{
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		LPSTR lpstr = strName.GetBuffer(_MAX_PATH);
		if (NULL == lpstr) _com_issue_error(E_POINTER);

		WObjManHelper IOMH = IT;
		IOMH -> GetParentName(lpstr, _MAX_PATH);
	}
	catch (_com_error&) {
		return g_cbNil;
	}
	catch(CMemoryException)
	{
		return g_cbNil;
	} 
	strName.ReleaseBuffer();
	return strName;
}

void CSplit::GetInitCaretPos (int & ix, int & iy, int & fSelect)
{
	WTreeItem IT;
	if (FAILED(GetLoadedItem(IT.ppi())))	
	{
		return;
	}
	IT -> GetInitCaretPos(ix, iy, fSelect);
}

BOOL CSplit::GetDirty()
{
	try {
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		WObjManHelper IOMH = IT;
		if (IOMH -> GetDirty())
			return true;
	} catch (_com_error&) {
		return false;
	}
	return false;
}
void CSplit::SetDirty(BOOL f)
{
	try {
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		WObjManHelper IOMH = IT;
		IOMH -> SetDirty(f);
	} catch (_com_error&) {
	}
}
BOOL CSplit::GetInitNew()
{
	try {
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		WObjManHelper IOMH = IT;
		if (IOMH -> GetInitNew())
			return true;
	} catch (_com_error&) {
		return false;
	}
	return false;
}

HTREEITEM CSplit::GetChildItemSel(ITreeItem **ppIT)
{
	return GetTreeCtrl() -> GetChildItemSel(ppIT);
}

BOOL CSplit::GetInitNew_Selected()
{
	try {
		WTreeItem IT;
		HRESULT hr = GetSelectedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		WObjManHelper IOMH = IT;
		if (IOMH -> GetInitNew())
			return true;
	} catch (_com_error&) {
		return false;
	}
	return false;
}
BOOL CSplit::GetEditOnly()
{
	try {
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		WObjManHelper IOMH = IT;
		if (IOMH -> GetEditOnly())
			return true;
	} catch (_com_error&) {
		return false;
	}
	return false;
}

void CSplit::SetEditOnly(BOOL fEdit)
{
	try {
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		WObjManHelper IOMH = IT;
		IOMH -> SetEditOnly(fEdit);
	} catch (_com_error&) {
	}
}

HWND CSplit::GetDebuggerWnd(void) 
{ 
	return GetDebuggerCtrl() -> GetSafeHwnd(); 
}

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen zur Initialisierung

BOOL CSplit::InitFirst()
{
	CString strDefaultScr = GetDefaultScript(); 
	if (strDefaultScr.IsEmpty()) return false;

	LPSTR lpstrMacroText = NULL;
	lpstrMacroText = (LPSTR)CoTaskMemAlloc(strDefaultScr.GetLength()+1);
	if (NULL == lpstrMacroText) return false;
	
	strcpy(lpstrMacroText, strDefaultScr);
	// wird intern in GetDebuggerCtrl() -> SetScript() freigegeben
	GetDebuggerCtrl() -> OnDebugNew(lpstrMacroText);
	GenerateCaption();
	return true;
}


HRESULT CSplit::InitTreeAndDebugger()
{
// Debugger Init., wenn noch Running RAUS !!!
	HRESULT hr = GetDebuggerCtrl() -> InitDebuggerCtrl(this);
	if (S_OK != hr) _com_issue_error(hr);
	// Initialisierung (Imageliste...)
	hr = GetTreeCtrl() -> Init(this);
	if (FAILED(hr)) return hr;
	return S_OK;
}

HRESULT CSplit::InitTreeView(IStreamInfo *pISI)
{
	ASSERT(pISI);
	if (NULL == pISI) return E_POINTER;
	CDebFormView* pLeft = (CDebFormView *) m_Splitter.GetPane(0,0);
	ASSERT(pLeft);
	if (NULL == pLeft) return E_POINTER;
	pLeft -> Init(pISI -> GetManID());
	return S_OK;
}

HRESULT CSplit::ResetTreeViewIfOnClose()
{
	CDebFormView* pLeft = (CDebFormView *) m_Splitter.GetPane(0,0);
	ASSERT(pLeft);
	if (NULL == pLeft) return E_POINTER;
	pLeft -> ResetIfOnClose(m_uiStartManID);
	return S_OK;
}

BOOL CSplit::GetFormerManagement (UINT uiManID,
										IObjectManagement *pIOM, 
										IStreamInfo *pISI,
										IObjectManagement **ppIOM, 
										IStreamInfo **ppISI)
{
	ASSERT(ppIOM);
	ASSERT(ppISI);
	if (NULL == ppIOM || NULL == ppISI) return false;

	*ppIOM = NULL;
	*ppISI = NULL;

	if (NULL != pIOM && NULL != pISI) 
	{
		*ppIOM = pIOM;
		(*ppIOM) -> AddRef();
		*ppISI = pISI;
		(*ppISI) -> AddRef();
		return true;
	}

	switch (uiManID)
	{
	case MANID_GENERAL:
		{
			WStreamInfo ISI;
			HRESULT hr = GetInfoGeneralScripts(ISI.ppi());
			if (FAILED(hr)) return false;
			WObjectManagement IOM;
			hr = GetGeneralScripts(IOM.ppi());
			if (FAILED(hr)) return false;

			*ppIOM = IOM.detach();
			*ppISI = ISI.detach();
			break;
		}
	case MANID_FILTER:
		{
			WStreamInfo ISI;
			HRESULT hr = GetInfoFilterScripts(ISI.ppi());
			if (FAILED(hr)) return false;
			WObjectManagement IOM;
			hr = GetFilterScripts(IOM.ppi());
			if (FAILED(hr)) return false;

			*ppIOM = IOM.detach();
			*ppISI = ISI.detach();
			break;
		}
	case MANID_OBJFEAT:
		{
			WStreamInfo ISI;
			HRESULT hr = GetInfoObjFeatScripts(ISI.ppi());
			if (FAILED(hr)) return false;
			WObjectManagement IOM;
			hr = GetObjFeatScripts(IOM.ppi());
			if (FAILED(hr)) return false;

			*ppIOM = IOM.detach();
			*ppISI = ISI.detach();
			break;
		}
	default:
		{
			return false;
		}
	}
	return true;
}

HRESULT CSplit::Init(LPCSTR lpcstr, BOOL fOpen, IObjectManagement *pIOM, IStreamInfo *pISI)
{
	Save();	// 0 ist Cancel
	Delete();
	ResetItems();

	WStreamInfo ISI;
	WObjectManagement IOM;
	if (!GetFormerManagement (m_uiStartManID, pIOM, pISI, IOM.ppi(), ISI.ppi()))
		return E_FAIL;
	m_uiStartManID = 0;
	HRESULT hr = GetDebuggerCtrl() -> SwitchManagement(IOM, ISI);
	if (FAILED(hr)) return hr;
	InitTreeView(ISI);
	GetTreeCtrl() -> InitTree(IOM, ISI);
	return InitOpen(lpcstr, fOpen);
}

BOOL CSplit::Init(LPCSTR lpcstrScriptName, 
				  BOOL fOpenFile, 
				  UINT ui, 
				  IObjectManagement *pIOM,
				  IStreamInfo *pISI)
{		
	try
	{
		THROW_FAILED_HRESULT(InitTreeAndDebugger());
		// 1. Löschen alter Baum
		// 2. Neuen Baum erzeugen
		// 3. ScriptName öffnen
		THROW_FAILED_HRESULT(Init(lpcstrScriptName, fOpenFile, pIOM, pISI));
		// Beim Schliessen muss richtiger Debugger geschlossen werden:
		// - BreakPoint
		// - Runtimeerror
		// - allgemein
		m_uiWMClose = ui;

		ShowWindow(SW_SHOWNORMAL);
		UpdateWindow();
	}
	catch (_com_error&)
	{
		return false;
	}
	return true;
}

HRESULT CSplit::InitOpen(LPCSTR lpcstrScriptName, BOOL fOpenFile)
{
	try
	{
		BOOL fResult = false;
		if (lpcstrScriptName && fOpenFile)
		{// dann File öffnen
			fResult = OnDebugInitOpen(lpcstrScriptName);
			if (!fResult) _com_issue_error(E_FAIL); 
		}
		else 
		{	
			// Macro suchen, Setzt Focus auf Tree, wenn Macro vorhanden
			HRESULT hr = NOERROR;
			if (!m_strStartScript.IsEmpty()){// StartScript zuerst bedienen
				hr = GetTreeCtrl() -> InitFirstScript(m_strStartScript);
			} else {
				hr = GetTreeCtrl() -> InitFirstScript(lpcstrScriptName);
			}	
			if (FAILED(hr)) _com_issue_error(hr);		

			if (S_OK == hr) {// Macro im Tree öffnen
				fResult = OnDebugInitOpen();
			} else {// kein Macro oder FileName vorhanden 
				fResult = InitFirst(); 
			}
			if (!fResult) _com_issue_error(E_FAIL);  
		}
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CSplit::CreateMRU ()
{
	m_uiMruID = ID_MRU_FILE-1;

	try {
		m_pMRUMenu = CreateMruMenu (NBMRUMENUSHOW, NBMRUMENU, MAXSIZEMRUITEM, m_uiMruID);
	} catch (bad_alloc) {
		return E_OUTOFMEMORY;
	}
	if (m_pMRUMenu == NULL) return E_FAIL; 
	
	LoadMruInReg (m_pMRUMenu, g_cbOpenMRUKey);

	HWND hWnd = GetSafeHwnd();
	ASSERT(NULL != hWnd);
	// refresh MRUMenu
	PlaceMenuMRUItem (m_pMRUMenu, ::GetSubMenu (::GetMenu(hWnd), 0), IDM_CLOSE); 

	return NOERROR;
}

BOOL CSplit::CreateNotifBar()
{
	if (!m_wndNotifBar.Create(this))
		return false;
	// Toolbar-Docking enable
	m_wndNotifBar.EnableDocking(CBRS_ALIGN_BOTTOM|CBRS_ALIGN_TOP);
	return true;
}

BOOL CSplit::CreateProjectToolbar(void)
{
	if (!m_wndProjectToolBar.Create (this, WS_CHILD|WS_VISIBLE|CBRS_TOP|
			CBRS_TOOLTIPS|CBRS_FLYBY) ||
	    !m_wndProjectToolBar.LoadBitmap(IDR_PROJECTTOOLBAR) ||
	    !m_wndProjectToolBar.SetButtons (TBProject, sizeof(TBProject)/sizeof(UINT)))
	{
		TRACE("Failed to create projecttoolbar\n");
		return false;      // fail to create
	}
	// Toolbar-Docking enable
	m_wndProjectToolBar.EnableDocking(CBRS_ALIGN_ANY);
	return true;
}

BOOL CSplit::CreateToolbar()
{
	if (!m_wndToolBar.Create (this, WS_CHILD|WS_VISIBLE|CBRS_TOP|
			CBRS_TOOLTIPS|CBRS_FLYBY) ||
	    !m_wndToolBar.LoadBitmap(IDR_DEBUGFRAME) ||
	    !m_wndToolBar.SetButtons (buttons, (sizeof(buttons)/sizeof(UINT))))
	{
		TRACE("Failed to create toolbar\n");
		return false;      // fail to create
	}
	// Toolbar-Docking enable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	return true;
}

BOOL CSplit::CreateStatusbar()
{
	if (!m_wndStatusBar.Create(this) ||
	    !m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return false;      // fail to create
	}
	SetFontStatusbar();
	return true;
}

void CSplit::SetFontStatusbar()
{
	m_pSBOldFont = m_wndStatusBar.GetFont();

	CFont f;
	
	f.Attach ((HFONT)GetStockObject (ANSI_VAR_FONT));
	m_wndStatusBar.SetFont (&f, true);
	f.Detach();
// StatusBar initialisieren
	m_wndStatusBar.SetPaneInfo (0, ID_STATUSBAR_PANE1, SBPS_STRETCH, 0);
}

void CSplit::SetWindowPosition()
{
	RECT rectDebugger, rectTree, rectFrame;
	if (ReadRegSettingsWindow (&rectFrame, &rectDebugger, &rectTree)) 
	{
		SetWindowPos (NULL, rectFrame.left, rectFrame.top, 
							rectFrame.right-rectFrame.left, 
							-rectFrame.top+rectFrame.bottom, 
							SWP_NOZORDER|SWP_NOACTIVATE);
	}
}

void CSplit::SetDebuggerIcon(UINT uiIcon)
{
	m_hIcon = GetIcon(true);
	SetIcon(AfxGetApp() -> LoadIcon(uiIcon), true);	
}

void CSplit::SetToolbarPos()
{
	HWND hWnd = m_wndToolBar.GetSafeHwnd();
	if (hWnd != NULL && IsWindow(hWnd))
	{
		m_wndToolBar.GetToolBarCtrl().AutoSize();
		RepositionBars (0, 0xffff, AFX_IDW_PANE_FIRST);
	}
}

void CSplit::SetWindowSize()
{
	if (!m_fInit) 
	{// nur beim ersten Mal
		UINT nFlags = SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER;
		RECT rect, rectTree;
		
		// Grösse Debuggerwindow
		GetDebuggerRect(&rect);
		// Grösse Treewindow
		GetTreeRect(&rectTree);

		UINT uiTreeWi = rectTree.right-rectTree.left;

		UINT uiDebWi =	rect.right-rect.left;
		UINT uiDebHi =	rect.bottom-rect.top;

		GetDebuggerCtrl() -> SetWindowPos (NULL, uiTreeWi+7, -1, uiDebWi+6, uiDebHi+5, nFlags); 
		
		m_fInit = true;
	}
}

void CSplit::GetTreeRect(RECT *prect)
{
	CWnd *pWndTree = (CWnd *)m_Splitter.GetPane(0,0);
	ASSERT(NULL != pWndTree); 
	// RIGHT==BREITE, BOTTOM==HÖHE
	pWndTree -> GetWindowRect(prect);
}

void CSplit::GetDebuggerRect(RECT *prect)
{
	CWnd *pWnd = (CWnd *) (CWnd *)m_Splitter.GetPane(0,1);
	ASSERT(NULL != pWnd);
	// RIGHT==BREITE, BOTTOM==HÖHE
	pWnd -> GetWindowRect(prect); 
}

//////////////////////////////////
// Resets
void CSplit::EndMRUHandling (void)
{
	if (m_pMRUMenu) 
	{
		SaveMruInReg (m_pMRUMenu, g_cbOpenMRUKey);
		if (m_pMRUMenu) DeleteMruMenu (m_pMRUMenu);
		m_pMRUMenu = NULL;
	}
}

void CSplit::ResetDebuggerIcon()
{// Fenstericon zurücksetzen
	if (m_hIcon)
		SetIcon(m_hIcon, true);
	m_hIcon = NULL;
}

void CSplit::ResetFontStatusbar()
{
	if (m_pSBOldFont) 
		m_wndStatusBar.SetFont (m_pSBOldFont, true);
	m_pSBOldFont = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// OnIdleUpdates
void CSplit::OnUpdateDebugFunctionInsert(CCmdUI* pCmdUI) 
{
	GetDebuggerCtrl() -> OnUpdateDebugFunctionInsert(pCmdUI);
}
void CSplit::OnUpdateDebugMRU(CMenu *pMenu, int nID)
{
	GetDebuggerCtrl() -> OnUpdateDebugMRU(pMenu, nID, m_uiMruID);
}
void CSplit::OnUpdateDebugPause(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugPause(pCmdUI);
}
void CSplit::OnUpdateDebugCopy(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugCopy(pCmdUI);
}
void CSplit::OnUpdateDebugCut(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugCut(pCmdUI);
}
void CSplit::OnUpdateDebugPaste(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugPaste(pCmdUI);
}	   
void CSplit::OnUpdateDebugUndo(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugUndo(pCmdUI);
}	   
void CSplit::OnUpdateDebugGo(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugGo(pCmdUI);
}	   
void CSplit::OnUpdateDebugSuspend(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugSuspend(pCmdUI);
}	   
void CSplit::OnUpdateDebugBreakpoint(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugBreakpoint(pCmdUI);
}	   
void CSplit::OnUpdateDebugAddwatch(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugAddwatch(pCmdUI);
}	   
void CSplit::OnUpdateDebugDeletewatch(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugDeletewatch(pCmdUI);
}	   
void CSplit::OnUpdateDebugCallstack(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugCallstack(pCmdUI);
}	   
void CSplit::OnUpdateDebugTracein(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugTracein(pCmdUI);
}	   
void CSplit::OnUpdateDebugTraceover(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugTraceover(pCmdUI);
}	   
void CSplit::OnUpdateDebugSyntax(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugSyntax(pCmdUI);
}
void CSplit::OnUpdateDebugHex(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugHex(pCmdUI);
}
void CSplit::OnUpdateDebugModifyDlg(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugModifyDlg(pCmdUI);
}
void CSplit::OnUpdateDebugReplace(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugReplace(pCmdUI);
}
void CSplit::OnUpdateDebugFindNext(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugFindNext(pCmdUI);
}
void CSplit::OnUpdateDebugFind(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugFind(pCmdUI);
}
void CSplit::OnUpdateDebugDelete(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugDelete(pCmdUI);
}
void CSplit::OnUpdateDebugGotoline(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugGotoline(pCmdUI);
}
void CSplit::OnUpdateDebugFonts(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugFonts(pCmdUI);
}
void CSplit::OnUpdateDebugNewdialog(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugNewdialog(pCmdUI);
}
void CSplit::OnUpdateDebugNewFile(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugNewFile(pCmdUI);
}
void CSplit::OnUpdateDebugEditdialog(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugEditdialog(pCmdUI);
}
void CSplit::OnUpdateDebugTriasHelp(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugTriasHelp(pCmdUI);
}
void CSplit::OnUpdateDebugEditorHelp(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugEditorHelp(pCmdUI);
}
void CSplit::OnUpdateDebugGetHelpOn(CCmdUI *pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugGetHelpOn(pCmdUI);
}

//////////////////////////////////////////////////////
// Persistenz
void CSplit::OnUpdateDebugRemove(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugRemove(pCmdUI);
}
void CSplit::OnUpdateDebugInsert(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugInsert(pCmdUI);
}
void CSplit::OnUpdateDebugObjfeatinsert(CCmdUI* pCmdUI) 
{
	GetDebuggerCtrl() -> OnUpdateDebugObjfeatinsert(pCmdUI);
}
void CSplit::OnUpdateDebugFilterInsert(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugFilterInsert(pCmdUI);
}
void CSplit::OnUpdateDebugNew(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugNew(pCmdUI);
}   
void CSplit::OnUpdateDebugOpen(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugOpen(pCmdUI);
}
void CSplit::OnUpdateDebugSave(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugSave(pCmdUI);
}
void CSplit::OnUpdateDebugExportall(CCmdUI* pCmdUI) 
{
	GetDebuggerCtrl() -> OnUpdateDebugExportall(pCmdUI); 
}
void CSplit::OnUpdateDebugSaveas(CCmdUI* pCmdUI)// Export
{
	GetDebuggerCtrl() -> OnUpdateDebugSaveas(pCmdUI);
}
void CSplit::OnUpdateDebugImport(CCmdUI* pCmdUI)
{
	GetDebuggerCtrl() -> OnUpdateDebugImport(pCmdUI);
}

/////////////////////////////////////////////////////////////////////////////
// OnCommands
void CSplit::OnExit()
{	
	if (!GetDebuggerCtrl() -> DebuggerEnd()) 
		return;

	CFrameWnd::OnClose();
}

void CSplit::OnDebugCut() 
{
	GetDebuggerCtrl() -> OnDebugCut();
}

void CSplit::OnDebugCopy() 
{
	GetDebuggerCtrl() -> OnDebugCopy();
}

void CSplit::OnDebugAddwatch() 
{
	GetDebuggerCtrl() -> OnDebugAddwatch();	
}

void CSplit::OnDebugModifyDlg() 
{
	GetDebuggerCtrl() -> OnDebugModifyDlg();
}

void CSplit::OnDebugDeletewatch() 
{
	GetDebuggerCtrl() -> OnDebugDeletewatch();
}

void CSplit::OnDebugHex() 
{
	GetDebuggerCtrl() -> OnDebugHex();
}

void CSplit::OnDebugBreakpoint() 
{
	GetDebuggerCtrl() -> OnDebugBreakpoint();	
}

void CSplit::OnDebugCallstack() 
{
	GetDebuggerCtrl() -> OnDebugCallstack();	
}

void CSplit::OnDebugDelete() 
{
	GetDebuggerCtrl() -> OnDebugDelete();
}

void CSplit::OnDebugEditdialog() 
{
	GetDebuggerCtrl() -> OnDebugEditdialog();
}

void CSplit::OnDebugNewdialog() 
{                        
	GetDebuggerCtrl() -> OnDebugNewdialog();
}
                              
BOOL CSplit::OnDebugMRU(UINT uiID, UINT uiNotifCode)
{
	if (uiNotifCode == 0 && uiID >= m_uiMruID && uiID <= m_uiMruID+4)// 4 Items in der MRU 
	{
		if (1 == Save())	// 0 ist Cancel
		{// Altes, wenn noch initneu Löschen
			if(Delete())
			{
				return OpenFromMRU (uiID);
			}
		}
	}

	return false;
}

// Aufruf von Menü 
void CSplit::OnDebugFindnext() 
{                                 
	GetDebuggerCtrl() -> OnDebugFindnext();
}

// Aufruf von Menü 
void CSplit::OnDebugFind() 
{
	GetDebuggerCtrl() -> OnDebugFind();
}

void CSplit::OnDebugReplace() 
{
	GetDebuggerCtrl() -> OnDebugReplace();
}

void CSplit::OnDebugFonts() 
{
	GetDebuggerCtrl() -> OnDebugFonts();
}

void CSplit::OnDebugGotoline() 
{
	GetDebuggerCtrl() -> OnDebugGotoline();	
}

void CSplit::OnDebugPaste() 
{
	GetDebuggerCtrl() -> OnDebugPaste();	
}


void CSplit::OnDebugRecording() 
{
	GetDebuggerCtrl() -> OnDebugRecording();	
}

void CSplit::OnDebugSuspend() 
{
	GetDebuggerCtrl() -> OnDebugSuspend();	
}

void CSplit::OnDebugSyntax() 
{
	GetDebuggerCtrl() -> OnDebugSyntax();	
	SetFocus(); // auf DebuggerCtrl
}

void CSplit::OnDebugGo() 
{
	// Superitem des Geladenen selektieren
	VERIFY(SUCCEEDED(OnGo()));
}

void CSplit::OnDebugTracein() 
{
	VERIFY(SUCCEEDED(OnTracein()));
}

void CSplit::OnDebugTraceover() 
{// eventuell Superitem des Geladenen selektieren
	VERIFY(SUCCEEDED(OnTraceover()));
}

void CSplit::OnDebugPause() 
{
	GetDebuggerCtrl() -> OnDebugPause();	
}

void CSplit::OnDebugUndo() 
{
	GetDebuggerCtrl() -> OnDebugUndo();	
}

/////////////////////////////////////////////////////////////
// Running
HRESULT CSplit::OnGo()
{
	HRESULT hr = OpenOnGo();
	if (FAILED(hr)) return hr;
	// Super starten
	GetDebuggerCtrl() -> OnDebugGo();	
	return S_OK;
}
HRESULT CSplit::OnTracein()
{	
	// Eventuell SuperItem laden
	HRESULT hr = OpenOnGo();
	if (FAILED(hr)) return hr;
	// Super starten
	GetDebuggerCtrl() -> OnDebugTracein();	
	return S_OK;
}
HRESULT CSplit::OnTraceover()
{
// Eventuell SuperItem laden
	HRESULT hr = OpenOnGo();
	if (FAILED(hr)) return hr;
	// Super starten
	GetDebuggerCtrl() -> OnDebugTraceover();	
	return S_OK;
}
HRESULT CSplit::OpenOnGo()
{	// Eventuell SuperItem laden
	if (false == g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject()) return S_FALSE;

	HRESULT hr = GetTreeCtrl() -> OnDebugGo();
	if (S_FALSE == hr)
		Open(); // und Laden
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
	SetFocus(); // auf DebuggerCtrl
	return hr;
}

////////////////////////////////////////////////////////////
// PERSISTENZ
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// NEUES MAKRO ÖFFNEN, ALTES INM EDITOR ÜBERSCHREIBEN
void CSplit::OnDebugNew()
{
	if (S_OK != GetDebuggerCtrl() -> CanEdit()) return;
	// SaveAs() bevor überschreiben ?
	if (S_FALSE == QuerySaveAs(false)) return; // Cancel

	VERIFY(New());

	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
	SetFocus(); // auf DebuggerCtrl
}
////////////////////////////////////////////////////////////
// NEUEE DATEI ÖFFNEN
void CSplit::OnDebugNewFile()
{
	if (S_OK != GetDebuggerCtrl() -> CanOpen()) return;
	NewFile();
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
	SetFocus(); // auf DebuggerCtrl
}
////////////////////////////////////////////////////////////
// ÖFFNEN
void CSplit::OnDebugOpen()
{
	if (S_OK != GetDebuggerCtrl() -> CanOpen()) return;
	Open();
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
	SetFocus(); // bei Open Focus immer auf Debugger
}
// bei Init
BOOL CSplit::OnDebugInitOpen(LPCSTR lpcstr)
{
	BOOL fResult = Open(lpcstr);
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
	SetFocus(); // bei Open Focus immer auf Debugger
	return fResult;
}

////////////////////////////////////////////////////////////
// SPEICHERN
void CSplit::OnDebugSave()
{
	VERIFY(SaveLoaded());
	// Speicherung der Related im Tree, da SUPER-Item gespeichert werden muss, 
	// das nicht in CSplit (MainFrame) bekannt ist
	SaveRelated();
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
}
////////////////////////////////////////////////////////////
// GANZES MAKROPROJEKT ALS EXTERNES FILE SPEICHERN
void CSplit::OnDebugExportall() 
{
	SaveAs(CC_EXPORTALL);
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
}
////////////////////////////////////////////////////////////
// ALS EXTERNES FILE SPEICHERN
void CSplit::OnDebugSaveas()
{
	if(!SaveAs())
		return; // Cancel
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
}
///////////////////////////////////////////////////////////
// HINZUFÜGEN externes File von Platte als VERKNÜPFUNG
void CSplit::OnDebugImport()
{
	if (!Import())
		return; // false == Cancel
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
	SetFocus(); // bei Import Focus immer auf Debugger
}
////////////////////////////////////////////////////////////
// File aus Project ENTFERNEN und löschen
void CSplit::OnDebugRemove() 
{
	Remove();// SaveRelated() in Tree nach löschen
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
}
////////////////////////////////////////////////////////////
// NEUES AllgMakro zum Project hinzu
void CSplit::OnDebugInsert() 
{	// Einfügen "Neues Macro"
	// EditLabel
	// Nach Labeledit CSplit::OnDebugOpen()
	Insert();
}
////////////////////////////////////////////////////////////
// NEUE Funktion zur Datei hinzu
void CSplit::OnDebugFunctionInsert() 
{
	if (S_OK != GetDebuggerCtrl() -> CanEdit()) return;
	VERIFY(FunctionInsert());
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
	SetFocus(); // bei FunctionInsert Focus immer auf Debugger
}


////////////////////////////////////////////////////////////
// HILFE
void CSplit::OnDebugGetHelpOn()
{
	GetDebuggerCtrl() -> OnDebugGetHelpOn();	
}
void CSplit::OnDebugEditorHelp()
{
	GetDebuggerCtrl() -> OnDebugEditorHelp();
}
void CSplit::OnDebugTriasHelp()
{
	GetDebuggerCtrl() -> OnDebugTriasHelp();
}

BOOL CSplit::SaveRelated() 
{
	return GetTreeCtrl() -> OnDebugSaveRelated();
}

BOOL CSplit::Insert() 
{
	// Eventuell SuperItem laden
	if (S_OK != GetDebuggerCtrl() -> CanOpen()) return true;
	return GetTreeCtrl() -> OnDebugInsert();
}

int CSplit::MessageInsertFunction(LPCSTR lpcstrName)
{
	CString strCaption = GetDefaultName(IDS_LONGCLASSNAME);
	CString strTemplate = GetDefaultName(IDS_INSERTFUNCTION);
	char str[MAXSTRLENGTH];
	wsprintf(str, strTemplate, lpcstrName);
	return ::MessageBox(GetSafeHwnd(), str, strCaption, MB_YESNO);
}

BOOL CSplit::FunctionInsert(LPCSTR lpcstrType, 
							LPCSTR lpcstrDecl, 
							LPCSTR lpcstrName, 
							LPCSTR lpcstrParams,
							LPCSTR lpcstrComment) 
{
	if (NULL == lpcstrDecl) return true;// RAUS, keine Funktion einfügen

	LPSTR lpstrFunctionText = NULL;
	try 
	{
		HRESULT hr = GetTreeCtrl() -> InsertFunctionLoadedItem (
			lpcstrName, lpcstrDecl, lpcstrType, lpcstrParams, lpcstrComment, &lpstrFunctionText
			);
		if (E_UNEXPECTED == hr) // Extern
		{
			WTreeItem IT;
			THROW_FAILED_HRESULT(GetLoadedItem(IT.ppi()));
			WObjManHelper IOMH = IT;
			THROW_FAILED_HRESULT(IOMH -> NewFunction(
				lpcstrName, lpcstrDecl, lpcstrType, lpcstrParams, lpcstrComment,&lpstrFunctionText
				));
		}

		if (!GetDebuggerCtrl() -> OnDebugFunctionInsert(lpstrFunctionText))
			_com_issue_error(E_FAIL);
	} 
	catch (_com_error&)
	{
		if (lpstrFunctionText) { CoTaskMemFree(lpstrFunctionText); lpstrFunctionText = NULL; }
		return false;
	}

	if (lpstrFunctionText) { CoTaskMemFree(lpstrFunctionText); lpstrFunctionText = NULL; }

	return true;
}

BOOL CSplit::FunctionInsert() 
{
	CAddFunctionDlg AddFDlg;
	
	if (IDOK != AddFDlg.DoModal()) return true;

	CString strType = AddFDlg.GetType();
	CString strDecl = AddFDlg.GetDeclaration();
	CString strName = AddFDlg.GetName();
	CString strParams = AddFDlg.GetParams();
	CString strComment = AddFDlg.GetComment();
	// muss vorhanden sein
	if (strName.IsEmpty()) return true;

	return FunctionInsert(strType, strDecl, strName, strParams, strComment);
}

BOOL CSplit::Open(LPCSTR lpcstr)
{
	if (IsTreeFocused()) 
	{
		if (!OpenSelected()) 
		{
			return false;
		}
	} 
	else 
	{
		if (!OpenFile(lpcstr)) 
		{
			return false;
		}
	}
		
	return true;
}
// Aufruf nur, wenn Focus auf Tree  
BOOL CSplit::OpenSelected() 
{// Wenn in Tree Anderes als Geladenes selektiert
	if (false == GetInitNew_Selected() && (IsScript_Selected() || IsFunction_Selected())) 
	{	// Altes erstmal Speichern, 
		// nicht fragen, wenn Altes == Neues
		if (1 == Save(GetScriptName_Selected()))	// 0 ist Cancel
		{// Altes, wenn noch initneu Löschen
			if (Delete())
			{
				if (OpenOther())
				{
					return true;
				}
			}
		}
	}
	else if (GetInitNew_Selected() && IsFunction_Selected())
	{// Auch öffnen, da gültiger Code bei der Enumerierung und Erzeugung der FunctionTreeItems
	// übergeben wurde
		if (OpenOther())
		{
			return true;
		}
	}

	return false;
}

// Aufruf nur, wenn Focus auf Tree  
BOOL CSplit::ImportSelected(REFIID riid, LPCSTR lpcstr) 
{// Wenn in Tree Anderes als Geladenes selektiert
	if (IsScript_Selected()) 
	{// Altes erstmal Speichern
		if (1 == Save())	// 0 ist Cancel
		{// Altes, wenn noch initneu Löschen
			if (Delete())
			{
				if (ImportSelectedItem(riid, lpcstr))
				{
					return true;
				}
			}
		}
	}

	return false;
}

// Aufruf nur, wenn Focus nicht auf Tree  
BOOL CSplit::OpenFile(LPCSTR lpcstr)
{
CString strOpenFile (lpcstr);	// != NULL kommt von Datei öffnen aus externem Dialog

	if (strOpenFile.IsEmpty()) {
	// erstmal File geben lassen
	BOOL fLink = false;
	
		if (!IsDebuggerFocused() || 
			!FileDialog (NULL, strOpenFile, true, false, fLink))
		{
			return true;	// Cancel
		}
	}

	if (IDOK == Save())	{	// 0 ist Cancel
	// Altes, wenn noch initneu Löschen
		if (Delete())
		{
			return OpenExtern(strOpenFile);
		}
	}
	return false;
}

// Aufruf nur, wenn Focus nicht auf Tree  
BOOL CSplit::NewFile()
{
	if (1 == Save())	// 0 ist Cancel
	{// Altes, wenn noch initneu Löschen
		if (Delete())
		{
			return OpenExtern(GetDefaultName(IDS_NEWMACRO), false/*new*/);
		}
	}

	return false;
}

BOOL CSplit::Delete()
{
	try {
		if (!GetInitNew()) _com_issue_error(S_FALSE);
		if (GetTreeCtrl() -> OnDebugDeleteLoaded()) _com_issue_error(S_FALSE);
		// externes geladen da Delete(hTreeitem) fehlschlägt
		ITreeItem *pIT;
		// AddRef() (hier == 2)
		HRESULT hr = GetLoadedItem(&pIT);
		if (FAILED(hr)) _com_issue_error(hr);
		// Nun externes löschen, 
		// Macht Release() (hier == 1) auf sich selbst
		// Mit Delete() wird gewährleistet, daß pIT aus der Objektliste in der Objektverwaltung fliegt
		WObjManHelper IOMH = pIT;
		hr = IOMH -> Delete();
		if (FAILED(hr)) _com_issue_error(hr);
	} catch (_com_error& e) {
		if (FAILED(_COM_ERROR(e)))
			return false;
	}	
	return true;
}

HRESULT CSplit::DeleteLabelEdit(void)
{
	if (false == IsLabelEdit_Selected()) return S_OK;
	
	if (GetTreeCtrl() -> OnDebugRemoveSelected())
		return S_OK;	

	return E_FAIL;
}

BOOL CSplit::Remove()
{// Neues nicht löschen, wird automatisch freigegeben, wenn anderer geöffnet wird
// SaveAs() bevor löschen ?
	if (S_OK != GetDebuggerCtrl() -> CanRemove() || S_FALSE == QuerySaveAs(true)) return false; // Cancel

	WTreeItem ITSel;
	if (SUCCEEDED(GetSelectedItem(ITSel.ppi())))	
	{
		WTreeItem ITLoad;
		if (SUCCEEDED(GetLoadedItem(ITLoad.ppi())))	
		{
			if (ITLoad == ITSel)
			{// Selectiertes auch geladen, öffnen Neues									
				if (GetTreeCtrl() -> OnDebugRemoveLoaded())
					return true;
			}
			else
			{// Anderes selektiert als Geladenenes
				if (GetTreeCtrl() -> OnDebugRemoveSelected())
					return true;
			}
		}
	}
	return false;
}

HRESULT CSplit::QuerySaveAs(BOOL fRemove)
{
	int iRet = AskSaveAs(fRemove);

	switch (iRet) 
	{
	case IDYES:
		if (!SaveAs())
			return S_FALSE; // Cancel
		break;		

	case IDCANCEL:
		// nicht weitermachen, RAUS
		return S_FALSE;
		break;
	}
	// WEITER
	return NOERROR;
}

int CSplit::AskSave() 
{
	return Save();
}
BOOL CSplit::DeleteIfNew()
{
	return Delete();
}

int CSplit::Save(LPCSTR lpcstrNext)
{
	int iRet = AskSaveChanges(lpcstrNext);

	switch (iRet) 
	{
	case 0: // nicht dirty
		return 1;
		break;

	case IDYES:
		OnDebugSave();
		return 1;
		break;		

	case IDCANCEL:
		// nicht weitermachen, RAUS
		return 0;
		break;

	case IDNO:
		// nicht speichern, rücksetzen
		SetDirty(false);
		return 1;
		break;
	}

	return 1;
}

int CSplit::AskSaveAs(BOOL fRemove)
{
	CString strCaption = GetDefaultName(IDS_LONGCLASSNAME);
	CString strTemplate = GetDefaultName(IDS_SAVEASPROMPT);
	if (false == fRemove)
		strTemplate = GetDefaultName(IDS_SAVEASPROMPT2);
	return ::MessageBox(GetSafeHwnd(), strTemplate, strCaption, MB_YESNOCANCEL | MB_TASKMODAL);
}

int CSplit::AskSaveChanges (LPCSTR lpcstrNextOpen)
{
	WTreeItem IT;
	if (FAILED(GetLoadedItem(IT.ppi())))	
		return 0;
	return IT -> AskSaveChanges (GetSafeHwnd(), lpcstrNextOpen);
}

BOOL CSplit::New()
{
	try
	{
		WTreeItem IT;
		// Geladenes beibehalten
		// AddRef()
		HRESULT hr = GetLoadedItem(IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		LPSTR lpstr = NULL;
		WObjManHelper IOMH = IT;
		hr = IOMH -> New(&lpstr);
		if (FAILED(hr)) _com_issue_error(hr);
		// Text geben lassen und Dirty
		if (S_OK == hr && lpstr) // bei S_FALSE ist Geladenes InitNew
		{// Defaulttext setzen
			GetDebuggerCtrl() -> OnDebugNew(lpstr);
			return true;
		}
	}
	catch (_com_error) {	
		return false;
	}
	return false;
}

BOOL CSplit::CreateExternItem(LPCSTR lpcstr, REFIID riid, ITreeItem **ppProjScript)
{
	ASSERT(lpcstr);
	ASSERT(ppProjScript);
	if (NULL == ppProjScript) return false;
	*ppProjScript = NULL;

	ITreeItem *pProjScript = NULL;

	try
	{
		WStreamInfo ISI;
		WObjectManagement IOM;
		CDebFormView* pLeft = (CDebFormView *) m_Splitter.GetPane(0,0);
		ASSERT(pLeft);
		if (NULL == pLeft) _com_issue_error(E_POINTER);
		UINT uiManID = pLeft -> GetManID();

		if (!GetFormerManagement (uiManID, NULL, NULL, IOM.ppi(), ISI.ppi()))
			_com_issue_error(E_FAIL);

		// Erzeugen eines externen Projectscripts
		pProjScript = (ITreeItem *) new CComObject<CExternProjectScript>;
		if (NULL == pProjScript) _com_issue_error(E_POINTER);
		// Initialisierung
		((CProjectScript *)pProjScript) -> Init (IOM, ISI, riid);
		
		WObjManHelper IOMH = pProjScript;
		// Ist PERMANENT neu !!!, 
		// soll aus der Liste des Projekts wieder entfernt werden
		IOMH -> SetInitNew(true);
		IOMH -> SetParentName(lpcstr);

		WBSProperty IBSP = pProjScript;
		IBSP -> SetScriptName(lpcstr);

		pProjScript -> AddRef();
		*ppProjScript = pProjScript;
	} 
	catch (bad_alloc) 
	{
		return false;
	}
	catch (_com_error&) 
	{
		if (NULL != pProjScript)  pProjScript -> Release();
		pProjScript = NULL;
		return false;
	}
	return true;
}

HRESULT CSplit::CreateItem(LPCSTR lpcstr, REFIID riid, ITreeItem **ppProjScript)
{
	ASSERT(lpcstr);
	ASSERT(ppProjScript);
	if (NULL == ppProjScript) return E_POINTER;
	*ppProjScript = NULL;

	ITreeItem *pProjScript = NULL;

	try
	{
		WStreamInfo ISI;
		HRESULT hr = GetInfoGeneralScripts(ISI.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		WObjectManagement IOM;
		hr = GetGeneralScripts(IOM.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		// Erzeugen eines externen Projectscripts
		pProjScript = (ITreeItem *) new CComObject<CProjectScript>;
		if (NULL == pProjScript) _com_issue_error(E_POINTER);
		// Initialisierung
		((CProjectScript *)pProjScript) -> Init (IOM, ISI, riid);
		
		WObjManHelper IOMH = pProjScript;
		IOMH -> SetParentName(lpcstr);

		WBSProperty IBSP = pProjScript;
		IBSP -> SetScriptName(lpcstr);

		pProjScript -> AddRef();
		*ppProjScript = pProjScript;
	} 
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	}
	catch (_com_error& e) 
	{
		RELEASE(pProjScript);
		return _COM_ERROR(e);
	}
	return S_OK;
}

BOOL CSplit::OpenExtern(LPCSTR lpcstr, BOOL fOpen)
{
	BOOL fResult = true;
	WTreeItem IT;

	try
	{	// Ein Item extern erzeugen					
		if (!CreateExternItem(lpcstr, CLSID_FileScript, IT.ppi())) _com_issue_error(E_FAIL);
		if (!GetTreeCtrl() -> OnDebugOpen(false)) _com_issue_error(E_FAIL);
		// Öffnet TreeItem und setzt Debugger
		LPSTR lpstr = NULL;
		ebHCODE hCode = NULL;
		if (fOpen) {
			if (!OpenItem(IT, &hCode, &lpstr)) _com_issue_error(E_FAIL);
		} else {
			if (!NewItem(IT, &lpstr)) _com_issue_error(E_FAIL);
		}
		SetLoadedItem(IT); // AddRef() == 1 nach dieser Funktion		
		GetDebuggerCtrl() -> OnDebugOpen(lpstr, hCode);	
		// Hinzufügen dieses Items zur MRU-Liste
		AddNewItem (m_pMRUMenu, GetScriptName());					
		PlaceMenuMRUItem (m_pMRUMenu, ::GetSubMenu(::GetMenu(m_hWnd), 0), IDM_CLOSE);// refresh MRUMenu
	}
	catch (_com_error)
	{
		WObjManHelper IOMH = IT;
		IOMH -> AddRef(); // da nochmal WTreeItem -> Release() bei out of scope, (detach() ?)
		IOMH -> Delete(); // Release() auf sich selbst und aus Objektverwaltung entfernen
		fResult = false;
	}
// WTreeItem -> Release()
	return fResult;
}

BOOL CSplit::OpenOther(void)
{
	LPSTR lpstr = NULL;
	ebHCODE hCode = NULL;
	try
	{	// selektiertes Item geben lassen
		// AddRef()
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetSelectedItem(IT.ppi()));
		if (!GetTreeCtrl() -> OnDebugOpen()) _com_issue_error(E_FAIL);
		// Öffnet TreeItem und setzt Debugger				
		if (!OpenItem(IT, &hCode, &lpstr)) _com_issue_error(E_FAIL);
		// Auch in MRU !
		SetLoadedItem(IT); // AddRef()	== 1 nach dieser Funktion	
		GetDebuggerCtrl() -> OnDebugOpen(lpstr, hCode);	// SetDebuggerScript		return true;
	}
	catch(_com_error&)
	{
		return false;
	}
	return true;
} 

BOOL CSplit::ImportSelectedItem(REFIID riid, LPCSTR lpcstr)
{
	try
	{	// selektiertes Item geben lassen
		// AddRef()
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetSelectedItem(IT.ppi()));

		if (!GetTreeCtrl() -> OnDebugOpen()) _com_issue_error(E_FAIL);

		// Öffnet TreeItem und setzt Debugger
		LPSTR lpstrText = NULL;
		ebHCODE hCode = NULL;
		if (!ImportItem(IT, riid, lpcstr, &hCode, &lpstrText)) _com_issue_error(E_FAIL);

		THROW_FAILED_HRESULT(GetTreeCtrl() -> CreateSubItems(lpcstr, CLSID_Script));

		SetLoadedItem(IT); // AddRef()	== 1 nach dieser Funktion	
		GetDebuggerCtrl() -> OnDebugOpen(lpstrText, hCode);	// SetDebuggerScript		return true;				
	}
	catch (_com_error&)
	{
		return false;
	}
	return true;
} // WTreeItem -> Release()

BOOL CSplit::OpenFromMRU (UINT uiID)
{
	LPSTR lpstr = NULL;
	ebHCODE hCode = NULL;		
	WTreeItem IT;
	try
	{// aus der MRU besorgen
		char FileName [_MAX_PATH];
		if (!GetMenuItem (m_pMRUMenu, uiID, true, FileName, _MAX_PATH)) _com_issue_error(E_FAIL);
		// Ein Item extern erzeugen, AddRef()
		if (!CreateExternItem(FileName, CLSID_FileScript, IT.ppi())) _com_issue_error(E_FAIL);
		// kein selektiertes Item im Tree
		if (!GetTreeCtrl() -> OnDebugOpen(false)) _com_issue_error(E_FAIL);
		// Öffnet TreeItem und setzt Debugger
		if (!OpenItem(IT, &hCode, &lpstr)) _com_issue_error(E_FAIL);
		// Als geladen kennzeichnen
		SetLoadedItem(IT); // AddRef()	== 1 nach dieser Funktion	
		GetDebuggerCtrl() -> OnDebugOpen(lpstr, hCode);	// SetDebuggerScript		return true;					
	}
	catch (_com_error&)
	{
		try {
			WObjManHelper IOMH = IT;
			IOMH -> AddRef(); // da nochmal WTreeItem -> Release() bei out of scope
			IOMH -> Delete(); // Release() auf sich selbst, auch aus der Objektverwaltung entfernen
		} catch (_com_error &) {
			;
		}
		// Löschen von MRU-Liste
		DelMenuItem (m_pMRUMenu, uiID, true);
		PlaceMenuMRUItem (m_pMRUMenu, ::GetSubMenu(::GetMenu(m_hWnd), 0), IDM_CLOSE);// refresh MRUMenu

		if (lpstr) CoTaskMemFree(lpstr); lpstr = NULL;
		if (hCode) CoTaskMemFree(hCode); hCode = NULL;
		return false;
	}
	return true;
}

BOOL CSplit::IsTreeFocused()
{
CWnd *pWnd = GetFocus();

	if (NULL == pWnd) return false;
	if (!::IsWindow(pWnd->m_hWnd)) return false;

CWnd *pTreeWnd = (CWnd *)GetTreeCtrl();

	ASSERT(NULL != pTreeWnd);
	ASSERT(::IsWindow(pTreeWnd->m_hWnd));

CWnd *pDebWnd = (CWnd *)GetDebuggerCtrl();

	ASSERT(NULL != pDebWnd);	
	ASSERT(::IsWindow(pDebWnd->m_hWnd));
	
	if (NULL == pWnd -> GetParent()) 
		return false;

	if (pWnd == pTreeWnd || pWnd -> GetParent() == pTreeWnd)
		return true;
	
	return false;
}

BOOL CSplit::IsDebuggerFocused()
{
	CWnd *pWnd = GetFocus();
	CWnd *pDebWnd = (CWnd *)GetDebuggerCtrl();
	
	ASSERT(NULL != pWnd);
	ASSERT(NULL != pDebWnd);
	ASSERT(::IsWindow(pWnd->m_hWnd));
	ASSERT(::IsWindow(pDebWnd->m_hWnd));
	ASSERT(NULL != pWnd -> GetParent());

	if (pWnd == pDebWnd || pWnd -> GetParent() == pDebWnd)
		return true;
	
	return false;
}

BOOL CSplit::OpenItem(ITreeItem *pITreeItem, ebHCODE *phCode, LPSTR *lplpstr)
{
	ASSERT(pITreeItem);
	ASSERT(phCode);
	ASSERT(lplpstr);
	if (NULL == pITreeItem || NULL == phCode || NULL == lplpstr) return false;

	*phCode = NULL;
	*lplpstr = NULL;

LPSTR *lplpstrRel = NULL;
UINT ui = 0;				// Bei FunctionLevel alten Text vom Script belassen
BOOL fResult = TRUE;

	try	{
	WObjManHelper IOMH (pITreeItem);

	// Wenn dirty, würde sonst File überaschrieben werden
		if (IOMH -> GetDirty()) 
			return TRUE;

	HRESULT hr = IOMH -> Open(lplpstr, phCode, &lplpstrRel, ui);	// Text, Code, StringListe geben lassen

		if (SUCCEEDED(hr) && !GetInitNew_Selected()) {
			hr = MessageNoText (GetSafeHwnd(), *lplpstr);
			if (FAILED(hr)) 
				fResult = FALSE;
		}
	}
	catch (_com_error&)
	{
		fResult = FALSE;
	}

	MEMFREE(lplpstrRel, ui);	// Stringliste wird an dieser Stelle nicht benötigt
	return fResult;
}

BOOL CSplit::NewItem(ITreeItem *pITreeItem, LPSTR *lplpstr)
{
	ASSERT(pITreeItem);
	ASSERT(lplpstr);
	if (NULL == pITreeItem || NULL == lplpstr) 
		return false;

	*lplpstr = NULL;
	try	{
	WObjManHelper IOMH = pITreeItem;
	
		if (FAILED(IOMH -> New (lplpstr)))	// Text, Code, StringListe geben lassen
			return FALSE;
	}
	catch (_com_error&)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CSplit::ImportItem(ITreeItem *pITreeItem, REFIID riid, LPCSTR lpcstrImport, ebHCODE *phCode, LPSTR *lplpstr)
{
	ASSERT(lpcstrImport);
	ASSERT(pITreeItem);
	ASSERT(phCode);
	ASSERT(lplpstr);
	if (NULL == pITreeItem || NULL == phCode || NULL == lplpstr || NULL == lpcstrImport) 
		return FALSE;

BOOL fResult = TRUE;

	*phCode = NULL;
	*lplpstr = NULL;

	LPSTR *lplpstrRel = NULL;
	UINT ui = 0;	// Bei FunctionLevel alten Text vom Script belassen
	try	{
	WObjManHelper IOMH = pITreeItem;
	
		THROW_FAILED_HRESULT(IOMH -> Import(riid, lpcstrImport, lplpstr, phCode, &lplpstrRel, ui));	// Text, Code, StringListe geben lassen
	}
	catch (_com_error&)
	{
		fResult =  false;
	}
	MEMFREE(lplpstrRel, ui);// Stringliste wird an dieser Stelle nicht benötigt
	return fResult;
}

BOOL CSplit::SaveLoaded(BOOL fOnImport)
{
	BOOL fResult = true;
	LPSTR pText = NULL;
	ebHCODE  hCode = NULL;
	LPSTR *lplpstr = NULL;
	UINT uiCnt = 0;
	DWORD dwSaveFlag = 0;

	try {	// Code und Text kommen aus Debugger
		if (!GetDebuggerCtrl() -> OnDebugSave(&pText, &hCode, dwSaveFlag)) _com_issue_error(E_FAIL);
	
	// Related Scripts kommen aus Tree
		if (!GetTreeCtrl() -> OnDebugSave(&lplpstr, uiCnt)) _com_issue_error(E_FAIL);
	
	// Treeitem geben lassen
	WTreeItem IT;
	HRESULT hr = GetLoadedItem(IT.ppi());
	
		if (FAILED(hr)) _com_issue_error(hr);
	
	// Bei Import ALLES MIT HEADER wegspeichern
		if (fOnImport) 
			dwSaveFlag |= CC_IMPORT;
	
	WObjManHelper IOMH = IT;
	
		if (FAILED(IOMH -> Save(pText, hCode, lplpstr, uiCnt, dwSaveFlag)))
		{// Bei neuem Externen existiert noch kein File, also erst eines erzeugen und unter neuen Namen abspeichern
			if (!SaveAs())  _com_issue_error(E_FAIL);
		}
	}
	catch (_com_error&)
	{
		fResult = false;
	}

	if (pText) CoTaskMemFree(pText); pText = NULL;
	MEMFREE(lplpstr, uiCnt);

	return fResult;
}

BOOL CSplit::Import()
{
	if (S_OK != GetDebuggerCtrl() -> CanOpen()) return true;
// OpenDialog, TreeItem erzeugen, Import, Selektieren, OndebugOpen
	CString strOpenFile;
	BOOL fLink = false;// File nur als Link importieren ?
	if (FileDialog (NULL, strOpenFile, false, true,	fLink))	
	{
		if (!fLink)
		{
			if (GetTreeCtrl() -> OnDebugImportInProject(strOpenFile))
			{// Alles OK
				VERIFY(ImportSelected(CLSID_FileScript, strOpenFile)); // selektiertes in eben erzeugtes Item importieren
				VERIFY(SaveLoaded(true)); // nicht aus der Objectliste löschen
				SaveRelated();			
			}
		}
		else 
		{
			if (GetTreeCtrl() -> OnDebugImport(strOpenFile))
			{// Alles OK
				VERIFY(OpenSelected()); // selektiertes öffnen
				// true: Alles wegspeichern MIT Header
				VERIFY(SaveLoaded(true)); // nicht aus der Objectliste löschen
				// Speicherung der Related in Tree, da SUPER-Item gespeichert werden muss, 
				// das nicht in CSplit (MainFrame) bekannt ist
				SaveRelated();			
			}
		}
	}

	return true;
}


HRESULT CSplit::ImportAll() 
{
	CString strFileName = GetScriptName();
	BOOL fLink = false;

UINT uiSave = FileDialog (NULL, strFileName, true, false, fLink);

	if (0 == uiSave) 
		return S_FALSE;		// Cancel
	if (strFileName.IsEmpty()) 
		return E_UNEXPECTED;
	
	if (GetTreeCtrl() -> OnDebugImportAllInProject(strFileName))
	{// Alles OK
		VERIFY(ImportSelected(CLSID_ExportImportProject, strFileName)); // selektiertes in eben erzeugtes Item importieren
		VERIFY(SaveLoaded(true)); // nicht aus der Objectliste löschen
		//SaveRelated();			
	}
	return S_OK;
}

BOOL CSplit::SaveAs(DWORD dSaveOptions)
{
CString strFileName = GetScriptName();
BOOL fLink = false;
UINT uiSave = FileDialog (NULL, strFileName, false, false, fLink);

	if (0 == uiSave) 
		return false; // Cancel
	if (strFileName.IsEmpty()) 
		return false;

	if (IsTreeFocused()) {
		if (SaveAsSelected(uiSave, strFileName, dSaveOptions))
			return true;
	} else {
		return SaveAsLoaded(uiSave, strFileName, dSaveOptions);
	}

	return false;
}

BOOL CSplit::SaveAsLoaded(UINT uiSave, LPCSTR lpcstr, DWORD dSaveOptions)
{
	BOOL fResult = true;
	LPSTR pText = NULL;
	ebHCODE  hCode = NULL;
	LPSTR *lplpstr = NULL;
	UINT uiCnt = 0;

	try
	{
		ASSERT_THROW_INVALIDSTRING(lpcstr);
		// Code und Text kommen aus Debugger
		if (!GetDebuggerCtrl() -> OnDebugSave(&pText, &hCode, dSaveOptions)) _com_issue_error(E_FAIL);
		// Related Scripts kommen aus Tree
		if (CC_EXPORTALL & dSaveOptions)
		{
			if (!GetTreeCtrl() -> OnDebugSave(&lplpstr, uiCnt)) _com_issue_error(E_FAIL);
		}
		
		WTreeItem IT;
		HRESULT hr = GetLoadedItem(IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		/////////////
		// Abspeichern an sich
		THROW_FAILED_HRESULT(SaveAs(IT, uiSave, lpcstr, hCode, pText, lplpstr, uiCnt, dSaveOptions));
	}
	catch (_com_error&)
	{
		fResult = false;
	}
	COTASKMEMFREE(pText);
	MEMFREE(lplpstr, uiCnt);
	return fResult;
}
 
BOOL CSplit::SaveAsSelected(UINT uiSave, LPCSTR lpcstr, DWORD dSaveOptions)
{
	ASSERT(lpcstr);

	BOOL fResult = true;
	LPSTR *lplpstr = NULL;
	UINT uiCnt = 0;

	try
	{
		ASSERT_THROW_INVALIDSTRING(lpcstr);

		// Entsprechendes Item zum Exportieren geben lassen
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetTreeCtrl() -> GetItemForExport(IT.ppi(), dSaveOptions));
		// Text und Code, da nicht im Debugger, von Platte laden
		dSaveOptions |= GETFROMDISC;
		/////////////
		// Abspeichern an sich
		THROW_FAILED_HRESULT(SaveAs(IT, uiSave, lpcstr, NULL, NULL, NULL, 0, dSaveOptions));
	}
	catch(_com_error&)
	{
		fResult = false;
	}
	return fResult;
}

HRESULT CSplit::SaveAs(
					ITreeItem *pIT, 
					UINT uiSave, 
					LPCSTR lpcstr, 
					ebHCODE hCode, 
					LPSTR lpstrText, 
					LPSTR *lplpstr, 
					UINT uiCnt, 
					DWORD dwSaveFlag)
{
	ASSERT(pIT);
	ASSERT(lpcstr);
	if (NULL == pIT || NULL == lpcstr) return E_POINTER;

	try
	{
		CString strFileName = lpcstr;		
		dwSaveFlag |= CC_EXPORT;

		switch (uiSave) 
		{
			case 1: // Text
				if (dwSaveFlag & CC_CODE) 
					dwSaveFlag &= ~CC_CODE;
				dwSaveFlag |= CC_SCRIPT;
				break;
			case 2: // alles
				dwSaveFlag |= CC_SCRIPT | CC_CODE;
				break;
			case 3: // Code
				dwSaveFlag |= CC_CODE;
				break;
		}
		ASSERT(!strFileName.IsEmpty());
		if (strFileName.IsEmpty()) _com_issue_error(E_FAIL);

		// Text und Code, da nicht im Debugger, von Platte laden
		WObjManHelper IOMH = pIT;
		THROW_FAILED_HRESULT(IOMH -> SaveAs(strFileName, lpstrText, hCode, lplpstr, uiCnt, dwSaveFlag));
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CSplit::EnumFunctions(HTREEITEM hItem)
{// Von aussen aus Debugger nach z.B. Compile oder Tree nach Expanding
	return GetTreeCtrl() -> EnumFunctions(hItem);
}

BOOL CSplit::GenerateCaption (LPSTR lpstr)
{
	CString strCaption, strAppName, strContainerText, strName; 
	char *pCaption = NULL;

	try {
		pCaption = strCaption.GetBuffer (_MAX_PATH);
		if (pCaption == NULL) return false;
	}
	catch (CMemoryException) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  

	if (lpstr)
		strName = lpstr;
	else
		strName = GetScriptName();
	strAppName = GetDefaultName(IDS_LONGCLASSNAME);

	if (strName.IsEmpty())
	{// für Initfirst
		strName = GetDefaultName(IDS_UNTITLED);
		strContainerText = GetDefaultName(IDS_UNTITLED);
		wsprintf (pCaption, "%s - %s [%s%s]", strAppName, strContainerText, strName, g_cbNil);
	}
	else
	{// eventuell Filenamen geben lassen, da im Object vollständiger Pfad abgespeichert ist
		//strName = GetFileName(strName, true);
		ASSERT(!strName.IsEmpty());
		if (GetParentName().IsEmpty())// Externes
			wsprintf (pCaption, "%s - %s%s", strAppName, strName, GetDirty() ? "*" : g_cbNil);
		else
		{
			strContainerText = GetParentName();
			strContainerText = GetFileName(strContainerText, false);
			ASSERT(!strContainerText.IsEmpty());
			wsprintf (pCaption, "%s - %s [%s%s]", strAppName, strContainerText, strName, GetDirty() ? "*" : g_cbNil);
		}	

	}	
	// eigentliche Caption setzen
	SetWindowText (pCaption);

	return true;
}

BOOL CSplit::SetReadyStatusbarText()
{
	CString str;
	str = GetDefaultName(ID_STATUSBAR_PANE1);
	GetStatusbar() -> SetPaneText (0, str, true);		
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////
// Settings aus Registry lesen, in Registry schreiben
BOOL CSplit::SaveRegSettingsWindow()
{
	if (IsIconic() ||  IsZoomed())
		return true;

	RECT Rect;

	GetWindowRect (&Rect);
	
	if (!SaveRegSettingsWindow(g_cbWindow, Rect))
		return false;

	memset(&Rect, 0, sizeof(Rect));
	CDebFormView* pLeft = (CDebFormView *) m_Splitter.GetPane(0,0);
	pLeft -> GetWindowRect (&Rect);

	if (!SaveRegSettingsWindow(g_cbTreeWindow, Rect))
		return false;

	memset(&Rect, 0, sizeof(Rect));
	CDebFormView2* pRight = (CDebFormView2 *) m_Splitter.GetPane(0,1);
	pRight -> GetWindowRect (&Rect);

	return SaveRegSettingsWindow(g_cbDebuggerWindow, Rect);
}

BOOL CSplit::ReadRegSettingsWindow (RECT *pRect, RECT *pRectDebugger, RECT *pRectTree)
{
	if (!ReadRegSettingsWindow (g_cbWindow, pRect))
	{
		pRect->bottom = 300;
		pRect->top = 100;
		pRect->left = 100;
		pRect->right = 300;
	}

	if (!ReadRegSettingsWindow (g_cbDebuggerWindow, pRectDebugger))
	{
		pRectDebugger->bottom = 300;
		pRectDebugger->top = 100;
		pRectDebugger->left = 100;
		pRectDebugger->right = 300;
	}
	
	if (!ReadRegSettingsWindow (g_cbTreeWindow, pRectTree))
	{
		pRectTree->bottom = 200;
		pRectTree->top = 100;
		pRectTree->left = 100;
		pRectTree->right = 200;
	}

	return true;
}

BOOL CSplit::SaveRegSettingsWindow(LPCSTR lpstrKey, RECT & Rect)
{ 
	ASSERT(lpstrKey);

char cBuffer[MAXSTRLENGTH];
CCurrentUser regBS (g_cbCfgKey);

// framewindow information
	wsprintf(cBuffer, g_cbWindowFmt, Rect.bottom, Rect.top, Rect.left, Rect.right);
	return regBS.SetSubSZ (lpstrKey, cBuffer);	// save in reg file...
}                                         

BOOL CSplit::ReadRegSettingsWindow (LPCSTR lpcstrKey, RECT *pRect)
{
	ASSERT(lpcstrKey);

char cBuffer[MAXSTRLENGTH];
CCurrentUser regBS (KEY_READ, g_cbCfgKey);
DWORD dwL = MAXSTRLENGTH;

	if (!regBS.GetSubSZ (lpcstrKey, cBuffer, dwL))
		return false;
	return ParseRectangleInfo (cBuffer, pRect); 
}

BOOL CSplit::ParseRectangleInfo (LPSTR pInfo, RECT *pRect)
{
	if (pInfo == NULL || *pInfo == '\0') return false;
	if(pRect == NULL) return false;

		// Lesen DebuggerCtrl
	char *pStr = strtok (pInfo, g_cbFmtDel);
	if (NULL == pStr) return false;
	pRect -> bottom = atoi (pStr);
	
	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pRect -> top = atoi (pStr);
	
	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pRect -> left = atoi (pStr);
	                                                  
	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pRect -> right = atoi (pStr);               

return true;
}

UINT CSplit::FileDialog (LPCSTR pcPath, CString & strFileName, BOOL fOpen, BOOL fImport, BOOL & fLink) 
{
UINT ui = 0;
char cbPath[_MAX_PATH]; 
CWnd *pFocusWnd = GetFocus();

	ASSERT(NULL != pFocusWnd);

	if (NULL == pcPath) {
		cbPath[0] = '\0';
		ReadRegSettingsLastOpenFile (cbPath, _MAX_PATH);
	} else
		strcpy (cbPath, pcPath);
	
	if (fOpen || fImport) {
		strFileName.Empty();
		ui = OpenFileDialog (cbPath, strFileName, fLink);
	}
//	else if (fOpen || fImport) {
//		strFileName.Empty();
//		ui = FileDialog (strFileName);				// File Öffnen
//	}
	else {
	CString str (GetDefaultName(IDS_SAVEAS));

		ui = FileDialog (cbPath, strFileName, false, str);	// File Speichern
	}

	SaveRegSettingsLastOpenFile(GetPathName (strFileName));
	if (!Enable())
		return 0;

	::SetFocus(pFocusWnd -> GetSafeHwnd());
	return ui;
}

UINT CSplit::OpenFileDialog (LPCSTR pcPath, CString &strFileName, BOOL &fLink) 
{
LPSTR lpstrFilters = NULL;
LPSTR lpstrExt = NULL;

	try {
	WTreeItem IT;
		THROW_FAILED_HRESULT(GetLoadedItem(IT.ppi()));
		WObjManHelper IOMH = IT;
		THROW_FAILED_HRESULT(IOMH->GetSaveAsFilters(&lpstrFilters));
		THROW_FAILED_HRESULT(IOMH->GetFileExt(&lpstrExt));
	}
	catch(_com_error&)
	{	
		COTASKMEMFREE(lpstrFilters);
		COTASKMEMFREE(lpstrExt);
		return 0;
	}

// Zusätzlichen Linkbutton einfügen
LPSTR lpTemplateName = MAKEINTRESOURCE(IDD_FILEDLG);
HINSTANCE hInst = AfxFindResourceHandle(lpTemplateName, RT_DIALOG);

	if (hInst == NULL) return 0;

DWORD dwFlags = OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_ENABLETEMPLATE|OFN_EXPLORER|OFN_LONGNAMES;

#if defined(OFN_ENABLESIZING)
	if (IsWin41() || (IsWin50() && IsWinNT())) {
		dwFlags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
		dwFlags |= OFN_DONTADDTORECENT;
#endif // defined(OFN_DONTADDTORECENT)
	}
#endif // defined(OFN_ENABLESIZING)

CDebFileDialog SDlg (true, lpstrExt, NULL, dwFlags, lpstrFilters, this);

	COTASKMEMFREE(lpstrFilters);
	COTASKMEMFREE(lpstrExt);

// ChildTemplate setzen
	SDlg.m_ofn.hInstance = hInst;
	SDlg.m_ofn.lpTemplateName = lpTemplateName;
	SDlg.m_ofn.lpstrInitialDir = pcPath;

	if (SDlg.DoModal() == IDOK) {
		strFileName = SDlg.GetPathName();
		fLink = SDlg.GetLink();
		return 1;
	}
	return 0;
}

BOOL CSplit::Enable()
{
	if (::GetActiveWindow() == m_hWnd)
	{
		SendMessage(WM_ACTIVATE, WA_ACTIVE);
		SendMessage(WM_NCACTIVATE, TRUE);
		return true;
	}

	return false;
}

HRESULT CSplit::GetGeneralScripts(IObjectManagement **ppIObj)
{
	IObjectManagement *pIObj = g_pBSE -> GetGeneralScripts();
	ASSERT(pIObj);
	if (pIObj) 
	{
		*ppIObj = pIObj;
		(*ppIObj) -> AddRef();
		return NOERROR;
	}
	return E_FAIL;
}

HRESULT CSplit::GetInfoGeneralScripts(IStreamInfo **ppISI)
{
	IStreamInfo *pISI = g_pBSE -> GetInfoGeneralScripts();
	ASSERT(pISI);
	if (pISI) 
	{
		*ppISI = pISI;
		(*ppISI) -> AddRef();
		return NOERROR;
	}
	return E_FAIL;
}

HRESULT CSplit::GetFilterScripts(IObjectManagement **ppIObj)
{
	IObjectManagement *pIObj = g_pBSE -> GetFilterScripts();
	ASSERT(pIObj);
	if (pIObj) 
	{
		*ppIObj = pIObj;
		(*ppIObj) -> AddRef();
		return NOERROR;
	}
	return E_FAIL;
}

HRESULT CSplit::GetInfoFilterScripts(IStreamInfo **ppISI)
{
	IStreamInfo *pISI = g_pBSE -> GetInfoFilterScripts();
	ASSERT(pISI);
	if (pISI) 
	{
		*ppISI = pISI;
		(*ppISI) -> AddRef();
		return NOERROR;
	}
	return E_FAIL;
}

HRESULT CSplit::GetObjFeatScripts(IObjectManagement **ppIObj)
{
	IObjectManagement *pIObj = g_pBSE -> GetObjectFeatureScripts();
	ASSERT(pIObj);
	if (pIObj) 
	{
		*ppIObj = pIObj;
		(*ppIObj) -> AddRef();
		return NOERROR;
	}
	return E_FAIL;
}

HRESULT CSplit::GetInfoObjFeatScripts(IStreamInfo **ppISI)
{
	IStreamInfo *pISI = g_pBSE -> GetInfoObjFeatureScripts();
	ASSERT(pISI);
	if (pISI) 
	{
		*ppISI = pISI;
		(*ppISI) -> AddRef();
		return NOERROR;
	}
	return E_FAIL;
}

//
// *** wenn der Debugger läuft !!! ***
//
HRESULT CSplit::RunThread(LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	return GetDebuggerCtrl() -> RunThread(pEntry, iNumParams, pPars);
}

HRESULT CSplit::EntryExists (LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	return GetDebuggerCtrl() -> EntryExists (pEntry, iNumParams, pPars);
}

HRESULT CSplit::RunModal()
{
	return GetDebuggerCtrl() -> RunModal();
}
///////////////////////////////////////////////////
// Wenn Projekt geschlossen rufen
HRESULT CSplit::ResetDebuggerIfOnClose()
{// Alle Einträge löschen
	if (g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject()) return E_UNEXPECTED;

// Management zurücksetzen
	ResetItems();
	GetTreeCtrl() -> ResetIfOnClose();
	GetDebuggerCtrl() -> ResetIfOnClose();
	// Hier wird sich auch der nächste StartID gemaerkt
	ResetTreeViewIfOnClose();
	m_strStartScript = GetScriptName();
	return S_OK;
}

BOOL CSplit::IsRBTreeMenu()
{
	return GetTreeCtrl() -> IsRBTreeMenu();
}

void CSplit::SetRBTreeMenu(BOOL f)
{
	GetTreeCtrl() -> SetRBTreeMenu(f);
}

HRESULT MessageNew(HWND hWnd)
{
	CString str = GetDefaultName(IDS_NEWSCRIPT);
	CString strApp = GetDefaultName(IDS_LONGCLASSNAME);

	if (IDOK == ::MessageBox (hWnd, str, strApp, MB_OKCANCEL | MB_ICONINFORMATION))
		return S_OK; 

	return E_ABORT;
}
HRESULT MessageNoText(HWND hWnd, LPCSTR lpcstr)
{
	if (NULL != lpcstr) return S_OK;

	CString str = GetDefaultName(IDS_CODEONLY);
	CString strApp = GetDefaultName(IDS_LONGCLASSNAME);

	::MessageBox (hWnd, str, strApp, MB_OK | MB_ICONINFORMATION);
	return E_ABORT;
}
HRESULT MessageLink(HWND hWnd) 
{
	CString str = GetDefaultName(IDS_CREATELINK);
	CString strApp = GetDefaultName(IDS_LONGCLASSNAME);
	UINT uiRes = 0;

	uiRes = ::MessageBox (hWnd, str, strApp, MB_YESNOCANCEL | MB_ICONQUESTION);
	
	if (uiRes == IDYES)
		return S_OK; 
	else if (uiRes == IDNO)
		return S_FALSE;

	return E_ABORT;
}

// global: wird mehrmals genutzt
UINT CSplit::FileDialog (LPCSTR pcPath, CString &strFileName, BOOL fOpen, LPCSTR lpcstrCaption) 
{
LPSTR lpstrFilters = NULL;
LPSTR lpstrExt = NULL;

	try	{
	WTreeItem IT;
	
		THROW_FAILED_HRESULT(GetLoadedItem(IT.ppi()));
	
	WObjManHelper IOMH (IT);
	
		THROW_FAILED_HRESULT(IOMH->GetSaveAsFilters(&lpstrFilters));
		THROW_FAILED_HRESULT(IOMH->GetFileExt(&lpstrExt));
	}
	catch(_com_error&) {	
		COTASKMEMFREE(lpstrFilters);
		COTASKMEMFREE(lpstrExt);
		return 0;
	}

UINT ui = 0;
DWORD dwFlags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST|OFN_CREATEPROMPT;

#if defined(OFN_ENABLESIZING)
	if (IsWin41() || (IsWin50() && IsWinNT())) {
		dwFlags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
		dwFlags |= OFN_DONTADDTORECENT;
#endif // defined(OFN_DONTADDTORECENT)
	}
#endif // defined(OFN_ENABLESIZING)

CDebFileDialog SDlg (fOpen, lpstrExt, strFileName, dwFlags, lpstrFilters, this, lpcstrCaption);

	SDlg.m_ofn.lpstrInitialDir = pcPath;

	COTASKMEMFREE(lpstrFilters);
	COTASKMEMFREE(lpstrExt);
	if (SDlg.DoModal() == IDOK) 
	{
		strFileName = SDlg.GetPathName();
		if (false == fOpen)// SaveFileDialog
			ui = SDlg.m_ofn.nFilterIndex; 
		else
			ui = 1;
	}

	return ui;
}

void CSplit::OnCombo() 
{
	CString strType, strDecl, strName, strParams, strComment;
	// Funktionselemente geben lassen
	if (!m_wndNotifBar.OnSelChange(strType, strDecl, strName, strParams, strComment))
		return;
	// nochmal fragen
	if (IDYES != MessageInsertFunction(strName)) return;
	// Funktion einfügen
	VERIFY(FunctionInsert(strType, strDecl, strName, strParams, strComment));
	VERIFY(GenerateCaption());
	SetReadyStatusbarText();
	SetFocus(); // bei FunctionInsert Focus immer auf Debugger
}

void CSplit::OnViewProjectbar() 
{
	// toggle visible state
	m_wndProjectToolBar.ShowWindow((m_wndProjectToolBar.GetStyle() & WS_VISIBLE) == 0);
	RecalcLayout();
}

void CSplit::OnUpdateViewProjectbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndProjectToolBar.GetStyle() & WS_VISIBLE) != 0);	
}

void CSplit::OnViewDebuggerbar() 
{
	// toggle visible state
	m_wndToolBar.ShowWindow((m_wndToolBar.GetStyle() & WS_VISIBLE) == 0);
	RecalcLayout();
}

void CSplit::OnUpdateViewDebuggerbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndToolBar.GetStyle() & WS_VISIBLE) != 0);	
}

void CSplit::OnViewNotificationbar() 
{
	// toggle visible state
	m_wndNotifBar.ShowWindow((m_wndNotifBar.GetStyle() & WS_VISIBLE) == 0);
	RecalcLayout();	
}

void CSplit::OnUpdateViewNotificationbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndNotifBar.GetStyle() & WS_VISIBLE) != 0);	
}

void CSplit::OnViewStatusbar() 
{
	// toggle visible state
	m_wndStatusBar.ShowWindow((m_wndStatusBar.GetStyle() & WS_VISIBLE) == 0);
	RecalcLayout();		
}

void CSplit::OnUpdateViewStatusbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndStatusBar.GetStyle() & WS_VISIBLE) != 0);	
}


void CSplit::OnSelTabGeneral()
{
	COM_TRY {
	WStreamInfo ISI;
	WObjectManagement IOM;

		THROW_FAILED_HRESULT(GetInfoGeneralScripts(ISI.ppi()));
		THROW_FAILED_HRESULT(GetGeneralScripts(IOM.ppi()));
		Init(NULL, false, IOM, ISI);

		SetDebuggerIcon (IDI_MACRO_DEFAULT);
	} COM_CATCH_NORETURN;
}

void CSplit::OnSelTabFilter()
{
	COM_TRY {
	WStreamInfo ISI;
	WObjectManagement IOM;

		THROW_FAILED_HRESULT(GetInfoFilterScripts(ISI.ppi()));
		THROW_FAILED_HRESULT(GetFilterScripts(IOM.ppi()));
		Init(NULL, false, IOM, ISI);

		SetDebuggerIcon (IDI_MACRO_DEFAULT_PROPACT);
	} COM_CATCH_NORETURN;
}

void CSplit::OnSelTabObjFeat()
{
	COM_TRY {
	WStreamInfo ISI;
	WObjectManagement IOM;

		THROW_FAILED_HRESULT(GetInfoObjFeatScripts(ISI.ppi()));
		THROW_FAILED_HRESULT(GetObjFeatScripts(IOM.ppi()));
		Init(NULL, false, IOM, ISI);

		SetDebuggerIcon (IDI_MACRO_DEFAULT_OBJPROP);
	} COM_CATCH_NORETURN;
}

BOOL CSplit::ModifyImportInsertMenu_ObjFeat()
{
	return ModifyMenu(
			ID_DEBUG_FILTERIMPORT,	// erster Versuch
			ID_DEBUG_IMPORT,		// zweiter Versuch 
			ID_DEBUG_OBJFEATIMPORT	// wird ersetzt durch
			);
}

BOOL CSplit::ModifyImportInsertMenu_Filter()
{
	return ModifyMenu(
			ID_DEBUG_IMPORT, 
			ID_DEBUG_OBJFEATIMPORT, 
			ID_DEBUG_FILTERIMPORT);
}

BOOL CSplit::ModifyImportInsertMenu_General()
{
	return ModifyMenu(
			ID_DEBUG_FILTERIMPORT, 
			ID_DEBUG_OBJFEATIMPORT, 
			ID_DEBUG_IMPORT);
}

BOOL CSplit::ModifyMenu(UINT uiIDTest1, UINT uiIDTest2, UINT uiNewID)
{
CMenu* pMenu = GetMenu();

	ASSERT(NULL != pMenu);
	if (NULL == pMenu) return false;

// erst den einen testen, dann den anderen
	if (!pMenu -> ModifyMenu(uiIDTest1, uiNewID))
	{
		if (!pMenu -> ModifyMenu(uiIDTest2, uiNewID))
			return false;
	}
	return true;
}


BOOL CSplit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_RBUTTONDOWN)
	{
		CWnd* pWnd = CWnd::FromHandlePermanent(pMsg->hwnd);
		CControlBar* pBar = DYNAMIC_DOWNCAST(CControlBar, pWnd);

		if (pBar != NULL)
		{
			CMenu Menu;
			CPoint pt;

			pt.x = LOWORD(pMsg->lParam);
			pt.y = HIWORD(pMsg->lParam);
			pBar->ClientToScreen(&pt);

			if (Menu.LoadMenu(IDR_MAINFRAMERB))
			{
				CMenu* pSubMenu = Menu.GetSubMenu(0);

				if (pSubMenu!=NULL)
				{
					pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,this);
					return true;
				}
			}
		}
	}	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CSplit::DockControlBarLeftOf(CToolBar* pBar,CToolBar* pLeftOf)
{
	CRect rect;
	UINT n;
	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	pLeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
/*	dw = pLeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;*/
	GetDockStyleFromBarStyle(pLeftOf, &n);

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(pBar,n,&rect);
}

void CSplit::Dockingbars()
{	// default 
	DockControlBar(&m_wndProjectToolBar, AFX_IDW_DOCKBAR_TOP);
	DockControlBar(&m_wndNotifBar, AFX_IDW_DOCKBAR_TOP);
	DockControlBarLeftOf(&m_wndToolBar, &m_wndProjectToolBar);
}

void CSplit::GetDockStyleFromBarStyle(CToolBar* pBar, UINT *puiStyle)
{
	ASSERT(pBar);
	ASSERT(puiStyle);
	if (NULL == pBar || NULL == puiStyle) return;
	*puiStyle = 0;
	
	UINT n = 0;
	DWORD dw = pBar->GetBarStyle();
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	*puiStyle = n;
}

// Bug in der MFC
void CSplit::FixedupSaveBarState (LPCTSTR lpszProfileName)
{
	CDockState state;
	GetDockState (state);
	
	for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++) 
	{
		CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
		int nSize = pInfo->m_arrBarID.GetSize(); 

		for (int j = 0; j < nSize - 1; ++j) 
		{
			if ((DWORD)(pInfo->m_arrBarID[j]) >= (DWORD)65536)
			{
				int act = j;

				if ((DWORD)(pInfo->m_arrBarID[j+1]) == 0) // >= (DWORD)65536))
				{
					pInfo->m_arrBarID.RemoveAt (j+1);
					nSize--;
					j--;
				}

				pInfo->m_arrBarID.RemoveAt (act);
				nSize--;
				j--;
			}
		}
	}
	state.SaveState (lpszProfileName);
}

void CSplit::OnDebugImportall() 
{
	ImportAll();
}


void CSplit::OnUpdateDebugImportall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

// global: wird mehrmals genutzt
UINT FileDialog (LPCSTR pcPath, CWnd *pParent, CString & strFileName, BOOL fOpen, LPCSTR lpcstrCaption) 
{
CString strFilters = GetDefaultName(IDS_SAVEASFILTERS) ; 
CString strExt = GetDefaultName(IDS_SCRIPTEXT); 
UINT ui = 0;
DWORD dwFlags = OFN_EXPLORER|OFN_LONGNAMES;

	if (fOpen)
		dwFlags |= OFN_HIDEREADONLY|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	else
		dwFlags |= OFN_OVERWRITEPROMPT;

#if defined(OFN_ENABLESIZING)
	if (IsWin41() || (IsWin50() && IsWinNT())) {
		dwFlags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
		dwFlags |= OFN_DONTADDTORECENT;
#endif // defined(OFN_DONTADDTORECENT)
	}
#endif // defined(OFN_ENABLESIZING)

CDebFileDialog  SDlg (fOpen, strExt, strFileName, dwFlags, strFilters, pParent, lpcstrCaption);

	SDlg.m_ofn.lpstrInitialDir = pcPath;
	if (SDlg.DoModal() == IDOK) 
	{
		strFileName = SDlg.GetPathName();
		if (false == fOpen)// SaveFileDialog
			ui = SDlg.m_ofn.nFilterIndex; 
		else
			ui = 1;
	}
	return ui;
}
