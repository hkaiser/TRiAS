// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.03.2001 20:22:42 
//
// @doc
// @module ProjectValueCategories.cpp | Definition of the <c CProjectValueCategories> class

#include "stdafx.h"

#if defined(_USE_PROJECTVALUES)

#include "fakemfc.h"
#include "ProjectValueCategories.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectValueCategories

CProjectValueCategories::CProjectValueCategories()
{
}

CProjectValueCategories::~CProjectValueCategories()
{
}


BEGIN_MESSAGE_MAP(CProjectValueCategories, CComboBoxEx)
	//{{AFX_MSG_MAP(CProjectValueCategories)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectValueCategories message handlers

#endif // defined(_USE_PROJECTVALUES)
