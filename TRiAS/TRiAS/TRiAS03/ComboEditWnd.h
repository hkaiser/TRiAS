// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.09.2000 21:25:19 
//
// @doc
// @module ComboEditWnd.h | Declaration of the <c CComboEditWnd> class

#if !defined(_COMBOEDITWND_H__0214D0EC_5334_467E_84B7_6B377AF405D3__INCLUDED_)
#define _COMBOEDITWND_H__0214D0EC_5334_467E_84B7_6B377AF405D3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// EditFenster der ComboBox muß subclassed werden, damit WM_KILLFOCUS
// ausgewertet werden kann, um Selektion zu speichern
class CComboEditWnd : public ControlWindow 
{
private:
	Selection m_sel;

protected:
	void FocusChange (FocusChangeEvt e)
	{
		if (!e.gotFocus())
			m_sel = ((SingleLineEdit *)GetControl()) -> GetSelection();
		ControlWindow::FocusChange(e);
	}

public:
	CComboEditWnd (pWindow pW, ComboBox &rCB)
		: ControlWindow (new SingleLineEdit (pW, GetDlgItem (rCB.Handle(), 1001)))
	{
	}
	~CComboEditWnd (void)
	{
		if (GetControl()) 
			delete ((SingleLineEdit *)GetControl());
	}

	Selection GetLastSelection (void) { return m_sel; }
};

#endif // !defined(_COMBOEDITWND_H__0214D0EC_5334_467E_84B7_6B377AF405D3__INCLUDED_)
