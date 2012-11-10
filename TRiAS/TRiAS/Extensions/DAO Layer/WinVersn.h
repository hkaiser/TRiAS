// WindowsVersion feststellen -------------------------------------------------
// File: WinVersn.h

#if !defined(_WINVERSN_H)
#define _WINVERSN_H

///////////////////////////////////////////////////////////////////////////////
// WindowsVersionsInfo initialisieren
void CalcVersion (void);

///////////////////////////////////////////////////////////////////////////////
// WindowsVersionen abfragen 
bool IsWin31 (void);
bool IsWin40 (void);
bool IsWin32s (void);
bool IsWinNT (void);

#endif // _WINVERSN_H


