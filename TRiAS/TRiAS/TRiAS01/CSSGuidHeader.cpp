// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/14/1998 07:51:23 PM
//
// @doc
// @module CSSGuidHeader.cpp | CSSGuid in GeoDBHeader verwalten

#include "trias01p.hxx"

#include <Ciid.h>
#include <CSSGuidHeader.h>

#include "Strings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

using namespace trias_nativeheader;

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
const TCHAR g_cbCSSGuid[] = TEXT("CSSGuid");
const TCHAR g_cbCoordOgcWkt[] = TEXT("CoordOgcWkt");
const TCHAR g_cbCoordEpsgId[] = TEXT("CoordEpsgId");

/////////////////////////////////////////////////////////////////////////////
// 
CCSGuidHeader::CCSGuidHeader (HPROJECT hPr)
	: m_hPr(hPr)
{
}

BOOL CCSGuidHeader::GetCSSGuid(GUID *pGuid)
{
	_ASSERTE(NULL != pGuid);

CDBHeader Hdr (m_hPr, g_cbCSSGuid);
char cbBuffer[64];

	Hdr.GetHeaderEntry (cbBuffer, sizeof(cbBuffer));

CIID Guid (cbBuffer, CIID::INITCIID_InitFromGuid);

	if (!Guid) {
    BOOL fIsCompound = TRUE;

        GetIsCompoundDB(m_hPr, &fIsCompound);
        if (fIsCompound) {
#pragma MESSAGE("TODO: Versuchen CSSGuid aus Vergleich von Header und Registry zu bestimmen.")
		    Guid.New();
		    Hdr.PutHeaderEntry (os_string(Guid).c_str(), 0, HEADER_SYSTEMRO);
        }
        else {
        // wenn Datenbank schreibgeschützt ist, dann eben neu erzeugenC
            Guid = CIID();
        }
	}

	memcpy (pGuid, &Guid, sizeof(GUID));
	return TRUE;
}

BOOL CCSGuidHeader::GetEpsgId(UINT *plCode)
{
	_ASSERTE(NULL != plCode);

CDBHeader Hdr (m_hPr, g_cbCoordOgcWkt);

	*plCode = Hdr.GetHeaderLong (-1);
	return TRUE;
}

BOOL CCSGuidHeader::GetOgcWkt(BSTR *pbstrWkt)
{
	_ASSERTE(NULL != pbstrWkt);

CDBHeader Hdr (m_hPr, g_cbCoordOgcWkt);
size_t iLen = 0;

	if (FAILED(Hdr.GetHeaderEntryLen(&iLen)))
		return FALSE;

char *pBuffer = (char *)_alloca(iLen);

	if (SUCCEEDED(Hdr.GetHeaderEntry (pBuffer, iLen))) {
		*pbstrWkt = CComBSTR(pBuffer).Detach();
		return TRUE;
	}
	return FALSE;
}

