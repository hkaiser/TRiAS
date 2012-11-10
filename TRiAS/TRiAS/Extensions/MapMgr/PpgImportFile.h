#if !defined(AFX_PPGIMPORTFILE_H__A6EEA9A5_FE40_11D1_8F55_0060085FC1CE__INCLUDED_)
#define AFX_PPGIMPORTFILE_H__A6EEA9A5_FE40_11D1_8F55_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPpgImportFile dialog

class CPpgImportFile : public CPropertyPage {
	BOOL	m_bProcessed;
	DECLARE_DYNCREATE(CPpgImportFile)
	virtual void UpdateControls();
	class P : public CFilterProgress {
		CProgressCtrl&	m_ctl;
		CWnd			*m_pTextWnd;
	public:
		P( CProgressCtrl& rCtl, CWnd* pWnd = NULL ) : m_ctl( rCtl ), m_pTextWnd( pWnd ) {}
		virtual	void StartingFilter( );
		virtual void ReportingStatus( double havePercent, LPCTSTR lpszMsg = NULL );
		virtual void EndingFilter();
	};
// Construction
public:
	CPpgImportFile();
	~CPpgImportFile();

// Dialog Data
	//{{AFX_DATA(CPpgImportFile)
	enum { IDD = IDD_PPGIMPORTFILE };
	CButton	m_btnStart;
	CProgressCtrl	m_progressChunk;
	CStatic	m_textProgressMessage;
	CProgressCtrl	m_progressItem;
	CString	m_strDstDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgImportFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgImportFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonstart();
	afx_msg void OnButtonseldir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	P	m_stsItem;
	P	m_stsChunk;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGIMPORTFILE_H__A6EEA9A5_FE40_11D1_8F55_0060085FC1CE__INCLUDED_)
