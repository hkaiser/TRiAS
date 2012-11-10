// OKSTreeCtrl.cpp : implementation file
//

#include "stdafx.h"

#include <ospace/std/string>
#include <ospace/std/algorithm>
#include <ospace/string/tokenize.h>

#if !defined(OS_NO_STREAM_SUPPORT)
#include <ospace/stream.h>
#include <ospace/com/olestrea.h>
#endif // OS_NO_STREAM_SUPPORT

using namespace ospace::std::rel_ops;

#include "ShowOKS.h"
#include "OKSTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COksTreeCtrl

COksTreeCtrl::COksTreeCtrl()
	: m_ptLast (-1, -1), m_fDoChecks(false), m_uiTimer(0)
{
	EnableDragDrop();
	EnableScrolling();
	HideCursor (false);
}

COksTreeCtrl::~COksTreeCtrl()
{
	if (m_uiTimer) {
		KillTimer(TIMER_EXPAND);
		m_uiTimer = 0;
	}
	m_OKSTree.erase();
	m_setCheck.erase();
}

bool COksTreeCtrl::InitControl()
{
	if (!m_OKSImages.Create (IDB_OKSFOLDER, 16, 0, RGB(0, 0, 128))) {
		TRACE("Couldn't load imagelist bitmap.\n");
		return false;
	}
	SetImageList (&m_OKSImages, TVSIL_NORMAL);

	if (!m_OKSCheckMarks.Create (IDB_CHECKMARKS, 15, 0, RGB(255, 255, 255))) {
		TRACE("Couldn't load imagelist bitmap.\n");
		return false;
	}

// wenn eine alte Version der CommCtrl.dll installiert ist checkmarks selbst
// organisieren
CImageList *pIList = SetImageList (&m_OKSCheckMarks, TVSIL_STATE);

	m_fDoChecks = (NULL == pIList) ? true : false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob Node ein vom Typ NODETYPE_Special ist
bool COksTreeCtrl::IsSpecialNode (HTREEITEM hItem)
{
oks_tree::oks_node *pNode = (oks_tree::oks_node *)GetItemData (hItem);

	return COksElement::NODETYPE_Special == pNode -> value.GetType();
}

///////////////////////////////////////////////////////////////////////////////
// Datei öffnen und einlesen
HRESULT COksTreeCtrl::OpenAndParseFile (CString strFile, bool fAddNew)
{
FILE *pIn = NULL;

	pIn = fopen (strFile, "r");
	if (NULL == pIn) return E_ACCESSDENIED;

CWaitCursor wait;

// evtl. alles bisherige verwerfen
	if (!fAddNew) {
		m_OKSTree.erase();
		m_OKSTree = oks_tree();		// neu initialisieren
		m_setCheck.erase();
	}

// Baum mit Elementen füllen
char cbBuffer[1024];
os_tokenizer tok;

	tok.separators (",\"");
	tok.allow_empty_tokens (false);
	tok.include_separators (false);

	while (NULL != fgets (cbBuffer, sizeof(cbBuffer), pIn)) {
	// auf Kommentar prüfen und evtl. übergehen
		if (cbBuffer[0] == ';')	continue;

	// Eingabezeile zerlegen
	os_string strIn (cbBuffer);
	vector <os_string> tokens (tok.tokenize(strIn));

		ASSERT(tokens.size() >= 2);
		ASSERT(tokens[0].size() > 0);
		ASSERT(tokens[1].size() > 0);

	long lNumDigits = tokens.size() > 2 ? atol(tokens[2].c_str()) : 0;
	long lLeading = tokens.size() > 3 ? atol(tokens[3].c_str()) : 0;

		VERIFY(m_OKSTree.end() != m_OKSTree.insert (tokens[0].c_str(), tokens[1].c_str(), lNumDigits, lLeading));
	}

	fclose (pIn);

#if defined(_DEBUG)
	m_OKSTree.DumpAll();
#endif // _DEBUG

	return FillControlWithData();
}

#if !defined(OS_NO_STREAM_SUPPORT)

///////////////////////////////////////////////////////////////////////////////
// Persistente Daten aus dem gegebenen Stream einlesen
HRESULT COksTreeCtrl::Load (IStream *pIStm)
{
	try {
	iolestream stream (pIStm);
	os_bstream instream (os_adapter_for(stream));

		instream >> m_OKSTree;
	
	} catch (...) {
		return E_FAIL;
	}

	return FillControlWithData();
}

HRESULT COksTreeCtrl::Save (IStream *pIStm, BOOL fClearDirty)
{
	try {
	oolestream stream (pIStm);
	os_bstream outstream (os_adapter_for(stream));

		outstream << m_OKSTree;
	
	} catch (...) {
		return E_FAIL;
	}

	return S_OK;
}

#endif // OS_NO_STREAM_SUPPORT

///////////////////////////////////////////////////////////////////////////////
// StateImages behandeln
void COksTreeCtrl::HideStateImage (HTREEITEM hItem)
{
TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	tvi.state = 0;
	tvi.stateMask = TVIS_STATEIMAGEMASK;
	SetItem (&tvi);
}

bool COksTreeCtrl::ToggleCheckMark (HTREEITEM hItem)
{
bool fWasOn = false;
TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	if (GetItem (&tvi)) {
		fWasOn = ((tvi.state & TVIS_STATEIMAGEMASK) == TV_CHECK_ON);
		tvi.state = (fWasOn ? TV_CHECK_OFF : TV_CHECK_ON);
		tvi.stateMask = TVIS_STATEIMAGEMASK;
		SetItem (&tvi);
	}
	return fWasOn;
}	

///////////////////////////////////////////////////////////////////////////////
// CheckMark umschalten
void COksTreeCtrl::HandleCheckMark(CPoint point, UINT uiMsg)
{
TV_HITTESTINFO ht;

	ht.pt.x = point.x;
	ht.pt.y = point.y;

HTREEITEM hNewTarget = HitTest (&ht);

	if (hNewTarget && (ht.flags & TVHT_ONITEMSTATEICON)) {
		if (m_fDoChecks) 
			ToggleCheckMark (hNewTarget);
		NotifyChecked (hNewTarget, uiMsg, GetCheckState(hNewTarget));
	}
}

///////////////////////////////////////////////////////////////////////////////
// Ist dieses Item derzeit expanded
bool COksTreeCtrl::IsExpanded (HTREEITEM hItem)
{
TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	if (GetItem (&tvi)) 
		return tvi.state & TVIS_EXPANDED;
	
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Parent von Änderung des Checkstatus
void COksTreeCtrl::NotifyChecked (HTREEITEM hNewTarget, UINT uiMsg, UINT uiCheckState)
{
NM_TREEVIEWCHECK nmCheck;

	nmCheck.hdr.hwndFrom = GetSafeHwnd();
	nmCheck.hdr.idFrom = GetDlgCtrlID();
	nmCheck.hdr.code = TVN_CHECKSTATECHANGED;
	nmCheck.hItem = hNewTarget;
	nmCheck.action = uiMsg;
	nmCheck.state = uiCheckState;
	GetParent()->SendMessage(WM_NOTIFY, nmCheck.hdr.idFrom, (LPARAM)&nmCheck);
}

///////////////////////////////////////////////////////////////////////////////
// CheckState abfragen
UINT COksTreeCtrl::GetCheckState (HTREEITEM hItem)
{
TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	if (GetItem (&tvi)) 
		return tvi.state & TVIS_STATEIMAGEMASK;
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert StringTemplate, anhand dessen entschieden werden kann in welcher
// Parallel-Hierarchie das Item hängt
os_string COksTreeCtrl::GetCheckTemplate (HTREEITEM hItem)
{
	return GetCode (hItem);
}

///////////////////////////////////////////////////////////////////////////////
// Entscheidet, ob zwei Items in ein und der selben Parallel-Hierarchie hängen
bool JokerCmp (char ch1, char ch2)
{
	return (ch1 == '.' || ch2 == '.' || ch1 == ch2);
}

bool COksTreeCtrl::MustRemoveCheck (os_string strNewTempl, os_string strTempl)
{
// es müssen die Stellen verglichen werden, die in beiden Templates _keine_ 
// Platzhalter zu stehen haben, bei derartiger _Gleichheit_ kann der Checkmark 
// stehen bleiben, da beide dann zu unterschiedlichen Zweigen in Parallel-
// Hierarchien stehen.

	if (strNewTempl.size() != strTempl.size())
		return true;
	return !equal (strNewTempl.begin(), strNewTempl.end(), strTempl.begin(), JokerCmp);
}

///////////////////////////////////////////////////////////////////////////////
// Control mit Daten aus internem Baum füllen
class CFillPred :
	public oks_tree::oks_callback
{
private:
	HTREEITEM m_Items[MAX_OKS_LEVEL];	// jeweilige parent items
	bool m_fChecks[MAX_OKS_LEVEL];		// CheckMarks setzen 
	COksTreeCtrl &m_rTree;

public:
	CFillPred (COksTreeCtrl &rTree)
		: m_rTree(rTree) {}

	bool operator() (int iLevel, oks_tree::oks_ch_iter it, const os_string str)
	{
		if (iLevel >= sizeof(m_Items)/sizeof(m_Items[0])) {
			ASSERT(iLevel < sizeof(m_Items)/sizeof(m_Items[0]));
			return false;
		}

		m_fChecks[iLevel] = false;

	HTREEITEM hItem = NULL;
	COksElement::NODETYPE rgType = it -> value.GetType();

		if (iLevel > 0) {
		int iImage = 16+(iLevel-1)*4;	// erstmal ParentBildchen

			if (COksElement::NODETYPE_Special == rgType) {
				iImage += 3;			// ParallelHierarchie
				m_fChecks[iLevel] = true;
			} else
				m_fChecks[iLevel] = m_fChecks[iLevel-1];

			hItem = m_rTree.InsertItem (str.c_str(), iImage, iImage, m_Items[iLevel-1]);
		} else
			hItem = m_rTree.InsertItem (str.c_str(), 56, 56);

	// Checkmarks nur innerhalb von Parallel-Hierarchien anzeigen
		if (!m_fChecks[iLevel] || COksElement::NODETYPE_Special == rgType) 
			m_rTree.HideStateImage (hItem);

	// an jedem HTREEITEM hängt z.Zt der NodeTyp dran
		m_rTree.SetItemData (hItem, (DWORD)&(*it));
		m_Items[iLevel] = hItem;
		return true;
	}
};

HRESULT COksTreeCtrl::FillControlWithData (void)
{
// ListCtrl mit Bauminhalt füllen
	DeleteAllItems();		// erstmal alles löschen

	if (oks_traverse (m_OKSTree.begin(), m_OKSTree.end(), CFillPred(*this))) {
	HTREEITEM hItem = GetNextItem (NULL, TVGN_CHILD);

		while (NULL != hItem) {
			AdjustChildImages(hItem);
			hItem = GetNextItem (hItem, TVGN_NEXT);
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Bildchen richten
bool COksTreeCtrl::AdjustImage (HTREEITEM hItem)
{
	if (!ItemHasChildren (hItem)) 
		return true;		// nur Parents behandeln

	if (NULL == GetParentItem (hItem))
		return true;		// WurzelEinträge nicht behandlen

	if (IsSpecialNode (hItem))	
		return true;		// zugehöriger Node ist NODETYPE_Special

// Node muß behandelt werden
int iImage = 0;
int iSelImage = 0;

	if (!GetItemImage (hItem, iImage, iSelImage))
		return false;

	if (GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
		SetItemImage (hItem, iImage+1, iSelImage+1);	// ist expandiert
	else
		SetItemImage (hItem, iImage-1, iSelImage-1);	// ist collabiert

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Baum durchgehen und alle Childs mit richtigen Bildchen versehen
bool COksTreeCtrl::AdjustChildImages (HTREEITEM hItem)
{
	if (NULL == hItem)
		return false;

	if (!ItemHasChildren (hItem)) {
	int iImage = 0;
	int iSelImage = 0;

		if (GetItemImage (hItem, iImage, iSelImage))
			SetItemImage (hItem, iImage+2, iSelImage+2);	// ist child
		return true;
	}

HTREEITEM hChild = GetChildItem (hItem);

	while (NULL != hChild) {
		if (!AdjustChildImages (hChild))
			return false;
		hChild = GetNextItem (hChild, TVGN_NEXT);
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// Platzhalter zu Nullen machen
extern bool trim_right (os_string &rStr, int c);

os_string ConvertJokers (os_string strSel)
{
int iDel = strSel.find_first_of('.');

	while (iDel >= 0) {
		strSel[iDel] = '0';
		iDel = strSel.find_first_of('.');
	}

	trim_right (strSel, '0');
	return strSel;
}

///////////////////////////////////////////////////////////////////////////////
// Kombinieren zweier Templates, um vollen Beschreibungstext generieren zu 
// können
char CombineCodeProc (char ch1, char ch2)
{
	if (ch1 == '.')
		return ch2;
		
	if (ch2 == '.')
		return ch1;

	ASSERT(ch1 == ch2);		// alles andere muß übereinstimmen
	return ch1;
}

os_string CombineCodes (os_string str1, os_string str2)
{
os_string strRes;
os_insert_iterator<os_string> ins (strRes, strRes.begin());

	if (str1.size() >= str2.size()) {
	os_insert_iterator<os_string> it = 
		transform (str2.begin(), str2.end(), str1.begin(), ins, CombineCodeProc);

	} else {
	os_insert_iterator<os_string> it = 
		transform (str1.begin(), str1.end(), str2.begin(), ins, CombineCodeProc);

	}
	return strRes;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert vollständigen Beschreibungstext entsprechend Selektion
os_string COksTreeCtrl::GetFullText (void)
{
os_string strText;
os_string strCode(GetCodeConverted());

	m_OKSTree.generate_text (strCode.c_str(), strText);
	return strText;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert vollständigen OKS entsprechend Selektion
os_string COksTreeCtrl::GetCode (HTREEITEM hItem)
{
	if (NULL == hItem)
		hItem = GetSelectedItem();
	if (NULL == hItem) return "";

// z.Zt. lediglich selektiertes Item verwenden
os_string strSel (GetItemText(hItem));
int iDel = strSel.find_first_of(' ');

	if (iDel < 0) return "";

	return strSel.substr(0, iDel);		// OKS abschneiden
}

os_string COksTreeCtrl::GetCodeConverted (HTREEITEM hItem)
{
// Code zusammenstellen aus selektiertem Item und allen
// Items mit Checkmarks
os_string str (GetCode(hItem));

	if (0 == str.size()) return str;

	for (CCheckMarks::iterator it = m_setCheck.begin();
		 it != m_setCheck.end(); ++it)
	{
	os_string strT (GetCode ((*it).GetItem()));

		str = CombineCodes (str, strT);
	}
	return ConvertJokers (str);
}

///////////////////////////////////////////////////////////////////////////////
// Overrideables for Drag'n Drop

/***********************************************************/
// AllowDragOperation - virtual function. Override to 
// control whether an item can be moved or not.
// Current implementation allows dragging for icon and 
// small icon views.
// Parameters: Current view and item to move.
// Return TRUE to allow drag, FALSE to disallow.
/***********************************************************/
BOOL COksTreeCtrl::AllowDragOperation (HTREEITEM hDragItem)
{
	ASSERT (0 == m_uiTimer);		// Timer darf nicht aktiv sein
	m_ptLast = CPoint (-1, -1);
	return TRUE;
}

/***********************************************************/
// HandleDragMove - overrideable virtual function.
// Parameters: CImageList pointer. This is initially set 
// to the default listview image. pt indicates the client 
// position of the mouse.
// The default version does nothing. 
// Set the imagelist pointer to what you want displayed and 
// the point at which it is to be displayed.
/***********************************************************/
void COksTreeCtrl::HandleDragMove (CImageList *pDragImage, CPoint& pt)
{
	if (pt != m_ptLast) {
	// letzte Position merken
		m_ptLast = pt;
		if (m_uiTimer) {
			KillTimer (TIMER_EXPAND);
			m_uiTimer = 0;
		}
	} else if (0 == m_uiTimer) {
	// Hilite target
	TV_HITTESTINFO tvHit;

		tvHit.pt.x = pt.x;
		tvHit.pt.y = pt.y;

	HTREEITEM hTarget = HitTest (&tvHit);

		if (NULL != hTarget && !IsExpanded(hTarget) && ItemHasChildren(hTarget))
			m_uiTimer = SetTimer (TIMER_EXPAND, TIMER_EXPAND_TIMEOUT, NULL);
	}
}

/***********************************************************/
// HandleItemMove - virtual function. Override to do the 
// actual move of the item.
// Current implementation moves the item for icon and 
// small icon views.
// Parameters: Dragged item, point at which item was 
// dropped (client coordinates).
/***********************************************************/
void COksTreeCtrl::HandleItemMove (HTREEITEM hDragItem, CPoint point)
{
	if (m_uiTimer) {
		KillTimer (TIMER_EXPAND);
		m_uiTimer = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// COksTreeCtrl message handlers

BEGIN_MESSAGE_MAP(COksTreeCtrl, CDragDropTreeCtrl)
	//{{AFX_MSG_MAP(COksTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
	ON_NOTIFY_REFLECT_EX(TVN_SELCHANGED, OnSelchanged)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT_EX(TVN_CHECKSTATECHANGED, OnCheckStateChanged)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void COksTreeCtrl::OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemNew.hItem;
	
	AdjustImage (hItem);
	*pResult = 0;
}

BOOL COksTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemNew.hItem;
UINT uiCheck = GetCheckState(hItem);

	if (TV_CHECK_OFF == uiCheck) {
		ToggleCheckMark (hItem);
		NotifyChecked (hItem, 0, TV_CHECK_ON);
	}

	*pResult = 0;
	return FALSE;	// continue processing
}

void COksTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDragDropTreeCtrl::OnLButtonDown(nFlags, point);
	HandleCheckMark (point, WM_LBUTTONDOWN);
}

void COksTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CDragDropTreeCtrl::OnLButtonDblClk(nFlags, point);
	HandleCheckMark (point, WM_LBUTTONDBLCLK);
}

BOOL COksTreeCtrl::OnCheckStateChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEWCHECK* pNMTreeView = (NM_TREEVIEWCHECK*)pNMHDR;

	if (TV_CHECK_OFF == (pNMTreeView->state & TVIS_STATEIMAGEMASK)) {
	// eine CheckMark entfernt
	CCheckMarks::iterator it = m_setCheck.find (CCheckMarkInfo(pNMTreeView->hItem));

		if (it != m_setCheck.end())
			m_setCheck.erase (it);					// aus Liste entfernen
	} else {
	// eine CheckMark gesetzt, alle jetzt überflüssigen Checks entfernen
	os_string strNewTempl (GetCheckTemplate (pNMTreeView->hItem));

		for (CCheckMarks::iterator it = m_setCheck.begin();
			 it != m_setCheck.end(); /**/)
		{
			if (MustRemoveCheck (strNewTempl, (*it).GetTemplate())) {
			HTREEITEM hItem = (*it).GetItem();
			os_string strText = (*it).GetTemplate();

				VERIFY(ToggleCheckMark (hItem));	// muß gesetzt gewesen sein
				
				++it;
				NotifyChecked (hItem, 0, TV_CHECK_OFF);
			} else
				++it;
		}

	// im set speichern
		Select (pNMTreeView->hItem, TVGN_CARET);
		m_setCheck.insert (CCheckMarkInfo (pNMTreeView->hItem, strNewTempl));
	}
	*pResult = 0;

	return FALSE;	// continue processing
}

// wird gerufen, wenn ein Item beim draggen länger als TIMER_EXPAND_TIMEOUT
// aktiv ist
void COksTreeCtrl::OnTimer(UINT nIDEvent) 
{
	if (TIMER_EXPAND == nIDEvent) {
	HTREEITEM hTarget = GetDropHilightItem();

		if (NULL != hTarget && !IsExpanded(hTarget) && ItemHasChildren(hTarget)) {
			KillTimer (TIMER_EXPAND);
			m_uiTimer = 0L;

			ImageList_DragShowNolock (FALSE);
			Expand (hTarget, TVE_EXPAND);
			UpdateWindow();
			ImageList_DragShowNolock (TRUE);
		}
	}

	CDragDropTreeCtrl::OnTimer(nIDEvent);
}

