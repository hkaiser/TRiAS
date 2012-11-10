// editmerk.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CEditMerkmal dialog

class CEditMerkmal : public CDialog
{
	CMapStringToString	TriasIdentMap;
	CMapStringToString	TriasXIdentMap;
	CMapStringToString	AttribTexteMap;
	CMapStringToString	WertTexteMap;

public:
	CMapStringToString	*m_pTriasIdentMap;
	CMapStringToString	*m_pTriasXIdentMap;
	CMapStringToString	*m_pAttribTexteMap;
	CMapStringToString	*m_pWertTexteMap;

// Construction
	CEditMerkmal(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEditMerkmal)
	enum { IDD = IDD_EDIT_MM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	void CopyMap( CMapStringToString*, CMapStringToString* );

	// Generated message map functions
	//{{AFX_MSG(CEditMerkmal)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
