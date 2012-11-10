#include "stdafx.h"

#include "resource.h"
#include "iterator.hpp"    // Klasse für Iteration


CLBIterator :: CLBIterator (CListBox &rlb)
			    : m_rlb (rlb)
{
	Reset();
}

void CLBIterator :: Reset (void)
{
	m_iCnt = 0;
	m_iCntItems = m_rlb.GetCount();
	
	TRY {                                       
		m_pItem = m_sItem.GetBuffer(STRLENGTH); 
	}
	CATCH ( CMemoryException, e ) {
		DEX_Error (0, EC_NOMEMORY); 
	}                  
	END_CATCH

}


BOOL CLBIterator :: GetNextItem (long &rlItem, char* pcGeo)
{
		
short   iRCode = 0;
char    cGeo = '0';
	if (m_iCnt > m_iCntItems)		// alle abgeholt
				return FALSE;

// was ist DAS ?? (#HK960110)
	while ((iRCode = m_rlb.GetSel(m_iCnt)) == 0)     // Aufruf für Auswahl mehrerer Obj.
		{
		if (m_iCnt > m_iCntItems)		// alle abgeholt
			return FALSE;
			m_iCnt++;
		}		
	if (iRCode == LB_ERR)
		{
		rlItem = -1;
		return FALSE;
	    }

	m_rlb.GetText (m_iCnt, m_sItem);
	m_iIdBase = DEX_GetIdBase();

		if (m_iIdBase == 10)
			rlItem = atol(m_sItem);
		else
			rlItem = strtoul(m_sItem, NULL, 16); 
		
	if (rlItem == 0)
		return FALSE;
		
	cGeo = FindObjGeo (m_pItem); 
	
	switch(cGeo) 
	{
		case 'F':
			break;
		case 'L':
			break;
		case 'P':
			break;
		default:
			return FALSE;
	}
	*pcGeo = cGeo; 	    
	m_iCnt++;
return TRUE;
}

char  CLBIterator :: FindObjGeo (char* pItem)
{
char *pcSuch = pItem;
char cGeo; 

	if (pcSuch == NULL)
	{
	*pcSuch = 'A';
	return cGeo = *pcSuch;
	}
	
	while (*pcSuch++)
	{
		if (*pcSuch == ':')
		{
			++pcSuch;
			return cGeo = *pcSuch ;
		}
	}
	*pcSuch = '0';
return cGeo = *pcSuch;
}			 

CLBIterator :: ~CLBIterator ()
{
m_sItem.ReleaseBuffer();
}
