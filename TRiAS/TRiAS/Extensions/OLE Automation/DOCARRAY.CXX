// ArrayContainer, der Docs Collection hält -------------
// File: DOCARRAY.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "docarray.hxx"		// CGeoDocsArray
#include "enumdocs.hxx"		// CEnumDocs
#include "doc.hxx"			// CGeoDoc

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor/Destruktor/Initialisierung  -------------------------------------
CGeoDocsArray::CGeoDocsArray (void)
	: CGeoDocsArrayBase (20, container_wrappers::CFNoSpecial)	// erstmal 20 Docs
{
	m_pICProc = NULL;
}


CGeoDocsArray *CGeoDocsArray::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, INITDOCCOLLECTIONPROC pICFcn, DWORD dwData)
{
CGeoDocsArray *pDocsArr = NULL;

	ATLTRY(pDocsArr = new CGeoDocsArray);
	if (pDocsArr == NULL) return NULL;

// Array mit Doc füllen	
INITDOCSTATUS rgStatus = INITDOCSTATUS_Error;

	{		// Container füllen
	CGeoDocCreator DocCr (*pDocsArr);
		
		rgStatus = pICFcn (pUnk, pApp, DocCr, dwData);
	}
	
	if (rgStatus == INITDOCSTATUS_Error) {
		DELETE_OBJ (pDocsArr);
		return NULL;
	}
	return pDocsArr;
}


// Kopieren des CGeoDocsArray's -------------------------------------------------
CGeoDocsArray *CGeoDocsArray::Copy (void)
{
CGeoDocsArray *pDocsArr = NULL;

	ATLTRY(pDocsArr = new CGeoDocsArray);
	if (pDocsArr == NULL) return NULL;

// neues Array mit Daten aus diesem Array füllen
CGeoDocCreator DocCr (*pDocsArr);
CGeoDocsArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoDocLock l(r);
	
		if (!l) continue;
		
		if (l -> IsValid()) {
		// Pointer einfach in anderem Array mit abspeichern
			((_DDocument *)(CGeoDoc *)l) -> AddRef();		// für neues Array festhalten
			DocCr.InsertPtr (l);	// Pointer einspeichern	
		}
	}
	return pDocsArr;		// liefert Pointer auf Kopie	
}



// LöschFunktion --------------------------------------------------------------
void _XTENSN_EXPORT CGeoDocsArray::UserDelete (void *pDoc)
{
	((_DDocument *)(CGeoDoc *)pDoc) -> Release();	// freigeben einer enthaltenen Doc
}


// ZugriffsFunktion -----------------------------------------------------------

// Liefert Doc  mit dem Index lIndex innerhalb des 
// Array's
char *CGeoDocsArray::Value (ULONG lIndex)
{
CGeoDocsArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoDocLock l(r);
	
		if (l && l -> IsValid()) 
			return (char *)l -> GetValue();
	}
	return NULL;	// Fehler
}


// Liefert Doc mit dem Index lIndex innerhalb des 
// Array's ausgehend vom KurzText
char *CGeoDocsArray::Value (LPCSTR bstrName)
{
CGeoDocsArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoDocLock l(r);
	
		if (!l) continue;
	
	char *pName = l -> GetName();

		if (NULL != pName && !strcmp (bstrName, pName)) 
			return (char *)l -> GetValue();		// gefunden
	}
	return NULL;	// Fehler
}

// Liefert das IDispatch-Interface auf die Docs mit dem lIndex
// innerhalb dieses Array's
HRESULT CGeoDocsArray::GetDocDisp (ULONG lIndex, DDocument **ppDoc)
{
	TEST_E_POINTER("CGeoDocsArray::GetDocDisp", ppDoc);
	*ppDoc = NULL;

CGeoDocsArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoDocLock l(r);
	
		if (l && l -> IsValid()) 
			return ((DDocument *)(CGeoDoc *)l) -> QueryInterface(IID_DDocument, (LPVOID *)ppDoc);
	}
	return DISP_E_BADINDEX;
}


// Liefert das IDispatch-Interface auf die Docs mit dem  pDocStr
// innerhalb dieses Array's
HRESULT CGeoDocsArray::GetDocDisp (LPCSTR pDocStr, DDocument **ppDoc)
{
	TEST_E_POINTER("CGeoDocsArray::GetDocDisp", ppDoc);
	*ppDoc = NULL;

CGeoDocsArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoDocLock l(r);
	
		if (!l) continue;

	char *pName = l -> GetName();

		if (NULL != pName && !strcmp (pDocStr, pName)) 
			return ((DDocument *)(CGeoDoc *)l) -> QueryInterface(IID_DDocument, (LPVOID *)ppDoc);
	}
	return DISP_E_BADINDEX;
}


// Testen, ob Sicht bereits in Container enthalten ist --------------------
long CGeoDocsArray::hasDoc (LPCSTR bName)	// returns valid index
{
CGeoDocsArrayRing r(*this);
long lIndex = 0;

	for (r.First(); r.Valid(); r.Next(), lIndex++) {
	CGeoDocLock l(r);
	
		if (!l) continue;

	char *pName = l -> GetName();

		if (NULL != pName && !strcmp (pName, bName)) 
			return lIndex;
	}
	
return -1L;
}

// delete object --------------------------------------------------------------
bool CGeoDocsArray::DeleteDoc (LPCSTR bName)
{
CGeoDocsArrayRing r(*this);
bool fDelete = false;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoDocLock l(r);

		if (!l) continue;
		
	char *pName = l -> GetName (true);
		
		if (NULL != pName && !strcmp (pName, bName)) {
			fDelete = true;
			break;
		}
	}
	if (fDelete && r.Valid()) return r.Delete();
	
return false;
}

// count valid documents ------------------------------------------------------
long CGeoDocsArray::Count (void)
{
CGeoDocsArrayRing r(*this);
long lCount = 0;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoDocLock l(r);

		if (l && l -> IsValid()) 
			lCount++;
	}
	return lCount;
}

// Refresh der Collection -----------------------------------------------------
HRESULT CGeoDocsArray::Refresh (void)
{
CGeoDocsArraySync Sync (this);		// make it threadsafe
CGeoDocsArrayRing r(*this);
bool fDeleted = false;

	for (r.First(); r.Valid(); ) {
	bool fToDelete = false;

		{
		CGeoDocLock l(r);
	
			if (l && !l -> IsValid()) 
				fToDelete = true;
		} // goes out of scope

		if (fToDelete) {
			r.Delete();
			fDeleted = true;
		} else
			r.Next();
	}
	return fDeleted ? S_OK : S_FALSE;
}


