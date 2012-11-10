// DlgPgBW.h : header file
//
class CDlgPgBW : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPgBW)

// Construction
public:
	CDlgPgBW();
	~CDlgPgBW();

// Dialog Data
	//{{AFX_DATA(CDlgPgBW)
	enum { IDD = IDD_PAGE_BWPARAM };
	BOOL	m_bTransparent;
	int		m_nChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPgBW)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateControls();
	// Generated message map functions
	//{{AFX_MSG(CDlgPgBW)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckTransparent();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#if 0 // obsolete
/////////////////////////////////////////////////////////////////////////////
// CDlgPgBW dialog
//{{AFX_INCLUDES()
#include "colorctrl.h"
//}}AFX_INCLUDES

class CColorWnd : public CStatic
{
	COLORREF	m_color;
// Construction
public:
	void Draw( int R, int G, int B );
	CColorWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
#endif