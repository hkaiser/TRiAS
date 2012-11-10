// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.03.2001 20:22:35 
//
// @doc
// @module ProjectValuesStore.cpp | Definition of the <c CProjectValueStore> class

#include "stdafx.h"

#if defined(_USE_PROJECTVALUES)

#include "fakemfc.h"
#include "ProjectValueStore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectValueStore

CProjectValueStore::CProjectValueStore()
{
}

CProjectValueStore::~CProjectValueStore()
{
}


BEGIN_MESSAGE_MAP(CProjectValueStore, CSECTreeCtrlEx)
	//{{AFX_MSG_MAP(CProjectValueStore)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectValueStore message handlers

#endif // defined(_USE_PROJECTVALUES)
