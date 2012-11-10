#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten
#include "version.h"

#include <new>
#include <iobjman.h>

#include "macrguid.h"
#include "iscrprop.h"

#include "conststr.h"
#include "projscr.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "runerr.h"
#include "runebobs.h"
#include "toolbarx.h"
#include "splitter.h"
#include "split.h"

#include "BSParam.h"

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

BOOL g_fFireEventRun = false;

/////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern SummitModul g_SummitModuls[];

///////////////////////////////////////////////////////////////////////////////
// Routine, welche PreProzessorkonstanten (vor)definiert
ebINT ebCALLBACK PreDefinedConstants (long lParam, ebLPCSTR lpName, ebLPVOID lpDest)
{
char cbVersion[64];

	if (!stricmp (g_cbTRiASVer, lpName)) {			// 'TRiAS_VER'
		wsprintf (cbVersion, "%s%s", TRiAS_VERSION_STR, TRiAS_RELEASE_STR);
		strcpy ((char *)lpDest, cbVersion);
		return TYP_STRING;
	}

	if (!stricmp (g_cbTRiASBuild, lpName)) {		// 'TRiAS_BUILD'
		wsprintf (cbVersion, "%s", TRiAS_BUILD_STR);
		strcpy ((char *)lpDest, cbVersion);
		return TYP_STRING;
	}
	return TYP_EMPTY;	// not found
}

////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(ObjectManagement);
DefineSmartInterface(StreamInfo);
DefineSmartInterface(ScriptProperty);
DefineSmartInterface(ObjManHelper);
DefineSmartInterface(BSProperty);

////////////////////////////////////////////////////////////////////////////
// globale Funktionen
extern CRunningObjectsHelper * GetRunningObjectsHelper(void);
BOOL	RegAutoStartScriptFile();
CString GetDefaultName(int IDS);
CString GetFilterDefaultScript();
BOOL	LoadString(CString & str, int IDS);
void	MakePath(LPSTR Buf, LPSTR DirPath);
HRESULT RunThread(ebHTHREAD hThread, ebHSCRIPT hScript);
HRESULT	MessageNoCode(HWND h, ebHCODE hCode, LPCSTR);
BOOL	GetFile(LPCSTR lpcstr);
HRESULT SetHomeDir(CebInstance *pInst, LPCSTR lpcstr);
HRESULT SetAllParams (CebThread & rThread, BSPARAM *pBSParams, int iCountPar);
HRESULT GetReturnParams (CebThread & rThread, BSPARAM *pBSParams, LPVOID *lplpExtVariant, ebWORD wExtVariantType);
HRESULT GetAllParams (CebThread & rThread, BSPARAM *pBSParams, int iCountPar);
HRESULT ResetApplicationObjects (CebThread & rThread, BSPARAM *pBSParams, int iCountPar);
HRESULT	WriteIniAutoLoadScript (LPCSTR pcMacroName);
HRESULT ReadIniAutoLoadScript (char *pcMacroName, int iLen);
BOOL	SaveRegSettingsAutoLoadFile (LPCSTR pc);
BOOL	ReadRegSettingsAutoLoadFile (LPSTR pc, DWORD dwL);
BOOL	MessageNoEntry(HWND h, UINT uiEntry, LPCSTR lpcstrEntry);
void	ErrorMessage(HWND h, LPCSTR lpcstrMessage);

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Rückruffunktionen
extern "C" 
ebHSCRIPT ebCALLBACK _XTENSN_EXPORT RequestorProc (ebHTHREAD hThread, ebLPCTSTR pcMacroName, long lParam);
extern "C" 
void ebCALLBACK _XTENSN_EXPORT OnRuntimeError (	long lParam, ebLPCSTR lpMsg, ebDWORD dwErrNum, ebWORD wLinNr, ebWORD wCharPos, 
												ebLPCSTR lpSource, ebLPCSTR lpHelpFile, ebDWORD dwHelpContext);

extern "C" 
void ebCALLBACK _XTENSN_EXPORT OnFilterRuntimeError (	long lParam, ebLPCSTR lpMsg, ebDWORD dwErrNum, ebWORD wLinNr, ebWORD wCharPos, 
												ebLPCSTR lpSource, ebLPCSTR lpHelpFile, ebDWORD dwHelpContext);

//////////////////////////////////////////////////////////////////////////////////////////////
// CRunningFilterObject
STDMETHODIMP CRunningFilterObject::New (LPSTR *ppcMacroText)
{
	ASSERT (!m_strMacroName.IsEmpty());
				
	CString strDefaultScr (GetFilterDefaultScript());
	if (strDefaultScr.IsEmpty()) return E_FAIL;
		
	*ppcMacroText = NULL;
	*ppcMacroText = (LPSTR)CoTaskMemAlloc(strDefaultScr.GetLength()+1);
	if (NULL == *ppcMacroText) return E_OUTOFMEMORY;

	strcpy(*ppcMacroText, strDefaultScr);
	return NOERROR;
}
STDMETHODIMP CRunningFilterObject::Delete ()
{
	ASSERT (!m_strMacroName.IsEmpty());
	USES_CONVERSION;

WStreamInfo Info (GetStreamInfo());

	if (Info.IsValid())
		Info -> Set (A2OLE(m_strMacroName), 0);

WObjectManagement Manage(GetObjManagement());

	if (Manage.IsValid()) {
	HRESULT hr = Manage -> DelObject (A2OLE(m_strMacroName));

		if (false == GetInitNew()) // Speichern beendet, aber noch COMMIT()
			DEX_SetDirtyGeoDB (TRUE);
		return hr;
	}
	return S_FALSE;
}

STDMETHODIMP CRunningFilterObject::Save(LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)
{// Erst öffnen des schon Gespeicherten, um RELATED zu bekommen
	ASSERT(0 == uiCnt);
	ASSERT(NULL == lplpstr);
	ASSERT(0 != dwSaveFlag);
	if (0 != uiCnt || NULL != lplpstr) return E_UNEXPECTED;
	if (0 == dwSaveFlag) return E_INVALIDARG;

	HRESULT hr = NOERROR;
	ebHCODE hSaveCode = NULL;
	LPSTR lpstr = NULL;
	LPSTR *lplpstrRel = NULL;
	UINT ui = 0;// Bei FunctionLevel alten Text vom Script belassen
	try
	{	// Wenn neues, dann können keine Related im Filter vorhanden sein
		if (false == GetInitNew()) 
			hr = Open(&lpstr, &hSaveCode, &lplpstrRel, ui);	// StringListe aus Related geben lassen
		if (FAILED(hr)) _com_issue_error(hr);
		// Save der Basisklasse nutzen, aber neuen Text speichern
		hr = CRunningObject::Save(pText, hCode, lplpstrRel, ui, dwSaveFlag);
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}	
	COTASKMEMFREE(lpstr);
	COTASKMEMFREE(hSaveCode);
	MEMFREE(lplpstrRel, ui);
	return hr;
}
void CRunningFilterObject::SetRuntimeErrorProc(CebThread & Thread)
{
	Thread.SetRuntimeErrorProc(&OnFilterRuntimeError, 0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// CRunningObject
/////////////////////////////////////////////////////////////////////////////////////////////////////
CRunningObject::CRunningObject()
	: m_EnumRunningThreads()
{
	m_pScript = NULL;
	m_pSuspendDeb = NULL;
	m_hEnum = NULL;
	m_dwAuto = 0;
	m_fExtension = 0;
	m_fInterrupt = false;
}
CRunningObject::~CRunningObject()
{
	DELETE_OBJ(m_pSuspendDeb);
	// gibt es noch noch laufende Threads, UNTERBRECHEN !!!
	EndThreads();
	SetScript(NULL);
	if (m_hEnum) ebEnumClose(m_hEnum); m_hEnum = NULL;
}

// Löschen des Objektes
STDMETHODIMP CRunningObject::Delete ()
{
HRESULT hr = S_OK;

	USES_CONVERSION;
	if (GetInitNew()) {
	WObjectManagement Manage (GetObjManagement());

		if (Manage.IsValid())
			hr = GetObjManagement() -> DelObject (A2OLE(m_strMacroName));
	}
	((ITreeItem *)this) -> Release();		// nur Release()
	return hr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// *** IRunningObject methods
STDMETHODIMP_(void) CRunningObject::SetManagement	(IObjectManagement* pIO, IStreamInfo* pIS, REFIID riid, LPCSTR lpcstrMacroName) 
{
	Init(pIO, pIS, riid);
	if (NULL != lpcstrMacroName)
		SetScriptName (lpcstrMacroName);	// Namen setzen
}

STDMETHODIMP CRunningObject::SetAutoStart(DWORD dw) 
{
	char str[_MAX_PATH];
	ReadIniAutoLoadScript (str, _MAX_PATH);
	// RAUS				steht auch in der Reg
	if (0 == dw && 0 == stricmp(str, m_strMacroName) && FAILED(WriteIniAutoLoadScript (g_cbNil)))
		return E_FAIL;
	// REIN		steht nicht in der Reg
	else if (0 < dw && 0 != stricmp(str, m_strMacroName) && FAILED(WriteIniAutoLoadScript (m_strMacroName)))
		return E_FAIL;

	m_dwAuto = dw; 
	return  S_OK;
}

STDMETHODIMP CRunningObject::LinkScript	()
{
	ASSERT(m_pScript);
	ASSERT(m_pScript -> GetHandle());
	if (NULL == m_pScript) return E_UNEXPECTED;
	if (NULL == m_pScript -> GetHandle()) return E_HANDLE;

	try
	{
	ebPROCINFO PI;
	
		memset(&PI, 0, sizeof(ebPROCINFO));

	// Findet ALLE schon erzeugten zur Instance gehörigen Scripts
	// nie Makroprojekt bezogen, ruft NICHT RequestorProc 
	ebINT iRet = ebLink(m_pScript -> GetHandle(), &PI);
		
		if (ebERR_TYPEMISMATCH == iRet || ebERR_ENTRYNOTFOUND == iRet) {		
		CString strLink, strApplication, strFunction, strErrorType; 
		char Error[MAXSTRLENGTH];

			LoadString(strLink, IDS_LINKERROR); 
			LoadString(strApplication, IDS_LONGCLASSNAME); 

			if (ebERR_TYPEMISMATCH == iRet) 
				LoadString(strErrorType, IDS_TYPEMISMATCH);
			else
				LoadString(strErrorType, IDS_NOENTRY);

			wsprintf(Error, strLink, m_strMacroName,
						PI.wType ? GetDefaultName(IDS_FUNCTIONSTRING) : GetDefaultName(IDS_SUBSTRING),
						PI.szName);
			::MessageBox(GetActiveWindow(), Error, strApplication, MB_OK|MB_ICONSTOP);
			_com_issue_error(E_FAIL);
		}
	}
	catch(_com_error& e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CRunningObject::CreateScript(CebInstance *pInst, ebHCODE hCode)
{
	ASSERT(pInst);
	ASSERT(hCode);
	if (NULL == pInst) return E_POINTER;
	if (NULL == hCode) return E_HANDLE;

CebScript *pSc = NULL;

	try {	// Script erzeugen
	char Buffer[MAXSTRLENGTH];
	
		pSc = new CebScript(pInst, hCode, Buffer, MAXSTRLENGTH);
		if (pSc -> Create()) _com_issue_error(E_FAIL);
	
	// eventuell Runtime Errorbehandlung (wenn Text vorhanden)
		pSc -> SetErrorBuffer(NULL, 0);		
		THROW_FAILED_HRESULT(SetScript(pSc)); // delete m_pScript , m_pScript = pSc
	
	// Debugger kreieren
		THROW_FAILED_HRESULT(OnDemandDebugger (m_strMacroName, &m_pSuspendDeb));

	} COM_CATCH_OP(
		DELETE_OBJ(m_pScript);
		DELETE_OBJ(m_pSuspendDeb);
	);
	return S_OK;
}

STDMETHODIMP CRunningObject::RunEntry (
	LPCSTR pEntry, int iNumParams, BSPARAM *pPars, BOOL fPreBreak, 
	INT_PTR hPrCtx, INT_PTR hInst)
{
	ASSERT(NULL != pEntry);
	ASSERT(NULL != m_pScript);
	if (NULL == m_pScript || NULL == pEntry) return E_POINTER;

HRESULT hr = NOERROR;

	if (HACTCONNECTION == reinterpret_cast<HPROJECT>(hPrCtx))
		hPrCtx = reinterpret_cast<INT_PTR>(DEX_GetDataSourceHandle());

// Datenquelle muß gegeben sein, wenn Projekt geöffnet ist
	ASSERT(!DEX_GetOpenedEx(HACTPROJECT) || HACTCONNECTION != reinterpret_cast<HPROJECT>(hPrCtx));

// wenn ResourceHandle nicht gegeben ist, dann lokales verwenden
	if (NULL == hInst)
		hInst = reinterpret_cast<INT_PTR>(_Module.GetResourceInstance());

	try {
	// EntryInfo setzen
	CebEntryInfo EI;
	CBSParamCopy BSParam (iNumParams, pPars);

		BSParam.RemoveModsParam();
		memset(&EI, 0, sizeof(CebEntryInfo));

		hr = SetEntryInfo(EI, pEntry, iNumParams, BSParam);		
		if (FAILED(hr)) _com_issue_error(hr);

	// EntryPoint überprüfen, wenn fehlerhaft, nicht weiterlaufen, nächsten Script zum gleichen Entry suchen
	UINT ui = ebCheckEntry (m_pScript -> GetHandle(), EI.GetEntryInfo());

		if (MessageNoEntry(GetActiveWindow(), ui, pEntry)) _com_issue_error(BS_E_NOENTRY); 

	// Thread erzeugen
	CebThread Thread (m_pScript -> GetHandle(), EI.GetEntryInfo());		

	// Try-Block nötig, damit Applikationsobjkte immer NULL gesetzt werden, 
	// sonst wäre ausserhalb des ersten try/catch das CebThread-Objekt nicht mehr gültig
		try {
			if (Thread.Create (CREATETHREAD_EXTRA)) 
				_com_issue_error(E_OUTOFMEMORY);

		// Break, Auto, Namen, HPROJECT etc. voreinstellen
			Thread.SetLong(SETLONG_BREAK, fPreBreak);
			Thread.SetLong(SETLONG_AUTO, m_dwAuto);	
			Thread.SetLong(SETLONG_NAME, 0);	
			Thread.SetLong(SETLONG_HPROJECT, hPrCtx);	
			Thread.SetLong(SETLONG_HINSTANCE, hInst);	

			if (!m_strMacroName.IsEmpty())
				Thread.SetLong(SETLONG_NAME, (long)(LPSTR)(LPCSTR)m_strMacroName);

		// Extensionscript voreinstellen
			Thread.SetLong(SETLONG_EXT, 0);	
			if (RESIDENT & m_dwAuto)
				Thread.SetLong(SETLONG_EXT, 1);	

		// Parameter setzen
			hr = SetAllParams (Thread, pPars, iNumParams);
			if (FAILED(hr)) _com_issue_error(hr);
		
		// eventuell Runtime Errorbehandlung
			// Wenn Project geschlossen, nicht RunTimeerror rufen
			SetRuntimeErrorProc(Thread);
			if (GetRunningObjectsHelper() -> GetOpenProject()) {
				hr = g_pBSE -> CreateRunTimeErrorDebugger(m_strMacroName);
				if (FAILED(hr)) _com_issue_error(hr);
			} 
		
		// laufenden Thread setzen
			hr = SetThread(&Thread);
			if (FAILED(hr)) _com_issue_error(hr);

		//////////////////////////////////////////////
		// eigentliches RUN
		// Routine rufen, bis die CallbackFunktion erfolgreich abgeschlossen wurde
		// wenn fehlerhaft, ABBRUCH, RAUS, Script löschen
			hr = RunThread(Thread, pEntry);			

		// Immer erst Running-Thread löschen !!!
			HRESULT hr1 = DeleteThread(&Thread);
			if (FAILED(hr1)) _com_issue_error(hr1);
			if (FAILED(hr)) _com_issue_error(hr);

		// aus der Liste Laufeneder RAUS
		// Rückgabewert holen		
			hr = GetReturnParams (Thread, pPars, NULL, 0);
			if (FAILED(hr)) _com_issue_error(hr);
		
		// evtl. Parameter zurückschreiben
			hr = GetAllParams (Thread, pPars, iNumParams);
			if (FAILED(hr)) _com_issue_error(hr);
		
		// BOOLsche Variable im Extrabuffer zum Zerstören des Scripts
		// Scriptausfürung abbrechen, S_OK == RAUS aus Liste
			if (Thread.GetLong(SETLONG_BREAK)) 
				hr = S_OK;
			else
				hr = S_FALSE;
		} 
		catch (_com_error& e) 
		{// Auch bei Laufzeitfehler und vorzeitigem Schliessen des Debuggers
			DELETE_OBJ(m_pSuspendDeb);
			hr = _COM_ERROR(e);
		}

	// Applikationsobjekte 0 setzen, um AppObj -> Release() von BS zu verhindern
		ResetApplicationObjects (Thread, pPars, iNumParams);			
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}

STDMETHODIMP CRunningObject::SetThread	(CebThread *pThread)
{
	ASSERT(pThread);
	if (NULL == pThread) return E_POINTER;
	LONG lThread = (LONG)pThread;
	HRESULT hr = m_EnumRunningThreads.AddItem(lThread);
	m_EnumRunningThreads.Reset();
	return hr;
}

STDMETHODIMP CRunningObject::GetThread	(CebThread **ppThread)
{
	ASSERT(ppThread);
	if (NULL == ppThread) return E_POINTER;
	*ppThread = NULL;

HRESULT hr = S_FALSE;
LONG lThread = 0;

	if ((hr = m_EnumRunningThreads.Next(1, &lThread, 0)) == S_OK) {
		if (lThread) 
		{
			*ppThread = (CebThread*)lThread; 
			return S_OK;
		}
		hr = E_FAIL;
	}
	m_EnumRunningThreads.Reset();
	return hr;
}

STDMETHODIMP CRunningObject::SetScript(CebScript *pScript)
{
	// kann auch NULL sein
	DELETE_OBJ(m_pScript);
	m_pScript = pScript;
	return S_OK;
}

STDMETHODIMP CRunningObject::GetScript(CebScript **ppScript)
{
	ASSERT(ppScript);
	if (NULL == ppScript || NULL == m_pScript) return E_POINTER;
	*ppScript = m_pScript;
	return S_OK;
}

STDMETHODIMP CRunningObject::EndThreads	()
{
	HRESULT hr = IsThreadRunning();
	if (S_OK == hr) {
		hr = EndThreadRunning();
		if (FAILED(hr)) return hr;
	}
	return S_OK;
}

STDMETHODIMP CRunningObject::EnumEntries(LPSTR lpstr, UINT uiLen, ebBOOL *pfNext)
{
	ASSERT(lpstr);
	ASSERT(m_pScript);
	if (NULL == m_pScript) return E_UNEXPECTED; 
	if (NULL == lpstr) return  E_POINTER;
	if (0 == uiLen) return E_INVALIDARG;

	try
	{
	ebPROCINFO PI;

		memset(&PI, 0, sizeof(ebPROCINFO));

	///////////////////////////////////////////////////
	// alle Entries enumerieren und in Map füllen
		if (false == *pfNext)// Am Anfang immer false !!!
		{	// das erste Mal Enum holen
			if (m_hEnum) ebEnumClose(m_hEnum); m_hEnum = NULL;
			
			m_hEnum = ebGetFirstProc(m_pScript -> GetHandle(), &PI);
			if (NULL == m_hEnum) _com_issue_error(E_HANDLE);
		
		// WEITER im Text
			*pfNext = true;
		}
		else if (NULL != m_hEnum)
			*pfNext = ebGetNextProc(m_hEnum, &PI);
		
		if (*pfNext) 
		{// einen gefunden, Ergebnis kopieren				
			if (strlen(PI.szName) > uiLen) 
				_com_issue_error(E_FAIL); 
			strcpy(lpstr, PI.szName);
		}	
		else// Letzter
			_com_issue_error(S_FALSE);
	}		
	catch (_com_error &e)
	{
		if (m_hEnum) ebEnumClose(m_hEnum); m_hEnum = NULL;
		return _COM_ERROR(e);
	}		

	return S_OK;
}		

STDMETHODIMP CRunningObject::RunScript()
{
	HRESULT hr = NOERROR;
	try
	{	// Initialisierung LoadScript
		HRESULT hrBreakLoad = Load();		// Script abbrechen liefert S_OK
		// kein Entry, trotzdem am Ende abbrechen mit Unload()
		if (BS_E_NOENTRY == hrBreakLoad) hrBreakLoad = S_OK;
		if (FAILED(hrBreakLoad)) _com_issue_error(hrBreakLoad);	
		// Hauptentry Main
		HRESULT hrBreakMain = Main();
		if (FAILED(hrBreakMain))	_com_issue_error(hrBreakMain); 		// S_OK == RAUS
		// Zerstören des Scripts ?
		if (S_OK == hrBreakMain && S_OK == hrBreakLoad)
		{// Endscript rufen, BScript-Resourcen freigeben
			hr = UnLoad();
			if (FAILED(hr) && BS_E_NOENTRY != hr) _com_issue_error(hr);
			hr = E_ABORT;
		}
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}	
	return hr;
}
HRESULT CRunningObject::OnDemandDebugger (LPCSTR lpcstr, CRunBreakPoint **ppSuspendDeb)
{// Run bestimmten Entry von fertigem Code
	ASSERT(ppSuspendDeb);
	if (NULL == ppSuspendDeb) return E_POINTER;

	*ppSuspendDeb = NULL;
	try {
		THROW_INVALIDSTRING(lpcstr, S_FALSE);
		CRunBreakPoint *pSuspendDeb = NULL;
		pSuspendDeb = new CRunBreakPoint (lpcstr);
		*ppSuspendDeb = pSuspendDeb;
	} catch (bad_alloc) {
		return E_OUTOFMEMORY;
	} catch (_com_error& e) {
		return _COM_ERROR(e);
	}

	return NOERROR;
}

HRESULT CRunningObject::RunThread(CebThread & Thread, LPCSTR lpcstrEntry)
{
CHandleMacroTrayIcons TrayIcons;		// evtl. TrayIcons anzeigen

HRESULT hr = S_OK;
LONG lThreadState = TS_IDLE;

	do {

		Thread.Start();
		lThreadState = Thread.GetState();
		if (lThreadState == TS_SUSPENDED) {
		// Bei Interrupt
			if (m_fInterrupt) {
				hr = E_ABORT;
				Thread.Interrupt(0, 0);		// Interrupt in Idle-Sate
				m_fInterrupt = false;
				MessageInterrupt (lpcstrEntry);			
			}
			else {
			// Breakpoint in CallBackfunktion ausgelöst
				hr = m_pSuspendDeb -> OnDemandBreakpoint (m_pScript, &Thread, GetObjManagement(), GetStreamInfo()); 

			// RAUS !!!, Ansonsten wird immer gleicher Thread angeworfen, 
			// ist immer SUSPENDED ausserhalb des Debuggers 
			}
			break; 
		}
	} while (lThreadState != TS_IDLE) ;

// Fehler aufgetreten
	if (Thread.GetErrorNumber()) 
		hr = BS_E_RUNTIMEERROR;
	return hr;
}

// Delete
// Nur Object instanzieren
HRESULT CRunningObject::GetScript(LPCSTR lpcstrScriptName, REFIID riid, BOOL fCreateTemp)
{	
	USES_CONVERSION;

// Objekt geben lesen
WUnknown IU;
WObjectManagement Manage (GetObjManagement());
HRESULT hr = S_FALSE;

	if (Manage.IsValid()) {
		hr = Manage -> GetObject(A2OLE(lpcstrScriptName), IU.ppi());
		if (FAILED(hr)) {
		// kein Objekt mit diesem Namen, GetObject FAILED, CoCreateInstance(...
			hr = Manage -> CreateObject(riid, A2OLE(lpcstrScriptName), STGM_READWRITE, IU.ppi(), fCreateTemp);
			if (SUCCEEDED(hr)) hr = S_FALSE;
		}
	}
	return hr;
}

// HILFE Öffnen
HRESULT CRunningObject::GetProperty (LPCSTR lpcstr, LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplpstr, UINT & uiCnt)
{
	ASSERT(NULL != ppcMacroText);
	ASSERT(NULL != phCode);
	ASSERT(NULL != lplplpstr);
	
HRESULT hr = S_OK;
ebSaveStruct SS;

	memset(&SS, 0, sizeof(ebSaveStruct));

	USES_CONVERSION;
	try {
		*phCode = NULL;
		*ppcMacroText = NULL;
		*lplplpstr = NULL;
		uiCnt = 0;

	// Objekt geben lesen
	WUnknown IU;
	WObjectManagement Manage (GetObjManagement());

		if (Manage.IsValid()) {
			THROW_FAILED_HRESULT(Manage -> GetObject(A2OLE(lpcstr), IU.ppi()));	

		// Kopieren der Daten
		WScriptProperty ISP(IU);

			THROW_FAILED_HRESULT(ISP -> Get(&SS));  
			if (SS.hCode) *phCode = SS.hCode;
			if (SS.pText) *ppcMacroText = SS.pText;
			if (SS.uiCntRelScripts) {
				uiCnt = SS.uiCntRelScripts;
				*lplplpstr = SS.lplpstrRelScripts;
			}
		} else
			hr = E_UNEXPECTED;
	}
	catch (_com_error &e) {
	// FEHLER
		if (SS.hCode) { CoTaskMemFree(SS.hCode); SS.hCode = NULL; }
		if (SS.pText) { CoTaskMemFree(SS.pText); SS.pText = NULL; }
		MEMFREE(SS.lplpstrRelScripts, SS.uiCntRelScripts);
		hr = _COM_ERROR(e);
	}
	return hr;
}
void CRunningObject::SetRuntimeErrorProc(CebThread & Thread)
{
	Thread.SetRuntimeErrorProc(&OnRuntimeError, 0);
}

// Sind noch Threads RUNNING ?
HRESULT CRunningObject::IsThreadRunning()
{
int iThreadCnt = 0;
CebThread *pThread = NULL;

	while (S_OK == GetThread(&pThread)) {
	// laufenden gefunden 
		ASSERT(pThread);
		iThreadCnt++;
	}

// Kein Thread Running
	if (0 == iThreadCnt) 
		return S_FALSE;

// Threads noch RUNNING !!!
	return OutputRunningThreads (iThreadCnt);
}

HRESULT CRunningObject::EndThreadRunning()
{
CebThread *pThread = NULL;

	while (S_OK == GetThread (&pThread)) 
	{
		ASSERT(pThread && pThread -> GetHandle());
		if (NULL == pThread) return E_POINTER;
		if (NULL == pThread -> GetHandle()) return E_HANDLE;

	// Abbruch, 0 heisst: dann Suspended-State	
	// kommt aus Running-Funktion wieder raus und wird zerstört
	int nErrorCode = 0;

		m_fInterrupt = true;
		ATLTRY(pThread -> Interrupt (0, 0));
	}
	return S_OK;
}

HRESULT CRunningObject::OutputRunningThreads (short iCnt)
{
	TRACE1("BSCRIPT: Es laufen noch %ld threads\r\n", iCnt);
//	TRY {
//		char c[MAXSTRLENGTH];
//		CString str = itoa(iCnt, c, 10);
//		CString strCap; strCap.LoadString (IDS_LONGCLASSNAME);
//		CString strOut;
//
//		strOut.Format (IDS_RUNNINGTHREADS, (LPCSTR)str); 
//		MessageBox (::GetActiveWindow(), strOut, strCap, MB_OK | MB_ICONINFORMATION);
//
//	} CATCH (CMemoryException, e) {
//		return E_OUTOFMEMORY;
//	} 
//	END_CATCH;
	return S_OK;
}

HRESULT CRunningObjectsHelper::MessageNoCode(LPCSTR lpcstrText, ebHCODE *phCode, LPCSTR lpcstr)
{
	if (*phCode) return S_OK;

	HRESULT hr = NOERROR; 
	ebCOMPILESTRUCT CompileStruct;
	memset (&CompileStruct, 0, sizeof(CompileStruct));

	try
	{
		if (NULL == *phCode && NULL == lpcstrText) _com_issue_error(E_FAIL);
		hr = Compile(CompileStruct, lpcstrText);
		if (FAILED(hr)) _com_issue_error(hr);
		*phCode = CompileStruct.hCode;
	}
	catch(_com_error& e)
	{	// Fehler erst hier ausgeben
		CString str;
		::LoadString (str, IDS_COMPERSAVEDSCRIPT);
		char Buffer[_MAX_PATH];
		wsprintf (Buffer, str, lpcstr); 
		ErrorMessage(GetActiveWindow(), Buffer);
		hr = _COM_ERROR(e);
	}
	return hr;
}

HRESULT CRunningObject::MessageInterrupt (LPCSTR lpcstrEntry)
{
	TRY {
		CString strCap; ::LoadString (strCap, IDS_LONGCLASSNAME);
		CString strInterrupt, strOut;
		
		strOut.Format (IDS_INTERRUPT, lpcstrEntry, m_strMacroName); 
		MessageBox (::GetActiveWindow(), strOut, strCap, MB_OK | MB_ICONINFORMATION);
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} 
	END_CATCH;
	
	return S_OK;
}

// allgemeie EntrieInfo setzen
HRESULT CRunningObject::SetEntryInfo (CebEntryInfo & EI, LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
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
		else
		{
			EI.SetMethodType (false);	// Sub
		}
	}

	return NOERROR;
}

HRESULT CRunningObject::UnLoad()
{
CString strEntryName;

	if (!::LoadString(strEntryName, IDS_UNLOADSCRIPT)) 
		return E_OUTOFMEMORY;

// eigentliche Ausführung: UnLoadScript
HRESULT hr = RunEntry (strEntryName, 0, NULL, true, NULL, NULL);	// Abbruch voreinstellen

	if (SUCCEEDED(hr)) 
		hr = EndThreads();
	return hr;
}

HRESULT CRunningObject::Main()
{
CString strEntryName;

	if (!::LoadString(strEntryName, IDS_MAIN)) 
		return E_OUTOFMEMORY;

// eigentliche Ausführung: Main
	return RunEntry (strEntryName, 0, NULL, true, NULL, NULL);	// Abbruch voreinstellen
}

HRESULT CRunningObject::Load()
{
CString strEntryName;
	
	if (!::LoadString(strEntryName, IDS_LOADSCRIPT)) 
		return E_OUTOFMEMORY;

// eigentliche Ausführung
	return RunEntry (strEntryName, 0, NULL, true, NULL, NULL);	// Abbruch voreinstellen
}

HRESULT CRunningObject::DeleteThread(CebThread *pCompareThread)
{
	ASSERT(pCompareThread);
	if (NULL == pCompareThread) return E_POINTER;

	CebThread *pThread;
	HRESULT hr = E_FAIL;
	// Bis Ende alle Running-Threads enum.
	// Passenden währenddessen rausfiltern
	while (S_OK == GetThread(&pThread))
	{
		ASSERT(pThread);
		if (pThread == pCompareThread)
		{
			LONG lThread = (LONG)pCompareThread;
			m_EnumRunningThreads.ClearItem(lThread);
			hr = S_OK;
			break;
		}
	}
	m_EnumRunningThreads.Reset();
	return hr;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// CRunningObjectFile
/////////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CRunningObjectFile::SetAutoStart(DWORD dw) 
{ 
	m_dwAuto = dw; 
	return S_OK; 
}

STDMETHODIMP CRunningObjectFile::Delete ()
{
	USES_CONVERSION;

CComBSTR bstrName (m_strMacroName);
WObjectManagement Manage (GetObjManagement());
HRESULT hr = S_FALSE;

	if (Manage.IsValid()) 
		hr = Manage -> DelObject (bstrName);
	
	((IRunningObject *)this) -> Release();
	return hr;
}

void CRunningObjectFile::SetRuntimeErrorProc(CebThread & Thread)
{
	Thread.SetRuntimeErrorProc(&OnRuntimeError, 1);// File wird geöffnet
}

//////////////////////////////////////////////////////////////////////////////////////////
// RunningObjects Container

CRunningObjectsHelper::CRunningObjectsHelper(CebInstance *pInst)
{
	ASSERT(pInst);
	m_pISI = NULL;
	m_pOM = NULL;
	m_pRelScripts = NULL;
	m_pRunningScripts = NULL;
	m_pInst = pInst;
	m_fFireEventIsRun = false;
}

CRunningObjectsHelper* CRunningObjectsHelper::CreateRunningObjectsHelper(CebInstance *pInst)
{
	CRunningObjectsHelper* pRunningObjHelper = NULL;
	try {
		pRunningObjHelper = new CRunningObjectsHelper(pInst);
		if (pRunningObjHelper) 
			pRunningObjHelper -> FInit();

	} catch (bad_alloc)	{
		pRunningObjHelper -> ResetContainer();
		if (pRunningObjHelper) delete pRunningObjHelper;
		pRunningObjHelper = NULL; 
		return NULL;
	}
	return pRunningObjHelper;
}

CRunningObjectsHelper::~CRunningObjectsHelper()
{
	ResetManagement();
	ResetContainer();
	m_fFireEventIsRun = false;
}

BOOL CRunningObjectsHelper::FInit()
{
	try {
		m_pRelScripts = new CRelScripts();
		m_pRunningScripts = new CRunScripts();
	} catch (bad_alloc) {
		return false;
	}
	return true;
}

void CRunningObjectsHelper::ResetContainer()
{
// Hier die Container an sich freigeben
	DELETE_OBJ(m_pRelScripts);
	DELETE_OBJ(m_pRunningScripts);
}

void CRunningObjectsHelper::ResetManagement()
{
// Alle Magagements der RunningObjects zurücksetzen
	if (m_pRelScripts) 
		m_pRelScripts -> ResetStorageManagement(); 
	if (m_pRunningScripts) 
		m_pRunningScripts -> ReleaseAllManagements();
	if (m_pOM)
		m_pOM -> Release();
	m_pOM = NULL;
	if (m_pISI)
		m_pISI -> Release();
	m_pISI = NULL;
}

HRESULT CRunningObjectsHelper::InitLinkAndStorage (IObjectManagement *pIOM, IStreamInfo *pISI)
{
	if (NULL == m_pRelScripts || (NULL == pIOM && NULL == pISI)) 
		return E_POINTER;
	
	if (pIOM) {
		if (m_pOM) m_pOM -> Release();
		m_pOM = pIOM;
		m_pOM -> AddRef();
	}
	if (pISI)	{
		if (m_pISI) m_pISI -> Release();
		m_pISI = pISI;
		m_pISI -> AddRef();
	}

	m_pRelScripts -> SetStorageManagement(m_pOM, m_pISI); 
	return S_OK;
}

CRunScripts * CRunningObjectsHelper::GetRunningScripts()
{
	ASSERT(this);
	if (NULL == this) return NULL;
	return m_pRunningScripts;
}

CRelScripts * CRunningObjectsHelper::GetRelScripts ()
{
	ASSERT(this);
	if (NULL == this) return NULL;
	return m_pRelScripts;
}

BOOL CRunningObjectsHelper::GetOpenProject() 
{ 
char strProject[_MAX_PATH];

	if (NULL == DEX_GetActiveProject(strProject))
		return false;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
// RunningScripts Wrapper-Funktionen
HRESULT CRunningObjectsHelper::CanAddString	(LPCSTR lpcstrMacroName)
{ 
WRunningObject IRO; 
HRESULT hr = Find(lpcstrMacroName, IRO.ppi()); 

	if (S_OK != hr) return hr;
	return IRO -> CanAddString();
}

HRESULT CRunningObjectsHelper::FindNext(LPSTR lpstrScriptName, short iLen, IRunningObject **ppIRO)
{
	ASSERT(this);
	if (NULL == this) return E_FAIL;
	return GetRunningScripts() -> NextScriptName(lpstrScriptName, iLen, ppIRO);
}

HRESULT CRunningObjectsHelper::Find(LPCSTR lpcstr, IRunningObject **ppIRO)
{
	ASSERT(this);
	if (NULL == this) return E_FAIL;
	return GetRunningScripts() -> Find(lpcstr, ppIRO);
}

HRESULT CRunningObjectsHelper::Delete(LPCSTR lpcstr)
{
	ASSERT(this);
	if (NULL == this) return E_FAIL;
	return GetRunningScripts() -> Delete(lpcstr);
}

HRESULT CRunningObjectsHelper::Add(IRunningObject *pIRO, LPCSTR lpcstr)
{
	ASSERT(this);
	if (NULL == this) return E_FAIL;
	return GetRunningScripts() -> Add (pIRO, lpcstr);
}

HRESULT CRunningObjectsHelper::SetAutoStart	(LPCSTR lpcstrMacroName, DWORD dw)
{
WRunningObject IRO;
HRESULT hr = Find(lpcstrMacroName, IRO.ppi());

	if (FAILED(hr)) return hr;
	return  IRO -> SetAutoStart(dw);
}

HRESULT CRunningObjectsHelper::GetAutoStart	(LPCSTR lpcstrMacroName, DWORD *pdw)
{
	WRunningObject IRO;
	HRESULT hr = Find(lpcstrMacroName, IRO.ppi());
	if (FAILED(hr)) return hr;
	return  IRO -> GetAutoStart(pdw);
}

HRESULT CRunningObjectsHelper::RunEntry(
	LPCSTR lpcstrMacroName, LPCSTR pEntry, int iNumParams, BSPARAM *pPars, 
	BOOL fPreBreak, INT_PTR hPrCtx, INT_PTR hInst)
{
	RETURN_FAILED_HRESULT(SwitchRelated());

// Ist Script zu finden 
WRunningObject IRO;
HRESULT hr = Find (lpcstrMacroName, IRO.ppi());

	if (FAILED(hr)) return hr;

// eigentliche Ausführung
	return IRO -> RunEntry (pEntry, iNumParams, pPars, fPreBreak, hPrCtx, hInst);	// Abbruch voreinstellen
}

HRESULT CRunningObjectsHelper::UnLoad(LPCSTR lpcstrMacroName)
{
	ASSERT(lpcstrMacroName);
	if (NULL == lpcstrMacroName) return E_POINTER;

HRESULT hr1 = NOERROR;

	try {
	CString strEntryName;

		if (!::LoadString(strEntryName, IDS_UNLOADSCRIPT)) 
			_com_issue_error(E_OUTOFMEMORY);

		hr1 = RunEntry (lpcstrMacroName, strEntryName, 0, NULL, true);	// Abbruch voreinstellen
	
	// Alle Threads, die noch laufen abwürgen, immer löschen bei UnLoad()
		try {
		HRESULT hr = GetRunningScripts() -> Delete (lpcstrMacroName);
		
			if (FAILED(hr)) _com_issue_error(hr); 
		} 
		catch (_com_error& e) {
		HRESULT hr = GetRelScripts() -> Delete(lpcstrMacroName);
		
			if (FAILED(hr)) return hr;
			return _COM_ERROR(e);
		}

	// Related löschen				
	HRESULT hr = GetRelScripts() -> Delete(lpcstrMacroName);
	
		if (FAILED(hr)) _com_issue_error(hr); 
	} 
	catch (_com_error& e) {
		return _COM_ERROR(e);
	}
	return hr1;
}

HRESULT CRunningObjectsHelper::RunEntry (
	LPCSTR pEntry, LPCSTR lpcstrText, ebHCODE hCode, int iNumParams, BSPARAM *pPars,
	BOOL fPreBreak, LPCSTR pcMacroName, INT_PTR hPrCtx, INT_PTR hInst)
{
	ASSERT(NULL != pEntry);
	if (NULL == this || NULL == pEntry) return E_FAIL;
	if (NULL == pEntry) return E_POINTER;

// Ist Script zu finden 
HRESULT hr = S_OK;
WRunningObject IRO;

	if (NULL == pcMacroName || FAILED(Find (pcMacroName, IRO.ppi()))) {
	// neuen Script anlegen und ausführen
	ebCOMPILESTRUCT CompileStruct;

		memset (&CompileStruct, 0, sizeof(CompileStruct));
		if (NULL == hCode && NULL != lpcstrText) {
			THROW_FAILED_HRESULT(Compile (CompileStruct, lpcstrText));
			hCode = CompileStruct.hCode;
		}	
		ASSERT(NULL != hCode);

		try {
		// Neues Scriptobjekt erzeugen
		CComObject<CRunningObject> *pIRO = NULL;

			THROW_FAILED_HRESULT(CComObject<CRunningObject>::CreateInstance(&pIRO));
			IRO = pIRO;		// pendig AddRef

		// CebScript erzeugen, Debugger erzeugen, IRunningObject merken
			THROW_FAILED_HRESULT(IRO -> CreateScript(m_pInst, hCode));
			if(NULL != pcMacroName)	{
			// ScriptNamen in Liste der RunningScripts speichern
				THROW_FAILED_HRESULT(m_pRunningScripts -> Add (IRO, pcMacroName));
				THROW_FAILED_HRESULT(WBSProperty(IRO) -> SetScriptName (pcMacroName));
			}
			THROW_FAILED_HRESULT(hr = IRO -> RunEntry (pEntry, iNumParams, pPars, fPreBreak, hPrCtx, hInst));
		}
		catch (_com_error &e)
		{
			hr = _COM_ERROR(e);
		}

		if (NULL != CompileStruct.hCode) {
			ebCode_Free (CompileStruct.hCode); 
			CompileStruct.hCode = NULL;
		}

	} else {
		ASSERT(NULL == hCode);		// Code ist hier überflüssig, da Script bereits existiert
		ASSERT(IRO.IsValid());		// Script sollte existieren

		hr = IRO -> RunEntry (pEntry, iNumParams, pPars, fPreBreak, hPrCtx, hInst);
	}
	return hr;
}

// Scriptabarbeitung anhalten
HRESULT CRunningObjectsHelper::StopScript(LPCSTR lpcstrMacroName)
{
	return UnLoad(lpcstrMacroName);		
}

// Scriptabarbeitung aller Scripts anhalten
HRESULT CRunningObjectsHelper::StopAllScripts()
{
HRESULT hres = NOERROR;
char ScriptName[_MAX_PATH];
WRunningObject IRO;

	GetRunningScripts() -> Reset();
	while (S_OK == FindNext(ScriptName, _MAX_PATH, IRO.ppi())) {
	HRESULT hr = UnLoad(ScriptName);

		if (FAILED(hr)) 
			hres = hr;	// damit alle durchlaufen werden und trotzdem Fehler angezeigt wird
	}
	return hres;
}

HRESULT CRunningObjectsHelper::CreateObject (REFCLSID rClsid, IRunningObject **ppIR)
{
// ScriptObjekt erzeugen
	ASSERT(NULL != ppIR);
	if (NULL == ppIR) return E_POINTER; 

	*ppIR = NULL;
	try	{
	// mmmh: sehr merkwürdig
		if (IsEqualIID(rClsid, CLSID_Script))
		{
			*ppIR = new CComObject<CRunningObject>;
		}
		else if (IsEqualIID(rClsid, CLSID_FileScript))
		{
			*ppIR = new CComObject<CRunningObjectFile>;
		}
		else
			_com_issue_error(E_UNEXPECTED);

		if (*ppIR) (*ppIR) -> AddRef();
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}
	catch (bad_alloc)
	{
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

// ScriptLinking 
HRESULT CRunningObjectsHelper::LinkScript(
	LPCSTR lpcstrMacroName, ebHCODE hNewCode, IObjectManagement *pIOM)
{
	ASSERT(this);
	if (NULL == this) return E_FAIL;
	if (!g_SummitModuls[RUNTIME].fIsInstalled) return E_FAIL;

	ASSERT(pIOM);
	ASSERT(m_pInst);
	ASSERT(lpcstrMacroName);
	if (NULL == lpcstrMacroName || NULL ==  pIOM || NULL == m_pInst) return E_POINTER;
	if (NULL == m_pInst -> GetHandle()) return E_UNEXPECTED;

	HRESULT	hr = S_OK;
	ebHCODE hSavedCode = NULL;
	ebHCODE hCompileCode = NULL;
	LPSTR	pText = NULL;
	IRunningObject *pIRO = NULL;
	UINT uiCntRelScripts = 0;
	LPSTR *lplpstrRelScripts = NULL;

	// fCreateTemp für File 
	try {	
		// ScriptObjekt erzeugen
		THROW_FAILED_HRESULT(CreateObject(CLSID_Script, &pIRO));
		// Management setzen
		pIRO -> SetManagement(pIOM, NULL, CLSID_Script, lpcstrMacroName);
		// Wenn Code explizit übergeben wird, diesen nehmen
		if (NULL == hNewCode)
		{	// Code , Text kann nch SetManagement geladen werden, Objekt öffnen
			WObjManHelper IOMH = pIRO;
			THROW_FAILED_HRESULT(IOMH -> Open(&pText, &hSavedCode, &lplpstrRelScripts, uiCntRelScripts, false));
			// kein Code !!!, eventuell raus hier		
			if (NULL == hSavedCode)
			{	// Kein Code abgespeichert ?, Kompilieren, wenn nicht kompiliert RAUS
				THROW_FAILED_HRESULT(MessageNoCode(pText, &hCompileCode, lpcstrMacroName));
			}
		}
		// ebScript kreieren
		if (hNewCode)
			hr = pIRO -> CreateScript(m_pInst, hNewCode);
		else if (hSavedCode)
			hr = pIRO -> CreateScript(m_pInst, hSavedCode);
		else if (hCompileCode)			
			hr = pIRO -> CreateScript(m_pInst, hCompileCode);
		THROW_FAILED_HRESULT(hr);
		// Related umschalten
		THROW_FAILED_HRESULT(SwitchRelated());
		// Related-Scripts dieses Scriptes erzeugen und füllen
		THROW_FAILED_HRESULT(AddRelated(lpcstrMacroName));
		// Script Linken
		THROW_FAILED_HRESULT(pIRO -> LinkScript());
	}
	catch (_com_error & e) 
	{
		hr = _COM_ERROR(e);
	}
	
	try { 
		WObjManHelper IOMH = pIRO;
		IOMH -> Delete(); 	
	} catch(_com_error&) {
	}
	pIRO = NULL;
	if (pText)			COTASKMEMFREE(pText); 
	if (hSavedCode)			COTASKMEMFREE(hSavedCode); 
	if (hCompileCode)	ebCode_Free(hCompileCode); hCompileCode = NULL;
	MEMFREE(lplpstrRelScripts, uiCntRelScripts);
	GetRelScripts() -> Delete(lpcstrMacroName);		// Related löschen				
	// nicht expliziten Code hNewCode löschen 
	return hr;
}

//
// *** Scriptabarbeitung ***
//
HRESULT CRunningObjectsHelper::RunScript(
	LPCSTR lpcstrMacroName, int fAutoStart, REFIID riid, BOOL fCreateTemp)
{
	ASSERT(this);
	if (NULL == this) return E_FAIL;
	if (!g_SummitModuls[RUNTIME].fIsInstalled) return E_FAIL;

	ASSERT(m_pOM);
	ASSERT(m_pInst);
	ASSERT(lpcstrMacroName);
	
	if (NULL == lpcstrMacroName || NULL == m_pOM || NULL == m_pInst) return E_POINTER;
	// ebInstance-Handle in CebInstance noch nicht erzeugt
	if (NULL == m_pInst -> GetHandle()) return E_UNEXPECTED;
	// Script läuft schon
	if (S_OK == IsRunning(lpcstrMacroName)) return E_UNEXPECTED;

	HRESULT	hr = S_OK;
	ebHCODE hCode = NULL;
	ebHCODE hCompileCode = NULL;
	LPSTR	pText = NULL;
	IRunningObject *pIRO = NULL;
	UINT uiCntRelScripts = 0;
	LPSTR *lplpstrRelScripts = NULL;

	// fCreateTemp für File 
	try 
	{	// ScriptObjekt erzeugen
		hr = CreateObject(riid, &pIRO);
		if (FAILED(hr)) _com_issue_error(hr);
		// Query
		WObjManHelper IOMH = pIRO;
		// Management setzen
		pIRO -> SetManagement(m_pOM, m_pISI, riid, lpcstrMacroName);
		// Code , Text kann nch SetManagement geladen werden, Objekt öffnen
		hr = IOMH -> Open(&pText, &hCode, &lplpstrRelScripts, uiCntRelScripts, fCreateTemp);
		if (FAILED(hr)) _com_issue_error(hr);
		// kein Code !!!, eventuell raus hier		
		if (NULL == hCode)
		{	// Kein Code abgespeichert ?
			hr = MessageNoCode(pText, &hCompileCode, lpcstrMacroName);
			if (FAILED(hr)) _com_issue_error(hr);// erstmal nach gültigen Code fragrn
		}
		// ebScript kreieren
		hr = pIRO -> CreateScript(m_pInst, hCode ? hCode : hCompileCode);
		if (FAILED(hr)) _com_issue_error(hr);
		// Autostart setzen
		pIRO -> SetAutoStart(fAutoStart);
		// RunningObjekt aufheben
		hr = Add (pIRO, lpcstrMacroName);
		// nur einmal gleichen Script mit gleichem Namen merken !!!
		if (FAILED(hr) || S_FALSE == hr) _com_issue_error(hr); 
		// Home setzen
		hr = SetHomeDir(lpcstrMacroName);
		if (FAILED(hr)) _com_issue_error(hr);
		// Related umschalten
		hr = SwitchRelated();
		if (FAILED(hr)) _com_issue_error(hr); 		
		// Related-Scripts dieses Scriptes erzeugen und füllen
		hr = AddRelated(lpcstrMacroName);
		if (FAILED(hr)) _com_issue_error(hr); 				
		////////////////////////////////////////////////////////////////////
		// Script linken
		hr = pIRO -> LinkScript	();
		if (FAILED(hr)) _com_issue_error(hr);
		////////////////////////////////////////////////////////////////////
		// Script ausführen, LoadScript, Main, bei UnLoad E_ABORT
		hr = pIRO -> RunScript();
		// kein Break gesetzt, aber von aussen erzwungen
		if (E_ABORT == hr && (fAutoStart & RESIDENT))	
			hr = S_OK;
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch (_com_error & e) 
	{
		GetRunningScripts() -> Delete (lpcstrMacroName);// Alle Threads, die noch laufen abwürgen
		GetRelScripts() -> Delete(lpcstrMacroName);		// Related löschen				
		hr = _COM_ERROR(e);
	}
	// Bei File wird auch das Objekt gelöschr, ansonsten nur Release()
	// Sollte Runtimeerror auftreten, Datei nicht gleich löschen, 
	// übernimmt der Debugger
	if (pIRO && BS_E_RUNTIMEERROR == hr) {
		pIRO -> Release(); 
	} 
	else if (pIRO) 
	{
		try {
			WObjManHelper IOMH = pIRO;
			IOMH -> Delete(); 
		} catch(_com_error&) {
			pIRO -> Release();
		}
	}
	pIRO = NULL;

	if (pText)			CoTaskMemFree	(pText); pText = NULL; 
	if (hCode)			CoTaskMemFree	(hCode); hCode = NULL;
	if (hCompileCode)	ebCode_Free(hCompileCode); hCompileCode = NULL;
	MEMFREE(lplpstrRelScripts, uiCntRelScripts);
	if (E_ABORT == hr || BS_E_RUNTIMEERROR == hr) hr = S_FALSE;// E_ABORT bei UnLoad()
	return hr;
}

HRESULT CRunningObjectsHelper::RunKeptEntry(LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	if (m_fFireEventIsRun) 
		return S_FALSE;
	m_fFireEventIsRun = true;

	ASSERT(pEntry);
	if (NULL == this) return E_FAIL;

	try {
	// All Scripts zu bestimmten Entries enum.	
	WRunningObject IRO;
	list<WRunningObject> listRunning;

		GetRunningScripts() -> Reset();
		while (S_OK == GetRunningScripts() -> NextFromEntry (pEntry, IRO.ppi())) 
			listRunning.push_back (IRO);

	// jetzt alle gefundene abarbeiten
		for (list<WRunningObject>::iterator it = listRunning.begin(); it != listRunning.end(); it++) {
		// Umschalten der Related
		HRESULT hr = SwitchRelated();

			if (FAILED(hr)) _com_issue_error(hr);// false heißt: Erst anhalten, wenn im Script selbst SetBreakScript(true) gesetzt wird
			
			hr = (*it) -> RunEntry (pEntry, iNumParams, pPars, false, NULL, NULL);
			if (S_OK == hr) {
			// Script entladen, Delete(Related), Delete (hScript-Runnings), Run Unloadscript
			WBSProperty IBSP(*it);
			char str[_MAX_PATH];

				IBSP -> GetScriptName(str, _MAX_PATH); 
				hr = UnLoad(str);
				if (FAILED(hr)) _com_issue_error(hr); 
			}
		}	
		m_fFireEventIsRun = false;
	}
	catch (_com_error &e)
	{
		m_fFireEventIsRun = false;
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CRunningObjectsHelper::EntryExists (LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	_ASSERTE(NULL != pEntry);
	COM_TRY {
	// All Scripts zu bestimmten Entry finden
	WRunningObject IRO;

		GetRunningScripts() -> Reset();
		if (S_OK == GetRunningScripts() -> NextFromEntry (pEntry, IRO.ppi())) 
			return S_OK;	// mindestens einer existiert

	} COM_CATCH;
	return S_FALSE;		// nichts gefunden
}

HRESULT CRunningObjectsHelper::SwitchRelated()
{
	ASSERT(m_pInst);
	if (NULL == m_pInst) return E_UNEXPECTED;
	if (NULL == m_pInst -> GetHandle()) return E_HANDLE;
	// Diese Related-Scripts für RequestorProc setzen
	m_pInst -> SetRequestorProc(RequestorProc, (LPARAM)GetRelScripts());
	m_pInst -> SetLinkOptions(LO_CALLREQUESTORBEFORE);

	return S_OK;
}

HRESULT CRunningObjectsHelper::AddRelated(LPCSTR lpcstrScriptName)
{
	ASSERT(lpcstrScriptName);
	if (NULL == lpcstrScriptName) return E_POINTER;
	// Muss Running sein
	//HRESULT hr = IsRunning(lpcstrScriptName);
	//if (FAILED(hr)) return hr;
	// Liste aus Scriptnamen und RunningScriptsOrg erstellen
	return m_pRelScripts -> Add(lpcstrScriptName);
}

HRESULT CRunningObjectsHelper::DeleteRelated(LPCSTR lpcstrScriptName)
{
	ASSERT(lpcstrScriptName);
	if (NULL == lpcstrScriptName) return E_POINTER;
	// aus Liste aus Scriptnamen und RunningScriptsOrg entfernen
	return m_pRelScripts -> Delete(lpcstrScriptName);
}

HRESULT CRunningObjectsHelper::SetHomeDir(LPCSTR lpcstrName)
{
	ASSERT(this);
	if (this == NULL) return E_FAIL;

	ASSERT(m_pInst);

	return ::SetHomeDir(m_pInst, lpcstrName);
}

HRESULT CRunningObjectsHelper::Compile(ebCOMPILESTRUCT & CompileStruct, LPCSTR lpText)
{
	ASSERT(this);
	if (NULL == this) return E_FAIL;
	ASSERT(lpText);
	if (NULL == lpText) return E_POINTER;

	CebCompiler Compiler;
	memset(&CompileStruct, 0, sizeof(ebLPCOMPILESTRUCT)); 
	
	CompileStruct.wVersion = CS_VERSION;						/* version of this structure (CS_VERSION) */
	CompileStruct.lpText = lpText;	 							/* Script to be compiled */
	CompileStruct.hInstance = m_pInst -> GetHandle();			/* instance of the application (returned fro ebInit) */

	CompileStruct.wFlags |= CF_USECONSTPROC;
	CompileStruct.lpfnConst = PreDefinedConstants;
	CompileStruct.ConstData = 0L;

HRESULT hr = NOERROR;

	if (Compiler.Compile(&CompileStruct)) return E_FAIL;
	if (NULL == CompileStruct.hCode) return E_HANDLE;

	return NOERROR;
}

// Rufen einer Basic-Routine von außen ----------------------------------------
BOOL SetParam (CebThread &rThread, int iIndex, ebPARAM &rParam, LPVOID pParam)
{
	switch (rParam.wType & TYP_TYPEMASK) {
	case TYP_EMPTY:
	case TYP_NULL:		break;
	case TYP_BOOLEAN:	return rThread.SetParamBool (iIndex, *(ebBOOL *)pParam);
	case TYP_INTEGER:	return rThread.SetParamInt (iIndex, *(short *)pParam);
	case TYP_LONG:		return rThread.SetParamLong (iIndex, *(long *)pParam);
	case TYP_SINGLE:	return rThread.SetParamSingle (iIndex, *(float *)pParam);
	case TYP_DOUBLE:   	return rThread.SetParamDouble (iIndex, *(double *)pParam);
	case TYP_CURRENCY: 	return rThread.SetParamCurrency (iIndex, *(ebCURRENCY *)pParam);
	case TYP_DATE:     	return rThread.SetParamDate (iIndex, *(double *)pParam);
	case TYP_STRING:
		{
			if (rParam.wType & TYP_MODSPARM)
	   			return rThread.SetParamString (iIndex, ::ebCreateString (rThread.GetHandle(), *(LPCSTR *)pParam));
			else
	   			return rThread.SetParamString (iIndex, ::ebCreateString (rThread.GetHandle(), (LPCSTR)pParam));
		}
	case TYP_OLEOBJECT:	return rThread.SetParamOleObject (iIndex, *(ebDWORD *)pParam);
	case TYP_ERROR:  	break;
	case TYP_VARIANT:	return rThread.SetParamVariant (iIndex, *(ebVARIANT *)pParam);
	case TYP_APPOBJECT:	return rThread.SetParamObject (iIndex, *(ebDWORD *)pParam);
	case TYP_DIALOG: 	break;
	case TYP_USERDEF:	break;
	}
	
return false;
}


BOOL GetParam (CebThread &rThread, int iIndex, ebPARAM &rParam, LPVOID pParam, BOOL fModsPar, BOOL fAddRef)
{
	switch (rParam.wType & TYP_TYPEMASK) {
	case TYP_EMPTY:
	case TYP_NULL:		break;
	case TYP_BOOLEAN:	return rThread.GetParamBool (iIndex, (ebBOOL *)pParam);
	case TYP_INTEGER:	return rThread.GetParamInt (iIndex, (WORD *)pParam);
	case TYP_LONG:		return rThread.GetParamLong (iIndex, (long *)pParam);
	case TYP_SINGLE:	return rThread.GetParamSingle (iIndex, (float *)pParam);
	case TYP_DOUBLE:   	return rThread.GetParamDouble (iIndex, (double *)pParam);
	case TYP_CURRENCY: 	return rThread.GetParamCurrency (iIndex, (ebCURRENCY *)pParam);
	case TYP_DATE:     	return rThread.GetParamDate (iIndex, (double *)pParam);
	case TYP_STRING:
		{
		ebHSUB hStr = NULL;
			
			if ((rParam.wType & TYP_MODSPARM) || fModsPar) {
				if (rThread.GetParamString (iIndex, &hStr)) {
				LPSTR pStr = ::ebLockString (rThread.GetHandle(), hStr);

					if (*(LPSTR *)pParam) CoTaskMemFree (*(LPSTR *)pParam);
						*(LPSTR *)pParam = (LPSTR)CoTaskMemAlloc (strlen(pStr)+1);
					if (NULL != *(LPSTR *)pParam)	// Ergebnis kopieren
						strcpy (*(LPSTR *)pParam, pStr);

					::ebUnlockString (rThread.GetHandle(), hStr);
					return true;
				}
			} else {
				if (rThread.GetParamString (iIndex, &hStr)) {
					::ebFreeString (rThread.GetHandle(), hStr);
					return true;
				}
			}
		}
		break;
	case TYP_OLEOBJECT:	return rThread.GetParamOleObject (iIndex, (ebDWORD *)pParam);
	case TYP_ERROR:  	break;
	case TYP_VARIANT:	return rThread.GetParamVariant (iIndex, (ebVARIANT *)pParam);
	case TYP_APPOBJECT:	
		{
		WUnknown Unk;

			if (rThread.GetParamObject (iIndex, (ULONG *)Unk.ppv())) {
				if (fAddRef && Unk.IsValid())
					Unk -> AddRef();
				*(ebDWORD *)pParam = reinterpret_cast<ebDWORD>(Unk.detach());
				return true;
			}
			break;
		}
	case TYP_DIALOG: 	break;
	case TYP_USERDEF:	break;
	}
	
return false;
}

HRESULT GetValueVariant (CebThread &rThread, ebVARIANT var, LPVOID *lplpVoid, ebWORD wType)
{
	ebLPSTR lpstr = NULL;
	ebVARIANT vString;
	
	if (lplpVoid == NULL) return E_POINTER;
	*lplpVoid = NULL;

	// Richtigen Wert aus Variant holen
	if (TYP_EMPTY == var.Type || TYP_NULL == var.Type)
		return S_FALSE;		// kein Wert enthalten (#HK)
	if (0 != ebVariantConvert (rThread.GetHandle(), &var, &vString, wType))
		return E_FAIL;		// nicht konvertierbar (#HK)
	
	if (TYP_STRING == wType)
	{// Wert ist String
		lpstr = ebLockString(rThread.GetHandle(), vString.u.h);

		if (NULL != lpstr)
		{
			ULONG ul = strlen(lpstr);
			*(LPSTR *)lplpVoid = (LPSTR)CoTaskMemAlloc (ul+1);
			if (NULL != *(LPSTR *)lplpVoid)	// Ergebnis kopieren
				strcpy (*(LPSTR *)lplpVoid , lpstr);
		}
		ebUnlockString(rThread.GetHandle(), vString.u.h);
	}
	// else if (TYP_... == wType)
	// {...

	ebFreeVariant(rThread.GetHandle(), &vString);

	return S_OK;
}

HRESULT CreateDebugger(CWnd *pWnd, LPCSTR lpcstr, BOOL fOpenFile, UINT uiWMClose, IObjectManagement *pIOM, IStreamInfo *pISI, CSplit **ppDebugger)
{// Debugger-DLL nicht installiert	
	if (!g_SummitModuls[DEBUGGER].fIsInstalled) return E_UNEXPECTED;

	ASSERT(pWnd);
	ASSERT(ppDebugger);

	// Alten Debugger freigeben
	if (NULL != *ppDebugger && IsWindow((*ppDebugger) -> GetSafeHwnd()))
		(*ppDebugger) -> DestroyWindow();
	*ppDebugger = NULL;

	CSplit *pSplit = NULL;
	try 
	{	
		CString str = GetDefaultName(IDS_LONGCLASSNAME);
		CRect rect;
		memset(&rect, 0, sizeof(CRect));
		// MainFrame erzeugen
		pSplit = new CSplit();
		if (!pSplit -> Create(NULL, str, WS_POPUP|WS_OVERLAPPEDWINDOW, rect, pWnd, MAKEINTRESOURCE(IDR_PROJECTMENU)))
			_com_issue_error(E_FAIL);
		// Initialisieren
		if (!pSplit ->  Init(lpcstr, fOpenFile, uiWMClose, pIOM, pISI))
			_com_issue_error(E_FAIL);
	} 
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	} 
	catch (_com_error& e) 
	{
		if (NULL != pSplit) pSplit -> DestroyWindow()/*delete*/; pSplit = NULL;
		return _COM_ERROR(e);
	}
	// Erfolg
	*ppDebugger = pSplit;
	return S_OK; 
}

// Globale Funktion, wird überall gebraucht
HRESULT RunThread (ebHTHREAD hThread, ebHSCRIPT hScript)
{
	ASSERT(NULL != hScript);
	ASSERT(NULL != hThread);

CHandleMacroTrayIcons TrayIcons;		// evtl. TrayIcons anzeigen

LONG lThreadState = TS_IDLE;
BOOL fWarning = true;
CebThread Thread(hScript, false);
	
	Thread.Attach (hThread);
	do {
		Thread.Start();

		lThreadState = Thread.GetState();
		if (lThreadState == TS_SUSPENDED) {
		// Breakpoint in CallBackfunktion ausgelöst
			if (fWarning) 
			{
				AfxMessageBox (IDS_ILLBREAKPOINT); 	// Warnung an Nutzer
				fWarning = false;			// aber nur einmal
			}
			
		// Breakpoint löschen
		ebDBGINFO DI;
		
			Thread.GetDebugInfo (&DI);
			::ebClearBreakPoint ((ebHOBJECT)hScript, DI.wCurrent);
		}
	} while (lThreadState != TS_IDLE);

	Thread.Detach();
	return S_OK;
}

BOOL MessageNoEntry(HWND h, UINT uiEntry, LPCSTR lpcstrEntry)
{
	if (0 == uiEntry) return false;

	CString str, strApp, strLoad, strUnLoad, strMain;
	if (!LoadString(strLoad, IDS_LOADSCRIPT) ||
		!LoadString(strUnLoad, IDS_UNLOADSCRIPT) || 
		!LoadString(str, IDS_BADENTRY))
		return false; // No memory

	// Kontrolle nicht notwendig, diese Entry müssen nicht vorhanden sein
	if (lpcstrEntry == strUnLoad || lpcstrEntry == strLoad) return true;

	ErrorMessage(h, str);
	return true;
}
