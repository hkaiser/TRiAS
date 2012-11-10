/* externe Datendefinitionen fuer Key-Funktionen                */
/* File: KEYEXTER.H             last update: 17. Oktober 1989   */

/* ZIPEDB: @(#)keyexter.h       2.5  90/04/11"
 */

#ifndef _KEYEXTERN_H
#define _KEYEXTERN_H
 
#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

#define MAXLEVEL 20
#define ROOT_ADDR (INT)1
 
/* Struktur eines Key-Page */
typedef struct node {
        time_t  nd_chng;     /* Datum der letzten Aenderung */
        short   nd_filled;   /* Anzahl der belegten Slots in der Page */
        short   dummy;
        char    nd_slots[1]; /* erstes Datenbyte der Page */
} NODE;
 
/* Struktur eines Key-Eintrages im B*Tree */
typedef struct key_slot{
        long ks_child;          /* NONE oder Childpointer */
        long ks_rec_no;         /* Verweis auf Datenfile */
        long ks_key[64];        /* Schluessel */
} KEY_SLOT;
 
/* Struktur eines Key-Eintrages im HTree */
typedef struct ht_key_slot {
        long ks_rec_no;         /* Verweis auf Datenfile */
        long ks_key[4];         /* Schluessel */
} HT_KEY_SLOT;
 
/* Struktur eines Key-Eintrages im QTree */
typedef struct qt_key_slot {
        long ks_rec_no;         /* Verweis auf Datenfile */
        long ks_key[2];         /* Schluessel (Punktkoordinaten) */
} QT_KEY_SLOT;
 
/* Struktur eines Eintrages im CubicTree */
typedef struct ct_key_slot {
        long ks_rec_no;         /* Verweis auf Datenfile */
        long ks_key[6];         /* Schluessel (3d-Container) */
} CT_KEY_SLOT;
 
/* Struktur eines internen Pageverweises */
typedef struct page_slot {
        long page_no;           /* Verweis auf Page im Keyfile */
        long ps_key;            /* interner Schluessel */
} PAGE_SLOT;
 
typedef struct tagSUGGESTPAGE {
	short m_iFileNo;	// geforderte DateiNummer
	long m_lPageNo;		// geforderte PageNummer
	DBASE *m_pDB;		// zugehörige Datenbank
	PAGE_ENTRY *m_pPE;	// Verweis auf bisherige Page
} SUGGESTPAGE;

extern short d;                 /* Anzahl der slots je Page */
extern short key_len;           /* Key-Laenge (in INT's) */
extern short slot_len;          /* Kopie aus File-Tabelle */
extern FLAG  unique;            /* TRUE, wenn aktueller Key einmalig sein soll */
extern short keyfile;           /* aktuelles Key-working-File */
extern KEY_ENTRY *key_table;    /* key_tabelle */
extern short size_kt;           /* Groesse der Key-Tabelle */
extern short find_field;        /* aktuelle Schluesselnummer */
extern short key_type;          /* aktueller Schluesselfeldtyp */
 
/* Arbeitspuffer */
extern INT buf[(2*MAXPAGESIZE+MAXPAGESIZE/2)/sizeof(INT)];
 
/* aktueller durchschrittener Pfad im Suchbaum */
extern PAGE_NO *parent;		/* Seitennummer */
extern short *slots;		/* Slotnummer */

extern short lvl;               /* aktueller Level im Suchbaum */
 
/* aktueller Key-Eintrag */
extern KEY_SLOT NEAR key;
extern CT_KEY_SLOT NEAR GeoKey;
 
#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _KEYEXTERN_H
