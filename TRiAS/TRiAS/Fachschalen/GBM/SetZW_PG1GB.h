// SetZW_PG1GB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetZW_PG1GB recordset

class CSetZW_PG1GB : public CRecordset
{
public:
	CSetZW_PG1GB(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetZW_PG1GB)

// Field/Param Data
	//{{AFX_FIELD(CSetZW_PG1GB, CRecordset)
	CString	m_NFP1_IDE;
	double	m_NFP1_GNR;
	double	m_NFP1_GFL;
	double	m_NFP1_VOL;
	double	m_NFP1_HOH;
	CString	m_NFP1_ANL;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetZW_PG1GB)
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
