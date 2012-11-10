#include "stdafx.h"
#include "LinesigImpl.h"
#include "PgError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPgError property page

IMPLEMENT_DYNCREATE(CPgError, CPropertyPage)

CPgError::CPgError()
	: CPropertyPage(CPgError::IDD) {
	//{{AFX_DATA_INIT(CPgError)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pError = NULL;
}

CPgError::CPgError(CStringArray *pError)
	: CPropertyPage(CPgError::IDD) {
	m_pError = pError;
}

CPgError::~CPgError() {
}

void CPgError::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgError)
	DDX_Control(pDX, IDC_LIST_ERROR, m_listError);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPgError, CPropertyPage)
	//{{AFX_MSG_MAP(CPgError)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgError message handlers

BOOL CPgError::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	if( NULL != m_pError ) {
		ASSERT_KINDOF( CStringArray, m_pError );
		for( int i = 0; i < m_pError->GetSize(); i++ ) {
			m_listError.AddString( m_pError->GetAt(i) );
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
