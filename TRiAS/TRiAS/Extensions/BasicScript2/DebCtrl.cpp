// file DebCtrl.cpp

#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <new>
#include <iobjman.h>
#include <afxcview.h>
#include <registrx.hxx>

#include "macrguid.h"

#include "iscrprop.h"

#include "projscr.h"
#include "strinfo.h"
#include "dummypar.h"
#include "conststr.h"
#include "fndrpld.h"
#include "toolbarx.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "runerr.h"
#include "runebobs.h"
#include "DebCtrl.h"
#include "projscr.h"
#include "spltree.h"
#include "splitter.h"
#include "split.h"
#include "editctrl.h"
#include "BSParam.h"

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

#define OS_NO_STREAM_SUPPORT

#define MENUPOS_IMPORTLINK	3
#define MENUPOS_IMPORT		4

static UINT NEAR uiWM_Replace = ::RegisterWindowMessage(FINDMSGSTRING);
static UINT NEAR uiWM_EndScript = ::RegisterWindowMessage("EndScript");

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(StreamInfo);
DefineSmartInterface(TreeItem);
DefineSmartInterface(ObjManHelper);
////////////////////////////////////////////////////////////////////////////
// weitere Member Save, Load, Running in externen Files

// The following names from WINDOWSX.H collide with names in this file
#undef SubclassWindow

////////////////////////////////////////////////////////////////////////////
// globale Funktionen
BOOL		LoadString(CString & str, int IDS);
CString		GetDefaultName(int IDS);
CString		GetDefaultScript();
CString		GetPathName (LPCSTR pcPath);
CString		CorrectExtension (CString &rPath, UINT uiResIDExt);
HRESULT		RunThread(ebHTHREAD hThread, ebHSCRIPT hScript);
BOOL		TranslateAcceleratorDebCtrl (CebDebugger *pDebug, Accelerator  *pAcc, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT		MessageNoCode(HWND hWnd, ebHCODE hCode);
HRESULT		MessageNoText(HWND hWnd, LPCSTR lpcstr);
HRESULT		MessageCompileSuccess(HWND hWnd);
HRESULT		MessageBoxBadText(HWND hWnd, int iLen);
BOOL		GetFile(LPCSTR lpcstr);
HRESULT		SetHomeDir(CebInstance *pInst, LPCSTR lpcstr);
CString		GetFileName (CString &rPath, BOOL fExt);
HRESULT		SetAllParams (CebThread & rThread, BSPARAM *pBSParams, int iCountPar);
HRESULT		GetReturnParams (CebThread & rThread, BSPARAM *pBSParams, LPVOID *lplpExtVariant, ebWORD wExtVariantType);
HRESULT		GetAllParams (CebThread & rThread, BSPARAM *pBSParams, int iCountPar);
HRESULT		ResetApplicationObjects (CebThread & rThread, BSPARAM *pBSParams, int iCountPar);

extern "C"
UINT ebCALLBACK _XTENSN_EXPORT CallbackFontProcDebugger(HWND hWnd, UINT msg,  
							UINT uiParam, long lParam);
extern "C" 
void ebCALLBACK _XTENSN_EXPORT OnRuntimeError (	long lParam, ebLPCSTR lpMsg, ebDWORD dwErrNum, ebWORD wLinNr, ebWORD wCharPos, 
												ebLPCSTR lpSource, ebLPCSTR lpHelpFile, ebDWORD dwHelpContext);
/////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern SummitModul g_SummitModuls[];


/////////////////////////////////////////////////////////////////////////////
// CDebuggerCtrl
IMPLEMENT_DYNCREATE(CDebuggerCtrl, CWnd)

CDebuggerCtrl::CDebuggerCtrl()
{
	m_hCode = NULL;
	m_pText = NULL;

	m_pRelGeneralScripts = NULL;
	m_lpstrRequestorName = NULL;

	m_fRMBMenu = false;
	m_hFontOld = NULL;
	m_hWndSaved= NULL;
	m_fEnabled = false;
	m_fSendClose = false;
	m_fAskSave = false;
	// Dummy für Laufzeitdialoge
	m_pDummyParent = NULL;
	m_fIsModifiedOpen = false;
	m_fIsModifiedSaveAs = false;
	m_fIsInsertSaveText = false;
	m_fIsModifiedNew = false;
	m_bFDOpen = false;
	m_pMainFrame = NULL;
	m_iNumParams = 0;
	m_pPars = NULL;
	
	m_pFRD = NULL;
	m_strFindText.Empty();	
	m_pcReplaceWithText = NULL;
	m_pcFindText = NULL;
	m_bMatchCase = false;      /* = 0, case-insensitive */
	m_bUpDown = false;
	m_bMatchWholeWord = false;

	m_fDisplayFormat = false;

	m_fRecursiv = false;

	m_hAccel = NULL;
}
CDebuggerCtrl::~CDebuggerCtrl()
{
	DELETE_OBJ(m_pEditCtrl);
	if (NULL != m_hWnd && IsWindow(m_hWnd))
	{
		UnsubclassWindow();
		DestroyWindow();
	}
	GetBSInstance() -> SetWindow (g_pBSE -> hWnd());		// ParentWindows zurücksetzen
	GetBSInstance() -> SetViewportParent(g_pBSE -> hWnd());

	ResetFindReplaceDialog();
	DeleteDummyParent();
	ResetDebuggerMember();
	// Related Scripts im Ganzen löschen
	DeleteRelated();
}


BEGIN_MESSAGE_MAP(CDebuggerCtrl, CWnd)
	//{{AFX_MSG_MAP(CDebuggerCtrl)
	ON_REGISTERED_MESSAGE(uiWM_Replace, OnCallbackFindReplace)
	ON_WM_INITMENUPOPUP()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_DEBUG_NEWFILE, OnNew)
	ON_COMMAND(ID_DEBUG_OPEN, OnOpen)
	ON_COMMAND(ID_DEBUG_SAVEAS, OnSaveas)
	ON_COMMAND(ID_DEBUG_SAVE, OnSave)
	ON_COMMAND(ID_DEBUG_REPLACE, OnReplace)
	ON_WM_DESTROY()
	ON_WM_NCDESTROY()
	ON_REGISTERED_MESSAGE(uiWM_EndScript, OnEndScript)
	ON_COMMAND(ID_DEBUG_GO, OnDebugGo)
	ON_WM_KILLFOCUS()
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
	ON_COMMAND(ID_DEBUG_PAUSE, OnDebugPause)
	ON_COMMAND(ID_DEBUG_GOTOLINE, OnDebugGotoline)
	ON_COMMAND(ID_DEBUG_NEWDIALOG, OnDebugNewdialog)
	ON_COMMAND(ID_DEBUG_PASTE, OnDebugPaste)
	ON_COMMAND(ID_DEBUG_RECORDING, OnDebugRecording)
	ON_COMMAND(ID_DEBUG_SUSPEND, OnDebugSuspend)
	ON_COMMAND(ID_DEBUG_SYNTAX, OnDebugSyntax)
	ON_COMMAND(ID_DEBUG_TRACEOVER, OnDebugTraceover)
	ON_COMMAND(ID_DEBUG_UNDO, OnDebugUndo)
	ON_COMMAND(ID_DEBUG_GETHELPON, OnDebugGetHelpOn)	
	ON_COMMAND(ID_DEBUG_EDITORHELP, OnDebugEditorHelp)	
	ON_COMMAND(ID_DEBUG_TRIASHELP, OnDebugTriasHelp)	
	ON_COMMAND(ID_DEBUG_INSERT, OnDebugInsert)
	ON_COMMAND(ID_DEBUG_REMOVE, OnDebugRemove)
	ON_COMMAND(ID_DEBUG_TRACEIN, OnDebugTracein)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////////////////////
// eigentliche Fenstererstellung des Debuggercontrols und CWnd-Subclassing dieses Fensters
BOOL CDebuggerCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// Parent: CFormView...
	if (!CreateDebuggerControl (dwStyle, pParentWnd->GetSafeHwnd(), rect, nID))
		return false;

	ASSERT(GetDebugger() -> GetWindow());
	if (!SubclassWindow(GetDebugger() -> GetWindow()))
		return false;
	
	if (!SubClassEditWindow())
		return false;

	return true;
}

HRESULT CDebuggerCtrl::InitDebuggerCtrl(CSplit *pMainFrame)
{
	if (GetDebugger() && GetDebugger() -> GetState() != TS_IDLE)
		return S_FALSE;

	ASSERT(pMainFrame);

	// eigentliche Initialisierungen der Debuggermember
	m_pMainFrame = pMainFrame;
			
	SetModus();
	SetFont();

	GetBSInstance() -> SetWindow (m_hWnd);		// ParentWindow setzen
	GetBSInstance() -> SetViewportParent(m_hWnd);

	GetDebugger() -> SetAutoCase	(true);
	GetDebugger() -> SetAutoIndent(true);
	GetDebugger() -> SetInstance (GetBSInstance());

// Extrabuffer für Threadbytes (z.B. ebThread_SetLong() für BREAK ?) 
	GetDebugger() -> SetThreadExtra(CREATETHREAD_EXTRA);

	GetDebugger() -> EnableTextColors();
	GetDebugger() -> EnableCtrlBreak();
//	GetDebugger() -> SetKeyboardFilter (KeyboardFilterDebCtrlProc);
	GetDebugger() -> SetNotificationProc(HandleDebuggerCtrlNotification);
	GetDebugger() -> SetNotificationData((long)this);

// Daten für KeyboardFilterProc merken
	SetProp (m_hWnd, g_cbKeyboardFilterData, (HANDLE)GetDebugger());

	try {
		if (NULL == m_pDummyParent) 
			m_pDummyParent = new CDummyParent (g_pBSE -> MWind());
		if (NULL == m_pDummyParent) _com_issue_error(E_POINTER);

		if (!GetDebugger() -> SetText(GetDefaultScript()) ||	!GetAccelerator()) 
			_com_issue_error(E_FAIL);
		GetDebugger() -> SetCode(NULL);
	} 
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	}
	catch (_com_error& e) 
	{
		return _COM_ERROR(e);
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrl message handlers

BOOL CDebuggerCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if (NULL != m_hAccel && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
			return true;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}

void CDebuggerCtrl::OnDestroy() 
{
	CWnd::OnDestroy();	
}
void CDebuggerCtrl::OnNcDestroy() 
{
	if (m_hWnd && IsWindow(m_hWnd))
	{
		if (NULL != GetProp (m_hWnd, g_cbKeyboardFilterData))
			RemoveProp (m_hWnd, g_cbKeyboardFilterData);
		UnsubclassWindow();
	}
	// ruft	PostNcDestroy() 
	CWnd::OnNcDestroy();
}
// Need this because this class is tagged DYNCREATE
void CDebuggerCtrl::PostNcDestroy() 
{
	// da es schon vom CWnd-Objekt destroyed wurde
	GetDebugger() -> DetachWindow();
	//delete this;
}

BOOL CDebuggerCtrl::CreateDebuggerControl (DWORD style, HWND hWnd, const RECT& rect, UINT nID)
{
	DWORD styleDebugger = 0;
	if (!g_SummitModuls[RUNTIME].fIsInstalled)
		styleDebugger = DS_NOWATCHWINDOW;
	
	styleDebugger |= WS_CHILD|WS_VISIBLE;

	GetDebugger() -> SetParent (hWnd);
	GetDebugger() -> SetStyle (styleDebugger);
	GetDebugger() -> SetId (nID);
	GetDebugger() -> SetInstance (g_hInstance);
	GetDebugger() -> SetRect(
					rect.left-2*SIZE_XBORDER, 
					rect.top-2*SIZE_YBORDER, 
					rect.right+(4*SIZE_YBORDER),		// Höhe
					rect.bottom+(4*SIZE_XBORDER));	// Breite
	GetDebugger() -> SetWatchWindowHeight(SIZE_WATCHWINDOWHEIGHT);

	if (!GetDebugger() -> Create()) 
	{
		TRACE("Failed to create debugger control\n");
		return false;      // fail to create
	}

return true;
}

void CDebuggerCtrl::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	GetMainFrame() -> OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}
void CDebuggerCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	GetEditCtrl() -> SetFocus();	
}

void CDebuggerCtrl::OnSize(UINT nType, int cx, int cy) 
{
	//SetWindowSize(cx, cy);
	CWnd::OnSize(nType, cx, cy);
}


///////////////////////////////////////////////////////////////////////////
// Memberzugriff von MainFrameparent
void CDebuggerCtrl::ResetIfOnClose()
{
	m_IObjManagement.Assign(NULL);
	DeleteRelated();
}

BOOL CDebuggerCtrl::GetAccelerator()
{
	ASSERT(g_hInstance);
	// free automaticly
	m_hAccel = LoadAccelerators(g_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR_DEBCTRL));
	ASSERT(m_hAccel);
	if (m_hAccel) return true;

	return false;
}

CSplit * CDebuggerCtrl::GetMainFrame()
{
	ASSERT(m_pMainFrame);
return m_pMainFrame ? m_pMainFrame : NULL; 
}

HTREEITEM CDebuggerCtrl::GetChildItemSel(ITreeItem **ppIT)
{
	return GetMainFrame() -> GetChildItemSel(ppIT);
}

CebInstance *CDebuggerCtrl::GetBSInstance()
{
	CebInstance *pInst = &(g_pBSE -> ebInst());
	ASSERT(pInst);
return pInst;
}

HRESULT CDebuggerCtrl::GetGeneralScripts(IObjectManagement **ppIObj)
{
	return GetMainFrame() -> GetGeneralScripts(ppIObj);
}

HRESULT CDebuggerCtrl::GetInfoGeneralScripts(IStreamInfo **ppISI)
{
	return GetMainFrame() -> GetInfoGeneralScripts(ppISI);
}

HRESULT CDebuggerCtrl::GetFilterScripts(IObjectManagement **ppIObj)
{
	return GetMainFrame() -> GetFilterScripts(ppIObj);
}

HRESULT CDebuggerCtrl::GetInfoFilterScripts(IStreamInfo **ppISI)
{
	return GetMainFrame() -> GetInfoFilterScripts(ppISI);
}

HRESULT CDebuggerCtrl::GetObjFeatScripts(IObjectManagement **ppIObj)
{
	return GetMainFrame() -> GetObjFeatScripts(ppIObj);
}

HRESULT CDebuggerCtrl::GetInfoObjFeatScripts(IStreamInfo **ppISI)
{
	return GetMainFrame() -> GetInfoObjFeatScripts(ppISI);
}

void CDebuggerCtrl::GetTreeRect(RECT *prect)
{
	GetMainFrame() -> GetTreeRect(prect); 
}

CStatusBar *CDebuggerCtrl::GetStatusbar(void)
{
	CSplit *pSplit = GetMainFrame();
	ASSERT(pSplit);
	CStatusBar *pStatbar = pSplit -> GetStatusbar();
	ASSERT(pStatbar);
	return  pStatbar;
}

CFrameToolBar *CDebuggerCtrl::GetToolbar(void)
{
	CSplit *pSplit = NULL;
	
	pSplit = GetMainFrame();
	ASSERT(pSplit);

	CFrameToolBar *pToolbar = NULL;

return  pToolbar = pSplit -> GetToolbar();
}

BOOL CDebuggerCtrl::GetLoadedItem(ITreeItem **ppIT)
{
	return GetMainFrame() -> GetLoadedItem(ppIT);	
}

BOOL CDebuggerCtrl::IsScript_Selected()
{
	return GetMainFrame() -> IsScript_Selected();	
}

BOOL CDebuggerCtrl::IsFunction_Selected()
{
	return GetMainFrame() -> IsFunction_Selected();	
}

void CDebuggerCtrl::GetInitCaretPos (int & ix, int & iy, int & fSelect)
{
	GetMainFrame() -> GetInitCaretPos (ix, iy, fSelect);	
}

BOOL CDebuggerCtrl::GetDirty()
{
	return GetMainFrame() -> GetDirty();	
}

BOOL CDebuggerCtrl::GetEditOnly()
{
	return GetMainFrame() -> GetEditOnly();	
}

void CDebuggerCtrl::SetEditOnly(BOOL fEdit)
{
	GetMainFrame() -> SetEditOnly(fEdit);	
}

BOOL CDebuggerCtrl::IsLabelEdit_Selected()
{
	return GetMainFrame() -> IsLabelEdit_Selected();
}

int CDebuggerCtrl::GetPopUpMenuID()
{
	return GetMainFrame() -> GetPopUpMenuID();
}

CString CDebuggerCtrl::GetScriptName()
{
	return GetMainFrame() -> GetScriptName();
}

CString CDebuggerCtrl::GetScriptName_Selected()
{
	return GetMainFrame() -> GetScriptName_Selected();
}

HRESULT CDebuggerCtrl::SetCode(ebHCODE hCode)
{
	return GetMainFrame() -> SetCode(hCode);
}
HRESULT CDebuggerCtrl::GetCode(ebHCODE *phCode)
{
	return GetMainFrame() -> GetCode(phCode);
}

CString CDebuggerCtrl::GetParentName()
{
	return GetMainFrame() -> GetParentName();	
}

void CDebuggerCtrl::SetDirty(BOOL fDirty)
{
	GetMainFrame() -> SetDirty(fDirty);
}

BOOL CDebuggerCtrl::GetInitNew_Selected()
{
	return GetMainFrame() -> GetInitNew_Selected();	
}

BOOL CDebuggerCtrl::GetInitNew()
{
	return GetMainFrame() -> GetInitNew();	
}

BOOL CDebuggerCtrl::IsTreeFocused()
{
	return GetMainFrame() -> IsTreeFocused();	
}

///////////////////////////////////////////////////////////
// Inits
BOOL CDebuggerCtrl::SubClassEditWindow()
{
	RECT rect;

	memset(&rect, 0, sizeof(RECT));

	try {
		m_pEditCtrl = new CEditCtrl();
		m_pEditCtrl -> Create(NULL, NULL, 0, rect, this, 0, NULL); 
	} catch (bad_alloc) {
		if (m_pEditCtrl) delete m_pEditCtrl;
		m_pEditCtrl = NULL;
		return false;
	}

	return true;
}

void CDebuggerCtrl::SetWindowSize(int nWidth, int nHeight)
{
	if (m_pMainFrame && !m_fRecursiv) 
	{
		UINT nFlags = SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER;
		RECT rectTree;
		GetTreeRect(&rectTree);

		UINT uiTreeWi = rectTree.right-rectTree.left;

		m_fRecursiv = true;
		
		CWnd::MoveWindow(uiTreeWi+7, -1, nWidth+6, nHeight+5); 
	}
	// Um nicht in Rekursion zu fallen, wird nur einmal gerufen
	m_fRecursiv = false;
}

void CDebuggerCtrl::SetModus()
{
	m_fRunModal = false;
	m_fUnLoadIsRun = false;
	m_fMainIsRun = false;
	m_fBreakSet = true;
	m_fOtherFunction = false;
	m_fRunError = false;	
	m_fLoadIsRun = true;
	m_fEditOnly = false;
}

// Font aus Registry/INI lesen
void CDebuggerCtrl::SetFont()
{
	LOGFONT LF;

	memset (&LF, 0, sizeof(LOGFONT));
	if (ReadRegSettingsFont (&LF) ) 
	{
		m_hFontOld = GetDebugger() -> GetFont(); 
		GetDebugger() -> SetFont (::CreateFontIndirect (&LF));
	} 
	else 
	{
		m_hFontOld = NULL;		
	}
}

///////////////////////////////////////////
// Resets
void CDebuggerCtrl::ResetDebuggerMember()
{
	if (m_pText) 
		CoTaskMemFree(m_pText);
	m_pText = NULL;
	if (m_hCode) 
		CoTaskMemFree(m_hCode);
	m_hCode = NULL;
}
void CDebuggerCtrl::ResetFont()
{// Font in Debugger zurücksetzen
	if (m_hFontOld) 
		GetDebugger() -> SetFont (m_hFontOld);		
	m_hFontOld = NULL;
}

void CDebuggerCtrl::ResetFindReplaceDialog()
{
	m_pFRD = NULL;
	DELETE_OBJ(m_pcFindText);
	DELETE_OBJ(m_pcReplaceWithText);
}

void CDebuggerCtrl::DeleteDummyParent()
{
	if (m_pDummyParent)
	{
		m_pDummyParent -> DestroyWindow();
		delete m_pDummyParent;
	}
	m_pDummyParent = NULL;
}

void CDebuggerCtrl::OnTimer()
{
	char Buffer[MAXSTRLENGTH];
	DWORD dwCursorPos = GetDebugger() -> GetCursorPos();
	wsprintf(Buffer, g_cbDezFmt, LOWORD(dwCursorPos) +1);
	GetStatusbar() -> SetPaneText (4, Buffer, true);
	wsprintf(Buffer, g_cbDezFmt, HIWORD(dwCursorPos) +1);
	GetStatusbar() -> SetPaneText (2, Buffer, true);
}

/////////////////////////////////////////////////////////////////////////////
//  OnCommands
void CDebuggerCtrl::OnNew() 
{
	GetMainFrame() -> OnDebugNewFile();
}
void CDebuggerCtrl::OnOpen() 
{
	GetMainFrame() -> OnDebugOpen();
}
void CDebuggerCtrl::OnSaveas() 
{
	GetMainFrame() -> OnDebugSaveas();
}
void CDebuggerCtrl::OnSave() 
{
	GetMainFrame() -> OnDebugSave();
}
void CDebuggerCtrl::OnDebugInsert() 
{
	return; 
}
void CDebuggerCtrl::OnReplace() 
{
	GetMainFrame() -> OnDebugReplace();
}

void CDebuggerCtrl::OnDebugRemove() 
{
	return;
}

void CDebuggerCtrl::OnDebugCut() 
{
	if (GetDebugger() -> GetState() != TS_RUNNING && GetDebugger() -> HasSelection()) {
		GetDebugger() -> EditCut();
		if(GetDebugger() -> CanUndo()) {
			// Toolbarknöpfe einstellen
			GetToolbar() -> Enable (ID_DEBUG_UNDO);
			GetToolbar() -> Repaint();
		}
	}
}

void CDebuggerCtrl::OnDebugCopy() 
{
	if (GetDebugger() -> HasSelection()) {
		GetDebugger() -> EditCopy();
		if(GetDebugger() -> CanUndo()) {
			// Toolbarknöpfe einstellen
			GetToolbar() -> Enable (ID_DEBUG_UNDO);
			GetToolbar() -> Repaint();
		}
	}
}

void CDebuggerCtrl::OnDebugAddwatch() 
{
	GetDebugger() -> AddWatch (NULL);	
}

void CDebuggerCtrl::OnDebugModifyDlg() 
{
	if (m_fBreakSet || m_fOtherFunction)
		ebDebugger_ModifyDialog(GetDebugger() -> GetWindow(), true);
}

void CDebuggerCtrl::OnDebugDeletewatch() 
{
	if (GetDebugger() -> CanDeleteWatch())
		GetDebugger() -> DeleteWatch (NULL);	
}

void CDebuggerCtrl::OnDebugHex() 
{
	if (GetDebugger() -> GetState() == TS_IDLE) return;

	if (m_fDisplayFormat == false) {
		ebDebugger_SetDisplayFormat(GetDebugger() -> GetWindow(), DF_HEX);
		m_fDisplayFormat = true;
	} else {
		ebDebugger_SetDisplayFormat(GetDebugger() -> GetWindow(), DF_DECIMAL);
		m_fDisplayFormat = false;
	}
}

void CDebuggerCtrl::OnDebugBreakpoint() 
{
	GetDebugger() -> ToggleBreakpoint (0);	
}

void CDebuggerCtrl::OnDebugCallstack() 
{
	if ((m_fBreakSet || m_fOtherFunction))
		GetDebugger() -> InvokeCallsDialogBox();	
}

void CDebuggerCtrl::OnDebugDelete() 
{
	if (S_OK != CanEdit()) return;
	if (GetDebugger() -> HasSelection())	
		GetDebugger() -> EditClear();	
}

void CDebuggerCtrl::OnDebugEditdialog() 
{
	if (S_OK != CanEdit()) return;
	if (GetDebugger() -> IsDialogSelected())	
		GetDebugger() -> EditDialog();	
}

void CDebuggerCtrl::OnDebugNewdialog() 
{                        
	if (S_OK != CanEdit()) return;
	GetDebugger() -> InsertDialog();                              
}
                              
// Aufruf von Menü 
void CDebuggerCtrl::OnDebugFindnext() 
{                                 
	GetStatusbar() -> SetPaneText ( 0, g_cbNil, true );

	TRY {                                       		
		if(m_strFindText.IsEmpty()) return;						
		FindNext();
	} CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
	} END_CATCH;
}

// Aufruf von Menü 
void CDebuggerCtrl::OnDebugFind() 
{
	ResetFindReplaceDialog();

	m_pcFindText = new char[MAXSTRLENGTH];
	if (NULL == m_pcFindText) AfxMessageBox (IDS_NOMEMORY);
	
	GetStatusbar() -> SetPaneText ( 0, g_cbNil, true );
	
	if (1 == GetDebugger() -> GetSelection (m_pcFindText, MAXSTRLENGTH) )
		GetDebugger() -> GetCaretWord (m_pcFindText, MAXSTRLENGTH);
	
	m_pFRD = CFindReplaceDlg :: CreateInstance();			
	if (NULL == m_pFRD) {
		AfxMessageBox (IDS_NOMEMORY);
		return;
	}		
	m_pFRD -> m_fr.lStructSize = sizeof ( FINDREPLACE );
	m_pFRD -> m_fr.lpstrFindWhat = m_pcFindText;
	m_pFRD -> m_fr.wFindWhatLen = MAXSTRLENGTH;                                      	
	m_pFRD -> m_fr.hwndOwner = m_hWnd; 
	m_pFRD -> Create ( true, NULL, NULL, FR_DOWN, this);
}

void CDebuggerCtrl::OnDebugReplace() 
{
	if (S_OK != CanEdit()) return;

	ResetFindReplaceDialog();

	m_pcFindText = new char[MAXSTRLENGTH];
	if (NULL == m_pcFindText) AfxMessageBox (IDS_NOMEMORY);

	m_pcReplaceWithText = new char[MAXSTRLENGTH];
	if (NULL == m_pcReplaceWithText) AfxMessageBox (IDS_NOMEMORY);
		
	GetStatusbar() -> SetPaneText (0, g_cbNil, true);

	if (1 == GetDebugger() -> GetSelection( m_pcFindText, MAXSTRLENGTH ) )
		GetDebugger() -> GetCaretWord ( m_pcFindText, MAXSTRLENGTH);		
	
	m_pFRD = CFindReplaceDlg :: CreateInstance();			
	if (NULL == m_pFRD) {
		AfxMessageBox (IDS_NOMEMORY);
		return;
	}		
	m_pFRD -> m_fr.lStructSize = sizeof (FINDREPLACE);
	m_pFRD -> m_fr.lpstrFindWhat = m_pcFindText;
	m_pFRD -> m_fr.lpstrReplaceWith = m_pcReplaceWithText;
	m_pFRD -> m_fr.wFindWhatLen = MAXSTRLENGTH;                                      	
	m_pFRD -> m_fr.wReplaceWithLen = MAXSTRLENGTH;                                      	
	m_pFRD -> m_fr.hwndOwner = m_hWnd; 
	m_pFRD -> Create ( false, NULL, NULL, FR_DOWN, this);
}

void CDebuggerCtrl::OnDebugFonts() 
{
	LOGFONT LF;
	HFONT hFont = GetDebugger() -> GetFont();
	int iSize = GetObject (hFont, sizeof(LOGFONT), &LF);
	ASSERT (iSize != 0);

	if (iSize != 0) 
	{
		DWORD dwFlags = CF_ENABLEHOOK | CF_SCREENFONTS | CF_ANSIONLY | 
			CF_INITTOLOGFONTSTRUCT | CF_FIXEDPITCHONLY;

		CFontDialog FD (&LF, dwFlags, NULL, this);

		FD.m_cf.lpfnHook = &CallbackFontProcDebugger;	 
		FD.m_cf.lCustData = (LONG) this;
	
		if (FD.DoModal() == IDOK) 
		{   // alle selbst kreierten Fonts auch wieder freigeben
			GetDebugger() -> SetFont (::CreateFontIndirect (&LF));

			if (NULL == m_hFontOld) // erster neuer Font
				m_hFontOld = hFont;
			else if (hFont)		// nicht erster, m_hFontOld beibehalten
				::DeleteObject (hFont);
		// neuen Font auch anzeigen
			::InvalidateRect (m_hWnd, NULL, true);
			::UpdateWindow (m_hWnd);
		}                                               
	}
}

void CDebuggerCtrl::OnDebugGotoline() 
{
	GetDebugger() -> InvokeGotoLineDialogBox();	
}

void CDebuggerCtrl::OnDebugPaste() 
{
	if (S_OK != CanEdit()) return;

	if (GetDebugger() -> GetState() != TS_RUNNING &&
		::IsClipboardFormatAvailable (CF_TEXT))
	{
		GetDebugger() -> EditPaste();
		if(GetDebugger() -> CanUndo()) {
			// Toolbarknöpfe einstellen
			GetToolbar() -> Enable (ID_DEBUG_UNDO);
			GetToolbar() -> Repaint();
		}
	}
}

void CDebuggerCtrl::OnDebugRecording() 
{
	// TODO: Add your command handler code here
	
}

void CDebuggerCtrl::OnDebugSuspend() 
{
	if (GetDebugger() -> GetState() == TS_RUNNING ||
		GetDebugger() -> GetState() == TS_SUSPENDED)	
	{
		GetDebugger() -> EndScript();
	}

	m_fBreakSet  = true;
	PostMessage(uiWM_EndScript, 0, GO);
}

void CDebuggerCtrl::OnDebugSyntax() 
{
	if (g_SummitModuls[COMPILER].fIsInstalled && 
		GetDebugger() -> GetState() != TS_RUNNING)
	{	
// Wenn Debugger nicht dirty und schon mal compiliert, wird Compile intern nicht gerufen.
		GetDebugger() -> SetCode(NULL);
// Trotzdem gewährleisten, dass Funktionen enumeriert werden.
//		if (FAILED(EnumFunctions ())) return;

		if (GetDebugger() -> Compile() && SUCCEEDED(LinkScript()))
		{
			MessageCompileSuccess(this -> GetSafeHwnd());
		}
	}
}

void CDebuggerCtrl::OnDebugGo() 
{
	try
	{
		if (GetDebugger() -> GetState() == ES_EXECUTING || !g_SummitModuls[RUNTIME].fIsInstalled)
			_com_issue_error(E_UNEXPECTED);

		HRESULT hr = GetMainFrame() -> OpenOnGo(); 
		if (FAILED(hr)) _com_issue_error(hr);

		// wenn nicht schon mal gefragt, fragen
		if (false == m_fAskSave) 
		{
			if (!AskSave()) _com_issue_error(S_FALSE);// Cancel
		}
		// Related hinzufügen
		hr = AddRelatedScript();
		if (FAILED(hr)) _com_issue_error(hr);

		if (m_fRunModal || m_fOtherFunction)
		{// anderen Entry
			GetDebugger() -> StartScript();
			_com_issue_error(S_FALSE);
		}
		else if (false == g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject())
		{// Debuggerlauf bei geschlossenem Projekt ermöglichen 
			RunScript(GO);
			_com_issue_error(S_FALSE);
		}

		if (NULL == GetDebugger() -> GetCode(false) || GetDirty()) {	
			if (!GetDebugger() -> Compile()) _com_issue_error(E_FAIL);
		}		
		hr = RunScript(GO);// Load, Main, UnLoad
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch (_com_error&)
	{
	}
}

void CDebuggerCtrl::OnDebugTracein() 
{
	if (g_SummitModuls[RUNTIME].fIsInstalled && (m_fBreakSet || m_fOtherFunction)) 
	{
		if (FAILED(GetMainFrame() -> OpenOnGo())) return;

		if (false == m_fAskSave) {
			if (!AskSave())
				return;// Cancel
		}

		HRESULT hr = AddRelatedScript();
		if (FAILED(hr)) return;

		if (m_fRunModal || m_fOtherFunction) 
		{
			GetDebugger() -> TraceInto();
			return;
		}
		else if (false == g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject())
		{
			RunScript(TRACEINTO);
			return;
		}

		if (NULL == GetDebugger() -> GetCode(false) || GetDirty()) {	
			if (!GetDebugger() -> Compile()) return;
		}

		if (FAILED(RunScript(TRACEINTO))) return;
	}
}

void CDebuggerCtrl::OnDebugTraceover() 
{
	if (g_SummitModuls[RUNTIME].fIsInstalled && (m_fBreakSet || m_fOtherFunction)) 
	{
		if (FAILED(GetMainFrame() -> OpenOnGo())) return;

		if (false == m_fAskSave) 
		{
			if (!AskSave())
				return;// Cancel
		}

		HRESULT hr = AddRelatedScript();
		if (FAILED(hr)) return;

		if (m_fRunModal || m_fOtherFunction) 
		{
			GetDebugger() -> StepOver();
			return;
		}
		else if (false == g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject())
		{
			RunScript(TRACEOVER);
			return;
		}

		if (NULL == GetDebugger() -> GetCode(false) || GetDirty()) {	
			if (!GetDebugger() -> Compile()) return;
		}

		if (FAILED(RunScript(TRACEOVER))) return;
	}
}

void CDebuggerCtrl::OnDebugPause() 
{
	if (g_SummitModuls[RUNTIME].fIsInstalled) {
		if (GetDebugger() -> GetState() == TS_RUNNING)
			GetDebugger() -> PauseScript();
	}
}

void CDebuggerCtrl::OnDebugUndo() 
{
	if (GetDebugger() -> GetState() != TS_RUNNING && GetDebugger() -> CanUndo())
		GetDebugger() -> EditUndo();
}

//////////////////////////////////////////////////////////
// Neue Funktion einfügen
BOOL CDebuggerCtrl::OnDebugFunctionInsert(LPCSTR lpcstrFunctionText)
{
	ASSERT(lpcstrFunctionText);

	if (S_OK != CanEdit()) return true;

	LPSTR lpstrWholeText = NULL;
	UINT uiLen = GetDebugger() -> GetTextLength();
	UINT uiLenFunction = strlen(lpcstrFunctionText);
	UINT uiLines = GetDebugger() -> GetNumLines();

	ASSERT(0 != uiLen);
	ASSERT(0 != uiLenFunction);

	if (0 == uiLen || 0 == uiLenFunction) return false;

	try 
	{// String allocieren TextString + FunktionString + '\0'
		lpstrWholeText = (LPSTR) CoTaskMemAlloc(uiLenFunction + uiLen + 1); // wegen der '0'
		if (0 == lpstrWholeText) throw false;

	// erstmal Text lesen
		if (0 == GetDebugger() -> GetText (lpstrWholeText, uiLenFunction + uiLen + 1)) 
			throw false;

	// FunktionText zum Text hinzufügen
		strcat (lpstrWholeText, lpcstrFunctionText);

	// Neuen Text setzen
		if (0 == GetDebugger() -> SetText (lpstrWholeText)) 
			throw false;

	// Cursor vor neue Funktion setzen
		if (false == GetDebugger() -> SetCaretPos (0, uiLines+1, false)) 
			throw false;						
	} 
	catch (BOOL fResult) 
	{
		if (lpstrWholeText) CoTaskMemFree(lpstrWholeText); lpstrWholeText = NULL;
		return fResult;
	}

	if (lpstrWholeText) CoTaskMemFree(lpstrWholeText); lpstrWholeText = NULL;
	return true;
}

///////////////////////////////////////////////////////////
// Speicheroperationen 
//
///////////////////////////////////////////////////////////
// Neues Script laden
BOOL CDebuggerCtrl::OnDebugNew(LPCSTR lpstr)
{    
	SetScript((LPSTR)lpstr, NULL);
	DeleteWatchVariables();
	return true;
}
///////////////////////////////////////////////////////////
// anderes Script laden
BOOL CDebuggerCtrl::OnDebugOpen(LPCSTR lpstr, ebHCODE hCode)
{
	SetScript((LPSTR)lpstr, hCode);
	DeleteWatchVariables();
	return true;
}

///////////////////////////////////////////////////////////
// geladenes Script geben lassen
BOOL CDebuggerCtrl::OnDebugSave(LPSTR *lplpstr, ebHCODE *phCode, DWORD & dwSaveFlag)
{
return	GetScript(lplpstr, phCode, dwSaveFlag);
}
///////////////////////////////////////////////////////////
// geladenes Script geben lassen
BOOL CDebuggerCtrl::OnDebugSaveas(LPSTR *lplpstr, ebHCODE *phCode, DWORD & dwSaveFlag)
{
return	GetScript(lplpstr, phCode, dwSaveFlag);
}

void CDebuggerCtrl::OnDebugGetHelpOn()
{
	char KeyWord[MAXSTRLENGTH];

	if (GetDebugger() -> GetCaretWord(KeyWord, MAXSTRLENGTH)) {
		VERIFY(SUCCEEDED(KeywordHelp(KeyWord)));
	}
}

void CDebuggerCtrl::OnDebugEditorHelp()
{
	VERIFY(SUCCEEDED(DebuggerHelp()));
}

void CDebuggerCtrl::OnDebugTriasHelp()
{
	VERIFY(SUCCEEDED(TriasHelp()));
}

////////////////////////////////////////////////////////////////
// OnIdleUpdates

void CDebuggerCtrl::OnUpdateDebugCut(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_CUT == pCmdUI->m_nID);

	if (ID_DEBUG_CUT == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_CUT, pCmdUI)) return;
	
		int iState = GetDebugger() -> GetState();		
		if (iState == ES_IDLE && 
			GetDebugger() -> HasSelection()	&& 
			(m_fBreakSet || m_fOtherFunction) &&
			false == IsLabelEdit_Selected())
		{
			pCmdUI -> Enable (true);
			GetToolbar() -> Enable (ID_DEBUG_CUT);
		} 
		else 
		{
			pCmdUI -> Enable (false);
			GetToolbar() -> Disable (ID_DEBUG_CUT);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugCopy(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_COPY == pCmdUI->m_nID);

	if (ID_DEBUG_COPY == pCmdUI->m_nID) 
	{
		if (GetDebugger() -> HasSelection()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_COPY);
			pCmdUI -> Enable(true);
		}
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_COPY);
			pCmdUI -> Enable(false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugBreakpoint(CCmdUI* pCmdUI)
{
	if (ID_DEBUG_BREAKPOINT == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_BREAKPOINT, pCmdUI)) return;
		
		if (GetEditOnly() || 
			!g_SummitModuls[RUNTIME].fIsInstalled ||
			IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Disable (ID_DEBUG_BREAKPOINT);
			pCmdUI -> Enable (false);
		} 
		else 
		{
			GetToolbar() -> Enable (ID_DEBUG_BREAKPOINT);
			pCmdUI -> Enable (true);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugCallstack(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_CALLSTACK == pCmdUI->m_nID);

	if (ID_DEBUG_CALLSTACK == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_CALLSTACK, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();
		if (iState == ES_SUSPENDED	&& 
			g_SummitModuls[RUNTIME].fIsInstalled	&& 
			(m_fBreakSet || m_fOtherFunction) && 
			false == GetEditOnly() &&
			false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_CALLSTACK);
			pCmdUI -> Enable (true);
		}
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_CALLSTACK);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugDelete(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_DELETE == pCmdUI->m_nID);

	if (ID_DEBUG_DELETE == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_DELETE, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();
		if (iState == ES_IDLE && 
			GetDebugger() -> HasSelection()	&& 
			(m_fBreakSet || m_fOtherFunction)) 
		{
			GetToolbar() -> Enable (ID_DEBUG_DELETE);
			pCmdUI -> Enable (true);
		}
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_DELETE);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugAddwatch(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_ADDWATCH == pCmdUI->m_nID);

	if (ID_DEBUG_ADDWATCH == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_ADDWATCH, pCmdUI)) return;

		if (g_SummitModuls[RUNTIME].fIsInstalled && 
			false == GetEditOnly() &&
			false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_ADDWATCH);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_ADDWATCH);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugDeletewatch(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_DELETEWATCH == pCmdUI->m_nID);

	if (ID_DEBUG_DELETEWATCH == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_DELETEWATCH, pCmdUI)) return;

		if (GetDebugger() -> CanDeleteWatch() && 
			g_SummitModuls[RUNTIME].fIsInstalled &&
			false == GetEditOnly() &&
			false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_DELETEWATCH);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_DELETEWATCH);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugModifyDlg(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_MODIFYDLG == pCmdUI->m_nID);

	if (ID_DEBUG_MODIFYDLG == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_MODIFYDLG, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();
		if (iState == ES_SUSPENDED	&& 
			IsWatch() && 
			g_SummitModuls[RUNTIME].fIsInstalled && 
			(m_fBreakSet || m_fOtherFunction) &&
			false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_MODIFYDLG);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_MODIFYDLG);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugHex(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_HEX == pCmdUI->m_nID);

	if (ID_DEBUG_HEX == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_HEX, pCmdUI)) return;

		ModifyMenu(pCmdUI -> m_pMenu, m_fDisplayFormat ? IDS_DEZ :IDS_HEX, ID_DEBUG_HEX);			
		if (!g_SummitModuls[RUNTIME].fIsInstalled || IsLabelEdit_Selected())
		{
			GetToolbar() -> Disable (ID_DEBUG_HEX);
			pCmdUI -> Enable (false);
		} 
		else 
		{
			GetToolbar() -> Enable (ID_DEBUG_HEX);
			pCmdUI -> Enable (true);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugEditdialog(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_EDITDIALOG == pCmdUI->m_nID);

	if (ID_DEBUG_EDITDIALOG == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_EDITDIALOG, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();
		if (iState == ES_IDLE && 
			GetDebugger() -> IsDialogSelected()	&& 
			g_SummitModuls[DLGEDIT].fIsInstalled && 
			(m_fBreakSet || m_fOtherFunction)) 
		{
			GetToolbar() -> Enable (ID_DEBUG_EDITDIALOG);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_EDITDIALOG);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugFonts(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_FONTS == pCmdUI->m_nID);

	if (ID_DEBUG_FONTS == pCmdUI->m_nID) 
	{	
		if (m_bFDOpen == false &&
			false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_FONTS);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_FONTS);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugFind(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_FIND == pCmdUI->m_nID);

	if (ID_DEBUG_FIND == pCmdUI->m_nID) 
	{
		if (m_pFRD == NULL && false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_FIND);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_FIND);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugFindNext(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_FINDNEXT == pCmdUI->m_nID);

	if (ID_DEBUG_FINDNEXT == pCmdUI->m_nID) 
	{
		if (m_pFRD == NULL && false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_FINDNEXT);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_FINDNEXT);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugPause(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_PAUSE == pCmdUI->m_nID);

	if (ID_DEBUG_PAUSE == pCmdUI->m_nID) 
	{
		int iState = GetDebugger() -> GetState();
		if (iState == ES_EXECUTING && 
			g_SummitModuls[RUNTIME].fIsInstalled && 
			!GetEditOnly()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_PAUSE);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_PAUSE);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugGotoline(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_GOTOLINE == pCmdUI->m_nID);

	if (ID_DEBUG_GOTOLINE == pCmdUI->m_nID) 
	{
		if (false == IsLabelEdit_Selected())
		{
			GetToolbar() -> Enable (ID_DEBUG_GOTOLINE);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_GOTOLINE);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugNewdialog(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_NEWDIALOG == pCmdUI->m_nID);

	if (ID_DEBUG_NEWDIALOG == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_NEWDIALOG, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();
		if (iState == ES_IDLE && 
			g_SummitModuls[DLGEDIT].fIsInstalled && 
			(m_fBreakSet || m_fOtherFunction) &&
			false == IsLabelEdit_Selected())	
		{
			GetToolbar() -> Enable (ID_DEBUG_NEWDIALOG);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_NEWDIALOG);
			pCmdUI -> Enable (false);
		}
	}
}

void CDebuggerCtrl::OnUpdateDebugPaste(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_PASTE == pCmdUI->m_nID);

	if (ID_DEBUG_PASTE == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_PASTE, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();		
		if (iState == ES_IDLE && 
			::IsClipboardFormatAvailable (CF_TEXT)	&& 
			(m_fBreakSet || m_fOtherFunction) &&
			false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_PASTE);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_PASTE);
			pCmdUI -> Enable (false);
		}		
	}
}

void CDebuggerCtrl::OnUpdateDebugRecording(CCmdUI* pCmdUI)
{
}

void CDebuggerCtrl::OnUpdateDebugReplace(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_REPLACE == pCmdUI->m_nID);

	if (ID_DEBUG_REPLACE == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_REPLACE, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();
		if (iState == ES_IDLE && 
			m_pFRD == NULL	&& 
			(m_fBreakSet || m_fOtherFunction) &&
			false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_REPLACE);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_REPLACE);
			pCmdUI -> Enable (false);
		}		
	}
}

void CDebuggerCtrl::OnUpdateDebugSuspend(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_SUSPEND == pCmdUI->m_nID);

	if (ID_DEBUG_SUSPEND == pCmdUI->m_nID) 
	{
		int iState = GetDebugger() -> GetState();
		if ((iState == ES_IDLE && 
			(m_fBreakSet || m_fOtherFunction)) || 
			!g_SummitModuls[RUNTIME].fIsInstalled || 
			GetEditOnly()) 
		{
			GetToolbar() -> Disable (ID_DEBUG_SUSPEND);
			pCmdUI -> Enable (false);
		} 
		else 
		{
			GetToolbar() -> Enable (ID_DEBUG_SUSPEND);
			pCmdUI -> Enable (true);
		}		
	}
}

void CDebuggerCtrl::OnUpdateDebugSyntax(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_SYNTAX == pCmdUI->m_nID);

	if (ID_DEBUG_SYNTAX == pCmdUI->m_nID) 
	{
		int iState = GetDebugger() -> GetState();		
		if (iState == ES_IDLE && 
			g_SummitModuls[COMPILER].fIsInstalled	&& 
			m_fBreakSet &&
			false == IsLabelEdit_Selected() &&
			false == IsTreeFocused())	 
		{
			GetToolbar() -> Enable (ID_DEBUG_SYNTAX);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_SYNTAX);
			pCmdUI -> Enable (false);
		}		
	}
}

void CDebuggerCtrl::OnUpdateDebugGo(CCmdUI* pCmdUI)
{
	//if (S_OK == DisableIfClosedProject(ID_DEBUG_GO, pCmdUI)) return;
	UpdateGoOperations(pCmdUI, ID_DEBUG_GO);
}
void CDebuggerCtrl::OnUpdateDebugTracein(CCmdUI* pCmdUI)
{
	//if (S_OK == DisableIfClosedProject(ID_DEBUG_TRACEIN, pCmdUI)) return;
	UpdateGoOperations(pCmdUI, ID_DEBUG_TRACEIN);
}
void CDebuggerCtrl::OnUpdateDebugTraceover(CCmdUI* pCmdUI)
{
	//if (S_OK == DisableIfClosedProject(ID_DEBUG_TRACEOVER, pCmdUI)) return;
	UpdateGoOperations(pCmdUI, ID_DEBUG_TRACEOVER);
}

void CDebuggerCtrl::OnUpdateDebugUndo(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_UNDO == pCmdUI->m_nID);

	if (ID_DEBUG_UNDO == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_UNDO, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();			
		if (iState == ES_IDLE && 
			GetDebugger() -> CanUndo() && 
			(m_fBreakSet || m_fOtherFunction) &&
			false == IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_UNDO);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_UNDO);
			pCmdUI -> Enable (false);
		}		
	}
}

void CDebuggerCtrl::OnUpdateDebugFunctionInsert(CCmdUI* pCmdUI) 
{
	ASSERT(ID_DEBUG_FUNCTIONINSERT == pCmdUI->m_nID);

	if (ID_DEBUG_FUNCTIONINSERT == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_FUNCTIONINSERT, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();		
		if (iState == ES_IDLE && 
			(m_fBreakSet || m_fOtherFunction) &&
			false == IsTreeFocused() &&
			false == IsLabelEdit_Selected()) // Focus muss Tree besitzen 
		{
			pCmdUI -> Enable (true);
		} 
		else 
		{
			pCmdUI -> Enable (false);
		}		
	}	
}

//////////////////////////////////////////////////////////////////
//  Einfügeoperastionen
void CDebuggerCtrl::OnUpdateDebugImport(CCmdUI* pCmdUI)
{
	if (S_OK == DisableIfClosedProject(ID_DEBUG_IMPORT, pCmdUI)) return;
	UpdateImportOperations(pCmdUI, ID_DEBUG_IMPORT);
}
void CDebuggerCtrl::OnUpdateDebugFilterImport(CCmdUI* pCmdUI)
{
	if (S_OK == DisableIfClosedProject(ID_DEBUG_FILTERIMPORT, pCmdUI)) return;
	UpdateImportOperations(pCmdUI, ID_DEBUG_FILTERIMPORT);
}
void CDebuggerCtrl::OnUpdateDebugObjfeatimport(CCmdUI* pCmdUI)
{
	if (S_OK == DisableIfClosedProject(ID_DEBUG_OBJFEATIMPORT, pCmdUI)) return;
	UpdateImportOperations(pCmdUI, ID_DEBUG_OBJFEATIMPORT);
}
void CDebuggerCtrl::OnUpdateDebugInsert(CCmdUI* pCmdUI)
{
	if (S_OK == DisableIfClosedProject(ID_DEBUG_INSERT, pCmdUI)) return;
	UpdateInsertOperations(pCmdUI, ID_DEBUG_INSERT);
}
void CDebuggerCtrl::OnUpdateDebugFilterInsert(CCmdUI* pCmdUI)
{
	if (S_OK == DisableIfClosedProject(ID_DEBUG_FILTERINSERT, pCmdUI)) return;
	UpdateInsertOperations(pCmdUI, ID_DEBUG_FILTERINSERT);
}
void CDebuggerCtrl::OnUpdateDebugObjfeatinsert(CCmdUI* pCmdUI)
{
	if (S_OK == DisableIfClosedProject(ID_DEBUG_OBJFEATINSERT, pCmdUI)) return;
	UpdateInsertOperations(pCmdUI, ID_DEBUG_OBJFEATINSERT);
}

void CDebuggerCtrl::OnUpdateDebugRemove(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_REMOVE == pCmdUI->m_nID);

	if (ID_DEBUG_REMOVE == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_REMOVE, pCmdUI)) return;
	
		ModifyMenu(pCmdUI -> m_pMenu, IDS_DEBUG_REMOVE, ID_DEBUG_REMOVE);
	
		int iState = GetDebugger() -> GetState();		
		if (iState == ES_IDLE && 
			(m_fBreakSet || m_fOtherFunction) &&
			IsTreeFocused() &&					// Entfernen nur, wenn Tree den Focus besitzt
			false == GetInitNew() &&			// Bei Neuem automatisches Freigeben wenn anderer geöffnet wird 
			GetMainFrame() -> IsScript_Selected() &&
			false == IsLabelEdit_Selected())
		{
			if (false == IsRBTreeMenu())
				ModifyMenu(pCmdUI -> m_pMenu, IDS_DEBUG_REMOVEDATEI, ID_DEBUG_REMOVE, GetScriptName_Selected());
			GetToolbar() -> Enable (ID_DEBUG_REMOVE);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_REMOVE);
			pCmdUI -> Enable (false);
		}		
	}
}
////////////////////////////////////////////////////////////////////////////////////////
// Andere Funktionen
BOOL CDebuggerCtrl::ModifyMenu(CMenu *pMenu, int IDS, UINT uiMenuID, LPCSTR lpcstrName) 
{
	if (NULL == pMenu) return false;

	char Buffer[_MAX_PATH];
	CString str;
 
	if (! LoadString(str, IDS)) return false;

	if (NULL != lpcstrName) {	// IDS z.B. "%s Entfernen"
		CString strFileName = lpcstrName;
		strFileName = GetFileName(strFileName, false);
		wsprintf(Buffer, str, strFileName);
	} else {
		strcpy(Buffer, str);
	}
	return pMenu ->  ModifyMenu(uiMenuID, MF_STRING|MF_BYCOMMAND, uiMenuID, Buffer);
}

void CDebuggerCtrl::OnUpdateDebugNew(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_NEW == pCmdUI->m_nID);

	if (ID_DEBUG_NEW == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_NEW, pCmdUI)) return;

		int iState = GetDebugger() -> GetState();		
		if (iState == ES_IDLE && 
			(m_fBreakSet || m_fOtherFunction) &&
			false == IsTreeFocused() &&
			false == IsLabelEdit_Selected())// Focus muss auf Debugger zeigen 
		{
			GetToolbar() -> Enable (ID_DEBUG_NEW);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_NEW);
			pCmdUI -> Enable (false);
		}		
	}
}

void CDebuggerCtrl::OnUpdateDebugMRU(CMenu *pMenu, int nID, UINT uiMruID)
{
	if (uiMruID <= nID && uiMruID + 4 >= nID) 
	{
		if (S_OK == DisableIfClosedProject(nID, NULL, pMenu)) return;

		int iState = GetDebugger() -> GetState();		
		if (iState == ES_IDLE && 
			(m_fBreakSet || m_fOtherFunction) && 
			(IsScript_Selected() || false == IsTreeFocused()) &&
			false == IsLabelEdit_Selected())  
			pMenu -> EnableMenuItem (nID, MF_ENABLED);
		else 
			pMenu -> EnableMenuItem (nID, MF_GRAYED);
	}
}

void CDebuggerCtrl::OnUpdateDebugOpen(CCmdUI* pCmdUI)
{
	if (S_OK == DisableIfClosedProject(ID_DEBUG_OPEN, pCmdUI)) return;

	if (pCmdUI -> m_pMenu) {
		ModifyMenu(pCmdUI -> m_pMenu, IDS_DEBUG_OPEN, ID_DEBUG_OPEN);
		if (IsTreeFocused())
			ModifyMenu(pCmdUI -> m_pMenu, IDS_DEBUG_OPENTREE, ID_DEBUG_OPEN, GetScriptName_Selected());
		if (IsRBTreeMenu())
			ModifyMenu(pCmdUI -> m_pMenu, IDS_OPENRBTREE, ID_DEBUG_OPEN);
		if (IsRBTreeMenu() && FUNCTION_POPUPMENU_ID == GetPopUpMenuID())
			ModifyMenu(pCmdUI -> m_pMenu, IDS_OPENFUNCTIONRBTREE, ID_DEBUG_OPEN);
	}
	if (FAILED(UpdateOpenOperations(pCmdUI, ID_DEBUG_OPEN))) return;
}

void CDebuggerCtrl::OnUpdateDebugNewFile(CCmdUI* pCmdUI)
{
	if (S_OK == DisableIfClosedProject(ID_DEBUG_NEWFILE, pCmdUI)) return;
	UpdateOpenOperations(pCmdUI, ID_DEBUG_NEWFILE);
}
void CDebuggerCtrl::OnUpdateDebugSave(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_SAVE == pCmdUI->m_nID);

	if (ID_DEBUG_SAVE == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_SAVE, pCmdUI)) return;

		if (GetDirty() && !IsLabelEdit_Selected()) 
		{
			GetToolbar() -> Enable (ID_DEBUG_SAVE);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_SAVE);
			pCmdUI -> Enable (false);
		}	 
	}
}

void CDebuggerCtrl::OnUpdateDebugExportall(CCmdUI* pCmdUI) 
{
	ASSERT(ID_DEBUG_EXPORTALL == pCmdUI->m_nID);

	if (ID_DEBUG_EXPORTALL == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_EXPORTALL, pCmdUI)) return;

		if (false == IsLabelEdit_Selected())
			pCmdUI -> Enable (true);
		else
			pCmdUI -> Enable (false);
	}
}

void CDebuggerCtrl::OnUpdateDebugSaveas(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_SAVEAS == pCmdUI->m_nID);

	if (ID_DEBUG_SAVEAS == pCmdUI->m_nID) 
	{
		if (S_OK == DisableIfClosedProject(ID_DEBUG_SAVEAS, pCmdUI)) return;

		if (false == IsLabelEdit_Selected())
			pCmdUI -> Enable (true);
		else
			pCmdUI -> Enable (false);
	}
}

void CDebuggerCtrl::OnUpdateDebugGetHelpOn(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_GETHELPON == pCmdUI->m_nID);

	if (ID_DEBUG_GETHELPON == pCmdUI->m_nID) 
	{
		char KeyWord[MAXSTRLENGTH];
		if (GetDebugger() -> GetCaretWord(KeyWord, MAXSTRLENGTH) && 
			false == IsLabelEdit_Selected())
		{
			GetToolbar() -> Enable (ID_DEBUG_GETHELPON);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_GETHELPON);
			pCmdUI -> Enable (false);
		}	
	}
}

void CDebuggerCtrl::OnUpdateDebugEditorHelp(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_EDITORHELP == pCmdUI->m_nID);

	if (ID_DEBUG_EDITORHELP == pCmdUI->m_nID) 
	{
		if (false == IsLabelEdit_Selected())
		{
			GetToolbar() -> Enable (ID_DEBUG_EDITORHELP);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_EDITORHELP);
			pCmdUI -> Enable (false);
		}	
	}
}

void CDebuggerCtrl::OnUpdateDebugTriasHelp(CCmdUI* pCmdUI)
{
	ASSERT(ID_DEBUG_TRIASHELP == pCmdUI->m_nID);

	if (ID_DEBUG_TRIASHELP == pCmdUI->m_nID) 
	{
		if (false == IsLabelEdit_Selected())
		{
			GetToolbar() -> Enable (ID_DEBUG_TRIASHELP);
			pCmdUI -> Enable (true);
		} 
		else 
		{
			GetToolbar() -> Disable (ID_DEBUG_TRIASHELP);
			pCmdUI -> Enable (false);
		}	
	}
}

HRESULT CDebuggerCtrl::UpdateImportOperations(CCmdUI* pCmdUI, UINT ui)
{
	ASSERT(ui == pCmdUI->m_nID);
	ASSERT(pCmdUI);
	if (ui != pCmdUI->m_nID) return E_INVALIDARG; 
	if (NULL == pCmdUI) return E_POINTER;

	try
	{
		BOOL fNewChild = false;
		WTreeItem IT;
		if (NULL != GetChildItemSel(IT.ppi()))
		{
			WObjManHelper IOMH = IT;
			fNewChild = IOMH -> GetInitNew();
		}

		int iState = GetDebugger() -> GetState();		
		if (iState == ES_IDLE && 
			(m_fBreakSet || m_fOtherFunction) && 
			false == IsLabelEdit_Selected() &&
			false == GetInitNew_Selected() &&
			false == fNewChild)	
		{
			pCmdUI -> Enable (true);
			if (pCmdUI -> m_pMenu)
				pCmdUI -> m_pMenu -> EnableMenuItem (MENUPOS_IMPORTLINK, MF_BYPOSITION | MF_ENABLED);
		}
		else
		{
			pCmdUI -> Enable (false);
			if (pCmdUI -> m_pMenu)
				pCmdUI -> m_pMenu -> EnableMenuItem (MENUPOS_IMPORTLINK, MF_BYPOSITION | MF_GRAYED);
		}
	}
	catch(_com_error & e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CDebuggerCtrl::UpdateGoOperations(CCmdUI* pCmdUI, UINT ui)
{
	ASSERT(ui == pCmdUI->m_nID);

	if (ui == pCmdUI->m_nID) 
	{
		int iState = GetDebugger() -> GetState();		
		if (iState == ES_EXECUTING || 
			!g_SummitModuls[RUNTIME].fIsInstalled	|| 
			(!m_fBreakSet && !m_fOtherFunction) || 
			GetEditOnly() ||
			IsLabelEdit_Selected())	
		{
			GetToolbar() -> Disable (ui);
			pCmdUI -> Enable (false);
		} 
		else 
		{
			GetToolbar() -> Enable (ui);
			pCmdUI -> Enable (true);
		}		
	}
	return S_OK;
}
HRESULT CDebuggerCtrl::UpdateInsertOperations(CCmdUI* pCmdUI, UINT ui)
{
	ASSERT(ui == pCmdUI->m_nID);

	try
	{
		BOOL fNewChild = false;
		WTreeItem IT;
		if (NULL != GetChildItemSel(IT.ppi()))
		{
			WObjManHelper IOMH = IT;
			fNewChild = IOMH -> GetInitNew();
		}

		if (ui == pCmdUI->m_nID) 
		{
			int iState = GetDebugger() -> GetState();		
			if (iState == ES_IDLE && 
				(m_fBreakSet || m_fOtherFunction) &&
				/*IsTreeFocused() && */// Focus muss Tree besitzen 
				false == IsLabelEdit_Selected() &&
				false == GetInitNew_Selected() &&
				false == fNewChild)
			{
				GetToolbar() -> Enable (ui);
				pCmdUI -> Enable (true);
			} 
			else 
			{
				GetToolbar() -> Disable (ui);
				pCmdUI -> Enable (false);
			}		
		}	
	}
	catch(_com_error &e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}
HRESULT CDebuggerCtrl::UpdateOpenOperations(CCmdUI* pCmdUI, UINT ui)
{
	ASSERT(pCmdUI);
	ASSERT(ui == pCmdUI->m_nID);
	if (ui != pCmdUI->m_nID) return E_INVALIDARG; 
	if (NULL == pCmdUI) return E_POINTER;

	int iState = GetDebugger() -> GetState();		
	if (iState == ES_IDLE && 
		(m_fBreakSet || m_fOtherFunction) && 
		(IsFunction_Selected() || IsScript_Selected() || false == IsTreeFocused()) &&
		false == IsLabelEdit_Selected())
	{
		GetToolbar() -> Enable (ui);
		pCmdUI -> Enable (true);
	}
	else
	{
		pCmdUI -> Enable (false);
		GetToolbar() -> Disable (ui);
	}
	return S_OK;
}

HRESULT CDebuggerCtrl::DisableIfClosedProject(UINT ui, CCmdUI* pCmdUI, CMenu *pMenu)
{
	if (g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject()) return S_FALSE;

	if (pCmdUI) pCmdUI -> Enable (false);
	if (GetToolbar()) GetToolbar() -> Disable (ui);
	if (pMenu) pMenu -> EnableMenuItem (ui, MF_GRAYED);
	return S_OK;
}

BOOL CDebuggerCtrl::IsRBTreeMenu()
{
	return GetMainFrame() -> IsRBTreeMenu();
}
void CDebuggerCtrl::SetRBTreeMenu(BOOL f)
{
	GetMainFrame() -> SetRBTreeMenu(f);
}

HRESULT CDebuggerCtrl::CanOpen()
{
	int iState = GetDebugger() -> GetState();		
	if (iState == ES_IDLE && 
		(m_fBreakSet || m_fOtherFunction) && 
		g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject())
	{
		return S_OK;
	}
	return S_FALSE;
}
HRESULT CDebuggerCtrl::CanRemove()
{
	int iState = GetDebugger() -> GetState();		
	if (iState == ES_IDLE && 
		(m_fBreakSet || m_fOtherFunction) &&
		IsTreeFocused() &&					// Entfernen nur, wenn Tree den Focus besitzt
		!GetInitNew() &&					// Bei Neuem automatisches Freigeben wenn anderer geöffnet wird 
		GetMainFrame() -> IsScript_Selected() &&
		!IsLabelEdit_Selected() &&
		g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject())
	{
		return S_OK;
	}
	return S_FALSE;
}
HRESULT CDebuggerCtrl::CanImport()
{
	int iState = GetDebugger() -> GetState();		
	if (iState == ES_IDLE && 
		(m_fBreakSet || m_fOtherFunction) && 
		(IsScript_Selected() || !IsTreeFocused()) &&
		!IsLabelEdit_Selected() &&
		g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject())
	{
		return S_OK;
	}
	return S_FALSE;
}
HRESULT CDebuggerCtrl::CanInsert()
{
	int iState = GetDebugger() -> GetState();		
	if (iState == ES_IDLE && 
		(m_fBreakSet || m_fOtherFunction) &&
		IsTreeFocused() &&
		!IsLabelEdit_Selected() &&
		g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject()) // Focus muss Tree besitzen 
	{
		return S_OK;
	} 
	return S_FALSE;
}
HRESULT CDebuggerCtrl::CanEdit()
{
	int iState = GetDebugger() -> GetState();		
	if (iState == ES_IDLE && 
		(m_fBreakSet || m_fOtherFunction) &&
		!IsLabelEdit_Selected() &&
		g_pBSE -> GetRunningObjectsHelper() -> GetOpenProject())
	{
		return S_OK;
	} 
	return S_FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////
// Editorfunktionen
LRESULT CDebuggerCtrl :: FindNext()
{
	if (-1 == GetDebugger() -> FindText(m_strFindText,m_bUpDown,m_bMatchCase, m_bMatchWholeWord) ) {		
		if (m_bUpDown) {
			OutputReachedEOF();
			GetDebugger() -> SetCaretPos (0, 0, false);

			if (-1 == GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) )
				OutPutNoMatch(m_strFindText);
		}
		else {
			OutputReachedBOF();
			GetDebugger() -> SetCaretPos (0, GetDebugger() -> GetNumLines()+1, false);

			if (-1 == GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) )
				OutPutNoMatch(m_strFindText);
		}
	}

return 1;
}
LRESULT CDebuggerCtrl :: ReplaceAll(const CString &str)
{
	GetDebugger() -> SetCaretPos (0, 0, false);

	if (-1 == GetDebugger() -> FindText (m_strFindText, true, m_bMatchCase, m_bMatchWholeWord) ) { 
		OutPutNoMatch(m_strFindText); return 1; 
	} 
	GetDebugger() -> ReplaceSelection (str, 0);			
	
	while (-1 != GetDebugger() -> FindText (m_strFindText, true, m_bMatchCase, m_bMatchWholeWord) ) 
		GetDebugger() -> ReplaceSelection (str, 0);

	OutputReachedEOF();

return 1;
}
LRESULT	CDebuggerCtrl :: ReplaceCurrent(const CString &str)
{
DWORD dwCursorPos = GetDebugger() -> GetCursorPos ();			
int ix = LOWORD (dwCursorPos), iy = HIWORD (dwCursorPos), iLength = m_strFindText.GetLength()+1;
	
	if (ix - iLength < 0) ix = 0;
	else ix = ix-iLength;
	GetDebugger() -> SetCaretPos (ix, iy);
	
	if (-1 !=  GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) ) {
		GetDebugger() -> ReplaceSelection (str, 0);
		if (-1 == GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) ) {
			if (m_bUpDown) {
				OutputReachedEOF();
				GetDebugger() -> SetCaretPos (0, 0, false);
				GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord);
			}
			else {
				OutputReachedBOF();
				GetDebugger() -> SetCaretPos (0, GetDebugger() -> GetNumLines()+1, false);
				GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord);
			}
		}
	}
	else {		
		if (m_bUpDown) {
			OutputReachedEOF();
			GetDebugger() -> SetCaretPos (0, 0, false);

			if (-1 != GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) ) {
				GetDebugger() -> ReplaceSelection (str, 0);
				if (-1 == GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) )
					OutputReachedEOF();
			}
			else
				OutPutNoMatch(m_strFindText);
		}		
		else {
			OutputReachedBOF();
			GetDebugger() -> SetCaretPos (0, GetDebugger() -> GetNumLines()+1, false);

			if (-1 != GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) ) {
				GetDebugger() -> ReplaceSelection (str, 0);
				if (-1 == GetDebugger() -> FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) )
					OutputReachedBOF();
			}
			else
				OutPutNoMatch(m_strFindText);
		}
	}
	
return 1;
}
LRESULT CDebuggerCtrl :: OnCallbackFindReplace(WPARAM wParam, LPARAM lParam)
{	
	ASSERT(m_pFRD);

	GetStatusbar() -> SetPaneText (0, g_cbNil, true );

	CString strReplaceWithText;

	if (m_pFRD -> IsTerminating()) 
	{
		CString str;
		if (!::LoadString (str, ID_STATUSBAR_PANE1)) return 0;
		GetStatusbar() -> SetPaneText (0, str, true);		
		m_pFRD = NULL;
		return 1;
	}
	else 
	{		
		m_pFRD -> UpdateWindow();		
		m_bMatchCase = m_pFRD -> MatchCase();			
		m_bUpDown = m_pFRD -> SearchDown();
		m_bMatchWholeWord = m_pFRD -> MatchWholeWord();
		
		m_strFindText = m_pFRD -> GetFindString();
		if(m_strFindText.IsEmpty()) return 0;

		strReplaceWithText = m_pFRD -> GetReplaceString();		
	}
 
	TRY {
		if (m_pFRD->FindNext())
			FindNext();
		else if (m_pFRD -> ReplaceAll()) 
			ReplaceAll(strReplaceWithText);
		else if (m_pFRD -> ReplaceCurrent())
			ReplaceCurrent(strReplaceWithText);		
		else ASSERT (0);

	} CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return 0;
	} END_CATCH;

	::SetFocus(m_pFRD -> GetSafeHwnd());

return 1;
}
LONG CDebuggerCtrl::OutPutNoMatch (CString & strFind)
{
	TRY {
	CString str; str.LoadString (IDS_TEXTNOTFOUND);
	CString strCap; strCap.LoadString (IDS_LONGCLASSNAME);
	CString strOut;

		strOut.Format (str, (LPCSTR)strFind); 
		MessageBox (strOut, strCap, MB_OK | MB_ICONINFORMATION);

	} CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return 0;
	} END_CATCH;
	
return 1;
}
void CDebuggerCtrl::OutputReachedEOF(void)
{
CString str;

	if (!::LoadString (str, IDS_REACHEDEOF)) return;
	GetStatusbar() -> SetPaneText (0, str, true );
	GetDebugger() -> SetCaretPos ( 0, 0, false);	
}
void CDebuggerCtrl::OutputReachedBOF(void)
{
CString str;

	if (!::LoadString (str, IDS_REACHEDBOF)) return;
	GetStatusbar() -> SetPaneText (0, str, true );
	GetDebugger() -> SetCaretPos ( 0, 0, false);	
}

///////////////////////////////////////////////////////////////////////////////
// Scriptbeendigung
LRESULT CDebuggerCtrl::OnEndScript(WPARAM wParam, LPARAM lParam)
{
	if (m_fBreakSet) 
	{
		HRESULT hr = RunUnLoadScript(lParam);
		if (FAILED(hr)) return 0;
	}
	return 1;
}

//
// *** Hilfe ***
//
HRESULT CDebuggerCtrl::LookupKeyword(LPCSTR lpKeyWord, int & id)
{
LPSTR lpszTemplateName = MAKEINTRESOURCE(AZ_KEYWORDS);
HANDLE hMem = NULL;
HINSTANCE hInst = NULL;
HRSRC hResource = NULL;

	// find the resrouce in my EXE
	hInst = AfxFindResourceHandle(lpszTemplateName, RT_RCDATA);
	if (hInst == NULL) return ResultFromScode(E_HANDLE);

	hResource = ::FindResource(hInst, lpszTemplateName, RT_RCDATA);

DWORD dwE = GetLastError();

	if (hResource == NULL) return ResultFromScode(E_HANDLE);
	
	// allocate memory for it and load it in
	hMem = LoadResource(hInst, hResource);
	if (hMem == NULL) return ResultFromScode(E_HANDLE);

BYTE FAR *lpMem;
char buf[80];

	// lock it
	lpMem = (BYTE FAR *)LockResource(hMem);

	id = -1;

	// get the default ID, in the case that the keyword isn't found
	id = *lpMem++;			// watch out for alignment!
	id |= *lpMem++ << 8;

	while (*lpMem) {
	
		strcpy(buf,(LPCSTR)lpMem);

		while (*lpMem) lpMem++;
		lpMem++;	// skip to ID

		if (!_stricmp(lpKeyWord, buf)) {
			// save the id for returning to caller
			id = *lpMem++;			// watch out for alignment!
			id |= *lpMem << 8;
			break;
		}
		else {
			// skip the id
			lpMem += sizeof(WORD);
		}
	}

	// get rid of the resource (it may hang around a while)
	UnlockResource(hMem);
	FreeResource(hMem);

return NOERROR;	// return id to caller
}

HRESULT CDebuggerCtrl::KeywordHelp(LPCSTR lpKeyWord)
{
CString strPath;
HRESULT hr = GetHelpFile(strPath, g_cbAZHelp);
	if (FAILED(hr)) return hr;

int id = -1;
	hr = LookupKeyword(lpKeyWord, id);
	if (SUCCEEDED(hr)) {
		if (!::WinHelp(m_hWnd, strPath, HELP_CONTEXT, id)) {
			ASSERT(0); return ResultFromScode(E_FAIL);
		}
	}
	else {
		if (!::WinHelp(m_hWnd, strPath, HELP_CONTENTS, 0L)) {
			ASSERT(0); return ResultFromScode(E_FAIL);
		}
	}

return NOERROR;
}

HRESULT CDebuggerCtrl::DebuggerHelp()
{
CString strPath;
HRESULT hr = GetHelpFile(strPath, g_cbDDHelp);
	if (FAILED(hr)) return hr;

	if (!::WinHelp(m_hWnd, strPath, HELP_CONTENTS, 0L)) {
			ASSERT(0); return ResultFromScode(E_FAIL);
	}

return NOERROR;
}

HRESULT CDebuggerCtrl::TriasHelp()
{
CString strPath;
HRESULT hr = GetHelpFile(strPath, g_cbMPHelp);
	if (FAILED(hr)) return hr;

	if (!::WinHelp(m_hWnd, strPath, HELP_CONTENTS, 0L)) {
			ASSERT(0); return ResultFromScode(E_FAIL);
	}

return NOERROR;
}

HRESULT CDebuggerCtrl::GetHelpFile(CString & strPath, LPCSTR pcFileName)
{
CString strName;
LPSTR pcStartupDir = strName.GetBuffer(MAXSTRLENGTH); 

	GetModuleFileName(NULL, pcStartupDir, MAXSTRLENGTH);	
	strPath = GetPathName (strName) + g_cbDel + pcFileName;

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////////
// allgemeine Member
HRESULT CDebuggerCtrl::EnumFunctions(HTREEITEM hItem)
{
	return GetMainFrame() -> EnumFunctions (hItem);
}

BOOL CDebuggerCtrl::DeleteWatchVariables (void)		// alle Watches entfernen
{
	char cbVarName[VARNAMESZ];
// delete the first watch variable until there aren't any more
	while (GetDebugger() -> GetFirstWatch (cbVarName, VARNAMESZ)) 
	{
		if (!GetDebugger() -> DeleteWatch (cbVarName))
			break;
	}
	GetDebugger() -> SetWatchWindowHeight (0);

return true;
}

LONG CDebuggerCtrl::GetBreakFlag()
{
	if (m_fRunModal) return 1;

	HWND hWnd = GetDebugger() -> GetWindow();
	ASSERT(hWnd);
	if (hWnd == NULL) return -1;

	ebHTHREAD hThread =	ebDebugger_GetThread(hWnd, false);
	ASSERT(hThread);
	if (hThread == NULL) return -1;

return ebThread_GetLong(hThread, 0);
}

BOOL CDebuggerCtrl::IsWatch()
{
	char Name[MAXSTRLENGTH];
	if (GetDebugger() -> GetFirstWatch(Name, MAXSTRLENGTH))
		return true;
return false;
}

BOOL CDebuggerCtrl::DebuggerEnd(void)
{
	if (!AskSave()) return false;// Cancel
	SaveRegSettingsFont();
	ResetFont();
	// end execution, if something is currently executing
	// Message "end" an den Debugger, warten in ExeEnd(), dann entgültig schliessen	
	if (GetDebugger() -> GetState() == ES_EXECUTING || GetDebugger() -> GetState() == ES_SUSPENDED) {
		GetDebugger() -> EndScript();
	// script currently executing, set state to resend CLOSE later on
		m_fSendClose = true; 
		return false; // Script erst nach Notification ExeEnd() schliessen
	} 
	// Damit RunUnLoad gerufen wird
	m_fBreakSet = true;
	OnEndScript(0,GO);// Entry "EndScript" rufen
	return true;
}

//////////////////////////////////////////////////////////
// Save, Load

int CDebuggerCtrl::AskSave()
{// Fragt und speichert
	int iAsk = GetMainFrame() -> AskSave();
	m_fAskSave = true;
	return iAsk;
}

BOOL CDebuggerCtrl::GetScript (LPSTR *ppText, ebHCODE *phCode, DWORD & dwSaveFlag)
{// zum Speichern bei Save ktuelle Daten aus Debugger holen
	*phCode = NULL;
	*ppText = NULL;

	try
	{
		int iLen = GetDebugger() -> GetTextLength();
		// wenn text zu groß oder 0 RAUS
		THROW_FAILED_HRESULT(MessageBoxBadText(this->GetSafeHwnd(), iLen));
		// aktuellen Text besorgen
		// einen für die 0 mehr allocieren
		*ppText = (LPSTR) CoTaskMemAlloc(iLen+1);
		if  (NULL == *ppText) _com_issue_error(E_OUTOFMEMORY);

		if (!GetDebugger() -> GetText (*ppText, iLen+1)) _com_issue_error(E_FAIL);				
		(*ppText)[iLen] = '\0';
		// Text o.k.
		dwSaveFlag |= CC_SCRIPT;

		// Script für alle Fälle noch mal kompilieren
		if (!GetDebugger() -> Compile()) _com_issue_error(S_FALSE);
		// Code geben lassen
		*phCode = GetDebugger() -> GetCode (false); 
		iLen = ebCode_GetSize(*phCode);
		// Wenn nach erfolgreichem Compile Code NULL, RAUS !!!
		if (NULL == *phCode || 0 == iLen) _com_issue_error(E_FAIL);
		// aktuellen Code für TreeItem setzen 
		THROW_FAILED_HRESULT(SetCode(*phCode));
		
		dwSaveFlag |= CC_CODE;
	}	
	catch (_com_error& e)
	{
		if (FAILED(_COM_ERROR(e))) 
		{
			if (*ppText) CoTaskMemFree (*ppText); *ppText = NULL; 
			return false;
		}
		// Kann auch S_FALSE sein
		return true;
	}
	return true;
}

BOOL CDebuggerCtrl::SetScript (LPSTR lpstr, ebHCODE hCode)
{
	COTASKMEMFREE(hCode); 

	if (NULL != lpstr)
	{// Alten Text belassen
		///ResetDebuggerMember();// CoTaskMemFree(...
		// Kann eigentlich auch weg (SetCode(NULL), wer weiss wozu ich's noch brauche
		//m_hCode = hCode;
		//m_pText = lpstr;
		GetDebugger() -> SetText (lpstr); 
		GetDebugger() -> SetCode (NULL); // Erzwingen, dass immer Kompiliert wird !!!
		// Text freigeben
		COTASKMEMFREE(lpstr); 
	}
		
	SetPosition ();

	return true;
}

BOOL CDebuggerCtrl::SetPosition ()
{
	int ix = 0, iy = 0;
	int fSelect = 0;
	
	GetInitCaretPos (ix, iy, fSelect);
	GetDebugger() -> SetCaretPos (ix, iy);

	if (fSelect)
	{
		GetDebugger() -> SetCaretPos (ix+fSelect, iy, true);
	}

	return true;
}

///////////////////////////////////////////////////////
// Registry
BOOL CDebuggerCtrl::ReadRegSettingsFont (LPLOGFONT pLF)
{
	CString strBuffer;
	LPTSTR pcBuffer = NULL;

	TRY {                                       
		pcBuffer = strBuffer.GetBuffer( MAXSTRLENGTH ); 
		if (pcBuffer == NULL) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH
	
DWORD dwL = MAXSTRLENGTH;
CCurrentUser regBS (KEY_READ, g_cbCfgKey);

	if (!regBS.GetSubSZ (g_cbFont, pcBuffer, dwL)) 
		return false;
	return ParseFontInfo (pcBuffer, pLF);
}

BOOL CDebuggerCtrl::ParseFontInfo (LPSTR pBuffer, LPLOGFONT pLF)
{
	if (pBuffer == NULL || *pBuffer == '\0') return false;  
	if (pLF == NULL) return false;

	char *pStr = strtok (pBuffer, g_cbFmtDel);

	if (NULL == pStr) return false;
	pLF -> lfHeight = atoi (pStr);
	
	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pLF -> lfWidth = atoi (pStr);

	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pLF -> lfWeight = atoi (pStr);

	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pLF -> lfItalic = atoi (pStr) ? true : false;

	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	strncpy (pLF -> lfFaceName, pStr, LF_FACESIZE);
	pLF -> lfFaceName[LF_FACESIZE-1] = '\0';

return true;
}

BOOL CDebuggerCtrl::SaveRegSettingsFont ()
{
LOGFONT LF;
char cBuffer[MAXSTRLENGTH];
CCurrentUser regBS (g_cbCfgKey);

	LF.lfFaceName[0] = 0;		//font information
	if  (0 == GetObject (GetDebugger() -> GetFont(), sizeof (LOGFONT), &LF))
		return false;

// save in reg file...
	wsprintf(cBuffer, g_cbFontFmt, LF.lfHeight, LF.lfWidth, LF.lfWeight, LF.lfItalic, LF.lfFaceName);
	return regBS.SetSubSZ (g_cbFont, cBuffer);
}


BOOL CDebuggerCtrl::GetWhichEntryMayRun()
{
	if (m_fRunModal) 
		return true;

	char EntryName[MAXSTRLENGTH];
	CString strLoad, strUnload, strMain;
	if (!LoadString(strLoad, IDS_LOADSCRIPT) ||
		!LoadString(strUnload, IDS_UNLOADSCRIPT) ||
		!LoadString(strMain, IDS_MAIN)) {
		return false;
	}

	m_EInfo.GetEntryName(EntryName);
	if (0 == _stricmp(EntryName, strLoad)) {
		m_fLoadIsRun = false;
		m_fMainIsRun = true;
		m_fUnLoadIsRun = false;
	} else if (0 == _stricmp(EntryName, strMain)) {
		m_fLoadIsRun = false;
		m_fMainIsRun = false;
		m_fUnLoadIsRun = true;
		// nur einmal für alle nach Speichern fragen
		m_fAskSave = false;
	} else if (0 == _stricmp(EntryName, strUnload)) {
		m_fLoadIsRun = true;
		m_fMainIsRun = false;
		m_fUnLoadIsRun = false;
	}

return true;
}

//////////////////////////////////////////////////////////
// Hilfsfunktionen RUNNING
BOOL CDebuggerCtrl::ResetEntryInfo()
{
CString str;

	if (!LoadString(str, IDS_MAIN)) return false;

	m_EInfo.SetEntryName(str); // "Main()"
	m_EInfo.GetEntryInfo() -> dwEntry = 0;
	m_EInfo.GetEntryInfo() -> wParms = 0;
	m_EInfo.GetEntryInfo() -> lpParms = NULL;
	m_EInfo.GetEntryInfo() -> RetParm.wType = 0;
	m_EInfo.GetEntryInfo() -> isFunc = 0;	// Sub and not a Function
	
	GetDebugger() -> SetEntryPoint (m_EInfo.GetEntryInfo());	

return true;
}

BOOL CDebuggerCtrl::SetEntryPointLoadScript()
{
HRESULT hr = NOERROR;
CString str;

	if (!ResetEntryInfo()) return false;
	if (!LoadString(str, IDS_LOADSCRIPT)) return false;

	m_EInfo.SetEntryName(str);	
	GetDebugger() -> SetEntryPoint (m_EInfo.GetEntryInfo());	

return true;
}

BOOL CDebuggerCtrl::SetEntryPointUnLoadScript()
{
HRESULT hr = NOERROR;
CString str;

	if (!ResetEntryInfo()) return false;
	if (!LoadString(str, IDS_UNLOADSCRIPT)) return false;

	m_EInfo.SetEntryName(str);
	GetDebugger() -> SetEntryPoint (m_EInfo.GetEntryInfo());	

return true;
}

HRESULT CDebuggerCtrl::RunScript(int iKindOfProcess)
{
HRESULT hr = NOERROR;

	hr = RunLoadScript(iKindOfProcess);
	if (FAILED(hr)) return hr;
	hr = RunMain(iKindOfProcess);
	if (FAILED(hr)) return hr;

// "m_fBreakSet" vorher schon in entweder StartScript() oder Main() gemerkt !!!
	OnEndScript(0,iKindOfProcess);

return NOERROR;
}

HRESULT CDebuggerCtrl::RunMain(int iKindOfProcess)
{
	if (false == m_fMainIsRun) return S_FALSE;

	// "Main()" als Entry setzen, ausnullen
	ResetEntryInfo();

	ebHCODE hCode = NULL;
	
	hCode = m_Debug.GetCode(false);	
	ASSERT(NULL != hCode);

	if (ebCheckEntry(hCode, m_EInfo.GetEntryInfo())) {
		m_fLoadIsRun = false;
		m_fMainIsRun = false;
		m_fUnLoadIsRun = true;
		return S_FALSE;
	}


	if (TRACEINTO == iKindOfProcess) {
		m_Debug.TraceInto();
	} else if (TRACEOVER == iKindOfProcess) {
		m_Debug.StepOver();
	} else if (GO == iKindOfProcess) {
		m_Debug.StartScript();
	}

return NOERROR;
}

HRESULT CDebuggerCtrl::RunLoadScript(int iKindOfProcess)
{
	if (false == m_fLoadIsRun) return S_FALSE;

	if (!SetEntryPointLoadScript()) 
		return E_FAIL;
	
ebHCODE hCode = NULL;
	
	hCode = m_Debug.GetCode(false);	
	ASSERT(NULL != hCode);

	if (ebCheckEntry(hCode, m_EInfo.GetEntryInfo())) {
		m_fLoadIsRun = false;
		m_fMainIsRun = true;
		m_fUnLoadIsRun = false;
		return S_FALSE;
	}

	if (TRACEINTO == iKindOfProcess) {
		m_Debug.TraceInto();
	} else if (TRACEOVER == iKindOfProcess) {
		m_Debug.StepOver();
	} else if (GO == iKindOfProcess) {
		m_Debug.StartScript();
	}

return NOERROR;
}

HRESULT CDebuggerCtrl::RunUnLoadScript(int iKindOfProcess)
{	
	if (false == m_fUnLoadIsRun && ABORT != iKindOfProcess) return S_FALSE;

	if (!SetEntryPointUnLoadScript()) return E_FAIL;

	ebHCODE hCode = NULL;
	hCode = m_Debug.GetCode(false);	
	ASSERT(NULL != hCode);
	if (NULL == hCode || ebCheckEntry(hCode, m_EInfo.GetEntryInfo()) || ABORT == iKindOfProcess)
	{
		m_fLoadIsRun = true;
		m_fMainIsRun = false;
		m_fUnLoadIsRun = false;
		return S_FALSE;
	}
	
	if (TRACEINTO == iKindOfProcess) {
		m_Debug.TraceInto();
	} else if (TRACEOVER == iKindOfProcess) {
		m_Debug.StepOver();
	} else if (GO == iKindOfProcess) {
		m_Debug.StartScript();
	}


	return NOERROR;
}

// darf NUR bei Unload() gerufen werden !!!
HRESULT CDebuggerCtrl::GetMethodType()
{
	ebHCODE hCode = m_Debug.GetCode();
	ASSERT(NULL != hCode);

	ebPROCINFO PI;
	ebBOOL fNext = true;

	ebHENUM hEnum = ebGetFirstProc(hCode, &PI);
	
	if (hEnum == NULL) return E_FAIL;

	CString strUnLoad;
		
	if (!LoadString(strUnLoad, IDS_UNLOADSCRIPT))
		return E_FAIL;

	while (fNext) {
		if (0 == _stricmp (strUnLoad, PI.szName)) {
			if (1 == PI.wType) {
				ebEnumClose(hEnum);
				return E_FAIL;
			}
		}
		fNext = ebGetNextProc(hEnum, &PI);
	}		
	
	ebEnumClose(hEnum);

return NOERROR;
}

///////////////////////////////////////////////////////////////////////
// Related Scripts-Bearbeitung
void CDebuggerCtrl::DeleteRelated()
{
	if (NULL != m_pRelGeneralScripts) delete m_pRelGeneralScripts;
	m_pRelGeneralScripts = NULL;
	if (NULL != m_lpstrRequestorName) CoTaskMemFree(m_lpstrRequestorName); m_lpstrRequestorName = NULL;

}
HRESULT CDebuggerCtrl::SwitchManagement(IObjectManagement *pIOM, IStreamInfo *pISI)
{
	try 
	{// delete m_pRelGeneralScripts
		DeleteRelated();
		m_pRelGeneralScripts = new CRelScripts();
		if (NULL == m_pRelGeneralScripts) _com_issue_error(E_POINTER);

		m_lpstrRequestorName = (LPSTR)CoTaskMemAlloc(_MAX_PATH);
		if (NULL == m_lpstrRequestorName) _com_issue_error(E_OUTOFMEMORY);

		m_pRelGeneralScripts -> SetStorageManagement(pIOM, pISI); 
		// Diese Related-Scripts für RequestorProc setzen
		THROW_FAILED_HRESULT(SwitchRelated());
		// zumindest Management merken
		m_IObjManagement = pIOM;
	}
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	}		
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CDebuggerCtrl::SwitchRelated()
{
	ASSERT(NULL != GetBSInstance());
	ASSERT(NULL != m_pRelGeneralScripts);
	if (NULL == GetBSInstance() || NULL == m_pRelGeneralScripts) return E_UNEXPECTED;

	GetBSInstance() -> SetRequestorProc(RequestorProc, (LPARAM)m_pRelGeneralScripts);
	GetBSInstance() -> SetLinkOptions(LO_CALLREQUESTORBEFORE);
	return S_OK;
}

HRESULT CDebuggerCtrl::AddRelatedScript()
{
	if (NULL == m_pRelGeneralScripts || GetInitNew()) return S_FALSE; // Neues kann keine Related haben
	return 	m_pRelGeneralScripts -> Add(GetScriptName());
}
HRESULT CDebuggerCtrl::DeleteRelatedScript()
{
	if (NULL == m_pRelGeneralScripts || GetInitNew()) return S_FALSE; // Neues kann keine Related haben
	return 	m_pRelGeneralScripts -> Delete(GetScriptName());
}

/////////////////////////////////////////////////////////////////
// Externe Scripts starten
/////////////////////////////////////////////////////////////////
HRESULT CDebuggerCtrl::RunThread(LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	int iState = GetDebugger() -> GetState();
	HRESULT hr = NOERROR; 
	
	switch (iState) 
	{
	case ES_EXECUTING:	// Debugger ist busy, do it your self
		{
			ebHCODE hCode = GetDebugger() -> GetCode (false);					
			if(NULL == hCode) return E_HANDLE;
	
			ebHSCRIPT hScript = ebDebugger_GetScript(m_hWnd, false);		
			if (hScript == NULL) return E_HANDLE;

		CebEntryInfo EI;
		CBSParamCopy BSParam (iNumParams, pPars);

			BSParam.RemoveModsParam();
			hr = SetEntryInfo(EI, pEntry, iNumParams, BSParam);		
			if (FAILED(hr)) return hr;		
		
		// EntryPoint überprüfen
			if (ebCheckEntry ((ebHOBJECT)hCode, EI.GetEntryInfo()))return S_FALSE;
			EI.SetEntryName (TEXT(""));		// optimierten Entry verwenden
		
		// Thread erzeugen
			CebThread Thread (hScript, EI.GetEntryInfo());
			if (Thread.Create(CREATETHREAD_EXTRA)) 
				return ResultFromScode (E_FAIL);
			Thread.SetRuntimeErrorProc(&OnRuntimeError, 0);
		
		// Parameter setzen
			for (int i = 1; i <= iNumParams; i++) 
				SetParam (Thread, i, pPars -> pTypes[i], pPars -> pValues[i]);		

		// eigenliches RUN: Routine rufen, bis die CallbackFunktion erfolgreich abgeschlossen wurde
			hr = ::RunThread(Thread.GetHandle(), hScript);
			if (FAILED(hr)) return hr;

		LONG iError = Thread.GetErrorNumber();
		LONG iLine = Thread.GetErrorLine();
	
		// evtl. Rückgabewert abfragen
			if (pPars -> pTypes[0].wType != 0) 
				GetParam (Thread, 0, pPars -> pTypes[0], pPars -> pValues[0], true);

		// evtl. Parameter zurückschreiben
			for (int iOut = 1; iOut <= iNumParams; iOut++) {
				if (pPars -> pTypes[iOut].wType & TYP_MODSPARM)
					GetParam (Thread, iOut, pPars -> pTypes[iOut], pPars -> pValues[iOut], true, true);
			}

			for (iOut = 0; iOut <= iNumParams; iOut++) {
			// Parameter ausnullen, damit eventuelle AppObjektpointer nicht released werden: 
				if (pPars && pPars -> pTypes && TYP_APPOBJECT == pPars -> pTypes[iOut].wType) 
				{
					DWORD dw = 0L;
					SetParam (Thread, iOut, pPars -> pTypes[iOut], &dw);
				}
			}
		}
		break;

	case ES_IDLE:		// das ganze dem Debugger überlassen
		{		
		CebEntryInfo EI;
		char cbEntry[ENTRYNAMESZ];
		CBSParamCopy BSParam (iNumParams, pPars);

			BSParam.RemoveModsParam();
			
			EI.GetEntryName (cbEntry);		
			hr = SetEntryInfo(EI, pEntry, iNumParams, BSParam);
			if (FAILED(hr)) return hr;
		
		// für EntryPoint überprüfen
		ebHCODE hCode = GetDebugger() -> GetCode (false);					

			if (hCode == NULL || ebCheckEntry ((ebHOBJECT)hCode, EI.GetEntryInfo())) return ResultFromScode(S_FALSE);
		
			GetDebugger() -> SetEntryPoint (EI.GetEntryInfo());
			SetOtherFunction(true);

		///////////////////////////////////////////////
		// eigentliches Starten des Threads im Debugger
			if (SetParams (iNumParams, pPars)) 
				GetDebugger() -> StartScript();							

		// alten Startpunkt wieder einstellen (Sub Main())
			EI.SetEntryName (cbEntry);
			GetDebugger() -> SetEntryPoint (EI.GetEntryInfo());
			ResetParams();			
		}
		break;

	case ES_SUSPENDED:
		break;
	}

	return NOERROR;
}

HRESULT CDebuggerCtrl::EntryExists (LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
int iState = GetDebugger() -> GetState();
HRESULT hr = NOERROR; 
	
	switch (iState) {
	case ES_EXECUTING:	// Debugger ist busy, do it your self
		{
		ebHCODE hCode = GetDebugger() -> GetCode (false);					

			if(NULL == hCode) return E_HANDLE;
	
		ebHSCRIPT hScript = ebDebugger_GetScript(m_hWnd, false);		

			if (hScript == NULL) return E_HANDLE;

		CebEntryInfo EI;
		CBSParamCopy BSParam (iNumParams, pPars);

			BSParam.RemoveModsParam();
			hr = SetEntryInfo (EI, pEntry, iNumParams, BSParam);		
			if (FAILED(hr)) return hr;		
		
		// EntryPoint überprüfen
			if (ebCheckEntry ((ebHOBJECT)hCode, EI.GetEntryInfo()))
				return S_FALSE;		// Entrypoint gibts hier nicht
		}
		break;

	case ES_IDLE:		// das ganze dem Debugger überlassen
		{		
		CebEntryInfo EI;
		CBSParamCopy BSParam (iNumParams, pPars);

			BSParam.RemoveModsParam();
			hr = SetEntryInfo (EI, pEntry, iNumParams, BSParam);
			if (FAILED(hr)) return hr;
		
				// für EntryPoint überprüfen
		ebHCODE hCode = GetDebugger() -> GetCode (false);					

			if (NULL == hCode || ebCheckEntry ((ebHOBJECT)hCode, EI.GetEntryInfo())) 
				return S_FALSE;		// Entrypoint gibts hier nicht
		}
		break;

	case ES_SUSPENDED:
		break;
	}
	return S_OK;	// entry point scheint zu existieren
}

HRESULT CDebuggerCtrl::SetEntryInfo (CebEntryInfo & EI, LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	ASSERT(pEntry);

	EI.SetEntryName (pEntry);			
	EI.SetParamsCount (iNumParams);
	
	if (pPars) 
	{	
		if (iNumParams > 0) 
			EI.SetParams (&pPars -> pTypes[1]);			
		if (pPars -> pTypes[0].wType != 0) 
		{
			EI.SetMethodType (true);	// Funktion
			EI.SetRetType (&pPars -> pTypes[0]);
		}
	}

	return NOERROR;
}

BOOL CDebuggerCtrl::SetParams (int iNumParams, BSPARAM *pPars)
{
	if (m_iNumParams) return false;		// nur einmal zulassen
	m_iNumParams = iNumParams;
	m_pPars = pPars;

return true;
}

void CDebuggerCtrl::ResetParams (void)
{
	m_iNumParams = 0;
	m_pPars = NULL;
}

BOOL CDebuggerCtrl::SetOtherFunction(BOOL fOther)
{
	if (m_fRunModal) return false;
	m_fOtherFunction = fOther;
	return true; 
}

BOOL CDebuggerCtrl::ModalReset(ebHTHREAD h)
{
	if (m_fRunModal) 
	{// möglicherweise Laufzeitfehler
		if (ebThread_GetErrorNumber(h)) m_fRunError = true;
		// Beenden des Modalloops, wenn Exeend erreicht wurde
		EndModalLoop(IDOK);
		return true;
	}
	return false;
}
BOOL CDebuggerCtrl::BreakReset()
{
	if (m_fRunModal) return false;
	// Main() und StartScript() schon glaufen ?, 
	// dann "m_fBreakSet" setzen und OnEndScript() rufen
	if (m_fUnLoadIsRun || m_fOtherFunction) {
		PostMessage(uiWM_EndScript, 0, GO);
	}
	return true; 
}


HRESULT CDebuggerCtrl::RunModal ()
{
	try	{
	// jetzt, wo alles fertig ist, anzeigen
		Stop();		// UI richten, so tun, als ob angehalten wäre (stimmt ja auch)

		ShowWindow (SW_SHOWNORMAL);
		UpdateWindow();

	DWORD dwFlags = MLF_SHOWONIDLE;
	
		if (GetStyle() & DS_NOIDLEMSG)
			dwFlags |= MLF_NOIDLEMSG;

		m_fRunModal = true;
	
	// Eigentlich sind Filterscripts Editonly !!!
		SetEditOnly(false);

	WObjectManagement IObjManagement;
	
		THROW_FAILED_HRESULT(GetFilterScripts(IObjManagement.ppi()));
			
	WStreamInfo ISI;

		THROW_FAILED_HRESULT(GetInfoFilterScripts(ISI.ppi()));

	// Related im Requestor umschalten
		THROW_FAILED_HRESULT(SwitchManagement(IObjManagement, ISI));

	// zum SUPER SUBS enumerieren
		THROW_FAILED_HRESULT(AddRelatedScript());
		RunModalLoop(dwFlags);

		SetEditOnly(true);
		if (m_fSendClose) 
			return E_ABORT;			// Zum endgültigen Schliessen des Debuggers während Running		
		else if (m_fRunError) 
			return E_UNEXPECTED;	// Zum Schliessen des Debuggers bei RunTimeError 
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}	
	
	return NOERROR;
}

HRESULT CDebuggerCtrl::LinkScript()
{// Kann keine Related besitzen
	if (GetInitNew()) return S_OK;
	HRESULT hr = g_pBSE -> GetRunningObjectsHelper() -> LinkScript(
													GetScriptName(), 
													GetDebugger() -> GetCode(), 
													m_IObjManagement
													);
	// Zurückschalten auf Debugger-Related
	SwitchRelated(); 
	return hr;
}

/////////////////////////////////////////////////////////////////
// Callback vom Debugger
extern "C"
UINT ebCALLBACK _XTENSN_EXPORT CallbackFontProcDebugger(HWND hWnd, UINT msg,  
							UINT uiParam, long lParam)
{   // Für Später ?     
	static CDebuggerCtrl *pSD = NULL;
	
	switch (msg)
	{
		case  WM_INITDIALOG:
		{
			if (NULL == pSD) 
				pSD = (CDebuggerCtrl*)((CHOOSEFONT *)lParam) -> lCustData; 
			break;
		}
		case WM_CLOSE:
		{
			pSD = NULL;
			break;
		}
	}
	return 0;
}       

long ebCALLBACK EXPORT HandleDebuggerCtrlNotification(HWND hWnd,int code,ebPARAM1 np1,ebPARAM2 np2,long lPassThrough)
{
	switch (code) 
	{
	case DN_SWITCH:
		return ((CDebuggerCtrl *)lPassThrough) -> Switch();
		break;// sent when the script needs to be changed
	case DN_UNSWITCH:
		return ((CDebuggerCtrl *)lPassThrough) -> UnSwitch();
		break;
	case DN_ERRSPACE:	// Sent, when memory-error occured
		return AfxMessageBox(IDS_NOMEMORY);
		break;
	case DN_COMPILE:	// Sent immediately before compilation
		return ((CDebuggerCtrl *)lPassThrough) -> Compile((ebLPCOMPILESTRUCT)np2);
		break;
	case DN_COMPILEEND:
		return ((CDebuggerCtrl *)lPassThrough) -> CompileEnd();
		break;

	case DN_CHANGED:	// script saving is required
		return ((CDebuggerCtrl *)lPassThrough) -> Changed();
		break;
		
	case DN_EXECUTESTART:// sent before begin of execution
		return ((CDebuggerCtrl *)lPassThrough) -> ExeStart();
		break;

	case DN_EXECUTEEND:	// sent if script execution has terminated
		return ((CDebuggerCtrl *)lPassThrough) -> ExeEnd(np1);
		break;

	case DN_GO:			// sent immediately before execution begins
		return ((CDebuggerCtrl *)lPassThrough) -> Go();
		break;

	case DN_STOP:		// sent when execution is suspended
		return ((CDebuggerCtrl *)lPassThrough) -> Stop();
		break;

	case DN_CLOSE:		// ESC was pressed
		break;

	case DN_DIALOGSTART:// sent before a dialog in the debugger is invoked
		break;

	case DN_DIALOGEND:	// sent after a dialog in the debugger was closed
		break;

    case DN_RIGHTBUTTONUP:
		return ((CDebuggerCtrl*)lPassThrough) -> RightButtonUp(np1);
		break;

	default:
		break;
	}

return 0;
}

void ebCALLBACK EXPORT LineNumberProc(long lParam, ebWORD wLineNo)
{
	ASSERT(lParam);

	TCHAR buf[64];
	CDebuggerCtrl *pDebCtrl = (CDebuggerCtrl*)lParam;
	int numlines = pDebCtrl -> GetDebugger() -> GetNumLines();

	ASSERT(0 < numlines);
	   
	if (numlines && ((wLineNo % 20 == 0) || numlines == wLineNo)) 
	{
		CString strFmt;
		if (LoadString (strFmt, IDS_COMPILEFORMAT)) 
		{
			wsprintf(buf, strFmt, (wLineNo * 100L) / numlines);
			pDebCtrl -> GetStatusbar() -> SetPaneText (0, buf, true);		
			pDebCtrl -> GetStatusbar() -> UpdateWindow();
		}
	}
}

void ebCALLBACK EXPORT CompilerError(
	long lParam,
	ebLPCTSTR lpMsg,
	ebDWORD dwErrNum,
	ebWORD wLine,
	ebWORD wCharPos,
	ebLPCTSTR lpSource,
	ebLPCTSTR lpHelpFile,
	ebDWORD dwContext)
{
	TCHAR buf[MAXSTRLENGTH];
	CString strCap = GetDefaultName(IDS_LONGCLASSNAME);

	wsprintf(
		buf,
		TEXT("Fehler %ld (Zeile %d, Spalte %d) bei der Kompilierung eines Includes."),
		dwErrNum,
		wLine,
		wCharPos,
		lpMsg);
	::MessageBox(::GetActiveWindow(), strCap, buf, MB_OK);
}

////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen Debuggernotification

long CDebuggerCtrl::Switch()
{
	HWND hWnd = GetDebugger() -> GetWindow();
	ASSERT(NULL != hWnd);
	
	ebHSCRIPT hScript = ebDebugger_GetScript(hWnd, false);
	ASSERT(NULL != hScript);
	
	if (hScript)
	{// hScript zum Vergleich übergeben, 
	// ob richtiger Text gefunden wurde
	// siehe RequestorProc in bscrpt.cpp
		LPSTR lpstr = NULL;	
		char strName[_MAX_PATH];
		HRESULT hr = GetRelScripts() -> GetItem(GetScriptName(), hScript, strName, _MAX_PATH, &lpstr);
		if (SUCCEEDED(hr))
		{
			BOOL fResult =  false;
			if (NULL != lpstr)
			{
				fResult = GetDebugger() -> SetText(lpstr);				
				CoTaskMemFree (lpstr); lpstr = NULL;			
				if (fResult) 
					GetMainFrame() -> GenerateCaption(strName);
			}
			return fResult;
		}
	}

	return 0;
}

long CDebuggerCtrl::UnSwitch()
{
	GetMainFrame() -> GenerateCaption();
	return 0;
}

long CDebuggerCtrl::RightButtonUp (ebPARAM1 np1)
{
	CMenu Menu;

	if (!Menu.LoadMenu(IDR_RBUTTONDEBUGGER)) return 1;

	POINT pt;

	GetCursorPos (&pt);
	::SetFocus(m_hWnd);
	
	int iPos = (1 == np1) ? 0 : 1;

	m_fRMBMenu = true;

	return !(Menu.GetSubMenu (iPos)) -> TrackPopupMenu (0, pt.x, pt.y, this);
}

long CDebuggerCtrl::Stop()
{
	HWND hWnd = GetMainFrame() -> GetSafeHwnd();
	ASSERT(hWnd);

	if (::IsIconic(hWnd)) {
		::ShowWindow(hWnd, SW_RESTORE);
		::BringWindowToTop(hWnd);
	}

	CString str; 
	if (::LoadString (str, IDS_SUSPENDED)) 
		GetStatusbar() -> SetPaneText (0, str, true);		

	m_hWndSaved = ::GetFocus();

	m_fEnabled = ::IsWindowEnabled(hWnd) ? true : false;
	::EnableWindow (hWnd, true);
	::SetFocus(hWnd);
	return 0;
}

long CDebuggerCtrl::Compile(ebLPCOMPILESTRUCT lpcs)
{
	// add a line number procedure
	lpcs -> wFlags |= CF_USELINENUMBERPROC;
	lpcs -> lpfnLineNum = LineNumberProc;
	lpcs -> LineNumData = (long)this;

	lpcs -> wFlags |= CF_USECONSTPROC;
	lpcs -> lpfnConst = PreDefinedConstants;
	lpcs -> ConstData = 0L;

	CString str;
	LoadString (str, IDS_COMPILESTART);
	GetStatusbar() -> SetPaneText (0, str, true);		
	return 0;
}

long CDebuggerCtrl::CompileEnd()
{
	// Code für TreeItem setzen
	if (FAILED(SetCode(GetDebugger() -> GetCode()))) return 1;
	if (FAILED(EnumFunctions ())) return 1;
	// Es werden, wenn ein SUPER geladen ist !!!,
	// die Related aus der Liste entfernt,
	// um neue hScripts erzeugen zu können
	if (NULL == GetDebugger() -> GetCode())
		DeleteRelatedScript();

	CString str;
	LoadString (str, ID_STATUSBAR_PANE1); 
	GetStatusbar() -> SetPaneText (0, str, true);		
	return 0;
}

long CDebuggerCtrl::Changed()
{
	if (false == GetDirty()) 
	{
		SetDirty(true);
		GetMainFrame() -> GenerateCaption ();	// beim ersten mal
	}

return 0;
}

long CDebuggerCtrl::ExeEnd(ebPARAM1 np1)
{
	try
	{
		CString str;
		if (!::LoadString (str, IDS_SCRIPTEXECUTEEND)) _com_issue_error(E_OUTOFMEMORY);
		GetStatusbar() -> SetPaneText (0, str, true);		
		// ParentWindow für Laufzeit und Viewport setzen
		GetBSInstance() -> SetWindow (m_hWnd);		// ParentWindow setzen
		GetBSInstance() -> SetViewportParent(m_hWnd);
		// Soll abgebrochen werden ?
		if (GetBreakFlag()) m_fBreakSet = true;
		else m_fBreakSet = false;			
		// evtl. Parameter rausholen
		{
			CebThread Thread (ebDebugger_GetScript (m_hWnd, false));	
			Thread.Attach ((ebHTHREAD) np1);
		// evtl. Rückgabewert abfragen
			GetReturnParams (Thread, m_pPars, NULL, 0);
			GetAllParams (Thread, m_pPars, m_iNumParams);
			ResetApplicationObjects (Thread, m_pPars, m_iNumParams);
			// setzt globale Variablen zur Steuerung des Script-Running (welche Entries ?)	
			GetWhichEntryMayRun();// Muß vorher gesetzt werden, da bei Fehler Variablen wieder zurückgesetzt werden 
			if (Thread.GetErrorNumber()) 
				SendMessage(uiWM_EndScript, 0, ABORT);
			Thread.Detach();
		}
		SetOtherFunction(false);
		BreakReset();	// ruft eventuell OnEndScript 
		// Bei modalem Lauf (Debuggeraufruf aus z.B. Filterscripts) 
		ModalReset((ebHTHREAD) np1);
		// Debuggerfenster sollte bereits geschlossen werden
		if (m_fSendClose) // OnClose wird gerufen
			GetMainFrame() -> PostMessage(WM_CLOSE);
		// Bereit setzen
		if (::LoadString (str, ID_STATUSBAR_PANE1))
			GetStatusbar() -> SetPaneText (0, str, true);		
	}
	catch (_com_error&)
	{
		return 1;
	}
	return 0;
}

long CDebuggerCtrl::Go()
{
	CString str;
	if (::LoadString (str, IDS_SCRIPTEXECUTESTART)) 
		GetStatusbar() -> SetPaneText (0, str, true);		
 
	if (m_hWndSaved && IsWindow(m_hWndSaved))
		::SetFocus (m_hWndSaved);
	HWND hWnd = GetMainFrame() -> GetSafeHwnd();
	ASSERT(hWnd);
	::EnableWindow (hWnd, m_fEnabled ? true : false);
	// ParentWindow setzen (zur Laufzeit ist CDummy der Parent)
	GetBSInstance() -> SetWindow (m_pDummyParent -> m_hWnd);
	GetBSInstance() -> SetViewportParent(m_pDummyParent -> m_hWnd);

	DEX_KickIdle();	// Update-User-Interface anschieben, 
					// da BasicScript's ebPCodeCallBack bei zeitaufwendigen 
					// Operationen zu spät gerufen wird
	return 0;
}

long CDebuggerCtrl::ExeStart()
{
CebThread Thread (ebDebugger_GetScript (GetDebugger() -> GetWindow(), false));	

	Thread.Attach (ebDebugger_GetThread (GetDebugger() -> GetWindow(), false));
	try {
	HRESULT hr = SetHomeDir (GetBSInstance(), GetScriptName());

		if (FAILED(hr)) _com_issue_error(hr);

		Thread.SetStackSize (8192);				

	// evtl. Parameter setzen
		hr = SetAllParams (Thread, m_pPars, m_iNumParams);
		if (FAILED(hr)) _com_issue_error(hr);

	// Runningvaiablen voreinstellen
		Thread.SetLong (SETLONG_BREAK, m_fBreakSet);		// BreakFlag voreinstellen
		Thread.SetLong (SETLONG_AUTO, 0);					// Auto voreinstellen
		Thread.SetLong (SETLONG_NAME, 0);					// Name voreinstellen
		Thread.SetLong (SETLONG_HPROJECT, reinterpret_cast<LONG>(DEX_GetDataSourceHandle()));				// Datenquelle voreinstellen
		Thread.SetLong (SETLONG_HINSTANCE, reinterpret_cast<LONG>(_Module.GetResourceInstance()));	
		
		if (m_lpstrRequestorName) 
			strcpy(m_lpstrRequestorName, GetScriptName());

	// Für RequestorProc einstellen
		Thread.SetLong (SETLONG_NAME, (long)m_lpstrRequestorName);
		
		m_hWndSaved = NULL;
		m_fEnabled = true;
	}
	catch (_com_error&)
	{// Für RequestorProc rückstellen
		if (m_lpstrRequestorName) CoTaskMemFree(m_lpstrRequestorName); m_lpstrRequestorName = 0;
		Thread.SetLong (SETLONG_NAME, 0);
	}
	Thread.Detach();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//												   Idle, Run, Susp, Hilight
static Accelerator AccTable[] = {
        { 'n' - 'a' + 1,	VKCTRL, ID_DEBUG_NEW,  true, false, true, true }, 
        { 'o' - 'a' + 1,	VKCTRL, ID_DEBUG_OPEN, true, false, true, true }, 
        { 's' - 'a' + 1,	VKCTRL, ID_DEBUG_SAVE, true, true, true, true }, 
        { 'f' - 'a' + 1,	VKCTRL, ID_DEBUG_FIND, true, true, true, true }, 
        { 'g' - 'a' + 1,	VKCTRL, ID_DEBUG_GOTOLINE, true, true, true, true },
        { 'r' - 'a' + 1,	VKCTRL, ID_DEBUG_REPLACE, true, false, false, true }, 
        { 'w' - 'a' + 1,	VKCTRL, ID_DEBUG_ADDWATCH, true, true, true, true }, 
        { 'u' - 'a' + 1,	VKCTRL, ID_DEBUG_DELETEWATCH, true, true, true, true }, 
        { VK_F3,     		ANYKEY, ID_DEBUG_FINDNEXT, true, true, true, true }, 
        { VK_F8,     		ANYKEY, ID_DEBUG_TRACEIN, true, true, true, true }, 
        { VK_F9,     		ANYKEY, ID_DEBUG_BREAKPOINT, true, true, true, true }, 
        { VK_F5,    		ANYKEY, ID_DEBUG_GO, true, true, true, true }, 
        { VK_F12,    		ANYKEY, ID_DEBUG_TRACEOVER, true, true, true, true }, 
        { VK_F1,    		ANYKEY, ID_DEBUG_GETHELPON, true, false, true, true }, 
        { '\0',      		0, 0, false, false, false, false },
};             

ebBOOL ebCALLBACK _XTENSN_EXPORT KeyboardFilterDebCtrlProc(HWND hWnd, UINT message, 
						WPARAM wParam,LPARAM lParam)
{
	CebDebugger *pDebug = (CebDebugger *)GetProp (hWnd, g_cbKeyboardFilterData);

	if (NULL == pDebug) return false;
	
return TranslateAcceleratorDebCtrl (pDebug, AccTable, GetParent(hWnd), message, wParam ,lParam);
/* OK for debugger control to process message */
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Funktionen zum Keyboardfilter
/////////////////////////////////////////////////////////////////////////////////////////////

BOOL ActivateDebCtrlMenuItem (HWND hWnd, WORD wID, BOOL fHilight)
{
HMENU hMenu = ::GetMenu (hWnd);
	
	if (fHilight) HiliteMenuItem (hWnd, hMenu, wID, MF_BYCOMMAND | MF_HILITE);
	PostMessage (hWnd, WM_COMMAND, wID, 0L);
	if (fHilight) HiliteMenuItem (hWnd, hMenu, wID, MF_BYCOMMAND | MF_UNHILITE);

return true;  //key combination found and processed
}

BOOL TranslateAcceleratorDebCtrl (CebDebugger *pDebug, Accelerator  *pAcc, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
BOOL bIdle = false;
BOOL bSuspended = false;
BOOL bRunning = false;

	int cChar = wParam;
	int i = 0;

	if (WM_CHAR == message) 
	{
		if (isascii(cChar)) cChar = tolower (cChar);

		while (pAcc[i].cChar != '\0') {
			if (pAcc[i].cChar == cChar)	{
			// key is in table
				switch (pAcc[i].cVirtKey) {
	           	case VKCTRL:  //is CONTROL down?
					if (GetKeyState(VK_CONTROL) & 0x8000) {
							return true;	/* do not pass this message ON */
					}               
					break;

				case VKSHFT:  //is SHIFT do
					if (GetKeyState(VK_SHIFT) & 0x8000) {
							return true;	/* do not pass this message ON */
					}
					break;

	            case VKALT:  //is CONTROL down?
					if ( HIWORD(lParam) & 0x2000 ) {
							return true;	/* do not pass this message ON */
					}
					break;

				default:
					return false;
				} //end switch          
			}
			i++;
		} //end while loop		          
	}
	else if (message == WM_KEYDOWN) {
		while (pAcc[i].cChar != '\0') {
			if (pAcc[i].cChar == cChar) {
			// key is in table
				switch (pAcc[i].cVirtKey) {
				case ANYKEY:  
					return true;	/* do not pass this message ON */
		       		break;

				default:
					return false;
				}
			}
			i++;
		}
	}

return false;    // key combination not found in accelerator table
}

// FontDialog
UINT ebCALLBACK _XTENSN_EXPORT CallbackFontProc(HWND hWnd, UINT msg,  
							UINT uiParam, long lParam)
{        
static CDebuggerCtrl *pSD = (CDebuggerCtrl *)((CHOOSEFONT *)lParam) -> lCustData; 
	     
	switch (msg) {                        
	case WM_INITDIALOG:              
		pSD -> m_bFDOpen = true;
		break;

	case IDCANCEL:
		pSD -> m_bFDOpen = false;
		break;
	}

return 0;
}       

void MemFree(LPSTR *lplpstr, int iCount)
{
	if (lplpstr == NULL  || iCount < 0) return;

	LPSTR lpstr = NULL;
	for (int i = 0; i < iCount; i++)
	{
		lpstr = lplpstr[i];
		COTASKMEMFREE(lpstr);
	}
	COTASKMEMFREE(lplpstr);
}

HRESULT MessageNoCode(HWND hWnd, ebHCODE hCode, LPCSTR lpcstrName)
{
	if (hCode) return S_OK;

	CString str;
	CString strApp;
	try
	{
		if (!LoadString(str, IDS_NOCODE) || !LoadString(strApp, IDS_LONGCLASSNAME))
			_com_issue_error(E_OUTOFMEMORY); // No memory

		LPSTR lpstrBuffer = new char[_MAX_PATH];
		wsprintf(lpstrBuffer, str, lpcstrName);
		
		::MessageBox (hWnd, lpstrBuffer, strApp, MB_OK | MB_ICONINFORMATION); 
		
		DELETE_OBJ(lpstrBuffer);
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	catch(bad_alloc)
	{
		return E_OUTOFMEMORY;
	}
	return E_HANDLE;
}

HRESULT MessageCompileSuccess(HWND hWnd)
{
	CString strOut = GetDefaultName(IDS_NOERRORSFOUND);
	CString strCap = GetDefaultName(IDS_LONGCLASSNAME);
	::MessageBox (hWnd, strOut, strCap, MB_OK | MB_ICONINFORMATION);
	return S_OK;
}

HRESULT	MessageBoxBadText(HWND hWnd, int iLen)
{
	if (0 != iLen && MAXTEXT > iLen) return S_OK;
	CString strOut = GetDefaultName(IDS_TEXTTOBIG);
	CString strCap = GetDefaultName(IDS_LONGCLASSNAME);
	::MessageBox (hWnd, strOut, strCap, MB_OK | MB_ICONINFORMATION);
	return E_ABORT;
}

BOOL GetFile(LPCSTR lpcstr)
{
	char Ext[_MAX_EXT];

	Ext[0] = '\0'; 
	//			Buffer, Laufwerk, Pfad, Datei, Erweiterung 
	_splitpath (lpcstr, NULL, NULL, NULL, Ext);

	if ('\0' == Ext[0])
		return false;// keine Extension, kein File

	return true;
}

HRESULT SetHomeDir (CebInstance *pInst, LPCSTR lpcstr)
{
	ASSERT(pInst);

LPSTR lpstrBuffer = NULL;
TCHAR cbBuffer[_MAX_PATH];
CString strName (lpcstr);
	
	if (GetFile(strName)) {
	// Wenn File, dann File als Home wählen
	CString strPath (GetPathName (strName));

		pInst -> SetHomeDir (strPath);
		SetCurrentDirectory (strPath);
		return S_OK;
	}
	else if (DEX_GetActiveProject(cbBuffer)) {
	// Wenn internes Projectscript, dann Project als Home wählen
	CString strPath (GetPathName (cbBuffer));

		pInst -> SetHomeDir (strPath);
		SetCurrentDirectory (strPath);
		return S_OK;
	}
	return E_FAIL;
}



