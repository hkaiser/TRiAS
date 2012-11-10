// Hilfsroutinen fuer die Umwandlung von double-Werten in ein String
// File: STRUTIL.C

#include "stdafx.h"
#include "AcadDXFImpl.h"

//XX	extern "C" {
	#include <string.h>

// Einfügen von Zeichen ab einer bestimmten Position des gegebenen Strings
//XX	static LPSTR PASCAL NEAR StrInsNChr (LPSTR String, char c, int Pos, int n) 
/*XX*/	static LPSTR StrInsNChr (LPSTR String, char c, int Pos, int n) 
{
	memmove (&String[Pos+n], &String[Pos], lstrlen (String)-Pos+1);
	memset (&String[Pos], c, n);

return String;
}

// Umwandlung eines Double-Wertes entsprechend Format-String 
// in eine Zeichenkette
//XX	LPSTR FAR PASCAL DtoA (LPSTR String, LPSTR Format, double Wert) 
/*XX*/	LPSTR DtoA (LPSTR String, LPCTSTR Format, double Wert) 
{
register int Laenge;
register int StrLaenge;
int NachKomma = 0;
int KommaPos;
int Sign;
//XX	LPSTR lpA;
/*XX*/	LPCTSTR lpA;
//XX	LPSTR lpB;
/*XX*/	LPCTSTR lpB;

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
	lstrcpy (String, fcvt (Wert, NachKomma, &KommaPos, &Sign));
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
	    (Laenge > (StrLaenge = lstrlen(String))))
		StrInsNChr (String, ' ', 
			(String[1] == '0' && (*String == '-' || *String == '+')) ?
				1 : 0, Laenge - StrLaenge);
	if (String[Laenge = (lstrlen(String) -1)] == '.')
		String[Laenge] = '\0';

	return String;
}

//XX	}	// extern "C"
