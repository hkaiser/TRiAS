// EditPage7.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditPage7 dialog

class CEigentuemerArray;

class CEditPage7 : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditPage7)

// Construction
public:
	BOOL m_bSummError;
	BOOL m_bDivError;
	BOOL m_bMiteigentum;
	CEigentuemerArray* m_parrEigent;
	void RestoreData();
	short m_iEigZahl;
	CEditPage7();
	~CEditPage7();

// Dialog Data
	//{{AFX_DATA(CEditPage7)
	enum { IDD = IDD_EDITPAGE7 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditPage7)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetGeaendert( BOOL f = TRUE );
	void InitData();
	short m_iOffset;
	void ShowControl( CDataExchange *pDX, UINT id, BOOL f = TRUE );
	void SpecialDDX_Check( CDataExchange *pDX, UINT id, BOOL &r );
	void SpecialDDX_Text( CDataExchange *pDX, UINT id, CString &txt );
	void SpecialDDX_Text( CDataExchange *pDX, UINT id, long &d );
	long	m_lNenn[4];
	long	m_lZaehl[4];
	BOOL	m_bHer[4];
	CString m_strTeil[4];
	CString m_strOrt[4];
	CString m_strPLZ[4];
	CString m_strStr[4];
	CString m_strName[4];
	CString m_strEig[4];
	// Generated message map functions
	//{{AFX_MSG(CEditPage7)
	afx_msg void OnNeu();
	afx_msg void OnDelete();
	afx_msg void OnWeiter();
	afx_msg void OnZurueck();
	virtual BOOL OnInitDialog();
	afx_msg void OnModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
