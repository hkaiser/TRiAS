// @doc 
// @module ScaleHeader.cpp | Koordinaten Scale/Offset-korrigieren

#include <StdAfx.h>

#include "Strings.h"
#include "ScaleHeader.h"

using namespace trias_nativeheader;

CScaleHeader::CScaleHeader()
	: m_hPr(NULL)
{
	m_dK11 = m_dK22 = 1.0;
	m_dK12 = m_dK21 = 0.0;
	m_dOffsetX = m_dOffsetY = 0.0;
}

inline double CScaleHeader::GetHeaderDouble (LPCSTR pcKey, double dDefault)
{
char cbBuffer[_MAX_PATH];
CDBHeader Hdr (m_hPr, pcKey);

	if (SUCCEEDED(Hdr.GetHeaderEntry (cbBuffer, _countof(cbBuffer)))) 
		return atof(cbBuffer);
	return dDefault;
} 

bool CScaleHeader::Initialize(HPROJECT hPr)
{
	m_hPr = hPr;

	m_dK11 = GetHeaderDouble (g_cbKoeff11, 1.0);
	m_dK12 = GetHeaderDouble (g_cbKoeff12, 0.0);
	m_dK21 = GetHeaderDouble (g_cbKoeff21, 0.0);
	m_dK22 = GetHeaderDouble (g_cbKoeff22, 1.0);
	m_dOffsetX = GetHeaderDouble (g_cbOffsetX, 0.0);
	m_dOffsetY = GetHeaderDouble (g_cbOffsetY, 0.0);
	return true;
}

