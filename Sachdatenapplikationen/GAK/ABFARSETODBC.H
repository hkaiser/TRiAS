// abfarset.h : interface of the CAbfartSet class
//
/////////////////////////////////////////////////////////////////////////////

class CAbfartSet : public CRecordset
{
DECLARE_DYNAMIC(CAbfartSet)

public:
	CAbfartSet(CDatabase* pDatabase);
	~CAbfartSet ();

// Field/Param Data
	//{{AFX_FIELD(CAbfartSet, CRecordset)
	BOOL m_bSonderAbfall;
	double m_dDichte;
	CString m_strAbfallArt;
	//}}AFX_FIELD        
	// CString m_strAbfArtParam;
	/*
	CString	m_NRABFART;
	BOOL	m_UEABFBESTV;
	BOOL	m_LABFGMASS;
	CString	m_ABFALL_ART;
	CString	m_HERKUNFT;
	CString	m_CPB;
	CString	m_HMV;
	CString	m_SAV;
	CString	m_HMD;
	CString	m_SAD;
	CString	m_UTD;
	CString	m_SONSTIGES;
	double	m_DICHTE;
	*/
// Implementation
protected:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
};
                     
                     