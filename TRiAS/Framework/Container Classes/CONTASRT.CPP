// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "contpre.hxx"
#include <process.h>
#include <stdarg.h>
#include <stdio.h>

#if defined(_DEBUG)

#include "DumpBuffer.h"
#include "AssertDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern DumpBuffer dumpBuffer;

LONG g_lAssertBusy = -1;
LONG g_lAssertReallyBusy = -1;

BOOL g_fTraceEnabled = false;

BOOL WINAPI AssertFailedLine(LPCSTR lpszExpr, LPCSTR lpszFileName, int nLine)
{
TCHAR szMessage[_MAX_PATH*2];

// handle the (hopefully rare) case of AfxGetAllocState ASSERT
	if (InterlockedIncrement(&g_lAssertReallyBusy) > 0)
	{
	// assume the debugger or auxiliary port
		wsprintf(szMessage, TEXT("Assertion Failed: File %hs, Line %d\n"),
			lpszFileName, nLine);
		OutputDebugString(szMessage);
		InterlockedDecrement(&g_lAssertReallyBusy);

	// assert w/in assert (examine call stack to determine first one)
		__asm int 3;
		return FALSE;
	}

// get app name or NULL if unknown (don't call assert)
LPCTSTR lpszAppName = TEXT("TRiAS");

// format message into buffer
	wsprintf(szMessage, TEXT("%s: File %hs, Line %d\r\n(%hs)"),
		 lpszAppName, lpszFileName, nLine, lpszExpr);

	if (g_fTraceEnabled)
	{
	// assume the debugger or auxiliary port
	// output into MacsBug looks better if it's done in one string,
	// since MacsBug always breaks the line after each output
	TCHAR szT[_MAX_PATH*2 + 20];
	
		wsprintf(szT, TEXT("Assertion Failed: %s\n"), szMessage);
		OutputDebugString(szT);
	}
	if (InterlockedIncrement(&g_lAssertBusy) > 0)
	{
		InterlockedDecrement(&g_lAssertBusy);
		InterlockedDecrement(&g_lAssertReallyBusy);

	// assert within assert (examine call stack to determine first one)
		__asm int 3;
		return false;
	}

	try {
		dumpBuffer.Clear();
		dumpBuffer.StaticPrintf ("File: %hs\r\nLine: %d\r\n(%hs)\r\n", lpszFileName, nLine, lpszExpr);
		DumpCallsStack (dumpBuffer);  

	AssertDialog dlg (dumpBuffer);
	AssertDialog::Choice res = dlg.GetUserChoice();

	// cleanup
		InterlockedDecrement(&g_lAssertBusy);
		InterlockedDecrement(&g_lAssertReallyBusy);

		switch (res) {
		case AssertDialog::abort:
			exit(1);     // should not return (but otherwise DebugBreak)
			break;

		case AssertDialog::ignore:
			return false;

		case AssertDialog::debug:
			break;	// DebugBreak;

		default:
		// Not reached, cannot use assert!
			MessageBeep (0);
		}

	} catch (...) {		// man hat schone Pferde vor der Apotheke gesehen
	// active popup window for the current thread
	HWND hWndParent = GetActiveWindow();

		if (hWndParent != NULL)
			hWndParent = GetLastActivePopup(hWndParent);

	// display the assert
	int nCode = ::MessageBox(hWndParent, szMessage, TEXT("Assertion Failed!"),
			MB_TASKMODAL|MB_ICONHAND|MB_ABORTRETRYIGNORE|MB_SETFOREGROUND);

	// cleanup
		InterlockedDecrement(&g_lAssertBusy);
		InterlockedDecrement(&g_lAssertReallyBusy);

		if (nCode == IDIGNORE) return false;   // ignore

		if (nCode == IDRETRY) return true;    // will cause DebugBreak

		exit(1);     // should not return (but otherwise DebugBreak)
		return true;
	}
	return true;
}

// Diagnostic Trace -----------------------------------------------------------
void CDECL ExtTrace (LPCTSTR lpszFormat, ...)
{
// all ExtTrace output is controlled by afxTraceEnabled
//	if (!fTraceEnabled) return;

va_list args;
va_start(args, lpszFormat);
TCHAR szBuffer[512]; 

	vsprintf(szBuffer, lpszFormat, args);
	OutputDebugString (szBuffer);

	va_end(args);
}

BOOL WINAPI _DLLENTRY TIsValidString(LPCSTR lpsz, int nLength)
{
	if (lpsz == NULL) return false;
#if defined(WIN32)
	return ::IsBadStringPtrA(lpsz, nLength) == 0;
#else
	return ::IsBadStringPtr (lpsz, nLength) == 0;
#endif
}

BOOL WINAPI _DLLENTRY TIsValidAddress(const void* lp, UINT nBytes, BOOL bReadWrite)
{
// simple version using Win32 APIs for pointer validation.
	return (lp != NULL && !IsBadReadPtr(lp, nBytes) &&
		(!bReadWrite || !IsBadWritePtr((LPVOID)lp, nBytes)));
}

BOOL WINAPI _DLLENTRY TIsValidIUnknown (const void *lp)
{
	if (lp == NULL || !TIsValidAddress (lp, 3*sizeof(void *), false))
		return false;

char *ppv = *(char **)lp;

return 	TIsValidAddress (ppv, 1, false) &&	// QueryInterface
	TIsValidAddress (ppv+sizeof(FARPROC), 1, false) &&	// AddRef
	TIsValidAddress (ppv+2*sizeof(FARPROC), 1, false);	// Release
}


#else // _DEBUG

void CDECL ExtTrace (LPCTSTR lpszFormat, ...)
{
}

BOOL WINAPI _DLLENTRY TIsValidString(LPCSTR lpsz, int nLength)
{
	return true;
}

BOOL WINAPI _DLLENTRY TIsValidAddress(const void* lp, UINT nBytes, BOOL bReadWrite)
{
	return true;
}

BOOL WINAPI _DLLENTRY TIsValidIUnknown (const void *lp)
{
	return true;
}

#endif //_DEBUG

// WindowsVersion feststellen -------------------------------------------------
static BOOL s_fWinVer = false;
static BOOL s_fWin31 = false;
static BOOL s_fWin40 = false;
static BOOL s_fWin41 = false;	// Memphis (#HK970827)
static BOOL s_fWin50 = false;	// Cairo (#HK980223)
static BOOL s_fWinNT = false;
static BOOL s_fWin32s = false;

static void PreCalcVersion (void)
{
	if (s_fWinVer) return;		// nur einmal abarbeiten

// Initialise Version Info
DWORD dwVersion = GetVersion();

	s_fWin31 = false;
	s_fWinNT = false;
	s_fWin32s = false;
	s_fWin40 = false;
	s_fWin41 = false;
	s_fWin50 = false;

#if defined(WIN32)
	if (dwVersion < ~0x7fffffff) {			// Windows NT
		s_fWinNT = true;
		if (LOBYTE(LOWORD(dwVersion)) == 3) {		// Major Version is 3 or greater
			if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
				s_fWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion)) == 4) {
			s_fWin40 = true;	// NT4.0
			s_fWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion)) > 4) {
			s_fWin50 = true;	// NT5.0
			s_fWin40 = true;
			s_fWin31 = true;
		}
	} else if (LOBYTE(LOWORD(dwVersion)) < 4) {	// Win32s
		if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
		    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			s_fWin31 = true;
		s_fWin32s = true;
	} else {					// Chicago or Memphis
		if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			s_fWin41 = true;	// 4.10
		s_fWin31 = true;
		s_fWin40 = true;
	}
#else
	if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
	    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
		s_fWin31 = true;
#endif

	s_fWinVer = true;	// nur einmal abarbeiten
}

BOOL WINAPI _DLLENTRY IsWin31 (void) 
{ 
	if (!s_fWinVer) PreCalcVersion();

return s_fWin31; 
}

BOOL WINAPI _DLLENTRY IsWin40 (void) 
{ 
	if (!s_fWinVer) PreCalcVersion();

return s_fWin40; 
}

BOOL WINAPI _DLLENTRY IsWin41 (void) 
{ 
	if (!s_fWinVer) PreCalcVersion();

return s_fWin41; 
}

BOOL WINAPI _DLLENTRY IsWin50 (void) 
{ 
	if (!s_fWinVer) PreCalcVersion();

return s_fWin50; 
}

BOOL WINAPI _DLLENTRY IsWin32s (void) 
{ 
	if (!s_fWinVer) PreCalcVersion();

return s_fWin32s; 
}

BOOL WINAPI _DLLENTRY IsWinNT (void) 
{ 
	if (!s_fWinVer) PreCalcVersion();

return s_fWinNT; 
}

