// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 13.02.2003 11:29:57 
//
// @doc
// @module NewLoadableObjectProperty.cpp | Definition of the <c CNewLoadableObjectProperty> class

#include "trias03p.hxx"
#include "trias03.h"

#include "NewLoadableObjectProperty.h"

///////////////////////////////////////////////////////////////////////////////
// 
CNewLoadableObjectPropertyDlg::CNewLoadableObjectPropertyDlg(Window *pWnd, ResID resId) :
	DialogWindow(pWnd, resId)
{
}

CNewLoadableObjectPropertyDlg::~CNewLoadableObjectPropertyDlg()
{
}

void CNewLoadableObjectPropertyDlg::ButtonClick(ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDCANCEL:
		EndDlg(FALSE);
		break;

	case IDOK:
		EndDlg(TRUE);
		break;
	}
}

