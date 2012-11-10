// NF_PG1FL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG1FL recordset

class CSetNF_PG1FL : public CRecordset
{
public:
	void DeleteIDE( const char* );
	BOOL ModIDE( const char*, const char* );
	CSetNF_PG1FL(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetNF_PG1FL)

// Field/Param Data
	//{{AFX_FIELD(CSetNF_PG1FL, CRecordset)
	CString	m_NFP1_IDE;
	CString	m_NFP1_FST;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetNF_PG1FL)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
