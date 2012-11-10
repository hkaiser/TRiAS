// EdPage1.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "EdPage1.h"

#include "ErfassPrivDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditPage1 property page

IMPLEMENT_DYNCREATE(CEditPage1, CPropertyPage)

CEditPage1::CEditPage1() : CPropertyPage(CEditPage1::IDD)
{
	//{{AFX_DATA_INIT(CEditPage1)
	m_strNFP1_ENA = _T("");
	m_strNFP1_IDE = _T("");
	m_strNFP1_EAN = _T("");
	m_strNFP1_EPL = _T("");
	m_strNFP1_EOR = _T("");
	m_strNFP1_ORT = _T("");
	m_strNFP1_FLU = _T("");
	m_strNFP1_FST = _T("");
	m_rNFP1_KAT = 0.0;
	m_rNFP1_GFZ = 0.0;
	m_rNFP1_BMZ = 0.0;
	m_rNFP1_VGZ = 0.0;
	m_rNFP1_GUZ = 0.0;
	m_iNFP1_BAR = -1;
	m_strNFP1_ANDAT = _T("");
	m_strNA_B_PLAN = _T("");
	m_rNFP1_VOLU = 0.0;
	m_bNFP1_TIEF = FALSE;
	m_strNFP1_GEFS = _T("");
	m_strNFP1_AGGS = _T("");
	m_strNFP1_AGG = _T("");
	m_strNFP1_TIEB = _T("");
	m_strEigentumArt = _T("");
	//}}AFX_DATA_INIT
}

CEditPage1::~CEditPage1()
{
}

void AFXAPI DDX_TextDatum(CDataExchange* pDX, int nIDC, COleDateTime& value)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		int nLen = ::GetWindowTextLength(hWndCtrl);
		CString strTemp;

		::GetWindowText(hWndCtrl, strTemp.GetBufferSetLength(nLen), nLen+1 );
		strTemp.ReleaseBuffer();

		if (!value.ParseDateTime(strTemp))  // throws exception
		{
			// Can't convert string to datetime
			AfxMessageBox(AFX_IDP_PARSE_DATETIME);
			pDX->Fail();    // throws exception
		}
	}
	else
	{
		CString strTemp = value.Format( "%d.%m.%Y" );
//		AfxSetWindowText(hWndCtrl, strTemp);
		::SetWindowText( hWndCtrl, strTemp );
	}
}


void CEditPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditPage1)
	DDX_Control(pDX, IDC_EDIT15, m_wndNA_B_PLAN);
	DDX_Control(pDX, IDC_COMBO4, m_cbBAR);
	DDX_Text(pDX, IDC_EDIT1, m_strNFP1_ENA);
	DDX_Text(pDX, IDC_IDE, m_strNFP1_IDE);
	DDX_Text(pDX, IDC_EDIT2, m_strNFP1_EAN);
	DDX_Text(pDX, IDC_EDIT3, m_strNFP1_EPL);
	DDX_Text(pDX, IDC_EDIT4, m_strNFP1_EOR);
	DDX_Text(pDX, IDC_EDIT5, m_strNFP1_ORT);
	DDX_Text(pDX, IDC_EDIT6, m_strNFP1_FLU);
	DDX_Text(pDX, IDC_EDIT7, m_strNFP1_FST);
	DDX_Text(pDX, IDC_EDIT9, m_rNFP1_KAT);
	DDX_Text(pDX, IDC_EDIT10, m_rNFP1_GFZ);
	DDX_Text(pDX, IDC_EDIT11, m_rNFP1_BMZ);
	DDX_Text(pDX, IDC_EDIT12, m_rNFP1_VGZ);
	DDX_Text(pDX, IDC_EDIT13, m_rNFP1_GUZ);
	DDX_CBIndex(pDX, IDC_COMBO4, m_iNFP1_BAR);
	DDX_Text(pDX, IDC_EDIT8, m_strNFP1_ANDAT);
	DDX_Text(pDX, IDC_EDIT15, m_strNA_B_PLAN);
	DDX_Text(pDX, IDC_EDIT14, m_rNFP1_VOLU);
	DDX_Check(pDX, IDC_CHECK1, m_bNFP1_TIEF);
	DDX_Text(pDX, IDC_EDIT16, m_strNFP1_GEFS);
	DDX_Text(pDX, IDC_EDIT17, m_strNFP1_AGGS);
	DDX_Text(pDX, IDC_EDIT18, m_strNFP1_AGG);
	DDX_Text(pDX, IDC_EDIT19, m_strNFP1_TIEB);
	DDX_Text(pDX, IDC_TEXTEIGENTUM, m_strEigentumArt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CEditPage1)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnAendern)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_EN_CHANGE(IDC_EDIT1, OnAendern)
	ON_EN_CHANGE(IDC_EDIT10, OnAendern)
	ON_EN_CHANGE(IDC_EDIT11, OnAendern)
	ON_EN_CHANGE(IDC_EDIT12, OnAendern)
	ON_EN_CHANGE(IDC_EDIT13, OnAendern)
	ON_EN_CHANGE(IDC_EDIT2, OnAendern)
	ON_EN_CHANGE(IDC_EDIT3, OnAendern)
	ON_EN_CHANGE(IDC_EDIT4, OnAendern)
	ON_EN_CHANGE(IDC_EDIT5, OnAendern)
	ON_EN_CHANGE(IDC_EDIT6, OnAendern)
	ON_EN_CHANGE(IDC_EDIT7, OnAendern)
	ON_EN_CHANGE(IDC_EDIT8, OnAendern)
	ON_EN_CHANGE(IDC_EDIT9, OnAendern)
	ON_EN_CHANGE(IDC_EDIT14, OnAendern)
	ON_EN_CHANGE(IDC_EDIT15, OnAendern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditPage1 message handlers

BOOL CEditPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_cbBAR.AddString( "Herstellungsbeitrag" );
	m_cbBAR.AddString( "Erneuerungsbeitrag" );
	m_cbBAR.AddString( "Verbesserungsbeitrag" );
	m_cbBAR.AddString( "Verbesserungsbeitrag II" );
	m_cbBAR.AddString( "Erweiterungsbeitrag" );

	m_strEigentumArt = "Einzeleigentümer";
	if ( "W" == m_strNFP1_NEIG )
		m_strEigentumArt = "Wohnungs- bzw. Teileigentümer";
	if ( "M" == m_strNFP1_NEIG )
		m_strEigentumArt = "Miteigentümer";

	EnableBPlan();
	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditPage1::SetGeaendert( BOOL flag )
{
	((CErfassPrivDlg*)GetParent()) -> SetGeaendert( flag );
}

void CEditPage1::OnAendern() 
{	SetGeaendert( TRUE );
}

void CEditPage1::OnCheck1() 
{
	UpdateData( TRUE );
	OnAendern();
	EnableBPlan();
	UpdateData( FALSE );
}

void CEditPage1::EnableBPlan()
{	m_wndNA_B_PLAN.EnableWindow( m_bNFP1_TIEF );
}
