// DlgVisu.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "DlgVisu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVisu dialog


CDlgVisu::CDlgVisu(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVisu::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVisu)
	m_strArtVisu = _T("");
	//}}AFX_DATA_INIT
}


void CDlgVisu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVisu)
	DDX_Control(pDX, IDC_COMBO1, m_cbArtVisu);
	DDX_Control(pDX, IDC_BUTTON1, m_btnVisuParam);
	DDX_CBString(pDX, IDC_COMBO1, m_strArtVisu);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVisu, CDialog)
	//{{AFX_MSG_MAP(CDlgVisu)
	ON_BN_CLICKED(IDC_BUTTON1, OnVisuParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVisu message handlers

BOOL CDlgVisu::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_cbArtVisu.AddString( "Stand Bescheidschreibung" );
	m_cbArtVisu.AddString( "Angeschlossene Dachteilflächen" );
	m_cbArtVisu.AddString( "Angeschlossene versiegelte Flächen" );
	m_cbArtVisu.AddString( "Beitragsart" );
	m_cbArtVisu.AddString( "Angeschlossene Grundstücke" );
	m_cbArtVisu.AddString( "Eigentumsverhältnisse" );
	m_cbArtVisu.SetCurSel( 0 );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVisu::OnVisuParam() 
{
}

void CDlgVisu::OnOK() 
{
	UpdateData( TRUE );

	m_iArtVisu = 0;
	if ( m_strArtVisu == "Stand Bescheidschreibung" )			m_iArtVisu = 1;
	if ( m_strArtVisu == "Angeschlossene Dachteilflächen" )		m_iArtVisu = 2;
	if ( m_strArtVisu == "Beitragsart" )						m_iArtVisu = 3;
	if ( m_strArtVisu == "Angeschlossene Grundstücke" )			m_iArtVisu = 4;
	if ( m_strArtVisu == "Eigentumsverhältnisse" )				m_iArtVisu = 5;
	if ( m_strArtVisu == "Angeschlossene versiegelte Flächen" )	m_iArtVisu = 6;

	CDialog::OnOK();
}
