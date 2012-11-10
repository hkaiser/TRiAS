#if !defined(AFX_PPGBASE_H__A6EEA9A6_FE40_11D1_8F55_0060085FC1CE__INCLUDED_)
#define AFX_PPGBASE_H__A6EEA9A6_FE40_11D1_8F55_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PpgBase.h : header file
//

#include "maskedit.h"

/////////////////////////////////////////////////////////////////////////////
// CPpgBase dialog

class CPpgBase : 
	public CPropertyPage 
{
private:
	DECLARE_DYNAMIC(CPpgBase)
	UINT	m_IDD;
	virtual void UpdateControls() = 0;

	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();

protected:
	virtual LRESULT OnWizardNext(UINT nextID);
	CMapImportDlg	*m_pParent;
	bool	MEInitMask( CMaskEdit& rCtl );
	bool	MESetValue( CMaskEdit& rCtl, const double& val );
	bool	MEGetValue( double& val, CMaskEdit& rCtl );
// Construction
public:
	CPpgBase(UINT nID);
	~CPpgBase();

// Dialog Data
	//{{AFX_DATA(CPpgBase)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgBase)
	public:
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgBase)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#define	CPropertyPage	CPpgBase

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGBASE_H__A6EEA9A6_FE40_11D1_8F55_0060085FC1CE__INCLUDED_)
