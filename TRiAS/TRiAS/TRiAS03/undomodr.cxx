// Undo/Redo für Relation erzeugen --------------------------------------------
// File: UNDOMODR.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "undomodr.hxx"

extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoCreateObjectRelation::CUndoRedoCreateObjectRelation (LPFNDESTROYED pfnDestroy)
			       : m_pfnDestroy (pfnDestroy)
{
	m_dwRefCnt = 0L;
	INITSTRUCT (m_mrObj, MODRELATION);
}

CUndoRedoCreateObjectRelation::~CUndoRedoCreateObjectRelation (void)
{
	// nothing else to do
}

BOOL CUndoRedoCreateObjectRelation::FInit (
		HOBJECT lONr, HOBJECT lSecONr, HRELATION ulRCode, short iRTyp)
{
	m_mrObj.lPONr = lONr;		// PrimärObjekt
	m_mrObj.lSONr = lSecONr;	// SekundärObjekt
	m_mrObj.lRCode = (long)ulRCode;	// RelationsCode
	m_mrObj.iRTyp = iRTyp;		// RelationsTyp

	Initialized();
	return true;		// nothing else to do
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoCreateObjectRelation::Capabilities (signed char **pDesc)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_UNDOCREATERELATION, &RF), 128);

		*pDesc = (signed char *)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf ((char *)*pDesc, resUndo.Addr(), 
				  m_mrObj.lRCode, m_mrObj.iRTyp, 
				  m_mrObj.lPONr, m_mrObj.lSONr);
	}

return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoCreateObjectRelation::Undo (void)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

// Relation wieder löschen
	if (DEX_DeleteRelation (m_mrObj))
		return S_OK;

	return S_FALSE;
}

STDMETHODIMP CUndoRedoCreateObjectRelation::Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Relation wieder erzeugen
	if (DEX_ModifyRelation (m_mrObj))
		return S_OK;

	return S_FALSE;
}

// *** IUndoRedoCreateRelation *** --------------------------------------------
STDMETHODIMP CUndoRedoCreateObjectRelation::Init (
		HOBJECT lONr, HOBJECT lSecONr, HRELATION ulRCode, short iRTyp)
{
	return FInit (lONr, lSecONr, ulRCode, iRTyp) ? S_OK : S_FALSE;
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoCreateObjectRelation::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoCreateObjectRelation) {
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

return S_OK;
}

STDMETHODIMP_(ULONG) CUndoRedoCreateObjectRelation::AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoCreateObjectRelation::Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

