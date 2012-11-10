// ErfassPrivDlg.h : header file
//

class CEditPage1;
class CEditPage2;
class CEditPage3;
class CEditPage4;
class CEditPage5;
class CEditPage6;
class CEditPage7;
class CPG2DArray;
class CPG1GBArray;
class CEigentuemerArray;

/////////////////////////////////////////////////////////////////////////////
// CErfassPrivDlg

class CErfassPrivDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CErfassPrivDlg)

	CEditPage1		*page1;
	CEditPage2		*page2;
	CEditPage3		*page3;
	CEditPage4		*page4;
	CEditPage5		*page5;
	CEditPage6		*page6;
	CEditPage7		*page7;

	BOOL			m_bGeaendert;

// Construction
public:
	BOOL m_bMiteigent;
	void RewriteDT();
	CErfassPrivDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CErfassPrivDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	// Seite 1
	CString		m_strNFP1_IDE;
	CString		m_strNFP1_ENA;
	CString		m_strNFP1_EAN;
	CString		m_strNFP1_EPL;
	CString		m_strNFP1_EOR;
	CString		m_strNFP1_ORT;
	CString		m_strNFP1_FLU;
	double		m_rNFP1_BAR;
	double		m_rNFP1_GFZ;
	double		m_rNFP1_BMZ;
	double		m_rNFP1_VGZ;
	double		m_rNFP1_GUZ;
	CString		m_strNFP1_FST;
	double		m_rNFP1_KAT;
	CTime		m_tNFP1_ANDAT;

	BOOL		m_bEditIDE;

	// Seite 2
	CPG2DArray	m_arrPG2D;
	BOOL		m_bDmodified;

	// Seite 3
	CPG2DArray	m_arrPG2H;
	BOOL		m_bHmodified;

	// Seite 4
	double		m_rAWE;
	double		m_rAEW;
	double		m_rEGW;
	BOOL		m_bZE;
	BOOL		m_bSGR;
	double		m_rFS;
	BOOL		m_bSGT;
	BOOL		m_bKK;
	double		m_rFKK;
	BOOL		m_bKKT;
	BOOL		m_bVF;
	BOOL		m_bK;
	BOOL		m_bFZ;
	BOOL		m_bFE;
	BOOL		m_bFZE;
	CString		m_strSonst;
	CString		m_strANNWL;

	// Seite 5
	CPG1GBArray	m_arrPG1GB;
	BOOL		m_bGBmodified;

	// Seite 6
	CString		m_strBem;

	// Seite 7
	CEigentuemerArray	m_arrEigent;
	BOOL		m_bEmodified;

	CString		m_strCaption;

// Operations
public:
	void		InitPages();
	void		RestorePages();
	BOOL		Geaendert()		{ return m_bGeaendert; }
	BOOL		GBGeaendert()	{ return m_bGBmodified; }
	BOOL		DGeaendert()	{ return m_bDmodified; }
	BOOL		HGeaendert()	{ return m_bHmodified; }
	BOOL		EGeaendert()	{ return m_bEmodified; }
	void		SetGeaendert( BOOL f = TRUE )
								{ m_bGeaendert = f; }
	void		SetGBGeaendert( BOOL f = TRUE )
								{ if ( f ) m_bGeaendert = f;
								  m_bGBmodified = f; }

	void		SetDGeaendert( BOOL f = TRUE )
								{ if ( f ) m_bGeaendert = f;
								  m_bDmodified = f; }

	void		SetHGeaendert( BOOL f = TRUE )
								{ if ( f ) m_bGeaendert = f;
								  m_bHmodified = f; }

	void		SetEGeaendert( BOOL f = TRUE )
								{ if ( f ) m_bGeaendert = f;
								  m_bEmodified = f; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErfassPrivDlg)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual		~CErfassPrivDlg();

protected:
	void RewriteEig();
	void RewriteVF();
	void RewriteGeb();
	BOOL		CreateStandardButtons();
	void		RecalcLayout();
		
	// Generated message map functions
	//{{AFX_MSG(CErfassPrivDlg)
	virtual void    OnOK();
	virtual void    OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
