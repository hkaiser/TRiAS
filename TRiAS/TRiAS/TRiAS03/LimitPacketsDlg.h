// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.08.2002 10:53:59 
//
// @doc
// @module LimitPacketsDlg.h | Declaration of the <c CLimitPacketsDlg> class

#if !defined(_LIMITPACKETSDLG_H__A24BF650_D880_4A26_9BAF_BF9705260AB2__INCLUDED_)
#define _LIMITPACKETSDLG_H__A24BF650_D880_4A26_9BAF_BF9705260AB2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "trias03.h"       // main symbols
#include "updnedit.h"

///////////////////////////////////////////////////////////////////////////////
// Selektierte Daten
enum LIMITPACKETS {
	LIMITPACKETS_None = -1,
	LIMITPACKETS_Lesser = 0,
	LIMITPACKETS_LesserEqual = 1,
	LIMITPACKETS_Equal = 2,
	LIMITPACKETS_MoreEqual = 3,
	LIMITPACKETS_More = 4,
};

typedef struct tagLIMITPACKETSDATA {
	LIMITPACKETS rgLimit;
	ULONG lLimitObjs;
	ULONG lLimitORWnds;
} LIMITPACKETSDATA;

#define MAX_ORWNDS	128		// maximal anzuzeigende ORWnds

/////////////////////////////////////////////////////////////////////////////
// CLimitPacketsDlg dialog

class CLimitPacketsDlg : 
	public CPropertyPage
{
// Construction
public:
	CLimitPacketsDlg(ResID uiResID, LPCSTR pcCaption);
	~CLimitPacketsDlg();

// Dialog Data
	enum { IDD = IDD_CLASSIFYRESULT_WIZ };

// Overrides
public:
	int OnSetActive (NotifyEvt e);
	int OnWizFinish (NotifyEvt e);
	int OnWizNext (NotifyEvt e);
	void WindowInit(Event e);
	void ButtonClick(ControlEvt e);
	void ListBoxSel(ControlEvt e);
	void EditChange(ControlEvt e);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CLimitPacketsDlg *CreateInstance (LPCSTR pcCaption);

	BOOL FInit();

	void GetSelectedData(LIMITPACKETSDATA &rData)
	{ rData = m_selData; }
	void PreSelectData(LIMITPACKETSDATA &rData)
	{ 
		m_selData = rData; 
		m_rgLastLimit = rData.rgLimit; 
		m_lLastLimitObjs = rData.lLimitObjs;
		m_lLastLimitORWnds = rData.lLimitORWnds;
	}

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }

// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	HRESULT PrepareResult();
	void SelectMode(LIMITPACKETS rgLimit = LIMITPACKETS_None);

private:
	DWORD m_dwFlags;
	LIMITPACKETSDATA m_selData;

	LIMITPACKETS m_rgLastLimit;
	ULONG m_lLastLimitObjs;
	ULONG m_lLastLimitORWnds;

	RadioButton m_rbAll;
	RadioButton m_rbLimit;
	ComboBox m_cbRelate;
	CSpinControl m_spinCount;
	FixedText m_ftCount;
	FixedText m_ftDesc;
	CheckBox m_cbLimitORWnds;
	CSpinControl m_spinCountORWnds;

	BOOL m_fSemaphore;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_LIMITPACKETSDLG_H__A24BF650_D880_4A26_9BAF_BF9705260AB2__INCLUDED_)
