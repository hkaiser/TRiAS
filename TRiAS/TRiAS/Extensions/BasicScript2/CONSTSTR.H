// Stringkonstanten für BScriptExt
// File: Conststr.h

#if !defined(_CONSTSTR_H)
#define _CONSTSTR_H

// globale Konstanten
#define MAGIC_FULLINSTALL	23041959L	// MagicNumber für fullinstall

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup geladen)
extern char g_cbTRiAS[];

// globale Strings
extern const TCHAR g_cbKeyboardFilterData[];	// TEXT("KeyboardFilterData");
extern const TCHAR g_cbIntegerLabel[];			// TEXT("'%i\n");


extern const TCHAR g_cbBeginBeforFiles[];		// TEXT("\n'{{BEGINFILE(%s,%i,%i)\n\n");
extern const TCHAR g_cbSplitBetweeFiles[];		// TEXT("\n'{{NEXTFILE(%s)\n\n");
extern const TCHAR g_cbSplit[];					// TEXT("'{{NEXTFILE(");
extern const TCHAR g_cbBegin[];					// TEXT("'{{BEGINFILE(");

extern const TCHAR g_cbOpenMRU[];		// TEXT("OpenMRU");
extern const TCHAR g_cbOpenMRUKey[];	// TEXT("Software\\TRiAS\\InterTRiAS\\Extensions\\TRiAS.MacroScript.1\\OpenMRU");
extern const TCHAR g_cbCfgKey[];		// TEXT("Software\\TRiAS\\InterTRiAS\\Extensions\\TRiAS.MacroScript.1\\Config");
extern const TCHAR g_cbConfig[];		// TEXT("Config");
extern const TCHAR g_cbFileProgID[];	// TEXT("FileProgID");
extern const TCHAR g_cbParameters[];		// TEXT("Parameters");
extern const TCHAR g_cbNumExtensions32[];	// TEXT("NumExtensions32");
extern const TCHAR g_cbExtensions32[];		// TEXT("Extensions32");
extern const TCHAR g_cbINI[];				// TEXT("ini");
extern const TCHAR g_cbIntro[];			// TEXT("Intro");

extern const TCHAR g_cbPropActKey[];	// TEXT("TRiAS.Application.2\\TRiASEx\\PropertyActions);
extern const TCHAR g_cbPropActKeyFmt[]; // TEXT("TRiAS.Application.2\\TRiASEx\\PropertyActions\\%s");
extern const TCHAR g_cbDirKey[];			// TEXT("Software\\TRiAS\\InterTRiAS\\Directories");
extern const TCHAR g_cbDirKeyOnly[];	// TEXT("Directories");
extern const TCHAR g_cbTRiASKey[];			// TEXT("Software\\TRiAS\\InterTRiAS");

extern const TCHAR g_cbLocalINI[];		// TEXT("bscript.ini");
extern const TCHAR g_cbEditor[];		// TEXT("Editor");
extern const TCHAR g_cbFont[];			// TEXT("Font");
extern const TCHAR g_cbWindow[];		// TEXT("Window");
extern const TCHAR g_cbDebuggerWindow[];// TEXT("DebuggerWindow");
extern const TCHAR g_cbTreeWindow[];	// TEXT("TreeWindow");
extern const TCHAR g_cbLastFile[];		// TEXT("LastFile");
extern const TCHAR g_cbBSVersion[];		// TEXT("Version");
extern const TCHAR g_cbFullInstall[];	// TEXT("FullInstall");


extern const TCHAR g_cbBasicScriptLayout[];// TEXT("BasicScriptLayout\\Layout");
//extern const TCHAR g_cbWindow[];		// TEXT("Window");

extern const TCHAR g_cbToolbarFmt[];	// TEXT("%d,%d,%d,%d,%d");
extern const TCHAR g_cbDel[];			// TEXT("\\");
extern const TCHAR g_cbNil[];			// TEXT("");
extern const wchar_t g_wcbNil[];		// L"";

extern const TCHAR g_cbFmtDel[];		// TEXT(",:;");
extern const TCHAR g_cbWindowFmt[];		// TEXT("%d,%d,%d,%d");
extern const TCHAR g_cbFontFmt[];		// TEXT("%d,%d,%d,%d,%s");
extern const TCHAR g_cbDezFmt[];		// TEXT("%d");
extern const TCHAR g_cbStringFmt[];		// TEXT("%s");

extern const TCHAR g_cbAZHelp[];		// TEXT("AZ.HLP");
extern const TCHAR g_cbDDHelp[];		// TEXT("DD.HLP");
extern const TCHAR g_cbMPHelp[];		// TEXT("TRIASMP.HLP");

extern const TCHAR g_cbBasicScript[];			// TEXT("BasicScript");
extern const TCHAR g_cbAutoStart[];				// TEXT("AutoStart");
extern const TCHAR g_cbAutoStartPath[];			// TEXT("AutoStartPath");
extern const TCHAR g_cbMacroDir[];				// TEXT("Macro");
extern const TCHAR g_cbAutoLoadFile[];			// TEXT("AutoStartFile");
// TRiAS-Messages

extern const TCHAR g_cbFileExt_Ini[];	// TEXT("ini");

/////////////////////////////////////////////////////////////////////////////
// Feststehende PropertyBag-Keys für PropertyActions
extern const TCHAR g_cbPattern[];			// TEXT(";%1=%2");

extern const OLECHAR g_cbPAPrefix[];		// L";PropActData";		// Prefix für PropActDaten
extern const OLECHAR g_cbPAName[];			// L"Name";				// Name der propertyAction
extern const OLECHAR g_cbPANoShow[];		// L"NoShow";			// Dialog _nicht_ anzeigen
extern const OLECHAR g_cbPAScriptName[];	// L"ScriptName";		// Name des auszuführenden Scriptes
extern const OLECHAR g_cbPADataSource[];	// L"DataSource";		// ContextDataSource

extern const TCHAR g_cbTRiASVer[];			// TEXT("TRiAS_VER");
extern const TCHAR g_cbTRiASBuild[];		// TEXT("TRiAS_BUILD");

///////////////////////////////////////////////////////////////////////////////
// aktueller TRiAS-Name
extern const char g_cbTRiASName[];			// TEXT("TRiASName");
extern const char g_cbRegConfig[];			// TEXT("Software\\TRiAS\\InterTRiAS\\Config");
extern const char g_cbCopyrightName[];		// TEXT("TRiAS");

#endif // _CONSTSTR_H
