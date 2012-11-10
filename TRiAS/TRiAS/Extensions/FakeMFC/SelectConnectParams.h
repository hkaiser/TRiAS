// SelectConnectParams.h : header file
//

#include "DDXGetFile.h"
#include "DDXGetFolder.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectParams dialog

class CSelectConnectParams : public CPropertyPage
{
	DECLARE_DYNCREATE(CSelectConnectParams)

// Construction
public:
	CSelectConnectParams(UINT uiResID = IDD, BOOL fAsDbmsPage = FALSE, UINT uiCapID = IDD_CAPTION_NEW);
	~CSelectConnectParams();

	void AdjustButtons (bool fForceDisableNext = false);
	void PrepareResults (bool fPrepareAfterClose = false);
	bool ShouldPrepareResults()
	{
		return m_fAsDbmsPage && m_fHasExtPages;
	}

	void AssocCoordSysWiz (UINT uiCaption)
	{
		m_uiCaption = uiCaption;
	}

// Dialog Data
	enum { 
		IDD = IDD_CONNECTION_PARAMS, 
		IDD_DBMS = IDD_CONNECTION_PARAMS_DBMS, 
		IDD_CAPTION_NEW = IDS_CREATENEWWIZARD,
		IDD_CAPTION_ADD = IDS_ADDDATASOURCE,
	};
	//{{AFX_DATA(CSelectConnectParams)
	CStatic	m_ftSelectPrompt;
	CStatic	m_ftDescText;
	CString	m_strConnectDesc;
	CString	m_strConnectName;
	CString	m_strFileName;
	//}}AFX_DATA

	CGetFilenameControl m_sleGetFileName;
	CGetFolderControl m_sleGetFolder;
	BOOL m_fHasExtPages;
	BOOL m_fAsDbmsPage;

	CFiles &GetFiles() 
	{ 
		if (m_pParams -> m_fNameIsFile)
			return m_sleGetFileName.m_Files;
		else if (!m_fAsDbmsPage)
			return m_sleGetFolder.m_Files; 

		return m_Files;
	}

	BOOL LoadExtPages (CString strProgID);
	HRESULT ResetExtPages ();
	static BOOL CALLBACK AddPropSheetPageProc (HPROPSHEETPAGE hpage, LPARAM lParam);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSelectConnectParams)
	public:
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	COpenNewPropertySheet *GetPropSheet()
	{
		ASSERT_KINDOF(COpenNewPropertySheet, GetParent());
		return (COpenNewPropertySheet *)GetParent();
	}

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSelectConnectParams)
	afx_msg void OnChangeConnectionName();
	afx_msg void OnKillfocusConnectionName();
	//}}AFX_MSG
	afx_msg LRESULT OnFileOrDirSelected (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFocusToConnectionName (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSwitchToNextPage (WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	BOOL SaveSelectedDirectory (LPCTSTR pcProgID, LPCTSTR pcFileName);

private:
	CConnectParams *m_pParams;

	BOOL m_fIsTempName;			// Dateiname ist für temporäre Datenquelle
	BOOL m_fNameIsFile;			// die letzten Einstellungen
	BOOL m_fNameIsDir;
	BOOL m_fNameIsSubStg;
	BOOL m_fHasCoordSystem;
	BOOL m_fWasNext;
	CString m_strFileDesc;
	CString m_strProgID;
	DATASOURCEMODE m_rgDataSrcMode;
	CFiles m_Files;

	CCreateNewWiz *m_pCoordSysWiz;
	UINT m_uiCaption;

	WComposeStringPairs m_Pairs;
};
