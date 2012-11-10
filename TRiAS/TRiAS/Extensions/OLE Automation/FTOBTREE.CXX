// Implementation der typspezifischen TreeKlasse ------------------------------
// File: FTOBTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "obj.hxx"

#include "feat.hxx"

#include "ftobtree.hxx"	// KlassenDeklarationen
#include "ftobtree.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Initialisierung ------------------------------------------------------------
CFeatObjTree *CFeatObjTree::CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc, IDispatch *pObj)
{
CFeatObjTree *pFeat = NULL;

	ATLTRY(pFeat = new CFeatObjTree());
	if (pFeat == NULL || !pFeat -> FInit (pApp, pDoc, pObj)) {
		DELETE_OBJ (pFeat);
		return NULL;
	}
	return pFeat;
}

bool CFeatObjTree::FInit (CTriasApp *pApp, CGeoDoc *pDoc, IDispatch *pObj)
{
	m_pApp = pApp;
//	ADDREF (m_pApp);	// fully dependend

	m_pDoc = pDoc;
//	ADDREF (m_pDoc);	// fully dependend

	m_pObj = pObj;
//	ADDREF (m_pObj);	// fully dependend
	return true;
}


// Konstruktor der typspezifischen TreeKlasse ---------------------------------
CFeatObjTree::CFeatObjTree (void)
	: CFeatObjTreeBase ((CTTREEGETKEYFCN)FCTTreeGetObjFeatBSTR, (CTTREECMPKEYFCN)FCTTreeCmpObjFeatBSTR, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CFeatObjTree);
	
	m_pApp = NULL;
	m_pDoc = NULL;
	m_pObj = NULL;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CFeatObjTree::~CFeatObjTree (void)
{
	DESTRUCT_TRACE(CFeatObjTree);
	
	EveryDelete();
	
//	RELEASE (m_pObj);
//	RELEASE (m_pDoc);
//	RELEASE (m_pApp);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
CGeoFeatureBase *CFeatObjTree::FAddItem (
	LPCSTR pName, DGeoFeature **ppIFeat, FEATUREMODE rgMode, 
	PROPCAPS rgProps, VARIANT *pvOptData, IObjectProperty *pIObjProp)
{
CFeatObjTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (pName);

	if (NULL == pFeat) {
	LONG lValue = 0;
	CGeoObject *pObj = NULL;
	CClass *pCls = NULL;
	
		if (SUCCEEDED(m_pObj -> QueryInterface (CLSID_GeoObject, (LPVOID *)&pObj)))	 
			lValue = pObj -> GetValue();
		else if (SUCCEEDED(m_pObj -> QueryInterface (CLSID_GeoClass, (LPVOID *)&pCls)))
			lValue = pCls -> GetValue();
		else
			return NULL;		// Fehler

		pFeat = CGeoFeatureObj::CreateInstance (
					m_pObj, m_pApp, m_pDoc, pName, 
					lValue, rgMode, rgProps, pvOptData, pIObjProp);
		if (pFeat == NULL) return NULL;

	// wenn ein neues Merkmal erzeugt werden soll, dann wird das neue Merkmal u.U. über eine
	// Notifikation in die Bäume reingebaut (von hinten), daher wird dieses Merkmal hier 
	// nicht mehr benötigt.
		TX_ASSERT(rgMode == FEATUREMODE_Add || NULL == FFindItem (pName));

		if (rgMode != FEATUREMODE_Add) {
		CGeoFeatureBase3Creator Cr (*this);

			if (!Cr.InsertPtr (pFeat)) {	// übernimmt RefCnt von pObj!
				delete pFeat;
				return NULL;
			}
		} 
		else {
		// die Klasse wiederfinden, welche u.U. von hinten in die Bäume gebaut wurde
		CGeoFeatureBase *pFeatHidden = FFindItem (pName);

			if (NULL != pFeatHidden) {
				delete pFeat;		// wird nicht mehr gebraucht
				pFeat = pFeatHidden;
			}
			else {
			CGeoFeatureBase3Creator Cr (*this);

				if (!Cr.InsertPtr (pFeat)) {	// übernimmt RefCnt von pFeat!
					delete pFeat;
					return NULL;
				}
			}
		}
	}

// request IID_IDispatch if requested
	if (ppIFeat && FAILED(((DGeoFeature *)pFeat) -> QueryInterface (IID_DGeoFeature, (LPVOID *)ppIFeat))) {
		delete pFeat;
		return NULL;
	}
	return pFeat;
}

// add existend View to tree -------------------------------------------------
bool CFeatObjTree::FAddItem (CGeoFeatureBase *pFeat)
{
CFeatObjTreeSync Sync (this);

	if (pFeat == NULL) return NULL;

CGeoFeatureBase3Creator Cr (*this);

	if (!Cr.InsertPtr (pFeat)) {
		delete pFeat;
		return false;
	}
	((_DGeoFeature *)pFeat) -> AddRef();
	return true;
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CFeatObjTree::FDeleteItem (LPCSTR rKT)
{
// remove physically
CFeatObjTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (rKT);

	if (pFeat == NULL) 
		return false;	// SUCCEEDED(m_pApp -> RemoveObjectProperty (rKT, m_pObj -> GetValue()));

	pFeat -> Remove();

// remove from tree
CFeatObjTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) 
		return t.Delete();
	return false;
}

bool CFeatObjTree::FInvalidateItem (LPCSTR pName)
{
// remove from tree, invalidate
CFeatObjTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (pName);

	if (pFeat == NULL) 
		return true;

	pFeat -> Invalidate();

// remove from tree
CFeatObjTreeTable t(*this);
bool fResult = false;

	if (t.Find ((LPVOID)pName)) 
		fResult = t.Delete();
	return fResult;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CGeoFeatureBase *CFeatObjTree::FFindItem (LPCSTR rKT)
{
CFeatObjTreeSync Sync (this);
CFeatObjTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) {
	CGeoFeatureBase3Lock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}


bool CFeatObjTree::SetFeatureName (LPCSTR bOldName, LPCSTR bNewName)
{
CFeatObjTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (bOldName);

	if (pFeat == NULL) return false;
	
LPCSTR bName = pFeat -> GetName();

	if (!strcmp (bName, bNewName)) 
		return true;
	
WUnknown Wrapper ((_DGeoFeature *)pFeat);		// festhalten

	if (FDeleteItem (bName)) {
		if (!pFeat -> SetName (bNewName, true))
			return false;
		pFeat -> Validate();
		return FAddItem (pFeat);
	}
	return false;
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CFeatObjTree::UserDelete (void *pFeat)
{
	((CGeoFeatureBase *)pFeat) -> Invalidate();
	((_DGeoFeature *)(CGeoFeatureBase *)pFeat) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPCSTR FCTTreeGetObjFeatBSTR (CGeoFeatureBase *pFeat)
{
	return ((CGeoFeatureBase *)pFeat) -> FGetBSTR();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpObjFeatBSTR (LPCSTR pFeat1, LPCSTR pFeat2)
{
	return FCmpBSTR (pFeat1, pFeat2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
bool CFeatObjTree::FEnumAllItems (CGeoFeatureEnumFunc pFcn, void *pEData)
{
CFeatObjTreeSync Sync (this);
CFeatObjTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CGeoFeatureBase3Lock l(t);

		if (l && pFcn (*(CGeoFeatureBase *)l, pEData) == false)
			return false;
	}
	return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CFeatObjTree::FEnumItems (LPCSTR rKey, CGeoFeatureEnumFunc pFcn, void *pEData)
{
CFeatObjTreeSync Sync (this);
CFeatObjTreeTable t(*this);

	for (t.FindFirst ((LPVOID)rKey); t.Valid(); t.FindNext ((LPVOID)rKey)) {
	CGeoFeatureBase3Lock l(t);

		if (l && pFcn (*(CGeoFeatureBase *)l, pEData) == false)
			return false;
	}
	return true;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CFeatObjTree::FReInsert (LPCSTR roldKey, LPCSTR rnewKey)
{
CFeatObjTreeSync Sync (this);
CFeatObjTreeTable t(*this);

	if (t.Find ((LPVOID)roldKey)) 
		return t.ReInsert ((LPVOID)rnewKey, sizeof (rnewKey));
	return false;
}
#endif // defined(_USE_UNSAFE_REINSERT)
