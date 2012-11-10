// PgOptDraw.cpp : implementation file
//

#include "stdafx.h"
#include "PictView.h"
#include "BasePpg.h"
#include "PgOptDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPgOptDraw property page

IMPLEMENT_DYNCREATE(CPgOptDraw, CBasePpg)

CPgOptDraw::CPgOptDraw() : CBasePpg(CPgOptDraw::IDD)
{
	//{{AFX_DATA_INIT(CPgOptDraw)
	m_bBanding = FALSE;
	//}}AFX_DATA_INIT
}

CPgOptDraw::~CPgOptDraw()
{
}

void CPgOptDraw::DoDataExchange(CDataExchange* pDX)
{
	CBasePpg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgOptDraw)
	DDX_Check(pDX, IDC_CHK_BANDING, m_bBanding);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPgOptDraw, CBasePpg)
	//{{AFX_MSG_MAP(CPgOptDraw)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgOptDraw message handlers
