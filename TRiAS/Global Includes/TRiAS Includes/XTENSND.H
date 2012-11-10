// DiagnoseNotifikationen -----------------------------------------------------
// File: XTENSND.H
// @doc
// @module XTENSND.H | Enhält die Definitionen aller Codes von 
// <tpc Diagnose-Notifikationen> und aller entsprechenden auslösenden Funktionen.
// @topic Diagnose-Notifikationen | Die Diagnose-Notifikationen von <tr> sind
// zusätzliche <tpc Notifikationen>, die dazu verwendet werden können, von außen 
// interne Prozesse in <tr> besser mitzuverfolgen.<nl>Diese Notifikationen werden 
// an verschiedenen Stellen des Programmablaufes verschickt. Insbesondere bei
// nicht vorhergesehenen Programmverläufen oder besonderen Programmzuständen
// liefern sie zusätzliche Diagnose-Informationen, die unterstützend bei der 
// Fehlersuche sein können.<nl>Diagnose-Notifikationen müssen ebenso wie normale
// <tpc Notifikationen> registriert werden, damit diese an eine Erweiterung 
// verschickt werden.<nl>Die Diagnose-Notifikationen werden jedoch lediglich 
// dann generiert, wenn durch die Message <m DEX_DIAGNOSTICSENABLE> das 
// entsprechende Flag in <tr> gestzt worden ist.

#ifndef _XTENSND_H
#define _XTENSND_H

#include <pshpack1.h>

#if defined(__cplusplus)
extern "C" {
#endif

// NotifikationsKonstanten ----------------------------------------------------
const short DEXD_OBJECTTODRAW		= 1000;	// ein Objekt wurde gezeichnet
const short DEXD_OBJECTNOTDRAWED1	= 1001;	// Objekt wurde nicht gezeichnet
const short DEXD_OBJECTNOTDRAWED2	= 1002;	// Objekt wurde nicht gezeichnet
const short DEXD_OBJECTNOTDRAWED3	= 1003;	// Objekt wurde nicht gezeichnet
const short DEXD_OBJECTNOTDRAWED4	= 1004;	// Objekt wurde nicht gezeichnet
const short DEXD_OBJECTNOTDRAWED5	= 1005;	// Objekt wurde nicht gezeichnet
const short DEXD_IDENTTOHANDLE		= 1006;	// Identifikator zu behandeln
const short DEXD_IDENTTODRAW		= 1007;	// Identifikator soll gezeichnet werden
const short DEXD_IDENTISLOADEDFULL	= 1008;	// Ident ist vollständig geladen
const short DEXD_IDENTISLOADEDPART	= 1009;	// Ident ist teilweise geladen
const short DEXD_IDENTISNOTLOADED	= 1010;	// Ident ist nicht geladen
const short DEXD_IDENTNOTTODRAW		= 1011;	// Ident ist nicht zu zeichnen
const short DEXD_IDENTWASLOADED		= 1012;	// Ident soll entladen werden
const short DEXD_IDENTWASNOTLOADED	= 1013;	// Ident soll entladen werden
const short DEXD_OBJTREEOPTIMIZED	= 1014;	// ObjTree was optimized
const short DEXD_IDENTTREEOPTIMIZED	= 1015;	// IdentTree was optimized

#if defined(__cplusplus)
}
#endif

extern bool g_fDiagnostics;	// Flag, welches darüber entscheidet, ob Diagnose
				// ausgegeben werden soll
// DiagnoseMeldungen auslösen -------------------------------------------------
inline void DEXD_ObjectToDraw (long lONr)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) 
		DexNotificationProc((WPARAM)DEXD_OBJECTTODRAW,(LPARAM)lONr);
#endif // DIAGNOSTICS
}

// nicht gezeichnet, da Erweiterung nicht wollte ------------------------------
inline void DEXD_ObjectNotDrawed1 (long lONr)	
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_OBJECTNOTDRAWED1, (LPARAM)lONr);
#endif // DIAGNOSTICS
}

// nicht gezeichnet, da falscher IdentMode ------------------------------------
inline void DEXD_ObjectNotDrawed2 (long lONr)	
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_OBJECTNOTDRAWED2, (LPARAM)lONr);
#endif // DIAGNOSTICS
}

// nicht gezeichnet, da falscher ObjektTyp ------------------------------------
inline void DEXD_ObjectNotDrawed3 (long lONr)	
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_OBJECTNOTDRAWED3, (LPARAM)lONr);
#endif // DIAGNOSTICS
}

// nicht gezeichnet, da nicht im Ausschnitt -----------------------------------
inline void DEXD_ObjectNotDrawed4 (long lONr)	
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_OBJECTNOTDRAWED4, (LPARAM)lONr);
#endif // DIAGNOSTICS
}

// nicht gezeichnet, da Zeichenfunktion versagt hat ---------------------------
inline void DEXD_ObjectNotDrawed5 (long lONr)	
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_OBJECTNOTDRAWED5, (LPARAM)lONr);
#endif // DIAGNOSTICS
}

// Identifikatoren beim zeichnen verfolgen ------------------------------------
inline void DEXD_IdentToHandle (long lIdent)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_IDENTTOHANDLE, (LPARAM)lIdent);
#endif // DIAGNOSTICS
}

inline void DEXD_IdentToDraw (long lIdent)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_IDENTTODRAW, (LPARAM)lIdent);
#endif // DIAGNOSTICS
}

inline void DEXD_IdentNotToDraw (long lIdent)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_IDENTNOTTODRAW, (LPARAM)lIdent);
#endif // DIAGNOSTICS
}

inline void DEXD_IdentIsLoadedFull (long lIdent)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_IDENTISLOADEDFULL, (LPARAM)lIdent);
#endif // DIAGNOSTICS
}

inline void DEXD_IdentIsLoadedPart (long lIdent)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_IDENTISLOADEDPART, (LPARAM)lIdent);
#endif // DIAGNOSTICS
}

inline void DEXD_IdentIsNotLoaded (long lIdent)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_IDENTISNOTLOADED, (LPARAM)lIdent);
#endif // DIAGNOSTICS
}

inline void DEXD_IdentWasLoaded (long lIdent)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_IDENTWASLOADED, (LPARAM)lIdent);
#endif // DIAGNOSTICS
}

inline void DEXD_IdentWasNotLoaded (long lIdent)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_IDENTWASNOTLOADED, (LPARAM)lIdent);
#endif // DIAGNOSTICS
}

// sonstige schnuckelige Meldungen vom Zeichnen -------------------------------
inline void DEXD_ObjectTreeOptimized (DWORD dwTimeDelta)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_OBJTREEOPTIMIZED, (LPARAM)dwTimeDelta);
#endif // DIAGNOSTICS
}

inline void DEXD_IdentTreeOptimized (void)
{
#if defined(DIAGNOSTICS)
	if (g_fDiagnostics) DexNotificationProc((WPARAM)DEXD_IDENTTREEOPTIMIZED, 0L);
#endif // DIAGNOSTICS
}

#include <poppack.h>

#endif // _XTENSND_H
