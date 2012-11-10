// ArrayContainer, der Views Collection hält -------------
// File: VIEWARRY.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "viewarry.hxx"		// CGeoViewsArray
#include "enuviews.hxx"		// CEnumViews
#include "view.hxx"			// CGeoView

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor/Destruktor/Initialisierung  -------------------------------------
CGeoViewsArray::CGeoViewsArray (void)
	: CGeoViewsArrayBase (20, container_wrappers::CFNoSpecial)	// erstmal 20 Views
{
	m_pICProc = NULL;
}


CGeoViewsArray *CGeoViewsArray::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, INITVIEWCOLLECTIONPROC pICFcn, DWORD dwData)
{
CGeoViewsArray *pViewsArr = NULL;

	ATLTRY(pViewsArr = new CGeoViewsArray);
	if (pViewsArr == NULL) return NULL;

// Array mit View füllen	
INITVIEWSTATUS rgStatus = INITVIEWSTATUS_Error;

	{		// Container füllen
	CGeoViewCreator ViewCr (*pViewsArr);
		
		rgStatus = pICFcn (pUnk, pApp, pDoc, ViewCr, dwData);
	}
	
	if (rgStatus == INITVIEWSTATUS_Error) {
		DELETE_OBJ (pViewsArr);
		return NULL;
	}
	return pViewsArr;
}


// Kopieren des CGeoViewsArray's -------------------------------------------------
CGeoViewsArray *CGeoViewsArray::Copy (void)
{
CGeoViewsArray *pViewsArr = NULL;

	ATLTRY(pViewsArr = new CGeoViewsArray);
	if (pViewsArr == NULL) return NULL;

// neues Array mit Daten aus diesem Array füllen
CGeoViewCreator ViewCr (*pViewsArr);
CGeoViewsArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoViewLock l(r);
	
		if (!l || !l -> IsValid()) continue;
		
	// Pointer einfach in anderem Array mit abspeichern
		((_DView *)(CGeoView *)l) -> AddRef();			// für neues Array festhalten
		ViewCr.InsertPtr (l);	// Pointer einspeichern	
	}
	return pViewsArr;		// liefert Pointer auf Kopie	
}



// LöschFunktion --------------------------------------------------------------
void _XTENSN_EXPORT CGeoViewsArray::UserDelete (void *pView)
{
	((_DView *)(CGeoView *)pView) -> Release();	// freigeben einer enthaltenen View
}


// ZugriffsFunktion -----------------------------------------------------------

// Liefert View  mit dem Index lIndex innerhalb des 
// Array's
char *CGeoViewsArray::Value (ULONG lIndex)
{
CGeoViewsArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoViewLock l(r);
	
		if (l && l -> IsValid()) 
			return (char *)l -> GetValue();
	}
	return NULL;	// Fehler
}


// Liefert View mit dem Index lIndex innerhalb des 
// Array's ausgehend vom KurzText
char *CGeoViewsArray::Value (LPCSTR bstrName)
{
CGeoViewsArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoViewLock l(r);
	
		if (l && l -> IsValid() && !strcmp (bstrName, l -> GetName())) 
			return (char *)l -> GetValue();		// gefunden
	}
	return NULL;	// Fehler
}

// Liefert das IDispatch-Interface auf die Views mit dem lIndex
// innerhalb dieses Array's
HRESULT CGeoViewsArray::GetViewDisp (ULONG lIndex, LPVOID *ppDisp)
{
	if (ppDisp == NULL) 
		return E_POINTER;
	*ppDisp = NULL;

CGeoViewsArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoViewLock l(r);
	
		if (l && l -> IsValid()) 
			return ((_DView *)(CGeoView *)l) -> QueryInterface(IID_IDispatch,ppDisp);
	}
	return DISP_E_BADINDEX;
}


// Liefert das IDispatch-Interface auf die Views mit dem  pViewStr
// innerhalb dieses Array's
HRESULT CGeoViewsArray::GetViewDisp (LPCSTR pViewStr, LPVOID *ppDisp)
{
	if (ppDisp == NULL) 
		return E_POINTER;
	*ppDisp = NULL;

CGeoViewsArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoViewLock l(r);
	
		if (l && l -> IsValid() && !strcmp (pViewStr, l -> GetName())) 
			return ((_DView *)(CGeoView *)l) -> QueryInterface(IID_IDispatch,ppDisp);
	}
	return DISP_E_BADINDEX;
}


// Testen, ob Sicht bereits in Container enthalten ist --------------------
long CGeoViewsArray::hasView (LPCSTR bName)	// returns valid index
{
CGeoViewsArrayRing r(*this);
long lIndex = 0;

	for (r.First(); r.Valid(); r.Next(), lIndex++) {
	CGeoViewLock l(r);
	
		if (l && l -> IsValid() && !strcmp (l -> GetName(), bName)) 
			return lIndex;
	}
	return -1L;
}

// delete object --------------------------------------------------------------
bool CGeoViewsArray::DeleteView (LPCSTR bName)
{
CGeoViewsArrayRing r(*this);
bool fDelete = false;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoViewLock l(r);
	
		if (l && !strcmp (l -> GetName (true), bName)) {
			fDelete = true;
			break;
		}
	}
	if (fDelete && r.Valid()) return r.Delete();
	
return false;
}

// count valid Views ------------------------------------------------------
long CGeoViewsArray::Count (void)
{
CGeoViewsArrayRing r(*this);
long lCount = 0;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoViewLock l(r);

		if (l && l -> IsValid()) 
			lCount++;
	}
	return lCount;
}

// Refresh der Collection -----------------------------------------------------
HRESULT CGeoViewsArray::Refresh (void)
{
CGeoViewsArraySync Sync (this);		// make it threadsafe
CGeoViewsArrayRing r(*this);
bool fDeleted = false;

	for (r.First(); r.Valid(); ) {
	bool fToDelete = false;

		{
		CGeoViewLock l(r);
	
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


