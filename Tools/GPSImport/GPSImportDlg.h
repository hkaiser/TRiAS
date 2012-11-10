// GPSIMPORTDlg.h : header file
//

#if !defined(AFX_GPSIMPORTDLG_H__1149A4E2_7503_4670_9AF7_A307F4F20D0D__INCLUDED_)
#define AFX_GPSIMPORTDLG_H__1149A4E2_7503_4670_9AF7_A307F4F20D0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DDXGetFolder.h"
#include "DDXGetFile.h"


struct CCopyData
{
	CString m_strSourcePath;
	CString m_strDestPath;
};



class CGPSImportDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CGPSImportDlg dialog

class CGPSImportDlg : public CDialog
{
	DECLARE_DYNAMIC(CGPSImportDlg);
	friend class CGPSImportDlgAutoProxy;

// Construction
public:

	static enum {CMD_NONE					= 0,
				 CMD_TIMEOUT_ELAPSED		= 1,
				 CMD_INITIALIZE				= 2,
				 CMD_RUN					= 3,
				 CMD_PAUSE					= 4,
				 CMD_CONTINUE				= 5,
				 CMD_RESET					= 6,
				 CMD_STOP					= 7,
				 CMD_USER_COMMAND			= 8,
				 BASE_DELAY_INTERVAL		= 100};



	CGPSImportDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CGPSImportDlg();

// Dialog Data
	//{{AFX_DATA(CGPSIMPORTDlg)
	enum { IDD = IDD_COPYDLKW_DIALOG };
	CProgressCtrl	m_Status;
	CButton	m_pbClose;
	CButton	m_pbAction;
	CString	m_strDestPath;
	CString	m_strSourcePath;
	CString	m_strPrompt;
	//}}AFX_DATA

//	CGetFolderControl	m_sleSourcePath;
	CGetFolderControl	m_sleDestPath;
	CGetFilenameControl	m_sleSourcePath;
//	CGetFilenameControl	m_sleDestPath;


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPSIMPORTDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGPSImportDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CGPSIMPORTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnStop();
	afx_msg void OnChangeDestinationdir();
	afx_msg void OnChangeSourcedir();
	afx_msg void OnCloseApp();
	afx_msg LRESULT OnThreadCallback(WPARAM, LPARAM);
	afx_msg LRESULT OnGPSImportStatus(WPARAM, LPARAM);
	afx_msg LRESULT OnCopyError(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void AdjustOK();

private:
	int m_iMinRange;
	int m_iMaxRange;

	CCopyData m_CopyData;

	set<string> m_vecFiles;
	BOOL m_fMustStop;
	BOOL m_fMustStart;


	OFSTRUCT		m_ofs;
	int m_iType;
	CString m_Extrte;
	CString m_Exttrk;

	CString m_cbTcfIn;		// "BeGkAuto3"  BeGkAuto3.tcf
	CString m_cbTcfOut;		// "WgsGeod"	WgsGeod.tcf


public:
	BOOL OnInitializeHandler();
	void OnRunHandler();
	bool PolyBNAParser (FILE *,const char *);
	bool ImportBNA (char const *,char const *);
	bool SkipObject(FILE *pFile);
	bool InitCoordSystems (void);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPSIMPORTWLG_H__1149A4E2_7503_4670_9AF7_A307F4F20D0D__INCLUDED_)
