// DLDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDatenListeDlg dialog
/*
class CGbmControlBar : public SECControlBar
{
// Construction
public:
	DECLARE_DYNAMIC(CGbmControlBar);

	CGbmControlBar();

// Attributes
protected:
	CDialog	m_theDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides

	//{{AFX_VIRTUAL(CGbmControlBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGbmControlBar();

	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );

// Generated message map functions
protected:
	//{{AFX_MSG(CGbmControlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
*/

//class CDatenListeDlg : public CDialog
class CDatenListeDlg : public SECDialogBar
{
	CString		m_strMinIDE;
	long		m_lGSClassID;
	long		m_lGebClassID;
	long		m_lDTClassID;
	long		m_lHofClassID;

// Construction
public:
	BOOL IstClassMember( long, long );
	BOOL IstHofflaeche( long );
	BOOL IstDachteilflaeche( long );
	BOOL IstGebaeude( long );
	void ResetInvalidDockBars( CControlBar* );
	void SelectObject( long );
	void RefreshNFPG1();
	void Bearbeiten( const char* );
	long GSohneIDE();
	void SaveTRiDBNr( int );
	double TB( const char* );
	void RefreshVFDB();
	void RefreshDTDB();
	void RefreshGebDB();
	void CopyArraySelID( CStringArray& );
	void CopyArrayID( CStringArray& );
	CString AktIDE();
	int AnzahlMarkedGS();
	int AnzahlSelectedGS();
	COrteSet*		m_pSetOrte;
	CStrasseSet*	m_pSetStrasse;
//	CSetNF_PG1*		m_pNF_PG1;
//	CSetNF_PG1GB*	m_pNF_PG1GB;
//	CSetNF_PG2D*	m_pNF_PG2D;
//	CSetNF_PG2H*	m_pNF_PG2H;
	CSetNF_PG3*		m_pNF_PG3;
	CStringArray	m_arrOrte;

	void HandleGSTeilen();
	void AddGS( long );
	void RegisterProjekt();
	void ShowSingleData( BOOL = TRUE );
	HWND m_hWndRemove;

	void RefreshListe();
	void ResetListe();
	void SyncListen( BOOL );
	void AddGS( const char*, const char* = NULL );
	void CreateORWnd( CPtrArray*, const char* );

	CString		OrtFromIDE( const char* );

	CDatenListeDlg( CWnd* pParent = NULL, short = 0, CSetNF_PG1* = NULL );   // standard constructor
	~CDatenListeDlg();

// Dialog Data
//	CStatic	m_staticLogo;
	//{{AFX_DATA(CDatenListeDlg)
	enum { IDD = IDD_GBMDATA };
	CStatic	m_txtError;
	CStatic	m_txtBText6;
	CStatic	m_txtBText7;
	CButton	m_btnLoeschen;
	CButton	m_btnGedr;
	CButton	m_btnGedr2;
	CButton	m_btnDetails;
	CStatic	m_txtText12;
	CStatic	m_txtText11;
	CStatic	m_txtText10;
	CStatic	m_txtText0;
	CStatic	m_txtSumme3;
	CStatic	m_txtSumme2;
	CStatic	m_txtSumme1;
	CButton	m_btnSuchen;
	CStatic	m_txtEigent;
	CStatic	m_txtFlurStk;
	CStatic	m_txtFlur;
	CStatic	m_txtStr;
	CStatic	m_txtOrt;
	CStatic	m_txtIDE;
	CStatic	m_txtBText5;
	CStatic	m_txtBText4;
	CStatic	m_txtBText3;
	CStatic	m_txtBText2;
	CStatic	m_txtBText1;
	CStatic	m_txtBText0;
	CListBox	m_lbListe;
	CString	m_strEigent;
	CString	m_strFlur;
	CString	m_strFlurstk;
	CString	m_strIDE;
	CString	m_strOrt;
	CString	m_strStr;
	CString	m_strGSFlaeche;
	CString	m_strBFlaeche;
	CString	m_strBeitrag;
	BOOL	m_bDetailsDummy;
	BOOL	m_bSuchenDummy;
	BOOL	m_bLoeschen;
	BOOL	m_bBBGedr;
	BOOL	m_bGBGedr;
	//}}AFX_DATA
	short m_iOISY;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatenListeDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitClassIDs();
	int m_cy;
	int m_cx;
	BOOL m_bSuspendSelObj;
	UINT m_uiSelObjTimerID;
	void SelectObjectProc();
	void UpdateTriasSelection();
	BOOL ObjektInArray( long, CPtrArray& );
	CMapStringToString m_mapAlleONr;
	CMapStringToPtr m_mapAlleID;
	long m_lAddedObjsSinceTimer;
	long m_lAddedObjsSinceSync;
	UINT m_uiSyncTimerID;
	CResizeItemArray m_arrResizeItem;
	long m_lStartWidth;
	long m_lMinHeight;
	LRESULT TriasFindBObject( long onr );
	void SetupTextObjekt( long onr, const char* text );
	CString GetUniqueIdent( long onr );
	BOOL m_bGSTeilenAtWork;
	void SetObjektName( long onr, const char* name );
	CString GetObjektName( long onr );
	CString m_strMultiName;
	long m_lMultiONr3;
	long m_lMultiONr2;
	long m_lMultiONr1;
	void AddFlurGS( const char*, const char* );
	void AddEignerGS( const char* );
	CStringArray m_arrSelectedIDE;
//	CFont* m_pOldFontGBM;
//	CFont m_FontGBM;
	BOOL ObjektEnthalten( HWND hWnd, long onr );
	CPtrArray m_arrSelectedONr;
	short ObjektSelected( HWND, long );
	void FillListe();
	short AddToListe( long, const char* );
	BOOL RemoveFromListe( long );
	void AddToORWnd( long, long* );
	BOOL RemoveFromORWnd( long, long* );
	BOOL m_bBusy;
	CPtrArray m_arrONr;
	CStringArray m_arrID;
	CPtrArray m_arrAlleONr, m_arrSonstONr;
	CStringArray m_arrAlleID;

public:
	BOOL IstGrundstueck( long onr );
	CString GetIdentNummer( long onr );
	void SetIdentNummer( long onr, const char* id );
	long FindONr( const char* );
	CString FindID( long );

	// Generated message map functions
	//{{AFX_MSG(CDatenListeDlg)
	afx_msg void OnSelchangeListe();
	afx_msg void OnDetails();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnSuchen();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI );
	afx_msg void OnBGedr();
	afx_msg void OnLoeschen();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnGGedr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
