///////////////////////////////////////////////////////////////////////////
// Stringkonstanten
// File: Strings.cpp

#include "StdAfx.h"
#include "strings.h"

///////////////////////////////////////////////////////////////////////////////
// Datenserver-RegistryKeys

const OLECHAR g_cbCollatePattern[] = L";%1=%2";

const TCHAR g_cbDatabaseClass[] = TEXT("DatabaseClass");
const TCHAR g_cbNameDescription[] = TEXT("NameDescription");
const TCHAR g_cbDefaultExtension[] = TEXT("DefaultExtension");
const TCHAR g_cbLongName[] = TEXT("LongName");
const TCHAR g_cbShortName[] = TEXT("ShortName");
const TCHAR g_cbNameIsDirectory[] = TEXT("NameIsDirectory");
const TCHAR g_cbNameIsFile[] = TEXT("NameIsFile");
const TCHAR g_cbReadWrite[] = TEXT("ReadWrite");

const TCHAR g_cbFilterString[] = TEXT("%s (*.%s)|*.%s|");

const TCHAR	g_cbMyProgID[] = _T("TRiASGDO.DBEngine.1");

// Fehlermeldungen bei schweren Fehlern
const TCHAR g_cbNoMemory[] = TEXT("Kein Speicherplatz!");
const TCHAR g_cbErrInternal[] = TEXT("<internal Error>");

// sonstiges
const OLECHAR g_cbInternal[] = L"__Internal__";

const TCHAR g_cbVersionFormat[] = TEXT("%s.%s.%s");
const TCHAR g_cbTRiASDefaultName[] = TEXT("TRiAS®");
const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbSpace[] = TEXT(" ");

const TCHAR g_cbCSFFileKey[] = TEXT("CSFFILENAME");

const OLECHAR g_cbObjectsMap[] = L"ObjectsMap";
const OLECHAR g_cbObjectMap[] = L"ObjectMap";
const OLECHAR g_cbFeatureMap[] = L"FeatureMap";
const OLECHAR g_cbGenericMap[] = L"GenericMap";
const OLECHAR g_cbMetaDataMap[] = L"MetaDataMap";
const OLECHAR g_cbDatabaseContainer[] = L"DatabaseContainer";
const OLECHAR g_cbGeometry[] = L"Geometry";
const OLECHAR g_cbTRiASCSService[] = L"TRiASCSService";
const OLECHAR g_cbObjectHandleIsValid[] = L"ObjectHandleIsValid";
const OLECHAR g_cbGDODataSource[] = L"GDODataSource";
const OLECHAR g_cbCSSGuid[] = L"CSSGuid";

const TCHAR g_cbLBracket[] = _T("[");
const TCHAR g_cbRBracket[] = _T("]");

///////////////////////////////////////////////////////////////////////////////
// Monikersupport
const OLECHAR g_cbColonW[] = L":";
const OLECHAR g_cbMkDelW[] = L"!";

const OLECHAR g_cbMkObjectsDefW[] = L"MkObjectsDef";
const OLECHAR g_cbMkObjectDefW[] = L"MkObjectDef";
const OLECHAR g_cbMkFeatureW[] = L"MkFeature";

const TCHAR	g_cbMkObjectsDef[] = _T("MkObjectsDef");
const TCHAR	g_cbMkObjectDef[] = _T("MkObjectDef");
const TCHAR	g_cbMkFeature[] = _T("MkFeature");

const OLECHAR g_SEARCHCOMMAND_IntersectsWindow[] = L"IntersectsWindow";

const CComBSTR g_bstrNil(g_cbNil);

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)

TCHAR g_cbTRiAS[_MAX_PATH];
