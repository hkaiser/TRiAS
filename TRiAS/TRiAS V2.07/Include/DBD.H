// Datenstrukturen des DBDictionaries -----------------------------------------
// File: DBD.H

#if !defined(_DBD_H)
#define _DBD_H

#include <time.h>

#include <pshpack1.h>

#include <dbconfig.h>

// Datendefinitionen ----------------------------------------------------------
#define COPYRIGHTLEN	80
#define NAMELEN		32
#define FILENMLEN	15

#if defined(WIN32)
typedef int	INT;
#else
typedef long 	INT;
#endif

// Struktur, die den Header der DBD-Datei enth�lt -----------------------------
typedef struct tagDBDHEADER {
	char Copyright[COPYRIGHTLEN];		// Copyright-Text
	short iFiles;		// Anzahl der Dateien der DB
	short iKeys;		// Anzahl der Schl�ssel in der DB
	short iRecords;		// Anzahl der verschiedenen Records
	short iFields;		// Anzahl der Felder der DB
	short iBackupFlag;	// Nummer des BackupFiles
} DBDHEADER;

// Dateitypen ------------------------------------------------------------------
#define DATAFILE	'd'	// File enth�lt Daten 
#define KEYFILE		'k'	// File enth�lt Schluesselinfo's 
#define HTREEFILE	'h'	// File enth�lt Geometriehexbaum 
#define QTREEFILE	'q'	// File enth�lt Geometrie-QuadTree 
#define CTREEFILE	'c'	// File enth�lt Geometrie-CubicTree 
#define TREEKEYFILE	'K'	// File enth�lt HilfsBaum
#define TEMPORARY	't'	// tempor�res File
#define BACKUPFILE	'b'	// Backupdatei 

// Struktur der Filetabelle ---------------------------------------------------
typedef struct tagFILEENTRY {
        char *fepName;		// Dateiname 
        short feiDesc;		// Filedescriptor 
        short feiStatus;	// Filestatus: 'o' oder 'c'
        short feiType;		// Filetyp: 'd' oder 'k' 
        short feiSlots;		// Anzahl der Slots je Page 
        short feiSlsize;	// Slotgr��e (in Bytes) 
        short feiRecfile;	// Index in Recordfiletabelle 
} FILEENTRY;

// Feldtypen ------------------------------------------------------------------
#define CHARACTER	'c'
#define CHAR_ARRAY	'C'
#define SHORTINT	's'
#define REGINT		'i'
#define STRUCT		'g'
#define UNION		'G'
#define GROUPED		'r'
#define LONGINT		'l'
#define FLOAT		'f'
#define DOUBLE		'F'
#define DBADDR		'd'

// Schl�sseltypen -------------------------------------------------------------
#define NOKEY		'n'
#define KEY		'd'
#define BTREE		'd'
#define HTREE		'h'
#define QTREE		'q'
#define CTREE		'c'
#define UNIQUE		'u'
#define UNIQUE_ONLY	'U'
#define KEY_ONLY	'D'
#define DUPLICATES	'd'

// Struktur eines Eintrages in der Key-Tabelle --------------------------------
typedef struct tagKEYENTRY {
        short keiTreefile;	// Index des Tree-Files (falls vorhanden) 
        short keiKeyfile;	// Index des Key-Files 
        short keiOffset;	// Offset des Key-Feldes im Record 
        short keiLen;		// Laenge des Keys (in Bytes) 
        short keiType;		// Schl�sseltyp 
        short keiField;		// Schl�sselfeldtyp 
        short keiFile;		// Targetfile, zu dem Key gehoert (Index) 
        short keiChain;		// Verkettung der Key's einer Record 
	char kepName[NAMELEN];	// KeyFeldName
} KEYENTRY;

// KeyEntry im DBD-File -------------------------------------------------------
typedef struct tagDBDKEYENTRY {
        short keiTreefile;	// Index des Tree-Files (falls vorhanden) 
        short keiKeyfile;	// Index des Key-Files 
        short keiOffset;	// Offset des Key-Feldes im Record 
        short keiLen;		// Laenge des Keys (in Bytes) 
        short keiType;		// Schl�sseltyp 
        short keiField;		// Schl�sselfeldtyp 
        short keiFile;		// Targetfile, zu dem Key gehoert (Index) 
        short keiChain;		// Verkettung der Key's einer Record 
} DBDKEYENTRY;

// Struktur eines Eintrages in der Record-Tabelle -----------------------------
typedef struct tagRECORDENTRY {
        short reiFile;		// File-Tabelleneintrag dieser Record 
        short reiKeyfile;	// Keytabelle (wenn Record Key enth�lt) 
        short reiChain;		// n�chster Record dieser Datei 
        short reiLen;		// Recordl�nge (ohne key_only Felder)
        short reiOnlykey;	// L�nge der Key_only Felder 
        short reiField;		// erster Eintrag in Feld-Tabelle 
        short reiFdtot;		// Anzahl der Felder in der Record 
	char repName[NAMELEN];	// RecordName
} RECORDENTRY;

// Struktur eines Eintrages in der Record-Tabelle im DBD-File ----------------
typedef struct tagDBDRECORDENTRY {
        short reiFile;		// File-Tabelleneintrag dieser Record 
        short reiKeyfile;	// Keytabelle (wenn Record Key enth�lt) 
        short reiChain;		// n�chster Record dieser Datei 
        short reiLen;		// Recordl�nge (ohne key_only Felder)
        short reiOnlykey;	// L�nge der Key_only Felder 
        short reiField;		// erster Eintrag in Feld-Tabelle 
        short reiFdtot;		// Anzahl der Felder in der Record 
} DBDRECORDENTRY;

// Struktur eines Eintrages in der Record-Tabelle im STB-File ----------------
typedef struct tagRISRECORDENTRY {
        short reiFile;		// File-Tabelleneintrag dieser Record 
        short reiKeyfile;	// Keytabelle (wenn Record Key enth�lt) 
        short reiChain;		// n�chster Record dieser Datei 
        short reiLen;		// Recordl�nge (ohne key_only Felder)
} RISRECORDENTRY;

/* Struktur eines Eintrages in der Field-Tabelle */
typedef struct tagFIELDENTRY {
        short feiType;  	// FeldTyp
        short feiLen;		// Feldl�nge 
        short feiOffset;	// Offset des Feldes im Record 
        short feiRecord;	// Record-Tabelleneintrag dieses Feldes 
        short feiKeytype;	// Keytyp 
        short feiKeyfile;	// Index in File-Tabelle des keyfiles 
        short feiTreefile;	// Index in File-Tabelle des Tree-Files 
        short feiFile;		// Index in Filetabelle des Records 
        short feiKey;		// Index in Key-Tabelle 
	char fepName[NAMELEN];	// FeldName
} FIELDENTRY;


/* Struktur eines Eintrages in der PGZeroTabelle */
typedef struct tagPGZEROENTRY {
	long pzlDelChain;	// R�ckverkettung der gel�schten S�tze
	long pzlNext;		// n�chster freier Satz
	long pzlBTime;		// BackupTime
} PGZEROENTRY;


// Struktur eine Page ---------------------------------------------------------
typedef union tagPAGE {
	INT lPage [PAGESIZE/sizeof(INT)];
	struct {	// allgemeine Page 1
		char Copyright[80];	/* Copyright */
		INT lDelChain;		/* Freikettenzeiger */
		INT lNext;		/* naechste freie Record im File */
		time_t BackupDate;	/* Datum/Zeit des letzten Backup */
		time_t CreationDate;	/* Datum/Zeit der Filegenerierung */
	} Page1;
	struct {	// Page 2 f�r KeyDateien
		time_t ChangeDate;      /* Datum der letzten �nderung dieser Page */
		INT dummy;
		INT iBytes[3];
	} Page2;
} PAGE;

#include <poppack.h>

#endif // _DBD_H
