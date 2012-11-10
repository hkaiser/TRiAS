///////////////////////////////////////////////////////////////////////////////
// Zeichenkettenkonstanten
// File: Strings.cpp

#include "Idntsdbp.hxx"
#include "Strings.h"

const char g_cbNil[] = TEXT("");
const char g_cbExportMode[] = TEXT("ExportMode");

///////////////////////////////////////////////////////////////////////////////
//
const char g_cbMyConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.IdentsDB.1\\Config");
const char g_cbRegConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");

///////////////////////////////////////////////////////////////////////////////
//
const char g_cbCopyrightName[] = TEXT("TRiAS®");
const char g_cbTRiASName[] = TEXT("TRiASName");

///////////////////////////////////////////////////////////////////////////////
// XML-Datenimport/Export
const char g_cbTRiASMetadata[] = TEXT("TRiAS_Metadata");
const char g_cbObjectClass[] = TEXT("ObjectClass");
const char g_cbOKS[] = TEXT("OKS");
const char g_cbIdent[] = TEXT("Ident");
const char g_cbTableName[] = TEXT("TableName");
const char g_cbName[] = TEXT("Name");
const char g_cbDescription[] = TEXT("Description");
const char g_cbObjectFeatures[] = TEXT("ObjectFeatures");
const char g_cbMCode[] = TEXT("MCode");
const char g_cbFeature[] = TEXT("Feature");
const char g_cbType[] = TEXT("Type");
const char g_cbLength[] = TEXT("Length");
const char g_cbIsDefault[] = TEXT("IsDefault");

///////////////////////////////////////////////////////////////////////////////
// bekannte Dateiendungen beim Import
const char g_cbTxc[] = TEXT("txc");
const char g_cbTxi[] = TEXT("txi");
const char g_cbTxm[] = TEXT("txm");

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup geladen)
char g_cbTRiAS[_MAX_PATH];

