// Implementation der typspezifischen TreeKlasse ------------------------------
// File: CONMTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "obj.hxx"

#include "conmtree.hxx"	// KlassenDeklarationen
#include "conmtree.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CObjNameTree::CObjNameTree (CTriasApp *pApp, CGeoDoc *pDoc)
	: CObjNameTreeBase ((CTTREEGETKEYFCN)FCTTreeGetObjBSTR, (CTTREECMPKEYFCN)FCTTreeCmpObjBSTR, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CObjNameTree);

	m_pDoc = pDoc;
//	ADDREF (m_pDoc);	// fully dependend
	
	m_pApp = pApp;
//	ADDREF (m_pApp);	// fully dependend
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CObjNameTree::~CObjNameTree (void)
{
	DESTRUCT_TRACE(CObjNameTree);

	EveryDelete();
	
//	RELEASE (m_pDoc);
// 	RELEASE (m_pApp);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
/*static*/
CGeoObject *CObjNameTree::FAddItem (LPCSTR bName, DGeoObject **ppIObj, GEOOBJECTMODE rgMode, VARIANT *pvClass)
{
CGeoObject *pObj = CGeoObject::CreateInstance ((DDocument *)m_pDoc, m_pApp, m_pDoc, bName, rgMode, pvClass);

	if (pObj == NULL) return NULL;

// wenn ein neues Objekt erzeugt werden soll, dann wird das neue Objekt über eine
// Notifikation in die Bäume reingebaut (von hinten), daher wird dieses Objekt hier 
// nicht mehr benötigt.
	TX_ASSERT(rgMode == GEOOBJECTMODE_Add || NULL == FFindItem (bName, pObj -> GetValue()));

	if (rgMode != GEOOBJECTMODE_Add) {
	CGeoObject2Creator Cr (*this);

		if (!Cr.InsertPtr (pObj)) {	// übernimmt RefCnt von pObj!
			delete pObj;
			return NULL;
		}
	} 
	else {
	// das Objekt wiederfinden, welches u.U. von hinten in die Bäume gebaut wurde
	CGeoObject *pObjHidden = FFindItem (bName, pObj -> GetValue());

		if (NULL != pObjHidden) {
			delete pObj;		// wird nicht mehr gebraucht
			pObj = pObjHidden;
		}
		else {
		CGeoObject2Creator Cr (*this);

			if (!Cr.InsertPtr (pObj)) {	// übernimmt RefCnt von pObj!
				delete pObj;
				return NULL;
			}
		}
	}

// request IID_IDispatch if requested
	if (ppIObj && FAILED(((DGeoObject *)pObj) -> QueryInterface (IID_DGeoObject, (LPVOID *)ppIObj))) {
		delete pObj;
		return NULL;
	}
	return pObj;
}

// Element hinzufügen
bool CObjNameTree::FAddItem (CGeoObject *pObj)
{
	if (pObj == NULL) return false;

CGeoObject2Creator Cr (*this);

	if (Cr.InsertPtr (pObj) != NULL) {
		ADDREF_CAST(_DGeoObject, pObj);
		return true;
	}
	return true;
}


// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CObjNameTree::FDeleteItem (LPCSTR rKT, LONG lONr)
{
CObjNameTreeTable t(*this);
bool fDelete = false;

	if (t.FindFirst ((LPVOID)rKT)) {
		
		do {
		CGeoObject2Lock l(t);

			TX_ASSERT(NULL != (CGeoObject *)l);
			if (!l) continue;

		LONG lONrFound = l -> GetValue (true);

			if (lONr == lONrFound || lONr == INVALID_ONR) {
				fDelete = true;		// gefunden oder erstbestes gefunden
				break;
			}
		} while (t.FindNext ((LPVOID)rKT));

		if (fDelete) return t.Delete();
	}
	return FALSE;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CGeoObject *CObjNameTree::FFindItem (LPCSTR rKT, LONG lONr)
{
CObjNameTreeTable t(*this);

	if (t.FindFirst ((LPVOID)rKT)) {

		do {
		CGeoObject2Lock l(t);

			TX_ASSERT(NULL != (CGeoObject *)l);
			if (!l) continue;

		LONG lONrFound = l -> GetValue();

			if (lONr == lONrFound || lONr == INVALID_ONR) 
				return l;		// gefunden oder erstbestes gefunden
		} while (t.FindNext ((LPVOID)rKT));
	}
	return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CObjNameTree::UserDelete (void *pObj)
{
	((CGeoObject *)pObj) -> Invalidate();
	((_DGeoObject *)(CGeoObject *)pObj) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPCSTR FCTTreeGetObjBSTR (CGeoObject *pObj)
{
	return ((CGeoObject *)pObj) -> FGetBSTR();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpObjBSTR (LPCSTR pObj1, LPCSTR pObj2)
{
	return FCmpBSTR (pObj1, pObj2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
bool CObjNameTree::FEnumAllItems (CGeoObjectEnumFunc pFcn, void *pEData)
{
CObjNameTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CGeoObject2Lock l(t);

		if (l && pFcn (*(CGeoObject *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CObjNameTree ::FEnumItems (LPCSTR rKey, CGeoObjectEnumFunc pFcn, void *pEData)
{
CObjNameTreeTable t(*this);

	for (t.FindFirst ((LPVOID)rKey); t.Valid(); t.FindNext ((LPVOID)rKey)) {
	CGeoObject2Lock l(t);

		if (l && pFcn (*(CGeoObject *)l, pEData) == FALSE)
			return FALSE;
	}
	return TRUE;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CObjNameTree::FReInsert (LPCSTR roldKey, LPCSTR rnewKey, LONG lONr)
{
CObjNameTreeTable t(*this);
bool fFound = false;

	if (t.FindFirst ((LPVOID)roldKey)) {
		
		do {
		CGeoObject2Lock l(t);

			TX_ASSERT(NULL != (CGeoObject *)l);
			if (!l) continue;

		LONG lONrFound = l -> GetValue();

			if (lONr == lONrFound || lONr == INVALID_ONR) {
				fFound = true;		// gefunden oder erstbestes gefunden
				break;
			}
		} while (t.FindNext ((LPVOID)roldKey));

		if (fFound) return t.ReInsert ((LPVOID)rnewKey, sizeof (rnewKey));
	}
	return FALSE;
}
#endif // defined(_USE_UNSAFE_REINSERT)
