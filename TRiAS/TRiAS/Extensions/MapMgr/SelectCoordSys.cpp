// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.10.2002 21:04:22 
//
// @doc
// @module SelectCoordSys.cpp | Definition of the <c CSelectCoordSys> class

#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectCoordSys property page

IMPLEMENT_DYNCREATE(CSelectCoordSys, CPropertyPage)

CSelectCoordSys::CSelectCoordSys() : 
	CPropertyPage(CSelectCoordSys::IDD)
{
	//{{AFX_DATA_INIT(CSelectCoordSys)
	//}}AFX_DATA_INIT

	m_fIsLast = false;
	m_fNotEmpty = false;
}

CSelectCoordSys::~CSelectCoordSys()
{
}

void CSelectCoordSys::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectCoordSys)
	DDX_Control(pDX, IDC_DESCTEXT, m_ftDescText);
	DDX_Control(pDX, IDC_COORDDESCRIPTION, m_ftDescription);
	DDX_Control(pDX, IDC_COORDSYSTEMS, m_tvCoordSystems);
	//}}AFX_DATA_MAP
}

void CSelectCoordSys::AdjustButtons(HTREEITEM hItem)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();
DWORD dwBttns = PSWIZB_BACK;

	_ASSERTE(NULL != pSheet);
	m_pParent->m_nNextStep = 0;
	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (NULL != pItemData) {
			if (!m_fIsLast) {
				m_pParent->m_nNextStep = CPpgSelDataSource::IDD;
				dwBttns |= PSWIZB_NEXT;
			}
			else 
				dwBttns |= PSWIZB_FINISH;
		}
		else if (m_fIsLast)
			dwBttns |= PSWIZB_DISABLEDFINISH;
	} 
	else if (m_fIsLast)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons (dwBttns);
}

void CSelectCoordSys::SetDescription (HTREEITEM hItem)
{
	if (NULL == hItem)
		hItem = m_tvCoordSystems.GetSelectedItem();
	_ASSERTE(!m_fNotEmpty || NULL != hItem);

	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (NULL == pItemData) 
			m_ftDescription.SetWindowText ("");
		else 
			m_ftDescription.SetWindowText (pItemData -> GetDesc());
	} 
	AdjustButtons(hItem);
}

bool CSelectCoordSys::PrepareResult()
{
// Selektierten Eintrag holen
HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL == hItem || m_tvCoordSystems.ItemHasChildren (hItem)) 
		return false;		// nur Childs behandeln

CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

	if (NULL == pItemData) 
		return false;

// Koordinatensystem am Parent setzen
CString strTcfName = pItemData->GetTcfName();

	COM_TRY {
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> CS;

		THROW_FAILED_HRESULT(CS.CoCreateInstance(CLSID_TRIASCS));
		THROW_FAILED_HRESULT(CS -> LoadFromFile(CComBSTR(strTcfName)));
		m_pParent->m_pCS = CS;
		THROW_FAILED_HRESULT(m_pParent->m_pTopoMap->PutCoordSystem(CS));

	} COM_CATCH_RETURN(false);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// 
BEGIN_MESSAGE_MAP(CSelectCoordSys, CPropertyPage)
	//{{AFX_MSG_MAP(CSelectCoordSys)
	ON_NOTIFY(NM_DBLCLK, IDC_COORDSYSTEMS, OnDblclkCoordSystems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectCoordSys message handlers

BOOL CSelectCoordSys::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
// TreeControl/Imagelist initialisieren
	m_tvCoordSystems.InitTreeCrtl (this);

// Koordinatensysteme einlesen
	m_fNotEmpty = m_tvCoordSystems.InitCoordSystemsFromRegistry();
	m_tvCoordSystems.SetFocus();

	SetDescription();
	AdjustButtons(m_tvCoordSystems.GetSelectedItem());
	UpdateData (FALSE);

	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectCoordSys::UpdateControls()
{
	SetDescription();
	AdjustButtons(m_tvCoordSystems.GetSelectedItem());

	UpdateData(FALSE);
}

void CSelectCoordSys::OnDblclkCoordSystems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (NULL != pItemData) {
		// nur, wenn leaf selektiert wurde
		CPropertySheet *pSheet = (CPropertySheet *)GetParent();

			_ASSERTE(NULL != pSheet);
			pSheet -> PressButton (m_fIsLast ? PSBTN_FINISH : PSBTN_NEXT);
		}
	}
}

LRESULT CSelectCoordSys::OnWizardNext() 
{
	_ASSERTE(!m_fIsLast);			// darf nicht letztes Fenster sein
	if (!PrepareResult())
		return 0;

	return CPropertyPage::OnWizardNext();
}

BOOL CSelectCoordSys::OnWizardFinish() 
{
	_ASSERTE(m_fIsLast);			// muﬂ letztes Fenster sein
	if (!PrepareResult())
		return FALSE;

	return CPropertyPage::OnWizardFinish();
}

