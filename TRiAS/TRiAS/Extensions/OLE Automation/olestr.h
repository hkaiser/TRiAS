// String - Funktionen für OLESTR/BSTR ----------------------------------------
// File: OLESTR.H

#if !defined(_OLESTR_H)
#define _OLESTR_H

#if !defined(OLE2ANSI) && defined(WIN32)
// BSTR ist unsigned short *
#define olescmp	wcscmp

#else
// BSTR ist char *
#define olescmp	strcmp

#endif // !OLE2ANSI && WIN32

#endif // _OLESTR_H
