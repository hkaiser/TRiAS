// filtrpge.hpp : header file
//

#ifndef _FILTER_PAGE_HPP
#define _FILTER_PAGE_HPP

/////////////////////////////////////////////////////////////////////////////
// CFilterPage dialog
class CHelpText;

class CFilterPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFilterPage)

// Construction
public:
	CFilterPage();
	~CFilterPage();

#ifdef WIN32
// Dialog Data
	//{{AFX_DATA(CFilterPage)
	enum { IDD = IDD_FILTER };
	CHelpText	m_Description;
	CButton	m_btFilterCheck;
	CListCtrl	m_lcFelder;
	CListBox	m_lbOperatoren;
	CListBox	m_lbFunktionen;
	CEdit		m_edKlausel;
	BOOL 		m_bIsChecked;
	short 		m_sNameSort;
	short 		m_sTypeSort;
	short 		m_sLenSort;
	//}}AFX_DATA
#else 
	enum { IDD = IDD_FILTER };
	CHelpText	m_Description;
	CButton		m_btFilterCheck;
	CListBox	m_lcFelder;
	CListBox	m_lbOperatoren;
	CListBox	m_lbFunktionen;
	CEdit		m_edKlausel;
	BOOL 		m_bIsChecked;	
	CString 	m_strLastInfo;
#endif		// WIN16            
            
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFilterPage)
	public:
	virtual void OnCancel();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:              
	CString m_strFilter;  
#ifdef WIN32
	CString m_strDataSource;
	CString m_strTableName;
	// Generated message map functions
	//{{AFX_MSG(CFilterPage)
	afx_msg void OnChangeFilterKlausel();
	afx_msg void OnSelchangeFilterFunkt();
	afx_msg void OnDblclkFilterFunkt();
	afx_msg void OnDblclkFilterOpera();
	afx_msg void OnSelchangeFilterOpera();
	afx_msg void OnDeleteitemFilterFeld(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickFilterFeld(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkFilterFeld(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnFilterCheck();
	afx_msg void OnSetfocusFilterFeld(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
#else 		// WIN16            
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnChangeFilterKlausel();
	afx_msg void OnSelchangeFilterFunkt();
	afx_msg void OnSelchangeFilterOpera();
	afx_msg void OnSelchangeFilterFeld();		
	afx_msg void OnDblclkFilterFunkt();
	afx_msg void OnDblclkFilterOpera();
	afx_msg void OnDblclkFilterFeld();
	afx_msg void OnFilterCheck();
	afx_msg LONG OnSetFocusToControl (UINT, LONG);
#endif		// WIN16
        void SetOkButton (void);        // Ok-Button aktivieren/deaktivieren
	BOOL ReadParams (void);		// akt. Parameter lesen
	CPropertySheet *GetParent (void) { return (CPropertySheet *) 
											   CWnd :: GetParent (); }
	//	prüfe und lese Beschreibungs-Info einer skalaren Funktion
	void GetScaleFunction (uint &uIndex, uint uResID,
						   UDWORD uwCheckFlag, UDWORD fFlag);

	BOOL GetUserEntries (BOOL bGet = TRUE);		// Nutzereingaben lesen
	//	prüfe und lese Beschreibungs-Info einer skalaren Funktion
        DECLARE_MESSAGE_MAP()
};

#endif 		// _FILTER_PAGE_HPP

