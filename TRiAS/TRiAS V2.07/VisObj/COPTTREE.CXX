// Baumklasse, die sich automatisch ausbalanciert -----------------------------
// File: COPTTREE.CXX

#include "visobjp.hxx"

#if !defined(WIN32)
#include <mmsystem.h>
#endif // !WIN32

#include "copttree.hxx"

bool COptTree :: Insert (FSHandle h, void * pobj)
{
DWORD dwT = GetTickCount();
bool fResult = CTree :: Insert (h, pobj);

	m_dwInsertTime = (GetTickCount() - dwT) / 10;

// bei Bedarf optimieren
	if (m_dwInsertTime > m_dwOptTime) {
		dwT = GetTickCount();
		Optimize();
		m_dwOptTime = GetTickCount() - dwT;
		if (m_dwOptTime == 0) m_dwOptTime = 1;
	}
	
return fResult;
}
