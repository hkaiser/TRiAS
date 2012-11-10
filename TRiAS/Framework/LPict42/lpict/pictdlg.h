// pictdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPagePictprop dialog

#include "lmfcx/LafxCtrl.h"

class AFX_EXT_CLASS CPagePictprop : public CPropertyPage
{
	DECLARE_DYNCREATE(CPagePictprop)

// Construction
public:
	CPicture* Attach( CPicture* pPicture );
	CPagePictprop();
	~CPagePictprop();

// Dialog Data
	//{{AFX_DATA(CPagePictprop)
	CTreeCtrlEx	m_treeProp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPagePictprop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPicture* m_pPicture;
	// Generated message map functions
	//{{AFX_MSG(CPagePictprop)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
