/* Datentypen fuer die Fehlerbehandlung                         */
/* File: ERRTYPES.H                                             */

/* ZIPEDB: @(#)errtypes.h       2.3  90/04/10"
 */

#ifndef _ERRTYPES_H
#define _ERRTYPES_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

/* Datenstrukturen fuer die Fehlerbehandlung */

/* Fehlerliste */
typedef struct error_entry {
        short error_code;       /* Fehlercode */
        short routine_code;     /* Routinencode */
} ERROR_ENTRY;

typedef struct error_list {
	INT error_cnt;	/* Anzahl der registrierten Fehler */
        ERROR_ENTRY irc[MAXERRORS];
} ERROR_LIST;

/* Fehlerbehandlungsroutine */
#if !defined(_INT_FUNC_DEFINED)

typedef int INT_FUNC (int, int, ...);	 /* Funktion, die int liefert */
typedef INT_FUNC *FUNC_PTR (INT);	 /* Funktion, die Zeiger auf INT_FUNC liefert */

#define _INT_FUNC_DEFINED
#endif

typedef struct err_handler_tab {
	short error_code;
        INT_FUNC *error_handler;
} ERR_ENTRY;

typedef ERR_ENTRY *ERR_TABLE;

#if !defined(E_IGNORE)
#define E_DEFAULT        (int (*)(int,int,...))1
#define E_IGNORE         (int (*)(int,int,...))0
#define E_INSTALLED     -1
#endif

#define ET_DELETE          1
#define ET_FIND            2
#define ET_INSTALL         3

/* Schrittweite bei Vergroesserung der Err_Handlertabelle */
#define ERROR_STEP      20

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _ERRTYPES_H
