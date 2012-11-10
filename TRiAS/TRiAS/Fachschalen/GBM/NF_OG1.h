// NF_OG1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetNF_OG1 recordset

class CSetNF_OG1 : public CRecordset
{
public:
	BOOL FindIDE( const char* );
	CSetNF_OG1(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetNF_OG1)

// Field/Param Data
	//{{AFX_FIELD(CSetNF_OG1, CRecordset)
	CString	m_NFO1_PRO;
	CString	m_NFO1_IDE;
	CString	m_NFO1_ORT;
	CString	m_NFO1_STR;
	CString	m_NFO1_FLU;
	CString	m_NFO1_FST;
	double	m_NFO1_BLT;
	double	m_NFO1_FLG;
	double	m_NFO1_PFA;
	double	m_NFO1_PFU;
	double	m_NFO1_PGR;
	CString	m_NFO1_AFA;
	CString	m_NFO1_AFU;
	double	m_NFO1_ART;
	double	m_NFO1_VFL;
	CString	m_NFO1_BEM;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetNF_OG1)
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
