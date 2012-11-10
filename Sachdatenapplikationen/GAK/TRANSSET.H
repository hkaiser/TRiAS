// TransSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTranspSet DAO recordset
class CTranspSet : public CSelectSet
{
public:
	CTranspSet(CDaoDatabase* pDatabase, const char *pTableName);
	DECLARE_DYNAMIC(CTranspSet)

// Field/Param Data
	//{{AFX_FIELD(CTranspSet, CDaoRecordset)
	CString	m_Strasse;
	CString	m_Ortsname;
	CString	m_Postleitzahl;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTranspSet)
	public:
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	virtual CString GetDefaultSQL();
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
