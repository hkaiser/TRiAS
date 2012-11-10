// FirmaSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFirmaSet DAO recordset

class CFirmaSet : public CDaoRecordset
{
public:
	CFirmaSet(CDaoDatabase* pDatabase);
	~CFirmaSet ();
	DECLARE_DYNAMIC(CFirmaSet)

// Field/Param Data
	//{{AFX_FIELD(CFirmaSet, CDaoRecordset)
	CString	m_Nummer;
	CString	m_Firmenname;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFirmaSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
