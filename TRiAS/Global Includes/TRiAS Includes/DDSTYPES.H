/* Datentyp-Definitionen fuer DDSP                                      */
/* File: DDSTYPES.H                                                     */

#ifndef _DDSTYPES_H
#define _DDSTYPES_H

#include <pshpack1.h>

/* allgemeine Datentypdefinitionen */
#include "dbtypes.h"

#define NAMELEN 32      /* Laenge der DDS-Identifikatoren */

#define TREEKEYFILE 'K' /* Keyfile fuer HTree */

/* Dimension des Geometriezugriffs */
#define HDIM 16
#define QDIM 4
#define CDIM 64

/* Struktur eines Eintrages in der Record-Tabelle */
typedef struct {
        short rt_file;          /* File-Tabelleneintrag dieser Record */
        short rt_keyfile;       /* Keytabelle (wenn Record Key enthaelt) */
        short rt_chain;         /* naechster Record dieser Datei */
        short rt_len;           /* Recordlaenge (ohne key_only Felder)*/
        short rt_onlykey;       /* Laenge der Key_only Felder */
        short rt_fields;        /* erster Eintrag in Feld-Tabelle */
        short rt_fdtot;         /* Anzahl der Felder in der Record */
} RECORD_ENTRY;

/* Struktur eines Eintrages in der Field-Tabelle */
typedef struct field_entry {
        short fd_type;  /* 'c' - char, 's' - short, 'i' - int, 'l' - long
                           'd' - DB_ADDR, 'g' - grouped, */
        short fd_len;   /* Feldlaenge */
        short fd_ptr;   /* Offset des Feldes im Record */
        short fd_rec;   /* Record-Tabelleneintrag dieses Feldes */
        short fd_key;   /* Keytyp */
        short fd_keyfile;       /* Index in File-Tabelle des keyfiles */
        short fd_treefile;      /* Index in File-Tabelle des Tree-Files */
        short fd_file;          /* Index in Filetabelle des Records */
        short fd_keyno;         /* Index in Key-Tabelle */
} FIELD_ENTRY;

/* Struktur eines Slots im HTree-File */
typedef struct htslot {
        INT records[HDIM];
        unsigned char filled[HDIM];
} HTSLOT;

/* Struktur eines Slots im QTree-File */
typedef struct qtslot {
        INT records[QDIM];
        unsigned char filled[QDIM];
} QTSLOT;

/* Struktur eines Slots im CTree-File */
typedef struct chtslot {
        INT records[CDIM];
        unsigned char filled[CDIM];
} CTSLOT;
 
#define abort dds_abort

#include <poppack.h>

#endif // _DDSTYPES_H
