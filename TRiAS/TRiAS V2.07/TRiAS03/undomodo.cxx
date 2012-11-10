// Undo/Redo für ObjektGeometrie modifzieren-----------------------------------
// File: UNDOMODO.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "ObjGeomW.h"
#include "undomodo.hxx"

extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoModifyObject :: CUndoRedoModifyObject (LPFNDESTROYED pfnDestroy)
		       : m_pfnDestroy (pfnDestroy)
{
	m_dwRefCnt = 0L;
	m_fRect = false;
}

CUndoRedoModifyObject :: ~CUndoRedoModifyObject (void)
{
}

BOOL CUndoRedoModifyObject :: FInit (LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc)
{
// Member initialisieren
	if (prc) {
		m_rcObj = *prc;
		m_fRect = true;
	} else
		m_fRect = false;

	try {
	// Objekt hier zwischenspeichern
		if (!m_ogOld.FillObjGeometrie(lONr))
			return false;

	// neue Geometrie kopieren
		m_ogNew = *pOGNew;		// throws bad_alloc

	} catch (...) {
		return false;
	}

// alles ok, raus hier
	Initialized();

return true;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoModifyObject :: Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_UNDOMODIFYOBJECT, &RF), 128);

		*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf (*pDesc, resUndo.Addr(), m_ogOld.lONr);
	}

DWORD dwFlags = UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;

	if (!m_fRect) dwFlags |= UNDOREDOCAPS_REPAINT;

return dwFlags;
}

STDMETHODIMP CUndoRedoModifyObject :: Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt wiederherstellen
	m_ogOld.iFlags |= (OGModObject|OGForceGeometry);
	if (DEX_ModObjGeometrie (m_ogOld)) {
		if (m_fRect) DEX_RePaintRect (m_rcObj);
		return NOERROR;
	}

return ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoModifyObject :: Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt wieder neu machen
	m_ogNew.iFlags |= (OGModObject|OGForceGeometry);
	if (DEX_ModObjGeometrie (m_ogNew)) {
		if (m_fRect) DEX_RePaintRect (m_rcObj);
		return NOERROR;
	}

return ResultFromScode (S_FALSE);
}

// *** IUndoRedoDeleteText *** ------------------------------------------------
STDMETHODIMP CUndoRedoModifyObject :: Init (LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc)
{
	return FInit (lONr, pOGNew, prc) ? NOERROR : ResultFromScode (S_FALSE);
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoModifyObject :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoModifyObject) {
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

STDMETHODIMP_(ULONG) CUndoRedoModifyObject :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoModifyObject :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

