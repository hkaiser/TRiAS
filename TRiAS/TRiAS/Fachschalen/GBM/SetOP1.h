// SetOP1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetOP1 recordset

class CSetOP1 : public CRecordset
{
public:
	BOOL SelectONr( long );
	CSetOP1(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOP1)

// Field/Param Data
	//{{AFX_FIELD(CSetOP1, CRecordset)
	CString	m_IDE;
	double	m_AGGS;
	double	m_GEFS;
	double	m_KAT;
	double	m_TIEB;
	CString	m_TIEF;
	CString	m_B_GEDR;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetOP1)
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
