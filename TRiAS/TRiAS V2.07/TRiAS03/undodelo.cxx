// Undo/Redo für Objekt löschen -----------------------------------------------
// File: UNDODELO.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "ObjGeomW.h"
#include "undodelo.hxx"

extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoDeleteObject :: CUndoRedoDeleteObject (LPFNDESTROYED pfnDestroy)
		       : m_pfnDestroy (pfnDestroy)
{
	m_dwRefCnt = 0L;
	m_fRect = false;
}

CUndoRedoDeleteObject :: ~CUndoRedoDeleteObject (void)
{
}

BOOL CUndoRedoDeleteObject :: FInit (LONG lONr, LPCRECT prc)
{
// Member initialisieren
	if (prc) {
		m_rcObj = *prc;
		m_fRect = true;
	} else
		m_fRect = false;

// Objekt hier zwischenspeichern
	if (!m_ogObj.FillObjGeometrie(lONr))
		return false;

	Initialized();

return true;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoDeleteObject :: Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_UNDODELETEOBJECT, &RF), 128);

		*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf (*pDesc, resUndo.Addr(), m_ogObj.lONr);
	}

return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoDeleteObject :: Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt wieder erzeugen
	m_ogObj.lONr = 0L;
	m_ogObj.iFlags |= (OGNewObject|OGForceGeometry);
	if (DEX_ModObjGeometrie (m_ogObj)) {
		if (m_fRect) DEX_RePaintRect (m_rcObj);
		return NOERROR;
	}

return ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoDeleteObject :: Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt wieder löschen
	if (DEX_DeleteObject (m_ogObj.lONr)) {
		if (m_fRect) DEX_RePaintRect (m_rcObj);
		return NOERROR;
	}

return ResultFromScode (S_FALSE);
}

// *** IUndoRedoDeleteText *** ------------------------------------------------
STDMETHODIMP CUndoRedoDeleteObject :: Init (LONG lONr, LPCRECT prc)
{
	return FInit (lONr, prc) ? NOERROR : ResultFromScode (S_FALSE);
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoDeleteObject :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoDeleteObject) 
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

STDMETHODIMP_(ULONG) CUndoRedoDeleteObject :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoDeleteObject :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

