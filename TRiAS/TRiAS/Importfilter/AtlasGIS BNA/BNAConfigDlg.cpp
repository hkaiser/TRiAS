// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser All rights reserved
// Created: 22.04.2002 20:21:06 
//
// @doc
// @module BNAConfigDlg.cpp | Definition of the <c CBNAConfigDlg> class

#include "bnaimpp.hpp"

#include <errinstx.hxx>
#include <xtensnn.h>
#include <Esnecil.h>

#include "BNAConfigDlg.h"
#include "BNAImportConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CBNAConfigDlg

/*static*/
CBNAConfigDlg *CBNAConfigDlg::CreateInstance(LPCSTR pcCaption, CBNAImportConfig *pBack)
{
CBNAConfigDlg *pDlg = NULL;

	COM_TRY {
	// Dialog neu anlegen
	ResourceFile RF (g_pDLLName);

		pDlg = new CBNAConfigDlg(ResID(IDD, &RF), 
			pcCaption, pBack);
		if (NULL == pDlg || !pDlg->FInit()) {
			DELETE_OBJ(pDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pDlg, NULL);
	return pDlg;
}

CBNAConfigDlg::CBNAConfigDlg(ResID uiDlg, LPCSTR pcCaption, CBNAImportConfig *pBack) :
	CPropertyPage(uiDlg, pcCaption),
	m_lvAssocLayers(this, IDC_LAYERS_AND_CLASSES),
	m_pbNewClass(this, IDC_DEFINENEW),
	m_pbCopyClass(this, IDC_COPYCLASS),
	m_pBack(pBack),
	m_fGcoProduction(false)
{
}

CBNAConfigDlg::~CBNAConfigDlg()
{
}

///////////////////////////////////////////////////////////////////////////////
// MessageHandler
extern TR_LayerTree *g_OKSTree;			// globaler Baum der OKS

void CBNAConfigDlg::WindowInit(Event e)
{
CEsnecil esnecil;

	m_fGcoProduction = esnecil.VerifyOptions(CKIOPTION_GCOPRODUCTION);
	if (m_fGcoProduction && QMSysAdmin & DEX_QueryMode())
		m_fGcoProduction = false;

	m_lvAssocLayers.FInit(g_OKSTree, m_pBack->GetContextHandle(), m_fGcoProduction);
	m_pbNewClass.FInit();
	m_pbCopyClass.FInit();

	if (m_fGcoProduction)
		m_pbCopyClass.Hide();
}

void CBNAConfigDlg::ButtonClick(ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_DEFINENEW:
		DefineNewEntry();
		break;

	case IDC_ASSOCIATE:
		m_lvAssocLayers.PostEvent (WM_SHOWCOMBO, -1, CLASS_COLUMN);
		break;

	case IDC_COPYCLASS:
		CopyBnaEntry();
		break;

	default:
		break;
	}
}

int CBNAConfigDlg::OnWizBack (NotifyEvt e)
{
	_ASSERTE(NULL != m_pBack);
	if (m_pBack -> GetFilesParsed())
		return m_pBack -> GetFirstPageId();
	return 0;
}

int CBNAConfigDlg::OnWizFinish (NotifyEvt e)
{
	if (SUCCEEDED(PrepareResult())) 					// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

int CBNAConfigDlg::OnSetActive (NotifyEvt e)
{
	AdjustSheetButtons();
	return 0;
}

bool CBNAConfigDlg::OnNotify (NotifyEvt e)
{
NMHDR *pNMHDR = e.GetNotifyInfo();
LRESULT lResult = false;

	if (LVN_ENDLABELEDIT == pNMHDR -> code) {
		m_lvAssocLayers.OnEndLabelEdit (pNMHDR, &lResult);
		SetWindowLong (Handle(API_WINDOW_HWND), DWL_MSGRESULT, lResult);
		return true;
	}
	else if (NM_CLICK == pNMHDR -> code) {
		m_lvAssocLayers.OnClick(pNMHDR, &lResult);
		SetWindowLong (Handle(API_WINDOW_HWND), DWL_MSGRESULT, lResult);
		return true;
	}
	return false;
}

LRESULT CBNAConfigDlg::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_NOTIFY:
		if (OnNotify ((NotifyEvt &)e))
			return true;
		break;

	default:
		if (WM_ADDNEWENTRY == e.Msg()) 
			return DefineNewEntry();
		if (WM_COPYBNAENTRY == e.Msg())
			return CopyBnaEntry();
		break;
	}
	return CPropertyPage::Dispatch (e);
}

///////////////////////////////////////////////////////////////////////////////
// 
void CBNAConfigDlg::AdjustSheetButtons()
{
// nicht erste Seite
DWORD dwBttns = PSWIZB_BACK;

// letzte Seite
	if (!GetDisableNextPage()) 
		dwBttns |= PSWIZB_FINISH;
	else 
		dwBttns |= PSWIZB_DISABLEDFINISH;

	SetSheetWizardButtons(dwBttns);
}

BOOL CBNAConfigDlg::GetDisableNextPage()
{
	return FALSE;
}

HRESULT CBNAConfigDlg::PrepareResult (void)
{
// alle ausgewählten Zuordnungen auslesen und speichern
int iCount = m_lvAssocLayers.GetItemCount();

	for (int i = 0; i < iCount; ++i) {
	string strLayer (m_lvAssocLayers.GetLayerName(i));
	CTable t(*g_OKSTree);

		if (!t.Find((void *)strLayer.c_str())) {
			_ASSERTE(t.Find((void *)strLayer.c_str()));
			continue;
		}

	DWORD dwType = m_lvAssocLayers.GetObjType(i);
	TR_LayerLock l(t);

		if (m_lvAssocLayers.GetDoImport(i)) {
		string strClass (m_lvAssocLayers.GetClassName(i));

			l -> SetKurzText(dwType, strClass.c_str(), m_pBack->GetContextHandle());
		}
		else {
			l -> ResetData(dwType);
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Neue Objeklasse definieren
BOOL CBNAConfigDlg::DefineNewEntry()
{
DEFINEIDENTDLG DlgData;

	INITSTRUCT(DlgData, DEFINEIDENTDLG);
	DlgData.hWnd = Handle(API_WINDOW_HWND);
	DlgData.lIdent = 0;
	DlgData.hPr = m_pBack -> GetContextHandle();

long lIdent = DEX_DefineNewObjectsDesc(DlgData);	// neue Identbeschreibung erzeugen

// neu definierten Ident für FocusItem voreinstellen
	if (0 != lIdent && !m_lvAssocLayers.GetDoImport()) {
	ErrInstall EI (WC_NOIDENT);
	PBDDATA pbdData;
	char cbBuffer[_MAX_PATH];

		INITSTRUCT(pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = lIdent;
		pbdData.pbdKText = cbBuffer;
		pbdData.pbdLText = NULL;
		pbdData.pbdKTextLen = sizeof(cbBuffer);
		pbdData.pbdLTextLen = 0;

	// PBD-Info holen
		if (EC_OKAY == DEX_GetPBDData(pbdData)) {
			m_lvAssocLayers.SetClassText(cbBuffer);
			m_lvAssocLayers.SetFocus();
			return TRUE;
		}
	}

	m_lvAssocLayers.SetCheckState(false);
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Objektklasse aus Bna-Datei übernehmen
BOOL CBNAConfigDlg::CopyBnaEntry()
{
// alle ausgewählten Zuordnungen durchgehen und übernehmen
int iIndex = m_lvAssocLayers.GetFirstSelected();
HPROJECT hPr = m_pBack -> GetContextHandle();

	while (-1 != iIndex) {
	string strLayer (m_lvAssocLayers.GetLayerName(iIndex));
	CTable t(*g_OKSTree);

	// Ebenennamen ggf. als neue Objektklasse definieren
		if (!t.Find((void *)strLayer.c_str()) || !CreateNewEntry(strLayer.c_str()))
			continue;

	// Objektklasse setzen
		m_lvAssocLayers.SetClassText(iIndex, strLayer.c_str());
		StoreInOKSTree(strLayer.c_str(), m_lvAssocLayers.GetObjType(iIndex), hPr, true);

	// nächsten selektierten Eintrag behandeln
		iIndex = m_lvAssocLayers.GetNextSelected();
	}
	return FALSE;
}

BOOL CBNAConfigDlg::CreateNewEntry(LPCSTR pcNewClass)
{
// evtl. Identifikator erzeugen
HPROJECT hPr = m_pBack->GetContextHandle();
ULONG lIdent = DEX_GetUniqueICodeEx(hPr);
char cbBuffer[MAX_OKS_LENX+1];

	if (FAILED(ClassFromIdentX (hPr, lIdent, cbBuffer, sizeof(cbBuffer))))
		return FALSE;

// zu bestimmtem Ident den OKS speichern
//MODOBJCLASSCODE MOCC;
//
//	INITSTRUCT(MOCC, MODOBJCLASSCODE);
//	MOCC.ulIdent = lIdent;
//	MOCC.pcClass = pcNewClass;
//	MOCC.fOverWrite = true;
//	
//HRESULT hr = DEX_ModObjectClassCodeEx(hPr, MOCC);
//	
//	if (FAILED(hr))	
//		return FALSE;		// Fehler

// aktuelle Texte wegschreiben
ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdTemp = false;
	pbdData.pbdKText = const_cast<char *>(pcNewClass);
	pbdData.pbdKTextLen = strlen(pcNewClass);

ErrCode RC = DEX_ModPBDDataEx (hPr, pbdData);

	_ASSERTE(EC_OKAY == RC);
	DEXN_PBDIdentChanged (lIdent);
	return TRUE;
}
