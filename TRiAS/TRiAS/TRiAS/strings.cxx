// StringKonstanten -----------------------------------------------------------
// File: STRINGS.CXX

#include "triaspre.hxx"
#include "strings.h"

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
char g_cbTRiAS[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// RegistryKeys
const TCHAR g_cbRegOpenMRU[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\OpenMRU");
const TCHAR g_cbRegConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");
const TCHAR g_cbRegExtensions[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions");
const TCHAR g_cbRegVersion[] = TEXT("SOFTWARE\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY) TEXT("\\5.0");
const TCHAR g_cbUninstall[] = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" REG_PRODUCT_KEY);
const TCHAR g_cbFakeMFCKey[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.FakeMFC.1\\Config");
const TCHAR g_cbTipOfTheDay[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\TipOfTheDay");

const TCHAR g_cbTipOfTheDayStartUp[] = TEXT("StartUp");
const TCHAR g_cbHideOpenWizard[] = TEXT("HideOpenWizard");

const TCHAR g_cbFakeMFC[] = TEXT("TRiAS.FakeMFC.1");
const TCHAR g_cbTRiASViewItem[] = TEXT("TRiASDB.TRiASViewItem.1");

const TCHAR g_cbClsId[] = TEXT("CLSID");
const TCHAR g_cbAppID[] = TEXT("AppID");
const TCHAR g_cbToolboxBitmap[] = TEXT("ToolboxBitmap32");
const TCHAR g_cbUnRegister[] = TEXT("UnRegister");

const TCHAR g_cbAppKey[] = TEXT("TRiAS.Application.4");
const TCHAR g_cbDocKey[] = TEXT("TRiAS.Document.2");
const TCHAR g_cbInprocServer[] = TEXT("InprocServer32");

const TCHAR g_cbUninstallString[] = TEXT("UninstallString");
const TCHAR g_cbOrigUninstallString[] = TEXT("OrigUninstallString");
const TCHAR g_cbDisplayName[] = TEXT("DisplayName");
const TCHAR g_cbSerial[] = TEXT("Serial");
const TCHAR g_cbUnregFull[] = TEXT(" /unregserver:full");

///////////////////////////////////////////////////////////////////////////////
// sonstiges
const TCHAR g_cbViewClass[] = TEXT("TRiAS_View");
const TCHAR g_cbFrameClass[] = TEXT("TRiAS_Frame");
const TCHAR g_cbLegendClass[] = TEXT("TRiAS_Legend");
const TCHAR g_cbOverViewClass[] = TEXT("TRiAS_OverView");

const TCHAR g_cbDel[] = TEXT("\\");
const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbUndoDel[] = TEXT("|");
const TCHAR g_cbColon[] = TEXT(":");
const TCHAR g_cbMinus[] = TEXT("-");
const TCHAR g_cbSpace[] = TEXT(" ");
const TCHAR g_cbSpaceDashSpace[] = TEXT(" - ");
const TCHAR g_cb2UnderScore[] = TEXT("__");
const TCHAR g_cbScalePrefix[] = TEXT("1:");
const TCHAR g_cbNL[] = TEXT("\n");
const OLECHAR g_cbHasOption[] = L"=1";
const OLECHAR g_cbSemiColon[] = L";";

const TCHAR g_cbINI[] = TEXT(".ini");
const TCHAR g_cbRiw[] = TEXT(".riw");
const TCHAR g_cbCopyrightName[] = TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
const TCHAR g_cbCopyrightNameT[] = TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
const TCHAR g_cbScrollInset[] = TEXT("DragScrollInset");
const TCHAR g_cbScrollDelay[] = TEXT("DragScrollDelay");
const TCHAR g_cbWindowsSection[] = TEXT("windows");

///////////////////////////////////////////////////////////////////////////////
// Config-Flags
const TCHAR g_cbConfig[] = TEXT("Config");
const TCHAR g_cbHSBColors[] = TEXT("HSBColors");
const TCHAR g_cbLastOpenDir[] = TEXT("LastOpenDir");
const TCHAR g_cbFlickerFreeTime[] = TEXT("FlickerFreeTime");
const TCHAR g_cbIdleTime[] = TEXT("IdleTime");

const TCHAR g_cbDrawingMode[] = TEXT("DrawingMode");

const TCHAR g_cbRegCompany[] = TEXT("Company");
const TCHAR g_cbRegName[] = TEXT("User");

const TCHAR g_cbSysAdmin[] = TEXT("SystemAdministration");
const TCHAR g_cbHideFlags[] = TEXT("HideFlags");
const TCHAR g_cbShowObjProp[] = TEXT("ShowObjProp");
const TCHAR g_cbPreLoad[] = TEXT("PreLoad");
const TCHAR g_cbPriorityLoad[] = TEXT("PriorityLoad");
const TCHAR g_cbUnLoadable[] = TEXT("UnLoadable");
const TCHAR g_cbVisible[] = TEXT("Visible");
const TCHAR g_cbCanImport[] = TEXT("CanImport");
const TCHAR g_cbAggregate[] = TEXT("Aggregate");
const TCHAR g_cbDelFeature[] = TEXT("DelimiterForFeature");
const TCHAR g_cbImportFormat[] = TEXT("ImportFormat");
const TCHAR g_cbDescription[] = TEXT("Description");
const TCHAR g_cbFileExt[] = TEXT("FileExtension");
const TCHAR g_cbHoldZoom[] = TEXT("PreserveZoom");
const TCHAR g_cbEnableDragDrop[] = TEXT("EnableDragDrop");
const TCHAR g_cbShowSysFeatures[] = TEXT("ShowSysFeatures");
const TCHAR g_cbBackGroundColor[] = TEXT("BackGroundColor");
const TCHAR g_cbScrollMode[] = TEXT("RedrawOnScroll");
const TCHAR g_cbPosTxtAtBaseLine[] = TEXT("PosTxtAtBaseLine");
const TCHAR g_cbCompatibility16[] = TEXT("Compatibility16");
const TCHAR g_cbNameIsDefault[] = TEXT("NameIsDefault");
const TCHAR g_cbImpressum[] = TEXT("Copyright       ");
const TCHAR g_cbDragDropTarget[] = TEXT("DragDropTarget");
const TCHAR g_cbBackupDatafiles[] = TEXT("BackupDatafiles");
const TCHAR g_cbWarnBeforeDelObj[] = TEXT("WarnBeforeDelObj");

///////////////////////////////////////////////////////////////////////////////
// ViewProperties
const TCHAR g_cbSysProperty[] = TEXT("Property %08ld");
const TCHAR g_cbObjectRegion[] = TEXT("ObjectRegion");
const TCHAR g_cbObjPropToShow[] = TEXT("ObjPropToShow");
const TCHAR g_cbHideAndSortFlags[] = TEXT("HideAndSortFlags");

const TCHAR g_cbLogoFileName[] = TEXT("LogoFileName");
const TCHAR g_cbTRiASName[] = TEXT("TRiASName");
const TCHAR g_cbTRiASMode[] = TEXT("TRiASMode");

const TCHAR g_cbHandledExtensions[] = TEXT("HandledExtensions");
const TCHAR g_cbFilter[] = TEXT("Filter");

///////////////////////////////////////////////////////////////////////////////
// Verzeichnisse
const TCHAR g_cbDirectories[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Directories");
const TCHAR g_cbCursorDirectory[] = TEXT("Cursors");

///////////////////////////////////////////////////////////////////////////////
// Diverse animierte Cursoren
const TCHAR g_cbCursors[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Cursors");
const TCHAR g_cbCursorLoad[] = TEXT("Load");
const TCHAR g_cbCursorSave[] = TEXT("Save");
const TCHAR g_cbCursorWait[] = TEXT("Wait");
const TCHAR g_cbCursorPrint[] = TEXT("Print");

///////////////////////////////////////////////////////////////////////////////
// IniKeys
const TCHAR g_cbIniOpenMRU[] = TEXT("OpenMRU");

///////////////////////////////////////////////////////////////////////////////
// TRiASEx - PropertySheetPages
const TCHAR g_cbDocSubKey[] = TEXT("TRiASEx\\PropertySheetHandlers");
const TCHAR g_cbSearchSubKey[] = TEXT("TRiASEx\\SearchEngines");

const TCHAR g_cbPrintLayout[] = TEXT("PrintLayout");
const TCHAR g_cbCustomize[] = TEXT("Customize");
const TCHAR g_cbCoordinates[] = TEXT("Coordinates");
const TCHAR g_cbOptions[] = TEXT("Options");
const TCHAR g_cbForceReload[] = TEXT("ForceReload");

const TCHAR g_cbHexDigits[] = TEXT("[[:blank:]]*\\(\\[[[:xdigit:]]+\\]\\)\\|\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]]?.*\\)");	// TEXT("0123456789abcdefABCDEF");

const TCHAR g_cbSelect[] = TEXT("Select=");

///////////////////////////////////////////////////////////////////////////////
// MetaFileHeader
const TCHAR g_cbTRiASPict[] = TEXT("TRiAS\0TRiAS Picture\0");

// Overviews speichern
const TCHAR g_cbOverviews[] = TEXT("OverviewPicts");
const TCHAR g_cbDefaultPict[] = TEXT("DefaultPict");

// Project/DatabaseProperties 
const TCHAR g_cbStgService[] = TEXT("StgService");

// FeatureMap in Objektklassen
const TCHAR g_cbFeatureMap[] = TEXT("FeatureMap");
const OLECHAR g_cbDefaultGeometry[] = L"DefaultGeometry";
const OLECHAR g_cbObjGuid[] = L"__ObjGuid__";

const TCHAR g_cbIndText[] = TEXT("@@");

const TCHAR g_cbId[] = TEXT("Id");
const TCHAR g_cbIdForce[] = TEXT("IdForce");
const TCHAR g_cbStandard[] = TEXT("Standard");
const TCHAR g_cbObjName[] = TEXT("Objektname");
const TCHAR g_cbPrimaryKey[] = TEXT("PrimaryKey");

const TCHAR g_cbUnknownOKS[] = TEXT("E0000000");

const TCHAR g_cbRelationMap[] = TEXT("RelationMap");
const TCHAR g_cbObjectMap[] = TEXT("ObjectMap");
const TCHAR g_cbObjectsMap[] = TEXT("ObjectsMap");
const TCHAR g_cbShowTextsInView[] = TEXT("ShowTextsInView");

#if defined(_USE_XML_GEOCOMPONENTS)
///////////////////////////////////////////////////////////////////////////////
// XML basierte Objekteigenschaften
const OLECHAR g_cbCatalogFolder[] = L"CatalogFolder";
const OLECHAR g_cbCatalogNode[] = L"CatalogNode";
const OLECHAR g_cbInitDesc[] = L"Description";
const OLECHAR g_cbInitName[] = L"Name";

#endif // defined(_USE_XML_GEOCOMPONENTS)
