// WrapperExtension.cpp

#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <triastlb.h>
#include <registrx.hxx>

#include "macrguid.h"
#include "conststr.h"
#include "wrapxt.h"

//#if _MSC_VER >= 1100
//EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
//#endif // _MSC_VER <= 1100

DefineSmartInterface (ExtendBScript);

/////////////////////////////////////////////////////////////////////////////
// Zähler der zusätzlichen Erweiterungen
LONG CBSWrapperExtension::m_lCntExts = 0;

CBSWrapperExtension::CBSWrapperExtension(void)
{
}

CBSWrapperExtension::~CBSWrapperExtension(void)
{
}

STDMETHODIMP_(HDEX) CBSWrapperExtension::LoadExtension (TRIASLOADEX *pTL, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	CTriasExtension::LoadExtension (pTL, hWnd);

// Der Rückkehrwert dieser Funktion wird in TRiAS als Schlüssel für die
// Sortierung der geladenen Erweiterungen verwendet: er muß _eindeutig_ sein !
// Da CTriasExtension::LoadExtension diesen jedoch auf den hInstance dieser DLL 
// initialisiert, würden alle Erweiterungen hier einen identischen Suchschlüssel 
// erhalten. Also ein kleiner Trick: hInstance + Zähler der instantiierten
// Erweiterungen. (ACHTUNG plattformspezifisch: der hInstance ist unter
// Win32 immer das Datensegment der DLL welches auf Segmentgrenzen 
// ausgerichtet ist und damit genug Raum für eindeutige Zahlen bietet.)
	{
	CComGlobalsThreadModel::AutoCriticalSection cs;

		cs.Lock();
		ASSERT(0 == ((DWORD)m_hDex & 0x00000FFF));	// genügend Nullen am Ende, das reicht für 0xfff Erweiterungen
		m_hDex += ++m_lCntExts;					// <<-- plattformspezifisch
		cs.Unlock();
	}

	return m_hDex;
}

STDMETHODIMP_(BOOL) CBSWrapperExtension::InitExtension (short iMode)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (!CTriasExtension::InitExtension (iMode)) return false;

	try 
	{
		// Haupterweiterung ggf. nachladen
		if (NULL == g_pTE || !g_pTE -> isLoaded()) 
		{// Haupterweiterung nachladen
			THROW_FAILED_HRESULT(m_pXtnSite -> GetXtension (CLSID_MacroScriptExtension, IID_IUnknown, m_UnknownExt.ppv()));
			// jetzt müßte alles geladen sein
			ASSERT(NULL != g_pTE && g_pTE -> isLoaded());
			if (NULL == g_pTE || !g_pTE -> isLoaded()) _com_issue_error(E_FAIL);
		} 
		// Script Öffnen, Starten
		// Wird angeworfen, wenn ebInstance schon vorhanden, 
		// und Script noch nicht läuft,
		// ansonsten erst in Notification DEX_N_ScriptingEngineActive
		HRESULT hr = OnActiveScriptEngine();
		// Script läuft schon oder keine ebInstance erzeugt
		if (FAILED(hr) && hr != E_UNEXPECTED) _com_issue_error(hr); 
		// Notification, daß ebInstance kreiert worden ist 
		RegisterNotification (DEX_N_SCRIPTINGENGINEACTIVE);		
	}
	catch (_com_error &) 
	{
		return false;		// Fehler melden
	}
	return true;		// snh
}

STDMETHODIMP_(BOOL) CBSWrapperExtension::UnLoadExtension (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	ASSERT(!m_strScriptName.IsEmpty());
	// Script anhalten
	g_pBSE -> StopScript(m_strScriptName);
	UnRegisterNotification (DEX_N_SCRIPTINGENGINEACTIVE);		
	return CTriasExtension::UnLoadExtension();
}

STDMETHODIMP_(LRESULT) CBSWrapperExtension::Notification (WPARAM iMsg, LPARAM p)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	HRESULT hr = NOERROR;
	bool fResult = true;
	switch (iMsg) 
	{
	case DEX_N_SCRIPTINGENGINEACTIVE:	// ebInstance erzeugt
		// Script Öffnen, Starten
		// Wird angeworfen, wenn ebInstance schon vorhanden 
		// und Script noch nicht läuft (ansonsten E_UNEXPECTED)
		hr = OnActiveScriptEngine();
		if (FAILED(hr) && hr != E_UNEXPECTED) fResult = false;
		break;
	default:
		break;
	}
	return fResult;
}
///////////////////////////////////////////////////////////////////////////////
// IInitDTRiASExtension
STDMETHODIMP CBSWrapperExtension::InitDTRiASExtension (IUnknown *pIUnk, long hPr)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return E_NOTIMPL;
}

// Initialisierung aus der Registry
STDMETHODIMP CBSWrapperExtension::InitDTRiASExtensionRegKey (BSTR bstrRegKey, long hPr)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	USES_CONVERSION;

	os_string strKey (OLE2A(bstrRegKey));
	char cbBuffer[_MAX_PATH];
	DWORD dwLen = _MAX_PATH;

	// Wenn nicht projektbezogener Script gestartet werden soll
	if (NULL == hPr)
	{
		strKey += os_string(g_cbDel) + g_cbConfig;

	CCurrentUser regCfg(KEY_READ, strKey.c_str());

		if (!regCfg.isValid() || !regCfg.GetSubSZ (g_cbFileProgID, cbBuffer, dwLen))
			return HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND);
	}
	else
	{	// IniNamen des Projektes geben lassen
		os_path ini;
		HRESULT hr = GetActiveProjectIni (hPr, ini);
		if (FAILED(hr)) return hr;

		if (!GetPrivateProfileString(
					OLE2A(bstrRegKey),				// Section hier der Name erzeugten Objektes (aus GUID ?)
					g_cbFileProgID,			// Schlüssel "FileProgID"
					NULL,					
					cbBuffer,				// eigentlicher zu lesender FileName
					dwLen,					// Bufferlänge
					ini)) return E_FAIL;
	}
	// FileName
	m_strScriptName = cbBuffer;
	return S_OK;
}

HRESULT CBSWrapperExtension::OnActiveScriptEngine()
{
	try
	{	
		ASSERT(!m_strScriptName.IsEmpty());
		if (m_strScriptName.IsEmpty()) _com_issue_error(E_UNEXPECTED);
		// Script Öffnen, Starten
		WExtendBScript IES = g_pBSE;
		THROW_FAILED_HRESULT(IES -> RunScript(m_strScriptName));
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Besorgen der aktuellen ProjektIni
HRESULT CBSWrapperExtension::GetActiveProjectIni (long hPr, os_path &path)
{
	try {
	char cbBuffer[_MAX_PATH];

		if (NULL == DEX_GetActiveProject (cbBuffer))
			_com_issue_error(E_UNEXPECTED);
		
		path = os_string(cbBuffer);
		path.extension (g_cbINI);	// DateiExtension ist jetzt .ini
	
	} catch (_com_error &e) {
		return _COM_ERROR(e);
	} catch (...) {
		return E_OUTOFMEMORY;
	}
	return S_OK;
}
