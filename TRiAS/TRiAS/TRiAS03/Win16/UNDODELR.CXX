// Undo/Redo für Relation löschen ---------------------------------------------
// File: UNDODELR.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "undodelr.hxx"

extern char g_pDLLName[260];

// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoDeleteObjectRelation :: CUndoRedoDeleteObjectRelation (LPFNDESTROYED pfnDestroy)
			       : m_pfnDestroy (pfnDestroy)
{
	m_dwRefCnt = 0L;
	INITSTRUCT (m_mrObj, MODRELATION);
}

CUndoRedoDeleteObjectRelation :: ~CUndoRedoDeleteObjectRelation (void)
{
	// nothing else to do
}

bool CUndoRedoDeleteObjectRelation :: FInit (
		LONG lONr, LONG lSecONr, ULONG ulRCode, short iRTyp)
{
	m_mrObj.lPONr = lONr;		// PrimärObjekt
	m_mrObj.lSONr = lSecONr;	// SekundärObjekt
	m_mrObj.lRCode = (long)ulRCode;	// RelationsCode
	m_mrObj.iRTyp = iRTyp;		// RelationsTyp
	Initialized ();

return true;		// nothing else to do
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoDeleteObjectRelation :: Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_UNDODELETERELATION, &RF), 128);

		*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf (*pDesc, resUndo.Addr(), 
				  m_mrObj.lRCode, m_mrObj.iRTyp, 
				  m_mrObj.lPONr, m_mrObj.lSONr);
	}

return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoDeleteObjectRelation :: Undo (void)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

// Relation wieder erzeugen
	if (DEX_ModifyRelation (m_mrObj))
		return NOERROR;

return ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoDeleteObjectRelation :: Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Relation wieder löschen
	if (DEX_DeleteRelation (m_mrObj))
		return NOERROR;

return ResultFromScode (S_FALSE);
}


// *** IUndoRedoDeleteObjectRelation *** --------------------------------------
STDMETHODIMP CUndoRedoDeleteObjectRelation :: Init (
		LONG lONr, LONG lSecONr, ULONG ulRCode, short iRTyp)
{
return FInit (lONr, lSecONr, ulRCode, iRTyp) ? NOERROR : ResultFromScode (S_FALSE);
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoDeleteObjectRelation :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoDeleteObjectRelation) {
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

STDMETHODIMP_(ULONG) CUndoRedoDeleteObjectRelation :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoDeleteObjectRelation :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

