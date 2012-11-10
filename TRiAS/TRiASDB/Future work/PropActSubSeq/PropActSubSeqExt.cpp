// @doc
// @module PropActSubSeq.cpp | Implementation of the <c CPropActSubSeqExtension> class

#include "stdafx.h"

#include "PropActSubSeq.h"
#include "PropActSubSeqExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

// Liefert den CLSID des TRiAS-Zusatzmodules PropActSubSeq
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_PropActSubSeq;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPropActSubSeqExtension

// InitExtension Wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CPropActSubSeqExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;

#pragma TODO("Add initialisation here!")

	return TRUE;
}

// UnLoadExtension wird vor dem entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) CPropActSubSeqExtension::UnLoadExtension (void)
{
#pragma TODO("Add clean up code here!")

	return CTriasExtension::UnLoadExtension();
}
