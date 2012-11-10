// ArrayContainer, der die Idents einer GeoClassesCollection hält -------------
// File: CLSARRAY.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "clsarray.hxx"		// CIdentArray
#include "class.hxx"		// CClass
#include "enumclss.hxx"		// CEnumClasses

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CIdentArray::CIdentArray (void)
	: CIdentArrayBase (20, container_wrappers::CFSyncThreads)	// erstmal 20 Idents
{
	m_pICProc = NULL;
}


CIdentArray *CIdentArray::CreateInstance (
	LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	INITCLASSCOLLECTIONPROC pICFcn, DWORD dwData)
{
CIdentArray *pIdArr = NULL;

	ATLTRY(pIdArr = new CIdentArray);
	if (pIdArr == NULL) return NULL;

// Array mit Objektklassen füllen	
INITCLSSTATUS rgStatus = INITCLSSTATUS_Error;

	{		// Container füllen
	CIdentArraySync Sync (pIdArr);		// make it threadsafe
	CClassCreator ClCr (*pIdArr);
	
		rgStatus = pICFcn (pUnk, pApp, pDoc, ClCr, dwData);
	}

	if (rgStatus == INITCLSSTATUS_Error) {
		DELETE_OBJ (pIdArr);
		return NULL;
	}
	return pIdArr;
}


// Kopieren des CIdentArray's -------------------------------------------------
CIdentArray *CIdentArray::Copy (void)
{
CIdentArraySync Sync (this);		// make it threadsafe
CIdentArray *pIdArr = NULL;

	ATLTRY(pIdArr = new CIdentArray);

// neues Array mit Daten aus diesem Array füllen
CIdentArraySync SyncNew (pIdArr);		// make it threadsafe
CClassCreator ClCr (*pIdArr);
CIdentArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CClassLock l(r);
	
		if (!l || !l -> IsValid()) continue;
		
	// Pointer einfach in anderem Array mit abspeichern
		((_DGeoClass *)(CClass *)l) -> AddRef();		// für neues Array festhalten
		ClCr.InsertPtr (l);	// Pointer einspeichern	
	}
	return pIdArr;		// liefert Pointer auf Kopie	
}



// LöschFunktion --------------------------------------------------------------
void _XTENSN_EXPORT CIdentArray::UserDelete (void *pObj)
{
	((_DGeoClass *)(CClass *)pObj) -> Release();	// freigeben einer enthaltenen GeoClass
}


// ZugriffsFunktion -----------------------------------------------------------

// Liefert Identifikator der Objektklasse mit dem Index lIndex innerhalb des 
// Array's
ULONG CIdentArray::Value (ULONG lIndex)
{
CIdentArraySync Sync (this);		// make it threadsafe
CIdentArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CClassLock l(r);
	
		if (l && l -> IsValid()) 
			return l -> GetValue();
	}
	return INVALID_IDENT;	// Fehler
}

// Liefert Identifikator der Objektklasse mit dem Index lIndex innerhalb des 
// Array's ausgehend vom KurzText
ULONG CIdentArray::Value (LPCSTR bstrName)
{
CIdentArraySync Sync (this);		// make it threadsafe
CIdentArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CClassLock l(r);
	
		if (l && l -> IsValid() && !strcmp (bstrName, l -> GetName())) 
			return l -> GetValue();		// gefunden
	}
	return INVALID_IDENT;	// Fehler
}

// Liefert das IDispatch-Interface auf die ObjektKlasse mit dem lIndex
// innerhalb dieses Array's
HRESULT CIdentArray::GetClassDisp (ULONG lIndex, LPVOID *ppDisp)
{
	if (ppDisp == NULL) 
		return E_POINTER;
	*ppDisp = NULL;

CIdentArraySync Sync (this);		// make it threadsafe
CIdentArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CClassLock l(r);
	
		if (l && l -> IsValid()) 
			return ((_DGeoClass *)(CClass *)l) -> QueryInterface(IID_IDispatch, ppDisp);
	}
	return DISP_E_BADINDEX;
}


// Liefert das IDispatch-Interface auf die ObjektKlasse mit dem  pIdStr
// innerhalb dieses Array's
HRESULT CIdentArray::GetClassDisp (LPCSTR pIdStr, LPVOID *ppDisp)
{
	if (ppDisp == NULL) 
		return E_POINTER;
	*ppDisp = NULL;

CIdentArraySync Sync (this);		// make it threadsafe
CIdentArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CClassLock l(r);
	
		if (l && l -> IsValid() && !strcmp (pIdStr, l -> GetName())) 
			return ((_DGeoClass *)(CClass *)l) -> QueryInterface(IID_IDispatch,ppDisp);
	}
	return DISP_E_BADINDEX;
}


// Liefert das IDispatch-Interface auf die ObjektKlasse mit dem lIdent
// innerhalb dieses Array's
HRESULT CIdentArray::GetClassDispValue (ULONG lIdent, LPVOID *ppDisp)
{
	if (ppDisp == NULL) 
		return E_POINTER;
	*ppDisp = NULL;

CIdentArraySync Sync (this);		// make it threadsafe
CIdentArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CClassLock l(r);
	
		if (l && l -> IsValid() && lIdent == l -> GetValue()) 
			return ((_DGeoClass *)(CClass *)l) -> QueryInterface(IID_IDispatch,ppDisp);
	}
	return DISP_E_BADINDEX;
}

// Testen, ob Ident bereits in Container enthalten ist --------------------
long CIdentArray::hasIdent (ULONG lIdent)	// returns valid index
{
CIdentArraySync Sync (this);		// make it threadsafe
CIdentArrayRing r(*this);
long lIndex = 0;

	for (r.First(); r.Valid(); r.Next(), lIndex++) {
	CClassLock l(r);
	
		if (l && l -> IsValid() && lIdent == l -> GetValue()) 
			return lIndex;
	}
	return -1L;
}


// delete class --------------------------------------------------------------
bool CIdentArray::DeleteClass (ULONG lIdent)
{
CIdentArraySync Sync (this);		// make it threadsafe
CIdentArrayRing r(*this);
bool fDelete = false;

	for (r.First(); r.Valid(); r.Next()) {
	CClassLock l(r);
	
		if (l && lIdent == l -> GetValue (true)) {
			fDelete = true;
			break;
		}
	}
	if (fDelete && r.Valid()) 
		return r.Delete();
	return false;
}

// count valid GeoClasses ------------------------------------------------------
long CIdentArray::Count (void)
{
CIdentArraySync Sync (this);		// make it threadsafe
CIdentArrayRing r(*this);
long lCount = 0;

	for (r.First(); r.Valid(); r.Next()) {
	CClassLock l(r);

		if (l && l -> IsValid()) 
			lCount++;
	}
	return lCount;
}

// Refresh der Collection -----------------------------------------------------
HRESULT CIdentArray::Refresh (void)
{
CIdentArraySync Sync (this);		// make it threadsafe
CIdentArrayRing r(*this);
bool fDeleted = false;

	for (r.First(); r.Valid(); ) {
	bool fToDelete = false;

		{
		CClassLock l(r);
	
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


