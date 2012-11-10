// SuchPage3.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SuchPage3.h"
#include "MyPropS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuchPage3 property page

IMPLEMENT_DYNCREATE(CSuchPage3, CPropertyPage)

CSuchPage3::CSuchPage3() : CPropertyPage(CSuchPage3::IDD)
{
	//{{AFX_DATA_INIT(CSuchPage3)
	m_strFlur = _T("");
	m_strFlurStck = _T("");
	//}}AFX_DATA_INIT
}

CSuchPage3::~CSuchPage3()
{
}

void CSuchPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuchPage3)
	DDX_Text(pDX, IDC_EDIT1, m_strFlur);
	DDX_Text(pDX, IDC_EDIT2, m_strFlurStck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuchPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CSuchPage3)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuchPage3 message handlers

BOOL CSuchPage3::OnSetActive() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
	if ( parent -> m_iNextPage != 3 )
	{
		parent -> SetActivePage( parent -> m_iNextPage );
		return FALSE;
	}
	else
	{
		UpdateData( TRUE );

		if (( m_strFlur.GetLength() > 0 ) || ( m_strFlurStck.GetLength() > 1 ))
			parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
		else
			parent -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );

		return CPropertyPage::OnSetActive();
	}
}

BOOL CSuchPage3::OnWizardFinish() 
{
	UpdateData( TRUE );
	return CPropertyPage::OnWizardFinish();
}

void CSuchPage3::OnChangeEdit1() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	UpdateData( TRUE );

	if (( m_strFlur.GetLength() > 0 ) || ( m_strFlurStck.GetLength() > 1 ))
		parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
	else
		parent -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );
}

void CSuchPage3::OnChangeEdit2() 
{
	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	UpdateData( TRUE );

	if (( m_strFlur.GetLength() > 0 ) || ( m_strFlurStck.GetLength() > 1 ))
		parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
	else
		parent -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );
}
