// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/14/1998 07:49:48 PM
//
// @doc
// @module CSSGuidHeader.h | CSSGuid in GeoDBHeader verwalten

#if !defined(_CSSGUIDHEADER_H__CBC5D022_03AF_11D2_8651_00600875138A__INCLUDED_)
#define _CSSGUIDHEADER_H__CBC5D022_03AF_11D2_8651_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <HeaderEntry.h>

class _TRIAS01_ENTRY CCSGuidHeader
{
private:
	HPROJECT m_hPr;

public:
	CCSGuidHeader (HPROJECT hPr);
	BOOL GetCSSGuid(GUID *pGuid);
	BOOL GetEpsgId(UINT *plCode);
	BOOL GetOgcWkt(BSTR *pbstrWkt);
};

#endif // !defined(_CSSGUIDHEADER_H__CBC5D022_03AF_11D2_8651_00600875138A__INCLUDED_)
