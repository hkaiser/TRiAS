// EDBS_CfgImpCmn.cpp: Implementierungsdatei
//

#include "stdafx.h"

#if defined(_USE_CONFIG_DIALOGS)

#include "resource.h"
#include "EDBS_CfgImpCmn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite CEDBS_CfgImpCmn 

IMPLEMENT_DYNCREATE(CEDBS_CfgImpCmn, CPropertyPage)

CEDBS_CfgImpCmn::CEDBS_CfgImpCmn() : CPropertyPage(CEDBS_CfgImpCmn::IDD)
{
	//{{AFX_DATA_INIT(CEDBS_CfgImpCmn)
	m_tCreateBIgeom = TRUE;
	m_tCreateBItext = FALSE;
	m_tCreateBIattr = TRUE;
	m_tImportKSIG = FALSE;
	m_tImportVPKT = FALSE;
	m_tCreateAttrAktualitaet = TRUE;
	m_tCreateAttrDateiname = FALSE;
	m_tCreateAttrFolie = FALSE;
	m_tCreateAttrObjektart = FALSE;
	m_tCreateAttrObjektnummer = TRUE;
	m_tCreateAttrObjektteilnummer = TRUE;
	m_tCreateAttrObjektteilnummerK = TRUE;
	m_tCreateAttrRegeln = FALSE;
	//}}AFX_DATA_INIT
}

CEDBS_CfgImpCmn::~CEDBS_CfgImpCmn()
{
}

void CEDBS_CfgImpCmn::LoadConfig()
{
	m_tDefault = m_pConfiguration->m_tDefaultObjectMapping;
	m_tCreateBItext = m_pConfiguration->m_tCreateBItext;
	m_tCreateBIattr = m_pConfiguration->m_tCreateBIattr;
	m_tCreateBIgeom = m_pConfiguration->m_tCreateBIgeom;
	m_tImportKSIG = m_pConfiguration->m_tImportKSIG;
	m_tImportVPKT = m_pConfiguration->m_tImportVPKT;

	this->m_tCreateAttrDateiname = m_pConfiguration->m_tCreateAttributeDateiname;
	this->m_tCreateAttrFolie = m_pConfiguration->m_tCreateAttributeFolie;
	this->m_tCreateAttrObjektart = m_pConfiguration->m_tCreateAttributeObjektart;
	this->m_tCreateAttrObjektnummer = m_pConfiguration->m_tCreateAttributeObjektnummer;
	this->m_tCreateAttrObjektteilnummer = m_pConfiguration->m_tCreateAttributeObjektteilnummer;
	this->m_tCreateAttrObjektteilnummerK = m_pConfiguration->m_tCreateAttributeObjektteilnummerK;
	this->m_tCreateAttrAktualitaet = m_pConfiguration->m_tCreateAttributeAktualitaet;
	this->m_tCreateAttrRegeln = m_pConfiguration->m_tCreateAttributeRegeln;

	UpdateData(false);
}

void CEDBS_CfgImpCmn::SaveConfig()
{
	m_pConfiguration->m_tDefaultObjectMapping = m_tDefault;
	m_pConfiguration->m_tCreateBItext = m_tCreateBItext;
	m_pConfiguration->m_tCreateBIattr = m_tCreateBIattr;
	m_pConfiguration->m_tCreateBIgeom = m_tCreateBIgeom;
	m_pConfiguration->m_tImportKSIG = m_tImportKSIG;
	m_pConfiguration->m_tImportVPKT = m_tImportVPKT;

	m_pConfiguration->m_tCreateAttributeDateiname = this->m_tCreateAttrDateiname;
	m_pConfiguration->m_tCreateAttributeFolie = this->m_tCreateAttrFolie;
	m_pConfiguration->m_tCreateAttributeObjektart = this->m_tCreateAttrObjektart;
	m_pConfiguration->m_tCreateAttributeObjektnummer = this->m_tCreateAttrObjektnummer;
	m_pConfiguration->m_tCreateAttributeObjektteilnummer = this->m_tCreateAttrObjektteilnummer;
	m_pConfiguration->m_tCreateAttributeObjektteilnummerK = this->m_tCreateAttrObjektteilnummerK;
	m_pConfiguration->m_tCreateAttributeAktualitaet = this->m_tCreateAttrAktualitaet;
	m_pConfiguration->m_tCreateAttributeRegeln = this->m_tCreateAttrRegeln;
}

void CEDBS_CfgImpCmn::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEDBS_CfgImpCmn)
	DDX_Check(pDX, IDC_DEFAULT, m_tDefault);
	DDX_Check(pDX, IDC_CREATEBIGEOM, m_tCreateBIgeom);
	DDX_Check(pDX, IDC_CREATEBITEXT, m_tCreateBItext);
	DDX_Check(pDX, IDC_CREATEBIATTR, m_tCreateBIattr);
	DDX_Check(pDX, IDC_IMPORTKSIG, m_tImportKSIG);
	DDX_Check(pDX, IDC_IMPORTVPKT, m_tImportVPKT);
	DDX_Check(pDX, IDC_CRTATRAKTUALITAET, m_tCreateAttrAktualitaet);
	DDX_Check(pDX, IDC_CRTATRDATEINAME, m_tCreateAttrDateiname);
	DDX_Check(pDX, IDC_CRTATRFOLIE, m_tCreateAttrFolie);
	DDX_Check(pDX, IDC_CRTATROBJEKTART, m_tCreateAttrObjektart);
	DDX_Check(pDX, IDC_CRTATROBJEKTNUMMER, m_tCreateAttrObjektnummer);
	DDX_Check(pDX, IDC_CRTATROBJEKTTEILNUMMER, m_tCreateAttrObjektteilnummer);
	DDX_Check(pDX, IDC_CRTATROBJEKTTEILNUMMERK, m_tCreateAttrObjektteilnummerK);
	DDX_Check(pDX, IDC_CRTATRREGELN, m_tCreateAttrRegeln);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEDBS_CfgImpCmn, CPropertyPage)
	//{{AFX_MSG_MAP(CEDBS_CfgImpCmn)
	ON_BN_CLICKED(IDC_DEFAULT, OnClickDefault)
	ON_BN_CLICKED(IDC_IMPORTKSIG, OnClickImportKSIG)
	ON_BN_CLICKED(IDC_IMPORTVPKT, OnClickImportVPKT)
	ON_BN_CLICKED(IDC_CREATEBITEXT, OnClickCreateBItext)
	ON_BN_CLICKED(IDC_CREATEBIGEOM, OnClickCreateBIgeom)
	ON_BN_CLICKED(IDC_CREATEBIATTR, OnClickCreateBIattr)
	ON_BN_CLICKED(IDC_CRTATRAKTUALITAET, OnClickCrtAtrAktualitaet)
	ON_BN_CLICKED(IDC_CRTATRDATEINAME, OnClickCrtAtrDateiname)
	ON_BN_CLICKED(IDC_CRTATRFOLIE, OnClickCrtAtrFolie)
	ON_BN_CLICKED(IDC_CRTATROBJEKTART, OnClickCrtAtrObjektart)
	ON_BN_CLICKED(IDC_CRTATROBJEKTNUMMER, OnClickCrtAtrObjektnummer)
	ON_BN_CLICKED(IDC_CRTATROBJEKTTEILNUMMER, OnClickCrtAtrObjektteilnummer)
	ON_BN_CLICKED(IDC_CRTATROBJEKTTEILNUMMERK, OnClickCrtAtrObjektteilnummerK)
	ON_BN_CLICKED(IDC_CRTATRREGELN, OnClickCrtAtrRegeln)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CEDBS_CfgImpCmn 

BOOL CEDBS_CfgImpCmn::OnSetActive() 
{
	LoadConfig();	
	SetWizardButtons();
	return CPropertyPage::OnSetActive();
}


void CEDBS_CfgImpCmn::SetWizardButtons()
{
	CPropertySheet* pPropertySheet = (CPropertySheet*) GetParent();   
//	int iActivePage = pPropertySheet->GetActiveIndex();
//	if( 0 == iActivePage ) {
//		if( iActivePage == pPropertySheet->GetPageCount() - 1 )
//			pPropertySheet->SetWizardButtons(PSWIZB_FINISH);
//		else
//			pPropertySheet->SetWizardButtons(PSWIZB_NEXT);
//	}
//	else if( iActivePage == pPropertySheet->GetPageCount() - 1 )
//		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
//	else
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

}

BOOL CEDBS_CfgImpCmn::OnWizardFinish() 
{
	SaveConfig();
	m_pConfiguration->Save();
	
	return CPropertyPage::OnWizardFinish();
}

BOOL CEDBS_CfgImpCmn::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	char strBuffer[255];
	UINT cbBuffer;

	cbBuffer = this->GetDlgItemText( IDC_CREATEBIATTR, strBuffer, sizeof(strBuffer) );
	sprintf(&strBuffer[cbBuffer+1],strBuffer,this->m_pConfiguration->m_strTRiASName );
	SetDlgItemText( IDC_CREATEBIATTR, &strBuffer[cbBuffer+1] );
	
	LoadConfig();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

LRESULT CEDBS_CfgImpCmn::OnWizardNext() 
{
	SaveConfig();
	
	return CPropertyPage::OnWizardNext();
}

void CEDBS_CfgImpCmn::OnClickDefault() 
{
	m_tDefault = !m_tDefault;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickImportKSIG() 
{
	m_tImportKSIG = !m_tImportKSIG;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickImportVPKT() 
{
	m_tImportVPKT = !m_tImportVPKT;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCreateBItext() 
{
	m_tCreateBItext = !m_tCreateBItext;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCreateBIgeom() 
{
	m_tCreateBIgeom = !m_tCreateBIgeom;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCreateBIattr() 
{
	m_tCreateBIattr = !m_tCreateBIattr;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCrtAtrAktualitaet() 
{
	this->m_tCreateAttrAktualitaet = !this->m_tCreateAttrAktualitaet;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCrtAtrDateiname() 
{
	this->m_tCreateAttrDateiname = !this->m_tCreateAttrDateiname;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCrtAtrFolie() 
{
	this->m_tCreateAttrFolie = !this->m_tCreateAttrFolie;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCrtAtrObjektart() 
{
	this->m_tCreateAttrObjektart = !this->m_tCreateAttrObjektart;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCrtAtrObjektnummer() 
{
	this->m_tCreateAttrObjektnummer = !this->m_tCreateAttrObjektnummer;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCrtAtrObjektteilnummer() 
{
	this->m_tCreateAttrObjektteilnummer = !this->m_tCreateAttrObjektteilnummer;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCrtAtrObjektteilnummerK() 
{
	this->m_tCreateAttrObjektteilnummerK = !this->m_tCreateAttrObjektteilnummerK;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpCmn::OnClickCrtAtrRegeln() 
{
	this->m_tCreateAttrRegeln = !this->m_tCreateAttrRegeln;
	this->SetModified(true);
	UpdateData( FALSE );
}

#endif // defined(_USE_CONFIG_DIALOGS)
