/*
FILE: TABLINFO.CPP

Das Modul stellt allgemeine Klassen für die Verwaltung und Darstellung 
von ODBC-Tabellen bereit.

Erarbeitet: J. Benkenstein 					Stand vom: 30.10.1994
*/
                            	
#include "pheader.h"			// vorübersetzter Header
#include "odbcext.hr"			// Resource-Konstanten

#include <string.h>			// strchr ()
#include <hpp/getodbci.hpp>
#include "database.hpp"			// CDataBaseEx                                                                
#include <hpp/odbcerr.hpp>      	// OdbcError 
#include <hpp/columnst.hpp>			// CColumns                                              
#include <hpp/waitcur.hpp>			// CWaitCursor
                                              
#include "tablinfo.hpp"			// zugeh. Header  

#if _MSC_VER >= 1200	// ????
#pragma warning(disable: 4273)
int __cdecl lstrcmp (void *p1, void *p2)
{
	return strcmp((char *)p1, (char *)p2); 
}
#pragma warning(default: 4273)
#endif // _MSC_VER >= 1200

// 	lokale Funktionen
void * __export GetTableName (void *pObj)
{
	return (void *) (((CColumns *) pObj) -> m_strTableNameParam.operator const char *());
}

//	CTableInfo ---------------------------------------------------------------------
//                                                           
CTableInfo::CTableInfo (CDatabase *pDataBase, const char *pTableName)
			: CColumns (pDataBase)
{                                             
//	prüfe Parameter
	if (!pDataBase || !pTableName || !*pTableName)
	{
		DEX_Error (RC_CTableInfo, m_ErrCode = EC_ILLPARS);		
		return;
	}		
	
	m_ErrCode = EC_OKAY;						// erstmal alles OKAY

	TRY
	{                              
		m_strTableNameParam = pTableName;        // Namen für ODBC speichern
		// m_strTableNameParam.MakeUpper ();		 // alles in Großbuchstaben wandeln
		if (! Open ())              			 // wenn Tabelle nicht geöffnet
			m_ErrCode = EC_SYSERROR;			 // werden kann	
	}
	CATCH (CDBException, dbe)
	{                               
		m_ErrCode = EC_SYSERROR;
		OdbcError oe (dbe);
		oe.Show (RC_CTableInfo);                                     
	}
	AND_CATCH (CMemoryException, mce)
	{               
		DEX_Error (RC_CTableInfo, m_ErrCode = EC_NOMEMORY);		
	}
	END_CATCH
}                       

CTableInfo::~ CTableInfo (void)
{              
	// nothing to do
}

// Beschreibungs-Information eines Feldes (Typ und Länge) ausgeben	                                   
ErrCode CTableInfo::OutputDescription (CEdit &stDescription, const char *pFieldName)
{
//	prüfe interne Parameter
	if (m_ErrCode != EC_OKAY)
		return m_ErrCode;
		
//	prüfe übergebene Parameter
	if (! pFieldName || ! *pFieldName)
	{
		DEX_Error (RC_CTableInfo, m_ErrCode = EC_ILLPARS);
		return m_ErrCode;
	}			         
	
//	Feld suchen	
	CWaitCursor wc;	                        
	m_ErrCode = WC_NOVALFOUND; 	// kein Wert gefunden
	TRY
	{            
		MoveFirst ();					// zum 1. Feld
		while (! IsEOF ())
		{   
		//	wenn Feld gefunden                       
			if (m_strColumnName.CompareNoCase (pFieldName) == 0)
			{                   
			//	Kommentar bilden
				CString strFormat;    
				strFormat.LoadString (IDS_FIELDESCRIPTIONFORMAT);
				char Buffer [80] = "";                              
				char LenBuffer [20] = "";
				ltoa (m_lLength, LenBuffer, 10);   
				wsprintf (Buffer, strFormat, m_strTypeName);
				lstrcat (Buffer, LenBuffer);
				stDescription.SetWindowText (Buffer);
				m_ErrCode = EC_OKAY;		
				break;				// Suche beenden		
			}			
			MoveNext ();				// zum nächsten Feld
		}				 					
	}        
	CATCH (CDBException, dbe)
	{		 
		OdbcError Err (dbe);
		Err.Show (RC_CTableInfo);
		m_ErrCode = EC_SYSERROR;
	}		
	AND_CATCH (CMemoryException, me)
	{                                                     
		DEX_Error (RC_CTableInfo, m_ErrCode = EC_NOMEMORY);
	}                     
	AND_CATCH (CFileException, me)
	{                                                       
		// DEX_Error (RC_OutputColumnNamesCODBCInfos, m_ErrCode = EC_SYSERROR);
		m_ErrCode = EC_SYSERROR;
		me -> ReportError ();
	}
	END_CATCH	                 

	return m_ErrCode;	
}               

// alle möglichen Recherche-Felder in eine Listbox ausgeben
ErrCode CTableInfo::OutputRechercheFields (
	CListBox &lbListBox, int &MaxStringLen, BOOL bOutputTableName)
{
//	prüfe interne Parameter
	if (m_ErrCode != EC_OKAY)
		return m_ErrCode;
		     
	TRY	{		            
	CString strFullName;                  
	
		MoveFirst ();			// zum 1. Feld		
		while (!IsEOF ()) {                          
		// nur "ausgesuchte" Felder für Kopplung
			switch (m_nDataType) {                                 
				case SQL_SMALLINT:
				case SQL_INTEGER:
				case SQL_REAL:
				case SQL_FLOAT:
				case SQL_DOUBLE:
				case SQL_DATE:
				case SQL_TIME:
				case SQL_TIMESTAMP:
				case SQL_DECIMAL:  
				case SQL_NUMERIC:  
				case SQL_CHAR:
				case SQL_VARCHAR:
				{                        
				//	ggf. Tabellen-Namen vorne anfügen
					if (bOutputTableName)
					{
						strFullName = m_strTableNameParam;
						strFullName += TableSQLSepStr;
					}
					strFullName += m_strColumnName;
				
				// strFullName.MakeUpper ();				// nur Großbuchstaben			
				MaxStringLen = max (MaxStringLen, strFullName.GetLength ());											
				
					if (lbListBox.AddString (strFullName) < 0)
					{
						DEX_Error (RC_CTableInfo, m_ErrCode = EC_NOMEMORY);
						break;
					}                           
				}								
			}
			
		//  zum nächsten Feld						
			MoveNext ();
			strFullName.Empty ();
		}	// end_while
	}		// end_TRY	                     
	CATCH (CDBException, dbe)
	{
		OdbcError Err (dbe);
		Err.Show (RC_CTableInfo);
		m_ErrCode = EC_SYSERROR;
	}		
	AND_CATCH (CMemoryException, me)
	{                                                     
		DEX_Error (RC_CTableInfo, m_ErrCode = EC_NOMEMORY);
	}                     
	AND_CATCH (CFileException, me)
	{                                                       
		// DEX_Error (RC_OutputColumnNamesCODBCInfos, m_ErrCode = EC_SYSERROR);
		me -> ReportError ();
	}
	END_CATCH	                 
                     
	return m_ErrCode;
}
                    
// CTableInfoTree ----------------------------------------------------------------
//                    
CTableInfoTree::CTableInfoTree (CDatabase *pDataBase)
				: CTree (GetTableName)
{   
	m_ErrCode = EC_OKAY;	
                        
//	prüfe Parameter
	if (!pDataBase)
	{
		DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_ILLPARS);
		m_pDataBase = NULL;
		return;
	}	        

	m_pDataBase = pDataBase;
}				                

CTableInfoTree::~ CTableInfoTree (void)
{
	EveryDelete ();
}

void __export CTableInfoTree::UserDelete (void *pObj)
{
	((CTableInfo *)pObj) -> ~CTableInfo();
}
        
//	TabellenInfo-Objekte erzeugen: Tabellen-Namen durch Komma getrennt
ErrCode CTableInfoTree::CreateTables (const char *pTableNames)
{
//	prüfe Parameter
	if (m_ErrCode != EC_OKAY)
		return m_ErrCode;
	
	if (!pTableNames ||!*pTableNames)
	{
		DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_ILLPARS);
		return m_ErrCode;
	}	       
	
	CWaitCursor wc;	              // Sanduhr          
	
//	für alle Tabellen Objekte erzeugen
	TRY 
	{
		CString strTableNames (pTableNames);	// Puffer aller Namen
		CString strActTable;					// akt. Tabellen-Name
		const char *pActTable = pTableNames;	// Puffer-Zeiger
		char *pKomma = NULL;        			// Separator-Zeiger
		short sCnt = 0;							// akt. NamensLänge
		CTableInfo *pTableInfo = NULL;			// akt. CTableInfo-Objekt
		while (*pActTable)
		{
			pKomma = strchr (pActTable, TableSep);
			sCnt = pKomma ? pKomma - pActTable : lstrlen (pActTable);
			strActTable = strTableNames.Mid (pActTable - pTableNames, sCnt);
			
		//	Objekt erzeugen			
			CTableInfoCreator Cr (*this);  
			pTableInfo =::ContCreate (Cr, CTableInfo) (m_pDataBase, strActTable);
			if ((m_ErrCode = pTableInfo -> Result ()) != EC_OKAY)
				break;
				
		//	Zeiger weiter setzen
			pActTable += sCnt;							
			if (*pActTable == TableSep)		// nicht auf letzten Separator
				pActTable++;
		}		
	}
	CATCH (CMemoryException, me)
	{                           
		DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_ILLPARS);
	}
	END_CATCH		
	                    
	return m_ErrCode;	                    
}			

// Recherche-Felder aller Tabellen ausgeben	                                      
ErrCode CTableInfoTree::OutputRechercheFields (CListBox &lbListBox, int &MaxStringLen)
{
//	prüfe interne Parameter
	if (m_ErrCode != EC_OKAY)
		return m_ErrCode;
		
	if (Count () == 0)   // keine Einträge vorhanden
	{
		DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_ILLPARS);
		return m_ErrCode;
	}			                                    
	                                        
	CWaitCursor wc;	              // Sanduhr          		                                        
	                                        
//	Table-Namen mit ausgeben ?
	BOOL bOutTableName = Count () > 1 ? TRUE : FALSE;
	                  
//	alle Felder ausgeben	                  
	CTable tb (*this);  
	for (tb.First (); tb.Valid (); tb.Next ())
	{
		CTableInfoLock pTableInfo (tb);
		if (!pTableInfo)
		{
			DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_LOCKERROR);
			break;
		}            
		
		if ((m_ErrCode = pTableInfo -> OutputRechercheFields (
						 lbListBox, MaxStringLen, bOutTableName)) != EC_OKAY)
			break;						 	
	}
		
	return m_ErrCode;	
}

// Beschreibungs-Information eines Feldes (Typ und Länge) ausgeben	                                   
ErrCode CTableInfoTree::OutputDescription (CEdit &stField, const char *pTableFieldName)
{
//	prüfe interne Parameter
	if (m_ErrCode != EC_OKAY)
		return m_ErrCode;
		
//	prüfe übergebene Parameter
	if (!pTableFieldName ||!*pTableFieldName)
	{
		DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_ILLPARS);
		return m_ErrCode;
	}			     
	
	TRY
	{
	//	Namen bilden
		CString strFullName (pTableFieldName);     // Tabellen- und Feldname: "test.feld1"
		CString strTableName;				  // Tabellen-Name			
		CString strFieldName;				  // FeldName	
		short sPos = -1;                      // nicht gefunden
		if ((sPos = strFullName.Find (TableSQLSep)) != -1)	// Separator gefunden ?
		{
			strTableName = strFullName.Left (sPos);	                               
			// strTableName.MakeUpper ();
			strFieldName = strFullName.Right (strFullName.GetLength () - sPos - 1);
			// strFieldName.MakeUpper ();
		}			
		else	// kein Feldname vorhanden
		{
			DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_ILLPARS);
			return m_ErrCode;		
		}

	//	Tabelle suchen
		CTable tb (*this);
		const char *pTableName = strTableName;
		if (! tb.Find ((void *) pTableName))
		{                           
			DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_SYSERROR);
			return m_ErrCode;		
		}   
		                             
	//	jetzt Info ausgeben		                             
		CTableInfoLock pTableInfo (tb);
		if (! pTableInfo)
		{                           
			DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_LOCKERROR);
			return m_ErrCode;		
		} 
		
		m_ErrCode = pTableInfo -> OutputDescription (stField, strFieldName);
	
	}	    
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_CTableInfoTree, m_ErrCode = EC_ILLPARS);	
	}	                                                        
	END_CATCH
	    
	return m_ErrCode;
}       
