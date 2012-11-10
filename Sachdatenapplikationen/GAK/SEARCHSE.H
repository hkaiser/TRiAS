// SearchSe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchSet DAO recordset
class CDaoTableDef;
class CDaoDatabase;

class CSearchSet : public CDaoRecordset
{
public:
	CSearchSet(CDaoDatabase* pDatabase = NULL);
	CSearchSet(const char *pSearch, CDaoDatabase* pDatabase = NULL);
	~CSearchSet (void);
	DECLARE_DYNAMIC(CSearchSet)

// Field/Param Data
	//{{AFX_FIELD(CSearchSet, CDaoRecordset)
	CString	m_strNummer;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	//	überlagere Open-Funktion
	// virtual void Open(int nOpenType = AFX_DAO_USE_DEFAULT_TYPE, LPCTSTR lpszSQL = NULL, int nOptions = 0);
	virtual void Close ();

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	CString m_strSearch;
	// CDaoTableDef *m_pTableDef;
};
