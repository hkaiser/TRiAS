// WhereSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWhereSet recordset

class CWhereSet : public CRecordset
{
public:
	CWhereSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CWhereSet)

// Field/Param Data
	//{{AFX_FIELD(CWhereSet, CRecordset)
	CString	m_Ident;
	CString	m_Ident2;
	//}}AFX_FIELD

	CString m_strField1,
			m_strField2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhereSet)
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
