// StringKonstanten
// File: Strings.h

#if !defined(_STRINGS_H)
#define _STRINGS_H

///////////////////////////////////////////////////////////////////////////////
// Moniker support
extern const TCHAR g_cbComma[];				// TEXT(",");
extern const TCHAR g_cbWild[];				// TEXT("\\");
extern const TCHAR g_cbColon[];				// TEXT(":");
extern const TCHAR g_cbNil[];				// TEXT("");

extern const TCHAR g_cbGeoClass[];			// TEXT("GeoClass");
extern const TCHAR g_cbGeoView[];			// TEXT("GeoView");
extern const TCHAR g_cbGeoObject[];			// TEXT("GeoObject");
extern const TCHAR g_cbGeoObjects[];		// TEXT("GeoObjects");
extern const TCHAR g_cbGeoObjects[];		// TEXT("GeoObjects");
extern const TCHAR g_cbGeoDocument[];		// TEXT("GeoDocument");
extern const TCHAR g_cbGeoObjectWin[];		// TEXT("GeoObjectWin");
extern const TCHAR g_cbGeoFeature[];		// TEXT("GeoFeature");

extern const TCHAR g_cbMkGeoDocument[];		// TEXT("MkGeoDocument");
extern const TCHAR g_cbMkGeoClass[];		// TEXT("MkGeoClass");
extern const TCHAR g_cbMkGeoView[];			// TEXT("MkGeoView");
extern const TCHAR g_cbMkGeoObject[];		// TEXT("MkGeoObject");
extern const TCHAR g_cbMkGeoObjects[];		// TEXT("MkGeoObjects");
extern const TCHAR g_cbMkGeoObjects36[];	// TEXT("MkGeoObjects36");
extern const TCHAR g_cbMkConnection[];		// TEXT("MkConnection");
extern const TCHAR g_cbMkObjectsDef[];		// TEXT("MkObjectsDef");

extern const TCHAR g_cbCopyGeoObjects[];	// TEXT("CopyGeoObjects")
extern const TCHAR g_cbCopyGeoObject[];		// TEXT("CopyGeoObject")

extern const TCHAR g_cbBezugsMasstab[];		// TEXT("BezugsMasstab")

///////////////////////////////////////////////////////////////////////////////
// RegistrySupport
extern const TCHAR g_cbConfig[];			// TEXT("Config");
extern const TCHAR g_cbTargetProgID[];		// TEXT("TargetProgID");

///////////////////////////////////////////////////////////////////////////////
// UniCode Strings
extern const wchar_t g_cbuMkDel[];			// TEXT("!");

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Name
extern const TCHAR g_cbLogoFileName[];		// TEXT("LogoFileName");
extern const TCHAR g_cbTRiASName[];			// TEXT("TRiASName");
extern const TCHAR g_cbRegConfig[];			// TEXT("Software\\TRiAS\\InterTRiAS\\Config");
extern const TCHAR g_cbCopyrightName[];		// TEXT("TRiAS®");

///////////////////////////////////////////////////////////////////////////////
// Strings für OLE-related Properties
extern const OLECHAR g_cbExtContX[];		// L"ExtContX";
extern const OLECHAR g_cbExtContY[];		// L"ExtContY";
extern const OLECHAR g_cbLastContLeft[];	// L"LastContLeft";
extern const OLECHAR g_cbLastContRight[];	// L"LastContRight";
extern const OLECHAR g_cbLastContTop[];		// L"LastContTop";
extern const OLECHAR g_cbLastContBottom[];	// L"LastContBottom";
extern const OLECHAR g_cbLastView[];		// L"LastView";

///////////////////////////////////////////////////////////////////////////////
// MetaFileHeader
extern const TCHAR g_cbTRiASPict[];			// TEXT("TRiAS\0TRiAS Picture\0");

/////////////////////////////////////////////////////////////////////////////
// SuchPattern für Objektklassenschlüssel
extern const TCHAR g_cbOKS[];
//TEXT("\\[\\([[:xdigit:]]+\\)\\]" "\\|"						// [OKS]
//	 "\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]].*\\)" "\\|"	// OKS:irgend was
//	 "\\[\\([[:xdigit:]]+\\)\\]\\(.*\\)"  "\\|"					// [OKS]irgend was
//	 "!\\(.*\\):\\[\\([[:xdigit:]]+\\)\\]\\(.*\\)"				// irgendwas![OKS]irgendwas (Monikerformat)
//	);

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup geladen)
extern char g_cbTRiAS[];

#endif // _STRINGS_H
