// Implementation des IUndoRedo (BasisKlasse) ---------------------------------
// File: UNDOREDO.CXX

#include "trias03p.hxx"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für UndoRedo ---------------------------------------------------
CUndoRedo :: CUndoRedo (REFIID riid, LPFNDESTROYED pfnDestroy)
	   : m_IID (riid), m_pfnDestroy(pfnDestroy)
{
	m_dwRefCnt = 0L;
	m_fInitialized = false;
}

CUndoRedo :: ~CUndoRedo (void)
{
	// nothing to do
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedo :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || riid == m_IID) {
	// Someone is asking us for our controlling IUnknown.
	// CUndoRedo is that IUnknown, so "this" is the answer.
		*ppvObj = this;
	} else {
	// They must have asked for another interface -- something
	// we don't support.  Report the error.
		*ppvObj = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}

// If execution reached this point then no error occurred.
	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CUndoRedo :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedo :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

// *** IUndoRedo methods *** --------------------------------------------------
STDMETHODIMP_(DWORD) CUndoRedo :: Capabilities (LPTSTR *pDesc)
{
	if (pDesc) *pDesc = NULL;

return UNDOREDOCAPS_NOFLAGS;
}

STDMETHODIMP CUndoRedo :: Undo (void)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CUndoRedo :: Redo (void)
{
	return ResultFromScode (E_NOTIMPL);
}


///////////////////////////////////////////////////////////////////////////////
// UndoRedoListe --------------------------------------------------------------
//
// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoList :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoList) 
	{
	// Someone is asking us for our controlling IUnknown.
	// CUndoRedo is that IUnknown, so "this" is the answer.
		*ppvObj = this;
	} else if (riid == IID_IEnumUnknown) {
	// someone is asking us for our enumerator, so m_pUndoList is the answer
		*ppvObj = &m_UndoList;
	} else {
	// They must have asked for another interface -- something
	// we don't support.  Report the error.
		*ppvObj = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}

// If execution reached this point then no error occurred.
	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CUndoRedoList :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoList :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CUndoRedoList *CUndoRedoList :: CreateInstance (LPCTSTR pDesc, int iCnt)
{
CUndoRedoList *pList = new CUndoRedoList (pDesc, iCnt);

	if (pList == NULL || !pList -> FInit()) {
		DELETE_OBJ(pList);
		return NULL;
	}
	pList -> AddRef();

return pList;
}

#pragma warning (disable: 4355)

CUndoRedoList :: CUndoRedoList (LPCTSTR pDesc, int iCnt)
	       : m_strDesc (pDesc), m_UndoList (this, iCnt)
{
	m_dwRefCnt = 0;
	m_dwCaps = UNDOREDOCAPS_CANREDO|UNDOREDOCAPS_CANUNDO;
}

#pragma warning (default: 4355)

CUndoRedoList :: ~CUndoRedoList (void)
{
}

BOOL CUndoRedoList :: FInit (void) { return true; }

///////////////////////////////////////////////////////////////////////////////
// *** IUndoRedo members ***
// Undo/Redo arbeitet nacheinander alle gespeicherten Undo's/Redo's ab --------
STDMETHODIMP CUndoRedoList :: Undo (void) 
{
	return Undo(-1, NULL) != UNDOREDOCAPS_NOFLAGS ? NOERROR : ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoList :: Redo (void) 
{ 
	return Redo(-1, NULL) != UNDOREDOCAPS_NOFLAGS ? NOERROR : ResultFromScode (S_FALSE);
}

STDMETHODIMP_(DWORD) CUndoRedoList :: Capabilities (LPTSTR *pDesc)
{
// gespeichertes String kopieren
	if (Count() == 1) {	// wenn nur ein Element, dann dessen Beschreibung liefern
	LPENUMUNKNOWN pEnum;
	HRESULT hr = m_UndoList.Clone (&pEnum);

		if (SUCCEEDED(hr)) {
		DWORD dwT = UNDOREDOCAPS_NOFLAGS;
		LPUNDOREDO pIUndo;

			pEnum -> Reset();
			if (pEnum -> Next (1, (LPUNKNOWN *)&pIUndo, NULL) == S_OK) {
			// Caps des ersten  UnterUndo abfragen
				dwT = pIUndo -> Capabilities (pDesc);
				pIUndo -> Release();
			}
			pEnum -> Release();
			if (dwT != UNDOREDOCAPS_NOFLAGS)
				return dwT;	// ok, Caps des ersten Elements
		}
	} 

	if (pDesc) {
	// ansonsten allgemeine Beschreibung liefern
		*pDesc = (LPTSTR)CoTaskMemAlloc (m_strDesc.length()+1);
		if (*pDesc) strcpy (*pDesc, m_strDesc.c_str());
	}

return m_dwCaps | UNDOREDOCAPS_MULTILEVEL;	// immer multilevel
}

///////////////////////////////////////////////////////////////////////////////
// *** IUndoRedoList members ***
STDMETHODIMP CUndoRedoList :: AddUndoRedo (LPUNDOREDO pIUndoRedo)
{
	if (m_UndoList.AddUnknown (pIUndoRedo)) {
		m_dwCaps = CombineCaps (m_dwCaps, pIUndoRedo -> Capabilities (NULL));
		return NOERROR;
	}

return ResultFromScode (E_OUTOFMEMORY);
}

STDMETHODIMP_(DWORD) CUndoRedoList :: Undo (LONG lNum, LPUNDOREDOLIST pIRedos)
{
DWORD dwCaps = UNDOREDOCAPS_NOFLAGS;

	if (lNum == -1L) lNum = m_UndoList.Count();
	if (lNum == 0) return UNDOREDOCAPS_NOFLAGS;

LPUNDOREDO pIUndo = NULL;
LPENUMUNKNOWN pEnum;
HRESULT hr = m_UndoList.Clone (&pEnum);

	if (FAILED(hr)) return UNDOREDOCAPS_NOFLAGS;

// alle gespeicherten Undo's abarbeiten
	pEnum -> Reset();
	while (pEnum -> Next (1, (LPUNKNOWN *)&pIUndo, NULL) == S_OK) {
	// Undo für dieses konkrete UnterUndo ausführen
		dwCaps = CombineCaps (dwCaps, pIUndo -> Capabilities (NULL));

		pIUndo -> Undo();
		if (pIRedos) { 	// evtl. als Redo merken
			pIRedos -> AddUndoRedo (pIUndo);
			m_UndoList.DeleteLast();	// letztes herauslöschen
		}
		pIUndo -> Release();

	// wenn alles abgearbeitet ist, dann abbrechen
		if (--lNum <= 0) break;
	}
	pEnum -> Release();

return dwCaps;
}

STDMETHODIMP_(DWORD) CUndoRedoList :: Redo (LONG lNum, LPUNDOREDOLIST pIUndos)
{
DWORD dwCaps = UNDOREDOCAPS_NOFLAGS;

	if (!(m_dwCaps & UNDOREDOCAPS_CANREDO)) 
		return UNDOREDOCAPS_NOFLAGS;

	if (lNum == -1L) lNum = m_UndoList.Count();
	if (lNum == 0) return UNDOREDOCAPS_NOFLAGS;

LPUNDOREDO pIRedo = NULL;
LPENUMUNKNOWN pEnum;
HRESULT hr = m_UndoList.Clone (&pEnum);

	if (FAILED(hr)) return UNDOREDOCAPS_NOFLAGS;

// wenn Redo's nicht als Undo's gespeichert werden sollen, dann muß die 
// Reihenfolge der Redo's umgekehrt werden (alle abarbeiten)
	if (pIUndos == NULL) {
	// umgekehrte Abarbeitungsreihenfolge
	ULONG lCnt = Count();

		while (lCnt > 0) {
			pEnum -> Reset();			// rücksetzen
			if (FAILED(pEnum -> Skip (lCnt-1)))	// positionieren
				break;	// E_UNEXPECTED

			if (FAILED(pEnum -> Next (1, (LPUNKNOWN *)&pIRedo, NULL)))
				break;	// E_UNEXPECTED

			dwCaps = CombineCaps (dwCaps, pIRedo -> Capabilities (NULL));
			pIRedo -> Redo();
			pIRedo -> Release();

			lCnt--;		// nächstes Undo/Redo
		}
		pEnum -> Release();
		return dwCaps;
	}

// in normaler Abarbeitungsreihenfolge alle gespeicherten Redo's abarbeiten
	pEnum -> Reset();
	while (pEnum -> Next (1, (LPUNKNOWN *)&pIRedo, NULL) == S_OK) {
	// Undo für dieses konkrete UnterRedo ausführen
		dwCaps = CombineCaps (dwCaps, pIRedo -> Capabilities (NULL));
		pIRedo -> Redo();
		if (pIUndos) { 	// evtl. als Redo merken
			pIUndos -> AddUndoRedo (pIRedo);
			m_UndoList.DeleteLast();	// letztes herauslöschen
		}
		pIRedo -> Release();

	// wenn alles abgearbeitet ist, dann abbrechen
		if (--lNum <= 0) break;
	}
	pEnum -> Release();

return dwCaps;
}

STDMETHODIMP_(ULONG) CUndoRedoList :: Count (void) 
{ 
	return m_UndoList.Count(); 
}

// diverse Helper -------------------------------------------------------------
void CUndoRedoList :: EveryDelete (void) 
{ 
	m_UndoList.EveryDelete(); 
}

HRESULT CUndoRedoList :: Clone (LPENUMUNKNOWN *ppEnum) 
{ 
	return m_UndoList.Clone (ppEnum); 
}


