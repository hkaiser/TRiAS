// tableset.hpp : interface of the CTables class
//  
// Lese alle Tabellen zum gegebenen Data-Source-Objekt.	
// Stand vom 27.08.1996

#include "stdafx.h"			// vorübersetzter Header
#include <tableset.hpp>		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTables implementation
CTables :: CTables(CDatabase* pDatabase)
		 : CRecordset(pDatabase)
{
	//{{AFX_FIELD_INIT(CTables)
	m_strQualifier = "";
	m_strOwner = "";
	m_strName = "";
	m_strType = "";
	m_strRemarks = "";
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_strQualifierParam = "";
	m_strOwnerParam = "";
	m_strNameParam = "";
	m_strTypeParam = "'TABLE'";
}

CTables :: ~CTables (void)
{
	Close ();
}

BOOL CTables :: Open (UINT nOpenType /* = snapshot */,
					  LPCSTR lpszSQL /* = NULL */, DWORD dwOptions /* = none */)
{
#ifdef WIN32
	
	ASSERT(lpszSQL == NULL);
	RETCODE	nRetCode;

	// Cache state info and allocate hstmt
	SetState(nOpenType,NULL,noDirtyFieldCheck);
	if (!AllocHstmt())
		return FALSE;

	TRY
	{
		OnSetOptions(m_hstmt);
		AllocStatusArrays();

		// call the ODBC catalog function with data member params
		AFX_SQL_ASYNC(this, (::SQLTables)(m_hstmt,
			(m_strQualifierParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strQualifierParam), SQL_NTS,
			(m_strOwnerParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strOwnerParam), SQL_NTS,
			(m_strNameParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strNameParam), SQL_NTS,
			(m_strTypeParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strTypeParam), SQL_NTS));
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
				/*
				if (m_pDatabase)      
				{
					delete m_pDatabase;
					m_pDatabase = NULL;	
				}
				*/					
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
		AFX_SQL_ASYNC(this, (::SQLTables)(m_hstmt,
			(m_strQualifierParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strQualifierParam), SQL_NTS,
			(m_strOwnerParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strOwnerParam), SQL_NTS,
			(m_strNameParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strNameParam), SQL_NTS,
			(m_strTypeParam.IsEmpty()? (UCHAR FAR *)NULL: (UCHAR FAR *)(const char*)m_strTypeParam), SQL_NTS));
		if (!Check(nRetCode))
		{
			AfxThrowDBException(nRetCode, m_pDatabase, m_hstmt);
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
#endif		// WIN16
}

void CTables :: Close (void)
{
	if (IsOpen ())
		CRecordset :: Close ();
}

CString CTables::GetDefaultConnect()
{
	return "ODBC;";
}

CString CTables::GetDefaultSQL()
{
	// should SQLTables directly, so GetSQL should never be called
	ASSERT(FALSE);
	return "!";
}

void CTables::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTables)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, "table_qualifier", m_strQualifier);
	RFX_Text(pFX, "table_owner", m_strOwner);	
	RFX_Text(pFX, "table_name", m_strName);
	RFX_Text(pFX, "table_type", m_strType);
	RFX_Text(pFX, "remarks", m_strRemarks);
	//}}AFX_FIELD_MAP
}
