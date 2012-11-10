// Strings.cpp

#include "fakemfcp.hxx"
#include "strings.h"

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
char g_cbTRiAS[_MAX_PATH];

//////////////////////////////////////////////////////////////////////////////
// StringKonstanten
const TCHAR g_cbLayoutRoot[] = TEXT("NormalLayout");
const TCHAR g_cbLayoutRootFS[] = TEXT("FullScreenLayout");
const TCHAR g_cbLayoutRootOld[] = TEXT("LastLayout");
const TCHAR g_cbLayout[] = TEXT("NormalLayout\\Tool");
const TCHAR g_cbLayoutFS[] = TEXT("FullScreenLayout\\Tool");
const TCHAR g_cbSECBars[] = TEXT("SecBars");
const TCHAR g_cbSummarySection[] = TEXT("%s-Summary");

const TCHAR g_cbConfig[] = TEXT("Config");
const TCHAR g_cbShowToolTips[] = TEXT("ShowToolTips");
const TCHAR g_cbTRiASApp[] = TEXT("TRiAS.Application.2");
const TCHAR g_cbTRiASEx[] = TEXT("TRiASEx");
const TCHAR g_cbPropAct[] = TEXT("PropertyActions");
#if defined(_USE_SEC_CLASSES)
const TCHAR g_cbCoolLook[] = TEXT("EnableCoolLook");
#endif // _USE_SEC_CLASSES

const TCHAR szApp[] = TEXT("TRiAS® Raumbezogenes Informationssystem");

const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbDel[] = TEXT("\\");

const TCHAR g_cbPropertyChoices[] = TEXT("PropertyChoices");

const TCHAR g_cbINI[] = TEXT(".ini");
const char g_cbCopyrightName[] = TEXT("TRiAS®");

///////////////////////////////////////////////////////////////////////////////
// Tip of the Day
const TCHAR g_cbRegSection[] = TEXT("Software\\uve\\TRiAS\\TipOfTheDay");
const TCHAR g_cbIntStartup[] = TEXT("StartUp");

///////////////////////////////////////////////////////////////////////////////
//
const char g_cbLogoFileName[] = TEXT("LogoFileName");
const char g_cbTRiASName[] = TEXT("TRiASName");

///////////////////////////////////////////////////////////////////////////////
// OpenWizard
const TCHAR g_cbMRUFiles[] = TEXT("Software\\uve\\TRiAS\\OpenMRU");
const TCHAR g_cbShowOpenWizard[] = TEXT("HideOpenWizard");
const TCHAR g_cbLastFile[] = TEXT("File1");

///////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
const TCHAR g_cbCoordSystems[] = TEXT("Software\\uve\\TRiAS\\CoordSystems");
const TCHAR g_cbToolbar32[] = TEXT("Toolbar32");

const TCHAR g_cbIdentBase[] = TEXT("IdentBase");
const TCHAR g_cbCompatible[] = TEXT("Compatibility16");
const TCHAR g_cbUseOldPointStyle[] = TEXT("UseOldPointStyle");

///////////////////////////////////////////////////////////////////////////////
// allgemeines
const char g_cbRegConfig[] = TEXT("Software\\uve\\TRiAS\\Config");

///////////////////////////////////////////////////////////////////////////////
// Text for der ZoomComboBox
const char g_cbZoomText[] = TEXT("1:");
