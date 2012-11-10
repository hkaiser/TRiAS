// Funktionsdefinitionen fuer OwnerDrawListBox --------------------------------
// File: OWNLIST.CXX

#include "trias03p.hxx"

#include <ownlist.hxx>
#include <ownliste.hxx>

// Konstruktoren --------------------------------------------------------------
OwnerDrawListBoxEx :: OwnerDrawListBoxEx (pDialogWindow pDW, ResID rsc) 
		    : OwnerDrawListBox ((Control *)new MultiSelListBox (pDW, rsc))
{
	// nothing to do
}

OwnerDrawListBoxEx :: ~OwnerDrawListBoxEx (void) 
{
	// nothing to do
}

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

bool OwnerDrawListBoxEx :: ClearSelected (void)
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

bool OwnerDrawListBoxEx :: ChangeSelected (int index, bool iFlag)
{
	if (LocCtrl() == NULL) return LB_ERR;

return LocCtrl() -> ChangeSelected (index, iFlag);
}

bool OwnerDrawListBoxEx :: ChangeSelected (Range R, bool iFlag)
{
	if (LocCtrl() == NULL) return LB_ERR;

return LocCtrl() -> ChangeSelected (R, iFlag);
}

// TRUE: Item ist selektiert, FALSE: Item ist nicht selektiert
bool OwnerDrawListBoxEx :: GetSelection (short Index) 
{
	return (ListBox_GetSel (GetHandle(), int(Index)) > 0);
}

int OwnerDrawListBoxEx :: GetCaretIndex (void)
{
	return ListBox_GetCaretIndex (GetHandle());
}

int OwnerDrawListBoxEx :: SetCaretIndex (int iIndex, bool iFlag)
{
	return ListBox_SetCaretIndexEx (GetHandle(), iIndex, iFlag);
}
