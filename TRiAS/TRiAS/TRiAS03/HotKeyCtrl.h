// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.10.2000 19:29:16 
//
// @doc
// @module HotKeyCtrl.h | Declaration of the <c CHotKeyCtrl> class

#if !defined(_HOTKEYCTRL_H__2FA32731_4952_43E8_9F9B_A548C3FF8ED3__INCLUDED_)
#define _HOTKEYCTRL_H__2FA32731_4952_43E8_9F9B_A548C3FF8ED3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CHotKeyCtrl :
	public Control
{
public:
	CHotKeyCtrl();
	~CHotKeyCtrl();

// Attributes
	void SetHotKey(WORD wVirtualKeyCode, WORD wModifiers);
	DWORD GetHotKey() const;
	void GetHotKey(WORD &wVirtualKeyCode, WORD &wModifiers) const;

// Operations
	void SetRules(WORD wInvalidComb, WORD wModifiers);
};

#endif // !defined(_HOTKEYCTRL_H__2FA32731_4952_43E8_9F9B_A548C3FF8ED3__INCLUDED_)
