// DlgMapProperties.h : header file
//

#include <lpict/PictDlg.h>

//{{AFX_INCLUDES()
#include "maskedit.h"
//}}AFX_INCLUDES

/////////////////////////////////////////////////////////////////////////////
// CListCtrlGCP window

class CListCtrlGCP : public CListCtrlEx
{
	int	m_widthColumns[5];
	CString	FormatCoord( double val, TOPOMAPTYPE mapType = MPT_UNKNOWN );
// Construction
public:
	void CommonConstruct();
	CListCtrlGCP();

// Attributes
public:
	TOPOMAPTYPE	m_mapType;

// Operations
public:
	BOOL AddGCP( GCP& gcp, int nImageIndex = -1);
	GCP GetGCP( int idx );
	void RecalcLayout();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlGCP)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlGCP();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlGCP)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

void AFXAPI DDX_Control(CDataExchange* pDX, int nIDC, CListCtrlGCP& rControl, CGCPArray& gcpArray );

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPgMappropCommon dialog

class CPgMappropCommon : public CPropertyPage
{
	DECLARE_DYNCREATE(CPgMappropCommon)

// Construction
public:
	BOOL bReadOnly;
	CPgMappropCommon();
	~CPgMappropCommon();

// Dialog Data
	//{{AFX_DATA(CPgMappropCommon)
	enum { IDD = IDD_PG_MAPPROP_COMMON };
	CListCtrlGCP	m_listGCP;
	CMaskEdit	m_editYTop;
	CMaskEdit	m_editYBtm;
	CMaskEdit	m_editXTop;
	CMaskEdit	m_editXBtm;
	CString	m_strXBtm;
	CString	m_strYBtm;
	CString	m_strYTop;
	CString	m_strM1;
	CString	m_strM2;
	CString	m_strM3;
	CString	m_strM4;
	CString	m_strXTop;
	//}}AFX_DATA

	TOPOMAPTYPE	m_mapType;
	GEOPOINT		m_ptBtmLeft;
	GEOPOINT		m_ptTopRight;
	CGCPArray	m_gcpArray;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgMappropCommon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COORDTYPE m_ct;
	void RetrieveValues();
	void PrepareValues();
	// Generated message map functions
	//{{AFX_MSG(CPgMappropCommon)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedEditXBtm();
	afx_msg void OnTextChangedEditXTop();
	afx_msg void OnTextChangedEditYBtm();
	afx_msg void OnTextChangedEditYTop();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDlgMapProperties

class CDlgMapProperties : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgMapProperties)

	CPgMappropCommon	m_pgComm;
	CPagePictprop		m_pgPictProp;

// Construction
public:
	CPicture* m_pPicture;
	CDlgMapProperties( CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	enum { IDD = IDD_DLG_MAPPROPERTIES };

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMapProperties)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgMapProperties();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgMapProperties)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
