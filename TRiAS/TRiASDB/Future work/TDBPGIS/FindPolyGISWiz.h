///////////////////////////////////////////////////////////////////////////
// @doc
// @module CreateNewParamWiz.h | Declaration of the <c CFindPolyGISWiz> class

#if !defined(_CREATENEWPARAMWIZ_H__C81DD8C7_A235_11D1_BA2A_080036D63803__INCLUDED_)
#define _CREATENEWPARAMWIZ_H__C81DD8C7_A235_11D1_BA2A_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#import "tlb/Helper.tlb" \
	raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") 

#include <AfxDlgs.h>
#include "DDXGetFile.h"

///////////////////////////////////////////////////////////////////////////
//
DefineSmartInterface(ComposeStringPairs);		// WComposeStringPairs

/////////////////////////////////////////////////////////////////////////////
// CFindPolyGISWiz dialog

class CFindPolyGISWiz 
	: public CPropertyPage
{
	DECLARE_DYNCREATE(CFindPolyGISWiz)

// Construction
public:
	CFindPolyGISWiz();
	~CFindPolyGISWiz();

// Dialog Data
	//{{AFX_DATA(CFindPolyGISWiz)
	enum { IDD = IDD_FINDPOLYGISWIZARD_PARAMS };
	//}}AFX_DATA
	CGetFilenameControl m_sleFileName;
	CString m_strFileName;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFindPolyGISWiz)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	void PrepareResult();

public:
////////////////////////////////////////////////////////////////////////////
// hier: Dialog nur für CreateDataSource und neue TRiAS-DBs anzeigen
	HRESULT SetProgID(LPCSTR pcProgID) 
	{ 
		USES_CONVERSION;
		ASSERT(!wcscmp(A2OLE(pcProgID), g_cbDatabase)); 
		if (wcscmp (A2OLE(pcProgID), g_cbDatabase))
			return E_FAIL;

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
#if !defined(_READWRITE)
		if (fCreate) 
			return E_FAIL;
#endif // !defined(_READWRITE)
		return S_OK; 
	}
	HRESULT SetPairs (IComposeStringPairs *pIPairs) 
	{
		m_Pairs = pIPairs; 
		return S_OK; 
	}

private:
	CString m_strProgID;
	WComposeStringPairs m_Pairs;

// Implementation
protected:
	void AdjustButtons(void);
	HRESULT SaveSettingsToPairs();

protected:
	// Generated message map functions
	//{{AFX_MSG(CFindPolyGISWiz)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};

#endif // !defined(_CREATENEWPARAMWIZ_H__C81DD8C7_A235_11D1_BA2A_080036D63803__INCLUDED_)
