// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 08/31/1998 10:26:12 PM
//
// @doc
// @module Strings.h | Zeichenkettenkonstanten für Identsdb

#if !defined(_STRINGS_H__84F9C7B4_4100_11D2_9EBB_006008447800__INCLUDED_)
#define _STRINGS_H__84F9C7B4_4100_11D2_9EBB_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

extern const char g_cbNil[];			// TEXT("");
extern const char g_cbExportMode[];		// TEXT("ExportMode");

///////////////////////////////////////////////////////////////////////////////
//
extern const char g_cbMyConfig[];		// TEXT("Software\\uve\\TRiAS\\Extensions\\TRiAS.IdentsDB.1");
extern const char g_cbRegConfig[];		// TEXT("Software\\uve\\TRiAS\\Config");

///////////////////////////////////////////////////////////////////////////////
//
extern const char g_cbTRiASName[];		// TEXT("TRiASName");
extern const char g_cbCopyrightName[];	// TEXT("TRiAS®");

///////////////////////////////////////////////////////////////////////////////
// XML-Datenimport/Export
extern const char g_cbTRiASMetadata[];	// "TRiAS_Metadata";
extern const char g_cbObjectClass[];	// "ObjectClass";
extern const char g_cbOKS[];			// "OKS";
extern const char g_cbIdent[];			// "Ident";
extern const char g_cbTableName[];		// "TableName";
extern const char g_cbName[];			// "Name";
extern const char g_cbDescription[];	// "Description";
extern const char g_cbObjectFeatures[];	// "ObjectFeatures";
extern const char g_cbMCode[];			// "MCode";
extern const char g_cbFeature[];		// "Feature";
extern const char g_cbType[];			// "Type";
extern const char g_cbLength[];			// "Length";
extern const char g_cbIsDefault[];		// TEXT("IsDefault");

///////////////////////////////////////////////////////////////////////////////
// bekannte Dateiendungen beim Import
extern const char g_cbTxc[];			// TEXT("txc");
extern const char g_cbTxi[];			// TEXT("txi");
extern const char g_cbTxm[];			// TEXT("txm");

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup geladen)
extern char g_cbTRiAS[_MAX_PATH];

#endif // !defined(_STRINGS_H__84F9C7B4_4100_11D2_9EBB_006008447800__INCLUDED_)
