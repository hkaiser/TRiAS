// Expandieren einer Expression, die Parameter der Form %1, %2 etc. enthaelt
// File: EXPEXPR.CXX

#include "pheader.h"

#include "expexpr.htp"
#include <commonvu.hxx>

extern "C" {
	#include <ctype.h>
}

#include "tools.hxx"			// GetMiText ()
#include "expexpr.hxx"		  	// zugeh. Header

// lokale Variablen -----------------------------------------------------------
static char *OutPut;
static char *EndOutPut;

// lokale Funktionen ----------------------------------------------------------
static short OutChar (char OutC) 
{
	if (OutPut +1 < EndOutPut) 
	{
		*OutPut++ = OutC;
		return OutC;
	} 
	else 
	{
		*(EndOutPut -1) = '\0'; // StringAbschluß
		DEX_Error (RC_ExpandParams, EC_NOEXPRSPACE);
		return -1;
	}
}

static char *OutString (char *OutStr) 
{
	char *OutBegin = OutStr;

	if (OutStr == NULL)
		return NULL;
	while (*OutStr) 
	{
		if (OutChar (*OutStr++) < 0)
			return NULL;
	}

	return OutBegin;
}

// Diese Funktion scannt die EingabeExpression (In) ab und ersetzt dabei
// Ausdrücke der Form %1, %2 etc. durch den jeweilige Merkmalswert, dessen
// MerkmalsCode in MCodes gegeben ist
char *ExpandParams (long ON,			// ObjektNummer
					long *MCodes,	   // Feld der DBase-relevanten MerkmalsCodes
					char **MStrs,	   // Feld evtl. gegebener Merkmalswerte
					short numMCodes,	// Anzahl der DBase-Merkmale
					char *Out,		  // AusgabeBuffer
					short ExprSize,	 // Größe des AusgabeBuffers
					char *In)		   // EingabeExpression
{
// 	wenn keine Parameter enthalten sind, dann umkopieren und raus
	if (strchr (In, '%') == NULL) 
	{
		memset (Out, '\0', ExprSize);
		lstrcpyn (Out, In, ExprSize);
		Out[ExprSize] = '\0';
		return Out;
	}

	char *pIn = In;
	char *ParamText = NULL;

	OutPut = Out;				   // AusgabeZeile initialisieren
	EndOutPut = OutPut + ExprSize;

	while (*pIn) 
	{	// gesamte Eingabezeile verarbeiten
		if (*pIn++ == '%') 	// Parameter ?
		{
			if (!isdigit (*pIn)) 
			{
			// 	überlesene Zeichen ausgeben
				if (OutChar ('%') < 0) 
					return NULL;
				if (*pIn++ != '%') 
				{	// '%%' -> '%'
					if (OutChar (*(pIn-1)) < 0) 
						return NULL;
				}
				continue;
			}
			short ParNum = atoi (pIn);	  // konvertieren
			if (ParNum <= 0) 
			{
			// 	DEX_Error (RC_ExpandParams, EC_BADPARAM);
				return NULL;	// Fehler
			}
			if (ParNum > 0) 
			{
			// 	wirklich Parameter: Digits überspringen
				while (isdigit (*pIn))
					pIn++;
			// 	Merkmalswert lesen
			if (ParNum > numMCodes) 
			{
			// 	DEX_Error (RC_ExpandParams, EC_BADPARAM);
				return NULL;
			}
			if (MCodes[ParNum-1] >= 0) 
			{
			// 	MerkmalsCode gegeben
				GetMiText (MCodes[ParNum-1], ON, ParamText);
				if (OutString (ParamText) == NULL) 
				{
					DELETE_VEC (ParamText);
					return NULL;
				}
				DELETE_VEC (ParamText);
			} 
			else
				if (MStrs[ParNum-1] != NULL) 
				{
				// 	Merkmalswert direkt gegeben
					if (OutString (MStrs[ParNum-1]) == NULL) 
						return NULL;
				} 
				else 
				{
				// 	DEX_Error (RC_ExpandParams, EC_NOMERKMAL);
					return NULL;
				}
			}
		} 
		else 
		{
		// 	einfach ausgeben
			if (OutChar (*(pIn-1)) < 0)
				return NULL;
		}
	}
	OutChar ('\0');		 // StringAbschluß

	return Out;
}
