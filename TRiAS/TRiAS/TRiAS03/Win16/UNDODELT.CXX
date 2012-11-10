// Undo/Redo für TextObjekt löschen -------------------------------------------
// File: UNDODELT.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "undodelt.hxx"

extern char g_pDLLName[260];

// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoDeleteTextObject :: CUndoRedoDeleteTextObject (LPFNDESTROYED pfnDestroy)
			   : m_pfnDestroy (pfnDestroy)
{
	m_dwRefCnt = 0L;
	INITSTRUCT (m_tgText, TEXTGEOMETRIE);
	m_fRect = false;
}

CUndoRedoDeleteTextObject :: ~CUndoRedoDeleteTextObject (void)
{
	// nothing else to do
}

bool CUndoRedoDeleteTextObject :: FInit (LONG lONr, LPCRECT prc)
{
// member initialisieren
	m_tgText.lONr = lONr;
	m_tgText.pdblX = (void *)&m_ptlText.x;
	m_tgText.pdblY = (void *)&m_ptlText.y;
	if (prc) {
		m_rcText = *prc;
		m_fRect = true;
	} else
		m_fRect = false;

// TextObjekt hier zwischenspeichern
	if (!DEX_GetObjStatistik (m_tgText)) 
		return false;

	if (!DEX_GetObjGeometrie (m_tgText))
		return false;

// Text des Textes besorgen
TCHAR cbBuffer[_MAX_PATH+1];
GETTEXTDATA td;

	memset (&td, '\0', sizeof(GETTEXTDATA));
	td.m_dwSize = sizeof (GETTEXTDATA);
	td.m_lONr = m_tgText.lONr;
	td.m_pText = cbBuffer;
	td.m_iLen = _MAX_PATH;
	if (!DEX_GetTextObjectText(td))
		return false;

	m_strText = cbBuffer;
	m_tgText.pText = (char *)m_strText.c_str();

	Initialized();

return true;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoDeleteTextObject :: Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_UNDODELETETEXT, &RF), 128);

		*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf (*pDesc, resUndo.Addr(), m_tgText.lONr);
	}

return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoDeleteTextObject :: Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Textobjekt wieder erzeugen
	if (DEX_ModObjGeometrie (m_tgText)) {
		if (m_fRect) DEX_RePaintRect (m_rcText);
		return NOERROR;
	}

return ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoDeleteTextObject :: Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Textobjekt wieder löschen
	if (DEX_DeleteObject (m_tgText.lONr)) {
		if (m_fRect) DEX_RePaintRect (m_rcText);
		return NOERROR;
	}

return ResultFromScode (S_FALSE);
}

// *** IUndoRedoDeleteText *** ------------------------------------------------
STDMETHODIMP CUndoRedoDeleteTextObject :: Init (LONG lONr, LPCRECT prc)
{
	return FInit (lONr, prc) ? NOERROR : ResultFromScode (S_FALSE);
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoDeleteTextObject :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoDeleteText) {
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

STDMETHODIMP_(ULONG) CUndoRedoDeleteTextObject :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoDeleteTextObject :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

