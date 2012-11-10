// rsltpge.hpp : header file
//

#ifndef _RESULT_PAGE_
#define _RESULT_PAGE_

/////////////////////////////////////////////////////////////////////////////
// CResultPage dialog

class CResultPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CResultPage)

// Construction
public:
	CResultPage();
	~CResultPage();

// Dialog Data
	//{{AFX_DATA(CResultPage)
	enum { IDD = IDD_ABGL_RESULT };
	CStatic	m_stAktion;
	CStatic	m_stDef;
	CEdit	m_edObjektKlassen;
	CStatic	m_stTable;
	CStatic	m_stRechtsWert;
	CStatic	m_stObjektMerkmal;
	CStatic	m_stNotExists;
	CStatic	m_stKoppelFeld;
	CStatic	m_stHochWert;
	CStatic	m_stFilter;
	CStatic	m_stDsn;
	CStatic	m_stAdd;
	//}}AFX_DATA
	
protected:
	CPropertySheet *GetParent (void) { return (CPropertySheet *) 
											   CWnd :: GetParent (); }
											   
	void StoreUserEntries (void);  	// akt. Eingaben speichern											   
	void GetUserEntries (void);		// Nutzereingaben in Dialog
           
// Overrides    
#ifdef WIN32	
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CResultPage)
	public:
	virtual BOOL OnSetActive();    
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
#else	// WIN16
	public:
	virtual BOOL OnSetActive();    
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
	protected:
	// Generated message map functions
	//{{AFX_MSG(CResultPage)
	afx_msg void OnDestroy();
	afx_msg LONG OnSetFocusToControl (UINT, LONG);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
#endif	// WIN16
};

#endif		// _RESULT_PAGE_



