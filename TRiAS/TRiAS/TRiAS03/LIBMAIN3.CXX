// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.C

#include "trias03p.hxx"
#include <shlwapi.h>

char g_pDLLName[_MAX_PATH];
extern "C" HINSTANCE g_hInstance = 0;

#if defined(__XT) && defined(__DEXPROCS)
DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#if _TRiAS_VER >= 0x0300
DEXEXTENSIONPROC2 g_pDexExtensionProc2 = NULL;
DEXEXTENSIONPROC g_pDexxExtensionProc = NULL;
#endif // _TRiAS_VER >= 0x0300
#endif // __XT && __DEXPROCS

#if !defined(WIN32)

extern "C"
int FAR PASCAL 
LibMain (HINSTANCE hInst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine) {

	if (cbHeapSize != 0) UnlockData (0);

// Namen der DLL abfragen
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hMod, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;

	USES_CONVERSION;
	if (cbShortName == _MAX_PATH)
		return E_OUTOFMEMORY;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

	strcpy (g_pDLLName, OLE2A(pszModule));
	g_hInstance = hInst;

// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, "DEXEXTENSIONPROC");
	g_pDexxExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXXEXTENSIONPROC"));
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (NULL, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

return 1;	// erfolgreich installiert
}

#else 

#include "trias03.h"

#include <fnamestr.h>

#include <xtsnguid.h>
#include <statguid.h>
#include <eonrguid.h>
#include <srchguid.h>
#include <oprpguid.h>
#include <triastlb.h>
#include <TrCatIds.h>

#include <ioprpini.hxx>
#include <registry.hxx>
#include <TRiASHelper.h>

#define _NO_ERROR_MACROS
#include <Com/ErrorMacros2.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "RegObj.h"
#include "Strings.h"

#include "selidprp.hxx"		// PropertyActions
#include "modidprp.hxx"
#include "selobwnd.hxx"
#include "dstobwnd.hxx"
#include "delobprp.hxx"
#include "clsfyprp.hxx"
#include "ImportProp.h"
#include "GenTextPropAct.h"

#include "enumonr.hxx"
#include "statimpl.hxx"

#include "intoprop.hxx"

#include "TextSearchEngine.h"
#include "multipi.h"
#include "RegisterExt.h"

#include "dlldatax.h"		// ProxyStub

#include <initguid.h>
#include <bscrguid.h>
#include <TrCatIds.h>
#include <ScriptPropActGuid.h>

#include <ObjekteDoppelnGuid.h>
#include <ObjekteVereinigenGuid.h>
#include <SelectExportObjectsGuid.h>
#include <AddAsClsPrp.h>
#include <TextReplacePrp.h>

#include "ScriptPropAct.h"
#include "ObjekteDoppeln.h"
#include "ObjekteVereinigen.h"
#include "SelectExportObjects.h"
#include "AddAsObjectClass.h"
#include "TextReplaceEngine.h"
#include "DeleteObjectProperty.h"
#include "PropertyActionJoin.h"
#include "PropertyActionSplit.h"
#include "PropertyOperation.h"
#include "GenerateObjectProperties.h"
#include "LimitSearches.h"
#include "LimitPackets.h"
#include "TRiASDataObject.h"
#include "VBPropertySequence.h"
#include "MkVBGeoComponent.h"
#include "SaveObjectCollection.h"
#include "LoadObjectCollection.h"
#include "ManageObjectProperties.h"
#include "AreasToLines.h"
#include "LinesToAreas.h"

#include "propseq.hxx"
#include "PropertyActionJoin.h"
#include "PropertyOperation.h"
#if defined(_USE_XML_GEOCOMPONENTS)
#include "PropertySequenceService.h"
#endif // defined(_USE_XML_GEOCOMPONENTS)
#include "CatSimpleCache.h"

#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
#include "CoDelegator.h"
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300

#if defined(_DEBUG)
// Count number of objects and number of locks.
extern LONG g_cObj;
extern LONG g_cLock;
#endif // _DEBUG

#if _TRiAS_VER < 0x0400
// schon mal TRiAS V4 vorbereiten
DWORD g_dwVer4 = 0;
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// benötigte GUID's
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_TRiASObjectHandleMap = {0xD4C24AD6,0xA5EA,0x11D1,{0xBA,0x31,0x08,0x00,0x36,0xD6,0x38,0x03}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_TRiASObjectsHandleMap = {0xCD579673,0xAA9D,0x11D1,{0x85,0x8C,0x00,0x60,0x08,0x75,0x13,0x8A}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_TRiASFeatureHandleMap = {0x95F58F33,0xDF2C,0x11D1,{0x86,0x06,0x00,0x60,0x08,0x75,0x13,0x8A}};

EXTERN_C const IID DECLSPEC_SELECTANY LIBID_TRiASDB = {0x1CB3AB53,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_FakeTRiASLockFeature = {0x26A3BD85,0x6D09,0x11D2,{0x9E,0xE7,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_CoDelegator = {0x58DAD7D5,0x6F34,0x11D2,{0x9E,0xEC,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const IID DECLSPEC_SELECTANY IID_ITRiASPropertyBase = {0x97993C78,0x5FE6,0x11D1,{0xB9,0xE6,0x08,0x00,0x36,0xD6,0x38,0x03}};

EXTERN_C const IID DECLSPEC_SELECTANY IID_ITRiASLockFeatureEx = {0x9F6A6EC3,0x83A6,0x47FC,{0x9A,0x27,0xF1,0x9A,0x87,0xBD,0x8B,0x2B}};
EXTERN_C const IID DECLSPEC_SELECTANY IID_IInitInnerObject = {0x58DAD7D6,0x6F34,0x11D2,{0x9E,0xEC,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const IID DECLSPEC_SELECTANY IID_ITRiASObject = {0x1CB3AB6F,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const IID DECLSPEC_SELECTANY IID_IDelegatorFactory = {0x58DAD7D7,0x6F34,0x11D2,{0x9E,0xEC,0x00,0x60,0x08,0x44,0x78,0x00}};

EXTERN_C const IID DECLSPEC_SELECTANY IID_ITRiASFeature = {0x1CB3AB73,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const IID DECLSPEC_SELECTANY IID_ITRiASObjects = {0x1CB3AB6D,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

EXTERN_C const IID DECLSPEC_SELECTANY IID_IInitScriptPropAct = {0x50AECBE6,0x46E8,0x11D2,{0x9E,0xBF,0x00,0x60,0x08,0x44,0x78,0x00}};

EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_DeleteObjectProperty = {0xE5927445,0x894C,0x4563,{0x8C,0x05,0xE9,0x45,0x05,0x30,0xA6,0x93}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_PropertyOperation = {0x28585AF2,0x53A2,0x42D8,{0xA9,0x2F,0x35,0x8A,0xEC,0x11,0xD9,0x9E}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_PropertyActionJoin = {0xD041DB48,0x4A2F,0x4567,{0x80,0xE9,0x7C,0x42,0x85,0x12,0xB5,0xD1}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_PropertyActionSplit = {0x52E25FEE,0xD9C8,0x4B3C,{0xAD,0x5A,0x04,0x7E,0xB9,0x2D,0x7D,0x60}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_GenerateObjectProperties = {0xF629A52E,0x9974,0x427B,{0x80,0x76,0x11,0x71,0x24,0x3B,0x33,0xD9}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_LimitSearches = {0x07BC2DFA,0x98C4,0x404D,{0xAA,0xFF,0x07,0x29,0xE3,0x01,0xA3,0x2B}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_LimitPackets = {0x44BBA22C,0x5A88,0x43F1,{0x9E,0xE3,0x62,0x39,0x96,0x45,0x2B,0x09}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_VBGeoComponent = {0x4A8BF07A,0x95E9,0x4FDB,{0xBE,0xBF,0x4E,0x7B,0x57,0xF2,0x55,0x74}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_MkVBGeoComponent = {0x76E385A4,0xF3D0,0x452F,{0x92,0x59,0xD3,0x39,0x40,0x62,0xFD,0x33}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_LoadObjectCollection = {0xF6A02599,0x29A7,0x4BBD,{0xA2,0x26,0x21,0xE0,0xCA,0x32,0x5F,0x02}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_SaveObjectCollection = {0x56BEA165,0xEE80,0x4F91,{0xA8,0x4C,0xB0,0x03,0xF5,0x99,0x10,0xDF}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_AreasToLines = {0xDBEB428A,0x5FD2,0x48B0,{0xA1,0xBA,0x42, 0x8E,0xE1,0x09,0x7E,0x85}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_LinesToAreas = {0x1442BAF6,0x39A1,0x43D8,{0x9D,0xA6,0xF8,0x27,0xF1,0x7A,0x88,0x3D}};

EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_PropertySequenceService = {0x92BB6B5E,0x3F46,0x4236,{0xA0,0xB6,0xDD,0xDB,0xD6,0x32,0xCE,0x1D}};
EXTERN_C const CLSID DECLSPEC_SELECTANY IID_IPropertySequenceService = {0x554FC4F9,0x3C1E,0x4954,{0x9E,0x67,0xDD,0x5E,0x42,0x4C,0xC7,0x6C}};

EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_CatSimpleCache = {0xEA68A685,0x5166,0x4E55,{0x90,0x62,0x0B,0x13,0x06,0x81,0x33,0x93}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_TRiASDataServerRegEntries = {0xF4B3F946,0x810E,0x11D1,{0x97,0x76,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

EXTERN_C const IID DECLSPEC_SELECTANY IID_ITRiASDataObject = {0x0D1B02AF,0xF578,0x4EAE,{0xAC,0xFF,0x4E,0x08,0x3E,0x01,0x87,0x64}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_TRiASDataObject = {0xB7E7EF89,0xD4B0,0x45F1,{0x93,0xDB,0x41,0xD5,0x0F,0xFC,0x41,0x96}};
EXTERN_C const IID DECLSPEC_SELECTANY IID_ITRiASPropertyBag = {0x77EA92EB,0x7A00,0x4D4D,{0x96,0x82,0x2E,0x8E,0xB0,0x47,0x4D,0xE8}};

EXTERN_C const IID DECLSPEC_SELECTANY IID_IGeoComponentCallback = {0x3BCD2124,0xD9A3,0x4A06,{0xB9,0xD9,0x5F,0x5C,0xA3,0xE6,0x04,0x87}};
EXTERN_C const IID DECLSPEC_SELECTANY IID_IGeoComponentUICallback = {0x9C3051D8,0x6A60,0x489D,{0x83,0x0B,0xD9,0x0D,0x9B,0x47,0xA4,0x37}};

EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_ManageObjectProperties = {0xE0E89DE4,0x8550,0x4CE5,{0xA1,0x1A,0x43,0x04,0x25,0x13,0x60,0x57}};

#else

EXTERN_C const IID IID_IInitScriptPropAct = {0x50AECBE6,0x46E8,0x11D2,{0x9E,0xBF,0x00,0x60,0x08,0x44,0x78,0x00}};

#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300


///////////////////////////////////////////////////////////////////////////////
// ATL
WTL::CAppModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)		// Liste der PropertyActions 
// der RegistryHelper _muß_ der erste sein (HiHi)
	OBJECT_ENTRY(CLSID_TRiASRegistryHelper, CTRiASRegObject)

// PropertyActions 
	OBJECT_ENTRY(CLSID_PropertyActionSequence, CPropertySequence)
	OBJECT_ENTRY(CLSID_PropertyActionJoin, CPropertyActionJoin)
	OBJECT_ENTRY(CLSID_PropertyActionSplit, CPropertyActionSplit)

	OBJECT_ENTRY(CLSID_SelectIdentObjTyp, CSelIDPropAct) 
	OBJECT_ENTRY(CLSID_ModifyIdent, CModIDPropAct) 
	OBJECT_ENTRY(CLSID_SelectFromObjectWindow, CSelObjWndPropAct)
	OBJECT_ENTRY(CLSID_DestinationObjectWindow, CDestObjWndPropAct)
	OBJECT_ENTRY(CLSID_DeleteObjects, CDelObjPropAct)
	OBJECT_ENTRY(CLSID_ClassifyByObjProp, CClsfyPropAct)
	OBJECT_ENTRY(CLSID_ImportDataPropAct, CImportPropAct)
	OBJECT_ENTRY(CLSID_GenTextPropAct, CGenTextPropAct)
	OBJECT_ENTRY(CLSID_ScriptPropAct, CScriptPropAct)
	OBJECT_ENTRY(CLSID_ObjekteDoppelnV2, CCopyObjects)
	OBJECT_ENTRY(CLSID_SelectObjectsDatasource, CSelectExportObjects)
	OBJECT_ENTRY(CLSID_AddAsObjectClass, CAddAsObjectClass)
	OBJECT_ENTRY(CLSID_DeleteObjectProperty, CDeleteObjectProperty)
	OBJECT_ENTRY(CLSID_PropertyOperation, CPropertyOperation)
	OBJECT_ENTRY(CLSID_GenerateObjectProperties, CGenerateObjectProperties)
//	OBJECT_ENTRY(CLSID_ObjekteVereinigen, CObjekteVereinigen)
	OBJECT_ENTRY(CLSID_ObjekteVereinigenEx, CObjekteVereinigenEx)
	OBJECT_ENTRY(CLSID_LimitSearches, CLimitSearches)
	OBJECT_ENTRY(CLSID_LimitPackets, CLimitPackets)
	OBJECT_ENTRY(CLSID_VBGeoComponent, CVBGeoComponent)
	OBJECT_ENTRY(CLSID_MkVBGeoComponent, CMkVBGeoComponent)
	OBJECT_ENTRY(CLSID_SaveObjectCollection, CSaveObjectCollection)
	OBJECT_ENTRY(CLSID_LoadObjectCollection, CLoadObjectCollection)
	OBJECT_ENTRY(CLSID_AreasToLines, CAreasToLines)
	OBJECT_ENTRY(CLSID_LinesToAreas, CLinesToAreas)

// SearchEngines 
	OBJECT_ENTRY(CLSID_TextSearchEngine, CTextSearchEngine) 
	OBJECT_ENTRY(CLSID_TextReplaceEngine, CTextReplaceEngine)

// sonstige Objekteinträge
	OBJECT_ENTRY(CLSID_EnumObjectsByNumber, CEnumObjectNumbers)
	OBJECT_ENTRY(CLSID_ProgressIndicator, CProgressIndicator)
	OBJECT_ENTRY(CLSID_MultiProgressIndicator, CMultiProgressIndicator)
	OBJECT_ENTRY(CLSID_RegisterExt, CRegisterExt)
	OBJECT_ENTRY(CLSID_DataTransferObject, CTRiASDataObject)

#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
// Objekteigenschaften
#if defined(_REGISTER_OBJECT_PROPERTIES)
	OBJECT_ENTRY(CLSID_ObjPropDataSource, CObjPropDataSource)
	OBJECT_ENTRY(CLSID_ObjPropDataSourceDesc, CObjPropDataSourceDesc)
	OBJECT_ENTRY(CLSID_ObjPropONr, CObjPropONr)
	OBJECT_ENTRY(CLSID_ObjPropGUID, CObjPropGUID)
	OBJECT_ENTRY(CLSID_ObjPropIdent, CObjPropIdent)
	OBJECT_ENTRY(CLSID_ObjPropObjClassCode, CObjPropObjClassCode)
	OBJECT_ENTRY(CLSID_ObjPropObjTypLong, CObjPropObjTypLong)
	OBJECT_ENTRY(CLSID_ObjPropQueryField, CObjPropQueryField)
#endif // defined(_REGISTER_OBJECT_PROPERTIES)
	OBJECT_ENTRY(CLSID_FakeTRiASLockFeature, CTRiASLockFeatureStandAlone)
	OBJECT_ENTRY(CLSID_ObjPropFeature, CObjPropMerkmal)

	OBJECT_ENTRY(CLSID_CatSimpleCache, CCatSimpleCache)
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300

#if defined(_USE_XML_GEOCOMPONENTS)
	OBJECT_ENTRY(CLSID_PropertySequenceService, CPropertySequenceService)
#if defined(_DEBUG)
	OBJECT_ENTRY(CLSID_ManageObjectProperties, CManageObjectProperties)
#endif // defined(_DEBUG)
#endif // defined(_USE_XML_GEOCOMPONENTS)

END_OBJECT_MAP()

void TermObjProps (void);	// freigeben der ObjPropCF's

#ifdef _MERGE_PROXYSTUB
extern "C" DWORD g_dwFlags = 0L;
extern "C" HINSTANCE hProxyDll;
#endif

extern "C" 
bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			g_hInstance = hInst;
#ifdef _MERGE_PROXYSTUB
		// erstmal feststellen, ob wirklich mut Proxies/Stubs gearbeitet werden soll
		CCurrentUser reg (g_cbRegConfig);

			g_dwFlags = 0L;
			reg.GetDWORD (TEXT("ProxyStub"), g_dwFlags);

		// jetzt evtl. ProxyStub initialisieren
			if (g_dwFlags) {
				hProxyDll = hInst;
				if (!PrxDllMain(hInst, dwReason, lpReserved))
					return FALSE;
			} else
				hProxyDll = NULL;
#endif
#if _TRiAS_VER < 0x0400
		// schon mal TRiAS V4 vorbereiten
			{
			CCurrentUser regCfg ("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");

				g_dwVer4 = 0;
				regCfg.GetDWORD ("FakeTRiAS4", g_dwVer4);
			}
#endif // _TRiAS_VER < 0x0400

		// Namen der DLL abfragen
		TCHAR szModule[_MAX_PATH];

			GetModuleFileName (hInst, szModule, _MAX_PATH);

		TCHAR szModuleShort[_MAX_PATH];
		int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
		LPOLESTR pszModule;

			USES_CONVERSION;
			if (cbShortName == _MAX_PATH)
				return false;
			pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

			strcpy (g_pDLLName, OLE2A(pszModule));

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
		HMODULE hTrias = GetModuleHandle (NULL);

			TX_ASSERT(NULL != hTrias);
			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
#if _TRiAS_VER >= 0x0300
			g_pDexExtensionProc2 = (DEXEXTENSIONPROC2)GetProcAddress (hTrias, TEXT("DEXEXTENSIONPROC2"));
			g_pDexxExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXXEXTENSIONPROC"));
#endif // _TRiAS_VER >= 0x0300
			g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

		// ATL Initialisieren
			_Module.Init (ObjectMap, hInst);
			DisableThreadLibraryCalls (hInst);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
#if defined(WIN32)
		TermObjProps();		// ATL freigeben
		_Module.Term();
#endif // WIN32

#if defined(_DEBUG)
		{
		string strName = g_pDLLName;
		string str = get_name(strName)+get_ext(strName);

			TX_TRACE1(TEXT("%s: exiting:\r\n"), str.c_str());
			if (0 != g_cObj) 
				TX_TRACE1(TEXT("\tInfo: Global object count: %ld\r\n"), g_cObj);
			if (0 != g_cLock) 
				TX_TRACE1(TEXT("\tInfo: Global lock count: %ld\r\n"), g_cLock);
			if (0 != _Module.GetLockCount())
				TX_TRACE1(TEXT("\tInfo: Global ATL lock count: %ld\r\n"), _Module.GetLockCount());
		}
#endif // _DEBUG
		break;
	}

return true;
}

#if defined(_MERGE_PROXYSTUB)
///////////////////////////////////////////////////////////////////////////////
// Testen, ob auf dieser Maschine DCOM enabled ist 
bool IsEnabledDCOM (void)
{
	TX_ASSERT(IsWin40());

CLocalMachine regDCOM (TEXT("SOFTWARE\\Microsoft\\Ole"));
TCHAR cbBuffer[10];
DWORD dwLen = sizeof(cbBuffer);

	if (!regDCOM.GetSubSZ (TEXT("EnableDCOM"), cbBuffer, dwLen))
		return false;

	return !_tcsicmp (cbBuffer, TEXT("y"));
}
#endif // defined(_MERGE_PROXYSTUB)

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Keys
static _ATL_REGMAP_ENTRY regEntryMap[] = 
{
#if _ATL_VER >= 0x0200
// HKCU\Software\uve\TRiAS\Config:ProxyStub
	{ L"PROXYSTUB", NULL },
	{ L"TRIAS", NULL },
	{ L"TRIASPATH", NULL, },
#else
// HKCU\Software\uve\TRiAS\Config:ProxyStub
	{ TEXT("PROXYSTUB"), NULL },
#endif // _ATL_VER
	{ NULL, NULL },		// EndeKennung
};

HRESULT RegisterAdditionalKeys(bool fRegister)
{
#if defined(_MERGE_PROXYSTUB)
#if _ATL_VER >= 0x0200
	regEntryMap[0].szData = (IsWin40() && (IsWinNT() || IsEnabledDCOM())) ? L"1" : L"0";
#else
	regEntryMap[0].szData = (IsWin40() && (IsWinNT() || IsEnabledDCOM())) ? TEXT("1") : TEXT("0");
#endif // _ATL_VER
#else // _MERGE_PROXY_STUB
#if _ATL_VER >= 0x0200
	regEntryMap[0].szData = L"0";
#else
	regEntryMap[0].szData = TEXT("0");
#endif // _ATL_VER
#endif // defined(_MERGE_PROXYSTUB)

#if _ATL_VER >= 0x0200
	USES_CONVERSION;

HINSTANCE hTRiAS = GetModuleHandle (NULL);
char cbBuffer[_MAX_PATH];

	GetModuleFileName(hTRiAS, cbBuffer, sizeof(cbBuffer));
	regEntryMap[1].szData = A2OLE(cbBuffer);

	PathRemoveFileSpec(cbBuffer);
	regEntryMap[2].szData = A2OLE(cbBuffer);
#endif // _ATL_VER

	return SUCCEEDED(_Module.UpdateRegistryFromResource(IDR_REGISTRY, fRegister, regEntryMap));
}

// DllRegisterServer - Adds entries to the system registry --------------------
STDAPI APIENTRY DllRegisterServer (void)
{
#ifdef _MERGE_PROXYSTUB
	if (g_dwFlags) {
		if (FAILED(PrxDllRegisterServer())) 
			return false;
	} 
#endif

	RegisterAdditionalKeys(true);
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
	DelegatorRegisterServer();
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300

	return _Module.RegisterServer(true);
}

// DllUnregisterServer - Removes entries from the system registry -------------
STDAPI APIENTRY DllUnregisterServer (void)
{
#ifdef _MERGE_PROXYSTUB
	PrxDllUnregisterServer();
#endif

	RegisterAdditionalKeys(false);
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
	DelegatorUnregisterServer();
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300

	return _Module.UnregisterServer();
}

#endif // WIN32

// alles merken, was zur Kommunikation mit dem Kern notwendig ist -------------
HWND __hWndM = NULL;
UINT __DexCmd = 0;
UINT __DexxCmd = 0;
UINT __DexNotify = 0;

extern "C" _TRIAS03_ENTRY
void FAR EXPORT02 FUNCTYPE InitTrias03 (HWND hWnd, UINT DEXCommand, UINT DEXXCommand, UINT DEXNotify) 
{
	__hWndM = hWnd;
	__DexCmd = DEXCommand;
	__DexxCmd = DEXXCommand;
	__DexNotify = DEXNotify;
}

#if defined(__XT) && defined(__DEXPROCS)

// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
#if defined(_DEBUG)	|| !defined(WIN32)	// ansonsten inline
extern "C" 
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);

	TX_ASSERT(NULL != __hWndM);
	return :: SendMessage (__hWndM, __DexCmd, w, l);
}
#if _TRiAS_VER >= 0x0300
extern "C" 
LRESULT PASCAL DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	TX_ASSERT(NULL != g_pDexExtensionProc2);
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
		
	TX_ASSERT(::IsWindow(__hWndM));
	return::SendMessage (__hWndM, __DexCmd, w, l);
}
extern "C"
LRESULT PASCAL DexxExtensionProc (WPARAM w, LPARAM l)
{
	TX_ASSERT(NULL != g_pDexxExtensionProc);
	if (g_pDexxExtensionProc)
		return (*g_pDexxExtensionProc)(w, l);
	return :: SendMessage (__hWndM, __DexxCmd, w, l);
}
#endif // _TRiAS_VER >= 0x0300
#endif // _DEBUG || !WIN32

extern "C" 
LRESULT WINAPI DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

	TX_ASSERT(NULL != __hWndM);
	return :: SendMessage (__hWndM, __DexNotify, w, l);
}

extern "C" 
LRESULT WINAPI DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

	TX_ASSERT(NULL != __hWndM);
	return :: PostMessage (__hWndM, __DexNotify, w, l);
}
#endif // __XT && __DEXPROCS


