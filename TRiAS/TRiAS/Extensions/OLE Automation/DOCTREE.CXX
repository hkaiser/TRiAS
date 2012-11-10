// Implementation der typspezifischen TreeKlasse ------------------------------
// File: DOCTREE.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "doc.hxx"

#include "doctree.hxx"	// KlassenDeklarationen
#include "doctree.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Initialisierung ------------------------------------------------------------
CDocTree *CDocTree::CreateInstance (CTriasApp *pApp)
{
CDocTree *pDoc = NULL;

	ATLTRY(pDoc = new CDocTree());
	if (pDoc == NULL || !pDoc -> FInit (pApp)) {
		DELETE_OBJ (pDoc);
		return NULL;
	}
	return pDoc;
}

bool CDocTree::FInit (CTriasApp *pApp)
{
	m_pApp = pApp;
//	ADDREF (m_pApp);	// fully dependend
	return true;
}


// Konstruktor der typspezifischen TreeKlasse ---------------------------------
CDocTree::CDocTree (void)
	: CDocTreeBase ((CTTREEGETKEYFCN)FCTTreeGetDocBSTR, (CTTREECMPKEYFCN)FCTTreeCmpDocBSTR, 
		container_wrappers::CFSyncThreads)
{
	CONSTRUCT_TRACE(CDocTree);
	m_pApp = NULL;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CDocTree::~CDocTree (void)
{
	DESTRUCT_TRACE(CDocTree);
	EveryDelete();
//	RELEASE (m_pApp);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
HRESULT CDocTree::FAddItem (LPCSTR pName, CGeoDoc **ppDoc, DDocument **ppIDoc, DOCMODE rgMode)
{
// wenn kein Name gegeben ist, dann aktuelles Projekt verwenden
CDocTreeSync Sync (this);
char cbBuffer[_MAX_PATH+1];

	if (NULL != ppDoc) *ppDoc = NULL;		// Initialisierung

	if (NULL == pName) {
		if (!DEX_TestActiveProject()) 
			return S_FALSE;			// kein aktives Projekt vorhanden
		if (NULL == DEX_GetActiveProject (cbBuffer))
			return E_UNEXPECTED;
	} else
		strcpy (cbBuffer, pName);

	strupr (cbBuffer);

// Im Baum nachsehen, ob Dokument bekannt ist etc.
CGeoDoc *pDoc = FFindItem (cbBuffer);

	if (NULL == pDoc) {
	HRESULT hr = CGeoDoc::CreateInstance ((DApplication *)m_pApp, m_pApp, cbBuffer, &pDoc, rgMode);

		if (FAILED(hr)) return hr;

	CGeoDoc2Creator Cr (*this);

		if (!Cr.InsertPtr (pDoc)) {
			delete pDoc;
			return E_OUTOFMEMORY;
		}
	} 

// request IID_IDispatch if requested
	if (ppIDoc && FAILED(((DDocument *)pDoc) -> QueryInterface (IID_DDocument, (LPVOID *)ppIDoc))) {
		delete pDoc;
		return E_NOINTERFACE;
	}
	if (NULL != ppDoc)
		*ppDoc = pDoc;

	return S_OK;
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
HRESULT CDocTree::FAddItem (HPROJECT hPr, CGeoDoc **ppDoc, DDocument **ppIDoc, DOCMODE rgMode)
{
// wenn kein Name gegeben ist, dann aktuelles Projekt verwenden
CDocTreeSync Sync (this);

	if (NULL != ppDoc) *ppDoc = NULL;		// Initialisierung

	if (NULL == hPr) {
		hPr = DEX_GetActiveProjectHandle();
		if (NULL == hPr)
			return S_FALSE;			// kein aktuelles Projekt
	} 

LPCSTR pcBuffer = DEX_GetProjectName(hPr);
char cbBuffer[_MAX_PATH+1];

	if (NULL == pcBuffer)
		return S_FALSE;				// gesuchtes Projekt ist nicht offen

	strcpy (cbBuffer, pcBuffer);
	CoTaskMemFree ((LPVOID)pcBuffer);

// Im Baum nachsehen, ob Dokument bekannt ist etc.
CGeoDoc *pDoc = FFindItem (cbBuffer);

	if (NULL == pDoc) {
	HRESULT hr = CGeoDoc::CreateInstance ((_DApplication *)m_pApp, m_pApp, cbBuffer, &pDoc, rgMode);
		
		if (FAILED(hr)) return hr;

	CGeoDoc2Creator Cr (*this);

		if (!Cr.InsertPtr (pDoc)) {
			delete pDoc;
			return E_OUTOFMEMORY;
		}
	} 

// request IID_IDispatch if requested
	if (ppIDoc && FAILED(((DDocument *)pDoc) -> QueryInterface (IID_DDocument, (LPVOID *)ppIDoc))) {
		delete pDoc;
		return E_NOINTERFACE;
	}
	if (NULL != ppDoc)
		*ppDoc = pDoc;

	return S_OK;
}

// add existend Doc to tree -------------------------------------------------
bool CDocTree::FAddItem (CGeoDoc *pDoc)
{
CDocTreeSync Sync (this);

	if (pDoc == NULL) return NULL;

CGeoDoc2Creator Cr (*this);

	if (!Cr.InsertPtr (pDoc)) {
		delete pDoc;
		return false;
	}
	ADDREF_CAST(_DDocument, pDoc);
	return true;
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CDocTree::FDeleteItem (LPCSTR rKT)
{
// remove physically
CDocTreeSync Sync (this);
CGeoDoc *pDoc = FFindItem (rKT);

	if (pDoc == NULL) {
		HPROJECT hPr = DEX_GetProjectHandle(rKT);
		return	DEX_CloseProject(hPr);
	}
	{
		((_DDocument *)pDoc) -> AddRef();

		pDoc -> Remove();		// Close etc.
		pDoc -> InvDoc();
	
		((_DDocument *)pDoc) -> Release();
	}

// remove from tree
CDocTreeTable t(*this);

char cbBuffer[_MAX_PATH+1];
	strcpy (cbBuffer, rKT);
	strupr (cbBuffer);
	if (t.Find (cbBuffer)) 
		return t.Delete();
	return false;
}


bool CDocTree::FInvalidateItem (LPCSTR pName)
{
// remove from tree, invalidate
CDocTreeSync Sync (this);
CGeoDoc *pDoc = FFindItem (pName);

	if (pDoc == NULL) 
		return true;

	pDoc -> InvDoc();

// remove from tree
CDocTreeTable t(*this);
bool fResult = false;

char cbBuffer[_MAX_PATH+1];
	strcpy (cbBuffer, pName);
	strupr (cbBuffer);

	if (t.Find (cbBuffer)) 
		fResult = t.Delete();

	return fResult;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CGeoDoc *CDocTree::FFindItem (LPCSTR rKT)
{
CDocTreeSync Sync (this);
CDocTreeTable t(*this);
char cbBuffer[_MAX_PATH+1];

	strcpy (cbBuffer, rKT);
	strupr (cbBuffer);
	if (t.Find (cbBuffer)) {
	CGeoDoc2Lock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}


bool CDocTree::SetDocName (LPCSTR bOldName, LPCSTR bNewName)
{
CDocTreeSync Sync (this);
CGeoDoc *pDoc = FFindItem (bOldName);

	if (pDoc == NULL) return false;
	
	((_DDocument *)pDoc) -> AddRef();		// ???? Release() ????
	
LPCSTR bName = pDoc -> GetName();

	if (!strcmp (bName, bNewName)) return true;
	
	if (FDeleteItem (bName)) {
		if (FAILED(pDoc -> SetName (bNewName, true))) 
			return false;
		pDoc -> Validate();
		return FAddItem (pDoc);
	}
	return false;
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CDocTree::UserDelete (void *pDoc)
{
	((CGeoDoc *)pDoc) -> Invalidate();
	((_DDocument *)(CGeoDoc *)pDoc) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPCSTR FCTTreeGetDocBSTR (CGeoDoc *pDoc)
{
	return ((CGeoDoc *)pDoc) -> FGetBSTR();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpDocBSTR (LPCSTR pDoc1, LPCSTR pDoc2)
{
	return FCmpBSTR (pDoc1, pDoc2);
}

// Enumeration aller Items in dem Baum ----------------------------------------
bool CDocTree::FEnumAllItems (CDocEnumFunc pFcn, void *pEData)
{
CDocTreeSync Sync (this);
CDocTreeTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CGeoDoc2Lock l(t);

		if (l && pFcn (*(CGeoDoc *)l, pEData) == false)
			return false;
	}
	return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CDocTree::FEnumItems (LPCSTR rKey, CDocEnumFunc pFcn, void *pEData)
{
CDocTreeSync Sync (this);
CDocTreeTable t(*this);

	for (t.FindFirst ((LPVOID)rKey); t.Valid(); t.FindNext ((LPVOID)rKey)) {
	CGeoDoc2Lock l(t);

		if (l && pFcn (*(CGeoDoc *)l, pEData) == false)
			return false;
	}
	return true;
}

#if defined(_USE_UNSAFE_REINSERT)
bool CDocTree::FReInsert (LPCSTR roldKey, LPCSTR rnewKey)
{
CDocTreeSync Sync (this);
CDocTreeTable t(*this);

	if (t.Find ((LPVOID)roldKey)) 
		return t.ReInsert ((LPVOID)rnewKey, sizeof (rnewKey));

	return false;
}
#endif // defined(_USE_UNSAFE_REINSERT)
 
