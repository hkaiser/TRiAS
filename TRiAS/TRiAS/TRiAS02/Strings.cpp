// @doc
// @module Strings.cpp | Stringkonstanten

#include "trias02p.hxx"
#include "Strings.h"

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
TCHAR g_cbTRiAS[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// konstante Strings
const TCHAR g_cbFakeMFCKey[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.FakeMFC.1\\Config");

const TCHAR g_cbDefault[] = TEXT("DEFAULT");
const TCHAR g_cbCoordTransform[] = TEXT("CoordTransform  ");
const TCHAR g_cbCTFExt[] = TEXT(".CTF");
const TCHAR g_cbDefaultCTF[] = TEXT("DEFAULT.CTF");
const TCHAR g_cbKoeff11[] = TEXT("Koeff11         ");
const TCHAR g_cbKoeff12[] = TEXT("Koeff12         ");
const TCHAR g_cbKoeff21[] = TEXT("Koeff21         ");
const TCHAR g_cbKoeff22[] = TEXT("Koeff22         ");
const TCHAR g_cbOffsetX[] = TEXT("OffsetX         ");
const TCHAR g_cbOffsetY[] = TEXT("OffsetY         ");

const TCHAR g_cbNoMemory[] = TEXT("Kein Speicherplatz!");

const TCHAR g_cbCopyrightName[] = TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
const TCHAR g_cbCopyrightNameT[] = TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400
const TCHAR g_cbTRiASName[] = TEXT("TRiASName");
const TCHAR g_cbTRiASMode[] = TEXT("TRiASMode");

const TCHAR g_cbOldName[] = TEXT("OldName");

const TCHAR g_cbCTFService[] = TEXT("CTFService");
const TCHAR g_cbStgService[] = TEXT("StgService");

const TCHAR g_cbNil[] = TEXT("");

const OLECHAR g_cbObjectsMap[] = L"ObjectsMap";
const OLECHAR g_cbObjectMap[] = L"ObjectMap";
const OLECHAR g_cbFeatureMap[] = L"FeatureMap";
const OLECHAR g_cbGeometry[] = L"Geometry";
const OLECHAR g_cbTRiASDataSource[] = L"TRiASDataSource";
const OLECHAR g_cbGDODataSource[] = L"GDODataSource";

const OLECHAR g_cbDefaultGeometry[] = L"DefaultGeometry";

const TCHAR g_cbId[] = TEXT("Id");
const TCHAR g_cbIdForce[] = TEXT("IdForce");
const TCHAR g_cbStandard[] = TEXT("Standard");
const TCHAR g_cbObjName[] = TEXT("Objektname");
const TCHAR g_cbPrimaryKey[] = TEXT("PrimaryKey");

const TCHAR g_cbArial[] = TEXT("Arial");
