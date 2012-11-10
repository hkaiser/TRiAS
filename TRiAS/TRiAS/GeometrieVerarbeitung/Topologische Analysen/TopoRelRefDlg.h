// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.01.2003
//
// @doc    Dialog zu PropertyAction für topologische Relationen von GeoObjekten
//         Zusatzbedingungen bei mehreren Bezugsobjekten
// @module TopoRelRefDlg.h | Declaration of the <c CTopoRelRefDlg> class

#if !defined(__TOPORELREFDLG_H_)
#define __TOPORELREFDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TopoRelR.h"       // Hauptsymbole (Ressourcen)

#include "updnedit.h"		// CSpinControl (MEIN Header!!!)


///////////////////////////////////////////////////////////////////////////////////////////////
// Zustand des Dialogs
typedef struct tagMULTIREFRESULT
{
	int iReferenceType;	// gewählte Methode bei mehreren Bezugsobjekten
	int iRefListIndex;	// Index in der ComboBox
	long lLimitCnt;		// Anzahl der Bezugsobjekte für "mindestens", "höchstens" bzw. "exakt"
} MULTIREFRESULT;



///////////////////////////////////////////////////////////////////////////////////////////////
// MultiReferenceDialog CTopoRelRefDlg

class CTopoRelRefDlg : public CPropertyPage
{
// Construction
public:
	CTopoRelRefDlg(ResID uiDlg, LPCSTR pcCaption);
	~CTopoRelRefDlg();

// Dialog Data
	enum { IDD = IDD_SEVERALREFOBJECTS };

// Overrides
public:
	BOOL OnSetActive (NotifyEvt e);
	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }

	BOOL FInit() { return TRUE; }
	
public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetSelectedInfo (MULTIREFRESULT* pSelInfo, bool bNoShow = false);
	HRESULT GetSelectedInfo (MULTIREFRESULT* pSelInfo, bool& bIsDirty);
	static CTopoRelRefDlg* CreateInstance (LPCSTR pcCaption);

// Implementation
protected:

	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

// EventHandler
	void WindowInit (Event);
	BOOL OnKillActive (NotifyEvt);
	int OnWizBack (NotifyEvt);
	int OnWizNext (NotifyEvt);
	BOOL OnWizFinish (NotifyEvt);
	void ButtonClick (ControlEvt e);
	void ListBoxSel (ControlEvt);
	void EditFocusChg (EditFocusChgEvt e);

private:
	DWORD m_dwFlags;

	RadioButton m_RBttnAllRefs, m_RBttnSomeRefs;
	ComboBox m_RefTypeList;
	CSpinControl m_SpinCount;
	FixedText m_Descript;
	
	int m_iReferenceType;	// gewählte Methode bei mehreren Bezugsobjekten
	int m_iRefListIndex;		// Index in der ComboBox
	long m_lLimitCnt;		// Anzahl der Bezugsobjekte für "mindestens", "höchstens" bzw. "exakt"
	
	void GetSelection (void);
	void FillComboBox (void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TOPORELREFDLG_H_)
