// erzliste.h : interface of the CErzListeSet class
//
/////////////////////////////////////////////////////////////////////////////
class CErzeugerSet;        
class CAbfallMap;
class CErzListeSet : public CRecordsetExt
{
DECLARE_DYNAMIC(CErzListeSet)

public:
	CErzListeSet(CDatabase* pDatabase);

// Field/Param Data
	//{{AFX_FIELD(CErzListeSet, CRecordset)
	CString	m_strNummer;
	CString	m_strAnfallstelle;
	CString	m_strOrtsname;
	CString	m_strAnsprechpartner;
	CString	m_strPartnertelefon;
	CString	m_strPartnertelefax;
	CString	m_strAbfallnummer;
	CString	m_strTransporteurnummer;
	CString	m_strEntsorgernummer;
	double	m_dMenge;
	BOOL	m_bSonderabfall;
	BOOL	m_bBilanzdaten;
	BOOL	m_bBearbeitet;
	CString	m_strBranchennummer;
	CString	m_strVerfahren;
	CString	m_strPrioritaet;
	CString	m_strNachweisnummer;
	//}}AFX_FIELD
	
	virtual void SetFieldCnt (BOOL bSet) {}

//	Ausgabe der selektierten Sätze beider Maps	
	BOOL Output (const CString &strErzNr, const CString& strAsn, CErzeugerSet *pInfoSet, CAbfallMap *pMap1, 
				 CAbfallMap *pMap2, CStatic &stUserInfo, long &lCnt);

// Implementation
protected:
//	Ausgabe der selektierten Sätze einer Map, oder auch aller (wenn bOnlySelected FALSE ist)
	BOOL OutputMap (const CString &strErzNr, CErzeugerSet *pInfoSet, CAbfallMap *pMap, BOOL bBilanz,
					long &lCnt, bool bOnlySelected = TRUE); 

	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
};
