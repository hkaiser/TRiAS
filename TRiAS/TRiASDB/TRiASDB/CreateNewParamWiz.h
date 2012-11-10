///////////////////////////////////////////////////////////////////////////
// @doc
// @module CreateNewParamWiz.h | Declaration of the <c CCreateNewParamWiz> class

#if !defined(_CREATENEWPARAMWIZ_H__C81DD8C7_A235_11D1_BA2A_080036D63803__INCLUDED_)
#define _CREATENEWPARAMWIZ_H__C81DD8C7_A235_11D1_BA2A_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#import "tlb/Helper.tlb" \
	raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") \
	exclude("IParseStringPairs2")

///////////////////////////////////////////////////////////////////////////
//
DefineSmartInterface(ComposeStringPairs);		// WComposeStringPairs

/////////////////////////////////////////////////////////////////////////////
// CCreateNewParamWiz dialog

class CCreateNewParamWiz 
	: public CPropertyPage
{
	DECLARE_DYNCREATE(CCreateNewParamWiz)

// Construction
public:
	CCreateNewParamWiz();
	~CCreateNewParamWiz();

	bool GetCompatibilityModeV2 (void) { return m_fCompatibleV2; }
#if _TRiAS_VER >= 0x0420
	bool GetCompatibilityModeV4 (void) { return m_fCompatibleV4; }
#endif // _TRiAS_VER >= 0x0420
	bool GetCompressedMode() { return m_fCompressed; }

// Dialog Data
	//{{AFX_DATA(CCreateNewParamWiz)
	enum { IDD = IDD_CREATENEWWIZARD_PARAMS };
	CButton	m_cbCompressed;
	CButton	m_cbCompatibleV2;
	//}}AFX_DATA
#if _TRiAS_VER >= 0x0420
	CButton	m_cbCompatibleV4;
#endif // _TRiAS_VER >= 0x0420

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCreateNewParamWiz)
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

	// Die Seite soll nur im CompatibilityMode oder im SysAdminMode angezeigt
	// werden
	CRegKey key;

		if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
			ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
			ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY) &&
			ERROR_SUCCESS == key.Open(key, TEXT("Config")))
		{
		DWORD dwMode = 0;	// nur im CompatibilityMode anzeigen

			key.QueryValue (dwMode, TEXT("UseCompatibilityMode"));
			if (0 != dwMode) return S_OK;		// Anzeigen, da gefordert

		DWORD dwSysAdmin = 0;

			key.QueryValue (dwSysAdmin, TEXT("SystemAdministration"));
			if (0 != dwSysAdmin) return S_OK;	// Anzeigen, da SysAdmin
		}		
		return E_FAIL;		// Laden verhindern (Seite wird nicht gebraucht)
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
	//{{AFX_MSG(CCreateNewParamWiz)
	virtual BOOL OnInitDialog();
	afx_msg void OnCompatibilitymode();
	afx_msg void OnCompressStreams();
	//}}AFX_MSG
#if _TRiAS_VER >= 0x0420
	afx_msg void OnCompatibilitymodeV4();
#endif // _TRiAS_VER >= 0x0420
	DECLARE_MESSAGE_MAP()

private:
	bool m_fCompatibleV2;
	bool m_fCompressed;
#if _TRiAS_VER >= 0x0420
	bool m_fCompatibleV4;
#endif // _TRiAS_VER >= 0x0420
};

#endif // !defined(_CREATENEWPARAMWIZ_H__C81DD8C7_A235_11D1_BA2A_080036D63803__INCLUDED_)
