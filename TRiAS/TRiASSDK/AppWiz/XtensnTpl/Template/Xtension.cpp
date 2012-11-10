// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: $$date_n_time$$
//
// @doc
// @module $$root$$.cpp | Implementation of the <c C$$safe_root$$Extension> class

#include "stdafx.h"

#include "$$root$$.h"
#include "$$root$$Ext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

// Liefert den CLSID des TRiAS-Zusatzmodules $$root$$
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_$$safe_root$$;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// C$$safe_root$$Extension

// InitExtension Wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) C$$safe_root$$Extension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;

#pragma TODO("Add initialisation here!")

	return TRUE;
}

// UnLoadExtension wird vor dem entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) C$$safe_root$$Extension::UnLoadExtension (void)
{
#pragma TODO("Add clean up code here!")

	return CTriasExtension::UnLoadExtension();
}
