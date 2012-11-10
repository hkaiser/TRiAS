// Fehler in BasicScript ------------------------------------------------------
// File: BSCRERR.H

#if !defined(_BSCRERR_H)
#define _BSCRERR_H

#define TRIASERR_TYPEMISMATCH	10000		// Typemismatch für TRiASObjekte
#define TRIASERR_NOTSUPPORTED	10001		// ErrorCode für nicht definierte Funktion 
#define TRIASERR_GENERALERROR	10002		// ErrorCode für unbekannten Fehler

extern int g_fDebugScript;

#endif // _BSCRERR_H