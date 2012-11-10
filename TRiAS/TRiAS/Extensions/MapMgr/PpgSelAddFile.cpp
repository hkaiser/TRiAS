#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpgSelAddFile property page

IMPLEMENT_DYNCREATE(CPpgSelAddFile, CPropertyPage)

CPpgSelAddFile::CPpgSelAddFile() : CPropertyPage(CPpgSelAddFile::IDD) {
	//{{AFX_DATA_INIT(CPpgSelAddFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpgSelAddFile::~CPpgSelAddFile() {
}

void CPpgSelAddFile::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgSelAddFile)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDITNAME, m_pParent->m_strAddMap);
}

void CPpgSelAddFile::UpdateControls() {

	m_pParent->m_nNextStep = -1;
	if( m_pParent->m_pTopoMap ) {
		CComBSTR	S;
		long		bValid;
		if(0) {
		} else if(S_OK == m_pParent->m_pTopoMap->HaveNomenclatur( &bValid ) && FALSE != bValid ) {
			m_pParent->m_nNextStep = CPpgNomenclatur::IDD;
		} else if(S_OK == m_pParent->m_pTopoMap->PrepareFinalData( &bValid ) && FALSE != bValid ) {
			m_pParent->m_nNextStep = CPpgMapInfo::IDD;
		}
	}

	DWORD dwButtons = PSWIZB_NEXT | PSWIZB_BACK;
	if( m_pParent->m_strAddMap.IsEmpty() ) {
		dwButtons &= ~PSWIZB_NEXT;
	}
	m_pParent->SetWizardButtons( dwButtons );
}

BEGIN_MESSAGE_MAP(CPpgSelAddFile, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgSelAddFile)
	ON_BN_CLICKED(IDC_BUTTONNAME, OnButtonsrcmap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgSelAddFile message handlers

BOOL CPpgSelAddFile::OnInitDialog()  {
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//LRESULT CPpgSelAddFile::OnWizardNext()  {
//	return CPropertyPage::OnWizardNext(m_pParent->m_TDI.m_nNextStep);
//}

void CPpgSelAddFile::OnButtonsrcmap()  {
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
	CString	strFilter( S );
	CFileDialog	dlg(TRUE,NULL,_T(""),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,this);
	if( IDOK == dlg.DoModal() ) {
		long	bValid;
		CComBSTR	S( dlg.GetPathName() );
		if( S_OK == m_pParent->m_pTopoMap->CheckAltFile( S, &bValid ) && TRUE == bValid ) {
			m_pParent->m_strAddMap = dlg.GetPathName();
		} else {
			CString So;
			CString St;
			St.LoadString ( IDS_NOMAPDOC);
			So.Format( St, (LPCTSTR) dlg.GetPathName(), (LPCTSTR) m_pParent->m_strMapType );
//			So.Format( _T("Die Beschreibungsdatei [%s] ist keine gültige Beschreibungsdatei für Karten des Typs [%s]."), (LPCTSTR) dlg.GetPathName(), (LPCTSTR) m_pParent->m_strMapType );
			::AfxMessageBox( So );
			m_pParent->m_strAddMap.Empty();
		}
	}
	UpdateData(FALSE);
	UpdateControls();
}
