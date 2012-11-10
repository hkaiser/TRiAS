// Diagnostics ----------------------------------------------------------------
// File: DUMPOUT.CXX

#include "triaspre.hxx"
#include <stdarg.h>
#include <stdio.h>

#if defined(_DEBUG)   // entire file

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

#else

void CDECL ExtTrace (LPCTSTR lpszFormat, ...)
{
}

#endif //_DEBUG

