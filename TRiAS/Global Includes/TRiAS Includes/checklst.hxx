// Klassendefinition für eine Listbox, die CheckBoxes enthält -----------------
// File: CHECKLST.HXX

#if !defined(CHECKLST_HXX)
#define CHECKLST_HXX

class CCheckListBox : public ControlWindow {
private:
	unsigned int m_uiCookie;	// ID für CheckBox's

	CheckBox *GetCheckBox (int iIndex);
	char *GetItemText (int iIndex, char *pBuffer, int iLen);

	HWND GetHandle (void) { return GetControl() -> Handle(); }

protected:
_TRIAS03_ENTRY void ButtonClick (ControlEvt e);

public:
	_TRIAS03_ENTRY CCheckListBox (pDialogWindow pDW, ResID rsc);
	_TRIAS03_ENTRY CCheckListBox (Control *pL);
	_TRIAS03_ENTRY ~CCheckListBox (void);

_TRIAS03_ENTRY bool FInit (void);

_TRIAS03_ENTRY int AddItem (const char *pString, int iIndex = LB_ERR);
_TRIAS03_ENTRY int FindString (const char *pString, int iIndexStart = -1);
_TRIAS03_ENTRY bool DelItem (int iIndex = LB_ERR);
_TRIAS03_ENTRY bool GetItem (char *pBuffer, int iLen, int iIndex = LB_ERR);

_TRIAS03_ENTRY unsigned int GetItemID (int iIndex = LB_ERR);
_TRIAS03_ENTRY int GetItemIndex (unsigned int iID);

_TRIAS03_ENTRY int GetCurrentIndex (void);
_TRIAS03_ENTRY void ChangeCurrentIndex (int iIndex);

_TRIAS03_ENTRY bool FreeItem (int iIndex);
_TRIAS03_ENTRY bool Clear (void);

_TRIAS03_ENTRY bool GetItemChecked (int iIndex = LB_ERR);
_TRIAS03_ENTRY bool SetItemChecked (int iIndex = LB_ERR, bool fCheck = true);
_TRIAS03_ENTRY bool ToggleItemChecked (int iIndex = LB_ERR);
_TRIAS03_ENTRY bool EnableItem (int iIndex = LB_ERR, bool fEnable = true);
_TRIAS03_ENTRY bool IsItemEnabled (int iIndex = LB_ERR);

_TRIAS03_ENTRY bool DrawItem (DrawItemEvt &e);
_TRIAS03_ENTRY bool SelectItem (DrawItemEvt &e);
_TRIAS03_ENTRY bool FocusItem (DrawItemEvt &e);
};

#endif // CHECKLST_HXX
