// SelSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectSet DAO recordset

class CSelectSet : public CDaoRecordset
{
public:
	virtual ~CSelectSet (void);
	CSelectSet(CDaoDatabase* pDatabase, const char *pTableName);
	DECLARE_DYNAMIC(CSelectSet)

// Field/Param Data
	//{{AFX_FIELD(CSelectSet, CDaoRecordset)
	CString	m_Nummer;
	CString	m_Name;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	virtual void Close();
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_strTableName;
};
