/* externe Datendefinitionen fuer Key-Funktionen                */
/* File: KEYEXTER.H             last update: 17. Oktober 1989   */

/* ZIPEDB: @(#)keyexter.h       2.5  90/04/11"
*/

#ifndef _KEYEXTERN_H
#define _KEYEXTERN_H

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
	long ks_key[64];        /* Schlüssel */
} KEY_SLOT;

/* Struktur eines Geometrie-Key-Eintrages */
template<class T, int iCnt>
struct key_slot_tmpl
{
	long ks_rec_no;			/* Verweis auf Datenfile */
	T ks_key[iCnt];			/* Schlüssel */
};

/* Struktur eines Key-Eintrages im HTree */
typedef struct key_slot_tmpl<long, 4> ht_key_slot;
typedef struct key_slot_tmpl<long, 4> HT_KEY_SLOT;
typedef struct key_slot_tmpl<double, 4> HT_KEY_SLOT2;

/* Struktur eines Key-Eintrages im QTree */
typedef struct key_slot_tmpl<long, 2> qt_key_slot;
typedef struct key_slot_tmpl<long, 2> QT_KEY_SLOT;
typedef struct key_slot_tmpl<double, 2> QT_KEY_SLOT2;

/* Struktur eines Eintrages im CubicTree */
typedef struct key_slot_tmpl<long, 6> ct_key_slot;
typedef struct key_slot_tmpl<long, 6> CT_KEY_SLOT;
typedef struct key_slot_tmpl<double, 6> CT_KEY_SLOT2;

/* Struktur eines internen Pageverweises */
typedef struct page_slot {
	long page_no;           /* Verweis auf Page im Keyfile */
	long ps_key;            /* interner Schluessel */
} PAGE_SLOT;

typedef struct tagSUGGESTPAGE {
	short m_iFileNo;		// geforderte DateiNummer
	long m_lPageNo;			// geforderte PageNummer
	DBASE *m_pDB;			// zugehörige Datenbank
	PAGE_ENTRY *m_pPE;		// Verweis auf bisherige Page
} SUGGESTPAGE;

#if defined(__cplusplus)
extern "C" {
#endif

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
extern KEY_SLOT key;
extern CT_KEY_SLOT2 GeoKey;

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _KEYEXTERN_H
