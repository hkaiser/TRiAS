// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.10.2000 19:50:54 
//
// @doc
// @module GenerateObjectPropertiesDlg.cpp | Definition of the 
// <c CGenerateObjectPropertiesSequenceDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include <eieruhr.hxx>
#include <SelObjProp.h>
#include <TrCatIds.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DataHelp.h"
#include "GenerateObjectProperties.h"
#include "GenerateObjectPropertiesSequenceDlg.h"

///////////////////////////////////////////////////////////////////////////////
// 
extern TCHAR g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// CGenerateObjectPropertiesSequenceDlg

CGenerateObjectPropertiesSequenceDlg* CGenerateObjectPropertiesSequenceDlg::CreateInstance (
	CGenerateObjectProperties *pParent, LPCSTR pcCaption)
{
CGenerateObjectPropertiesSequenceDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CGenerateObjectPropertiesSequenceDlg(pParent, ResID(IDD, &RF), pcCaption);
		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CGenerateObjectPropertiesSequenceDlg::CGenerateObjectPropertiesSequenceDlg(
		CGenerateObjectProperties *pParent, ResID uiResID, LPCSTR pcCaption) :
	CPropertyPage(uiResID, pcCaption), 
	m_pParent(pParent),
	m_lstProps(this, IDC_PROPERTY_SEQUENCE),
	m_pbUp(this, IDC_UP),
	m_pbDown(this, IDC_DOWN)
{
	m_dwFlags = 0;
}

CGenerateObjectPropertiesSequenceDlg::~CGenerateObjectPropertiesSequenceDlg()
{
}

BOOL CGenerateObjectPropertiesSequenceDlg::FInit (void)
{
	return TRUE;
}

void CGenerateObjectPropertiesSequenceDlg::AdjustSheetButtons()
{
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	SetSheetWizardButtons(dwBttns);
}

BOOL CGenerateObjectPropertiesSequenceDlg::GetDisableNextPage()
{
	if (0 == m_lstProps.GetItemCount())
		return TRUE;
	return FALSE;
}

HRESULT CGenerateObjectPropertiesSequenceDlg::PrepareResult (void)
{
	m_lstObjProps.clear();
	return m_lstProps.GetObjectProperties(m_lstObjProps) ? S_OK : E_FAIL;
}

bool CGenerateObjectPropertiesSequenceDlg::FillListWithProps()
{
CEierUhr Wait (this);		// EierUhr anzeigen
list<os_string> lstStrs;

	if (!m_pParent -> GetSelectedProps (lstStrs))
		return false;

	return m_lstProps.FillWithItems(lstStrs);
}

/////////////////////////////////////////////////////////////////////////////
// CGenerateObjectPropertiesSequenceDlg message handlers

void CGenerateObjectPropertiesSequenceDlg::WindowInit (Event e)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// Liste der vorher ausgewählten Objekteigenschaften initialisieren
// Liste der Objekteigenschaften initialisieren
WObjectProps ObjProps;
BOOL fMustReInit = DEX_GetObjectProps (ObjProps.ppi());

	if (ObjProps.IsValid()) {
	// evtl. alle ObjProps installieren
		if (fMustReInit) {
			ObjProps -> OnNewReferenceObject (-1L);	// alles bisherige löschen
			if (FAILED(ObjProps -> OnNewReferenceObject (0L))) 
				return;
			DEX_SetMustInitOPFs(FALSE);
		}
	}
	if (!m_lstProps.InitControl(ObjProps) || !FillListWithProps())
		return;
		
// OwnerDraw Knöpfe initialisieren
	if (!m_pbUp.FInit() || !m_pbDown.FInit())
		return;
		
	if (m_pbUp.LoadBitmaps (IDB_UP, IDB_UP_SEL, IDB_UP_FOCUS, IDB_UP_DISABLED))
		m_pbUp.SizeToContent(); 
	if (m_pbDown.LoadBitmaps (IDB_DOWN, IDB_DOWN_SEL, IDB_DOWN_FOCUS, IDB_DOWN_DISABLED))
		m_pbDown.SizeToContent(); 

	AdjustSheetButtons();
}

int CGenerateObjectPropertiesSequenceDlg::OnWizNext (NotifyEvt)
{
	if (SUCCEEDED(PrepareResult()))		// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

// Finish wurde gedrückt 
int CGenerateObjectPropertiesSequenceDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult(); 					// Ergebnisse zwischenspeichern
	return 0;
}

int CGenerateObjectPropertiesSequenceDlg::OnSetActive (NotifyEvt e)
{
	FillListWithProps();
	AdjustSheetButtons();
	return 0;
}

void CGenerateObjectPropertiesSequenceDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_UP:
		m_lstProps.MoveItemUp();
		break;

	case IDC_DOWN:
		m_lstProps.MoveItemDown();
		break;
	}
}

