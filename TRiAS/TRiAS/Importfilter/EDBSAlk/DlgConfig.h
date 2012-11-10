#if !defined(AFX_DLGCONFIG_H__986AAAE6_973E_11D3_8E4D_00105AF354F9__INCLUDED_)
#define AFX_DLGCONFIG_H__986AAAE6_973E_11D3_8E4D_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConfig.h : Header-Datei
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCfgCommon 

class CDlgCfgCommon : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCfgCommon)

// Konstruktion
public:
	void SetWizardButtons( void );
	void SaveConfig( void );
	void LoadConfig( void );
	CDlgCfgCommon();
	~CDlgCfgCommon();

// Dialogfelddaten
	//{{AFX_DATA(CDlgCfgCommon)
	enum { IDD = IDD_CFGCOMMON };
	CComboBox	m_cbbConfigurations;
	CString	m_strConfigDescription;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgCfgCommon)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgCfgCommon)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeConfigurations();
	afx_msg void OnSelchangeConfigurations();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCfgDefault 

class CDlgCfgDefault : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCfgDefault)

// Konstruktion
public:
	void SetWizardButtons( void );
	void SaveConfig( void );
	void LoadConfig( void );
	CDlgCfgDefault();
	~CDlgCfgDefault();

// Dialogfelddaten
	//{{AFX_DATA(CDlgCfgDefault)
	enum { IDD = IDD_CFGDEFAULT };
	BOOL	m_tCreateBItext;
	BOOL	m_tCreateBIgeom;
		// HINWEIS - Der Klassen-Assistent fügt hier Datenelemente ein.
		//    Innerhalb dieser generierten Quellcodeabschnitte NICHTS BEARBEITEN!
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgCfgDefault)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgCfgDefault)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickCreateBIgeom();
	afx_msg void OnClickCreateBItext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCfgExtra 

class CDlgCfgExtra : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCfgExtra)

// Konstruktion
public:
	void SetWizardButtons( void );
	void LoadConfig( void );
	void SaveConfig( void );
	CDlgCfgExtra();
	~CDlgCfgExtra();

// Dialogfelddaten
	//{{AFX_DATA(CDlgCfgExtra)
	enum { IDD = IDD_CFGEXTRA };
	BOOL	m_tImportAreas;
	BOOL	m_tImportLines;
	BOOL	m_tImportPoints;
	BOOL	m_tImportText;
	BOOL	m_tOverwriteRules;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgCfgExtra)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgCfgExtra)
	afx_msg void OnClickDefaultobjectmapping();
	afx_msg void OnClickImportAreas();
	afx_msg void OnClickImportLines();
	afx_msg void OnClickImportPoints();
	afx_msg void OnClickImportText();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGCONFIG_H__986AAAE6_973E_11D3_8E4D_00105AF354F9__INCLUDED_
