// StringKonvertierung ANSI<-->UNICODE ----------------------------------------
// File: STRCVRT.H

#if !defined(_STRCVRT_H)
#define _STRCVRT_H

LPWSTR ConvertStrAtoW (LPCSTR strIn, LPWSTR buf, UINT size);
LPWSTR WideString (LPCSTR strIn);
LPSTR ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size);
LPSTR AnsiString (LPCWSTR strIn);

#endif // _STRCVRT_H
