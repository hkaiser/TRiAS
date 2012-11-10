#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <new>
#include <iobjman.h>
#include "macrguid.h"

#include "iscrprop.h"
#include "projscr.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "runebobs.h"

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

//////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(ScriptProperty);
DefineSmartInterface(ObjManHelper);
DefineSmartInterface(BSProperty);
//////////////////////////////////////////////////////////
// globale Funktionen
CString	GetDefaultName(int IDS);
HRESULT	MessageNoCode(HWND hWnd, ebHCODE hCode, LPCSTR);

//////////////////////////////////////////////////////////
// CRelScripts: HilfsKlasse für Aufbewahrung von Related Scripts
CRelScripts::CRelScripts()
{
	m_pIObjectManagement = NULL;
	m_pIStreamInfo = NULL;
}

CRelScripts::~CRelScripts()
{
	ResetStorageManagement();
	DeleteRunningScriptsOrg();
}

bool CRelScripts::SetStorageManagement(IObjectManagement *pIObjMan, IStreamInfo *pIStrI)
{
	ResetStorageManagement();
	if (NULL != pIObjMan)
	{// ObjMan setzen
		m_pIObjectManagement = pIObjMan;
		m_pIObjectManagement -> AddRef();
	}
	if (NULL != pIStrI)
	{	// Streaminfo setzen
		m_pIStreamInfo = pIStrI;
		m_pIStreamInfo -> AddRef();
	}
	return true;
}

void CRelScripts::ResetStorageManagement(void)
{// Alle StorageManagements zurücksetzen
	ReleaseManagements();
	if(NULL != m_pIStreamInfo)
		m_pIStreamInfo -> Release();
	m_pIStreamInfo = NULL;
	if(NULL != m_pIObjectManagement)
		m_pIObjectManagement -> Release();
	m_pIObjectManagement = NULL;
}

void CRelScripts::DeleteRunningScriptsOrg()
{
	MapRelScriptsIt it = m_mapRelatedScripts.begin();
	// nicht in der Map
	while (it != m_mapRelatedScripts.end()) 
	{	// Subitem suchen
		long lRunScript = (*it).second;
		CRunScripts *pRunScriptsOrg = (CRunScripts *)lRunScript;
		ASSERT(pRunScriptsOrg);
		if (pRunScriptsOrg)
		{
			delete pRunScriptsOrg;
			pRunScriptsOrg = NULL;
		}
		it++;
	}
}

void CRelScripts::ReleaseManagements()
{
	MapRelScriptsIt it = m_mapRelatedScripts.begin();
	// nicht in der Map
	while (it != m_mapRelatedScripts.end()) 
	{	// Subitem suchen
		long lRunScript = (*it).second;
		CRunScripts *pRunScriptsOrg = (CRunScripts *)lRunScript;
		ASSERT(pRunScriptsOrg);
		if (pRunScriptsOrg)
		{
			pRunScriptsOrg -> ReleaseAllManagements ();
		}
		it++;
	}
}

HRESULT CRelScripts::AddScript(LPCSTR lpcstrSuperItem)
{// Fügt Script zur Liste aus SuperItems hinzu
	ASSERT(lpcstrSuperItem);
	if (NULL == lpcstrSuperItem) return E_POINTER;
	// Nur einmal einfügen !!!
	MapRelScriptsIt it = m_mapRelatedScripts.find(lpcstrSuperItem);
	if (it != m_mapRelatedScripts.end()) return S_FALSE;
	// Neue Runnings für bestimmtes Makroprojekt erzeugen
	CRunScripts *pRunScriptsOrg = NULL;
	try {
		pRunScriptsOrg = new CRunScripts();
	} catch(bad_alloc) {
		return E_OUTOFMEMORY;
	}
	m_mapRelatedScripts.insert(lpcstrSuperItem, (long)pRunScriptsOrg);
	return S_OK;
}
// Fügt Script zur Liste aus SuperItems hinzu
HRESULT CRelScripts::Add(LPCSTR lpcstrSuperItem)
{
	ASSERT(lpcstrSuperItem);
	if (NULL == lpcstrSuperItem) return E_POINTER;
	
	HRESULT hr = IsLoad(lpcstrSuperItem);
	if (S_OK != hr) return hr;

	hr = AddScript(lpcstrSuperItem);
	if (FAILED(hr)) return hr;

	return SetItems(lpcstrSuperItem);
}

HRESULT CRelScripts::IsLoad(LPCSTR lpcstrScriptName)
{
	ASSERT(lpcstrScriptName);
	ASSERT(m_pIObjectManagement);
	if (NULL == lpcstrScriptName || NULL == m_pIObjectManagement)  return E_POINTER;
	USES_CONVERSION;
	WUnknown IU;
	if (FAILED(m_pIObjectManagement -> GetObject(A2OLE(lpcstrScriptName), IU.ppi())))
		return S_FALSE;
	return S_OK;
}

// Löscht Script aus Liste von SuperItems 
HRESULT CRelScripts::Delete	(LPCSTR lpcstrSuperItem)
{
	ASSERT(lpcstrSuperItem);
	if (NULL == lpcstrSuperItem) return E_POINTER;
	// erstmal für Rückgabe Failed setzen
	HRESULT hr = S_FALSE;
	MapRelScriptsIt it = m_mapRelatedScripts.find(lpcstrSuperItem);
	// in der Map
	if (it != m_mapRelatedScripts.end()) 
	{
		long lRunS = (*it).second;
		CRunScripts *pRunScriptsOrg = (CRunScripts *)lRunS;
		ASSERT(pRunScriptsOrg);
		if (pRunScriptsOrg == NULL) return E_POINTER;
		// Alle Scripts und zugehörige Entries löschen
		delete pRunScriptsOrg;
		pRunScriptsOrg = NULL;
		// Aus der Map entfernen
		m_mapRelatedScripts.erase (it);
		hr = S_OK;
	}

	return hr;
}

// liefert  Script
HRESULT CRelScripts::CreateScript(CRunScripts *pRun, ebHCODE hCode, LPCSTR lpcstrSubItem, IRunningObject **ppIRO)
{
	ASSERT(pRun);
	ASSERT(lpcstrSubItem);
	ASSERT(ppIRO);
	if (NULL == ppIRO || NULL == lpcstrSubItem || NULL == pRun) return E_POINTER; 

	HRESULT hr = S_OK;
	ebHCODE hMakeCode = NULL;	
	LPSTR pText = NULL;
	WRunningObject IRO;
	UINT uiCntRelScripts = 0;
	LPSTR *lplpstrRelScripts = NULL;
	
	*ppIRO = NULL;

	try 
	{// Scriptobjekt erzeugen
		hr = CreateObject(CLSID_Script, IRO.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		// Objektverwaltung setzen
		IRO -> SetManagement(m_pIObjectManagement, m_pIStreamInfo, CLSID_Script, lpcstrSubItem);		
		 // Code von ObjectManagement
		WObjManHelper IOMH = IRO; // Query...
		if (NULL == hCode)
			hr = IOMH-> Open(&pText, &hMakeCode, &lplpstrRelScripts, uiCntRelScripts, false);
		if (FAILED(hr)) _com_issue_error(hr);
		// kein Code !!!, eventuell raus hier		
		if (NULL == hMakeCode && NULL == hCode)
			hr = MessageNoCode(GetActiveWindow(), NULL, lpcstrSubItem);
		if (FAILED(hr)) _com_issue_error(hr);// erstmal nch gültigen Code fragrn
		// CebScript erzeugen, Namen setzen
		hr = IRO -> CreateScript(&(g_pBSE -> ebInst()), hMakeCode ? hMakeCode : hCode);
		if (FAILED(hr)) _com_issue_error(hr);		
		// zu jedem Script nur einen Namen, aber mehrere Einsprungfunktionen
		hr = pRun -> Add(IRO, lpcstrSubItem);
		if (FAILED(hr)) _com_issue_error(hr);

		*ppIRO = IRO.detach();
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	if (pText) CoTaskMemFree (pText); pText = NULL;
	if (hMakeCode) CoTaskMemFree (hMakeCode); hMakeCode = NULL;
	return hr;
}

HRESULT CRelScripts::GetItem(
									LPCSTR lpcstrSuperItem, // zu diesem SUPER
									ebHSCRIPT hScript,		// zu diesem Script
									LPSTR lpstrName,		// Name 
									UINT uiLen,
									LPSTR *lplp				// Text geben lassen
									)
{// Text und Namen zum Script geben lassen, die z.B. in DN_SWITCH gesetzt werden

	ASSERT(lplp);
	ASSERT(uiLen > 0);		// zurückzuliefernder Name und Text des geswitchten SUB's
	ASSERT(lpstrName);
	ASSERT(lpcstrSuperItem);	// Gerade laufendes SUPER
	ASSERT(hScript);			// Gerade zu diesem Script innerhalb SUPER geswitcht

	if (NULL == lpcstrSuperItem) return E_UNEXPECTED;

	// zu diesem Script den Namen geben lassen 
	HRESULT	hr = GetName(lpcstrSuperItem, hScript, lpstrName, uiLen);
	ASSERT('\0' != lpstrName[0]);
	// zu diesem  Script den Text von Platte geben lassen 
	if (SUCCEEDED(hr))
	{
		hr = GetText(lpcstrSuperItem, hScript, lplp);
	}

	return hr;
}

HRESULT CRelScripts::GetItem(
							 LPCSTR lpcstrSuperItem,	// zu diesem SUPER
							 LPCSTR lpcstrEntry,		// zu diesem Entry
							 LPSTR lpstrSubItem,		// Name 
							 UINT uiLen, 
							 ebHSCRIPT *phScript		// Script geben lassen
							 )
{// Thread kein SuperItem mitgegeben
	if (NULL == lpcstrSuperItem) return E_UNEXPECTED;

	ASSERT(lpcstrEntry);
	ASSERT(phScript);
	ASSERT(lpstrSubItem);

	*phScript = NULL;
	lpstrSubItem[0] = '\0';
	// Zu diesem Entry den passenden Script innerhalb des SUPER finden
	HRESULT hr = GetScript(lpcstrSuperItem, lpcstrEntry, phScript);
	if (SUCCEEDED(hr))
	{	// Zu diesem Script den passenden Namen innerhalb des SUPER finden
		hr = GetName(lpcstrSuperItem, *phScript, lpstrSubItem, uiLen);
	}

	return hr;
}

HRESULT CRelScripts::GetScript(LPCSTR lpcstrSuperItem, LPCSTR lpcstrEntry, ebHSCRIPT *phScript)
{
	ASSERT(lpcstrEntry);
	ASSERT(phScript);

	// erstmal für Rückgabe Failed setzen
	HRESULT hr = E_FAIL;
	MapRelScriptsIt it = m_mapRelatedScripts.find(lpcstrSuperItem);

	*phScript = NULL;

	// nicht in der Map aus SUPER-Scriptnamen 
	if (it != m_mapRelatedScripts.end()) 
	{	// Subitem suchen
		long lRunS = (*it).second;// Finden des zugehörigen RunningScripts-Pointers
		CRunScripts *pRunScriptsOrg = (CRunScripts *)lRunS;
		ASSERT(pRunScriptsOrg);
		hr = FindScriptHandle(pRunScriptsOrg, lpcstrEntry, phScript);
	}

	return hr;
}

HRESULT CRelScripts::GetName(LPCSTR lpcstrSuperItem, ebHSCRIPT hCompareScript, LPSTR lpstrSubItem, UINT uiLen)
{
	// erstmal für Rückgabe Failed setzen
	HRESULT hr = E_FAIL;
	MapRelScriptsIt it = m_mapRelatedScripts.find(lpcstrSuperItem);

	lpstrSubItem[0] = '\0';
	// in der Map aus SUPER-Scriptnamen 
	if (it != m_mapRelatedScripts.end()) 
	{	// Subitem suchen
		long lRunS = (*it).second;// Finden des zugehörigen RunningScripts-Pointers
		CRunScripts *pRunScriptsOrg = (CRunScripts *)lRunS;

		if (pRunScriptsOrg) {
			hr = FindScriptName(pRunScriptsOrg, hCompareScript, lpstrSubItem, uiLen);
		}
	}

	return hr;
}
HRESULT CRelScripts::GetText(LPCSTR lpcstrSuperItem, ebHSCRIPT hCompareScript, LPSTR *lplpstr)
{
	// erstmal für Rückgabe Failed setzen
	HRESULT hr = E_FAIL;
	MapRelScriptsIt it = m_mapRelatedScripts.find(lpcstrSuperItem);
	// in der Map aus SUPER-Scriptnamen 
	if (it == m_mapRelatedScripts.end()) return E_FAIL;
	// Subitem suchen
	long lRunS = (*it).second;// Finden des zugehörigen RunningScripts-Pointers
	CRunScripts *pRunScriptsOrg = (CRunScripts *)lRunS;
	if (NULL == pRunScriptsOrg) return E_POINTER;
	
	return FindScriptText(pRunScriptsOrg, hCompareScript, lplpstr);
}
	// SubItem setzen
HRESULT CRelScripts::SetItem (ebHCODE hCode, LPCSTR lpcstrSuperItem, LPCSTR lpcstrSubItem)
{
	ASSERT(lpcstrSuperItem);
	ASSERT(lpcstrSubItem);

	// erstmal für Rückgabe Failed setzen
	HRESULT hr = E_FAIL;
	try
	{
	// nicht in der Map
	MapRelScriptsIt it = m_mapRelatedScripts.find(lpcstrSuperItem);

		if (it == m_mapRelatedScripts.end()) _com_issue_error(E_FAIL);

	// Subitem suchen
	long lRunS = (*it).second;
	CRunScripts *pRunScriptsOrg = (CRunScripts *)lRunS;
	
		ASSERT(pRunScriptsOrg);
		if (NULL == pRunScriptsOrg) _com_issue_error(E_POINTER);
	
	// SUB schon hinzugefügt ?
	WRunningObject IRO;
	
		hr = pRunScriptsOrg -> Find(lpcstrSubItem, IRO.ppi());
	
	// Schon hinzugefügt, dann...
		if (S_OK == hr)	
		{
		// Alte Entries des Scripts löschen (in AddEntries()), und neue eintragen.
			hr = pRunScriptsOrg -> AddEntries(IRO);
		}
		else
		{// zu jedem SubScript einen neuen Script erzeugen
			THROW_FAILED_HRESULT(CreateScript(pRunScriptsOrg, hCode, lpcstrSubItem, IRO.ppi()));
		}
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}

	return hr;
}

HRESULT CRelScripts::CreateObject(REFIID riid, IRunningObject **ppIR)
{// ScriptObjekt erzeugen
	ASSERT(NULL != ppIR);
	if (NULL == ppIR) return E_POINTER; 

	*ppIR = NULL;
	try
	{
	// mmmh: sehr merkwürdig ...

		if (IsEqualIID(riid, CLSID_Script))
		{
			*ppIR = new CComObject<CRunningObject>;
		}
		else if (IsEqualIID(riid, CLSID_FileScript))
		{
			*ppIR = new CComObject<CRunningObjectFile>;
		}
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
HRESULT CRelScripts::SetItems(LPCSTR lpcstrSuper)
{
	ASSERT(lpcstrSuper);
	ASSERT(m_pIObjectManagement);

	HRESULT hr = NOERROR;
	ebHCODE hCode = NULL;
	LPSTR	pText = NULL;
	WRunningObject IRO;
	UINT uiCntRelScripts = 0;
	LPSTR *lplpstrRelScripts = NULL;

	try
	{// ScriptObjekt erzeugen
		THROW_FAILED_HRESULT(CreateObject(CLSID_Script, IRO.ppi()));

	// Management setzen
		IRO -> SetManagement(m_pIObjectManagement, m_pIStreamInfo, CLSID_Script, lpcstrSuper);

	// Code , Text kann nch SetManagement geladen werden, Objekt öffnen
	WObjManHelper IOMH = IRO; // Query...

		THROW_FAILED_HRESULT(IOMH -> Open(&pText, &hCode, &lplpstrRelScripts, uiCntRelScripts, true));

		// In diesem Falle abbrechen
		if (0 == uiCntRelScripts || NULL == lplpstrRelScripts)
			_com_issue_error(S_FALSE);

		for (UINT ui = 0; ui < uiCntRelScripts; ui++) {
		LPSTR lpstrSub = lplpstrRelScripts [ui];
		
			ASSERT(NULL != lpstrSub);
		
		// zum SUPER Gehöriges setzen
			SetItem(NULL, lpcstrSuper, lpstrSub); // Failed nicht berbeiten, mitunter kein Code
		}

	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}

	if (hCode) CoTaskMemFree(hCode); hCode = NULL;
	if (pText) CoTaskMemFree(pText); pText = NULL;
	MEMFREE(lplpstrRelScripts, uiCntRelScripts);
	return hr;
}

// SubItem löschen
HRESULT CRelScripts::DeleteItem (LPCSTR lpcstrSuperItem, LPCSTR lpcstrItem)
{
	ASSERT(lpcstrItem);
	ASSERT(lpcstrSuperItem);

	// Finden des richtigen Superitem-Containers
	MapRelScriptsIt it = m_mapRelatedScripts.find(lpcstrSuperItem);
	// in der Map
	if (it == m_mapRelatedScripts.end()) return E_FAIL;

	long lRunS = (*it).second;
	CRunScripts *pRunScriptsOrg = (CRunScripts *)lRunS;	
	ASSERT(pRunScriptsOrg);
	if (NULL == pRunScriptsOrg) return E_POINTER;
	// Subitem suchen und löschen
	return pRunScriptsOrg -> Delete(lpcstrItem);
}

HRESULT CRelScripts::FindScriptHandle(CRunScripts *pRunScriptsOrg, LPCSTR lpcstrEntry, ebHSCRIPT *phScript)
{
	ASSERT(pRunScriptsOrg);
	ASSERT(phScript);
	ASSERT(lpcstrEntry);
	if (NULL == pRunScriptsOrg || NULL == phScript || NULL == lpcstrEntry) return E_POINTER;

// an dieser Stelle darf zu einem Entry auch nur ein Script vorhanden sein
// (sonst mehrere Scripts zu einem Entry möglich, MULTIMAP !!!)
HRESULT hr = E_FAIL;

	*phScript = NULL;
	pRunScriptsOrg -> Reset();
	try {
	WRunningObject IRO;

		if (S_OK == pRunScriptsOrg -> NextFromEntry (lpcstrEntry, IRO.ppi())) {	// Find first		 
		// Script zu einem Entry gefunden
		WRunningObject IRONext;

		// Überprüfen, ob mehr Scripts zu einem Entry vorhanden
			if (S_OK == pRunScriptsOrg -> NextFromEntry (lpcstrEntry, IRONext.ppi())) {
			// Fehler: Mehr als ein Entry gefunden
				FoundMoreDefinitions(lpcstrEntry);
				_com_issue_error(E_FAIL);
			}

		CebScript *pScript = NULL;
		WBSProperty IBSP = IRO;

			hr = IBSP -> GetScript(&pScript);
			if (FAILED(hr)) _com_issue_error(hr);
			*phScript = pScript -> GetHandle();
		}
	} catch (_com_error& e) {
		hr = _COM_ERROR(e);
	}
	pRunScriptsOrg -> Reset();
	return hr;
}

HRESULT CRelScripts::FindScriptName(CRunScripts *pRunScriptsOrg, ebHSCRIPT hScriptCompare, LPSTR lpstrSubItem, UINT uiLen)
{
	ASSERT(hScriptCompare);
	ASSERT(pRunScriptsOrg);
	ASSERT(lpstrSubItem);
	if (NULL == pRunScriptsOrg || NULL == lpstrSubItem) return E_POINTER;
	if (NULL == hScriptCompare) return E_HANDLE;

	HRESULT hr = NOERROR;
	try
	{// Finden des zugehörigen Dateinamens des SUB-Scriptes
		pRunScriptsOrg -> Reset();

		WRunningObject IRO;
		while (S_OK == pRunScriptsOrg -> NextScriptName (lpstrSubItem, uiLen, IRO.ppi()))
		{
			WBSProperty IBSP = IRO;
			CebScript *pScript = NULL;
			hr = IBSP -> GetScript(&pScript);
			if (FAILED (hr)) _com_issue_error(hr);
			if (hScriptCompare == pScript -> GetHandle())	// gefunden
				break;
		}
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	pRunScriptsOrg -> Reset();
	return hr;
}

HRESULT CRelScripts::FindScriptText(CRunScripts *pRunScriptsOrg, ebHSCRIPT hScriptCompare, LPSTR *lplpstr)
{
	ASSERT(hScriptCompare);
	ASSERT(pRunScriptsOrg);
	ASSERT(lplpstr);
	if (NULL == pRunScriptsOrg || NULL == lplpstr) return E_POINTER;
	if (NULL == hScriptCompare) return E_HANDLE;

	HRESULT hr = S_OK;
	ebHCODE hCode = NULL;
	LPSTR	pText = NULL;
	UINT uiCntRelScripts = 0;
	LPSTR *lplpstrRelScripts = NULL;
	char strSubItem [_MAX_PATH];

	*lplpstr = NULL;

	try
	{
		pRunScriptsOrg -> Reset();
		// Finden des zugehörigen Textes des SUB-Scriptes
		WRunningObject IRO;
		while (S_OK == pRunScriptsOrg -> NextScriptName (strSubItem, _MAX_PATH, IRO.ppi()))
		{// Solange enumerieren, bis Script übereinstimmt
			CebScript *pScript = NULL;
			WBSProperty IBSP = IRO;
			hr = IBSP -> GetScript(&pScript);
			if (FAILED(hr)) _com_issue_error(hr);
			if (hScriptCompare == pScript -> GetHandle())	// gefunden
			{// Code , Text kann nch SetManagement geladen werden, Objekt öffnen
				WObjManHelper IOMH = IRO; // Query...
				hr = IOMH -> Open(&pText, &hCode, &lplpstrRelScripts, uiCntRelScripts, false);
				if (FAILED(hr)) _com_issue_error(hr);
				break;
			}
		}		
		*lplpstr = pText;
	}
	catch(_com_error& e)
	{
		if (pText) CoTaskMemFree	(pText); pText = NULL; 
		hr = _COM_ERROR(e);
	}
	if (hCode) CoTaskMemFree	(hCode); hCode = NULL;
	MEMFREE(lplpstrRelScripts, uiCntRelScripts);

	pRunScriptsOrg -> Reset();	

	return hr;
}

bool CRelScripts::FoundMoreDefinitions(LPCSTR lpcstrEntry)
{
	ASSERT(lpcstrEntry);

	CString strCaption = GetDefaultName(IDS_LONGCLASSNAME);
	CString strTemplate = GetDefaultName(IDS_MORETHANONEDEF);
	char Prompt[MAXSTRLENGTH];
	HWND hWnd = ::GetActiveWindow();
	ASSERT(hWnd);

	wsprintf(Prompt, strTemplate, lpcstrEntry);

	return ::MessageBox(hWnd, Prompt, strCaption, MB_OK | MB_TASKMODAL);
}