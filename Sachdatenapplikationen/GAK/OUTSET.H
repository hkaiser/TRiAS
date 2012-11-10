// abfalset.h : interface of the COutputSet class
//
/////////////////////////////////////////////////////////////////////////////

class COutputSet : public CRecordset
{
DECLARE_DYNAMIC(COutputSet)

public:
	COutputSet(CDatabase* pDatabase);
	~COutputSet (void);

// Field/Param Data
	//{{AFX_FIELD(COutputSet, CRecordset)
	CString	m_strNummer;
	CString	m_strAbfallnummer;
	CString	m_strTransporteurnummer;
	CString	m_strEntsorgernummer;
	double	m_dMenge_t;
	CString	m_strEntsorgungsverfahren;
	CString	m_strNachweisnummer;
	CString	m_strPrioritaet;
	BOOL	m_bBearbeitet;
	CTime	m_tErfassungsdatum;
	//}}AFX_FIELD
	
	CString m_strTableName;
	
// Implementation
protected:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
};
