// SetSI.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetStrIndex recordset

class CSetStrIndex : public CRecordset
{
public:
	CSetStrIndex(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetStrIndex)

// Field/Param Data
	//{{AFX_FIELD(CSetStrIndex, CRecordset)
	CString	m_SCHL;
	CString	m_LISTE;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetStrIndex)
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
