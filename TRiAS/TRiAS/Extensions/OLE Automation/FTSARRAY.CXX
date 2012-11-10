// ArrayContainer, der die Idents einer GeoFeatures Collection hält -------------
// File: FTSARRAY.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "ftsarray.hxx"		// CGeoFtsArray
#include "feat.hxx"			// CGeoFeatureBase
#include "enumfts.hxx"		// CEnumGeoFts

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CGeoFtsArray::CGeoFtsArray (void)
	: CGeoFtsArrayBase (20, container_wrappers::CFSyncThreads)	// erstmal 20 Idents
{
}


CGeoFtsArray *CGeoFtsArray::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, void *pViewClsObj, 
	INITFEATCOLLECTIONPROC pICFcn, DWORD dwData, DWORD dwFlags)
{
CGeoFtsArray *pFtsArr = NULL;

	ATLTRY(pFtsArr = new CGeoFtsArray);
	if (pFtsArr == NULL) return NULL;

// Array mit Feature füllen	
bool fResult = false;

	{		// Container füllen
	CGeoFtsArraySync Sync (pFtsArr);		// make it threadsafe
	CGeoFeatureBaseCreator FtCr (*pFtsArr);

		fResult = pICFcn (pUnk, pApp, pDoc, pViewClsObj, FtCr, dwData, NULL, dwFlags);
	}
	
	if (!fResult) {
		DELETE_OBJ (pFtsArr);
		return NULL;
	}
	return pFtsArr;
}


// Kopieren des CGeoFtsArray's -------------------------------------------------
CGeoFtsArray *CGeoFtsArray::Copy (void)
{
CGeoFtsArraySync Sync (this);		// make it threadsafe
CGeoFtsArray *pFtsArr = NULL;

	ATLTRY(pFtsArr = new CGeoFtsArray);
	if (pFtsArr == NULL) return NULL;

// neues Array mit Daten aus diesem Array füllen
CGeoFtsArraySync SyncNew (pFtsArr);		// make it threadsafe
CGeoFeatureBaseCreator FtCr (*pFtsArr);
CGeoFtsArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoFeatureBaseLock l(r);
	
		if (!l || !l -> IsValid()) continue;
		
	// Pointer einfach in anderem Array mit abspeichern
		((_DGeoFeature *)(CGeoFeatureBase *)l) -> AddRef();		// für neues Array festhalten
		FtCr.InsertPtr (l);	// Pointer einspeichern	
	}
	return pFtsArr;		// liefert Pointer auf Kopie	
}

// LöschFunktion --------------------------------------------------------------
void _XTENSN_EXPORT CGeoFtsArray::UserDelete (void *pFts)
{
	((_DGeoFeature *)(CGeoFeatureBase *)pFts) -> Release();	// freigeben einer enthaltenen GeoFeature
}

// ZugriffsFunktion -----------------------------------------------------------

// Liefert Identifikator der Objektklasse mit dem Index lIndex innerhalb des 
// Array's
char *CGeoFtsArray::Value (ULONG lIndex)
{
CGeoFtsArraySync Sync (this);		// make it threadsafe
CGeoFtsArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoFeatureBaseLock l(r);
	
		if (l && l -> IsValid()) 
			return (char *)l -> GetValue();
	}
	return NULL;	// Fehler
}


// Liefert Identifikator der Objektklasse mit dem Index lIndex innerhalb des 
// Array's ausgehend vom KurzText
char *CGeoFtsArray::Value (LPCSTR bstrName)
{
CGeoFtsArraySync Sync (this);		// make it threadsafe
CGeoFtsArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoFeatureBaseLock l(r);
	
		if (l && l -> IsValid() && !strcmp (bstrName, l -> GetName())) 
			return (char *)l -> GetValue();		// gefunden
	}
	return NULL;	// Fehler
}


// Liefert das IDispatch-Interface auf die Objekt mit dem lIndex
// innerhalb dieses Array's
HRESULT CGeoFtsArray::GetFeatureDisp (ULONG lIndex, DGeoFeature **ppIFeat)
{
	TEST_E_POINTER("CGeoFtsArray::GetFeatureDisp", ppIFeat);
	*ppIFeat = NULL;

CGeoFtsArraySync Sync (this);		// make it threadsafe
CGeoFtsArrayRing r(*this);

	if (r.Goto (lIndex)) {
	CGeoFeatureBaseLock l(r);
	
		if (l && l -> IsValid()) 
			return ((DGeoFeature *)(CGeoFeatureBase *)l) -> QueryInterface (IID_DGeoFeature, (LPVOID *)ppIFeat);
	}
	
	return DISP_E_BADINDEX;
}

// Liefert das IDispatch-Interface auf die Objekt mit dem  pFtStr
// innerhalb dieses Array's
HRESULT CGeoFtsArray::GetFeatureDisp (LPCSTR pFtStr, DGeoFeature **ppIFeat)
{
	TEST_E_POINTER("CGeoFtsArray::GetFeatureDisp", ppIFeat);
	*ppIFeat = NULL;

CGeoFtsArraySync Sync (this);		// make it threadsafe
CGeoFtsArrayRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	CGeoFeatureBaseLock l(r);
	
		if (l && l -> IsValid() && !strcmp (pFtStr, l -> GetName())) 
			return ((DGeoFeature *)(CGeoFeatureBase *)l) -> QueryInterface(IID_DGeoFeature, (LPVOID *)ppIFeat);
	}
	return DISP_E_BADINDEX;
}



// Testen, ob Feature bereits in Container enthalten ist --------------------
long CGeoFtsArray::hasFeature (LPCSTR bName)	// returns valid index
{
CGeoFtsArrayRing r(*this);
long lIndex = 0;

	for (r.First(); r.Valid(); r.Next(), lIndex++) {
	CGeoFeatureBaseLock l(r);
	
		if (l && l -> IsValid() && !strcmp (l -> GetName(), bName)) 
			return lIndex;
	}
	return -1L;
}

// delete Feature --------------------------------------------------------------
bool CGeoFtsArray::DeleteFeature (LPCSTR bName)
{
CGeoFtsArrayRing r(*this);
bool fDelete = false;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoFeatureBaseLock l(r);
	
		if (l && !strcmp (l -> GetName (true), bName)) {
			fDelete = true;
			break;
		}
	}
	if (fDelete && r.Valid()) 
		return r.Delete();
	return false;
}

// count valid GeoClasses ------------------------------------------------------
long CGeoFtsArray::Count (void)
{
CGeoFtsArrayRing r(*this);
long lCount = 0;

	for (r.First(); r.Valid(); r.Next()) {
	CGeoFeatureBaseLock l(r);

		if (l && l -> IsValid()) 
			lCount++;
	}
	return lCount;
}

// Refresh der Collection -----------------------------------------------------
HRESULT CGeoFtsArray::Refresh (void)
{
CGeoFtsArraySync Sync (this);		// make it threadsafe
CGeoFtsArrayRing r(*this);
bool fDeleted = false;

	for (r.First(); r.Valid(); ) {
	bool fToDelete = false;

		{
		CGeoFeatureBaseLock l(r);
	
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


