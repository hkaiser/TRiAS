// EntsSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntsorgerSet DAO recordset
class CEntsorgerSet : public CSelectSet
{
public:
	CEntsorgerSet(CDaoDatabase* pdb, const char *pTableName);
	DECLARE_DYNAMIC(CEntsorgerSet)

// Field/Param Data
	//{{AFX_FIELD(CEntsorgerSet, CDaoRecordset)
	CString	m_Anlage;
	CString	m_Strasse;
	CString	m_Ortsname;
	CString	m_Postleitzahl;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntsorgerSet)
	public:
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
