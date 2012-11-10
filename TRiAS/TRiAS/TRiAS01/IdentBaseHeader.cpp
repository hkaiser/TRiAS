// @doc 
// @module IdentBaseHeader.cpp | Identifikator-Zahlenbasis aus Header lesen

#include "trias01p.hxx"

#include <IdentBaseHeader.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

using namespace trias_nativeheader;

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
const TCHAR g_cbIdentBase[] = TEXT("IdentBase");

/////////////////////////////////////////////////////////////////////////////
// 
CIdentBaseHeader::CIdentBaseHeader (HPROJECT hPr)
	: m_hPr(hPr)
{
}

int CIdentBaseHeader::GetIdentBase()
{
CDBHeader Hdr (m_hPr, g_cbIdentBase);
long lIdBase = Hdr.GetHeaderLong (16);

	TX_ASSERT(10 == lIdBase || 16 == lIdBase);
	if (10 != lIdBase && 16 != lIdBase)
		lIdBase = 16;

	return lIdBase;
}
