// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.11.2000 12:48:46 
//
// @doc
// @module MacroIntroDlg.cpp | Definition of the <c CMacroIntroDlg> class


#include "bscriptp.hxx"

#include <registrx.hxx>

#include "bscript.h"
#include "conststr.h"
#include "MacroIntroDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMacroIntroDlg dialog

CMacroIntroDlg::CMacroIntroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMacroIntroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMacroIntroDlg)
	m_fDoNotShowAnyFurther = TRUE;
	//}}AFX_DATA_INIT
}

void CMacroIntroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMacroIntroDlg)
	DDX_Check(pDX, IDC_DONOTSHOWANYFURTHER, m_fDoNotShowAnyFurther);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMacroIntroDlg, CDialog)
	//{{AFX_MSG_MAP(CMacroIntroDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMacroIntroDlg message handlers

void CMacroIntroDlg::OnOK() 
{
	UpdateData(TRUE);
	if (!m_fDoNotShowAnyFurther) {
	CCurrentUser regCfg (g_cbCfgKey, true);

		regCfg.SetDWORD(g_cbIntro, 0);
	}
	CDialog::OnOK();
}

BOOL CMacroIntroDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();		// immer schön in der Mitte anzeigen ...
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
