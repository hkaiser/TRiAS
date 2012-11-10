///////////////////////////////////////////////////////////////////////////
// Stringkonstanten
// File: Strings.h

#if !defined(_STRINGS_H__978C1EC9_2F3C_11d1_969F_00A024D6F582__INCLUDED_)
#define _STRINGS_H__978C1EC9_2F3C_11d1_969F_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Datenserver registryKeys
extern const TCHAR g_cbDatabaseClass[];			// TEXT("DatabaseClass")
extern const TCHAR g_cbNameDescription[];		// TEXT("NameDescription")
extern const TCHAR g_cbDefaultExtension[];		// TEXT("DefaultExtension")
extern const TCHAR g_cbLongName[];				// TEXT("LongName")
extern const TCHAR g_cbShortName[];				// TEXT("ShortName")
extern const TCHAR g_cbNameIsDirectory[];		// TEXT("NameIsDirectory")
extern const TCHAR g_cbNameIsFile[];			// TEXT("NameIsFile")
extern const TCHAR g_cbReadWrite[];				// TEXT("ReadWrite")

extern const TCHAR g_cbFilterString[];			// TEXT("%s (*.%s)|*.%s|")
extern const TCHAR g_cbGDBVersion[];			// TEXT("1.0");
extern const TCHAR g_cbGeoMediaClass[];			// TEXT("Access.GDatabase");

extern const TCHAR g_cbMyProgID[];				// _T("TRiASGDO.DBEngine.1")
//extern const TCHAR g_cbMyVersion[];				// 

// Fehlermeldungen bei schweren Fehlern
extern const TCHAR g_cbNoMemory[];				// TEXT("Kein Speicherplatz!");

// sonstiges
extern const OLECHAR g_cbInternal[];			// TEXT("__Internal__")
extern const TCHAR g_cbErrInternal[];			// TEXT("<internal Error>")

extern const TCHAR g_cbVersionFormat[];			// TEXT("%s.%s.%s");
extern const TCHAR g_cbTRiASDefaultName[];		// TEXT("TRiAS®");
extern const TCHAR g_cbNil[];					// TEXT("");
extern const TCHAR g_cbSpace[];					// TEXT(" ");

extern const TCHAR g_cbCSFFileKey[];			// TEXT("CSFFILENAME")
extern const OLECHAR g_cbCollatePattern[];		// TEXT(";%1=%2");

extern const OLECHAR g_cbObjectsMap[];			// L"ObjectsMap";
extern const OLECHAR g_cbObjectMap[];			// L"ObjectMap";
extern const OLECHAR g_cbFeatureMap[];			// L"FeatureMap";
extern const OLECHAR g_cbGenericMap[];			// L"GenericMap";
extern const OLECHAR g_cbMetaDataMap[];			// L"MetaDataMap"
extern const OLECHAR g_cbDatabaseContainer[];	// L"DatabaseContainer"
extern const OLECHAR g_cbTRiASCSService[];		// L"TRiASCSService"
extern const OLECHAR g_cbGeometry[];			// L"Geometry";
extern const OLECHAR g_cbObjectHandleIsValid[];	// L"ObjectHandleIsValid";
extern const OLECHAR g_cbGDODataSource[];		// L"GDODataSource";
extern const OLECHAR g_cbCSSGuid[];				// L"CSSGuid";

extern const TCHAR g_cbLBracket[];				// = _T("[");
extern const TCHAR g_cbRBracket[];				// = _T("]");

extern const OLECHAR g_cbColonW[];				// = L":";
extern const OLECHAR g_cbMkDelW[];				// = L"!";

extern const OLECHAR g_cbMkObjectsDefW[];		// = L"MkObjectsDef";
extern const OLECHAR g_cbMkObjectDefW[];		// = L"MkObjectDef";
extern const OLECHAR g_cbMkFeatureW[];			// = L"MkFeature";

extern const TCHAR	g_cbMkObjectsDef[];			// = _T("MkObjectsDef");
extern const TCHAR	g_cbMkObjectDef[];			// = _T("MkObjectDef");
extern const TCHAR	g_cbMkFeature[];			// = _T("MkFeature");

extern const OLECHAR g_SEARCHCOMMAND_IntersectsWindow[];	// =L"SEARCHCOMMAND_IntersectsWindow";

extern const CComBSTR g_bstrNil;

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
extern TCHAR g_cbTRiAS[_MAX_PATH];

#endif // !defined(_STRINGS_H__978C1EC9_2F3C_11d1_969F_00A024D6F582__INCLUDED_)
