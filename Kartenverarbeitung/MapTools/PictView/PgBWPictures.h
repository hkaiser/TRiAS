/////////////////////////////////////////////////////////////////////////////
// CPgBWPictures dialog
//{{AFX_INCLUDES()
#include "colors.h"
//}}AFX_INCLUDES

class CPgBWPictures : public CBasePpg {
	DECLARE_DYNCREATE(CPgBWPictures)

// Construction
public:
	CPgBWPictures();
	~CPgBWPictures();

// Dialog Data
	//{{AFX_DATA(CPgBWPictures)
	enum { IDD = IDD_PG_TRANSP };
	CButton	m_btnSelColor;
	CButton	m_btnChannel;
	BOOL	m_bTransparent;
	int		m_nChannel;
	CColors	m_colorCtrl;
	short	m_rgbRed;
	short	m_rgbGreen;
	short	m_rgbBlue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPgBWPictures)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateControls();
	// Generated message map functions
	//{{AFX_MSG(CPgBWPictures)
	afx_msg void OnCheckTransp();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSelcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
