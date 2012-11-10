// GeoObjWin Tree -----------------------------------------------
// File: OWINTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>
#include <ScopeVar.h>

#include "objwin.hxx"

#include "owintree.hxx"
#include "owintree.inl"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// constructor/destructor/initialisation --------------------------------------
CObjWinTree *CObjWinTree::CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc)
{
CObjWinTree *pOWTr = NULL;

	ATLTRY(pOWTr = new CObjWinTree());
	if (pOWTr == NULL || !pOWTr -> FInit (pApp, pDoc)) {
		DELETE_OBJ (pOWTr);
		return NULL;
	}
	return pOWTr;
}

bool CObjWinTree::FInit (CTriasApp *pApp, CGeoDoc *pDoc)
{
	m_pApp = pApp;
//	ADDREF (m_pApp);	// fully dependend

	m_pDoc = pDoc;
//	ADDREF (m_pDoc);	// fully dependend
	return true;
}

CObjWinTree::CObjWinTree (void)
	: CObjWinTreeBase ((CTTREEGETKEYFCN)FCTTreeGetObjWinHWND, (CTTREECMPKEYFCN)FCTTreeCmpObjWinHWND, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CObjWinTree);
	
	m_pApp = NULL;
	m_pDoc = NULL;

	m_fCreating = false;
}               

CObjWinTree::~CObjWinTree (void)
{
	DESTRUCT_TRACE(CObjWinTree);
	
	EveryDelete();
	
//	RELEASE (m_pDoc);
//	RELEASE (m_pApp);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
CGeoObjectWin *CObjWinTree::FAddItem (HWND hWnd, DGeoObjectWin **ppIWin, GEOOBJWINMODE rgMode)
{
CObjWinTreeSync Sync (this);
CGeoObjectWin *pObjWin = NULL;

	if (GEOOBJWINMODE_Get == rgMode || GEOOBJWINMODE_Replace == rgMode)
		pObjWin = FFindItem (hWnd);

	if (NULL == pObjWin) {
	// Rekursion verhindern
		if (m_fCreating) return NULL;

	CScopeVar<bool> fCreating (m_fCreating, true);

		pObjWin = CGeoObjectWin::CreateInstance (
					(DDocument *)m_pDoc, m_pApp, m_pDoc, hWnd, rgMode);
		if (NULL == pObjWin) return NULL;

	// add to tree
	CGeoObjectWin2Creator Cr (*this);

		if (!Cr.InsertPtr (pObjWin)) {
			delete pObjWin;
			return NULL;
		}
	}

// request IID_IDispatch if requested
	if (ppIWin && FAILED(((DGeoObjectWin *)pObjWin) -> QueryInterface (IID_DGeoObjectWin, (LPVOID *)ppIWin))) {
		delete pObjWin;
		return NULL;
	}
	return pObjWin;
}

CGeoObjectWin *CObjWinTree::FAddItem (LPCSTR bName, DGeoObjectWin **ppIWin, GEOOBJWINMODE rgMode)
{
CObjWinTreeSync Sync (this);
CGeoObjectWin *pObjWin = NULL;

	if (GEOOBJWINMODE_Get == rgMode || GEOOBJWINMODE_Replace == rgMode)
		pObjWin = FFindItem (bName);

	if (NULL == pObjWin) {
	// Rekursion verhindern
		if (m_fCreating) return NULL;

	CScopeVar<bool> fCreating (m_fCreating, true);

		pObjWin = CGeoObjectWin::CreateInstance (
					(DDocument *)m_pDoc, m_pApp, m_pDoc, bName, rgMode);
		if (NULL == pObjWin) return NULL;

	// add to tree
	CGeoObjectWin2Creator Cr (*this);

		if (!Cr.InsertPtr (pObjWin)) {
			delete pObjWin;
			return NULL;
		}
	}

// request IID_IDispatch if requested
	if (ppIWin && FAILED(((_DGeoObjectWin *)pObjWin) -> QueryInterface (IID_DGeoObjectWin, (LPVOID *)ppIWin))) {
		delete pObjWin;
		return NULL;
	}
	return pObjWin;
}

													 
// Element hinzufügen
bool CObjWinTree::FAddItem (CGeoObjectWin *pObjWin)
{
	if (pObjWin == NULL) return false;

CObjWinTreeSync Sync (this);
CGeoObjectWin2Creator Cr (*this);

	if (Cr.InsertPtr (pObjWin) != NULL) {
		((_DGeoObjectWin *)pObjWin) -> AddRef();
		return true;
	}
	return false;
}


// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CObjWinTree::FDeleteItem (HWND &rKT)
{
CObjWinTreeSync Sync (this);
CObjWinTreeTable t(*this);

	if (t.Find (&rKT)) {
	CGeoObjectWin *pWin = NULL;

		{
		CGeoObjectWin2Lock l(t);
			
			pWin = (CGeoObjectWin *)l;
		} // lock should go out of scope
		return pWin -> Remove();
	}
	return DEX_RemoveORWnd (rKT);
}

bool CObjWinTree::FInvalidateItem (HWND &rKT)
{
// invalidate
CObjWinTreeSync Sync (this);
CGeoObjectWin *pObjWin = FFindItem (rKT);

	if (pObjWin == NULL) 
		return true;

	pObjWin -> Invalidate();

// remove from tree
CObjWinTreeTable t(*this);
bool fResult = false;

	if (t.Find (&rKT)) 
		fResult = t.Delete();
	return fResult;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CGeoObjectWin *CObjWinTree::FFindItem (HWND &rKT)
{
CObjWinTreeSync Sync (this);
CObjWinTreeTable t(*this);

	if (t.Find (&rKT)) {
	CGeoObjectWin2Lock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}

CGeoObjectWin *CObjWinTree::FFindItem (LPCSTR pcName)
{
HWND hWnd = GethWndFromObjWinName (pcName);

	if (INVALID_HWND != hWnd)
		return FFindItem (hWnd);

	return NULL;
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CObjWinTree::UserDelete (void *pObjWin)
{
	((CGeoObjectWin *)pObjWin) -> Invalidate();
	((_DGeoObjectWin *)(CGeoObjectWin *)pObjWin) -> Release();
}

bool CObjWinTree::SetObjWinName (HWND hWnd, LPCSTR bNewName) 
{
CObjWinTreeSync Sync (this);
CGeoObjectWin *pObjWin = FFindItem (hWnd);

	if (pObjWin == NULL) return false;
	
LPCSTR bName = pObjWin -> GetName();

	if (!strcmp (bName, bNewName)) 
		return true;
	
	return pObjWin -> SetName (bNewName, true, true);
}

bool CmpCaptions (LPCSTR pCap1, LPCSTR pCap2)
{
char *pLast1 = strrchr (pCap1, '(');
char *pLast2 = strrchr (pCap2, '(');
int iLen1 = (NULL != pLast1) ? pLast1-pCap1-1 : strlen(pCap1);
int iLen2 = (NULL != pLast2) ? pLast2-pCap2-1 : strlen(pCap2);

	if (iLen1 == iLen2) 
		return !strncmp (pCap1, pCap2, iLen1);	
	return false;
}

HWND CObjWinTree::GethWndFromObjWinName (LPCSTR bName)	// find hWnd
{
CObjWinTreeSync Sync (this);
CObjWinTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CGeoObjectWin2Lock l(t);

		if (!l) continue;

	char cbCaption[_MAX_PATH];
	HWND hWnd = l -> FGetHWND();

		::GetWindowText (hWnd, cbCaption, sizeof(cbCaption));
		if (CmpCaptions (bName, cbCaption))
			return hWnd;
	}
	return NULL;
}


// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
HWND *FCTTreeGetObjWinHWND (CGeoObjectWin *pObjWin)
{
	return & ((CGeoObjectWin *)pObjWin) -> FGetHWND();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpObjWinHWND (HWND *pObjWin1, HWND *pObjWin2)
{
	return FCmpHWND (*pObjWin1, *pObjWin2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
bool CObjWinTree::FEnumAllItems (CGeoObjectWinEnumFunc pFcn, void *pEData)
{
CObjWinTreeSync Sync (this);
CObjWinTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CGeoObjectWin2Lock l(t);

		if (l && pFcn (*(CGeoObjectWin *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CObjWinTree::FEnumItems (HWND &rKey, CGeoObjectWinEnumFunc pFcn, void *pEData)
{
CObjWinTreeSync Sync (this);
CObjWinTreeTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CGeoObjectWin2Lock l(t);

		if (l && pFcn (*(CGeoObjectWin *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CObjWinTree::FReInsert (HWND &roldKey, HWND &rnewKey)
{
CObjWinTreeSync Sync (this);
CObjWinTreeTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));

	return FALSE;
}
#endif // defined(_USE_UNSAFE_REINSERT)

