// Undo/Redo für Objekt aus OR-Fenster entfernen ------------------------------
// File: UNDOHWND.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "undohwnd.hxx"

extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisierung 
CUndoRedoDeleteObjectWnd::CUndoRedoDeleteObjectWnd (LPFNDESTROYED pfnDestroy)
			  : m_pfnDestroy(pfnDestroy), m_hWnd (NULL), m_lONr(-1L)
{
	m_dwRefCnt = 0L;
	m_fSelected = false;
	m_fActivated = false;
}

CUndoRedoDeleteObjectWnd::~CUndoRedoDeleteObjectWnd (void)
{
	// nothing else to do
}

BOOL CUndoRedoDeleteObjectWnd::FInit (HWND hWnd, LONG lONr)
{
	if (!IsWindow (hWnd) || lONr == -1L) return false;

	m_hWnd = hWnd;
	m_lONr = lONr;

// RechercheStaus abfragen
RECHOBJECT ro;

	INITSTRUCT (ro, RECHOBJECT);
	ro.lONr = m_lONr;
	DEXOR_QueryRechercheStatus (m_hWnd, ro);

	if (!(ro.iFlags & RSListed)) return false;	// nicht in ORFenster

// RechercheStaus merken
	m_fSelected = (ro.iFlags & RSSelected) ? true : false;
	m_fActivated = (ro.iFlags & RSActivated) ? true : false;

	Initialized();
	return true;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoDeleteObjectWnd::Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_DELETEOBJHWND, &RF), 128);

		*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf (*pDesc, resUndo.Addr(), m_lONr);
	}

return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoDeleteObjectWnd::Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt in Recherchefenster einbauen
	if (!IsWindow (m_hWnd)) return ResultFromScode (E_UNEXPECTED);

	DEXOR_AddObjectToList (m_hWnd, m_lONr);
	if (m_fSelected) 
		DEXOR_SelectObject (m_hWnd, m_lONr);
	if (m_fActivated) 
		DEXOR_ActivateObject (m_hWnd, m_lONr);
	return NOERROR;
}

STDMETHODIMP CUndoRedoDeleteObjectWnd::Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt wieder aus Recherchefenster entfernen
	if (!IsWindow (m_hWnd)) return ResultFromScode (E_UNEXPECTED);

	if (DEXOR_RemoveFromListObject (m_hWnd, m_lONr))
		return NOERROR;

	return ResultFromScode (S_FALSE);
}

// *** IUndoRedoDeleteObjectWnd *** -------------------------------------------
STDMETHODIMP CUndoRedoDeleteObjectWnd::Init (HWND hWnd, LONG lONr)
{
	return FInit (hWnd, lONr) ? NOERROR : ResultFromScode (S_FALSE);
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoDeleteObjectWnd::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoDeleteObjectWnd) 
	{
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

STDMETHODIMP_(ULONG) CUndoRedoDeleteObjectWnd::AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoDeleteObjectWnd::Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}
	return m_dwRefCnt;
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisieriung 
CUndoRedoReplaceObjectWnd::CUndoRedoReplaceObjectWnd (LPFNDESTROYED pfnDestroy)
			  : m_pfnDestroy(pfnDestroy), m_hWnd (NULL), m_lONr(-1L), m_lNewONr(-1L)
{
	m_dwRefCnt = 0L;
}

CUndoRedoReplaceObjectWnd::~CUndoRedoReplaceObjectWnd (void)
{
	// nothing else to do
}

BOOL CUndoRedoReplaceObjectWnd::FInit (HWND hWnd, LONG lONr, LONG lNewONr)
{
	if (!IsWindow (hWnd) || lONr == -1L || -1L == lNewONr) 
		return false;

	m_hWnd = hWnd;
	m_lONr = lONr;
	m_lNewONr = lNewONr;

	Initialized();
	return true;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoReplaceObjectWnd::Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_REPLACEOBJHWND, &RF), 128);

		*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf (*pDesc, resUndo.Addr(), m_lONr, m_lNewONr);
	}
	return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoReplaceObjectWnd::Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt in Recherchefenster einbauen
	if (!IsWindow (m_hWnd)) return ResultFromScode (E_UNEXPECTED);

REPLACEOBJECT RO;

	INITSTRUCT(RO, REPLACEOBJECT);
	RO.lONr = m_lNewONr;
	RO.lNewONr = m_lONr;

	DEXOR_ReplaceObjectInList (m_hWnd, RO);
	return NOERROR;
}

STDMETHODIMP CUndoRedoReplaceObjectWnd::Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt wieder aus Recherchefenster entfernen
	if (!IsWindow (m_hWnd)) return ResultFromScode (E_UNEXPECTED);

REPLACEOBJECT RO;

	INITSTRUCT(RO, REPLACEOBJECT);
	RO.lONr = m_lONr;
	RO.lNewONr = m_lNewONr;

	DEXOR_ReplaceObjectInList (m_hWnd, RO);
	return S_OK;
}

// *** IUndoRedoReplaceObjectWnd *** ------------------------------------------
STDMETHODIMP CUndoRedoReplaceObjectWnd::Init (HWND hWnd, LONG lONr, LONG lNewONr)
{
	return FInit (hWnd, lONr, lNewONr) ? NOERROR : ResultFromScode (S_FALSE);
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoReplaceObjectWnd::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoReplaceObjectWnd) 
	{
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

STDMETHODIMP_(ULONG) CUndoRedoReplaceObjectWnd::AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoReplaceObjectWnd::Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}
	return m_dwRefCnt;
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisierung 
CUndoRedoAddToObjectWnd::CUndoRedoAddToObjectWnd (LPFNDESTROYED pfnDestroy)
			  : m_pfnDestroy(pfnDestroy), m_hWnd (NULL), m_lONr(-1L)
{
	m_dwRefCnt = 0L;
	m_fSelected = false;
	m_fActivated = false;
}

CUndoRedoAddToObjectWnd::~CUndoRedoAddToObjectWnd (void)
{
	// nothing else to do
}

BOOL CUndoRedoAddToObjectWnd::FInit (HWND hWnd, LONG lONr)
{
	if (!IsWindow (hWnd) || lONr == -1L) return false;

	m_hWnd = hWnd;
	m_lONr = lONr;

// RechercheStaus abfragen
RECHOBJECT ro;

	INITSTRUCT (ro, RECHOBJECT);
	ro.lONr = m_lONr;
	DEXOR_QueryRechercheStatus (m_hWnd, ro);

	if (!(ro.iFlags & RSListed)) return false;	// nicht in ORFenster

// RechercheStaus merken
	m_fSelected = (ro.iFlags & RSSelected) ? true : false;
	m_fActivated = (ro.iFlags & RSActivated) ? true : false;

	Initialized();
	return true;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoAddToObjectWnd::Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_ADDTOOBJHWND, &RF), 128);

		*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf (*pDesc, resUndo.Addr(), m_lONr);
	}
	return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoAddToObjectWnd::Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt in Recherchefenster einbauen
	if (!IsWindow (m_hWnd)) return ResultFromScode (E_UNEXPECTED);

	if (DEXOR_RemoveFromListObject (m_hWnd, m_lONr))
		return NOERROR;

	return ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoAddToObjectWnd::Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt wieder aus Recherchefenster entfernen
	if (!IsWindow (m_hWnd)) return ResultFromScode (E_UNEXPECTED);

	DEXOR_AddObjectToList (m_hWnd, m_lONr);
	if (m_fSelected) 
		DEXOR_SelectObject (m_hWnd, m_lONr);
	if (m_fActivated) 
		DEXOR_ActivateObject (m_hWnd, m_lONr);
	return NOERROR;
}

// *** IUndoRedoAddToObjectWnd *** -------------------------------------------
STDMETHODIMP CUndoRedoAddToObjectWnd::Init (HWND hWnd, LONG lONr)
{
	return FInit (hWnd, lONr) ? NOERROR : ResultFromScode (S_FALSE);
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoAddToObjectWnd::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoAddToObjectWnd) 
	{
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

STDMETHODIMP_(ULONG) CUndoRedoAddToObjectWnd::AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoAddToObjectWnd::Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}
	return m_dwRefCnt;
}

