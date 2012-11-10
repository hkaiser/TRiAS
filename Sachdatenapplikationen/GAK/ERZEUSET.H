// erzeuset.h : interface of the CErzeugerSet class
//
/////////////////////////////////////////////////////////////////////////////

class CErzeugerSet : public CRecordsetExt
{
DECLARE_DYNAMIC(CErzeugerSet)

public:
	CErzeugerSet(CDatabase* pDatabase);
	
// Field/Param Data
	//{{AFX_FIELD(CErzeugerSet, CRecordset)
	CString	m_strErzNr; 
	CString	m_strErzNrParam; 	
	CString m_strAsnParam;
	CString m_strBezAnfall;
	CString m_strOrtAnfall;
	CString m_strAnspr;
	CString m_strTelAnspr;
	CString m_strFaxAnspr;
	CString m_strBranche;
	BOOL m_bBearbeitet;
	//}}AFX_FIELD
	
	virtual void SetFieldCnt (BOOL bSet) {}
	
// Implementation
protected:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
};

//	"leichte" Variationen des Erzeugersets
class CErzeugerSetErzeugerListe : public CErzeugerSet
{
public:
//	Konstruktor/Destruktor
	CErzeugerSetErzeugerListe (CDatabase* pDatabase);
	
//	überlagerte virtuelle Funktionen    
	virtual void SetFieldCnt (BOOL bSet) {}
	
protected:
	virtual CString GetDefaultSQL(); 
	virtual void DoFieldExchange(CFieldExchange* pFX);	
};                                   

/*
class CErzeugerSetListeOhne : public CErzeugerSet
{
public:
//	Konstruktor/Destruktor
	CErzeugerSetListeOhne (CDatabase* pDatabase);
	
//	überlagerte virtuelle Funktionen    
	virtual void SetFieldCnt (BOOL bSet) {}
	
protected:
	virtual CString GetDefaultSQL(); 
	virtual void DoFieldExchange(CFieldExchange* pFX);	
};
*/                                   

class CErzeugerSetListeListe : public CErzeugerSet
{
public:
//	Konstruktor/Destruktor
	CErzeugerSetListeListe (CDatabase* pDatabase);
	
//	überlagerte virtuelle Funktionen    
	virtual void SetFieldCnt (BOOL bSet) {}
	
protected:
	virtual CString GetDefaultSQL(); 
	virtual void DoFieldExchange(CFieldExchange* pFX);	
};                                   


// CAbgleichCntSetFilter
class CAbgleichCntSetFilter
{
protected:
	BOOL	m_bOnlySonderAbfall;
	BOOL	m_bOnlyThisErzeuger;
	CString m_strLastErzeuger;
	CString m_strLastAsn;
	int		m_iModus;

public:
	// Anlegen des parametrisierten	Filters
	CAbgleichCntSetFilter(	const BOOL bOnlyThisErzeuger,
							const CString& strLastErzeuger,
							const CString& strLastAsn,
							const BOOL bOnlySonderAbfall,
							const int iModus)
	{
		m_bOnlySonderAbfall = bOnlySonderAbfall;
		m_bOnlyThisErzeuger = bOnlyThisErzeuger;
		m_strLastErzeuger= strLastErzeuger;
		m_strLastAsn= strLastAsn;
		m_iModus= iModus;
	}

	// Abfragen des an die Tabellen angepaßten Filters
	CString GetFilter(const CString& strBilanztable, const CString& strErzeugerTable);
};

//	CAbgleichCntSet ---------------------------------------------
class CAbgleichCntSet : public CRecordsetExt
{
DECLARE_DYNAMIC(CAbgleichCntSet)

public:
	CAbgleichCntSet(CDatabase* pDatabase,
					const CString& strErzeugerTable,
					const CString& strBilanztable,
					const CString &strBgsTable,
					CAbgleichCntSetFilter &filter);
	
// Field/Param Data
	//{{AFX_FIELD(CAbgleichCntSet, CRecordset)
	CString m_strErzNr;
	CString m_strAsn;
	CString	m_strErzNrParam; 	
	CString m_strAsnParam;
	//}}AFX_FIELD
	
	virtual void SetFieldCnt (BOOL bSet) {}
	
// Implementation
protected:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

	CString m_strSelect;
};
