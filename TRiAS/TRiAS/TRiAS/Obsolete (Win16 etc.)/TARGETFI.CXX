// Iteratorklasse fuer Finden aller Targetdateien fuer eine KeyDatei ----------
// File: TARGETFI.CXX

#include "triaspre.hxx"

#include <dbd.h>
#include <dbd.hxx>

#include "targetfi.hxx"

// Konstruktor ----------------------------------------------------------------
CTargetFileIterator :: CTargetFileIterator (CDBDict &DBD)
		     : m_rDBD (DBD)
{
	m_iActIndex = -1;
}

BOOL CTargetFileIterator :: Init (short iKeyIndex)
{
	if (iKeyIndex < 0 || iKeyIndex >= m_rDBD.iKeys()) {
		m_iKeyFile = -1;
		return FALSE;
	}
	m_iKeyFile = m_rDBD.m_pKeyTable[iKeyIndex].keiKeyfile;
	
return TRUE;
}


short CTargetFileIterator :: GetFirstTargetFile (void)
{
	m_iActIndex = -1;

return GetNextTargetFile();	
}

short CTargetFileIterator :: GetNextTargetFile (void)
{
	if (m_iKeyFile == -1) return -1;

	for (m_iActIndex++ ; m_iActIndex < m_rDBD.iKeys(); m_iActIndex++) {
		if (m_rDBD.m_pKeyTable[m_iActIndex].keiKeyfile == m_iKeyFile) 
			return m_rDBD.m_pKeyTable[m_iActIndex].keiFile;
	}

return -1;
}
