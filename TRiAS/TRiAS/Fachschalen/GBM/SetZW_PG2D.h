// SetZW_PG2D.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetZW_PG2D recordset

class CSetZW_PG2D : public CRecordset
{
public:
	CSetZW_PG2D(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetZW_PG2D)

// Field/Param Data
	//{{AFX_FIELD(CSetZW_PG2D, CRecordset)
	CString	m_NFP2_IDE;
	CString	m_NFP2_FLN;
	double	m_NFP2_FLG;
	double	m_NFP2_ABF;
	CString	m_NFP2_ANS;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetZW_PG2D)
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
