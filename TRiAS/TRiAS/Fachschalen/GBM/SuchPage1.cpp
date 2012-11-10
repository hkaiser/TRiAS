// SuchPage1.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SuchPage1.h"
#include "MyPropS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuchPage1 property page

IMPLEMENT_DYNCREATE(CSuchPage1, CPropertyPage)

CSuchPage1::CSuchPage1() : CPropertyPage(CSuchPage1::IDD)
{
	//{{AFX_DATA_INIT(CSuchPage1)
	m_strIdent = _T("");
	//}}AFX_DATA_INIT
}

CSuchPage1::~CSuchPage1()
{
}

void CSuchPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuchPage1)
	DDX_Text(pDX, IDC_EDIT1, m_strIdent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuchPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CSuchPage1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuchPage1 message handlers


BOOL CSuchPage1::OnSetActive() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	if ( parent -> m_iNextPage != 1 )
	{
		parent -> SetActivePage( parent -> m_iNextPage );
		return FALSE;
	}
	else
	{
		UpdateData( TRUE );

		if ( m_strIdent.GetLength() > 4 )
			parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
		else
			parent -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );

		return CPropertyPage::OnSetActive();
	}
}

BOOL CSuchPage1::OnWizardFinish() 
{
	UpdateData( TRUE );
	return CPropertyPage::OnWizardFinish();
}

void CSuchPage1::OnChangeEdit1() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	UpdateData( TRUE );

	if ( m_strIdent.GetLength() > 4 )
		parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
	else
		parent -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );
}
