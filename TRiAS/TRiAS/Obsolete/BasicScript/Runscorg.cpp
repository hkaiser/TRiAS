#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <ospace/std/string>

#include "runscorg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////////////////////////////////////////////
// *** Verwaltung laufender Scripts ***
////////////////////////////////////////////////////////////////////////////////

CRunScriptsOrg::CRunScriptsOrg(void)
	:	m_mapThreads(),
		m_mapScripts()
{
	m_itS = m_mapScripts.begin();
	m_it = m_mapThreads.begin();
	m_hScriptAutoStart = NULL;
}


CRunScriptsOrg::~CRunScriptsOrg()
{
HRESULT hr = DeleteAll();
	ASSERT(SUCCEEDED(hr));
}

// Scripts zu einem bestimmten Entry enumerieren
HRESULT CRunScriptsOrg::FindNext (ebHSCRIPT *phScript, LPCSTR pcThreadEntry, bool fFirst)
{
	ASSERT(pcThreadEntry);
	ASSERT(phScript);

char  lpstr[MAXSTRLENGTH];
	
	strcpy(lpstr, pcThreadEntry);

	ToUpper(lpstr);

os_string str(lpstr);
	
	if (m_mapThreads.count(str) == 0) return S_FALSE;

	*phScript = NULL;

	if (fFirst) 
		m_it = m_mapThreads.find(str); // Find first match.
	
	if (m_it != m_mapThreads.end()) {
		str = (*m_it).first;
		if (0 == _stricmp (str.c_str(), lpstr)) 
			*phScript = (*m_it).second;
		m_it++;
    }
	else {
// == end() !!!
		m_it = m_mapThreads.begin();
		*phScript = NULL;
		return S_FALSE;
	}

// != end() !!!
return S_OK;  
}

// alle Scriptnamen und zugehörige Scripts enumerieren
HRESULT CRunScriptsOrg::FindNext (char *pcScriptName, short iLen, ebHSCRIPT *phScript)
{
	ASSERT(pcScriptName);

	*phScript = NULL;

char  lpstr[MAXSTRLENGTH];
	
	strcpy(lpstr, pcScriptName);

	ToUpper(lpstr);

os_string str;

	if (m_itS != m_mapScripts.end()) {
		*phScript = (*m_itS).second;
		str = (*m_itS).first;
		if ((int)str.length() > iLen) return E_FAIL;
		strcpy(lpstr, (LPSTR)str.c_str());
		m_itS++;
    }
	else {
// == end() !!!
		m_itS = m_mapScripts.begin();
		*pcScriptName = NULL;
		*phScript = NULL;
		return S_FALSE;
	}

// != end() !!!
return S_OK;  
}

// Script zum Scriptnamen finden 
HRESULT CRunScriptsOrg::Find (LPCSTR pcScriptName, ebHSCRIPT *phScript)
{
	ASSERT(pcScriptName);

	*phScript = NULL;

char  lpstr[MAXSTRLENGTH];
	
	strcpy(lpstr, pcScriptName);

	ToUpper(lpstr);

os_string str(lpstr);
script_map::iterator it = m_mapScripts.find(str);
// kein Match gefunden
	if (it == m_mapScripts.end()) return S_FALSE;

	*phScript = (*it).second;

	if (NULL == *phScript) return E_FAIL;

return S_OK;  
}

HRESULT CRunScriptsOrg::OutputRunningThreads (short iCnt)
{
	TRY {
	char c[MAXSTRLENGTH];
	CString str = itoa(iCnt, c, 10);
	CString strCap; strCap.LoadString (IDS_LONGCLASSNAME);
	CString strOut;

		strOut.Format (IDS_RUNNINGTHREADS, (LPCSTR)str); 
		MessageBox (::GetActiveWindow(), strOut, strCap, MB_OK | MB_ICONINFORMATION);

	} CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return E_OUTOFMEMORY;
	} END_CATCH;
	
return NOERROR;
}

// Sind noch Threads RUNNING ?
HRESULT CRunScriptsOrg::IsThreadRunning(ebHSCRIPT hScript)
{
ebHTHREAD hThread = (ebHTHREAD)ebEnumObject((ebHOBJECT) hScript, EO_FIRSTTHREAD);
	if (hThread == NULL) return NOERROR;

// schon einen laufenden gefunden !
short iThreadCnt = 0;

	while (hThread) {
		iThreadCnt++;
		hThread = (ebHTHREAD)ebEnumObject(hScript, EO_NEXTTHREAD);
	}

// Threads noch RUNNING !!!
return OutputRunningThreads (iThreadCnt);
}

HRESULT CRunScriptsOrg::EndThreadRunning(ebHSCRIPT hScript)
{
ebHTHREAD hThread = (ebHTHREAD)ebEnumObject((ebHOBJECT) hScript, EO_FIRSTTHREAD);

// einen laufenden gefunden 
	while (hThread) {

	ebDWORD dwErr = 0;
	// Abbruch, 1 heisst: Runtimeerror-Generierung, dann IDLE-State	
		ebThread_Interrupt(hThread, 1, dwErr);
		::ebDestroyThread(hThread);
		hThread = (ebHTHREAD)ebEnumObject(hScript, EO_NEXTTHREAD);
	}

return NOERROR;
}

// hTHread zum enumerieren der Entries
HRESULT CRunScriptsOrg::Add (ebHSCRIPT hScript, LPCSTR pcScriptName)
{
// *** Map und Multimap füllen ***

	ASSERT(hScript);
	ASSERT(pcScriptName);

char  lpstr[MAXSTRLENGTH];
	
	strcpy(lpstr, pcScriptName);

	ToUpper(lpstr);

	// Map füllen, zu einem Script ein Scriptname
HRESULT hr = AddScript (hScript, lpstr); 
					// Script schon in Map
	if (FAILED(hr) || GetScode(hr) == S_FALSE) return hr;

ebPROCINFO PI;
ebBOOL fNext = true;

// alle Entries enumerieren und in Map füllen
ebHENUM hEnum = ebGetFirstProc(hScript, &PI);
	if (hEnum == NULL) return E_FAIL;
		
	while (fNext) {
		if (strcmp ("Main", PI.szName)) {
			// Multimap füllen, mehrere Entries zu einem Script

			ToUpper(PI.szName);

			hr = AddEntry (hScript, PI.szName); 
			if (FAILED(hr)) {
				ebEnumClose(hEnum);
				return hr;
			}
		}
		fNext = ebGetNextProc(hEnum, &PI);
	}		
	
	ebEnumClose(hEnum);
	
	m_itS = m_mapScripts.begin();
	m_it = m_mapThreads.begin();

return hr;
}

// Map füllen, ein ScriptName
HRESULT CRunScriptsOrg::AddScript (ebHSCRIPT hScript, LPCSTR pcScriptName)
{
	ASSERT(pcScriptName);
	ASSERT(hScript);

// *** Nur einen Script (ein Scriptname) !!! *** 

os_string strS(pcScriptName);
script_map::iterator itS;

	itS = m_mapScripts.find(strS);
// Script schon vorhanden
	if (itS != m_mapScripts.end())
		return S_FALSE;

	m_mapScripts.insert(strS, hScript);

return NOERROR;
}

// Multimap füllen, mehrere Entries für ein Script, wird in Schleife ausgeführt
HRESULT CRunScriptsOrg::AddEntry (ebHSCRIPT hScript, LPCSTR pcThreadEntry)
{
	ASSERT(hScript);
	ASSERT(pcThreadEntry);

os_string str(pcThreadEntry);
thread_mmap::iterator it = m_mapThreads.insert(str, hScript);
	if(it == m_mapThreads.end()) return E_FAIL;

return NOERROR;
}

HRESULT CRunScriptsOrg::Delete (ebHSCRIPT hScript)
{
	ASSERT(hScript);

	// wenn noch laufende Threads, Scripts nicht löschen
	// *** später noch bearbeiten !!! ***
HRESULT hr = IsThreadRunning(hScript);
	if (FAILED(hr) || GetScode(hr) == S_FALSE) return hr;

	hr = DeleteEntry(hScript);
	if (FAILED(hr)) return hr;
	
	hr = DeleteScript(hScript);
	if (FAILED(hr)) return hr;

return hr;
}

// alle Entries der Multimap löschen 
HRESULT CRunScriptsOrg::DeleteEntry (ebHSCRIPT hScript)
{
thread_mmap::iterator it = m_mapThreads.begin();

// mehrere Entries für einen Script 
	while(it != m_mapThreads.end()) {		
		if ((*it).second == hScript) {
// aus Map löschen 
			m_mapThreads.erase(it);
// wieder an den Anfang, da it++ nicht funktioniert,
// wenn der linke Knoten in der Map gelöscht ist (GP!)
			it = m_mapThreads.begin();
		}
		else
			it++;
	}

	m_it = m_mapThreads.begin();

return NOERROR; 
}

HRESULT CRunScriptsOrg::DeleteScript (ebHSCRIPT hScript)
{
	ASSERT(hScript);

script_map::iterator it = m_mapScripts.begin();

	while(it != m_mapScripts.end()) {		
		if ((*it).second == hScript) {
	
		// aus Map löschen 
			m_mapScripts.erase(it);

		// freigeben
			if (hScript) ::ebDestroyScript(hScript);
			hScript = NULL;

			m_itS = m_mapScripts.begin();

			return NOERROR;
		}
		it++;
	}
	
return NOERROR;
}

HRESULT CRunScriptsOrg::DeleteAll (void)
{
thread_mmap::iterator it = m_mapThreads.begin();
HRESULT hr = NOERROR;
ebHSCRIPT hScript = NULL;
	
	while(it != m_mapThreads.end()) {		
		hScript = (*it).second;		
		if (hScript) {
	// wenn noch laufende Threads, Scripts nicht löschen
	// *** später noch bearbeiten !!! ***
			hr = IsThreadRunning(hScript);
			if (FAILED(hr) || GetScode(hr) == S_FALSE) return hr;
			::ebDestroyScript(hScript);
		}
		it++;
	}
	
	m_mapThreads.erase(m_mapThreads.begin(), m_mapThreads.end());

return hr;
}

void CRunScriptsOrg::ToUpper(LPSTR lpstr)
{
int i=0;
int iSize = strlen(lpstr);
LPSTR lpstrSearch = lpstr;

	for (i=0; i<iSize; i++) {
		if (__isascii(*lpstrSearch) && islower(*lpstrSearch)) {
			*lpstrSearch = toupper ((int)*lpstrSearch); 
		}
		lpstrSearch++;
	}
}