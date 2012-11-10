// DoImpPge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoImportPage dialog

class CDoImportPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDoImportPage)

// Construction
public:
	CDoImportPage();
	~CDoImportPage();

	void SetParams (CImportParams &Params);

// Dialog Data
	//{{AFX_DATA(CDoImportPage)
	enum { IDD = IDD_DO_IMPORT };
	CStatic	m_stAction;
	CProgressCtrl	m_ctProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDoImportPage)
	public:
	virtual BOOL OnSetActive();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bBreak;
	CImportParams *m_pParams;
	CPropertySheet *GetParent (void) { return (CPropertySheet *) CWnd::GetParent (); }
	void SetIniEntry(void);			//	die Ausgabetabelle in INI-Datei schreiben	
	void WasInterrupted (void);
	long GetAnzahl (void);			// Bestimme Anzahl Datensätze im QuellTabelle
	void CreateLink (void);			// erstelle Link zwischen Eingabetabelle u. Ausgabedatenbank
	void DestroyLink(void);			// Link wieder löschen
	void GetFindString (CString &strFind);	// Suchstring-Format aufbauen
	BOOL FindOutputRecord (const char *pFindString);

	// Generated message map functions
	//{{AFX_MSG(CDoImportPage)
		// NOTE: the ClassWizard will add member functions here
	afx_msg LONG OnDoImport (UINT, LONG);
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
