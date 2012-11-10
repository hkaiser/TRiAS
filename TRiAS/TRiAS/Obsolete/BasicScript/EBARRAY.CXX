// Wrapperklasse für eindimensionale ebARRAY's --------------------------------
// File: EBARRAY.CXX

#include "bscriptp.hxx"

#include <eb.h>

#include "ebarray.hxx"

// Memberfunktionen -----------------------------------------------------------
bool CEbArray :: ReDim (long lCnt)
{
long lDim = 0;

	{	// testen, ob dieses Array bearbeitet werden kann
	CEbLock l(*this);
	ebLPARRAY pArr = (ebLPARRAY )l;
		
		if (pArr -> bNumDims > 1) return false;
		lDim = pArr -> Dim[0].wUpper - pArr -> Dim[0].wLower;
		if (pArr -> bFlags & AF_FIXED && (lDim < lCnt))
			return false;
	} // Lock aufheben
	
	if (lDim < lCnt && ebRedimArray (m_hThread, m_hArr, int(lCnt)))
		return false;
	
return true;
}

// LockWrapper, der auf Elemente eines CEbArray zugreifen läßt ----------------
CEbLock :: CEbLock (CEbArray &eba)
	 : m_reba(eba)
{
	m_pData = NULL;
	m_pArray = NULL;
	m_lDim = 0;
			
	if ((m_pArray = m_reba.Lock()) != NULL) {
		m_pData = m_reba.AccessData (m_pArray);
		if (m_pData == NULL) {
			m_reba.UnAccessData (m_pArray);
			m_pArray = NULL;
		}
		m_lDim = m_pArray -> Dim[0].wUpper - m_pArray -> Dim[0].wLower;
	}
}

CEbLock :: ~CEbLock (void)
{
	if (m_pData){
		if (m_pArray) m_reba.UnAccessData (m_pArray);
		m_reba.UnLock();
	}
}
