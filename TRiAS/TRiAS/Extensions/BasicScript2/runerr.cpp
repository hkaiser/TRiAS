#include "bscriptp.hxx"
#include "bscript.h"

#include <oleguid.h>
#include <dirisole.h>
#include <triastlb.h>
#include <itriasap.h>
#include <iobjman.h>

#include "macrguid.h"
#include "iscrprop.h"

#include "toolbarx.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "DebCtrl.h"
#include "splitter.h"
#include "split.h"
#include "runerr.h"

extern SummitModul g_SummitModuls[];


CRunErr::CRunErr(const CString & strName)
{
	ASSERT(!strName.IsEmpty());
	m_pScriptDebugger = NULL;
	SetName(strName);
}

CRunErr::~CRunErr()
{	
// erst TRiAS wieder aktivieren, dann Debugger zerlegen, da sonst
// jemand anders als TRiAS aktiviert wird
	EnableTriasWindow(true);
	m_pScriptDebugger = NULL;
}

HRESULT CRunErr::CreateDebugger(UINT uiWMClose, BOOL fOpen, ebWORD wLineNr, IObjectManagement *pIOM, IStreamInfo *pISI)
{
	ASSERT(!m_strName.IsEmpty());
	if (m_strName.IsEmpty()) return E_INVALIDARG;

	EnableTriasWindow(false);
	
	HRESULT hr = NOERROR;
	
	// Neuen Debugger kreieren, Baum füllen, DebCtrl init.
	if (NULL == m_pScriptDebugger)
		hr = ::CreateDebugger(g_pBSE -> MWind(), m_strName, fOpen, uiWMClose, pIOM, pISI, &m_pScriptDebugger);
	else // Nur neuen Script öffnen
		hr = m_pScriptDebugger -> Init(m_strName, fOpen, pIOM, pISI);

	if (FAILED(hr)) return hr;
	
	m_pScriptDebugger -> SetEditOnly(true);// Nur editieren möglich	
	ebDebugger_SelectLines(GetDebuggerWnd(), wLineNr-2, wLineNr-1, true);
	
	return hr;
}

HRESULT CRunErr::EnableTriasWindow(BOOL fEnable)
{
	HWND hWnd = g_pBSE -> hWnd();
	ASSERT(NULL != hWnd && IsWindow(hWnd));
	::EnableWindow(hWnd, fEnable); 
	if (fEnable) SetFocus(hWnd);
	return NOERROR;
}
HWND CRunErr::GetDebuggerWnd()
{
	HWND hWnd = m_pScriptDebugger -> GetDebuggerWnd();	
	ASSERT(NULL != hWnd && IsWindow(hWnd));
	if (!IsWindow(hWnd)) hWnd = NULL;
	return hWnd;
}
////////////////////////////////////////////////////////////////
// BreakPointDebuuger
CRunBreakPoint::~CRunBreakPoint()
{	// intern Delete()
	if (NULL != m_pScriptDebugger) 
		m_pScriptDebugger -> DestroyWindow();
	m_pScriptDebugger = NULL;
}

HRESULT CRunBreakPoint::OnDemandBreakpoint(CebScript *pScript, CebThread *pThread, IObjectManagement *pIOM, IStreamInfo *pISI)
{
	ASSERT(NULL != pScript);
	ASSERT(NULL != pThread);
	if (pScript == NULL || pThread == NULL) return E_POINTER;
	ASSERT(NULL != pThread->GetHandle());
	ASSERT(NULL != pScript->GetHandle());
	if (NULL == pScript->GetHandle() || NULL == pThread->GetHandle()) return E_HANDLE;

	HRESULT hr = NOERROR;
	try
	{// evtl. Debuggerfenster erzeugen
		hr = CreateDebugger(WM_CLOSEBREAKPOINTDEBUGGERDIALOG, false, 0, pIOM, pISI);
		if (FAILED(hr)) _com_issue_error(hr);
		// Fertzigen Script und Thread unterschieben
		if (!ebDebugger_SetScript(GetDebuggerWnd(), pScript->GetHandle())) _com_issue_error(E_FAIL);
		if (!ebDebugger_SetThread(GetDebuggerWnd(), pThread->GetHandle())) _com_issue_error(E_FAIL);
		// jetzt Debugger anzeigen 
		hr = m_pScriptDebugger -> RunModal();	
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch(_com_error& e)
	{
		if (m_pScriptDebugger) 
			m_pScriptDebugger -> DestroyWindow(); 
		m_pScriptDebugger = NULL;
		return _COM_ERROR(e);
	}
	return S_OK;
}
