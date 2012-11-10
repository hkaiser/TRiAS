// SPage1.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int g_iMessageStatus;

/////////////////////////////////////////////////////////////////////////////
// CStartPage1 property page

IMPLEMENT_DYNCREATE(CStartPage1, CPropertyPage)

CStartPage1::CStartPage1() : CPropertyPage(CStartPage1::IDD)
{
	//{{AFX_DATA_INIT(CStartPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iSelect = 0;
	m_iMRU = 0;
}

CStartPage1::~CStartPage1()
{
}

void CStartPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartPage1)
	DDX_Control(pDX, IDC_COMBO1, m_cbMRU);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CStartPage1)
	ON_BN_CLICKED(IDC_OPEN, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeMRU)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartPage1 message handlers

void CStartPage1::OnRadio1() 
{
	((CPropertySheet*)GetParent()) -> SetWizardButtons( PSWIZB_NEXT );
	m_iSelect = 0;
}

void CStartPage1::OnRadio2() 
{
	((CPropertySheet*)GetParent()) -> SetWizardButtons( PSWIZB_FINISH );
	m_iSelect = 1;
}

void CStartPage1::OnRadio3() 
{
	((CPropertySheet*)GetParent()) -> SetWizardButtons( PSWIZB_FINISH );
	m_iSelect = 2;
}

BOOL CStartPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	CString		text, eintrag, message;

	CWnd*	pWnd = GetDlgItem( IDC_RADIO3 );
	if ( NULL != pWnd )
	{
		eintrag.LoadString( IDS_TROPENFILE );
		text = g_cbTRiAS;
		text += eintrag;
		pWnd -> SetWindowText( text );
	}

	if ( g_iMessageStatus >= 3 )
	{
		message = "Lesen MRU 1";
		DEX_SetMessageString((const char*)message );
	}

	m_strarrMRU.RemoveAll();

	text = AfxGetApp() -> GetProfileString( _T("OpenMRU"),
											_T("File1"),
											_T(""));
	if ( text.GetLength() > 0 )
	{
		m_strarrMRU.Add( text );
		text = text.Left( text.GetLength() - 2 );
		if ( text.GetLength() < 30 )
			eintrag = text;
		else
		{
			eintrag = text.Left( 3 );
			eintrag += "..";
			eintrag += text.Right( 25 );
		}
		m_cbMRU.AddString( eintrag );
	}

	if ( g_iMessageStatus >= 3 )
	{
		message = "Lesen MRU 2";
		DEX_SetMessageString((const char*)message );
	}

	if ( text.GetLength() > 0 )
	{
		text = AfxGetApp() -> GetProfileString( _T("OpenMRU"),
												_T("File2"),
												_T(""));
		if ( text.GetLength() > 0 )
		{
			m_strarrMRU.Add( text );
			text = text.Left( text.GetLength() - 2 );
			if ( text.GetLength() < 30 )
				eintrag = text;
			else
			{
				eintrag = text.Left( 3 );
				eintrag += "..";
				eintrag += text.Right( 25 );
			}
			m_cbMRU.AddString( eintrag );
		}
	}

	if ( g_iMessageStatus >= 3 )
	{
		message = "Lesen MRU 3";
		DEX_SetMessageString((const char*)message );
	}

	if ( text.GetLength() > 0 )
	{
		text = AfxGetApp() -> GetProfileString( _T("OpenMRU"),
												_T("File3"),
												_T(""));
		if ( text.GetLength() > 0 )
		{
			m_strarrMRU.Add( text );
			text = text.Left( text.GetLength() - 2 );
			if ( text.GetLength() < 30 )
				eintrag = text;
			else
			{
				eintrag = text.Left( 3 );
				eintrag += "..";
				eintrag += text.Right( 25 );
			}
			m_cbMRU.AddString( eintrag );
		}
	}

	if ( g_iMessageStatus >= 3 )
	{
		message = "Lesen MRU 4";
		DEX_SetMessageString((const char*)message );
	}

	if ( text.GetLength() > 0 )
	{
		text = AfxGetApp() -> GetProfileString( _T("OpenMRU"),
												_T("File4"),
												_T(""));
		if ( text.GetLength() > 0 )
		{
			m_strarrMRU.Add( text );
			text = text.Left( text.GetLength() - 2 );
			if ( text.GetLength() < 30 )
				eintrag = text;
			else
			{
				eintrag = text.Left( 3 );
				eintrag += "..";
				eintrag += text.Right( 25 );
			}
			m_cbMRU.AddString( eintrag );
		}
	}

	if ( m_cbMRU.GetCount() > 0 )	m_cbMRU.SetCurSel( 0 );
	else
	{
		CWnd	*pW = GetDlgItem( IDC_RADIO2 );
		if ( pW != NULL )	pW -> EnableWindow( FALSE );
		m_cbMRU.EnableWindow( FALSE );
	}

	switch ( m_iSelect )
	{
	case 0:
		CheckRadioButton( IDC_OPEN, IDC_RADIO3, IDC_OPEN );
		break;
	case 1:
		if ( m_cbMRU.GetCount() > 0 )
			CheckRadioButton( IDC_OPEN, IDC_RADIO3, IDC_RADIO2 );
		else
			CheckRadioButton( IDC_OPEN, IDC_RADIO3, IDC_OPEN );
		break;
	case 2:
		CheckRadioButton( IDC_OPEN, IDC_RADIO3, IDC_RADIO3 );
		break;
	}

	message.LoadString( IDS_BEREIT );
	DEX_SetMessageString((const char*)message );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CStartPage1::OnSetActive() 
{
	BOOL	result = CPropertyPage::OnSetActive();

	((CPropertySheet*)GetParent()) -> SetWizardButtons( PSWIZB_NEXT );
	return result;
}

void CStartPage1::OnOK() 
{
	CPropertyPage::OnOK();
}

void CStartPage1::OnSelchangeMRU() 
{
	if (( m_iMRU = m_cbMRU.GetCurSel()) != CB_ERR )
	{
		CheckRadioButton( IDC_OPEN, IDC_RADIO3, IDC_RADIO2 );
		OnRadio2();
	}
}
