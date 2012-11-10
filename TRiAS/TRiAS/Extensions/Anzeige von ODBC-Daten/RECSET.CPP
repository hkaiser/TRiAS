// recset.cpp : implementation file
// Stand vom 16. Mai 1994

#include "pheader.h"                    // vorübersetzter Header
#include "odbcext.hr"					// Resourcen-Konstanten

#include <hpp/odbcerr.hpp>                  // OdbcError 
#include <hpp/waitcur.hpp>                  // CWaitCursor 
#include <hpp/columnst.hpp>                 // CColumns
#include <hpp/collist.hpp>          		// CColumnObjArray                                                    
// #include <blobrfx.hpp>					// RFX_LongBinary2 ()
#include "recset.hpp"                  	// zugeh. Header

/////////////////////////////////////////////////////////////////////////////
// CRecSet
CRecSet :: CRecSet(CDatabase &Database, CColumnObjArray &CA, CString strWhere
#ifdef __UseOGX__
			, CString& strSQL	// bisher wurde selber geöffnet
#endif //__UseOGX__

			)
		 : CRecordset(&Database)
{
	//{{AFX_FIELD_INIT(CRecSet)
	m_nFields = (uint) CA.Count ();         
	//}}AFX_FIELD_INIT  
	
	m_pCA = &CA;                        // Zeiger auf SpaltenInfoArray merken
	m_strFilter = strWhere;               // WHERE-Klausel   
	m_bReadAll	= FALSE;				// LongBinary nicht lesen
	m_sLastRow = -1;					// zuletzt gelesene Satz-Nummer	
	m_bForwardOnly = FALSE;				// nicht nur vorwärts lesen
#ifdef __UseOGX__
	m_strExtSQL = strSQL;				// wen wollen wir denn
#endif //__UseOGX__

}

CRecSet :: ~CRecSet (void)
{
	Close ();	// im Destruktor der Basisklasse gemacht
}            

void CRecSet :: Close (void)
{
	if (IsOpen ())
		CRecordset :: Close ();
}

CString CRecSet::GetDefaultConnect()
{   
	CString strConnect;
	strConnect.LoadString (IDS_DEFAULTCONNECTION);
	return strConnect;
}

CString CRecSet::GetDefaultSQL()
{
	// JG hope to do this right, or why did he return here m_strFilter
#ifdef __UseOGX__
	return m_strExtSQL;
#else
	return m_strFilter;
#endif //__UseOGX__
}

void CRecSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP
						      
//      alle Spalten bearbeiten                                   
	CRing ri (*m_pCA);
	for (ri.First (); ri.Valid (); ri.Next ())
	{
		CColumnObjLock pCO (ri);
		if (pCO == NULL)
		{
			DEX_Error (RC_DoFieldExRecSet, EC_SYSERROR);
			continue;
		}                       
		else
		{   
			switch (pCO -> RFXType ())
			{              
				case AFX_RFX_TEXT:                          
					RFX_Text (pFX, pCO -> BracketsColName (), *((CString *) (pCO -> Value ())),
						 	  (int) pCO -> FieldLen (), pCO -> SQLType ());
				break;                                                          
				case AFX_RFX_INT:
					RFX_Int (pFX, pCO -> BracketsColName (), *((int *) (pCO -> Value ())));         
				break;
				case AFX_RFX_LONG:
					RFX_Long (pFX, pCO -> BracketsColName (), *((long *) (pCO -> Value ())));                                               
				break;
				case AFX_RFX_SINGLE:
					RFX_Single (pFX, pCO -> BracketsColName (), *((float *) (pCO -> Value ())));                                            
				break;
				case AFX_RFX_DOUBLE:
					RFX_Double (pFX, pCO -> BracketsColName (), *((double *) (pCO -> Value ())));                                           
				break;                                          
				case AFX_RFX_BYTE:              
					RFX_Byte (pFX, pCO -> BracketsColName (), *((BYTE *) (pCO -> Value ())));                                               
				break;                                                   
				case AFX_RFX_BOOL:              
					RFX_Bool (pFX, pCO -> BracketsColName (), *((BOOL *) (pCO -> Value ())));                                               
				break;
				case AFX_RFX_DATE:
					RFX_Date (pFX, pCO -> BracketsColName (), *((CTime *) (pCO -> Value ())));                                              
				break;
				case AFX_RFX_BINARY:
					RFX_Binary (pFX, pCO -> BracketsColName (), *((CByteArray *) (pCO -> Value ())));                       
				break;                                                                                                                                                                                                                          
				case AFX_RFX_LONGBINARY:
				{	// SQLGetData nur bei Bedarf rufen: dauert u.U. sehr lange
					if ((pFX -> m_nOperation != CFieldExchange :: Fixup) ||
						(m_bReadAll	 && pFX -> m_nOperation == CFieldExchange::Fixup))
					{						
						TRY 
						{						
                            RFX_LongBinary (pFX, pCO -> BracketsColName (), *((CLongBinary *) (pCO -> Value ())));
						}
						CATCH (CMemoryException, me)
						{
							DEX_Error (RC_RefreshCRecSet, EC_NOMEMORY);
						}
						END_CATCH
					}
					else
					{   
						UINT nField;
						if (! pFX->IsFieldType(&nField))		// interner Feldzähler erh.
							return;
					}						
				}					
				break;
				default:
				{
					DEX_Error (RC_DoFieldExRecSet,  EC_UNKN_FIELD_TYPE);
				}                                       
				break;                          
			}
		}                       
	}
}
    
// lese Anz. aller im Set enth. Sätze    
// lese ab aktueller Position im Set
long CRecSet :: GetRecordCount (void)
{               
	DWORD dwRowsMoved = 1;
	WORD wStatus = SQL_ROW_SUCCESS;
	RETCODE nRetCode= SQL_SUCCESS;
	long sRow = 0;
	
	for (; nRetCode == SQL_SUCCESS || nRetCode == SQL_SUCCESS_WITH_INFO;)
	{
		if (m_bScrollable)
		{
			AFX_SQL_ASYNC(this, ::SQLExtendedFetch(m_hstmt, SQL_FETCH_NEXT, 
										    	   0L, &dwRowsMoved, &wStatus));
		}
		else
		{   
			AFX_SQL_ASYNC(this, ::SQLFetch(m_hstmt));
		}
		
		if (wStatus != SQL_ROW_DELETED)
			sRow++;	
	}		
	         
//	gehe wieder zum 1. Satz	         
	if (m_bScrollable)
	{
		AFX_SQL_ASYNC(this, ::SQLExtendedFetch(m_hstmt, SQL_FETCH_FIRST, 
									    	   	   0L, &dwRowsMoved, &wStatus));			
	}			
	else
	{
		TRY
		{       
			MoveFirst ();
		}   
		CATCH (CDBException, dbe)
		{            
			TRY 
			{						
				Requery ();         	// vielleicht geht's mit einer erneuten Abfrage
				m_bForwardOnly = TRUE;
			}
			CATCH (CDBException, dbe)										
			{
				OdbcError oe (dbe);
				oe.Show (RC_GetRecCntCRecSet);                 
				return -1;                    
			}
			END_CATCH 			
		}			             
		END_CATCH 
	}		
	    
	return --sRow;
}
                 
//	aktuellen Satz mit LongBinary-Feldern lesen
BOOL CRecSet :: RefreshAllFields (short sActRow)
{                                   
	if (m_sLastRow == sActRow)		// Satz bereits gelesen
		return TRUE;
                
	m_bReadAll	 = TRUE;  

	TRY
	{
		CWaitCursor wc; 			// Sanduhr ein             
		CFieldExchange fx(CFieldExchange::Fixup, this);
		fx.m_hstmt = m_hstmt;
		DoFieldExchange(&fx);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_RefreshCRecSet, EC_NOMEMORY);
		return FALSE;
	}
	AND_CATCH (CDBException, dbe)
	{
		OdbcError oe (dbe);
		oe.Show (RC_RefreshCRecSet);  
		return FALSE;               		
	}		                         
	END_CATCH
	
	m_sLastRow = sActRow;		// Satz-Nummer speichern
	m_bReadAll	 = FALSE;

	return TRUE;
}	
