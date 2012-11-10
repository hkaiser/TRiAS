// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 02.05.2004 19:36:09
//
// @doc
// @module SelectCoordSysActionDlg.cpp | Implementation of the <c CSelectCoordSysActionDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include "SelectCoordSysActionDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectCoordSysActionDlg

CSelectCoordSysActionDlg * 
CSelectCoordSysActionDlg::CreateInstance (UINT uiDlg, LPCSTR pcCaption, 
	ResourceFile &rRF)
{
CSelectCoordSysActionDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CSelectCoordSysActionDlg(ResID (uiDlg, &rRF), pcCaption);

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CSelectCoordSysActionDlg::CSelectCoordSysActionDlg(ResID uiId, LPCSTR pcCaption) 
:	CPropertyPage(uiId, pcCaption),
	m_ftDescription(this, IDC_COORDDESCRIPTION),
	m_tvCoordSystems(this, IDC_COORDSYSTEMS)
{
	m_uiNextPage = 0;
	m_dwFlags = 0;
	m_fNotEmpty = false;
}

CSelectCoordSysActionDlg::~CSelectCoordSysActionDlg()
{
}

void CSelectCoordSysActionDlg::AdjustSheetButtons(HTREEITEM hItem)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	_ASSERTE(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage(hItem)) {
		if ((m_dwFlags & ADDPAGES_LASTPAGE) && 0 == m_uiNextPage)
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if ((m_dwFlags & ADDPAGES_LASTPAGE) && 0 == m_uiNextPage)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons(dwBttns);
}

BOOL CSelectCoordSysActionDlg::GetDisableNextPage(HTREEITEM hItem)
{
	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		return (NULL != pItemData) ? FALSE : TRUE;
	}
	return FALSE;
}

void CSelectCoordSysActionDlg::SetDescription (HTREEITEM hItem)
{
	if (NULL == hItem)
		hItem = m_tvCoordSystems.GetSelectedItem();
	_ASSERTE(!m_fNotEmpty || NULL != hItem);

	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (NULL == pItemData) 
			m_ftDescription.SetText ("");
		else 
			m_ftDescription.SetText (pItemData -> GetDesc().c_str());
	} 
	AdjustSheetButtons(hItem);
}

bool CSelectCoordSysActionDlg::PrepareResult()
{
// Selektierten Eintrag holen
HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL == hItem || m_tvCoordSystems.ItemHasChildren (hItem)) 
		return false;		// nur Childs behandeln

CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

	if (NULL == pItemData) 
		return false;

// Koordinatensystem am Parent setzen
os_string strTcfName = pItemData->GetTcfName();

	COM_TRY {
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> CS;

		THROW_FAILED_HRESULT(CS.CoCreateInstance(CLSID_TRIASCS));
		THROW_FAILED_HRESULT(CS -> LoadFromFile(CComBSTR(strTcfName.c_str())));

		m_CS = CS;		// store result coordsystem

	} COM_CATCH_RETURN(false);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CSelectCoordSysActionDlg message handlers

void CSelectCoordSysActionDlg::WindowInit(Event) 
{
	m_ftDescription.FInit();
	m_tvCoordSystems.FInit();

// TreeControl/Imagelist initialisieren
	m_tvCoordSystems.InitTreeCrtl (this);

// Koordinatensysteme einlesen
	m_fNotEmpty = m_tvCoordSystems.InitCoordSystemsFromRegistry();
	m_tvCoordSystems.SetFocus();

	SetDescription();
	AdjustSheetButtons(m_tvCoordSystems.GetSelectedItem());
}

int CSelectCoordSysActionDlg::OnSetActive(NotifyEvt) 
{
	AdjustSheetButtons(m_tvCoordSystems.GetSelectedItem());
	return 0;
}

void CSelectCoordSysActionDlg::OnDblClick (NotifyEvt e)
{
NMHDR *pNMHDR = e.GetNotifyInfo();

	if (IDC_COORDSYSTEMS == pNMHDR->idFrom) {
	HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

		if (NULL != hItem) {
		CCoordSystemItem *pItemData = 
			(CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

			if (NULL != pItemData) {
			// nur, wenn leaf selektiert wurde
			CPropertySheet *pSheet = (CPropertySheet *)GetParent();

				_ASSERTE(NULL != pSheet);
				pSheet -> PressButton ((m_dwFlags & ADDPAGES_LASTPAGE) ? 
					PSBTN_FINISH : PSBTN_NEXT);
			}
		}
	}
}

void CSelectCoordSysActionDlg::OnDeleteItem (NotifyEvt e)
{
NMHDR *pNMHDR = e.GetNotifyInfo();

	if (IDC_COORDSYSTEMS == pNMHDR->idFrom) 
		m_tvCoordSystems.OnDeleteCoordSystemItem(pNMHDR);
}

void CSelectCoordSysActionDlg::OnSelChanged (NotifyEvt e)
{
NMHDR *pNMHDR = e.GetNotifyInfo();

	if (IDC_COORDSYSTEMS == pNMHDR->idFrom) 
		m_tvCoordSystems.OnSelchanged(pNMHDR);
}

void CSelectCoordSysActionDlg::OnItemExpanded (NotifyEvt e)
{
NMHDR *pNMHDR = e.GetNotifyInfo();

	if (IDC_COORDSYSTEMS == pNMHDR->idFrom) 
		m_tvCoordSystems.OnItemExpanded(pNMHDR);
}

int CSelectCoordSysActionDlg::OnWizNext (NotifyEvt)
{
	_ASSERTE(!(m_dwFlags & ADDPAGES_LASTPAGE) || 0 != m_uiNextPage);		// darf nicht letztes Fenster sein
	if (!PrepareResult())
		return 0;

	return m_uiNextPage;
}

int CSelectCoordSysActionDlg::OnWizFinish (NotifyEvt)
{
	_ASSERTE(m_dwFlags & ADDPAGES_LASTPAGE);		// muﬂ letztes Fenster sein
	if (!PrepareResult())
		return FALSE;

	return 0;
}

