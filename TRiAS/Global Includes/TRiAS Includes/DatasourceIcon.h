// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 11.10.2001 08:42:21 
//
// @doc
// @module DatasourceIcon.h | Declaration of the datasource_icon namespace

#if !defined(_DATASOURCEICON_H__1030D6E6_B3EE_4C78_84F2_5C95FCC26FE5__INCLUDED_)
#define _DATASOURCEICON_H__1030D6E6_B3EE_4C78_84F2_5C95FCC26FE5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

EXTERN_C const CLSID CLSID_TRiASDataServerRegEntries;

///////////////////////////////////////////////////////////////////////////////
// GetBitmapIndex
namespace datasource_icon {

///////////////////////////////////////////////////////////////////////////////
// ItemIds in Imagelist
	#define IMG_NOICON							0

	#define IMG_DATASOURCE						1		// allgemeine Datenquelle
	#define IMG_DATASOURCE_TRiAS1				2		// .stb
	#define IMG_DATASOURCE_TRiAS2				3		// V2.0 .ris
	#define IMG_DATASOURCE_TRiAS3				4		// V3.0 .ris
	#define IMG_DATASOURCE_TRiAS_EMBEDDED		5		// V3.0 embedded in .riw
	#define IMG_DATASOURCE_ARCVIEW				6		// ArcView
	#define IMG_DATASOURCE_MAPINFO				7		// MapInfo
	#define IMG_DATASOURCE_OLEDB				8		// OleDb
	#define IMG_DATASOURCE_POLYGIS				9		// PolyGIS
	#define IMG_DATASOURCE_GDO					10		// Geomedia GDO
	#define IMG_DATASOURCE_MEMDB				11		// FastDB/GigaBase

// mappen der RegistryBmpNo auf unsere Imagelist
	extern int __declspec(selectany) g_cbBmps[] = {
		IMG_NOICON, IMG_NOICON, IMG_DATASOURCE_GDO, IMG_NOICON,
		IMG_NOICON, IMG_DATASOURCE, IMG_DATASOURCE, IMG_DATASOURCE, 
		IMG_NOICON, IMG_NOICON, IMG_NOICON, IMG_DATASOURCE_TRiAS1,
		IMG_DATASOURCE_TRiAS2, IMG_DATASOURCE_TRiAS3, IMG_DATASOURCE_TRiAS_EMBEDDED, IMG_DATASOURCE_TRiAS1, 
		IMG_DATASOURCE_ARCVIEW, IMG_DATASOURCE_MAPINFO, IMG_DATASOURCE_ARCVIEW, IMG_DATASOURCE_MAPINFO, 
		IMG_DATASOURCE_OLEDB, IMG_DATASOURCE_OLEDB, IMG_DATASOURCE_POLYGIS, IMG_DATASOURCE_POLYGIS,
		IMG_DATASOURCE_ARCVIEW, IMG_DATASOURCE_ARCVIEW, IMG_DATASOURCE_GDO, IMG_DATASOURCE_MEMDB
	};

	inline DWORD GetBitmapIndex(HPROJECT hPr)
	{
	// Icon der Datenquelle besorgen
	DWORD dwBmp = 5;

		{
		__Interface<ITRiASConnection> Conn;

			if (DEX_GetDataSourcePtr(hPr, *Conn.ppv())) {
			__Interface<ITRiASDatabase> DBase;

				if (SUCCEEDED(Conn -> get_Database (DBase.ppi()))) {
					USES_CONVERSION;

				CComBSTR bstrProgID;		// ProgID des TRiAS-DataBase-TargetObjektes
				
					if (SUCCEEDED(DBase -> get_Type (&bstrProgID))) {
					__Interface<ITRiASDataServerRegEntries> Entries(CLSID_TRiASDataServerRegEntries);
					__Interface<ITRiASDataServerRegEntry> Entry;

						if (SUCCEEDED(Entries -> FindFromServerProgID (bstrProgID, Entry.ppi()))) 
							Entry -> get_ToolboxBitmap32 ((LONG *)&dwBmp);
					}
				}
			}
		}
		_ASSERTE(0 <= dwBmp && dwBmp < _countof(g_cbBmps));
		return g_cbBmps[dwBmp];
	}
}

#endif // !defined(_DATASOURCEICON_H__1030D6E6_B3EE_4C78_84F2_5C95FCC26FE5__INCLUDED_)
