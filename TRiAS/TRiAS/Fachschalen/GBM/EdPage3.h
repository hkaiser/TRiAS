// EdPage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditPage3 dialog

#define MAX_ANZAHL_DT 20

class CEditPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CEditPage3)

// Construction
public:
	CString m_strIDE;
	CPG2DArray* m_parrPG2H;
	CEditPage3();
	~CEditPage3();

// Dialog Data
	//{{AFX_DATA(CEditPage3)
	enum { IDD = IDD_EDITPAGE3 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEditPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void HideControl( CDataExchange*, UINT );
	void SpecialDDX_Check( CDataExchange*, UINT, BOOL& );
	void SpecialDDX_Text( CDataExchange*, UINT, double& );
	void RestoreData();
	void InitData();
	void SetGeaendert( BOOL = TRUE );
	short m_iGebZahl;
	short m_iOffset;
	BOOL m_bA[MAX_ANZAHL_DT];
	double m_rAF[MAX_ANZAHL_DT];
	double m_rF[MAX_ANZAHL_DT];
	CString m_strD[MAX_ANZAHL_DT];
	// Generated message map functions
	//{{AFX_MSG(CEditPage3)
	virtual BOOL OnInitDialog();
	afx_msg void OnNeu();
	afx_msg void OnDelete();
	afx_msg void OnWeiter();
	afx_msg void OnZurueck();
	afx_msg void OnAnschl1();
	afx_msg void OnAnschl10();
	afx_msg void OnAnschl11();
	afx_msg void OnAnschl12();
	afx_msg void OnAnschl13();
	afx_msg void OnAnschl14();
	afx_msg void OnAnschl15();
	afx_msg void OnAnschl16();
	afx_msg void OnAnschl17();
	afx_msg void OnAnschl18();
	afx_msg void OnAnschl19();
	afx_msg void OnAnschl2();
	afx_msg void OnAnschl20();
	afx_msg void OnAnschl3();
	afx_msg void OnAnschl4();
	afx_msg void OnAnschl5();
	afx_msg void OnAnschl6();
	afx_msg void OnAnschl7();
	afx_msg void OnAnschl8();
	afx_msg void OnAnschl9();
	afx_msg void OnChangeEdit10();
	afx_msg void OnChangeEdit11();
	afx_msg void OnChangeEdit12();
	afx_msg void OnChangeEdit13();
	afx_msg void OnChangeEdit14();
	afx_msg void OnChangeEdit15();
	afx_msg void OnChangeEdit16();
	afx_msg void OnChangeEdit17();
	afx_msg void OnChangeEdit18();
	afx_msg void OnChangeEdit19();
	afx_msg void OnChangeEdit20();
	afx_msg void OnChangeEdit21();
	afx_msg void OnChangeEdit22();
	afx_msg void OnChangeEdit23();
	afx_msg void OnChangeEdit24();
	afx_msg void OnChangeEdit25();
	afx_msg void OnChangeEdit26();
	afx_msg void OnChangeEdit27();
	afx_msg void OnChangeEdit28();
	afx_msg void OnChangeEdit29();
	afx_msg void OnChangeEdit30();
	afx_msg void OnChangeEdit31();
	afx_msg void OnChangeEdit32();
	afx_msg void OnChangeEdit33();
	afx_msg void OnChangeEdit34();
	afx_msg void OnChangeEdit35();
	afx_msg void OnChangeEdit36();
	afx_msg void OnChangeEdit37();
	afx_msg void OnChangeEdit38();
	afx_msg void OnChangeEdit39();
	afx_msg void OnChangeEdit40();
	afx_msg void OnChangeEdit41();
	afx_msg void OnChangeEdit42();
	afx_msg void OnChangeEdit43();
	afx_msg void OnChangeEdit44();
	afx_msg void OnChangeEdit45();
	afx_msg void OnChangeEdit46();
	afx_msg void OnChangeEdit47();
	afx_msg void OnChangeEdit48();
	afx_msg void OnChangeEdit49();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
