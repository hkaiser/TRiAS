// TRiASGDO.cpp : Implementation of DLL Exports.
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
//		Modify the custom build rule for TRiASGDO.idl by adding the following 
//		files to the Outputs.
//			TRiASGDO_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL, 
//		run nmake -f TRiASGDOps.mk in the project directory.

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "initguid.h"
#include "dlldatax.h"

#include "GDODBEngine.h"
#include "GDODatabase.h"

#include "TRiASGDO_i.c"
#include "GDOObject.h"
#include "GDOObjects.h"
#include "GDOFeature.h"
#include "GDOFeatures.h"
#include "GDOObjectsColl.h"

#include "PPgOracle.h"
#include "CreateOpenWizPropExt.h"
#include "ReconnectSQLServer.h"
#include "CreateSQLServerDB.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CAppModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_GDODBEngine, CGDODBEngine)
	OBJECT_ENTRY(CLSID_GDODatabase, CGDODatabase)
	OBJECT_ENTRY(CLSID_GDOObject, CGDOObject)
	OBJECT_ENTRY(CLSID_GDOObjects, CGDOObjects)
	OBJECT_ENTRY(CLSID_GDOFeature, CGDOFeature)
	OBJECT_ENTRY(CLSID_GDOFeatures, CGDOFeatures)
	OBJECT_ENTRY(CLSID_GDOObjectsCollection, CGDOObjectsCollection)
	OBJECT_ENTRY(CLSID_PPGOracle, CPPGOracle)
	OBJECT_ENTRY(CLSID_CreateOpenWizPropExt, CCreateOpenWizPropExt)
	OBJECT_ENTRY(CLSID_ReconnectSQLServer, CReconnectSQLServer)
	OBJECT_ENTRY(CLSID_CreateSQLServerDB, CCreateSQLServerDB)
END_OBJECT_MAP()

CLASSFACTORY_CACHE_BEGIN(ClassFactories)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASObject)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASFeature)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_GDOObject)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_GDOFeature)
CLASSFACTORY_CACHE_END()

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/) 
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);

	CRegKey regCfg;
	DWORD dwSize = _MAX_PATH;
	
		if (ERROR_SUCCESS != regCfg.Open(HKEY_CURRENT_USER, _T("Software"), KEY_READ) ||
			ERROR_SUCCESS != regCfg.Open(regCfg, REG_COMPANY_KEY, KEY_READ) ||
			ERROR_SUCCESS != regCfg.Open(regCfg, REG_PRODUCT_KEY, KEY_READ) ||
			ERROR_SUCCESS != regCfg.Open(regCfg, _T("Config"), KEY_READ) ||
			ERROR_SUCCESS != regCfg.QueryValue(g_cbTRiAS, _T("TRiASName"), &dwSize) ||
			0 == dwSize)
		{
			strcpy (g_cbTRiAS, g_cbTRiASDefaultName);		// default
		}
	} 
	else if (dwReason == DLL_PROCESS_DETACH) {
		_Module.Term();
	}
	return TRUE;    // ok
}

HRESULT RegisterGDODataServers (void);
HRESULT RegisterGDODataServer( WDGDOServerRegEntry &dataServer );
HRESULT UnregisterGDODataServers (void);

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void) 
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllCanUnloadNow() != S_OK)
		return S_FALSE;
#endif
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
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
	HRESULT hr;
	if (SUCCEEDED(hr = _Module.RegisterServer(TRUE))) 
		hr = RegisterGDODataServers();	// _nach_ allen anderen regsitrieren

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void) 
{
#ifdef _MERGE_PROXYSTUB
	PrxDllUnregisterServer();
#endif
	UnregisterGDODataServers();			// _vor_ allen anderen deregistrieren
	_Module.UnregisterServer();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Umhängen aller registrierten GeoMedia DatenServerEinträge
// GeoMedia registriert alle DatenServer unter 'HKLM\SOFTWARE\GDO\...'
// Wir brauchen jedoch einen einheitlichen Platz, damit TRiAS alles wiederfindet.
// Daher werden die entsprechenden Einträge jeweils unter dem ProgID der
// DatenBaseClass (z.B. unter 'Access.GDatabase') nachgetragen.
// Die TRiAS-Projekte haben entsprechende Einträge unter 'TRiAS.Document.1'
// bzw. 'TRiAS.Document.2'
//
// Um alle entsprechenden Datenserver auch wieder sicher deregistrieren zu können,
// werden diese zusätzlich unter 'TRiASGDO.TRiASDBEngine' eingetragen.

HRESULT RegisterGDODataServers (void) 
{
	COM_TRY {
	CIID clsid (_T("GDOServerRegEntries"), CIID::INITCIID_InitFromProgId);
	WDGDOServerRegEntries dataServers;

		if (FAILED(dataServers.CreateInstance(clsid))) 
			return E_FAIL;		// kein Geomedia

	WDGDOServerRegEntry dataServer;
	WEnumVARIANT srvEnum;
	CComVariant v;
	HRESULT	hr = dataServers->_NewEnum (srvEnum.ppu());
	
		for (srvEnum -> Reset(); S_OK == (hr = srvEnum -> Next (1, CLEARED(v), NULL)); /**/) 
		{
			if(FAILED(hr = v.ChangeType(VT_DISPATCH)))
				continue;
			dataServer = V_DISPATCH(&v);
			hr = RegisterGDODataServer (dataServer);
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Die neuen RegistryEinträge werden über parametrisierte RegistryScripts erzeugt
// Indizies in s_regEntryMap

#define MYPROGID			0

///////////////////////////////////////////////////////////////////////////////
// ab diesem Index beginnen alle Mappings die nicht intern verwendet werden

#define	GDO_EXTKEYSTART		MYPROGID + 1

#define GDO_PROGID			GDO_EXTKEYSTART + 0
#define GDO_NAMEDESC		GDO_EXTKEYSTART + 1
#define GDO_DEFAULTEXT		GDO_EXTKEYSTART + 2
#define GDO_LONGNAME		GDO_EXTKEYSTART + 3
#define GDO_SHORTNAME		GDO_EXTKEYSTART + 4
#define GDO_NAMEISDIR		GDO_EXTKEYSTART + 5
#define GDO_NAMEISFILE		GDO_EXTKEYSTART + 6
#define GDO_READWRITE		GDO_EXTKEYSTART + 7
#define GDO_FILTERSTRING	GDO_EXTKEYSTART + 8
#define GDO_VERSION			GDO_EXTKEYSTART + 9
#define GDO_BITMAP			GDO_EXTKEYSTART + 10

static _ATL_REGMAP_ENTRY s_regEntryMap[] =  {
	{ L"MYPROGID", NULL },			// MYPROGID

// ab hier Mappings oberhalb von EXTKEYSTART
	{ L"GDO_PROGID", NULL },		// GDO_PROGID
	{ L"GDO_NAMEDESC", NULL },		// GDO_NAMEDESC
	{ L"GDO_DEFAULTTEXT", NULL },	// GDO_DEFAULTEXT
	{ L"GDO_LONGNAME", NULL },		// GDO_LONGNAME
	{ L"GDO_SHORTNAME", NULL },		// GDO_SHORTNAME
	{ L"GDO_NAMEISDIR", NULL },		// GDO_NAMEISDIR
	{ L"GDO_NAMEISFILE", NULL },	// GDO_NAMEISFILE
	{ L"GDO_READWRITE", NULL },		// GDO_READWRITE
	{ L"GDO_FILTERSTRING", NULL },	// GDO_FILTERSTRING
	{ L"GDO_VERSION", NULL },		// GDO_VERSION
	{ L"GDO_BITMAP", NULL },		// GDO_BITMAP
	{ NULL, NULL },			// EndeKennung
};

static	LPCTSTR	
	szZero = _T("0")
	, szOne = _T("1")
	, szSpace = _T(" ")
	, szGMRegExt = _T(".gws")
	, szGMExt = _T("gws")
	;

//////////////////////////////////////////////////////////////
//
HRESULT RegisterGDODataServer (WDGDOServerRegEntry &dataServer) 
{
CComBSTR BS[_countof(s_regEntryMap)];
CComBSTR strFilter;
VARIANT_BOOL bFlag;
int i;
HRESULT	hr;

	BS[MYPROGID] = g_cbMyProgID;
	for (i = GDO_EXTKEYSTART; s_regEntryMap[i].szKey; ++i) 
		BS[i] = szSpace;

	COM_TRY {
		dataServer->get_DatabaseClass( &BS[GDO_PROGID] );
		dataServer->get_NameDescription( &BS[GDO_NAMEDESC] );
		dataServer->get_DefaultExtension( &BS[GDO_DEFAULTEXT] );
		dataServer->get_LongName( &BS[GDO_LONGNAME] );
		dataServer->get_ShortName( &BS[GDO_SHORTNAME] );
		dataServer->get_NameIsDirectory( &bFlag );
			BS[GDO_NAMEISDIR] = (0 == bFlag) ? szZero : szOne;
		dataServer->get_NameIsFile( &bFlag );
			BS[GDO_NAMEISFILE] = (0 == bFlag) ? szZero : szOne;
		dataServer->get_ReadWrite( &bFlag );
			BS[GDO_READWRITE] = (0 == bFlag) ? szZero : szOne;
		BS[GDO_BITMAP] = (0 == bFlag) ? _T("26") : _T("2");
		strFilter = BS[GDO_NAMEDESC];
		strFilter += _T(" (*.");
		strFilter += BS[GDO_DEFAULTEXT];
		strFilter += _T(")|*.");
		strFilter += BS[GDO_DEFAULTEXT];
		strFilter += _T("|");
		BS[GDO_FILTERSTRING] = strFilter;
		dataServer->get_Version( &BS[GDO_VERSION] );
	} COM_CATCH;

	for (i = 0; s_regEntryMap[i].szKey; ++i) 
		s_regEntryMap[i].szData = BS[i];

	if (FAILED(hr = _Module.UpdateRegistryFromResource(IDR_FAKEGDOSERVER, true, s_regEntryMap)))
		hr = REGDB_E_READREGDB;

	if (FAILED(hr = _Module.UpdateRegistryFromResource(IDR_GDOTRIASDB, true, s_regEntryMap))) 
		hr = REGDB_E_READREGDB;

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Deregistrieren aller Datenserver

HRESULT UnregisterDataServer (LPCTSTR pStrSubKey) 
{
HRESULT	hr, res;
CComBSTR	BS(pStrSubKey);

	s_regEntryMap[GDO_PROGID].szData = BS;

	if (FAILED(res = _Module.UpdateRegistryFromResource(IDR_FAKEGDOSERVER, 
		false, s_regEntryMap)))
	{
		hr = REGDB_E_READREGDB;
	}
	if (FAILED(res = _Module.UpdateRegistryFromResource(IDR_GDOTRIASDB, 
		false, s_regEntryMap)))
	{
		hr = REGDB_E_READREGDB;
	}
	return hr;
}

HRESULT UnregisterGDODataServers (void) 
{
list<os_string>	subKeys;		// STL
CComBSTR		BS[_countof(s_regEntryMap)];

// Block; 'CRegKey key' gibt beim Verlassen den geöffneten Schlüssel frei
// damit greife ich *nicht* mehr auf die Registry zu... ;-))
	{
	CRegKey key;
	int	i;

		key.Attach(OpenDataServerKey());
		if (NULL == HKEY(key))
			return S_OK;

	// zu löschende Keys einsammeln
	TCHAR cbEnumKey[_MAX_PATH];

		for (i = 0; ERROR_SUCCESS == ::RegEnumKey (key, i, cbEnumKey, _MAX_PATH); ++i) 
			subKeys.push_back(cbEnumKey);

	// Map für Resource basteln
		BS[MYPROGID] = g_cbMyProgID;
		s_regEntryMap[MYPROGID].szData = BS[MYPROGID];
		for( i = GDO_EXTKEYSTART; s_regEntryMap[i].szKey; ++i ) {
			BS[i] = g_cbSpace;
			s_regEntryMap[i].szData = BS[i];
		}
	}

HRESULT hr = S_OK;

	for (list<os_string>::iterator i = subKeys.begin(); i != subKeys.end(); ++i) {
		if (FAILED(UnregisterDataServer((*i).data())))
			hr = REGDB_E_READREGDB;
	}
	return hr;
}

