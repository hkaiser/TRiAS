// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.11.1999 23:15:49
//
// @doc
// @module TemplateWizPropExt.cpp | Implementation of the <c CTemplateWizPropExt> class

#include "stdafx.h"
#include <AfxDlgs.h>
#include <xtsnguid.h>

#include "TemplateWizPropExt.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TemplateWizPropExt, CTemplateWizPropExt)

HRESULT WINAPI CTemplateWizPropExt::UpdateRegistry(BOOL bRegister)
{
// beim Registrieren nur im SysAdminMode arbeiten
CRegKey key;
DWORD dwSysAdminMode = 0;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY))
	{
	CRegKey cfgkey;

		if (ERROR_SUCCESS == cfgkey.Open(key, TEXT("Config"))) 
			cfgkey.QueryValue (dwSysAdminMode, TEXT("SystemAdministration"));
	}
	if (!bRegister || 0 != dwSysAdminMode)
		return _Module.UpdateRegistryFromResource(IDR_TEMPLATEWIZPROPEXT, bRegister);

	return S_OK;	// nicht registrieren
}

/////////////////////////////////////////////////////////////////////////////
// CTemplateWizPropExt

