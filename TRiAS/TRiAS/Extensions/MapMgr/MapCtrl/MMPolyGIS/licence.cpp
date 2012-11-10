// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 02.05.2002 11:43:46 
//
// @doc
// @module licence.cpp | Funktionen, die die Lizenz verwalten

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

// PolyGIS Rasterkarten sind jetzt immer zu sehen ;-)
//	INITSTRUCT(VL, VERIFYLICENSE);
//	VL.iMode = VERIFYMODE_DontShowDialog|VERIFYMODE_Equal;
//	VL.lLevelOrOption = CKIOPTION_GCOPRODUCTION;
//	if (!DEX_VerifyLicenseOption(VL))
//		return FALSE;

CEsnecilExt Lic;
LPCSTR pcSiteCode = Lic.GetSiteCode();

	if (NULL != pwKey && NULL != pcSiteCode) 		// Key kopieren
		mbstowcs (pwKey, pcSiteCode, min(iLen, strlen(pcSiteCode)));

	return (NULL != pcSiteCode) ? TRUE : FALSE;
}

BOOL GetLicensed (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

VERIFYLICENSE VL;
CString resLicCap;

	VERIFY(resLicCap.LoadString(IDS_LONGCLASSNAME));

	INITSTRUCT(VL, VERIFYLICENSE);
	VL.iMode = VERIFYMODE_LessOrEqual;
	VL.lLevelOrOption = CKILEVEL_PLUS;
	VL.pcCaption = resLicCap;

// PolyGIS Rasterkarten sind jetzt immer zu sehen :-)
//	if (!DEX_VerifyLicenseLevel(VL))
//		return FALSE;
//
//	INITSTRUCT(VL, VERIFYLICENSE);
//	VL.iMode = VERIFYMODE_Equal;
//	VL.lLevelOrOption = CKIOPTION_GCOPRODUCTION;
//	VL.pcCaption = resLicCap;

	return DEX_VerifyLicenseOption(VL);
}

BOOL SetLicensed (LPCSTR lpNewKey)		// Lizensierung ist erfolgt
{
CEsnecilExt Lic;

	return Lic.Authorize(lpNewKey);
}

