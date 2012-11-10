#if !defined(AFX_EDBS_CFGIMPCMN_H__73645438_AED5_11D3_8E7B_00105AF354F9__INCLUDED_)
#define AFX_EDBS_CFGIMPCMN_H__73645438_AED5_11D3_8E7B_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EDBS_CfgImpCmn.h : Header-Datei
//

#if defined(_USE_CONFIG_DIALOGS)

#include <afxdlgs.h>
#include "Cfg.h"
#include "CfgDb.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld EDBS_CfgImpCmn 

class CEDBS_CfgImpCmn : public CPropertyPage
{
	DECLARE_DYNCREATE(CEDBS_CfgImpCmn)

// Konstruktion
public:
	void SetWizardButtons( void );
	CEDBS_CfgImpCmn();
	~CEDBS_CfgImpCmn();

	CCfg*	m_pConfiguration;
	void LoadConfig( void );
	void SaveConfig( void );

// Dialogfelddaten
	//{{AFX_DATA(CEDBS_CfgImpCmn)
	enum { IDD = IDD_CFGCOMMON };
	BOOL	m_tDefault;
	BOOL	m_tCreateBIgeom;
	BOOL	m_tCreateBItext;
	BOOL	m_tCreateBIattr;
	BOOL	m_tImportKSIG;
	BOOL	m_tImportVPKT;
	BOOL	m_tCreateAttrAktualitaet;
	BOOL	m_tCreateAttrDateiname;
	BOOL	m_tCreateAttrFolie;
	BOOL	m_tCreateAttrObjektart;
	BOOL	m_tCreateAttrObjektnummer;
	BOOL	m_tCreateAttrObjektteilnummer;
	BOOL	m_tCreateAttrObjektteilnummerK;
	BOOL	m_tCreateAttrRegeln;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CEDBS_CfgImpCmn)
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
	//{{AFX_MSG(CEDBS_CfgImpCmn)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickDefault();
	afx_msg void OnClickImportKSIG();
	afx_msg void OnClickImportVPKT();
	afx_msg void OnClickCreateBItext();
	afx_msg void OnClickCreateBIgeom();
	afx_msg void OnClickCreateBIattr();
	afx_msg void OnClickCrtAtrAktualitaet();
	afx_msg void OnClickCrtAtrDateiname();
	afx_msg void OnClickCrtAtrFolie();
	afx_msg void OnClickCrtAtrObjektart();
	afx_msg void OnClickCrtAtrObjektnummer();
	afx_msg void OnClickCrtAtrObjektteilnummer();
	afx_msg void OnClickCrtAtrObjektteilnummerK();
	afx_msg void OnClickCrtAtrRegeln();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // defined(_USE_CONFIG_DIALOGS)

#endif // AFX_EDBS_CFGIMPCMN_H__73645438_AED5_11D3_8E7B_00105AF354F9__INCLUDED_

