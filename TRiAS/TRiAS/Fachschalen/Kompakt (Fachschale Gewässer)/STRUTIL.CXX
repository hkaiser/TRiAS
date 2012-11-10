// Hilfsroutinen fuer die Umwandlung von double-Werten in ein String
// File: STRUTIL.CXX

#include "kompp.hxx"
#include "kompias.h"

// Einfügen von Zeichen ab einer bestimmten Position des gegebenen Strings
static LPSTR PASCAL NEAR
ST_StrInsNChr (LPSTR String, char c, int Pos, int n) 
{
	memmove (&String[Pos+n], &String[Pos], strlen (String)-Pos+1);
	memset (&String[Pos], c, n);

return String;
}

// Umwandlung eines Double-Wertes entsprechend Format-String 
// in eine Zeichenkette
LPSTR FAR PASCAL ST_DtoA (LPSTR String, LPSTR Format, double Wert) 
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
	    ST_StrInsNChr (String, '0', 0, abs (KommaPos) + 1);
	    ST_StrInsNChr (String, '.', 1, 1);
	}
	else
	    ST_StrInsNChr (String, '.', KommaPos, 1);
	if (*(strchr(Format, '%')+1) == '+') {
		if (!Sign)
			ST_StrInsNChr (String, '+', 0, 1);
	}
	if (Sign)
		ST_StrInsNChr (String, '-', 0, 1);
	if (!strchr (Format, '-') &&	 // wenn keine linksbündige Ausgabe
	    (Laenge > (StrLaenge = strlen(String))))
		ST_StrInsNChr (String, ' ', 
			(String[1] == '0' && (*String == '-' || *String == '+')) ?
				1 : 0, Laenge - StrLaenge);
	if (String[Laenge = (strlen(String) -1)] == '.')
		String[Laenge] = '\0';

	return String;
}

