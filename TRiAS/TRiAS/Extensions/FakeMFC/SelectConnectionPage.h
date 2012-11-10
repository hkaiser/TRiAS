// SelectConnectionPage.h : header file
//

#include "ConnectParams.h"
#include "TreeCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CDataServerList window

class CDataServerList
	: public CSECTreeCtrlEx
{
// Construction
public:
	CDataServerList();

// Attributes
public:
	void SetDeleting() { m_fIsDeleting = true; }
	void ResizeColumns();
	void HideToolTip();

// Operations
public:
	void InitListCrtl (class CSelectConnectionPage *pPage);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataServerList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDataServerList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataServerList)
	afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	class CSelectConnectionPage *m_pPage;
	CImageList m_ilImages;
	bool m_fIsDeleting;
};

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectionPage dialog

class CSelectConnectionPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSelectConnectionPage)

// Construction
public:
	CSelectConnectionPage(UINT uiCapID = IDD_CAPTION_NEW);
	~CSelectConnectionPage();

// Operations
	void SetDescription (HTREEITEM hItem = NULL);
	BOOL InitDataServersFromRegistry (void);
	HRESULT InitDataServers (REFGUID rGuid);
	HRESULT InitDataServer (HTREEITEM hParent, LPCSTR pcProgID);

	void DlgClosed();

// Dialog Data
	//{{AFX_DATA(CSelectConnectionPage)
	enum { 
		IDD = IDD_SELECT_CONNECTION, 
		IDD_CAPTION_NEW = IDS_CREATENEWWIZARD,
		IDD_CAPTION_ADD = IDS_ADDDATASOURCE,
	};
	CStatic	m_ftDescription;
	CDataServerList	m_lvConnections;
	CStatic	m_ftConnection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSelectConnectionPage)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
#if defined(_DEBUG)
public:
	virtual BOOL OnWizardFinish();
#endif // _DEBUG

	COpenNewPropertySheet *GetPropSheet()
	{
		ASSERT_KINDOF(COpenNewPropertySheet, GetParent());
		return (COpenNewPropertySheet *)GetParent();
	}

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSelectConnectionPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkConnections(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnListCRPressed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CConnectParams *m_pParams;	// hier müssen die Resultate abgelegt werden
	BOOL m_fNotEmpty;
	LONG m_lCnt;
	DATASOURCEMODE m_rgDatasourceMode;
};

/////////////////////////////////////////////////////////////////////////////
