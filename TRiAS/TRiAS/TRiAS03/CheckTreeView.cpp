// Klassendefinition für eine Listbox, die CheckBoxes enthält -----------------
// File: CHECKTREEVIEW.CPP

#include "trias03p.hxx"
#include "trias03.h"

#include <containr.hxx>

#include <CheckTreeView.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

// Konstruktoren --------------------------------------------------------------
CCheckTreeView::CCheckTreeView (
		pDialogWindow pDW, ResID rsc, bool fUseCheckMarks, bool fUsePartialCheckMarks) :
	ControlWindow (new CTreeViewCtrl (pDW, rsc)), 
	m_fUseCheckMarks(fUseCheckMarks), m_fUsePartialCheckMarks(fUsePartialCheckMarks)
{
	if (NULL == GetControl())
		db_error (EC_NOMEMORY, RC_ctOwnerDrawListBox);
}

CCheckTreeView::~CCheckTreeView (void) 
{
	if (m_fUseCheckMarks) {
	CImageList *pIList = SetImageList (NULL, TVSIL_STATE);

		DELETE_OBJ (pIList);
	}
	
	DeleteAllItems();
	if (GetTree()) 
		delete GetTree();
}

bool CCheckTreeView::FInit ()
{
	if (NULL == GetTree() || !ControlWindow::FInit())
		return false;

	if (UseCheckMarks()) {
//	UINT uiRes = IsWin40() ? IDB_CHECKMARKS_40 : IDB_CHECKMARKS_NT;
	UINT uiRes = IDB_CHECKMARKS_40;		// jetzt nur noch neue Bildchen
	ResourceFile RF (g_pDLLName);

		if (!m_CheckMarks.CreateList (ResID(uiRes, &RF), 15, 0, RGB(255, 255, 255))) {
			TX_TRACE("Couldn't create state imagelist");
			return false;
		}

	CImageList *pIList = SetImageList (&m_CheckMarks, TVSIL_STATE);

		DELETE_OBJ(pIList);
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen
bool CCheckTreeView::ToggleCheckMark (HTREEITEM hItem)
{
	if (!UseCheckMarks() || NULL == hItem)
		return false;

bool fWasOn = false;
TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	if (GetItem (&tvi)) {
	UINT uiState = TV_CHECK_NOMARK;
	
		switch (tvi.state & TVIS_STATEIMAGEMASK) {
		case TV_CHECK_OFF:
			uiState = TV_CHECK_ON;
			break;

		case TV_CHECK_ON:
			uiState = TV_CHECK_OFF;
			fWasOn = true;
			break;

		case TV_CHECK_PARTIAL_ON:
			if (UsePartialCheckMarks()) {
				uiState = TV_CHECK_ON;
				fWasOn = true;
			}
			break;

		case TV_CHECK_PASSIVE:
		case TV_CHECK_NOMARK:
			break;

		default:
			_ASSERTE(FALSE);
			break;
		}
		SetCheckState(hItem, uiState);
	}
	return fWasOn;
}

void CCheckTreeView::HideStateImage (HTREEITEM hItem)
{
	if (m_fUseCheckMarks)
		SetCheckState (hItem, TV_CHECK_NOMARK);
}

UINT CCheckTreeView::GetCheckState (HTREEITEM hItem)
{
	if (!m_fUseCheckMarks)
		return TV_CHECK_NOMARK;

TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	if (GetItem (&tvi)) 
		return tvi.state & TVIS_STATEIMAGEMASK;
	return TV_CHECK_NOMARK;
}

void CCheckTreeView::SetCheckState (HTREEITEM hItem, UINT uiState, bool fPropagateUp, bool fPropagateDown)
{
	if (!m_fUseCheckMarks)
		return;

TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	tvi.state = uiState;
	tvi.stateMask = TVIS_STATEIMAGEMASK;
	SetItem (&tvi);

// ggf. die Änderung nach oben/unten propagieren
	if (m_fUsePartialCheckMarks) {
	HTREEITEM hParent = GetParentItem(hItem);

		if (fPropagateUp && (TVI_ROOT != hParent && NULL != hParent)) {
		UINT uiOldState = GetCheckState(hParent);
		UINT uiNewState = CalcParentCheckState(hParent);

			if (uiOldState != uiNewState)
				SetCheckState(hParent, uiNewState, true, false);	// eine Etage hoch, aber nicht wieder runter
		}

	// wenns eindeutig ist, dann alle drunter liegenden auch umschalten
		if (fPropagateDown && (TV_CHECK_ON == uiState || TV_CHECK_OFF == uiState)) {
		HTREEITEM hChildItem = NULL;

			if (TVI_ROOT == hItem)
				hChildItem = GetNextItem (NULL, TVGN_CHILD);
			else 
				hChildItem = GetChildItem (hItem);
		
			while (NULL != hChildItem) {
				SetCheckState (hChildItem, uiState, false, true);	// nicht wieder nach oben propagieren
				hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
			}
		}
	}
}

UINT CCheckTreeView::CalcParentCheckState (HTREEITEM hItem)
{
	_ASSERTE(m_fUsePartialCheckMarks);

UINT uiCurrState = GetCheckState(hItem);

	if (TV_CHECK_NOMARK == uiCurrState || TV_CHECK_PASSIVE == uiCurrState)
		return uiCurrState;		// hat nichts anzuhaken

// jetzt alle Childs durchgehen, um unseren CheckState zu berechnen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else 
		hChildItem = GetChildItem (hItem);

UINT uiMinState = TV_CHECK_ON;
UINT uiMaxState = TV_CHECK_NOMARK;

	while (NULL != hChildItem) {
	UINT uiState = GetCheckState(hChildItem);
	
		switch (uiState) {
		case TV_CHECK_NOMARK:
		case TV_CHECK_PASSIVE:
			break;	// do not bother

		case TV_CHECK_OFF:
			if (TV_CHECK_ON != uiMaxState && TV_CHECK_PARTIAL_ON != uiMaxState)
				uiMaxState = uiState;
			uiMinState = uiState;
			break;

		case TV_CHECK_PARTIAL_ON:
			if (TV_CHECK_ON != uiMaxState)
				uiMaxState = uiState;
			if (TV_CHECK_OFF != uiMinState)
				uiMinState = uiState;
			break;

		case TV_CHECK_ON:
			uiMaxState = uiState;
			if (TV_CHECK_OFF != uiMinState && TV_CHECK_PARTIAL_ON != uiMinState)
				uiMinState = uiState;
			break;

		default:
			_ASSERTE(FALSE);
			break;
		}
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}

	return (uiMinState == uiMaxState) ? uiMinState : TV_CHECK_PARTIAL_ON;
}

HTREEITEM CCheckTreeView::FindItem (HTREEITEM hItem, LPCSTR pcItem)
{
	if (NULL == hItem) 
		return NULL;

// wenn's das RootItem ist, dann erstes Child geben lassen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else {
	// zuerst dieses Item testen (die Root kann's nicht sein)
	string strItem = GetItemText (hItem);

		if (strItem == pcItem)
			return hItem;

		hChildItem = GetChildItem (hItem);
	}

// anschließen alle Childs abtesten
	while (NULL != hChildItem) {
	HTREEITEM hReturn = FindItem (hChildItem, pcItem);

		if (NULL != hReturn)
			return hReturn;
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}
	return NULL;	// nichts gefunden
}

HTREEITEM CCheckTreeView::FindString (LPCSTR pcItem)
{
	return FindItem (TVI_ROOT, pcItem);
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler
void CCheckTreeView::MouseButtonDn (MouseEvt e)
{
	if (e.isLeftButton() && UseCheckMarks()) 
		HandleCheckMark (e.Where(), WM_LBUTTONDOWN);
	ControlWindow::MouseButtonDn (e);
}

void CCheckTreeView::MouseButtonDblClk (MouseEvt e)
{
	if (e.isLeftButton() && UseCheckMarks()) 
		HandleCheckMark (e.Where(), WM_LBUTTONDOWN);
	ControlWindow::MouseButtonDblClk (e);
}

void CCheckTreeView::HandleCheckMark(Point point, UINT uiMsg)
{
Rectangle rc = CanvasRect();
CoOrd dY = rc.Top()-rc.Bottom();
TV_HITTESTINFO ht;

	ht.pt.x = point.X();
	ht.pt.y = dY-point.Y();

HTREEITEM hNewTarget = HitTest (&ht);

	if (hNewTarget && (ht.flags & TVHT_ONITEMSTATEICON)) {
	UINT uiState = ChangingCheckState (hNewTarget, uiMsg);

		if (TV_CHECK_NOCHANGE != uiState) {
			if (TV_CHECK_NOMARK != uiState)
				SetCheckState (hNewTarget, uiState);
			else
				ToggleCheckMark (hNewTarget);
			NotifyChecked (hNewTarget, uiMsg, GetCheckState(hNewTarget));
		}
	}
}

void CCheckTreeView::NotifyChecked (HTREEITEM hNewTarget, UINT uiMsg, UINT uiCheckState)
{
NM_TREEVIEWCHECK nmCheck;

	nmCheck.hdr.hwndFrom = Handle();
	nmCheck.hdr.idFrom = GetDlgCtrlID(nmCheck.hdr.hwndFrom);
	nmCheck.hdr.code = TVN_CHECKSTATECHANGED;
	nmCheck.hItem = hNewTarget;
	nmCheck.action = uiMsg;
	nmCheck.state = uiCheckState;
	SendMessage(GetParent()->Handle(), WM_NOTIFY, nmCheck.hdr.idFrom, (LPARAM)&nmCheck);
}

UINT CCheckTreeView::ChangingCheckState (HTREEITEM hNewTarget, UINT uiMsg)
{
NM_TREEVIEWCHECK nmCheck;

	nmCheck.hdr.hwndFrom = Handle();
	nmCheck.hdr.idFrom = GetDlgCtrlID(nmCheck.hdr.hwndFrom);
	nmCheck.hdr.code = TVN_CHANGINGCHECKSTATE;
	nmCheck.hItem = hNewTarget;
	nmCheck.action = uiMsg;
	nmCheck.state = TV_CHECK_NOMARK;
	SendMessage(GetParent()->Handle(), WM_NOTIFY, nmCheck.hdr.idFrom, (LPARAM)&nmCheck);

	return nmCheck.state;
}
