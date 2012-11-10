// SuchPage4.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SuchPage4.h"
#include "MyPropS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuchPage4 property page

IMPLEMENT_DYNCREATE(CSuchPage4, CPropertyPage)

CSuchPage4::CSuchPage4() : CPropertyPage(CSuchPage4::IDD)
{
	//{{AFX_DATA_INIT(CSuchPage4)
	m_strName = _T("");
	//}}AFX_DATA_INIT
}

CSuchPage4::~CSuchPage4()
{
}

void CSuchPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuchPage4)
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuchPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CSuchPage4)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuchPage4 message handlers

BOOL CSuchPage4::OnSetActive() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
	if ( parent -> m_iNextPage != 4 )
	{
		parent -> SetActivePage( parent -> m_iNextPage );
		return FALSE;
	}
	else
	{
		UpdateData( TRUE );

		if ( m_strName.GetLength() > 1 )
			parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
		else
			parent -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );

		return CPropertyPage::OnSetActive();
	}
}

void CSuchPage4::OnChangeEdit1() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	UpdateData( TRUE );

	if ( m_strName.GetLength() > 1 )
		parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
	else
		parent -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );
}

BOOL CSuchPage4::OnWizardFinish() 
{
	UpdateData( FALSE );
	return CPropertyPage::OnWizardFinish();
}
