// SuchResDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SuchResDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuchResDlg dialog


CSuchResDlg::CSuchResDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuchResDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuchResDlg)
	m_strGesamt = _T("");
	m_strGesamt2 = _T("");
	//}}AFX_DATA_INIT
	m_iGesamt = 0;
	m_iFehl = 0;
}


void CSuchResDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuchResDlg)
	DDX_Control(pDX, IDC_INFOTEXT, m_txtInfo);
	DDX_Text(pDX, IDC_GESAMT, m_strGesamt);
	DDX_Text(pDX, IDC_GESAMT2, m_strGesamt2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuchResDlg, CDialog)
	//{{AFX_MSG_MAP(CSuchResDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuchResDlg message handlers

BOOL CSuchResDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CxString	text;

	text.AppendF( m_iGesamt, -1 );
	m_strGesamt = text;

	text.Empty();
	text.AppendF( m_iGesamt - m_iFehl, -1 );
	m_strGesamt2 = text;
	
	if ( m_iFehl == 0 )
		m_txtInfo.ShowWindow( SW_HIDE );
	else
		m_txtInfo.ShowWindow( SW_SHOW );

	UpdateData( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
