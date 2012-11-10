// Ersatzfunktion fuer Rectangle ----------------------------------------------
// File: DRAWRECT.CXX

#include <bool.h>
#include <windows.h>

#if !defined(WIN32)
#define EXPORT02	__export
#define _ENTRY		/*__export*/
#define _TRIAS02_ENTRY
#else
#define EXPORT02
#define _ENTRY		__declspec(dllimport)
#define _TRIAS02_ENTRY	__declspec(dllexport)
#endif

extern "C" _TRIAS02_ENTRY 
BOOL EXPORT02 WINAPI DrawRectangle (HDC hDC, int x1, int y1, int x2, int y2) 
{
#if defined(WIN32)
	return Rectangle (hDC, x1, y1, x2, y2);
#else
	return ::rectangle (hDC, x1, y1, x2, y2);
#endif
}
