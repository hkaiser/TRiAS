/*
Datei: CHKLAUSL.CPP

Earbeitet: J.Benkenstein 			Stand vom 30.10.1994
*/

#include "pheader.h"					// vorübersetzten Header
#include "odbcext.hr"					// Resource-Konstanten

#include <sqlext.h>						// SQLPrepare () u.a.
#include <ctype.h>						// isdigit () u.a.

#include <errinstx.hxx>					// ErrInstall             
#include <hpp/waitcur.hpp>					// CWaitCursor             
#include <hpp/getodbci.hpp>
#include "database.hpp"                 // CDataBaseEx
#include <hpp/chklausl.hpp>					// zugeh. Header

// Konstanten
const char MerkmalBeginChar = '{';   	 // Beginn und Ende-Zeichen eines
const char MerkmalEndChar = '}';	 	 // Merkmals
const char SQLPlaceHolder [] = "1.0";	 // Platzhalter für TRIAS-Merkmalskode	

// externe Variablen
extern int g_sMkBase;

//	- Anzahl der "{" gleich Anzahl "}"
// 	- innerhalb dieser Klammern nur Ziffern bzw. hex. Buchstaben ?
// 	- ist diese Ziffer ein gültiger Merkmalskode
//	- substituiere den Merkmals-Ausdrücke durch formale Parameter ("?")
//	- prüfe Klausel mit Hilfe der Funktion SQLExecute ()
BOOL __export CheckWhereKlausel (CDatabase *pDataBase, CString &strTableNames,
								 CString &strKlausel, CString &strError, 
								 short &sErrorPos)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//	prüfe Parameter
	if (!pDataBase || strTableNames.IsEmpty ())
	{   
		DEX_Error (RC_CheckWhereKlausel, EC_ILLPARS);
		return FALSE;
	}		                                    
	                
//	prüfe Inhalt der übergebenen Klausel	                
	if (strKlausel.IsEmpty ())
		return TRUE;  
    
    CWaitCursor wc;		// Sanduhr ein
    BOOL bRet = TRUE;	// bisher alles OK	    
    sErrorPos = -1;		// auf ungültigen Wert
    char *pResKlausel = NULL;	// Ergebnis-Klausel
    
	TRY
	{   
	//	prüfe TRIAS-Merkmal
		short sLen = strKlausel.GetLength ();
		short sMax = sLen * 2;
		pResKlausel = new char [sMax];
		memset (pResKlausel, 0, sMax);
		char *pBuffer = pResKlausel;

	PBDDATA pbdData;            

		memset (&pbdData, 0, sizeof (pbdData));
		pbdData.dwSize = sizeof(PBDDATA);
		pbdData.pbdTyp = 'm';        

	BOOL bDezBase = g_sMkBase == 10 ? True : False;
	ErrInstall TriasError (WC_NOMERKMAL);		// unbekannten MKode ignorieren
// KK000426
	BOOL bFound = FALSE;

		for (short i = 0; i < sLen; i++, pBuffer++)
		{                                 
			if (strKlausel.GetAt (i) != MerkmalBeginChar)  
			{
				*pBuffer = strKlausel.GetAt (i);
				continue;
			}		     
			
		//	öffnende geschweifte Klammer gefunden: existiert MerkmalsKode ?
		const char *pTemp = ((const char *) strKlausel) + i + 1; 
		ulong lMKode = strtoul (pTemp, NULL, g_sMkBase);

			if (lMKode == 0)	// hier kann z.B. "{ fn substring ... }" stehen
			{
				*pBuffer = strKlausel.GetAt (i);		// Zeichen übernehmen
				continue;							    // und weiter
			}				

			pbdData.pbdCode = lMKode;
			if (DEX_GetPBDData (pbdData) != EC_OKAY)
			{   
				DELETE_VEC (pResKlausel);
				strError.LoadString (IDS_UNKNOWN_MKODE);
				sErrorPos = i + 1;
				return FALSE;
			}
			
		//	suche nach schließender Klammer: sind Zeichen bis dahin Ziffern ?
			bFound = FALSE;
			while (*pTemp)
			{   
				if ((bDezBase && isdigit (*pTemp)) || 
					(!bDezBase && isxdigit (*pTemp)))
				{
					pTemp++;
					continue;			
				}			
				if (*pTemp == MerkmalEndChar)
				{
					bFound = TRUE;
					break;
				}					
				
			//	unbekanntes Zeichen
				strError.LoadString (IDS_KEINE_ZIFFER);
				sErrorPos = pTemp - strKlausel;				
				DELETE_VEC (pResKlausel);				
				return FALSE;
			}								
			
		//	Klammer gefunden ?
			if (!bFound)
			{   
				DELETE_VEC (pResKlausel);            
				strError.LoadString (IDS_NOSCHL_KLAMMER);
				return FALSE;
			}						
			
		//	jetzt sind Syntax und MerkmalsKode OK
			//*pBuffer = SQLPlaceHolder;	// Mermkalskode ersetzen: '?'
			lstrcat (pBuffer, SQLPlaceHolder); // Mermkalskode ersetzen: '1.0'
			pBuffer += (lstrlen (SQLPlaceHolder) - 1);
			
		//	jetzt Index hinter nächste geschweifte Klammer
			while ((i < sLen) && (strKlausel.GetAt (i) != MerkmalEndChar))
				i++;
		}   

	//	rufe SQL-Parser                                            
	RETCODE nRetCode;
	HSTMT hstmt;
	                         
		AFX_SQL_ASYNC (pDataBase, :: SQLAllocStmt (pDataBase -> m_hdbc, &hstmt));
		if (nRetCode != SQL_SUCCESS)
		{                
			DEX_Error (RC_CheckWhereKlausel, EC_NOMEMORY);
			DELETE_VEC (pResKlausel);
			return FALSE;
		}
	
	CString strSelect; 		

		AfxFormatString2 (strSelect, IDS_SELECT_WHERE, strTableNames, pResKlausel);	
		AFX_SQL_ASYNC (pDataBase, :: /*SQLPrepare*/SQLExecDirect (hstmt, 
												(UCHAR FAR*)(const char *)strSelect, 
											 	 SQL_NTS));
							
	//	ggf. SQL-Fehler auswerten
		switch (nRetCode)											 
		{                            
			case SQL_NEED_DATA:
			case SQL_SUCCESS:
			case SQL_SUCCESS_WITH_INFO:
			{
				strError.LoadString (IDS_OK_KRIT);
			}
			break;  
			case SQL_ERROR:
			{   
				bRet = FALSE;                    
				TRY
				{   
				//	Fehler-Meldung generieren
			    	AfxThrowDBException(nRetCode, pDataBase, hstmt); 
				}				
				CATCH (CDBException, dbe)
				{
					strError = dbe -> m_strError;
					
				//	ggf. \n ersetzen		
				/*			
					for (register short i = strError.Find ('\n'); i != -1;
										i = strError.Find ('\n'))										
						strError.SetAt (i, ',');										
				*/						
				}              
				END_CATCH
			}
			break;			
			case SQL_STILL_EXECUTING:
			case SQL_INVALID_HANDLE:
			default:         
			{
				bRet = FALSE;
				strError.LoadString (IDS_INTERNAL_ERROR);				
			}
		}		// end_switch

	//	SQL-Statement freigeben		                                       
		AFX_SQL_ASYNC (pDataBase, :: SQLFreeStmt (hstmt, SQL_DROP));			                                       
	}
	CATCH (CMemoryException, me)
	{                                                
		bRet = FALSE;
		DEX_Error (RC_CheckWhereKlausel, EC_NOMEMORY);                  
	}	
	END_CATCH 	
		
	DELETE_VEC (pResKlausel);			                                       
	return bRet;
}
