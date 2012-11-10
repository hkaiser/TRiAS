// SetOP2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetOP2 recordset

class CSetOP2 : public CRecordset
{
public:
	long m_lFLN;
	BOOL SelectONr( long );
	CSetOP2(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetOP2)

// Field/Param Data
	//{{AFX_FIELD(CSetOP2, CRecordset)
	CString	m_IDE;
	double	m_GFL;
	double	m_GNR;
	CString	m_ANL;
	double	m_HOH;
	double	m_VOL;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetOP2)
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
