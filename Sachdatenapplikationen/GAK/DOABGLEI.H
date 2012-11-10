// doabglei.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoAbgleich dialog
class CErzeugerSet;
class CAbfartSet;
class CAbfallSet;
class CBgsSet;
class CSelectSet;
class COutputSet;
class CErzListeSet;
class CAbfallMap;
class CAbfallArtenMap;
class CErzeugerListe;
class CAbgleichCntSet;
class CDoAbgleich : public CDialog
{
// Construction
public:
	CDoAbgleich(CWnd* pParent, UINT uiResID);
	~CDoAbgleich ();

// Dialog Data
	//{{AFX_DATA(CDoAbgleich)
	enum { IDD = IDD_DOABGLEICH };
	CStatic	m_ctrlBranchennummer;
	CStatic	m_ctrlAnfallstelle;
	CButton	m_btWeiter;
	CListCtrl	m_lbBgs;
	CListCtrl	m_lbAbfall;
	CListCtrl	m_lbAbfallVJ;
	CButton	m_btErzInfo;
	CButton	m_btHelp;
	CButton	m_btInListe;
	CProgressCtrl m_ctProgress;
	CStatic	m_stAction;
	CButton	m_btOk;
	CButton	m_btEscape;
	BOOL m_bOnlySonderAbfall;
	//}}AFX_DATA
	
	CDatabase *m_pFoxProDatabase;
	CDatabase *m_pMdbDatabase;
	CString m_strErzeugerTable;
	CString m_strAbfallTable;
	CString m_strAbfallTableVJ;
	CString m_strBgsTable;   
	CString m_strOutputTable;
	CString m_strErzListe;
	CString m_strLastErzeuger;
	CString m_strLastAsn;
	
	double m_dMinMenge, m_dMinMengeRec;
	long m_lMaxErzCnt, m_lOutputCnt, m_lEscCnt, m_lInListeCnt, m_lDirtyCnt;
	int m_iModus, m_iPrioritaet;
	BOOL m_bOnlyThisErzeuger, m_bAbfallAppend, m_bErzListeAppend;

	CErzListeSet *GetErzListeSet (void) { return NULL != m_pErzListeSet ? m_pErzListeSet : NULL; }
	
// Implementation
protected:             
	BOOL m_bNotInit, m_bUserBreak, m_bInAction, m_bInputFromListe, m_bMoveInit;
	long m_lActErzCnt;
	CAbgleichCntSet *m_pErzeugerSet;
	CErzeugerSet *m_pErzeugerInfoSet;
	CAbfartSet *m_pAbfArtenSet;
	CAbfallSet *m_pAbfallSet;
	CAbfallSet *m_pAbfallSetVJ;
	CBgsSet *m_pBgsSet;
	COutputSet *m_pOutputSet;   
	CErzListeSet *m_pErzListeSet;
	CAbfallMap *m_pAbfallMap;
	CAbfallMap *m_pAbfallMapVJ;
	CAbfallMap *m_pBgsMap;	
	CAbfallArtenMap *m_pAbfArtenMap;
	CSelectSet* m_pBranchenSet;
	
	BOOL InitSets ();
	void OutputUserInfo (UINT uiID);
	void SetSummenMenge();
	BOOL ReadNextErzeuger ();
	void ResetControlValues ();
	void SetBearbeitet ();			
	void SaveStatus ();
	void ShowSelection (CListCtrl *pList, CAbfallMap *pMap, BOOL bStoreChanges = TRUE);
	int SetSelection (CListCtrl *pList, BOOL bSelect = TRUE);
	void SetBearbeitet (CRecordset *pSet, const CString &strWhere);
	void ShowAktData();		// fill Ctrl's with UserInformations

//	Felder "Bearbeitet" und "Prioritaet" erzeugen
	void CreateFields (CDatabase *pDB, const CString& strTable);

//	Gesamtmenge in der Abfalltabelle ok ?
	BOOL GesAbfMengeOk ();

//	Gesamtmenge in der Referenztabelle ok ?
	BOOL GesBgsMengeOk ();

//	Priorität für den Fall 1 OK ?
	BOOL BgsPrioOk ();

//	temp. BGS-Tabelle erzeugen
	void CreateBgsErzAbfTable ();

//  Lazy Singleton
	CSelectSet* GetBranchenSet();

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDoAbgleich)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnEscape();
	afx_msg void OnDestroy();
	afx_msg void OnInListe();
	afx_msg void OnHelp();
	afx_msg void OnClose();
	afx_msg void OnErzInfo();
	afx_msg void OnClickAbfall(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickBgs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemAbfallVorjahr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemAbfall(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemBgs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickAbfallVorjahr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickAbfallVorjahr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickAbfall(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickBgs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnWeiter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//	Filter anhängen
	void AppendFilter (CString &strFilter, const CString& strExtension);
