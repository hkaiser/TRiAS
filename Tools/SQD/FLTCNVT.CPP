// Konvertierung einer SICAD-RealZahl (interne Darstellung)
// File: FLTCNVT.CXX

#include "stdafx.h"

static char ConvertAscii (char);

static long double FloatConst[14];
static Bool FloatValid = FALSE;

// --> Diese Routine ist nicht maschine-independent ---------------------------

double ReadSicadFloat (char *FloatString) {
register int i;

	if (!FloatValid) {
	// 1. Konstanten berechnen (nur beim 1. Mal)
		FloatConst[0] = 1.0/16.0;
		for (i = 1; i < 14; i++) 
			FloatConst[i] = FloatConst[i-1]/16.0;
		FloatValid = TRUE;
	}

// 2. ASCII-Format in Bin„res Format konvertieren (je Byte ein Digit)
char InBuff[16];		// eingelesene Bin„rZahl

	for (i = 0; i < 16; i++) {
	char inChar = FloatString[i];

		if (inChar == '\0') 
			break;		// kurze Realzahl
		InBuff[i] = ConvertAscii (inChar);
	}
	for ( ; i < 16; i++)
		InBuff[i] = 0;			// restliche Stellen ausnullen

// 3. Konvertierung der Mantisse vornehmen
double Mantisse = 0.0;

	for (i = 0; i < 14; i++) 
		Mantisse += InBuff[i+2]*FloatConst[i];

// 4. Vorzeichen bestimmen
Bool Sign = FALSE;	// default: positive Zahl
int Exp = 0;

	if (InBuff[0] >= 0x08) {
	// negative Zahl
		InBuff[0] &= 0x07;	// Vorzeichen in Exponent l”schen
		Sign = TRUE;
	}
	Exp = InBuff[0] << 4 | InBuff[1];		// GesamtExponent
	Exp -= 64;				// korrigieren

// 5. Exponent konvertieren und reinrechnen
	errno = 0;
	Mantisse = ldexp (Mantisse, Exp * 4);
	if (errno != 0)
		perror (NULL);

// 6. Vorzeichen setzen
	if (Sign)
		Mantisse = -Mantisse;

return Mantisse;
}

static char ConvertAscii (char toConvert) {

	if (toConvert >= '0' && toConvert <= '9')
		return (toConvert - '0');		// DezDigit
	else if (toConvert >= 'A' && toConvert <= 'F')
		return (toConvert - 'A' + 10);		// HexDigit
	else 
		return 0;	// Fehler
}
