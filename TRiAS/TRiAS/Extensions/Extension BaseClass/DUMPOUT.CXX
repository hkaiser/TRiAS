// Diagnostics ----------------------------------------------------------------
// File: DUMPOUT.CXX

#include "xtensnp.hxx"
#include <stdarg.h>
#include <stdio.h>

#include <xtsnaux.hxx>

#if defined(_DEBUG)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LONG g_lAssertBusy = -1;
LONG g_lAssertReallyBusy = -1;

bool g_fTraceEnabled = false;

bool WINAPI DEX_AssertFailedLine(LPCSTR lpszExpr, LPCSTR lpszFileName, int nLine)
{
TCHAR szMessage[_MAX_PATH*2];

// handle the (hopefully rare) case of AfxGetAllocState ASSERT
#if defined(WIN32)
	if (InterlockedIncrement(&g_lAssertReallyBusy) > 0)
	{
	// assume the debugger or auxiliary port
		wsprintf(szMessage, TEXT("Assertion Failed: File %hs, Line %d\n"),
			lpszFileName, nLine);
		OutputDebugString(szMessage);
		InterlockedDecrement(&g_lAssertReallyBusy);

	// assert w/in assert (examine call stack to determine first one)
		DebugBreak();
		return FALSE;
	}
#endif

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

#if defined(WIN32)
	if (InterlockedIncrement(&g_lAssertBusy) > 0)
	{
		InterlockedDecrement(&g_lAssertBusy);

	// assert within assert (examine call stack to determine first one)
		DebugBreak();
		return FALSE;
	}
#endif // WIN32

// active popup window for the current thread
HWND hWndParent = GetActiveWindow();

	if (hWndParent != NULL)
		hWndParent = GetLastActivePopup(hWndParent);

// display the assert
#if defined(WIN32)
int nCode = ::MessageBox(hWndParent, szMessage, TEXT("Assertion Failed!"),
		MB_TASKMODAL|MB_ICONHAND|MB_ABORTRETRYIGNORE|MB_SETFOREGROUND);

// cleanup
	InterlockedDecrement(&g_lAssertBusy);
#else
int nCode = ::MessageBox(hWndParent, szMessage, TEXT("Assertion Failed!"),
		MB_TASKMODAL|MB_ICONHAND|MB_ABORTRETRYIGNORE);
#endif

	if (nCode == IDIGNORE) return FALSE;   // ignore

	if (nCode == IDRETRY) return TRUE;    // will cause DebugBreak

	abort();     // should not return (but otherwise DebugBreak)

return TRUE;
}


// Diagnostic Trace -----------------------------------------------------------
#if !defined(__CV__)/* && !defined(__WTL__)*/

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

#endif // __CV__ && !defined(__WTL__)

#else // _DEBUG

#if !defined(__CV__)/* && !defined(__WTL__)*/

void CDECL ExtTrace (LPCTSTR lpszFormat, ...)
{
}

#endif // TX_TRACE
#endif //_DEBUG

