#if !defined(AFX_EDBS_CFGIMPOBAK_H__058472E3_24BD_11D4_8F2A_004F4E05A09F__INCLUDED_)
#define AFX_EDBS_CFGIMPOBAK_H__058472E3_24BD_11D4_8F2A_004F4E05A09F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EDBS_CfgImpOBAK.h : Header-Datei
//
#include "resource.h"
#include "separator.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld EDBS_CfgImpOBAK 

class CEDBS_CfgImpOBAK : public CPropertyPage
{
	DECLARE_DYNCREATE(CEDBS_CfgImpOBAK)

// Konstruktion
public:
	void Load_OBAK();
	CEDBS_CfgImpOBAK();
	~CEDBS_CfgImpOBAK();

	void SetWizardButtons( void );

	CCfg*	m_pConfiguration;
	void LoadConfig( void );
	void SaveConfig( void );

// Dialogfelddaten
	//{{AFX_DATA(CEDBS_CfgImpOBAK)
	enum { IDD = IDD_CFGOBAK };
	CSeparator	m_Sep3;
	CSeparator	m_Sep2;
	CSeparator	m_Sep1;
	CComboBox	m_cbbConfigurations;
	CString	m_strConfigDescription;
	BOOL	m_tModifyRules;
	BOOL	m_tCreateBItext;
	BOOL	m_tImportVPKT;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(EDBS_CfgImpOBAK)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CEDBS_CfgImpOBAK)
	afx_msg void OnSelchangeConfigurations();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickCreateBItext();
	afx_msg void OnClickImportVPKT();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_EDBS_CFGIMPOBAK_H__058472E3_24BD_11D4_8F2A_004F4E05A09F__INCLUDED_
