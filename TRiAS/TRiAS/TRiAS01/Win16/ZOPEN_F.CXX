/* Fortran Schnittstelle (UNIX) - Eroeffnen der DB              */
/* File: ZOPEN_F.C              last update: 7. Februar 1990    */

#ifdef sccs
static char SccsId[] = "ZIPEDB: @(#)zopen_f.c   2.10  90/05/18";
#endif

#ifdef MSWIND
#include <windows.h>
#endif //MSWIND
#include <stdio.h>
#include "dwd.h"
#include <fcntl.h>
#include <io.h>
#include <string.h>
#include <malloc.h>
#include "dbtypes.h"
#include "dioexter.h"
#include "keyexter.h"
#include "errdef.h"
#ifdef vms
#include "vmstypes.h"
#endif

#if defined(MSWIND)
#define close(fh)	_lclose(fh)
#endif

#ifdef unix
zopen_ (s_dbfile, s_uname, s_passwd, l_dbfile, l_uname, l_passwd)
char *s_dbfile; /* Name des Steuerfiles */
char *s_uname;  /* Nutzername */
char *s_passwd; /* Passwort */
long l_dbfile;  /* Laenge der Parameter */
long l_uname;
long l_passwd;
#endif

#ifdef msdos
/*VARARGS 2*/
INT FUNCTYPE
zopen_ (s_dbfile, l_dbfile, s_uname, l_uname, s_passwd, l_passwd)
char *s_dbfile;   /* Name des Steuerfiles */
char *s_uname;    /* Nutzername */
char *s_passwd;   /* Passwort */
int l_dbfile, l_uname, l_passwd;
#endif

#ifdef vms
zopen (file, uname, pwd)
struct str_par *file, *uname, *pwd;
#endif
{
register struct dbpasswd *dwd;
#ifdef MSWIND
OFSTRUCT of;	// Dateiverwaltungsstruktur
HANDLE handle;
#endif // MSWIND
register int dbf;

int namelen;
char *name;
char *dummy;
#ifdef MULTI_DB
register int i;
#endif

#if defined(unix) || defined(msdos)
char dbfile[81], uname[81], passwd[81];
register char *cptr;

        memset (dbfile, '\0', 81);
        memset (uname, '\0', 81);
        memset (passwd, '\0', 81);
        strncpy (dbfile, s_dbfile, (int)l_dbfile > 80 ? 80 : (int)l_dbfile);
        strncpy (uname, s_uname, (int)l_uname > 80 ? 80 : (int)l_uname);
        strncpy (passwd, s_passwd, (int)l_passwd > 80 ? 80 : (int)l_passwd);
        if ((cptr = strrlchr (dbfile, ' ')) != NULL) *cptr = '\0';
        if ((cptr = strrlchr (uname, ' ')) != NULL) *cptr = '\0';
        if ((cptr = strrlchr (passwd, ' ')) != NULL) *cptr = '\0';
#endif
#ifdef vms
char dbfile[81], uname[81], passwd[81];
register char *cptr;

        memset (dbfile, '\0', 81);
        memset (uname, '\0', 81);
        memset (passwd, '\0', 81);
        strncpy (dbfile, file->str, (int)file->len > 80 ? 80 : (int)file->len);
        strncpy (uname, uname->str, (int)uname->len > 80 ? 80 : (int)uname->len);
        strncpy (passwd, pwd->str, (int)pwd->len > 80 ? 80 : (int)pwd->len);
        if ((cptr = strrlchr (dbfile, ' ')) != NULL) *cptr = '\0';
        if ((cptr = strrlchr (uname, ' ')) != NULL) *cptr = '\0';
        if ((cptr = strrlchr (passwd, ' ')) != NULL) *cptr = '\0';
#endif
#ifdef MULTI_DB
/* Bereitstellen eines DB-slots */
        for (i = 0; i < MAXDB; ++i)
                if (db_table[i].db_name == NULL) break;

        if (i == MAXDB) return (dberr (S_MAXDB, ZOPEN_F));
        else db_table[i].db_name = "Slot besetzt";
#endif // MULTI_DB

/* Steuerblockdatei eroeffnen */
	namelen = _fstrlen (dbfile);
#ifdef MSWIND
	if ((handle = GlobalAlloc (GHND, namelen+5)) == NULL) {
		db_table[i].db_name = NULL;
		return (db_error (S_NOMEMORY, ZOPEN_F));
	}
	name = (char *)GlobalLock (handle);
#else // MSWIND
	name = calloc (namelen+5, 1);
#endif //MSWIND
	if (name == NULL) {
		db_table[i].db_name = NULL;
		return (dberr (S_NOMEMORY, ZOPEN_F));
	}
	_fstrcpy (name, dbfile);
#ifndef MSWIND
	_fstrcat (name, STB_EXTENSION);
#endif
#ifdef MSWIND
	if ((dbf = OpenFile ((LPSTR)name, &of, OF_READ)) == -1)
#else // MSWIND
#ifdef unix
	if ((dbf = open (name, O_RDONLY)) < 0)
#endif
#ifdef vms
	if ((dbf = open (name, O_RDONLY)) < 0)
#endif
#ifdef msdos
	if ((dbf = open (name, O_RDONLY+O_BINARY)) < 0)
#endif
#endif // MSWIND
	{
		db_table[i].db_name = NULL;
                return (dberr (S_INVDB, ZOPEN_F));
	}
/* Passworteintrag lesen */
        if ((dwd = getdwnam (uname, dbfile)) == NULL) {
		db_table[i].db_name = NULL;
		close (dbf);
                return (dberr (S_ACCESS, ZOPEN_F));
	}
/* Passwort vergleichen */
	if (*dwd->dw_passwd &&
		strcmp (crypt (passwd, dwd->dw_passwd), dwd->dw_passwd)) {
		db_table[i].db_name = NULL;
		close (dbf);
                return (dberr (S_ACCESS, ZOPEN_F));
	}
#if !defined(MULTI_DB)
        if (dbopen) db_close ();                /* nur eine DB offen halten */
#endif
/* interne Tabellen einrichten */
        if (inittab (name, dwd, dbf) != S_OKAY) {
		db_table[i].db_name = NULL;
		close (dbf);
		return (db_status);
	}
/* E/A-Tabellen, Pages etc. einrichten */
        if (dio_init () != S_OKAY) {
		db_table[i].db_name = NULL;
		close (dbf);
		return (db_status);
	}
	close (dbf);

/* Handler fuer S_INVADDR installieren */
	err_install (S_INVADDR, (INT_FUNC *)einvaddr, (INT_FUNC **)&dummy);

#ifdef MULTI_DB
/* Diese Datenbasis ist die aktuelle */
	act_db = &db_table[i];
        name[namelen] = '\0';
        act_db->db_name = name;         /* DB-Name */
        act_db->db_sft = size_ft;       /* Groesse der Dateitabelle */
        act_db->db_skt = size_kt;       /* Anzahl der Schluessel */
        act_db->db_srt = size_rt;       /* Anzahl der Records */
        act_db->last_file = 0;          /* zuletzt angefasste Datei */
        act_db->db_work = NONE;         /* working_file */
	act_db->db_field = NONE;	/* KeyFieldNumber */
	act_db->db_lvl = 0;             /* Level im BTree */
        act_db->db_ftab = file_table;   /* Dateitabelle */
        act_db->db_ktab = key_table;    /* Schluesseltabelle */
        act_db->db_rtab = record_table; /* Recordtabelle */
        act_db->db_pztab = pgzero;      /* Page 0 Tabelle */
        act_db->db_slots = NULL;        /* Position im BTree */
        act_db->db_parent = NULL;
	act_db->db_version = DBVersion;	/* VersionsNummer */
	act_db->db_pagesize = PageSize;
#ifdef BACKUP
        act_db->db_bflag = backup_flag; /* Backupdatei */
#endif // BACKUP

	return (i);
#else  // MULTI_DB
        dbopen = TRUE;
        return (db_status = S_OKAY);
#endif // MULTI_DB
}
 
