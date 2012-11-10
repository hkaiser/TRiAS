// Stringkonstanten
// File: Strings.cpp

#include "StdAfx.h"
#include "Strings.h"

///////////////////////////////////////////////////////////////////////////////
// Initialisierungen
const TCHAR g_cbTriasExtensionMessage[] = TEXT("TriasExtensionMessage");
const TCHAR g_cbTriasNotification[] = TEXT("TriasNotification");
const TCHAR g_cbTriasCPPExtensionMessage[] = TEXT("TriasCPPExtensionMessage");

const TCHAR g_cbTRiASProject[] = TEXT("TRiAS® 3.0 Projekt Workspace");
const TCHAR g_cbTRiASConnections[] = TEXT("TRiAS® 1.0 Database Connections");
const TCHAR g_cbTRiASViews[] = TEXT("TRiAS® 1.0 Project Views");
const TCHAR g_cbTRiASQueryCollection[] = TEXT("TRiAS® 1.0 Project QueryDefs");
const TCHAR g_cbTRiASConnectionFilters[] = TEXT("TRiAS® 1.0 Project Connectionfilters");

const OLECHAR g_cbConnections[] = L"TRiASDB_Connections";
const OLECHAR g_cbViews[] = L"TRiASDB_Views";
const OLECHAR g_cbQueries[] = L"TRiASDB_Queries";
const OLECHAR g_cbObjects[] = L"TRiASDB_Objects";
const OLECHAR g_cbConnFilts[] = L"TRiASDB_ConnectionFilters";

const TCHAR g_cbProjectData[] = TEXT("TRiASDB_ProjectData");
const TCHAR g_cbProjectDataBase[] = TEXT("TRiASDB_ProjectDataBase");
const TCHAR g_cbObjectsData[] = TEXT("TRiASDB_ObjectsData");

const TCHAR g_cbMetaData[] = TEXT("Beschreibungsdaten");
const TCHAR g_cbCompatibility16[] = TEXT("Compatibility16");

///////////////////////////////////////////////////////////////////////////////
// Fehlermeldungen bei schweren Fehlern
const TCHAR g_cbNoMemory[] = TEXT("Kein Speicherplatz!");

///////////////////////////////////////////////////////////////////////////////
// sonstiges
const TCHAR g_cbVersionFormat[] = TEXT("%s.%s.%s");
const TCHAR g_cbTRiASDefaultName[] = TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
const TCHAR g_cbInterTRiASDefaultName[] = TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400
const TCHAR g_cbCollatePattern[] = TEXT(";%1=%2");
const TCHAR g_cbLangId[] = TEXT("LANGID");
const TCHAR g_cbCompatible[] = TEXT("COMPATIBLE");
const TCHAR g_cbCompressed[] = TEXT("COMPRESSED");
const TCHAR g_cbSource[] = TEXT(";PROGID=");
const TCHAR g_cbDefPropName[] = TEXT("Property(0x%08lx)");
const TCHAR g_cbSysProperty[] = TEXT("Property %08ld");
const TCHAR g_cbProgID[] = TEXT("PROGID");
const OLECHAR g_cbFile[] = L"File:";
const OLECHAR g_cbStorage[] = L"Storage:";
const OLECHAR g_cbConnect[] = L"Connect:";

const TCHAR g_cbIdentsDB[] = TEXT("IDENTSDB");
const TCHAR g_cbPbdName[] = TEXT("PBD-NAME");
const TCHAR g_cbCompatibilityMode[] = TEXT ("CompatibleWithV");

const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbDel[] = TEXT("\\");
const TCHAR g_cbColon[] = TEXT(":");
const TCHAR g_cbComma[] = TEXT(",");
const TCHAR g_cbLBracket[] = TEXT("[");
const TCHAR g_cbRBracket[] = TEXT("]");
const TCHAR g_cbUnderScore[] = TEXT("_");

const OLECHAR g_cbMkDel[] = L"!";
const OLECHAR g_cbMkWild[] = L"\\";

///////////////////////////////////////////////////////////////////////////////
// DateiErweiterungen
const TCHAR g_cbRis[] = TEXT("ris");
const TCHAR g_cbRiw[] = TEXT("riw");
const TCHAR g_cbPbd[] = TEXT("pbd");
const TCHAR g_cbIni[] = TEXT("ini");

///////////////////////////////////////////////////////////////////////////////
// diverse ProgIDs
const OLECHAR g_cbTRiASProject120[] = L"TRiAS.Document.1";
const OLECHAR g_cbTRiASProject130[] = L"TRiAS.Document.2";
const OLECHAR g_cbTRiASProject3[] = L"TRiAS.Document.3";

const TCHAR g_cbMetaProject130[] = TEXT("TRiAS.MetaDocument.2");
const TCHAR g_cbTRiASDBProject[] = TEXT("TRiASDB.Project.2");
const TCHAR g_cbTRiASObjects[] = TEXT("TRiASDB.TRiASObjects.1");

///////////////////////////////////////////////////////////////////////////////
// Temp-Verzeichnisse
const TCHAR g_cbTmpPrefix[] = TEXT("Tmp");

///////////////////////////////////////////////////////////////////////////////
// Properties
const OLECHAR g_cbCTFService[] = L"CTFService";
const OLECHAR g_cbCoordExternPipe[] = L"CoordExternPipe";
const OLECHAR g_cbTRiASCSService[] = L"TRiASCSService";
const OLECHAR g_cbTRiASCSTransform[] = L"TRiASCSTransform";
const OLECHAR g_cbTRiASConnectFilter[] = L"TRiASConnectFilter";
const OLECHAR g_cbStgService[] = L"StgService";
const OLECHAR g_cbObjectStgService[] = L"ObjectStgService";
const OLECHAR g_cbSysAdmin[] = L"SystemAdministration";
const OLECHAR g_cbObjectsMap[] = L"ObjectsMap";
const OLECHAR g_cbObjectMap[] = L"ObjectMap";
const OLECHAR g_cbFeatureMap[] = L"FeatureMap";
const OLECHAR g_cbGenericMap[] = L"GenericMap";
const OLECHAR g_cbIdentBaseHdr[] = L"IdentBase";
const OLECHAR g_cbTRiASDataSource[] = L"TRiASDataSource";
const OLECHAR g_cbActualPath[] = L"ActualPath";	
const OLECHAR g_cbGeometry[] = L"Geometry";
const OLECHAR g_cbObjGuid[] = L"__ObjGuid__";
const OLECHAR g_cbDefaultGeometry[] = L"DefaultGeometry";
const OLECHAR g_cbPrimaryKey[] = L"PrimaryKey";
const OLECHAR g_cbGlobal[] = L"Global";
const OLECHAR g_cbLastObjectsCookie[] = L"LastObjsCookie";
const OLECHAR g_cbLastObjectCookie[] = L"LastObjCookie";
const OLECHAR g_cbLastFeatCookie[] = L"LastFeatCookie";
const OLECHAR g_cbViewBMasstab[] = L"BMasstabMCode";
const OLECHAR g_cbViewCaption[] = L"CaptionMCode";
const OLECHAR g_cbSichtContMCode[] = L"SichtContMCode";
const OLECHAR g_cbNextSystemMCode[] = L"NextSystemMCode";
const OLECHAR g_cbObjVisInfoMCode[] = L"ObjVisInfoMCode";
const OLECHAR g_cbScaleViewPMCode[] = L"ScaleViewPMCode";
const OLECHAR g_cbScaleViewLMCode[] = L"ScaleViewLMCode";
const OLECHAR g_cbScaleViewAMCode[] = L"ScaleViewAMCode";
const OLECHAR g_cbScaleViewTMCode[] = L"ScaleViewTMCode";
const OLECHAR g_cbLegendInfoMCode[] = L"LegendInfoMCode";
const OLECHAR g_cbSimpleFeatures[] = L"SimpleFeatures";
const OLECHAR g_cbHasSimpleFeatures[] = L"HasSimpleFeatures";
const OLECHAR g_cbSimpleGeoFeatures[] = L"SimpleGeoFeatures";
const OLECHAR g_cbHasSimpleGeoFeatures[] = L"HasSimpleGeoFeatures";
const OLECHAR g_cbMetaDataMap[] = L"MetaDataMap";
const OLECHAR g_cbNameIsDefault[] = L"NameIsDefault";
const OLECHAR g_cbSavingProject[] = L"SavingProject";
const OLECHAR g_cbSavingProjectAs[] = L"SavingProjectAs";
const OLECHAR g_cbClosingProject[] = L"ClosingProject";
const OLECHAR g_cbObjectHandleIsValid[] = L"ObjectHandleIsValid";
const OLECHAR g_cbDataSourceGuid[] = L"DataSourceGuid";

const TCHAR g_cbDefault[] = TEXT("DEFAULT");
const TCHAR g_cbOldName[] = TEXT("OldName");
const TCHAR g_cbCoordTransform[] = TEXT("CoordTransform  ");

const TCHAR g_cbCLSID[] = TEXT("CLSID");

///////////////////////////////////////////////////////////////////////////////
// Einträge in DB-Ini
const TCHAR g_cbSights[] = TEXT("Sights");
const TCHAR g_cbStandard[] = TEXT("Standard");

///////////////////////////////////////////////////////////////////////////////
// DataServerRegEntry
const TCHAR g_cbTRiASDB[] = TEXT("TRiASDB");
const TCHAR g_cbDescription[] = TEXT("Description");

const TCHAR g_cbDatabaseClass[] = TEXT("DatabaseClass");
const TCHAR g_cbNameDescription[] = TEXT("NameDescription");
const TCHAR g_cbDefaultExtension[] = TEXT("DefaultExtension");
const TCHAR g_cbLongName[] = TEXT("LongName");
const TCHAR g_cbShortName[] = TEXT("ShortName");
const TCHAR g_cbNameIsDirectory[] = TEXT("NameIsDirectory");
const TCHAR g_cbNameIsFile[] = TEXT("NameIsFile");
const TCHAR g_cbNameIsSubStorage[] = TEXT("NameIsSubStorage");
const TCHAR g_cbMultipleFiles[] = TEXT("MultipleFiles");
const TCHAR g_cbReadWrite[] = TEXT("ReadWrite");
const TCHAR g_cbFilterString[] = TEXT("FilterString");
const TCHAR g_cbVersion[] = TEXT("Version");
const TCHAR g_cbSourceDescription[] = TEXT("SourceDescription");
const TCHAR g_cbSourceStringUsed[] = TEXT("SourceStringUsed");
const TCHAR g_cbRestrictInstances[] = TEXT("RestrictInstances");
const TCHAR g_cbTempName[] = TEXT("TempName");
const TCHAR g_cbLastDirUsed[] = TEXT("LastDirUsed");
const TCHAR g_cbToolboxBitmap32[] = TEXT("ToolboxBitmap32");
const TCHAR g_cbOpenWizExt[] = TEXT("OpenWizPages");
const TCHAR g_cbNeedsCoordSysNew[] = TEXT("NeedsCoordSysNew");
const TCHAR g_cbNeedsCoordSysExisting[] = TEXT("NeedsCoordSysExisting");
const TCHAR g_cbReconnectDialog[] = TEXT("ReconnectDialog");
const TCHAR g_cbCreateDatabase[] = TEXT("CreateDatabase");

///////////////////////////////////////////////////////////////////////////////
// Monikersupport
const TCHAR g_cbMkObjectsDef[] = TEXT("MkObjectsDef");
const TCHAR g_cbMkObjectDef[] = TEXT("MkObjectDef");
const TCHAR g_cbMkConnection[] = TEXT("MkConnection");
const TCHAR g_cbMkProject[] = TEXT("MkProject");
const TCHAR g_cbMkFeature[] = TEXT("MkFeature");

/////////////////////////////////////////////////////////////////////////////
// SuchPattern für Objektklassenschlüssel
const TCHAR g_cbOKS[] = 
TEXT("\\[\\([[:xdigit:]]+\\)\\]" "\\|"							// [OKS]
	 "\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]].*\\)" "\\|"	// OKS:irgend was
	 "\\[\\([[:xdigit:]]+\\)\\]\\(.*\\)"  "\\|"					// [OKS]irgend was
	 "!\\(.*\\):\\[\\([[:xdigit:]]+\\)\\]\\(.*\\)"				// irgendwas![OKS]irgendwas (Monikerformat)
	);

///////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
const wchar_t g_cbBESSELGK[] = L"BESSELGK";
const wchar_t g_cbKRASSGK[] = L"KRASSGK";
const wchar_t g_cbETRSGK[] = L"ETRS89GK";
const wchar_t g_cbBEGEOD[] = L"BEGEOD";
const wchar_t g_cbKRGEOD[] = L"KRGEOD";
const wchar_t g_cbETRSGEOD[] = L"ETGEOD";
const wchar_t g_cbCassiniSoldner[] = L"BESSELESO";

const wchar_t g_cbCoordMeridian[] = L"CoordMeridian";
const wchar_t g_cbCoordLatitude[] = L"CoordLatitude";
const wchar_t g_cbCoordStrBreite[] = L"CoordStrBreite";
const wchar_t g_cbCoordFalseX[] = L"CoordFalseX";
const wchar_t g_cbCoordFalseY[] = L"CoordFalseY";
const wchar_t g_cbCoordTransGUID[] = L"CoordTransGUID";
const wchar_t g_cbCoordScaleAtOrig[] = L"CoordScaleAtOrig";
const wchar_t g_cbCoordAutoMeridian[] = L"CoordAutoZone";
const wchar_t g_cbCoordDHDNType[] = L"CoordDHDNType";
const wchar_t g_cbCoordTcfName[] = L"CoordTcfName";

const wchar_t g_cbActLookupWindow[] = L"ActLookupWindow";

#if defined(_USE_PERFMON_COUNTERS)

///////////////////////////////////////////////////////////////////////////////
// Stringkonstanten für PerformanceCounter
const wchar_t g_cbPerfCtx[] = L"TRiASDB";		// globaler PerfCtxName

#endif // defined(_USE_PERFMON_COUNTERS)

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)

TCHAR g_cbTRiAS[_MAX_PATH];
TCHAR g_cbProjects[_MAX_PATH];
