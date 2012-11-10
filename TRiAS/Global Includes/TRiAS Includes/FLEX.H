/* Headerdatei fuer dynamische Feldverwaltung                           */
/* File: FLEX.H                                                         */

/* ZIPEDB: @(#)flex.h   2.3  90/05/02
 */

#ifndef _FLEX_H
#define _FLEX_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

/* Anzahl der gleichzeitig zu verwaltenden Felder */
#define MAXFLEXES       20

/* Schrittweite bei Flexgenerierung */
#define FLEXSTEP        256

/* Struktur eines dynamischen Feldes */
typedef struct flex {
	long __huge *pFlex;		// eigentliches Feld
	unsigned long len;		// aktuelle Anzahl der Feldelemente
	unsigned long max;		// aktuelle Feldgroesse
	short used;				// TRUE, wenn benutzt
	short iShrink;			// TRUE, wenn verdichtet werden darf
#if defined(MSWIND) || defined(_WINDOWS)
	HGLOBAL handle;			// Speicherhandle des Feldes
#endif
} FLEX;

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _FLEX_H
