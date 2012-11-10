// Von TRIAS02 exportierte Funktionen -----------------------------------------
// File: FUNCS02.H

#if !defined(_FUNCS02_H)
#define _FUNCS02_H

// C++ -Funktionen ////////////////////////////////////////////////////////////
_TRIAS02_ENTRY bool IsValidONr (LONG lONr);
_TRIAS02_ENTRY bool IsValidIdent (LONG lIdent);
_TRIAS02_ENTRY bool IsValidMCode (LONG lMCode);
_TRIAS02_ENTRY bool IsValidRCode (LONG lRCode);

// C-Funktionen ///////////////////////////////////////////////////////////////
// InitialisierungsFunktion für TRIAS02
extern "C" _TRIAS02_ENTRY void FUNCTYPE InitTrias02 (HWND, UINT, UINT, UINT);
extern "C" _TRIAS02_ENTRY void FUNCTYPE EXPORT02 CleanUpTrias02 (void);

// FuzzyMatching von Strings
extern "C" _TRIAS02_ENTRY int FUNCTYPE EXPORT02 isalike (char *, char *);
extern "C" _TRIAS02_ENTRY char *WINAPI DtoA (char *, char *, double);

extern "C" _TRIAS02_ENTRY BOOL isDBTextObjekt (INT_PTR lONr);
extern "C" _TRIAS02_ENTRY BOOL isDBSubTextObjekt (INT_PTR lONr);
extern "C" _TRIAS02_ENTRY BOOL isDBSubTextObjektInd (INT_PTR lONr);

extern "C" _TRIAS02_ENTRY long FUNCTYPE EXPORT02 AssociatedObjekt (INT_PTR lONr, bool *pfRelated);
extern "C" _TRIAS02_ENTRY long FUNCTYPE EXPORT02 AssociatedTextObjekt (INT_PTR);

extern "C" _TRIAS02_ENTRY bool WINAPI DrawRectangle (HDC hDC, int x1, int y1, int x2, int y2);
extern "C" _TRIAS02_ENTRY long EXPORT02 FindLong (long *, long, long);

extern "C" _TRIAS02_ENTRY BOOL EXPORT02 ExpandPalette (HPALETTE hPal, class VisInfo *pVI);
extern "C" _TRIAS02_ENTRY BOOL EXPORT02 ExpandPaletteColor (HPALETTE hPal, COLORREF C);
extern "C" _TRIAS02_ENTRY class VisInfo * EXPORT02 MakeNewVI (enum VisType iVTyp);
extern "C" _TRIAS02_ENTRY short EXPORT02 MakeCompleteNewVisInfo (VisInfo **ppVI, short iBits, BOOL fSpecial);

#endif // _FUNCS02_H
