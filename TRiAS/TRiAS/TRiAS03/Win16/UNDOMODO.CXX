// Undo/Redo für ObjektGeometrie modifzieren-----------------------------------
// File: UNDOMODO.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "undomodo.hxx"

extern char g_pDLLName[260];

// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoModifyObject :: CUndoRedoModifyObject (LPFNDESTROYED pfnDestroy)
		       : m_pfnDestroy (pfnDestroy)
{
	INITSTRUCT (m_ogOld, OBJGEOMETRIE);
	INITSTRUCT (m_ogNew, OBJGEOMETRIE);
	m_dwRefCnt = 0L;
	m_fRect = false;
}

CUndoRedoModifyObject :: ~CUndoRedoModifyObject (void)
{
	DELETE (m_ogOld.pdblX);
	DELETE (m_ogOld.pdblY);
	DELETE (m_ogOld.plCnt);

	DELETE (m_ogNew.pdblX);
	DELETE (m_ogNew.pdblY);
	DELETE (m_ogNew.plCnt);
}

static bool InitObjGeometrie (OBJGEOMETRIE &OG)
{
	OG.iFlags |= OGModObject;
	OG.pdblX = new double [OG.lCnt];
	OG.pdblY = new double [OG.lCnt];
	if (OG.pdblX == NULL || OG.pdblY == NULL)
		return false;

	if (OG.iKCnt > 0) {
		if (OG.iObjTyp == OGFlaeche) {
			OG.plCnt = new long [OG.iKCnt];
			if (OG.plCnt == NULL) 
				return false;
		} else if (OG.iObjTyp == OGText) {
		int iLen = OG.iKCnt+1;

			if (0 == iLen) iLen = _MAX_PATH;
			((TEXTGEOMETRIE &)OG).pText = new char [iLen];
			if (((TEXTGEOMETRIE &)OG).pText == NULL) 
				return false;
		}
	} else
		OG.plCnt = NULL;

return true;
}

bool CUndoRedoModifyObject :: FInit (LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc)
{
// Member initialisieren
	m_ogOld.lONr = lONr;
	if (prc) {
		m_rcObj = *prc;
		m_fRect = true;
	} else
		m_fRect = false;

// Objekt hier zwischenspeichern
	if (!DEX_GetObjStatistik (m_ogOld)) 
		return false;

	if (!InitObjGeometrie (m_ogOld)) return false;
	if (!DEX_GetObjGeometrie (m_ogOld)) return false;

	if (m_ogOld.iObjTyp == OGText) {
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
		((TEXTGEOMETRIE &)m_ogOld).pText = (char *)m_strText.c_str();
	}

// neue Geometrie kopieren
	m_ogNew = *pOGNew;
	if (!InitObjGeometrie (m_ogNew)) return false;

	if (pOGNew -> iFlags & OGConverted) {
		memcpy (m_ogNew.pdblX, pOGNew -> pdblX, pOGNew -> lCnt*sizeof(double));
		memcpy (m_ogNew.pdblY, pOGNew -> pdblY, pOGNew -> lCnt*sizeof(double));
	} else {
		memcpy (m_ogNew.pdblX, pOGNew -> pdblX, pOGNew -> lCnt*sizeof(long));
		memcpy (m_ogNew.pdblY, pOGNew -> pdblY, pOGNew -> lCnt*sizeof(long));
	}
	if (pOGNew -> iKCnt > 0) {
		if (pOGNew -> iObjTyp == OGFlaeche) 
			memcpy (m_ogNew.plCnt, pOGNew -> plCnt, pOGNew->iKCnt*sizeof(long));
		else if (pOGNew -> iObjTyp == OGText) {
		TEXTGEOMETRIE &TG = (TEXTGEOMETRIE &)m_ogNew;
		TEXTGEOMETRIE &oldTG = (TEXTGEOMETRIE &)m_ogOld;

			if (NULL != TG.pText)
				strcpy (TG.pText, ((TEXTGEOMETRIE *)pOGNew) -> pText);
			else if (NULL != oldTG.pText)
				strcpy (TG.pText, oldTG.pText);
			else
				TG.pText[0] = '\0';
		}
	} else
		m_ogNew.plCnt = NULL;

// evtl. verschiedenes aus der alten Struktur übernehmen
	if (0 == m_ogNew.iObjTyp)
		m_ogNew.iObjTyp = m_ogOld.iObjTyp;
	if (0L == m_ogNew.lIdent)
		m_ogNew.lIdent = m_ogOld.lIdent;

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
	m_ogOld.iFlags |= OGModObject;
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
	m_ogOld.iFlags |= OGModObject;
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

