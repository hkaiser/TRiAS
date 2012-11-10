// Generieren verschiedener Einträge in der RegDB und WIN.INI -----------------
// File: REGTRIAS.CXX

#include "StdAfx.h"

#include <shellapi.h>

#include "triasres.h"

#if defined(WIN16)
#include <tchar.h> 
#else
#if defined(_DEBUG)
#include <konsobj.hxx>
#endif // _DEBUG

#include <ospace/file/path.h>
#include <ospace/time/timedate.h>
#include <comcat.h>
#include <TrCatIDs.h>
#include <WrongTrCatIDs.h>
#include <Esnecil.h>
#include <funcs03.h>

#include "copystr.h"
#include "strings.h"
#include "regprog.h"
#endif // WIN16

#include <registry.hxx>
#include <cextreg.hxx>

//#include "extmain3.hxx"
#include "DllBindFromFileName.h"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_DEBUG)
#define TRIAS03_MODULENAME	TEXT("TRIAS33D.DLL")
#define FAKEMFC_MODULENAME	TEXT("FAKEMFCD.EXT")
#define TDBGEO_MODULENAME	TEXT("TDBGEOD.DLL")
#else // _DEBUG
#define TRIAS03_MODULENAME	TEXT("TRIAS323.DLL")
#define FAKEMFC_MODULENAME	TEXT("FAKEMFC.EXT")
#define TDBGEO_MODULENAME	TEXT("TDBGEO.DLL")
#endif // _DEBUG

// vorläufig, solange GEOMETR.DLL sich noch nicht selbst registriert (#HK960415)
#if defined(_DEBUG)
#define GEOMETR_MODULENAME	TEXT("%sGEOMETD.DLL")
#else // _DEBUG
#define GEOMETR_MODULENAME	TEXT("%sGEOMETR.DLL")
#endif // _DEBUG

static int CountModules (CVersionBind &rVer, LPCTSTR);
static int CountFiles (CVersionBind &rVer, LPCTSTR pcFPath, LPCTSTR pcExt);
static bool RegisterAllExtensions (CVersionBind &rVer, LPCTSTR pPath, bool fRegister, CRegistryProgress *pDlg = NULL);	// registriert alle Erweiterungen
static HRESULT RemoveComponentCategory (REFCATID catid);
extern "C" bool WINAPI FKeyDelete (HKEY hKey, LPCSTR pszKey);

const char g_cbTimeFmt[] = TEXT("%e. %B %Y, %T");	// TEXT("%A, %e. %B %Y, %T");

///////////////////////////////////////////////////////////////////////////////
// Component categories
// 19BBA822-01AA-4A90-B8E8-3F9D095A1216
EXTERN_C const CATID __declspec(selectany) CATID_TRiASStatistValue = 
	{ 0x19BBA822, 0x01AA, 0x4A90, 0xB8, 0xE8, 0x3F, 0x9D, 0x09, 0x5A, 0x12, 0x16 };

// 5784231F-3487-4EA9-ACE8-C5EADDB58794
EXTERN_C const CATID __declspec(selectany) CATID_TRiASStatistValuesContainer = 
	{ 0x5784231F, 0x3487, 0x4EA9, 0xAC, 0xE8, 0xC5, 0xEA, 0xDD, 0xB5, 0x87, 0x94 };

// 079639C6-3123-101C-BB62-00AA0018497C
EXTERN_C const CATID __declspec(selectany) CATID_TRiASDBEngine = 
	{ 0x079639C6, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C };

///////////////////////////////////////////////////////////////////////////////
// das folgende dient ausschließlich der Registrierung
#if !defined(_NO_REGISTRATION_CODE)

bool IsLegalRegNumber (LPCSTR pcRegEntry);

static bool RegisterAllEntries (LPCTSTR pPath, bool fFullReg);		// registriert alle Entries
static bool RegisterUninstaller (LPCTSTR pFPath);
static HRESULT CreateComponentCategory (LPCSTR pModule, CATID catid, WCHAR *catDescription, UINT uiRes);
static HRESULT InitComponentCategoryCache (CATID catid, bool fClearAll = false);
static bool TestCorrectPath (LPCSTR pPath);
static HRESULT RegisterToolBitmap (LPCSTR pModule, REFCATID catid, WCHAR *catDescription, UINT uiID);

// Initialisieren verschiedener Einträge in RegDB und WIN.INI -----------------
bool TriasRegInit (bool fForce, bool fFullReg, bool fSilent, bool fSetup)
{
	USES_CONVERSION;   

// 1. vollen PfadNamen von Trias besorgen
HMODULE hMod = GetModuleHandle (NULL);	// ResString (IDS_TRIASMODULE, 20));
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hMod, szModule, _MAX_PATH);

// Convert to short path to work around bug in NT4's CreateProcess
// #HK990528: fixed (Q201318)
TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;
   
	if (cbShortName == _MAX_PATH)
		return false;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

LPSTR pPath = OLE2A(pszModule);

	strupr (pPath);

LPTSTR pInBuff = new TCHAR [_MAX_PATH + 20];

#if _TRiAS_VER < 0x0400
// 2. WIN.INI setzen
ResString StbExt (IDS_REGSTBEXTENSION, 5);
ResString RisExt (IDS_REGRISEXTENSION, 5);

// alte Einräge aus WIN.INI entfernen
ResString RegExt (IDS_REGEXTENSION, 20);

	WriteProfileString (RegExt, StbExt+1, NULL);
	WriteProfileString (RegExt, RisExt+1, NULL);
#endif // _TRiAS_VER < 0x0400

// 3. Einträge in der RegDB initialisieren
//ResString rsOpenKey (IDS_REGOPENSUBKEY, 64);
//ResString rsExeIcon (IDS_REGEXEICON, 32);
LONG dw = _MAX_PATH + 20;
bool fWrite = false;

// alte Einträge (TRiAS1.20) grundsätzlich entfernen
	if (RegQueryValue (HKEY_CLASSES_ROOT, "Trias1.20", pInBuff, &dw) == ERROR_SUCCESS) 
	{
	// alle Unterschlüssel entfernen
		FKeyDelete (HKEY_CLASSES_ROOT, "Trias1.20");
		fWrite = true;		// alles andere neu schreiben
	}

	if (!fForce && !fWrite) {	// Pfad prüfen, um ggf. zu korrigieren
	// oder generieren, wenn der Pfad sich geändert hat
		fWrite = TestCorrectPath (pPath);
	}

	if (fForce || fWrite) {
	// evtl. fez\TRiAS Key herauslöschen
		CCurrentUser("Software\\fez").DeleteKey("TRiAS");
		CLocalMachine("SOFTWARE\\fez").DeleteKey("TRiAS");

	// fez nur dann löschen, wenn kein Subkey mehr da ist
		CCurrentUser("Software").DeleteKey("fez", false);
		CLocalMachine("SOFTWARE").DeleteKey("fez", false);

	// magischen Explorer Key löschen, welcher u.U. entscheidet, was beim Doppelklick 
	// auf ein Dokument gestartet wird
	CClassesRoot regApp("Applications");
		
		regApp.DeleteKey("TRiAS32.exe");
		regApp.DeleteKey("TRiAS32D.exe");

	// als erstes aktuelle Version im HKCU wegschreiben
	string resVersion (g_cbTRiAS);
	
		resVersion += g_cbSpace;
		resVersion += FakeTRiASName (IDS_SIGNONVERSION_MODAL, g_cbTRiAS);

	CCurrentUser regUserVer (TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY), true);

		if (m_esnecil.IsDemoCopy())
			resVersion+= " (Trial)";
		regUserVer.SetSZ(g_cbNil, resVersion.c_str());
			
	// jetzt wirklich registrieren
	LPTSTR pDrive = new TCHAR [_MAX_DRIVE];
	LPTSTR pNewPath = new TCHAR [_MAX_PATH];
	LPTSTR pFPath = new TCHAR [_MAX_FNAME];

		_splitpath (pPath, pDrive, pNewPath, NULL, NULL);
		_makepath (pFPath, pDrive, pNewPath, g_cbNil, g_cbNil);

		DELETE_OBJ (pDrive);
		DELETE_OBJ (pNewPath);

	CRegistryProgress *pDlg = NULL;
	CVersionBind Ver;

		TX_ASSERT(Ver.IsValid());
		if (Ver.IsValid()) {
			if (!fSilent) {
				pDlg = new CRegistryProgress(CountModules(Ver, pFPath)+3,
							(fForce && !fSetup) ? IDS_REGISTEREDMSG : 0, fFullReg);
				if (NULL != pDlg) {
					pDlg -> Show (ShowState(Centre|NoQuitOnHide));
					pDlg -> SetText (pPath);
				}
			}

			RegisterAllEntries (pFPath, fFullReg);
			if (NULL != pDlg) pDlg -> IncPos();

#if defined(_PROFILE)
			DELETE_OBJ (pInBuff);
			DELETE_OBJ (pPath);
			DELETE_OBJ(pDlg);
			return true;		// beim profiling niemals weiter registrieren
#endif // _PROPFILE

		// falsche CATID's entfernen
			RemoveComponentCategory (CATID_TRiASExtension_Wrong);
			RemoveComponentCategory (CATID_TRiASImportModule_Wrong);
			RemoveComponentCategory (CATID_TRiASExportModule_Wrong);
			RemoveComponentCategory (CATID_TRiASGeoComponent_Wrong);
			RemoveComponentCategory (CATID_TRiASGeoComponentContainer_Wrong);
			RemoveComponentCategory (CATID_TRiASSelfRegister_Wrong);

		// CATID's registrieren
			{
			string strCATExtension (FakeTRiASName(IDS_CATID_EXTENSION, g_cbTRiAS));
			string strCATImport (FakeTRiASName(IDS_CATID_IMPORTFILTER, g_cbTRiAS));
			string strCATExport (FakeTRiASName(IDS_CATID_EXPORTFILTER, g_cbTRiAS));
			string strCATGeoCom (FakeTRiASName(IDS_CATID_GEOCOMPONENT, g_cbTRiAS));
			string strCATGeoComCont (FakeTRiASName(IDS_CATID_GEOCOMPONENTCONTAINER, g_cbTRiAS));
			string strCATSelfRegister (FakeTRiASName(IDS_CATID_SELFREGISTER, g_cbTRiAS));
			string strCATObjProp (FakeTRiASName(IDS_CATID_OBJECTPROP, g_cbTRiAS));
			string strCATObjPropRO (FakeTRiASName(IDS_CATID_OBJECTPROP_RO, g_cbTRiAS));

				USES_CONVERSION;
				TX_VERIFY(SUCCEEDED(CreateComponentCategory (pPath, CATID_TRiASExtension, A2OLE(strCATExtension.c_str()), IDB_CATID_PLUGIN)));
				TX_VERIFY(SUCCEEDED(CreateComponentCategory (pPath, CATID_TRiASImportModule, A2OLE(strCATImport.c_str()), IDB_CATID_TOOLBITMAP)));
				TX_VERIFY(SUCCEEDED(CreateComponentCategory (pPath, CATID_TRiASExportModule, A2OLE(strCATExport.c_str()), IDB_CATID_TOOLBITMAP)));
				TX_VERIFY(SUCCEEDED(CreateComponentCategory (pPath, CATID_TRiASGeoComponent, A2OLE(strCATGeoCom.c_str()), IDB_CATID_TOOLBITMAP)));
				TX_VERIFY(SUCCEEDED(CreateComponentCategory (pPath, CATID_TRiASGeoComponentContainer, A2OLE(strCATGeoComCont.c_str()), IDB_CATID_TOOLBITMAP)));
				TX_VERIFY(SUCCEEDED(CreateComponentCategory (pPath, CATID_TRiASSelfRegister, A2OLE(strCATSelfRegister.c_str()), IDB_CATID_SELFREGISTER)));
				TX_VERIFY(SUCCEEDED(CreateComponentCategory (pPath, CATID_TRiASObjectProperty, A2OLE(strCATObjProp.c_str()), IDB_CATID_TOOLBITMAP)));
				TX_VERIFY(SUCCEEDED(CreateComponentCategory (pPath, CATID_TRiASObjectPropertyRO, A2OLE(strCATObjPropRO.c_str()), IDB_CATID_TOOLBITMAP)));
			}

		// Erweiterungen registrieren 
			RegisterUninstaller(pFPath);
			RegisterAllExtensions (Ver, pFPath, true, pDlg);	// registrieren

		// ComCatCache initialisieren
			if (NULL != pDlg) {
				pDlg -> IncPos();
				pDlg -> SetText (pPath);
			}

			TX_VERIFY(S_OK == InitComponentCategoryCache (CATID_TRiASCoordsystem, true));
			TX_VERIFY(S_OK == InitComponentCategoryCache (CATID_TRiASSelfRegister));
			TX_VERIFY(S_OK == InitComponentCategoryCache (CATID_TRiASDBEngine));
			TX_VERIFY(S_OK == InitComponentCategoryCache (CATID_TRiASExportModule));
//			TX_VERIFY(S_OK == InitComponentCategoryCache (CATID_TRiASImportModule));
			TX_VERIFY(S_OK == InitComponentCategoryCache (CATID_TRiASGeoComponent));
			TX_VERIFY(S_OK == InitComponentCategoryCache (CATID_TRiASGeoComponentContainer));
			TX_VERIFY(S_OK == InitComponentCategoryCache (CATID_TRiASStatistValue));
			TX_VERIFY(S_OK == InitComponentCategoryCache (CATID_TRiASStatistValuesContainer));

			DELETE_OBJ(pDlg);
		}
		DELETE_OBJ (pFPath);
	}

// Speicher freigeben
	DELETE_OBJ (pInBuff);
	return true;
}

// TRiAS als Demoversion registrieren
bool RegisterDemoRegNum (void)
{
CLocalMachine regName (g_cbRegVersion, true);
char cbBuffer[64];

	wsprintf (cbBuffer, "%03ld-%04ld-%08ld", 1L, 0L, 7621669L);
	return regName.SetSubSZ (g_cbSerial, cbBuffer);
}

// TRiAS in Registry eintragen ------------------------------------------------
typedef struct tagTRiASREGSERVER {
	HKEY m_hKeyRoot;	        // bezogen worauf
	const char *m_pKey;		    // Schlüssel 
	const char *m_pSubKey;	    // SubSchlüssel
	const char *m_pValue;		// zugehöriger Wert
	const char *m_pValueName;	// m_pSubKey und m_pValue sind NULL
	const char *m_pSubValue;	// dann ist das hier ein Wert für RegCreateKeyEx
	DWORD m_dwSubValue;	        // entweder als SZ oder als DWORD
	bool m_fFullReg;	        // nur bei FullRegister eintragen
	bool m_fOnlyIfNotExists;	// nur eintragen, wenn noch nicht existent
} TRiASREGSERVER;

static TRiASREGSERVER s_regEntries[] = {
// Dateierweiterungen
//	{ HKEY_CLASSES_ROOT, TEXT(".stb"), g_cbNil, g_cbDocKey, NULL, NULL, 0, false, },
//	{ HKEY_CLASSES_ROOT, TEXT(".ris"), g_cbNil, g_cbDocKey, NULL, NULL, 0, false, },
//	{ HKEY_CLASSES_ROOT, TEXT(".ris\\TRiAS.Document.2\\ShellNew"), NULL, NULL, TEXT("Command"), TEXT("%s") TRIAS_MODULENAME TEXT(" /Init:NoShortcut \"%%2\""), 0, false, },

// TRiAS.Document
//	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document"), g_cbNil, TEXT("TRiAS GIS-Datenbank"), NULL, NULL, 0, false, },
//	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document\\CurVer"), g_cbNil, g_cbDocKey, NULL, NULL, 0, false, },

// TRiAS.Document.2
//	{ HKEY_CLASSES_ROOT, g_cbDocKey, g_cbNil, TEXT("TRiAS 2.0 GIS-Datenbank"), NULL, NULL, 0, false, },
//	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document.2\\CLSID"), g_cbNil, TEXT("{937EEB40-2234-101B-AAE1-E7E7E7E7E7E7}"), NULL, NULL, 0, false, },	// #HK960124
//	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document.2\\DefaultIcon"), g_cbNil, TEXT("%s") TRIAS_MODULENAME TEXT(",5"), NULL, NULL, 0, false, },
//	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document.2\\shell\\open"), g_cbNil, TEXT("&Datenbank öffnen"), NULL, NULL, 0, false, },
//	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document.2\\shell\\open\\command"), g_cbNil, TEXT("%s") TRIAS_MODULENAME TEXT(" \"%%1\""), NULL, NULL, 0, false, },

	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.UndoRedoObject"), g_cbNil, TEXT("TRiAS Undo/Redo Verwaltung"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.UndoRedoObject\\CLSID"), g_cbNil, TEXT("{B16261A1-856C-11CE-8CC3-444553540000}"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{B16261A1-856C-11CE-8CC3-444553540000}"), g_cbNil, TEXT("TRiAS Undo/Redo Verwaltung"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{B16261A1-856C-11CE-8CC3-444553540000}\\ProgID"), g_cbNil, TEXT("TRiAS.UndoRedoObject"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{B16261A1-856C-11CE-8CC3-444553540000}\\InprocServer32"), g_cbNil, TEXT("%s") TRIAS03_MODULENAME, TEXT("ThreadingModel"), TEXT("Apartment"), 0, false, },

	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.DataTransferObject"), g_cbNil, TEXT("TRiAS Datentransfer-Objekt"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.DataTransferObject\\CLSID"), g_cbNil, TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), g_cbNil, TEXT("TRiAS Datentransfer-Objekt"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}\\ProgID"), g_cbNil, TEXT("TRiAS.DataTransferObject"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}\\InprocServer32"), g_cbNil, TEXT("%s") TRIAS03_MODULENAME, TEXT("ThreadingModel"), TEXT("Apartment"), 0, false, },

// FullRegs
	{ HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, g_cbSysAdmin, NULL, 1, true, },
	{ HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, g_cbShowSysFeatures, NULL, 1, true, },
#if defined(_DEBUG)
	{ HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, TEXT("GlobalLicense"), NULL, 1, true, },
#if _TRiAS_VER < 0x0400
	{ HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, TEXT("KonsistenzTest"), NULL, KTDNothing /*(KTDRepair|KTDQueryCorrection|KTDProtocol)*/, true, },
#endif // _TRiAS_VER < 0x0400
#endif // _DEBUG

// vorläufig, solange GEOMETR.DLL sich noch nicht selbst registriert (#HK960415)
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.ObjektGeometrie.1"), g_cbNil, TEXT("ObjektGeometrie"), NULL, NULL, 0, false,  },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.ObjektGeometrie.1\\CLSID"), g_cbNil, TEXT("{07963832-3123-101C-BB62-00AA0018497C}"), NULL, NULL, 0, false, },

	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{07963832-3123-101C-BB62-00AA0018497C}"), g_cbNil, TEXT("ObjektGeometrie"), NULL, NULL, 0, false,  },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{07963832-3123-101C-BB62-00AA0018497C}\\InprocServer32"), g_cbNil, GEOMETR_MODULENAME, TEXT("ThreadingModel"), TEXT("Apartment"), 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{07963832-3123-101C-BB62-00AA0018497C}\\ProgID"), g_cbNil, TEXT("TRiAS.ObjektGeometrie.1"), NULL, NULL, 0, false, },

// EndeKennung
	{ 0, NULL, NULL, NULL, NULL, NULL, 0, false, },

#define s_regEntries40	s_regEntries
};

#endif // !defined(_NO_REGISTRATION_CODE)

// Alle Registrierungen entfernen ---------------------------------------------
typedef struct TRiASUNREGSERVER {
	HKEY m_hKey;
	const char *m_pKey;
} TRiASUNREGSERVER;

static TRiASUNREGSERVER s_unregEntries[] = {
//	{ HKEY_CLASSES_ROOT, TEXT(".stb"), },			// Dateierweiterungen
//	{ HKEY_CLASSES_ROOT, TEXT(".ris"), },
	{ HKEY_CLASSES_ROOT, TEXT("Trias1.20"), },				// altes TRiAS
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Application"), },		// TRiAS.Application
//	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document"), },			// TRiAS.Document
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.DataTransferObject"), },// DataTransferObject
	{ HKEY_CLASSES_ROOT, TEXT("CLSID") TEXT("\\") TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.ObjektGeometrie.1"), },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID") TEXT("\\") TEXT("{07963832-3123-101C-BB62-00AA0018497C}"), },
	{ HKEY_CLASSES_ROOT, g_cbDocKey, },						// TRiAS.Document
	{ HKEY_CLASSES_ROOT, g_cbAppKey, },						// TRiAS.Application.2
	{ HKEY_CURRENT_USER, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY), },
//	{ HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY), },
	{ NULL, NULL, },			// EndeKennung
};

bool TriasRegUnInit (bool fSilent, bool fFullUninstall)
{
#if _TRiAS_VER < 0x0400
// alte Einräge aus WIN.INI entfernen
ResString StbExt (IDS_REGSTBEXTENSION, 5);
ResString RisExt (IDS_REGRISEXTENSION, 5);
ResString RegExt (IDS_REGEXTENSION, 20);

	WriteProfileString (RegExt, StbExt+1, NULL);
	WriteProfileString (RegExt, RisExt+1, NULL);
#endif // _TRiAS_VER < 0x0400

// vollen PfadNamen von Trias besorgen
HMODULE hMod = GetModuleHandle (NULL);
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hMod, szModule, _MAX_PATH);

// Convert to short path to work around bug in NT4's CreateProcess
// #HK990528: fixed (Q201318)
TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;

	USES_CONVERSION;   
	if (cbShortName == _MAX_PATH)
		return false;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

LPSTR pPath = OLE2A(pszModule);

	strupr (pPath);

// Erweiterungen unregistrieren
LPTSTR pDrive = new TCHAR [_MAX_DRIVE];
LPTSTR pNewPath = new TCHAR [_MAX_PATH];
LPTSTR pFPath = new TCHAR [_MAX_FNAME];

	_splitpath (pPath, pDrive, pNewPath, NULL, NULL);
	_makepath (pFPath, pDrive, pNewPath, g_cbNil, g_cbNil);

	DELETE_OBJ (pDrive);
	DELETE_OBJ (pNewPath);

CRegistryProgress *pDlg = NULL;
CVersionBind Ver;

	TX_ASSERT(Ver.IsValid());
	if (Ver.IsValid()) {
		if (!fSilent) {
#if defined(_DEBUG)
		bool fShowNames = true;
#else
		bool fShowNames = false;
#endif // _DEBUG

			pDlg = new CRegistryProgress (CountModules(Ver, pFPath)+1,
						fFullUninstall ? 0 : IDS_UNREGISTEREDMSG, fShowNames);
			if (NULL != pDlg) 
				pDlg -> Show (ShowState(Centre|NoQuitOnHide));
		}
		RegisterAllExtensions (Ver, pFPath, false, pDlg);	// alles aufräumen
	}

// falsche CATID's entfernen
	RemoveComponentCategory (CATID_TRiASExtension_Wrong);
	RemoveComponentCategory (CATID_TRiASImportModule_Wrong);
	RemoveComponentCategory (CATID_TRiASExportModule_Wrong);
	RemoveComponentCategory (CATID_TRiASGeoComponent_Wrong);
	RemoveComponentCategory (CATID_TRiASGeoComponentContainer_Wrong);
	RemoveComponentCategory (CATID_TRiASSelfRegister_Wrong);

// richtige CATID's entfernen
	RemoveComponentCategory (CATID_TRiASExtension);
	RemoveComponentCategory (CATID_TRiASImportModule);
	RemoveComponentCategory (CATID_TRiASExportModule);
	RemoveComponentCategory (CATID_TRiASGeoComponent);
	RemoveComponentCategory (CATID_TRiASGeoComponentContainer);
	RemoveComponentCategory (CATID_TRiASSelfRegister);

	DELETE_OBJ (pFPath);

// Registry säubern
int i = 0;

	while (s_unregEntries[i].m_hKey) {
#if !defined(WIN16) && defined(ENABLE_WIN32S_CODE)
		if (!IsWin32s() || s_unregEntries[i].m_hKey == HKEY_CLASSES_ROOT)
#endif // WIN32 && ENABLE_WIN32S_CODE
			FKeyDelete (s_unregEntries[i].m_hKey, s_unregEntries[i].m_pKey);
		i++;
	}

bool fResult = true;

// wenn TRiAS das letzte registrierte Programm der TRiAS war, dann auch noch
// den Schlüssel entfernen. 
// Bei existierenden SubKey's macht die Funktion garnichts.
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
		RegDeleteKey (HKEY_CURRENT_USER, TEXT("Software\\" REG_COMPANY_KEY));
		RegDeleteKey (HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\" REG_COMPANY_KEY));
	}

#if _TRiAS_VER < 0x0400
// vollständiges DeInstallieren muß uninst rufen
	try {
		if (fFullUninstall) {
		CLocalMachine regUnInst (KEY_READ, g_cbUninstall);
		char cbBuffer[2*_MAX_PATH];
		DWORD dwLen = sizeof(cbBuffer);

			if (!regUnInst.GetSubSZ (g_cbOrigUninstallString, cbBuffer, dwLen)) 
				throw false;

		// execute orifinal uninstallstring
			if (IsWin40()) {
			string strCmd (TEXT("start.exe "));		// use start.exe to avoid file locking problems
			
				strCmd += cbBuffer;
				::WinExec (strCmd.c_str(), SW_HIDE);
			} else
				App::Run (cbBuffer);
		}
	} catch (bool) {
		fResult = false;
	}
#endif // _TRiAS_VER < 0x0400

	DELETE_OBJ(pDlg);
	return fResult;
}

// Löschen eines Schlüssels aus der Registry samt allen SubKeys ---------------
// Diese Funktion ist rukursiv und löscht von unten her alles weg
static bool FSubKeyDelete (HKEY hUpKey, LPCSTR szRegPath);

extern "C" bool WINAPI FKeyDelete (HKEY hKey, LPCSTR szKey)
{
	return FSubKeyDelete (hKey, szKey);
}

static bool FSubKeyDelete (HKEY hUpKey, LPCSTR szRegPath)
{
HKEY hKey;
DWORD retCode;
char cbBuffer[_MAX_PATH];

// Use RegOpenKey() with the new Registry path to get an open handle
// to the child key you want to enumerate.
	retCode = RegOpenKey (hUpKey, szRegPath, &hKey);
	if (retCode != ERROR_SUCCESS) return false;

// alle Subkeys löschen
DWORD i = 0;

	while (RegEnumKey (hKey, i++, cbBuffer, sizeof(cbBuffer)) == ERROR_SUCCESS) {
		if (!FSubKeyDelete (hKey, cbBuffer))
			break;
	}
	RegCloseKey (hKey);   // Close the key handle.

// Key selbst löschen
	retCode = RegDeleteKey (hUpKey, szRegPath);

return (retCode == ERROR_SUCCESS);
}

#if !defined(_NO_REGISTRATION_CODE)

// Alle Einträge aus TRiASREGISTRY registrieren -------------------------------
static 
bool RegisterAllEntries(LPCTSTR pFPath, bool fFullReg, TRiASREGSERVER *pTRS)
{
char cbBuffer[_MAX_PATH];

	for (/**/; pTRS -> m_pKey; pTRS++) {
		if (NULL != pTRS -> m_pSubKey) {
			wsprintf (cbBuffer, pTRS -> m_pValue, pFPath);

		CClassesRoot regEntry (pTRS -> m_pKey, true);

			TX_ASSERT(regEntry.isValid() || !AmIAdministrator());
			if (regEntry.isValid())
				TX_VERIFY(regEntry.SetSZ (pTRS -> m_pSubKey, cbBuffer));
		} 
		else {
#if defined(ENABLE_WIN32S_CODE)
			if (IsWin32s()) continue;
#endif // ENABLE_WIN32S_CODE

			if (!pTRS -> m_fFullReg || fFullReg) {
			CRegistry regEntry (pTRS -> m_hKeyRoot, pTRS -> m_pKey, true);
			DWORD dwData = 0;

				TX_ASSERT(regEntry.isValid() || !AmIAdministrator());
				if (!regEntry.isValid()) continue;
				if (NULL != pTRS -> m_pSubValue) {	// als SZ eintragen
					wsprintf (cbBuffer, pTRS -> m_pSubValue, pFPath);

				char cbBuffer[_MAX_PATH];
				DWORD dwLen = sizeof(cbBuffer);

					if (!pTRS->m_fOnlyIfNotExists || 
						!regEntry.GetSubSZ(pTRS->m_pValueName, cbBuffer, dwLen)) 
					{
					// ggf. nur erzeugen, wenns noch nicht da ist
						TX_VERIFY(regEntry.SetSubSZ (pTRS -> m_pValueName, cbBuffer));
					}
				} 
				else if (!pTRS->m_fOnlyIfNotExists || 
						 !regEntry.GetDWORD(pTRS -> m_pValueName, dwData)) 
				{
				// oder als DWORD
					TX_VERIFY(regEntry.SetDWORD (pTRS -> m_pValueName, pTRS -> m_dwSubValue));
				}
			} 
#if !defined(_DEBUG)
		// nur in Release-Variante
			else if (pTRS -> m_fFullReg && !fFullReg) {
			// admin-Einträge löschen, wenn nicht FullReg
			CRegistry regEntry (pTRS -> m_hKeyRoot, pTRS -> m_pKey);

				if (!regEntry.isValid() || !AmIAdministrator()) 
					continue;		// Entry existiert nicht
				regEntry.DeleteValue (pTRS -> m_pValueName);
			}
#endif // !defined(_DEBUG)
		}
	}
	return true;
}

static 
bool RegisterAllEntries (LPCTSTR pFPath, bool fFullReg)
{
// alle vorgegebenen Schlüssel aus der Struktur registrieren
TRiASREGSERVER *pTRS = IsWin40() ? s_regEntries40 : s_regEntries;

    if (!RegisterAllEntries(pFPath, fFullReg, pTRS))
        return false;

// ggf. spezielle Einträge für GCO Produktion initialisieren
CEsnecil esnecil;

    if (esnecil.VerifyOptions(CKIOPTION_GCOPRODUCTION)) {
    static TRiASREGSERVER regGCO[] = {
        // AutoBackup einschalten
	        { HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, g_cbBackupDatafiles, NULL, 1, false, true, },

        // Beim Löschen warnen
	        { HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, g_cbWarnBeforeDelObj, NULL, 1, false, },

        // EndeKennung
	        { 0, NULL, NULL, NULL, NULL, NULL, 0, false, },
        };
        return RegisterAllEntries(pFPath, fFullReg, regGCO);
    }
    return true;
}

#endif // !defined(_NO_REGISTRATION_CODE)

// Registrieren aller Erweiterungen im aktuellen Verzeichnis ------------------
static 
bool RegisterFiles (int fh, CVersionBind &rVer, LPCTSTR pcFPath, 
	LPCTSTR pcExt, bool fRegister, CRegistryProgress *pDlg, 
	LPCSTR pcSkipName = NULL)
{
HANDLE hFile;
string strFile (pcFPath);
WIN32_FIND_DATA c_file;
bool fGlobal = true;		// erstmal annehmen, daß alles ok ist

	strFile += pcExt;
	if ((hFile = FindFirstFile (strFile.c_str(), &c_file)) == INVALID_HANDLE_VALUE)
		return true; 		// nichts gefunden

	do {
		if (c_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		if (NULL != pcSkipName) {
		// diese Datei überspringen
			if (!stricmp(pcSkipName, c_file.cFileName))
				continue;
		}
		strFile = string(pcFPath) + c_file.cFileName;

	CExtReg Ext (rVer, strFile, fh);

		if (!Ext.SupportsSelfRegister()) continue;

	bool fResult = fRegister ? Ext.Register() : Ext.Unregister();

		if (!fResult)
			fGlobal = false;
		if (NULL != pDlg) {
			pDlg -> SetText (strFile.c_str(), fResult ? BLACK : RED);
			pDlg -> IncPos();
		}
		::CoFreeUnusedLibraries();

	} while (FindNextFile (hFile, &c_file));

	FindClose (hFile);
	return fGlobal;
}

#if !defined(_NO_REGISTRATION_CODE)
static 
bool RegisterUninstaller (LPCTSTR pFPath)
{
// Uninstallbezeichner korrigieren
CLocalMachine regUnInst (g_cbUninstall, true);
string resVersion (g_cbTRiAS);

	resVersion += g_cbSpace;
	resVersion += FakeTRiASName (IDS_SIGNONVERSION, g_cbTRiAS);
	if (!regUnInst.SetSubSZ (g_cbDisplayName, resVersion.c_str()))
		return false;

#if _TRiAS_VER < 0x0400
// existierende UninstallInfo lesen und unter modifiziertem Namen neu ablegen
char cbBuffer[2*_MAX_PATH];
DWORD dwLen = sizeof(cbBuffer);

	if (!regUnInst.GetSubSZ (g_cbUninstallString, cbBuffer, dwLen))
		return false;

	if (NULL == strstr (cbBuffer, g_cbUnregFull)) {
	// nur schreiben, wenn neuer UnInst-string einer zwischenzeitlichen Installation
		if (!regUnInst.SetSubSZ (g_cbOrigUninstallString, cbBuffer))
			return false;
	}

HMODULE hTRiAS = GetModuleHandle(NULL);

	GetModuleFileName(hTRiAS, cbBuffer, sizeof(cbBuffer));
	strcat (cbBuffer, g_cbUnregFull);
	if (!regUnInst.SetSubSZ (g_cbUninstallString, cbBuffer))
		return false;
#endif // _TRiAS_VER < 0x0400

	return true;
}
#endif // !defined(_NO_REGISTRATION_CODE)

static bool RegisterAllExtensions (
	CVersionBind &rVer, LPCTSTR pFPath, bool fRegister, CRegistryProgress *pDlg)
{
// evtl. LogFile erzeugen und Version und Datum reinschreiben
HINSTANCE hTRiAS = GetModuleHandle(NULL);
HFILE fh = HFILE_ERROR;

	if (fRegister) {
	// 'REGISTER.LOG' im aktuellen TRiAS-Verzeichnis erzeugen
	char cbBuffer[_MAX_PATH];

		GetModuleFileName (hTRiAS, cbBuffer, sizeof(cbBuffer));

	os_path path (cbBuffer);

		path.filename ("register.log");
		fh = _lcreat (string(path).c_str(), 0);
	}

	if (HFILE_ERROR != fh) {
	ResString resVersion (IDS_SIGNONVERSION_MODAL, 128);
	ResString resNotRegistered (IDS_NOTREGISTEREDVERSION, 128);
//	CLocalMachine regName (g_cbRegVersion);
	os_time_and_date now;
//	char cbRegNr[65];
//	DWORD dwLen = sizeof(cbRegNr);
//
//		if (!regName.GetSubSZ (g_cbSerial, cbRegNr, dwLen) || !IsLegalRegNumber (cbRegNr)) 
//			strcpy (cbRegNr, resNotRegistered);

		TX_TRY(now = os_time_and_date::now());

	os_string strT (FakeTRiASName (IDS_LOGVERSIONINFO, g_cbTRiAS, resVersion.Addr()));
	
		_lwrite (fh, strT.c_str(), strT.size());
		strT = FakeTRiASName (IDS_LOGSTART, now.to_string (g_cbTimeFmt).c_str());
		_lwrite (fh, strT.c_str(), strT.size());
	}

// jetzt wirklich registrieren
bool fGlobal = true;		// alles ok?

// TDBGeo ist die erste beim anmelden
	if (!RegisterFiles (fh, rVer, pFPath, TDBGEO_MODULENAME, true, NULL))	// wird für FAKEMFC benötigt
		fGlobal = false;

CDLLBindFromFileName FakeMFC (hTRiAS, FAKEMFC_MODULENAME);

	if (NULL != pDlg) pDlg -> IncPos();

	if (!RegisterFiles (fh, rVer, pFPath, TRIAS03_MODULENAME, fRegister, pDlg))	// RegisterHelper registrieren
		fGlobal = false;
	if (!RegisterFiles (fh, rVer, pFPath, TEXT("*.dll"), fRegister, pDlg, TRIAS03_MODULENAME))	// Dll's registrieren
		fGlobal = false;
	if (!RegisterFiles (fh, rVer, pFPath, TEXT("*.ext"), fRegister, pDlg))	// Erweiterungen registrieren
		fGlobal = false;
	if (!RegisterFiles (fh, rVer, pFPath, TEXT("*.ctf"), fRegister, pDlg))	// KoordinatenTransformationen registrieren
		fGlobal = false;
	if (!RegisterFiles (fh, rVer, pFPath, TEXT("*.css"), fRegister, pDlg))	// KoordinatenTransformationen registrieren
		fGlobal = false;
	if (!RegisterFiles (fh, rVer, pFPath, TEXT("*.vmd"), fRegister, pDlg))	// Visualisierungsmodule registrieren
		fGlobal = false;
	if (!RegisterFiles (fh, rVer, pFPath, TEXT("*.ebn"), fRegister, pDlg))	// BasicExtensions registrieren
		fGlobal = false;
	if (!RegisterFiles (fh, rVer, pFPath, TEXT("*.flt"), fRegister, pDlg))	// ExportModule registrieren
		fGlobal = false;

// TDBGeo ist die letzte beim abmelden
	if (!fRegister && !RegisterFiles (fh, rVer, pFPath, TDBGEO_MODULENAME, false, NULL))	// wird für FAKEMFC benötigt
		fGlobal = false;

// LogDatei schließen
	if (HFILE_ERROR != fh) {
	os_time_and_date now;

		TX_TRY(now = os_time_and_date::now());
	
	os_string strT (FakeTRiASName (IDS_LOGVERSIONINFOEND, now.to_string (g_cbTimeFmt).c_str()));

		_lwrite (fh, strT.c_str(), strT.size());
		_lclose (fh);
	}
	return fGlobal;
}

//static bool UnRegisterAllExtensions (CVersionBind &rVer, LPCTSTR pFPath, 
//	bool fRegister, CRegistryProgress *pDlg)
//{
//HINSTANCE hFakeMfc = ::LoadLibrary (FAKEMFC_MODULENAME);	// muß immer geladen sein
//bool fGlobal = true;		// alles ok?
//
//	if (NULL != pDlg) pDlg -> IncPos();
//	if (!RegisterFiles (rVer, pFPath, TEXT("*.ext"), fRegister, pDlg))	// Erweiterungen registrieren
//		fGlobal = false;
//	if (!RegisterFiles (rVer, pFPath, TEXT("*.css"), fRegister, pDlg))	// KoordinatenTransformationen registrieren
//		fGlobal = false;
//	if (!RegisterFiles (rVer, pFPath, TEXT("*.ctf"), fRegister, pDlg))	// KoordinatenTransformationen registrieren
//		fGlobal = false;
//	if (!RegisterFiles (rVer, pFPath, TEXT("*.ebn"), fRegister, pDlg))	// Visualisierungsmodule registrieren
//		fGlobal = false;
//	if (!RegisterFiles (rVer, pFPath, TEXT("*.vmd"), fRegister, pDlg))	// Visualisierungsmodule registrieren
//		fGlobal = false;
//	if (!RegisterFiles (rVer, pFPath, TEXT("*.dll"), fRegister, pDlg, TRIAS03_MODULENAME))	// Dll's registrieren
//		fGlobal = false;
//	if (!RegisterFiles (rVer, pFPath, TRIAS03_MODULENAME, fRegister, pDlg))	// RegisterHelper als letzten registrieren
//		fGlobal = false;
//
//	if (NULL != hFakeMfc) 
//		::FreeLibrary (hFakeMfc);
//
//	return fGlobal;
//}

// Zählen der zu behandelnden Module
static int CountModules (CVersionBind &rVer, LPCTSTR pFPath)
{
int iCnt = 0;		// TRiAS03

	iCnt += CountFiles (rVer, pFPath, TEXT("*.dll"));
	iCnt += CountFiles (rVer, pFPath, TEXT("*.ext"));
	iCnt += CountFiles (rVer, pFPath, TEXT("*.ctf"));
	iCnt += CountFiles (rVer, pFPath, TEXT("*.css"));
	iCnt += CountFiles (rVer, pFPath, TEXT("*.vmd"));
	iCnt += CountFiles (rVer, pFPath, TEXT("*.ebn"));
	iCnt += CountFiles (rVer, pFPath, TEXT("*.flt"));
	return iCnt;
}

static int CountFiles (CVersionBind &rVer, LPCTSTR pcFPath, LPCTSTR pcExt)
{
HANDLE hFile;
string strFile (pcFPath);
WIN32_FIND_DATA c_file;
int iCnt = 0;

	strFile += pcExt;
	if ((hFile = FindFirstFile (strFile.c_str(), &c_file)) == INVALID_HANDLE_VALUE)
		return 0; 		// nichts gefunden

	do {
		if (c_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		strFile = string(pcFPath) + c_file.cFileName;

	CExtReg Ext (rVer, strFile);

		if (Ext.SupportsSelfRegister())
			iCnt++;

	} while (FindNextFile (hFile, &c_file));

	FindClose (hFile);
	return iCnt;
}

// Testen, ob der aktuelle Pfad dem in der Registry entspricht ----------------
static bool TestCorrectPath (LPCSTR pPath)
{
char cbBuffer[_MAX_PATH+20];
LONG dw = _MAX_PATH + 20;

#if defined(_FORCE_LEGACY_CODE)
	if (!IsWin40()) {
	// Version im HKCR vergleichen
	CClassesRoot regCurVer (KEY_READ, TEXT("TRiAS.Document\\CurVer"));

		dw = _MAX_PATH + 20;
		if (!regCurVer.GetSZ (g_cbNil, cbBuffer, dw)) 
			return true;

	string strIn (cbBuffer);
	
	// aktive Programmversion abfragen
		if (strIn != g_cbDocKey) 
			return true;
		
	// aktuellen Pfad abfragen
		strIn += TEXT("\\shell\\open\\command");
	
	CClassesRoot regShell (KEY_READ, strIn.c_str());
	
		dw = _MAX_PATH+20;
		if (!regShell.GetSZ (g_cbNil, cbBuffer, dw))
			return true;
	
	string strPath (cbBuffer);

		if (_strnicmp (pPath, strPath.c_str(), strlen(pPath))) 
			return true;
	} else 
#endif // defined(_FORCE_LEGACY_CODE)
	{
	// Version im HKCR vergleichen
	CClassesRoot regCurVer (KEY_READ, TEXT("TRiAS.Document"));
	
		if (!regCurVer.GetSZ (TEXT("CurVer"), cbBuffer, dw)) 
			return true;

	string strIn (cbBuffer);
	
	// aktive Programmversion abfragen
		if (strIn != g_cbDocKey) 
			return true;

	// aktuellen Pfad abfragen
		strIn += TEXT("\\shell\\open");
	
	CClassesRoot regShell (KEY_READ, strIn.c_str());
	
		dw = _MAX_PATH+20;
		if (!regShell.GetSZ (TEXT("command"), cbBuffer, dw))
			return true;
	
	string strPath (cbBuffer);

		if (_strnicmp (pPath, strPath.c_str(), strlen(pPath))) 
			return true;

	// konkrete Version abstimmen
	CLocalMachine regUnInst (KEY_READ, g_cbUninstall);

		dw = _MAX_PATH;
		if (!regUnInst.GetSubSZ (g_cbDisplayName, cbBuffer, (DWORD &)dw))
			return true;

	string strVersion (cbBuffer);
	string resVersion (g_cbTRiAS);
	
		resVersion += g_cbSpace;
		resVersion += FakeTRiASName (IDS_SIGNONVERSION, g_cbTRiAS);
		if (!(strVersion == resVersion))
			return true;

	// Version im HKCU vergleichen
	CCurrentUser regUserVer (KEY_READ, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY));

		dw = _MAX_PATH;
		if (!regUserVer.GetSZ(g_cbNil, cbBuffer, dw))
			return true;	// existiert nicht

		strVersion = cbBuffer;

		resVersion = g_cbTRiAS;
		resVersion += g_cbSpace;
		resVersion += FakeTRiASName (IDS_SIGNONVERSION_MODAL, g_cbTRiAS);
		if (m_esnecil.IsDemoCopy())
			resVersion += " (Trial)";
		if (!(strVersion == resVersion))
			return true;
	}
	return false;	// alles stimmt, nicht neu schreiben
}

#if !defined(_NO_REGISTRATION_CODE)

static HRESULT CreateComponentCategory (
	LPCSTR pModule, CATID catid, WCHAR *catDescription, UINT uiRes)
{
ICatRegister *pcr = NULL;
HRESULT hr = S_OK;

	hr = CoCreateInstance (CLSID_CatSimpleCache, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID *)&pcr);
	if (FAILED(hr))	return hr;

// Make sure the HKCR\Component Categories\{..catid...}
// key is registered
CATEGORYINFO catinfo;

	catinfo.catid = catid;

#if defined(_GERMAN_RESOURCES)
	catinfo.lcid = 0x0407;			// german
#elif defined(_ENGLISH_RESOURCES)
	catinfo.lcid = 0x0409;			// english
#else
#error "No LCID given for CATID's\n"
	catinfo.lcid = GetUserDefaultLCID();
#endif

// Make sure the provided description is not too long.
// Only copy the first 127 characters if it is
int len = wcslen(catDescription);

	if (len > 127) len = 127;
    wcsncpy (catinfo.szDescription, catDescription, len);

// Make sure the description is null terminated
	catinfo.szDescription[len] = '\0';
    hr = pcr -> RegisterCategories (1, &catinfo);
	pcr -> Release();

	if (SUCCEEDED(hr)) 		// Bitmap registrieren
		hr = RegisterToolBitmap (pModule, catid, catDescription, uiRes);
	return hr;
}

static HRESULT RegisterToolBitmap (LPCSTR pModule, REFCATID catid, 
	WCHAR *catDescription, UINT uiID)
{
string str (g_cbClsId);
LPOLESTR poleCATID = NULL;
HRESULT hr = StringFromIID (catid, &poleCATID);

	if (SUCCEEDED(hr)) {
		USES_CONVERSION;
		str += g_cbDel;
		str += OLE2A(poleCATID);

	CClassesRoot regCat (str.c_str(), true);
	char cbBuffer[20];

		regCat.SetSZ (NULL, OLE2A(catDescription));

		str = pModule;
		str += TEXT(",");
		str += ltoa (uiID, cbBuffer, 10);
		regCat.SetSZ (g_cbToolboxBitmap, str.c_str());
		regCat.SetSubSZ (g_cbAppID, TEXT("{8DE4E3C2-4D53-101B-AAE1-E7E7E7E7E7E7}"));
	}
	CoTaskMemFree (poleCATID);
	return hr;
}

// Cache initialisieren
HRESULT InitComponentCategoryCache (CATID catid, bool fClearAll)
{
ICatSimpleCache *pcr = NULL;
HRESULT hr = S_OK;

	hr = CoCreateInstance (CLSID_CatSimpleCache, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatSimpleCache, (LPVOID *)&pcr);
	if (FAILED(hr))	return hr;

	if (fClearAll)
		pcr -> ClearCacheAll();
	hr = pcr -> InitializeCache (catid, VARIANT_TRUE);
	pcr -> Release();
	return hr;
}

#else

EXTERN_C const CLSID CLSID_CatSimpleCache =
	{ 0xEA68A685, 0x5166, 0x4E55, {0x90, 0x62, 0x0B, 0x13, 0x06, 0x81, 0x33, 0x93 }};

#endif // !defined(_NO_REGISTRATION_CODE)
 
static HRESULT RemoveComponentCategory (REFCATID catid)
{
ICatRegister *pcr = NULL;
HRESULT hr = S_OK;

	hr = CoCreateInstance (CLSID_CatSimpleCache, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID *)&pcr);
	if (FAILED(hr))	return hr;

    hr = pcr -> UnRegisterCategories (1, (CATID *)&catid);
	pcr -> Release();
	return hr;
}
 
