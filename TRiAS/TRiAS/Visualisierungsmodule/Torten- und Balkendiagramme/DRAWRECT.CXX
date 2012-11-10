// Ersatzfunktion fuer Rectangle ----------------------------------------------
// File: DRAWRECT.CXX

#include <bool.h>
#include <windows.h>

extern "C" BOOL WINAPI DrawRectangle (HDC hDC, int x1, int y1, int x2, int y2) 
{
#if defined(WIN32)
	return Rectangle (hDC, x1, y1, x2, y2);
#else
	return ::rectangle (hDC, x1, y1, x2, y2);
#endif
}
