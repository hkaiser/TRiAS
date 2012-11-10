// @doc 
// @module UniqueHeader.cpp | Eindeutige Handles aus Header besorgen

#include "trias01p.hxx"

#include <UniqueHeader.h>
#include <IdentBaseHeader.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

using namespace trias_nativeheader;

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
const TCHAR g_cbNextUniqueICode[] = TEXT("NextUniqueICode");
const TCHAR g_cbNextSystemICode[] = TEXT("NextSystemICode");
const TCHAR g_cbNextUniqueMCode[] = TEXT("NextUniqueMCode");
const TCHAR g_cbNextSystemMCode[] = TEXT("NextSystemMCode");
const TCHAR g_cbNextUniqueRCode[] = TEXT("NextUniqueRCode");

/////////////////////////////////////////////////////////////////////////////
// Erste Codes, die fortlaufend vergeben werden 
const long FIRSTUNIQUEICODE = 1100000000L;		// Identifikator (Dez)
const long FIRSTUNIQUEICODEX = 0xF1000000L;		// Identifikator (Hex)
const long FIRSTUNIQUEMCODE = 1100000000L;		// MerkmalsCode
const long FIRSTUNIQUESYSMCODE = 2090000000L;	// MerkmalsCode (System)
const long FIRSTUNIQUERCODE = 1100000000L;		// RelationsCode

/////////////////////////////////////////////////////////////////////////////
// Konstruktor
CUniqueHeader::CUniqueHeader(HPROJECT hPr)
	: m_hPr(hPr)
{
}

long CUniqueHeader::GetNextUniqueCode(UNIQUETYPE rgType)
{
	switch(rgType) {
	case UNIQUETYPE_ICODE:
	case UNIQUETYPE_SYSICODE:
		{
		CIdentBaseHeader IdBase (m_hPr);
		long lFirstCode = 10 == IdBase.GetIdentBase() ? FIRSTUNIQUEICODE : FIRSTUNIQUEICODEX;

			return GetUniqueLong (g_cbNextUniqueICode, lFirstCode);
		}
		break;

	case UNIQUETYPE_MCODE:
		return GetUniqueLong (g_cbNextUniqueMCode, FIRSTUNIQUESYSMCODE);

	case UNIQUETYPE_SYSMCODE:
		return GetUniqueLong (g_cbNextSystemMCode, FIRSTUNIQUESYSMCODE);

	case UNIQUETYPE_RCODE:
		return GetUniqueLong (g_cbNextUniqueRCode, FIRSTUNIQUESYSMCODE);

	default:
		break;
	}
	return 0L;
}

long CUniqueHeader::GetUniqueLong (LPCSTR pcKey, long lFirstCode)
{
CDBHeader Hdr (m_hPr, pcKey);
long lFlags = HEADER_SYSTEMRO;
long lEntry = Hdr.GetHeaderLong (0L, &lFlags);

	if (0L == lEntry)
		lEntry = lFirstCode;

BOOL fIsCompound = TRUE;

    GetIsCompoundDB(m_hPr, &fIsCompound);
	if (fIsCompound && FAILED(Hdr.PutHeaderLong (lEntry+1, lFlags)))
		lEntry = 0L;		// Fehlerkennzeichen

	return lEntry;
}
