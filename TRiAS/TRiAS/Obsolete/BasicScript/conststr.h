// Stringkonstanten für BScriptExt
// File: Conststr.h

#if !defined(_CONSTSTR_H)
#define _CONSTSTR_H

extern const TCHAR g_cbKeyboardFilterData[];	// TEXT("KeyboardFilterData");

extern const TCHAR g_cbOpenMRU[];		// TEXT("OpenMRU");
extern const TCHAR g_cbOpenMRUKey[];	// TEXT("Software\\uve\\TRiAS\\Extensions\\TRiAS.MacroScript.1\\OpenMRU");
extern const TCHAR g_cbCfgKey[];		// TEXT("Software\\uve\\TRiAS\\Extensions\\TRiAS.MacroScript.1\\Config");

extern const TCHAR g_cbPropActKey[];	// TEXT("TRiAS.Application.2\\TRiASEx\\PropertyActions);
extern const TCHAR g_cbPropActKeyFmt[]; // TEXT("TRiAS.Application.2\\TRiASEx\\PropertyActions\\%s");
extern const TCHAR g_cbDirKey[];			// TEXT("Software\\uve\\TRiAS\\Directories");
extern const TCHAR g_cbDirKeyOnly[];	// TEXT("Directories");
extern const TCHAR g_cbTRiASKey[];			// TEXT("Software\\uve\\TRiAS");

extern const TCHAR g_cbLocalINI[];		// TEXT("bscript.ini");
extern const TCHAR g_cbEditor[];		// TEXT("Editor");
extern const TCHAR g_cbFont[];			// TEXT("Font");
extern const TCHAR g_cbWindow[];		// TEXT("Window");
extern const TCHAR g_cbLastFile[];		// TEXT("LastFile");

extern const TCHAR g_cbDel[];			// TEXT("\\");
extern const TCHAR g_cbNil[];			// TEXT("");
extern const TCHAR g_cbFmtDel[];		// TEXT(",:;");
extern const TCHAR g_cbWindowFmt[];		// TEXT("%d,%d,%d,%d");
extern const TCHAR g_cbFontFmt[];		// TEXT("%d,%d,%d,%d,%s");
extern const TCHAR g_cbDezFmt[];		// TEXT("%d");
extern const TCHAR g_cbStringFmt[];		// TEXT("%s");

extern const TCHAR g_cbAZHelp[];		// TEXT("AZ.HLP");
extern const TCHAR g_cbDDHelp[];		// TEXT("DD.HLP");
extern const TCHAR g_cbMPHelp[];		// TEXT("TRIASMP.HLP");

// BSCRIPT.EXT-Einträge in die Projekt.ini
extern const TCHAR g_cbBasicScript[];			// TEXT("BasicScript");
extern const TCHAR g_cbAutoStart[];				// TEXT("AutoStart");
extern const TCHAR g_cbAutoStartPath[];			// TEXT("AutoStartPath");
extern const TCHAR g_cbMacroDir[];				// TEXT("Macro");

// TRiAS-Messages
extern const TCHAR g_cbProjectOpen[];	// TEXT("DocumentOpened");
extern const TCHAR g_cbProjectClosed[];	// TEXT("DocumenClosed");
extern const TCHAR g_cbProjectClosing[];// TEXT("ClosingDocument");

extern const TCHAR g_cbFileExt_Ini[];	// TEXT("ini");

#endif // _CONSTSTR_H
