// @doc 
// @module ScaleHeader.cpp | Koordinaten Scale/Offset-korrigieren

#include "trias01p.hxx"

#include <ScaleHeader.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

using namespace trias_nativeheader;

/////////////////////////////////////////////////////////////////////////////
// Stringkonstanten für diese Klasse 
const TCHAR g_cbKoeff11[] = TEXT("Koeff11");
const TCHAR g_cbKoeff12[] = TEXT("Koeff12");
const TCHAR g_cbKoeff21[] = TEXT("Koeff21");
const TCHAR g_cbKoeff22[] = TEXT("Koeff22");
const TCHAR g_cbOffsetX[] = TEXT("OffsetX");
const TCHAR g_cbOffsetY[] = TEXT("OffsetY");

/////////////////////////////////////////////////////////////////////////////
// 
CScaleHeader::CScaleHeader()
	: m_hPr(NULL)
{
	m_Koeffs.m_dK11 = m_Koeffs.m_dK22 = m_Koeffs.m_dInvK11 = m_Koeffs.m_dInvK22 = 1.0;
	m_Koeffs.m_dK12 = m_Koeffs.m_dK21 = m_Koeffs.m_dInvK12 = m_Koeffs.m_dInvK21 = 0.0;
	m_Koeffs.m_dOffsetX = m_Koeffs.m_dOffsetY = 0.0;
}

CScaleHeader::CScaleHeader(HPROJECT hPr)
	: m_hPr(NULL)
{
	m_Koeffs.m_dK11 = m_Koeffs.m_dK22 = m_Koeffs.m_dInvK11 = m_Koeffs.m_dInvK22 = 1.0;
	m_Koeffs.m_dK12 = m_Koeffs.m_dK21 = m_Koeffs.m_dInvK12 = m_Koeffs.m_dInvK21 = 0.0;
	m_Koeffs.m_dOffsetX = m_Koeffs.m_dOffsetY = 0.0;

	TX_VERIFY(Initialize (hPr));
}

inline double CScaleHeader::GetHeaderDouble (LPCSTR pcKey, double dDefault)
{
CDBHeader Hdr (m_hPr, pcKey);

	return Hdr.GetHeaderDouble (dDefault) ;
} 

bool CScaleHeader::Initialize (HPROJECT hPr)
{
	m_hPr = hPr;

	if (FAILED(GetScaleKoeffs (m_hPr, &m_Koeffs))) {
		m_Koeffs.m_dK11 = GetHeaderDouble (g_cbKoeff11, 1.0);
		m_Koeffs.m_dK12 = GetHeaderDouble (g_cbKoeff12, 0.0);
		m_Koeffs.m_dK21 = GetHeaderDouble (g_cbKoeff21, 0.0);
		m_Koeffs.m_dK22 = GetHeaderDouble (g_cbKoeff22, 1.0);
		m_Koeffs.m_dOffsetX = GetHeaderDouble (g_cbOffsetX, 0.0);
		m_Koeffs.m_dOffsetY = GetHeaderDouble (g_cbOffsetY, 0.0);
		if (EvalInvKoeffs())
			SetScaleKoeffs (m_hPr, &m_Koeffs);
		else
			return false;
	}
	return true;
}

bool CScaleHeader::EvalInvKoeffs() 
{
double DetA = m_Koeffs.m_dK11 * m_Koeffs.m_dK22 - m_Koeffs.m_dK12 * m_Koeffs.m_dK21;

	if (0.0 != DetA) {
	double temp = m_Koeffs.m_dK11;

		m_Koeffs.m_dInvK11 = m_Koeffs.m_dK22/DetA;
		m_Koeffs.m_dInvK22 = m_Koeffs.m_dK11/DetA;
		m_Koeffs.m_dInvK12 = -(m_Koeffs.m_dK12/DetA);
		m_Koeffs.m_dInvK21 = -(m_Koeffs.m_dK21/DetA);
		return true;
	}
	return false;
}


