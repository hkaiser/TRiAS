// ClasFactory für Undo/Redo-Objekte ------------------------------------------
// File: UNDOCF.HXX

#include "trias03p.hxx"

#include <funcs03.h>

#include <containr.hxx>

#include <undoguid.h>
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration

#include "undocf.hxx"

#include "undofeat.hxx"
#include "undodelr.hxx"
#include "undomodr.hxx"
#include "undodelt.hxx"
#include "undotext.hxx"
#include "undohwnd.hxx"
#include "undodelo.hxx"
#include "undomodo.hxx"
#include "undopbd.hxx"

extern LONG g_cObj;
extern LONG g_cLock;

void PASCAL ObjectDestroyed (void);

CUndoRedoClassFactory :: CUndoRedoClassFactory (void)
{
	m_cRef = 0L;
}


CUndoRedoClassFactory :: ~CUndoRedoClassFactory (void)
{
}

STDMETHODIMP CUndoRedoClassFactory :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;

// Any interface on this object is the object pointer.
	if (riid == IID_IUnknown || riid == IID_IClassFactory)
		*ppv = (LPVOID)this;

	if (NULL!=*ppv) {
		((LPUNKNOWN)*ppv)->AddRef();
		return NOERROR;
	}

return ResultFromScode(E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CUndoRedoClassFactory :: AddRef(void)
{
	return ++m_cRef;
}


STDMETHODIMP_(ULONG) CUndoRedoClassFactory :: Release(void)
{
ULONG cRefT = --m_cRef;

	if (m_cRef == 0L)
		delete this;

return cRefT;
}

static HRESULT CreateUndoInstance (REFIID riid, LPVOID *ppvObj, LPFNDESTROYED pfn = NULL)
{
LPUNDOREDO pObj = NULL;
bool fOK = false;
HRESULT hr = NOERROR;

// Create the required UndoRedoObject -----------------------------------------
	if (riid == IID_IUndoRedoObjectFeature) {
	// Merkmal löschen, erzeugen oder modifizieren
		fOK = true;
		pObj = new CUndoRedoObjectFeature (pfn);
	} else if (riid == IID_IUndoRedoDeleteObjectRelation) {
	// Relation löschen 
		fOK = true;
		pObj = new CUndoRedoDeleteObjectRelation (pfn);
	} else if (riid == IID_IUndoRedoCreateObjectRelation) {
	// Relation erzeugen 
		fOK = true;
		pObj = new CUndoRedoCreateObjectRelation (pfn);
	} else if (riid == IID_IUndoRedoDeleteText) {
	// Textobjekt löschen 
		fOK = true;
		pObj = new CUndoRedoDeleteTextObject (pfn);
	} else if (riid == IID_IUndoRedoCreateText) {
	// Textobjekt erzeugen 
		fOK = true;
		pObj = new CUndoRedoCreateTextObject (pfn);
	} else if (riid == IID_IUndoRedoDeleteObjectWnd) {
	// Objekt aus OR-Fenster entfernen 
		fOK = true;
		pObj = new CUndoRedoDeleteObjectWnd (pfn);
	} else if (riid == IID_IUndoRedoDeleteObject) {
	// Objekt löschen 
		fOK = true;
		pObj = new CUndoRedoDeleteObject (pfn);
	} else if (riid == IID_IUndoRedoModifyObject) {
	// Objekt modifizieren
		fOK = true;
		pObj = new CUndoRedoModifyObject (pfn);
	} else if (riid == IID_IUndoRedoPBDData) {
	// PBD-Eintrag modifizieren, anlegen, löschen
		fOK = true;
		pObj = new CUndoRedoPBDData (pfn);
	}

	if (pObj == NULL) 
		return ResultFromScode (fOK ? E_OUTOFMEMORY : E_NOINTERFACE);

	hr = pObj -> QueryInterface (riid, ppvObj);

// Kill the object if initial creation failed.
	if (FAILED(hr))
		delete pObj;
	else if (pfn)
		InterlockedIncrement (&g_cObj);

return hr;
}

// Externe Funktion, über welche eine Instanz erzeugt werden kann -------------
_TRIAS03_ENTRY HRESULT UndoCreateInstance (REFIID riid, LPVOID *ppvObj)
{
	return CreateUndoInstance (riid, ppvObj);
}

STDMETHODIMP CUndoRedoClassFactory :: CreateInstance
			(LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;
	if (pUnkOuter != NULL)		// no aggregation
		return ResultFromScode (CLASS_E_NOAGGREGATION);

return CreateUndoInstance (riid, ppvObj, ObjectDestroyed);
}


/*
 * CUndoRedoClassFactory::LockServer
 *
 * Purpose:
 *  Increments or decrements the lock count of the DLL.  If the lock
 *  count goes to zero and there are no objects, the DLL is allowed
 *  to unload.  See DllCanUnloadNow.
 *
 * Parameters:
 *  fLock           BOOL specifying whether to increment or
 *                  decrement the lock count.
 *
 * Return Value:
 *  HRESULT         NOERROR always.
 */

STDMETHODIMP CUndoRedoClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		g_cLock++;
	else
		g_cLock--;

return NOERROR;
}
