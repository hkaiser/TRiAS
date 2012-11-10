// RegNum.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wisedll.h"

BOOL APIENTRY DllMain (HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Interne Registriernummer: 100-0000-16670989
bool IsInternalRegNumber (LPCSTR pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	return (100 == lInit && 0 == l2nd && 16670989L == lNumber);
}

///////////////////////////////////////////////////////////////////////////////
// Demoregistriernummer: 001-0000-07621669
bool IsDemoRegNumber (LPCSTR pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	return (1 == lInit && 0 == l2nd && 7621669L == lNumber);
}

///////////////////////////////////////////////////////////////////////////////
// alle anderen Registriernummern
HRESULT IsLegalRegNumber (LPCSTR pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);

	if (300 > lInit && !IsInternalRegNumber(pcRegEntry) && !IsDemoRegNumber(pcRegEntry))
		return S_FALSE;

long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	srand (230459L);
	for (long i = 0; i < lInit-2; i++) 
		rand();

long lStep = lInit / ((rand() % 93) + 7);	// teilen durch mind 7 und max 92
long lGroup = rand() % 1000;
long lResult = 0;

	if (lInit >= 500) {
	// für Werte über 500
		for (int j = 0; j <= l2nd; j += lStep)
			lResult = rand()*lGroup+rand();
		if (j != l2nd + lStep)
			return S_FALSE;		// lStep muß auch stimmen
	} else {
	// für Werte zwischen 300 und 499
		for (int j = 0; j <= l2nd; j++)
			lResult = rand()*lGroup+rand();
	}
	return (lResult == lNumber) ? S_OK : S_FALSE;
}

// SetVariable: Sets/Creates a variable.
//
// lpDllParams  Parameter structure passed from Wise Installation
// szVariable   Name of the variable (without %'s) to set value for
// szValue      String that contains the variables new value

void SetVariable (LPDLLCALLPARAMS lpDllParams,char *szVariable,char *szValue)
{
   WORD i;
   char szVar[32];

   *szVar = '%';
   lstrcpy(&szVar[1],szVariable);
   lstrcat(szVar,"%");
   for (i = 0 ; (i < lpDllParams->wCurrReps) &&
      (lstrcmp(&lpDllParams->lpszRepName[i * lpDllParams->wRepNameWidth],szVar) != 0) ; i++) ;
   if (i >= lpDllParams->wCurrReps) {
      if (i >= lpDllParams->wMaxReplaces) return; // Too many variables
      lstrcpy(&lpDllParams->lpszRepName[i * lpDllParams->wRepNameWidth],szVar);
      lpDllParams->wCurrReps++;
   }
   lstrcpy(&lpDllParams->lpszRepStr[i * lpDllParams->wRepStrWidth],szValue);
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob eine Dateiversion mindestens den gegebenen Forderungen entspricht
BOOL IsLegalVersion (LPCSTR pcVersion, int iMinVer, int iMinSubVer = 0, int iMinBuild = 0, int iMinSubBuild = 0)
{
int iVer = 0;
int iSubVer = 0;
int iBuild = 0;
int iSubBuild = 0;

	if (2 <= sscanf (pcVersion, "%d.%d.%d.%d", &iVer, &iSubVer, &iBuild, &iSubBuild)) {
	// zumindest scheint's eine gültige Versionsnummer zu sein
		if (iVer < iMinVer)
			return FALSE;
		if (iSubVer < iMinSubVer)
			return FALSE;
		if (iBuild < iMinBuild)
			return FALSE;
		if (iSubBuild < iMinSubBuild)
			return FALSE;
		return TRUE;		// Version schein zu stimmen
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob Registriernummer gültig ist
extern "C"
BOOL CALLBACK IsLegalRegNumber (LPDLLCALLPARAMS lpDllParams)
{
	try {
		if (lpDllParams->lpszParam) {
		char cbRegNumber[256];

			strcpy (cbRegNumber, lpDllParams->lpszParam);
			if (S_FALSE == IsLegalRegNumber (cbRegNumber)) 
				SetVariable (lpDllParams, "LEGALREGNUMBER", "0");
			else
				SetVariable (lpDllParams, "LEGALREGNUMBER", "1");
		}
	} catch (...) {
		SetVariable (lpDllParams, "LEGALREGNUMBER", "0");
		return FALSE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob ComCtl32.dll installiert werden muß
extern "C"
BOOL CALLBACK HasToInstallComCtl (LPDLLCALLPARAMS lpDllParams)
{
	try {
		if (lpDllParams->lpszParam) {
		char cbRegNumber[256];

			strcpy (cbRegNumber, lpDllParams->lpszParam);
//			MessageBox (NULL, cbRegNumber, "Versionsinfo der ComCtl32.dll", MB_OK);
			if (S_FALSE == IsLegalVersion (cbRegNumber, 4, 72)) 
				SetVariable (lpDllParams, "INSTALL_COMCTL", "0");
			else
				SetVariable (lpDllParams, "INSTALL_COMCTL", "1");
		}
	} catch (...) {
		SetVariable (lpDllParams, "INSTALL_COMCTL", "1");
		return FALSE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob MsXml.dll installiert werden muß
extern "C"
BOOL CALLBACK HasToInstallXMLParser (LPDLLCALLPARAMS lpDllParams)
{
	try {
		if (lpDllParams->lpszParam) {
		char cbRegNumber[256];

			strcpy (cbRegNumber, lpDllParams->lpszParam);
//			MessageBox (NULL, cbRegNumber, "Versionsinfo der MSXML.dll", MB_OK);
			if (S_FALSE == IsLegalVersion (cbRegNumber, 5)) 
				SetVariable (lpDllParams, "INSTALL_XML", "0");
			else
				SetVariable (lpDllParams, "INSTALL_XML", "1");
		}
	} catch (...) {
		SetVariable (lpDllParams, "INSTALL_XML", "1");
		return FALSE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob IProp.dll installiert werden muß
extern "C"
BOOL CALLBACK HasToInstallIProp (LPDLLCALLPARAMS lpDllParams)
{
	try {
		if (lpDllParams->lpszParam) {
		char cbRegNumber[256];

			strcpy (cbRegNumber, lpDllParams->lpszParam);
//			MessageBox (NULL, cbRegNumber, "Versionsinfo der IProp.dll", MB_OK);
			if (S_FALSE == IsLegalVersion (cbRegNumber, 4, 0)) 
				SetVariable (lpDllParams, "INSTALL_IPROP", "0");
			else
				SetVariable (lpDllParams, "INSTALL_IPROP", "1");
		}
	} catch (...) {
		SetVariable (lpDllParams, "INSTALL_IPROP", "1");
		return FALSE;
	}
	return FALSE;
}
