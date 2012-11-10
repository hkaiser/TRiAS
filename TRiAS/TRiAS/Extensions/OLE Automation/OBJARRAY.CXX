// ArrayContainer, der die Idents einer GeoObjs Collection hält -------------
// File: OBJARRAY.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>
#include <ospace/com/iterenum.h>

#include "objarray.hxx"		// CGeoObjArray
#include "obj.hxx"		// CGeoObject
#include "enumobjs.hxx"		// CEnumGeoObjs

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if _TRiAS_VER >= 0x0300
using std::bad_alloc;
#endif // _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(InitObjektGeometrie);

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CGeoObjArray::CGeoObjArray (void)
	: CGeoObjArrayBase (20, container_wrappers::CFSyncThreads)	// erstmal 20 Objekte
{
	m_pICProc = NULL;
}


CGeoObjArray *CGeoObjArray::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, INITOBJCOLLECTIONPROC pICFcn, DWORD dwData)
{
CGeoObjArray *pObjArr = NULL;

	ATLTRY(pObjArr = new CGeoObjArray);
	if (pObjArr == NULL) return NULL;

// Array mit Objekten füllen	
INITOBJSTATUS rgStatus = INITOBJSTATUS_Error;

	{		// Container füllen
	CGeoObjArraySync Sync (pObjArr);		// make it threadsafe
	CGeoObjectCreator ObCr (*pObjArr);

		rgStatus = pICFcn (pUnk, pApp, pDoc, ObCr, dwData);
	}
	
	if (rgStatus == INITOBJSTATUS_Error) {
		DELETE_OBJ(pObjArr);
		return NULL;
	}
	return pObjArr;
}

// Kopieren des CGeoObjArray's -------------------------------------------------
CGeoObjArray *CGeoObjArray::Copy (void)
{
CGeoObjArraySync Sync (this);		// make it threadsafe
CGeoObjArray *pObjArr = NULL;

	ATLTRY(pObjArr = new CGeoObjArray);
	if (pObjArr == NULL) return NULL;

// neues Array mit Daten aus diesem Array füllen
CGeoObjArraySync SyncNew (pObjArr);		// make it threadsafe
CGeoObjectCreator ObCr (*pObjArr);
CGeoObjArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectLock l(r);
	
		if (!l || !l -> IsValid()) continue;
		
	// Pointer einfach in anderem Array mit abspeichern
		((_DGeoObject *)(CGeoObject *)l) -> AddRef();		// für neues Array festhalten
		ObCr.InsertPtr (l);	// Pointer einspeichern	
	}
	return pObjArr;		// liefert Pointer auf Kopie	
}

// LöschFunktion --------------------------------------------------------------
void _XTENSN_EXPORT CGeoObjArray::UserDelete (void *pObj)
{
	((_DGeoObject *)(CGeoObject *)pObj) -> Release();	// freigeben einer enthaltenen GeoObject
}

// ZugriffsFunktion -----------------------------------------------------------
// Liefert Identifikator der Objektklasse mit dem Index lIndex innerhalb des 
// Array's
LONG CGeoObjArray::Value (LONG lIndex)
{
CGeoObjArraySync Sync (this);		// make it threadsafe
CGeoObjArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoObjectLock l(r);
	
		if (l && l -> IsValid()) return l -> GetValue();
	}
	return INVALID_ONR;	// Fehler
}


// Liefert Identifikator der Objektklasse mit dem Index lIndex innerhalb des 
// Array's ausgehend vom KurzText
LONG CGeoObjArray::Value (LPCSTR bstrName)
{
CGeoObjArraySync Sync (this);		// make it threadsafe
CGeoObjArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectLock l(r);
	
		if (l && l -> IsValid() && !strcmp (bstrName, l -> GetName())) 
			return l -> GetValue();		// gefunden
	}
	return 0;	// Fehler
}


// Liefert das IDispatch-Interface auf die Objekt mit dem lIndex
// innerhalb dieses Array's
HRESULT CGeoObjArray::GetObjectDisp (long lIndex, LPVOID *ppDisp)
{
CGeoObjArraySync Sync (this);		// make it threadsafe

	if (ppDisp == NULL) 
		return E_UNEXPECTED;
	*ppDisp = NULL;

CGeoObjArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoObjectLock l(r);
	
		if (l && l -> IsValid()) 
			return ((_DGeoObject *)(CGeoObject *)l) -> QueryInterface (IID_IDispatch, ppDisp);
	}
	return DISP_E_BADINDEX;
}

// Liefert das IDispatch-Interface auf die Objekt mit dem  pObStr
// innerhalb dieses Array's
HRESULT CGeoObjArray::GetObjectDisp (LPCSTR pObStr, LPVOID *ppDisp)
{
CGeoObjArraySync Sync (this);		// make it threadsafe

	if (ppDisp == NULL) 
		return E_UNEXPECTED;
	*ppDisp = NULL;

CGeoObjArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectLock l(r);
	
		if (l && l -> IsValid() && !strcmp (pObStr, l -> GetName())) 
			return ((_DGeoObject *)(CGeoObject *)l) -> QueryInterface(IID_IDispatch,ppDisp);
	}
	return DISP_E_BADINDEX;
}


// Liefert das IDispatch-Interface auf die Objekt mit dem lONr
// innerhalb dieses Array's
HRESULT CGeoObjArray::GetObjectDispValue (LONG lONr, LPVOID *ppDisp)
{
CGeoObjArraySync Sync (this);		// make it threadsafe

	if (ppDisp == NULL) 
		return E_UNEXPECTED;
	*ppDisp = NULL;

CGeoObjArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectLock l(r);
	
		if (l && l -> IsValid() && lONr == l -> GetValue()) 
			return ((_DGeoObject *)(CGeoObject *)l) -> QueryInterface(IID_IDispatch,ppDisp);
	}
	return DISP_E_BADINDEX;
}


// Testen, ob Objekt bereits in Container enthalten ist --------------------
long CGeoObjArray::hasObject (LONG lONr)	// returns valid index
{
	if (INVALID_ONR == lONr) 
		return -1L;		// bad ObjNumber

CGeoObjArraySync Sync (this);		// make it threadsafe
CGeoObjArrayRing r(*this);
long lIndex = 0;

	for (r.First(); r.Valid(); r.Next(), lIndex++) {
	CGeoObjectLock l(r);
	
		if (l && l -> IsValid() && lONr == l -> GetValue()) 
			return lIndex;
	}
	return -1L;
}

// get object -----------------------------------------------------------------
/*
CGeoObject *CGeoObjArray::GetGeoObject (ULONG lONr)
{
CGeoObjArrayRing r(*this);
long lIndex = 0;

	for (r.First(); r.Valid(); r.Next(), lIndex++) {
	CGeoObjectLock l(r);
	
		if (l && lONr == l -> GetValue()) 
			return l;
	}
	
return NULL;
}
*/

// delete object --------------------------------------------------------------
bool CGeoObjArray::DeleteObject (LONG lONr)
{
CGeoObjArraySync Sync (this);		// make it threadsafe
CGeoObjArrayRing r(*this);
bool fDelete = false;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectLock l(r);
	
		if (l && lONr == l -> GetValue (true)) {
			fDelete = true;
			break;
		}
	}
	if (fDelete && r.Valid()) 
		return r.Delete();
	return false;
}


HOBJECT *CGeoObjArray::GetObjectsAsArray (void)
{
CGeoObjArraySync Sync (this);		// make it threadsafe
CGeoObjArrayRing r(*this);
long i = 0;
HOBJECT *plObjs = NULL;

	ATLTRY(plObjs = new HOBJECT [Count()]);
	if (plObjs == NULL) return NULL;
	
	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectLock l(r);
	
		if (l && l -> IsValid()) 
			plObjs[i++] = l -> GetValue ();
	}
	return plObjs;
}

///////////////////////////////////////////////////////////////////////////////
// IEnumLONG mit unseren Objektnummern liefern
HRESULT CGeoObjArray::GetEnumLONG (IEnumLONG **ppIEnum)
{
	if (NULL == ppIEnum) 
		return E_POINTER;

	*ppIEnum = NULL;

IEnum<LONG> *pEnumOut = NULL;
HRESULT hr = CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER, 
							   IID_IEnumLONG, (LPVOID *)&pEnumOut);
	if (FAILED(hr)) return hr;

	try {
	CGeoObjArrayRing r(*this);

		for (r.First(); r.Valid(); r.Next()) {
		CGeoObjectLock l(r);
		
			if (l && l -> IsValid()) 
				pEnumOut -> AddItem (l -> GetValue());
		}
	} catch (bad_alloc) {
		pEnumOut -> Release();
		return E_OUTOFMEMORY;
	}
	*ppIEnum = reinterpret_cast<IEnumLONG *>(pEnumOut);
	return S_OK;
}

// count valid GeoObjects ------------------------------------------------------
ULONG CGeoObjArray::Count (void)
{
CGeoObjArraySync Sync (this);		// make it threadsafe
CGeoObjArrayRing r(*this);
ULONG lCount = 0;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectLock l(r);

		if (l && l -> IsValid()) 
			lCount++;
	}
	return lCount;
}

// Refresh der Collection -----------------------------------------------------
HRESULT CGeoObjArray::Refresh (void)
{
CGeoObjArraySync Sync (this);		// make it threadsafe
CGeoObjArrayRing r(*this);
bool fDeleted = false;

	for (r.First(); r.Valid(); ) {
	bool fToDelete = false;

		{
		CGeoObjectLock l(r);
	
			if (l && !l -> IsValid()) 
				fToDelete = true;
		} // goes out of scope

		if (fToDelete) {
			r.Delete();
			fDeleted = true;
		} else
			r.Next();
	}
	return fDeleted ? S_OK : S_FALSE;
}


