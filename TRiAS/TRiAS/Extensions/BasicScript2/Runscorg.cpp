#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include "macrguid.h"
#include "iscrprop.h"
#include "runscorg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Smarts 
////////////////////////////////////////////////////////////////////////////////
// *** Verwaltung laufender Scripts ***
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Globales
BOOL LoadString(CString & str, int IDS);

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
CRunScripts::CRunScripts(void)
	:	m_mapThreads(),
		m_mapScripts()
{
	Reset();
}

CRunScripts::~CRunScripts()
{
	VERIFY(SUCCEEDED(DeleteAll()));
}

void CRunScripts::Reset()
{
	m_itS = m_mapScripts.begin();
	m_it = m_mapThreads.begin();
}

// Bei Projektschliessen alle Managements zurücksetzen
HRESULT CRunScripts::ReleaseAllManagements ()
{
	char str[_MAX_PATH];
	HRESULT hr = NOERROR;
	WRunningObject IRO;
	while (S_OK == NextScriptName (str, _MAX_PATH, IRO.ppi())) {// End Threadrunning, Destroy Entries, Destroy Script
		IRO -> SetManagement(NULL, NULL, CLSID_NULL, NULL);
	}
	return hr;
}

// Scripts zu einem bestimmten Entry enumerieren
HRESULT CRunScripts::NextFromEntry (LPCSTR pcThreadEntry, IRunningObject ** ppIRunn)
{
	ASSERT(pcThreadEntry);
	ASSERT(ppIRunn);
	if (NULL == ppIRunn) return E_POINTER;
	if (NULL != *ppIRunn) return E_UNEXPECTED; // holds allready an instance

	HRESULT hr = E_FAIL;

	*ppIRunn = NULL;

	try {
		while (m_it != m_mapThreads.end()) {
			if (0 == _stricmp ((*m_it).first.c_str(), pcThreadEntry)) {	// Match gefunden
				*ppIRunn = (*m_it).second;
				ASSERT(NULL != *ppIRunn);
				if (NULL == *ppIRunn) _com_issue_error(E_POINTER);
				(*ppIRunn) -> AddRef();
				// Wegen return S_OK hochzählen	
				m_it++;
				return S_OK; // found and ABORT while
			} 
			// sonst hier hochzählen
			m_it++;
		} 
		hr = E_FAIL;
	} 
	catch (_com_error & e) 
	{// End or no match
		if (*ppIRunn) (*ppIRunn) -> Release(); *ppIRunn = NULL;
		hr =  _COM_ERROR(e);
	}
// == end() !!!
	m_it = m_mapThreads.begin();
	return hr;  
}

// alle Scriptnamen und zugehörige Scripts enumerieren
HRESULT CRunScripts::NextScriptName (LPSTR lpstrScriptName, short iLen, IRunningObject ** ppIRunn)
{
	ASSERT(lpstrScriptName);
	ASSERT(ppIRunn);
	if (NULL == ppIRunn) return E_POINTER;

	*ppIRunn = NULL;
	
	try {// reached end of map
		if (m_itS == m_mapScripts.end()) _com_issue_error(E_FAIL);

		os_string str = (*m_itS).first;
		if ((int)str.length() >= iLen) _com_issue_error(E_INVALIDARG);		
		strcpy(lpstrScriptName, str.c_str());
		if (0 == strlen(lpstrScriptName)) _com_issue_error(E_FAIL);		
		
		*ppIRunn = (*m_itS).second;
		ASSERT(NULL != *ppIRunn);
		if (NULL == *ppIRunn) _com_issue_error(E_FAIL);
		(*ppIRunn) -> AddRef();

		m_itS++; // try to find next match.	

	} catch (_com_error& e) {// == end() !!!, error ?
		m_itS = m_mapScripts.begin();
		if (*ppIRunn) (*ppIRunn) -> Release(); *ppIRunn = NULL;
		lpstrScriptName[0] = '\0';
		return _COM_ERROR(e);
	}
// != end() !!!
	return S_OK;  
}
// Script zum Scriptnamen finden 
HRESULT CRunScripts::Find (LPCSTR pcScriptName, IRunningObject ** ppIRunn)
{
	ASSERT(pcScriptName);

	if (NULL == pcScriptName) return E_POINTER;
	if (NULL != ppIRunn && NULL != *ppIRunn) return E_UNEXPECTED;

	if (NULL != ppIRunn)
		*ppIRunn = NULL;

script_map::iterator it = m_mapScripts.find(pcScriptName);

	if (it == m_mapScripts.end()) 
		return BS_E_NOTFOUND;		// no match

	if (NULL != ppIRunn) {
		*ppIRunn = (*it).second;
		ASSERT(NULL != *ppIRunn);
		if (NULL == *ppIRunn) 
			return E_POINTER;
		(*ppIRunn) -> AddRef();
	}
	return S_OK;  
}
// hTHread zum enumerieren der Entries
HRESULT CRunScripts::Add (IRunningObject *pIRunn, LPCSTR pcScriptName)
{// *** Map und Multimap füllen ***
	ASSERT(pIRunn);
	ASSERT(pcScriptName);
	// Map füllen, zu einem Script ein Scriptname
	HRESULT hr = AddScript (pIRunn, pcScriptName); 					
	if (S_OK != hr) return hr;// Script schon in Map
	// Entries enumerieren
	hr = AddEntries (pIRunn);
	if (FAILED(hr)) return hr;
	Reset();
	return hr;
}
// Entries enumerieren
HRESULT CRunScripts::AddEntries (IRunningObject *pIRunn)
{
	ASSERT(pIRunn);
	if (NULL == pIRunn) return E_POINTER;
	///////////////////////////////////////////////////
	// Alte Entries des Scripts werden gelöscht, und neue eingetragen.
	HRESULT hr = DeleteEntries (pIRunn);
	if (FAILED(hr)) return hr;

	CString strM, strL, strUn;
	if (!::LoadString(strM, IDS_MAIN) || !::LoadString (strL, IDS_LOADSCRIPT) || !::LoadString (strUn, IDS_UNLOADSCRIPT)) 
			return E_OUTOFMEMORY;
	
	char str[_MAX_PATH];
	ebBOOL fNext = false;// erstmal Enum holen

	while (S_OK == pIRunn -> EnumEntries(str, _MAX_PATH, &fNext))
	{	///////////////////////////////////////////////////
		// Multimap füllen, mehrere neue Entries zu einem Script
		if (strlen(str) > 0 &&			// Nur Gültige eintragen
			0 != _stricmp(strM, str) && 
			0 != _stricmp(strL, str) &&
			0 != _stricmp(strUn, str)) 
		{
			hr = AddEntry (pIRunn, str); 
			if (FAILED(hr)) return hr;
		}
	}
	return S_OK;
}
// Map füllen, ein ScriptName, ein Script
HRESULT CRunScripts::AddScript (IRunningObject *pIRunn, LPCSTR pcScriptName)
{
	ASSERT(pcScriptName);
	ASSERT(pIRunn);
	if (NULL == pcScriptName || NULL == pIRunn) return E_POINTER;
// *** Nur einen Script (ein Scriptname) !!! *** 
	os_string strS(pcScriptName);
	script_map::iterator itS = m_mapScripts.find(strS);
	if (itS != m_mapScripts.end()) return S_FALSE;	// Script schon vorhanden 

	WRunningObject IRO(pIRunn);
	m_mapScripts.insert(strS, IRO);
	return S_OK;
}

HRESULT CRunScripts::AddEntry (IRunningObject *pIRunn, LPCSTR pcThreadEntry)
{// Multimap füllen, mehrere Entries für ein Script, wird in Schleife ausgeführt
	ASSERT(pIRunn);
	ASSERT(pcThreadEntry);
	if (NULL == pIRunn || NULL == pcThreadEntry) return E_POINTER;

	os_string ossstr(pcThreadEntry);
	WRunningObject IRO(pIRunn);
	thread_mmap::iterator it = m_mapThreads.insert(ossstr, IRO);
	if (it == m_mapThreads.end()) return E_FAIL;
	return S_OK;
}
// Delete one Script and all entries of this script
HRESULT CRunScripts::Delete (LPCSTR lpcstr)
{// End Threadrunning, Destroy Entries, Destroy Script
	ASSERT(lpcstr);
	if (NULL == lpcstr) return E_POINTER;

	HRESULT hr1 = NOERROR;
	try 
	{
		WRunningObject IRO;
		HRESULT hr = Find(lpcstr, IRO.ppi());
		if (FAILED(hr)) _com_issue_error(hr);// no match
		IRO -> EndThreads();
		try 
		{// erstmal die Entries zu einem bestimmten Script immer löschen
			hr = DeleteEntries(IRO);
			if (FAILED(hr)) _com_issue_error(hr);
		} 
		catch (_com_error& e) 
		{// Script an sich immer löschen
			hr = DeleteScript(lpcstr);
			if (FAILED(hr)) return hr;
			return _COM_ERROR(e);
		}
		hr = DeleteScript(lpcstr);
		if (FAILED(hr)) _com_issue_error(hr);
	} 
	catch (_com_error& e) 
	{
		return _COM_ERROR(e);
	}
	return hr1;
}
// alle Entries der Multimap löschen 
HRESULT CRunScripts::DeleteEntries (IRunningObject *pIRO)
{
	ASSERT(pIRO);
	if (NULL == pIRO) return E_POINTER;

	thread_mmap::iterator it = m_mapThreads.begin();
	// mehrere Entries für einen Script 
	while(it != m_mapThreads.end()) {		
		if (pIRO == (*it).second) {	// aus Map löschen , Release()
			m_mapThreads.erase(it);
			// wieder an den Anfang, da it++ nicht funktioniert,
			// wenn der linke Knoten in der Map gelöscht ist (GP!)
			it = m_mapThreads.begin();
		} 
		else
			it++;
	}
	m_it = m_mapThreads.begin();
	return S_OK; 
}

HRESULT CRunScripts::DeleteScript (LPCSTR lpcstr)
{
	ASSERT(lpcstr);
	if (NULL == lpcstr) return E_POINTER;
	// Nur ein Eintrag zu einem Script in dieser Liste vorhanden	
	script_map::iterator it = m_mapScripts.find(lpcstr);
	if (it != m_mapScripts.end()) {		
		m_mapScripts.erase(it);
		m_itS = m_mapScripts.begin();
		return S_OK;
	}
	// nicht gefunden
	return E_FAIL;
}

HRESULT CRunScripts::DeleteAll (void)
{
	char str[_MAX_PATH];
	HRESULT hr = NOERROR;
	WRunningObject IRO;
	while (S_OK == NextScriptName (str, _MAX_PATH, IRO.ppi())) {// End Threadrunning, Destroy Entries, Destroy Script
		HRESULT hres = Delete(str);
		if (FAILED(hres)) hr = hres;
	}
	return hr;
}

