// Generieren verschiedener Einträge in der RegDB und WIN.INI -----------------
// File: REGTRIAS.CXX

#include "triaspre.hxx"

#include <shellapi.h>

#include "triasres.h"

#if !defined(WIN32)
#include <tchar.h> 
#else
#if defined(_DEBUG)
#include <konsobj.hxx>
#endif // _DEBUG
#include <comcat.h>
#include <TrCatIDs.h>

#include "strings.h"
#include "regprog.h"
#endif // !WIN32

#include <registry.hxx>
#include <cextreg.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(WIN32)
#if defined(_DEBUG)
//#define TRIASEXE_MODULENAME	TEXT("TRIAS32D.EXE")
#define TRIAS03_MODULENAME	TEXT("TRIAS33D.DLL")
#define FAKEMFC_MODULENAME	TEXT("FAKEMFCD.EXT")
#else // _DEBUG
//#define TRIASEXE_MODULENAME	TEXT("TRIAS32.EXE")
#define TRIAS03_MODULENAME	TEXT("TRIAS323.DLL")
#define FAKEMFC_MODULENAME	TEXT("FAKEMFC.EXT")
#endif // _DEBUG
#else // WIN32
//#define TRIASEXE_MODULENAME	TEXT("TRIAS.EXE")
#define TRIAS03_MODULENAME	TEXT("TRIAS03.DLL")
#endif // WIN32

// vorläufig, solange GEOMETR.DLL sich noch nicht selbst registriert (#HK960415)
#if defined(WIN32)
#if defined(_DEBUG)
#define GEOMETR_MODULENAME	TEXT("%sGEOMETD.DLL")
#else // _DEBUG
#define GEOMETR_MODULENAME	TEXT("%sGEOMETR.DLL")
#endif // _DEBUG
#else // WIN32
#define GEOMETR_MODULENAME	TEXT("%sGEOMETR.DLL")
#endif // WIN32

extern "C" bool WINAPI FKeyDelete (HKEY hKey, LPCSTR pszKey);

#if !defined(WIN32)
bool IsWin40 (void);
#endif

static bool RegisterAllEntries (LPCTSTR pPath, bool fFullReg);		// registriert alle Entries
#if defined(WIN32)
static bool RegisterAllExtensions (CVersionBind &rVer, LPCTSTR pPath, bool fRegister, CRegistryProgress *pDlg = NULL);	// registriert alle Erweiterungen
static bool UnRegisterAllExtensions (CVersionBind &rVer, LPCTSTR pPath, bool fRegister, CRegistryProgress *pDlg = NULL);	// registriert alle Erweiterungen
static bool RegisterUninstaller (LPCTSTR pFPath);
static int CountModules (CVersionBind &rVer, LPCTSTR);
static bool CountFiles (CVersionBind &rVer, LPCTSTR pcFPath, LPCTSTR pcExt);
static HRESULT CreateComponentCategory (LPCSTR pModule, CATID catid, WCHAR *catDescription, UINT uiRes);
static HRESULT RegisterToolBitmap (LPCSTR pModule, REFCATID catid, WCHAR *catDescription, UINT uiID);
static HRESULT RemoveComponentCategory (REFCATID catid);
#else
static bool RegisterAllExtensions (LPCTSTR pPath, bool fRegister);	// registriert alle Erweiterungen
#endif // WIN32
static bool TestCorrectPath (LPCSTR pPath);

// Initialisieren verschiedener Einträge in RegDB und WIN.INI -----------------
bool TriasRegInit (bool fForce, bool fFullReg, bool fSilent, bool fSetup)
{
// 1. vollen PfadNamen von Trias besorgen
HMODULE hMod = GetModuleHandle (NULL);	// ResString (IDS_TRIASMODULE, 20));
LPTSTR pPath = new TCHAR [_MAX_PATH];

	if (pPath == NULL) return FALSE;
	GetModuleFileName (hMod, pPath, _MAX_PATH);
	strupr (pPath);

// 2. WIN.INI setzen
LPTSTR pInBuff = new TCHAR [_MAX_PATH + 20];
ResString StbExt (IDS_REGSTBEXTENSION, 5);
ResString RisExt (IDS_REGRISEXTENSION, 5);

#if !defined(WIN32)	// ist nicht mehr üblich
	if (pInBuff) {
	ResString RegExt (IDS_REGEXTENSION, 20);

		if (!GetProfileString (RegExt, StbExt+1, g_cbNil, pInBuff, _MAX_PATH +20)) {
			wsprintf (pInBuff, TEXT("%s ^%s"), pPath, StbExt.Addr());
			WriteProfileString (RegExt, StbExt+1, pInBuff);
		}
		if (!GetProfileString (RegExt, RisExt+1, g_cbNil, pInBuff, _MAX_PATH +20)) {
			wsprintf (pInBuff, TEXT("%s ^%s"), pPath, RisExt.Addr());
			WriteProfileString (RegExt, RisExt+1, pInBuff);
		}
	}
#else
// alte Einräge aus WIN.INI entfernen
ResString RegExt (IDS_REGEXTENSION, 20);

	WriteProfileString (RegExt, StbExt+1, NULL);
	WriteProfileString (RegExt, RisExt+1, NULL);
#endif

// 3. Einträge in der RegDB initialisieren
ResString TriasClass (IDS_TRIASCLASSNAME, 20);
ResString rsOpenKey (IDS_REGOPENSUBKEY, 64);
ResString rsExeIcon (IDS_REGEXEICON, 32);
LONG dw = _MAX_PATH + 20;
bool fWrite = false;

// alte Einträge (TRiAS1.20) grundsätzlich entfernen
	if (RegQueryValue (HKEY_CLASSES_ROOT, TriasClass, pInBuff, &dw) == ERROR_SUCCESS) 
	{
	// alle Unterschlüssel entfernen
		FKeyDelete (HKEY_CLASSES_ROOT, TriasClass);
		fWrite = true;		// alles andere neu schreiben
	}

	if (!fForce && !fWrite) {	// Pfad prüfen, um ggf. zu korrigieren
	// oder generieren, wenn der Pfad sich geändert hat
		fWrite = TestCorrectPath (pPath);
	}

	if (fForce || fWrite) {
	LPTSTR pDrive = new TCHAR [_MAX_DRIVE];
	LPTSTR pNewPath = new TCHAR [_MAX_PATH];
	LPTSTR pFPath = new TCHAR [_MAX_FNAME];

		_splitpath (pPath, pDrive, pNewPath, NULL, NULL);
		_makepath (pFPath, pDrive, pNewPath, g_cbNil, g_cbNil);

		DELETE (pDrive);
		DELETE (pNewPath);

#if defined(WIN32)
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
			DELETE (pInBuff);
			DELETE (pPath);
			DELETE(pDlg);
			return true;		// beim profiling niemals weiter registrieren
#endif // _PROPFILE

		// CATID's registrieren
			{
			ResString resCATExtension (IDS_CATID_EXTENSION, 128);
			ResString resCATImport (IDS_CATID_IMPORTFILTER, 128);
			ResString resCATGeoCom (IDS_CATID_GEOCOMPONENT, 128);
			ResString resCATSelfRegister (IDS_CATID_SELFREGISTER, 128);

				USES_CONVERSION;
				TX_VERIFY(S_OK == CreateComponentCategory (pPath, CATID_TRiASExtension, A2OLE(resCATExtension), IDB_CATID_PLUGIN));
				TX_VERIFY(S_OK == CreateComponentCategory (pPath, CATID_TRiASImportModule, A2OLE(resCATImport), IDB_CATID_TOOLBITMAP));
				TX_VERIFY(S_OK == CreateComponentCategory (pPath, CATID_TRiASGeoComponent, A2OLE(resCATGeoCom), IDB_CATID_TOOLBITMAP));
				TX_VERIFY(S_OK == CreateComponentCategory (pPath, CATID_TRiASSelfRegister, A2OLE(resCATSelfRegister), IDB_CATID_SELFREGISTER));
			}

		// Erweiterungen registrieren 
			RegisterAllExtensions (Ver, pFPath, true, pDlg);	// registrieren

			RegisterUninstaller(pFPath);
			if (NULL != pDlg) pDlg -> IncPos();
			DELETE(pDlg);
		}
#else
		RegisterAllEntries (pFPath, fFullReg);
		RegisterAllExtensions (pFPath, true);	// registrieren
#endif // WIN32
		DELETE (pFPath);
	}

// Speicher freigeben
	DELETE (pInBuff);
	DELETE (pPath);

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
#if defined(WIN32)
typedef struct tagTRiASREGSERVER {
	HKEY m_hKeyRoot;	// bezogen worauf
	const char *m_pKey;		// Schlüssel 
	const char *m_pSubKey;	// SubSchlüssel
	const char *m_pValue;		// zugehöriger Wert
	const char *m_pValueName;	// m_pSubKey und m_pValue sind NULL
	const char *m_pSubValue;	// dann ist das hier ein Wert für RegCreateKeyEx
	DWORD m_dwSubValue;	// entweder als SZ oder als DWORD
	bool m_fFullReg;	// nur bei FullRegister eintragen
} TRiASREGSERVER;
#else
typedef struct tagTRiASREGSERVER {
	char *m_pKey;		// Schlüssel 
	char *m_pSubKey;	// SubSchlüssel
	char *m_pValue;		// zugehöriger Wert
} TRiASREGSERVER;
#endif

#if defined(WIN32)
static TRiASREGSERVER s_regEntries[] = {
// Dateierweiterungen
	{ HKEY_CLASSES_ROOT, TEXT(".stb"), g_cbNil, g_cbDocKey, NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT(".ris"), g_cbNil, g_cbDocKey, NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT(".ris\\TRiAS.Document.2\\ShellNew"), NULL, NULL, TEXT("Command"), TEXT("%s") TRIAS_MODULENAME TEXT(" /Init:NoShortcut \"%%2\""), 0, false, },

// TRiAS.Document.2
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document"), g_cbNil, TEXT("TRiAS Projekt"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document\\CurVer"), g_cbNil, g_cbDocKey, NULL, NULL, 0, false, },

	{ HKEY_CLASSES_ROOT, g_cbDocKey, g_cbNil, TEXT("TRiAS 2.0 Projekt"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document.2\\CLSID"), g_cbNil, TEXT("{937EEB40-2234-101B-AAE1-E7E7E7E7E7E7}"), NULL, NULL, 0, false, },	// #HK960124
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document.2\\DefaultIcon"), g_cbNil, TEXT("%s") TRIAS_MODULENAME TEXT(",5"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document.2\\shell\\open"), g_cbNil, TEXT("&Projekt öffnen"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document.2\\shell\\open\\command"), g_cbNil, TEXT("%s") TRIAS_MODULENAME TEXT(" \"%%1\""), NULL, NULL, 0, false, },

	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.UndoRedoObject"), g_cbNil, TEXT("TRiAS Undo/Redo Verwaltung"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.UndoRedoObject\\CLSID"), g_cbNil, TEXT("{B16261A1-856C-11CE-8CC3-444553540000}"), NULL, NULL, 0, false, },

// CLSID's
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), g_cbNil, TEXT("TRiAS Datentransfer-Objekt"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}\\ProgID"), g_cbNil, TEXT("TRiAS.DataTransferObject"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}\\InprocServer32"), g_cbNil, TEXT("%s") TRIAS03_MODULENAME, NULL, NULL, 0, false, },

	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{B16261A1-856C-11CE-8CC3-444553540000}"), g_cbNil, TEXT("TRiAS Undo/Redo Verwaltung"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{B16261A1-856C-11CE-8CC3-444553540000}\\ProgID"), g_cbNil, TEXT("TRiAS.UndoRedoObject"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{B16261A1-856C-11CE-8CC3-444553540000}\\InprocServer32"), g_cbNil, TEXT("%s") TRIAS03_MODULENAME, NULL, NULL, 0, false, },

// FullRegs
	{ HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, g_cbSysAdmin, NULL, 1, true, },
	{ HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, g_cbShowSysFeatures, NULL, 1, true, },
#if defined(_DEBUG)
	{ HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, TEXT("GlobalLicense"), NULL, 1, true, },
	{ HKEY_CURRENT_USER, g_cbRegConfig, NULL, NULL, TEXT("KonsistenzTest"), NULL, KTDNothing /*(KTDRepair|KTDQueryCorrection|KTDProtocol)*/, true, },
#endif // _DEBUG

// DataTransferObject
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.DataTransferObject"), g_cbNil, TEXT("TRiAS Datentransfer-Objekt"), NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.DataTransferObject\\CLSID"), g_cbNil, TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), NULL, NULL, 0, false, },

// vorläufig, solange GEOMETR.DLL sich noch nicht selbst registriert (#HK960415)
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.ObjektGeometrie.1"), g_cbNil, TEXT("ObjektGeometrie"), NULL, NULL, 0, false,  },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.ObjektGeometrie.1\\CLSID"), g_cbNil, TEXT("{07963832-3123-101C-BB62-00AA0018497C}"), NULL, NULL, 0, false, },

	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{07963832-3123-101C-BB62-00AA0018497C}"), g_cbNil, TEXT("ObjektGeometrie"), NULL, NULL, 0, false,  },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{07963832-3123-101C-BB62-00AA0018497C}\\InprocServer32"), g_cbNil, GEOMETR_MODULENAME, NULL, NULL, 0, false, },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID\\{07963832-3123-101C-BB62-00AA0018497C}\\ProgID"), g_cbNil, TEXT("TRiAS.ObjektGeometrie.1"), NULL, NULL, 0, false, },

// EndeKennung
	{ 0, NULL, NULL, NULL, NULL, NULL, 0, false, },

#define s_regEntries40	s_regEntries
};
#else // WIN32
static TRiASREGSERVER s_regEntries[] = {
// Dateierweiterungen
	{ TEXT(".stb"), TEXT(""), TEXT("TRiAS.Document.1"), },
	{ TEXT(".ris"), TEXT(""), TEXT("TRiAS.Document.1"), },

// TRiAS.Application
	{ TEXT("TRiAS.Document"), TEXT(""), TEXT("TRiAS Projekt"), },
	{ TEXT("TRiAS.Document\\CurVer"), TEXT(""), TEXT("TRiAS.Document.1"), },

// TRiAS.Application.1
	{ TEXT("TRiAS.Document.1"), TEXT(""), TEXT("TRiAS 1.20 Projekt"), },
	{ TEXT("TRiAS.Document.1\\DefaultIcon"), TEXT(""), TEXT("%sTRIAS.EXE,1"), },
	{ TEXT("TRiAS.Document.1\\shell\\open\\command"), TEXT(""), TEXT("%sTRIAS.EXE \"%%1\""), },

// CLSID's
	{ TEXT("CLSID") TEXT("\\") TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), TEXT(""), TEXT("TRiAS Datentransfer-Objekt"), },
	{ TEXT("CLSID") TEXT("\\") TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}") TEXT("\\InprocServer"), TEXT(""), TEXT("%s") TRIAS03_MODULENAME, },
	{ TEXT("CLSID") TEXT("\\") TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}") TEXT("\\ProgID"), TEXT(""), TEXT("TRiAS.DataTransferObject"), },

// DataTransferObject
	{ TEXT("TRiAS.DataTransferObject"), TEXT(""), TEXT("TRiAS Datentransfer-Objekt"), },
	{ TEXT("TRiAS.DataTransferObject") TEXT("\\") TEXT("CLSID"), TEXT(""), TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), },

// vorläufig, solange GEOMETR.DLL sich noch nicht selbst registriert (#HK960415)
	{ TEXT("TRiAS.ObjektGeometrie.1"), TEXT(""), TEXT("ObjektGeometrie") },
	{ TEXT("TRiAS.ObjektGeometrie.1") TEXT("\\") TEXT("CLSID"), TEXT(""), TEXT("{07963832-3123-101C-BB62-00AA0018497C}"), },

	{ TEXT("CLSID") TEXT("\\") TEXT("{07963832-3123-101C-BB62-00AA0018497C}"), TEXT(""), TEXT("ObjektGeometrie") },
	{ TEXT("CLSID") TEXT("\\") TEXT("{07963832-3123-101C-BB62-00AA0018497C}") TEXT("\\InprocServer"), TEXT(""), GEOMETR_MODULENAME, },
	{ TEXT("CLSID") TEXT("\\") TEXT("{07963832-3123-101C-BB62-00AA0018497C}") TEXT("\\ProgID"), TEXT(""), TEXT("TRiAS.ObjektGeometrie.1"), },

// EndeKennung
	{ NULL, NULL, NULL, },
};

static TRiASREGSERVER s_regEntries40[] = {
// Dateierweiterungen
	{ TEXT(".stb"), TEXT(""), TEXT("TRiAS.Document.1"), },
	{ TEXT(".ris"), TEXT(""), TEXT("TRiAS.Document.1"), },

// TRiAS.Application
	{ TEXT("TRiAS.Document"), TEXT(""), TEXT("TRiAS Projekt"), },
	{ TEXT("TRiAS.Document"), TEXT("\\CurVer"), TEXT("TRiAS.Document.1"), },

// TRiAS.Application.1
	{ TEXT("TRiAS.Document.1"), TEXT(""), TEXT("TRiAS 1.20 Projekt"), },
	{ TEXT("TRiAS.Document.1"), TEXT("\\DefaultIcon"), TEXT("%sTRIAS.EXE,1"), },
	{ TEXT("TRiAS.Document.1"), TEXT("\\shell\\open\\command"), TEXT("%sTRIAS.EXE \"%%1\""), },

// CLSID's
	{ TEXT("CLSID"), TEXT("\\") TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), TEXT("TRiAS Datentransfer-Objekt"), },
	{ TEXT("CLSID"), TEXT("\\") TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}") TEXT("\\InprocServer"), TEXT("%s") TRIAS03_MODULENAME, },
	{ TEXT("CLSID"), TEXT("\\") TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}") TEXT("\\ProgID"), TEXT("TRiAS.DataTransferObject"), },

// DataTransferObject
	{ TEXT("TRiAS.DataTransferObject"), TEXT(""), TEXT("TRiAS Datentransfer-Objekt"), },
	{ TEXT("TRiAS.DataTransferObject"), TEXT("\\") TEXT("CLSID"), TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), },

// vorläufig, solange GEOMETR.DLL sich noch nicht selbst registriert (#HK960415)
	{ TEXT("TRiAS.ObjektGeometrie.1"), TEXT(""), TEXT("ObjektGeometrie") },
	{ TEXT("TRiAS.ObjektGeometrie.1"), TEXT("\\") TEXT("CLSID"), TEXT("{07963832-3123-101C-BB62-00AA0018497C}"), },

	{ TEXT("CLSID"), TEXT("\\") TEXT("{07963832-3123-101C-BB62-00AA0018497C}"), TEXT("ObjektGeometrie") },
	{ TEXT("CLSID"), TEXT("\\") TEXT("{07963832-3123-101C-BB62-00AA0018497C}") TEXT("\\InprocServer"), GEOMETR_MODULENAME, },
	{ TEXT("CLSID"), TEXT("\\") TEXT("{07963832-3123-101C-BB62-00AA0018497C}") TEXT("\\ProgID"), TEXT("TRiAS.ObjektGeometrie.1"), },

// EndeKennung
	{ NULL, NULL, NULL, },
};
#endif


// Alle Registrierungen entfernen ---------------------------------------------
typedef struct TRiASUNREGSERVER {
	HKEY m_hKey;
	const char *m_pKey;
} TRiASUNREGSERVER;

static TRiASUNREGSERVER s_unregEntries[] = {
	{ HKEY_CLASSES_ROOT, TEXT(".stb"), },			// Dateierweiterungen
	{ HKEY_CLASSES_ROOT, TEXT(".ris"), },
	{ HKEY_CLASSES_ROOT, TEXT("Trias1.20"), },				// altes TRiAS
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Application"), },		// TRiAS.Application
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document"), },			// TRiAS.Document
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.DataTransferObject"), },// DataTransferObject
	{ HKEY_CLASSES_ROOT, TEXT("CLSID") TEXT("\\") TEXT("{CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}"), },
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.ObjektGeometrie.1"), },
	{ HKEY_CLASSES_ROOT, TEXT("CLSID") TEXT("\\") TEXT("{07963832-3123-101C-BB62-00AA0018497C}"), },
#if defined(WIN32)
	{ HKEY_CLASSES_ROOT, g_cbDocKey, },						// TRiAS.Document
	{ HKEY_CLASSES_ROOT, g_cbAppKey, },						// TRiAS.Application.2
	{ HKEY_CURRENT_USER, TEXT("Software\\uve\\TRiAS"), },
	{ HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\uve\\TRiAS"), },
#else
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Document.1"), },		// TRiAS.Document
	{ HKEY_CLASSES_ROOT, TEXT("TRiAS.Application.1"), },	// TRiAS.Application.1
#endif
	{ NULL, NULL, },			// EndeKennung
};

#if defined(WIN32)
bool TriasRegUnInit (bool fSilent, bool fFullUninstall)
#else
bool TriasRegUnInit (bool fSilent)
#endif // WIN32
{
// alte Einräge aus WIN.INI entfernen
ResString StbExt (IDS_REGSTBEXTENSION, 5);
ResString RisExt (IDS_REGRISEXTENSION, 5);
ResString RegExt (IDS_REGEXTENSION, 20);

	WriteProfileString (RegExt, StbExt+1, NULL);
	WriteProfileString (RegExt, RisExt+1, NULL);

// vollen PfadNamen von Trias besorgen
HMODULE hMod = GetModuleHandle (NULL);
LPTSTR pPath = new char [_MAX_PATH];

	if (pPath == NULL) return FALSE;
	GetModuleFileName (hMod, pPath, _MAX_PATH);
	strupr (pPath);

// Erweiterungen unregistrieren
LPTSTR pDrive = new TCHAR [_MAX_DRIVE];
LPTSTR pNewPath = new TCHAR [_MAX_PATH];
LPTSTR pFPath = new TCHAR [_MAX_FNAME];

	_splitpath (pPath, pDrive, pNewPath, NULL, NULL);
	_makepath (pFPath, pDrive, pNewPath, g_cbNil, g_cbNil);

	DELETE (pDrive);
	DELETE (pNewPath);

#if defined(WIN32)
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

	RemoveComponentCategory (CATID_TRiASExtension);
	RemoveComponentCategory (CATID_TRiASImportModule);
	RemoveComponentCategory (CATID_TRiASGeoComponent);
	RemoveComponentCategory (CATID_TRiASSelfRegister);
#else
	UnRegisterAllExtensions (pFPath, false);	// alles aufräumen
#endif // WIN32

	DELETE (pFPath);
	DELETE (pPath);

// Registry säubern
int i = 0;

	while (s_unregEntries[i].m_hKey) {
#if defined(WIN32) && defined(ENABLE_WIN32S_CODE)
		if (!IsWin32s() || s_unregEntries[i].m_hKey == HKEY_CLASSES_ROOT)
#endif // WIN32 && ENABLE_WIN32S_CODE
			FKeyDelete (s_unregEntries[i].m_hKey, s_unregEntries[i].m_pKey);
		i++;
	}

bool fResult = true;

#if defined(WIN32)
// wenn TRiAS das letzte registrierte Programm der uve war, dann auch noch
// den Schlüssel entfernen. 
// Bei existierenden SubKey's macht die Funktion garnichts.
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
		RegDeleteKey (HKEY_CURRENT_USER, TEXT("Software\\uve"));
		RegDeleteKey (HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\uve"));
	}

// vollständiges DeInstallieren muß uninst rufen
	try {
		if (fFullUninstall) {
		CLocalMachine regUnInst (g_cbUninstall);
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

	DELETE(pDlg);
#endif // WIN32

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


// Alle Einträge aus TRiASREGISTRY registrieren -------------------------------
static bool RegisterAllEntries (LPCTSTR pFPath, bool fFullReg)
{
// alle vorgegebenen Schlüssel aus der Struktur registrieren
char cbBuffer[_MAX_PATH];
TRiASREGSERVER *pTRS = IsWin40() ? s_regEntries40 : s_regEntries;

	for (/**/; pTRS -> m_pKey; pTRS++) {
		if (NULL != pTRS -> m_pSubKey) {
			wsprintf (cbBuffer, pTRS -> m_pValue, pFPath);

		CClassesRoot regEntry (pTRS -> m_pKey, true);

			TX_ASSERT(regEntry.isValid());
			if (regEntry.isValid())
				TX_VERIFY(regEntry.SetSZ (pTRS -> m_pSubKey, cbBuffer));
		} 
#if defined(WIN32)
		else {
#if defined(ENABLE_WIN32S_CODE)
			if (IsWin32s()) continue;
#endif // ENABLE_WIN32S_CODE

			if (!pTRS -> m_fFullReg || fFullReg) {
			CRegistry regEntry (pTRS -> m_hKeyRoot, pTRS -> m_pKey, true);

				TX_ASSERT(regEntry.isValid());
				if (!regEntry.isValid()) continue;
				if (NULL != pTRS -> m_pSubValue) {	// als SZ eintragen
					wsprintf (cbBuffer, pTRS -> m_pSubValue, pFPath);
					TX_VERIFY(regEntry.SetSubSZ (pTRS -> m_pValueName, cbBuffer));
				} else		// oder als DWORD
					TX_VERIFY(regEntry.SetDWORD (pTRS -> m_pValueName, pTRS -> m_dwSubValue));
			}
		}
#endif
	}

return true;
}

// Registrieren aller Erweiterungen im aktuellen Verzeichnis ------------------
#if !defined(WIN32)
#include <dos.h>
#endif // WIN32

#if defined(WIN32)

static bool RegisterFiles (CVersionBind &rVer, LPCTSTR pcFPath, 
	LPCTSTR pcExt, bool fRegister, CRegistryProgress *pDlg, 
	LPCSTR pcSkipName = NULL)
{
HANDLE hFile;
string strFile (pcFPath);
WIN32_FIND_DATA c_file;

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

	CExtReg Ext (rVer, strFile);

		if (!Ext.SupportsSelfRegister()) continue;

		if (NULL != pDlg) pDlg -> SetText (strFile.c_str());

		if (fRegister) Ext.Register();
		else	       Ext.Unregister();

		if (NULL != pDlg) pDlg -> IncPos();

	} while (FindNextFile (hFile, &c_file));

	FindClose (hFile);

return true;
}

static bool RegisterUninstaller (LPCTSTR pFPath)
{
// Uninstallbezeichner korrigieren
CLocalMachine regUnInst (g_cbUninstall, true);
ResString resVersion (IDS_SIGNONVERSION, 128);

	if (!regUnInst.SetSubSZ (g_cbDisplayName, resVersion))
		return false;

// exitierende UninstallInfo lesen und unter modifiziertem Namen neu ablegen
char cbBuffer[2*_MAX_PATH];
DWORD dwLen = sizeof(cbBuffer);

	if (!regUnInst.GetSubSZ (g_cbUninstallString, cbBuffer, dwLen))
		return false;

	if (NULL == strstr (cbBuffer, g_cbUnregFull)) {
	// nur schreiben, wenn neuer UnInst-string einer zwischenzeitlichen
	// Installation
		if (!regUnInst.SetSubSZ (g_cbOrigUninstallString, cbBuffer))
			return false;
	}

	strcpy (cbBuffer, pFPath);
	strcat (cbBuffer, TRIAS_MODULENAME);
	strcat (cbBuffer, g_cbUnregFull);
	if (!regUnInst.SetSubSZ (g_cbUninstallString, cbBuffer))
		return false;

return true;
}

static bool RegisterAllExtensions (CVersionBind &rVer, LPCTSTR pFPath, 
	bool fRegister, CRegistryProgress *pDlg)
{
HINSTANCE hFakeMfc = ::LoadLibrary (FAKEMFC_MODULENAME);	// muß immer geladen sein

	if (NULL != pDlg) pDlg -> IncPos();
	RegisterFiles (rVer, pFPath, TRIAS03_MODULENAME, fRegister, pDlg);	// RegisterHelper registrieren
	RegisterFiles (rVer, pFPath, TEXT("*.dll"), fRegister, pDlg, TRIAS03_MODULENAME);	// Dll's registrieren
	RegisterFiles (rVer, pFPath, TEXT("*.ext"), fRegister, pDlg);	// Erweiterungen registrieren
	RegisterFiles (rVer, pFPath, TEXT("*.ctf"), fRegister, pDlg);	// KoordinatenTransformationen registrieren
	RegisterFiles (rVer, pFPath, TEXT("*.vmd"), fRegister, pDlg);	// Visualisierungsmodule registrieren

	if (NULL != hFakeMfc) 
		::FreeLibrary (hFakeMfc);

	return true;
}

static bool UnRegisterAllExtensions (CVersionBind &rVer, LPCTSTR pFPath, 
	bool fRegister, CRegistryProgress *pDlg)
{
HINSTANCE hFakeMfc = ::LoadLibrary (FAKEMFC_MODULENAME);	// muß immer geladen sein

	if (NULL != pDlg) pDlg -> IncPos();
	RegisterFiles (rVer, pFPath, TEXT("*.ext"), fRegister, pDlg);	// Erweiterungen registrieren
	RegisterFiles (rVer, pFPath, TEXT("*.ctf"), fRegister, pDlg);	// KoordinatenTransformationen registrieren
	RegisterFiles (rVer, pFPath, TEXT("*.vmd"), fRegister, pDlg);	// Visualisierungsmodule registrieren
	RegisterFiles (rVer, pFPath, TEXT("*.dll"), fRegister, pDlg, TRIAS03_MODULENAME);	// Dll's registrieren
	RegisterFiles (rVer, pFPath, TRIAS03_MODULENAME, fRegister, pDlg);	// RegisterHelper als letzten registrieren

	if (NULL != hFakeMfc) 
		::FreeLibrary (hFakeMfc);

	return true;
}

// Zählen der zu behandelnden Module
static bool CountModules (CVersionBind &rVer, LPCTSTR pFPath)
{
int iCnt = 0;		// TRiAS03

	iCnt += CountFiles (rVer, pFPath, TEXT("*.dll"));
	iCnt += CountFiles (rVer, pFPath, TEXT("*.ext"));
	iCnt += CountFiles (rVer, pFPath, TEXT("*.ctf"));
	iCnt += CountFiles (rVer, pFPath, TEXT("*.vmd"));

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

#else // WIN32

static bool RegisterAllExtensions (LPCTSTR pFPath, bool fRegister)
{
// Alle Erweiterungen im eigenen Verzeichnis finden und registreren
struct _find_t c_file;
string strFile (pFPath);

	strFile += TEXT("*.ext");
	if (_dos_findfirst (strFile.c_str(), _A_NORMAL, &c_file) != 0)
		return true;	// nichts gefunden

	do {
		strFile = string(pFPath) + c_file.name;
	
	CExtReg Ext (strFile);

		if (fRegister) Ext.Register();
		else	       Ext.Unregister();
	} while (_dos_findnext (&c_file) == 0);

return true;
}

#endif // WIN32

// Testen, ob der aktuelle Pfad dem in der Registry entspricht ----------------
static bool TestCorrectPath (LPCSTR pPath)
{
	if (!IsWin40()) {
	CClassesRoot regCurVer (TEXT("TRiAS.Document\\CurVer"));
	string strIn (_MAX_PATH, default_size);
	LONG dw = _MAX_PATH + 20;
	
		if (!regCurVer.GetSZ (g_cbNil, (LPSTR)strIn.c_str(), dw)) 
			return true;
		strIn.adjustlen();
	
	// aktive Programmversion abfragen
#if defined(WIN32)
		if (strIn != g_cbDocKey) return true;
#else
		if (strIn != TEXT("TRiAS.Document.1")) return true;
#endif
		
	// aktuellen Pfad abfragen
		strIn += TEXT("\\shell\\open\\command");
	
	CClassesRoot regShell (strIn.c_str());
	string strPath (_MAX_PATH, default_size);
	
		dw = _MAX_PATH+20;
		if (!regShell.GetSZ (g_cbNil, (LPSTR)strPath.c_str(), dw))
			return true;
	
		strPath.adjustlen();
		if (_strnicmp (pPath, strPath.c_str(), strlen(pPath))) 
			return true;
	} else {
	CClassesRoot regCurVer (TEXT("TRiAS.Document"));
	string strIn (_MAX_PATH, default_size);
	LONG dw = _MAX_PATH + 20;
	
		if (!regCurVer.GetSZ (TEXT("CurVer"), (LPSTR)strIn.c_str(), dw)) 
			return true;
		strIn.adjustlen();
	
	// aktive Programmversion abfragen
#if defined(WIN32)
		if (strIn != g_cbDocKey) return true;
#else
		if (strIn != TEXT("TRiAS.Document.1")) return true;
#endif
	// aktuellen Pfad abfragen
		strIn += TEXT("\\shell\\open");
	
	CClassesRoot regShell (strIn.c_str());
	string strPath (_MAX_PATH, default_size);
	
		dw = _MAX_PATH+20;
		if (!regShell.GetSZ (TEXT("command"), (LPSTR)strPath.c_str(), dw))
			return true;
	
		strPath.adjustlen();
		if (_strnicmp (pPath, strPath.c_str(), strlen(pPath))) 
			return true;

#if defined(WIN32)
	// konkrete Version abstimmen
	CLocalMachine regUnInst (g_cbUninstall);
	string strVersion (_MAX_PATH, default_size);

		dw = _MAX_PATH;
		if (!regUnInst.GetSubSZ (g_cbDisplayName, (LPSTR)strVersion.c_str(), (DWORD &)dw))
			return true;

	ResString resVersion  (IDS_SIGNONVERSION, 128);

		strVersion.adjustlen();
		if (strVersion != resVersion.Addr())
			return true;
#endif // WIN32
	}
	
return false;	// alles stimmt, nicht neu schreiben
}

#if defined(WIN32)

static HRESULT CreateComponentCategory (
	LPCSTR pModule, CATID catid, WCHAR *catDescription, UINT uiRes)
{
ICatRegister *pcr = NULL;
HRESULT hr = S_OK;

	hr = CoCreateInstance (CLSID_StdComponentCategoriesMgr, 
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
 
static HRESULT RemoveComponentCategory (REFCATID catid)
{
ICatRegister *pcr = NULL;
HRESULT hr = S_OK;

	hr = CoCreateInstance (CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID *)&pcr);
	if (FAILED(hr))	return hr;

    hr = pcr -> UnRegisterCategories (1, (CATID *)&catid);
	pcr -> Release();

return hr;
}
 
#endif // WIN32
