// StatDlg.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"
#include "Stat1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatus1Dlg dialog


CStatus1Dlg::CStatus1Dlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CStatus1Dlg::IDD, pParent)
{
	Create( CStatus1Dlg::IDD, pParent );
	//{{AFX_DATA_INIT(CStatus1Dlg)
	m_strText0 = _T("");
	m_strText1 = _T("");
	m_strText2 = _T("");
	//}}AFX_DATA_INIT
}


void CStatus1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatus1Dlg)
	DDX_Text(pDX, IDC_TEXT0, m_strText0);
	DDX_Text(pDX, IDC_TEXT1, m_strText1);
	DDX_Text(pDX, IDC_TEXT2, m_strText2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatus1Dlg, CDialog)
	//{{AFX_MSG_MAP(CStatus1Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatus1Dlg message handlers

BOOL CStatus1Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatus1Dlg::Text( short idx, const char* txt )
{
	CString		text;

	if ( AfxIsValidString( txt ))	text = txt;
	switch ( idx )
	{
	case 0:	m_strText0 = text;	break;
	case 1:	m_strText1 = text;	break;
	case 2:	m_strText2 = text;	break;
	}
	UpdateData( FALSE );
}
