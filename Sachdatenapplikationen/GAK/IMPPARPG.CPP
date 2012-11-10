// ImpParPg.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "importty.h"	// CImportParams
#include "ImpParPg.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportParamPage property page
IMPLEMENT_DYNCREATE(CImportParamPage, CPropertyPage)

CImportParamPage::CImportParamPage() : CPropertyPage(CImportParamPage::IDD)
{
	//{{AFX_DATA_INIT(CImportParamPage)
	//}}AFX_DATA_INIT
	m_pParams = NULL;
}

CImportParamPage::~CImportParamPage()
{
}

void CImportParamPage::SetParams (CImportParams &Params)
{
	m_pParams = &Params;
}

void CImportParamPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportParamPage)
	DDX_Control(pDX, IDB_ALWAYS_INDEX, m_btActIndex);
	DDX_Control(pDX, IDB_ALL_RECORDS, m_btAllRecords);
	DDX_Control(pDX, IDB_ALWAYS_MOD, m_btAlwaysMod);
	DDX_Control(pDX, IDB_ONLY_REFERENZ, m_btOnlyWithRef);
	DDX_Control(pDX, IDB_ONLY_NOT_REFERENZ, m_btOnlyWithoutRef);
	DDX_Control(pDX, IDB_NEVER_MOD, m_btNeverMod);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImportParamPage, CPropertyPage)
	//{{AFX_MSG_MAP(CImportParamPage)
	ON_BN_CLICKED(IDB_ALL_RECORDS, OnAllRecords)
	ON_BN_CLICKED(IDB_ALWAYS_MOD, OnAlwaysMod)
	ON_BN_CLICKED(IDB_NEVER_MOD, OnNeverMod)
	ON_BN_CLICKED(IDB_ONLY_NOT_REFERENZ, OnOnlyNotReferenz)
	ON_BN_CLICKED(IDB_ONLY_REFERENZ, OnOnlyReferenz)
	ON_BN_CLICKED(IDB_ALWAYS_INDEX, OnAlwaysIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportParamPage message handlers

BOOL CImportParamPage::OnSetActive() 
{
//	TODO: Add your specialized code here and/or call the base class
	GetParent () -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);

//	1. Spezialfall: keine Datensätze im Ausgabeset (z.B. Tabelle neu erstellt)
	ASSERT (NULL != m_pParams);
	ASSERT (m_pParams->m_DestSet.IsOpen ());
	if (m_pParams->m_DestSet.IsBOF ())
	{
	//	Voreinstellung überschreiben
		m_pParams -> m_pTableInfo -> m_tMenge = AllRecords;
		m_pParams -> m_pTableInfo -> m_tActual = Never;

		m_btAllRecords.EnableWindow (TRUE);
		m_btAllRecords.SetCheck (1);
		m_btNeverMod.EnableWindow (TRUE);
		m_btNeverMod.SetCheck (1);	
		m_btOnlyWithRef.ShowWindow (SW_HIDE);
		m_btOnlyWithoutRef.ShowWindow (SW_HIDE);
		m_btAlwaysMod.ShowWindow (SW_HIDE);
		m_btActIndex.ShowWindow (SW_HIDE);
	}				
	else
	{
	//	nur mögliche Aktionen zulassen: Menge
		UINT uiSelFlag = m_pParams -> m_pTableInfo -> SelectFlag ();
		UINT uiActFlag = m_pParams -> m_pTableInfo -> ActFlag ();

		m_btAllRecords.ShowWindow (uiSelFlag & AllRecords ? SW_NORMAL : SW_HIDE);
		m_btOnlyWithRef.ShowWindow (uiSelFlag & OnlyRefRecords ? SW_NORMAL : SW_HIDE);
		m_btOnlyWithoutRef.ShowWindow (uiSelFlag & OnlyNotRefRecords ? SW_NORMAL : SW_HIDE);

	//	Aktualisierung	
		m_btAlwaysMod.ShowWindow (uiActFlag & Always ? SW_NORMAL : SW_HIDE);
		m_btNeverMod.ShowWindow (uiActFlag & Never ? SW_NORMAL : SW_HIDE);
		m_btActIndex.ShowWindow (uiActFlag & Index ? SW_NORMAL : SW_HIDE);

	//	Voreinstellung setzen: Menge
		if (uiSelFlag & Always)
			m_btAllRecords.SetCheck (AllRecords == m_pParams -> m_pTableInfo -> m_tMenge);
		if (uiSelFlag & OnlyRefRecords)
			m_btOnlyWithRef.SetCheck (OnlyRefRecords == m_pParams -> m_pTableInfo -> m_tMenge);
		if (uiSelFlag & OnlyNotRefRecords)
			m_btOnlyWithoutRef.SetCheck (OnlyNotRefRecords == m_pParams -> m_pTableInfo -> m_tMenge);

	//	Voreinstellung setzen: Aktualisierung
		if (uiActFlag & Always)
			m_btAlwaysMod.SetCheck (Always == m_pParams -> m_pTableInfo -> m_tActual);
		if (uiActFlag & Never)
			m_btNeverMod.SetCheck (Never == m_pParams -> m_pTableInfo -> m_tActual);
		if (uiActFlag & Index)
			m_btActIndex.SetCheck (Index == m_pParams -> m_pTableInfo -> m_tActual);
	}

	return CPropertyPage::OnSetActive();
}

//	alle Datensätze
void CImportParamPage::OnAllRecords() 
{
	ASSERT (NULL != m_pParams);
	ASSERT (NULL != m_pParams -> m_pTableInfo);
	m_pParams -> m_pTableInfo -> m_tMenge = AllRecords;
}

//	Datensätze mit Referenz
void CImportParamPage::OnOnlyReferenz() 
{
	ASSERT (NULL != m_pParams);
	ASSERT (NULL != m_pParams -> m_pTableInfo);	
	m_pParams -> m_pTableInfo -> m_tMenge = OnlyRefRecords;

	if (m_btNeverMod.IsWindowVisible () && m_btNeverMod.GetCheck () == 1)
	{
	//	unmöglicher Zustand
		m_btNeverMod.SetCheck (0);

		if (m_btActIndex.IsWindowVisible ())
		{
			m_btActIndex.SetCheck (1);
			m_pParams -> m_pTableInfo -> m_tActual = Index;
		}
		else
		{
			m_btAlwaysMod.SetCheck (1);
			m_pParams -> m_pTableInfo -> m_tActual = Always; 
		}
	}
}

//	Datensätze ohne Referenz
void CImportParamPage::OnOnlyNotReferenz() 
{
	ASSERT (NULL != m_pParams);
	ASSERT (NULL != m_pParams -> m_pTableInfo);	
	m_pParams -> m_pTableInfo -> m_tMenge = OnlyNotRefRecords;

	if (m_btNeverMod.IsWindowVisible () && m_btNeverMod.GetCheck () == 0)
	{
	//	unmöglicher Zustand
		m_btNeverMod.SetCheck (1);
		m_pParams -> m_pTableInfo -> m_tActual = Never;

		if (m_btActIndex.IsWindowVisible ())
			m_btActIndex.SetCheck (0);
		if (m_btAlwaysMod.IsWindowVisible ())
			m_btAlwaysMod.SetCheck (0);
	}
}

//	Aktualisierung über Indexsuche
void CImportParamPage::OnAlwaysIndex() 
{
	ASSERT (NULL != m_pParams);
	ASSERT (NULL != m_pParams -> m_pTableInfo);	
	m_pParams -> m_pTableInfo -> m_tActual = Index;

	if (m_btOnlyWithoutRef.IsWindowVisible () && m_btOnlyWithoutRef.GetCheck () == 1)
	{
	//	unmöglicher Zustand
		m_btOnlyWithoutRef.SetCheck (0);

		if (m_btOnlyWithRef.IsWindowVisible ())
		{
			m_btOnlyWithRef.SetCheck (1);
			m_pParams -> m_pTableInfo -> m_tMenge = OnlyRefRecords;					
		}
		else
		{
			m_btAllRecords.SetCheck (1);
			m_pParams -> m_pTableInfo -> m_tMenge = AllRecords;
		}
	}
}

//	Akt. über seq. Suche
void CImportParamPage::OnAlwaysMod() 
{
	ASSERT (NULL != m_pParams);
	ASSERT (NULL != m_pParams -> m_pTableInfo);	
	m_pParams -> m_pTableInfo -> m_tActual = Always; 

	if (m_btOnlyWithoutRef.IsWindowVisible () && m_btOnlyWithoutRef.GetCheck () == 1)
	{
	//	unmöglicher Zustand
		m_btOnlyWithoutRef.SetCheck (0);

		if (m_btOnlyWithRef.IsWindowVisible ())
		{
			m_btOnlyWithRef.SetCheck (1);
			m_pParams -> m_pTableInfo -> m_tMenge = OnlyRefRecords;					
		}
		else
		{
			m_btAllRecords.SetCheck (1);
			m_pParams -> m_pTableInfo -> m_tMenge = AllRecords;
		}
	}
}

//	Anhängen
void CImportParamPage::OnNeverMod() 
{
	ASSERT (NULL != m_pParams);
	ASSERT (NULL != m_pParams -> m_pTableInfo);	
	m_pParams -> m_pTableInfo -> m_tActual = Never;

	if (m_btOnlyWithRef.IsWindowVisible () && m_btOnlyWithRef.GetCheck () == 1)
	{
	//	unmöglicher Zustand
		m_btOnlyWithRef.SetCheck (0);

		if (m_btOnlyWithoutRef.IsWindowVisible ())
		{
			m_btOnlyWithoutRef.SetCheck (1);
			m_pParams -> m_pTableInfo -> m_tMenge = OnlyNotRefRecords;
		}
		else
		{
			m_btAllRecords.SetCheck (1);
			m_pParams -> m_pTableInfo -> m_tMenge = AllRecords;					
		}
	}
}



