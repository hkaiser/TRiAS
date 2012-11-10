// FlAbgleichDlg.h : header file
//

class CSetZW_PG1GB;
class CSetZW_PG2D;
class CSetZW_PG2H;

/////////////////////////////////////////////////////////////////////////////
// CFlAbgleichDlg dialog

class CFlAbgleichDlg : public CDialog
{
	CSetZW_PG1GB	*m_pdbZW_PG1GB;
	CSetZW_PG2D		*m_pdbZW_PG2D;
	CSetZW_PG2H		*m_pdbZW_PG2H;

// Construction
public:
	CFlAbgleichDlg(CWnd* pParent = NULL);   // standard constructor
	~CFlAbgleichDlg();

// Dialog Data
	//{{AFX_DATA(CFlAbgleichDlg)
	enum { IDD = IDD_ABGLEICH1 };
	int		m_iAnzahlGS;
	int		m_iAnzahlGeb;
	int		m_iAnzahlDT;
	int		m_iAnzahlVF;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlAbgleichDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RewriteVF();
	void RewriteDT();
	void RewriteGeb();

	// Generated message map functions
	//{{AFX_MSG(CFlAbgleichDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
