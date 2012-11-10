// object-destroyed-callback --------------------------------------------------
// File CF.CXX
// H. Kaiser

#include "GeometrP.hxx"

#include <xtsnaux.hxx>  // piInterlockedDecrement

#include "objgeocf.hxx"	// ObjektGeometrieCF

#include "objgguid.h"   // CLSID_ObjektGeometrie



typedef DESTROYNOTIFYPROC *DESTROYNOTIFYPROCPTR;

extern DESTROYNOTIFYPROC ObjectDestroyed;
extern LONG g_cObj;		// Anzahl der aktiven Objekte
extern LONG g_cLock;	// Anzahl der externen Locks

/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the TriasXtension object to call when it gets destroyed.
 *  Since we're in a DLL we only track the number of objects here
 *  letting DllCanUnloadNow take care of the rest.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */
void PASCAL ObjectDestroyed(void)
{
	piInterlockedDecrement (&g_cObj);
}


/*
 * DllGetClassObject
 *
 * Purpose:
 *  Provides an IClassFactory for a given CLSID that this DLL is
 *  registered to support.  
 *
 * Parameters:
 *  clsID           REFCLSID that identifies the class factory desired.
 *                  Since this parameter is passed this DLL can handle
 *                  any number of objects simply by returning different
 *                  class factories here for different CLSIDs.
 *
 *  riid            REFIID specifying the interface the caller wants
 *                  on the class object, usually IID_ClassFactory.
 *
 *  ppv             LPVOID FAR * in which to return the interface pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, otherwise contains an error SCODE.
 */

extern "C" 
HRESULT PASCAL DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
// zuerst abfragen, ob PropertySheetHandler gefragt ist
	if (rclsid == CLSID_ObjektGeometrie) {
	// Check that we can provide the interface
		if (!IsEqualIID(riid, IID_IUnknown) && !IsEqualIID(riid, IID_IClassFactory))
			return ResultFromScode(E_NOINTERFACE);

		*ppv = new ObjektGeometrieCF();
		if (NULL == *ppv)
			return ResultFromScode (E_OUTOFMEMORY);
	}

// Don't forget to AddRef the object through any interface we return
	((LPUNKNOWN)(*ppv)) -> AddRef();

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
 *  bool            true if nothing is using us, false otherwise.
 */

extern "C" 
STDAPI DllCanUnloadNow(void)
{
SCODE sc;

// Our answer is whether there are any object or locks
	sc = (g_cObj == 0L && g_cLock == 0) ? S_OK : S_FALSE;

return ResultFromScode(sc);
}
