// $Header: /TRiAS/TRiAS/TRiAS01/GeometryGuid.cpp 1     15.06.98 22:23 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/14/1998 12:45:49 PM
//
// @doc
// @module GeometryGuid.cpp | Guids für Koordinatensysteme verwalten

#include "trias01p.hxx"

#include <CSSGuidHeader.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

HRESULT EnsureCSGuidLoaded (HPROJECT hPr, GUID *pGuid)
{
short db_slot = (short)hPr -1;

	TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

DBASE *db_p = &db_table[db_slot];

	if (InlineIsEqualGUID(db_p -> db_CSSGuid, GUID_NULL)) {
	CCSGuidHeader GuidHdr (hPr);
	GUID Guid;

		if (!GuidHdr.GetCSSGuid (&Guid)) 
			return E_UNEXPECTED;

	// fürs nächste mal setzen
		memcpy (&db_p -> db_CSSGuid, &Guid, sizeof(GUID));
	} 

	memcpy (pGuid, &db_p -> db_CSSGuid, sizeof(GUID));
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Alle Objekte liegen in einem Koordinatensystem
HRESULT GetGeometryGuid (HPROJECT hPr, long lIdent, LPCSTR pcName, _GUID *pGuid)
{
	if (NULL == pGuid) return E_POINTER;
	if (NULL == hPr) return E_INVALIDARG;

	return EnsureCSGuidLoaded(hPr, pGuid);
}

/////////////////////////////////////////////////////////////////////////////
// Liefert alle Guids dieser GeoDB
HRESULT GetGeometryGuids (HPROJECT hPr, long *plCnt, _GUID **ppGuids)
{
	if (NULL == plCnt || NULL == ppGuids)
		return E_POINTER;
	if (NULL == hPr)
		return E_INVALIDARG;

GUID Guid;

	*plCnt = 0;		// für alle Fälle
	RETURN_FAILED_HRESULT(EnsureCSGuidLoaded(hPr, &Guid));

// Resultat liefern
	*ppGuids = (GUID *)::CoTaskMemAlloc (sizeof(GUID));
	if (NULL == *ppGuids)
		return E_OUTOFMEMORY;

	memcpy (*ppGuids, &Guid, sizeof(GUID));
	*plCnt = 1;
	return S_OK;
}

