// trs16pge.hpp : header file
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
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTriasPage)
	public:
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTriasPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeObjektMerkmale (void);
	afx_msg void OnSelChangeObjektKlassen(void);
	afx_msg void OnDestroy();
	afx_msg LONG OnSetFocusToControl (UINT, LONG);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL SelectItem (CListBox &list, ulong ulKode, short sType); // sel. Item
	BOOL ReadParams (void);			// akt. Parameter lesen
	void SetOkButton (void);		//	Ok-Button aktivieren/deaktivieren
	CPropertySheet *GetParent (void) { return (CPropertySheet *) CWnd :: GetParent (); }
	
	CListBox m_lvObjektKlassen;
	CListBox m_lvObjektMerkmale;

public:
	BOOL GetUserEntries (BOOL bGet = TRUE);		// Nutzereingaben lesen
};

#endif          //_TRIAS_PAGE

