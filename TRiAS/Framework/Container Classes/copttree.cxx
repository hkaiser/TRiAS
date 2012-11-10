// Baumklasse, die sich automatisch ausbalanciert -----------------------------
// File: COPTTREE.CXX

#include "contpre.hxx"
#include "copttree.hxx"

#include "p5ticker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(WIN32)
BOOL COptTree::m_fP5TickerAvailable = P5_Ticker().P5_Ticker_Available();
#else
BOOL COptTree::m_fP5TickerAvailable = FALSE;
#endif // WIN32

BOOL COptTree::Insert (FSHandle h, void *pobj)
{
BOOL fResult = false;

	if (m_fP5TickerAvailable) {		// nur für Pentiums et. al.
	P5_Ticker timeBefore;
	P5_Ticker timePast;

		timeBefore.Get_Time();
		fResult = CTree::Insert (h, pobj);
		timePast.Get_Time();

		m_liLastInsertTime = (timePast - timeBefore).To_Ticks();

		if (m_fOptimized) {	// erstes Einfügen nach Optimierung, Zeit speichern
			m_liInsertTime = m_liLastInsertTime;
			m_fOptimized = false;
		} else {
		LONGLONG llT = m_liLastInsertTime.QuadPart - m_liInsertTime.QuadPart;

			if (llT < 0) 
				llT = -llT;		// für alle Fälle (digital ist alles möglich)
			if (llT > (LONGLONG)(m_liOptTime.QuadPart)/* /m_lDelta */) 
			{
			// Differenz der Einfügezeit und der optimalen Einfügezeit liegt im Bereich der
			// letzten Optimierzeit

				timeBefore.Get_Time();
				Optimize();		// Baum optimieren
				timePast.Get_Time();

				m_fOptimized = true;
				m_liOptTime = (timePast - timeBefore).To_Ticks();
				if (m_liOptTime.QuadPart == 0) 
					m_liOptTime.QuadPart = 1;
			}
		}

	} else {
		TX_ASSERT(m_lDelta > 0);

	DWORD dwT = GetTickCount();
	
		fResult = CTree::Insert (h, pobj);
		dwT = GetTickCount() - dwT;
		ULISet32(m_liLastInsertTime, dwT);

	// bei Bedarf optimieren
		if (m_liLastInsertTime.QuadPart > m_liOptTime.QuadPart) {
			dwT = GetTickCount();
			Optimize();
			dwT = (GetTickCount() - dwT) / m_lDelta;

			ULISet32(m_liOptTime, dwT);
			if (m_liOptTime.LowPart == 0) m_liOptTime.LowPart = 1;
		}
	}

	return fResult;
}
