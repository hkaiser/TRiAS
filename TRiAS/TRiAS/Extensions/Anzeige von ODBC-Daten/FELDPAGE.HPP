// feldpage.hpp : header file
//

#ifndef _FELD_PAGE_HPP
#define _FELD_PAGE_HPP

class CFeldInform
{
public:
	CString m_strName, m_strType;
	long m_lLen, m_lId;

	CFeldInform (long lId, long lLen, const char *pName, const char *pType);
	~CFeldInform (void) {}

	const char* Name (void) { return m_strName; }
	const char* Type (void) { return m_strType; }

	friend void* GetFeldInform (void *Obj);
	friend int CompareFeldInform (void *pObj1, void *pObj2);	 
};

//	Dieser Baum speichert die Feldinformationen für alle 3 CListCtrls !
class CFeldInformTree : public CTree
{
protected:
	void UserDelete (void *);
	
public:
	CFeldInformTree (void);
	~ CFeldInformTree (void);		

//	Schreibfunktion(en)
	BOOL AddFeldInform (long lId, long lLen, const char *pName, const char *pType);

//	Lese-Funktionen
	const char *GetFeldName	(long lId);
	const char *GetFeldType (long lId);
	long GetFeldLen (long lId);		
};
DeclareLock (CFeldInformTree, CFeldInform);

/////////////////////////////////////////////////////////////////////////////
// CFeldPage dialog

class CFeldPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFeldPage)

// Construction
public:
	CFeldPage();
	~CFeldPage();

// Dialog Data
	//{{AFX_DATA(CFeldPage)
	enum { IDD = IDD_FELDER };
	CListCtrl	m_lcRechtsWert;
	CListCtrl	m_lcKoppelFeld;
	CListCtrl	m_lcHochWert;
	short 		m_sKoppNameSort;
	short 		m_sKoppTypeSort;
	short 		m_sKoppLenSort;
	short 		m_sHochNameSort;
	short 		m_sHochTypeSort;
	short 		m_sHochLenSort;
	short 		m_sRechtsNameSort;
	short 		m_sRechtsTypeSort;
	short 		m_sRechtsLenSort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFeldPage)
	public:
	virtual BOOL OnSetActive();
	virtual void OnCancel();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strDataSource;
	CString m_strTableName;
	// Generated message map functions
	//{{AFX_MSG(CFeldPage)
	afx_msg void OnColumnclickFeldRechtsw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickFeldKoppel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickFeldHochw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickFeldRechtsw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickFeldKoppel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickFeldHochw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CFeldInformTree m_FeldTree;	// Baum speichert Feldinfos
	void SetOkButton (void); 	// Ok-Button aktivieren/deaktivieren

	BOOL ReadParams (void);				// akt. Parameter lesen
	CPropertySheet *GetParent (void) { return (CPropertySheet *) 
											   CWnd :: GetParent (); }

public:
	BOOL GetUserEntries (BOOL bGet = TRUE);		// Nutzereingaben lesen
};

#endif 		// _FELD_PAGE_HPP
