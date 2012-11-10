// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 01:46:52 PM
//
// @doc
// @module PerfObjects.cpp | Implementation of the <c CPerfObjects> class

#include "stdafx.h"

#include <Com/PerfMonContext.h>
#include "Wrapper.h"

#include "PerfObjects.h"

/////////////////////////////////////////////////////////////////////////////
// CPerfObjects

STDMETHODIMP CPerfObjects::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfObjects,
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
