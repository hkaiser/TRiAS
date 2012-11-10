// AbfSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbfSheet

class CAbfSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAbfSheet)

// Construction
public:
	void DeleteAbfallGruppe();
	void SetCaption();
/*
	CString GetVerwertung (void);
	CString GetEntsArt (void);
	CString GetEntsPlz (void);
	CString GetEntsOrt (void);
	CString GetEntsStrasse (void);
	CString GetEntsName (void);
	CString GetTranspPlz (void);
	CString GetTranspOrt (void);
	CString GetTranspStrasse (void);
	CString GetTranspName (void);
	CString GetVorbehandlung (void);
	CString GetAbfallName (void);
	CString GetMengeM (void);
	CString GetMengeT (void);
	CString GetSonderAbfall (void);
*/
	CAbfSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbfSheet)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAbfSheet() {}

// public Functions
	void UpdatePages(bool bSaveAndValidate)
	{
		m_pgAbfall.UpdateData(bSaveAndValidate);
		m_pgEntPage.UpdateData(bSaveAndValidate);
		m_pgTransPage.UpdateData(bSaveAndValidate);
		m_pgBetreiber.UpdateData(bSaveAndValidate);
	}

	// Generated message map functions
protected:
	CAbfPage m_pgAbfall;
	CEntPage m_pgEntPage;
	CEntsorger1 m_pgEntPage2;
	CTranspPage m_pgTransPage;
	CBetreiberPage m_pgBetreiber;
	//{{AFX_MSG(CAbfSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
