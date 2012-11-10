// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.09.99 15:58:03
//
// @doc
// @module RegisterPerfMon.cpp | Implementation of the <c CRegisterPerfMon> class

#include <StdAfx.h>

#include "RegisterPerfMon.h"

#define LOADLIBRARY_FAILED(x) (x == 0)

using namespace std;

extern const char g_cbRegPerfMon[];

typedef HRESULT (STDAPICALLTYPE *PERFMONREGPROC)(void); 

CRegisterPerfMon::CRegisterPerfMon (LPCSTR pcPathName)
	: m_strPathName(pcPathName)
{
}

CRegisterPerfMon::~CRegisterPerfMon (void)
{
}

bool CRegisterPerfMon::Register (bool bSilent)
{
bool bResult = false;

	if (SupportsSelfRegister()) {  
	HINSTANCE hModule = ::LoadLibrary (m_strPathName.c_str());
	
		if (LOADLIBRARY_FAILED(hModule)) {
			if (!bSilent) {
			DWORD dwError = GetLastError();
			char cbBuffer[_MAX_PATH];
			strstream str;

				FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, 
					NULL, dwError, 0, cbBuffer, _MAX_PATH, NULL);

				str <<  "An error occurred! " << cbBuffer << "\n"
						"Win32 Error = " << GetLastError() << "\n\0";
				MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK);
			}
			return false;
		}

	PERFMONREGPROC DLLRegisterServer = (PERFMONREGPROC)::GetProcAddress (hModule, TEXT("DllRegisterPerfMon"));
	
		if (DLLRegisterServer == NULL) 
			DLLRegisterServer = (PERFMONREGPROC)::GetProcAddress (hModule, TEXT("DLLREGISTERPERFMON"));

	HRESULT regResult = E_FAIL;

		if (DLLRegisterServer != NULL) {
			try {
				regResult = DLLRegisterServer();
				bResult = (regResult == S_OK); 
			} catch (...) {
			// GP oä
				regResult = DISP_E_EXCEPTION;		// Exception occured
				bResult = FALSE;
			}

			if (!bSilent && !bResult) {
			char cbBuffer[_MAX_PATH];
			strstream str;

				FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, 
					NULL, regResult, 0, cbBuffer, _MAX_PATH, NULL);

				str <<  "An error occurred! " << cbBuffer << "\n"
						"Win32 Error = " << GetLastError() << "\n" << ends;
				MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK);
			}
		} else if (!bSilent) {
		strstream str;

			str << "An error occurred! Entrypoint not found (DllRegisterPerfMon).\n" << ends;
			MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK);
		}
		::FreeLibrary (hModule);
	} 
	else if (!bSilent) {
	strstream str;

		str << "An error occurred! Module does not support selfregistering performance counters.\n" << ends;
		MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK);
	}
	return bResult;	
}

bool CRegisterPerfMon::Unregister (bool bSilent)
{
bool bResult = false;

	if (SupportsSelfRegister()) {                                    
	HINSTANCE hModule = ::LoadLibrary (m_strPathName.c_str());

		if (LOADLIBRARY_FAILED(hModule)) {
			if (!bSilent) {
			DWORD dwError = GetLastError();
			char cbBuffer[_MAX_PATH];
			strstream str;

				FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, 
					NULL, dwError, 0, cbBuffer, _MAX_PATH, NULL);

				str <<  "An error occurred! " << cbBuffer << "\n"
						"Win32 Error = " << GetLastError() << "\n\0";
				MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK);
			}
			return false;
		}
				
	PERFMONREGPROC DllUnregisterServer = (PERFMONREGPROC)::GetProcAddress (hModule, TEXT("DllUnregisterPerfMon"));
		
		if (DllUnregisterServer == NULL) 
			DllUnregisterServer = (PERFMONREGPROC)::GetProcAddress (hModule, TEXT("DLLUNREGISTERPERFMON"));

		if (DllUnregisterServer != NULL) {
		HRESULT regResult = S_OK;
		
			try {
				regResult = DllUnregisterServer();
				bResult = (regResult == S_OK); 
			} catch (...) {
				bResult = FALSE;
			}

			if (!bSilent && !bResult) {
			char cbBuffer[_MAX_PATH];
			strstream str;

				FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, 
					NULL, regResult, 0, cbBuffer, _MAX_PATH, NULL);

				str <<  "An error occurred! " << cbBuffer << "\n"
						"Win32 Error = " << GetLastError() << "\n" << ends;
				MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK);
			}
		} else if (!bSilent) {
		strstream str;

			str << "An error occurred! Entrypoint not found (DllUnregisterPerfMon).\n" << ends;
			MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK);
		}
		::FreeLibrary (hModule);

	} else if (!bSilent) {
	strstream str;

		str << "An error occurred! Module does not support selfregistering performance counters.\n" << ends;
		MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK);
	}                                     
	return bResult;	
} 

bool CRegisterPerfMon::SupportsSelfRegister (void)
{
int bResult = false;
DWORD  handle;
DWORD  uiInfoSize;
UINT  uiVerSize;
UINT  uiSize;
DWORD *lpBuffer;
char szName[128];

// Get the size of the version information.
	uiInfoSize = GetFileVersionInfoSize ((LPSTR)m_strPathName.c_str(), &handle);
	if (uiInfoSize == 0) return false;

// Allocate a buffer for the version information.
char *pbData = NULL;

	ATLTRY(pbData = new char[uiInfoSize]);
	if (NULL == pbData) return false;

// Fill the buffer with the version information.
	bResult = GetFileVersionInfo ((LPSTR)m_strPathName.c_str(), handle, uiInfoSize, pbData);
	if (!bResult) goto NastyGoto;

// Get the translation information.
	strcpy (szName, TEXT("\\VarFileInfo\\Translation"));
	bResult = VerQueryValue (pbData, szName, (void **)&lpBuffer, &uiVerSize);
	if (!bResult || uiVerSize == 0) goto NastyGoto;

// Build the path to the key OLESelfRegister using the translation information.
	wsprintf (szName, TEXT("\\StringFileInfo\\%04hX%04hX\\PerfMonSelfRegister"), LOWORD(*lpBuffer), HIWORD(*lpBuffer));

// Search for the key.
DWORD *lpSelfReg;

	bResult = VerQueryValue (pbData, szName, (void **)&lpSelfReg, &uiSize);

NastyGoto:
	delete [] pbData;
	return bResult ? true : false;
}

