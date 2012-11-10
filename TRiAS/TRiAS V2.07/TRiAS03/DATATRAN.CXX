/*
 * DATATRAN.CPP
 * Data Transfer Object Chapter 7
 *
 * Transfer data object implemented in a DLL.  This data object will
 * cache specific formats and renderings such that its IDataObject
 * interface could be plopped on the clipboard or used in drag-drop.
 *
 * Copyright (c)1993 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "trias03p.hxx"

#include <funcs03.h>
#include <statguid.h>

#define INITGUIDS
#define _TriasTLB_H_
#include <dirisole.h>

#include "pdataobj.hxx"
#include "datatran.hxx"

#if defined(WIN32)
extern CComModule _Module;
#include <undoguid.h>		// GUID's
#include <xtsnguid.h>
#include <oprpguid.h>
#include <srchguid.h>

#include <selidprp.h>
#include <modidprp.h>
#include <selobwnd.h>
#include <dstobwnd.h>
#include <DelObPrp.h>
#include <clsfyprp.h>
#include <importprp.h>
#include "gentguid.h"

#include "undocf.hxx"

//#define IID_DEFINED
//#include "TRiASHelper_i.c"

#ifdef _MERGE_PROXYSTUB
#include "dlldatax.h"
extern "C" HINSTANCE hProxyDll;
#endif

#if !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100
#include "CoDelegator.h"
#endif // !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100

#endif // WIN32

//Count number of objects and number of locks.
LONG       g_cObj=0;
LONG       g_cLock=0;

//Make this global for the data object to create listboxes.
extern "C" HINSTANCE   g_hInstance;


/*
 * DllGetClassObject
 *
 * Purpose:
 *  Provides an IClassFactory for a given CLSID that this DLL is
 *  registered to support.  This DLL is placed under the CLSID
 *  in the registration database as the InProcServer.
 *
 * Parameters:
 *  clsID           REFCLSID that identifies the class factory
 *                  desired.  Since this parameter is passed this
 *                  DLL can handle any number of objects simply
 *                  by returning different class factories here
 *                  for different CLSIDs.
 *
 *  riid            REFIID specifying the interface the caller wants
 *                  on the class object, usually IID_ClassFactory.
 *
 *  ppv             LPLPVOID in which to return the interface
 *                  pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, otherwise an error code.
 */

extern "C" _TRIAS03_ENTRY STDAPI EXPORT03 DllGetClassObject (
		REFCLSID rclsid, REFIID riid, LPLPVOID ppv)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
		return S_OK;
#endif
// Check that we can provide the interface
//	if (!(riid == IID_IUnknown) && !(riid == IID_IClassFactory))
//		return E_NOINTERFACE;

	*ppv = NULL;

// Check each of the CLSIDs we support.
	if (rclsid == CLSID_DataTransferObject)
		ATLTRY(*ppv = (LPVOID)new CDataTransferClassFactory());

#if defined(WIN32)
// UndoRedoVerwaltung
	if (rclsid == CLSID_UndoRedoObject)
		ATLTRY(*ppv = (LPVOID)new CUndoRedoClassFactory());

#if !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100
	if (rclsid == CLSID_CoDelegator) 
		 return CreateDelegatorFactory (riid, ppv);
#endif // !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100

// ATL befragen
	if (NULL == *ppv)
		return _Module.GetClassObject (rclsid, riid, ppv);
		
#else
	if (*ppv == NULL) return ResultFromScode (E_OUTOFMEMORY);
#endif // WIN32

	((LPUNKNOWN)*ppv)->AddRef();

return NOERROR;
}

/*
 * DllCanUnloadNow
 *
 * Purpose:
 *  Answers if the DLL can be freed, that is, if there are no
 *  references to anything this DLL provides.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if nothing is using us, FALSE otherwise.
 */

extern "C" 
_TRIAS03_ENTRY STDAPI EXPORT03 DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllCanUnloadNow() != S_OK)
		return S_FALSE;
#endif
SCODE sc;

#if defined(WIN32)
// ATL befragen
	if (0 != _Module.GetLockCount())
		return S_FALSE;
#endif // WIN32

// Our answer is whether there are any object or locks
	sc = (g_cObj == 0 && g_cLock == 0L) ? S_OK : S_FALSE;

return ResultFromScode(sc);
}

/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the DataObject object to call when it gets
 *  destroyed.  Since we're in a DLL we only track the number
 *  of objects here letting DllCanUnloadNow take care of the rest.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void FAR PASCAL ObjectDestroyed(void)
{
	piInterlockedDecrement(&g_cObj);
}

/*
 * CDataTransferClassFactory::CDataTransferClassFactory
 * CDataTransferClassFactory::~CDataTransferClassFactory
 *
 * Constructor Parameters:
 *  None
 */

CDataTransferClassFactory::CDataTransferClassFactory(void)
{
	m_cRef = 0L;
}


CDataTransferClassFactory::~CDataTransferClassFactory(void)
{
}


/*
 * CDataTransferClassFactory::QueryInterface
 * CDataTransferClassFactory::AddRef
 * CDataTransferClassFactory::Release
 */

STDMETHODIMP CDataTransferClassFactory::QueryInterface (REFIID riid, LPLPVOID ppv)
{
	*ppv = NULL;

// Any interface on this object is the object pointer.
	if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory))
		*ppv = (LPVOID)this;

	if (NULL!=*ppv) {
		((LPUNKNOWN)*ppv)->AddRef();
		return NOERROR;
	}

return ResultFromScode(E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CDataTransferClassFactory::AddRef(void)
{
	return ++m_cRef;
}


STDMETHODIMP_(ULONG) CDataTransferClassFactory::Release(void)
{
ULONG           cRefT;

	cRefT=--m_cRef;

	if (0L==m_cRef)
		delete this;

return cRefT;
}


static HRESULT CreateDataObjInstance (
	LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppvObj, LPFNDESTROYED pfn = NULL)
{
CDataObject         *pObj;
HRESULT             hr;

	*ppvObj = NULL;
	hr = ResultFromScode(E_OUTOFMEMORY);

	if (NULL != pUnkOuter && !IsEqualIID (riid, IID_IUnknown))
		return ResultFromScode(E_NOINTERFACE);

// Create the object telling it the data size to work with
	pObj = CDataObject::CreateInstance (pUnkOuter, pfn);
	if (NULL == pObj) return hr;

	hr = pObj -> QueryInterface(riid, ppvObj);
	pObj -> Release();			// !!! CreateInstance liefert mit RefCnt = 1 ab

// Kill the object if initial creation or FInit failed.
	if (SUCCEEDED(hr) && NULL != pfn)
		piInterlockedIncrement (&g_cObj);

return hr;
}

/*
 * CDataTransferClassFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates a DataObject object that supports the IDataObject
 *  and IUnknown interfaces.  If the caller asks for a different
 *  interface than these two then we fail.
 *
 * Parameters:
 *  pUnkOuter       LPUNKNOWN to the controlling IUnknown if we
 *                  are being used in an aggregation.
 *  riid            REFIID identifying the interface the caller
 *                  desires to have for the new object.
 *  ppvObj          LPLPVOID in which to store the desired
 *                  interface pointer for the new object.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise E_NOINTERFACE
	 *                  if we cannot support the requested interface.
 */

STDMETHODIMP CDataTransferClassFactory::CreateInstance
			(LPUNKNOWN pUnkOuter, REFIID riid, LPLPVOID ppvObj)
{
	return CreateDataObjInstance (pUnkOuter, riid, ppvObj, ObjectDestroyed);
}

// Externe Funktion, über welche eine Instanz erzeugt werden kann -------------
_TRIAS03_ENTRY HRESULT DataObjectCreateInstance (IUnknown *pIUnk, REFIID riid, LPVOID *ppvObj)
{
	return CreateDataObjInstance (pIUnk, riid, ppvObj);
}




/*
 * CDataTransferClassFactory::LockServer
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

STDMETHODIMP CDataTransferClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		g_cLock++;
	else
		g_cLock--;

return NOERROR;
}
