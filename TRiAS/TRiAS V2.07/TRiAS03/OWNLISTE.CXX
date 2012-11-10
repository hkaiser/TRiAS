// Funktionsdefinitionen fuer OwnerDrawListBox --------------------------------
// File: OWNLIST.CXX

#include "trias03p.hxx"

#include <ownlist.hxx>
#include <ownliste.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstruktoren --------------------------------------------------------------
OwnerDrawListBoxEx :: OwnerDrawListBoxEx (pDialogWindow pDW, ResID rsc) 
		    : OwnerDrawListBox ((Control *)new MultiSelListBox (pDW, rsc))
{
#if defined(WIN32)
	m_fMouseOpPending = false;
	m_fCaptured = false;
	m_fDragDrop = false;
#endif // WIN32
}

OwnerDrawListBoxEx :: ~OwnerDrawListBoxEx (void) 
{
	// nothing to do
}

#if defined(WIN32)
BOOL OwnerDrawListBoxEx::EnableDragDrop (BOOL fDragDrop)
{
BOOL fOldDD = m_fDragDrop;

	m_fDragDrop = fDragDrop;
	return fOldDD;
}
#endif // WIN32

class NakedDialogWindow : public DialogWindow {
public:
	void FocusChange (FocusChangeEvt e) { DialogWindow :: FocusChange (e); }
};

void OwnerDrawListBoxEx :: FocusChange (FocusChangeEvt e)
{
NakedDialogWindow *pW = (NakedDialogWindow *)GetParent(); 

	if (pW) pW -> FocusChange (e);
	OwnerDrawListBox :: FocusChange (e);
}

// Memberfunktionen -----------------------------------------------------------
int OwnerDrawListBoxEx :: GetNoSelected (void)
{
	if (LocCtrl() == NULL) return LB_ERR;

return LocCtrl() -> GetNoSelected();
}

BOOL OwnerDrawListBoxEx :: ClearSelected (void)
{
	if (LocCtrl() == NULL) return FALSE;

return LocCtrl() -> ClearSelected();
}

int OwnerDrawListBoxEx :: GetFirstSelected (void)
{
	if (LocCtrl() == NULL) return LB_ERR;

return LocCtrl() -> GetFirstSelected();
}

int OwnerDrawListBoxEx :: GetNextSelected (void)
{
	if (LocCtrl() == NULL) return LB_ERR;

return LocCtrl() -> GetNextSelected();
}

BOOL OwnerDrawListBoxEx :: ChangeSelected (int index, BOOL iFlag)
{
	if (LocCtrl() == NULL) return LB_ERR;

return LocCtrl() -> ChangeSelected (index, iFlag);
}

BOOL OwnerDrawListBoxEx :: ChangeSelected (Range R, BOOL iFlag)
{
	if (LocCtrl() == NULL) return LB_ERR;

return LocCtrl() -> ChangeSelected (R, iFlag);
}

// TRUE: Item ist selektiert, FALSE: Item ist nicht selektiert
BOOL OwnerDrawListBoxEx :: GetSelection (short Index) 
{
	return (ListBox_GetSel (GetHandle(), int(Index)) > 0);
}

int OwnerDrawListBoxEx :: GetCaretIndex (void)
{
	return ListBox_GetCaretIndex (GetHandle());
}

int OwnerDrawListBoxEx :: SetCaretIndex (int iIndex, BOOL iFlag)
{
	return ListBox_SetCaretIndexEx (GetHandle(), iIndex, iFlag);
}

#if defined(WIN32)

///////////////////////////////////////////////////////////////////////////////
// support for Drag'n Drop
DWORD g_dwScrollDist = ::GetProfileInt("windows", "DragMinDist", DD_DEFDRAGMINDIST);

///////////////////////////////////////////////////////////////////////////////
// MouseButtons untersuchen
void OwnerDrawListBoxEx::MouseButtonDn (MouseEvt e)
{
	if (!m_fDragDrop) {
		OwnerDrawListBox::MouseButtonDn(e);
		return;
	}
		
// Get the index value of the item under the mouse
Point pt (e.Where());
int iSel = IndexFromPoint(pt);

// If no item was hit, there is nothing to do
    if (LB_ERR == iSel) {
		OwnerDrawListBox::MouseButtonDn(e);
		return;
	}

	m_ptMouseDown = pt;	// Save the position the mouse is in

// if the item is already selected, defer the operation until the 
// mouse button goes up since this might be the start of a drag op.
	if (GetSelection (iSel)) {
		m_fMouseOpPending = true;
	
	// Focus auf aktuellen Eintrag umsetzen
		LocCtrl()->SetCaretIndex (iSel);

	// set mouse capture
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		MouseTrap (CVOn);
#else
		MouseTrap (On);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
		m_fCaptured = true;
	} else {
		m_fMouseOpPending = false;
		OwnerDrawListBox::MouseButtonDn(e);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Klasse, die eine BUTTONUP-Message in eine entsprechenenden BUTTONDOWN-Message
// umwandelt (ugly hack!)
class CButtonDnEvt : public MouseEvt {
public:
	CButtonDnEvt (Event &e)
	{
		wMsg = (WM_LBUTTONUP == e.Msg()) ? WM_LBUTTONDOWN : WM_RBUTTONDOWN;
		wParam = e.WParam();
		lParam = e.LParam();
		EvtExtra = NULL;
	}
};

void OwnerDrawListBoxEx::MouseButtonUp (MouseEvt e)
{
	if (m_fDragDrop && m_fCaptured) {
		if (m_fMouseOpPending) {
			m_fMouseOpPending = false;
			OwnerDrawListBox::MouseButtonDn(CButtonDnEvt(e));
		}
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		MouseTrap (CVOff);
#else
		MouseTrap (Off);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
		m_fCaptured = false;

		OwnerDrawListBox::MouseButtonUp(e);

	// fehlende LBN_SELCHANGE nachsenden
		if (e.isLeftButton()) {
		HWND hWnd = GetHandle();

			TX_ASSERT(::IsWindow(hWnd));
			::SendMessage (GetParent()->Handle(API_WINDOW_HWND), WM_COMMAND, 
						   MAKELONG(GetDlgCtrlID(hWnd), LBN_SELCHANGE),
						   (LPARAM)hWnd);
		}
	} else
		OwnerDrawListBox::MouseButtonUp(e);
}

void OwnerDrawListBoxEx::MouseDrag (MouseEvt e)
{
	if (m_fDragDrop && m_fCaptured) {
	// See if the mouse has moved far enough to start
	// a drag operation
	Point pt (e.Where());

		if ((abs(pt.X() - m_ptMouseDown.X()) > (long)g_dwScrollDist) || 
			(abs(pt.Y() - m_ptMouseDown.Y()) > (long)g_dwScrollDist)) 
		{
		// release the mouse capture
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
			MouseTrap (CVOff);
#else
			MouseTrap (Off);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
            m_fCaptured = false;

		// Tell the parent window to begin a drag and drop op.
		static NM_LISTBOX nmData;
		HWND hWnd = GetHandle();

			TX_ASSERT(::IsWindow(hWnd));
			nmData.hdr.hwndFrom = hWnd;
			nmData.hdr.idFrom = GetDlgCtrlID(hWnd);
			nmData.hdr.code = e.isLeftButton() ? LBN_BEGINDRAG : LBN_BEGINRDRAG;

		Point pt (e.Where());

			nmData.iItem = IndexFromPoint(pt);
			nmData.ptDrag = (POINT &)pt;
			nmData.dwFlags = e.WParam();
			::PostMessage (GetParent()->Handle(API_WINDOW_HWND),
						   WM_FAKENOTIFYFORWIN95, (WPARAM)nmData.hdr.idFrom,
						   (LPARAM)&nmData);
		}
	}
	OwnerDrawListBox::MouseDrag(e);
}

int OwnerDrawListBoxEx::IndexFromPoint (Point point, BOOL *pfPastLastEntry)
{
int iTop = ListBox_GetTopIndex (GetHandle());

	if (pfPastLastEntry) *pfPastLastEntry = false;
    if (LB_ERR == iTop) return LB_ERR; // no items to select

#if defined(_DEBUG)
DWORD dwStyle = GetWindowLong (GetHandle(), GWL_STYLE);

    TX_ASSERT(!(dwStyle & LBS_MULTICOLUMN));		// Make sure it isn't multi-column
    TX_ASSERT(!(dwStyle & LBS_OWNERDRAWVARIABLE));	// Make sure all the items are the same height
#endif // _DEBUG

Rectangle Rc = CanvasRect();						// Größe der ListBox
int iHeight = ListBox_GetItemHeight (GetHandle(), 0);
long lY = Rc.Top()-Rc.Bottom()-point.Y();
int iSel = iTop + ((lY+iHeight) / iHeight) -1;

    if (iSel >= LocCtrl()->GetCount()) {
		if (pfPastLastEntry)
			*pfPastLastEntry = true;		// hinter dem letzten Eintrag
        return LB_ERR;
	}

    return iSel;
}

#endif // WIN32
