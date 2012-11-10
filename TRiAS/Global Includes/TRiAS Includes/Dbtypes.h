/* Datentyp-Definitionen fuer DIO.C (Datenbank-I/O-Routinen)			*/
/* File: DBTYPES.H				last update: 22. September 1989 		*/

/* ZIPEDB: @(#)dbtypes.h		2.6  90/04/11
 */

#ifndef _DBTYPES_H
#define _DBTYPES_H

#include <risdb.h>

#if defined(__cplusplus)
extern "C" {
#endif 

#include <pshpack1.h>

/* Systemspezifische und generierungsabhaengige Groessen */
#include <dbconfig.h>
#include <Versions.h>
#include <DeclareHandles.h>

#if !defined(_TIME_T_DEFINED) && !defined(_TIME_T_DEFINED_)
typedef unsigned long time_t;
#define _TIME_T_DEFINED
#endif

/* maximale Anzahl der Records in einem File */
#define MAXRECORDS		2147483647L 	/* 2^31 -1 */
#define MAXPAGES		  16777216L 	/* 2^24 -1 */
 
#define MAXPOSLONG		2147483647L 	/* 2^31 -1 */ 
 
#define OPEN	'o' 	/* File eroeffnet */
#define CLOSED	'c' /* File abgeschlossen */
#if defined(MSWIND) || defined(_WINDOWS) || defined(_CONSOLE)
#define TO_INIT 'i' // Dateistruktur nicht initialisiert
#endif
 
/* Zugriffsmodi zu DB-Dateien */
#define O_NOACC -1		/* kein Zugriff erlaubt */
#define O_ALL	0x80000000	/* Alle Dateien */

#define DATAFILE  'd'	/* File enthaelt Daten */
#define KEYFILE   'k'	/* File enthaelt Schluesselinfo's */
#define HTREEFILE 'h'	/* File enthaelt Geometriehexbaum */
#define QTREEFILE 'q'	/* File enthaelt Geometrie-QuadTree */
#define CTREEFILE 'c'	/* File enthaelt Geometrie-CubicTree */
#define TEMPORARY 't'	/* temporaeres File */
#define BACKUPFILE 'b'	/* Backupdatei */

#define FIRST_PAGE 1			/* Nummer der ersten Datenpage */
#define PAGEHDRSIZE 8			/* Datenoffset in jeder Page */

#define NONE -1
 
/* Definition verschiedener Datentypen */
#if defined(WIN16)
typedef long INT;		/* Datentyp, der I*4 in F77 entspricht */
#else
#if _MSC_VER < 1300
typedef int INT;		// da windef.h das so vorschreibt
#else
typedef INT32 INT;
#endif // _MSC_VER < 1300
#endif

typedef short FLAG; 	/* Boolean Variable */
typedef long REC_NO, PAGE_NO;
 
/* Struktur eines Eintrages in der Filetabelle */
typedef struct IStream *LPSTREAM;

typedef struct file_entry {
	char *ft_name;				/* Filename */
	int ft_desc;				/* Filedescriptor */
	short ft_status;			/* Filestatus: 'o', 'i' oder 'c' */
	short ft_type;				/* Filetyp: 'd' oder 'k' */
	short ft_slots; 			/* Anzahl der Slots je Page */
	short ft_slsize;			/* Slotgroesse (in Bytes) */
	short ft_recfile;			/* Index in Recordfiletabelle */
	short ft_access;			/* Zugriffsmode */
	FLAG ft_used;				/* File wurde benutzt */
#if defined(MSWIND) || defined(_WINDOWS) || defined(_CONSOLE)
	OFSTRUCT of;				// Dateibeschreibungsstruktur
#endif
#ifdef HOLD
	short ft_refer; 			/* >= 0: gebundene Pagenummer */
#endif
	short ft_oldaccess; 		// alter Wert von ft_access
#if defined(MSWIND) || defined(_WINDOWS) || defined(_CONSOLE)
	LPSTREAM ft_pIStream;		// wird für CompoundFiles verwendet
#endif
} FILE_ENTRY;

/* Struktur der Filetabelle in `.stb' */
typedef struct ft_entry {
	char *ft_name;				/* Filename */
	short ft_desc;				/* Filedescriptor */
	short ft_status;			/* Filestatus: 'o' oder 'c' */
	short ft_type;				/* Filetyp: 'd' oder 'k' */
	short ft_slots; 			/* Anzahl der Slots je Page */
	short ft_slsize;			/* Slotgroesse (in Bytes) */
	short ft_recfile;			/* Index in Recordfiletabelle */
} FT_ENTRY;

/* Feldtypen */
#define FT_CHARACTER	   'c'
#define FT_CHAR_ARRAY	   'C'
#define FT_SHORTINT 	   's'
#define FT_REGINT		   'i'
#define FT_STRUCT		   'g'
#define FT_UNION		   'G'
#define FT_GROUPED		   'r'
#define FT_LONGINT		   'l'
#define FT_FLOAT		   'f'
#define FT_DOUBLE		   'F'
#define FT_DBADDR		   'd'

/* Schluesseltypen */
#define KT_NOKEY   'n'
#define KT_KEY	   'd'
#define KT_BTREE   'd'
#define KT_HTREE   'h'
#define KT_QTREE   'q'
#define KT_CTREE   'c'
#define KT_UNIQUE  'u'
#define KT_UNIQUE_ONLY	   'U'
#define KT_KEY_ONLY 	   'D'
#define KT_DUPLICATES	   'd'
/* Struktur eines Eintrages in der Key-Tabelle */
typedef struct key_entry {
	short kt_treefile;		/* Index des Tree-Files (falls vorhanden) */
	short kt_keyfile;		/* Index des Key-Files */
	short kt_offset;		/* Offset des Key-Feldes im Record */
	short kt_len;			/* Laenge des Keys (in Bytes) */
	short kt_type;			/* Schluesseltyp */
	short kt_field; 		/* Schluesselfeldtyp */
	short kt_file;			/* Targetfile, zu dem Key gehoert (Index) */
	short kt_chain; 		/* Verkettung der Key's einer Record */
} KEY_ENTRY;

/* Page 0 enthaelt fuer jedes File die zur Laufendhaltung notwendigen
   Informationen */
typedef struct pg_zero {
	INT pz_dchain;			/* Nummer des ersten geloeschten Satzes */
	INT pz_next;			/* Nummer des naechsten freien Satzes am Ende */
	time_t bdate;			/* Backup Date */
} PGZERO;

/* Interner Recordentry (entspricht verkuerztem RECORD_ENTRY) */
typedef struct rec_entry {
	short rt_file;			/* File-Tabelleneintrag dieser Record */
	short rt_keyfile;		/* Keytabelle (wenn Record Key enthaelt) */
	short rt_chain; 		/* naechster Record dieser Datei */
	short rt_len;			/* Länge des Records (ohne Key_Only-Felder) */
} REC_ENTRY;

#ifdef MULTI_DB
typedef struct IStorage *LPSTORAGE; // Deklaration

// Struktur enthält SkalierungsKoeffinzienten einer GeoDB
typedef struct tagSCALEKOEFFS {
	double m_dK11, m_dK12, m_dK21, m_dK22;				// Vorwärtstransformation
	double m_dInvK11, m_dInvK12, m_dInvK21, m_dInvK22;	// Rückwärtstransformation
	double m_dOffsetX, m_dOffsetY;						// Offsets
} SCALEKOEFFS;

typedef enum tagPREDEFINEDMCODE {
	PREDEFINEDMCODE_ObjGuid = 0,
	PREDEFINEDMCODE_LastDefined = 0,
} PREDEFINEDMCODE;

typedef struct tagCONNECTFILTER {
	int m_iMode;								// Typ des Verbindungsfilters (CF_...)
	double *m_pX;
	double *m_pY;
	long m_lCnt;
} CONNECTFILTER;

class CObjectGiST;								// forward declaration

typedef struct tagCONNECTFILTEREX :	public CONNECTFILTER {
	double m_dXMin, m_dXMax, m_dYMin, m_dYMax;	// Container
	CObjectGiST *m_prsTree;
} CONNECTFILTEREX;

/* Struktur, die eine DB beschreibt */
typedef struct tagDBASE {
	char *db_name;			/* DB-Name */
	FILE_ENTRY *db_ftab;	/* Dateitabelle */
	short db_sft;			/* Groesse der Dateitabelle */
	KEY_ENTRY *db_ktab; 	/* Schluesseltabelle */
	short db_skt;			/* Anzahl der Schluessel */
	REC_ENTRY *db_rtab; 	/* Recordtabelle */
	short db_srt;			/* Anzahl der Records */
	PGZERO *db_pztab;		/* Page 0 Tabelle */
	short last_file;		/* zuletzt angefasste Datei */
	short db_work;			/* working_file */
	short db_field; 	/* KeyFieldNumber */
	PAGE_NO *db_parent; 	/* Position im BTree */
	short *db_slots;
	short db_lvl;			/* Level im BTree */
	long db_version;	/* VersionsNummer */
	unsigned short db_pagesize; /* PageGröße dieser DB */
#if defined(PROJECT_LOCKING)	
	HFILE db_fhShared;	/* DateiHandle eines evtl. LockingFiles */
#endif // PROJECT_LOCKING
#ifdef BACKUP
	short db_bflag; 		/* Backupdateinummer */
#endif // BACKUP
#if defined(MSWIND) || defined(_WINDOWS)
	LPSTORAGE db_pIStorage; 	// für CompoundFile's
	BOOL db_fOpenedRO;			// nur RO Zugriff
	BOOL db_fOpenedAsCopy;		// als Kopie eröffnet
	BOOL db_fDirty; 			// wurde modifiziert
	HPROJECT db_hProjectRelated;	// zugehörige Pbd
	GUID db_CSSGuid;			// GUID des Koordinatensystems
	IUnknown *db_pIIdentMap;	// Map mit allen Identifikatoren
	BOOL db_fNoCaseIdents;		// IdentKurztexte ohne Groß-/Kleinschreibung eindeutig machen (#HK010615)
	IUnknown *db_pIMCodeMap;	// Map mit allen MCodes
	BOOL db_fNoCaseAttribs;		// AttributKurztexte ohne Groß-/Kleinschreibung eindeutig machen (#HK010615)
	BOOL db_fKoeffsValid;
	SCALEKOEFFS db_Koeffs;		// Skalierungskoeffizienten
	LONG db_lMCode[PREDEFINEDMCODE_LastDefined+1];	// diverse DB-weite MCodes
#if defined(_USE_COMPRESSED_STREAM)
	int db_fCompressed; 		// Streams sind komprimiert
#endif // defined(_USE_COMPRESSED_STREAM)
#if defined(_USE_CONNECTFILTER)
	BOOL m_dbfConnectFilterValid;
	CONNECTFILTEREX db_ConnectFilter;
#endif // defined(_USE_CONNECTFILTER)
#if defined(_USE_OPENREFCNT)
	DWORD db_RefCnt;			// RefCnt (Anzahl der z_open)
	DWORD db_Mode;				// Mode, in dem Datei geöffnet wurde
#endif // defined(_USE_OPENREFCNT)
#endif
} DBASE;
#endif // MULTI_DB

/* Struktur zur Verwaltung der kleinsten vom/zum externen
   Speichermedium bewegten Dateneinheit */
typedef struct pg_entry {
#ifdef MULTI_DB
	DBASE *dbase;			/* Datenbasis */
#endif
	INT pageno; 			/* Pagenummer im File */
	short file; 			/* Index in Filetabelle */
	FLAG recently_used; 	/* TRUE wenn Page angefasst wurde */
	FLAG modified;			/* TRUE wenn Page modifiziert wurde */
#ifdef PAGEHASH
	short hash; 			/* zugehoeriger Hash_Tableeintrag */
#endif
	unsigned short pg_pagesize; /* PageGröße dieser Page */
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
	HPROJECT db_no; 	/* HPROJECT */
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
#if defined(__TRIAS01DLL__)
			: db_addr(hPr, (VERSION0500000E <= LocGetDBVersion(hPr) ? OBL_NEW : OBL_OLD))
#else
			: db_addr(hPr, (VERSION0500000E <= GetDBVersion(hPr) ? OBL_NEW : OBL_OLD))
#endif // defined(__TRIAS01DLL__)
		{
		}
		db_addr_obl (HPROJECT hPr, REC_NO lRecNo) 
#if defined(__TRIAS01DLL__)
			: db_addr(hPr, (VERSION0500000E <= LocGetDBVersion(hPr) ? OBL_NEW : OBL_OLD), lRecNo)
#else
			: db_addr(hPr, (VERSION0500000E <= GetDBVersion(hPr) ? OBL_NEW : OBL_OLD), lRecNo)
#endif // defined(__TRIAS01DLL__)
		{
		}
};
typedef db_addr_obl DB_ADDR_OBL;

///////////////////////////////////////////////////////////////////////////////
// spezifische DatenBasisAdresse für IDL-Sätze
class db_addr_idl :
	public db_addr
{
public:
#if defined(ENABLE_DEFAULT_PROJECT)
		db_addr_idl (void) : file_no(IDL_OLD) {}
#endif // ENABLE_DEFAULT_PROJECT
		db_addr_idl (HPROJECT hPr) 
#if defined(__TRIAS01DLL__)
			: db_addr(hPr, (VERSION05000013 <= LocGetDBVersion(hPr) ? IDL_NEW : IDL_OLD))
#else
			: db_addr(hPr, (VERSION05000013 <= GetDBVersion(hPr) ? IDL_NEW : IDL_OLD))
#endif // defined(__TRIAS01DLL__)
		{
		}
		db_addr_idl (HPROJECT hPr, REC_NO lRecNo) 
#if defined(__TRIAS01DLL__)
			: db_addr(hPr, (VERSION05000013 <= LocGetDBVersion(hPr) ? IDL_NEW : IDL_OLD), lRecNo)
#else
			: db_addr(hPr, (VERSION05000013 <= GetDBVersion(hPr) ? IDL_NEW : IDL_OLD), lRecNo)
#endif // defined(__TRIAS01DLL__)
		{
		}
};
typedef db_addr_idl DB_ADDR_IDL;

#else // __cplusplus
typedef struct db_addr {
	short file_no;			/* Filenummer */
	HPROJECT db_no; 	/* HPROJECT */
	REC_NO rec_no;			/* Satznummer */
} DB_ADDR;
#endif // __cplusplus
#define _DB_ADDR_DEFINED
#endif

// HashListenElement
typedef struct hash_list {
	PAGE_ENTRY *pPage;
	struct hash_list *pHList;
} HASH_LIST;

#define dbopen			db_open_flag
#define db_open 		z_open
#define db_close		z_close
#define db_hold 		z_hold
#define db_release		z_release

#include <poppack.h>

#if defined(__cplusplus)
}	// extern "C"
#endif 

#endif // _DBTYPES_H
