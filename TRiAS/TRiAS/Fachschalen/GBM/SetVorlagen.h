// SetVorlagen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetVorlagen recordset

class CSetVorlagen : public CRecordset
{
public:
	CMapStringToString m_mapType;
	BOOL UpdateVorlage();
	BOOL SelectVorlage( const char );
	CSetVorlagen(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetVorlagen)

// Field/Param Data
	//{{AFX_FIELD(CSetVorlagen, CRecordset)
	long	m_ID;
	CString	m_Kode;
	CString	m_Name;
	CString	m_Pfad;
	int		m_Typ;
	BOOL	m_NurLesen;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetVorlagen)
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
protected:
	CMapStringToString m_mapPfade;
	CMapStringToString m_mapNamen;
	void InitListen();
};
