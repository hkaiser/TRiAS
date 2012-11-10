// ImpSumPg.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp u. Ressourcen
#include "importty.h"		// CImportParams
#include "ImpSumPg.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportSumPage property page

IMPLEMENT_DYNCREATE(CImportSumPage, CPropertyPage)

CImportSumPage::CImportSumPage() : CPropertyPage(CImportSumPage::IDD)
{
	//{{AFX_DATA_INIT(CImportSumPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParams = NULL;
}

CImportSumPage::~CImportSumPage()
{
}

void CImportSumPage::SetParams (CImportParams &Params)
{
	m_pParams = &Params;
}

void CImportSumPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportSumPage)
	DDX_Control(pDX, IDS_AS_NEW_TABLE, m_stAsNewTable);
	DDX_Control(pDX, IDS_TABLE_INFO, m_stTableKind);
	DDX_Control(pDX, IDS_SELECTED, m_stSelected);
	DDX_Control(pDX, IDS_OUTPUT_TABLE, m_stOutputTable);
	DDX_Control(pDX, IDS_OUTPUT_DATABASE, m_stOutputDatabase);
	DDX_Control(pDX, IDS_INPUT_TABLE, m_stInputTable);
	DDX_Control(pDX, IDS_INPUT_DATABASE, m_stInputDatabase);
	DDX_Control(pDX, IDS_ACTUAL, m_stAtcual);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportSumPage, CPropertyPage)
	//{{AFX_MSG_MAP(CImportSumPage)
		ON_COMMAND(ID_HELP, OnHelp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportSumPage message handlers

BOOL CImportSumPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetParent () -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);	

	ASSERT (NULL != m_pParams);
	ASSERT (NULL != m_pParams -> m_pTableInfo);

//	Infos ausgeben
	m_stInputDatabase.SetWindowText (m_pParams -> m_SourceSet.m_pDatabase -> GetName ());
	m_stOutputDatabase.SetWindowText (m_pParams -> m_DestSet.m_pDatabase -> GetName ());
	m_stInputTable.SetWindowText (m_pParams -> m_strInputTableName);
	m_stOutputTable.SetWindowText (m_pParams -> m_strOutputTableName);
	m_stTableKind.SetWindowText (m_pParams -> m_pTableInfo -> TableName ());

//	Art der Datensatz-Selektion ausgeben
	CString strInfo;
	switch (m_pParams -> m_pTableInfo -> m_tMenge)
	{
		case AllRecords:
			VERIFY (strInfo.LoadString (IDS_IMPORT_ALL_RECORDS));
		break;
		case OnlyRefRecords:
			VERIFY (strInfo.LoadString (IDS_IMPORT_ONLY_REF));
		break;
		case OnlyNotRefRecords:
			VERIFY (strInfo.LoadString (IDS_IMPORT_WITHOUT_REF));
		break;
		default:
			ASSERT (FALSE);
	};
	m_stSelected.SetWindowText (strInfo);

//	Art der Datensatz-Aktualisierung ausgeben
	switch (m_pParams -> m_pTableInfo -> m_tActual)
	{
		case Always:
			VERIFY (strInfo.LoadString (IDS_ACTUAL_AUTOMATIC));
		break;
		case Index:
			VERIFY (strInfo.LoadString (IDS_AUTOMATIC_INDEX));
		break;
		case Never:
			VERIFY (strInfo.LoadString (IDS_ACTUAL_NEVER));
		break;
		default:
			ASSERT (FALSE);
	};
	m_stAtcual.SetWindowText (strInfo);

	if (m_pParams->m_bAsNewTable)
	{		
		VERIFY (strInfo.LoadString (IDS_AS_NEW_TABLE));
		m_stAsNewTable.SetWindowText (strInfo);
	}
		
	return CPropertyPage::OnSetActive();
}

void CImportSumPage :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}
