/*
File: COLUMNST.HPP
- lese Spaltennamen und -Typ und weitere Parameter einer ODBC-Tabelle.

Erarbeitet: J.Benkenstein					Stand vom 14.1.1997
*/
                                                         
#ifndef _COLUMNST_HPP
#define _COLUMNST_HPP

class CColumns : public CRecordset
{
public:       
    CColumns (CDatabase* pDatabase);
	~CColumns ();		// Set ggf. schlieﬂen
	BOOL Open (UINT nOpenType = snapshot, LPCSTR lpszSQL = NULL, 
			   DWORD dwOptions = none);	// Ereugt CDBException bei fatalem Fehler
			   
	BOOL FieldExists (const char *pFieldName, int iType, long lLen = -1);

// Field/Param Data
	//{{AFX_FIELD(CColumns, CRecordset)
	CString m_strQualifier;
	CString m_strOwner;
	CString m_strTableName;
	CString m_strColumnName;
	long m_lLength;
	int  m_nDataType;
	CString m_strTypeName;
	long m_lPrecision;
	int m_nScale;
	int m_nRadix;
	int m_nNullable;
	//}}AFX_FIELD

	// Table we're enumerating columns for
	CString m_strQualifierParam;
	CString m_strOwnerParam;
	CString m_strTableNameParam;
	CString m_strColumnNameParam;
	
// Implementation
protected:
	virtual CString GetDefaultConnect();    // default connection string
	virtual CString GetDefaultSQL();    	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
};

#endif 	// _COLUMNST_HPP
