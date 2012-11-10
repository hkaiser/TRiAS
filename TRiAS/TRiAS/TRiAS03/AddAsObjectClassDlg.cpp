// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.01.2000 21:48:11
//
// @doc
// @module AddAsObjectClassDlg.cpp | Implementation of the <c CAddAsObjectClassDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include <eieruhr.hxx>
#include <AddAsClsPrp.h>
#include <ipropseq.hxx>
#include <funcs02.h>
#include <funcs03.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "AddAsObjectClass.h"
#include "AddAsObjectClassDlg.h"

/////////////////////////////////////////////////////////////////////////////
// externe Daten
extern char g_pDLLName[_MAX_PATH];		// dieser Modul

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(DataObject);
DefineSmartInterface(ObjectWithSite);
DefineSmartInterface(PropertyActionSequence);

/////////////////////////////////////////////////////////////////////////////
// CAddAsObjectClassDlg

CAddAsObjectClassDlg* CAddAsObjectClassDlg::CreateInstance (CAddAsObjectClass *pParent, LPCSTR pcCaption)
{
CAddAsObjectClassDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CAddAsObjectClassDlg(pParent, ResID(IDD, &RF), pcCaption);
		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CAddAsObjectClassDlg::CAddAsObjectClassDlg(CAddAsObjectClass *pParent, ResID uiDlg, LPCSTR pcCaption) 
	: CPropertyPage(uiDlg, pcCaption), m_pParent(pParent),
	  m_cbAddToView (this, IDC_ADDTOVIEW),
	  m_ftAdjustIdent (this, IDC_STATIC_SELECTIDENT),
	  m_cbAdjustIdent (this, IDC_CHECK_SELECTIDENT),
	  m_pbDefine (this, IDC_DEFINENEW)
{
	m_dwFlags = 0;
	m_pIdents = NULL;

	m_lResult = 0;			// ErgebnisIdent
	m_fAddToView = true;
}

CAddAsObjectClassDlg::~CAddAsObjectClassDlg()
{
	DELETE_OBJ (m_pIdents);
}

BOOL CAddAsObjectClassDlg::FInit (void)
{
// IdentifikatorListBox füllen
	m_pIdents = new CSelIdentListViewWindow (this, IDC_LISTDESTIDENTS);
	if (m_pIdents == NULL) 
		return FALSE;
	return TRUE;
}

void CAddAsObjectClassDlg::AdjustSheetButtons()
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

BOOL CAddAsObjectClassDlg::GetDisableNextPage()
{
// TODO: return TRUE, if 'Next >' - button should be disabled
	return (0 < (*m_pIdents) -> GetSelectedCount()) ? FALSE : TRUE;
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
HRESULT CAddAsObjectClassDlg::PrepareResult (void)
{
// Daten (Ident) aus Page lesen und speichern
bool fHasIdent = GetSelectedIdent (m_lResult);

	_ASSERTE(!fHasIdent || IsValidIdent(m_lResult));
	m_fAddToView = m_cbAddToView.isChecked() ? true : false;

// ProjektHandle der ausgewählten Datenquelle im KontextObjekt ablegen
	if (fHasIdent) {
		COM_TRY {
		WDataObject DO;
		WPropertyActionSequence Seq;

			THROW_FAILED_HRESULT(WObjectWithSite(m_pParent) -> GetSite (__uuidof(IPropertyActionSequence), Seq.ppv()));
			THROW_FAILED_HRESULT(Seq -> GetSequenceContext (DO.ppi()));

		CComVariant vData (reinterpret_cast<LONG>(HACTPROJECT), VT_I4);

			THROW_FAILED_HRESULT(SetVariantData (vData, DO, &c_feDataSourceHandle));

		} COM_CATCH_IGNORE;
	}
	return fHasIdent ? S_OK : S_FALSE;
}

bool CAddAsObjectClassDlg::GetSelectedIdent (long &rlIdent)
{
short iOTyp = 0;	// dummy

	if (m_pIdents) 
		return (*m_pIdents) -> GetFirstIdent (rlIdent, iOTyp);
		
	return false;
}

int CAddAsObjectClassDlg::GetItemCount (void)
{
	if (m_pIdents) 
		return (*m_pIdents) -> GetItemCount();
	return 0;
}

int CAddAsObjectClassDlg::SelectIdent (long lIdent, bool fSel)
{
	if (m_pIdents) {
	int fResult = (*m_pIdents) -> SelectIdent (lIdent, 0, fSel);

		AdjustSheetButtons();
		return fResult;
	} else if (fSel)
		m_lResult = lIdent;		// lediglich vormerken
		
	return -1;
}

/////////////////////////////////////////////////////////////////////////////
// CAddAsObjectClassDlg message handlers

void CAddAsObjectClassDlg::WindowInit (Event e)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// ListViewCtrl initialisieren/Identifikatoren laden
DWORD dwMode = SELIDMODE_NOICONS|SELIDMODE_ALLIDENTSPBD|SELIDMODE_ONLYWRITABLE;
int iTypes = OTPunkt|OTLinie|OTFlaeche|OTText;

	if (NULL == m_pIdents || !m_pIdents -> FInit() ||
		!(*m_pIdents) -> InitControl(iTypes, dwMode, NULL, CmpEntries, (DWORD)m_pIdents, EnsureUnique))
	{
		return;
	}
	
// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) {
	DWORD dwStyleEx = (*m_pIdents) -> GetExtendedStyle();

		(*m_pIdents) -> SetExtendedStyle (dwStyleEx | LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_INFOTIP);
	}
#endif 

// Mode voreinstellen: Text ist eingeblendet und Checkbox ist aus (alter Mode)
	m_ftAdjustIdent.FInit();
	m_ftAdjustIdent.Enable();
	m_ftAdjustIdent.Show();

	m_cbAdjustIdent.FInit();
	m_cbAdjustIdent.Disable();
	m_cbAdjustIdent.Hide();

	m_cbAddToView.FInit();
	m_cbAddToView.SetChecked (true);

	m_pbDefine.FInit();

// vorhergehende Einstellungen wieder einstellen
	if (0 != m_lResult) {
	int iIndex = SelectIdent (m_lResult);

		if (-1 != iIndex) {	// Focus setzen, ins Bild rollen
			(*m_pIdents) -> EnsureVisible (iIndex, false);
			(*m_pIdents) -> SelectItemFocus (iIndex);
		}
		m_cbAddToView.SetChecked (m_fAddToView);
	}
	AdjustSheetButtons();
}

int CAddAsObjectClassDlg::OnWizNext (NotifyEvt)
{
	if (SUCCEEDED(PrepareResult()))		// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

// Finish wurde gedrückt 
int CAddAsObjectClassDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult(); 					// Ergebnisse zwischenspeichern
	return 0;
}

int CAddAsObjectClassDlg::OnSetActive (NotifyEvt e)
{
	AdjustSheetButtons();
	return 0;
}

void CAddAsObjectClassDlg::OnItemChanged (NotifyEvt e)
{
NM_LISTVIEW *pNfyData = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (!(pNfyData -> uChanged & LVIF_STATE))
		return;		// Status nicht geändert

// Selektion erhalten/verloren
	if (pNfyData -> uOldState & LVIS_SELECTED ||
		pNfyData -> uNewState & LVIS_SELECTED)
	{
		AdjustSheetButtons();
	}
}

void CAddAsObjectClassDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_DEFINENEW:
		{
		DEFINEIDENTDLG DlgData;

			INITSTRUCT(DlgData, DEFINEIDENTDLG);
			DlgData.hWnd = Handle(API_WINDOW_HWND);
			DlgData.lIdent = 0;
			DlgData.hPr = HACTPROJECT;

		long lIdent = DEX_DefineNewObjectsDesc(DlgData);	// neue Identbeschreibung erzeugen

		// Daten neu einlesen, dazu ListViewCtrl initialisieren/Identifikatoren laden
			if (0 != lIdent) {
				_ASSERTE(NULL != m_pIdents);
				(*m_pIdents) -> FillWithData (true);
				(*m_pIdents) -> SelectIdent (lIdent, 0, true);
			}
		}
		break;

	default:
		break;
	}
}

void CAddAsObjectClassDlg::OnClick (NotifyEvt e)
{
NMHDR *pNMHdr = e.GetNotifyInfo();
POINT pt;

	GetCursorPos (&pt);
	ScreenToClient (pNMHdr -> hwndFrom, &pt);
	pt.x = 1;	// ganz am linken Rand testen

UINT uiFlags = 0L;
int iIndex = (*m_pIdents) -> HitTest ((Point &)pt, &uiFlags);

	if (uiFlags & LVHT_ONITEM && 0 <= iIndex) {
		(*m_pIdents) -> SetItemState (iIndex, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		(*m_pIdents) -> Update (iIndex);
	}
}

