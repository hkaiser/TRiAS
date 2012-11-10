#if !defined(AFX_PPGSELDATASOURCE_H__AF102EC3_BC8F_47D2_9DB8_C001F4BA4B03__INCLUDED_)
#define AFX_PPGSELDATASOURCE_H__AF102EC3_BC8F_47D2_9DB8_C001F4BA4B03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpgSelDataSource.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpgSelDataSource dialog

class CPpgSelDataSource : public CPropertyPage
{
	DECLARE_DYNCREATE(CPpgSelDataSource)
	virtual void UpdateControls();

// Construction
public:
	CPpgSelDataSource();
	~CPpgSelDataSource();

// Dialog Data
	//{{AFX_DATA(CPpgSelDataSource)
	enum { IDD = IDD_PPGSELDATASOURCE };
	CComboBoxEx	m_cbDataSources;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgSelDataSource)
	public:
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgSelDataSource)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL FillDataSources();
	void AdjustButtons();

private:
	CImageList m_ilImages;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGSELDATASOURCE_H__AF102EC3_BC8F_47D2_9DB8_C001F4BA4B03__INCLUDED_)
