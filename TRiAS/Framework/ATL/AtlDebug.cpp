// @doc 
// @module atldebug.cpp | Debug-HilfsMacros und Debug-HilfsKlaasen

#if defined(_ATLX_DEBUG_REFCOUNT_WALKSTACK)

#ifndef __ATLBASE_H__
	#error atldebug.cpp requires atlbase.h to be included first
#endif

#include <AtlDebug.h>
#include <ospace/file/path.h>

#include <PE_Debug.cpp>			// reqiured only in one module

#if defined(_USE_BSCKIT)
#include <bsc.h>
#pragma comment(lib, "msbsc50.lib")		// link to msbsc50.dll
#endif // _USE_BSCKIT

namespace {

	enum ATLDEBUGSUPPORTX {
		ATLDEBUGSUPPORTX_NoWalkStackAtAll = 0,		// kein StackWalk 
		ATLDEBUGSUPPORTX_WalkStackForAll = 1,		// alle Interfaces untersuchen
		ATLDEBUGSUPPORTX_WalkStackForSelected = 2,	// nur in DEBUGSUPPORT_MAP gegebene Interfaces untersuchen
		ATLDEBUGSUPPORTX_RefreshList = 0x80,		// vor jedem Test Liste neu einlesen
		ATLDEBUGSUPPORTX_OptionMask = 0x03,
	};

/////////////////////////////////////////////////////////////////////////////
// Einlesen der RegistrySettings für den AtlDebugSupport
	class CReadRegistrySettings 
	{
	private:
		ATLDEBUGSUPPORTX m_rgSettings;

	public:
		CReadRegistrySettings()
		{
		CRegKey cfgkey;

			m_rgSettings = ATLDEBUGSUPPORTX_NoWalkStackAtAll;
			if (ERROR_SUCCESS == cfgkey.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
				ERROR_SUCCESS == cfgkey.Open(cfgkey, TEXT("uve")) &&
				ERROR_SUCCESS == cfgkey.Open(cfgkey, TEXT("TRiAS")) &&
				ERROR_SUCCESS == cfgkey.Open(cfgkey, TEXT("Config")))
			{
				ASSERT(sizeof(DWORD) == sizeof(ATLDEBUGSUPPORTX));
				cfgkey.QueryValue ((DWORD &)m_rgSettings, TEXT("AtlDebugSupport"));
			}
		}
		ATLDEBUGSUPPORTX GetSettings() { return (ATLDEBUGSUPPORTX)(m_rgSettings & ATLDEBUGSUPPORTX_OptionMask); }
		bool RefreshList() { return m_rgSettings & ~ATLDEBUGSUPPORTX_OptionMask; }
	};
	CReadRegistrySettings g_Settings;

}; // namespace

#ifndef ATL_NO_NAMESPACE
namespace ATL
{
#endif

/////////////////////////////////////////////////////////////////////////////
//
ATLAPI_(void) AtlWalkStackOnAddRefX (CStackProbeLists &Lists, DWORD dwCookie, REFIID riid, bool fNotFatal)
{
	if (ATLDEBUGSUPPORTX_NoWalkStackAtAll == g_Settings.GetSettings())
		return;		// WalkStack vollständig passiviert

// überprüfen, ob dieses Interface überhaupt getestet werden soll
	if (ATLDEBUGSUPPORTX_NoWalkStackAtAll != g_Settings.GetSettings() && 
		!g_IIDsToAnalyse.Analyse(riid, g_Settings.RefreshList()))
	{
		return;		// nicht analysieren
	}

// evtl. nicht das erste mal
CStackProbeLists::iterator it = Lists.find (dwCookie);

	if (it != Lists.end()) {
	// nicht das erste AddRef über diesen Pointer, StackWalk vom ersten beibehalten
		if ((*it).second) {
			(*it).second -> AddRef();
			(*it).second -> SetStatus();
		}
		return;
	}
	
CStackProbeList *pProbe = NULL;

	ATLTRY(pProbe = new CStackProbeList(fNotFatal));
	if (NULL == pProbe) return;

// The structure of the stack frames is the following:
// EBP -> parent stack frame EBP
//        return address for this call ( = caller )
// The chain can be navigated iteratively, after the
// initial value of EBP is loaded from the register
DWORD parentEBP;

	__asm MOV parentEBP, EBP

// Skip the first EBP as it points to AtlWalkStackOnAddRefX, which is
// uninteresting for the user
	parentEBP = *(DWORD*)parentEBP;
	do {
	BYTE* caller = *((BYTE**)parentEBP + 1);

		parentEBP = *(DWORD*)parentEBP;
    
	// Get the instance handle of the module where caller belongs to
	MEMORY_BASIC_INFORMATION mbi;

		::VirtualQuery (caller, &mbi, sizeof(mbi));
    
	// The instance handle is equal to the allocation base in Win32
    HINSTANCE hInstance = (HINSTANCE)mbi.AllocationBase;

		if (NULL == hInstance) 
			break; // End of the call chain

		pProbe -> push_back (caller);
	} while (true);

// in Baum einfügen
	Lists.insert (CStackProbeLists::value_type(dwCookie, pProbe));
}

ATLAPI_(void) AtlWalkStackOnReleaseX (CStackProbeLists &Lists, DWORD dwCookie, REFIID riid)
{
	if (ATLDEBUGSUPPORTX_NoWalkStackAtAll == g_Settings.GetSettings())
		return;		// WalkStack vollständig passiviert

// überprüfen, ob dieses Interface überhaupt getestet werden soll
	if (ATLDEBUGSUPPORTX_NoWalkStackAtAll != g_Settings.GetSettings() && 
		!g_IIDsToAnalyse.Analyse(riid, g_Settings.RefreshList()))
	{
		return;		// nicht analysieren
	}

CStackProbeLists::iterator it = Lists.find (dwCookie);

	if (it != Lists.end()) {
		if ((*it).second && 0 == (*it).second -> Release()) {
			delete (*it).second;
			Lists.erase (it);		// wenns die letzte Referenz war, dann rauslöschen
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// dekorierten Namen lesbar machen
LPSTR demangle (LPCSTR pcModule, LPSTR pcFunction)
{
#if defined(_USE_BSCKIT)
Bsc *pBsc = NULL;

	if (Bsc::open (pcModule, &pBsc))
		return pBsc -> formatDname (pcFunction);
#endif // _USE_BSCKIT
	return pcFunction;		// *.bsc nicht gefunden
}

HRESULT WINAPI AtlDumpIIDX (REFIID iid)
{
	USES_CONVERSION;

CRegKey key;
TCHAR szName[100];
DWORD dwType, dw = sizeof(szName);

LPOLESTR pszGUID = NULL;

	StringFromCLSID(iid, &pszGUID);

// Attempt to find it in the interfaces section
	key.Open(HKEY_CLASSES_ROOT, _T("Interface"));
	if (key.Open(key, OLE2T(pszGUID)) == S_OK)
	{
		*szName = 0;
		RegQueryValueEx(key.m_hKey, (LPTSTR)NULL, NULL, &dwType, (LPBYTE)szName, &dw);
		OutputDebugString(szName);
		goto cleanup;
	}

// Attempt to find it in the clsid section
	key.Open(HKEY_CLASSES_ROOT, _T("CLSID"));
	if (key.Open(key, OLE2T(pszGUID)) == S_OK)
	{
		*szName = 0;
		RegQueryValueEx(key.m_hKey, (LPTSTR)NULL, NULL, &dwType, (LPBYTE)szName, &dw);
		OutputDebugString(_T("(CLSID\?\?\?) "));
		OutputDebugString(szName);
		goto cleanup;
	}
	OutputDebugString(OLE2T(pszGUID));

cleanup:
	CoTaskMemFree(pszGUID);
	return S_OK;
}

ATLAPI_(void) AtlDumpPendingReleasesX (CStackProbeLists &Lists, REFIID riid)
{
	if (ATLDEBUGSUPPORTX_NoWalkStackAtAll == g_Settings.GetSettings())
		return;		// WalkStack vollständig passiviert

	if (0 == Lists.size())
		return;		// nichts mehr übrig (keine leaks)

// Leaks auflisten
static CPEDebug PE_debug;		// workhorse
static char cbFile[_MAX_PATH];
static char cbModule[_MAX_PATH];
static char cbFunc[2*_MAX_PATH];
int iLineNo = 0;

	for (CStackProbeLists::iterator it = Lists.begin(); it != Lists.end(); ++it) {
	CStackProbeList *pList = (*it).second;

		if (NULL == pList || pList -> Status())		// nicht fataler Fehler (von ppi() etc.)
			continue;

		ATLTRACE("-------------------------------------------------------------------------------\r\n");
		ATLTRACE("%08lx: Pending release (refcnt: %ld) on interface ", (*it).first, pList -> RefCnt());
		AtlDumpIIDX(riid);
		ATLTRACE(" (%08lx)\r\n", *(BYTE **)((*it).first));
		for (CStackProbeList::iterator lit = pList -> begin(); lit != pList -> end(); ++lit) {
		// Get the instance handle of the module where caller belongs to
		BYTE *pCaller = (*lit);
		MEMORY_BASIC_INFORMATION mbi;

			::VirtualQuery (pCaller, &mbi, sizeof(mbi));
    
		// The instance handle is equal to the allocation base in Win32
		HINSTANCE hInstance = (HINSTANCE)mbi.AllocationBase;

			if (NULL == hInstance)
				break;	// End of the call chain

			iLineNo = 0;
			cbFile[0] = '\0';
			cbFunc[0] = '\0';

			PE_debug.DumpDebugInfo (pCaller, hInstance, cbFile, sizeof(cbFile), cbFunc, sizeof(cbFunc), &iLineNo);
			ATLTRACE("%s(%ld): ", cbFile, iLineNo);

			GetModuleFileName (hInstance, cbModule, sizeof(cbModule));

		os_path path = os_string(cbModule);

			ATLTRACE("%s: ", path.filename().c_str());
			ATLTRACE("%s\r\n", demangle(cbModule, cbFunc));
		}

	// jetzt noch alles freigeben
		delete pList;
		(*it).second = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Zu analysierende IID's
CIIDsToAnalyse::CIIDsToAnalyse()
{
	Refresh(); 
}

CIIDsToAnalyse::~CIIDsToAnalyse()
{
}

void CIIDsToAnalyse::Refresh() 
{
const IID **ppriid = GetIIDsToAnalyse();

	erase(begin(), end());				// bisheriges vergessen
	m_fAnalyseAll = true;

	if (ATLDEBUGSUPPORTX_WalkStackForSelected == g_Settings.GetSettings()) 
	{
	// lediglich vorgebbare Id's auswerten
		while (!InlineIsEqualGUID(IID_NULL, **ppriid)) {
			m_fAnalyseAll = false;
			push_back(*ppriid);
			ppriid++;
		}
	}
}

bool CIIDsToAnalyse::Analyse (REFIID riid, bool fRefresh)
{
	if (m_fAnalyseAll) return true;

	if (fRefresh) Refresh();

	for (iterator it = begin(); it != end(); ++it) {
		if (InlineIsEqualGUID(*(*it), riid))
			return true;
	}
	return false;
}

const IID **CIIDsToAnalyse::GetIIDsToAnalyse() 
{
	return _atl_debugsupport_IIDsToAnalyse; 
}

#ifndef ATL_NO_NAMESPACE
}; //namespace ATL
#endif

#endif // _ATLX_DEBUG_REFCOUNT_WALKSTACK

