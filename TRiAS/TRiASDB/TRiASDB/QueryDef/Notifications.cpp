// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.03.2000 15:41:03
//
// @doc
// @module Notifications.cpp | Implementation of the notification handlers

#include "StdAfx.h"

#include "Strings.h"
#include "QueryDef.h"
#include "QueryDefExt.h"

///////////////////////////////////////////////////////////////////////////////
// DEX_OBJECTCHANGED
namespace {
	BOOL CALLBACK ObjectClassesCB (long lIdent, DWORD hObj, void *pData)
	{
		if (hObj != reinterpret_cast<INT_PTR>(pData)) 
			DEX_UnloadObject (hObj);		// Objekt muﬂ neu geladen werden
		return TRUE;
	}
}

BOOL CQueryDefExtension::OnObjectChanged (INT_PTR lONr)
{
ENUMLONGKEYEX ELK;

	ELK.eKey = lONr;
	ELK.eFcn = reinterpret_cast<ENUMLONGKEYEXPROC>(ObjectClassesCB);
	ELK.ePtr = reinterpret_cast<void *>(lONr);	// for comparing purposes only
	ELK.eData = CFO_ActViewOnly;
	return DEX_EnumObjectClasses (ELK);
}



