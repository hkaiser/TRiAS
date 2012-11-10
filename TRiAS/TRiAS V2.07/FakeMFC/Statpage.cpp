// statpage.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include "strings.h"

#include <itoolbar.h>
#include <toolguid.h>

#include "fakemfc.hxx"		// die Erweiterung selbst

#include "statpage.h"
#include "summinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatPage property page

IMPLEMENT_DYNCREATE(CStatPage, CPropertyPage)

CStatPage::CStatPage() : CPropertyPage(CStatPage::IDD)
{
	//{{AFX_DATA_INIT(CStatPage)
	m_strSavedBy = g_cbNil;
	m_strRevNum = g_cbNil;
	m_strEditTime = g_cbNil;
	m_strLastPrint = g_cbNil;
	m_strCreateDate = g_cbNil;
	m_strLastSave = g_cbNil;
	m_strSecurity = g_cbNil;
	//}}AFX_DATA_INIT
}

CStatPage::~CStatPage()
{
}

void CStatPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatPage)
	DDX_Text(pDX, IDC_SAVEDBY, m_strSavedBy);
	DDX_Text(pDX, IDC_REVNUM, m_strRevNum);
	DDX_Text(pDX, IDC_EDITTIME, m_strEditTime);
	DDX_Text(pDX, IDC_LASTPRINT, m_strLastPrint);
	DDX_Text(pDX, IDC_CREATEDATE, m_strCreateDate);
	DDX_Text(pDX, IDC_LASTSAVE, m_strLastSave);
	DDX_Text(pDX, IDC_SECURITY, m_strSecurity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatPage, CPropertyPage)
        //{{AFX_MSG_MAP(CStatPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// setzen der SummaryInfo -----------------------------------------------------
void CStatPage::SetSummInfo (CSummInfo *pSI)
{
	m_pSummInfo = pSI; 

	if (NULL == m_pSummInfo) return;

	m_strSavedBy = m_pSummInfo -> GetLastAuthor();
	m_strRevNum = m_pSummInfo -> GetRevNum();
	m_strEditTime = m_pSummInfo -> GetEditTime();
	m_strLastPrint = m_pSummInfo -> GetLastPrintDate();
	m_strCreateDate = m_pSummInfo -> GetCreateDate();
	m_strLastSave = m_pSummInfo -> GetLastSaveDate();
	m_strSecurity = m_pSummInfo -> GetSecurity();
}

/////////////////////////////////////////////////////////////////////////////
// CStatPage message handlers

