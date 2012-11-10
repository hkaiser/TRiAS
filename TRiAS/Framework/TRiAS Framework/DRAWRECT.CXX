// Ersatzfunktion fuer Rectangle ----------------------------------------------
// File: DRAWRECT.CXX

#if !defined(_CV_NO_PRAGMA_WARNINGS)
#if _MSC_VER > 1020
#pragma warning(disable: 4800)	// forcing value to bool 'true' or 'false'
#endif // _MSC_VER
#endif // _CV_NO_PRAGMA_WARNINGS

#include <bool.h>
#include <windows.h>

extern "C" bool DrawRectangle (HDC hDC, int x1, int y1, int x2, int y2) 
{
	return Rectangle (hDC, x1, y1, x2, y2);
}
