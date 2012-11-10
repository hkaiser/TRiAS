// bgsset.h : interface of the CBgsSet class
//
/////////////////////////////////////////////////////////////////////////////

class CBgsSet : public CRecordsetExt
{
DECLARE_DYNAMIC(CBgsSet)

public:
	CBgsSet(CDatabase* pDatabase);

// Field/Param Data
	//{{AFX_FIELD(CBgsSet, CRecordset)
	CString	m_strAbfallschluesselnummer;
	BOOL	m_bBearbeitet;
	CString	m_strBefoerderernummer;
	CString	m_strEntsorgernummer;
	CString	m_strEntsorgungsverfahren;
	CString	m_strErzeugernummer;
	double	m_dMenge;
	double	m_dMenge_en;
	CString	m_strNachweisnummer;
	CString	m_strPrioritaet;
	//}}AFX_FIELD
	
	CString m_strErzNrParam, m_strAsnParam;
	virtual void SetFieldCnt (BOOL bSet) {}

// Implementation
protected:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
};
/////////////////////////////////////////////////////////////////////////////
// CBgsSetRed recordset

class CBgsSetRed : public CRecordset
{
public:
	CBgsSetRed(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBgsSetRed)

// Field/Param Data
	//{{AFX_FIELD(CBgsSetRed, CRecordset)
	BOOL	m_Bearbeitet;
	CString	m_Nachweisnummer;
	CString	m_Erzeugernummer;
	CString	m_Abfallschluesselnummer;
	CString	m_Befoerderernummer;
	CString	m_Entsorgernummer;
	double	m_Menge;
	double	m_Menge_en;
	CString	m_Entsorgungsverfahren;
	CString	m_Prioritaet;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBgsSetRed)
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
