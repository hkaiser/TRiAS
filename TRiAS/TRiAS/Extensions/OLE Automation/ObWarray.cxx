// ArrayContainer, Object Windows Collection -------------
// File: OBWARRAY.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "obwarray.hxx"
#include "objwin.hxx"
#include "enumobws.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CGeoObjWinArray::CGeoObjWinArray (void)
	: CGeoObjWinArrayBase (20, container_wrappers::CFSyncThreads)	// erstmal 20 Idents
{
	m_pICProc = NULL;
}


CGeoObjWinArray *CGeoObjWinArray::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	INITOBJWINCOLLECTIONPROC pICFcn, DWORD dwData)
{
CGeoObjWinArray *pOWArr = NULL;

	ATLTRY(pOWArr = new CGeoObjWinArray);
	if (pOWArr == NULL) return NULL;

// Array mit Object Window füllen	
INITOBJWINSTATUS rgStatus = INITOBJWINSTATUS_Error;

	{		// Container füllen
	CGeoObjWinArraySync Sync (pOWArr);		// make it threadsafe
	CGeoObjectWinCreator ObCr (*pOWArr);

		rgStatus = pICFcn (pUnk, pApp, pDoc, ObCr, dwData);
	}
	
	if (rgStatus == INITOBJWINSTATUS_Error) {
		DELETE_OBJ (pOWArr);
		return NULL;
	}
	return pOWArr;
}


// Kopieren des CGeoObjWinArray's -------------------------------------------------
CGeoObjWinArray *CGeoObjWinArray::Copy (void)
{
CGeoObjWinArraySync Sync (this);		// make it threadsafe
CGeoObjWinArray *pOWArr = NULL;

	ATLTRY(pOWArr = new CGeoObjWinArray);
	if (pOWArr == NULL) return NULL;

// neues Array mit Daten aus diesem Array füllen
CGeoObjWinArraySync SyncNew (pOWArr);		// make it threadsafe
CGeoObjectWinCreator ObCr (*pOWArr);
CGeoObjWinArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectWinLock l(r);
	
		if (!l || !l -> IsValid()) continue;
		
	// Pointer einfach in anderem Array mit abspeichern
		((_DGeoObjectWin *)(CGeoObjectWin *)l) -> AddRef();		// für neues Array festhalten
		ObCr.InsertPtr (l);	// Pointer einspeichern	
	}
	return pOWArr;		// liefert Pointer auf Kopie	
}

// LöschFunktion --------------------------------------------------------------
void _XTENSN_EXPORT CGeoObjWinArray::UserDelete (void *pObjWin)
{
	((_DGeoObjectWin *)(CGeoObjectWin *)pObjWin) -> Release();	// freigeben einer enthaltenen GeoObjectWin
}

// ZugriffsFunktion -----------------------------------------------------------
HWND CGeoObjWinArray::Value (LONG lIndex)
{
CGeoObjWinArraySync Sync (this);		// make it threadsafe
CGeoObjWinArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoObjectWinLock l(r);
	
		if (l && l -> IsValid()) 
			return l -> GetValue();
	}
	return NULL;	// Fehler
}

HWND CGeoObjWinArray::Value (LPCSTR pName)
{
CGeoObjWinArraySync Sync (this);		// make it threadsafe
CGeoObjWinArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectWinLock l(r);
	
		if (l && l -> IsValid() && !strcmp (pName, l -> GetName())) 
			return l -> GetValue();		// gefunden
	}
	return NULL;	// Fehler
}

// Liefert das IDispatch-Interface auf die Objekt Window mit dem lIndex
// innerhalb dieses Array's
HRESULT CGeoObjWinArray::GetObjectWinDisp (long lIndex, LPVOID *ppDisp)
{
	if (ppDisp == NULL) 
		return E_POINTER;
	*ppDisp = NULL;

CGeoObjWinArraySync Sync (this);		// make it threadsafe
CGeoObjWinArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoObjectWinLock l(r);
	
		if (l && l -> IsValid()) 
			return ((_DGeoObjectWin *)(CGeoObjectWin *)l) -> QueryInterface (IID_IDispatch, ppDisp);
	}
	return DISP_E_BADINDEX;
}

// Liefert das IDispatch-Interface auf die Objekt Window mit dem  pObWinStr
// innerhalb dieses Array's
HRESULT CGeoObjWinArray::GetObjectWinDisp (LPCSTR pObWinStr, LPVOID *ppDisp)
{
	if (ppDisp == NULL) 
		return E_POINTER;
	*ppDisp = NULL;

CGeoObjWinArraySync Sync (this);		// make it threadsafe
CGeoObjWinArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectWinLock l(r);
	
		if (l && l -> IsValid() && !strcmp (pObWinStr, l -> GetName())) 
			return ((_DGeoObjectWin *)(CGeoObjectWin *)l) -> QueryInterface(IID_IDispatch,ppDisp);
	}
	return DISP_E_BADINDEX;
}

// Liefert das IDispatch-Interface auf die Objekt Window mit dem hWnd
// innerhalb dieses Array's
HRESULT CGeoObjWinArray::GetObjectWinDispValue (HWND hWnd, LPVOID *ppDisp)
{
	if (ppDisp == NULL) 
		return E_POINTER;
	*ppDisp = NULL;

CGeoObjWinArraySync Sync (this);		// make it threadsafe
CGeoObjWinArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectWinLock l(r);
	
		if (l && l -> IsValid() && hWnd == l -> GetValue()) 
			return ((_DGeoObjectWin *)(CGeoObjectWin *)l) -> QueryInterface(IID_IDispatch,ppDisp);
	}
	return DISP_E_BADINDEX;
}

// Testen, ob Objekt Window bereits in Container enthalten ist --------------------
long CGeoObjWinArray::hasObjectWin (HWND hWnd)	// returns valid index
{
CGeoObjWinArraySync Sync (this);		// make it threadsafe
CGeoObjWinArrayRing r(*this);
long lIndex = 0;

	for (r.First(); r.Valid(); r.Next(), lIndex++) {
	CGeoObjectWinLock l(r);
	
		if (l && l -> IsValid() && hWnd == l -> GetValue()) 
			return lIndex;
	}
	return -1L;
}


// delete object --------------------------------------------------------------
bool CGeoObjWinArray::DeleteObjectWin (HWND hWnd)
{
CGeoObjWinArraySync Sync (this);		// make it threadsafe
CGeoObjWinArrayRing r(*this);
bool fDelete = false;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectWinLock l(r);
	
		if (l && hWnd == l -> GetValue (true)) {
			fDelete = true;
			break;
		}
	}
	if (fDelete && r.Valid()) 
		return r.Delete();
	return false;
}


// count valid Windows ------------------------------------------------------
long CGeoObjWinArray::Count (void)
{
CGeoObjWinArrayRing r(*this);
long lCount = 0;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoObjectWinLock l(r);

		if (l && l -> IsValid()) 
			lCount++;
	}
	return lCount;
}

// Refresh der Collection -----------------------------------------------------
HRESULT CGeoObjWinArray::Refresh (void)
{
CGeoObjWinArraySync Sync (this);		// make it threadsafe
CGeoObjWinArrayRing r(*this);
bool fDeleted = false;

	for (r.First(); r.Valid(); r.Next()) {
	bool fToDelete = false;

		{
		CGeoObjectWinLock l(r);
	
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

