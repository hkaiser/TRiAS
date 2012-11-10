#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpgSelDocFile property page

IMPLEMENT_DYNCREATE(CPpgSelDocFile, CPropertyPage)

CPpgSelDocFile::CPpgSelDocFile() : CPropertyPage(CPpgSelDocFile::IDD) {
	//{{AFX_DATA_INIT(CPpgSelDocFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpgSelDocFile::~CPpgSelDocFile() {
}

void CPpgSelDocFile::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgSelDocFile)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_CHECKASCIIFILE, m_btnCheckAscii);
	DDX_Control(pDX, IDC_FILEDESCRIPTION, m_textDescription);
	DDX_Check(pDX,IDC_CHECKASCIIFILE, m_bCheckAscii);
	//}}AFX_DATA_MAP

}

void CPpgSelDocFile::UpdateControls() {

	// KK010306
	m_pParent->m_nNextStep = -1;

	m_pParent->m_bDstDir = FALSE;

	DWORD dwButtons = PSWIZB_FINISH | PSWIZB_BACK;
	m_pParent->SetWizardButtons( dwButtons );

	CString R;
	int iPos = m_pParent->m_strSrcMap.ReverseFind ('\\');
	R = m_pParent->m_strSrcMap.Left (iPos+1);

	CString S;
	CString St;
	St.LoadString(IDS_DISPLAYPROTOCOL);
//	S.Format( St,(LPCTSTR) m_pParent->m_strMapType,(LPCTSTR)m_pParent->m_strMapExt, (LPCTSTR) m_pParent->m_strSrcMap, (LPCTSTR) m_pParent->m_strDstDir );
	S.Format( St,(LPCTSTR) m_pParent->m_strMapType,(LPCTSTR)m_pParent->m_strMapExt, (LPCTSTR) R, (LPCTSTR) m_pParent->m_strDstDir );

	m_textDescription.SetWindowText(S);
	UpdateWindow();
}

BEGIN_MESSAGE_MAP(CPpgSelDocFile, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgSelDocFile)
	ON_BN_CLICKED(IDC_CHECKASCIIFILE, OnASCIIFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgSelDocFile message handlers

BOOL CPpgSelDocFile::OnInitDialog()  {
	CPropertyPage::OnInitDialog();
	m_bCheckAscii = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//LRESULT CPpgSelDocFile::OnWizardNext()  {
//	return CPropertyPage::OnWizardNext(m_pParent->m_TDI.m_nNextStep);
//}

void CPpgSelDocFile::OnASCIIFile()  {
	_ASSERTE( m_pParent->m_pTopoMap );
	CComBSTR	S;
	if( S_OK != m_pParent->m_pTopoMap->GetAltFileFilter( &S ) 
		|| 0 == S.Length() ) {
		CString Ss;
		Ss.LoadString(IDS_HARDERROR);
		::AfxMessageBox( Ss);
//		::AfxMessageBox( _T("schwerer interner Fehler") );
		return;
	}

	m_pParent->m_bNoReduce = m_bCheckAscii = m_btnCheckAscii.GetCheck();

	UpdateData();
}
