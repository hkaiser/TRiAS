// abfalset.h : interface of the CAbfallSet class
//
/////////////////////////////////////////////////////////////////////////////

class CAbfallSet : public CRecordsetExt
{
DECLARE_DYNAMIC(CAbfallSet)

public:
	CAbfallSet(CDatabase* pDatabase);

// Field/Param Data
	//{{AFX_FIELD(CAbfallSet, CRecordset)
	CString	m_strNummer;
	CString	m_strAbfallnummer;
	CString	m_strTransporteurnummer;
	CString	m_strEntsorgernummer;
	double	m_dMenge_t;
	CString	m_strEntsorgungsverfahren;
	CString	m_strNachweisnummer;
	CString	m_strPrioritaet;
	CString m_strEntsorgerBemerkung;
	CString m_strTransportBemerkung;
	BOOL	m_bBearbeitet;	
	//}}AFX_FIELD  
	
	CString m_strErzNrParam, m_strAsnParam;
	
	virtual void SetFieldCnt (BOOL bSet) {}

// Implementation
protected:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
};
