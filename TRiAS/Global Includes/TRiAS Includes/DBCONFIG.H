/* Festlegen der Generierungsparameter fuer ZIPEDB              */
/* File: DBCONFIG.H             last update: 1. Maerz 1990      */

/* ZIPEDB: @(#)dbconfig.h       2.6  90/04/10"
 */

#ifndef _DBCONFIG_H
#define _DBCONFIG_H

#undef unix

/* Verschiedene statistische Groessen werden berechnet, wenn
   STATISTICS definiert ist. 
 */
#define STATISTICS

/* BACKUP ermoeglicht die Nutzung des 'lazy copy' - Konzeptes
 */
#define BACKUP

/* MULTI_DB erlaubt die gleichzeitige Arbeit mit mehreren (MAXDB)
   Datenbasen.
   Es ist unbedingt zu beachten, dass die Anzahl der Datenbasen
   uebereinstimmt mit der Anzahl der in dbopen.c initialisierten 
   Eintraege in der Datenbasistabelle uebereinstimmt.
 */
#define MULTI_DB
#define MAXDB   500

/* HOLD generiert zusaetzlichen Programmkode fuer das Binden bzw.
   loesen einer Speicherseite an eine konkrete Datei.
   HOLD niemals gemeinsam mit PAGEHASH verwenden!
   MINDYNPAGES legt die minimale Anzahl von Speicherseiten fest, 
   die nicht gebunden werden duerfen.
 */
/* #define HOLD
   #define MINDYNPAGES  2
 */

/* PAGEHASH schaltet eine Hashverwaltung der Speicherseiten ein.
   Besonders wirkungsvoll bei einer grossen Anzahl von Speicher-
   seiten (DEFPAGES - Anzahl der Speicherseiten).
   HASHSIZE legt die Groesse der internen Hashtabelle fest und
   sollte (in etwa) die naechstgroessere Primzahl nach 1.1 * DEFPAGES
   sein.
 */
#define PAGEHASH
#define DEFPAGES        1024
#define HASHSIZE        1129
// Hashfunktion (PageNummer, DateiNummer) - immer positiv !
#define HASH(p,f) ((short)( (((p-1)^((short)f*hashsize)) & 0x0FFF) % hashsize) )

#ifdef HOLD
/* niemals gleichzeitig mit HOLD verwenden ! */
#undef HOLD
#endif

/* PAGESIZE legt die Groesse der Speicherpages fest und sollte gleich
   der Groesse der vom System verwendeten Plattenbloecke sein.
 */
/* UNIX (VAX, P8000, 1420) */
#ifdef unix
#ifdef BSD_2_9
#define PAGESIZE        1024
#else
#define PAGESIZE        512
#endif
#endif
/* PC's unter MS/DOS */
#if defined(msdos) || defined(_WINDOWS) || defined(_CONSOLE)
#define PAGESIZE        1024
#endif
#define MAXPAGESIZE	2048	// prinzipiell max. mögliche PageGröße

#if !defined(PAGESIZE)
#define PAGESIZE	MAXPAGESIZE
#endif

#if PAGESIZE > MAXPAGESIZE
#error "Die eingestellte Pagegröße ist zu groß !"
#endif

/* FILENMLEN legt die maximale Laenge der vom jeweiligen System
   unterstuetzten Dateinamen (ohne Pfad) fest. 
 */
#define FILENMLEN       15

/* slash bzw. slashp stehen fuer die von jeweiligen System 
   verwendeten Pfadtrennzeichen.
 */
#ifdef unix
#define slash   '/'
#define slashp  "/"
#endif
#if defined(msdos) || defined(_WINDOWS) || defined(_CONSOLE)
#define slash   '\\'
#define slashp  "\\"
#endif
 

/* MAXFILES legt fest, wieviele Dateien gleichzeitig durch ZIPEDB
   offen gehalten werden duerfen. 
 */
#define MAXFILES        1

#if MAXFILES == 1
#define SINGLEFILE
#else
#undef SINGLEFILE
#endif

/* METADIR legt den Pfadnamen fest, wo die Meta-Datenbasis 
   (Fehlercodes etc.) gesucht werden soll.
   META ist der Name der Meta-Datenbasis.
   META_USER ist der Nutzername fuer normale Fehlermeldungsausgabe.
 */
#ifdef unix
#define META            "errdb"
#define META_USER       "normal"
#endif
#if defined(msdos) || defined(_WINDOWS) || defined(_CONSOLE)

#if defined(MSWIND) || defined(_WINDOWS) || defined(_CONSOLE)
#define META            "errdb.stb"
#else // MSWIND
#define META            "errdb"
#endif // MSWIND

#define META_USER       "normal"
#endif

#define ERRORDB_ENV     "ERRORDB"

/* MAXERRORS legt die Groesse der internen Fehlerlisten fest
 */
#define MAXERRORS       100

/* PROTOTYPES sollte definiert werden, wenn der verwendete Compiler
   ANSI-C unterstuetzt (Prototypen).
 */
#if (defined(msdos) || defined(_WINDOWS) || defined(_CONSOLE)) && !defined(PROTOTYPES)
#define PROTOTYPES
#endif

/* MSWIND muß definiert sein, wenn ZIPEDB fuer MS Windows (tm)
   generiert werden soll 
 */
#if defined(MSWIND) || defined(_WINDOWS) || defined(_CONSOLE)
// Besonderheiten von Datei I/O-Funktionen
#define lseek(h,offset,orig) _llseek((h),(offset),(orig))
#define _dos_read(h,buf,n,nr) _lread((h),(buf),(n))
#define _dos_write(h,buf,n,nr) _lwrite((h),(buf),(n))

// MultiUserZugriff erlauben
#define PROJECT_LOCKING
#endif


/* STB_EXTENSION ist die Standarderweiterung fuer die Steuerblockdatei
   PWD_EXTENSION ist die Standarderweiterung fuer die Passwortdatei
 */
#define STB_EXTENSION   ".STB"
#define PWD_EXTENSION   ".PWD"
#define RIS_EXTENSION	".RIS"
#define PBD_EXTENSION	".PBD"
#define LOK_EXTENSION	".LOK"

/* READ_OPENMODE legt den Mode fuer fopen/readonly fest,
   WRITE_OPENMODE legt den Mode fuer fopen/writeonly fest,
   RDWR_OPENMODE legt den Mode fuer fopen/rdwr fest
 */
#if defined(msdos) || defined(_WINDOWS) || defined(_CONSOLE)
#define READ_OPENMODE   "rb"
#define WRITE_OPENMODE  "wb"
#endif

#ifdef unix
#define READ_OPENMODE   "r"
#define WRITE_OPENMODE  "w"
#endif


/* BTREE legt fest, ob B-Baumfunktionen eingebunden werden
 */
#define BTREE_FUNCTIONS


/* HTREE legt fest, ob Hex-Treefunktionen eingebunden werden
 */
#define HTREE_FUNCTIONS


/* QTREE legt fest, ob Quad-Treefunktionen eingebunden werden
 */
#define QTREE_FUNCTIONS


/* Definieren des Funktionstypes
 */
#if (defined(MSWIND) || defined(_WINDOWS) || defined(_CONSOLE)) && defined(DLL) 
#if !defined(FUNCTYPE)
#define FUNCTYPE __pascal
#endif
#else
#if defined(WIN16)
#if !defined(FUNCTYPE)
#define FUNCTYPE __cdecl
#endif
#else // WIN16
#undef FUNC_TYPE
#define FUNC_TYPE
#endif 
#endif

/* Legt fest, ob Schlüssel mit Wert gleich NULL berücksichtigt werden
 */
// #define NULLCMP

#endif // _DBCONFIG_H
