/* Headerfile fuer QTree Operartionen                           */
/* File: QTEXTERN.H             last update: 11. Oktober 1989   */

/* ZIPEDB: @(#)qtextern.h       2.4  90/04/10"
 */

#ifndef _QTEXTERN_H
#define _QTEXTERN_H
 
#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

#define QDIM 4          /* 2-dimensionaler Tree */
#define MAXTREELEVEL 30
#define MAXQTREC   	  16777216L
#define MAXKOORD   	1073741824L
 
#define TESTKOORD(x) 	 (((x)>=0)&&((x)<MAXKOORD))
#define ASSERTKOORD(x,r) if(!TESTKOORD(x))db_error(S_BADCOORD,(r))

#ifndef _DEFINED_WINDOW
#define _DEFINED_WINDOW
/* Struktur eines Windows (QTree) */
typedef struct window {
        long x_min, x_max;
        long y_min, y_max;
} WINDOW;
#endif // _DEFINED_WINDOW

 
/* Struktur eines Eintrages im QTree */
typedef struct point {
        long x_min, y_min;
} QTPOINT;
 
/* Struktur eines Hyperwuerfels (QTree) */
typedef union quadrant {
        struct {
                long qd_x, qd_y;        /* Anfangskoordinaten */
                long qd_len;            /* Kantenlaenge */
        } w;
        long feld[3];
} QUADRANT;
 
/* Struktur eines Slots des QTree-Files */
typedef struct qtslot {
        REC_NO records[QDIM];
        unsigned char filled[QDIM];
} QTSLOT;

/* Funktions-Sprungverteiler */
typedef int (FUNCTYPE *QTACTIONPROC)(long, QUADRANT *, QTSLOT *, short);

extern QTACTIONPROC qtaction;
 
/* aktueller durchlaufener Pfad */
extern PAGE_NO cubparent[MAXTREELEVEL];
extern short cubslots[MAXTREELEVEL];
extern DB_ADDR NEAR treedba;                 /* DB-Adresse im QTree */

extern short qtfile;                    /* QTree Keyfile */
 
//#define QTSLOTS    ((PAGESIZE-PAGEHDRSIZE)/sizeof(QT_KEY_SLOT))
#define QTSLOTS	(unsigned)((PageSize-PAGEHDRSIZE)/sizeof(QT_KEY_SLOT))

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _QTEXTERN_H
