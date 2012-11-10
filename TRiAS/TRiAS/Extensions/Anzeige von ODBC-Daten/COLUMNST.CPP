/*
File: COLUMNST.CPP
- lese Spaltennamen und -typ und weitere Parameter einer ODBC-Tabelle.

Erarbeitet: J.Benkenstein					Stand vom 27.08.1996
*/
                                                 
#include "pheader.h"		// vorübersetzte Header                                                 
#include "odbcext.hr"		// Resourcen-Konstanten

#include <hpp/odbcerr.hpp>		// OdbcError                                                                                 
#include <hpp/waitcur.hpp>		// CWaitCursor                                                 
#include <hpp/columnst.hpp>		// zugehöriger Header

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

CColumns :: ~CColumns (void)
{
}

CString CColumns::GetDefaultConnect()
{
	// this minimal connect string will cause ODBC login dialog to be brought up
	CString DefConnect;
	DefConnect.LoadString (IDS_DEFAULTCONNECTION);	
	return DefConnect;
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
	   
	// leider liefert ff. Zeile einen GP	   
	// m_nRFXType = pFX -> m_pfi -> nDataType;			// RFX-Typ lesen
	
	// deshalb wird zur Typ-Konvertierung ff. Code aus "dbcore.cpp" benutzt
	switch (m_nDataType)
	{
		case SQL_BIT:
			m_nRFXType = AFX_RFX_BOOL;
		break;
		
		case SQL_TINYINT:
			m_nRFXType = AFX_RFX_BYTE;
		break;

		case SQL_SMALLINT:
			m_nRFXType = AFX_RFX_INT;
		break;

		case SQL_INTEGER:
			m_nRFXType = AFX_RFX_LONG;
		break;

		case SQL_REAL:
			m_nRFXType = AFX_RFX_SINGLE;
		break;

		case SQL_FLOAT:
		case SQL_DOUBLE:
			m_nRFXType = AFX_RFX_DOUBLE;
		break;

		case SQL_DATE:
		case SQL_TIME:
		case SQL_TIMESTAMP:
			m_nRFXType = AFX_RFX_DATE;
		break;

		case SQL_BINARY:
		case SQL_VARBINARY:
			m_nRFXType = AFX_RFX_BINARY;
		break;

		case SQL_DECIMAL:   // ODBC default xfer type
		case SQL_NUMERIC:   // ODBC default xfer type
		case SQL_BIGINT:	// ODBC default xfer type
		case SQL_CHAR:
		case SQL_VARCHAR:
			m_nRFXType = AFX_RFX_TEXT;
		break;

		case SQL_LONGVARCHAR:
		case SQL_LONGVARBINARY:
			m_nRFXType = AFX_RFX_LONGBINARY;
		break;

		default:
			m_nRFXType = (uint) -1;		// unbekannter Typ
	}
}

//	Ist das akt. Feld geeignet für die Anzeige der Objekteigenschaften
BOOL CColumns :: IsPropField (void)
{
	switch (m_nRFXType)
	{
		case AFX_RFX_TEXT:                      
		case AFX_RFX_INT:
		case AFX_RFX_LONG:                                              
		case AFX_RFX_SINGLE:    
		case AFX_RFX_DOUBLE:
		case AFX_RFX_BYTE:                                             
		case AFX_RFX_BOOL:            
		case AFX_RFX_DATE:                 
			return TRUE;
		break;
	}	

	return FALSE;
}

//	Ist das akt. Feld geeignet für Ankopplung an TRIAS
BOOL CColumns :: IsKoppelField (void)
{
	switch (m_nRFXType)
	{
		case AFX_RFX_TEXT:                      
		case AFX_RFX_INT:
		case AFX_RFX_LONG:                                              
		case AFX_RFX_SINGLE:    
		case AFX_RFX_DOUBLE:
		case AFX_RFX_DATE:                 
			return TRUE;
		break;
	}	

	return FALSE;
}

//	Ist das akt. Feld geeignet für Import von Koordinaten
BOOL CColumns :: IsKoordField (void)
{
	switch (m_nRFXType)
	{
		case AFX_RFX_TEXT:                      
		case AFX_RFX_INT:
		case AFX_RFX_LONG:                                              
		case AFX_RFX_SINGLE:    
		case AFX_RFX_DOUBLE:
			return TRUE;
		break;
	}	

	return FALSE;
}

// lese SQL-Datentyp
short CColumns :: GetSQLTyp (CWnd *pParent, const char *pFieldName)
{
//	prüfe interne Parameter
	if (!pFieldName)
	{
		DEX_Error (RC_GetSQLTypeCColumns, EC_ILLPARS);
		return SQL_ERROR;
	}	        

	CWaitCursor wc;	                    // Sanduhr ein
	TRY
	{                
		MoveFirst ();					// zum 1. Feld

	//	Feld suchen		
		while (! IsEOF ())
		{                                            
		//	wenn Feld gefunden
			if (m_strColumnName.CompareNoCase (pFieldName) == 0)
				return m_nDataType;		// mit Typ zurück
			MoveNext ();				// zum nächsten Feld
		}	
	}        
	CATCH (CDBException, dbe)
	{		 
		OdbcError Err (dbe);
		Err.Show (RC_GetSQLTypeCColumns);
	}		
	AND_CATCH (CMemoryException, me)
	{                                                     
		DEX_Error (RC_GetSQLTypeCColumns, EC_NOMEMORY);
	}                     
	AND_CATCH (CFileException, me)
	{                                                       
		// DEX_Error (RC_GetSQLTypeCColumns, EC_SYSERROR);
		me -> ReportError ();
	}
	END_CATCH	                 

	return SQL_ERROR;		// nicht gefunden oder Fehler
}                                                                  
    
//	Text- oder Datumsfeld ?
SQL_Type CColumns :: GetSqlType (CWnd *pParent, const char *pFieldName)
{                             
	switch (GetSQLTyp (pParent, pFieldName))
	{
		case SQL_DATE:
		case SQL_TIME:
		case SQL_TIMESTAMP:
			return Date;
		case SQL_DECIMAL:   // ODBC default xfer type
		case SQL_NUMERIC:   // ODBC default xfer type
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_BIGINT:	// ODBC default xfer type
			return Text;
	}	
	
	return Other;
}

// prüfe Typekompatibilität (RFX-Typ)                                                        
BOOL RFXTypesCompatible (short sType1, short sType2)
{
	if (sType1 == sType2)		// auch bei unbekanntem Typ
		return TRUE;
		
	switch (sType1)
	{		
		case AFX_RFX_INT:    	// numerischen Typen 
		case AFX_RFX_LONG:		// sollen untereinander kompatibel sein
		case AFX_RFX_SINGLE:
		case AFX_RFX_DOUBLE:
		case AFX_RFX_BYTE:       
			if ((sType2 == AFX_RFX_LONG) ||
				(sType2 == AFX_RFX_SINGLE) ||
				(sType2 == AFX_RFX_DOUBLE) ||
				(sType2 == AFX_RFX_BYTE))
				return TRUE;				 
		break;
		case AFX_RFX_TEXT:      // mit keinem Typ kompatibel            
		case AFX_RFX_BOOL:            	
		case AFX_RFX_DATE:
		case AFX_RFX_BINARY:
		case AFX_RFX_LONGBINARY:
		default:
		break;				
	}
	return FALSE;
}
        
// prüfe Typekompatibilität (SQL-Typ)                                                        
BOOL SQLTypesCompatible (short sType1, short sType2)
{
	if (sType1 == sType2)			// auch bei unbekanntem Typ
		return TRUE;
		
	switch (sType1)
	{                                 
		case SQL_TINYINT:			// numerischer Wert
		case SQL_SMALLINT:
		case SQL_INTEGER:
		case SQL_REAL:
		case SQL_FLOAT:
		case SQL_DOUBLE:
			if ((sType2 == SQL_TINYINT) ||
				(sType2 == SQL_SMALLINT) ||
				(sType2 == SQL_INTEGER) ||
				(sType2 == SQL_REAL) ||
				(sType2 == SQL_FLOAT) ||
				(sType2 == SQL_DOUBLE))
				return TRUE;
		break;
		case SQL_DECIMAL:			// AFX_RFX_TEXT   
		case SQL_NUMERIC:  
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_BIGINT:
			if ((sType2 == SQL_DECIMAL) || 
				(sType2 == SQL_NUMERIC) || 
				(sType2 == SQL_CHAR) || 
				(sType2 == SQL_VARCHAR))
				return TRUE;
		break;
        case SQL_BIT:    			// Typen sind mit keinem
		case SQL_BINARY:			// anderen Typ kompatibel
		case SQL_VARBINARY:
		case SQL_LONGVARCHAR:
		case SQL_LONGVARBINARY:
		case SQL_DATE:
		case SQL_TIME:
		case SQL_TIMESTAMP:
		default:
			return FALSE;
	}                    
	
	return FALSE;
}

    
