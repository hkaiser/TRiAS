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
extern const TCHAR g_cbImportFormat[];			// TEXT("ImportFormat");
extern const TCHAR g_cbDescription[];			// TEXT("Description");
extern const TCHAR g_cbFileExtension[];			// TEXT("FileExtension");

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

// Fehlermeldungen bei schweren Fehlern
extern const TCHAR g_cbNoMemory[];				// TEXT("Kein Speicherplatz!");

// sonstiges
extern const TCHAR g_cbVersionFormat[];			// TEXT("%s.%s.%s");
extern const TCHAR g_cbTRiASDefaultName[];		// TEXT("TRiAS®");
extern const TCHAR g_cbNil[];					// TEXT("");
extern const TCHAR g_cbSpace[];					// TEXT(" ");

extern const TCHAR g_cbCollatePattern[];		// TEXT(";%1=%2");
extern const TCHAR g_cbProgID[];				// TEXT("ProgID");
extern const TCHAR g_cbImpAnsiOEM[];			// TEXT("DOS-Charset");
extern const TCHAR g_cbImpFeatures[];			// TEXT("ImportFeatures");
extern const TCHAR g_cbImpGeometry[];			// TEXT("ImportGeometry");
extern const TCHAR g_cbImpRelations[];			// TEXT("ImportRelations");
extern const TCHAR g_cbImpVisualis[];			// TEXT("ImportVisualization");

extern const TCHAR g_cbImpYes[];				// TEXT("1");

extern const TCHAR g_cbCanImpAnsiOEM[];			// TEXT("CanAnsiOEM");
extern const TCHAR g_cbCanImpFeat[];			// TEXT("CanImportFeatures");
extern const TCHAR g_cbCanImpGeom[];			// TEXT("CanImportGeometry");
extern const TCHAR g_cbCanImpRela[];			// TEXT("CanImportRelations");
extern const TCHAR g_cbCanImpVisu[];			// TEXT("CanImportVisualisation");
extern const TCHAR g_cbOptImpAnsiOEM[];			// TEXT("OptAnsiOEM");
extern const TCHAR g_cbOptImpFeat[];			// TEXT("OptImportFeatures");
extern const TCHAR g_cbOptImpGeom[];			// TEXT("OptImportGeometry");
extern const TCHAR g_cbOptImpRela[];			// TEXT("OptImportRelations");
extern const TCHAR g_cbOptImpVisu[];			// TEXT("OptImportVisualisation");
extern const TCHAR g_cbMultipleFiles[];			// TEXT("MultipleFiles");
extern const TCHAR g_cbShouldConfig[];			// TEXT("ShouldConfig");

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
extern TCHAR g_cbTRiAS[_MAX_PATH];

#endif // !defined(_STRINGS_H__978C1EC9_2F3C_11d1_969F_00A024D6F582__INCLUDED_)
