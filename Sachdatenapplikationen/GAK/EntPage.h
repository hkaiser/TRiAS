// EntPage.h : header file
//

#include "Entsorger1.h"

/////////////////////////////////////////////////////////////////////////////
// CEntPage dialog

class CEntPage : public CEntsorger1
{
	DECLARE_DYNCREATE(CEntPage)

// Construction
public:
	//CString GetVerwertung (void);
	// CString GetArt (void);
	CEntPage();
	~CEntPage();

	// CString GetOrt (void);
	// CString GetPlz (void);
	// CString GetStrasse (void);
	// virtual CString GetName ();

// Dialog Data
	//{{AFX_DATA(CEntPage)
	enum { IDD = IDD_ENTSORGER };
	CEdit	m_edFreiNr;
	CButton	m_btEigen;
	CButton	m_btFrei;
	CEdit	m_edStrasse;
	CEdit	m_edPlz;
	CEdit	m_edOrt;
	CEdit	m_edArt;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEntPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// BOOL FindActRecord (void);
	virtual void SetControlState (bool bDisableAll = false);	// JG Schalten der Ctrl's
																// bDisableAll deaktiviert alle
	void OutputEntsParam (const char *pNummer);
	// Generated message map functions
	//{{AFX_MSG(CEntPage)
	afx_msg LONG OnChangeNummer(UINT, LONG);
	afx_msg LONG OnChangeName(UINT, LONG);
	afx_msg void OnEigenEntsorgung();
	afx_msg void OnFreistellung();
	afx_msg void OnChangeFreiNr();
	//}}AFX_MSG
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	virtual BOOL GetStringData(CString& strTarget);
};
