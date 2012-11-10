// @doc
// @module CTFParams.h | declaration file for CCTFParams

#if !defined(AFX_CTFPARAMS_H__C862BA33_A9C1_11D1_A062_0060975566B4__INCLUDED_)
#define AFX_CTFPARAMS_H__C862BA33_A9C1_11D1_A062_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Resource.h"
#include "CoordTransBase.h"	// renamed JG990125

/////////////////////////////////////////////////////////////////////////////
// CCTFParams dialog

class CCTFParams : 
	public CPropertyPage
{
	DECLARE_DYNCREATE(CCTFParams)

// Construction
public:
	CCTFParams();
	~CCTFParams();

	void SetTargetCTF (class CCoordTrans *pCTF);

// Dialog Data
	//{{AFX_DATA(CCTFParams)
	enum { IDD = IDD_COORDPARAM };
	CComboBox	m_cbCoordSystemGeod;
	CButton	m_rbNative;
	CButton	m_rbTransMerc;
	CComboBox	m_cbMeridian;
	CStatic	m_ftMeridian;
	CComboBox	m_cbStrBreite;
	CStatic	m_ftStrBreite;
	CButton	m_rbAutoMeridian;
	CButton	m_rbSelectMeridian;
	CSpinButtonCtrl	m_sbPrec;
	CEdit	m_slePrec;
	CComboBox	m_cbCoordSystem;
	CStatic	m_ftCoordSystem;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCTFParams)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCTFParams)
	virtual BOOL OnInitDialog();
	afx_msg void OnAutomeridian();
	afx_msg void OnGaucoords();
	afx_msg void OnGeocoords();
	afx_msg void OnSelectmeridian();
	afx_msg void OnSelchangeStrbreite();
	afx_msg void OnSelchangeSelellipse();
	afx_msg void OnChangePrecision();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void CalcMeridians (void);
	void FillMeridian (int iStrBreite, int iMeridian);
	void SwitchState (COORDTRANSFORMTYPE rgCTF, COORDTRANSFORMMODE rgCTFMode = CTFMODE_AutoMeridian);
	int GetStrBreite (void);
	int GetMeridian (void);
	int GetPrecision (void)	{ return m_sbPrec.GetPos();	}

private:
	CFont m_Font;
	CCoordTrans *m_pCTF;

	int m_iMin3, m_iMax3;		// min/Max. Streifen dieser GeoDB
	int m_iMin6, m_iMax6;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTFPARAMS_H__C862BA33_A9C1_11D1_A062_0060975566B4__INCLUDED_)
