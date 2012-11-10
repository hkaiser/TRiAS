// Klassendefinition für eine Listbox, die CheckBoxes enthält -----------------
// File: CHECKLST.CXX

#include "trias03p.hxx"

#include <containr.hxx>

#include <limits.h>
#include <checklst.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktoren --------------------------------------------------------------
EXPORT03 CCheckListBox :: CCheckListBox (pDialogWindow pDW, ResID rsc) 
			: ControlWindow (new ListBox (pDW, rsc))
{
	if (GetControl() == NULL)
		db_error (EC_NOMEMORY, RC_ctOwnerDrawListBox);
	m_uiCookie = 100;
}

EXPORT03 CCheckListBox :: CCheckListBox (Control *pL) 
			: ControlWindow (pL)
{
	if (GetControl() == NULL)
		db_error (EC_NOMEMORY, RC_ctOwnerDrawListBox);
}

EXPORT03 CCheckListBox :: ~CCheckListBox (void) 
{
	Clear();
	if (GetControl()) delete (ListBox *)GetControl();
}


// Memberfunktionen -----------------------------------------------------------
// Funktionen zum Handling der einzelnen Einträge -----------------------------
int EXPORT03 CCheckListBox :: AddItem (const char *pString, int iIndex) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

// Text zu Listbox hinzufügen
int iItem = LB_ERR;
HWND hCtl = GetHandle();

	if (iIndex == LB_ERR)
		iItem = ListBox_AddString (hCtl, pString);
	else
		iItem = ListBox_InsertString (hCtl, iIndex, pString);
	if (iItem == LB_ERR)
		return LB_ERR;

// CheckBox generieren
Rectangle Rc;

	ListBox_GetItemRect (hCtl, iItem, &Rc);

// CommonVu - Käse rausrechnen
Rectangle rcC = CanvasRect();
CoOrd iY = rcC.Top()-rcC.Bottom();
CoOrd iHeight = Rc.Bottom()-Rc.Top()-3;
CheckBox *pBox = new CheckBox (this, ++m_uiCookie, Point (2, iY-Rc.Bottom()+1), 
			       Dimension (iHeight, iHeight));
	if (pBox == NULL) return LB_ERR;	// E_OUTOFMEMORY

#if defined(WIN32)
	if (IsWin40())
		pBox -> SetStyle (BS_FLAT|BS_AUTOCHECKBOX);
#endif // WIN32

	ListBox_SetItemData (hCtl, iItem, (LONG)pBox);
	pBox -> Show();

return iItem;
}

// Liefert Text eines Items ---------------------------------------------------
bool EXPORT03 CCheckListBox :: GetItem (char *pBuffer, int iLen, int iIndex)
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HWND hCtl = GetHandle();

	if (iIndex == LB_ERR) {	// aktuellen Eintrag lesen
		iIndex = ListBox_GetCurSel (hCtl);
		if (iIndex == LB_ERR) return false;
	} else if (iIndex >= ListBox_GetCount (hCtl))
		return false;		// Index zu groß

int iCurrLen = ListBox_GetTextLen (GetHandle(), iIndex);
char cbBuffer[_MAX_PATH];

	if (iCurrLen > _MAX_PATH-1) return false;
	ListBox_GetText (GetHandle(), iIndex, cbBuffer);
	iLen = min (iLen-1, iCurrLen);
	strncpy (pBuffer, cbBuffer, iLen);
	pBuffer[iLen] = '\0';

return true;
}

// Suchen eines bestimmten Eintrages ------------------------------------------
int EXPORT03 CCheckListBox :: FindString (const char *pString, int iIndexStart)
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

return ListBox_FindString (GetHandle(), iIndexStart, pString);
}


int EXPORT03 CCheckListBox :: GetCurrentIndex (void)
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

return ListBox_GetCurSel (GetHandle());
}

void EXPORT03 CCheckListBox :: ChangeCurrentIndex (int iIndex)
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

	ListBox_SetCurSel (GetHandle(), iIndex);
}


// liefert Anzahl der in der ListBox der ComboBox verbleibenden Items
bool EXPORT03 CCheckListBox :: DelItem (int iIndex) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HWND hCtl = GetHandle();

	if (iIndex == LB_ERR) {	// aktuellen Eintrag lesen
		iIndex = ListBox_GetCurSel (hCtl);
		if (iIndex == LB_ERR) return false;
	} else if (iIndex >= ListBox_GetCount (hCtl))
		return false;		// Index zu groß

// Eintrag löschen
	if (iIndex != LB_ERR) {
	CheckBox *pBox = GetCheckBox (iIndex);

		DELETE (pBox);
		ListBox_SetItemData (hCtl, iIndex, NULL);
		return ListBox_DeleteString (hCtl, iIndex);
	} 

// Fehler: kein Eintrag selektiert und kein Index gegeben
return false;
}

// löscht alle Einträge aus Listbox -------------------------------------------
bool EXPORT03 CCheckListBox :: Clear (void) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HWND hCtl = GetHandle();
int iCnt = ListBox_GetCount (hCtl);

	for (int i = iCnt-1; i >= 0; i--) {
		if (!DelItem (i))
			return false;
	}

return true;
}

bool EXPORT03 CCheckListBox :: FreeItem (int iIndex)
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

CheckBox *pBox = GetCheckBox (iIndex);

	if (pBox) {
		delete pBox;
		ListBox_SetItemData (GetHandle(), iIndex, NULL);
		return true;
	}

return false;
}

// Behandlung der einzelnen CheckBoxEinträge ----------------------------------
bool EXPORT03 CCheckListBox :: GetItemChecked (int iIndex) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HWND hCtl = GetHandle();

	if (iIndex == LB_ERR) {	// aktuellen Eintrag lesen
		iIndex = ListBox_GetCurSel (hCtl);
		if (iIndex == LB_ERR) return false;
	} else if (iIndex >= ListBox_GetCount (hCtl))
		return false;		// Index zu groß

// CheckBox besorgen
CheckBox *pBox = GetCheckBox (iIndex);

	if (pBox == NULL) return false;

return pBox -> isChecked();
}

bool EXPORT03 CCheckListBox :: SetItemChecked (int iIndex, bool fCheck) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HWND hCtl = GetHandle();

	if (iIndex == LB_ERR) {	// aktuellen Eintrag lesen
		iIndex = ListBox_GetCurSel (hCtl);
		if (iIndex == LB_ERR) return false;
	} else if (iIndex >= ListBox_GetCount (hCtl))
		return false;		// Index zu groß

// CheckBox besorgen
CheckBox *pBox = GetCheckBox (iIndex);

	if (pBox == NULL) return false;

bool fOldChecked = pBox -> isChecked();

	pBox -> SetChecked (fCheck);

return fOldChecked;
}

bool EXPORT03 CCheckListBox :: ToggleItemChecked (int iIndex) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HWND hCtl = GetHandle();

	if (iIndex == LB_ERR) {	// aktuellen Eintrag lesen
		iIndex = ListBox_GetCurSel (hCtl);
		if (iIndex == LB_ERR) return false;
	} else if (iIndex >= ListBox_GetCount (hCtl))
		return false;		// Index zu groß

// CheckBox besorgen
CheckBox *pBox = GetCheckBox (iIndex);

	if (pBox == NULL) return false;

bool fOldChecked = pBox -> isChecked();

	pBox -> SetChecked (!fOldChecked);

return fOldChecked;
}

unsigned int EXPORT03 CCheckListBox :: GetItemID (int iIndex) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HWND hCtl = GetHandle();

	if (iIndex == LB_ERR) {	// aktuellen Eintrag lesen
		iIndex = ListBox_GetCurSel (hCtl);
		if (iIndex == LB_ERR) return 0;
	} else if (iIndex >= ListBox_GetCount (hCtl))
		return 0;	// Index zu groß

// CheckBox besorgen
CheckBox *pBox = GetCheckBox (iIndex);

	if (pBox == NULL) return 0;

return (unsigned int)(pBox -> GetID());
}

int EXPORT03 CCheckListBox :: GetItemIndex (unsigned int iID) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

int iCnt = ListBox_GetCount (GetHandle());

	for (int i = 0; i < iCnt; i++) {
	CheckBox *pBox = GetCheckBox (i);
		
		if (pBox && pBox -> GetID() == iID)
			return i;
	}

return LB_ERR;
}

bool EXPORT03 CCheckListBox :: EnableItem (int iIndex, bool fEnable) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HWND hCtl = GetHandle();

	if (iIndex == LB_ERR) {	// aktuellen Eintrag lesen
		iIndex = ListBox_GetCurSel (hCtl);
		if (iIndex == LB_ERR) return false;
	} else if (iIndex >= ListBox_GetCount (hCtl))
		return false;		// Index zu groß

// CheckBox besorgen
CheckBox *pBox = GetCheckBox (iIndex);
bool fWasEnabled = IsWindowEnabled (pBox -> Handle());

	if (pBox == NULL) return false;
	if (fEnable)
		pBox -> Enable();
	else
		pBox -> Disable();

return fWasEnabled;
}

bool EXPORT03 CCheckListBox :: IsItemEnabled (int iIndex) 
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HWND hCtl = GetHandle();

	if (iIndex == LB_ERR) {	// aktuellen Eintrag lesen
		iIndex = ListBox_GetCurSel (hCtl);
		if (iIndex == LB_ERR) return false;
	} else if (iIndex >= ListBox_GetCount (hCtl))
		return false;		// Index zu groß

// CheckBox besorgen
CheckBox *pBox = GetCheckBox (iIndex);

	if (pBox != NULL) return IsWindowEnabled (pBox -> Handle());

return false;
}

// interne Member -------------------------------------------------------------
CheckBox *CCheckListBox :: GetCheckBox (int iIndex)
{
LONG lItem = ListBox_GetItemData (GetHandle(), iIndex);

	if (lItem == LB_ERR) return NULL;

return (CheckBox *)lItem;
}

char *CCheckListBox :: GetItemText (int iIndex, char *pBuffer, int iLen)
{
char cbBuffer[_MAX_PATH];

	if (ListBox_GetText (GetHandle(), iIndex, cbBuffer) == LB_ERR)
		return NULL;

int iToCopy = min (iLen-1, _MAX_PATH-1);

	strncpy (pBuffer, cbBuffer, iToCopy);
	pBuffer[iToCopy] = '\0';

return pBuffer;
}

// Item malen -----------------------------------------------------------------
bool EXPORT03 CCheckListBox :: DrawItem (DrawItemEvt &e)
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

	SelectItem (e);
	if (e.hasFocus()) 
		FocusItem (e);

return true;
}

bool EXPORT03 CCheckListBox :: FocusItem (DrawItemEvt &e)
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);
Rectangle rcItem = CanvasRect();
Rectangle rcC = e.ItemSize();

	rcItem.Top() = rcC.Top();
	rcItem.Bottom() = rcC.Bottom();
	rcItem.Left() += 16;

	DrawFocusRect (hDC, (RECT *)&rcItem);

return true;
}

bool EXPORT03 CCheckListBox :: SelectItem (DrawItemEvt &e)
{
// wenn Objekt ungültig ist
	TX_ASSERT(GetControl() != NULL);

char szText[64];
Rectangle rcItem = CanvasRect();
Rectangle rcC = e.ItemSize();
HBRUSH hBrush;
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);
RECT rcClip;

	GetClipBox (hDC, &rcClip);

	rcItem.Top() = rcC.Top();
	rcItem.Bottom() = rcC.Bottom();
	rcItem.Left() += 16;	 //  Move right so the checkbox isn't clobbered
	
	hBrush = CreateSolidBrush (GetSysColor (COLOR_WINDOW));
	FillRect (hDC, (RECT *)&rcItem, hBrush);
	DeleteObject (hBrush);
                                        
	Default ((Event &)e);

	if (GetItemText (e.GetItemID(), szText, sizeof(szText))) {
	CheckBox *pBox = GetCheckBox (e.GetItemID());
	bool fEnabled = IsWindowEnabled (pBox -> Handle());

		if (!e.isSelected() || !fEnabled) {
			SetBkColor (hDC, GetSysColor (COLOR_WINDOW));
			if (fEnabled)
				SetTextColor (hDC, GetSysColor (COLOR_WINDOWTEXT));
			else
				SetTextColor (hDC, GetSysColor (COLOR_GRAYTEXT));
		} else {
			SetBkColor (hDC, GetSysColor (COLOR_HIGHLIGHT));
			SetTextColor (hDC, GetSysColor (COLOR_HIGHLIGHTTEXT));
		}
		ExtTextOut (hDC, rcItem.Left() +3, rcItem.Top() +1, ETO_CLIPPED|ETO_OPAQUE, 
			    (const RECT *)&rcItem, szText, lstrlen (szText), NULL);
	}			

return true;
}

// EventHandler ---------------------------------------------------------------
void EXPORT03 CCheckListBox :: ButtonClick (ControlEvt e)
{
#if defined(WIN32)
	GetParent() -> ForwardEvent ((Event &)e);
#else
NakedEvt &ne = (NakedEvt &)e;

	SendMessage (GetParent() -> Handle(), WM_COMMAND, ne.wparam(), ne.lparam());
#endif // WIN32
	ControlWindow :: ButtonClick (e);
}
