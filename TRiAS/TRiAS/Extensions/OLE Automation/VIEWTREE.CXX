// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: VIEWTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "view.hxx"

#include "viewtree.hxx"	// KlassenDeklarationen
#include "viewtree.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Initialisierung ------------------------------------------------------------
CViewTree *CViewTree::CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc)
{
CViewTree *pView = NULL;

	ATLTRY(pView = new CViewTree());
	if (pView == NULL || !pView -> FInit (pApp, pDoc)) {
		DELETE_OBJ (pView);
		return NULL;
	}
	return pView;
}

bool CViewTree::FInit (CTriasApp *pApp, CGeoDoc *pDoc)
{
	m_pApp = pApp;
//	ADDREF (m_pApp);	// fully dependend

	m_pDoc = pDoc;
//	ADDREF (m_pDoc);	// fully dependend
	return true;
}


// Konstruktor der typspezifischen TreeKlasse ---------------------------------
CViewTree::CViewTree (void)
	: CViewTreeBase ((CTTREEGETKEYFCN)FCTTreeGetViewBSTR, (CTTREECMPKEYFCN)FCTTreeCmpViewBSTR, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CViewTree);
	
	m_pApp = NULL;
	m_pDoc = NULL;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CViewTree::~CViewTree (void)
{
	DESTRUCT_TRACE(CViewTree);
	
	EveryDelete();
	
//	RELEASE (m_pDoc);
//	RELEASE (m_pApp);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
CGeoView *CViewTree::FAddItem (LPCSTR pName, DView **ppIView, VIEWMODE rgMode)
{
CViewTreeSync Sync (this);
CGeoView *pView = FFindItem (pName);

	if (NULL == pView) {
		pView = CGeoView::CreateInstance ((DDocument *)m_pDoc, m_pApp, m_pDoc, pName, rgMode);
		if (NULL == pView) return NULL;
		
	// wenn eine neue Ansicht erzeugt werden soll, dann wird die neue Ansicht u.U. über eine
	// Notifikation in die Bäume reingebaut (von hinten), daher wird diese Ansicht hier 
	// nicht mehr benötigt.
		if (rgMode != VIEWMODE_Add) {
		CGeoView2Creator Cr (*this);

			if (!Cr.InsertPtr (pView)) {
				delete pView;
				return NULL;
			}
		} 
		else {
		// die Ansicht wiederfinden, welche von hinten in die Bäume gebaut wurde
		CGeoView *pViewHidden = FFindItem (pName);

			if (NULL != pViewHidden) {
				delete pView;		// wird nicht mehr gebraucht
				pView = pViewHidden;
			} 
			else {
			CGeoView2Creator Cr (*this);

				if (!Cr.InsertPtr (pView)) {
					delete pView;
					return NULL;
				}
			}
		}
	}

// request IID_IDispatch if requested
	if (ppIView && FAILED(((DView *)pView) -> QueryInterface (IID_DView, (LPVOID *)ppIView))) {
		delete pView;
		return NULL;
	}
	return pView;
}

// add existend View to tree -------------------------------------------------
bool CViewTree::FAddItem (CGeoView *pView)
{
CViewTreeSync Sync (this);

	if (pView == NULL) return NULL;

CGeoView2Creator Cr (*this);

	if (!Cr.InsertPtr (pView)) {
		delete pView;
		return false;
	}
	((_DView *)pView) -> AddRef();
	return true;
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CViewTree::FDeleteItem (LPCSTR rKT)
{
// remove physically
CViewTreeSync Sync (this);
CGeoView *pView = FFindItem (rKT);

	if (pView == NULL)
		return DEX_DeleteSight (rKT);	

	pView -> Remove();	// remove physically

// remove from tree
CViewTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) 
		return t.Delete();
	return false;
}

bool CViewTree::FInvalidateItem (LPCSTR pName)
{
// remove from tree, invalidate
CViewTreeSync Sync (this);
CGeoView *pView = FFindItem (pName);

	if (pView == NULL) 
		return true;

	pView -> Invalidate();

// remove from tree
CViewTreeTable t(*this);
bool fResult = false;

	if (t.Find ((LPVOID)pName)) 
		fResult = t.Delete();
	return fResult;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CGeoView *CViewTree::FFindItem (LPCSTR rKT)
{
CViewTreeSync Sync (this);
CViewTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) {
	CGeoView2Lock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}


bool CViewTree::SetViewName (LPCSTR bOldName, LPCSTR bNewName)
{
CViewTreeSync Sync (this);
CGeoView *pView = FFindItem (bOldName);

	if (pView == NULL) return false;
	
	((_DView *)pView) -> AddRef();		// ???? Release() ????
	
LPCSTR bName = pView -> GetName();

	if (!strcmp (bName, bNewName)) return true;
	
	if (FDeleteItem (bName)) {
		if (!pView -> SetName (bNewName, true))
			return false;
		pView -> Validate();
		return FAddItem (pView);
	}
	return false;
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CViewTree::UserDelete (void *pView)
{
	((CGeoView *)pView) -> Invalidate();
	((_DView *)(CGeoView *)pView) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPCSTR FCTTreeGetViewBSTR (CGeoView *pView)
{
	return ((CGeoView *)pView) -> FGetBSTR();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpViewBSTR (LPCSTR pView1, LPCSTR pView2)
{
	return FCmpBSTR (pView1, pView2);
}

// Enumeration aller Items in dem Baum ----------------------------------------
bool CViewTree::FEnumAllItems (CGeoViewEnumFunc pFcn, void *pEData)
{
CViewTreeSync Sync (this);
CViewTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CGeoView2Lock l(t);

		if (l && pFcn (*(CGeoView *)l, pEData) == false)
			return false;
	}
	return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CViewTree::FEnumItems (LPCSTR rKey, CGeoViewEnumFunc pFcn, void *pEData)
{
CViewTreeSync Sync (this);
CViewTreeTable t(*this);

	for (t.FindFirst ((LPVOID)rKey); t.Valid(); t.FindNext ((LPVOID)rKey)) {
	CGeoView2Lock l(t);

		if (l && pFcn (*(CGeoView *)l, pEData) == false)
			return false;
	}
	return true;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CViewTree::FReInsert (LPCSTR roldKey, LPCSTR rnewKey)
{
CViewTreeSync Sync (this);
CViewTreeTable t(*this);

	if (t.Find ((LPVOID)roldKey)) 
		return t.ReInsert ((LPVOID)rnewKey, sizeof (rnewKey));

	return false;
}
#endif // defined(_USE_UNSAFE_REINSERT)
