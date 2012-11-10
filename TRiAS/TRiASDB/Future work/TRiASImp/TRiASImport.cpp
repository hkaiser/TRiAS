// TRiASImport.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To merge the proxy/stub code into the object DLL, add the file 
//		dlldatax.c to the project.  Make sure precompiled headers 
//		are turned off for this file, and add _MERGE_PROXYSTUB to the 
//		defines for the project.  
//
//		If you are not running WinNT4.0 or Win95 with DCOM, then you
//		need to remove the following define from dlldatax.c
//		#define _WIN32_WINNT 0x0400
//
//		Further, if you are running MIDL without /Oicf switch, you also 
//		need to remove the following define from dlldatax.c.
//		#define USE_STUBLESS_PROXY
//
//		Modify the custom build rule for TRiASImport.idl by adding the following 
//		files to the Outputs.
//			TRiASImport_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL, 
//		run nmake -f TRiASImportps.mk in the project directory.

#include "stdafx.h"
#include <afxdlgs.h>

#include "resource.h"
#include "initguid.h"
#include "TRiASImport.h"
#include "dlldatax.h"
//#include "Helper.h"

#include "TRiASDB_i.c"
#include "TRiASImport_i.c"
//#include "Helper_i.c"

//#include "TRiASXtensionSite_i.c"
#include "ImportDBEngine.h"

#include <ComCat.h>
#include "TrCatIDs.h"
#include "CIID.h"

#include "Strings.h"

#include "Wrapper.h"
#include "PDB.h"
#include "DatabaseBase.h"
#include "ImportDlgExt.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ImportDBEngine, CImportDBEngine)
	OBJECT_ENTRY(CLSID_DatabaseBase, CDatabaseBase)
	OBJECT_ENTRY(CLSID_ImportDlgExt, CImportDlgExt)
END_OBJECT_MAP()

///////////////////////////////////////////////////////////////////////////////
// Registrieren/Deregistrieren der TRiAS-Import Datenserver
HRESULT RegisterAllDataServers (void);
HRESULT RegisterDataServer (HKEY hKey, REFGUID rGuid);
HRESULT UnregisterAllDataServers (void);
HRESULT UnregisterDataServer (LPCTSTR pcSubKey);
HKEY OpenDataServerKey (void);

class CTRiASImportApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CTRiASImportApp theApp;

BOOL CTRiASImportApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	hProxyDll = m_hInstance;
#endif
	_Module.Init(ObjectMap, m_hInstance);
	if (!CWinApp::InitInstance())
		return FALSE;

// den aktuellen Namen von TRiAS lesen
CRegKey key;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
		ERROR_SUCCESS == key.Open(key, TEXT("uve")) &&
		ERROR_SUCCESS == key.Open(key, TEXT("TRiAS")) &&
		ERROR_SUCCESS == key.Open(key, TEXT("Config")))
	{
	DWORD dwCount = _countof(g_cbTRiAS);

		if (ERROR_SUCCESS != key.QueryValue (g_cbTRiAS, TEXT("TRiASName"), &dwCount))
			_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden
	} 
	else
		_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden

	return TRUE;
}

int CTRiASImportApp::ExitInstance()
{
	_Module.Term();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllCanUnloadNow() != S_OK)
		return S_FALSE;
#endif
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
		return S_OK;
#endif
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	HRESULT hRes = PrxDllRegisterServer();
	if (FAILED(hRes))
		return hRes;
#endif
	// registers object, typelib and all interfaces in typelib
HRESULT hr = _Module.RegisterServer(TRUE);

	if (SUCCEEDED(hr))
		hr = RegisterAllDataServers();	// _nach_ allen anderen regsitrieren
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	PrxDllUnregisterServer();
#endif

	UnregisterAllDataServers();			// _vor_ allen anderen deregistrieren
	_Module.UnregisterServer();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//	Hier werden alle für TRiAS registrierten Import-Module ermittelt und
//	für die Nutzung durch DBEngine registriert.
HRESULT RegisterAllDataServers (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// ImportModule über CATID enumerieren
BOOL fNotEmpty = FALSE;
CRegKey key;

	if (ERROR_SUCCESS != key.Open (HKEY_CURRENT_USER, TEXT("SOFTWARE")) ||
		ERROR_SUCCESS != key.Open (key, TEXT("uve")) ||
		ERROR_SUCCESS != key.Open (key, TEXT("TRiAS")) ||
		ERROR_SUCCESS != key.Open (key, TEXT("Extensions")))
	{
		return S_FALSE;		// keine TRiAS-Extensions registriert
	}

	try {
	WEnumGUID EnumGuids;		// Enumerator der ImportModule
	WCatInformation CatInfo (CLSID_StdComponentCategoriesMgr);	// throws hr
	GUID guidImpl[1]; 

		guidImpl[0] = CATID_TRiASImportModule;
		THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));

	GUID guid;

		for (EnumGuids -> Reset(); S_OK == EnumGuids -> Next (1, &guid, NULL); /**/)
		{
			if (SUCCEEDED(RegisterDataServer ( key, guid )))		// Fehler nicht fatal
				fNotEmpty = TRUE;
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	} 

	return fNotEmpty ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Die neuen RegistryEinträge werden über einen parametrisierten RegistryScript
// 'FakeImportServer.Rgs' erzeugt

// Die Parametrisierung erfolgt über die folgenden Key's
static TCHAR s_cbProgID[64];
static TCHAR s_cbNameDesc[128];
static TCHAR s_cbDefaultExt[32];
static TCHAR s_cbLongName[128];
static TCHAR s_cbShortName[128];
static TCHAR s_cbNameIsDir[16];
static TCHAR s_cbNameIsFile[16];
static TCHAR s_cbReadWrite[16];
static TCHAR s_cbFilterString[256];
static TCHAR s_cbVersion[16];
static TCHAR s_cbBuffer[16];

// Indizies in s_regEntryMap
#define REM_PROGID			0
#define REM_NAMEDESC		1
#define REM_DEFAULTTEXT		2
#define REM_LONGNAME		3
#define REM_SHORTNAME		4
#define REM_NAMEISDIR		5
#define REM_NAMEISFILE		6
#define REM_READWRITE		7
#define REM_FILTERSTRING	8
#define REM_VERSION			9
#define REM_BITMAP			10
#define REM_MULTIPLEFILES	11
#define REM_CANIMPGEOM		12
#define REM_OPTIMPGEOM		13
#define REM_CANIMPFEAT		14
#define REM_OPTIMPFEAT		15
#define REM_CANIMPRELA		16
#define REM_OPTIMPRELA		17
#define REM_CANIMPVISU		18
#define REM_OPTIMPVISU		19
#define REM_CANANSIOEM		20
#define REM_OPTANSIOEM		21
#define REM_SHOULDCONFIG	22

static _ATL_REGMAP_ENTRY s_regEntryMap[] = 
{
	{ L"PROGID", NULL },		// REM_PROGID
	{ L"NAMEDESC", NULL },		// REM_NAMEDESC
	{ L"DEFAULTTEXT", NULL },	// REM_DEFAULTTEXT
	{ L"LONGNAME", NULL },		// REM_LONGNAME
	{ L"SHORTNAME", NULL },		// REM_SHORTNAME
	{ L"NAMEISDIR", NULL },		// REM_NAMEISDIR
	{ L"NAMEISFILE", NULL },	// REM_NAMEISFILE
	{ L"READWRITE", NULL },		// REM_READWRITE
	{ L"FILTERSTRING", NULL },	// REM_FILTERSTRING
	{ L"VERSION", NULL },		// REM_VERSION
	{ L"BITMAP", NULL },		// REM_BITMAP
	{ L"MULTIFILE", NULL },		// REM_MULTIPLEFILES
	{ L"CANIMPGEOM", NULL },	// REM_CANIMPGEOM
	{ L"OPTIMPGEOM", NULL },	// REM_OPTIMPGEOM
	{ L"CANIMPFEAT", NULL },	// REM_CANIMPFEAT
	{ L"OPTIMPFEAT", NULL },	// REM_OPTIMPFEAT
	{ L"CANIMPRELA", NULL },	// REM_CANIMPRELA
	{ L"OPTIMPRELA", NULL },	// REM_OPTIMPRELA
	{ L"CANIMPVISU", NULL },	// REM_CANIMPVISU
	{ L"OPTIMPVISU", NULL },	// REM_OPTIMPVISU
	{ L"CANANSIOEM", NULL },	// REM_CANANSIOEM
	{ L"OPTANSIOEM", NULL },	// REM_OPTANSIOEM
	{ L"SHOULDCONFIG", NULL },	// REM_SHOULDCONFIG
	{ NULL, NULL },		// EndeKennung
};

// Füllen eines ParameterEintrages
#define FILL_REGMAP_ENTRY(iIndex, cbBuffer, cbKey)			\
	lCount = _countof(cbBuffer);							\
	lRes = ::RegQueryValueEx (key, cbKey, NULL,				\
						&lType, (LPBYTE)cbBuffer, &lCount);	\
	if (ERROR_SUCCESS != lRes) {							\
		ASSERT(ERROR_SUCCESS != lRes);						\
		return HRESULT_FROM_WIN32(lRes);					\
	}														\
	s_regEntryMap[iIndex].szData = A2OLE(cbBuffer);

#define FILL_REGMAP_ENTRY_OPT(iIndex, cbBuffer, cbKey, cbDef)		\
	lCount = _countof(cbBuffer);							\
	lRes = ::RegQueryValueEx (key, cbKey, NULL,				\
						&lType, (LPBYTE)cbBuffer, &lCount);	\
	if (ERROR_SUCCESS != lRes)								\
		s_regEntryMap[iIndex].szData = cbDef;		\
	else													\
		s_regEntryMap[iIndex].szData = A2OLE(cbBuffer);

// Registrieren einer TRiAS-ImportExtension als DataServer
HRESULT RegisterDataServer (HKEY hKey, REFGUID rGuid)
{
CRegKey key;
CString	progID;
CIID	ciid;

	VERIFY( ciid = CIID( rGuid ));
	VERIFY( progID = ciid.ProgID().c_str());

	if (ERROR_SUCCESS != key.Open (hKey, progID))
		return HRESULT_FROM_WIN32(GetLastError());

// Unterschlüssel 'ImportFormat' öffnen
	if (ERROR_SUCCESS != key.Open (key, g_cbImportFormat))
		return HRESULT_FROM_WIN32(GetLastError());

// Struktur füllen

// Alle notwendigen Infos aufsammeln und in der Zuordnungstabelle ablegen
DWORD	lCount = 0;
LONG	lRes= ERROR_SUCCESS;
DWORD	lType = REG_SZ;

	USES_CONVERSION;
//	FILL_REGMAP_ENTRY(REM_PROGID, s_cbProgID, g_cbDatabaseClass);
	s_regEntryMap[REM_PROGID].szData = A2OLE(progID);
//	FILL_REGMAP_ENTRY(REM_NAMEDESC, s_cbNameDesc, g_cbNameDescription);
	FILL_REGMAP_ENTRY(REM_DEFAULTTEXT, s_cbDefaultExt, g_cbFileExtension);
	FILL_REGMAP_ENTRY(REM_LONGNAME, s_cbLongName, g_cbDescription);		// bis wir etwas besseres finden
//	FILL_REGMAP_ENTRY(REM_SHORTNAME, s_cbShortName, g_cbDescription);	// bis wir etwas besseres finden
//	FILL_REGMAP_ENTRY(REM_NAMEISDIR, s_cbNameIsDir, g_cbNameIsDirectory);
	s_regEntryMap[REM_NAMEISDIR].szData = L"0";		// sollte für Importmodul immer stimmen
//	FILL_REGMAP_ENTRY(REM_NAMEISFILE, s_cbNameIsFile, g_cbNameIsFile);
	s_regEntryMap[REM_NAMEISFILE].szData = L"1";	// sollte für Importmodul immer stimmen
//	FILL_REGMAP_ENTRY(REM_READWRITE, s_cbReadWrite, g_cbReadWrite);
	s_regEntryMap[REM_READWRITE].szData = L"0";		// sollte für Importmodul immer stimmen

//	lRes = ::RegQueryValueEx (key, g_cbMultipleFiles, NULL, &lType, (LPBYTE)cbBuffer, &lCount);
//	if (ERROR_SUCCESS == lRes)
//		s_regEntryMap[REM_MULTIPLEFILES].szData = A2OLE(cbBuffer);	// mehrere Dateien gleichzeitig öffnen?
//	else
//		s_regEntryMap[REM_MULTIPLEFILES].szData = L"0";	// nur eine Datei zum Import öffnen
	FILL_REGMAP_ENTRY_OPT(REM_MULTIPLEFILES, s_cbBuffer, g_cbMultipleFiles, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_CANIMPGEOM, s_cbBuffer, g_cbCanImpGeom, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_OPTIMPGEOM, s_cbBuffer, g_cbOptImpGeom, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_CANIMPFEAT, s_cbBuffer, g_cbCanImpFeat, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_OPTIMPFEAT, s_cbBuffer, g_cbOptImpFeat, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_CANIMPRELA, s_cbBuffer, g_cbCanImpRela, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_OPTIMPRELA, s_cbBuffer, g_cbOptImpRela, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_CANIMPVISU, s_cbBuffer, g_cbCanImpVisu, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_OPTIMPVISU, s_cbBuffer, g_cbOptImpVisu, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_CANANSIOEM, s_cbBuffer, g_cbCanImpAnsiOEM, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_OPTANSIOEM, s_cbBuffer, g_cbOptImpAnsiOEM, L"0");
	FILL_REGMAP_ENTRY_OPT(REM_SHOULDCONFIG, s_cbBuffer, g_cbShouldConfig, L"0");

// Wie gesagt Version '1.0'
	s_regEntryMap[REM_VERSION].szData = A2OLE(g_cbGDBVersion);

// jetzt noch das Bildchen festlegen
//	if (!_tcsicmp(s_cbProgID, g_cbGeoMediaClass))
//		s_regEntryMap[REM_BITMAP].szData = L"2";	// GeoMedia ist eben was Besonderes
//	else
		s_regEntryMap[REM_BITMAP].szData = L"5";

// Kurzbeschreibung zusammenbauen
	CString		str;

	// FakeTRiASName (IDS_IMPORTDATEI, g_cbTRiAS, s_cbDefaultExt );
	VERIFY( str.LoadString( IDS_IMPORTDATEI ));
	if ( str.IsEmpty())		str = "%s Importdatei (%s)";
	wsprintf ( s_cbShortName, str, g_cbTRiAS, s_cbDefaultExt );

	// FakeTRiASName (IDS_IMPORTDATEI2, g_cbTRiAS );
	str.Empty();
	VERIFY( str.LoadString( IDS_IMPORTDATEI2 ));
	if ( str.IsEmpty())		str = "%s Importdatei";
	wsprintf ( s_cbNameDesc, str, g_cbTRiAS );

	s_regEntryMap[REM_SHORTNAME].szData = A2OLE(s_cbShortName);
	s_regEntryMap[REM_NAMEDESC].szData = A2OLE(s_cbNameDesc);

// jetzt noch FilterString zusammenbauen
	wsprintf (s_cbFilterString, g_cbFilterString, s_cbNameDesc, s_cbDefaultExt, s_cbDefaultExt);
	s_regEntryMap[REM_FILTERSTRING].szData = A2OLE(s_cbFilterString);

// jetzt wird registriert
	return _Module.UpdateRegistryFromResource(IDR_FAKEIMPSERVER, true, s_regEntryMap);
}

///////////////////////////////////////////////////////////////////////////////
// Deregistrieren aller Datenserver
HRESULT UnregisterAllDataServers (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// alle installierten DataServer enumerieren
CRegKey key;

	key.Attach (OpenDataServerKey());
	ASSERT(NULL != HKEY(key));

// alle registrierten Einträge durchgehen, immer den ersten löschen
DWORD dwCnt = 0;
TCHAR cbEnumKey[_MAX_PATH];

	while (ERROR_SUCCESS == ::RegEnumKey (key, dwCnt, cbEnumKey, _MAX_PATH)) 
	{
		if (ERROR_SUCCESS != UnregisterDataServer (cbEnumKey))	// Bei Fehler: überspringen
			dwCnt++;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Routine, die RegistryKey liefert, unter dem alle Import-Server registriert sind
HKEY OpenDataServerKey (void)
{
CRegKey key;

	if (ERROR_SUCCESS != key.Open (HKEY_CLASSES_ROOT, TEXT("TRiASImport.DBEngine.1")) ||
		ERROR_SUCCESS != key.Open (key, TEXT("TRiASDB")))
	{
		return NULL;		// keine Import-Server registriert
	}
	return key.Detach();
}

HRESULT UnregisterDataServer (LPCTSTR pcSubKey)
{
// erstmal alle Parameter auf Sinnvolle Werte rücksetzen
	USES_CONVERSION;
	for (int i = 1; i < _countof(s_regEntryMap); i++)
		s_regEntryMap[i].szData = A2OLE(g_cbSpace);

// es wird nur der ProgID als Parameter benötigt, da alles andere
// an selbigem dranhängt.
	s_regEntryMap[REM_PROGID].szData = A2OLE(pcSubKey);

// jetzt wird UnRegistriert
	return _Module.UpdateRegistryFromResource(IDR_FAKEIMPSERVER, false, s_regEntryMap);
}

///////////////////////////////////////////////////////////////////////////////
// alle registrierten Einträge durchgehen und zählen
int CountRegisteredDataServers (HKEY hKey)
{
	ASSERT(NULL != hKey);

DWORD dwCnt = 0;
TCHAR cbEnumKey[_MAX_PATH];

	while (ERROR_SUCCESS == ::RegEnumKey (hKey, dwCnt, cbEnumKey, _MAX_PATH)) 
	{
		dwCnt++;		// nur zählen
	}
	return int(dwCnt);
}
