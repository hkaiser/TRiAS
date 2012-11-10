// StringKonstanten -----------------------------------------------------------
// File: STRINGS.CXX

#include "triaspre.hxx"
#include "strings.h"

#if defined(WIN32)

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
char g_cbTRiAS[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// RegistryKeys
const char g_cbRegOpenMRU[] = TEXT("Software\\uve\\TRiAS\\OpenMRU");
const char g_cbRegConfig[] = TEXT("Software\\uve\\TRiAS\\Config");
const char g_cbRegExtensions[] = TEXT("Software\\uve\\TRiAS\\Extensions");
const char g_cbRegVersion[] = TEXT("SOFTWARE\\uve\\TRiAS\\") TEXT("2.10");
const char g_cbUninstall[] = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\TRiAS");
const char g_cbFakeMFCKey[] = TEXT("Software\\uve\\TRiAS\\Extensions\\TRiAS.FakeMFC.1\\Config");

const char g_cbClsId[] = TEXT("CLSID");
const char g_cbAppID[] = TEXT("AppID");
const char g_cbToolboxBitmap[] = TEXT("ToolboxBitmap32");
const char g_cbUnRegister[] = TEXT("UnRegister");

const char g_cbAppKey[] = TEXT("TRiAS.Application.2");
const char g_cbDocKey[] = TEXT("TRiAS.Document.2");
const char g_cbInprocServer[] = TEXT("InprocServer32");

const char g_cbUninstallString[] = TEXT("UninstallString");
const char g_cbOrigUninstallString[] = TEXT("OrigUninstallString");
const char g_cbDisplayName[] = TEXT("DisplayName");
const char g_cbSerial[] = TEXT("Serial");
const char g_cbUnregFull[] = TEXT(" /unregserver:full");

///////////////////////////////////////////////////////////////////////////////
// sonstiges
const char g_cbViewClass[] = TEXT("TRiAS_View");
const char g_cbFrameClass[] = TEXT("TRiAS_Frame");

const char g_cbDel[] = TEXT("\\");
const char g_cbNil[] = TEXT("");
const char g_cbUndoDel[] = TEXT("|");
const char g_cbColon[] = TEXT(":");
const char g_cbMinus[] = TEXT("-");
const char g_cbSpaceDashSpace[] = TEXT(" - ");
const char g_cbScalePrefix[] = TEXT("1:");

const char g_cbINI[] = TEXT(".ini");
const char g_cbCopyrightName[] = TEXT("TRiAS®");
const char g_cbCopyrightNameT[] = TEXT("InterTRiAS®");

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
const char g_cbScrollInset[] = TEXT("DragScrollInset");
const char g_cbScrollDelay[] = TEXT("DragScrollDelay");
const char g_cbWindowsSection[] = TEXT("windows");

///////////////////////////////////////////////////////////////////////////////
// Config-Flags
const char g_cbConfig[] = TEXT("Config");
const char g_cbHSBColors[] = TEXT("HSBColors");
const char g_cbLastOpenDir[] = TEXT("LastOpenDir");

const char g_cbRegCompany[] = TEXT("Company");
const char g_cbRegName[] = TEXT("Name");

const char g_cbSysAdmin[] = TEXT("SystemAdministration");
const char g_cbHideFlags[] = TEXT("HideFlags");
const char g_cbShowObjProp[] = TEXT("ShowObjProp");
const char g_cbPreLoad[] = TEXT("PreLoad");
const char g_cbPriorityLoad[] = TEXT("PriorityLoad");
const char g_cbUnLoadable[] = TEXT("UnLoadable");
const char g_cbVisible[] = TEXT("Visible");
const char g_cbCanImport[] = TEXT("CanImport");
const char g_cbAggregate[] = TEXT("Aggregate");
const char g_cbDelFeature[] = TEXT("DelimiterForFeature");
const char g_cbImportFormat[] = TEXT("ImportFormat");
const char g_cbDescription[] = TEXT("Description");
const char g_cbFileExt[] = TEXT("FileExtension");
const char g_cbHoldZoom[] = TEXT("PreserveZoom");
const char g_cbEnableDragDrop[] = TEXT("EnableDragDrop");
const char g_cbShowSysFeatures[] = TEXT("ShowSysFeatures");

const char g_cbLogoFileName[] = TEXT("LogoFileName");
const char g_cbTRiASName[] = TEXT("TRiASName");
const char g_cbTRiASMode[] = TEXT("TRiASMode");

const char g_cbHandledExtensions[] = TEXT("HandledExtensions");
const char g_cbFilter[] = TEXT("Filter");

///////////////////////////////////////////////////////////////////////////////
// Verzeichnisse
const char g_cbDirectories[] = TEXT("Software\\uve\\TRiAS\\Directories");
const char g_cbCursorDirectory[] = TEXT("Cursors");

///////////////////////////////////////////////////////////////////////////////
// Diverse animierte Cursoren
const char g_cbCursors[] = TEXT("Software\\uve\\TRiAS\\Cursors");
const char g_cbCursorLoad[] = TEXT("Load");
const char g_cbCursorSave[] = TEXT("Save");
const char g_cbCursorWait[] = TEXT("Wait");
const char g_cbCursorPrint[] = TEXT("Print");

///////////////////////////////////////////////////////////////////////////////
// IniKeys
const char g_cbIniOpenMRU[] = TEXT("OpenMRU");

///////////////////////////////////////////////////////////////////////////////
// TRiASEx - PropertySheetPages
const char g_cbDocSubKey[] = TEXT("TRiASEx\\PropertySheetHandlers");
const char g_cbSearchSubKey[] = TEXT("TRiASEx\\SearchEngines");

const char g_cbPrintLayout[] = TEXT("PrintLayout");
const char g_cbCustomize[] = TEXT("Customize");
const char g_cbCoordinates[] = TEXT("Coordinates");
const char g_cbOptions[] = TEXT("Options");

const char g_cbHexDigits[] = TEXT("\\(\\[[[:xdigit:]]+\\]\\)\\|\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]]?.*\\)");	// TEXT("0123456789abcdefABCDEF");
//const char g_cbHexDigitsSpec[] = TEXT("\\(\\[[[:xdigit:]#]+\\]\\)\\|\\(\\([[:xdigit:]#]+\\)[[:punct:][:blank:]]?.*\\)");	// TEXT("0123456789abcdefABCDEF");

///////////////////////////////////////////////////////////////////////////////
// MetaFileHeader
const char g_cbTRiASPict[] = TEXT("TRiAS\0TRiAS Picture\0");

// Overviews speichern
const char g_cbOverviews[] = TEXT("OverviewPicts");
const char g_cbDefaultPict[] = TEXT("DefaultPict");

const char g_cbId[] = TEXT("Id");
const char g_cbIdForce[] = TEXT("IdForce");

#else

///////////////////////////////////////////////////////////////////////////////
// sonstiges
const char g_cbNil[] = TEXT("");

///////////////////////////////////////////////////////////////////////////////
// Config-Flags
const char g_cbSysAdmin[] = TEXT("SystemAdministration");
const char g_cbHideFlags[] = TEXT("HideFlags");
const char g_cbShowObjProp[] = TEXT("ShowObjProp");
const char g_cbImportFormat[] = TEXT("ImportFormat");
const char g_cbDescription[] = TEXT("Description");
const char g_cbFileExt[] = TEXT("FileExtension");

#endif // WIN32
