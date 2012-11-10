// fld16pge.hpp : header file
//

#ifndef _FELD_PAGE_HPP
#define _FELD_PAGE_HPP

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
	CListBox	m_lcRechtsWert;
	CListBox	m_lcKoppelFeld;
	CListBox	m_lcHochWert;
	//}}AFX_DATA
	
	CHelpText m_stDescription;
	CString m_strLastInfo;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFeldPage)
	public:
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetOkButton (void); 					// Ok-Button aktivieren/deaktivieren

	BOOL ReadParams (void);						// akt. Parameter lesen
	BOOL GetUserEntries (BOOL bGet = TRUE);		// Nutzereingaben lesen

	// Generated message map functions
	//{{AFX_MSG(CFeldPage)      
	afx_msg void OnSelChangeRechtsWert ();
	afx_msg void OnSelChangeHochWert ();
	afx_msg void OnSelChangeKoppelFeld ();	
	afx_msg void OnDestroy();
	afx_msg LONG OnSetFocusToControl (UINT, LONG);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 		// _FELD_PAGE_HPP
