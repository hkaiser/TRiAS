// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 11.04.2002 17:48:20 
//
// @doc
// @module licence.cpp | Definition of the licensing functions

#include "StdAfx.h"

#include <Esnecil.h>
#include <EsnecilExt.h>

#include "resource.h"

BOOL GetLicenseKey (LPWSTR pwKey, size_t iLen)
{
VERIFYLICENSE VL;

	INITSTRUCT(VL, VERIFYLICENSE);
	VL.iMode = VERIFYMODE_DontShowDialog|VERIFYMODE_LessOrEqual;
	VL.lLevelOrOption = CKILEVEL_PLUS;
	if (!DEX_VerifyLicenseLevel(VL))
		return FALSE;

	INITSTRUCT(VL, VERIFYLICENSE);
	VL.iMode = VERIFYMODE_DontShowDialog|VERIFYMODE_Equal;
	VL.lLevelOrOption = CKIOPTION_RASTERIMPORT;
	if (!DEX_VerifyLicenseOption(VL))
		return FALSE;

CEsnecilExt Lic;
LPCSTR pcSiteCode = Lic.GetSiteCode();

	if (NULL != pwKey && NULL != pcSiteCode) 		// Key kopieren
		mbstowcs (pwKey, pcSiteCode, min(iLen, strlen(pcSiteCode)));

	return (NULL != pcSiteCode) ? TRUE : FALSE;
}

BOOL GetLicensed (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

VERIFYLICENSE VL;
CString strLicCap;

	VERIFY(strLicCap.LoadString(IDS_INDICATORCAPTION));

	INITSTRUCT(VL, VERIFYLICENSE);
	VL.iMode = VERIFYMODE_LessOrEqual;
	VL.lLevelOrOption = CKILEVEL_PLUS;
	VL.pcCaption = (LPCTSTR)strLicCap;
	if (!DEX_VerifyLicenseLevel(VL))
		return FALSE;

	INITSTRUCT(VL, VERIFYLICENSE);
	VL.iMode = VERIFYMODE_Equal;
	VL.lLevelOrOption = CKIOPTION_RASTERIMPORT;
	VL.pcCaption = (LPCTSTR)strLicCap;
	return DEX_VerifyLicenseOption(VL);
}

BOOL SetLicensed (LPCSTR lpNewKey)		// Lizensierung ist erfolgt
{
	CEsnecilExt Lic;
	return Lic.Authorize(lpNewKey);
}

