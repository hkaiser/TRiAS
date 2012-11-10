// filtdlg.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#define _NEW_FILTERSCRIPT_TEMPLATE

#include <new>
#include <direct.h>
#include <oleguid.h>
#include <dirisole.h>
#include <triastlb.h>
#include <itriasap.h>
#include <iobjman.h>
#include <registrx.hxx>
#if defined(_NEW_FILTERSCRIPT_TEMPLATE)
#include <igeoobjs.h>
#endif // _NEW_FILTERSCRIPT_TEMPLATE

#include "macrguid.h"
#include "iscrprop.h"

#include "conststr.h"
#include "projscr.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "runebobs.h"
#include "runerr.h"
#include "filtdlg2.h"
//#include "strinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße
#define MAX_MACRO_CNT 200

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

//////////////////////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
#define OS_NO_STREAM_SUPPORT

DefineEnumerator2(os_wstring, IID_IEnumos_wstring);
DefineSmartEnumerator2(os_wstring, IID_IEnumos_wstring);

DefineSmartInterface(ScriptProperty);
DefineSmartInterface(Dispatch);
DefineSmartInterface(ObjectManagement);
DefineSmartInterface(StreamInfo);
DefineSmartInterface(GetTRiASApplication);
DefineSmartInterface(ObjManHelper);
DefineSmartInterface(BSProperty);

#if !defined(_NEW_FILTERSCRIPT_TEMPLATE)
DefineSmartInterface2(_DDocument, IID_DDocument);		// W_Document
DefineSmartInterface2(_DApplication, IID_DApplication);
DefineSmartInterface2(_DGeoObject, IID_DGeoObject);		// W_DGeoObject
#else
DefineSmartInterface2(_DGeoObjects, IID_DGeoObjects);	// W_DGeoObjects
DefineSmartInterface(QueryGeoObjects);					// WQueryGeoObjects
DefineSmartInterface(QueryEnumLONG);					// WQueryEnumLONG
#endif _NEW_FILTERSCRIPT_TEMPLATE

//////////////////////////////////////////////////////////////////////////////////////////////
// globale Variablen 
extern SummitModul g_SummitModuls[];

//////////////////////////////////////////////////////////////////////////////////////////////
// globale Funktionsdeklarationen
BOOL	LoadString(CString & str, int IDS);
CString GetPathName (LPCSTR pcPath);
CString CorrectExtension (CString &rPath, UINT uiResIDExt);
BOOL	MyTranslateAccelerator (CebDebugger *, Accelerator  *pAcc,	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
CString GetDefaultName(int IDS);
BOOL	ReadRegSettingsLastOpenFile(char *pc, DWORD dwL);
BOOL	SaveRegSettingsLastOpenFile (LPCSTR pc);
HRESULT	MessageNoCode(HWND h, ebHCODE hCode, LPCSTR lpcstrName);
HRESULT SetHomeDir(CebInstance *pInst, LPCSTR lpcstr);
BOOL	GetFile(LPCSTR lpcstr);
BOOL	IsRemoteDir(LPCSTR cbPath);
UINT	FileDialog (LPCSTR pcPath, CWnd *pParent, CString & strFileName, BOOL fOpen = true, LPCSTR lpcstr = NULL);
BOOL	FindFirstDefaultString(IObjectManagement *pIObjMan, LPSTR lpstrDef);
BOOL	ModifyName(LPSTR lpstr);
HRESULT MessageNoText(HWND hWnd, LPCSTR lpcstr);

//////////////////////////////////////////////////////////////////////////////////////////////
// CALLBACK Funktionsdeklarationen 
extern "C" 
ebHSCRIPT ebCALLBACK _XTENSN_EXPORT RequestorProc (ebHTHREAD hThread, ebLPCTSTR pcMacroName, long lParam);
extern "C" 
void ebCALLBACK _XTENSN_EXPORT OnFilterRuntimeError (	long lParam, ebLPCSTR lpMsg, ebDWORD dwErrNum, ebWORD wLinNr, ebWORD wCharPos, 
												ebLPCSTR lpSource, ebLPCSTR lpHelpFile, ebDWORD dwHelpContext);

/////////////////////////////////////////////////////////////////////////////
//												   Idle, Run, Susp, Hilight
static Accelerator AccTable[] = {
    { VK_F9,     		ANYKEY, ID_DEBUG_BREAKPOINT, true, true, true, false }, 
    { VK_F8,     		ANYKEY, ID_DEBUG_TRACEIN, false, false, false, false }, 
    { VK_F12,     		ANYKEY, ID_DEBUG_TRACEOVER, false, false, false, false }, 
    { VK_F5,     		ANYKEY, ID_DEBUG_GO, false, false, false, false }, 
    { 's' - 'a' + 1,	VKCTRL, ID_DEBUG_SAVE, true, true, true, true }, 
    { 'w' - 'a' + 1,	VKCTRL, ID_DEBUG_ADDWATCH, true, true, true, true }, 
    { 'u' - 'a' + 1,	VKCTRL, ID_DEBUG_DELETEWATCH, true, true, true, true }, 
    { '\0',      		0, 0, false, false, false, false },
};             

extern "C"
ebBOOL ebCALLBACK _XTENSN_EXPORT PropActKeyboardFilterProc (HWND hWnd, UINT message, 
						WPARAM wParam,LPARAM lParam)
{
CebDebugger *pDebug = (CebDebugger *)GetProp (hWnd, g_cbKeyboardFilterData);

	if (NULL == pDebug) return false;
	
return MyTranslateAccelerator (pDebug, AccTable, GetParent(hWnd), message, wParam ,lParam);
/* OK for debugger control to process message */
}

BOOL ActivateMenuItem (HWND hWnd, WORD wID, BOOL fHilight)
{
HMENU hMenu = ::GetMenu (hWnd);
	
	if (fHilight) HiliteMenuItem (hWnd, hMenu, wID, MF_BYCOMMAND | MF_HILITE);
	PostMessage (hWnd, WM_COMMAND, wID, 0L);
	if (fHilight) HiliteMenuItem (hWnd, hMenu, wID, MF_BYCOMMAND | MF_UNHILITE);

return true;  //key combination found and processed
}

BOOL MyTranslateAccelerator (
	CebDebugger *pDebug, Accelerator  *pAcc, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
BOOL bIdle = false;
BOOL bSuspended = false;
BOOL bRunning = false;

	switch (pDebug -> GetState()) {
	case TS_IDLE:
		bIdle  = true;
		break;

	case TS_SUSPENDED:
		bSuspended = true;
		break;

	case TS_RUNNING:
		bRunning = true;
		break;

	default:
		ASSERT(false);
		break;
	}

int cChar = wParam;
int i = 0;

	if (WM_CHAR == message) {
		if (isascii(cChar)) cChar = tolower (cChar);

		while (pAcc[i].cChar != '\0') {
			if (pAcc[i].cChar == cChar)	{
			// key is in table
				switch (pAcc[i].cVirtKey) {
	           	case VKCTRL:  //is CONTROL down?
					if (GetKeyState(VK_CONTROL) & 0x8000) {
						if (bRunning == pAcc[i].fRunning ||
						    bSuspended == pAcc[i].fSuspended ||							 
						    bIdle == pAcc[i].fIdle) 
						{
							ActivateMenuItem (hWnd, pAcc[i].wID, pAcc[i].fHilight);
							return true;	/* do not pass this message ON */
						}
					}               
					break;

				case VKSHFT:  //is SHIFT do
					if (GetKeyState(VK_SHIFT) & 0x8000) {
						if (bRunning == pAcc[i].fRunning ||
						    bSuspended == pAcc[i].fSuspended ||							 
						    bIdle == pAcc[i].fIdle) 
						{
							ActivateMenuItem (hWnd, pAcc[i].wID, pAcc[i].fHilight);
							return true;	/* do not pass this message ON */
						}
					}
					break;

	            case VKALT:  //is CONTROL down?
					if ( HIWORD(lParam) & 0x2000 ) {
						if (bRunning == pAcc[i].fRunning ||
						    bSuspended == pAcc[i].fSuspended ||							 
						    bIdle == pAcc[i].fIdle) 
						{
							ActivateMenuItem (hWnd, pAcc[i].wID, pAcc[i].fHilight);
							return true;	/* do not pass this message ON */
						}
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
					if (bRunning == pAcc[i].fRunning ||
					    bSuspended == pAcc[i].fSuspended ||							 
					    bIdle == pAcc[i].fIdle) 
					{
						ActivateMenuItem (hWnd, pAcc[i].wID, pAcc[i].fHilight);
						return true;	/* do not pass this message ON */
					}
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

long ebCALLBACK EXPORT HandleFilterDebuggerNotification(HWND hWnd,int code,ebPARAM1 np1,ebPARAM2 np2,long lPassThrough)
{
	switch (code) {
	case DN_ERRSPACE:	// Sent, when memory-error occured
		return AfxMessageBox(IDS_NOMEMORY);
		break;

	case DN_COMPILE:	// Sent immediately before compilation	
		break;

	case DN_COMPILEEND:
		break;

	case DN_CHANGED:	// script saving is required
		return ((CFilterScriptDlg2 *)lPassThrough) -> Changed();
		break;
		
	case DN_EXECUTESTART:// sent before begin of execution
		break;

	case DN_EXECUTEEND:	// sent if script execution has terminated
		break;

	case DN_GO:			// sent immediately before execution begins
		break;

	case DN_STOP:		// sent when execution is suspended
		break;

	case DN_CLOSE:		// ESC was pressed
		break;

	case DN_SWITCH:		// sent when the script needs to be changed
		break;

	case DN_DIALOGSTART:// sent before a dialog in the debugger is invoked
		break;

	case DN_DIALOGEND:	// sent after a dialog in the debugger was closed
		break;

    case DN_RIGHTBUTTONUP:
		return ((CFilterScriptDlg2 *)lPassThrough) -> RightButtonUp(np1);
		break;

	default:
		break;
	}

return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CFilterScriptDlg2 property page

IMPLEMENT_DYNCREATE(CFilterScriptDlg2, CPropertyPage)

CFilterScriptDlg2* CFilterScriptDlg2::CreateInstance()
{
	if (!g_SummitModuls[COMPILER].fIsInstalled || !g_SummitModuls[RUNTIME].fIsInstalled)
		return NULL;

CFilterScriptDlg2* pFD = NULL;

	try {
		pFD = new CFilterScriptDlg2();	// Anlegen ScriptWrapper und RunningObjectContainer
	} catch(bad_alloc) {
		return NULL;
	}
	return pFD; 
}


CFilterScriptDlg2::CFilterScriptDlg2() 
		:	CPropertyPage(CFilterScriptDlg2::IDD),
			m_rInst (g_pBSE->ebInst())
{
	//{{AFX_DATA_INIT(CFilterScriptDlg2)
	//}}AFX_DATA_INIT
	m_pText = NULL;
	m_hCode = NULL;
	m_hOuterCode = NULL;
	m_hPrCtx = HACTCONNECTION;

	m_dwSheetBttns = 0;
	
	m_pIDoc = NULL;
	m_hFontOld = NULL;

	m_fModified = false;
	m_itEnLong = m_listEnumLongOut.begin();
	
	m_pRunningObject = NULL;;
	m_pRunningObjs = NULL;;
}

CFilterScriptDlg2::~CFilterScriptDlg2()
{	
	COTASKMEMFREE(m_pText);

// Kommt aus Debugger, also:
	if (m_hCode) ebCode_Free(m_hCode); m_hCode = NULL;

// kommt von Platte, also:
	COTASKMEMFREE(m_hOuterCode);

// Font zurücksetzen	
	ResetFont();
	Reset();
}

// Member ScriptWrapper, ScriptContainer und Document zurücksetzen
void CFilterScriptDlg2::Reset()
{
	if (m_pRunningObject) { m_pRunningObject -> Release(); m_pRunningObject = NULL; }
	if (m_pRunningObjs) { delete m_pRunningObjs; m_pRunningObjs = NULL; }
	if (m_pIDoc) { m_pIDoc -> Release(); m_pIDoc = NULL; }
}

BOOL CFilterScriptDlg2::SetButtons(LPCSTR lpcstr)
{
	m_Test.EnableWindow(true); 
	m_bttnEntfernen.EnableWindow(true); 
	if (NULL == lpcstr || (GetInitNew() && GetDirty())) //Defaulttext, Syntaxanalyse unsinnig
	{
		m_Test.EnableWindow(false); 
	}
	if (NULL == lpcstr || GetInitNew()) //neues Makro, wird sowieso entfernt
	{
		m_Test.EnableWindow(false); 
	}
	return 	true;
}

HRESULT CFilterScriptDlg2::GetGeneralScripts(IObjectManagement **ppIObj)
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
HRESULT CFilterScriptDlg2::GetInfoGeneralScripts(IStreamInfo **ppISI)
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
HRESULT CFilterScriptDlg2::GetFilterScripts(IObjectManagement **ppIObj)
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
HRESULT CFilterScriptDlg2::GetInfoFilterScripts(IStreamInfo **ppISI)
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
HRESULT CFilterScriptDlg2::GetObjFeatScripts(IObjectManagement **ppIObj)
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
HRESULT CFilterScriptDlg2::GetInfoObjFeatScripts(IStreamInfo **ppISI)
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
///////////////////////////////////////////////////////////
// Loaded Item Properties
void CFilterScriptDlg2::SetLoadedItem(IRunningObject* p) 
{ 
	if (p)// wenn Null, schon freigegeben
	{
		if (m_pRunningObject) m_pRunningObject -> Release();
		m_pRunningObject = p; 
		m_pRunningObject -> AddRef(); 
	}
	else
		m_pRunningObject = NULL;
}
// Loaded und Selected Item PROPERTIES
HRESULT CFilterScriptDlg2::GetLoadedItem(IRunningObject** ppI) 
{ 
	if (m_pRunningObject)
	{
		*ppI = m_pRunningObject;
		(*ppI) -> AddRef();
		return NOERROR;
	}
	return E_FAIL; 
}

BOOL CFilterScriptDlg2::GetDirty()
{
	try {
		WRunningObject I;
		HRESULT hr = GetLoadedItem(I.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		WObjManHelper IOMH = I;
		if (IOMH -> GetDirty())
			return true;
	} catch (_com_error&) {
		return false;
	}
	return false;
}
void CFilterScriptDlg2::SetDirty(BOOL f)
{
	try {
		WRunningObject I;
		HRESULT hr = GetLoadedItem(I.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);

		WObjManHelper IOMH = I;
		IOMH -> SetDirty(f);
	} catch (_com_error&) {
	}
}
BOOL CFilterScriptDlg2::GetInitNew()
{
	try {
	WRunningObject I;

		THROW_FAILED_HRESULT(GetLoadedItem(I.ppi()));

	WObjManHelper IOMH (I);
	
		if (IOMH -> GetInitNew())
			return true;

	} catch (_com_error&) {
		return false;
	}
	return false;
}
CString CFilterScriptDlg2::GetScriptName()
{
	char str[_MAX_PATH];
	try
	{
		WRunningObject IRO;
		HRESULT hr = GetLoadedItem(IRO.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		WBSProperty IBSP = IRO;
		IBSP -> GetScriptName(str, _MAX_PATH);
	}
	catch (_com_error&) {
		return '\0';
	}
	return str;
}
void CFilterScriptDlg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterScriptDlg2)
	DDX_Control(pDX, IDC_ENTFERNEN, m_bttnEntfernen);
	DDX_Control(pDX, IDC_SYNTAXTEST, m_Test);
	DDX_Control(pDX, IDC_COMBOOPATESCRIPTS, m_cbxFilterScripts);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFilterScriptDlg2, CPropertyPage)
	//{{AFX_MSG_MAP(CFilterScriptDlg2)
	ON_BN_CLICKED(IDC_SYNTAXTEST, OnSyntaxTest)
	ON_CBN_EDITCHANGE(IDC_COMBOOPATESCRIPTS, OnEditChangeCB)
	ON_CBN_SELCHANGE(IDC_COMBOOPATESCRIPTS, OnSelChangeCB)
	ON_CBN_KILLFOCUS(IDC_COMBOOPATESCRIPTS, OnKillFocusCB)
	ON_BN_CLICKED(IDC_ENTFERNEN, OnEntfernen)
	ON_COMMAND(ID_DEBUG_CUT, OnDebugCut)
	ON_COMMAND(ID_DEBUG_COPY, OnDebugCopy)
	ON_COMMAND(ID_DEBUG_PASTE, OnDebugPaste)
	ON_COMMAND(ID_DEBUG_DELETE, OnDebugDelete)
	ON_COMMAND(ID_DEBUG_UNDO, OnDebugUndo)
	ON_COMMAND(ID_DEBUG_EDITDIALOG, OnDebugEditdialog)
	ON_COMMAND(ID_DEBUG_NEWDIALOG, OnDebugNewdialog)
	ON_COMMAND(ID_DEBUG_BREAKPOINT, OnDebugBreakpoint)
	ON_WM_INITMENU()
	ON_COMMAND(ID_DEBUG_GETHELPON, OnDebugGetHelpOn)	
	ON_COMMAND(ID_DEBUG_SAVE, OnDebugSave)
	ON_COMMAND(ID_DEBUG_IMPORT, OnDebugImport)
	ON_COMMAND(ID_DEBUG_SAVEAS, OnDebugExport)
	ON_COMMAND(ID_DEBUG_GO, OnDebugGo)
	ON_COMMAND(ID_DEBUG_TRACEIN, OnDebugTraceIn)
	ON_COMMAND(ID_DEBUG_TRACEOVER, OnDebugTraceOver)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterScriptDlg2 message handlers

BOOL CFilterScriptDlg2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	try
	{	// Debugger erzeugen
		HRESULT hr = CreateDebugger();	
		if (FAILED(hr)) _com_issue_error(hr);
		// Font setzen
		SetFont();
		// Listbox füllen
		hr = FillComboBox();
		if (FAILED(hr)) _com_issue_error(hr);
		// ersten Script öffnen, in Liste, Stream öffnen	
		// Dieser darf nicht <defaultname> haben (z.B. <Ohne Name>)
		hr = OpenInit();
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch (_com_error&)
	{
		return false;
	}		
	return true;  // return true  unless you set the focus to a control
}	   

void CFilterScriptDlg2::OnDestroy() 
{
	CPropertyPage::OnDestroy();	
// Property für KeyboardRoutine wieder freigeben
// Muss hier geschehen, da hier Fenster noch gültig
	CWnd *pWnd = GetDlgItem (CFilterScriptDlg2::ID_DEBUG);
	ASSERT(NULL != pWnd);

	if (NULL != GetProp (pWnd -> GetSafeHwnd(), g_cbKeyboardFilterData))
		RemoveProp (pWnd -> GetSafeHwnd(), g_cbKeyboardFilterData);

// Muss hier geschehen, da hier Combo noch gültig
	DeleteNew();

// Bevor Debuggerwindow zerstört wird, noch Code und Text merken
// Jeweils selbst zerstören in ~
	if (m_Debug.Compile())
		m_hCode = m_Debug.GetCode(true);
	GetText(&m_pText);

// Fenster zurücksetzen, da Debuggerfenster als Member nun zerlegt wird
	m_rInst.SetWindow (g_pBSE -> hWnd());	
	m_rInst.SetViewportParent (g_pBSE -> hWnd());	
}

BOOL CFilterScriptDlg2::OnSetActive() 
{
	ASSERT(m_hWnd);

	if (CPropertyPage::OnSetActive()) 
	{
		if (FAILED(InitSheetButtons())) return false;	
		return true;
	}
	return false;
}

// *** ComboBox-Kommandos ***
void CFilterScriptDlg2::OnEditChangeCB() 
{
	CString str;
	m_cbxFilterScripts.GetWindowText(str);
	if (str.IsEmpty()) return;
	// Damit Dirty angezeigt wird
	m_fModified = true;
	GenerateCaption(str);
//	VERIFY(SUCCEEDED(Open(str))); // in OnKillFocusCB()damit nicht jedesmal ein neuer geöffnet wird
}

void CFilterScriptDlg2::OnKillFocusCB() 
{
	// nicht editiert
	if (m_fModified == false) return;
	try
	{
		CString str;// Text aus EditControl von Combo geben lassen
		m_cbxFilterScripts.GetWindowText(str);	
		LPSTR lpstrName = str.GetBuffer(str.GetLength()+1);
		ModifyName(lpstrName);
		str.ReleaseBuffer();
		HRESULT hr = Open(str);
		if (FAILED(hr)) _com_issue_error(hr);
		// OK , ist geöffnet
		m_fModified = false;
	}
	catch (CMemoryException&)
	{
	}
	catch (_com_error&)
	{
	}
}

void CFilterScriptDlg2::OnSelChangeCB() 
{
	CString str; str.Empty();
	if (CB_ERR == m_cbxFilterScripts.GetCurSel()) 
		return;
	m_cbxFilterScripts.GetLBText(m_cbxFilterScripts.GetCurSel(), str);
	// sel. Text aus der Combo geben lassen
	VERIFY(SUCCEEDED(Open(str)));
}

// *** Compilebutton ***
void CFilterScriptDlg2::OnSyntaxTest() 
{
	if (m_Debug.Compile()) {
		FilterMessageBox(IDS_NOERRORSFOUND);		
	}
}
//
// *** Wizard-Kommandos ***
//
void CFilterScriptDlg2::OnCancel() 
{
	CPropertyPage::OnCancel();
}

LRESULT CFilterScriptDlg2::OnWizardNext() 
{
// Property für KeyboardRoutine wieder freigeben
	if (0 == WizardFinishNext())
		return CPropertyPage::OnWizardNext();

return -1;
}

BOOL CFilterScriptDlg2::OnWizardFinish() 
{
	if (0 == WizardFinishNext())
		return CPropertyPage::OnWizardFinish();

return 0;
}
////////////////////////////////////////////////////////////////////
// *** Hilfsfunktionen ***
////////////////////////////////////////////////////////////////////
HRESULT CFilterScriptDlg2::CreateDebugger()
{
// dieser Dialog ist Parent für Debugger
	m_Debug.SetParent (m_hWnd);
	m_Debug.SetStyle (WS_CHILD|WS_VISIBLE|DS_NOWATCHWINDOW);
	m_Debug.SetId (CFilterScriptDlg2::ID_DEBUG);

	HRESULT hr = SetRect();
	if (FAILED(hr)) return hr;	

// Applicationinstance siehe Extensionfile, ebCreateDebugger(...,Appl.hInst)
// nicht verwechseln mit ebDebugger_SetInstance(BS-Inst)	
	m_Debug.SetInstance (g_hInstance);
	if (!m_Debug.Create()) {
		TRACE("Failed to create debugger control\n");
		return ResultFromScode(E_FAIL);      // fail to create
	}

// BasicScriptInstance setzen, ebDebugger_SetInstance()
	m_Debug.SetInstance(&m_rInst);

// ParentWindow für BS-Inst setzen
	m_rInst.SetWindow (m_hWnd);	
	m_rInst.SetViewportParent (m_hWnd);	

// Editor
	m_Debug.EnableTextColors();
	m_Debug.SetAutoCase	(true);
	m_Debug.SetAutoIndent(true);
	m_Debug.SetKeyboardFilter (PropActKeyboardFilterProc);
	m_Debug.SetNotificationProc(HandleFilterDebuggerNotification);
	m_Debug.SetNotificationData((long)this);

// Daten für KeyboardFilterProc merken
	SetProp (m_Debug.GetWindow(), g_cbKeyboardFilterData, (HANDLE)&m_Debug);

	return NOERROR;
}

HRESULT CFilterScriptDlg2::OuterInit()
{
	ASSERT(!m_strStartName.IsEmpty());
	ASSERT(NULL == m_hCode);
	if (m_strStartName.IsEmpty()) return E_UNEXPECTED;

	ebHCODE hCode = NULL;
	LPSTR lpstrText = NULL;
	HRESULT hr = NOERROR;
	try
	{
		hr = OpenOther(m_strStartName, CLSID_Script, &hCode, &lpstrText);
		// gleich wieder freigeben, brauche nur Code
		COTASKMEMFREE(lpstrText);
		// Wenn kein Code abgespeichert, Fehler
		HRESULT hr1 =  MessageNoCode(::GetActiveWindow(), hCode, m_strStartName);
		if (FAILED(hr1)) _com_issue_error(hr1);
		if (FAILED(hr)) _com_issue_error(hr);
		// Code merken		
		COTASKMEMFREE(m_hOuterCode);
		m_hOuterCode = hCode;
	}
	catch (_com_error& e)
	{
		COTASKMEMFREE(hCode);
		COTASKMEMFREE(lpstrText);
		hr = _COM_ERROR(e); 
	}
	return hr;
}

HRESULT CFilterScriptDlg2::FillComboBox()
{
	HRESULT hr = NOERROR;
	USES_CONVERSION;
	try
	{
		WObjectManagement IOM;
		hr = GetFilterScripts(IOM.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		WStreamInfo ISI;
		hr = GetInfoFilterScripts(ISI.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		WUnknown IU;
		HRESULT hr = IOM -> EnumStrings(IU.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		WEnumos_wstring IE = IU;
		os_wstring oswstr;
		while (S_OK == IE -> Next(1, &oswstr, NULL)) 
		{
			CString str, strOld;
			DWORD dwInfo = 0;
			LPSTR lpstr = OLE2A(oswstr.c_str());

			if (!LoadString (str, IDS_NEWSTREAMINFO)) _com_issue_error(E_OUTOFMEMORY);
			if (!LoadString (strOld, IDS_STREAMINFOS)) _com_issue_error(E_OUTOFMEMORY);
			
			if (0 != _stricmp(str, lpstr) && 0 != _stricmp(strOld, lpstr))
			{
				// Bei alter Storage-Struktur existiert keine Streaminfo !!!,
				// alle einfügen
				hr = ISI -> Get(A2OLE(lpstr), &dwInfo);
				if (FAILED(hr))
					m_cbxFilterScripts.AddString(lpstr);
				else if (dwInfo & SUPERITEM)
				// Neue Storage-Struktur nur SUPER einfügen
					m_cbxFilterScripts.AddString(lpstr);
			}
		}
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}

	return hr;
}
LRESULT CFilterScriptDlg2::WizardFinishNext()
{
	// Speichern, wenn Dirty und YES
	Save();
	return 0;
}
//
// *** eigentliche AKTION !!! ***
//
// In Beginaction
HRESULT CFilterScriptDlg2::InitActions ()
{
	LPSTR	pText = NULL;
	UINT uiCntRelScripts = 0;
	LPSTR *lplpstrRelScripts = NULL;
	HRESULT hr = NOERROR;
	ebHCODE hCode = NULL;
	try
	{	// aktuellen Code aus Debugger holen
		if (NULL == m_hCode && NULL == m_hOuterCode) _com_issue_error(E_HANDLE);
		if (NULL != m_hCode && NULL != m_hOuterCode) _com_issue_error(E_UNEXPECTED);
		hCode = m_hCode;
		if (NULL == hCode) 
			hCode = m_hOuterCode;
		// mit diesem Code Script kreieren
		hr = m_pRunningObject -> CreateScript(&m_rInst, hCode);
		if (FAILED(hr)) _com_issue_error(hr);	
		// gemerkte Breakpoints setzen
		hr = SetKeptBreaks();
		if (FAILED(hr)) _com_issue_error(hr);
		// neuen RunningObjectHelper kreieren
		m_pRunningObjs = CRunningObjectsHelper::CreateRunningObjectsHelper(&m_rInst);
		if (NULL == m_pRunningObjs) _com_issue_error(E_OUTOFMEMORY);

		WObjectManagement IOM;
		hr = GetFilterScripts(IOM.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		WStreamInfo ISI;
		hr = GetInfoFilterScripts(ISI.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		// Storage initialiseiern
		hr = m_pRunningObjs -> InitLinkAndStorage(IOM, ISI);
		if (FAILED(hr)) _com_issue_error(hr);
		// Requestor umschalten
		hr = m_pRunningObjs -> SwitchRelated();
		if (FAILED(hr)) _com_issue_error(hr);
		// RelatedScripts von geladenem Macro in Liste eintragen
		hr = m_pRunningObjs -> AddRelated(GetScriptName());
		if (FAILED(hr)) _com_issue_error(hr);
		// Gerade Geladenes und Auszuführendes Script zumspäteren Speichern setzen 
		SetStartName(GetScriptName());
	} // try
	catch (_com_error& e)
	{
		if (m_pRunningObjs) delete m_pRunningObjs;  m_pRunningObjs = NULL;
		return _COM_ERROR(e);
	}
	catch (bad_alloc)
	{
		if (m_pRunningObjs) delete m_pRunningObjs;  m_pRunningObjs = NULL;
		return E_OUTOFMEMORY;
	}
	return hr;
}
HRESULT CFilterScriptDlg2::ResetActions ()
{
	ASSERT(!GetScriptName().IsEmpty());
	if (GetScriptName().IsEmpty()) return E_FAIL;
	// RelatedScripts von geladenem Macro in Liste eintragen
	return m_pRunningObjs -> DeleteRelated(GetScriptName());
}

// Aktionen am Anfang und am Ende, eigenständige Threads erzeugen
HRESULT CFilterScriptDlg2::BeginAction(void)
{
HRESULT hr = NOERROR;
ebBOOL lRet = 0;
BSPARAM BSParams;	

	memset(&BSParams, 0, sizeof(BSPARAM));
	try	{
		ASSERT(HACTCONNECTION != m_hPrCtx);

	// jetzt gehts los
		hr = InitActions ();
		if (FAILED(hr)) _com_issue_error(hr);

	// EntryString laden
		CString strEntryName;
		if (!::LoadString(strEntryName, IDS_BEGINACTION)) _com_issue_error(E_OUTOFMEMORY);

		BSParams.pTypes = new ebPARAM[1];
		BSParams.pValues = new LPVOID[1];	

	// Returnwert
		BSParams.pTypes -> wType = TYP_BOOLEAN;
		BSParams.pTypes -> szExtType[0] = '\0';

	// Returnwert setzen
		BSParams.pValues[0] = (LPVOID)&lRet;

	// eigentliche Ausführung
		hr = m_pRunningObject -> RunEntry (strEntryName, 0, &BSParams, true, reinterpret_cast<INT_PTR>(m_hPrCtx), NULL); // Params
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	if (BSParams.pTypes) delete BSParams.pTypes; BSParams.pTypes = NULL;
	if (BSParams.pValues) delete BSParams.pValues; BSParams.pValues = NULL;

	if (0 == lRet)
		return E_ABORT;		// abbrechen
	return hr;
}
HRESULT CFilterScriptDlg2::EndAction()
{
CString strEntryName;

	if (!::LoadString(strEntryName, IDS_ENDACTION)) 
		return E_OUTOFMEMORY;

// eigentliche Ausführung
	ASSERT(HACTCONNECTION != m_hPrCtx);

HRESULT hr = m_pRunningObject -> RunEntry (strEntryName, NULL, 0, true, reinterpret_cast<INT_PTR>(m_hPrCtx), NULL); // Params

	ResetActions();
	return hr;
}

HRESULT CFilterScriptDlg2::DoAction(IEnum<long> *pIEn)
{
	ASSERT(NULL != pIEn);
	if (NULL == pIEn) return E_POINTER;

WEnumLONG IEnumOut;

// jedes einzelne Objekt abarbeiten und Ausgabeliste füllen
HRESULT hr = RunThreadHelper(pIEn, IEnumOut.ppi()); // E_ABORT: Debugger zu, E_UNEXPECTED: RuntimeError

	if (FAILED(hr)) return hr;

// in Ausgabeliste eintragen, AddRef()
	m_listEnumLongOut.insert (m_listEnumLongOut.end(), IEnumOut);
	m_itEnLong = m_listEnumLongOut.begin();
	return S_OK;
}

HRESULT CFilterScriptDlg2::RunThreadHelper (IEnum<long> *pIEnum, IEnum<long> **ppIEnumOut)
{
	ASSERT(NULL != pIEnum);
	ASSERT(NULL != ppIEnumOut);
	if (NULL == pIEnum || NULL == ppIEnumOut) return E_POINTER;

HRESULT hr = NOERROR;
BSPARAM BSParams;	

	try {
	CString strEntryName;
		
		if (!::LoadString(strEntryName, IDS_DOACTION)) _com_issue_error(E_OUTOFMEMORY);

	// Anlegen der Parameterwerte
		BSParams.pTypes = new ebPARAM[2];
		BSParams.pValues = new LPVOID[2];	

#if !defined(_NEW_FILTERSCRIPT_TEMPLATE)
	// Returnwert, Eigenschaftswert
		BSParams.pTypes -> wType = TYP_INTEGER;
		BSParams.pTypes -> szExtType[0] = '\0';

	// erster Param: Objektmenge, für das Featurewert berechnet werden soll
		(BSParams.pTypes + 1) -> wType = TYP_APPOBJECT;
		strcpy ((BSParams.pTypes + 1) -> szExtType, TEXT("GeoObject"));

	LONG lRetObj = 0;
	LONG lObj = 0;
	WEnumLONG EnumOut;

		THROW_FAILED_HRESULT(CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, 
			CLSCTX_INPROC_SERVER, IID_IEnumLONG, IEnumOut.ppv()));

	// noch Schleife für alle Objekte im Enum !!!
		for (pIEnum -> Reset(); S_OK == pIEnum->Next(1, &lObj, NULL); /**/) 
		{
			if (lObj <= 0) _com_issue_error(E_INVALIDARG);

		// Konvertierung long zu Objekt
			W_DGeoObject IObj;
			{// Dokument geben lassen
				hr = GetDocument ();		
				if (FAILED(hr)) _com_issue_error(hr);
				// Objekt geben lassen
				hr = ConvertLongToObject (lObj, IObj.ppi());
				if (FAILED(hr)) _com_issue_error(hr);
			}
	
		// Returnwert setzen
			BSParams.pValues[0] = (LPVOID)&lRetObj;
	
		// erster Param: Objekt 
			ebDWORD dw = (ebDWORD)(_DGeoObject *)IObj;
			BSParams.pValues[1] = (LPVOID)&dw;	// Adresse des Object-Pointers übergeben
	
		// Entry laufen lassen
			hr = m_pRunningObject -> RunEntry (strEntryName, 1, &BSParams, true);
			if (FAILED(hr)) _com_issue_error(hr);

		// Soll Objekt weitergereicht werden ?	
			if (0 != lRetObj) 
				EnumOut -> AddItem (lObj);
		} // for
#else
		ASSERT(HACTCONNECTION != m_hPrCtx);

	// Returnwert, Eigenschaftswert
		BSParams.pTypes -> wType = TYP_APPOBJECT;
		strcpy (BSParams.pTypes -> szExtType, TEXT("GeoObjects"));

	// erster Param: Objektmenge, für das Featurewert berechnet werden soll
		(BSParams.pTypes + 1) -> wType = TYP_APPOBJECT;
		strcpy ((BSParams.pTypes + 1) -> szExtType, TEXT("GeoObjects"));

	WQueryGeoObjects QObjs(pIEnum);
	W_DGeoObjects InObjs;

		THROW_FAILED_HRESULT(QObjs -> GetGeoObjects (InObjs.ppi()));

	_DGeoObjects *pIObjs = (_DGeoObjects *)InObjs;
	_DGeoObjects *pOutObjs = NULL;
		
		BSParams.pValues[0] = &pOutObjs;		// Returnwert setzen
		BSParams.pValues[1] = &pIObjs;			// erster Parameter

	// Entry laufen lassen
		pIObjs -> AddRef();						// BScript ruft Release()
		THROW_FAILED_HRESULT(m_pRunningObject -> RunEntry (strEntryName, 1, &BSParams, true, reinterpret_cast<INT_PTR>(m_hPrCtx), NULL));
		if (NULL == pOutObjs) _com_issue_error(E_UNEXPECTED);

	WQueryEnumLONG QEnum(pOutObjs);
	WEnumLONG EnumOut;

		pOutObjs -> Release();
		THROW_FAILED_HRESULT(QEnum -> QueryEnumLONG ((IEnumLONG **)EnumOut.ppi()));
#endif // _NEW_FILTERSCRIPT_TEMPLATE

		EnumOut -> Reset();
		*ppIEnumOut = EnumOut.detach();

	} // try
	catch (_com_error& e) 
	{	// E_UNEXPECTED  == RuntimeError
		hr =  _COM_ERROR(e);
	}
	if (BSParams.pTypes) { delete BSParams.pTypes; BSParams.pTypes = NULL; }
	if (BSParams.pValues) { delete BSParams.pValues; BSParams.pValues = NULL; }

	return hr;
}

//
// *** Dialog-Daten übergeben, konvertieren ***
//
HRESULT CFilterScriptDlg2::ConvertLongToObject (long lObjNr, _DGeoObject **ppIObj)
{
#if !defined(_NEW_FILTERSCRIPT_TEMPLATE)
	ASSERT(m_pIDoc);
	ASSERT(lObjNr > 0);		// !! Objektnummer immer größer 0

	if (m_pIDoc == NULL) return E_POINTER;
	if (lObjNr <= 0) return E_INVALIDARG;

	try
	{
	VARIANT vObj;
	VARIANT vMode;
			
		V_VT(&vObj)  = VT_I4;
		V_I4(&vObj)  = lObjNr;
		V_VT(&vMode) = VT_I2;
		V_I2(&vMode) = GEOOBJECTMODE_Get;

	// Übergebe Objektnummer, return IUnknown des Objekts als Variant
		THROW_FAILED_HRESULT(m_pIDoc -> GetObject(vObj, vMode, ppIObj));
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}
#endif // !_NEW_FILTERSCRIPT_TEMPLATE

	return S_OK;
}

HRESULT CFilterScriptDlg2::GetDocument()
{
#if !defined(_NEW_FILTERSCRIPT_TEMPLATE)
	if (NULL != m_pIDoc) return S_FALSE;
	try {
	// von OLE_Erweiterung IGetAppl. geben lassen
	WGetTRiASApplication IGA;

		THROW_FAILED_HRESULT(g_pTE -> m_pXtnSite -> GetXtension (
										CLSID_OleAutoExtension, 
										IID_IGetTRiASApplication, 
										IGA.ppv()
							 ));

	// Applikationsobjekt-Dispatchinterface an sich geben lassen
	W_DApplication IA;

		THROW_FAILED_HRESULT(IGA -> GetApplication(IID_DApplication, IA.ppv()));

	W_DDocument ID;	// W_DGeoObject

		THROW_FAILED_HRESULT(IA -> get_ActiveDocument(ID.ppi()));
		m_pIDoc = ID.detach();
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}
#endif // _NEW_FILTERSCRIPT_TEMPLATE
	return S_OK;
}

// StartNamen abfragen und setzen
HRESULT	CFilterScriptDlg2::SetStartName(LPCSTR lpcstrStartName)
{
	ASSERT(lpcstrStartName);
	if (NULL == lpcstrStartName) return E_POINTER;

// Nur schon Gespeicherte beim nächsten Mal laden
	if (GetInitNew()) {
		m_strStartName.Empty();
		return S_FALSE; 
	}

	m_strStartName = lpcstrStartName;
	return S_OK;
}

HRESULT	CFilterScriptDlg2::GetStartName(LPSTR lpstrStartName, UINT uiLen)
{
	if (uiLen < m_strStartName.GetLength())
		return E_FAIL;
	strcpy(lpstrStartName, m_strStartName);
	return S_OK;
}

// Liefert den jeweils nächsten EnumLONG mit Objekten, wenns der letzte war
// dann S_OK, wenn nicht dann S_FALSE, ansonsten einen FehlerCode
HRESULT CFilterScriptDlg2::GetEnumLONG (IEnum<long> **ppEnum)
{
	if (NULL == ppEnum) {
		ASSERT(0); return ResultFromScode (E_POINTER);
	}
	
	*ppEnum = NULL;		// für alle Fälle
	if (m_listEnumLongOut.size() == 0) 
		return E_UNEXPECTED;

	if (m_itEnLong != m_listEnumLongOut.end()) {
		*ppEnum = *m_itEnLong;
		(*ppEnum) -> AddRef();
		m_itEnLong++;
		return m_itEnLong == m_listEnumLongOut.end() ? S_OK : S_FALSE;
	}
	else 
		m_itEnLong = m_listEnumLongOut.begin();
	
return E_UNEXPECTED;
}

//
// *** Initialisierungen ***
//

HRESULT CFilterScriptDlg2::GetText(LPSTR *lplpstrText)
{
	ASSERT(lplpstrText);
	if (NULL == lplpstrText) return E_POINTER;
	*lplpstrText = NULL;
	// aktuellen Text besorgen
	UINT iLen = m_Debug.GetTextLength() + 1;
	if (iLen == 1) return E_FAIL;

	*lplpstrText = (LPSTR) CoTaskMemAlloc(iLen);
	if(NULL == *lplpstrText) return E_OUTOFMEMORY;

	iLen = m_Debug.GetText (*lplpstrText, iLen);
	if (0 != iLen) return S_OK;

	COTASKMEMFREE(*lplpstrText);
	return E_FAIL;
}

HRESULT CFilterScriptDlg2::InitSheetButtons(BOOL fNextDisable)
{
	CPropertySheet *pSh = (CPropertySheet *)GetParent();
	ASSERT(NULL != pSh);	
	if (pSh == NULL) return E_POINTER;

	DWORD dwBttns = 0;
	if ( ! (m_dwSheetBttns & ADDPAGES_FIRSTPAGE) )
		dwBttns = PSWIZB_BACK;

	CString str;
	m_cbxFilterScripts.GetWindowText(str);
	if ( !str.IsEmpty() && !fNextDisable ) {
		if (m_dwSheetBttns & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;
		else 
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwSheetBttns & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSh -> SetWizardButtons(dwBttns);

	return NOERROR;
}

HRESULT CFilterScriptDlg2::SetRect()
{
HWND hDebuggerSizeWnd = ::GetDlgItem(m_hWnd, IDC_DEBUGGERSIZE);	

	ASSERT(NULL != hDebuggerSizeWnd);

	if (NULL == hDebuggerSizeWnd) return E_HANDLE;

RECT DebuggerSizeRect, DlgRect;

	if (!::GetWindowRect(m_hWnd, &DlgRect) || !::GetWindowRect(hDebuggerSizeWnd, &DebuggerSizeRect)) {
		ASSERT(0); return ResultFromScode(E_FAIL);
	}

LONG lx = DebuggerSizeRect.left - DlgRect.left;
LONG ly = DebuggerSizeRect.top - DlgRect.top;
LONG lw = DebuggerSizeRect.right - DebuggerSizeRect.left;
LONG lh = DebuggerSizeRect.bottom - DebuggerSizeRect.top;

	m_Debug.SetRect((int)lx, (int)ly, (int)lw, (int)lh);

return NOERROR;
}
HRESULT CFilterScriptDlg2::EntryName(LPCSTR lpcstr)
{
	CString strName;
	if (!LoadString(strName, IDS_OPERATE)) return E_FAIL;
	if (0 == strcmp(lpcstr, strName)) 
	{// <Ohne Namen>
		if (!FilterMessageBox(IDS_SELECTSCRIPTNAME)) return E_FAIL;
//		m_cbxFilterScripts.SetEditSel(0, -1);
		m_cbxFilterScripts.SetFocus();
		return S_FALSE;
	}
	return S_OK;
}
////////////////////////////////////////////////////
// *** Save, Load ***
////////////////////////////////////////////////////
////////////////////////////////////////////////////
// Export die im Debugger befindlichen Code und Text
HRESULT CFilterScriptDlg2::Export()
{
HRESULT hr = NOERROR;
LPSTR lpstr = NULL;

	try {	// Für FileDialog Dir einstellen
	char cbPath[_MAX_PATH];

		cbPath[0] = '\0';
		ReadRegSettingsLastOpenFile (cbPath, _MAX_PATH);
	
	// FileDialog rufen
	CString strFileName (GetScriptName());
	CString strSave; ::LoadString(strSave, IDS_SAVEAS);
	UINT ui = FileDialog (cbPath, this, strFileName, false, strSave); 
	
		if (0 == ui) 
			return S_FALSE; // Cancel
	
	// Für nächsten FileDialog richtige Dir-Eistellung merken
		SaveRegSettingsLastOpenFile(GetPathName (strFileName));
	
	// Code, Text aus Debugger
		hr = GetText(&lpstr);
		if (FAILED(hr)) _com_issue_error(hr);
		ebHCODE hCode = NULL;
		if (m_Debug.Compile())
			hCode = m_Debug.GetCode();
		// Was wurde ausgewählt
		DWORD dwSaveFlag = 0;
		switch (ui) 
		{
			case 1: // Text
				dwSaveFlag = CC_SCRIPT | CC_EXPORT;
				strFileName = CorrectExtension (strFileName, IDS_SCRIPTEXT);
				break;
			case 2: // alles
				dwSaveFlag = CC_SCRIPT;
				if (hCode) dwSaveFlag |= CC_CODE;
				strFileName = CorrectExtension (strFileName, IDS_COMPLIEDSCRIPTEXT);
				break;
			case 3: // Code
				if (hCode) dwSaveFlag |= CC_CODE;
				strFileName = CorrectExtension (strFileName, IDS_COMPLIEDSCRIPTEXT);
				break;
		}
		WObjManHelper IOMH = m_pRunningObject;
		hr  = IOMH -> SaveAs (strFileName, lpstr, hCode, NULL, 0, dwSaveFlag);
		if (FAILED(hr)) _com_issue_error(hr);		
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	COTASKMEMFREE(lpstr);
	return hr;
}
////////////////////////////////////////////////////////////
// Import Code und Text aus externer Datei, überschreibt alten
HRESULT CFilterScriptDlg2::Import()
{
	HRESULT hr = NOERROR;
	try
	{
		hr = Save();					   
		if (FAILED(hr)) _com_issue_error(hr);
		if (S_FALSE == hr) return hr; // Cancel ?
		// Neues löschen
		hr = DeleteNew();
		if (FAILED(hr)) _com_issue_error(hr);
		// eigentlicher Import, File öffnen, nach Storage kopieren , File schliessen
		// Es wird hir kein neues geöffnet 
		hr = ImportScript();
		if (S_OK != hr) 
		{// Hier wenigstens NEUSES öffnen
			hr = OpenScript(GetScriptName());
			if (FAILED(hr)) _com_issue_error(hr);
		}
	} 
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	} 
	return hr;
} 
HRESULT CFilterScriptDlg2::ImportScript()
{
HRESULT hr = NOERROR;
LPSTR lpstrText = NULL;
ebHCODE hCode = NULL;
LPSTR *lplpstr = NULL;
UINT ui = 0;

	try {	// Für FileDialog Dir einstellen
	char cbPath[_MAX_PATH];

		cbPath[0] = '\0';
		ReadRegSettingsLastOpenFile (cbPath, _MAX_PATH);

	// FileDialog rufen
	CString strFileName;
	UINT ui = FileDialog (cbPath, this, strFileName); 

		if (0 == ui) return S_FALSE; // Cancel

	// Für nächsten FileDialog richtige Dir-Eistellung merken
		SaveRegSettingsLastOpenFile(GetPathName (strFileName));

	// eigentlicher Import, File öffnen, nach Storage kopieren , File schliessen
	// Es wird hir kein neues geöffnet 
	WObjManHelper IOMH = m_pRunningObject;

		hr = IOMH -> Import (CLSID_FileScript, strFileName, &lpstrText, &hCode, &lplpstr, ui);
		HRESULT hr1 =  MessageNoText(this->GetSafeHwnd(), lpstrText);
		if (FAILED(hr1)) _com_issue_error(hr1);
		if (FAILED(hr)) _com_issue_error(hr);
	
		m_Debug.SetText(lpstrText); // Text setzen
		// In Combo eintragen
		InsertCombo(GetScriptName());

		GenerateCaption (strFileName);
		SetButtons(GetScriptName());
		::SetFocus(m_Debug.GetWindow());				
	} 
	catch (bad_alloc) 
	{
		AfxMessageBox("Kein ausreichender Speicher vorhanden!");
		hr = E_OUTOFMEMORY;
	} 
	catch (_com_error & e) 
	{
		TRACE("Fehler: 0x%x in Modul OnDebugImport()!", hr);
		hr = _COM_ERROR(e);
	} 
	COTASKMEMFREE(hCode);
	COTASKMEMFREE(lpstrText);
	MEMFREE(lplpstr, ui);
	return hr;
} 
// Für Inititialisierungs-Script
HRESULT CFilterScriptDlg2::OpenInit()
{// Initialisierungsobject bilden,
	// Dazu erstes nicht genutztes Makro suchen
	char str[_MAX_PATH];
	HRESULT hr = NOERROR;
	// erstmal versuchen, den Startscriptnamen zu laden
	if (m_strStartName.IsEmpty())// leer, also Defaultname laden
	{
		hr = GetInitName(str, _MAX_PATH);
		if (FAILED(hr)) return hr;
		m_strStartName = str;
	}
	// richtiges Script öffnen
	return OpenScript(m_strStartName);	
}
////////////////////////////////////////////////////
// Öffnet beliebigen Stoareg-Script
HRESULT CFilterScriptDlg2::Open(LPCSTR lpcstrScriptName)
{
	ASSERT(NULL != lpcstrScriptName);
	if (NULL == lpcstrScriptName) return E_POINTER;
	// Gleiches, wie Geladenes, nicht öffnen
	if (lpcstrScriptName == GetScriptName()) return S_FALSE;	
	
	try
	{
		// Save altes, wenn dirty
		HRESULT hr = Save();	
		if (S_OK != hr) _com_issue_error(hr); // S_FALSE == Cancel
		// Altes, wenn noch initneu Löschen
		hr = DeleteNew();
		if (FAILED(hr)) _com_issue_error(hr);
		// Neues öffnen
		hr = OpenScript(lpcstrScriptName);
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}
////////////////////////////////////////////////////
// Speichert die im Debugger befindlichen Code und Text
HRESULT CFilterScriptDlg2::Save()
{
	int iRet = AskSave();

	switch (iRet) 
	{
	case 0: // nicht dirty
		break;

	case IDYES:
		SaveLoaded();
		break;		

	case IDCANCEL:
		// nicht weitermachen, RAUS
		return S_FALSE;
		break;

	case IDNO:
		// nicht speichern, rücksetzen
		SetDirty(false);
		break;
	}

	return S_OK;
}
HRESULT CFilterScriptDlg2::SaveLoaded()
{
	HRESULT hr = NOERROR;
	ebHCODE  hCode = NULL;
	LPSTR lpstr = NULL;
	LPSTR *lplpstr = NULL;
	UINT uiCnt = 0;
	DWORD dwSaveFlag = 0;

	try
	{	
		// Code und Text kommen aus Debugger
		if (m_Debug.Compile())
			hCode = m_Debug.GetCode(false);
		if (hCode) dwSaveFlag = CC_CODE;
		// Text geben lassen, ist Membor vom Dialog
		hr = GetText(&lpstr);
		if (FAILED(hr)) _com_issue_error(hr);
		if (lpstr) dwSaveFlag |= CC_SCRIPT;
		// Related Scripts kommen aus altem Script
		// hr = GetRelated(&lplpstr, uiCnt);
		// if (FAILED(hr)) _com_issue_error(hr);
		// Treeitem geben lassen
		WRunningObject IR;
		hr = GetLoadedItem(IR.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		// in Save werden pText, lplpstr, freigegeben
		WObjManHelper IOMH = IR;
		hr = IOMH -> Save(lpstr, hCode, lplpstr, uiCnt, dwSaveFlag);
		if (FAILED(hr)) _com_issue_error(hr);

		SetButtons(GetScriptName());
		GenerateCaption (GetScriptName());
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	MEMFREE(lplpstr, uiCnt);
	COTASKMEMFREE(lpstr);
	return hr;
}
// Dient zum Öffnen eines neuen RunningObject
HRESULT CFilterScriptDlg2::OpenOther(LPCSTR lpcstr, REFIID riid, ebHCODE *phCode, LPSTR *lplpstr)
{
	ASSERT(phCode);
	ASSERT(lplpstr);
	if (NULL == phCode || NULL == lplpstr) 
		return E_POINTER;

	*phCode = NULL;
	*lplpstr = NULL;

IRunningObject *pIR = NULL;
LPSTR *lplpstrRel = NULL;
UINT ui = 0;			// Bei FunctionLevel alten Text vom Script belassen

	COM_TRY {
		pIR = new CComObject<CRunningFilterObject>;
		if (NULL == pIR) _com_error(E_POINTER);

	// Object aufheben, altes vorher freigeben
		SetLoadedItem(pIR);

	// Management setzen
	WObjectManagement IOM;
	WStreamInfo ISI;

		THROW_FAILED_HRESULT(GetFilterScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoFilterScripts(ISI.ppi()));

		pIR -> SetManagement(IOM, ISI, riid, lpcstr);
	
	// Öffnen immer nach Management setzen durchführen
	WObjManHelper IOMH (pIR);

		pIR = NULL;		// doppeltes delete im Fehlerfall vermeiden
		THROW_FAILED_HRESULT(IOMH -> Open(lplpstr, phCode, &lplpstrRel, ui));	// Text, Code, StringListe geben lassen

	} COM_CATCH_OP((delete pIR, MEMFREE(lplpstrRel, ui)));

	MEMFREE(lplpstrRel, ui);		// Stringliste wird an dieser Stelle nicht benötigt
	return S_OK;
}
int CFilterScriptDlg2::AskSave(void)
{
	if (!GetDirty()/* && !m_fModified*/) return 0;

CString strPrompt, strTemplate;

// Fehler
	if (GetScriptName().IsEmpty()) 
		return E_FAIL;
	if (!LoadString (strTemplate, IDS_SAVEPROMPTSTORAGE)) 
		return E_OUTOFMEMORY;

	strPrompt.Format (strTemplate, GetScriptName());
	return AfxMessageBox (strPrompt, MB_YESNO|MB_TASKMODAL);
}

HRESULT CFilterScriptDlg2::Delete()
{
	try {
		WRunningObject IR;
		// AddRef() (hier == 2)
		HRESULT hr = GetLoadedItem(IR.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		// Mit Delete() wird gewährleistet, daß IR aus der Objektliste in der Objektverwaltung fliegt
		// Query() (hier == 3)
		WObjManHelper IOMH = IR;
		hr = IOMH -> Delete();		
		if (FAILED(hr)) _com_issue_error(hr);
		// String muss nun noch aus Combo entfernt werden		
		DeleteCombo(GetScriptName());
	} catch (_com_error& e) {
		return _COM_ERROR(e);
	}	
	return S_OK;// WRunningObject -> Release() == 2
				//	WObjManHelper -> Release() == 1
}
void CFilterScriptDlg2::InsertCombo(LPCSTR lpcstr)
{
	ASSERT(lpcstr);
	if (NULL == lpcstr) return;
	// nur, wenn NICHT in Listbox
	if (CB_ERR == m_cbxFilterScripts.FindString(-1, lpcstr))
		m_cbxFilterScripts.InsertString(0, lpcstr);
	m_cbxFilterScripts.SetWindowText(lpcstr);
}
void CFilterScriptDlg2::DeleteCombo(LPCSTR lpcstr)
{
	ASSERT(lpcstr);
	if (NULL == lpcstr) return;
	int iFind = m_cbxFilterScripts.FindString(-1, lpcstr);
	// nur, wenn in Listbox
	if (iFind != CB_ERR)
		m_cbxFilterScripts.DeleteString(iFind);
}
HRESULT CFilterScriptDlg2::DeleteNew()
{// Nur löschen, wenn neu erzeugt
	if (false == GetInitNew()) return S_FALSE;
	return Delete();
}
HRESULT CFilterScriptDlg2::OpenScript(LPCSTR lpcstr)
{	// Initialisierungsobject bilden
	ebHCODE hCode = NULL;
	LPSTR lpstr = NULL;
	HRESULT hr = OpenOther(lpcstr, CLSID_Script, &hCode, &lpstr);	
	if (hCode) CoTaskMemFree(hCode); hCode = NULL;// Code gleich wieder freigeben
	HRESULT hr1 =  MessageNoText(this->GetSafeHwnd(), lpstr);
	if (FAILED(hr1)) return(hr1);
	if (FAILED(hr)) return hr;
	// Debugger, Combo und Edit setzen
	m_Debug.SetText(lpstr); // NUR Text setzen !!!
	// Combo und Edit setzen
	InsertCombo(GetScriptName());

	GenerateCaption (GetScriptName());
	SetButtons(GetScriptName());
	::SetFocus(m_Debug.GetWindow());				
	// Text wieder freigeben
	COTASKMEMFREE(lpstr);
	return S_OK;
}

long CFilterScriptDlg2::Changed(void)
{
//	if (S_FALSE == EntryName(GetScriptName())) return 0;// Ohne Name ???
	SetDirty(true);
	SetButtons(GetScriptName());
	GenerateCaption (GetScriptName());
	return 0;
}
HRESULT CFilterScriptDlg2::GetInitName(LPSTR lpstrDefaultName, UINT uiLen)
{
	ASSERT(uiLen > 0);
	ASSERT(lpstrDefaultName);

	WObjectManagement IObjFeatObjManagement;
	WObjectManagement IObjManagement;
	WObjectManagement IFilterObjManagement;
	CString  strDefault = GetDefaultName(IDS_DEFAULTMACRONAMEWITHCOUNT);
	UINT ui = 1;
	HRESULT hr = E_FAIL;
	
	// Alle Container (und noch andere SPÄTER) durchsuchen
	hr = GetFilterScripts(IFilterObjManagement.ppi());
	if (FAILED(hr)) return hr;
	hr = GetGeneralScripts(IObjManagement.ppi());
	if (FAILED(hr)) return hr;
	hr = GetObjFeatScripts(IObjFeatObjManagement.ppi());
	if (FAILED(hr)) return hr;
	// ob z.B. "Makro #1" oder "Makro #100" noch nicht vorhanden ist
	// MAX_MACRO_CNT == 200
	while (ui < MAX_MACRO_CNT && lpstrDefaultName)
	{
		wsprintf(lpstrDefaultName, (LPSTR)(LPCSTR)strDefault, ui); 

		if ( ! FindFirstDefaultString(IObjManagement, lpstrDefaultName) &&
			 ! FindFirstDefaultString(IFilterObjManagement, lpstrDefaultName) &&
			 ! FindFirstDefaultString(IObjFeatObjManagement, lpstrDefaultName))
		{// Nirgendswo dieses Makro gefunden, also gültig
			hr = S_OK;
			break;			
		}
		ui++;
	}
	return hr;
}
//
// *** rechte Maustaste gedrückt ***
//
long CFilterScriptDlg2::RightButtonUp(ebPARAM1 np1)
{
	CMenu Menu;
	if (!Menu.LoadMenu(IDR_RBUTTONFILTER)) return 1;

	POINT pt;
    GetCursorPos(&pt);
	::SetFocus(m_Debug.GetWindow());		
	return !(Menu.GetSubMenu (0)) -> TrackPopupMenu(0, pt.x, pt.y, this);
}

/////////////////////////////////////////////////////////////////////////////
// *** MOUSE-Events: Menu-Commands ***

void CFilterScriptDlg2::OnEntfernen() 
{
	if (FAILED(Delete())) return;
	OpenInit();
//	DEX_SetDirtyGeoDB(true);
}

void CFilterScriptDlg2::OnDebugBreakpoint() 
{
// Breakpoints merken: aktuelle Zeile 
	m_Debug.ToggleBreakpoint(0);			
	// Curosposition geben lassen, um Breakpoint an dieserStelle zu merken
	ebDWORD dw = m_Debug.GetCursorPos();	
	BreakPointList::iterator it = m_setBreakPoints.find(dw);
	if (it != m_setBreakPoints.end()) {// existiert bereits: Breakpoint abgeschaltet
		m_setBreakPoints.erase (it);
	} else {
		m_setBreakPoints.insert (ebHIWORD(dw));
	}
}

void CFilterScriptDlg2::OnDebugCut() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.HasSelection()) {
		m_Debug.EditCut();
	}
}
void CFilterScriptDlg2::OnDebugCopy() 
{
	if (m_Debug.HasSelection()) {
		m_Debug.EditCopy();
	}
}
void CFilterScriptDlg2::OnDebugPaste() 
{
	if (m_Debug.GetState() != TS_RUNNING &&	::IsClipboardFormatAvailable (CF_TEXT)) {
		m_Debug.EditPaste();
	}
}
void CFilterScriptDlg2::OnDebugDelete() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.HasSelection())	
		m_Debug.EditClear();	
}
void CFilterScriptDlg2::OnDebugUndo() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.CanUndo())
		m_Debug.EditUndo();
}
void CFilterScriptDlg2::OnDebugNewdialog() 
{                        
	if (m_Debug.GetState() != TS_RUNNING)	
		m_Debug.InsertDialog();
                              
}
void CFilterScriptDlg2::OnDebugEditdialog() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.IsDialogSelected())	
		m_Debug.EditDialog();	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Dummiefunktionen, machen gar nichts
void CFilterScriptDlg2::OnDebugGo() 
{
}
void CFilterScriptDlg2::OnDebugTraceOver() 
{
}
void CFilterScriptDlg2::OnDebugTraceIn() 
{
}

// Menu-Init
void CFilterScriptDlg2::OnInitMenu(CMenu* pMenu) 
{
	CDialog::OnInitMenu(pMenu);

int iState = m_Debug.GetState();		
	
// Copy, Cut, Del enabled if there is a selection in the debugger control and if
// we are not executing
	UINT uiEnabled = (iState == ES_IDLE && m_Debug.HasSelection()) ? MF_ENABLED : MF_GRAYED;

	pMenu -> EnableMenuItem (ID_DEBUG_COPY, uiEnabled);
	pMenu -> EnableMenuItem (ID_DEBUG_CUT, uiEnabled);
	pMenu -> EnableMenuItem (ID_DEBUG_DELETE, uiEnabled);

// Undo
	uiEnabled = (iState == ES_IDLE && m_Debug.CanUndo()) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_UNDO, uiEnabled);

	uiEnabled = ((iState == ES_IDLE) && ::IsClipboardFormatAvailable (CF_TEXT)) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_PASTE, uiEnabled);

// DialogEditor
	uiEnabled = ((iState == ES_IDLE) && m_Debug.IsDialogSelected()) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_EDITDIALOG, uiEnabled);

	uiEnabled = (iState == ES_IDLE) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_NEWDIALOG, uiEnabled);	

// Speichern
	uiEnabled = (GetDirty()/* || m_fModified*/) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_SAVE, uiEnabled);	

// Hilfe
	char KeyWord[MAXSTRLENGTH];

	uiEnabled = (m_Debug.GetCaretWord(KeyWord, MAXSTRLENGTH)) ? MF_ENABLED : MF_GRAYED; 
	pMenu -> EnableMenuItem (ID_DEBUG_GETHELPON, uiEnabled);	
}

// *** ENDE MOUSE-Events: Menu-Commands ***
/////////////////////////////////////////////////////////////////////////////

// *** Hilfe ***
//
void CFilterScriptDlg2::OnDebugGetHelpOn()
{
char KeyWord[MAXSTRLENGTH];

	if (m_Debug.GetCaretWord(KeyWord, MAXSTRLENGTH)) {
		KeywordHelp(KeyWord);
	}
}

HRESULT CFilterScriptDlg2::SetKeptBreaks()
{
	try
	{// Script vom aktuellen RunningObject besorgen
		CebScript *pScript = NULL;		
		WBSProperty IBSP = m_pRunningObject; // Query...
		HRESULT hr = IBSP -> GetScript(&pScript);
		if (FAILED(hr)) _com_issue_error(hr);
		ASSERT(pScript);
		ASSERT(pScript->GetHandle());
		if (NULL == pScript) _com_issue_error(E_POINTER);
		if (NULL == pScript->GetHandle()) _com_issue_error(E_HANDLE);
		// gemerkte breks enumerieren und im Script setzen
		BreakPointList::iterator it = m_setBreakPoints.begin();
		while (it != m_setBreakPoints.end()) {
			if (0 == pScript -> SetBreakpoint(*it+1))
				_com_issue_error(E_FAIL); // Breakpoint im Script setzen (Script-Scope)
			it++;
		}
	}
	catch (_com_error&)
	{
	}
	return S_OK;
}

HRESULT CFilterScriptDlg2::KeywordHelp(LPCSTR lpKeyWord)
{
CString strPath;	
CString strName;
LPSTR pcStartupDir = strName.GetBuffer(MAXSTRLENGTH); 

	GetModuleFileName(NULL, pcStartupDir, MAXSTRLENGTH);	

	strPath = GetPathName(strName) + TEXT("\\AZ.HLP");

int id = -1;
HRESULT hr = LookupKeyword(lpKeyWord, id);

	if (SUCCEEDED(hr)) {
		if (!::WinHelp(m_hWnd, strPath, HELP_CONTEXT, id)) 
			return E_FAIL;
	}
	else {
		if (!::WinHelp(m_hWnd, strPath, HELP_CONTENTS, 0L)) 
			return E_FAIL;
	}

return NOERROR;
}

HRESULT CFilterScriptDlg2::LookupKeyword(LPCSTR lpKeyWord, int & id)
{
LPSTR lpszTemplateName = MAKEINTRESOURCE(AZ_KEYWORDS);
HANDLE hMem = NULL;
HINSTANCE hInst = NULL;
HRSRC hResource = NULL;

	// find the resrouce in my EXE
	hInst = AfxFindResourceHandle(lpszTemplateName, RT_RCDATA);
	if (hInst == NULL) return E_HANDLE;

	hResource = ::FindResource(hInst, lpszTemplateName, RT_RCDATA);
	if (hResource == NULL) return E_HANDLE;
	
	// allocate memory for it and load it in
	hMem = LoadResource(hInst, hResource);
	if (hMem == NULL) return E_HANDLE;

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

		if (!strcmpi(lpKeyWord, buf)) {
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

//
// *** Font für Debugger setzen ***
//

BOOL CFilterScriptDlg2::ParseFontInfo (LPSTR pBuffer, LPLOGFONT pLF)
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

BOOL CFilterScriptDlg2::ReadRegSettingsFont (LPLOGFONT pLF)
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

void CFilterScriptDlg2::SetFont()
{
	ASSERT(NULL == m_hFontOld);
	LOGFONT LF;
	memset (&LF, 0, sizeof(LOGFONT));
	if (ReadRegSettingsFont (&LF) ) {
		m_hFontOld = m_Debug.GetFont(); 
		m_Debug.SetFont (::CreateFontIndirect (&LF));
	} else 
		m_hFontOld = NULL;		
}

void CFilterScriptDlg2::ResetFont()
{
	if (m_hFontOld) 
		m_Debug.SetFont (m_hFontOld);		
	m_hFontOld = NULL;
}

//
// *** andere globale Funktionen ***
//
BOOL LoadString(CString & str, int IDS)
{
	TRY {                               
	HINSTANCE hInst = AfxGetResourceHandle();

		if (NULL == hInst) return false;
		AfxSetResourceHandle(g_hInstance);
		if (0 == str.LoadString (IDS)) 
			return false;	
		AfxSetResourceHandle(hInst);
	}
	CATCH (CMemoryException, e) {
		MessageBox(GetActiveWindow(), "Kein Speicher verfügbar!", "Makroprogrammierung", MB_OK); 
		return false;
	}                  
	END_CATCH
	return true;
}


BOOL CFilterScriptDlg2::OnKillActive() 
{
	return CPropertyPage::OnKillActive();
}

///////////////////////////////////////////////////////////////////////////////
// Speichern übers Menu
void CFilterScriptDlg2::OnDebugSave() 
{
	SaveLoaded();
}

///////////////////////////////////////////////////////////////////////////////
// Script als Datei exportieren
void CFilterScriptDlg2::OnDebugExport (void) 
{
	Export();
}

///////////////////////////////////////////////////////////////////////////////
// # einer Datei
void CFilterScriptDlg2::OnDebugImport() 
{
	Import();
}

BOOL CFilterScriptDlg2::FilterMessageBox(int iIDS1)
{
	CString str, strClN;
	if (!LoadString(str, iIDS1) ||
		!LoadString(strClN, IDS_LONGCLASSNAMEFILTERSCRIPT)) 
	{
		return false;
	}
	MessageBox(str, strClN, MB_ICONEXCLAMATION);
return true;
}

BOOL CFilterScriptDlg2::GenerateCaption (LPCSTR lpcstr)
{
	CString strCaption, strAppName, strName; 
	char *pCaption = NULL;

	try {
		pCaption = strCaption.GetBuffer (_MAX_PATH);
		if (pCaption == NULL) return false;
	}
	catch (CMemoryException*) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  

	strName = lpcstr;
	strAppName = GetDefaultName(IDS_LONGCLASSNAME);

	if (strName.IsEmpty())
	{// für Initfirst
		wsprintf (pCaption, "%s", strAppName);
	}
	else
	{// eventuell Filenamen geben lassen, da im Object vollständiger Pfad abgespeichert ist
		//strName = GetFileName(strName, true);
		wsprintf (pCaption, "%s - [%s%s]", strAppName, strName, (GetDirty()/* || m_fModified*/) ? "*" : g_cbNil);
	}
	
	// eigentliche Caption setzen
	GetParent() -> SetWindowText (pCaption);

	return true;
}


