// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.01.2001 22:37:42 
//
// @doc
// @module MessageBoxEx.cpp | Definition of the <c CMessageBoxEx> class

#include "stdafx.h"
#include "triasdb.h"
#include "MessageBoxEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageBoxEx dialog

CMessageBoxEx::CMessageBoxEx(LPCSTR pcPrompt, LPCSTR pcCaption, bool fHasCancel, CWnd* pParent /*=NULL*/)
	: CDialog(fHasCancel ? CMessageBoxEx::IDDCANCEL : CMessageBoxEx::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessageBoxEx)
	//}}AFX_DATA_INIT
	m_strCaption = pcCaption;
	m_strPrompt = pcPrompt;
}

void CMessageBoxEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageBoxEx)
	DDX_Control(pDX, IDC_PROMPT_STATIC, m_PromptStatic);
	DDX_Control(pDX, IDC_PROMPT, m_Prompt);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMessageBoxEx, CDialog)
	//{{AFX_MSG_MAP(CMessageBoxEx)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDC_YESALL, OnYesall)
	ON_BN_CLICKED(IDNO, OnNo)
	ON_BN_CLICKED(IDC_NOALL, OnNoall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageBoxEx message handlers

void CMessageBoxEx::OnYes() 
{
	EndDialog(IDYES);
}

void CMessageBoxEx::OnYesall() 
{
	EndDialog(IDC_YESALL);
}

void CMessageBoxEx::OnNo() 
{
	EndDialog(IDNO);
}

void CMessageBoxEx::OnNoall() 
{
	EndDialog(IDC_NOALL);
}

BOOL CMessageBoxEx::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText (m_strCaption);

// Größe des gesamten Dialoges an Text anpassen
	m_Prompt.SetWindowText (m_strPrompt);
	m_PromptStatic.SetWindowText(m_strPrompt);
	
int iLines = m_Prompt.GetLineCount();

	if (iLines > 3) {
	// Editcontrol behandeln
	CDC *pDC = m_PromptStatic.GetDC();
	TEXTMETRIC tm;

		pDC->GetTextMetrics(&tm);

	int iHeight = iLines * tm.tmHeight;
	CRect rcOld;

		m_PromptStatic.GetWindowRect(&rcOld);
		m_PromptStatic.SetWindowPos(NULL, 0, 0, rcOld.Width(), iHeight, SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);

	// Buttons verschieben
	int iDelta = iHeight - rcOld.Height();

		MoveButton(IDYES, iDelta);
		MoveButton(IDC_YESALL, iDelta);
		MoveButton(IDNO, iDelta);
		MoveButton(IDC_NOALL, iDelta);
		MoveButton(IDCANCEL, iDelta);

	// Fenster selbst behandeln
		GetWindowRect(&rcOld);
		rcOld.bottom += iDelta;
		SetWindowPos (NULL, 0, 0, rcOld.Width(), rcOld.Height(), SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CMessageBoxEx::MoveButton (UINT uiId, int iDelta)
{
CButton *pButton = (CButton *)GetDlgItem(uiId);

	if (NULL == pButton) {
		_ASSERTE(IDCANCEL == uiId);
		return false;
	}

CRect rcBttn;

	pButton -> GetWindowRect(&rcBttn);
	rcBttn.top += iDelta;
	rcBttn.bottom += iDelta;
	ScreenToClient(&rcBttn);
	
	pButton -> SetWindowPos (NULL, rcBttn.left, rcBttn.top, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
	return true;
}
