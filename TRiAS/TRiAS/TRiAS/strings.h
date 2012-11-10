///////////////////////////////////////////////////////////////////////////
// @doc 
// @module strings.h | Globale StringKonstanten 

#if !defined(_STRINGS_H__73362994_A520_11D1_BA30_080036D63803__INCLUDED_)
#define _STRINGS_H__73362994_A520_11D1_BA30_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup initialisiert)
extern char g_cbTRiAS[];

///////////////////////////////////////////////////////////////////////////////
// RegistryKeys
extern const TCHAR g_cbRegOpenMRU[];	// TEXT("Software\\TRiAS\\InterTRiAS\\OpenMRU");
extern const TCHAR g_cbRegConfig[];		// TEXT("Software\\TRiAS\\InterTRiAS\\Config");
extern const TCHAR g_cbRegExtensions[];	// TEXT("Software\\TRiAS\\InterTRiAS\\Extensions")
extern const TCHAR g_cbRegVersion[];	// TEXT("SOFTWARE\\TRiAS\\InterTRiAS\\2.0");
extern const TCHAR g_cbUninstall[];		// TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\InterTRiAS");
extern const TCHAR g_cbTipOfTheDay[];	// TEXT("Software\\TRiAS\\InterTRiAS\\TipOfTheDay");

extern const TCHAR g_cbTipOfTheDayStartUp[];	// TEXT("StartUp");
extern const TCHAR g_cbHideOpenWizard[];		// TEXT("HideOpenWizard");

extern const TCHAR g_cbFakeMFCKey[];	// TEXT("Software\\TRiAS\\InterTRiAS\\Extensions\\TRiAS.FakeMFC.1\\Config");
extern const TCHAR g_cbFakeMFC[];		// TEXT("TRiAS.FakeMFC.1");
extern const TCHAR g_cbTRiASViewItem[];	// TEXT("TRiASDB.TRiASViewItem.1");

extern const TCHAR g_cbClsId[];			// TEXT("CLSID")
extern const TCHAR g_cbAppID[];			// TEXT("AppID");
extern const TCHAR g_cbToolboxBitmap[];	// TEXT("ToolboxBitmap32");
extern const TCHAR g_cbUnRegister[];	// TEXT("UnRegister");

extern const TCHAR g_cbAppKey[];		// TEXT("TRiAS.Application.4");
extern const TCHAR g_cbDocKey[];		// TEXT("TRiAS.Document.2");
extern const TCHAR g_cbInprocServer[];	// TEXT("InprocServer32");

extern const TCHAR g_cbUninstallString[];	// TEXT("UninstallString");
extern const TCHAR g_cbOrigUninstallString[];	// TEXT("OrigUninstallString");
extern const TCHAR g_cbDisplayName[];	// TEXT("DisplayName");
extern const TCHAR g_cbSerial[];		// TEXT("Serial");
extern const TCHAR g_cbUnregFull[];		// TEXT(" /unregserver:full");

///////////////////////////////////////////////////////////////////////////////
// IniKeys
extern const TCHAR g_cbIniOpenMRU[];	// TEXT("OpenMRU");

///////////////////////////////////////////////////////////////////////////////
// sonstiges
extern const TCHAR g_cbViewClass[];		// TEXT("TRiAS_View");
extern const TCHAR g_cbFrameClass[];	// TEXT("TRiAS_Frame");
extern const TCHAR g_cbLegendClass[];	// TEXT("TRiAS_Legend");
extern const TCHAR g_cbOverViewClass[];	// TEXT("TRiAS_OverView");

extern const TCHAR g_cbDel[];			// TEXT("\\");
extern const TCHAR g_cbNil[];			// TEXT("");
extern const TCHAR g_cbUndoDel[];		// TEXT("|");
extern const TCHAR g_cbColon[];			// TEXT(":");
extern const TCHAR g_cbMinus[];			// TEXT("-");
extern const TCHAR g_cbSpace[];			// TEXT(" ");
extern const TCHAR g_cbSpaceDashSpace[];	// TEXT(" - ");
extern const TCHAR g_cb2UnderScore[];	// TEXT("__");
extern const TCHAR g_cbScalePrefix[];	// TEXT("1:");
extern const TCHAR g_cbNL[];			// TEXT("\n");
extern const OLECHAR g_cbHasOption[];	// L"=1";
extern const OLECHAR g_cbSemiColon[];	// L";";

extern const TCHAR g_cbINI[];			// TEXT(".ini");
extern const TCHAR g_cbRiw[];			// TEXT(".riw");
extern const TCHAR g_cbCopyrightName[];	// TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
extern const TCHAR g_cbCopyrightNameT[]; // TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
extern const TCHAR g_cbScrollInset[];	// TEXT("DragScrollInset");
extern const TCHAR g_cbScrollDelay[];	// TEXT("DragScrollDelay");
extern const TCHAR g_cbWindowsSection[];	// TEXT("windows");

///////////////////////////////////////////////////////////////////////////////
// Config-Flags
extern const TCHAR g_cbConfig[];		// TEXT("Config");
extern const TCHAR g_cbHSBColors[];		// TEXT("HSBColors");
extern const TCHAR g_cbLastOpenDir[];	// TEXT("LastOpenDir");
extern const TCHAR g_cbFlickerFreeTime[];	// TEXT("FlickerFreeTime");
extern const TCHAR g_cbIdleTime[];		// TEXT("IdleTime");

extern const TCHAR g_cbDrawingMode[];	// TEXT("DrawingMode");

extern const TCHAR g_cbRegCompany[];	// TEXT("Company");
extern const TCHAR g_cbRegName[];		// TEXT("Name");

extern const TCHAR g_cbSysAdmin[];		// TEXT("SystemAdministration");
extern const TCHAR g_cbHideFlags[];		// TEXT("HideFlags");
extern const TCHAR g_cbShowObjProp[];	// TEXT("ShowObjProp");
extern const TCHAR g_cbPreLoad[];		// TEXT("PreLoad");
extern const TCHAR g_cbPriorityLoad[];	// TEXT("PriorityLoad");
extern const TCHAR g_cbUnLoadable[];	// TEXT("UnLoadable");
extern const TCHAR g_cbVisible[];		// TEXT("Visible");
extern const TCHAR g_cbCanImport[];		// TEXT("CanImport");
extern const TCHAR g_cbAggregate[];		// TEXT("Aggregate");
extern const TCHAR g_cbDelFeature[];	// TEXT("DelimiterForFeature");
extern const TCHAR g_cbImportFormat[];	// TEXT("ImportFormat");
extern const TCHAR g_cbDescription[];	// TEXT("Description");
extern const TCHAR g_cbFileExt[];		// TEXT("FileExtension");
extern const TCHAR g_cbHoldZoom[];		// TEXT("PreserveZoom");
extern const TCHAR g_cbEnableDragDrop[];	// TEXT("EnableDragDrop");
extern const TCHAR g_cbShowSysFeatures[];	// TEXT("ShowSysFeatures");
extern const TCHAR g_cbBackGroundColor[];	// TEXT("BackGroundColor");
extern const TCHAR g_cbScrollMode[];		// TEXT("RedrawOnScroll");
extern const TCHAR g_cbPosTxtAtBaseLine[];	// TEXT("PosTxtAtBaseLine");
extern const TCHAR g_cbCompatibility16[];	// TEXT("Compatibility16");
extern const TCHAR g_cbNameIsDefault[];		// TEXT("NameIsDefault");
extern const TCHAR g_cbImpressum[];			// TEXT("Impressum       ");
extern const TCHAR g_cbDragDropTarget[];	// TEXT("DragDropTarget");
extern const TCHAR g_cbBackupDatafiles[];	// TEXT("BackupDatafiles");
extern const TCHAR g_cbWarnBeforeDelObj[];   // TEXT("WarnBeforeDelObj");

///////////////////////////////////////////////////////////////////////////////
// ViewProperties
extern const TCHAR g_cbSysProperty[];	// TEXT("Property %08lx");
extern const TCHAR g_cbObjectRegion[];	// TEXT("ObjectRegion");
extern const TCHAR g_cbObjPropToShow[];	// TEXT("ObjPropToShow");
extern const TCHAR g_cbHideAndSortFlags[];	// TEXT("HideAndSortFlags");

extern const TCHAR g_cbLogoFileName[];	// TEXT("LogoFileName");
extern const TCHAR g_cbTRiASName[];		// TEXT("TRiASName");
extern const TCHAR g_cbTRiASMode[];		// TEXT("TRiASMode");

extern const TCHAR g_cbHandledExtensions[];	// TEXT("HandledExtensions");
extern const TCHAR g_cbFilter[];		// TEXT("Filter");

///////////////////////////////////////////////////////////////////////////////
// Verzeichnisse
extern const TCHAR g_cbDirectories[];	// TEXT("Software\\TRiAS\\InterTRiAS\\Directories");
extern const TCHAR g_cbCursorDirectory[];	// TEXT("Cursors");

///////////////////////////////////////////////////////////////////////////////
// Diverse animierte Cursoren
extern const TCHAR g_cbCursors[];		// TEXT("Software\\TRiAS\\InterTRiAS\\Cursors");
extern const TCHAR g_cbCursorLoad[];	// TEXT("Load");
extern const TCHAR g_cbCursorSave[];	// TEXT("Save");
extern const TCHAR g_cbCursorWait[];	// TEXT("Wait");
extern const TCHAR g_cbCursorPrint[];	// TEXT("Print");

///////////////////////////////////////////////////////////////////////////////
// TRiASEx - PropertyPages
extern const TCHAR g_cbDocSubKey[];		// TEXT("TRiASEx\\PropertySheetHandlers");
extern const TCHAR g_cbSearchSubKey[];	// TEXT("TRiASEx\\SearchEngines");

extern const TCHAR g_cbPrintLayout[];	// TEXT("PrintLayout");
extern const TCHAR g_cbCustomize[];		// TEXT("Customize");
extern const TCHAR g_cbCoordinates[];	// TEXT("Coordinates");
extern const TCHAR g_cbOptions[];		// TEXT("Options");
extern const TCHAR g_cbForceReload[];	// TEXT("ForceReload");

extern const TCHAR g_cbHexDigits[];		// TEXT("\\(\\[[[:xdigit:]]+\\]\\)\\|\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]]?.*\\)");

extern const TCHAR g_cbSelect[];		// TEXT("Select=");

///////////////////////////////////////////////////////////////////////////////
// MetaFileHeader
extern const TCHAR g_cbTRiASPict[];		// TEXT("TRiAS\0TRiAS Picture\0");

// Overviews speichern
extern const TCHAR g_cbOverviews[];		// TEXT("OverviewPicts");
extern const TCHAR g_cbDefaultPict[];	// TEXT("DefaultPict");

// Project/DatabaseProperties 
extern const TCHAR g_cbStgService[];	// TEXT("StgService");

// FeatureMap in Objektklassen
extern const TCHAR g_cbFeatureMap[];	// TEXT("FeatureMap");
extern const OLECHAR g_cbDefaultGeometry[];	// L"DefaultGeometry";
extern const OLECHAR g_cbObjGuid[];		// L"__ObjGuid__";

extern const TCHAR g_cbIndText[];		// TEXT("@@");

extern const TCHAR g_cbId[];			// TEXT("Id");
extern const TCHAR g_cbIdForce[];		// TEXT("IdForce");
extern const TCHAR g_cbStandard[];		// TEXT("Standard");
extern const TCHAR g_cbObjName[];		// TEXT("Objektname");
extern const TCHAR g_cbPrimaryKey[];	// TEXT("PrimaryKey");

extern const TCHAR g_cbUnknownOKS[];	// TEXT("E0000000");

extern const TCHAR g_cbRelationMap[];	// TEXT("RelationMap");
extern const TCHAR g_cbObjectMap[];		// TEXT("ObjectMap");
extern const TCHAR g_cbObjectsMap[];	// TEXT("ObjectsMap");
extern const TCHAR g_cbShowTextsInView[];	// TEXT("ShowTextsInView");

#if defined(_USE_XML_GEOCOMPONENTS)
///////////////////////////////////////////////////////////////////////////////
// XML basierte Objekteigenschaften
extern const OLECHAR g_cbCatalogFolder[];	// L"CatalogFolder";
extern const OLECHAR g_cbCatalogNode[];		// L"CatalogNode";
extern const OLECHAR g_cbInitDesc[];		// L"Description";
extern const OLECHAR g_cbInitName[];		// L"Name";

#endif // defined(_USE_XML_GEOCOMPONENTS)

#endif // !defined(_STRINGS_H__73362994_A520_11D1_BA30_080036D63803__INCLUDED_)
