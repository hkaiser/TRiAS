#include "stdafx.h"
 
#include "resource.h"
#include "helper.h"

extern CHelper *g_pHelper;

//-----------------------------------------------------------------------------
// Enumeration der Merkmalscodes und Identifikatoren für
// jeweilige Boxen

extern "C"
bool FAR PASCAL _XTENSN_EXPORT EnumIdentProcEx (long lIdent, DWORD dwType, void *pData)
{
	ASSERT (0 != lIdent);
	ASSERT (NULL != pData);
	ASSERT (NULL != g_pHelper);
	
	return g_pHelper -> FuellBox (dwType, (CListBox *) pData, lIdent);
}

extern "C"
bool FAR PASCAL _XTENSN_EXPORT EnumIdentProc (long lIdent, bool, void *pData)
{
	ASSERT (0 != lIdent);
	ASSERT (NULL != pData);
	ASSERT (NULL != g_pHelper);

	return g_pHelper -> FuellBox ((CComboBox *)pData, lIdent);
}

extern "C"
bool FAR PASCAL _XTENSN_EXPORT EnumMCodeProc (long lMCode, bool, void *pData)
{
	ASSERT (0 != lMCode);
	ASSERT (NULL != pData);
	ASSERT (NULL != g_pHelper);

	TRY {                                    
	CString cbBuffer ('\0', _MAX_PATH);
	CString cbKText;

		if (!g_pHelper -> GetKText (cbKText, 'm', lMCode))
			return true;	// trotzdem weitermachen

	// Zeichenkette formatieren
		if (DEX_GetMkBase() == 10) {
			cbBuffer.Format ("%08ld:%s", lMCode, (LPCSTR)cbKText);
			((CComboBox *)pData) -> AddString (cbBuffer);
		}
		else {
			cbBuffer.Format ("%08lx:%s", lMCode, (LPCSTR)cbKText);
			((CComboBox *)pData) -> AddString (cbBuffer);
		}
	}
	CATCH (CMemoryException, e) {
		DEX_Error (0, EC_NOMEMORY); 
		return false;
	}                  
	END_CATCH

return true;
}
