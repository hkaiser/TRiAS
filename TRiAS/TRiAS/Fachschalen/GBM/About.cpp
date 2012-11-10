// About.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "About.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSetNF_PG1* g_pNF_PG1;
extern CSetNF_PG2H* g_pNF_PG2H;
extern CSetNF_PG2D* g_pNF_PG2D;
extern CSetNF_PG1GB* g_pNF_PG1GB;

/////////////////////////////////////////////////////////////////////////////
// CAbout dialog

CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbout)
	m_bManagerFlag = FALSE;
	m_strExtName = _T("");
	m_strZahlDT = _T("");
	m_strZahlGem = _T("");
	m_strZahlGS = _T("");
	m_strZahlStr = _T("");
	m_strZahlVF = _T("");
	//}}AFX_DATA_INIT
}


void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbout)
	DDX_Check(pDX, IDC_MANAGER, m_bManagerFlag);
	DDX_Text(pDX, IDC_TEXT0, m_strExtName);
	DDX_Text(pDX, IDC_ZAHLDT, m_strZahlDT);
	DDX_Text(pDX, IDC_ZAHLGEM, m_strZahlGem);
	DDX_Text(pDX, IDC_ZAHLGS, m_strZahlGS);
	DDX_Text(pDX, IDC_ZAHLSTR, m_strZahlStr);
	DDX_Text(pDX, IDC_ZAHLVF, m_strZahlVF);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAbout, CDialog)
	//{{AFX_MSG_MAP(CAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbout message handlers

BOOL CAbout::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CxString	text;
	CString		eintrag;
	CWnd*		pWnd = GetDlgItem( IDC_TEXT0 );

	if ( NULL != pWnd )
	{
		eintrag.LoadString( IDS_EXTNAME );
		text = g_cbTRiAS;
		text += eintrag;
		pWnd -> SetWindowText( text );
	}
	if ( NULL != g_pNF_PG2D )
	{
		text.Empty();
		text.AppendFormated( g_pNF_PG2D -> GetCount(), -1 );
	}
	else
		text = "--";
	m_strZahlDT  = text;
	if ( NULL != g_pNF_PG1GB )
	{
		text.Empty();
		text.AppendFormated( g_pNF_PG1GB -> GetCount(), -1 );
	}
	else
		text = "--";
	m_strZahlGem = text;
	if ( NULL != g_pNF_PG1 )
	{
		text.Empty();
		text.AppendFormated( g_pNF_PG1 -> GetCount(), -1 );
	}
	else
		text = "--";
	m_strZahlGS  = text;
	if ( NULL != g_pNF_PG2D )
	{
		text.Empty();
//		text.AppendFormated( g_pNF_PG2D -> GetCount(), -1 );
	}
	else
		text = "--";
	m_strZahlStr = text;
	if ( NULL != g_pNF_PG2H )
	{
		text.Empty();
		text.AppendFormated( g_pNF_PG2H -> GetCount(), -1 );
	}
	else
		text = "--";
	m_strZahlVF  = text;

	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
