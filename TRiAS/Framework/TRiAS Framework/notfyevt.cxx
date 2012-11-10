// Notification Events --------------------------------------------------------
// File: NOTFYEVT.CXX

#include "tfrmpre.hxx"

// CommonControl notifications ------------------------------------------------
void Window :: OnBeginDrag (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnBeginRDrag (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnEndDrag (NotifyEvt e)
{
	Default ((Event &)e);
}

BOOL Window :: OnBeginLabelEdit (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow processing
}

void Window :: OnEndLabelEdit (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnDeleteItem (NotifyEvt e)
{
	Default ((Event &)e);
}

// Tree View Control notifications --------------------------------------------
void Window :: OnGetDispInfo (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnSetDispInfo (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnItemExpanded (NotifyEvt e)
{
	Default ((Event &)e);
}

BOOL Window :: OnItemExpanding (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow processing
}

void Window :: OnSelChanged (NotifyEvt e)
{
	Default ((Event &)e);
}

BOOL Window :: OnSelChanging (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow processing
}

void Window :: OnClick (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnDblClick (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnKeyDown (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnInsertItem (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnDeleteAllItems (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnItemChanged (NotifyEvt e)
{
	Default ((Event &)e);
}

BOOL Window :: OnItemChanging (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow processing
}

void Window :: OnColumnClick (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnReset (NotifyEvt e)
{
	Default ((Event &)e);
}

BOOL Window :: OnQueryDelete (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow processing (true <--> false)
}

BOOL Window :: OnQueryInsert (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow processing (true <--> false)
}

void Window :: OnBeginAdjust (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnEndAdjust (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnCustHelp (NotifyEvt e)
{
	Default ((Event &)e);
}

void Window :: OnToolBarChange (NotifyEvt e)
{
	Default ((Event &)e);
}

BOOL Window :: OnGetButtonInfo (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// no Info is copied
}

void Window :: OnNeedText (ToolTipEvt e)
{
	Default ((Event &)e);
}

void Window :: OnHidingTip (ToolTipEvt e)
{
	Default ((Event &)e);
}

void Window :: OnShowingTip (ToolTipEvt e)
{
	Default ((Event &)e);
}

BOOL Window :: OnDeltaPos (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow operation
}

