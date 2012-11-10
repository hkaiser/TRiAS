// DlgTB.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "DlgTB.h"

#include "SetParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTB dialog


CDlgTB::CDlgTB(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTB::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTB)
	m_bAnrFl = TRUE;
	m_bGesFl = TRUE;
	m_bGlobal = FALSE;
	m_dTiefe = 50.0;
	//}}AFX_DATA_INIT
}


void CDlgTB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTB)
	DDX_Check(pDX, IDC_CHECK1, m_bAnrFl);
	DDX_Check(pDX, IDC_CHECK2, m_bGesFl);
	DDX_Check(pDX, IDC_CHECK3, m_bGlobal);
	DDX_Text(pDX, IDC_EDIT1, m_dTiefe);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTB, CDialog)
	//{{AFX_MSG_MAP(CDlgTB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTB message handlers

BOOL CDlgTB::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTB::OnOK() 
{
	UpdateData( TRUE );

	CSetParam	set;

	set.Open();
	while ( !set.IsEOF())
	{
		set.Delete();
		set.MoveNext();
	}

	if (( m_dTiefe < 10 ) || ( m_dTiefe > 500 ))
	{
		MessageBox( "Ungültiger Wert für Tiefenbegrenzung!\n(Zulässige Werte zwischen 10 und 500 m)",
			"Fehler", MB_ICONHAND|MB_OK );
		return;
	}

	set.AddNew();
	set.m_AnrFl_speichern = m_bAnrFl;
	set.m_GesFl_berechnen = m_bGesFl;
	set.m_Global          = m_bGlobal;
	set.m_Tiefe           = m_dTiefe;
	set.Update();
	set.Close();

	CDialog::OnOK();
}
