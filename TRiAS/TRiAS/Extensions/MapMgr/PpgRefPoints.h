//{{AFX_INCLUDES()
#include "maskedit.h"
#include "triascsui.h"
//}}AFX_INCLUDES
#if !defined(AFX_PPGREFPOINTS_H__B1F4C093_0C0D_11D2_8F68_0060085FC1CE__INCLUDED_)
#define AFX_PPGREFPOINTS_H__B1F4C093_0C0D_11D2_8F68_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PpgRefPoints.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpgRefPoints dialog

#if !defined(_SMARTIF_H__F5802CB5_D772_11D1_85F2_00600875138A__INCLUDED_)
#error "You must include <ospace/com/smartif.h>!"
#endif

//DefineSmartInterface2( ITRiASCSTransform, IID_ITRiASCSTransform )
//DefineSmartInterface2( ITRiASCS, IID_ITRiASCS )
//DefineSmartInterface2( ITRiASCSGCS, IID_ITRiASCSGCS )
//DefineSmartInterface2( ITRiASCSPCS, IID_ITRiASCSPCS )

class CPpgRefPoints : public CPropertyPage {
	DECLARE_DYNCREATE(CPpgRefPoints)
	virtual void UpdateControls();
	double	m_p0x, m_p0y, m_p1x, m_p1y;
// Construction
public:
	CPpgRefPoints();
	~CPpgRefPoints();

// Dialog Data
	//{{AFX_DATA(CPpgRefPoints)
	enum { IDD = IDD_PPGREFPOINTS };
	int		m_nSelected;
	CMaskEdit	m_P0X;
	CMaskEdit	m_P0Y;
	CMaskEdit	m_P1X;
	CMaskEdit	m_P1Y;
	CTRiASCSUI	m_csUI;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgRefPoints)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgRefPoints)
	afx_msg void OnButtondefcs();
	afx_msg void OnSelchangeCombopointschema();
	virtual BOOL OnInitDialog();
	afx_msg void OnAdvanceFocusNextP0x();
	afx_msg void OnAdvanceFocusNextP0y();
	afx_msg void OnAdvanceFocusNextP1x();
	afx_msg void OnAdvanceFocusNextP1y();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGREFPOINTS_H__B1F4C093_0C0D_11D2_8F68_0060085FC1CE__INCLUDED_)
