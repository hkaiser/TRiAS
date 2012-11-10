/*
File: COLUMNST.CPP
- lese Spaltennamen und -typ und weitere Parameter einer ODBC-Tabelle.

Erarbeitet: J.Benkenstein					Stand vom 14.1.1997
*/
                                                 
#include "stdafx.h"			//	prec. Header                                            
#include "columnst.h"		// 	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColumns implementation

CColumns :: CColumns (CDatabase* pDatabase)
		  : CRecordset (pDatabase)
{
	//{{AFX_FIELD_INIT(CColumns)
	m_strQualifier = "";
	m_strOwner = "";
	m_strTableName = "";
	m_strColumnName = "";
	m_nDataType = 0;
	m_lLength = 0;
	m_strTypeName = "";
	m_lPrecision = 0;
	m_lLength = 0;
	m_nScale = 0;
	m_nRadix = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_strQualifierParam = "";
	m_strOwnerParam = "";
	m_strTableNameParam = "";
	m_strColumnNameParam = "";
}       

CColumns ::~CColumns()
{
	if (IsOpen ())
		Close ();
}

CString CColumns::GetDefaultConnect()
{
	// this minimal connect string will cause ODBC login dialog to be brought up
	return "ODBC;"; // DSN=BGS-Abgleich - FoxPro;";
}

CString CColumns::GetDefaultSQL()
{
	// there  is no default SQL - a direct ODBC call is made instead
	// ASSERT(FALSE);
	return "!";
}

void CColumns::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CColumns)
	pFX->SetFieldType(CFieldExchange::outputColumn);              
	
	RFX_Text(pFX, "table_qualifier", m_strQualifier);
	RFX_Text(pFX, "table_owner", m_strOwner);
	RFX_Text(pFX, "table_name", m_strTableName);
	RFX_Text(pFX, "column_name", m_strColumnName);
	RFX_Int(pFX, "data_type", m_nDataType);
	RFX_Text(pFX, "type_name", m_strTypeName);
	RFX_Long(pFX, "precision", m_lPrecision);
	RFX_Long(pFX, "length", m_lLength);
	RFX_Int(pFX, "scale", m_nScale);
	RFX_Int(pFX, "radix", m_nRadix);
	RFX_Int(pFX, "nullable", m_nNullable);
	//}}AFX_FIELD_MAP
}

BOOL CColumns::Open(UINT nOpenType /* = snapshot */,
					LPCSTR lpszSQL /* = NULL */, DWORD dwOptions /* = none */)
{
#ifdef WIN32

	ASSERT(lpszSQL == NULL);
	RETCODE	nRetCode;

	// Cache state info and allocate hstmt
	SetState(nOpenType,NULL,noDirtyFieldCheck | dwOptions);
	if (!AllocHstmt())
		return FALSE;

	TRY
	{
		OnSetOptions(m_hstmt);
		AllocStatusArrays();

		// call the ODBC catalog function with data member params
		AFX_SQL_ASYNC(this, ::SQLColumns(m_hstmt,
			(m_strQualifierParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strQualifierParam), SQL_NTS,
			(m_strOwnerParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strOwnerParam), SQL_NTS,
			(m_strTableNameParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strTableNameParam), SQL_NTS,
			NULL, SQL_NTS));
		if (!Check(nRetCode))
			ThrowDBException(nRetCode, m_hstmt);

		// Allocate memory and cache info
		AllocAndCacheFieldInfo();
		AllocRowset();

		// Fetch the first row of data
		MoveNext();

		// If EOF, result set is empty, set BOF as well
		m_bBOF = m_bEOF;
	}

	CATCH_ALL(e)
	{
		Close();
		THROW_LAST();
	}
	END_CATCH_ALL

	return TRUE;

#else		// WIN16

	RETCODE nRetCode;
	ASSERT(lpszSQL == NULL);

	// Allocation and opening of database not supported
	if (m_hstmt == SQL_NULL_HSTMT)
	{
		CString strDefaultConnect;
		TRY
		{
			if (m_pDatabase == NULL)
			{
				m_pDatabase = new CDatabase();
				m_bRecordsetDb = TRUE;
			}

			strDefaultConnect = GetDefaultConnect();
			// If not already opened, attempt to open
			if (!m_pDatabase->IsOpen() &&
				!m_pDatabase->Open("", FALSE, FALSE, strDefaultConnect))
				return FALSE;

			AFX_SQL_SYNC(::SQLAllocStmt(m_pDatabase->m_hdbc, &m_hstmt));
			if (!Check(nRetCode))
				ThrowDBException(SQL_INVALID_HANDLE);
		//		return FALSE;					#JB951122
		}
		CATCH_ALL(e)
		{
#ifdef _DEBUG
			if (afxTraceFlags & 0x20)
				TRACE0("Error: CDatabase create for CRecordset failed\n");
#endif // _DEBUG
			strDefaultConnect.Empty();
			if (m_bRecordsetDb)
			{
				DELETE_OBJ (m_pDatabase);
			}
			ASSERT(m_hstmt == SQL_NULL_HSTMT);
			THROW_LAST();
		}
		END_CATCH_ALL
	}

	TRY
	{
		// set any options, like timeouts, scrolling options
		OnSetOptions(m_hstmt);

		// call the ODBC catalog function with data member params
		RETCODE nRetCode;
		AFX_SQL_ASYNC(this, ::SQLColumns(m_hstmt,
			(m_strQualifierParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strQualifierParam), SQL_NTS,
			(m_strOwnerParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strOwnerParam), SQL_NTS,
			(m_strTableNameParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strTableNameParam), SQL_NTS,
			NULL, SQL_NTS));
		if (!Check(nRetCode))
		{
			AfxThrowDBException(nRetCode, m_pDatabase, m_hstmt);
			// return FALSE;		//#JB951122
		}
		// load first record
		MoveFirst();
	}   
	CATCH_ALL(e)
	{
		Close();
		THROW_LAST();
	}
	END_CATCH_ALL
	return TRUE;
#endif			// WIN16
}                     

//	Suche Feldnamen
BOOL CColumns :: FieldExists (const char *pFieldName, int iType, long lLen)
{
	ASSERT (NULL != pFieldName && AfxIsValidString (pFieldName));
                                    
	TRY
	{                                    
		CWaitCursor wc;	                // Sanduhr ein
		MoveLast ();
		MoveFirst ();					// zum 1. Feld

	//	Felder suchen		
		while (! IsEOF ())
		{               
			if ((0 == strcmpi (pFieldName, m_strColumnName)) && (iType == m_nDataType))
			{
				if (lLen > 0)   
				{
					if (m_lLength >= lLen)
						return TRUE;
				}						
				else
					return TRUE;
			}
		                             
			MoveNext ();				// zum nächsten Feld
		}	
	}
	CATCH_ALL(e)
	{               
		THROW_LAST ();		
	}
	END_CATCH_ALL		
	
	return FALSE;
}                                                                  
