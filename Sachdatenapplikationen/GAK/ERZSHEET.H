// Erzsheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErzeugerSheet
class CErzeugerSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CErzeugerSheet)

// Construction
public:
	// CString GetBranchenName ();
	CErzeugerSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErzeugerSheet)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CErzeugerSheet() {}

protected:
	CFirmaPage m_pgFirma;
	CAnfallStelle m_pgAnfallStelle;
	CEntsPage m_pgEntsorgung;
	CBranchPage m_pgBranche;
	CPartnerPage m_pgPartner;

	// Generated message map functions
	//{{AFX_MSG(CErzeugerSheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
