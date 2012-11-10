// Globale StringKonstanten ---------------------------------------------------
// File: STRINGS.H

#if !defined(_STRINGS_H)
#define _STRINGS_H

#if defined(WIN32)

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
extern char g_cbTRiAS[];

///////////////////////////////////////////////////////////////////////////////
// RegistryKeys
extern const char g_cbRegOpenMRU[];		// TEXT("Software\\uve\\TRiAS\\OpenMRU");
extern const char g_cbRegConfig[];		// TEXT("Software\\uve\\TRiAS\\Config");
extern const char g_cbRegExtensions[];	// TEXT("Software\\uve\\TRiAS\\Extensions")
extern const char g_cbRegVersion[];		// TEXT("SOFTWARE\\uve\\TRiAS\\2.0");
extern const char g_cbUninstall[];		// TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\TRiAS");
extern const char g_cbFakeMFCKey[];		// TEXT("Software\\uve\\TRiAS\\Extensions\\TRiAS.FakeMFC.1\\Config");

extern const char g_cbClsId[];			// TEXT("CLSID")
extern const char g_cbAppID[];			// TEXT("AppID");
extern const char g_cbToolboxBitmap[];	// TEXT("ToolboxBitmap32");
extern const char g_cbUnRegister[];		// TEXT("UnRegister");

extern const char g_cbAppKey[];			// TEXT("TRiAS.Application.2");
extern const char g_cbDocKey[];			// TEXT("TRiAS.Document.2");
extern const char g_cbInprocServer[];	// TEXT("InprocServer32");

extern const char g_cbUninstallString[];	// TEXT("UninstallString");
extern const char g_cbOrigUninstallString[];	// TEXT("OrigUninstallString");
extern const char g_cbDisplayName[];	// TEXT("DisplayName");
extern const char g_cbSerial[];			// TEXT("Serial");
extern const char g_cbUnregFull[];		// TEXT(" /unregserver:full");

///////////////////////////////////////////////////////////////////////////////
// IniKeys
extern const char g_cbIniOpenMRU[];		// TEXT("OpenMRU");

///////////////////////////////////////////////////////////////////////////////
// sonstiges
extern const char g_cbViewClass[];		// TEXT("TRiAS_View");
extern const char g_cbFrameClass[];		// TEXT("TRiAS_Frame");

extern const char g_cbDel[];			// TEXT("\\");
extern const char g_cbNil[];			// TEXT("");
extern const char g_cbUndoDel[];		// TEXT("|");
extern const char g_cbColon[];			// TEXT(":");
extern const char g_cbMinus[];			// TEXT("-");
extern const char g_cbSpaceDashSpace[];	// TEXT(" - ");
extern const char g_cbScalePrefix[];	// TEXT("1:");

extern const char g_cbINI[];			// TEXT(".ini");
extern const char g_cbCopyrightName[];	// TEXT("TRiAS®");
extern const char g_cbCopyrightNameT[];	// TEXT("InterTRiAS®");

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
extern const char g_cbScrollInset[];	// TEXT("DragScrollInset");
extern const char g_cbScrollDelay[];	// TEXT("DragScrollDelay");
extern const char g_cbWindowsSection[];	// TEXT("windows");

///////////////////////////////////////////////////////////////////////////////
// Config-Flags
extern const char g_cbConfig[];			// TEXT("Config");
extern const char g_cbHSBColors[];		// TEXT("HSBColors");
extern const char g_cbLastOpenDir[];	// TEXT("LastOpenDir");

extern const char g_cbRegCompany[];		// TEXT("Company");
extern const char g_cbRegName[];		// TEXT("Name");

extern const char g_cbSysAdmin[];		// TEXT("SystemAdministration");
extern const char g_cbHideFlags[];		// TEXT("HideFlags");
extern const char g_cbShowObjProp[];	// TEXT("ShowObjProp");
extern const char g_cbPreLoad[];		// TEXT("PreLoad");
extern const char g_cbPriorityLoad[];	// TEXT("PriorityLoad");
extern const char g_cbUnLoadable[];		// TEXT("UnLoadable");
extern const char g_cbVisible[];		// TEXT("Visible");
extern const char g_cbCanImport[];		// TEXT("CanImport");
extern const char g_cbAggregate[];		// TEXT("Aggregate");
extern const char g_cbDelFeature[];		// TEXT("DelimiterForFeature");
extern const char g_cbImportFormat[];	// TEXT("ImportFormat");
extern const char g_cbDescription[];	// TEXT("Description");
extern const char g_cbFileExt[];		// TEXT("FileExtension");
extern const char g_cbHoldZoom[];		// TEXT("PreserveZoom");
extern const char g_cbEnableDragDrop[];	// TEXT("EnableDragDrop");
extern const char g_cbShowSysFeatures[];	// TEXT("ShowSysFeatures");

extern const char g_cbLogoFileName[];	// TEXT("LogoFileName");
extern const char g_cbTRiASName[];		// TEXT("TRiASName");
extern const char g_cbTRiASMode[];		// TEXT("TRiASMode");

extern const char g_cbHandledExtensions[];	// TEXT("HandledExtensions");
extern const char g_cbFilter[];			// TEXT("Filter");

///////////////////////////////////////////////////////////////////////////////
// Verzeichnisse
extern const char g_cbDirectories[];	// TEXT("Software\\uve\\TRiAS\\Directories");
extern const char g_cbCursorDirectory[];	// TEXT("Cursors");

///////////////////////////////////////////////////////////////////////////////
// Diverse animierte Cursoren
extern const char g_cbCursors[];		// TEXT("Software\\uve\\TRiAS\\Cursors");
extern const char g_cbCursorLoad[];		// TEXT("Load");
extern const char g_cbCursorSave[];		// TEXT("Save");
extern const char g_cbCursorWait[];		// TEXT("Wait");
extern const char g_cbCursorPrint[];	// TEXT("Print");

///////////////////////////////////////////////////////////////////////////////
// TRiASEx - PropertyPages
extern const char g_cbDocSubKey[];		// TEXT("TRiASEx\\PropertySheetHandlers");
extern const char g_cbSearchSubKey[];	// TEXT("TRiASEx\\SearchEngines");
extern const char g_cbPrintLayout[];	// TEXT("TRiASEx\\PrintLayout");

extern const char g_cbCustomize[];		// TEXT("Customize");
extern const char g_cbCoordinates[];	// TEXT("Coordinates");
extern const char g_cbOptions[];		// TEXT("Options");

extern const char g_cbHexDigits[];		// TEXT("\\(\\[[[:xdigit:]]+\\]\\)\\|\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]]?.*\\)");

///////////////////////////////////////////////////////////////////////////////
// MetaFileHeader
extern const char g_cbTRiASPict[];		// TEXT("TRiAS\0TRiAS Picture\0");

// Overviews speichern
extern const char g_cbOverviews[];		// TEXT("OverviewPicts");
extern const char g_cbDefaultPict[];	// TEXT("DefaultPict");

extern const TCHAR g_cbId[];			// TEXT("Id");
extern const TCHAR g_cbIdForce[];		// TEXT("IdForce");

#else // WIN32

///////////////////////////////////////////////////////////////////////////////
// sonstiges
extern const char __far g_cbNil[];			// TEXT("");

///////////////////////////////////////////////////////////////////////////////
// Config-Flags
extern const char __far g_cbSysAdmin[];		// TEXT("SystemAdministration");
extern const char __far g_cbHideFlags[];	// TEXT("HideFlags");
extern const char __far g_cbShowObjProp[];	// TEXT("ShowObjProp");
extern const char __far g_cbImportFormat[];	// TEXT("ImportFormat");
extern const char __far g_cbDescription[];	// TEXT("Description");
extern const char __far g_cbFileExt[];		// TEXT("FileExtension");

#endif // WIN32

#endif // _STRINGS_H

