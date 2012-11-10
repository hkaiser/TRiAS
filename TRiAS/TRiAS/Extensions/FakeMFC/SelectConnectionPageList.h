// SelectConnectionPage.h : header file
//

#include "ConnectParams.h"
#include "ListCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// DataItem, welches in Tree hängt

class CDataServerItem
	: public CConnectParams
{
public:
	CDataServerItem() {}
	~CDataServerItem() {}

	CString GetDesc() { return m_strLongName; }
};

/////////////////////////////////////////////////////////////////////////////
// CDataServerList window

class CDataServerList
	: public CListCtrlEx
{
// Construction
public:
	CDataServerList();

// Attributes
public:

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
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	class CSelectConnectionPage *m_pPage;
	CImageList m_ilImages;
};

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectionPage dialog

class CSelectConnectionPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSelectConnectionPage)

// Construction
public:
	CSelectConnectionPage();
	~CSelectConnectionPage();

// Operations
	void SetDescription (int iItem = -1);
	BOOL InitDataServersFromRegistry (void);
	HRESULT InitDataServers (REFGUID rGuid);
	HRESULT InitDataServer (LPCSTR pcProgID);

// Dialog Data
	//{{AFX_DATA(CSelectConnectionPage)
	enum { IDD = IDD_SELECT_CONNECTION };
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CConnectParams *m_pParams;	// hier müssen die Resultate abgelegt werden
	BOOL m_fNotEmpty;
	LONG m_lCnt;
	DATASOURCEMODE m_rgDatasourceMode;
};

/////////////////////////////////////////////////////////////////////////////
