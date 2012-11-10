// StringKonvertierung ANSI<-->UNICODE ----------------------------------------
// File: STRCVRT.CPP

#include "stdafx.h"

#include "strcvrt.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

inline LPWSTR __ConvertStrAtoW (const char *strIn, LPWSTR buf, UINT size)
{
	MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, strIn, -1, buf, size); 

return buf;
}

LPWSTR ConvertStrAtoW (const char *strIn, LPWSTR buf, UINT size)
{
	return __ConvertStrAtoW (strIn, buf, size);
}

LPWSTR WideString (const char *strIn)
{
static wchar_t buf[1024];
  
	return (__ConvertStrAtoW (strIn, buf, 1024));
}

inline char *__ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size)
{
int badConversion = false;
  
	WideCharToMultiByte (CP_ACP, NULL, strIn, -1, buf, size, 
			     NULL, &badConversion);

return buf;
}

char *ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size)
{
	return __ConvertStrWtoA (strIn, buf, size);
}

char *AnsiString (LPCWSTR strIn)
{
static char buf[1024];
  
	return (__ConvertStrWtoA (strIn, buf, 1024));
}
