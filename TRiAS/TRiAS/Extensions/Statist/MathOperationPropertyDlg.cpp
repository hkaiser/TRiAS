// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.12.2000 15:17:19 
//
// @doc
// @module MathOperationPropertyDlg.cpp | Definition of the <c CMathOperationPropertyDlg> class

#include "stdafx.h"

#include "Statist.h"
#include "MathOperationPropertyDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathOperationPropertyDlg dialog

CMathOperationPropertyDlg::CMathOperationPropertyDlg()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMathOperationPropertyDlg message handlers

BOOL CMathOperationPropertyDlg::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage<CMathOperationPropertyDlg::IDD>::OnSetActive();
}

BOOL CMathOperationPropertyDlg::OnWizardFinish() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage<CMathOperationPropertyDlg::IDD>::OnWizardFinish();
}
