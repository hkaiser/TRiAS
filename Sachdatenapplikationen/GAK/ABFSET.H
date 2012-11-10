// AbfSet.h : header file
//

//	SatzInfo speichern
class CRecordInfo
{
public:
//	Attribute
	COleVariant m_varBookMark;	// Buchmarke
	CString m_strAbfArt;		// Abfallart
	BOOL m_bFirst;				// 1. Satz im set

//	Konstruktur/Destruktor
	CRecordInfo (CString &strArt, /*CString& strEnts, */COleVariant varBookmark, BOOL bFirst = FALSE);
	~CRecordInfo (void) {}
};

//	Verwaltet SatzInfo-Einträge 
class CPtrListExt : public CPtrList
{
public:
//	Konstruktor/Destruktor
	CPtrListExt (int nBlockSize = 10) :
				 CPtrList (nBlockSize) {}
	~CPtrListExt (void);

//	einzelnen Eintrag über seine Bauchmarke löschen
	BOOL DeleteRecord (COleVariant &varBookmark);
	BOOL SetFirstRecord (COleVariant varBookmark, const char *pAbfallArt = NULL);
	BOOL AddRecord (COleVariant varBookmark, const char *pAbfallArt, BOOL bFirst = TRUE);

//	alle Einträge löschen
	void RemoveAll ();				// alle Einträge entfernen
};
typedef CTypedPtrList<CPtrListExt, CRecordInfo*> CRecordInfoList;

/////////////////////////////////////////////////////////////////////////////
// CAbfSet DAO recordset

class CAbfSet : public CDaoRecordsetExt
{
public:
	bool IsValid();
	virtual BOOL PrepareAddNew (const char *pNummer, PFPREPARE = NULL, LPARAM = 0);
	virtual BOOL SearchNummer (const char *pNummer = NULL , BOOL bOutErrMsg =TRUE);
	virtual BOOL CanUpdate(void);
	virtual void OutputLockErrorMessage (void) {};	// keine Message (das amcht doch schon der Erzeuger)

	virtual void Delete();
	BOOL m_bDeleteAll;
	virtual int LockReckord (BOOL bLock = TRUE, CWnd *pWnd = NULL, const char *pNummer = NULL);
	// BOOL Seek( LPCTSTR lpszComparison, COleVariant* pKey1, COleVariant* pKey2 = NULL, COleVariant* pKey3 = NULL );
	BOOL MoveExt (const char *pSearch, int iDirect, const char *pErzNummer = NULL);
	CAbfSet(CDaoDatabase* pDatabase = NULL);
	~CAbfSet ();
	DECLARE_DYNAMIC(CAbfSet)
	CRecordInfoList m_RecordInfoList;			//	Liste mit zugeh. Infos

// Field/Param Data
	//{{AFX_FIELD(CAbfSet, CDaoRecordset)
	CString	m_Abfallbezeichnung;
	CString	m_Abfallnummer;
	CString	m_Bemerkungen;
	CString	m_Betreiberbemerkungen;
	CString	m_Betreibernummer;
	BOOL	m_Eigenentsorgung;
	BOOL	m_Eigentransport;
	CString	m_Entsorgerbemerkungen;
	CString	m_Entsorgernummer;
	BOOL	m_Entsorgungsfreistellung;
	CString	m_Entsorgungspartner;
	CString	m_Entsorgungstelefax;
	CString	m_Entsorgungstelefon;
	CString	m_Entsorgungsverfahren;
	CString	m_Freistellungsnummer;
	double	m_Menge_t;
	CString	m_Transporteurbemerkungen;
	CString	m_Transporteurnummer;
	CString	m_Verbringungscode;
	CString	m_Vorbehandlung;
	CString m_EAKNummer;
	CString m_Nachweisnummer;
	CString	m_Exportiert;
//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbfSet)
	public:
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	virtual void Move(long lRows);
	//}}AFX_VIRTUAL

	// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
