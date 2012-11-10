// StringKonstanten
// File: Strings.cpp

#include "precomp.hxx"
#include "Strings.h"

///////////////////////////////////////////////////////////////////////////////
// Moniker support
const TCHAR g_cbComma[] = TEXT(",");
const TCHAR g_cbWild[] = TEXT("\\");
const TCHAR g_cbColon[] = TEXT(":");
const TCHAR g_cbNil[] = TEXT("");

const TCHAR g_cbGeoClass[] = TEXT("GeoClass");
const TCHAR g_cbGeoView[] = TEXT("GeoView");
const TCHAR g_cbGeoObject[] = TEXT("GeoObject");
const TCHAR g_cbGeoObjects[] = TEXT("GeoObjects");
const TCHAR g_cbGeoDocument[] = TEXT("GeoDocument");
const TCHAR g_cbGeoObjectWin[] = TEXT("GeoObjectWin");
const TCHAR g_cbGeoFeature[] = TEXT("GeoFeature");

const TCHAR g_cbMkGeoDocument[] = TEXT("MkGeoDocument");
const TCHAR g_cbMkGeoClass[] = TEXT("MkGeoClass");
const TCHAR g_cbMkGeoView[] = TEXT("MkGeoView");
const TCHAR g_cbMkGeoObject[] = TEXT("MkGeoObject");
const TCHAR g_cbMkGeoObjects[] = TEXT("MkGeoObjects");
const TCHAR g_cbMkGeoObjects36[] = TEXT("MkGeoObjects36");
const TCHAR g_cbMkConnection[] = TEXT("MkConnection");
const TCHAR g_cbMkObjectsDef[] = TEXT("MkObjectsDef");

const TCHAR g_cbCopyGeoObjects[] = TEXT("CopyGeoObjects");
const TCHAR g_cbCopyGeoObject[]	= TEXT("CopyGeoObject");

const TCHAR g_cbBezugsMasstab[] = TEXT("BezugsMasstab");

///////////////////////////////////////////////////////////////////////////////
// RegistrySupport
const TCHAR g_cbConfig[] = TEXT("Config");
const TCHAR g_cbTargetProgID[] = TEXT("TargetProgID");

///////////////////////////////////////////////////////////////////////////////
// UniCode Strings
const wchar_t g_cbuMkDel[] = L"!";

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Name
const TCHAR g_cbLogoFileName[] = TEXT("LogoFileName");
const TCHAR g_cbTRiASName[] = TEXT("TRiASName");
const TCHAR g_cbRegConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");
const TCHAR g_cbCopyrightName[] = TEXT("TRiAS®");

///////////////////////////////////////////////////////////////////////////////
// Strings für OLE-related Properties
const OLECHAR g_cbExtContX[] = L"ExtContX";
const OLECHAR g_cbExtContY[] = L"ExtContY";
const OLECHAR g_cbLastContLeft[] = L"LastContLeft";
const OLECHAR g_cbLastContRight[] = L"LastContRight";
const OLECHAR g_cbLastContTop[] = L"LastContTop";
const OLECHAR g_cbLastContBottom[] = L"LastContBottom";
const OLECHAR g_cbLastView[] = L"LastView";

///////////////////////////////////////////////////////////////////////////////
// MetaFileHeader
const TCHAR g_cbTRiASPict[] = TEXT("TRiAS\0TRiAS Picture\0");

/////////////////////////////////////////////////////////////////////////////
// SuchPattern für Objektklassenschlüssel
const TCHAR g_cbOKS[] = 
TEXT("\\[\\([[:xdigit:]]+\\)\\]" "\\|"							// [OKS]
	 "\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]].*\\)" "\\|"	// OKS:irgend was
	 "\\[\\([[:xdigit:]]+\\)\\]\\(.*\\)"  "\\|"					// [OKS]irgend was
	 "!\\(.*\\):\\[\\([[:xdigit:]]+\\)\\]\\(.*\\)"				// irgendwas![OKS]irgendwas (Monikerformat)
	);

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup geladen)
char g_cbTRiAS[_MAX_PATH];


