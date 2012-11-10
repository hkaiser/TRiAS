// tableset.hpp : interface of the CTables class
//  
// Lese alle Tabellen zum gegebenen Data-Source-Objekt.	
// Stand vom 4.10.1994

class CTables : public CRecordset
{
public:
	CTables(CDatabase* pDatabase = NULL);
	~CTables (void);	// Set ggf. schlieﬂen
	BOOL Open(UINT nOpenType = snapshot, LPCSTR lpszSQL = NULL, DWORD dwOptions = none);
	void Close (void);

// Field/Param Data
	//{{AFX_FIELD(CTables, CRecordset)
	CString m_strQualifier;
	CString m_strOwner;
	CString m_strName;
	CString m_strType;
	CString m_strRemarks;
	//}}AFX_FIELD

	CString m_strQualifierParam;
	CString m_strOwnerParam;
	CString m_strNameParam;
	CString m_strTypeParam;

// Implementation
protected:
	virtual CString GetDefaultConnect();    			// default connection string
	virtual CString GetDefaultSQL();    				// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
};
