// fieldinf.cpp : implementation file
//

#include "pheader.h"

#include <hpp/fieldinf.hpp>                        // zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//	globale Funktionen
int __export CALLBACK CompareFelderFunction (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	ASSERT ((lParam1 != 0) && (lParam2 != 0));

	CFeldInf *pFI1 = (CFeldInf *) lParam1;
	CFeldInf *pFI2 = (CFeldInf *) lParam2;

//	prüfe Parameter
	ASSERT ((pFI1 != NULL) && (pFI2 != NULL));
 
 	const char *pT1 = NULL;
	const char *pT2 = NULL;

	if (lParamSort & SortName || lParamSort & SortType)
	{
		if (lParamSort & SortName)
		{
			pT1 = pFI1 -> m_strName;
			pT2 = pFI2 -> m_strName;
		}
		else
		{
			pT1 = pFI1 -> m_strType;
			pT2 = pFI2 -> m_strType;
		}

	//	prüfe Parameter
		ASSERT (pT1 != NULL && AfxIsValidString (pT1));
		ASSERT (pT2 != NULL && AfxIsValidString (pT2));		
		if (lParamSort & SortAsc)			
			return strcmpi (pT1, pT2);		// aufsteigende Sortierung
		else
			return strcmpi (pT2, pT1);		// absteigende Sortierung				
	}
	else 	// sortiere nach Länge
	{
		if (lParamSort & SortAsc)
			return pFI1 -> m_lLen - pFI2 -> m_lLen;
		else
			return pFI2 -> m_lLen - pFI1 -> m_lLen;
	}
}

// 	CFeldInf ---------------------------------------------------------
CFeldInf :: CFeldInf (const char *pName, const char *pType, long lLen)
{
// 	prüfe Parameter
	ASSERT (pName != NULL && AfxIsValidString (pName));
	ASSERT (pType != NULL && AfxIsValidString (pType));	
        ASSERT (lLen >= 0);

	TRY
	{
		m_lLen = lLen;
		m_strName = pName;
		m_strType = pType;
	} 
	CATCH (CMemoryException, me)	
	{
		THROW_LAST ();
	}
	END_CATCH
}

// CFeldInfExt -------------------------------------------------
CFeldInfExt :: CFeldInfExt (const char *pName, const char *pTypeName, long lLen, 
							long lExtData)
							: CFeldInf (pName, pTypeName, lLen)
{
	m_lExtData = lExtData;
}



