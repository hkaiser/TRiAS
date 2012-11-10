/* Datenbank -- I/O, Datendefinitionen                          */
/* File: DIOEXTER.H             last update: 28. Februar 1990   */

/* ZIPEDB: @(#)dioexter.h       2.5  90/04/10"
 */

#ifndef _DIOEXTERN_H
#define _DIOEXTERN_H
 
#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

/* globale Variablendeklarationen */
extern short max_open_files;    /* maximale Anzahl eroffneter Files */
extern short cnt_open_files;    /* aktuelle Anzahl eroeffneter Files */
#ifdef MULTI_DB
extern short last_db;           /* zuletzt angesprochene DB (in fdbopen) */
#endif
 
extern short no_of_pages;       /* Anzahl der Pages in der Pagetabelle */
extern short dynamic;           /* Anzahl der dynamisch verwalteten Pages */
extern short least_recent;      /* Zaehler fuer dyn. Pageswopping */
extern short working_file;      /* fuer Operationen mit default_file */
#ifdef PAGEHASH
extern short hashsize;          /* Groesse der Hashtabelle */
#endif
 
extern PAGE_ENTRY *pages;       /* Pageverzeichnisse */
extern PGZERO *pgzero;		/* Nullpagetabelle */
extern PAGE_ENTRY **page_table; /* Pagetabelle */

extern FILE_ENTRY *file_table;  /* Fileverzeichnis */
extern short size_ft;           /* Anzahl der Files in file_table */

extern REC_ENTRY *record_table; /* Recordverzeichnis */
extern short size_rt;           /* Anzahl der Records in record_table */

/* database status code */
extern int db_status;

#ifndef MULTI_DB
extern FLAG dbopen;             /* DB offen */
#else
_TRIAS01_ENTRY extern DBASE *act_db;           /* aktuelle bearbeitete DB */
_TRIAS01_ENTRY extern DBASE *pActivatedDB;		/* aktuell aktivierte DB */
_TRIAS01_ENTRY extern DBASE db_table[MAXDB];   /* DB-Tabelle */
extern long DBVersion;		/* VersionsNummer */

inline HPROJECT GetHandleFromPtr (DBASE *pDB)
{
	return (NULL != pDB) ? HPROJECT((pDB-db_table)+1) : NULL;
}

#endif

#ifdef BACKUP
/* Variablen fuer faules Kopieren */
extern short backup_flag;
extern PAGE_ENTRY *backup_page;
#endif // BACKUP

#ifdef PAGEHASH
/* Hashtabelle */
extern HASH_LIST **hash_table;
#endif // PAGEHASH

extern unsigned short PageSize;		/* PageGröße */

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _DIOEXTERN_H
