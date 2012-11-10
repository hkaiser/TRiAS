// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.07.2002 10:37:46 
//
// @doc
// @module Licence.cpp | Lizensierungsfunktionen

#include "stdafx.h"

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
	VL.lLevelOrOption = CKIOPTION_GCOPRODUCTION;
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
VERIFYLICENSE VL;
CString resLicCap;

	resLicCap.LoadString(IDS_LONGCLASSNAME);
	_ASSERTE(resLicCap.GetLength() > 0);

	INITSTRUCT(VL, VERIFYLICENSE);
	VL.iMode = VERIFYMODE_LessOrEqual;
	VL.lLevelOrOption = CKILEVEL_PLUS;
	VL.pcCaption = resLicCap;
	if (!DEX_VerifyLicenseLevel(VL))
		return FALSE;

	INITSTRUCT(VL, VERIFYLICENSE);
	VL.iMode = VERIFYMODE_Equal;
	VL.lLevelOrOption = CKIOPTION_GCOPRODUCTION;
	VL.pcCaption = resLicCap;
	return DEX_VerifyLicenseOption(VL);
}

BOOL SetLicensed (LPCSTR lpNewKey)		// Lizensierung ist erfolgt
{
CEsnecilExt Lic;

	return Lic.Authorize(lpNewKey);
}

