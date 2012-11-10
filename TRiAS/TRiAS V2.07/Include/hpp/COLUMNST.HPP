/*
File: COLUMNST.HPP
- lese Spaltennamen und -Typ und weitere Parameter einer ODBC-Tabelle.

Erarbeitet: J.Benkenstein					Stand vom 24.3.1993
*/
                                                         
#ifndef _COLUMNST_HPP
#define _COLUMNST_HPP

enum SQL_Type { Text, Date, Other };
                                                        
// prüfe Typekompatibilität (RFX-Typ)                                                        
BOOL RFXTypesCompatible (short sType1, short sType2);	

// prüfe Typekompatibilität (SQL-Typ)                                                        
BOOL SQLTypesCompatible (short sType1, short sType2);
                                                         
class CColumns : public CRecordset
{
public:       
    CColumns (CDatabase* pDatabase = NULL);
	~CColumns (void);		// Set ggf. schließen
	BOOL Open (UINT nOpenType = snapshot, LPCSTR lpszSQL = NULL, 
			   DWORD dwOptions = none);	// Ereugt CDBException bei fatalem Fehler
	
	short GetSQLTyp (CWnd *pParent, const char *pFieldName); // lese SQL-Datentyp
        SQL_Type GetSqlType (CWnd *pParent, const char *pFieldName); // Text- oder Datumsfeld ?

	BOOL IsPropField (void);	// ist akt. Feld geeignet für Anzeige der Objekt-Eigensch.
	BOOL IsKoppelField (void);  // ist akt. Feld geeignet für TRIAS-Kopplung
	BOOL IsKoordField (void);	// ist akt. Feld geeignet für Koordinaten-Import

// Field/Param Data
	//{{AFX_FIELD(CColumns, CRecordset)
	CString m_strQualifier;
	CString m_strOwner;
	CString m_strTableName;
	CString m_strColumnName;
	int  m_nDataType;
	CString m_strTypeName;
	long m_lPrecision;
	long m_lLength;
	int m_nScale;
	int m_nRadix;
	int m_nNullable;
	//}}AFX_FIELD

	// Table we're enumerating columns for
	CString m_strQualifierParam;
	CString m_strOwnerParam;
	CString m_strTableNameParam;
	CString m_strColumnNameParam;
	
	uint m_nRFXType;				// RFX-Datentyp                   
	
// Implementation
protected:
	virtual CString GetDefaultConnect();    // default connection string
	virtual CString GetDefaultSQL();    	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
};

#endif 	// _COLUMNST_HPP
