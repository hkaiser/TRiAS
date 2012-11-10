// KreisSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKreisSet DAO recordset

class CKreisSet : public CDaoRecordset
{
public:
	CKreisSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CKreisSet)

// Field/Param Data
	//{{AFX_FIELD(CKreisSet, CDaoRecordset)
	CString	m_Nummer;
	CString	m_Name;
	CString	m_Kuerzel;
	CString	m_AfI;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKreisSet)
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
