//	File: HELPTEXT.CPP
//	Erabeitet: J. Benkenstein 			Stand vom 13.10.1994

#include "pheader.h"			// vorübersetzter Header
#include "odbcext.hr"	// Resourcen-Konstante

#include <hpp/objinfo.hpp>			// KurzTextLen 
#include <hpp/helptext.hpp>			// zugeh. Header
#include "fakename.h"

BOOL CHelpText :: InitFont (void)
{                              
#ifdef WIN32
    if (IsWin40())
   		return True;
#endif // WIN32
                             
	TRY
	{               
		CString strFont;
	 	if (!strFont.LoadString (IDS_DESCRIPTION_FONT))
	 		AfxThrowResourceException ();
	
		if (!m_hWnd)
			return FALSE;
			     
		if (m_Font.CreateFont (-12,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,
					   	   	   OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY, 
					   	       FF_SWISS | DEFAULT_PITCH, strFont))
		{					   	         
			SetFont (&m_Font); 
			m_Font.Detach ();
			return TRUE;
		}				
	}		
	CATCH (CResourceException, re)
	{                                          
		DEX_Error (RC_CommonODBC, EC_NORESOURCE);
	}
	AND_CATCH (CMemoryException, me)	// hier nur auffangen 
	{            
		DEX_Error (RC_CommonODBC, EC_NOMEMORY);
	}                
	END_CATCH
	
	return FALSE;
}					 	   
                         
//	Resstring ausgeben                         
BOOL CHelpText :: Output (uint ResId)
{
	CString strText;
	TRY
	{
//	JG hier kommen Ressourcen runter die den AppNamen enthalten, deshalb ...
		
		strText	= FakeName(ResId);
//	 	strText.LoadString (ResId);


	}
	CATCH (CMemoryException, me)	// hier nur auffangen 
	{                           
		return FALSE;
	}                
	END_CATCH

	SetWindowText (strText);
	return TRUE;
}

//	Beschreibung über Merkmal/Objektklasse ausgeben 
BOOL CHelpText :: OutputDescription (ulong lKode, char cType, uint ResId)
{                  
//	prüfe Parameter
	if ((lKode == 0) || ((cType != 'i') && (cType != 'm')))		// ungültiger Typ
		return FALSE;

	TRY	{	
	PBDDATA pbdData;            
	char KText [KurzTextLen] = "";
	CString strLangText;
	char *pLangText = strLangText.GetBuffer (LangTextLen);

		INITSTRUCT(pbdData, PBDDATA);
		*pLangText = '\0';
		pbdData.dwSize = sizeof(PBDDATA);
		pbdData.pbdTyp = cType;
		pbdData.pbdCode = lKode;
		pbdData.pbdKText = KText;
		pbdData.pbdKTextLen = sizeof(KText) - 1;
		pbdData.pbdLText = pLangText;
		pbdData.pbdLTextLen = LangTextLen - 1;		
		
	//	wenn Information in TRIAS vorhanden		
		if (DEX_GetPBDData (pbdData) == EC_OKAY) {                          
		//	prüfe LangTextinhalt vom LangText
			if (!pLangText || !*pLangText)
				pLangText = KText;

		//	prüfe max. Darstellungslänge für Control
			if (lstrlen (pLangText) > maxLangTextShowLen) {
			CString strTruncated;
			
				strTruncated.LoadString (IDS_STRING_TRUNCATED);
				pLangText [maxLangTextShowLen - strTruncated.GetLength () - 1] = '\0';
				lstrcat (pLangText, strTruncated);
			}

		CString strFormat;
		
			strFormat.LoadString (ResId);		// Format lesen	

		CString strBuffer;
		char *pBuffer = strBuffer.GetBuffer (lstrlen (pLangText) +  strFormat.GetLength () + 20);

			wsprintf (pBuffer, strFormat, pLangText);
			SetWindowText (pBuffer); 				
		}
		else
			SetWindowText ("");		// alte Info nur löschen
		return TRUE;
	}
	CATCH (CMemoryException, me)
	{         
		DEX_Error (RC_OdbcExtension, EC_NOMEMORY);
	}                                   
	END_CATCH

	return FALSE;
}		                    

