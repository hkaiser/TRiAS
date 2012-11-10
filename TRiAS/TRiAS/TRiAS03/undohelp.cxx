// Verwaltung von Undo/Redo ---------------------------------------------------
// File: UNDOHELP.CXX

#include "trias03p.hxx"

#include "trias03.h"		// ResourceID's

#include <containr.hxx>

#include <undoguid.h>		// GUID

#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>		// Enumerator
#include <undoredo.hxx>		// Klassendeklaration
#include <undohelp.hxx>		// gesamte Undo/Redo Verwaltung

extern char g_pDLLName[_MAX_PATH];

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CManageUndoRedo :: CManageUndoRedo (void)
{
	m_pUndoList = NULL;
	m_pRedoList = NULL;
	m_iCurrPos = 0;
	memset (m_rgLists, '\0', sizeof(LPUNDOREDOLIST)*MAXUNDOREDOLISTS);
}

CManageUndoRedo :: ~CManageUndoRedo (void)
{
	m_pUndoList -> Release();
	m_pRedoList -> Release();

	for (short i = 0; i < MAXUNDOREDOLISTS; i++) {
		if (m_rgLists[i]) {
			m_rgLists[i] -> Release(); 
			m_rgLists[i] = NULL;
		}
	}
}

CManageUndoRedo *CManageUndoRedo :: CreateInstance (int iCnt)
{
CManageUndoRedo *pMUndo = new CManageUndoRedo();

	if (pMUndo == NULL || !pMUndo -> FInit(iCnt)) {
		DELETE_OBJ (pMUndo);
		return NULL;
	}

return pMUndo;
}

bool CManageUndoRedo :: FInit (int iCnt)
{
ResourceFile RF (g_pDLLName);

	m_pUndoList = CUndoRedoList :: CreateInstance (ResString (ResID (IDS_GLOBALUNDOLIST, &RF), 40), iCnt);
	m_pRedoList = CUndoRedoList :: CreateInstance (ResString (ResID (IDS_GLOBALREDOLIST, &RF), 40), iCnt);
	if (m_pUndoList == NULL || m_pRedoList == NULL)
		return false;

// Stack initialisieren
	m_rgLists[0] = m_pUndoList;	// vordefiniertes komplexes Undo
	m_rgLists[0] -> AddRef();
	m_iCurrPos = 0;

return true;
}

void CManageUndoRedo :: EveryDelete (void)
{
	m_pUndoList -> EveryDelete();
	m_pRedoList -> EveryDelete();

	for (short i = 1; i < MAXUNDOREDOLISTS; i++) {
		if (m_rgLists[i]) {
			m_rgLists[i] -> Release(); 
			m_rgLists[i] = NULL;
		}
	}
}

// Eigentliche funktionalen member --------------------------------------------
// neues Undo hinzufügen 
HRESULT CManageUndoRedo :: AddUndo (LPUNKNOWN pIUnk)
{
	TX_ASSERT (TIsValidIUnknown (pIUnk));

LPUNDOREDO pIUndo;
HRESULT hr = pIUnk -> QueryInterface (IID_IUndoRedo, (LPVOID *)&pIUndo);
	
	if (SUCCEEDED(hr)) {
		TX_ASSERT(m_iCurrPos < MAXUNDOREDOLISTS);

		hr = m_rgLists[m_iCurrPos] -> AddUndoRedo (pIUndo);
 		if (SUCCEEDED(hr) && m_iCurrPos == 0) 
 			m_pRedoList -> EveryDelete();	// RedoListe löschen
		
		pIUndo -> Release();
	}

return hr;
}

HRESULT CManageUndoRedo :: BeginUndoLevel (LPCTSTR pDesc)
{
	TX_ASSERT(TIsValidString (pDesc));

	if (m_iCurrPos+1 >= MAXUNDOREDOLISTS) return ResultFromScode (E_FAIL);

LPUNDOREDOLIST pIUndoList = CUndoRedoList :: CreateInstance (pDesc, -1);

	if (pIUndoList == NULL)
		return ResultFromScode (E_OUTOFMEMORY);
	
	m_rgLists[++m_iCurrPos] = pIUndoList;	// AddRef wird übernommen

return NOERROR;
}

HRESULT CManageUndoRedo :: BeginUndoLevel (LPUNKNOWN pIUnk)
{
	TX_ASSERT (TIsValidIUnknown (pIUnk));

	if (m_iCurrPos+1 >= MAXUNDOREDOLISTS) return ResultFromScode (E_FAIL);

LPUNDOREDOLIST pIUndoList;
HRESULT hr = pIUnk -> QueryInterface (IID_IUndoRedoList, (LPVOID *)&pIUndoList);

	if (FAILED(hr)) return hr;
	
	m_rgLists[++m_iCurrPos] = pIUndoList;	// AddRef wird übernommen

return NOERROR;
}

HRESULT CManageUndoRedo :: EndUndoLevel (void)
{
	if (m_iCurrPos <= 0) return ResultFromScode (E_FAIL);

LPUNDOREDOLIST &rpIUndoList = m_rgLists[m_iCurrPos--];
HRESULT hr = m_rgLists[m_iCurrPos] -> AddUndoRedo (rpIUndoList);

 	if (SUCCEEDED(hr) && m_iCurrPos == 0) 	// wieder im ersten level
 		m_pRedoList -> EveryDelete();		// RedoListe löschen
	
	rpIUndoList -> Release();
	rpIUndoList = NULL;
	return hr;
}

HRESULT CManageUndoRedo :: CancelUndoLevel (bool fUndoExisting)
{
	if (m_iCurrPos <= 0) return ResultFromScode (E_FAIL);

// einfach den gesamten Eintrag vergessen (zerlegt sich selbst)
LPUNDOREDOLIST &rpIUndoList = m_rgLists[m_iCurrPos--];

	if (fUndoExisting)
		static_cast<IUndoRedo *>(rpIUndoList) -> Undo();

	rpIUndoList -> Release();
	rpIUndoList = NULL;
	return NOERROR;
}


// alle geforderten Undo's abarbeiten und in RedoListe hängen
HRESULT CManageUndoRedo :: Undo (LONG lNum)
{
	return m_pUndoList -> Undo (lNum, m_pRedoList);
}

// alle geforderten Redo's abarbeiten und in UndoListe hängen
HRESULT CManageUndoRedo :: Redo (LONG lNum)
{
	return m_pRedoList -> Redo (lNum, m_pUndoList);
}

// Liste der aktuellen Undo's liefern
HRESULT CManageUndoRedo :: GetUndoList (LPENUMUNKNOWN *ppUndos)
{
	return m_pUndoList -> Clone (ppUndos);
}

// Liste der aktuellen Redo's liefern
HRESULT CManageUndoRedo :: GetRedoList (LPENUMUNKNOWN *ppRedos)
{
	return m_pRedoList -> Clone (ppRedos);
}

// nächstes verfügbares Undo liefern
DWORD CManageUndoRedo :: GetNextUndoDesc (LPTSTR *pDesc)
{
LPENUMUNKNOWN pEnum;
HRESULT hr = m_pUndoList -> Clone (&pEnum);
DWORD dwCap = UNDOREDOCAPS_NOFLAGS;
LPUNDOREDO pIUndo;

	if (FAILED(hr)) return hr;

	pEnum -> Reset();
	if (pEnum -> Next (1, (LPUNKNOWN *)&pIUndo, NULL) == S_OK) {
	// Capabilities des ersten Undo's abfragen
		dwCap = pIUndo -> Capabilities ((signed char **)pDesc);
		pIUndo -> Release();
	}
	pEnum -> Release();

return dwCap;
}

// nächstes verfügbares Redo liefern
DWORD CManageUndoRedo :: GetNextRedoDesc (LPTSTR *pDesc)
{
LPENUMUNKNOWN pEnum;
HRESULT hr = m_pRedoList -> Clone (&pEnum);
DWORD dwCap = UNDOREDOCAPS_NOFLAGS;
LPUNDOREDO pIRedo;

	if (FAILED(hr)) return hr;

	pEnum -> Reset();
	if (pEnum -> Next (1, (LPUNKNOWN *)&pIRedo, NULL) == S_OK) {
	// Capabilities des ersten Redo's abfragen
		dwCap = pIRedo -> Capabilities ((signed char **)pDesc);
		pIRedo -> Release();
	}
	pEnum -> Release();

return dwCap;
}

