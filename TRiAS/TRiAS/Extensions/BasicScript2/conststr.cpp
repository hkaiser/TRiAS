// Stringkonstanten für BScriptExt
// File: Conststr.cpp

#include "bscriptp.hxx"
#include "conststr.h"

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
char g_cbTRiAS[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// Stringkonstanten
const TCHAR g_cbSplitBetweeFiles[] = TEXT("\n'{{NEXTFILE(%s)\n\n");
const TCHAR g_cbBeginBeforFiles[] = TEXT("\n'{{BEGINFILE(%s,%i,%i)\n\n");
const TCHAR g_cbBegin[] = TEXT("\n'{{BEGINFILE");

const TCHAR g_cbSplit[] = TEXT("'{{NEXTFILE(");

const TCHAR g_cbKeyboardFilterData[] = TEXT("KeyboardFilterData");

const TCHAR g_cbOpenMRU[] = TEXT("OpenMRU");
const TCHAR g_cbOpenMRUKey[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.MacroScript.1\\OpenMRU");
const TCHAR g_cbCfgKey[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.MacroScript.1\\Config");
const TCHAR g_cbConfig[] = TEXT("Config");
const TCHAR g_cbDirKey[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Directories");
const TCHAR g_cbDirKeyOnly[] = TEXT("Directories");
const TCHAR g_cbTRiASKey[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY);
const TCHAR g_cbFileProgID[] = TEXT("FileProgID");
const TCHAR g_cbExtensions32[] = TEXT("Extensions32");
const TCHAR g_cbParameters[] = TEXT("Parameters");
const TCHAR g_cbNumExtensions32[] = TEXT("NumExtensions32");
const TCHAR g_cbINI[] = TEXT("ini");
const TCHAR g_cbIntro[] = TEXT("Intro");

const TCHAR g_cbPropActKey[] = TEXT("TRiAS.Application.4\\TRiASEx\\PropertyActions");
const TCHAR g_cbPropActKeyFmt[] = TEXT("TRiAS.Application.4\\TRiASEx\\PropertyActions\\%s");

const TCHAR g_cbLocalINI[] = TEXT("bscript.ini");
const TCHAR g_cbEditor[] = TEXT("Editor");
const TCHAR g_cbFont[] = TEXT("Font");
const TCHAR g_cbWindow[] = TEXT("Window");
const TCHAR g_cbDebuggerWindow[] = TEXT("DebuggerWindow");
const TCHAR g_cbTreeWindow[] = TEXT("TreeWindow");
const TCHAR g_cbLastFile[] = TEXT("LastMacroDir");
const TCHAR g_cbBSVersion[] = TEXT("Version");
const TCHAR g_cbFullInstall[] = TEXT("FullInstall");

const TCHAR g_cbBasicScriptLayout[] = TEXT("BasicScriptLayout\\Layout");

// BSCRIPT.EXT-Einträge in die Projekt.ini
const TCHAR g_cbBasicScript[] = TEXT("BasicScript");
const TCHAR g_cbAutoStart[] = TEXT("AutoStart");
const TCHAR g_cbAutoStartPath[] = TEXT("AutoStartPath");
const TCHAR g_cbMacroDir[] = TEXT("DefaultMacroDir");
const TCHAR g_cbAutoLoadFile[] = TEXT("AutoLoadFile");

// TRiAS-Messages
const TCHAR g_cbProjectOpen[] = TEXT("DocumentOpened");
const TCHAR g_cbProjectClosed[] = TEXT("DocumenClosed");
const TCHAR g_cbProjectClosing[] = TEXT("ClosingDocument");

const TCHAR g_cbFileExt_Ini[] = TEXT("ini");

const TCHAR g_cbDel[] = TEXT("\\");
const TCHAR g_cbNil[] = TEXT("");
const wchar_t g_wcbNil[] = L"";

const TCHAR g_cbFmtDel[] = TEXT(",:;");
const TCHAR g_cbWindowFmt[] = TEXT("%d,%d,%d,%d,");
const TCHAR g_cbFontFmt[] = TEXT("%d,%d,%d,%d,%s");
const TCHAR g_cbDezFmt[] = TEXT("%d");
const TCHAR g_cbStringFmt[] = TEXT("%s");
const TCHAR g_cbToolbarFmt[] = TEXT("%d,%d,%d,%d,%d");

const TCHAR g_cbAZHelp[] = TEXT("AZ.HLP");
const TCHAR g_cbDDHelp[] = TEXT("DD.HLP");
const TCHAR g_cbMPHelp[] = TEXT("OLEAUTO.HLP");

/////////////////////////////////////////////////////////////////////////////
// Feststehende PropertyBag-Keys für PropertyActions
const TCHAR g_cbPattern[] = TEXT(";%1=%2");

const OLECHAR g_cbPAPrefix[] = L";PropActData";		// Prefix für PropActDaten
const OLECHAR g_cbPAName[] = L"Name";				// Name der propertyAction
const OLECHAR g_cbPANoShow[] = L"NoShow";			// Dialog _nicht_ anzeigen
const OLECHAR g_cbPAScriptName[] = L"ScriptName";	// Name des auszuführenden Scriptes
const OLECHAR g_cbPADataSource[] = L"DataSource";	// ContextDataSource

const TCHAR g_cbTRiASVer[] = TEXT("TRiAS_VER");
const TCHAR g_cbTRiASBuild[] = TEXT("TRiAS_BUILD");

///////////////////////////////////////////////////////////////////////////////
// aktueller TRiAS-Name
const char g_cbTRiASName[] = TEXT("TRiASName");
const char g_cbRegConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");
const char g_cbCopyrightName[] = TEXT("TRiAS");

