// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 07.02.2003 11:39:15 
//
// @doc
// @module ManageObjectPropertiesDlg.h | Declaration of the <c CManageObjectPropertiesDlg> class

#if !defined(_MANAGEOBJECTPROPERTIESDLG_H__7CA88B2D_3F35_4CEB_8E37_3F3FEC17D3C3__INCLUDED_)
#define _MANAGEOBJECTPROPERTIESDLG_H__7CA88B2D_3F35_4CEB_8E37_3F3FEC17D3C3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <SelObjProp.h>

///////////////////////////////////////////////////////////////////////////////
// 
class CManageObjectPropertiesDlg :
	public CPropertyPage
{
public:
	CManageObjectPropertiesDlg(ResourceFile &rRF);
	~CManageObjectPropertiesDlg();
	
	void WindowInit(Event e);
	void ButtonClick(ControlEvt e);
	void OnSelChanged(NotifyEvt e);

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }

protected:
	void OnNewObjProp();
	void ObDelObjProp();
	void ObObjPropProperties();

	void AdjustButtons();

private:
	CSelObjPropTree m_ObjProps;	
	PushButton m_pbDelete;
	PushButton m_pbProperties;
};

#endif // !defined(_MANAGEOBJECTPROPERTIESDLG_H__7CA88B2D_3F35_4CEB_8E37_3F3FEC17D3C3__INCLUDED_)
