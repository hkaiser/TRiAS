// EdPage4.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "EdPage4.h"
#include "ErfassPrivDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditPage4 property page

IMPLEMENT_DYNCREATE(CEditPage4, CPropertyPage)

CEditPage4::CEditPage4() : CPropertyPage(CEditPage4::IDD)
{
	//{{AFX_DATA_INIT(CEditPage4)
	m_bZE = FALSE;
	m_bSGR = FALSE;
	m_bSGT = FALSE;
	m_bKK = FALSE;
	m_bVF = FALSE;
	m_bK = FALSE;
	m_bKKT = FALSE;
	m_rAWE = 0.0;
	m_rAEW = 0.0;
	m_rEGW = 0.0;
	m_strSonst = _T("");
	m_rFS = 0.0;
	m_rFKK = 0.0;
	m_bANNWL = FALSE;
	//}}AFX_DATA_INIT
}

CEditPage4::~CEditPage4()
{
}

void CEditPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditPage4)
	DDX_Control(pDX, IDC_CHECK1, m_ckZentrEnts);
	DDX_Control(pDX, IDC_CHECK2, m_ckDezEnts);
	DDX_Check(pDX, IDC_CHECK1, m_bZE);
	DDX_Check(pDX, IDC_CHECK3, m_bSGR);
	DDX_Check(pDX, IDC_CHECK4, m_bSGT);
	DDX_Check(pDX, IDC_CHECK5, m_bKK);
	DDX_Check(pDX, IDC_CHECK6, m_bVF);
	DDX_Check(pDX, IDC_CHECK7, m_bK);
	DDX_Check(pDX, IDC_CHECK8, m_bKKT);
	DDX_Text(pDX, IDC_EDIT1, m_rAWE);
	DDX_Text(pDX, IDC_EDIT14, m_rAEW);
	DDX_Text(pDX, IDC_EDIT15, m_rEGW);
	DDX_Text(pDX, IDC_EDIT2, m_strSonst);
	DDX_Text(pDX, IDC_EDIT6, m_rFS);
	DDX_Text(pDX, IDC_EDIT7, m_rFKK);
	DDX_Check(pDX, IDC_CHECK9, m_bANNWL);
	//}}AFX_DATA_MAP

	if ( pDX -> m_bSaveAndValidate )
	{
		m_bFE = m_bFZ = m_bFZE = FALSE;
		switch ( GetCheckedRadioButton( IDC_RADIO1, IDC_RADIO5 ))
		{
		case IDC_RADIO1:	m_bFZ = TRUE;	break;
		case IDC_RADIO4:	m_bFE = TRUE;	break;
		case IDC_RADIO5:	m_bFZE = TRUE;	break;
		default:			m_bFZ = TRUE;	break;
		}
	}
	else
	{
		if ( m_bFZE )		CheckRadioButton( IDC_RADIO1, IDC_RADIO5, IDC_RADIO5 );
		else if ( m_bFE )	CheckRadioButton( IDC_RADIO1, IDC_RADIO5, IDC_RADIO4 );
		else				CheckRadioButton( IDC_RADIO1, IDC_RADIO5, IDC_RADIO1 );
	}
	EnableDezEntsorg( !m_bZE );
}


BEGIN_MESSAGE_MAP(CEditPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CEditPage4)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT14, OnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, OnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditPage4 message handlers

void CEditPage4::OnCheck1() 
{
	SetGeaendert();
	UpdateData( TRUE );
//	m_ckDezEnts.SetCheck( !m_bZE );
	EnableDezEntsorg( !m_bZE );
}

void CEditPage4::OnCheck2() 
{
	SetGeaendert();
	UpdateData( TRUE );
//	m_bZE = !m_ckDezEnts.GetCheck();
	m_bZE = !m_bZE;
	UpdateData( FALSE );
	EnableDezEntsorg( !m_bZE );
}

void CEditPage4::OnCheck3() 
{	SetGeaendert();
//	EnableDezEntsorg( TRUE );
}

void CEditPage4::OnCheck4() 
{	SetGeaendert();	}

void CEditPage4::OnCheck5() 
{	SetGeaendert();
//	EnableDezEntsorg( TRUE );
}

void CEditPage4::OnCheck6() 
{	SetGeaendert();	}

void CEditPage4::OnCheck7() 
{	SetGeaendert();	}

void CEditPage4::OnCheck8() 
{	SetGeaendert();	}

void CEditPage4::OnCheck9() 
{	SetGeaendert();	}

void CEditPage4::OnChangeEdit1() 
{	SetGeaendert();	}

void CEditPage4::OnChangeEdit14() 
{	SetGeaendert();	}

void CEditPage4::OnChangeEdit15() 
{	SetGeaendert();	}

void CEditPage4::OnChangeEdit2() 
{	SetGeaendert();	}

void CEditPage4::OnChangeEdit6() 
{	SetGeaendert();	}

void CEditPage4::OnChangeEdit7() 
{	SetGeaendert();	}

void CEditPage4::OnRadio1() 
{	SetGeaendert();	}

void CEditPage4::OnRadio4() 
{	SetGeaendert();	}

void CEditPage4::OnRadio5() 
{	SetGeaendert();	}

void CEditPage4::SetGeaendert( BOOL f )
{
	UpdateData( TRUE );
	((CErfassPrivDlg*)GetParent()) -> SetGeaendert( f );
}	// SetGeaendert

void CEditPage4::EnableDezEntsorg( BOOL flag )
{
	EnableDlgWindow( IDC_CHECK3, flag );
	EnableDlgWindow( IDC_CHECK5, flag );
	EnableDlgWindow( IDC_CHECK6, flag );
	EnableDlgWindow( IDC_CHECK7, flag );
	EnableSG( m_bSGR && flag );
	EnableKK( m_bKK && flag );
	m_ckDezEnts.SetCheck( flag );
}

void CEditPage4::EnableDlgWindow( UINT id, BOOL flag )
{
	CWnd	*pWnd = GetDlgItem( id );
	if ( pWnd )		pWnd -> EnableWindow( flag );
}

void CEditPage4::EnableSG( BOOL flag )
{
	EnableDlgWindow( IDC_CHECK4, flag );
	EnableDlgWindow( IDC_EDIT6, flag );
}

void CEditPage4::EnableKK( BOOL flag )
{
	EnableDlgWindow( IDC_CHECK8, flag );
	EnableDlgWindow( IDC_EDIT7, flag );
}
