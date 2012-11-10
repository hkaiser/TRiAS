// Funktionen, die die Lizenz verwalten ---------------------------------------
// File ASCLIC.CPP

#include "ascimpp.hpp"

#include <Esnecil.h>
#include <EsnecilExt.h>

#include "ascimp.h"

#if _TRiAS_VER < 0x0400

#include <registrx.hxx>

///////////////////////////////////////////////////////////////////////////////
// Versionskontrolle
extern DWORD g_dwVer4;

///////////////////////////////////////////////////////////////////////////////
// Registrierung über eigene Seriennummer, die in Registry steht
const char g_cbRegVersion[]	= TEXT("SOFTWARE\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\3.0");
const char g_cbSerial[] = TEXT("Serial");

HRESULT IsLegalRegNumber (LPCSTR pcRegEntry);

BOOL GetLicenseKeyObsolete (LPWSTR pwKey, size_t iLen)
{
CLocalMachine regName (KEY_READ, g_cbRegVersion);
char cbRegEntry[65];
DWORD dwLen = sizeof(cbRegEntry);

	if (regName.GetSubSZ (g_cbSerial, cbRegEntry, dwLen) &&
		S_OK == IsLegalRegNumber (cbRegEntry)) 
	{
		if (NULL != pwKey)		// Key kopieren
			mbstowcs (pwKey, cbRegEntry, min(dwLen, iLen));
		return true;
	} 
	return false;
}

BOOL GetLicensedObsolete (void)
{
CLocalMachine regName (KEY_READ, g_cbRegVersion);
char cbRegEntry[65];
DWORD dwLen = sizeof(cbRegEntry);

	if (!regName.GetSubSZ (g_cbSerial, cbRegEntry, dwLen))
		return false;

	return S_OK == IsLegalRegNumber (cbRegEntry) ? true : false;	// lizensiert ??
}

BOOL SetLicensedObsolete (LPCSTR lpNewKey)		// Lizensierung ist erfolgt
{
	if (S_OK != IsLegalRegNumber(lpNewKey))
		return false;

CLocalMachine regName (g_cbRegVersion, true);

	return regName.SetSubSZ (g_cbSerial, lpNewKey);
}
#endif // _TRiAS_VER < 0x0400

BOOL GetLicenseKey (LPWSTR pwKey, size_t iLen)
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) 
		return GetLicenseKeyObsolete(pwKey, iLen);
#endif // _TRiAS_VER < 0x0400

VERIFYLICENSE VL;

	INITSTRUCT(VL, VERIFYLICENSE);
	VL.iMode = VERIFYMODE_DontShowDialog|VERIFYMODE_LessOrEqual;
	VL.lLevelOrOption = CKILEVEL_PLUS;
	if (!DEX_VerifyLicenseLevel(VL))
		return FALSE;

CEsnecilExt Lic;
LPCSTR pcSiteCode = Lic.GetSiteCode();

	if (NULL != pwKey && NULL != pcSiteCode) 		// Key kopieren
		mbstowcs (pwKey, pcSiteCode, min(iLen, strlen(pcSiteCode)));

	return (NULL != pcSiteCode) ? TRUE : FALSE;
}

BOOL GetLicensed (void)
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) 
		return GetLicensedObsolete();
#endif // _TRiAS_VER < 0x0400

VERIFYLICENSE VL;
ResourceFile RF (g_pDLLName);
ResString resLicCap (ResID (IDS_LONGCLASSNAME, &RF), 64);

	INITSTRUCT(VL, VERIFYLICENSE);
	VL.iMode = VERIFYMODE_LessOrEqual;
	VL.lLevelOrOption = CKILEVEL_PLUS;
	VL.pcCaption = resLicCap.Addr();
	return DEX_VerifyLicenseLevel(VL);
}

BOOL SetLicensed (LPCSTR lpNewKey)		// Lizensierung ist erfolgt
{
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) 
		return SetLicensedObsolete(lpNewKey);
#endif // _TRiAS_VER < 0x0400

CEsnecilExt Lic;

	return Lic.Authorize(lpNewKey);
}

