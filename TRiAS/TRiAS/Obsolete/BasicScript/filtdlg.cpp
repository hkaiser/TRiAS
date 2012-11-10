// filtdlg.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#include <direct.h>
#include <oleguid.h>
#include <dirisole.h>
#include <triastlb.h>
#include <itriasap.h>

#include "macrguid.h"

#include "conststr.h"
#include "imacro.h"
#include "imacorg.h"
#include "enumscpt.h"
#include "strmimp.h"
#include "perstimp.h"
#include "macroimp.h"
#include "macro.h"

#include "toolbarx.h"
#include "bscripta.h"
#include "runerr.h"
#include "filtdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

//////////////////////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
#define OS_NO_STREAM_SUPPORT

DefineSmartInterface(Dispatch);
DefineSmartInterface(Storage);
DefineSmartInterface(PersistStorage);
DefineSmartInterface2(_DGeoObject, IID_DGeoObject);	// W_DGeoObject

//DefineSmartInterface(ScriptContainer);
DefineSmartInterface(EnumScripts);
DefineSmartInterface(Script);

//////////////////////////////////////////////////////////////////////////////////////////////
// globale Variablen 
extern CRunErr *g_pRunErr;
extern SummitModul g_SummitModuls[];

//////////////////////////////////////////////////////////////////////////////////////////////
// globale Funktionsdeklarationen
bool LoadString(CString & str, int IDS);
CString GetPathName (CString &rPath);
bool ReadRegSettingsLastOpenFile (char *pc, DWORD dwL);
bool SaveRegSettingsLastOpenFile (LPCSTR pc);
CString CorrectExtension (CString &rPath, UINT uiResIDExt);

//////////////////////////////////////////////////////////////////////////////////////////////
// CALLBACK Funktionsdeklarationen 
extern "C"
void ebCALLBACK _XTENSN_EXPORT OnRuntimeError (
		long lParam, ebLPCTSTR lpMsg, ebDWORD dwErrNum,
		ebWORD wLinNr, ebWORD wCharPos, ebLPCTSTR lpSource,
		ebLPCTSTR lpHelpFile, ebDWORD dwHelpContext);

/////////////////////////////////////////////////////////////////////////////
//												   Idle, Run, Susp, Hilight
static Accelerator AccTable[] = 
{
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
	
	return CustomTranslateAccelerator (pDebug, AccTable, GetParent(hWnd), message, wParam, lParam);
}

long ebCALLBACK EXPORT HandleFilterDebuggerNotification(HWND hWnd,int code,ebPARAM1 np1,ebPARAM2 np2,long lPassThrough)
{
	switch (code) {
	case DN_ERRSPACE:	// Sent, when memory-error occured
		return AfxMessageBox(IDS_NOMEMORY);

	case DN_COMPILE:	// Sent immediately before compilation	
		break;

	case DN_COMPILEEND:
		break;

	case DN_CHANGED:	// script saving is required
		return ((CFilterScriptDlg *)lPassThrough) -> Changed();
		
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
		return ((CFilterScriptDlg *)lPassThrough) -> RightButtonUp(np1);

	default:
		break;
	}

return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CFilterScriptDlg property page

IMPLEMENT_DYNCREATE(CFilterScriptDlg, CPropertyPage)

CFilterScriptDlg* CFilterScriptDlg::CreateInstance(void)
{
	if (!g_SummitModuls[COMPILER].fIsInstalled || 
		!g_SummitModuls[RUNTIME].fIsInstalled)
	{
		return NULL;
	}

CFilterScriptDlg* pFD = NULL;

	TRY {
		pFD = new CFilterScriptDlg();
		if (!pFD -> FInit()) {
			DELETE(pFD);
			return NULL;
		}

	} CATCH (CMemoryException, e) {
		return NULL;
	} END_CATCH;

	return pFD; 
}

// Member Script, Thread, Document und Speicherverwaltung zurücksetzen
void CFilterScriptDlg::Reset()
{
	DELETE(m_pScript);

	if (m_pThread) {
	// versucht, auch GeoObjekt freizugeben !!!, deshalb Pointer ausnullen:
		m_pThread -> SetParamObject (1, 0);

		delete m_pThread;
		m_pThread = NULL;
	}
	RELEASE(m_pIDoc);
}

bool CFilterScriptDlg::FInit(void)
{
	m_itEnLong = m_listEnumLongOut.begin();
	
	return true;
}

CFilterScriptDlg::CFilterScriptDlg() 
		:	CPropertyPage(CFilterScriptDlg::IDD),
			m_rInst (((CMacroScriptExtension *)g_pTE)->ebInst())
{
	//{{AFX_DATA_INIT(CFilterScriptDlg)
	//}}AFX_DATA_INIT

	m_pOperateScripts = NULL;
	m_pSuspendDeb = NULL;
	m_pRunErr = NULL;

	m_pScript = NULL;
	m_pThread = NULL;

	m_pText = NULL;

	m_dwSheetBttns = 0;
	m_fInitNew = false;
	m_fIsDirty = false;	
	
	m_Types[0].wType = TYP_INTEGER;
	m_Types[0].szExtType[0] = '\0';

	m_Types[1].wType = TYP_APPOBJECT;
	strcpy(m_Types[1].szExtType, "GeoObject");
	
	m_pIDoc = NULL;
	m_hFontOld = NULL;

	m_fModified = false;
}

CFilterScriptDlg::~CFilterScriptDlg()
{	
	if (m_pText) {
		CoTaskMemFree (m_pText); 
		m_pText = NULL;
	}

	ResetFont();	// Font zurücksetzen

// eventuell Member Script, Thread, Document und Speicherverwaltung zurücksetzen
	Reset();

#if defined(_DEBUG)
DWORD dw = 0L;

	if (m_pOperateScripts) 
		dw = m_pOperateScripts -> Release();
	if (NULL == g_pRunErr == NULL) 
		ASSERT(0 == dw);
	m_pOperateScripts = NULL;
#else
	RELEASE(m_pOperateScripts);	
#endif // _DEBUG
}

void CFilterScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterScriptDlg)
	DDX_Control(pDX, IDC_ENTFERNEN, m_bttnEntfernen);
	DDX_Control(pDX, IDC_SYNTAXTEST, m_Test);
	DDX_Control(pDX, IDC_COMBOOPATESCRIPTS, m_cbxFilterScripts);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterScriptDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CFilterScriptDlg)
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
	// Dummies
	ON_COMMAND(ID_DEBUG_GO, OnDebugGo)
	ON_COMMAND(ID_DEBUG_TRACEIN, OnDebugTraceIn)
	ON_COMMAND(ID_DEBUG_TRACEOVER, OnDebugTraceOver)
	ON_WM_INITMENU()
	ON_COMMAND(ID_DEBUG_GETHELPON, OnDebugGetHelpOn)	
	ON_COMMAND(ID_DEBUG_SAVE, OnDebugSave)
	ON_WM_CREATE()
	ON_COMMAND(ID_DEBUG_IMPORT, OnDebugImport)
	ON_COMMAND(ID_DEBUG_EXPORT, OnDebugExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterScriptDlg message handlers

BOOL CFilterScriptDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	try {
		THROW_FAILED_HRESULT(CreateScript());

		m_pOperateScripts = CMacroScripts::CreateScript (NULL, &m_rInst);
		if (NULL == m_pOperateScripts) throw E_OUTOFMEMORY;

		THROW_FAILED_HRESULT(LoadStorage());
	
	// Listbox füllen
		THROW_FAILED_HRESULT(Fill());
	
	// ersten Script öffnen, in Liste, Stream öffnen	
	// Dieser darf nicht <defaultname> haben (z.B. <Ohne Name>)
		THROW_FAILED_HRESULT(LoadInitialScript());

		SetFont();

	} catch (HRESULT) {
		RELEASE(m_pOperateScripts);
		ASSERT(false);
		return false;
	}
		
return true;  // return true  unless you set the focus to a control
}	   

BOOL CFilterScriptDlg::OnSetActive() 
{
	ASSERT(NULL != m_hWnd);

	if (CPropertyPage::OnSetActive()) {
		if (FAILED(InitSheetButtons())) 
			return false;
		
	// BACK !!!	
		if (NULL != m_pText) {
		// Fenster setzen
			m_rInst.SetWindow (m_hWnd);	
			if (FAILED(InitOperateScript(m_pText))) 
				return false;
		}
	
	// Daten für KeyboardFilterProc merken
		if (!SetProp (m_Debug.GetWindow(), g_cbKeyboardFilterData, (HANDLE)&m_Debug)) 
			return false;

		return true;
	}

return false;
}

// *** ComboBox-Kommandos ***
void CFilterScriptDlg::OnEditChangeCB() 
{
CString str;

	m_cbxFilterScripts.GetWindowText(str);
	if (str.IsEmpty()) 
		m_bttnEntfernen.EnableWindow(false);
	else
		m_bttnEntfernen.EnableWindow(true);

	m_fModified = true;
}

void CFilterScriptDlg::OnKillFocusCB() 
{
	if (m_fModified == false) return;

CString str;

	m_cbxFilterScripts.GetWindowText(str);

	if (str.IsEmpty()) {
		m_bttnEntfernen.EnableWindow(false); 
		return;
	} else
		m_bttnEntfernen.EnableWindow(true);

// altes Script eventuell löschen
	if (m_fInitNew) {
		if (FAILED(Delete())) return;
	}

	m_strMacroName = str;
	LoadScript();			// Scriptnamen in Liste, Stream öffnen
}

void CFilterScriptDlg::OnSelChangeCB() 
{
CString str;
// erst Selection überprüfen
	if (CB_ERR == m_cbxFilterScripts.GetCurSel()) 
		return;

	m_cbxFilterScripts.GetLBText(m_cbxFilterScripts.GetCurSel(), str);

// Text o.k. ?
	if (str.IsEmpty()) {
		m_bttnEntfernen.EnableWindow(false); 
		return;
	} else 
		m_bttnEntfernen.EnableWindow(true);

	if (str == m_strMacroName) return;

// unter alten Namen:
// nach Speichern fragen UND Speichern an sich 
HRESULT hr = AskSave();
	// Cancel
	if (GetScode(hr) == S_FALSE || FAILED(hr)) return;

// neuen Namen merken	
	m_strMacroName = str;

// neues Script eventuell laden, Stream Öffnen
	LoadScript();
}

// *** Compilebutton ***
void CFilterScriptDlg::OnSyntaxTest() 
{
	if (m_Debug.Compile()) 
		FilterMessageBox(IDS_NOERRORSFOUND);		
}

// *** Löschen eines Scripts ***
void CFilterScriptDlg::OnEntfernen() 
{
	if (SUCCEEDED(Delete())) 
		LoadInitialScript();
}

//
// *** Wizard-Kommandos ***
//
void CFilterScriptDlg::OnCancel() 
{
// Property für KeyboardRoutine wieder freigeben
CWnd *pWnd = GetDlgItem (CFilterScriptDlg::ID_DEBUG);

	ASSERT(NULL != pWnd);
	if (NULL != GetProp (pWnd -> GetSafeHwnd(), g_cbKeyboardFilterData))
		RemoveProp (pWnd -> GetSafeHwnd(), g_cbKeyboardFilterData);

	if (m_fInitNew) {
		if (FAILED(Delete())) return;
	}
	Reset();

// Fenster zurücksetzen, da Debuggerfenster als Member nun zerlegt wird
	m_rInst.SetWindow (((CMacroScriptExtension *)g_pTE) -> hWnd());	
	CPropertyPage::OnCancel();
}

LRESULT CFilterScriptDlg::OnWizardNext() 
{
	if (0 == WizardFinishNext())
		return CPropertyPage::OnWizardNext();

	return -1;	// Fehler
}

BOOL CFilterScriptDlg::OnWizardFinish() 
{
// Property für KeyboardRoutine wieder freigeben
CWnd *pWnd = GetDlgItem (CFilterScriptDlg::ID_DEBUG);

	ASSERT(NULL != pWnd);
	if (NULL != GetProp (pWnd -> GetSafeHwnd(), g_cbKeyboardFilterData))
		RemoveProp (pWnd -> GetSafeHwnd(), g_cbKeyboardFilterData);

	if (0 == WizardFinishNext())
		return CPropertyPage::OnWizardFinish();		// alles ok

	return 0;	// Fehler!
}

LRESULT CFilterScriptDlg::OnWizardBack() 
{	
	return CPropertyPage::OnWizardBack();
}

////////////////////////////////////////////////////////////////////
// *** Hilfsfunktionen ***
LRESULT CFilterScriptDlg::WizardFinishNext()
{
ebHCODE hCode = NULL;
	
	if (!m_Debug.Compile()) return -1;

	hCode = m_Debug.GetCode(false);
	if (hCode == NULL) {
		TRACE("Codehandle ist Null !");
		return -1;
	}
		
// bei "Ohne Namen", Löschen ohne Name, Load neuer
HRESULT hr = EntryName();

	if (FAILED(hr)) {
		TRACE("Fehler bei Nameneingabe !");
		return -1;
	}
	if (S_FALSE == GetScode(hr)) return -1;	// Namen eingeben

// nach Speichern fragen UND Speichern an sich
	hr = AskSave();
	if (FAILED(hr)) {
		TRACE("Fehler beim Abspeichern !");
		return -1;
	}
	if (S_FALSE == GetScode(hr)) return -1;	// Cancel()

	if (FAILED(GetText())) {
		TRACE("Text ungültig !");
		return -1;
	}

// Member Script, Thread, Document und Speicherverwaltung zurücksetzen
	Reset();

// Script kreieren und Entry des Scripts überprüfen, Thread für DoAction() kreieren
// BeginAction(), EndAction() nur einmal bei Aufruf kreieren
	hr = GetDocument();
	if (FAILED(hr)) {
		TRACE("Fehler bei Erzeugen des Dokuments !");
		return -1;
	}
															
	hr = CreateScriptAndThread (hCode);
	if (E_ABORT == hr) return -1;		// Entrypoint fehlerhaft
	if (FAILED(hr)) {
		TRACE("Fehler bei Script- oder Threaderzeugung !");
		return -1;
	}

// Fenster zurücksetzen, da Debuggerfenster als Member nun zerlegt wird
HWND hWnd = ((CMacroScriptExtension *)g_pTE) -> hWnd();

	ASSERT(NULL != hWnd);
	m_rInst.SetWindow (hWnd);

return 0;
}

HRESULT CFilterScriptDlg::CreateScriptAndThread (ebHCODE hCode)
{
	ASSERT (NULL != hCode);

	try {
		THROW_FAILED_HRESULT(SetEntryInfoAction (m_EI, true/* Function */, IDS_DOACTION, 1));
		ASSERT(m_EI.GetEntryInfo());

	// EntryPoint überprüfen
		if (ebCheckEntry ((ebHOBJECT)hCode, m_EI.GetEntryInfo())) {
			if (!FilterMessageBox(IDS_BADENTRY)) 
				throw E_FAIL;
			throw E_ABORT;
		}

		try {
		// allgemeinen Script für Begin-, Do-, EndAction() erzeugen
			m_pScript = new CebScript (&m_rInst, hCode, NULL, 0);
			if (m_pScript -> Create()) 
				throw E_FAIL;
		
		// Thread für DoAction() erzeugen
			m_pThread = new CebThread (m_pScript, m_EI.GetEntryInfo());
			if (m_pThread -> Create(2*sizeof(long))) 
				throw E_FAIL;

		} catch (bad_alloc) {
			throw E_OUTOFMEMORY;
		}

		THROW_FAILED_HRESULT(SetBreakPoints (m_pThread));

	} // try
	catch (HRESULT hr) {
		if (E_OUTOFMEMORY == GetScode(hr)) 
			AfxMessageBox (IDS_NOMEMORY);
		else 
			ASSERT(false);

		DELETE(m_pThread); 
		DELETE(m_pScript); 
		return hr;
	}

return S_OK;
}

HRESULT CFilterScriptDlg::DoAction(IEnum<long> *pIEn)
{
	ASSERT(NULL != pIEn);
	if (pIEn == NULL) return E_POINTER;

HRESULT hr = SetEntryInfoAction (m_EI, true/* Function */, IDS_DOACTION, 1);				
	
	if (FAILED(hr)) return hr;
	ASSERT(m_EI.GetEntryInfo());

WEnumLONG IEnumOut;		// AddRef()
	
	hr = CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, 
			CLSCTX_INPROC_SERVER, IID_IEnumLONG, IEnumOut.ppv());
	if (FAILED(hr)) return hr;

// jedes einzelne Objekt abarbeiten und Ausgabeliste füllen
	hr = RunThreadHelper(pIEn, IEnumOut); // AddRef()
	if (FAILED(hr)) return hr; // E_ABORT: Debugger zu, E_UNEXPECTED: RuntimeError

// in Ausgabeliste eintragen, AddRef()
	m_listEnumLongOut.insert(m_listEnumLongOut.end(), IEnumOut);
	m_itEnLong = m_listEnumLongOut.begin();

// IEnumOut->Release() von WEnumLONG() 
	return NOERROR;
}

HRESULT CFilterScriptDlg::RunThreadHelper(IEnum<long> *pIEnum, IEnum<long> *pIEnumOut)
{
	ASSERT(pIEnum);
	ASSERT(pIEnumOut);
	ASSERT(!m_strMacroName.IsEmpty());

	if (pIEnum == NULL || pIEnumOut == NULL) return ResultFromScode(E_POINTER);
	if (m_strMacroName.IsEmpty()) return ResultFromScode(E_FAIL);

HRESULT hr = NOERROR;
LONG lRetObj = 0;
LONG lObj = 0;
	
	try {
		pIEnumOut -> Reset();

	// noch Schleife für alle Objekte im Enum !!!
		for (pIEnum -> Reset(); S_OK == pIEnum->Next(1, &lObj, NULL); /**/) {
			if (lObj <= 0) throw ResultFromScode(E_INVALIDARG);

		// Konvertierung long zu Objekt
			{
			W_DGeoObject IObj;
												 // AddRef()
				hr = ConvertLongToObject (lObj, IObj.ppi());
				if (FAILED(hr)) throw hr;

				ASSERT(NULL != (_DGeoObject *)IObj);

			// Thread ausführen, oder bei BreakPoints Debugger starten
				hr = RunThread (lRetObj, (ebDWORD)(_DGeoObject *)IObj);
				if (FAILED(hr)) throw hr;
			} // IObj geht out of scope, Release()

		// Soll Objekt weitergereicht werden ?	
			if (0 != lRetObj) 
				pIEnumOut -> AddItem (lObj);
		}
	} // try
	catch (HRESULT hr) {	
		// E_UNEXPECTED  == RuntimeError
		if (E_UNEXPECTED != hr) {
			DELETE(m_pRunErr);
		}
		DELETE(m_pSuspendDeb);
		return hr;
	}

return hr;
}

HRESULT CFilterScriptDlg::SetRuntimeErrorProc(CRunErr **ppRunErr)
{
	ASSERT(!m_strMacroName.IsEmpty());
	if (m_strMacroName.IsEmpty()) return E_FAIL;

	ASSERT(m_pText);
	ASSERT(m_pThread);
	if (m_pThread == NULL || m_pText == NULL) return E_POINTER;
	
	ASSERT(m_pThread->GetHandle());
	if (m_pThread->GetHandle() == NULL) return E_HANDLE;

	if (NULL == ppRunErr) return E_POINTER;

	*ppRunErr = NULL;

CRunErr *pRunErr = new CRunErr (m_pOperateScripts, m_pText, m_strMacroName);

	if (pRunErr == NULL) {
		AfxMessageBox(IDS_NOMEMORY);
		return E_OUTOFMEMORY;
	}

	*ppRunErr = pRunErr;

	m_pThread -> SetRuntimeErrorProc(&OnRuntimeError, (ebDWORD)*ppRunErr);

return NOERROR;
}

HRESULT CFilterScriptDlg::OnDemandDebugger (CRunErr **ppSuspendDeb)
{
	ASSERT(m_pText);
	ASSERT(!m_strMacroName.IsEmpty());
	ASSERT(m_pOperateScripts);

	if (NULL == ppSuspendDeb) return E_POINTER;

	*ppSuspendDeb = NULL;

	if (m_pOperateScripts == NULL || m_pText == NULL) return E_POINTER;
	if (m_strMacroName.IsEmpty()) return E_FAIL;

CRunErr *pSuspendDeb = NULL;

	TRY {
		pSuspendDeb= new CRunErr (m_pOperateScripts, m_pText, m_strMacroName);

	} CATCH(CMemoryException, e) {
		AfxMessageBox(IDS_NOMEMORY);
		return E_OUTOFMEMORY;
	} END_CATCH;

	*ppSuspendDeb = pSuspendDeb;
	return NOERROR;
}

HRESULT CFilterScriptDlg::RunThread (long & rlRetObj, ebDWORD dwObj)
{
	ASSERT(NULL != m_pThread);
	ASSERT(NULL != m_pScript);
	if (m_pThread == NULL || m_pScript == NULL) return E_POINTER;

	ASSERT(NULL != m_pThread->GetHandle());
	ASSERT(NULL != m_pScript->GetHandle());
	if (m_pThread->GetHandle() == NULL || m_pScript->GetHandle() == NULL) return E_HANDLE;
	
	ASSERT(0L != dwObj);
	if (0L == dwObj) return E_INVALIDARG;

	// Parameterwert setzen
	if (!m_pThread -> SetParamObject (1, dwObj)) return E_FAIL;

HRESULT hr = NOERROR;
LONG lThreadState = 0;
	
	do {
		m_pThread -> SetLong (0, true);		// BreakFlag voreinstellen
		m_pThread -> Start();

		if (m_pThread -> GetErrorNumber()) 
			return E_UNEXPECTED;

		lThreadState = m_pThread -> GetState();
		if (lThreadState == TS_SUSPENDED && NULL != m_pSuspendDeb) {
		// Breakpoint in CallBackfunktion ausgelöst
		// Debugger wurde geschlossen	
			hr = m_pSuspendDeb -> OnDemandBreakpoint (m_pScript, m_pThread); //, &m_EI);
			if (FAILED(hr)) return hr;
			break;		// raus hier
		}
	} while (lThreadState != TS_IDLE);

// evtl. Parameter zurückschreiben
	m_pThread -> GetParamLong (0, &rlRetObj);

return hr;
}

// Aktionen am Anfang und am Ende, eigenständige Threads erzeugen
HRESULT CFilterScriptDlg::BeginAction(void)
{
	ASSERT(m_pScript);
	if (m_pScript == NULL) return E_POINTER;

	ASSERT(m_pScript ->GetHandle());
	if (m_pScript ->GetHandle() == NULL) return E_HANDLE;

	try {
	CebEntryInfo EI;
	HRESULT hr = SetEntryInfoAction (EI, true/* Function */, IDS_BEGINACTION, 0);

		if (FAILED(hr))	throw hr;

	// neuen Thread von fertigem Script (m_pScript) für BeginAction() bzw. EndAction() erzeugen
	CebThread Thread (m_pScript, EI.GetEntryInfo());

		if (Thread.Create(2*sizeof(long))) {
			AfxMessageBox (IDS_NOMEMORY);
			throw E_OUTOFMEMORY;
		}

	// EntryPoint überprüfen
		if (ebCheckEntry ((ebHOBJECT)Thread.GetHandle(), EI.GetEntryInfo())) {
			if (!FilterMessageBox(IDS_BADENTRY)) 
				throw E_FAIL;
			throw E_INVALIDARG;
		}

	// Vorbereitungen für OnDemandDebugging
		DELETE (m_pRunErr);
		THROW_FAILED_HRESULT(SetRuntimeErrorProc (&m_pRunErr));

	// fährt bei BreakPoint Debugger hoch			
		DELETE(m_pSuspendDeb);
		if (m_setBreakPoints.size() > 0) // new Debugger
			THROW_FAILED_HRESULT(OnDemandDebugger (&m_pSuspendDeb));

	// eigentliche Abarbeitung von "BeginAction"
		SetBreakPoints (&Thread);
		Thread.SetLong (0, true);		// BreakFlag voreinstellen

	LONG lThreadState = 0;
		
		do {
			Thread.Start();
			if (Thread.GetErrorNumber())
				throw E_UNEXPECTED;

			lThreadState = Thread.GetState();
			if (lThreadState == TS_SUSPENDED && NULL != m_pSuspendDeb) {
			// Breakpoint in CallBackfunktion ausgelöst
				THROW_FAILED_HRESULT(m_pSuspendDeb -> OnDemandBreakpoint (m_pScript, &Thread)); 
				break;		// raus hier
			}
		} while (TS_IDLE != lThreadState);
	} // try
	catch (HRESULT hr) {
		DELETE(m_pSuspendDeb);
		if (E_UNEXPECTED != hr) 
			DELETE (m_pRunErr);
		return hr;
	}

return NOERROR;
}

HRESULT CFilterScriptDlg::EndAction()
{
	ASSERT(m_pScript);
	if (NULL == m_pScript) return E_POINTER;
	ASSERT(m_pScript ->GetHandle());
	if (NULL == m_pScript ->GetHandle()) return E_HANDLE;

	try {
	CebEntryInfo EI;
	HRESULT hr = NOERROR;

		THROW_FAILED_HRESULT(SetEntryInfoAction(EI, false/* Sub */, IDS_ENDACTION, 0));

	// neuen Thread von fertigem Script (m_pScript) erzeugen
	CebThread Thread (m_pScript, EI.GetEntryInfo());

		if (Thread.Create(2*sizeof(long))) 
			throw E_FAIL;

	// EntryPoint überprüfen
		if (ebCheckEntry ((ebHOBJECT)Thread.GetHandle(), EI.GetEntryInfo())) {
			if (!FilterMessageBox(IDS_BADENTRY)) 
				throw E_FAIL;
			return E_INVALIDARG;
		}

// eigentliche Abarbeitung von "EndAction"
		SetBreakPoints (&Thread);
		Thread.SetLong (0, true);		// BreakFlag voreinstellen

	LONG lThreadState = 0;
		
		do {
			Thread.Start();
			if (Thread.GetErrorNumber())
				throw E_UNEXPECTED;

			lThreadState = Thread.GetState();

			if (lThreadState == TS_SUSPENDED && NULL != m_pSuspendDeb) {
			// Breakpoint in CallBackfunktion ausgelöst
				THROW_FAILED_HRESULT(m_pSuspendDeb -> OnDemandBreakpoint (m_pScript, &Thread));
				break;		// raus hier
			}
		} while (TS_IDLE != lThreadState);
	
	} catch (HRESULT hr) {
		DELETE (m_pSuspendDeb);
		if (E_UNEXPECTED != hr)
			DELETE (m_pRunErr);
		return hr;
	}

	DELETE(m_pSuspendDeb);
	DELETE(m_pRunErr);

return NOERROR;
}

HRESULT CFilterScriptDlg::SetEntryInfoAction (
	CebEntryInfo & EI, bool fMethodType, UINT uiID, int iParamCnt)
{
CString strEntry;

	if(!LoadString (strEntry, uiID)) return E_OUTOFMEMORY;
	
	if (fMethodType) 
		EI.SetRetType (&m_Types[0]);

	EI.SetEntryName (strEntry);	//strcpy			
	EI.SetParamsCount (iParamCnt);
	EI.SetMethodType (fMethodType);	// EndAction(): Sub, BeginAction(): Function
	return NOERROR;
}

HRESULT CFilterScriptDlg::SetBreakPoints (CebThread *pThread)
{
	ASSERT(pThread);
	if (NULL == pThread) return E_POINTER;
	ASSERT(pThread->GetHandle());
	if (NULL == pThread -> GetHandle()) return E_HANDLE;

BreakPointList::iterator it = m_setBreakPoints.begin();

	while (it != m_setBreakPoints.end()) {
		pThread -> SetBreakpoint(*it+1);
		it++;
	}

return NOERROR;
}

//
// *** Dialog-Daten übergeben, konvertieren ***
//
HRESULT CFilterScriptDlg::ConvertLongToObject (long lObjNr, _DGeoObject **ppIObj)
{
	ASSERT(NULL != m_pIDoc);
	if (m_pIDoc == NULL) return ResultFromScode(E_FAIL);
	ASSERT(lObjNr > 0);		// !! Objektnummer immer größer 0

VARIANT vObj;
VARIANT vMode;
HRESULT hr = NOERROR;
		
	V_VT(&vObj)  = VT_I4;
	V_I4(&vObj)  = lObjNr;
	V_VT(&vMode) = VT_I2;
	V_I2(&vMode) = GEOOBJECTMODE_Get;

// Übergebe Objektnummer, return IUnknown des Objekts als Variant
WDispatch Disp;

	hr = m_pIDoc -> GetObject(vObj, vMode, Disp.ppi());
	if (FAILED(hr)) return hr;

//	m_pIDoc -> Release(); im Destruktor
	return Disp -> QueryInterface(IID_DGeoObject, (LPVOID *) ppIObj);
}

HRESULT CFilterScriptDlg::GetDocument ()
{
HRESULT hr = NOERROR;
IGetTRiASApplication *pIGA = NULL;

// von OLE_Erweiterung IGetAppl. geben lassen
	hr = g_pTE -> m_pXtnSite -> GetXtension (CLSID_OleAutoExtension, 
									IID_IGetTRiASApplication, 
									(LPVOID *)&pIGA);
	if (FAILED(hr)) return hr;

_DApplication *pIA = NULL;
// Applikationsobjekt-Dispatchinterface an sich geben lassen

	hr = pIGA -> GetApplication(IID_DApplication, (LPVOID *)&pIA);
	pIGA -> Release();
	if (FAILED(hr)) return hr;

WDispatch Disp;

	hr = pIA -> get_ActiveDocument(Disp.ppi());
	pIA -> Release();
	if (FAILED(hr)) return hr;

	return Disp -> QueryInterface(IID_DDocument, (LPVOID *)&m_pIDoc);
}

// Liefert den jeweils nächsten EnumLONG mit Objekten, wenns der letzte war
// dann S_OK, wenn nicht dann S_FALSE, ansonsten einen FehlerCode
HRESULT CFilterScriptDlg::GetEnumLONG (IEnum<long> **ppEnum)
{
	if (NULL == ppEnum) {
		ASSERT(0); return E_POINTER;
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

// *** Initialisierungen ***
HRESULT CFilterScriptDlg::GetText()
{
	if (m_pText) {
		CoTaskMemFree(m_pText); 
		m_pText = NULL;
	}

// aktuellen Text besorgen
UINT iLen = m_Debug.GetTextLength() + 1;
	
	if (iLen == 1) return E_FAIL;

	m_pText = (LPSTR) CoTaskMemAlloc(iLen);
	if(NULL == m_pText) { 
		AfxMessageBox(IDS_NOMEMORY); 
		return E_OUTOFMEMORY;
	}

	iLen = m_Debug.GetText (m_pText, iLen);
	if (0 == iLen) {
		CoTaskMemFree(m_pText); 
		m_pText = NULL; 
		return E_FAIL;
	}

return NOERROR;
}

HRESULT CFilterScriptDlg::InitSheetButtons(bool fNextDisable)
{
CPropertySheet *pSh = (CPropertySheet *)GetParent();
	
	ASSERT(NULL != pSh);	
	if (pSh == NULL) return E_POINTER;

DWORD dwBttns = 0;

	if (!(m_dwSheetBttns & ADDPAGES_FIRSTPAGE) )
		dwBttns = PSWIZB_BACK;

CString str;

	m_cbxFilterScripts.GetWindowText(str);
	if (!str.IsEmpty() && !fNextDisable ) {
		if (m_dwSheetBttns & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;
		else 
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwSheetBttns & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSh -> SetWizardButtons(dwBttns);

return NOERROR;
}

HRESULT CFilterScriptDlg::SetRect()
{
HWND hDebuggerSizeWnd = ::GetDlgItem(m_hWnd, IDC_DEBUGGERSIZE);	

	ASSERT(NULL != hDebuggerSizeWnd);
	if (NULL == hDebuggerSizeWnd) return E_HANDLE;

RECT DebuggerSizeRect, DlgRect;

	if (!::GetWindowRect(m_hWnd, &DlgRect) || 
		!::GetWindowRect(hDebuggerSizeWnd, &DebuggerSizeRect)) 
	{
		ASSERT(0); 
		return E_FAIL;
	}

LONG lx = DebuggerSizeRect.left - DlgRect.left;
LONG ly = DebuggerSizeRect.top - DlgRect.top;
LONG lw = DebuggerSizeRect.right - DebuggerSizeRect.left;
LONG lh = DebuggerSizeRect.bottom - DebuggerSizeRect.top;

	m_Debug.SetRect((int)lx, (int)ly, (int)lw, (int)lh);
	return NOERROR;
}

HRESULT CFilterScriptDlg::CreateScript()
{
// dieser Dialog ist Parent für Debugger
	m_Debug.SetParent (m_hWnd);
	m_Debug.SetStyle (WS_CHILD|WS_VISIBLE|DS_NOWATCHWINDOW);
	m_Debug.SetId (CFilterScriptDlg::ID_DEBUG);

HRESULT hr = SetRect();
	
	if (FAILED(hr)) return hr;	

// Applicationinstance siehe Extensionfile, ebCreateDebugger(...,Appl.hInst)
// nicht verwechseln mit ebDebugger_SetInstance(BS-Inst)	
	m_Debug.SetInstance (g_hInstance);
	if (!m_Debug.Create()) {
		TRACE("Failed to create debugger control\n");
		return E_FAIL;      // fail to create
	}

// BasicScriptInstance setzen, ebDebugger_SetInstance()
	m_Debug.SetInstance(&m_rInst);
// ParentWindow für BS-Inst setzen
	m_rInst.SetWindow (m_hWnd);	
	
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

HRESULT CFilterScriptDlg::InitNewOperateScript()
{
// spezielle Initialisierung für ein DefaultScript
CString strDefaultScr; 

	if (!LoadString (strDefaultScr, IDS_FILTERDEFAULTSCRIPT)) 
		return E_FAIL;

	return InitOperateScript (strDefaultScr);
}

HRESULT CFilterScriptDlg::InitOperateScript (LPCSTR pc)
{
	ASSERT(NULL != pc);
	ASSERT(!m_strMacroName.IsEmpty());

	if (pc == NULL) return E_POINTER;
	if (m_strMacroName.IsEmpty()) return E_FAIL;

	m_fIsDirty = false;
	
	if (m_Debug.SetText(pc) == false)
		return E_FAIL; 

	m_Debug.SetCaretPos (4, 1);
	m_Debug.SetModified (false);

return NOERROR;
}

HRESULT CFilterScriptDlg::Fill()
{
	ASSERT(NULL != m_pOperateScripts);
	if (NULL == m_pOperateScripts) return E_POINTER;

	try {
	WScriptContainer ISC (m_pOperateScripts);	// throws hr
	WEnumScripts EnumScripts;
	
		THROW_FAILED_HRESULT(ISC -> GetEnumScripts (EnumScripts.ppi()));
		EnumScripts -> Reset();

	WUnknown Unk;
	char cName[MAXSTRLENGTH];
	
		while (S_OK == EnumScripts -> Next (1, Unk.ppi(), NULL)) 
		{
		WScript IScript (Unk);		// throws hr

			THROW_FAILED_HRESULT(IScript -> GetName (cName, MAXSTRLENGTH));
			m_cbxFilterScripts.AddString (cName);	// Combobox füllen
		}	

	} catch (HRESULT hr) {
		return hr;
	}

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// *** Save, Load ***
HRESULT CFilterScriptDlg::EntryName()
{
CString strName;	
CString str;

	m_cbxFilterScripts.GetWindowText(str);
	if (!LoadString(strName, IDS_OPERATE)) 
		return E_FAIL;

	if (str == strName) {
		m_fModified = false;
		if (!FilterMessageBox(IDS_SELECTSCRIPTNAME)) 
			return E_FAIL;

		m_cbxFilterScripts.SetEditSel (0, -1);
		m_cbxFilterScripts.SetFocus();
		return S_FALSE;
	}

return NOERROR;
}

int CFilterScriptDlg::AskSaveChanges (void)
{
CString strPrompt, strTemplate;

	TRY {
	char *pPrompt = strPrompt.GetBuffer (_MAX_PATH);

		if (m_strMacroName.IsEmpty() ||
			!LoadString (strTemplate, IDS_SAVEPROMPTSTORAGE)) 
		{
			return -1;		// Fehler
		}
		wsprintf (pPrompt, strTemplate, m_strMacroName);
		return AfxMessageBox (pPrompt, MB_YESNOCANCEL | MB_TASKMODAL);
	
	} CATCH(CMemoryException, e) {
		return -1;
	} END_CATCH;
}

HRESULT CFilterScriptDlg::AskSave()
{
HRESULT hr = NOERROR;

	if (m_fIsDirty || m_fModified) {
		switch (AskSaveChanges()) {
		case IDYES:
			return OnYes();

		case IDCANCEL:
			return S_FALSE;

		case IDNO:	
		// Neues Script, wenn nicht speichern, 
		// dann vom Enumerator löschen
			if (m_fInitNew)	{
				hr = Delete();
				if (FAILED(hr)) return hr;
		
				m_fIsDirty = false;
			}
			break;
		}

	} else if (m_fInitNew)
		return Delete();

return hr;
}

HRESULT CFilterScriptDlg::OnYes()
{
HRESULT hr = SaveScript();

	if (FAILED(hr)) return hr;

	if (m_fInitNew) {
		m_cbxFilterScripts.AddString (m_strMacroName);
		m_fInitNew = false;
	}
	return S_OK;
}

HRESULT CFilterScriptDlg::Delete ()
{
	ASSERT(!m_strMacroName.IsEmpty());
	ASSERT(NULL != m_pOperateScripts);

	if (NULL == m_pOperateScripts) return E_POINTER;

	try {
	WScriptContainer ISC (m_pOperateScripts);	// throw hr
	int iFind = m_cbxFilterScripts.FindStringExact (-1, m_strMacroName);
	
	// nur, wenn in Listbox
		if (iFind != CB_ERR)
			m_cbxFilterScripts.DeleteString(iFind);

		return ISC -> DelScript (m_strMacroName);
	} catch (HRESULT hr) {
		return hr;
	}
}

HRESULT CFilterScriptDlg::LoadScript()
{
	ASSERT(!m_strMacroName.IsEmpty());
	ASSERT(NULL != m_pOperateScripts);
	if (NULL == m_pOperateScripts) return E_POINTER;

	if (CB_ERR == m_cbxFilterScripts.FindStringExact (-1, m_strMacroName)) 
		m_cbxFilterScripts.InsertString(0,m_strMacroName);
	
char *pMakroText = NULL;

	try {
	// Text aus geöffnetem STREAM lesen oder neuen STREAM anlegen, 
	// *** m_hCode später SELBST freigeben !!! ***
	WScriptContainer IS (m_pOperateScripts);
	ebHCODE hCode = NULL;
	HRESULT hr = IS -> GetScript (m_strMacroName, &pMakroText, &hCode);

		if (FAILED(hr)) throw hr;
		if (hCode) CoTaskMemFree(hCode);	// Nur Text lesen

	// vorher noch kein Stream mit diesem Namen geladen 
		if (S_FALSE == GetScode(hr)) 
		// soll heißen: Neues Script, wenn nicht verändert, dann nicht speichern
			m_fInitNew = true;
		else {
			THROW_FAILED_HRESULT(InitOperateScript (pMakroText));

			m_fInitNew = false;
			m_fModified = false;
		}
	
	} catch (HRESULT hr) {
		if (pMakroText) {
			CoTaskMemFree (pMakroText);
			pMakroText = NULL;
		}
		return hr;
	} 

	if (pMakroText) {
		CoTaskMemFree (pMakroText);
		pMakroText = NULL;
	}

	return NOERROR;
}

HRESULT CFilterScriptDlg::LoadInitialScript()
{
	if (!LoadString(m_strMacroName, IDS_OPERATE)) return E_FAIL;
	
	m_bttnEntfernen.EnableWindow(false);
	m_cbxFilterScripts.SetWindowText(m_strMacroName);
	m_cbxFilterScripts.InsertString(0, m_strMacroName);

	ASSERT(NULL != m_pOperateScripts);
	if (NULL == m_pOperateScripts) return ResultFromScode(E_POINTER);

	try {
	WScriptContainer IS (m_pOperateScripts);

	// neuen STREAM anlegen
	char *pMakroText = NULL;
	ebHCODE hCode = NULL;
	HRESULT hr = IS -> GetScript (m_strMacroName, &pMakroText, &hCode);

		if (FAILED(hr)) return hr;

		if (hCode) CoTaskMemFree(hCode);
		if (pMakroText) CoTaskMemFree (pMakroText);
	
		THROW_FAILED_HRESULT(InitNewOperateScript());

		// soll heißen: Neues Script, wenn nicht verändert, dann nicht speichern
		m_fInitNew = true;
	
	} catch (HRESULT hr) {
		return hr;
	}

return NOERROR;
}

HRESULT CFilterScriptDlg::SaveScript()
{
// von SetFocus
	ASSERT(!m_strMacroName.IsEmpty());
	ASSERT(NULL != m_pOperateScripts);

	if (NULL == m_pOperateScripts) return ResultFromScode(E_POINTER);

LPSTR pText = NULL;

	try {
	// aktuellen Text besorgen
	WScriptContainer IS(m_pOperateScripts);		// throws hr
	UINT iLen = m_Debug.GetTextLength()+1;

		pText = (LPSTR) CoTaskMemAlloc(iLen);
		if (NULL == pText) throw E_OUTOFMEMORY;

		if (0 == m_Debug.GetText (pText, iLen))
			throw E_FAIL;
	
	// in  STREAM speichern	
		THROW_FAILED_HRESULT(IS -> SetScript (m_strMacroName, pText, NULL, CC_SCRIPT));
	
		m_fIsDirty = false; 
		m_Debug.SetModified (false);	
	
	} catch (HRESULT hr) {
		CoTaskMemFree(pText); 
		return hr;
	}

// Speichern beendet, aber noch COMMIT()
	DEX_SetDirtyGeoDB(true);
	CoTaskMemFree (pText); 

return NOERROR;
}

HRESULT CFilterScriptDlg::GetScriptInfo(const CString & str, DWORD & dwInfo)
{
	ASSERT(NULL != m_pOperateScripts);
	ASSERT(!str.IsEmpty());

	if (NULL == m_pOperateScripts) return E_POINTER;

	try {
	WScriptContainer ISC(m_pOperateScripts);	// throws hr

		return ISC -> GetScriptInfo(str, &dwInfo);
	} catch (HRESULT hr) {
		return hr;
	}
}

HRESULT CFilterScriptDlg::LoadStorage()
{
	ASSERT(NULL != m_pOperateScripts);
	if (NULL == m_pOperateScripts) return E_POINTER;

HRESULT hr = NOERROR;
LPSTORAGE pIRootStorage = NULL; 

	if(!DEX_GetProjectStorage(pIRootStorage)) 
		return E_FAIL;

bool fNew = false;
WStorage ISubStorage;
CString strStorName; 
	
	if(!LoadString(strStorName, IDS_STORAGE_NAME_OPERATESCRIPTS)) {
		pIRootStorage -> Release(); 
		return E_FAIL;
	}

	hr = MakeSubStorage(pIRootStorage, ISubStorage.ppi(), strStorName, fNew, true, CLSID_ScriptContainer);
	pIRootStorage -> Release();
	if(FAILED(hr)) return hr;

	try {
	WPersistStorage IPersistStorage(m_pOperateScripts);		// throws hr
	
		hr = IPersistStorage -> Load(ISubStorage);
		if (FAILED(hr)) throw hr;
		if (GetScode(hr) == S_FALSE) 
			hr = IPersistStorage -> InitNew(ISubStorage);
	
	} catch (HRESULT hr) {
		return hr;
	}

return hr;
}

long CFilterScriptDlg::Changed(void)
{
	m_fIsDirty = true;
	return 0;
}

// *** rechte Maustaste gedrückt ***
long CFilterScriptDlg::RightButtonUp(ebPARAM1 np1)
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
void CFilterScriptDlg::OnDebugCut() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.HasSelection()) {
		m_Debug.EditCut();
	}
}
void CFilterScriptDlg::OnDebugCopy() 
{
	if (m_Debug.HasSelection()) {
		m_Debug.EditCopy();
	}
}
void CFilterScriptDlg::OnDebugPaste() 
{
	if (m_Debug.GetState() != TS_RUNNING &&	::IsClipboardFormatAvailable (CF_TEXT)) {
		m_Debug.EditPaste();
	}
}
void CFilterScriptDlg::OnDebugDelete() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.HasSelection())	
		m_Debug.EditClear();	
}
void CFilterScriptDlg::OnDebugUndo() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.CanUndo())
		m_Debug.EditUndo();
}
void CFilterScriptDlg::OnDebugNewdialog() 
{                        
	if (m_Debug.GetState() != TS_RUNNING)	
		m_Debug.InsertDialog();
                              
}
void CFilterScriptDlg::OnDebugEditdialog() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.IsDialogSelected())	
		m_Debug.EditDialog();	
}

void CFilterScriptDlg::OnDebugBreakpoint() 
{
	m_Debug.ToggleBreakpoint(0);	// Breakpoints merken: aktuelle Zeile 

ebDWORD dw = m_Debug.GetCursorPos();
BreakPointList::iterator it = m_setBreakPoints.find(dw);

	if (it != m_setBreakPoints.end()) {
	// existiert bereits: Breakpoint abgeschaltet
		m_setBreakPoints.erase (it);
	} else {
		m_setBreakPoints.insert (ebHIWORD(dw));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Dummiefunktionen, machen gar nichts
void CFilterScriptDlg::OnDebugGo() 
{
}
void CFilterScriptDlg::OnDebugTraceOver() 
{
}
void CFilterScriptDlg::OnDebugTraceIn() 
{
}

// Menu-Init
void CFilterScriptDlg::OnInitMenu(CMenu* pMenu) 
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
	uiEnabled = m_fIsDirty ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_SAVE, uiEnabled);	

// Hilfe
char KeyWord[MAXSTRLENGTH];

	uiEnabled = (m_Debug.GetCaretWord(KeyWord, MAXSTRLENGTH)) ? MF_ENABLED : MF_GRAYED; 
	pMenu -> EnableMenuItem (ID_DEBUG_GETHELPON, uiEnabled);	
}

// *** ENDE MOUSE-Events: Menu-Commands ***

/////////////////////////////////////////////////////////////////////////////
// *** Hilfe ***
void CFilterScriptDlg::OnDebugGetHelpOn()
{
char KeyWord[MAXSTRLENGTH];

	if (m_Debug.GetCaretWord(KeyWord, MAXSTRLENGTH)) 
		KeywordHelp(KeyWord);
}

HRESULT CFilterScriptDlg::KeywordHelp(LPCSTR lpKeyWord)
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

HRESULT CFilterScriptDlg::LookupKeyword(LPCSTR lpKeyWord, int & id)
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

// globale Funktion
bool ReadSettingsFont(LPLOGFONT pLF);

void CFilterScriptDlg::SetFont()
{
	ASSERT(NULL == m_hFontOld);

LOGFONT LF;

	memset (&LF, 0, sizeof(LOGFONT));
	if (ReadSettingsFont (&LF) ) {
		m_hFontOld = m_Debug.GetFont(); 
		m_Debug.SetFont (::CreateFontIndirect (&LF));
	} else 
		m_hFontOld = NULL;		
}

void CFilterScriptDlg::ResetFont()
{
	if (m_hFontOld) 
		m_Debug.SetFont (m_hFontOld);		
	m_hFontOld = NULL;
}

//
// *** andere globale Funktionen ***
//
bool LoadString(CString & str, int IDS)
{
	TRY {                                       
		if (0 == str.LoadString (IDS)) 
			return false;	
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY); 
		return false;
	}                  
	END_CATCH

return true;
}


BOOL CFilterScriptDlg::OnKillActive() 
{
// Property für KeyboardRoutine wieder freigeben
CWnd *pWnd = GetDlgItem (CFilterScriptDlg::ID_DEBUG);

	ASSERT(NULL != pWnd);
	if (NULL != GetProp (pWnd -> GetSafeHwnd(), g_cbKeyboardFilterData))
		RemoveProp (pWnd -> GetSafeHwnd(), g_cbKeyboardFilterData);

	return CPropertyPage::OnKillActive();
}

///////////////////////////////////////////////////////////////////////////////
// Speichern übers Menu
void CFilterScriptDlg::OnDebugSave() 
{
	if (SUCCEEDED(EntryName()))
		OnYes();
}

///////////////////////////////////////////////////////////////////////////////
// Compilierten Script laden 
bool CFilterScriptDlg::LoadCode (int fh, ebFILEHEADER &rHead, CString &rstrFileName)
{
LPVOID lpCode = CoTaskMemAlloc(rHead.dwCodeSz);

	if(lpCode == NULL) { 
		AfxMessageBox(IDS_NOMEMORY); 
		return false; 
	}

CString strText;
char *pText = NULL;

	TRY {
		pText = strText.GetBuffer ((int)rHead.dwScriptSz);
   	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH
	
	_llseek (fh, rHead.dwCode, SEEK_SET);
	if (_hread (fh, lpCode, rHead.dwCodeSz) != (LONG)rHead.dwCodeSz) {
		CoTaskMemFree(lpCode); 
		return FileErrorMessage (IDS_CANTREADFILE, rstrFileName);
	}
	
	_llseek (fh, rHead.dwScript, SEEK_SET);
	if (_lread (fh, pText, (UINT)rHead.dwScriptSz) != (UINT)rHead.dwScriptSz) {
		CoTaskMemFree(lpCode); 
		return FileErrorMessage (IDS_CANTREADFILE, rstrFileName);
	}
	
	m_Debug.SetText (pText);
	m_Debug.SetCode (ebCode_Create (lpCode));
	
	rstrFileName = CorrectExtension (rstrFileName, IDS_SCRIPTEXT);

return true;
}                                                                               

// Script als Textdatei einlesen 
bool CFilterScriptDlg::LoadScriptFromFile (int fh, CString &rstrFileName)
{
LONG lBytes = _llseek (fh, 0L, SEEK_END);	// DateiGröße feststellen

	if (lBytes > MAXTEXT) {
		FileErrorMessage (IDS_FILETOLARGE, rstrFileName);
		lBytes = MAXTEXT;
	}

UINT iLen = (UINT)lBytes;
CString strText;
char *pText = NULL;

	TRY {
		pText = strText.GetBuffer (iLen);
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  false;
	}                  
	END_CATCH

	_llseek (fh, 0L, SEEK_SET);		// an  Anfang positionieren
	if (iLen != _lread (fh, pText, iLen)) return false;
	pText[iLen-1] = '\0';
		
	m_Debug.SetText (pText);
	m_Debug.SetCode (NULL);

return true;
}

// Script aus Datei laden 
bool CFilterScriptDlg::Open (CString &rstrFileName)
{
int fh = _lopen (rstrFileName, OF_READ);

	if (fh <= 0) return FileErrorMessage (IDS_CANTOPENFILE, rstrFileName);

ebFILEHEADER Head; 
int iBytes = _lread (fh, (LPSTR)&Head, sizeof(Head));
bool fResult = false;

	if (iBytes == sizeof(Head) && 
	    Head.id == FH_ID && Head.wVersion == FH_VERSION)
		fResult = LoadCode (fh, Head, rstrFileName);
	else
		fResult = LoadScriptFromFile (fh, rstrFileName);
		
	_lclose (fh);
	
// set current directory
	_chdir (GetPathName (rstrFileName));
	
return fResult;
}

// Import einer Datei
void CFilterScriptDlg::OnDebugImport() 
{
	if (S_OK == AskSave()) {
		TRY {
		CString strFilters; strFilters.LoadString (IDS_SAVEASFILTERS);
		CString strExt; strExt.LoadString (IDS_SCRIPTEXT);
		CFileDialog ODlg (true, strExt, NULL, 
				  OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, 
				  strFilters, this);
		
		char cbPath[_MAX_PATH]; 
		
			if (ReadRegSettingsLastOpenFile (cbPath, _MAX_PATH)) 
				_chdir (cbPath);

			if (IDOK == ODlg.DoModal()) {
			CString strFileName = ODlg.GetPathName();

				if (Open (strFileName)) {
					SaveRegSettingsLastOpenFile(GetPathName (strFileName));
		
					m_fIsDirty = true;
					m_Debug.SetModified (false);
					m_Debug.SetCaretPos (4, 1);
					::SetFocus(m_Debug.GetWindow());	
				}
			}
		} CATCH (CMemoryException, e) {
			;
		} END_CATCH;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Script als Datei exportieren

// Compilierten Script speichern ----------------------------------------------
bool CFilterScriptDlg::SaveCode (bool fCorrectExt, CString &rstrFileName)
{
// Script für alle Fälle noch mal kompilieren
	if (!m_Debug.Compile())	return false;

// Code vom Debugger geben lassen, dabei den Eigentümer nicht wechseln
// auf jeden Fall den Code verwenden, der keine BreakPoints enthält
ebHCODE hCode = m_Debug.GetCode (false);
	
	if(NULL == hCode) return false;

// DateiErweiterung richten
CString strScript = fCorrectExt ? CorrectExtension (rstrFileName, IDS_COMPLIEDSCRIPTEXT)
								: rstrFileName;
int fh = _lcreat (strScript, 0);

	if (fh <= 0) return FileErrorMessage (IDS_CANTCREATEFILE, strScript);

int iLen = m_Debug.GetTextLength() + 5;

	if (iLen == 5) return false;

CString strText;
char *pText = NULL;

	TRY {
		pText = strText.GetBuffer (iLen);
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH

	if (0 == m_Debug.GetText (pText, iLen)) 
		return false;

// Header initialisieren und wegschreiben
ebFILEHEADER Head;

	Head.wVersion = FH_VERSION;
	Head.id = FH_ID;
	Head.dwCodeSz = ebCode_GetSize(hCode);
	Head.dwScriptSz = iLen;
	
	_lwrite (fh, (LPCSTR)&Head, sizeof(Head));	// Header schreiben
	
	Head.dwCode = _llseek (fh, 0L, SEEK_CUR);	// Code schreiben
	_hwrite (fh, (LPCSTR)ebCode_GetPointer(hCode), Head.dwCodeSz);
	
	Head.dwScript = _llseek (fh, 0L, SEEK_CUR);	// Script schreiben
	_hwrite (fh, pText, Head.dwScriptSz);
	
	_llseek (fh, 0L, SEEK_SET);
	_lwrite (fh, (LPCSTR)&Head, sizeof(Head));	// Header nochmal schreiben
	
	_lclose (fh);

return true;		
}

// Script speichern (nur den eigentlichen Text) -------------------------------
bool CFilterScriptDlg::SaveScriptAsFile (CString &rstrFileName)
{
UINT iLen = m_Debug.GetTextLength() + 1; // zur Sicherheit

	if (iLen == 1) return false;

CString strText;
char *pText = NULL;

	TRY {
		pText = strText.GetBuffer (iLen);
		if (pText == NULL) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH

	if (iLen != m_Debug.GetText (pText, iLen)) 
		return false;		// aktuellen Text besorgen
	pText[iLen-1] = '\0';

// Datei erzeugen und ggf. Fehler auswerten
int fh = _lcreat (rstrFileName, 0);

	if (fh <= 0) return FileErrorMessage (IDS_CANTCREATEFILE, rstrFileName);

// Text wegschreiben, ggf. Fehler auswerten
	if (_lwrite (fh, pText, iLen) != iLen) {
		_lclose (fh);
		return FileErrorMessage (IDS_CANTWRITEFILE, rstrFileName);
	}
	_lclose (fh);

return true;
}

void CFilterScriptDlg::OnDebugExport (void) 
{
CString strFilters; 
CString strExt; 

	if (!::LoadString (strFilters, IDS_SAVEASFILTERS) || 
		!::LoadString (strExt, IDS_SCRIPTEXT)) 
	{
		return;
	}

CFileDialog SADlg (false, strExt, NULL, 
		   OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST, 
		   strFilters, this);
char cbPath[_MAX_PATH]; 
	
	if (ReadRegSettingsLastOpenFile(cbPath, _MAX_PATH)) 
		_chdir (cbPath);
	
	if (IDOK != SADlg.DoModal()) 
		return;

CString strFileName = SADlg.GetPathName();
bool fResult = false;

	SaveRegSettingsLastOpenFile(GetPathName (strFileName));
	if (2 == SADlg.m_ofn.nFilterIndex) 
		fResult = SaveCode (false, strFileName);	// kompletten Script speichern (compiled)
	else 
		fResult = SaveScriptAsFile(strFileName);	// lediglich Text speichern
	
	if (fResult) {
		::SetFocus(m_Debug.GetWindow());	
		_chdir (GetPathName (strFileName));	// set current directory
	}
}

bool CFilterScriptDlg::FilterMessageBox(int iIDS1)
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