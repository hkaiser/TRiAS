// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.09.99 15:36:28
//
// @doc
// @module RegPerfMon.cpp | Implementation of the RegPerfMon utility

#include <StdAfx.h>

#include "RegisterPerfMon.h"

using namespace std;

extern const char g_cbRegPerfMon[] = "RegPerfMon";

CComModule _Module;

///////////////////////////////////////////////////////////////////////////////
// Function prototypes 
void ShowHelp();	// Displays information (via cout) about using RegPerfMon

///////////////////////////////////////////////////////////////////////////////
// Creates an ATL Registrar and uses it to register the RGS file passed by name
bool RegisterPerfMonFile (LPCSTR pstrFileName, bool bUnregister = false, bool bSilent = false);

class CRegOle
{
public:
	CRegOle() { CoInitialize(NULL); }
	~CRegOle() { CoUninitialize(); }
};

///////////////////////////////////////////////////////////////////////////////
//
int __stdcall WinMain (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pcCmdLine, int iShow)
{
HRESULT hRes = S_OK;
bool bUnregister = false;
bool bShowHelp = false;
bool bSilent = false;

int argc = __argc;
char **argv = __argv;

USES_CONVERSION;
int nFileArgIndex = -1;
LPCSTR pstrFileName = NULL;

	if ( (argc == 1) or (argc > 4) )	// At most we'll have: module, -u, -s, perfmonfile
		bShowHelp = true;

	for (int i = 1; i < argc; i++)
	{
	// First check to see if this is a command line switch
		if ( (argv[i][0] == '-') or (argv[i][0] == '/')) {
		// For simplicity just check the first character
			switch (argv[i][1]) {
			case 'u':
			case 'U':
				bUnregister = true;
				break;

			case 's':
			case 'S':
				bSilent = true;
				break;

			case '?':
			default:
				bShowHelp = true;
				break;
			}	// switch (argv[i][1])
		}	// if ( (argv[i][0] == '-') or (argv[i][0] == '/'))
		else {
			pstrFileName = argv[i];
			nFileArgIndex = i;
		}
	}	// for (int i = 1; i < argc; i++)

// If there was an error or the user requested it, we show the help screen and quit
	if (bShowHelp) {
		ShowHelp();
		return hRes;
	}

// Check if file exists
HANDLE hFile = CreateFile (argv[nFileArgIndex], GENERIC_READ, 0, NULL,
						   OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		hRes = GetLastError();
		if (!bSilent) {
		strstream str;

			str << "An error occurred! File does not exist.\n"
				   "Win32 Error = " << hRes << "\n" << ends;
			MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK|MB_SETFOREGROUND);
		}
		return HRESULT_FROM_WIN32(hRes);
	}
	CloseHandle(hFile);

bool fResult = RegisterPerfMonFile(pstrFileName, bUnregister, bSilent);

	if (!bSilent && fResult) {
	strstream str;

		str << "Successfully " << ((bUnregister) ? "unregistered" : "registered") << 
			   " performance counters in " << pstrFileName << "\n" << ends;
		MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK|MB_SETFOREGROUND);
	}
	return fResult ? 0 : 1;
}	// main()

///////////////////////////////////////////////////////////////////////////////////////////
// Aufruf der entsprechenden Funktion
bool RegisterPerfMonFile(LPCSTR pstrFileName, bool bUnregister, bool bSilent)
{
CRegOle RegOle;		// handle CoInitialize/CoUninitialize
CRegisterPerfMon Reg (pstrFileName);

	if (!bUnregister)
		return Reg.Register (bSilent);

	return Reg.Unregister (bSilent);
} 

///////////////////////////////////////////////////////////////////////////////////////////
void ShowHelp()
{
strstream str;

	str << 
			"RegPerfMon adds to (or removes from) the registry information\n"
			"regarding performance counters in the given module\n\n"
			"RegPerfMon takes the same command line switches as RegSvr32\n"
			"\n"
			"Usage: RegPerfMon [/U] [/S] Filename\n"
			"\t/U - Unregister\n"
			"\t/S - Silent; no output\n"
			"\tFilename - the name of the performance counter service dll file.\n" << ends;

	MessageBox (NULL, str.str(), g_cbRegPerfMon, MB_OK|MB_SETFOREGROUND);
}	// ShowHelp()

