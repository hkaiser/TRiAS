// @doc 
// @module ResetHideAddEntryCB.cpp | Implementation of the CResetHideAddEntryCB

#include "visobjp.hxx"

#include "visobj.hxx"
#include "ResetHideAddEntryCB.h"

/////////////////////////////////////////////////////////////////////////////
// CResetHideAddEntryCB

STDMETHODIMP CResetHideAddEntryCB::AddEntry (INT_PTR lIdent, DWORD dwTypes, DWORD *pdwTypesToAdd) 
{
	if (NULL == pdwTypesToAdd)
		return E_POINTER;
	*pdwTypesToAdd = 0;

	if (DEX_GetROModeIdent(lIdent))		// Tabelle ist sowieso schreibgeschützt
		return S_OK;

char cbBuffer[_MAX_PATH];
long lMCode = ((CVisObjExtension *)g_pTE) -> GetIdentMCode (false, NULL, lIdent);

	if (-1L == lMCode || !ReadTextMerkmal (TT_Identifikator, lIdent, lMCode, cbBuffer))
		return S_OK;	// Ident ist nicht visualisiert

// auf zu behandelnde Objekttypen beschränken
	*pdwTypesToAdd = dwTypes & GetObjectTypeBits(CVisObjExtension::StringToIdMode(cbBuffer), OVModShow);
	return S_OK;
}

