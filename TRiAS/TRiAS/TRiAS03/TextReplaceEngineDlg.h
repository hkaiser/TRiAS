// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.09.2000 18:04:49
//
// @doc
// @module TextReplaceEngineDlg.h | Declaration of the <c CTextReplaceEngineDlg> class

#if !defined(__TEXTREPLACEENGINEDLG_H_)
#define __TEXTREPLACEENGINEDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiAS03.h"       // main symbols

#include "MatchLastComboBox.h"
#include "SelectObjectProperty.h"

/////////////////////////////////////////////////////////////////////////////
// CTextReplaceEngineDlg dialog

class CTextReplaceEngine;

class CTextReplaceEngineDlg : 
	public CPropertyPage
{
public:
	typedef list<os_string> CSearchList;
	typedef map<os_string, HMENU, less<os_string> > CParentMenuItems;
	
// Construction
public:
	CTextReplaceEngineDlg(CTextReplaceEngine *pParent, ResID resID, LPCSTR pcCaption);
	~CTextReplaceEngineDlg();

// Dialog Data
	enum { IDD = IDD_TEXTREPLACE_WIZ };

	BOOL FInit (void) { return TRUE; }

// Overrides
public:
	void WindowInit (Event);
	void ButtonClick (ControlEvt e);
	LRESULT Dispatch (Event e);
	void EditChange (ControlEvt);
	void ListBoxSel (ControlEvt);

	void MenuInit(MenuInitEvt e);
	void MenuSelect(MenuSelectEvt e);
	void MenuCommand (MenuCommandEvt e);

	int OnSetActive (NotifyEvt);
	void OnCancel (NotifyEvt);
	int OnWizNext (NotifyEvt);
	BOOL OnWizFinish (NotifyEvt);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CTextReplaceEngineDlg *CreateInstance (CTextReplaceEngine *pParent, ResID resID, LPCSTR pcCaption);

	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

// Statusvariablen für Persistenz
	class CDlgStatus {
	public:
		BOOL m_fCapital;
		BOOL m_fPartialMatch;
		BOOL m_fUseRegExpr;
		BOOL m_fTestBOB;

		os_string m_strObjPropSrc;
		os_string m_strObjPropDest;
		os_string m_strFindWhat;
		CSearchList m_lstFindWhat;
		os_string m_strReplaceWith;
		CSearchList m_lstReplaceWith;

		void erase (void) 
		{ 
			m_strObjPropSrc = "";
			m_strObjPropDest = "";
			m_strFindWhat.erase();
			m_strReplaceWith.erase();
			m_lstFindWhat.erase(m_lstFindWhat.begin(), m_lstFindWhat.end()); 
			m_lstReplaceWith.erase(m_lstReplaceWith.begin(), m_lstReplaceWith.end()); 
		}

		CDlgStatus (void) 
		{
			m_fCapital = m_fPartialMatch = false;
			m_fUseRegExpr = m_fTestBOB = false;
		}
	};
	HRESULT InitWithData (CTextReplaceEngineDlg::CDlgStatus &rStatus);

// Implementation
protected:
	BOOL AdjustSheetButtons();
	BOOL GetDisableNextPage();
	void DoUpdate (void);

// MenuCommands
	BOOL OnSrcExprCommand (LPCSTR pcInsert, int iMove = 0);
	BOOL OnDestExprCommand (LPCSTR pcInsert);
	BOOL OnDestExprCommand (UINT uiID, LPCSTR pcInsert);
	os_string GetObjectProperty (UINT uiID);

	BOOL ShowSrcExprMenu();
	BOOL ShowDestExprMenu();

	BOOL FillMenuWithObjProps (HMENU hObjPropMenu);
	HMENU CalcParentMenu (os_string strGroup, CParentMenuItems &rItems);
	HMENU CalcSubGroupMenu (HMENU hParentMenu, os_string strSubGroup);

	int GetGroupCount();

private:
	DWORD m_dwFlags;
	bool m_fIsInitialized;
	bool m_fDestSelected;			// ZielObjekteigenschaft wurde explizit ausgewählt

// Controls
	CSelectObjectProperty m_ObjPropSrc;
	CSelectObjectProperty m_ObjPropDest;
	
	CMatchLastComboBox m_cbFindWhat;		// Suchen nach
	CMatchLastComboBox m_cbReplaceWith;		// Ersetzen durch

	CheckBox m_cbCapital;					// Suchoptionen
	CheckBox m_cbPartialMatch;
	CheckBox m_cbUseRegExpr;
	CheckBox m_cbTestBOB;

	HMENU m_hMenu;

	CTextReplaceEngine *m_pParent;			// Rückverweis

// Persistente Daten (Eingabeergebnisse)
	CDlgStatus *m_pStatus;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TEXTREPLACEENGINEDLG_H_)
