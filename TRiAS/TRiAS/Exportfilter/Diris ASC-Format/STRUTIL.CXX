// Hilfsroutinen fuer die Umwandlung von double-Werten in ein String
// File: STRUTIL.C

#include "stdafx.h"

#include <string.h>

// Einfügen von Zeichen ab einer bestimmten Position des gegebenen Strings
static LPSTR PASCAL NEAR
StrInsNChr (LPSTR String, char c, int Pos, int n) 
{
	memmove (&String[Pos+n], &String[Pos], strlen (String)-Pos+1);
	memset (&String[Pos], c, n);

return String;
}

// Umwandlung eines Double-Wertes entsprechend Format-String 
// in eine Zeichenkette

extern "C" LPSTR PASCAL DtoAFlt (LPSTR String, LPSTR Format, double Wert) 
{
register int Laenge;
register int StrLaenge;
int NachKomma = 0;
int KommaPos;
int Sign;
LPSTR lpA;
LPSTR lpB;

	lpA = Format + strcspn (Format, "0123456789");
	lpB = strchr (Format, '.');
	if (lpB) 
		NachKomma = atoi (lpB+1);
	else {
		lpB = lpA;
		NachKomma = 3;
	}
	if (lpA <= lpB) 
		Laenge = atoi (lpA);
	else
		Laenge = 7;
	strcpy (String, fcvt (Wert, NachKomma, &KommaPos, &Sign));
	if (KommaPos <= 0) {
	    StrInsNChr (String, '0', 0, abs (KommaPos) + 1);
	    StrInsNChr (String, '.', 1, 1);
	}
	else
	    StrInsNChr (String, '.', KommaPos, 1);
	if (*(strchr(Format, '%')+1) == '+') {
		if (!Sign)
			StrInsNChr (String, '+', 0, 1);
	}
	if (Sign)
		StrInsNChr (String, '-', 0, 1);
	if (!strchr (Format, '-') &&	 // wenn keine linksbündige Ausgabe
	    (Laenge > (StrLaenge = strlen(String))))
		StrInsNChr (String, ' ', 
			(String[1] == '0' && (*String == '-' || *String == '+')) ?
				1 : 0, Laenge - StrLaenge);
	if (String[Laenge = (strlen(String) -1)] == '.')
		String[Laenge] = '\0';

	return String;
}

// ZeichenkettenKonvertierung ANSI <-> UNICODE --------------------------------
#if defined(WIN32) && !defined(OLE2ANSI)

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

#endif

#if defined(WIN32)

inline LPWSTR __ConvertStrAtoW2 (const char *strIn, LPWSTR buf, UINT size)
{
	MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, strIn, -1, buf, size); 

return buf;
}


LPWSTR ConvertStrAtoW2 (const char *strIn, LPWSTR buf, UINT size)
{
	return __ConvertStrAtoW2 (strIn, buf, size);
}

LPWSTR WideString2 (const char *strIn)
{
static wchar_t buf[1024];
  
	return (__ConvertStrAtoW2 (strIn, buf, 1024));
}

inline char *__ConvertStrWtoA2 (LPCWSTR strIn, char *buf, UINT size)
{
int badConversion = false;
  
	WideCharToMultiByte (CP_ACP, NULL, strIn, -1, buf, size, 
			     NULL, &badConversion);

return buf;
}

char *ConvertStrWtoA2 (LPCWSTR strIn, char *buf, UINT size)
{
	return __ConvertStrWtoA2 (strIn, buf, size);
}

char *AnsiString2 (LPCWSTR strIn)
{
static char buf[1024];
  
	return (__ConvertStrWtoA2 (strIn, buf, 1024));
}

#endif
