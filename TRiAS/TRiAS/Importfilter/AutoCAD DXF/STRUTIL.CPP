// Hilfsroutinen fuer die Umwandlung von double-Werten in ein String
// File: STRUTIL.CPP

#include "pheader.hpp"

extern "C" {
	#include <stdlib.h>
	#include <string.h>
}

char *DtoA (double Wert, char *String, char *Format = NULL); 
char DoubleFormat [] = "%10.3lf";    // voreingestelltes double-Format

// Einfügen von Zeichen ab einer bestimmten Position des gegebenen Strings
static char *StrInsNChr (char *String, char c, int Pos, int n) 
{
	memmove (&String[Pos+n], &String[Pos], lstrlen (String)-Pos+1);
	memset (&String[Pos], c, n);

return String;
}

// Umwandlung eines Double-Wertes entsprechend Format-String 
// in eine Zeichenkette
char *DtoA (double Wert, char *String, char *Format) 
{
register int Laenge;
register int StrLaenge;
int NachKomma = 0;
int KommaPos;
int Sign;
char *lpA;
char *lpB;

//  prüfe Parameter
	if (Format == NULL)
		Format = DoubleFormat;

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
	if (!strchr (Format, '-') &&   // wenn keine linksbündige Ausgabe
	    (Laenge > (StrLaenge = strlen(String))))
		StrInsNChr (String, ' ', 
			(String[1] == '0' && (*String == '-' || *String == '+')) ?
				1 : 0, Laenge - StrLaenge);
	if (String[Laenge = (strlen(String) -1)] == '.')
		String[Laenge] = '\0';

//  führende Leerzeichen ggf. Löschen        
	if (*String == ' ')
	{
	//  1. gültige Zeichen suchen
		char *pFirstCh = String;
		while (*pFirstCh != '\0' && *pFirstCh == ' ')
			pFirstCh++;

	//  String umkopieren
		char *pStringTmp = String;
		while (*pFirstCh != '\0')
			*pStringTmp++ = *pFirstCh++;

		*pStringTmp = '\0';     // Endekennzeichen setzen
	}

	return String;
}

