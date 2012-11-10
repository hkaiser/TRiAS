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
#include "UndoCreo.hxx"

extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoCreateObject::CUndoRedoCreateObject (LPFNDESTROYED pfnDestroy)
		       : m_pfnDestroy (pfnDestroy)
{
	m_dwRefCnt = 0L;
	m_fRect = false;
}

CUndoRedoCreateObject::~CUndoRedoCreateObject (void)
{
}

BOOL CUndoRedoCreateObject::FInit (LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc)
{
// Member initialisieren
	if (prc) {
		m_rcObj = *prc;
		m_fRect = true;
	} else
		m_fRect = false;

	try {
	// Objekt hier zwischenspeichern (neue Geometrie kopieren)
		m_ogNew = *pOGNew;		// throws bad_alloc
	
	} catch (...) {
		return false;
	}

// alles ok, raus hier
	Initialized();

return true;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoCreateObject::Capabilities (signed char **pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_UNDOCREATEOBJECT, &RF), 128);

		*pDesc = (signed char *)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) 
			wsprintf ((char *)*pDesc, resUndo.Addr(), m_ogNew.lONr);
	}

DWORD dwFlags = UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;

	if (!m_fRect) dwFlags |= UNDOREDOCAPS_REPAINT;

return dwFlags;
}

STDMETHODIMP CUndoRedoCreateObject::Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt wieder löschen
	if (DEX_DeleteObject (m_ogNew.lONr)) {
		m_ogNew.lONr = 0L;
		if (m_fRect) 
			DEX_RePaintRect (m_rcObj);
		return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CUndoRedoCreateObject::Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// Objekt wieder erzeugen
	m_ogNew.lONr = 0L;
	m_ogNew.iFlags |= (OGNewObject|OGForceGeometry);
	if (DEX_ModObjGeometrie (m_ogNew)) {
		if (m_fRect) DEX_RePaintRect (m_rcObj);
		return S_OK;
	}
	return S_FALSE;
}

// *** IUndoRedoDeleteText *** ------------------------------------------------
STDMETHODIMP CUndoRedoCreateObject::Init (LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc)
{
	return FInit (lONr, pOGNew, prc) ? S_OK : ResultFromScode (S_FALSE);
}

// *** IPropagateObjectNumber
STDMETHODIMP CUndoRedoCreateObject::GetUndoObjectNumber (INT_PTR *plONr)
{
	if (NULL == plONr)
		return E_POINTER;
	*plONr = 0L;			// Objekt ist gelöscht
	return S_OK;
}

STDMETHODIMP CUndoRedoCreateObject::SetUndoObjectNumber (INT_PTR lONr)
{
	return E_NOTIMPL;		// hier nicht implementiert
}

STDMETHODIMP CUndoRedoCreateObject::GetRedoObjectNumber (INT_PTR *plONr)
{
	if (NULL == plONr)
		return E_POINTER;
	*plONr = m_ogNew.lONr;
	return S_OK;
}

STDMETHODIMP CUndoRedoCreateObject::SetRedoObjectNumber (INT_PTR lONr)
{
	return E_NOTIMPL;		// hier nicht implementiert
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoCreateObject::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || 
		riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoCreateObject)
	{
	// Someone is asking us for our controlling IUnknown.
	// CUndoRedo is that IUnknown, so "this" is the answer.
		*ppvObj = static_cast<IUndoRedoCreateObject *>(this);
	} 
	else if (riid == IID_IPropagateObjectNumber) {
		*ppvObj = static_cast<IPropagateObjectNumber *>(this);
	}
	else {
	// They must have asked for another interface -- something
	// we don't support.  Report the error.
		*ppvObj = NULL;
		return E_NOINTERFACE;
	}

// If execution reached this point then no error occurred.
	LPUNKNOWN(*ppvObj) -> AddRef();
	return S_OK;
}

STDMETHODIMP_(ULONG) CUndoRedoCreateObject::AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoCreateObject::Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

