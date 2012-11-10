/* Datentyp-Definitionen fuer DIO.C (Datenbank-I/O-Routinen)            */
/* File: DBTYPES.H              last update: 22. September 1989         */

/* ZIPEDB: @(#)dbtypes.h        2.6  90/04/11
 */

#ifndef _DBTYPES_H
#define _DBTYPES_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

/* Systemspezifische und generierungsabhaengige Groessen */
#include <dbconfig.h>
#include <risdb.h>

// ProjectHandle
#if defined(MSWIND) || defined(_WINDOWS)
#if !defined(_DEFINED_HPROJECT)
#define _DEFINED_HPROJECT
DECLARE_HANDLE(HPROJECT);
#define HACTPROJECT		((HPROJECT)(-1))		// bezieht sich auf Projekt
#define HACTCONNECTION	((HPROJECT)(NULL))		// bezieht sich auf aktuelle Datenquelle
#endif
#else
#define HPROJECT int
#endif

#if !defined(_TIME_T_DEFINED) && !defined(_TIME_T_DEFINED_)
typedef unsigned long time_t;
#define _TIME_T_DEFINED
#endif

/* maximale Anzahl der Records in einem File */
#define MAXRECORDS      2147483647L     /* 2^31 -1 */
#define MAXPAGES          16777216L     /* 2^24 -1 */
 
#define MAXPOSLONG      2147483647L     /* 2^31 -1 */ 
 
#define OPEN    'o'     /* File eroeffnet */
#define CLOSED	'c'	/* File abgeschlossen */
#if defined(MSWIND) || defined(_WINDOWS) || defined(_CONSOLE)
#define TO_INIT 'i'	// Dateistruktur nicht initialisiert
#endif
 
/* Zugriffsmodi zu DB-Dateien */
#define O_NOACC -1      /* kein Zugriff erlaubt */
#define O_ALL	0x80000000	/* Alle Dateien */

#define DATAFILE  'd'   /* File enthaelt Daten */
#define KEYFILE   'k'   /* File enthaelt Schluesselinfo's */
#define HTREEFILE 'h'   /* File enthaelt Geometriehexbaum */
#define QTREEFILE 'q'   /* File enthaelt Geometrie-QuadTree */
#define CTREEFILE 'c'   /* File enthaelt Geometrie-CubicTree */
#define TEMPORARY 't'   /* temporaeres File */
#define BACKUPFILE 'b'  /* Backupdatei */

#define FIRST_PAGE 1            /* Nummer der ersten Datenpage */
#define PAGEHDRSIZE 8           /* Datenoffset in jeder Page */

#define NONE -1
 
/* Definition verschiedener Datentypen */
#if !defined(WIN32)
typedef long INT;       /* Datentyp, der I*4 in F77 entspricht */
#else
typedef int INT;	// da windef.h das so vorschreibt
#endif

typedef short FLAG;     /* Boolean Variable */
typedef long REC_NO, PAGE_NO;
 
/* Struktur eines Eintrages in der Filetabelle */
typedef struct IStream *LPSTREAM;

typedef struct file_entry {
        char *ft_name;                  /* Filename */
        int ft_desc;                    /* Filedescriptor */
	short ft_status;		/* Filestatus: 'o', 'i' oder 'c' */
        short ft_type;                  /* Filetyp: 'd' oder 'k' */
        short ft_slots;                 /* Anzahl der Slots je Page */
        short ft_slsize;                /* Slotgroesse (in Bytes) */
        short ft_recfile;               /* Index in Recordfiletabelle */
        short ft_access;                /* Zugriffsmode */
        FLAG ft_used;                   /* File wurde benutzt */
#if defined(MSWIND) || defined(_WINDOWS) || defined(_CONSOLE)
	OFSTRUCT of;			// Dateibeschreibungsstruktur
#endif
#ifdef HOLD
        short ft_refer;                 /* >= 0: gebundene Pagenummer */
#endif
	short ft_oldaccess;		// alter Wert von ft_access
#if defined(MSWIND) || defined(_WINDOWS) || defined(_CONSOLE)
	LPSTREAM ft_pIStream;		// wird für CompoundFiles verwendet
#endif
} FILE_ENTRY;

/* Struktur der Filetabelle in `.stb' */
typedef struct ft_entry {
        char *ft_name;                  /* Filename */
        short ft_desc;                  /* Filedescriptor */
        short ft_status;                /* Filestatus: 'o' oder 'c' */
        short ft_type;                  /* Filetyp: 'd' oder 'k' */
        short ft_slots;                 /* Anzahl der Slots je Page */
        short ft_slsize;                /* Slotgroesse (in Bytes) */
        short ft_recfile;               /* Index in Recordfiletabelle */
} FT_ENTRY;

/* Feldtypen */
#define FT_CHARACTER       'c'
#define FT_CHAR_ARRAY      'C'
#define FT_SHORTINT        's'
#define FT_REGINT          'i'
#define FT_STRUCT          'g'
#define FT_UNION           'G'
#define FT_GROUPED         'r'
#define FT_LONGINT         'l'
#define FT_FLOAT           'f'
#define FT_DOUBLE          'F'
#define FT_DBADDR          'd'

/* Schluesseltypen */
#define KT_NOKEY   'n'
#define KT_KEY     'd'
#define KT_BTREE   'd'
#define KT_HTREE   'h'
#define KT_QTREE   'q'
#define KT_CTREE   'c'
#define KT_UNIQUE  'u'
#define KT_UNIQUE_ONLY     'U'
#define KT_KEY_ONLY        'D'
#define KT_DUPLICATES      'd'
/* Struktur eines Eintrages in der Key-Tabelle */
typedef struct key_entry {
        short kt_treefile;      /* Index des Tree-Files (falls vorhanden) */
        short kt_keyfile;       /* Index des Key-Files */
        short kt_offset;        /* Offset des Key-Feldes im Record */
        short kt_len;           /* Laenge des Keys (in Bytes) */
        short kt_type;          /* Schluesseltyp */
        short kt_field;         /* Schluesselfeldtyp */
        short kt_file;          /* Targetfile, zu dem Key gehoert (Index) */
        short kt_chain;         /* Verkettung der Key's einer Record */
} KEY_ENTRY;

/* Page 0 enthaelt fuer jedes File die zur Laufendhaltung notwendigen
   Informationen */
typedef struct pg_zero {
        INT pz_dchain;          /* Nummer des ersten geloeschten Satzes */
        INT pz_next;            /* Nummer des naechsten freien Satzes am Ende */
        time_t bdate;           /* Backup Date */
} PGZERO;

/* Interner Recordentry (entspricht verkuerztem RECORD_ENTRY) */
typedef struct rec_entry {
        short rt_file;          /* File-Tabelleneintrag dieser Record */
        short rt_keyfile;       /* Keytabelle (wenn Record Key enthaelt) */
        short rt_chain;         /* naechster Record dieser Datei */
	short rt_len;		/* Laenge der Record (ohne Key_Only-Felder) */
} REC_ENTRY;

#ifdef MULTI_DB
typedef struct IStorage *LPSTORAGE;	// Deklaration

/* Struktur, die eine DB beschreibt */
typedef struct tagDBASE {
	char *db_name;          /* DB-Name */
	FILE_ENTRY *db_ftab;    /* Dateitabelle */
	short db_sft;           /* Groesse der Dateitabelle */
	KEY_ENTRY *db_ktab;     /* Schluesseltabelle */
	short db_skt;           /* Anzahl der Schluessel */
	REC_ENTRY *db_rtab;     /* Recordtabelle */
	short db_srt;           /* Anzahl der Records */
	PGZERO *db_pztab;       /* Page 0 Tabelle */
	short last_file;        /* zuletzt angefasste Datei */
	short db_work;          /* working_file */
	short db_field;		/* KeyFieldNumber */
	PAGE_NO *db_parent;     /* Position im BTree */
	short *db_slots;
	short db_lvl;           /* Level im BTree */
	long db_version;	/* VersionsNummer */
	unsigned short db_pagesize;	/* PageGröße dieser DB */
#if defined(PROJECT_LOCKING)	
	HFILE db_fhShared;	/* DateiHandle eines evtl. LockingFiles */
#endif // PROJECT_LOCKING
#ifdef BACKUP
        short db_bflag;         /* Backupdateinummer */
#endif // BACKUP
#if defined(MSWIND) || defined(_WINDOWS)
	LPSTORAGE db_pIStorage;		// für CompoundFile's
	BOOL db_fOpenedRO;			// nur RO Zugriff
	BOOL db_fOpenedAsCopy;		// als Kopie eröffnet
	BOOL db_fDirty;				// wurde modifiziert
	HPROJECT db_hProjectRelated;	// zugehörige Pbd
#endif
} DBASE;
#endif // MULTI_DB

/* Struktur zur Verwaltung der kleinsten vom/zum externen
   Speichermedium bewegten Dateneinheit */
typedef struct pg_entry {
#ifdef MULTI_DB
        DBASE *dbase;           /* Datenbasis */
#endif
        INT pageno;             /* Pagenummer im File */
        short file;             /* Index in Filetabelle */
        FLAG recently_used;     /* TRUE wenn Page angefasst wurde */
        FLAG modified;          /* TRUE wenn Page modifiziert wurde */
#ifdef PAGEHASH
        short hash;             /* zugehoeriger Hash_Tableeintrag */
#endif
	unsigned short pg_pagesize;	/* PageGröße dieser Page */
	unsigned char buff[1];
} PAGE_ENTRY;

#define COPYRIGHT_LEN 80

/* Datenbankadresse */
#if !defined(_DB_ADDR_DEFINED)
#if defined(__cplusplus)	

struct db_addr 
{
public:
	short file_no;		/* Filenummer */
	HPROJECT db_no;		/* HPROJECT */
	REC_NO rec_no;		/* Satznummer */
	
#if defined(ENABLE_DEFAULT_PROJECT)
		db_addr (void) : db_no(0) {}
#endif // ENABLE_DEFAULT_PROJECT
		db_addr (HPROJECT hPr) 
			: db_no (hPr) 
		{
		}
		db_addr (HPROJECT hPr, short iFileNo) 
			: db_no (hPr), file_no(iFileNo) 
		{
		}
		db_addr (HPROJECT hPr, short iFileNo, REC_NO lRecNo) 
			: db_no (hPr), file_no(iFileNo), rec_no(lRecNo) 
		{
		}
};
typedef db_addr DB_ADDR;

///////////////////////////////////////////////////////////////////////////////
// spezifische DatenBasisAdresse für OBL-Sätze
class db_addr_obl :
	public db_addr
{
public:
#if defined(ENABLE_DEFAULT_PROJECT)
		db_addr_obl (void) : file_no(OBL_OLD) {}
#endif // ENABLE_DEFAULT_PROJECT
		db_addr_obl (HPROJECT hPr) 
			: db_addr(hPr, (VERSION0500000E <= GetDBVersion(hPr) ? OBL_NEW : OBL_OLD))
		{
		}
		db_addr_obl (HPROJECT hPr, REC_NO lRecNo) 
			: db_addr(hPr, (VERSION0500000E <= GetDBVersion(hPr) ? OBL_NEW : OBL_OLD), lRecNo)
		{
		}
};
typedef db_addr_obl DB_ADDR_OBL;

#else // __cplusplus
typedef struct db_addr {
	short file_no;          /* Filenummer */
	HPROJECT db_no;		/* HPROJECT */
	REC_NO rec_no;          /* Satznummer */
} DB_ADDR;
#endif // __cplusplus
#define _DB_ADDR_DEFINED
#endif

// HashListenElement
typedef struct hash_list {
	PAGE_ENTRY *pPage;
	struct hash_list *pHList;
} HASH_LIST;

#define dbopen          db_open_flag
#define db_open         z_open
#define db_close        z_close
#define db_hold         z_hold
#define db_release      z_release

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _DBTYPES_H
