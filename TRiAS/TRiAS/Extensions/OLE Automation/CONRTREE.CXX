// Implementation der typspezifischen TreeKlasse ------------------------------
// File: CONRTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "obj.hxx"

#include "conrtree.hxx"	// KlassenDeklarationen
#include "conrtree.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CONrTree::CONrTree (CTriasApp *pApp, CGeoDoc *pDoc)
	: CONrTreeBase ((CTTREEGETKEYFCN)FCTTreeGetObjLONG, (CTTREECMPKEYFCN)FCTTreeCmpObjLONG, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CONrTree);

	m_pDoc = pDoc;
//	ADDREF (m_pDoc);	// fully dependend
	
	m_pApp = pApp;
// 	ADDREF (m_pApp);	// fully dependend
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CONrTree::~CONrTree (void)
{
	DESTRUCT_TRACE(CONrTree);

	EveryDelete();
	
//	RELEASE (m_pDoc);
//	RELEASE (m_pApp);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
CGeoObject *CONrTree::FAddItem (LONG lONr, DGeoObject **ppIObj, GEOOBJECTMODE rgMode, VARIANT *pvClass)
{
CGeoObject *pObj = CGeoObject::CreateInstance ((DDocument *)m_pDoc, m_pApp, m_pDoc, lONr, rgMode, pvClass);

	if (pObj == NULL) return NULL;

// add to tree
CGeoObject1Creator Cr (*this);

	if (!Cr.InsertPtr (pObj)) {
		delete pObj;
		return NULL;
	}

// request IID_IDispatch if requested
	if (ppIObj && FAILED(((DGeoObject *)pObj) -> QueryInterface (IID_DGeoObject, (LPVOID *)ppIObj))) {
		delete pObj;
		return NULL;
	}
	return pObj;
}

// Element hinzufügen
bool CONrTree::FAddItem (CGeoObject *pObj)
{
	if (pObj == NULL) return false;

CGeoObject1Creator Cr (*this);

	if (Cr.InsertPtr (pObj) != NULL) {
		ADDREF_CAST(_DGeoObject, pObj);
		return true;
	}
	return false;
}


// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CONrTree::FDeleteItem (const LONG &rKT)
{
CONrTreeTable t(*this);

	if (t.Find (const_cast<long *>(&rKT))) 
		return t.Delete();
	return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CGeoObject *CONrTree::FFindItem (const LONG &rKT)
{
CONrTreeTable t(*this);

	if (t.Find (const_cast<long *>(&rKT))) {
	CGeoObject1Lock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CONrTree::UserDelete (void *pObj)
{
	((CGeoObject *)pObj) -> Invalidate();
	((_DGeoObject *)(CGeoObject *)pObj) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LONG *FCTTreeGetObjLONG (CGeoObject *pObj)
{
	return & ((CGeoObject *)pObj) -> FGetLONG();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpObjLONG (LONG *pObj1, LONG *pObj2)
{
	return FCmpLONG (*pObj1, *pObj2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
bool CONrTree::FEnumAllItems (CGeoObjectEnumFunc pFcn, void *pEData)
{
CONrTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CGeoObject1Lock l(t);

		if (l && pFcn (*(CGeoObject *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CONrTree ::FEnumItems (LONG &rKey, CGeoObjectEnumFunc pFcn, void *pEData)
{
CONrTreeTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CGeoObject1Lock l(t);

		if (l && pFcn (*(CGeoObject *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CONrTree ::FReInsert (const LONG &roldKey, LONG &rnewKey)
{
CONrTreeTable t(*this);

	if (t.Find (const_cast<long *>(&roldKey))) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));

	return FALSE;
}
#endif // defined(_USE_UNSAFE_REINSERT)
