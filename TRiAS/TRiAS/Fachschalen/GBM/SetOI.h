// SetOI.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetOrtIndex recordset

class CSetOrtIndex : public CRecordset
{
public:
	CSetOrtIndex(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOrtIndex)

// Field/Param Data
	//{{AFX_FIELD(CSetOrtIndex, CRecordset)
	CString	m_SCHL;
	CString	m_LISTE;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetOrtIndex)
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
