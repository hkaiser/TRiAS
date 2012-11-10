// PreviewDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreviewDialog dialog

class CPreviewDialog : public CDialog
{
// Construction
public:
	BOOL m_bWithOptionDialog;
	RECTL m_rclRectangle;
	RECTL m_rclPage;
	RECTL m_rclClipBox;
	RECTL m_rclFrame;
	CStringArray* m_pPrintListe;
	CPreviewDialog(CWnd* pParent = NULL);   // standard constructor
	~CPreviewDialog();

// Dialog Data
	//{{AFX_DATA(CPreviewDialog)
	enum { IDD = IDD_PREVIEW };
	CButton	m_btnPrevPage;
	CButton	m_btnNextPage;
	CButton	m_btnRect;
	CStatic	m_txtPageText;
	CButton	m_btn2Seiten;
	CButton	m_btnOK;
	CComboBox	m_cbSeiten;
	CStatic	m_wndFrame0;
	CString	m_strPageText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewDialog)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSize m_sizeTopLeftOffset;
	HENHMETAFILE m_hdcMetaFile;
	BOOL m_bUseMetaFile;
	void RenderGeoDB( CPreviewDC* pDC );
	CString Identisch( const char*, const char* );
	CString m_strEqIDE;
	CPrintAnlage1* m_pPA;
	CPrintAnlageArray	m_pArray;

	void OnDisplayPageNumber( UINT, UINT );
	void PrintPage( CPreviewDC*, CPrintInfo*, UINT );
	UINT m_nHeadRoom;
	CPoint GetDeviceScrollPosition() const;
	UINT m_cyPixelsPerInch;
	UINT m_cxPixelsPerInch;
	UINT m_nSecondPageOffset;
	void SetScaledSize( UINT );
	CSize CalcScaleRatio( CSize, CSize );
	CSize CalcPageDisplaySize();
	void PositionPage( UINT );
	void OnPrepareDC( CDC*, CPrintInfo* );
	void OnDraw( CDC* );
	void OnEndPrinting( CDC*, CPrintInfo* );
	struct PAGE_INFO
	{
		CRect rectScreen; // screen rect (screen device units)
		CSize sizeUnscaled; // unscaled screen rect (screen device units)
		CSize sizeScaleRatio; // scale ratio (cx/cy)
		CSize sizeZoomOutRatio; // scale ratio when zoomed out (cx/cy)
	};

	PAGE_INFO m_pageInfoArray[2];
	PAGE_INFO* m_pPageInfo;
	UINT m_nZoomState;
	UINT m_nCurrentPage;
	UINT m_nMaxPages;
	void OnEndPrintPreview( CDC* pDC, CPrintInfo* pInfo, POINT point );
	void SetCurrentPage( UINT, BOOL );
	UINT m_nZoomOutPages;
	UINT m_nPages;
	CSize m_sizePrinterPPI;
	void OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo );
	BOOL OnPreparePrinting( CPrintInfo* pInfo );
	CPrintInfo* m_pPreviewInfo;
	CPreviewDC* m_pPreviewDC;
	CDC m_dcPrint;
	BOOL m_bCreated;

	// Generated message map functions
	//{{AFX_MSG(CPreviewDialog)
	afx_msg void OnGetMinMaxInfo( MINMAXINFO FAR* );
	afx_msg void OnPaint();
	afx_msg void OnOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePage();
	afx_msg void OnZweiSeiten();
	afx_msg void OnRect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
