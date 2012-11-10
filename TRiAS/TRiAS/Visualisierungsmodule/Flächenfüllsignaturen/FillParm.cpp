// Objekt, welches die Füllparameter verwaltet --------------------------------
// File: FILLPARM.CPP

#include "stdafx.h"
#include "FillParm.h"
#include "Helper.h"

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor
CFillParams::CFillParams (HDC hTargetDC)
			: m_hDC(hTargetDC)
{
	m_lOffset = 0;
	m_lStep = 0;
	m_lWidth = 0;

	m_dScale = 1.0;
	DEX_GetActiveScaling (m_dScale);
	
	ASSERT (0.0 != m_dScale);
	if (0 == m_dScale) m_dScale = 1.0;

	m_sizeDots = GetDotsPerMM(m_hDC);
}

CFillParams::~CFillParams (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Implementation
//
inline long GetToken (LPCSTR pStr, LPSTR *ppTmp)
{
long lT = strtol (pStr, ppTmp, 10);

	if (*ppTmp == pStr)
		return 0L;

return lT;
}

// Die VisStr-Zeichenkette hat folgendes Format:
//		lWidth,lStep,lOffset
// Fehlende Werte für lWidth und lOffset werden gleich 0 gesetzt.
// Fehlende Werte für lStep werden gleich max(2*lWidth, 2) gesetzt 
//  (in GetStepOnDC()).
HRESULT CFillParams::ParseVisString (LPCSTR pVisStr)
{
LPSTR pT = NULL;

	m_lWidth = GetToken (pVisStr, &pT);
	m_lStep = GetToken (pT+1, &pT);
	m_lOffset = GetToken (pT+1, &pT);

return NOERROR;
}

long CFillParams::GetStepOnDC_X (void)
{
	if (0 == m_lStep) {
	long lT = 2*GetWidthOnDC_X();

		return (lT != 0) ? lT : ScaleX (DEFAULT_STEP);
	}

return ScaleX (m_lStep);
}

long CFillParams::GetStepOnDC_Y (void)
{
	if (0 == m_lStep) {
	long lT = 2*GetWidthOnDC_Y();

		return (lT != 0) ? lT : ScaleY (DEFAULT_STEP);
	}

return ScaleY (m_lStep);
}

