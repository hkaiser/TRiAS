// Strings.h

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup geladen)
extern char g_cbTRiAS[];

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
extern const TCHAR g_cbNoMemory[];		// TEXT("Kein Speicherplatz!");

extern const TCHAR g_cbLayout[];		// TEXT("NormalLayout\\Tool");
extern const TCHAR g_cbLayoutFS[];		// TEXT("FullScreenLayout\\Tool");
extern const TCHAR g_cbLayoutRoot[];	// TEXT("NormalLayout");
extern const TCHAR g_cbLayoutRootFS[];	// TEXT("FullScreenLayout");
extern const TCHAR g_cbLayoutRootOld[];	// TEXT("LastLayout");

extern const TCHAR g_cbSECBars[];		// TEXT("SecBars");
extern const TCHAR g_cbSummarySection[];	// TEXT("%s-Summary");
extern const TCHAR g_cbToolboxBitmap32[];	// TEXT("ToolboxBitmap32")

extern const TCHAR g_cbConfig[];		// TEXT("Config");
extern const TCHAR g_cbShowToolTips[];	// TEXT("ShowToolTips");
extern const TCHAR g_cbTRiASApp[];		// TEXT("TRiAS.Application.4");
extern const TCHAR g_cbTRiASEx[];		// TEXT("TRiASEx");
extern const TCHAR g_cbPropAct[];		// TEXT("PropertyActions");
extern const TCHAR g_cbOpenMRU[];		// TEXT("OpenMRU");
extern const TCHAR g_cbDirectories[];	// TEXT("Directories");
extern const TCHAR g_cbLastOpenDir[];	// TEXT("LastOpenDir");
extern const TCHAR g_cbDefaultDir[];	// TEXT("DefaultProjectDir");
extern const TCHAR g_cbLastFilter[];	// TEXT("LastFilter");
extern const TCHAR g_cbBackupDatafiles[]; // TEXT("BackupDatafiles");
extern const TCHAR g_cbTabServiceProviders[]; // TEXT("TabServiceProviders");
extern const TCHAR g_cbName[];			// TEXT("Name");
extern const TCHAR g_cbStyle[];			// TEXT("Style");
extern const TCHAR g_cbStyleEx[];		// TEXT("StyleEx");
extern const TCHAR g_cbEnableDocking[];	// TEXT("EnableDocking");
extern const TCHAR g_cbInitialDocking[];	// TEXT("InitialDocking");
extern const TCHAR g_cbInitialRatio[];	// TEXT("InitialRatio");
extern const TCHAR g_cbInitialPosX[];	// TEXT("InitialPosX");
extern const TCHAR g_cbInitialPosY[];	// TEXT("InitialPosY");
extern const TCHAR g_cbShouldBeAddedToMenu[];	// TEXT("ShouldBeAddedToMenu");

#if defined(_USE_SEC_CLASSES)
extern const TCHAR g_cbCoolLook[];		// TEXT("EnableCoolLook");
extern const TCHAR g_cbEnvision[];		// TEXT("Envision");
#endif // _USE_SEC_CLASSES

extern const TCHAR szApp[];				// TEXT("TRiAS® Raumbezogenes Informationssystem");

extern const TCHAR g_cbNil[];			// TEXT("");
extern const TCHAR g_cbDel[];			// TEXT("\\");
extern const TCHAR g_cbSpace[];			// TEXT(" ");
extern const OLECHAR g_cbSemicolon[];	// = L";";

extern const TCHAR g_cbPropertyChoices[];	// TEXT("PropertyChoices");

extern const TCHAR g_cbRiw[];			// TEXT(".riw");
extern const TCHAR g_cbRis[];			// TEXT(".ris");
extern const TCHAR g_cbINI[];			// TEXT(".ini");
extern const char g_cbCopyrightName[];	// TEXT("TRiAS®");

/////////////////////////////////////////////////////////////////////////////
// Tip of the Day
extern const TCHAR g_cbRegSection[];	// TEXT("Software\\TRiAS\\InterTRiAS\\TipOfTheDay");
extern const TCHAR g_cbIntStartup[];	// TEXT("StartUp");

///////////////////////////////////////////////////////////////////////////////
//
extern const char g_cbLogoFileName[];	// TEXT("LogoFileName");
extern const char g_cbTRiASName[];		// TEXT("TRiASName");

/////////////////////////////////////////////////////////////////////////////
// OpenWizard
extern const TCHAR g_cbMRUFiles[];		// TEXT("Software\\TRiAS\\InterTRiAS\\OpenMRU");
extern const TCHAR g_cbHideOpenWizard[];	// TEXT("HideOpenWizard");
extern const TCHAR g_cbLastFile[];		// TEXT("File1");
extern const TCHAR g_cbTRiASDB[];		// TEXT("TRiASDB");
extern const TCHAR g_cbLastDirUsed[];	// TEXT("LastDirUsed");
extern const TCHAR g_cbOldDataBase[];	// TEXT("TRiAS.Document.1");
extern const TCHAR g_cbDefaultDataBase[];	// TEXT("TRiAS.Document.2");
extern const TCHAR g_cbInternalDataBase[];	// TEXT("TRiAS.Document.3");
extern const TCHAR g_cbDescription[];	// TEXT("Description");
extern const TCHAR g_cbCLSID[];			// TEXT("CLSID");
extern const TCHAR g_cbConnSource[];	// TEXT(";PROGID=");
extern const TCHAR g_cbPattern[];		// TEXT(";%1=%2");

/////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
extern const TCHAR g_cbCoordSystems[];	// TEXT("Software\\TRiAS\\InterTRiAS\\CoordinateSystems");
extern const TCHAR g_cbToolbar32[];		// TEXT("Toolbar32");

extern const TCHAR g_cbIdentBase[];		// TEXT("IdentBase");
extern const TCHAR g_cbCompatible[];	// TEXT("Compatibility16");
extern const TCHAR g_cbUseOldPointStyle[];	// TEXT("UseOldPointStyle");
extern const TCHAR g_cbCaption[];		// TEXT("Caption");
extern const TCHAR g_cbActSubObject[];	// TEXT("ActSubObject");
extern const TCHAR g_cbStorage[];		// TEXT("Storage:");
extern const TCHAR g_cbConnect[];		// TEXT("Connect:");

///////////////////////////////////////////////////////////////////////////////
// allgemeines
extern const TCHAR g_cbRegConfig[];		// TEXT("Software\\TRiAS\\InterTRiAS\\Config");

///////////////////////////////////////////////////////////////////////////////
// Text for der ZoomComboBox
extern const TCHAR g_cbZoomText[];		// TEXT("1:");

///////////////////////////////////////////////////////////////////////////////
// Datenserver-RegistryKeys
//extern const TCHAR g_cbDatabaseClass[];	// TEXT("DatabaseClass");
//extern const TCHAR g_cbNameDescription[];	// TEXT("NameDescription");
//extern const TCHAR g_cbDefaultExtension[];	// TEXT("DefaultExtension");
//extern const TCHAR g_cbLongName[];		// TEXT("LongName");
//extern const TCHAR g_cbShortName[];		// TEXT("ShortName");
//extern const TCHAR g_cbNameIsDirectory[];	// TEXT("NameIsDirectory");
//extern const TCHAR g_cbNameIsFile[];	// TEXT("NameIsFile");
//extern const TCHAR g_cbReadWrite[];		// TEXT("ReadWrite");
//extern const TCHAR g_cbFilterString[];	// TEXT("FilterString");
//extern const TCHAR g_cbExtendedProperties[];	// TEXT("ExtendedProperties");
//extern const TCHAR g_cbTempName[];		// TEXT("TempName");

///////////////////////////////////////////////////////////////////////////////
//
extern const TCHAR g_cbLangGeneral[];	// TEXT(";LANGID=0x0409;CP=1252;COUNTRY=0");

///////////////////////////////////////////////////////////////////////////////
//
extern const TCHAR g_cbUnknownName[];	// TEXT("Unbekannt");
extern const OLECHAR g_cbDefaultVisInfo[];	// TEXT("__DefaultVisInfo__");
