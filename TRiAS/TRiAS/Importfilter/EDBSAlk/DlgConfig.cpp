// DlgConfig.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DlgConfig.h"
#include "edbs.hpp"
#include "CfgDb.h"
#include "Cfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite CDlgCfgExtra 

IMPLEMENT_DYNCREATE(CDlgCfgExtra, CPropertyPage)

CDlgCfgExtra::CDlgCfgExtra() : CPropertyPage(CDlgCfgExtra::IDD)
{
	//{{AFX_DATA_INIT(CDlgCfgExtra)
	m_tImportAreas = FALSE;
	m_tImportLines = FALSE;
	m_tImportPoints = FALSE;
	m_tImportText = FALSE;
	m_tOverwriteRules = FALSE;
	//}}AFX_DATA_INIT
}

CDlgCfgExtra::~CDlgCfgExtra()
{
}

void CDlgCfgExtra::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgExtra)
	DDX_Check(pDX, IDC_IMPORTAREAS, m_tImportAreas);
	DDX_Check(pDX, IDC_IMPORTLINES, m_tImportLines);
	DDX_Check(pDX, IDC_IMPORTPOINTS, m_tImportPoints);
	DDX_Check(pDX, IDC_IMPORTTEXT, m_tImportText);
	DDX_Check(pDX, IDC_DEFAULTOBJECTMAPPING, m_tOverwriteRules);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgExtra, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCfgExtra)
	ON_BN_CLICKED(IDC_DEFAULTOBJECTMAPPING, OnClickDefaultobjectmapping)
	ON_BN_CLICKED(IDC_IMPORTAREAS, OnClickImportAreas)
	ON_BN_CLICKED(IDC_IMPORTLINES, OnClickImportLines)
	ON_BN_CLICKED(IDC_IMPORTPOINTS, OnClickImportPoints)
	ON_BN_CLICKED(IDC_IMPORTTEXT, OnClickImportText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgCfgExtra 
/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite CDlgCfgCommon 

IMPLEMENT_DYNCREATE(CDlgCfgCommon, CPropertyPage)

CDlgCfgCommon::CDlgCfgCommon() : CPropertyPage(CDlgCfgCommon::IDD)
{
	//{{AFX_DATA_INIT(CDlgCfgCommon)
	m_strConfigDescription = _T("");
	//}}AFX_DATA_INIT
}

CDlgCfgCommon::~CDlgCfgCommon()
{
}

void CDlgCfgCommon::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgCommon)
	DDX_Control(pDX, IDC_CONFIGURATIONS, m_cbbConfigurations);
	DDX_Text(pDX, IDC_CFGDESCRIPTION, m_strConfigDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgCommon, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCfgCommon)
	ON_CBN_EDITCHANGE(IDC_CONFIGURATIONS, OnEditchangeConfigurations)
	ON_CBN_SELCHANGE(IDC_CONFIGURATIONS, OnSelchangeConfigurations)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgCfgCommon 

void CDlgCfgExtra::LoadConfig()
{
 CCfg*	pConfiguration;

	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;

	m_tOverwriteRules = pConfiguration->m_tOverwriteRules;
	m_tImportAreas = pConfiguration->m_tImportAreas;
	m_tImportLines = pConfiguration->m_tImportLines;
	m_tImportPoints = pConfiguration->m_tImportPoints;
	m_tImportText = pConfiguration->m_tImportText;

	UpdateData(false);

}

void CDlgCfgExtra::SaveConfig()
{
 CCfg*	pConfiguration;
 
	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;

	pConfiguration->m_tOverwriteRules = m_tOverwriteRules;
	pConfiguration->m_tImportAreas = m_tImportAreas;
	pConfiguration->m_tImportLines = m_tImportLines;
	pConfiguration->m_tImportPoints = m_tImportPoints;
	pConfiguration->m_tImportText = m_tImportText;

}


BOOL CDlgCfgExtra::OnApply() 
{
	SaveConfig();
	this->SetModified(false);
	return CPropertyPage::OnApply();
}

void CDlgCfgExtra::OnClickDefaultobjectmapping() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_tOverwriteRules = !m_tOverwriteRules;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CDlgCfgExtra::OnClickImportAreas() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_tImportAreas = !m_tImportAreas;
	this->SetModified(true);
	UpdateData( FALSE );
	
}

void CDlgCfgExtra::OnClickImportLines() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_tImportLines = !m_tImportLines;
	this->SetModified(true);
	UpdateData( FALSE );
	
}

void CDlgCfgExtra::OnClickImportPoints() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_tImportPoints = !m_tImportPoints;
	this->SetModified(true);
	UpdateData( FALSE );
	
}

void CDlgCfgExtra::OnClickImportText() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_tImportText = !m_tImportText;
	this->SetModified(true);
	UpdateData( FALSE );
	
}


void CDlgCfgDefault::OnClickCreateBIgeom() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_tCreateBIgeom = !m_tCreateBIgeom;
	this->SetModified(true);
	UpdateData( FALSE );
}

void CDlgCfgDefault::OnClickCreateBItext() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_tCreateBItext = !m_tCreateBItext;
	this->SetModified(true);
	UpdateData( FALSE );
}

BOOL CDlgCfgExtra::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	LoadConfig();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgCfgCommon::LoadConfig()
{
	POSITION	pos;
	CString		key;
	CCfgDb		*pCfgDb;
	int			idx;
	
	m_pConfiguration->LoadCfgDbs();

	for ( pos = m_pConfiguration->m_CfgDbs.GetStartPosition(); pos != NULL; ) {
		m_pConfiguration->m_CfgDbs.GetNextAssoc( pos, key, (CObject*&)pCfgDb );
		idx = m_cbbConfigurations.AddString( pCfgDb->m_strConfigName );
		m_cbbConfigurations.SetItemDataPtr( idx, (void*)pCfgDb );
	}
}

void CDlgCfgCommon::SaveConfig()
{
	CCfgDb* pCfgDb;

	pCfgDb = (CCfgDb*)m_cbbConfigurations.GetItemDataPtr(m_cbbConfigurations.GetCurSel());
	m_pConfiguration->m_strConfigFile = pCfgDb->m_strConfigFile;
}

BOOL CDlgCfgCommon::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	LoadConfig();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite CDlgCfgDefault 

IMPLEMENT_DYNCREATE(CDlgCfgDefault, CPropertyPage)

CDlgCfgDefault::CDlgCfgDefault() : CPropertyPage(CDlgCfgDefault::IDD)
{
	//{{AFX_DATA_INIT(CDlgCfgDefault)
	m_tCreateBItext = FALSE;
	m_tCreateBIgeom = FALSE;
	//}}AFX_DATA_INIT
}

CDlgCfgDefault::~CDlgCfgDefault()
{
}

void CDlgCfgDefault::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgDefault)
	DDX_Check(pDX, IDC_CREATEBITEXT, m_tCreateBItext);
	DDX_Check(pDX, IDC_CREATEBIGEOM, m_tCreateBIgeom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgDefault, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCfgDefault)
	ON_BN_CLICKED(IDC_CREATEBIGEOM, OnClickCreateBIgeom)
	ON_BN_CLICKED(IDC_CREATEBITEXT, OnClickCreateBItext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgCfgDefault 

BOOL CDlgCfgDefault::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	LoadConfig();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgCfgDefault::LoadConfig()
{
 CRegKey regEDBS;
 DWORD dwConfigBase;
 CString strRegKey(TRiAS_REGKEY);

	regEDBS.Open(HKEY_CURRENT_USER,strRegKey + "Extensions\\EDBS");

	regEDBS.QueryValue( dwConfigBase,"ConfigBase" );

	m_tCreateBIgeom = (0 != (dwConfigBase & EDBSCFG_CREATEBIGEOM));
	m_tCreateBItext = (0 != (dwConfigBase & EDBSCFG_CREATEBITEXT));

	regEDBS.Close();
	UpdateData(false);
}

void CDlgCfgDefault::SaveConfig()
{
 CRegKey regEDBS;
 DWORD dwConfigBase;
 CCfg*	pConfiguration;
 CxString strConfigFile;
 CString strREgKey(TRiAS_REGKEY);

	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;

	regEDBS.Open(HKEY_CURRENT_USER,strRegKey + "Extensions\\EDBS");

	regEDBS.QueryValue( dwConfigBase,"ConfigBase" );

	if( m_tCreateBIgeom )
		dwConfigBase |= EDBSCFG_CREATEBIGEOM;
	else
		dwConfigBase &= ~EDBSCFG_CREATEBIGEOM;
	if( m_tCreateBItext )
		dwConfigBase |= EDBSCFG_CREATEBITEXT;
	else
		dwConfigBase &= ~EDBSCFG_CREATEBITEXT;
	
	regEDBS.SetValue( dwConfigBase, "ConfigBase");

	regEDBS.Close();
}

BOOL CDlgCfgDefault::OnApply() 
{
	SaveConfig();
	this->SetModified(false);
	return CPropertyPage::OnApply();
}

BOOL CDlgCfgCommon::OnApply() 
{
	SaveConfig();
	this->SetModified(false);
	return CPropertyPage::OnApply();
}

void CDlgCfgCommon::OnEditchangeConfigurations() 
{
	this->SetModified(true);	
}

void CDlgCfgCommon::OnSelchangeConfigurations() 
{
	CCfg*	pConfiguration;
	CCfgDb* pCfgDb;
	CPropertySheet* pPropertySheet;   
	int iNextPage;

	pCfgDb = (CCfgDb*)m_cbbConfigurations.GetItemDataPtr(m_cbbConfigurations.GetCurSel());
	m_strConfigDescription = pCfgDb->m_strConfigDescription;
	UpdateData(false);
//	SetModified(true);

	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;
	pPropertySheet = (CPropertySheet*) GetParent();   
	
	iNextPage = pPropertySheet->GetActiveIndex() + 1;
	while( pPropertySheet->GetPageCount() > iNextPage )
		pPropertySheet->RemovePage( iNextPage );

	pCfgDb = (CCfgDb*)m_cbbConfigurations.GetItemDataPtr(m_cbbConfigurations.GetCurSel());
	if( pCfgDb->m_strConfigFile == "Default" ) {
		pPropertySheet->AddPage( pConfiguration->ppagDefault );		
	}	
	if( pConfiguration->ppagExtra )		
		pPropertySheet->AddPage( pConfiguration->ppagExtra );		

	SetWizardButtons();

}

BOOL CDlgCfgCommon::OnSetActive() 
{
	CCfg	*pConfiguration;
	CCfgDb	*pCfgDb, *pCfgDbDefault;
	int idx, idxDefault;

	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;
	
	for( idx = 0; idx < m_cbbConfigurations.GetCount(); idx++ ) {
		pCfgDb = (CCfgDb*)m_cbbConfigurations.GetItemDataPtr( idx );
		if( pCfgDb->m_strConfigFile == pConfiguration->m_strConfigFile )
			break;
		if( pCfgDb->m_strConfigFile == "Default" ) {
			idxDefault = idx;
			pCfgDbDefault = pCfgDb;
		}
	}
	if( idx < m_cbbConfigurations.GetCount() ) {
		m_cbbConfigurations.SetCurSel( idx );
		m_strConfigDescription = pCfgDb->m_strConfigDescription;
	}
	else {
		m_cbbConfigurations.SetCurSel( idxDefault );
		m_strConfigDescription = pCfgDbDefault->m_strConfigDescription;
	}

	OnSelchangeConfigurations();

	return CPropertyPage::OnSetActive();
}

BOOL CDlgCfgExtra::OnSetActive() 
{
	SetWizardButtons();
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCfgDefault::OnSetActive() 
{
	SetWizardButtons();
	
	return CPropertyPage::OnSetActive();
}


void CDlgCfgCommon::SetWizardButtons()
{
	CPropertySheet* pPropertySheet = (CPropertySheet*) GetParent();   
	int iActivePage = pPropertySheet->GetActiveIndex();
	if( 0 == iActivePage ) {
		if( iActivePage == pPropertySheet->GetPageCount() - 1 )
			pPropertySheet->SetWizardButtons(PSWIZB_FINISH);
		else
			pPropertySheet->SetWizardButtons(PSWIZB_NEXT);
	}
	else if( iActivePage == pPropertySheet->GetPageCount() - 1 )
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
	else
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
}

void CDlgCfgDefault::SetWizardButtons()
{
	CPropertySheet* pPropertySheet = (CPropertySheet*) GetParent();   
	int iActivePage = pPropertySheet->GetActiveIndex();
	if( 0 == iActivePage ) {
		if( iActivePage == pPropertySheet->GetPageCount() - 1 )
			pPropertySheet->SetWizardButtons(PSWIZB_FINISH);
		else
			pPropertySheet->SetWizardButtons(PSWIZB_NEXT);
	}
	else if( iActivePage == pPropertySheet->GetPageCount() - 1 )
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
	else
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
}

void CDlgCfgExtra::SetWizardButtons()
{
	CPropertySheet* pPropertySheet = (CPropertySheet*) GetParent();   
	int iActivePage = pPropertySheet->GetActiveIndex();
	if( 0 == iActivePage ) {
		if( iActivePage == pPropertySheet->GetPageCount() - 1 )
			pPropertySheet->SetWizardButtons(PSWIZB_FINISH);
		else
			pPropertySheet->SetWizardButtons(PSWIZB_NEXT);
	}
	else if( iActivePage == pPropertySheet->GetPageCount() - 1 )
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
	else
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
}

LRESULT CDlgCfgCommon::OnWizardNext() 
{
	SaveConfig();
	
	return CPropertyPage::OnWizardNext();
}

LRESULT CDlgCfgDefault::OnWizardNext() 
{
	SaveConfig();
	
	return CPropertyPage::OnWizardNext();
}

LRESULT CDlgCfgExtra::OnWizardNext() 
{
	SaveConfig();	

	return CPropertyPage::OnWizardNext();
}

BOOL CDlgCfgCommon::OnWizardFinish() 
{
	CCfg	*pConfiguration;

	SaveConfig();
	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;
	pConfiguration->Save();
	
	return CPropertyPage::OnWizardFinish();
}

BOOL CDlgCfgDefault::OnWizardFinish() 
{
	CCfg	*pConfiguration;

	SaveConfig();
	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;
	pConfiguration->Save();
	
	return CPropertyPage::OnWizardFinish();
}

BOOL CDlgCfgExtra::OnWizardFinish() 
{
	CCfg	*pConfiguration;

	SaveConfig();
	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;
	pConfiguration->Save();
	
	return CPropertyPage::OnWizardFinish();
}


