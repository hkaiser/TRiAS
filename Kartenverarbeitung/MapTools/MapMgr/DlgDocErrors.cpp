// DlgDocErrors.cpp : implementation file
//

#include "stdafx.h"
#include "mapmgr.h"
#include "DlgDocErrors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPgDocErrors property page

IMPLEMENT_DYNCREATE(CPgDocErrors, CPropertyPage)

CPgDocErrors::CPgDocErrors( UINT nIdCaption ) : CPropertyPage(CPgDocErrors::IDD, nIdCaption)
{
}

CPgDocErrors::CPgDocErrors( ) : CPropertyPage(CPgDocErrors::IDD)
{
	//{{AFX_DATA_INIT(CPgDocErrors)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPgDocErrors::~CPgDocErrors()
{
}

void CPgDocErrors::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgDocErrors)
	DDX_Control(pDX, IDC_LST_ERRORS, m_lstErrors);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPgDocErrors, CPropertyPage)
	//{{AFX_MSG_MAP(CPgDocErrors)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgDocErrors message handlers

BOOL CPgDocErrors::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	for( int i = 0; i < m_strErrors.GetSize(); ++i )
		m_lstErrors.AddString( m_strErrors.GetAt( i ) );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
