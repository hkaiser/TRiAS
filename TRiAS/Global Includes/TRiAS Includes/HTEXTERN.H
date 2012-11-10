/* Headerfile fuer HTree Operartionen							*/
/* File: HTEXTERN.H 			last update: 7. September 1989	*/

/* ZIPEDB: @(#)htextern.h		2.4  90/04/10"
 */

#ifndef _HTEXTERN_H
#define _HTEXTERN_H
 
#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

#define HDIM 16 		/* 4-dimensionaler Tree */
#define MAXTREELEVEL 30
#define MAXHTREC	  16777216L
#define MAXKOORD	1073741824L 

#define TESTKOORD(x)	 (((x)>=0)&&((x)<MAXKOORD))
#define ASSERTKOORD(x,r) if(!TESTKOORD(x))db_error(S_BADCOORD,(r))

// SubKnoten testen/nicht testen
const FLAG COMPARE = 1;
const FLAG NOCOMP = 0;

// Position der Koordinaten in einem double[4]-Fenster
#define XMIN	0
#define XMAX	1
#define YMIN	2
#define YMAX	3

#ifndef _DEFINED_WINDOWACTIONPROC
#define _DEFINED_WINDOWACTIONPROC
typedef long (__cdecl * QTWINDOWACTIONPROC)(DB_ADDR *, ...);
typedef long (__cdecl * HTWINDOWACTIONPROC)(DB_ADDR *, ...);
#endif // _DEFINED_WINDOWACTIONPROC

#ifndef _DEFINED_WINDOW
#define _DEFINED_WINDOW
/* Struktur eines Windows (HTree) */
typedef struct window {
	long x_min, x_max;
	long y_min, y_max;
} WINDOW;
#endif // _DEFINED_WINDOW

/* Struktur eines Containers fuer HTree */
typedef struct container {
	long x_min, x_max;
	long y_min, y_max;
} CONTAINER;
 
/* Struktur eines Hyperwuerfels (HTree) */
typedef union hypercube {
	struct {
		long hc_w, hc_x, hc_y, hc_z;	/* Anfangskoordinaten */
		long hc_len;					/* Kantenlaenge */
	} w;
	long feld[5];
} HYPERCUBE;
 
/* Struktur eines Slots des HTree-Files */
typedef struct htslot {
	REC_NO records[HDIM];
	unsigned char filled[HDIM];
} HTSLOT;

/* Funktions-Sprungverteiler */
typedef int (FUNCTYPE *HTACTIONPROC)(long, HYPERCUBE *, HTSLOT _far *, short);

extern HTACTIONPROC htaction;

/* aktueller durchlaufener Pfad */
extern PAGE_NO cubparent[MAXTREELEVEL];
extern short cubslots[MAXTREELEVEL];
extern DB_ADDR NEAR treedba;				 /* DB-Adresse im HTree */

extern short htfile;			/* aktuelles HTree-File */
 
//#define HTSLOTS	 ((PAGESIZE-PAGEHDRSIZE)/sizeof(HT_KEY_SLOT))
#define HTSLOTS (unsigned)((PageSize-PAGEHDRSIZE)/sizeof(HT_KEY_SLOT))

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _HTEXTERN_H
