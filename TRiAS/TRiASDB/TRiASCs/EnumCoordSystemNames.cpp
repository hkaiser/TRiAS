// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 09.09.2002 19:26:47 
//
// @doc
// @module EnumCoordSystemNames.cpp | Definition of the <c CEnumCoordSystemNames> class

#include "stdafx.h"
#include "TRiASCs.h"
#include "TRiASCsImpl.h"

#include <Com/Thunk.h>

#include "Strings.h"
#include "EnumCoordSystemNames.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEnumCoordSystemNames

// FinalConstruct implementation
HRESULT CEnumCoordSystemNames::FinalConstruct()
{
CStdThunkImpl<CEnumCoordSystemNames, ENUMRESNAMEPROC> 
	cbProc(this, &CEnumCoordSystemNames::EnumResNameProc);

	EnumResourceNames(_Module.GetResourceInstance(), g_cbCOORDSYS, cbProc.GetThunk(), NULL);
	return CComObjectRootEx<_ThreadModel>::FinalConstruct();
}

// FinalRelease implementation
void CEnumCoordSystemNames::FinalRelease()
{
}

///////////////////////////////////////////////////////////////////////////////
// Fill Collection with enumerated resource names
BOOL CEnumCoordSystemNames::EnumResNameProc(HMODULE hModule, 
	LPCTSTR lpszType, LPTSTR lpszName, LONG_PTR lParam)
{
	_ASSERTE(!strcmp(lpszType, g_cbCOORDSYS));
	return SUCCEEDED(this->InitAppend(CComBSTR(lpszName))) ? TRUE : FALSE;
}
