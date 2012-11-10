///////////////////////////////////////////////////////////////////////////
// Stringkonstanten
// File: Strings.h

#if !defined(_STRINGS_H__7C8CB9C3_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _STRINGS_H__7C8CB9C3_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Initialisierungen
extern const TCHAR g_cbTriasExtensionMessage[];		// TEXT("TriasExtensionMessage");
extern const TCHAR g_cbTriasNotification[];			// TEXT("TriasNotification");
extern const TCHAR g_cbTriasCPPExtensionMessage[];	// TEXT("TriasCPPExtensionMessage");

extern const TCHAR g_cbTRiASProject[];				// TEXT("TRiAS® 3.0 Projekt Workspace");
extern const TCHAR g_cbTRiASConnections[];			// TEXT("TRiAS® 1.0 Database Connections");
extern const TCHAR g_cbTRiASViews[];				// TEXT("TRiAS® 1.0 Project Views");
extern const TCHAR g_cbTRiASQueryCollection[];		// TEXT("TRiAS® 1.0 Project QueryDefs");
extern const TCHAR g_cbTRiASConnectionFilters[];	// TEXT("TRiAS® 1.0 Project Connectionfilters");

extern const OLECHAR g_cbConnections[];				// L"TRiASDB_Connections";
extern const OLECHAR g_cbViews[];					// L"TRiASDB_Views";
extern const OLECHAR g_cbQueries[];					// L"TRiASDB_Queries";
extern const OLECHAR g_cbObjects[];					// L"TRiASDB_Objects";
extern const OLECHAR g_cbConnFilts[];				// L"TRiASDB_ConnectionFilters";

extern const TCHAR g_cbProjectData[];				// TEXT("TRiASDB_ProjectData");
extern const TCHAR g_cbProjectDataBase[];			// TEXT("TRiASDB_ProjectDataBase");
extern const TCHAR g_cbObjectsData[];				// TEXT("TRiASDB_ObjectsData");

extern const TCHAR g_cbMetaData[];					// TEXT("Beschreibungsdaten");
extern const TCHAR g_cbCompatibility16[];			// TEXT("Compatibility16");

///////////////////////////////////////////////////////////////////////////////
// Fehlermeldungen bei schweren Fehlern
extern const TCHAR g_cbNoMemory[];					// TEXT("Kein Speicherplatz!");

///////////////////////////////////////////////////////////////////////////////
// sonstiges
extern const TCHAR g_cbVersionFormat[];				// TEXT("%s.%s.%s");
extern const TCHAR g_cbTRiASDefaultName[];			// TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
extern const TCHAR g_cbInterTRiASDefaultName[];		// TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400
extern const TCHAR g_cbCollatePattern[];			// TEXT(";%1=%2");
extern const TCHAR g_cbLangId[];					// TEXT("LANGID");
extern const TCHAR g_cbCompatible[];				// TEXT("COMPATIBLE");
extern const TCHAR g_cbCompressed[];				// TEXT("COMPRESSED");
extern const TCHAR g_cbIdentBase[];					// TEXT("IDENTBASE");
extern const TCHAR g_cbSource[];					// TEXT(";PROGID=");
extern const TCHAR g_cbDefPropName[];				// TEXT("Property(0x%08lx)");
extern const TCHAR g_cbSysProperty[];				// TEXT("Property %08lx");
extern const TCHAR g_cbProgID[];					// TEXT("PROGID");
extern const OLECHAR g_cbFile[];					// L"File:";
extern const OLECHAR g_cbStorage[];					// L"Storage:";
extern const OLECHAR g_cbConnect[];					// L"Connect:";

extern const TCHAR g_cbIdentsDB[];					// TEXT("IDENTSDB");
extern const TCHAR g_cbPbdName[];					// TEXT("PBD-NAME");
extern const TCHAR g_cbCompatibilityMode[];			// TEXT ("CompatibleWithV");

extern const TCHAR g_cbNil[];						// TEXT("");
extern const TCHAR g_cbDel[];						// TEXT("\\");
extern const TCHAR g_cbColon[];						// TEXT(":");
extern const TCHAR g_cbComma[];						// TEXT(",");
extern const TCHAR g_cbLBracket[];					// TEXT("[");
extern const TCHAR g_cbRBracket[];					// TEXT("]");
extern const TCHAR g_cbUnderScore[];				// TEXT("_");

extern const OLECHAR g_cbMkDel[];					// L"!";
extern const OLECHAR g_cbMkWild[];					// L"\\";

///////////////////////////////////////////////////////////////////////////////
// DateiErweiterungen
extern const TCHAR g_cbRis[];						// TEXT("ris");
extern const TCHAR g_cbRiw[];						// TEXT("riw");
extern const TCHAR g_cbPbd[];						// TEXT("pbd");
extern const TCHAR g_cbIni[];						// TEXT("ini");

///////////////////////////////////////////////////////////////////////////////
// diverse ProgIDs
extern const OLECHAR g_cbTRiASProject120[];			// L"TRiAS.Document.1"
extern const OLECHAR g_cbTRiASProject130[];			// L"TRiAS.Document.2"
extern const OLECHAR g_cbTRiASProject3[];			// L"TRiAS.Document.3";

extern const TCHAR g_cbMetaProject130[];			// TEXT("TRiAS.MetaDocument.2");
extern const TCHAR g_cbTRiASDBProject[];			// TEXT("TRiASDB.Project.2");
extern const TCHAR g_cbTRiASObjects[];				// TEXT("TRiASDB.TRiASObjects.1");

///////////////////////////////////////////////////////////////////////////////
// Temp-Verzeichnisse
extern const TCHAR g_cbTmpPrefix[];					// TEXT("Tmp");

///////////////////////////////////////////////////////////////////////////////
// Properties
extern const OLECHAR g_cbCTFService[];				// L"CTFService";
extern const OLECHAR g_cbCoordExternPipe[];			// L"CoordExternPipe";
extern const OLECHAR g_cbTRiASCSService[];			// L"TRiASCSService";
extern const OLECHAR g_cbTRiASCSTransform[];		// L"TRiASCSTransform";
extern const OLECHAR g_cbTRiASConnectFilter[];		// L"TRiASConnectFilter";
extern const OLECHAR g_cbStgService[];				// L"StgService";
extern const OLECHAR g_cbObjectStgService[];		// L"ObjectStgService";
extern const OLECHAR g_cbSysAdmin[];				// L"SystemAdministration";
extern const OLECHAR g_cbObjectsMap[];				// L"ObjectsMap";
extern const OLECHAR g_cbObjectMap[];				// L"ObjectMap";
extern const OLECHAR g_cbFeatureMap[];				// L"FeatureMap";
extern const OLECHAR g_cbGenericMap[];				// L"GenericMap";
extern const OLECHAR g_cbIdentBaseHdr[];			// L"IdentBase";
extern const OLECHAR g_cbTRiASDataSource[];			// L"TRiASDataSource";
extern const OLECHAR g_cbActualPath[];				// L"ActualPath";
extern const OLECHAR g_cbGeometry[];				// L"Geometry";
extern const OLECHAR g_cbObjGuid[];					// L"__ObjGuid__";
extern const OLECHAR g_cbDefaultGeometry[];			// L"DefaultGeometry";
extern const OLECHAR g_cbPrimaryKey[];				// L"PrimaryKey";
extern const OLECHAR g_cbGlobal[];					// L"Global";
extern const OLECHAR g_cbLastObjectsCookie[];		// L"LastObjsCookie";
extern const OLECHAR g_cbLastObjectCookie[];		// L"LastObjCookie";
extern const OLECHAR g_cbLastFeatCookie[];			// L"LastFeatCookie";
extern const OLECHAR g_cbViewBMasstab[];			// L"BMasstabMCode";
extern const OLECHAR g_cbViewCaption[];				// L"CaptionMCode";
extern const OLECHAR g_cbSichtContMCode[];			// L"SichtContMCode";
extern const OLECHAR g_cbNextSystemMCode[];			// L"NextSystemMCode";
extern const OLECHAR g_cbObjVisInfoMCode[];			// L"ObjVisInfoMCode";
extern const OLECHAR g_cbScaleViewPMCode[];			// L"ScaleViewPMCode";
extern const OLECHAR g_cbScaleViewLMCode[];			// L"ScaleViewLMCode";
extern const OLECHAR g_cbScaleViewAMCode[];			// L"ScaleViewAMCode";
extern const OLECHAR g_cbScaleViewTMCode[];			// L"ScaleViewTMCode";
extern const OLECHAR g_cbLegendInfoMCode[];			// L"LegendInfoMCode";
extern const OLECHAR g_cbSimpleFeatures[];			// L"SimpleFeatures";
extern const OLECHAR g_cbHasSimpleFeatures[];		// L"HasSimpleFeatures";
extern const OLECHAR g_cbSimpleGeoFeatures[];		// L"SimpleGeoFeatures";
extern const OLECHAR g_cbHasSimpleGeoFeatures[];	// L"HasSimpleGeoFeatures";
extern const OLECHAR g_cbMetaDataMap[];				// L"MetaDataMap";
extern const OLECHAR g_cbNameIsDefault[];			// L"NameIsDefault";
extern const OLECHAR g_cbSavingProject[];			// L"SavingProject";
extern const OLECHAR g_cbSavingProjectAs[];			// L"SavingProjectAs";
extern const OLECHAR g_cbClosingProject[];			// L"ClosingProject";
extern const OLECHAR g_cbObjectHandleIsValid[];		// L"ObjectHandleIsValid";
extern const OLECHAR g_cbDataSourceGuid[];			// L"DataSourceGuid";

extern const TCHAR g_cbDefault[];					// TEXT("DEFAULT");
extern const TCHAR g_cbOldName[];					// TEXT("OldName");
extern const TCHAR g_cbCoordTransform[];			// TEXT("CoordTransform  ");

extern const TCHAR g_cbCLSID[];						// TEXT("CLSID");

///////////////////////////////////////////////////////////////////////////////
// Einträge in DB-Ini
extern const TCHAR g_cbSights[];					// TEXT("Sights");
extern const TCHAR g_cbStandard[];					// TEXT("Standard");

///////////////////////////////////////////////////////////////////////////////
// DataServerRegEntry
extern const TCHAR g_cbTRiASDB[];					// TEXT("TRiASDB");
extern const TCHAR g_cbDescription[];				// TEXT("Description");

extern const TCHAR g_cbDatabaseClass[];				// TEXT("DatabaseClass");
extern const TCHAR g_cbNameDescription[];			// TEXT("NameDescription");
extern const TCHAR g_cbDefaultExtension[];			// TEXT("DefaultExtension");
extern const TCHAR g_cbLongName[];					// TEXT("LongName");
extern const TCHAR g_cbShortName[];					// TEXT("ShortName");
extern const TCHAR g_cbNameIsDirectory[];			// TEXT("NameIsDirectory");
extern const TCHAR g_cbNameIsFile[];				// TEXT("NameIsFile");
extern const TCHAR g_cbNameIsSubStorage[];			// TEXT("NameIsSubStorage");
extern const TCHAR g_cbReadWrite[];					// TEXT("ReadWrite");
extern const TCHAR g_cbFilterString[];				// TEXT("FilterString");
extern const TCHAR g_cbVersion[];					// TEXT("Version");
extern const TCHAR g_cbSourceDescription[];			// TEXT("SourceDescription");
extern const TCHAR g_cbSourceStringUsed[];			// TEXT("SourceStringUsed");
extern const TCHAR g_cbRestrictInstances[];			// TEXT("RestrictInstances");
extern const TCHAR g_cbTempName[];					// TEXT("TempName");
extern const TCHAR g_cbLastDirUsed[];				// TEXT("LastDirUsed");
extern const TCHAR g_cbToolboxBitmap32[];			// TEXT("ToolboxBitmap32");
extern const TCHAR g_cbMultipleFiles[];				// TEXT("MultipleFiles");
extern const TCHAR g_cbOpenWizExt[];				// TEXT("OpenWizPages");
extern const TCHAR g_cbNeedsCoordSysNew[];			// TEXT("NeedsCoordSysNew");
extern const TCHAR g_cbNeedsCoordSysExisting[];		// TEXT("NeedsCoordSysExisting");
extern const TCHAR g_cbReconnectDialog[];			// TEXT("ReconnectDialog");
extern const TCHAR g_cbCreateDatabase[];			// TEXT("CreateDatabase");

///////////////////////////////////////////////////////////////////////////////
// Monikersupport
extern const TCHAR g_cbMkObjectsDef[];				// TEXT("MkObjectsDef");
extern const TCHAR g_cbMkObjectDef[];				// TEXT("MkObjectDef");
extern const TCHAR g_cbMkConnection[];				// TEXT("MkConnection");
extern const TCHAR g_cbMkProject[];					// TEXT("MkProject");
extern const TCHAR g_cbMkFeature[];					// TEXT("MkFeature");

/////////////////////////////////////////////////////////////////////////////
// SuchPattern für Objektklassenschlüssel
extern const TCHAR g_cbOKS[];						// TEXT("\\(\\[[[:xdigit:]]+\\]\\)\\|\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]]?.*\\)");	// TEXT("0123456789abcdefABCDEF");

///////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
extern const wchar_t g_cbBESSELGK[];				// L"BESSELGK";
extern const wchar_t g_cbKRASSGK[];					// L"KRASSGK";
extern const wchar_t g_cbETRSGK[];					// L"ETRSGK";
extern const wchar_t g_cbBEGEOD[];					// L"BEGEOD";
extern const wchar_t g_cbKRGEOD[];					// L"KRGEOD";
extern const wchar_t g_cbETRSGEOD[];				// L"ETRSGEOD";
extern const wchar_t g_cbCassiniSoldner[];			// L"BESSELESO";

extern const wchar_t g_cbCoordMeridian[];			// L"CoordMeridian"
extern const wchar_t g_cbCoordStrBreite[];			// L"CoordStrBreite"
extern const wchar_t g_cbCoordLatitude[];			// L"CoordLatitude";
extern const wchar_t g_cbCoordFalseX[];				// L"CoordFalseX";
extern const wchar_t g_cbCoordFalseY[];				// L"CoordFalseY";
extern const wchar_t g_cbCoordTransGUID[];			// L"CoordTransGUID";
extern const wchar_t g_cbCoordScaleAtOrig[];		// L"CoordScaleAtOrig";
extern const wchar_t g_cbCoordAutoMeridian[];		// L"CoordAutoZone";
extern const wchar_t g_cbCoordDHDNType[];			// L"CoordDHDNType";
extern const wchar_t g_cbCoordTcfName[];			// L"CoordTcfName";

extern const wchar_t g_cbActLookupWindow[];			// L"ActLookupWindow";


#if defined(_USE_PERFMON_COUNTERS)

///////////////////////////////////////////////////////////////////////////////
// Stringkonstanten für PerformanceCounter
extern const wchar_t g_cbPerfCtx[];					// L"TRiASDB";			// globaler PerfCtxName

#endif // defined(_USE_PERFMON_COUNTERS)

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
extern TCHAR g_cbTRiAS[_MAX_PATH];
extern TCHAR g_cbProjects[_MAX_PATH];

#endif // !defined(_STRINGS_H__7C8CB9C3_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
