///////////////////////////////////////////////////////////////////////////
// Stringkonstanten
// File: Strings.cpp

#include "StdAfx.h"

///////////////////////////////////////////////////////////////////////////////
// Datenserver-RegistryKeys
const TCHAR g_cbImportFormat[] = TEXT("ImportFormat");
const TCHAR g_cbDescription[] = TEXT("Description");
const TCHAR g_cbFileExtension[] = TEXT("FileExtension");

const TCHAR g_cbDatabaseClass[] = TEXT("DatabaseClass");
const TCHAR g_cbNameDescription[] = TEXT("NameDescription");
const TCHAR g_cbDefaultExtension[] = TEXT("DefaultExtension");
const TCHAR g_cbLongName[] = TEXT("LongName");
const TCHAR g_cbShortName[] = TEXT("ShortName");
const TCHAR g_cbNameIsDirectory[] = TEXT("NameIsDirectory");
const TCHAR g_cbNameIsFile[] = TEXT("NameIsFile");
const TCHAR g_cbReadWrite[] = TEXT("ReadWrite");

const TCHAR g_cbFilterString[] = TEXT("%s (*.%s)|*.%s|");
const TCHAR g_cbGDBVersion[] = TEXT("1.0");
const TCHAR g_cbGeoMediaClass[] = TEXT("Access.GDatabase");

// Fehlermeldungen bei schweren Fehlern
const TCHAR g_cbNoMemory[] = TEXT("Kein Speicherplatz!");

// sonstiges
const TCHAR g_cbVersionFormat[] = TEXT("%s.%s.%s");
const TCHAR g_cbTRiASDefaultName[] = TEXT("TRiAS®");
const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbSpace[] = TEXT(" ");

const TCHAR g_cbCollatePattern[] = TEXT(";%1=%2");
const TCHAR g_cbProgID[] = TEXT("PROGID");
const TCHAR g_cbImpAnsiOEM[] = TEXT("DOS-Charset");
const TCHAR g_cbImpFeatures[] = TEXT("ImportFeatures");
const TCHAR g_cbImpGeometry[] = TEXT("ImportGeometry");
const TCHAR g_cbImpRelations[] = TEXT("ImportRelations");
const TCHAR g_cbImpVisualis[] = TEXT("ImportVisualisation");

const TCHAR g_cbImpYes[] = TEXT("1");

const TCHAR g_cbCanImpAnsiOEM[] = TEXT("CanAnsiOEM");
const TCHAR g_cbCanImpFeat[] = TEXT("CanImportFeatures");
const TCHAR g_cbCanImpGeom[] = TEXT("CanImportGeometry");
const TCHAR g_cbCanImpRela[] = TEXT("CanImportRelations");
const TCHAR g_cbCanImpVisu[] = TEXT("CanImportVisualisation");
const TCHAR g_cbOptImpAnsiOEM[] = TEXT("OptAnsiOEM");
const TCHAR g_cbOptImpFeat[] = TEXT("OptImportFeatures");
const TCHAR g_cbOptImpGeom[] = TEXT("OptImportGeometry");
const TCHAR g_cbOptImpRela[] = TEXT("OptImportRelations");
const TCHAR g_cbOptImpVisu[] = TEXT("OptImportVisualisation");
const TCHAR g_cbMultipleFiles[] = TEXT("MultipleFiles");
const TCHAR g_cbShouldConfig[] = TEXT("ShouldConfig");

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)

TCHAR g_cbTRiAS[_MAX_PATH];
