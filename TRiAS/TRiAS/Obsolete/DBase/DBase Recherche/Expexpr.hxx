// Expandieren einer Expression, die Parameter der Form %1, %2 etc. enthaelt
// File: EXPEXPR.HXX

#ifndef  _EXPEXPR_HXX
#define _EXPEXPR_HXX

char *ExpandParams (long ON,		// ObjektNummer
		    long *MCodes,       // Feld der DBase-relevanten MerkmalsCodes
		    char **MStrs,       // Feld evtl. gegebener Merkmalswerte
		    short numMCodes,    // Anzahl der DBase-Merkmale
		    char *Out,          // AusgabeBuffer
		    short ExprSize,     // Gr”áe des AusgabeBuffers
		    char *In);		// EingabeExpression

#endif	    // _EXPEXPR_HXX
