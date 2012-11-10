// Undo/Redo für ObjIdent modifizieren ----------------------------------------
// File: UNDOMODI.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <funcs02.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "undomodi.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// Umrechnen der verschiedenen Darstellungsformen der Objekttypen -------------
short OTypToBits (ObjTyp iOTyp)
{
        switch (iOTyp) {
        case OT_PUNKT:  return OTPunkt;
        case OT_KANTE:  return OTLinie;
        case OT_FLAECHE:
        case OT_KREIS:  return OTFlaeche;
        case OT_TEXT:   return OTText;
        case OT_KO:     return (OTPunkt|OTLinie|OTFlaeche|OTText);
        case OT_UNKNOWN:
        default:
                break;
        }

return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoModIdent :: CUndoRedoModIdent (LPFNDESTROYED pfnDestroy)
		       : m_pfnDestroy (pfnDestroy)
{
	m_dwRefCnt = 0L;
	m_ulNewIdent = 0L;
	m_ulOldIdent = 0L;
	m_lONr = 0L;
	m_iMode = 0;
}

CUndoRedoModIdent :: ~CUndoRedoModIdent (void)
{
}

BOOL CUndoRedoModIdent :: FInit (LONG lONr, ULONG ulNewIdent, ULONG ulOldIdent, int iMode)
{
// Gültigkeit der Daten absichern
//	TX_ASSERT(IsValidONr(lONr));
	TX_ASSERT(IsValidIdent(ulNewIdent));
	TX_ASSERT(0L == ulOldIdent || IsValidIdent(ulOldIdent));

// Daten speichern
	m_lONr = lONr;
	m_ulNewIdent = ulNewIdent;
	if (0L == ulOldIdent) 
		m_ulOldIdent = DEX_GetObjIdent (lONr);
	else
		m_ulOldIdent = ulOldIdent;

	if (0 == iMode)
		m_iMode = MODIDENT_ADDTOVIEW|OTypToBits((ObjTyp)DEX_GetObjectType(lONr));
	else
		m_iMode = iMode;

// alles ok, raus hier
	Initialized();

return true;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoModIdent :: Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_UNDOMODIDENT, &RF), 128);

		*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf (*pDesc, resUndo.Addr(), m_lONr);
	}

return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO|UNDOREDOCAPS_REPAINT;
}

STDMETHODIMP CUndoRedoModIdent :: Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Ident wiederherstellen
MODOBJIDENT MI;

	INITSTRUCT(MI, MODOBJIDENT);
	MI.lONr = m_lONr;
	MI.lNewIdent = static_cast<LONG>(m_ulOldIdent);
	MI.iMode = m_iMode;

	if (DEX_ModObjectIdent(MI)) 
		return NOERROR;

return ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoModIdent :: Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Ident wieder neu machen
MODOBJIDENT MI;

	INITSTRUCT(MI, MODOBJIDENT);
	MI.lONr = m_lONr;
	MI.lNewIdent = static_cast<LONG>(m_ulNewIdent);
	MI.iMode = m_iMode;

	if (DEX_ModObjectIdent(MI)) 
		return NOERROR;

return ResultFromScode (S_FALSE);
}

// *** IUndoRedoDeleteText *** ------------------------------------------------
STDMETHODIMP CUndoRedoModIdent :: Init (LONG lONr, ULONG ulNewIdent, ULONG ulOldIdent, int iMode)
{
	return FInit (lONr, ulNewIdent, ulOldIdent, iMode) ? NOERROR : ResultFromScode (S_FALSE);
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoModIdent :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoModIdent) {
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

STDMETHODIMP_(ULONG) CUndoRedoModIdent :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoModIdent :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

