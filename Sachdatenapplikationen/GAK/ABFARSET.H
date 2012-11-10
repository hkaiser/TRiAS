// AbfArStet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbfArtSet DAO recordset

class CAbfArtSet : public CSelectSet
{
public:
	CAbfArtSet(CDaoDatabase* pDatabase, const char *pTableName);
	DECLARE_DYNAMIC(CAbfArtSet)

// Field/Param Data
	//{{AFX_FIELD(CAbfArtSet, CDaoRecordset)
	BOOL	m_Sonderabfall;
	float	m_Dichte;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbfArtSet)
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
