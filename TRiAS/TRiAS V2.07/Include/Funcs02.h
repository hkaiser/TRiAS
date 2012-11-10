// Von TRIAS02 exportierte Funktionen -----------------------------------------
// File: FUNCS02.H

#if !defined(_FUNCS02_H)
#define _FUNCS02_H

// C++ -Funktionen ////////////////////////////////////////////////////////////
_TRIAS02_ENTRY bool IsValidONr (HPROJECT hPr, LONG lONr);
_TRIAS02_ENTRY bool IsValidIdent (LONG lIdent);
_TRIAS02_ENTRY bool IsValidMCode (LONG lMCode);
_TRIAS02_ENTRY bool IsValidRCode (LONG lRCode);

// C-Funktionen ///////////////////////////////////////////////////////////////
// InitialisierungsFunktion für TRIAS02 ---------------------------------------
extern "C"
_TRIAS02_ENTRY void FUNCTYPE InitTrias02 (HWND, UINT, UINT, UINT);

// FuzzyMatching von Strings
extern "C"
_TRIAS02_ENTRY int FUNCTYPE EXPORT02 isalike (char *, char *);

#endif // _FUNCS02_H
