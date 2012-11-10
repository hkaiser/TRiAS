// EDBS_CfgImpOBAK.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include <afxdlgs.h>
#include "Cfg.h"
#include "CfgDb.h"

#include "MetaData.h"
#include "EDBS_CfgImpOBAK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite EDBS_CfgImpOBAK 

IMPLEMENT_DYNCREATE(CEDBS_CfgImpOBAK, CPropertyPage)

CEDBS_CfgImpOBAK::CEDBS_CfgImpOBAK() : CPropertyPage(CEDBS_CfgImpOBAK::IDD)
{
	//{{AFX_DATA_INIT(CEDBS_CfgImpOBAK)
	m_strConfigDescription = _T("");
	m_tModifyRules = FALSE;
	m_tCreateBItext = FALSE;
	m_tImportVPKT = FALSE;
	//}}AFX_DATA_INIT
}

CEDBS_CfgImpOBAK::~CEDBS_CfgImpOBAK()
{
}

void CEDBS_CfgImpOBAK::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEDBS_CfgImpOBAK)
	DDX_Control(pDX, IDC_SEP3, m_Sep3);
	DDX_Control(pDX, IDC_SEP2, m_Sep2);
	DDX_Control(pDX, IDC_SEP1, m_Sep1);
	DDX_Control(pDX, IDC_CONFIGURATIONS, m_cbbConfigurations);
	DDX_Text(pDX, IDC_CFGDESCRIPTION, m_strConfigDescription);
	DDX_Check(pDX, IDC_CREATEBITEXT, m_tCreateBItext);
	DDX_Check(pDX, IDC_IMPORTVPKT, m_tImportVPKT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEDBS_CfgImpOBAK, CPropertyPage)
	//{{AFX_MSG_MAP(CEDBS_CfgImpOBAK)
	ON_CBN_SELCHANGE(IDC_CONFIGURATIONS, OnSelchangeConfigurations)
	ON_BN_CLICKED(IDC_CREATEBITEXT, OnClickCreateBItext)
	ON_BN_CLICKED(IDC_IMPORTVPKT, OnClickImportVPKT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten EDBS_CfgImpOBAK 

BOOL CEDBS_CfgImpOBAK::OnSetActive() 
{
	CCfgDb	*pCfgDb, *pCfgDbDefault;
	int idx, idxDefault;

	for( idx = 0; idx < m_cbbConfigurations.GetCount(); idx++ ) {
		pCfgDb = (CCfgDb*)m_cbbConfigurations.GetItemDataPtr( idx );
		if( pCfgDb->m_strConfigFile == m_pConfiguration->m_strConfigFile )
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

	if( m_cbbConfigurations.GetCount() <= 1 )
		m_cbbConfigurations.EnableWindow(FALSE);
	else
		m_cbbConfigurations.EnableWindow(TRUE);

	OnSelchangeConfigurations();

	return CPropertyPage::OnSetActive();
}

void CEDBS_CfgImpOBAK::OnSelchangeConfigurations() 
{
	CCfgDb* pCfgDb;
//	CPropertySheet* pPropertySheet;   
//	int iNextPage;

	pCfgDb = (CCfgDb*)m_cbbConfigurations.GetItemDataPtr(m_cbbConfigurations.GetCurSel());
	m_strConfigDescription = pCfgDb->m_strConfigDescription;

	m_pConfiguration->m_strConfigFile = pCfgDb->m_strConfigFile;

	m_tModifyRules = (m_pConfiguration->m_strConfigFile != "Default") && (pCfgDb->m_strShowCfgPage == "ja");
/*
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
*/
	UpdateData(false);
	SetModified(true);
	SetWizardButtons();
}

void CEDBS_CfgImpOBAK::LoadConfig()
{
	POSITION	pos;
	CString		key;
	CCfgDb		*pCfgDb;
	int			idx;
	
	m_tCreateBItext = m_pConfiguration->m_tCreateBItext;
	m_tImportVPKT = m_pConfiguration->m_tImportVPKT;

	m_pConfiguration->LoadCfgDbs();

	for ( pos = m_pConfiguration->m_CfgDbs.GetStartPosition(); pos != NULL; ) {
		m_pConfiguration->m_CfgDbs.GetNextAssoc( pos, key, (CObject*&)pCfgDb );
		idx = m_cbbConfigurations.AddString( pCfgDb->m_strConfigName );
		m_cbbConfigurations.SetItemDataPtr( idx, (void*)pCfgDb );
	}

	UpdateData(false);

}

void CEDBS_CfgImpOBAK::SaveConfig()
{
	CCfgDb* pCfgDb;

	m_pConfiguration->m_tCreateBItext = m_tCreateBItext;
	m_pConfiguration->m_tImportVPKT = m_tImportVPKT;

	pCfgDb = (CCfgDb*)m_cbbConfigurations.GetItemDataPtr(m_cbbConfigurations.GetCurSel());
	m_pConfiguration->m_strConfigFile = pCfgDb->m_strConfigFile;

}

void CEDBS_CfgImpOBAK::SetWizardButtons()
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
	if( m_tModifyRules )
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
	else
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

}

BOOL CEDBS_CfgImpOBAK::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	LoadConfig();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

/*
void CEDBS_CfgImpOBAK::OnClickModifyrules() 
{
	CPropertySheet* pPropertySheet = (CPropertySheet*) GetParent();   
	pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
	m_tModifyRules = !m_tModifyRules;
	SetModified(true);
	UpdateData( FALSE );

	SetWizardButtons();
}
*/

void CEDBS_CfgImpOBAK::Load_OBAK()
{
	CRule_Layer	*pRule_Layer;

	if( g_pMetaData ) {
		delete g_pMetaData;
		g_pMetaData = NULL;
	}
	g_pMetaData = new CMetaData;
	g_pMetaData->Load();

	if( m_pConfiguration->m_tImportVPKT ) {
		pRule_Layer = g_pMetaData->GetRule_Layer(CString("050"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 255;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("051"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 255;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("052"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 255;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("053"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 255;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("054"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 255;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("059"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 255;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("085"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 255;
	}
	else {
		pRule_Layer = g_pMetaData->GetRule_Layer(CString("050"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 0;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("051"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 0;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("052"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 0;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("053"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 0;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("054"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 0;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("059"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 0;

		pRule_Layer = g_pMetaData->GetRule_Layer(CString("085"), FALSE);
		if (NULL != pRule_Layer) pRule_Layer->ImportMode() = 0;
	}
}

LRESULT CEDBS_CfgImpOBAK::OnWizardNext() 
{
	SaveConfig();
	Load_OBAK();
	return CPropertyPage::OnWizardNext();
}

BOOL CEDBS_CfgImpOBAK::OnWizardFinish() 
{
	SaveConfig();
//	m_pConfiguration->Save(); 
//  Hier konnte noch nichts verändert werden.
	Load_OBAK();
	return CPropertyPage::OnWizardFinish();
}

void CEDBS_CfgImpOBAK::OnClickCreateBItext() 
{
	m_tCreateBItext = !m_tCreateBItext;
	SetModified(true);
	UpdateData( FALSE );
}

void CEDBS_CfgImpOBAK::OnClickImportVPKT() 
{
	m_tImportVPKT = !m_tImportVPKT;
	SetModified(true);
	UpdateData( FALSE );
	
}

