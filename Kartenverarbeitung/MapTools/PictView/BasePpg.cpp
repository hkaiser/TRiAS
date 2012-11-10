#include "stdafx.h"
#include "PictView.h"
#include "BasePpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBasePpg property page

IMPLEMENT_DYNCREATE(CBasePpg, CPropertyPage)

CBasePpg::CBasePpg( ) : CPropertyPage() {
	m_bIsActive = FALSE;
}

CBasePpg::CBasePpg( UINT nID ) : CPropertyPage(nID) {
	m_bIsActive = FALSE;
	//{{AFX_DATA_INIT(CBasePpg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CBasePpg::~CBasePpg() {
}

void CBasePpg::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBasePpg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBasePpg, CPropertyPage)
	//{{AFX_MSG_MAP(CBasePpg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBasePpg message handlers

BOOL CBasePpg::OnSetActive()  {
	m_bIsActive = TRUE;
	return CPropertyPage::OnSetActive();
}

BOOL CBasePpg::OnKillActive()  {
	m_bIsActive = FALSE;
	return CPropertyPage::OnKillActive();
}
