// importsh.hpp : header file
//

#ifndef _IMPORT_SHEET
#define _IMPORT_SHEET

class CImportParams;
class CHelpText;

/////////////////////////////////////////////////////////////////////////////
// CImportSheet

class CImportSheet : public CPropertySheetExt
{
	DECLARE_DYNAMIC(CImportSheet)

// Construction
public:
	CImportSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	~CImportSheet (void);

// Attributes
public:
   	CTriasPage m_pgTrias;
   	CAbgleichPage m_pgAbgleich;
	CDsnPage m_pgDsn;  
	CFeldPage m_pgFeld;
	CFilterPage m_pgFilter;
	CResultPage m_pgResult;
	CImportResult2 m_pgResult2; 
	CDoAbgleich m_pgDoAgleich;
   	BOOL m_bResult;
	CImportParams m_Params;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportSheet)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
#ifdef WIN32
	//{{AFX_MSG(CImportSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG         
#else		// WIN16	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	                                                    
	afx_msg void OnNext ();
	afx_msg void OnBack ();		
	afx_msg LONG OnNextPage (UINT, LONG);
	void ActPage (int iAct);			// Page akt. 
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support		
#endif		// WIN16

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif          //

