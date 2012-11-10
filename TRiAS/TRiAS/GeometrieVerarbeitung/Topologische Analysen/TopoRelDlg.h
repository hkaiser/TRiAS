// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 20.12.2002 11:31:12
//
// @doc    Dialog zu PropertyAction für topologische Relationen von GeoObjekten
//         Auswahl der gewünschten Relationen
// @module TopoRelDlg.h | Declaration of the <c CTopoRelDlg> class

#if !defined(__TOPORELDLG_H_)
#define __TOPORELDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TopoRelR.h"       // Hauptsymbole (Ressourcen)



///////////////////////////////////////////////////////////////////////////////////////////////
// Zustand des Dialogs
typedef struct tagTOPORELRESULT
{
	ulong ulSelRelat;	// Bitmuster für ausgewählte Relationen
	bool bSepaWin;		// Analyseergebnisse in separate bzw. ein gemeinsames Fenster ausgeben
} TOPORELRESULT;


///////////////////////////////////////////////////////////////////////////////////////////////
// RelationenDialog CTopoRelDlg

class CTopoRelDlg : public CPropertyPage
{
// Construction
public:
	CTopoRelDlg(ResID uiDlg, LPCSTR pcCaption);
	~CTopoRelDlg();

// Dialog Data
	enum { IDD = IDD_TOPORELOPTIONS };

// Overrides
public:
	BOOL OnSetActive (NotifyEvt e);
	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }

	BOOL FInit() { return TRUE; }
	
public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetSelectedInfo (TOPORELRESULT* pSelInfo, bool bNoShow = false);
	HRESULT GetSelectedInfo (TOPORELRESULT* pSelInfo, bool& bIsDirty);
	static CTopoRelDlg* CreateInstance (LPCSTR pcCaption);

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

private:
	DWORD m_dwFlags;

	CheckBox m_CBoxIntersect, m_CBoxWithin, m_CBoxContain, m_CBoxOverlap;
	CheckBox m_CBoxEnter, m_CBoxTouch, m_CBoxEqual, m_CBoxDisjoint;
	CheckBox m_CBoxRechWindows;
	FixedText m_Descript;
	
	ulong m_ulSelRelat;	// Bitmuster für ausgewählte Relationen
						// Standard: innerhalb , d. h. m_ulSelRelat == WITH
	bool m_bSepaWin;	// die Analyseergebnisse für "innerhalb", "außerhalb" usw. in separaten (true)
						// bzw. in einem gemeinsamen Recherchefenster (false)
	
	void SetComment (ControlEvt e);
	void GetSelection (void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__TOPORELDLG_H_)
