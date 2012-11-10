// Strings.h

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup geladen)
extern char g_cbTRiAS[];

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
extern const TCHAR g_cbLayout[];		// TEXT("NormalLayout\\Tool");
extern const TCHAR g_cbLayoutFS[];		// TEXT("FullScreenLayout\\Tool");
extern const TCHAR g_cbLayoutRoot[];	// TEXT("NormalLayout");
extern const TCHAR g_cbLayoutRootFS[];	// TEXT("FullScreenLayout");
extern const TCHAR g_cbLayoutRootOld[];	// TEXT("LastLayout");
extern const TCHAR g_cbSECBars[];		// TEXT("SecBars");
extern const TCHAR g_cbSummarySection[];	// TEXT("%s-Summary");

extern const TCHAR g_cbConfig[];		// TEXT("Config");
extern const TCHAR g_cbShowToolTips[];	// TEXT("ShowToolTips");
extern const TCHAR g_cbTRiASApp[];		// TEXT("TRiAS.Application.2");
extern const TCHAR g_cbTRiASEx[];		// TEXT("TRiASEx");
extern const TCHAR g_cbPropAct[];		// TEXT("PropertyActions");
#if defined(_USE_SEC_CLASSES)
extern const TCHAR g_cbCoolLook[];		// TEXT("EnableCoolLook");
#endif // _USE_SEC_CLASSES

extern const TCHAR szApp[];				// TEXT("TRiAS® Raumbezogenes Informationssystem");

extern const TCHAR g_cbNil[];			// TEXT("");
extern const TCHAR g_cbDel[];			// TEXT("\\");

extern const TCHAR g_cbPropertyChoices[];	// TEXT("PropertyChoices");

extern const TCHAR g_cbINI[];			// TEXT(".ini");
extern const char g_cbCopyrightName[];	// TEXT("TRiAS®");

/////////////////////////////////////////////////////////////////////////////
// Tip of the Day
extern const TCHAR g_cbRegSection[];	// TEXT("Software\\uve\\TRiAS\\TipOfTheDay");
extern const TCHAR g_cbIntStartup[];	// TEXT("StartUp");

///////////////////////////////////////////////////////////////////////////////
//
extern const char g_cbLogoFileName[];	// TEXT("LogoFileName");
extern const char g_cbTRiASName[];		// TEXT("TRiASName");

/////////////////////////////////////////////////////////////////////////////
// OpenWizard
extern const TCHAR g_cbMRUFiles[];		// TEXT("Software\\uve\\TRiAS\\OpenMRU");
extern const TCHAR g_cbShowOpenWizard[];	// TEXT("ShowOpenWizard");
extern const TCHAR g_cbLastFile[];		// TEXT("File1");

/////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
extern const TCHAR g_cbCoordSystems[];	// TEXT("Software\\uve\\TRiAS\\CoordSystems");
extern const TCHAR g_cbToolbar32[];		// TEXT("Toolbar32");

extern const TCHAR g_cbIdentBase[];		// TEXT("IdentBase");
extern const TCHAR g_cbCompatible[];	// TEXT("Compatibility16");
extern const TCHAR g_cbUseOldPointStyle[];	// TEXT("UseOldPointStyle");

///////////////////////////////////////////////////////////////////////////////
// allgemeines
extern const TCHAR g_cbRegConfig[];		// TEXT("Software\\uve\\TRiAS\\Config");

///////////////////////////////////////////////////////////////////////////////
// Text for der ZoomComboBox
extern const TCHAR g_cbZoomText[];		// TEXT("1:");
