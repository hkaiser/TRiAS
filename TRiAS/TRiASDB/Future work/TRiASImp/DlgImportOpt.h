///////////////////////////////////////////////////////////////////////////
// @doc
// @module DlgImportOpt.h | Declaration of the <c CDlgImportOpt> class

#if !defined(AFX_DLGIMPORTOPT_H__48C04403_9960_11D1_A036_0060975566B4__INCLUDED_)
#define AFX_DLGIMPORTOPT_H__48C04403_9960_11D1_A036_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Helper.h>

///////////////////////////////////////////////////////////////////////////
//
DefineSmartInterface(ComposeStringPairs);		// WComposeStringPairs

/////////////////////////////////////////////////////////////////////////////
// CDlgImportOpt PropertyPage für den OpenDataSource-Wizard

class CDlgImportOpt :
	public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgImportOpt)

// Construction
public:
	CDlgImportOpt();   // standard constructor
	~CDlgImportOpt();

// Dialog Data
	//{{AFX_DATA(CDlgImportOpt)
	enum { IDD = IDD_IMPORTOPT };
	CButton	m_btnVisu;
	CButton	m_btnRelations;
	CButton	m_btnKonfig;
	CButton	m_btnGeometry;
	CButton	m_btnFeatures;
	CButton	m_btnAnsiOEM;
	BOOL	m_bImpAnsiOEM;
	BOOL	m_bImpFeatures;
	BOOL	m_bImpGeometry;
	BOOL	m_bImpRelations;
	BOOL	m_bImpVisu;
	CString	m_strDesc;
	//}}AFX_DATA
	BOOL	m_bOptAnsiOEM;
	BOOL	m_bOptFeatures;
	BOOL	m_bOptGeometry;
	BOOL	m_bOptRelations;
	BOOL	m_bOptVisu;
	BOOL	m_bShouldConfig;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImportOpt)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
////////////////////////////////////////////////////////////////////////////
// hier: Dialog anzeigen: return S_OK, nicht anzeigen: return 
	HRESULT SetProgID(LPCSTR pcProgID) 
	{ 
		m_strProgID = pcProgID;
		return S_OK; 
	}

	HRESULT SetTitle(LPCSTR pcCaption) 
	{ 
		ASSERT(NULL != pcCaption); 
		m_strCaption = pcCaption; 
		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;
		return S_OK; 
	}

	HRESULT SetCreateMode (BOOL fCreate) 
	{
		if (fCreate) 
			return E_FAIL;
		return S_OK; 
	}

	HRESULT SetPairs (IComposeStringPairs *pIPairs) 
	{
		m_Pairs = pIPairs; 
		return S_OK; 
	}

	STDMETHOD(GetImportExt)(IUnknown**pImpExt)
	{
		if ( NULL == pImpExt )
			return E_POINTER;

		WUnknown	unk(m_ImportGeoData);	// AddRef!
		*pImpExt = unk.detach();
		return S_OK;
	}

private:
	CString m_strProgID;
	WComposeStringPairs m_Pairs;
	WImportGeoData	m_ImportGeoData;

// Implementation
protected:
	void AdjustButtons(void);
	HRESULT SaveSettingsToPairs();

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImportOpt)
	afx_msg void OnKonfig();
	afx_msg void OnKoord();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMPORTOPT_H__48C04403_9960_11D1_A036_0060975566B4__INCLUDED_)
