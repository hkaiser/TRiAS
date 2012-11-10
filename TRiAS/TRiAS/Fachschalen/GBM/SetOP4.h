// SetOP4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetOP4 recordset

class CSetOP4 : public CRecordset
{
public:
	long m_lFLN;
	BOOL SelectONr( long );
	CSetOP4(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOP4)

// Field/Param Data
	//{{AFX_FIELD(CSetOP4, CRecordset)
	double	m_ABF;
	CString	m_ANS;
	double	m_FLG;
	CString	m_FLN;
	CString	m_IDE;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetOP4)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL
	virtual BOOL Update();

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
