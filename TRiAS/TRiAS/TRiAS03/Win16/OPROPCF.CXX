// ClassFactory für ObjektEigenschaften ---------------------------------------
// File: OPROPCF.CX

#include "trias03p.hxx"

#include <funcs03.h>

#include <containr.hxx>

#include <undoguid.h>
#include <oprpguid.h>

#include <ixtensn.hxx>		// Interface's
#include <iunredo.hxx>
#include <ioprpini.hxx>

#include <enumundo.hxx>		// Klassendeklaration
#include <undoredo.hxx>

#include "opropcf.hxx"
#include "intoprop.hxx"

extern LONG g_cObj;
extern LONG g_cLock;

void PASCAL ObjectDestroyed (void);

CObjPropCF :: CObjPropCF (REFCLSID rclsid)
{
	m_cRef = 0L;
	m_clsID = rclsid;
}


CObjPropCF :: ~CObjPropCF (void)
{
}

STDMETHODIMP CObjPropCF :: QueryInterface (REFIID riid, LPVOID *ppv)
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


STDMETHODIMP_(ULONG) CObjPropCF :: AddRef(void)
{
	return ++m_cRef;
}


STDMETHODIMP_(ULONG) CObjPropCF :: Release(void)
{
ULONG cRefT = --m_cRef;

	if (m_cRef == 0L)
		delete this;

return cRefT;
}

static HRESULT CreateObjPropInstance (REFCLSID rClsID, REFIID riid, LPVOID *ppvObj, LPFNDESTROYED pfn = NULL)
{
IObjectProperty *pObj = NULL;
bool fOK = false;
HRESULT hr = NOERROR;

// konkrete Objekteigenschaft generieren
	if (rClsID == CLSID_ObjPropONr) {
		fOK = true;
		pObj = new CObjPropONr (pfn);
	} else if (rClsID == CLSID_ObjPropIdent) {
		fOK = true;
		pObj = new CObjPropIdent (pfn);
	} else if (rClsID == CLSID_ObjPropObjTypShort) {
		fOK = true;
		pObj = new CObjPropObjTypShort (pfn);
	} else if (rClsID == CLSID_ObjPropObjTypLong) {
		fOK = true;
		pObj = new CObjPropObjTypLong (pfn);
	} else if (rClsID == CLSID_ObjPropQueryField) {
		fOK = true;
		pObj = new CObjPropQueryField (pfn);
	} else if (rClsID == CLSID_ObjPropFeature) {
		fOK = true;
		pObj = new CObjPropMerkmal (pfn);
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
_TRIAS03_ENTRY HRESULT ObjPropCreateInstance (IUnknown *pIUnk, REFCLSID rClsID, REFIID riid, LPVOID *ppvObj)
{
	if (NULL != pIUnk)
		return ResultFromScode (CLASS_E_NOAGGREGATION);

	return CreateObjPropInstance (rClsID, riid, ppvObj);
}

STDMETHODIMP CObjPropCF :: CreateInstance
		(LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;
	if (pUnkOuter != NULL)		// no aggregation
		return ResultFromScode (CLASS_E_NOAGGREGATION);

return CreateObjPropInstance (m_clsID, riid, ppvObj, ObjectDestroyed);
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

STDMETHODIMP CObjPropCF::LockServer(BOOL fLock)
{
	if (fLock)
		g_cLock++;
	else
		g_cLock--;

return NOERROR;
}
