// SetParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetParam recordset

class CSetParam : public CRecordset
{
public:
	CSetParam(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetParam)

// Field/Param Data
	//{{AFX_FIELD(CSetParam, CRecordset)
	BOOL	m_Global;
	double	m_Tiefe;
	BOOL	m_AnrFl_speichern;
	BOOL	m_GesFl_berechnen;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetParam)
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
