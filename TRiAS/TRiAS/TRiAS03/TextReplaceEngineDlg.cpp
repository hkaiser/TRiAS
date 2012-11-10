// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.09.2000 18:04:49
//
// @doc
// @module TextReplaceEngineDlg.cpp | Implementation of the <c CTextReplaceEngineDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include <ClipBrd.hxx>
#include <propname.hxx>
#include <StrDup.hxx>
#include <ipropseq.hxx>

#include <TextReplacePrp.h>
#include <xtsnguid.h>

#include "TextReplaceEngineDlg.h"
#include "TextReplaceEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// MenuKommandos verteilen
#define ON_SRCEXPR_ID(uiID,pText)					case (uiID): OnSrcExprCommand(pText); break
#define ON_SRCEXPR_ID_MOVE(uiID,pText,iMove)		case (uiID): OnSrcExprCommand(pText,iMove); break
#define ON_DESTEXPR_ID(uiID,pText)					case (uiID): OnDestExprCommand(pText); break
#define ON_DESTEXPR_ID_OBJPROP(uiID,pText)			case (uiID): OnDestExprCommand(uiID,pText); break
#define ON_DESTEXPR_DEFAULT(uiID,pText)				default: OnDestExprCommand(uiID,pText); break

const int WM_SHOWSRCEXPRMENU = WM_USER+1234;
const int WM_SHOWDESTEXPRMENU = WM_USER+1235;

const int GROUPS_MENUPOSITION = 1;
const int OBJPROP_MENUPOSITION = 4;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// globale Funktionen
namespace {
	void FreeMenuTexts (HMENU hMenu)
	{
		if (NULL == hMenu)
			return;

	int iCnt = GetMenuItemCount(hMenu);

		for (int i = 0; i < iCnt; ++i) {
			if (MF_POPUP & GetMenuState(hMenu, i, MF_BYPOSITION))
				FreeMenuTexts(GetSubMenu(hMenu, i));
			else {
			MENUITEMINFO mii;

				memset(&mii, '\0', sizeof(MENUITEMINFO));
				mii.cbSize = sizeof(MENUITEMINFO);
				mii.fMask = MIIM_DATA;
				GetMenuItemInfo (hMenu, i, TRUE, &mii);
				if (0 != mii.dwItemData)
					StrFreeF(reinterpret_cast<char *>(mii.dwItemData));
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTextReplaceEngineDlg

CTextReplaceEngineDlg* CTextReplaceEngineDlg::CreateInstance (
	CTextReplaceEngine *pParent, ResID resID, LPCSTR pcCaption)
{
CTextReplaceEngineDlg *pCfgDlg = NULL;

// Dialog erzeugen
	TX_TRY(pCfgDlg = new CTextReplaceEngineDlg(pParent, resID, pcCaption));
	if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
		DELETE_OBJ(pCfgDlg);
		return NULL;
	}
	return pCfgDlg; 
}

#pragma warning (disable: 4355)

CTextReplaceEngineDlg::CTextReplaceEngineDlg(
		CTextReplaceEngine *pParent, ResID resID, LPCSTR pcCaption) :
	CPropertyPage(resID, pcCaption),
	m_ObjPropSrc (this, IDC_OBJPROPERTY_SRC, IDC_SELECT_OBJPROP_SRC),
	m_ObjPropDest (this, IDC_OBJPROPERTY_DEST, IDC_SELECT_OBJPROP_DEST, IncludeWritable),
	m_cbCapital (this, IDC_CAPITAL_REPLACE),
	m_cbPartialMatch (this, IDC_PARTIALMATCH_REPLACE),
	m_cbUseRegExpr (this, IDC_USEREGEXPR_REPLACE),
	m_cbTestBOB (this, IDC_BEGINOFTEXT_REPLACE),
	m_cbFindWhat (this, IDC_FINDWHAT_REPLACE, IDC_INSERT_REGEXPR_SEARCH),
	m_cbReplaceWith (this, IDC_REPLACEWITH, IDC_INSERT_REGEXPR_REPLACE)
{
	m_dwFlags = 0;
	m_fIsInitialized = false;
	m_fDestSelected = false;
	m_pStatus = NULL;
	m_hMenu = NULL;
	m_pParent = pParent;
}

#pragma warning (default: 4355)

CTextReplaceEngineDlg::~CTextReplaceEngineDlg()
{
}

BOOL CTextReplaceEngineDlg::AdjustSheetButtons()
{
	if (!m_fIsInitialized) 
		return false;

// Knöpfe des Dialoges richten (Next, Previous, Finish)
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
	return true;
}

BOOL CTextReplaceEngineDlg::GetDisableNextPage()
{
	if (!m_ObjPropSrc.hasSelection() || !m_ObjPropDest.hasSelection())
		return TRUE;	// Quelle und Ziel müssen gegeben sein
	if (!m_cbFindWhat.hasSelection())
		return TRUE;	// Suchtext und Zieltext müssen gegeben sein
		
	return FALSE;
}

void CTextReplaceEngineDlg::DoUpdate (void)
{
	_ASSERTE(NULL != m_pStatus);

	if (NULL == m_pStatus) return;

	m_pStatus -> erase();

// Flags wegschreiben
	m_pStatus -> m_fCapital = m_cbCapital.isChecked();
	m_pStatus -> m_fPartialMatch = m_cbPartialMatch.isChecked();
	m_pStatus -> m_fUseRegExpr = m_cbUseRegExpr.isChecked();
	m_pStatus -> m_fTestBOB = m_cbTestBOB.isChecked();

// SuchStrings wegschreiben
	m_cbFindWhat.SaveData (m_pStatus -> m_strFindWhat, m_pStatus -> m_lstFindWhat);
	m_cbReplaceWith.SaveData (m_pStatus -> m_strReplaceWith, m_pStatus -> m_lstReplaceWith);

// Objekteigenschaft wegschreiben
	m_ObjPropSrc.SaveData (m_pStatus -> m_strObjPropSrc);
	m_ObjPropDest.SaveData (m_pStatus -> m_strObjPropDest);

// ausgewählte Objekteigenschaft im Kontext ablegen
WPropertyActionSequence Seq;
WDataObject CtxDO;

	if (SUCCEEDED(m_pParent -> GetSite(IID_IPropertyActionSequence, Seq.ppv())) &&
		SUCCEEDED(Seq -> GetSequenceContext (CtxDO.ppi())))
	{
		PropActBase::SetObjectProperty(CtxDO, m_pStatus -> m_strObjPropDest.c_str());
	}
}

HRESULT CTextReplaceEngineDlg::InitWithData (CTextReplaceEngineDlg::CDlgStatus &rStatus)
{
	m_pStatus = &rStatus;	// Pointer auf StatusObjekt speichern
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// MenuCommands
BOOL CTextReplaceEngineDlg::OnSrcExprCommand (LPCSTR pcInsert, int iMove)
{
	m_cbFindWhat.AddToExprString (pcInsert, iMove);
	m_cbUseRegExpr.SetChecked(true);
	m_cbTestBOB.SetChecked(false);

	AdjustSheetButtons();
	return true;
}

os_string CTextReplaceEngineDlg::GetObjectProperty (UINT uiID)
{
os_string strName("");

	if (ID_ORIGVALUE == uiID)
		m_ObjPropSrc.SaveData(strName);
	else if (uiID >= ID_FIRST_OBJPROP) {
	// die Objekteigenschaften haben die größten ID's
//	char cbBuffer[_MAX_PATH];

		_ASSERTE(NULL != m_hMenu);

	MENUITEMINFO mii;

		memset (&mii, '\0', sizeof(MENUITEMINFO));
		mii.cbSize = sizeof(MENUITEMINFO);
		mii.fMask = MIIM_DATA;
		GetMenuItemInfo(m_hMenu, uiID, FALSE, &mii);
//		GetMenuString(m_hMenu, uiID, cbBuffer, sizeof(cbBuffer), MF_BYCOMMAND);
//		strName = cbBuffer;
		_ASSERTE(0 != mii.dwItemData);
		strName = reinterpret_cast<char *>(mii.dwItemData);
	}
	return strName;
}

BOOL CTextReplaceEngineDlg::OnDestExprCommand (LPCSTR pcInsert)
{
	m_cbReplaceWith.AddToExprString (pcInsert, 0);
	AdjustSheetButtons();
	return true;
}

BOOL CTextReplaceEngineDlg::OnDestExprCommand (UINT uiID, LPCSTR pcInsert)
{
// ggf. Namen einer Objekteigenschaft reinapplizieren
os_string strName (GetObjectProperty(uiID));
char cbBuffer[_MAX_PATH];

	wsprintf (cbBuffer, pcInsert, strName.c_str());
	m_cbReplaceWith.AddToExprString (cbBuffer, 0);
	AdjustSheetButtons();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// sämtliche zur Verfügung stehenden Objekteigenschaften rekursiv in ein Menu 
// einhängen
BOOL CTextReplaceEngineDlg::FillMenuWithObjProps(HMENU hMenu)
{
	_ASSERTE(NULL != hMenu);

// 1. Menu leeren
	while (GetMenuItemCount(hMenu) > 0)
		DeleteMenu(hMenu, 0, MF_BYPOSITION);

// 2. neue Items erzeugen
WObjectProps Props;
WEnumObjProps Enum;

	if (FAILED(m_ObjPropSrc.GetObjProps(Props.ppi())) || FAILED(Props -> EnumObjectProps (Enum.ppi()))) 
		return FALSE;

// Objekteigenschaften durchgehen
WObjectProperty ObjProp;
char cbPropInfo[_MAX_PATH];
CParentMenuItems Items;
UINT uiCmd = ID_FIRST_OBJPROP-1;

	for (Enum -> Reset(); S_OK == Enum -> Next (1, ObjProp.ppu(), NULL); /**/)
	{
	// vollständigen Namen geben lassen
	DWORD dwFlags = 0L;
	HRESULT hr = ObjProp -> GetPropInfo (cbPropInfo, sizeof(cbPropInfo), &dwFlags);
	
		if (FAILED(hr) || !IncludeObjProp(dwFlags))
			continue;		// nur gewünschte ObjProps anzeigen

	CPropertyName PropName (cbPropInfo);
	HMENU hParentMenu = CalcParentMenu (PropName.GetGroup(), Items);

		if (NULL == hParentMenu)
			continue;

	// den vollen Namen der Objekteigenschaft am Menuitem ablegen
	MENUITEMINFO mii;

		memset(&mii, '\0', sizeof(MENUITEMINFO));
		mii.cbSize = sizeof(MENUITEMINFO);
		mii.fMask = MIIM_DATA;
		mii.dwItemData = reinterpret_cast<UINT_PTR>(StrDupF(PropName.GetCompareName().c_str()));

		if (PropName.hasSubGroup()) {
		HMENU hSubGroupMenu = CalcSubGroupMenu (hParentMenu, PropName.GetSubGroup());

			if (NULL != hSubGroupMenu) {
				InsertMenu(hSubGroupMenu, (UINT)-1, MF_BYPOSITION|MF_STRING, (UINT_PTR)(++uiCmd), PropName.GetName().c_str());
				SetMenuItemInfo(hSubGroupMenu, uiCmd, FALSE, &mii);
			}
		} else {
			InsertMenu(hParentMenu, (UINT)-1, MF_BYPOSITION|MF_STRING, (UINT_PTR)(++uiCmd), PropName.GetName().c_str());
			SetMenuItemInfo(hParentMenu, uiCmd, FALSE, &mii);
		}
	}

// 3. jetzt alle Groups ins Hauptmenu einbauen
	for (CParentMenuItems::iterator it = Items.begin(); it != Items.end(); ++it)
		InsertMenu(hMenu, (UINT)-1, MF_BYPOSITION|MF_POPUP, (UINT_PTR)((*it).second), (*it).first.c_str());
	return true;
}

HMENU CTextReplaceEngineDlg::CalcParentMenu (os_string strGroup, CParentMenuItems &rItems)
{
HMENU hMenu = NULL;
CParentMenuItems::iterator it = rItems.find (strGroup);

	if (it == rItems.end()) {
	// erstes mal
		hMenu = CreatePopupMenu();
		rItems.insert (make_pair(strGroup, hMenu));
	} else
		hMenu = (*it).second;

	return hMenu;
}

HMENU CTextReplaceEngineDlg::CalcSubGroupMenu (HMENU hParentMenu, os_string strSubGroup)
{
	_ASSERTE(NULL != hParentMenu);
	
HMENU hMenu = NULL;
char cbBuffer[_MAX_PATH];

	for (UINT i = 0; i < GetMenuItemCount(hParentMenu); ++i) {
		if ((MF_POPUP & GetMenuState(hParentMenu, i, MF_BYPOSITION)) && 
			(GetMenuString(hParentMenu, i, cbBuffer, sizeof(cbBuffer), MF_BYPOSITION) > 0) &&
			(strSubGroup == cbBuffer))
		{
			hMenu = GetSubMenu(hParentMenu, i);
			break;
		}
	}

	if (NULL == hMenu) {
	// bisher noch nichts gefunden, neues SubMenu erzeugen und dranhängen
		hMenu = CreatePopupMenu();
		InsertMenu(hParentMenu, (UINT)-1, MF_BYPOSITION|MF_POPUP, (UINT_PTR)hMenu, strSubGroup.c_str());
	}
	return hMenu;
}

/////////////////////////////////////////////////////////////////////////////
// CTextReplaceEngineDlg message handlers

void CTextReplaceEngineDlg::WindowInit (Event)
{
// Suchoptionen
	m_cbCapital.FInit();
	m_cbPartialMatch.FInit();
	m_cbUseRegExpr.FInit();
	m_cbTestBOB.FInit();

	m_cbCapital.SetChecked(false);
	m_cbPartialMatch.SetChecked(false);
	m_cbUseRegExpr.SetChecked(false);
	m_cbTestBOB.SetChecked(false);

// Compound controls
	m_cbFindWhat.FInit();
	m_cbReplaceWith.FInit();
	m_ObjPropSrc.FInit();
	m_ObjPropDest.FInit();
	
// Optionen initialisieren
	if (NULL != m_pStatus) {
		m_cbCapital.SetChecked(m_pStatus -> m_fCapital);
		m_cbPartialMatch.SetChecked(m_pStatus -> m_fPartialMatch);
		m_cbUseRegExpr.SetChecked(m_pStatus -> m_fUseRegExpr);
		m_cbTestBOB.SetChecked(m_pStatus -> m_fTestBOB);

	// Liste der letzten SuchPatterns initialisieren
		m_cbFindWhat.InitFromData (m_pStatus -> m_strFindWhat, m_pStatus -> m_lstFindWhat);
		m_cbReplaceWith.InitFromData (m_pStatus -> m_strReplaceWith, m_pStatus -> m_lstReplaceWith);

	// Objekteigenschaften
		m_ObjPropSrc.InitFromData(m_pStatus -> m_strObjPropSrc.c_str());
		m_ObjPropDest.InitFromData(m_pStatus -> m_strObjPropDest.c_str());
	}

	m_fIsInitialized = true;
	AdjustSheetButtons();
}

int CTextReplaceEngineDlg::OnSetActive(NotifyEvt) 
{
	AdjustSheetButtons();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen 
void CTextReplaceEngineDlg::OnCancel (NotifyEvt)
{
	return;		// hier evtl. Aufräumarbeiten durchführen
}

int CTextReplaceEngineDlg::OnWizNext (NotifyEvt e)
{
	DoUpdate();
	return 0;
}

BOOL CTextReplaceEngineDlg::OnWizFinish (NotifyEvt e)
{
	DoUpdate();
	return FALSE;
}

void CTextReplaceEngineDlg::ButtonClick (ControlEvt e)
{
	switch ((UINT)e.GetControlID()) {
	case IDC_INSERT_REGEXPR_SEARCH:
		PostEvent (WM_SHOWSRCEXPRMENU);		// Menu anzeigen
		break;
		
	case IDC_INSERT_REGEXPR_REPLACE:
		PostEvent (WM_SHOWDESTEXPRMENU);	// Menu anzeigen
		break;

	case IDC_SELECT_OBJPROP_SRC:
		if (m_ObjPropSrc.ShowObjPropDlg()) {
		os_string strObjProp;

			if (!m_fDestSelected && m_ObjPropSrc.SaveData(strObjProp)) {
				if (!m_ObjPropDest.InitFromData(strObjProp.c_str()))
					m_ObjPropDest.ResetSelection();		// Objekteigenschaft existiert hier nicht
			}
			AdjustSheetButtons();
		}
		break;

	case IDC_SELECT_OBJPROP_DEST:
		if (m_ObjPropDest.ShowObjPropDlg()) {
			m_fDestSelected = true;
			AdjustSheetButtons();
		}
		break;

	case IDC_USEREGEXPR_REPLACE:
		CPropertyPage::ButtonClick(e);
		if (m_cbUseRegExpr.isChecked()) 
			m_cbTestBOB.SetChecked(false);
		break;

	case IDC_BEGINOFTEXT_REPLACE:
		CPropertyPage::ButtonClick(e);
		if (m_cbTestBOB.isChecked())
			m_cbUseRegExpr.SetChecked(false);
		break;

	case IDC_CAPITAL_REPLACE:
	case IDC_PARTIALMATCH_REPLACE:
		break;
	}
}

void CTextReplaceEngineDlg::EditChange (ControlEvt)
{
	AdjustSheetButtons();
}

void CTextReplaceEngineDlg::ListBoxSel (ControlEvt)
{
	AdjustSheetButtons();
}

// MenuInitialisierung
int CTextReplaceEngineDlg::GetGroupCount()
{
int iGrpCnt = 0;
os_string str (m_cbFindWhat.GetSelection());

	if (0 == str.size())
		return 0;

size_t iPos = str.find("\\(", 0);

	while (iPos != os_string::npos) {
		++iGrpCnt;
		iPos = str.find("\\(", iPos + 2);
	} 
	return iGrpCnt;
}

namespace {
	BOOL HasMenuItem (HMENU hMenu, UINT uiCmd)
	{
		for (UINT i = 0; i < GetMenuItemCount(hMenu); ++i) {
			if ((MF_POPUP|MF_SEPARATOR) & GetMenuState(hMenu, i, MF_BYPOSITION))
				continue;
			if (uiCmd == GetMenuItemID(hMenu, i))
				return TRUE;
		}
		return FALSE;		// nicht gefunden
	}
}

void CTextReplaceEngineDlg::MenuInit(MenuInitEvt e)
{
	if (e.Msg() != WM_INITMENUPOPUP)
		return;

// lediglich das Zielmenu muß beeinflußt werden
	_ASSERTE(NULL != m_hMenu);
	if (HasMenuItem(m_hMenu, ID_ORIGVALUE)) {
	// QuellObjekteigenschaft bereits selektiert
		EnableMenuItem (m_hMenu, ID_ORIGVALUE, MF_BYCOMMAND|(m_ObjPropSrc.hasSelection() ? MF_ENABLED : MF_GRAYED));

	// enthält SuchString Gruppierungen
	int iGroupCount = GetGroupCount();

		if (iGroupCount > 0) {
			EnableMenuItem (m_hMenu, GROUPS_MENUPOSITION, MF_BYPOSITION|MF_ENABLED);

		HMENU hGrpMenu = GetSubMenu (m_hMenu, GROUPS_MENUPOSITION);
		
			for (int i = 0; i < 10; ++i)
				EnableMenuItem (hGrpMenu, ID_GRUPPIERUNG_1+i, MF_BYCOMMAND|((i < iGroupCount) ? MF_ENABLED : MF_GRAYED));
		} else {
			_ASSERTE(0 == iGroupCount);
			EnableMenuItem (m_hMenu, GROUPS_MENUPOSITION, MF_BYPOSITION|MF_GRAYED);
		}
		
	// ist Text in der Zwischenablage
		{
		CClipboard CB;

			EnableMenuItem (m_hMenu, ID_FROMCLIPBOARD, MF_BYCOMMAND|((0 != CB.GetItemSize(CClipboard::FmtText)) ? MF_ENABLED : MF_GRAYED));
		}
		
	// gibt es überhaupt eine Objekteigenschaft
	HMENU hObjPropMenu = GetSubMenu (m_hMenu, OBJPROP_MENUPOSITION);

		EnableMenuItem (m_hMenu, OBJPROP_MENUPOSITION, MF_BYPOSITION|((0 != GetMenuItemCount(hObjPropMenu)) ? MF_ENABLED : MF_GRAYED));
	}
}

// MenuSelect
void CTextReplaceEngineDlg::MenuSelect(MenuSelectEvt e)
{
UINT nItemID = e.GetItemID();
UINT nFlags = HIWORD(e.WParam());

	if (nFlags != 0xFFFF) {
	// no cancel menu operation (go back to idle now)
		if (0 != nItemID && IDCANCEL != nItemID && !(nFlags & (MF_SEPARATOR|MF_POPUP))) {
		ResourceFile RF (g_pDLLName);
		ResString res (ResID (nItemID, &RF), 255);

			if (res.Len() > 0) {
				DEX_SetMessageString(res.Addr());
				return;
			}
		}
	}

// else show default text
	DEX_SetMessageString(0);
}

// MenuKommandos vom RegExprMenu auswerten
void CTextReplaceEngineDlg::MenuCommand (MenuCommandEvt e)
{
	BEGIN_COMMANDS(e.GetItemID()) 
	// Regular Expressions für FindWhat
		ON_SRCEXPR_ID(ID_ANYCHAR, TEXT("."));
		ON_SRCEXPR_ID_MOVE(ID_CHARINRANGE, TEXT("[]"), -1);
		ON_SRCEXPR_ID_MOVE(ID_CHARNOTINRANGE, TEXT("[^]"), -1);
		ON_SRCEXPR_ID(ID_BEGINOFTEXT, TEXT("\\`"));
		ON_SRCEXPR_ID(ID_LINEEND, TEXT("\\'"));
		ON_SRCEXPR_ID(ID_BEGINOFLINE, TEXT("^"));
		ON_SRCEXPR_ID(ID_ENDOFLINE, TEXT("$"));
		ON_SRCEXPR_ID(ID_OR, TEXT("\\|"));
		ON_SRCEXPR_ID(ID_ZEROORMORE, TEXT("*"));
		ON_SRCEXPR_ID(ID_ONEORMORE, TEXT("+"));
		ON_SRCEXPR_ID(ID_ZEROORONE, TEXT("?"));
		ON_SRCEXPR_ID(ID_WORDBEGIN, TEXT("\\<"));
		ON_SRCEXPR_ID(ID_WORDEND, TEXT("\\>"));
		ON_SRCEXPR_ID(ID_WITHINWORD, TEXT("\\B"));
		ON_SRCEXPR_ID(ID_WORDBOUNDARY, TEXT("\\b"));
		ON_SRCEXPR_ID_MOVE(ID_GROUPTOKENS, TEXT("\\(\\)"), -2);
	END_COMMANDS;
}

LRESULT CTextReplaceEngineDlg::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_SHOWSRCEXPRMENU:	// Menu für RegExpr anzeigen
		ShowSrcExprMenu();
		break;

	case WM_SHOWDESTEXPRMENU:	// Menu für Ziel-Objekteigenschaft anzeigen
		ShowDestExprMenu();
		break;
	}
	return CPropertyPage::Dispatch(e);
}

BOOL CTextReplaceEngineDlg::ShowSrcExprMenu()
{
// Menu generieren und anzeigen
ResourceFile RF (g_pDLLName);
Menu ExprMenu (ResID(IDR_REGEXPR, &RF));
Point Pt (m_cbFindWhat.GetMenuPos());
HWND hWnd = Handle (API_CLIENT_HWND);

// rechts unten positionieren
	m_hMenu = GetSubMenu (ExprMenu.Handle(API_MENU_HMENU), 0);		// SubMenu 0 holen

BOOL fResult = TrackPopupMenu (m_hMenu, TPM_RIGHTALIGN, Pt.X(), Pt.Y(), 0, hWnd, NULL);
	
	m_hMenu = NULL;
	return fResult;
}

BOOL CTextReplaceEngineDlg::ShowDestExprMenu()
{
// Menu generieren und anzeigen
ResourceFile RF (g_pDLLName);
Menu ExprMenu (ResID(IDR_REGEXPR, &RF));
Point Pt (m_cbReplaceWith.GetMenuPos());
HWND hWnd = Handle (API_CLIENT_HWND);

// rechts unten positionieren
	m_hMenu = GetSubMenu (ExprMenu.Handle(API_MENU_HMENU), 1);		// SubMenu 1 holen

// Objekteigenschaften hinzufügen
HMENU hObjPropMenu = GetSubMenu (m_hMenu, OBJPROP_MENUPOSITION);

// alle existierenden Objekteigenschaften
	FillMenuWithObjProps (hObjPropMenu);

// Menu anzeigen
UINT uiCmd = TrackPopupMenu (m_hMenu, TPM_RETURNCMD|TPM_RIGHTALIGN, Pt.X(), Pt.Y(), 0, hWnd, NULL);

	if (0 != uiCmd) {
		BEGIN_COMMANDS(uiCmd) 
			ON_DESTEXPR_ID(ID_GRUPPIERUNG_1, TEXT("\\1"));
			ON_DESTEXPR_ID(ID_GRUPPIERUNG_2, TEXT("\\2"));
			ON_DESTEXPR_ID(ID_GRUPPIERUNG_3, TEXT("\\3"));
			ON_DESTEXPR_ID(ID_GRUPPIERUNG_4, TEXT("\\4"));
			ON_DESTEXPR_ID(ID_GRUPPIERUNG_5, TEXT("\\5"));
			ON_DESTEXPR_ID(ID_GRUPPIERUNG_6, TEXT("\\6"));
			ON_DESTEXPR_ID(ID_GRUPPIERUNG_7, TEXT("\\7"));
			ON_DESTEXPR_ID(ID_GRUPPIERUNG_8, TEXT("\\8"));
			ON_DESTEXPR_ID(ID_GRUPPIERUNG_9, TEXT("\\9"));
			ON_DESTEXPR_ID(ID_FROMCLIPBOARD, TEXT("\\c"));
			ON_DESTEXPR_ID_OBJPROP(ID_ORIGVALUE, TEXT("\\{%s\\}"));
			ON_DESTEXPR_DEFAULT(uiCmd, TEXT("\\{%s\\}"));
		END_COMMANDS;
	}

// angehängte Texte wieder freigeben
	FreeMenuTexts(m_hMenu);

	m_hMenu = NULL;
	return (0 != uiCmd) ? true : false;
}

