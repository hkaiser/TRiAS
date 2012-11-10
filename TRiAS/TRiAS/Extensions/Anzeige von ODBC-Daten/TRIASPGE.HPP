// triaspge.hpp : header file
//

#ifndef _TRIAS_PAGE
#define _TRIAS_PAGE

/////////////////////////////////////////////////////////////////////////////
// CTriasPage

class CTriasPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTriasPage)

// Construction
public:
   CTriasPage();
   ~CTriasPage();

// Dialog Data
        //{{AFX_DATA(CTriasPage)
	enum { IDD = IDD_TRIAS };
	CListCtrl	m_lvObjektMerkmale;
	CListCtrl	m_lvObjektKlassen;
	short 		m_sSortIdKode;
	short 		m_sSortIdDescr;
	short  		m_sSortMerkmKode;
	short 		m_sSortMerkmDescr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTriasPage)
	public:
	virtual void OnCancel();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTriasPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnColumnclickObjKlList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickObjMerkmList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteItemObjektKlassen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteItemObjektMerkmal(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickObjektMerkmale(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickObjektKlassen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL SelectItem (CListCtrl &list, ulong ulKode, short sType); // sel. Item
	BOOL ReadParams (void);			// akt. Parameter lesen
	void SetOkButton (void);		//	Ok-Button aktivieren/deaktivieren
	CPropertySheet *GetParent (void) { return (CPropertySheet *) CWnd :: GetParent (); }

public:
	BOOL GetUserEntries (BOOL bGet = TRUE);		// Nutzereingaben lesen
};

#endif          //_TRIAS_PAGE

