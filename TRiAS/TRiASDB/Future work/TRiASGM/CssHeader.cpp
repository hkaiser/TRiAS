///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CssHeader.cpp | GM-Koordinatensystem aus Datenbank-Headereinträgen
// erzeugen

#include <StdAfx.h>

#include "Strings.h"
#include "CssHeader.h"

using namespace trias_nativeheader;

///////////////////////////////////////////////////////////////////////////
// Konstruktion/Initialisierung etc.
CCSSHeader::CCSSHeader (HPROJECT hPr, IGMCoordSystem *pCSS)
	: m_CS(pCSS), m_hPr(hPr)
{
}

CCSSHeader::~CCSSHeader()
{
	m_CS.Assign(NULL);
}

///////////////////////////////////////////////////////////////////////////
// Memberfunktionen
bool CCSSHeader::InitCoordTransform()
{
char cbBuffer[_MAX_PATH];
CDBHeader Hdr (m_hPr, g_cbCoordTransform);

	m_rgType = csbsProjected;
	m_rgProj = cspaUndefined;
	m_rgDatum = csgdUndefined;
	m_dMeridian = 0.0;
	m_dFalseX = 0.0;
	m_lZone = 0;
	m_fIsTransverseMercator = false;
	m_fIsUserDefined = true;

	if (SUCCEEDED(Hdr.GetHeaderEntry(cbBuffer, _countof(cbBuffer)))) {
	// Typ der Koordinatentransformation feststellen
	os_string str (cbBuffer);

		m_fIsUserDefined = false;
		if (str == TEXT("BESSELGK")) {
			m_rgType = csbsProjected;
			m_rgProj = cspaTransverseMercator;
			m_rgDatum = csgdPotsdam;
			m_dMeridian = RetrieveMeridian();
			m_dFalseX = RetrieveFalseX(m_lZone);
			m_fIsTransverseMercator = true;

		} else if (str == TEXT("KRASSGK")) {
			m_rgType = csbsProjected;
			m_rgProj = cspaTransverseMercator;
			m_rgDatum = csgdPulkovo1942;
			m_dMeridian = RetrieveMeridian();
			m_dFalseX = RetrieveFalseX(m_lZone);
			m_fIsTransverseMercator = true;

		} else if (str == TEXT("BEGEOD")) {
			m_rgType = csbsGeographic;
			m_rgDatum = csgdPotsdam;

		} else if (str == TEXT("KRGEOD")) {
			m_rgType = csbsGeographic;
			m_rgDatum = csgdPulkovo1942;

		} else if (str == TEXT("ETRSGEOD")) {
			m_rgType = csbsGeographic;
			m_rgDatum = csgdWGS84;

		} else 
			m_fIsUserDefined = true;
			
	}
	return true;
}

double CCSSHeader::RetrieveMeridian()
{
	ASSERT(m_rgType == csbsProjected);
	ASSERT(m_rgDatum != csgdUndefined);

char cbBuffer[_MAX_PATH];
CDBHeader Hdr (m_hPr, g_cbCoordMeridian);

	if (SUCCEEDED(Hdr.GetHeaderEntry (cbBuffer, _countof(cbBuffer)))) {
		m_dMeridian = atol(cbBuffer);
		return m_dMeridian;
	}

// wenn nicht gegeben, Standard annehmen
	return (csgdPotsdam == m_rgDatum) ? 12.0 : 15.0;
}

double CCSSHeader::RetrieveFalseX (long &rlZone)
{
	ASSERT(m_rgType == csbsProjected);
	ASSERT(0.0 != m_dMeridian);

char cbBuffer[_MAX_PATH];
CDBHeader Hdr (m_hPr, g_cbCoordStrBreite);

	if (SUCCEEDED(Hdr.GetHeaderEntry (cbBuffer, _countof(cbBuffer)))) {
	long lStr = atol (cbBuffer);

		ASSERT(3 == lStr || 6 == lStr);
		if (3 == lStr) {
			rlZone = (long)(m_dMeridian / 3.0);
			return rlZone * 1000000.0 + 500000.0;
		} else if (6 == lStr) {
			rlZone = (long)((m_dMeridian + 3) / 6.0);
			return rlZone * 1000000.0 + 500000.0;
		}
	}

// wenn nicht gegeben, Standard annehmen
	return (csgdPotsdam == m_rgDatum) ? 4500000.0 : 3500000.0;
}

///////////////////////////////////////////////////////////////////////////////
// für Projektionen
double CCSSHeader::GetMetricDistVal()
{
	return 1.0;
}

CComBSTR CCSSHeader::GetMetricUnitStr()
{
	return CComBSTR("m");
}

///////////////////////////////////////////////////////////////////////////////
// für geodätische css
double CCSSHeader::GetAngleDistVal()
{
	return 1.0;
}

CComBSTR CCSSHeader::GetAngleUnitStr()
{
	return CComBSTR("sec");
}
