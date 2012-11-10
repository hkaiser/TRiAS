// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 18.12.2002 11:38:08 
//
// @doc
// @module CreateConnectfilter.h | Declaration of the <c CCreateConnectfilter> class

#if !defined(_CREATECONNECTFILTER_H__6522DACC_CEC5_4615_971D_D600C93CF950__INCLUDED_)
#define _CREATECONNECTFILTER_H__6522DACC_CEC5_4615_971D_D600C93CF950__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateConnectfilter dialog

class CCreateConnectfilter : public CDialog
{
// Construction
public:
	CCreateConnectfilter(UINT uiResId = IDD, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD_NOAPPLY = IDD_CREATENEW_FILTER };

	//{{AFX_DATA(CCreateConnectfilter)
	enum { IDD = IDD_CREATENEW_FILTER_APPLY };
	CButton	m_cbApplyToAll;
	CComboBoxEx	m_cbFilters;
	int		m_iOperator;
	CString	m_strOperatorDesc;
	//}}AFX_DATA

// DataAccess
	CString GetFilterName() { return m_strFilterName; }
	void SetFilterName(char const *pcName) { m_strFilterName = pcName; }

	BOOL GetApplyToAllConnections() { return m_fHasApplyToAll ? m_fApplyToAll : FALSE; }
	void SetApplyToAllConnections(BOOL fApply) { m_fApplyToAll = m_fHasApplyToAll ? fApply : FALSE; }

	BOOL GetNameIsNew() { return m_fNameIsNew; }

	int GetFilterTyp() 
	{ 
		if (!m_fIsPolygon) {
			return (0 == m_iOperator) ? CF_Rectangle_OverlappedObjects : 
				CF_Rectangle_ContainedObjects; 
		}
		else {
			return (0 == m_iOperator) ? CF_Polygon_OverlappedObjects : 
				CF_Polygon_ContainedObjects; 
		}
	}
	void SetFilterTyp(int iType) 
	{ 
		if (CF_Rectangle_OverlappedObjects == iType ||
			CF_Rectangle_OverlappedPoints == iType ||
			CF_Rectangle_OverlappedContainers == iType ||
			CF_Polygon_OverlappedObjects == iType ||
			CF_Polygon_OverlappedPoints == iType ||
			CF_Polygon_OverlappedContainers == iType)
		{
			m_iOperator = 0;
		}
		else {
			m_iOperator = 1;
		}
		m_fIsPolygon = (iType & CF_Polygon_Flag) ? TRUE : FALSE;
	}

	void SetEditMode(BOOL fShowOnly) { m_fShowPropertiesOnly = fShowOnly; }
	void SetTargetObject(HOBJECT hTargetONr) { m_hTargetONr = hTargetONr; }

	BOOL ApplySettings(BOOL fFullApply);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateConnectfilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL CALLBACK EnumConnectionFilters(char *pName, BOOL, void *pData);
	BOOL CALLBACK EnumConnectionsNewName(long hPr, BOOL, void *pData);
	BOOL CALLBACK EnumConnectionsOldName(long hPr, BOOL, void *pData);

	// Generated message map functions
	//{{AFX_MSG(CCreateConnectfilter)
	virtual BOOL OnInitDialog();
	afx_msg void OnOverlapped();
	afx_msg void OnContained();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	bool PrepareResults();
	HRESULT InitGeometry(IDispatch *pICS, _DGMGeometry *pPolygon);

private:
	CImageList m_ilImages;
	CString m_strFilterName;
	BOOL m_fApplyToAll;
	BOOL m_fNameIsNew;
	BOOL m_fHasApplyToAll;
	BOOL m_fShowPropertiesOnly;
	BOOL m_fIsPolygon;
	HOBJECT m_hTargetONr;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_CREATECONNECTFILTER_H__6522DACC_CEC5_4615_971D_D600C93CF950__INCLUDED_)
