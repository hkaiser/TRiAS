// Basisklasse für GeoDataImport-Interface in einer Erweiterung ---------------
// File: XTSNIMPATL.CPP

#include "xtensnp.hxx"

#include "XtsnImpAtl.h"

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// ** IImportGeoData methods --------------------------------------------------
STDMETHODIMP_(DWORD) CImportGeoData::Capabilities (void)
{
	return IMPORTCAPS_NOTIMPLEMENTED;	// can do nothing
}

STDMETHODIMP CImportGeoData::Configure (HWND hWnd)
{
	ATLTRACENOTIMPL("CImportGeoData::Configure");
}

STDMETHODIMP CImportGeoData::ImportData (IEnumString *pEnumFiles, DWORD dwFlags)
{
	ATLTRACENOTIMPL("CImportGeoData::ImportData");
}

// IImportGeoDataWithResult methods 
STDMETHODIMP CImportGeoData::ImportDataWithResult (IEnumString *pEnumFiles, 
	DWORD dwFlags, IProgressIndicator *pIStatus, IEnumLONG **ppIObjs)
{
	ATLTRACENOTIMPL("CImportGeoData::ImportDataWithResult");
}

// IImportGeoDataWithResultCS methods
STDMETHODIMP CImportGeoData::put_CS (IUnknown *pICS)
{
	ATLTRACENOTIMPL("CImportGeoData::ImportDataWithResultCS");
}

STDMETHODIMP CImportGeoData::GetConfigInfo (IEnumString **pIEnumStr, DWORD dwReserved)
{
	ATLTRACENOTIMPL("CImportGeoData::GetConfigInfo");
}

bool IsInternalRegNumber (LPCSTR pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	return (100 == lInit && 0 == l2nd && 16670989L == lNumber);
}

bool IsDemoRegNumber (LPCSTR pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	return (1 == lInit && 0 == l2nd && 7621669L == lNumber);
}

HRESULT IsLegalRegNumber (LPCSTR pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);

#if _MSC_VER >= 1200
	if (300 > lInit && !IsInternalRegNumber(pcRegEntry) && !IsDemoRegNumber(pcRegEntry))
		return S_FALSE;
#endif // _MSC_VER >= 1200
	
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	srand (230459L);
	for (long i = 0; i < lInit-2; i++) 
		rand();

long lStep = lInit / ((rand() % 93) + 7);	// teilen durch mind 7 und max 92
long lGroup = rand() % 1000;
long lResult = 0;

	if (lInit >= 500) {
	// für Werte über 500
		for (int j = 0; j <= l2nd; j += lStep)
			lResult = rand()*lGroup+rand();
		if (j != l2nd + lStep)
			return S_FALSE;		// lStep muß auch stimmen
	} else {
	// für Werte zwischen 300 und 499
		for (int j = 0; j <= l2nd; j++)
			lResult = rand()*lGroup+rand();
	}
	return (lResult == lNumber) ? S_OK : S_FALSE;
}

