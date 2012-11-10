// ImportInterface-Implementation für den Import von DirisAsc-Daten -----------
// File: ASCIMPIF.CPP

#include "ascimpp.hpp"

#include <errinstx.hxx>
#include <xtensnn.h>
#include <fnamestr.h>
#include <eonrguid.h>

#include "ascimp.h"
#include "status.hxx"
#include "result.hxx"

char cbInFile[_MAX_PATH] = "";		// aktuelle EingabeDatei

static void protocol_open (char *pFile);
static void make_file (char *pNew, char *old, char *ext);

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineEnumIIDWrapper(LONG);
DefineSmartEnumerator(LONG);

/////////////////////////////////////////////////////////////////////////////
// Globale Variablen
time_t g_lFullTime = 0L;
CStatusDlg *g_pDlg = NULL;
WEnumLONG g_Enum;
bool g_fReReadHeader = false;

// *** IImportGeoData methods -------------------------------------------------
// Abfrage der Eigenschaften und Möglichkkeiten des ImportModuls (siehe Flags
// in File IXTENSN.HXX IMPORTCAPS_...
STDMETHODIMP_(DWORD) CImpAscExtension::Capabilities (void)
{
	return IMPORTCAPS_CANIMPORTGEOMETRY  | IMPORTCAPS_OPTIMPORTFEATURES |
	       IMPORTCAPS_CANIMPORTRELATIONS | IMPORTCAPS_OPTIMPORTGEOMETRY |
	       IMPORTCAPS_CANIMPORTFEATURES  | IMPORTCAPS_OPTIMPORTRELATIONS |
	       IMPORTCAPS_MULTIPLEFILES;
}

// Diese Funktion wird nur dann gerufen, wenn 'Capabilities' das Flag
// IMPORTCAPS_SHOULDCONFIGURE geliefert hat. Im dieser Funktion sollte die
// Konfiguration des Modules für den nächsten Import durchgeführt werden.
STDMETHODIMP CImpAscExtension::Configure (HWND hWnd)
{
	m_hWnd = hWnd;
	ATLTRACENOTIMPL("CImpAscExtension::Configure");
}

// Das ist die eigentliche ImportFunktion, die einmal gerufen wird und dann alles
// machen muß, was sie für richtig hält. 
// Der Enumerator pEnumFiles liefert die Dateinamen der zu importierenden Datei(en)
// (ACHTUNG: UNICODE!!! und OLE-TaskAllocator)
STDMETHODIMP CImpAscExtension::ImportData (IEnumString *pEnumFiles, DWORD dwFlags)
{
	return ImportDataWithResult (pEnumFiles, dwFlags, NULL, NULL);
}

STDMETHODIMP CImpAscExtension::ImportDataWithResult (
	IEnumString *pEnumFiles, DWORD dwFlags, 
	IProgressIndicator *pIStatus, IEnumLONG **ppIObjs)
{
LPWSTR pFile = NULL;
ULONG ulGot = 0;
HRESULT hr = ResultFromScode (E_FAIL);

// ImportModi setzen
	r_flag = (dwFlags & TOIMPORT_RELATIONS) ? true : false;
	g_flag = (dwFlags & TOIMPORT_GEOMETRY) ? true : false;
	m_flag = (dwFlags & TOIMPORT_FEATURES) ? true : false;

// ZählerVariablen initialisieren
	g_lPoints = 0;
	g_lLines = 0;
	g_lAreas = 0;
	g_lTexts = 0;
	g_lKomplex = 0;

	g_lWithErrors = 0;
	g_lNotImported = 0;

	g_fReReadHeader = false;

// eigentlichen Import durchführen
	if (NULL != ppIObjs) {
		try { g_Enum = WEnumLONG (CLSID_EnumObjectsByNumber); } catch (...) {}
	}			

	USES_CONVERSION;
	if (NULL == pIStatus) {
	CStatusDlg SDlg (g_pTE -> MWind());	// StatusDialog
	bool fShown = false;

		g_pDlg = &SDlg;
		g_lFullTime = 0L;		// GesamtZeit

		pEnumFiles -> Reset();
		while (S_OK == pEnumFiles -> Next (1, (LPOLESTR *)&pFile, &ulGot)) {
		// alle Dateien nacheinander abarbeiten
			if (!fShown) {
				SDlg.Show();
				fShown = true;
			}
			hr = ImportASC (OLE2A(pFile));
			CoTaskMemFree (pFile);
			if (FAILED(hr))	break;
		}
		g_pDlg = NULL;

	} else {
		g_pDlg = NULL;
		g_lFullTime = 0L;		// GesamtZeit

		pEnumFiles -> Reset();
		while (S_OK == pEnumFiles -> Next (1, (LPOLESTR *)&pFile, &ulGot)) {
		// alle Dateien nacheinander abarbeiten
			hr = ImportASC (OLE2A(pFile));
			CoTaskMemFree (pFile);
			if (FAILED(hr))	break;
		}
	}

// evtl. Enumerator liefern
	if (NULL != ppIObjs)
		*ppIObjs = (IEnumLONG *)g_Enum.detach();

// Abschlußdialog nach jedem File - Übergangslösung
// Neues Interface in allen Import-Funktionen nachziehen und Objekt(g_Enum) auswerten
// -> neue Schnittstelle : ImportDataWithResult

	/*if (NULL == ppIObjs) */
	{
		DEX_PostRebuildSight();		// alles neu zeichnen

	// ResultatsDialog anzeigen
	
	CResultDlg RDlg (g_pTE -> MWind());

		RDlg.SetTexts (g_lTexts);
		RDlg.SetLines (g_lLines);
		RDlg.SetAreas (g_lAreas);
		RDlg.SetPoints (g_lPoints);
		RDlg.SetKomplex (g_lKomplex);
		RDlg.SetWithErrors (g_lWithErrors);
		RDlg.SetNotImported (g_lNotImported);
		RDlg.SetImported (g_lPoints + g_lLines + g_lAreas + g_lTexts + g_lKomplex);
		SetTime (g_lFullTime, RDlg.m_ftTime);

		MessageBeep (MB_ICONASTERISK);		// fertig !!
		RDlg.Show (Centre);
	}
	return hr;
}

// Übergabe des zu verwendenden Koodinatensystemes
STDMETHODIMP CImpAscExtension::put_CS (IUnknown *pICS)
{
	m_CS = pICS;
	return S_OK;
}

STDMETHODIMP CImpAscExtension::ImportASC (char *pFile)
{
	strcpy (cbInFile, pFile);	// für FehlerMeldung sichern

	protocol_open (pFile);
	yyin = fopen (pFile, "r");
	if (yyin == NULL)
		return ResultFromScode (STG_E_PATHNOTFOUND);

HRESULT hr = NOERROR;

	fseek (yyin, 0L, SEEK_END);		// Dateilänge bestimmen

long lLen = ftell (yyin);

	if (lLen > 0) {
	ErrInstall EI ((ErrCode)ESYNTX, esyntx);
	string strFile = pFile;
	string str = get_name (strFile) + get_ext(strFile);

		g_pDlg -> FInit (lLen, str.c_str()); 
		g_pDlg -> Update();

		fseek (yyin, 0L, SEEK_SET);	// wieder am Anfang

		InitAllEnvironment();

		g_lTime = timeGetTime();	// Zeit für diese Datei
		hr = yyparse() ? S_OK : S_FALSE;
		g_lFullTime += timeGetTime() - g_lTime;
	}
	fclose (yyin);

// MCodeMap leeren
	g_MCodes.clear();

// evtl. Protokolldatei schließen
	if (fpProt) {
		fclose (fpProt);
		fpProt = NULL;
	}

// GeoDB neu initialisieren
	DEXN_ReScale();
	DEXN_ReReadIdents();
	DEXN_ReReadContainer();
	return hr;
}


// Protokolldatei eröffnen ----------------------------------------------------
static void protocol_open (char *pFile) 
{
char cbProtocol[_MAX_PATH];

	make_file (cbProtocol, pFile, ".lst");

	if (fpProt)
		fclose (fpProt);		// evtl. vorherige Datei schließen

	fpProt = fopen (cbProtocol, "w");
	if (fpProt)
		setvbuf (fpProt, NULL, _IONBF, 0);	// Buffering ausschalten
}


// Neue Extension anhängen ----------------------------------------------------
static void make_file (char *pNew, char *old, char *ext) 
{
char *cptr;

	strcpy (pNew, old);
	for (cptr = &pNew[strlen(pNew) -1]; cptr >= pNew; --cptr) {
		if (*cptr == '.') {
			strcpy (cptr, ext);
			break;
		}
		if (*cptr == BACKSLASH || cptr == pNew) {
			strcat (pNew, ext);
			break;
		}
	}
}


// FehlerAusgabeRoutine -------------------------------------------------------
int __cdecl esyntx (int errcode, int routine, ...) 
{
va_list pList;
ERROR_PARAMETER *pErrPar;

	va_start (pList, routine);
	pErrPar = va_arg (pList, ERROR_PARAMETER *);
	va_end (pList);

ResourceFile RF (g_pDLLName);
ResString resErrorCap (ResID (IDS_PARSERERRORCAP, &RF), 64);
ResString resError (ResID (IDS_PARSERERROR, &RF), 256);
char cbBuffer[_MAX_PATH];

	wsprintf (cbBuffer, resError, pErrPar -> pFile, pErrPar -> iLineNumber, pErrPar -> pString);
	MessBox mb (resErrorCap, cbBuffer, g_pTE -> MWind());
	mb.Show();
	return errcode;
}
