// Hilfsroutinen fuer die Umwandlung von double-Werten in ein String
// File: STRUTIL.C

#include "tortenp.hxx"

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
extern "C" LPSTR FAR PASCAL DtoAVMD (LPSTR String, LPSTR Format, double Wert) 
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
#if defined(WIN32)

inline OLECHAR *__ConvertStrAtoW (const char *strIn, OLECHAR *buf, UINT size)
{
	MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, strIn, -1, buf, size); 

return buf;
}


OLECHAR *ConvertStrAtoW (const char *strIn, OLECHAR *buf, UINT size)
{
	return __ConvertStrAtoW (strIn, buf, size);
}

OLECHAR *VMDWideString (const char *strIn)
{
static OLECHAR buf[_MAX_PATH];
  
	return (__ConvertStrAtoW (strIn, buf, _MAX_PATH));
}

inline char *__ConvertStrWtoA (const OLECHAR *strIn, char *buf, UINT size)
{
int badConversion = false;
  
	WideCharToMultiByte (CP_ACP, NULL, strIn, -1, buf, size, 
			     NULL, &badConversion);

return buf;
}

char *ConvertStrWtoA (const OLECHAR *strIn, char *buf, UINT size)
{
	return __ConvertStrWtoA (strIn, buf, size);
}

char *VMDAnsiString (const OLECHAR *strIn)
{
static char buf[256];
  
	return (__ConvertStrWtoA (strIn, buf, 256));
}

#else

#include <tchar.h>

char *VMDAnsiString (const OLECHAR *strIn)
{
	return (char *)strIn;
}

OLECHAR *VMDWideString (const char *strIn)
{
	return (char *)strIn;
}

#endif // WIN32
