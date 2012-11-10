#if !defined(AFX_EDBS_CFGIMPOBJ_H__EC7070C4_1A77_11D4_8F08_004F4E05A09F__INCLUDED_)
#define AFX_EDBS_CFGIMPOBJ_H__EC7070C4_1A77_11D4_8F08_004F4E05A09F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EDBS_CfgImpObj.h : Header-Datei
//


// Stingray
//#include "config/Default.h"
//#include "secall.h"
//#include <afxcmn.h>		//CTreeCtrl
#include <afxcmn.h>		// CImageList
#include "ListCtrlObjects.h"

#include "resource.h"
#include "separator.h"
#include "Cfg.h"
#include "CfgDb.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld EDBS_CfgImpObj 

class CEDBS_CfgImpObj : public CPropertyPage
{
	DECLARE_DYNCREATE(CEDBS_CfgImpObj)

// Konstruktion
public:
	void SaveConfig( void );
	void LoadConfig(void );
	void SetWizardButtons( void );
	void InitImageList( void );
	void SetItemOverlayImage( HTREEITEM hti, int iImage );
	CEDBS_CfgImpObj();
	~CEDBS_CfgImpObj();

	CCfg*	m_pConfiguration;
	CImageList		m_cIList;
	CImageList		m_cIListState;
	bool			m_tBtnSelect;
	int           m_idiFolderClosed,
		          m_idiFolderOpen,
				  m_idiText,
				  m_idiOverlay;


// Dialogfelddaten
	//{{AFX_DATA(CEDBS_CfgImpObj)
	enum { IDD = IDD_CFGOBJECTS };
	CSeparator			m_Sep1;
	CButton				m_btnSelect;
	CListCtrlObjects	m_lvObjects;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CEDBS_CfgImpObj)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CEDBS_CfgImpObj)
	virtual BOOL OnInitDialog();
	afx_msg void OnClicklvObjects(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickBtnSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_EDBS_CFGIMPOBJ_H__EC7070C4_1A77_11D4_8F08_004F4E05A09F__INCLUDED_
