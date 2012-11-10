// Implementation der typspezifischen TreeKlasse ------------------------------
// File: FTCLTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "class.hxx"

#include "feat.hxx"

#include "ftcltree.hxx"	// KlassenDeklarationen
#include "ftcltree.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG


// Initialisierung ------------------------------------------------------------
CFeatClsTree *CFeatClsTree::CreateInstance (CTriasApp *pApp, 
											  CGeoDoc *pDoc, 
											  CClass *pCls)
{
CFeatClsTree *pFeat = NULL;

	ATLTRY(pFeat = new CFeatClsTree());
	if (pFeat == NULL || !pFeat -> FInit (pApp, pDoc, pCls)) {
		DELETE_OBJ (pFeat);
		return NULL;
	}
	return pFeat;
}

bool CFeatClsTree::FInit (CTriasApp *pApp, CGeoDoc *pDoc, CClass *pCls)
{
	m_pApp = pApp;
//	ADDREF (m_pApp);	// fully dependend

	m_pDoc = pDoc;
//	ADDREF (m_pDoc);	// fully dependend

	m_pCls = pCls;
//	ADDREF (m_pCls);	// fully dependend
	return true;
}


// Konstruktor der typspezifischen TreeKlasse ---------------------------------
CFeatClsTree::CFeatClsTree (void)
	: CFeatClsTreeBase ((CTTREEGETKEYFCN)FCTTreeGetClsFeatBSTR, (CTTREECMPKEYFCN)FCTTreeCmpClsFeatBSTR, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CFeatClsTree);
	
	m_pApp = NULL;
	m_pDoc = NULL;
	m_pCls = NULL;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CFeatClsTree::~CFeatClsTree (void)
{
	DESTRUCT_TRACE(CFeatClsTree);
	
	EveryDelete();
	
//	RELEASE (m_pCls);
//	RELEASE (m_pDoc);
//	RELEASE (m_pApp);
}



// Funktion, die ein neues Element in den Baum einhängt -----------------------
CGeoFeatureBase *CFeatClsTree::FAddItem (LPCSTR pName, DGeoFeature **ppIFeat, FEATUREMODE rgMode)
{
CFeatClsTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (pName);

	if (NULL == pFeat) {	 
		pFeat = CGeoFeatureVC::CreateInstance (
					(DGeoClass *)m_pCls, m_pApp, m_pDoc, pName, 
					TT_Identifikator, (DWORD)m_pCls -> GetValue(), rgMode);

		if (pFeat == NULL) return NULL;

	CGeoFeatureBase2Creator Cr (*this);

		if (!Cr.InsertPtr (pFeat)) {
			delete pFeat;
			return NULL;
		}
	}

// request IID_IDispatch if requested
	if (ppIFeat && FAILED(((_DGeoFeature *)pFeat) -> QueryInterface (IID_DGeoFeature, (LPVOID *)ppIFeat))) {
		delete pFeat;
		return NULL;
	}
	return pFeat;
}

// add existend View to tree -------------------------------------------------
bool CFeatClsTree::FAddItem (CGeoFeatureBase *pFeat)
{
CFeatClsTreeSync Sync (this);

	if (pFeat == NULL) return NULL;

CGeoFeatureBase2Creator Cr (*this);

	if (!Cr.InsertPtr (pFeat)) {
		delete pFeat;
		return false;
	}
	((_DGeoFeature *)pFeat) -> AddRef();
	return true;
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CFeatClsTree::FDeleteItem (LPCSTR rKT)
{
// remove physically
CFeatClsTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (rKT);

	if (pFeat == NULL) {
	ErrInstall EI (WC_NOMERKMAL);
	TARGETMERKMAL TM;
	
		INITSTRUCT (TM, TARGETMERKMAL);
		TM.lTarget = (DWORD)m_pCls -> GetValue(); // Ident
		TM.lMCode  = DEX_GetMCodeFromFeatureName(rKT);
		TM.imaxLen = 0;
		TM.pMText = NULL;	// NULL: delete feature
		TM.iTTyp = TT_Identifikator;
	
		return DEX_ModTextMerkmal(TM);
	}

	pFeat -> Remove();	// remove physically

// remove from tree
CFeatClsTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) 
		return t.Delete();
	return false;
}

bool CFeatClsTree::FInvalidateItem (LPCSTR pName)
{
// remove from tree, invalidate
CFeatClsTreeSync Sync (this);
CGeoFeatureBase *pFeat = FFindItem (pName);

	if (pFeat == NULL) 
		return true;

	pFeat -> Invalidate();

// remove from tree
CFeatClsTreeTable t(*this);
bool fResult = false;

	if (t.Find ((LPVOID)pName)) 
		fResult = t.Delete();
	return fResult;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CGeoFeatureBase *CFeatClsTree::FFindItem (LPCSTR rKT)
{
CFeatClsTreeSync Sync (this);
CFeatClsTreeTable t(*this);

	if (t.Find ((LPVOID)rKT)) {
	CGeoFeatureBase2Lock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}


bool CFeatClsTree::SetFeatureName (LPCSTR bOldName, LPCSTR bNewName)
{
CFeatClsTreeSync Sync (this);
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
void _XTENSN_EXPORT CFeatClsTree::UserDelete (void *pFeat)
{
	((CGeoFeatureBase *)pFeat) -> Invalidate();
	((_DGeoFeature *)(CGeoFeatureBase *)pFeat) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPCSTR FCTTreeGetClsFeatBSTR (CGeoFeatureBase *pFeat)
{
	return ((CGeoFeatureBase *)pFeat) -> FGetBSTR();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpClsFeatBSTR (LPCSTR pFeat1, LPCSTR pFeat2)
{
	return FCmpBSTR (pFeat1, pFeat2);
}

// Enumeration aller Items in dem Baum ----------------------------------------
bool CFeatClsTree::FEnumAllItems (CGeoFeatureEnumFunc pFcn, void *pEData)
{
CFeatClsTreeSync Sync (this);
CFeatClsTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CGeoFeatureBase2Lock l(t);

		if (l && pFcn (*(CGeoFeatureBase *)l, pEData) == false)
			return false;
	}
	return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CFeatClsTree::FEnumItems (LPCSTR rKey, CGeoFeatureEnumFunc pFcn, void *pEData)
{
CFeatClsTreeSync Sync (this);
CFeatClsTreeTable t(*this);

	for (t.FindFirst ((LPVOID)rKey); t.Valid(); t.FindNext ((LPVOID)rKey)) {
	CGeoFeatureBase2Lock l(t);

		if (l && pFcn (*(CGeoFeatureBase *)l, pEData) == false)
			return false;
	}
	return true;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CFeatClsTree::FReInsert (LPCSTR roldKey, LPCSTR rnewKey)
{
CFeatClsTreeSync Sync (this);
CFeatClsTreeTable t(*this);

	if (t.Find ((LPVOID)roldKey)) 
		return t.ReInsert ((LPVOID)rnewKey, sizeof (rnewKey));

	return false;
}
#endif // defined(_USE_UNSAFE_REINSERT)
