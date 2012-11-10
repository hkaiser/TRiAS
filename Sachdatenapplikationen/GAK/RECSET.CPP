// recset.cpp : implementation of the CRecordsetExt class
//

#include "stdafx.h"			// prec. Header
#include "res.h"			// Ressource-Konstanten
#include "recset.h"			// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErzeugerSet implementation

IMPLEMENT_DYNAMIC(CRecordsetExt, CRecordset)

CRecordsetExt:: CRecordsetExt(CDatabase* pdb)
			  : CRecordset(pdb)
{
}

CRecordsetExt :: ~CRecordsetExt ()
{
	if (IsOpen ())
		Close ();
}

// 	lese Anz. aller im Set enth. Sätze    
// 	lese ab aktueller Position im Set
//	gehe dann wieder auf 1. Satz
long CRecordsetExt :: GetRecordCount (BOOL bMoveToFirstRecord)
{               
	DWORD dwRowsMoved = 1;
	WORD wStatus = SQL_ROW_SUCCESS;
	RETCODE nRetCode= SQL_SUCCESS;
	long lRow = 0;
	
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
			lRow++;	
	}		
	         
//	gehe ggf. wieder zum 1. Satz	         
	if (bMoveToFirstRecord)
	{	
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
				}
				CATCH (CDBException, dbe)										
				{
					THROW_LAST ();
					return -1;                    
				}
				END_CATCH 			
			}			             
			END_CATCH 
		}		
	}		
	    
	return lRow;
}

//	alle Datenätze im Set löschen
void CRecordsetExt ::DeleteAll (const CString &strWhere)
{
	ASSERT (IsOpen ());
	ASSERT (!strWhere.IsEmpty ());
	ASSERT (!m_strTableName.IsEmpty ());

	CWaitCursor wc;
	try
	{
		CString strSQL;
		AfxFormatString2 (strSQL, IDS_DELETE_FROM, m_strTableName, strWhere);
		m_pDatabase->ReplaceBrackets (strSQL.GetBuffer(0));
		m_pDatabase->ExecuteSQL (strSQL);
	}
	catch (CDBException *db)
	{
		db->ReportError ();
		db->Delete ();
	}
}

                 