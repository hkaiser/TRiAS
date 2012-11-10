/* Struktur zur Pruefung der Rueckverkettung einer DB-Datei	*/
/* File: DBCHECK.H						*/

/* ZIPEDB: %W%	%E%
*/

#ifndef _DBCHECK_H
#define _DBCHECK_H

/* Delete chain */
typedef struct d_chain {
	REC_NO rec_no;		/* Recordnummer des geloeschten Satzes */
	struct d_chain *next;	/* Naechste DCHAIN Struktur */
	FLAG found;		/* TRUE, wenn Satz beim Scannen der Datei
				   gefunden wurde */
} DCHAIN;

#endif // _DBCHECK_H
