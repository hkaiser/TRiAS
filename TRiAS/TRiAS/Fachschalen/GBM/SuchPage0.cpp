// SuchPage0.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SuchPage0.h"
#include "MyPropS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuchPage0 property page

IMPLEMENT_DYNCREATE(CSuchPage0, CPropertyPage)

CSuchPage0::CSuchPage0() : CPropertyPage(CSuchPage0::IDD)
{
	//{{AFX_DATA_INIT(CSuchPage0)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInit = FALSE;
}

CSuchPage0::~CSuchPage0()
{
}

void CSuchPage0::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuchPage0)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuchPage0, CPropertyPage)
	//{{AFX_MSG_MAP(CSuchPage0)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuchPage0 message handlers

void CSuchPage0::OnRadio1() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	parent -> m_iNextPage = 1;
}

void CSuchPage0::OnRadio4() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	parent -> m_iNextPage = 2;
}

void CSuchPage0::OnRadio5() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	parent -> m_iNextPage = 3;
}

void CSuchPage0::OnRadio6() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	parent -> m_iNextPage = 4;
}

BOOL CSuchPage0::OnSetActive() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	parent -> SetWizardButtons( PSWIZB_NEXT );

	if ( !m_bInit )
	{
		parent -> m_iNextPage = 1;
		CheckRadioButton( IDC_RADIO1, IDC_RADIO6, IDC_RADIO1 );
		m_bInit = TRUE;
	}
	else
	{
		switch ( parent -> m_iNextPage )
		{
		case 1:
			CheckRadioButton( IDC_RADIO1, IDC_RADIO6, IDC_RADIO1 );
			break;
		case 2:
			CheckRadioButton( IDC_RADIO1, IDC_RADIO6, IDC_RADIO4 );
			break;
		case 3:
			CheckRadioButton( IDC_RADIO1, IDC_RADIO6, IDC_RADIO5 );
			break;
		case 4:
			CheckRadioButton( IDC_RADIO1, IDC_RADIO6, IDC_RADIO6 );
			break;
		}
	}
	
	return CPropertyPage::OnSetActive();
}
