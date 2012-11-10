// Implementation der typspezifischen TreeKlasse ------------------------------
// File: FTVWTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "view.hxx"

#include "feat.hxx"

#include "ftvwtree.hxx"	// KlassenDeklarationen
#include "ftvwtree.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Initialisierung ------------------------------------------------------------
CFeatViewTree *CFeatViewTree::CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc, CGeoView *pView)
{
CFeatViewTree *pFeat = NULL;

	ATLTRY(pFeat = new CFeatViewTree());
	if (pFeat == NULL || !pFeat -> FInit (pApp, pDoc, pView)) {
		DELETE_OBJ (pFeat);
		return NULL;
	}
	return pFeat;
}

bool CFeatViewTree::FInit (CTriasApp *pApp, 
							 CGeoDoc *pDoc, 
							 CGeoView *pView)
{
	m_pApp = pApp;
//	ADDREF (m_pApp);	// fully dependend

	m_pDoc = pDoc;
//	ADDREF (m_pDoc);	// fully dependend

	m_pView = pView;
//	ADDREF (m_pView);	// fully dependend
	return true;
}


// Konstruktor der typspezifischen TreeKlasse ---------------------------------
CFeatViewTree::CFeatViewTree (void)
	: CFeatViewTreeBase ((CTTREEGETKEYFCN)FCTTreeGetViewFeatBSTR, (CTTREECMPKEYFCN)FCTTreeCmpViewFeatBSTR, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CFeatViewTree);
	
	m_pApp = NULL;
	m_pDoc = NULL;
	m_pView = NULL;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CFeatViewTree::~CFeatViewTree (void)
{
	DESTRUCT_TRACE(CFeatViewTree);
	
	EveryDelete();
	
//	RELEASE (m_pView);
//	RELEASE (m_pDoc);
//	RELEASE (m_pApp);
}



// Funktion, die ein neues Element in den Baum einhängt -----------------------
CGeoFeatureBase *CFeatViewTree::FAddItem (LPCSTR pName, DGeoFeature **ppIFeat, FEATUREMODE rgMode)
{
CFeatViewTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (pName);

	if (NULL == pFeat) {	 
		pFeat = CGeoFeatureVC::CreateInstance (
					(DView *)m_pView, m_pApp, m_pDoc, pName, 
					TT_Sicht, (DWORD)m_pView -> GetValue(), rgMode);
		if (pFeat == NULL) return NULL;

	CGeoFeatureBase1Creator Cr (*this);

		if (!Cr.InsertPtr (pFeat)) {
			delete pFeat;
			return NULL;
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
bool CFeatViewTree::FAddItem (CGeoFeatureBase *pFeat)
{
CFeatViewTreeSync Sync (this);

	if (pFeat == NULL) return NULL;

CGeoFeatureBase1Creator Cr (*this);

	if (!Cr.InsertPtr (pFeat)) {
		delete pFeat;
		return false;
	}
	((_DGeoFeature *)pFeat) -> AddRef();
	return true;
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CFeatViewTree::FDeleteItem (LPCSTR rKT)
{
// remove physically
CFeatViewTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (rKT);

	if (pFeat == NULL) {
	ErrInstall EI (WC_NOMERKMAL);
	TARGETMERKMAL TM;
	
		INITSTRUCT (TM, TARGETMERKMAL);
		TM.lTarget = (DWORD)m_pView -> GetValue(); // pView
		TM.lMCode  = DEX_GetMCodeFromFeatureName(rKT);
		TM.imaxLen = 0;
		TM.pMText = NULL;	// NULL: delete feature
		TM.iTTyp = TT_Sicht;
	
		return DEX_ModTextMerkmal(TM);
	}

	pFeat -> Remove();	// remove physically

// remove from tree
CFeatViewTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) 
		return t.Delete();
	return false;
}

bool CFeatViewTree::FInvalidateItem (LPCSTR pName)
{
// remove from tree, invalidate
CFeatViewTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (pName);

	if (pFeat == NULL) 
		return true;

	pFeat -> Invalidate();

// remove from tree
CFeatViewTreeTable t(*this);
bool fResult = false;

	if (t.Find ((LPVOID)pName)) 
		fResult = t.Delete();

	return fResult;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CGeoFeatureBase *CFeatViewTree::FFindItem (LPCSTR rKT)
{
CFeatViewTreeSync Sync (this);
CFeatViewTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) {
	CGeoFeatureBase1Lock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}


bool CFeatViewTree::SetFeatureName (LPCSTR bOldName, LPCSTR bNewName)
{
CFeatViewTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (bOldName);

	if (pFeat == NULL) return false;
	
	((_DGeoFeature *)pFeat) -> AddRef();			// ???? Release() ????
	
LPCSTR bName = pFeat -> GetName();

	if (!strcmp (bName, bNewName)) return true;
	
	if (FDeleteItem (bName)) {
		if (!pFeat -> SetName (bNewName, true))
			return false;
		pFeat -> Validate();
		return FAddItem (pFeat);
	}
	return false;
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CFeatViewTree::UserDelete (void *pFeat)
{
	((CGeoFeatureBase *)pFeat) -> Invalidate();
	((_DGeoFeature *)(CGeoFeatureBase *)pFeat) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPCSTR FCTTreeGetViewFeatBSTR (CGeoFeatureBase *pFeat)
{
	return ((CGeoFeatureBase *)pFeat) -> FGetBSTR();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpViewFeatBSTR (LPCSTR pFeat1, LPCSTR pFeat2)
{
	return FCmpBSTR (pFeat1, pFeat2);
}

// Enumeration aller Items in dem Baum ----------------------------------------
bool CFeatViewTree::FEnumAllItems (CGeoFeatureEnumFunc pFcn, void *pEData)
{
CFeatViewTreeSync Sync (this);
CFeatViewTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CGeoFeatureBase1Lock l(t);

		if (l && pFcn (*(CGeoFeatureBase *)l, pEData) == false)
			return false;
	}
	return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CFeatViewTree::FEnumItems (LPCSTR rKey, CGeoFeatureEnumFunc pFcn, void *pEData)
{
CFeatViewTreeSync Sync (this);
CFeatViewTreeTable t(*this);

	for (t.FindFirst ((LPVOID)rKey); t.Valid(); t.FindNext ((LPVOID)rKey)) {
	CGeoFeatureBase1Lock l(t);

		if (l && pFcn (*(CGeoFeatureBase *)l, pEData) == false)
			return false;
	}
	return true;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CFeatViewTree::FReInsert (LPCSTR roldKey, LPCSTR rnewKey)
{
CFeatViewTreeSync Sync (this);
CFeatViewTreeTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert ((LPVOID)rnewKey, sizeof (rnewKey));

	return false;
}
#endif // defined(_USE_UNSAFE_REINSERT)
