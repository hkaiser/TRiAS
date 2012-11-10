// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/10/1998 09:29:43 PM
//
// @doc
// @module CoordSysKeys.h | Bekannte HeaderEinträge für Koordinatensystem

#if !defined(_COORDSYSKEYS_H__14C90605_9059_11D2_9F00_006008447800__INCLUDED_)
#define _COORDSYSKEYS_H__14C90605_9059_11D2_9F00_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Bekannte RegistryKeys für Koordinatensysteme
typedef struct tagCOORDSYSKEY {
	TCHAR *m_pKey;
	DWORD m_dwMode;
} COORDSYSKEY;

extern "C" const COORDSYSKEY __declspec(selectany) g_cbCoordSysKeys[] = {
	{ TEXT("CoordTransform"), HEADER_SYSTEMRO },
	{ TEXT("CoordMeridian"), HEADER_SYSTEMRO },
	{ TEXT("CoordStrBreite"), HEADER_SYSTEMRO },
	{ TEXT("CoordPrecision"), HEADER_SYSTEM },
	{ TEXT("CoordScaling"), HEADER_SYSTEMRO },
	{ TEXT("ShowGKCoords"), HEADER_SYSTEMRO },
	{ TEXT("CoordMeridianV"), HEADER_SYSTEMRO },
	{ TEXT("OffsetX"), HEADER_SYSTEMRO },
	{ TEXT("OffsetY"), HEADER_SYSTEMRO },
	{ TEXT("Koeff11"), HEADER_SYSTEMRO },
	{ TEXT("Koeff12"), HEADER_SYSTEMRO },
	{ TEXT("Koeff21"), HEADER_SYSTEMRO },
	{ TEXT("Koeff22"), HEADER_SYSTEMRO },
	{ TEXT("CSSGuid"), HEADER_SYSTEMRO },
	{ TEXT("CoordTransGUID"), HEADER_SYSTEMRO },
	{ TEXT("CoordScaleAtOrig"), HEADER_SYSTEMRO },
	{ TEXT("CoordFalseX"), HEADER_SYSTEMRO },
	{ TEXT("CoordFalseY"), HEADER_SYSTEMRO },
	{ TEXT("CoordLatitude"), HEADER_SYSTEMRO },
	{ TEXT("CoordUnitOfAngle"), HEADER_SYSTEMRO },
	{ TEXT("CoordEpsgId"), HEADER_SYSTEMRO },
	{ TEXT("CoordOgcWkt"), HEADER_SYSTEMRO },
	{ TEXT("CoordAutoZone"), HEADER_SYSTEMRO },
	{ TEXT("CoordDHDNType"), HEADER_SYSTEMRO },
	{ TEXT("CoordTcfName"), HEADER_SYSTEMRO },
};

///////////////////////////////////////////////////////////////////////////////
// Bekannte sonstige HeaderEinträge, die ggf. übernommen werden sollten
extern "C" const COORDSYSKEY __declspec(selectany) g_cbAuxHeaderEntries[] = {
	{ TEXT("Caption"), HEADER_NORMAL, },
	{ TEXT("Copyright"), HEADER_SYSTEMRO, },
	{ TEXT("HideFlags"), HEADER_NORMAL, },
	{ TEXT("ShowObjProp"), HEADER_NORMAL, },
	{ TEXT("BezugsMasstab"), HEADER_NORMAL, },
};

#endif // !defined(_COORDSYSKEYS_H__14C90605_9059_11D2_9F00_006008447800__INCLUDED_)
