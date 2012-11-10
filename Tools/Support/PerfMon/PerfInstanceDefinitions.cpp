// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/28/1998 09:41:43 PM
//
// @doc
// @module PerfInstanceDefinitions.cpp | Implementation of the <c CPerfInstanceDefinitions> class

#include "stdafx.h"

#include <Com/PerfMonContext.h>
#include "Wrapper.h"

#include "PerfInstanceDefinitions.h"

/////////////////////////////////////////////////////////////////////////////
// CPerfInstanceDefinitions

STDMETHODIMP CPerfInstanceDefinitions::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfInstanceDefinitions,
		&IID_IDynamicCollection,
		&IID_IStaticCollection,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
