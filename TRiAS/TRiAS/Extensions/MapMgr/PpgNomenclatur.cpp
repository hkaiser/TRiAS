#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpgNomenclatur property page

IMPLEMENT_DYNCREATE(CPpgNomenclatur, CPropertyPage)

CPpgNomenclatur::CPpgNomenclatur() : CPropertyPage(CPpgNomenclatur::IDD) {
	//{{AFX_DATA_INIT(CPpgNomenclatur)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpgNomenclatur::~CPpgNomenclatur() {
}

void CPpgNomenclatur::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgNomenclatur)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CPpgNomenclatur::UpdateControls() {
}

BEGIN_MESSAGE_MAP(CPpgNomenclatur, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgNomenclatur)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgNomenclatur message handlers
