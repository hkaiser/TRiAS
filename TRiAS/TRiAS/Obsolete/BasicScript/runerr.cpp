#include "bscriptp.hxx"
#include "bscript.h"

#include <oleguid.h>
#include <dirisole.h>
#include <triastlb.h>
#include <itriasap.h>

#include "toolbarx.h"

#include "bscripta.h"
#include "runerr.h"

extern SummitModul g_SummitModuls[];

CRunErr::CRunErr(LPUNKNOWN pOp, LPCSTR pT, const CString & strName)
{
	ASSERT(NULL != pT);
	ASSERT(!strName.IsEmpty());

	m_pOperateScripts = NULL;
	if (pOp) {
		m_pOperateScripts = pOp; 
		m_pOperateScripts -> AddRef();
	}

	m_strText = pT;	
	m_pScriptDebugger = NULL;
	
	m_strName = strName;
	m_fRunModal = false;
	m_fRTError = false;
}

CRunErr::~CRunErr()
{
	if (m_pOperateScripts) {
		m_pOperateScripts -> Release();
		m_pOperateScripts = NULL;
	}
			
// erst TRiAS wieder aktivieren, dann Debugger zerlegen, da sonst
// jemand anders als TRiAS aktiviert wird
	EnableTriasWindow(true);

// intern DestroyWindow()
	if (NULL != m_pScriptDebugger) {
		if (m_fRunModal) 
			m_pScriptDebugger -> Close(); 
		delete m_pScriptDebugger;
		m_pScriptDebugger = NULL;
	}
}

HRESULT CRunErr::CreateDebugger()
{
// Debugger-DLL nicht installiert	
	if (!g_SummitModuls[DEBUGGER].fIsInstalled) 
		return E_FAIL;

	EnableTriasWindow(false);

CMacroScriptExtension *pExt = (CMacroScriptExtension *)g_pTE;

	ASSERT(NULL != pExt);

	m_pScriptDebugger = new CBScriptDebug(pExt->ebInst(), pExt->MWind(), m_pOperateScripts); 
	ASSERT(NULL != m_pScriptDebugger);
	if (NULL == m_pScriptDebugger) return E_OUTOFMEMORY;
	
	if (NULL != m_pOperateScripts) {
	// öffnet Stream
		ASSERT(!m_strName.IsEmpty());
		if (!m_pScriptDebugger -> OpenStream((LPSTR)(LPCSTR)m_strName)) 
			return E_FAIL;
	}

	ASSERT(!m_strText.IsEmpty());
// immer
	if (!ebDebugger_SetText(GetDebuggerWnd(), m_strText)) 
		return E_FAIL;
	
return NOERROR;
}

HRESULT CRunErr::OnDemandRuntimeError(ebWORD wLinNr)
{
// testen, ob im richtigen Kontext verwendet
	ASSERT (!m_fRunModal);

// evtl. Debuggerfenster erzeugen
	m_fRTError = true;

	if (NULL == m_pScriptDebugger) {
	HRESULT hr = CreateDebugger();

		if (FAILED(hr)) 
			return hr;
		ASSERT(NULL != m_pScriptDebugger);
	}

	ebDebugger_SelectLines(GetDebuggerWnd(), wLinNr-2, wLinNr-1, true);

// jetzt, wo alles fertig ist, anzeigen
	m_pScriptDebugger -> EditOnly();	// UI richten, kein GO etc. möglich
	m_pScriptDebugger -> ShowWindow (SW_SHOWNORMAL);
	m_pScriptDebugger -> UpdateWindow();

return NOERROR;
}

HRESULT CRunErr::OnDemandBreakpoint(CebScript *pScript, CebThread *pThread)
{
	ASSERT(NULL != pScript);
	ASSERT(NULL != pThread);
	if (pScript == NULL || pThread == NULL) 
		return E_POINTER;
	ASSERT(NULL != pThread->GetHandle());
	ASSERT(NULL != pScript->GetHandle());
	if (NULL == pScript->GetHandle() || NULL == pThread->GetHandle()) 
		return E_HANDLE;

// testen, ob im richtigen Kontext verwendet
	ASSERT(!m_fRTError);

	m_fRunModal = true;

// evtl. Debuggerfenster erzeugen
	if (NULL == m_pScriptDebugger) {
	HRESULT hr = CreateDebugger();

		if (FAILED(hr)) 
			return hr;
		ASSERT(NULL != m_pScriptDebugger);
	}

	if (!ebDebugger_SetScript(GetDebuggerWnd(), pScript->GetHandle())) return E_FAIL;
	if (!ebDebugger_SetThread(GetDebuggerWnd(), pThread->GetHandle())) return E_FAIL;

// jetzt Debugger anzeigen 
HRESULT hr = m_pScriptDebugger -> RunModal();	
	if (E_ABORT == hr || E_UNEXPECTED == hr)
		// Debugger wurde geschlossen
		m_fRunModal = false;

return hr;
}

HRESULT CRunErr::EnableTriasWindow(bool fEnable)
{
HWND hWnd = ((CMacroScriptExtension *)g_pTE) -> hWnd();

	ASSERT(NULL != hWnd && IsWindow(hWnd));

	::EnableWindow(hWnd, fEnable); 

return NOERROR;
}

HWND CRunErr::GetDebuggerWnd()
{
HWND hWnd = m_pScriptDebugger -> m_Debug.GetWindow();	

	ASSERT(NULL != hWnd && IsWindow(hWnd));
	if (!IsWindow(hWnd)) 
		hWnd = NULL;

return hWnd;
}
