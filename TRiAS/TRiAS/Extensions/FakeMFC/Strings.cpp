// Strings.cpp

#include "fakemfcp.hxx"
#include "strings.h"

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
char g_cbTRiAS[_MAX_PATH];

//////////////////////////////////////////////////////////////////////////////
// StringKonstanten
const TCHAR g_cbNoMemory[] = TEXT("Kein Speicherplatz!");

const TCHAR g_cbLayoutRoot[] = TEXT("NormalLayout");
const TCHAR g_cbLayoutRootFS[] = TEXT("FullScreenLayout");
const TCHAR g_cbLayoutRootOld[] = TEXT("LastLayout");
const TCHAR g_cbLayout[] = TEXT("NormalLayout\\Tool");
const TCHAR g_cbLayoutFS[] = TEXT("FullScreenLayout\\Tool");

const TCHAR g_cbSECBars[] = TEXT("SecBars");
const TCHAR g_cbSummarySection[] = TEXT("%s-Summary");
const TCHAR g_cbToolboxBitmap32[] = TEXT("ToolboxBitmap32");

const TCHAR g_cbConfig[] = TEXT("Config");
const TCHAR g_cbShowToolTips[] = TEXT("ShowToolTips");
const TCHAR g_cbTRiASApp[] = TEXT("TRiAS.Application.4");
const TCHAR g_cbTRiASEx[] = TEXT("TRiASEx");
const TCHAR g_cbPropAct[] = TEXT("PropertyActions");
const TCHAR g_cbOpenMRU[] = TEXT("OpenMRU");
const TCHAR g_cbDirectories[] = TEXT("Directories");
const TCHAR g_cbLastOpenDir[] = TEXT("LastProjectDir");
const TCHAR g_cbDefaultDir[] = TEXT("DefaultProjectDir");
const TCHAR g_cbLastFilter[] = TEXT("LastFilter");
const TCHAR g_cbBackupDatafiles[] = TEXT("BackupDatafiles");
const TCHAR g_cbTabServiceProviders[] = TEXT("TabServiceProviders");
const TCHAR g_cbName[] = TEXT("Name");
const TCHAR g_cbStyle[] = TEXT("Style");
const TCHAR g_cbStyleEx[] = TEXT("StyleEx");
const TCHAR g_cbEnableDocking[] = TEXT("EnableDocking");
const TCHAR g_cbInitialDocking[] = TEXT("InitialDocking");
const TCHAR g_cbInitialRatio[] = TEXT("InitialRatio");
const TCHAR g_cbInitialPosX[] = TEXT("InitialPosX");
const TCHAR g_cbInitialPosY[] = TEXT("InitialPosY");
const TCHAR g_cbShouldBeAddedToMenu[] = TEXT("ShouldBeAddedToMenu");

#if defined(_USE_SEC_CLASSES)
const TCHAR g_cbCoolLook[] = TEXT("EnableCoolLook");
const TCHAR g_cbEnvision[] = TEXT("Envision");
#endif // _USE_SEC_CLASSES

const TCHAR szApp[] = TEXT("TRiAS® Raumbezogenes Informationssystem");

const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbDel[] = TEXT("\\");
const TCHAR g_cbSpace[] = TEXT(" ");
const OLECHAR g_cbSemicolon[] = L";";

const TCHAR g_cbPropertyChoices[] = TEXT("PropertyChoices");

const TCHAR g_cbRiw[] = TEXT(".riw");
const TCHAR g_cbRis[] = TEXT(".ris");
const TCHAR g_cbINI[] = TEXT(".ini");
const char g_cbCopyrightName[] = TEXT("TRiAS");

///////////////////////////////////////////////////////////////////////////////
// Tip of the Day
const TCHAR g_cbRegSection[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\TipOfTheDay");
const TCHAR g_cbIntStartup[] = TEXT("StartUp");

///////////////////////////////////////////////////////////////////////////////
//
const char g_cbLogoFileName[] = TEXT("LogoFileName");
const char g_cbTRiASName[] = TEXT("TRiASName");

///////////////////////////////////////////////////////////////////////////////
// OpenWizard
const TCHAR g_cbMRUFiles[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\OpenMRU");
const TCHAR g_cbHideOpenWizard[] = TEXT("HideOpenWizard");
const TCHAR g_cbLastFile[] = TEXT("File1");

const TCHAR g_cbTRiASDB[] = TEXT("TRiASDB");
const TCHAR g_cbLastDirUsed[] = TEXT("LastDirUsed");
const TCHAR g_cbOldDataBase[] = TEXT("TRiAS.Document.1");
const TCHAR g_cbDefaultDataBase[] = TEXT("TRiAS.Document.2");
const TCHAR g_cbInternalDataBase[] = TEXT("TRiAS.Document.3");
const TCHAR g_cbDescription[] = TEXT("Description");
const TCHAR g_cbCLSID[] = TEXT("CLSID");
const TCHAR g_cbConnSource[] = TEXT(";PROGID=");
const TCHAR g_cbPattern[] = TEXT(";%1=%2");

///////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
const TCHAR g_cbCoordSystems[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\CoordinateSystems");
const TCHAR g_cbToolbar32[] = TEXT("Toolbar32");

const TCHAR g_cbIdentBase[] = TEXT("IdentBase");
const TCHAR g_cbCompatible[] = TEXT("Compatibility16");
const TCHAR g_cbUseOldPointStyle[] = TEXT("UseOldPointStyle");
const TCHAR g_cbCaption[] = TEXT("Caption");
const TCHAR g_cbActSubObject[] = TEXT("ActSubObject");
const TCHAR g_cbStorage[] = TEXT("Storage:");
const TCHAR g_cbConnect[] = TEXT("Connect:");

///////////////////////////////////////////////////////////////////////////////
// allgemeines
const char g_cbRegConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");

///////////////////////////////////////////////////////////////////////////////
// Text for der ZoomComboBox
const char g_cbZoomText[] = TEXT("1:");

///////////////////////////////////////////////////////////////////////////////
// Datenserver-RegistryKeys
//const TCHAR g_cbDatabaseClass[] = TEXT("DatabaseClass");
//const TCHAR g_cbNameDescription[] = TEXT("NameDescription");
//const TCHAR g_cbDefaultExtension[] = TEXT("DefaultExtension");
//const TCHAR g_cbLongName[] = TEXT("LongName");
//const TCHAR g_cbShortName[] = TEXT("ShortName");
//const TCHAR g_cbNameIsDirectory[] = TEXT("NameIsDirectory");
//const TCHAR g_cbNameIsFile[] = TEXT("NameIsFile");
//const TCHAR g_cbReadWrite[] = TEXT("ReadWrite");
//const TCHAR g_cbFilterString[] = TEXT("FilterString");
//const TCHAR g_cbExtendedProperties[] = TEXT("ExtendedProperties");
//const TCHAR g_cbTempName[] = TEXT("TempName");

///////////////////////////////////////////////////////////////////////////////
//
const TCHAR g_cbLangGeneral[] = TEXT(";LANGID=0x0409;CP=1252;COUNTRY=0");

///////////////////////////////////////////////////////////////////////////////
//
const TCHAR g_cbUnknownName[] = TEXT("Unbekannt");
const OLECHAR g_cbDefaultVisInfo[] = L"__DefaultVisInfo__";

