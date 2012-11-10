// dlglines.h : header file
//

class	CDlgLinesigParam;		// Vorwärtsdeklaration...

/////////////////////////////////////////////////////////////////////////////
// CPageSelectSig dialog

class CPageSelectSig : public CPropertyPage {
	DECLARE_DYNCREATE(CPageSelectSig)
	CImageList	m_imgList;
	CString		m_strSigname;

// Construction
public:
	CPageSelectSig();
	~CPageSelectSig();

// Dialog Data
	//{{AFX_DATA(CPageSelectSig)
	enum { IDD = IDD_DLGPAGE_SELECT };
	CTreeCtrlEx	m_treeSig;
	//}}AFX_DATA

	MetafileMap		*m_pMapOfSignatures;
//	CMapStringToOb	*m_pListOfSignatures;

// Operations
protected:
	CDlgLinesigParam	*GetParent();
public:
	void	UpdatePreview( );

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSelectSig)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageSelectSig)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeLinesig(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline CDlgLinesigParam* CPageSelectSig::GetParent()
	{ return (CDlgLinesigParam*) CPropertyPage::GetParent(); }

/////////////////////////////////////////////////////////////////////////////
// CPageGeometry dialog

class CPageGeometry : public CPropertyPage {
	DECLARE_DYNCREATE(CPageGeometry)

// Construction
public:
	CPageGeometry();
	~CPageGeometry();

// Dialog Data
	//{{AFX_DATA(CPageGeometry)
	enum { IDD = IDD_DLGPAGE_GEOMETRY };
	CSpinButtonCtrl	m_sigOffsetY;
	CSpinButtonCtrl	m_sigOffsetX;
	CSpinButtonCtrl	m_sigWidth;
	CSpinButtonCtrl	m_sigHeight;
	BOOL	m_bSwapX;
	BOOL	m_bSwapY;
	long	m_nSigHeight;
	long	m_nSigWidth;
	int		m_nSigOffsetY;
	int		m_nSigOffsetX;
	//}}AFX_DATA

protected:

// Operations
protected:
	CDlgLinesigParam	*GetParent();
public:
	void	UpdatePreview();

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageGeometry)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageGeometry)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnfromheight();
	afx_msg void OnBtnfromwidth();
	afx_msg void OnCheckswapx();
	afx_msg void OnCheckswapy();
	afx_msg void OnDeltaposSpinSigxoffset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSigyoffset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSigheight(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSigwidth(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

inline CDlgLinesigParam* CPageGeometry::GetParent()
	{ return (CDlgLinesigParam*) CPropertyPage::GetParent(); }

/////////////////////////////////////////////////////////////////////////////
// CWmfShape window

class CWmfShape : public CStatic {
protected:
	CMetaFile	*m_pMetaFile;
	CDRect		m_rcDraw;
	CSize		m_szPict;
	CPoint		m_ptOffset;
	BOOL		m_bSwapX;
	BOOL		m_bSwapY;
public:

// Construction
public:
	CWmfShape();

// Operations
public:
	BOOL	Create( const RECT& rect, CWnd* pParent, UINT nID );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWmfShape)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWmfShape();

	void	GetClientRect( LPRECT lpRect ) const;
	void	GetDrawRect( LPRECT lpRect ) const;
	BOOL	GetPictureRect( LPRECT pRect ) const;

	void	SetDrawRect( const CSize& rSizePict, BOOL bInvalidate = TRUE );
	void	SetOffset( const CPoint& rPtOffset, BOOL bInvalidate = TRUE );
	void	SetSwap( BOOL swapX = FALSE, BOOL swapY = FALSE, BOOL bInvalidate = TRUE );
	void	SetMetaFile( CMetaFile *pMetaFile, BOOL bInvalidate = TRUE );

	// Generated message map functions
protected:
	void		DrawOffset( CDC *pDC );
	//{{AFX_MSG(CWmfShape)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CPageDebug dialog

class CPageDebug : public CPropertyPage
{
// Construction
public:
	CPageDebug();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageDebug)
	enum { IDD = IDD_DLG_SPECPARAM };
	CSpinButtonCtrl	m_spinScale;
	CSpinButtonCtrl	m_spinArc;
	long	m_scale;
	long	m_arc;
	BOOL	m_bClipExtended;
	BOOL	m_bMarkSegments;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageDebug)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageDebug)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDlgLinesigParam

class CDlgLinesigParam : public CPropertySheet {
	DECLARE_DYNAMIC(CDlgLinesigParam)

	COLORREF m_sigColor;
	CWmfShape	m_wmfShape;
	BOOL		m_bFirstDraw;

// Construction
public:
	CDlgLinesigParam( CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	enum { IDD = IDD_DLGSHEET_LINESIG };

	CPageSelectSig	m_pageSelectSig;
	CPageGeometry	m_pageGeometry;
	CPageDebug		m_pageDebug;

	BOOL			m_bAdminMode;

// Operations
protected:
	void	CreateCommon( );

public:
	void	UpdatePreviewPict( CMetaFile *pMF, BOOL bInvalidate = TRUE );
	void	UpdatePreviewSize( const CSize& rSize, BOOL bInvalidate = TRUE );
	void	UpdatePreviewOffset( const CPoint& rPtOffset, BOOL bInvalidate = TRUE );
	void	UpdatePreviewSwap( BOOL swapX, BOOL swapY, BOOL bInvalidate = TRUE );
	BOOL	GetPictureRect( LPRECT pRect ) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLinesigParam)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgLinesigParam();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgLinesigParam)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
