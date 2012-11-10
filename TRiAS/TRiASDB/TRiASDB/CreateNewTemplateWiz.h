// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.11.1999 23:23:57 
//
// @doc
// @module CreateNewTemplateWiz.h | Declaration of the <c CCreateNewTemplateWiz> class

#if !defined(_CREATENEWTEMPLATEWIZ_H__A559C28B_AF42_4ED6_BE6D_139A4121B10E__INCLUDED_)
#define _CREATENEWTEMPLATEWIZ_H__A559C28B_AF42_4ED6_BE6D_139A4121B10E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#import "tlb/Helper.tlb" \
	raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") \
	exclude("IParseStringPairs2")

///////////////////////////////////////////////////////////////////////////
//
DefineSmartInterface(ComposeStringPairs);		// WComposeStringPairs

/////////////////////////////////////////////////////////////////////////////
// CCreateNewTemplateWiz dialog

class CCreateNewTemplateWiz 
	: public CPropertyPage
{
	DECLARE_DYNCREATE(CCreateNewTemplateWiz)

// Construction
public:
	CCreateNewTemplateWiz();
	~CCreateNewTemplateWiz();

// Dialog Data
	//{{AFX_DATA(CCreateNewTemplateWiz)
	enum { IDD = IDD_CREATENEWWIZARD_TEMPLATE };
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCreateNewTemplateWiz)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
////////////////////////////////////////////////////////////////////////////
// hier: Dialog nur für CreateDataSource und neue TRiAS-DBs anzeigen
	HRESULT SetProgID(LPCSTR pcProgID) 
	{ 
		USES_CONVERSION;
		ASSERT(!wcscmp(A2OLE(pcProgID), g_cbTRiASProject130)); 
		if (wcscmp (A2OLE(pcProgID), g_cbTRiASProject130))
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
		if (!fCreate) 
			return E_FAIL;
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
	//{{AFX_MSG(CCreateNewTemplateWiz)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};

#endif // !defined(_CREATENEWTEMPLATEWIZ_H__A559C28B_AF42_4ED6_BE6D_139A4121B10E__INCLUDED_)
