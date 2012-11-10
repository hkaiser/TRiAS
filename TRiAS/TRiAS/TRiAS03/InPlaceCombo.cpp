// InPlaceCombo.cpp : implementation file
//

#include "trias03p.hxx"
#include <InPlaceCombo.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInPlaceCombo

static ComboBox::ComboStyle GetComboStyle (DWORD dwStyle)
{
	dwStyle &= CBS_DROPDOWNLIST;

	if (dwStyle == CBS_DROPDOWNLIST)
		return ComboBox::DropDownList;
	if (dwStyle == CBS_DROPDOWN)
		return ComboBox::DropDown;
	if (dwStyle == CBS_SIMPLE)
		return ComboBox::Simple;

	TX_ASSERT(false);		// falscher ComboStyle
	return ComboBox::Simple;
}

CInPlaceCombo::CInPlaceCombo (pWindow pW, CvID uiID, Point pt, Dimension dim, DWORD dwStyle)
	: ControlWindow (new ComboBox (pW, uiID, pt, dim, GetComboStyle(dwStyle))),
	m_dwStyle (dwStyle)
{
	m_bESC = false;
}

bool CInPlaceCombo::Create (int iItem, int iSubItem, CStringList &rlstItems, int nSel, LPCSTR pcInitEntry)
{
	if (NULL == GetControl()) 
		return false;

	m_iItem = iItem;
	m_iSubItem = iSubItem;

bool fVisible = (m_dwStyle & WS_VISIBLE) ? true : false;

	SetStyle (m_dwStyle & ~WS_VISIBLE);
	if (!FInit())
		return false;

// Set the proper font
HFONT hF = (HFONT)GetParent()->ForwardEvent(WM_GETFONT);

	ForwardEvent (WM_SETFONT, (WPARAM)hF);

// alle Elemente zur Box hinzufügen
	for (CStringList::iterator it = rlstItems.begin(); 
		 it != rlstItems.end(); 
		 ++it)
	{
		GetComboBox() -> AddString ((*it).c_str());
	}

	if (-1 != nSel) 
		GetComboBox() -> ChangeCurrentIndex (nSel);
	else if (NULL != pcInitEntry) {
		TX_ASSERT(ComboBox::DropDownList == GetComboStyle(m_dwStyle));
		GetComboBox() -> SetText (pcInitEntry);
	}

	if (fVisible) {
		Show();
		SetFocus();
	}
	return true;
}

CInPlaceCombo::~CInPlaceCombo()
{
}

/////////////////////////////////////////////////////////////////////////////
// CInPlaceCombo message handlers

BOOL CInPlaceCombo::PreTranslateMsg (MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) {
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return TRUE;				// DO NOT process further
		}
	}
	return ControlWindow::PreTranslateMsg(pMsg);
}

void CInPlaceCombo::FocusChange (FocusChangeEvt e) 
{
	ControlWindow::FocusChange (e);

	if (!e.gotFocus()) {
//		if (ComboBox::DropDownList != GetComboStyle(m_dwStyle)) {
//		// evtl. ist der Focus jetzt in unserem child
//			if (GetWindow (Handle(API_WINDOW_HWND), GW_CHILD) == reinterpret_cast<HWND>(e.WParam()))
//				return;
//		}

	char cbBuffer[_MAX_PATH];

		cbBuffer[0] = '\0';
		GetComboBox() -> GetString (cbBuffer, -1, sizeof(cbBuffer));

	// Send Notification to parent of ListView ctrl
	LV_DISPINFO dispinfo;
	HWND hParent = GetParent()->Handle(API_WINDOW_HWND);

		dispinfo.hdr.hwndFrom = hParent;
		dispinfo.hdr.idFrom = ::GetDlgCtrlID (Handle(API_WINDOW_HWND));
		dispinfo.hdr.code = LVN_ENDLABELEDIT;

		dispinfo.item.mask = LVIF_TEXT;
		dispinfo.item.iItem = m_iItem;
		dispinfo.item.iSubItem = m_iSubItem;
		dispinfo.item.pszText = m_bESC ? NULL : cbBuffer;
		dispinfo.item.cchTextMax = m_bESC ? 0 : strlen(cbBuffer);

		GetParent()->GetParent()->ForwardEvent(WM_NOTIFY, GetDlgCtrlID(hParent), (LPARAM)&dispinfo);

		Hide();					// sofort ausblenden 
		PostEvent(WM_CLOSE);	// jetzt zerlegen
	}
}

void CInPlaceCombo::KeyDown (KeyEvt e)
{
	if (WM_CHAR == e.Msg()) {
	UINT nChar = e.Keycode();

		if (nChar == VK_ESCAPE || nChar == VK_RETURN)
		{
			if (nChar == VK_ESCAPE)
				m_bESC = TRUE;
			GetParent() -> SetFocus();
			return;
		}
	}
	ControlWindow::KeyDown (e);
}

LRESULT CInPlaceCombo::Dispatch (Event e) 
{
LRESULT lResult = ControlWindow::Dispatch (e);
	
	if (WM_NCDESTROY == e.Msg())
		delete this;
	return lResult;
}

void CInPlaceCombo::OnCloseup() 
{
	GetParent()->SetFocus();
}

void CInPlaceCombo::SetHorizontalExtent (UINT uiExtent)
{
	if (IsWin40())
		ForwardEvent(CB_SETHORIZONTALEXTENT, uiExtent, 0);
}

int CInPlaceCombo::SetItemHeight (int nIndex, UINT cyItemHeight)
{
	return (int)ForwardEvent(CB_SETITEMHEIGHT, nIndex, MAKELONG(cyItemHeight, 0));
}

