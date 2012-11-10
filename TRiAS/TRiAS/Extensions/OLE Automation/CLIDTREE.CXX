// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: CLIDTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "class.hxx"

#include "clidtree.hxx"	// KlassenDeklarationen
#include "clidtree.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CIDTree::CIDTree (CTriasApp *pApp, CGeoDoc *pDoc)
	: CIDTreeBase ((CTTREEGETKEYFCN)FCTTreeGetClsULONG, (CTTREECMPKEYFCN)FCTTreeCmpClsULONG, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CIDTree);

	m_pDoc = pDoc;
//	ADDREF (m_pDoc);	// fully dependend
	
	m_pApp = pApp;
//	ADDREF (m_pApp);	// fully dependend
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CIDTree::~CIDTree (void)
{
	DESTRUCT_TRACE(CIDTree);

	EveryDelete();
	
//	RELEASE (m_pDoc);
//	RELEASE (m_pApp);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
CClass *CIDTree::FAddItem (ULONG lIdent, DGeoClass **ppICls, GEOCLASSMODE rgMode, LPCSTR pcSrc)
{
CClass *pCls = CClass::CreateInstance (
	(DDocument *)m_pDoc, m_pApp, m_pDoc, lIdent, rgMode, pcSrc);

	if (pCls == NULL) return NULL;

// add to tree
CClass1Creator Cr (*this);

	if (!Cr.InsertPtr (pCls)) {
		delete pCls;
		return NULL;
	}

// request IID_IDispatch if requested
	if (ppICls && FAILED(((DGeoClass *)pCls) -> QueryInterface (IID_DGeoClass, (LPVOID *)ppICls))) {
		delete pCls;
		return NULL;
	}
	return pCls;
}

// Element hinzufügen
bool CIDTree::FAddItem (CClass *pCls)
{
	if (pCls == NULL) return false;

CClass1Creator Cr (*this);

	if (Cr.InsertPtr (pCls) != NULL) {
		ADDREF_CAST(_DGeoClass, pCls);
		return true;
	}
	return false;
}


// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CIDTree::FDeleteItem (ULONG &rKT)
{
CIDTreeTable t(*this);

	if (t.Find (&rKT)) 
		return t.Delete();
	return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CClass *CIDTree::FFindItem (ULONG &rKT)
{
CIDTreeTable t(*this);

	if (t.Find (&rKT)) {
	CClass1Lock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CIDTree::UserDelete (void *pCls)
{
	((CClass *)pCls) -> Invalidate();
	((_DGeoClass *)(CClass *)pCls) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
ULONG *FCTTreeGetClsULONG (CClass *pCls)
{
	return & ((CClass *)pCls) -> FGetULONG();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpClsULONG (const ULONG *pCls1, const ULONG *pCls2)
{
	return FCmpULONG (*pCls1, *pCls2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
bool CIDTree::FEnumAllItems (CClassEnumFunc pFcn, void *pEData)
{
CIDTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CClass1Lock l(t);

		if (l && pFcn (*(CClass *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CIDTree::FEnumItems (ULONG &rKey, CClassEnumFunc pFcn, void *pEData)
{
CIDTreeTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CClass1Lock l(t);

		if (l && pFcn (*(CClass *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CIDTree::FReInsert (ULONG &roldKey, ULONG &rnewKey)
{
CIDTreeTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));
	return FALSE;
}
#endif // defined(_USE_UNSAFE_REINSERT)
