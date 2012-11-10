// summpage.cpp : implementation file
//
#include "fakemfcp.hxx"
#include "fakemfc.h"
#include "strings.h"

#include <itoolbar.h>
#include <toolguid.h>

#include "fakemfc.hxx"		// die Erweiterung selbst

#include "summpage.h"
#include "summinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSummPage property page

IMPLEMENT_DYNCREATE(CSummPage, CPropertyPage)

CSummPage::CSummPage() : CPropertyPage(CSummPage::IDD)
{
	//{{AFX_DATA_INIT(CSummPage)
	m_strAuthor = g_cbNil;
	m_strKeywd = g_cbNil;
	m_strSubj = g_cbNil;
	m_strCmt = g_cbNil;
	m_strTitle = g_cbNil;
	//}}AFX_DATA_INIT

	m_fDirty = false;
}

CSummPage::~CSummPage()
{
}

void CSummPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	
	//{{AFX_DATA_MAP(CSummPage)
	DDX_Text(pDX, IDC_AUTHOR, m_strAuthor);
	DDX_Text(pDX, IDC_KEYWORDS, m_strKeywd);
	DDX_Text(pDX, IDC_SUBJECT, m_strSubj);
	DDX_Text(pDX, IDC_COMMENTS, m_strCmt);
	DDX_Text(pDX, IDC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSummPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSummPage)
	ON_EN_KILLFOCUS(IDC_AUTHOR, OnKillfocusAuthor)
	ON_EN_KILLFOCUS(IDC_COMMENTS, OnKillfocusComments)
	ON_EN_KILLFOCUS(IDC_KEYWORDS, OnKillfocusKeywords)
	ON_EN_KILLFOCUS(IDC_SUBJECT, OnKillfocusSubject)
	ON_EN_KILLFOCUS(IDC_TITLE, OnKillfocusTitle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// setzen der SummaryInfo -----------------------------------------------------
void CSummPage::SetSummInfo (CSummInfo *pSI)
{
	m_pSummInfo = pSI; 

	if (NULL == m_pSummInfo) return;

	m_strTitle = m_pSummInfo -> GetTitle();
	m_strSubj = m_pSummInfo -> GetSubject();
	m_strAuthor = m_pSummInfo -> GetAuthor();
	m_strKeywd = m_pSummInfo -> GetKeywords();
	m_strCmt = m_pSummInfo -> GetComments();
}

void CSummPage::SaveChanges (void)
{
	if (IsDirty()) {
		m_pSummInfo -> SetAuthor (m_strAuthor);
		m_pSummInfo -> SetKeywords (m_strKeywd);
		m_pSummInfo -> SetSubject (m_strSubj);
		m_pSummInfo -> SetComments (m_strCmt);
		m_pSummInfo -> SetTitle (m_strTitle);

		DEX_SetDirtyGeoDB (true);	// DB am Schluß speichern
		SetDirty (false);
	}	
}

/////////////////////////////////////////////////////////////////////////////
// CSummPage message handlers

BOOL CSummPage::OnApply() 
{
	SaveChanges();
	return CPropertyPage::OnApply();
}

void CSummPage::OnKillfocusAuthor() 
{
CEdit *pEdit = (CEdit *)GetDlgItem (IDC_AUTHOR);

	if (pEdit -> GetModify()) {
		SetDirty();
		pEdit -> SetModify (false);
	}
}

void CSummPage::OnKillfocusComments() 
{
CEdit *pEdit = (CEdit *)GetDlgItem (IDC_COMMENTS);

	if (pEdit -> GetModify()) {
		SetDirty();
		pEdit -> SetModify (false);
	}
}

void CSummPage::OnKillfocusKeywords() 
{
CEdit *pEdit = (CEdit *)GetDlgItem (IDC_KEYWORDS);

	if (pEdit -> GetModify()) {
		SetDirty();
		pEdit -> SetModify (false);
	}
}

void CSummPage::OnKillfocusSubject() 
{
CEdit *pEdit = (CEdit *)GetDlgItem (IDC_SUBJECT);

	if (pEdit -> GetModify()) {
		SetDirty();
		pEdit -> SetModify (false);
	}
}

void CSummPage::OnKillfocusTitle() 
{
CEdit *pEdit = (CEdit *)GetDlgItem (IDC_TITLE);

	if (pEdit -> GetModify()) {
		SetDirty();
		pEdit -> SetModify (false);
	}
}
