// WherePge.h : header file
//

#include "AutoListComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// CWherePage dialog
class CWhereKlauselPropAct;
class CWherePage;

class CWherePage : 
	public CPropertyPage
{
	//DECLARE_DYNCREATE(CWherePage)

private:
	DWORD m_dwFlags;
	BOOL m_bIsChecked;
	CWhereKlauselPropAct *m_pAction;
	CODBCInfos m_OdbcInfos;
	UINT *m_pFunctionsArray;
	UINT *m_pOperatorsArray;
	IEnumObjectsByNumber *m_pIEnumObjs;

// Construction
public:
	CWherePage(UINT uiResID);
	~CWherePage();

// Dialog Data
	//{{AFX_DATA(CWherePage)
	enum { IDD = IDD_INPUT_WHERE_PAGE1 };
	CToolTipButton m_btContents;
	CAutoListComboBox	m_cbTables;
	CFileDlg	m_dlgFileDsn;
	CUserDlg	m_dlgUserDsn;
	CUserDlg	m_dlgSystemDsn;
	CHelpText	m_stDescription;
	CAutoListComboBox	m_cbOperators;
	CAutoListComboBox	m_cbFunctions;
	CEdit		m_edFilter;
	CAutoListComboBox	m_cbFields;
	CTabbedDialogs	m_tbDsn;
	CButton		m_btCheck;
	//}}AFX_DATA

//	Parameter
	CString m_strFilter,
			m_strDataSource,
			m_strAlias,
			m_strTable,
			m_strKoppelFeld;
	DataSourceType m_tpDataSource;

	static CWherePage *CreateInstance (UINT uiResID, CWhereKlauselPropAct *);
	HRESULT SetEnumLONG (IEnumObjectsByNumber *pIEnum);
	HRESULT GetEnumLONG (IEnumObjectsByNumber **ppIEnum);
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWherePage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWherePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnFilterCheck();
	afx_msg void OnChangeFilterKlausel();
	afx_msg void OnSelchangeFilterFeld();
	afx_msg void OnSelchangeFilterFunkt();
	afx_msg void OnSelchangeFilterOpera();
	afx_msg void OnSelchangeTables();
	afx_msg void OnContents();
	afx_msg void OnSetfocusFilterFeld();
	afx_msg void OnSetfocusFilterFunkt();
	afx_msg void OnSetfocusFilterOpera();
	//}}AFX_MSG

	BOOL ReadOdbcInfos (const char *pDataSource, DataSourceType tType);
	BOOL ReadParams (CRecordset &RecSet, ULONG &ulMerkmalsKode, CString &strClasses, HPROJECT hPr);
	void SetControlState ();
	void CopyField ();
	void CopyFunction ();
	//void CopyTable ();
	void CopyOperator ();

	void SetButtons (void);			// Button für den WIZZARD setzen
	CPropertySheet *GetPropertySheet (void) { return (CPropertySheet *)GetParent (); } 
	
	DECLARE_MESSAGE_MAP()
};
