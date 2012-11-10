// FrameStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrameStatus window

class CFrameStatus : public CStatusBar
{
private:
	void SetPaneSize( UINT nPane, LPCTSTR lpszPaneText );
	CBitmap	m_bitmap;

// Construction
public:
	CFrameStatus();

// Attributes
public:

// Operations
public:
	void UpdateSize( const LPSIZE lpSize );
	void UpdatePos( const LPPOINT lpPoint );
protected:
	BOOL SetPaneText( int nIndex, LPCTSTR lpszNewText, BOOL bUpdate = TRUE );
	void UpdateTime( const CTime& rTime );
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameStatus)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFrameStatus();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFrameStatus)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
