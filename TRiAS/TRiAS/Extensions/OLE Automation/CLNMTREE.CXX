// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: CLNMTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "class.hxx"

#include "clnmtree.hxx"	// KlassenDeklarationen
#include "clnmtree.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CClsNameTree::CClsNameTree (CTriasApp *pApp, CGeoDoc *pDoc)
	: CClsNameTreeBase ((CTTREEGETKEYFCN)FCTTreeGetClsBSTR, (CTTREECMPKEYFCN)FCTTreeCmpClsBSTR, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CClsNameTree);

	m_pDoc = pDoc;
//	ADDREF (m_pDoc);	// fully dependend
	
	m_pApp = pApp;
//	ADDREF (m_pApp);	// fully dependend
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CClsNameTree::~CClsNameTree (void)
{
	DESTRUCT_TRACE(CClsNameTree);

	EveryDelete();
	
//	RELEASE (m_pDoc);
//	RELEASE (m_pApp);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
CClass *CClsNameTree::FAddItem (LPCSTR bName, DGeoClass **ppICls, GEOCLASSMODE rgMode, LPCSTR pcSrc)
{
CClass *pCls = CClass::CreateInstance ((_DDocument *)m_pDoc, m_pApp, m_pDoc, bName, rgMode, pcSrc);

	if (pCls == NULL) return NULL;

// wenn eine neue Klasse erzeugt werden soll, dann wird die neue Klasse u.U. über eine
// Notifikation in die Bäume reingebaut (von hinten), daher wird diese Klasse hier 
// nicht mehr benötigt.
	TX_ASSERT(rgMode == GEOCLASSMODE_Add || NULL == FFindItem (bName));

	if (rgMode != GEOCLASSMODE_Add) {
	CClass2Creator Cr (*this);

		if (!Cr.InsertPtr (pCls)) {	// übernimmt RefCnt von pObj!
			delete pCls;
			return NULL;
		}
	} 
	else {
	// die Klasse wiederfinden, welche u.U. von hinten in die Bäume gebaut wurde
	CClass *pClsHidden = FFindItem (bName);

		if (NULL != pClsHidden) {
			delete pCls;		// wird nicht mehr gebraucht
			pCls = pClsHidden;
		}
		else {
		CClass2Creator Cr (*this);

			if (!Cr.InsertPtr (pCls)) {		// übernimmt RefCnt von pCls!
				delete pCls;
				return NULL;
			}
		}
	}

// request IID_IDispatch if requested
	if (ppICls && FAILED(((DGeoClass *)pCls) -> QueryInterface (IID_DGeoClass, (LPVOID *)ppICls))) {
		delete pCls;
		return NULL;
	}
	return pCls;
}

// Element hinzufügen
bool CClsNameTree::FAddItem (CClass *pCls)
{
	if (pCls == NULL) return false;

CClass2Creator Cr (*this);

	if (Cr.InsertPtr (pCls) != NULL) {
		ADDREF_CAST(_DGeoClass, pCls);
		return true;
	}
	return true;
}


// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CClsNameTree::FDeleteItem (LPCSTR rKT)
{
CClsNameTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) 
		return t.Delete();
	return FALSE;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CClass *CClsNameTree::FFindItem (LPCSTR rKT)
{
CClsNameTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) {
	CClass2Lock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CClsNameTree::UserDelete (void *pCls)
{
	((CClass *)pCls) -> Invalidate();
	((_DGeoClass *)(CClass *)pCls) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPCSTR FCTTreeGetClsBSTR (CClass *pCls)
{
	return ((CClass *)pCls) -> FGetBSTR();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpClsBSTR (LPCSTR pCls1, LPCSTR pCls2)
{
	return FCmpBSTR (pCls1, pCls2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
bool CClsNameTree::FEnumAllItems (CClassEnumFunc pFcn, void *pEData)
{
CClsNameTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CClass2Lock l(t);

		if (l && pFcn (*(CClass *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CClsNameTree::FEnumItems (LPCSTR rKey, CClassEnumFunc pFcn, void *pEData)
{
CClsNameTreeTable t(*this);

	for (t.FindFirst ((LPVOID)rKey); t.Valid(); t.FindNext ((LPVOID)rKey)) {
	CClass2Lock l(t);

		if (l && pFcn (*(CClass *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CClsNameTree::FReInsert (LPCSTR roldKey, LPCSTR rnewKey)
{
CClsNameTreeTable t(*this);

	if (t.Find ((LPVOID)roldKey)) 
		return t.ReInsert ((LPVOID)rnewKey, sizeof (rnewKey));

	return FALSE;
}
#endif // defined(_USE_UNSAFE_REINSERT)
