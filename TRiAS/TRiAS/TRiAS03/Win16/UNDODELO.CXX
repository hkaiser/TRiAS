// Undo/Redo für Objekt löschen -----------------------------------------------
// File: UNDODELO.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "undodelo.hxx"

extern char g_pDLLName[260];

// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoDeleteObject :: CUndoRedoDeleteObject (LPFNDESTROYED pfnDestroy)
		       : m_pfnDestroy (pfnDestroy)
{
	INITSTRUCT (m_ogObj, OBJGEOMETRIE);
	m_dwRefCnt = 0L;
	m_fRect = false;
}

CUndoRedoDeleteObject :: ~CUndoRedoDeleteObject (void)
{
	DELETE (m_ogObj.pdblX);
	DELETE (m_ogObj.pdblY);
	DELETE (m_ogObj.plCnt);
}

bool CUndoRedoDeleteObject :: FInit (LONG lONr, LPCRECT prc)
{
// Member initialisieren
	m_ogObj.lONr = lONr;
	if (prc) {
		m_rcObj = *prc;
		m_fRect = true;
	} else
		m_fRect = false;

// Objekt hier zwischenspeichern
	if (!DEX_GetObjStatistik (m_ogObj)) 
		return false;

	m_ogObj.pdblX = new double [m_ogObj.lCnt];
	m_ogObj.pdblY = new double [m_ogObj.lCnt];
	if (m_ogObj.pdblX == NULL || m_ogObj.pdblY == NULL)
		return false;

	if (m_ogObj.iKCnt > 0) {
		if (m_ogObj.iObjTyp == OGFlaeche) {
			m_ogObj.plCnt = new long [m_ogObj.iKCnt];
			if (m_ogObj.plCnt == NULL) 
				return false;
		} else if (m_ogObj.iObjTyp == OGText) {
			((TEXTGEOMETRIE &)m_ogObj).pText = new char [m_ogObj.iKCnt+1];
			if (((TEXTGEOMETRIE &)m_ogObj).pText == NULL) 
				return false;
		}
	}

	if (!DEX_GetObjGeometrie (m_ogObj))
		return false;

	if (m_ogObj.iObjTyp == OGText) {
	// Text des Textes besorgen
	TCHAR cbBuffer[_MAX_PATH+1];
	GETTEXTDATA td;

		memset (&td, '\0', sizeof(GETTEXTDATA));
		td.m_dwSize = sizeof (GETTEXTDATA);
		td.m_lONr = lONr;
		td.m_pText = cbBuffer;
		td.m_iLen = _MAX_PATH;
		if (!DEX_GetTextObjectText(td))
			return false;

		m_strText = cbBuffer;
		((TEXTGEOMETRIE &)m_ogObj).pText = (char *)m_strText.c_str();
	}

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
	m_ogObj.iFlags |= OGNewObject;
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
	    riid == IID_IUndoRedoDeleteObject) {
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

