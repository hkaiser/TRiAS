// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 13.02.2003 09:31:13 
//
// @doc
// @module NewLoadableObjectProperty.h | Declaration of the <c CNewLoadableObjectPropertyDlg> class

#if !defined(_NEWLOADABLEOBJECTPROPERTY_H__EC461AC3_9D7B_4EB4_A78F_626754CCE0A0__INCLUDED_)
#define _NEWLOADABLEOBJECTPROPERTY_H__EC461AC3_9D7B_4EB4_A78F_626754CCE0A0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// 
class CNewLoadableObjectPropertyDlg :
	public DialogWindow
{
public:
	CNewLoadableObjectPropertyDlg(Window *pWnd, ResID resId);
	~CNewLoadableObjectPropertyDlg();

	void ButtonClick(ControlEvt e);

private:
};

#endif // !defined(_NEWLOADABLEOBJECTPROPERTY_H__EC461AC3_9D7B_4EB4_A78F_626754CCE0A0__INCLUDED_)
