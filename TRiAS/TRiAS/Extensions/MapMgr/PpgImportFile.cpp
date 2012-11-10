#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpgImportFile property page

IMPLEMENT_DYNCREATE(CPpgImportFile, CPropertyPage)

CPpgImportFile::CPpgImportFile()
	: CPropertyPage(CPpgImportFile::IDD)
	, m_stsItem( m_progressItem )
	, m_stsChunk( m_progressChunk, &m_textProgressMessage )
	, m_bProcessed( FALSE )
{
	//{{AFX_DATA_INIT(CPpgImportFile)
	m_strDstDir = _T("");
	//}}AFX_DATA_INIT
}

CPpgImportFile::~CPpgImportFile() {
}

void CPpgImportFile::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgImportFile)
	DDX_Control(pDX, IDC_BUTTONSTART, m_btnStart);
	DDX_Control(pDX, IDC_PROGRESSCHUNK, m_progressChunk);
	DDX_Control(pDX, IDC_PROGRESSMESSAGE, m_textProgressMessage);
	DDX_Control(pDX, IDC_PROGRESSIMPORT, m_progressItem);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDITDIR, m_pParent->m_strDstDir);
}

void CPpgImportFile::UpdateControls() {
	m_btnStart.EnableWindow( !m_pParent->m_strDstDir.IsEmpty() && !m_bProcessed );
	DWORD dwButtons = PSWIZB_FINISH | PSWIZB_BACK;
	if( m_bProcessed ) {
		dwButtons &= ~PSWIZB_BACK;
		dwButtons |= PSWIZB_FINISH;
	}
	m_pParent->SetWizardButtons( dwButtons );
}

BEGIN_MESSAGE_MAP(CPpgImportFile, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgImportFile)
	ON_BN_CLICKED(IDC_BUTTONSTART, OnButtonstart)
	ON_BN_CLICKED(IDC_BUTTONSELDIR, OnButtonseldir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgImportFile message handlers

void CPpgImportFile::P::StartingFilter() {
	m_ctl.SetPos(0);
}

void CPpgImportFile::P::ReportingStatus( double havePercent, LPCTSTR lpszMsg ) {
	m_ctl.SetPos( froundl( havePercent ) );
	if( m_pTextWnd && lpszMsg ) {
		m_pTextWnd->SetWindowText( lpszMsg );
	}
}

void CPpgImportFile::P::EndingFilter() {
}

BOOL CPpgImportFile::OnInitDialog() {
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPpgImportFile::OnButtonstart() {
	CComQIPtr<IPictHolder,&IID_IPictHolder>	p;
	p = m_pParent->m_pTopoPict;
	p->Close();
	m_pParent->SetWizardButtons( PSWIZB_DISABLEDFINISH );
	m_pParent->ReduceInFile( m_stsChunk, m_stsItem );
	m_bProcessed = TRUE;
	UpdateControls();
}

void CPpgImportFile::OnButtonseldir()  {
	CDirSelectDialog	dlg;
	if( IDOK == dlg.DoModal() ) {
		m_pParent->m_strDstDir = dlg.m_strDirectory;
		UpdateData(FALSE);
		UpdateControls();
	}
}
