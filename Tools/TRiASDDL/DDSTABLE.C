/* DDSP - Tabellenhandhabung (Unterprogramme fuer Parser)       */
/* File: DDSTABLE.C             last update: 22. Juni 1989      */

#include "StdAfx.h"

#include "dbversio.h"
#include "ddspprot.h"		// Prototypen

#define FALSE 0
#define TRUE  1

extern char fnout[];		/* AusgabeDateiname */

static int key_tab_init ();
static void wr_C_inc ();
static void wr_f77_inc (char *name);
static void wr_rec (struct record_info *r, char *string1, char *format, char *string2);

/* File-Tabelle */

struct file_info {
	struct file_info  *next_file;   /* Zeiger zum naechsten file_info Eintrag */
	ID_INFO    *name_list;          /* Zeiger zum Record/Fieldlisteeintrag */
	char name[FILENMLEN];           /* Filename */
	FT_ENTRY ft;                  /* file_entry Eintrag fuer dieses File */
} 
*file_list = NULL,
*last_file = NULL;

short tot_files = 0;    /* Anzahl der Files */

/* Record-Tabellen */
struct record_info {
	struct record_info  *next_rec;
	char   rec_name[NAMELEN];
	RECORD_ENTRY rt;                
} 
*rec_list = NULL,
*last_rec = NULL;

short tot_records = 0;  /* Anzahl der Records */

/* Datenfield-Tabellen */
struct field_info {
	struct field_info  *next_field;
	int union_cnt;
	char   fld_name[NAMELEN];
	FIELD_ENTRY fd;                 
}
*field_list = NULL,
*last_fld = NULL,
*cur_struct = NULL;

short tot_fields = 0;   /* Anzahl der Datenfelder insgesamt */

/* Key-Feldtabelle */
struct key_info {
	struct key_info *next_key;
	char key_name[NAMELEN];
	int kt_rec;
	KEY_ENTRY kt;
} *key_list = NULL,
*last_key = NULL;

short tot_keys = 0;
short key_prefix = 0;   /* Keyfeldzaehler */

#ifdef BACKUP
short backup_flag = -1; /* Backupflag fuer faules Kopieren */
#endif

FILE *ifile;            /* Includefilepointer 'C' (Ausgabe) */
FILE *ffile;            /* Includefilepointer 'F77' (Ausgabe) */
char ifn[_MAX_PATH];      /* Includefilename */
char ffn[_MAX_PATH];      /* F77 - Includefilename */
extern char db_name[];  /* Datenbasisname */
extern int r_flag;      /* Kommandozeilenflag */
extern int f_flag;
extern int s_flag;
extern int h_flag;
extern int c_flag;

extern long DBVersion;	/* VersionsNummer */
extern long PageSize;	/* PageGröße */

extern char dbd_ext[];	/* Erweiterung des DictionaryFiles */

char val[20];

int onlyflag = 0;       /* 0: noch kein OnlyKey in Record
						1: aktuelle Struct/Union ist OnlyKey
2: OnlyKey-Feld in Record enthalten */

/* Konvertieren einer Zeile in Grossbuchstaben */
char *upper(s)
char *s;
{
	register char *p;
	
	for (p = s; *p; p++) {
		if ( *p >= 'a' && *p <= 'z' )
			*p = *p - 'a' + 'A';
	}
	return(s);
}


/* Konvertierung: Integer -> String */
char *itos(num)
int num;
{
	register int i,j;
	register int div;
	register char ch;
	
	for (i = 0; num ; i++) {
		div = num % 10;
		num = num / 10;
		val[i] = (char)(div + '0');
	}
	val[i] = '\0';
	for (j = 0; j < i; j++) {
		ch = val[--i];
		val[i] = val[j];
		val[j] = ch;
	}
	return(val);
}

/* Eroeffnen der Includefiles */
void open_files()
{
	if ('\0' != fnout)
		strcpy (ifn, fnout);
	else
		strcpy (ifn, db_name);
	strcat(ifn, ".h");
	if (h_flag) {
		if ((ifile = fopen (ifn, "w")) == NULL)
			abort ("Kann C Includedatei nicht eroeffnen");
		if (!s_flag) printf ("Includedateiname: %s\n", ifn);
		fprintf (ifile, "/* Deklaration der Datenbasisstruktur fuer %s */\n\n", db_name);
	}
}


/* Suchen des zu einer Record gehoerenden Files */
struct file_info 
*find_file(name,fno)
char *name;
int  *fno;
{
	register struct file_info *p;
	register ID_INFO   *q;
	
	for (*fno = 0, p = file_list; p; p = p->next_file, ++(*fno)) {
		for (q = p->name_list; q; q = q->next_id) {
			if (strcmp (name, q->id_name) == 0)
				return(p);
		}
	}
	return(NULL);
}


/* Suchen einer Record in der Record-Tabelle */
struct record_info *find_rec(rname, rno)
char *rname;
int  *rno;
{
	register struct record_info *p;
	
	for (*rno = 0, p = rec_list; p; p = p->next_rec, ++(*rno) ) {
		if (strcmp (rname, p->rec_name) == 0)
			break;
	}
	return(p);
}


/* Suchen eines Feldnamens in der Field-Tabelle */
struct field_info *find_fld(fname, fno)
char *fname;
int  *fno;
{
	register struct field_info *p;
	
	for (*fno = 0, p = field_list; p; p = p->next_field, ++(*fno)) {
		if (strcmp(fname, p->fld_name) == 0)
			break;
	}
	return(p);
}


/* Hinzufuegen eines Files zur File-Tabelle */
struct file_info 
*add_file(fname, ftype, idlist)
char *fname;
int ftype;
ID_INFO *idlist;
{
	int i;
	register struct file_info *p;
	register ID_INFO *q;
	
	/* ueberpruefen, ob File bereits definiert ist */
	for (p = file_list; p; p = p->next_file) {
		if (strcmp (p->name, fname) == 0) {
			yyerror ("Datei ist bereits definiert");
			return (NULL);
		}
	}
	/* ueberpruefen, ob Record oder Field schon in anderen
	Files definiert ist */
	for (q = idlist; q; q = q->next_id) {
		p = find_file (q->id_name, &i);
		if (p && p->ft.ft_type != HTREEFILE
			&& p->ft.ft_type != QTREEFILE
			&& p->ft.ft_type != CTREEFILE) {
			yyerror ("Record/Feld ist in anderer Datei enthalten");
			return (NULL);
		}
	}
	/* anlegen des File-Tabellen-Eintrages */
	p = (struct file_info *)calloc (1, sizeof (struct file_info));
	if (p == NULL)
		abort ("Kein Speicherplatz");
	if (last_file == NULL)
		file_list = p;
	else
		last_file->next_file = p;
	last_file = p;
	p->next_file = NULL;
	p->name_list = idlist;
	strncpy (p->name, fname, FILENMLEN);
	p->ft.ft_name = NULL;
	p->ft.ft_type = ftype;
	p->ft.ft_status = 'c';
	p->ft.ft_recfile = -1;
	
#ifdef BACKUP
	if (ftype == 'b') backup_flag = tot_files;
#endif
	
	++tot_files;
	return(p);
}


/* Hinzufuegen eines Record-Eintrages zur Record-Table */
struct record_info *add_record(rname)
char *rname;
{
	int fno;
	register struct record_info *p;
	register struct file_info *ft_p;
	
	/* ueberpruefen, dass Record noch nicht definiert ist */
	for (p = rec_list; p; p = p->next_rec) {
		if (strcmp (p->rec_name, rname) == 0)
			abort("Record ist bereits definiert");
	}
	
	/* ueberpruefen, dass Record wirklich in angegebenem File ist */
	if ((ft_p = find_file (rname, &fno)) == NULL)
		abort ("Record ist nicht in einer Datei enthalten");
	
	/* anlegen eines neuen Record-Eintrages */
	p = (struct record_info *)calloc (1, sizeof (struct record_info));
	if (p == NULL)
		abort ("Kein Speicherplatz");
	if (last_rec == NULL)
		rec_list = p;
	else
		last_rec->next_rec = p;
	last_rec = p;
	strcpy (p->rec_name, rname);
	p->rt.rt_len = 0;
	p->rt.rt_onlykey = 0;
	p->rt.rt_fdtot = 0;
	p->rt.rt_fields = tot_fields;
	p->rt.rt_file = fno;
	p->rt.rt_keyfile = -1;
	p->next_rec = NULL;
	p->rt.rt_chain = ft_p->ft.ft_recfile;
	//      if (ft_p->ft.ft_recfile != -1)
	ft_p->ft.ft_recfile = tot_records;
	++tot_records;
	onlyflag = FALSE;
	if (h_flag)
		fprintf (ifile,"struct %s {\n",rname);
	
	return (p);
}


/* Abschliessen einer Record-Struktur Definition */
void close_record()
{
	if (h_flag)
		fprintf(ifile,"};\n");
}


/* hinzufuegen eines Feld-Eintrages in die Field-Tabelle */
struct field_info *add_field (name, type, size, key, decl)
char *name;
int type;
int  size;
register int  key;
char *decl;
{
	int key_file;
	register struct field_info *p;
	register struct file_info *f;
	int key_only;
	char orig_type = type;
	
	if (type == FT_STRUCT || type == FT_UNION)
		type = FT_GROUPED;
	/* ueberpruefen, dass Feld noch nicht definiert wurde */
	for (p = field_list; p; p = p->next_field) {
		if (strcmp (p->fld_name, name) == 0) {
			yyerror ("Doppelt vergebener Feldname");
			return (NULL);
		}
	}
	f = find_file (name, &key_file);
	/* ueberpruefen, ob Keyfeld in einem Keyfile enthalten ist */
	if (key != KT_NOKEY && type != FT_GROUPED) {
		if (f == NULL || (f->ft.ft_type != KEYFILE &&
			f->ft.ft_type != HTREEFILE &&
			f->ft.ft_type != CTREEFILE &&
			f->ft.ft_type != QTREEFILE &&
			f->ft.ft_type != TREEKEYFILE)) {
			yyerror("Feld ist in keiner Key-Datei enthalten");
			return(NULL);
		}
	}
	p = (struct field_info *) calloc (1, sizeof (struct field_info));
	if (p == NULL)
		abort("Kein Speicherplatz");
	if (last_fld == NULL)
		field_list = p;
	else
		last_fld->next_field = p;
	last_fld = p;
	strcpy (p->fld_name, name);
	p->fd.fd_key = key;             /* NOKEY ... */
	p->fd.fd_type = orig_type;      /* int, long, grouped ... */
	p->fd.fd_len  = size;           /* Feldlaenge */
	if (key != KT_NOKEY)
		p->fd.fd_keyno = key_prefix++;
	else
		p->fd.fd_keyno = -1;
	if (type != FT_GROUPED && f != NULL) {
		switch (f->ft.ft_type) {
		case HTREEFILE:         /* HexTree */
		case QTREEFILE:         /* QuadTree */
		case CTREEFILE:         /* CubicTree */
			p->fd.fd_keyfile = key_file +1;
			p->fd.fd_treefile = key_file;
			break;
			
		case KEYFILE:           /* B*Tree */
		case TREEKEYFILE:       /* GeoTree */
			p->fd.fd_keyfile = key_file;
			p->fd.fd_treefile = -1;
			break;
			
		default:
			/* nichts machen */
			break;
		}
	} else {
        /* NOKEY */
		p->fd.fd_keyfile =
			p->fd.fd_treefile = -1;
	}
	p->fd.fd_file = last_rec->rt.rt_file;
	p->fd.fd_ptr = 0;
	p->fd.fd_rec = tot_records - 1;
	p->next_field = NULL;
	key_only = (key == KT_UNIQUE_ONLY || key == KT_KEY_ONLY || (cur_struct &&
		(cur_struct->fd.fd_key == KT_UNIQUE_ONLY || cur_struct->fd.fd_key == KT_KEY_ONLY)));
	if (!key_only && !(cur_struct && cur_struct->fd.fd_type == FT_UNION)) {
        /* Nicht KeyOnly und nicht Union */
		last_rec->rt.rt_len += size;  /* Increment record size */
	}
	if (!(cur_struct && cur_struct->fd.fd_type == FT_UNION))
        /* nicht UNION */
		last_rec->rt.rt_onlykey += size;    /* only_key Feldlaenge */
	++(last_rec->rt.rt_fdtot);   /* Inc total Fields in Record */
	if (type == FT_GROUPED) {
        /* Struktur/Union-Deklaration */
		if (cur_struct)
			yyerror ("Verschachtelte Strukturen/Unions sind nicht implementiert");
		else {
			if (h_flag) fprintf (ifile,"\t%s\n", decl);
			cur_struct = p;
			if (orig_type == FT_UNION) p->union_cnt = 0;
		}
	}
	else if (cur_struct) {
        /* Datenfeld in Struktur/Union */
		if (h_flag) fprintf(ifile,"\t\t%s\n", decl);
		switch (cur_struct->fd.fd_type) {
		case FT_STRUCT:
			cur_struct->fd.fd_len += size;
			break;
			
		case FT_UNION:
			if (cur_struct->fd.fd_len < size)
				cur_struct->fd.fd_len = size;
			++(cur_struct->union_cnt);
			break;
			
		default:
			yyerror ("Falscher Grouped-Datentyp");
			break;
		}
	}
	else    /* normales Datenfeld */
		if (h_flag) fprintf(ifile,"\t%s\n", decl);
	if (onlyflag > 1) yyerror ("OnlyKey musz letztes Feld in Record sein");
	if (key_only) {
		if (onlyflag == 1 && (key == KT_KEY || key == KT_UNIQUE))
			yyerror ("Keydefinition in OnlyKey-Struktur/Union nicht erlaubt");
		if (cur_struct) onlyflag = 1;
		else onlyflag = 2;
	}
	++tot_fields;
	return(p);
}

/* Abschliessen einer Strukturdeklaration */
void close_struct (key, name, entries)
int key;
char *name;
int entries;
{
	int key_file;
	register struct file_info *f;
	
	if (h_flag) fprintf (ifile, "\t} %s", name);
	if (entries > 1) {
		if (h_flag) fprintf (ifile, "[%d]", entries);
		cur_struct->fd.fd_len *= entries;
	}
	if (h_flag) fprintf (ifile, ";\n");
	strcpy (cur_struct->fld_name, name);
	f = find_file (name, &key_file);
	if (cur_struct->fd.fd_key != KT_NOKEY) {
		if (f == NULL
			|| (f->ft.ft_type != KEYFILE &&
			f->ft.ft_type != HTREEFILE &&
			f->ft.ft_type != CTREEFILE &&
			f->ft.ft_type != QTREEFILE &&
			f->ft.ft_type != TREEKEYFILE)) 
		{
			yyerror("Feld ist in keiner Key-Datei enthalten");
		}
	}
	if (f != NULL) {
		switch (f->ft.ft_type) {
		case HTREEFILE:         /* HexTree */
		case CTREEFILE:         /* CubicTree */
		case QTREEFILE:         /* QuadTree */
			cur_struct->fd.fd_keyfile = key_file +1;
			cur_struct->fd.fd_treefile = key_file;
			break;
			
		case KEYFILE:           /* B*Tree */
		case TREEKEYFILE:       /* GeoTree */
			cur_struct->fd.fd_keyfile = key_file;
			cur_struct->fd.fd_treefile = -1;
			
		default:
			/* nichts machen */
			break;
		}
	} else {
        /* NOKEY */
		cur_struct->fd.fd_keyfile =
			cur_struct->fd.fd_treefile = -1;
	}
	if (cur_struct->fd.fd_type == FT_UNION) {
        /* Recordgroesse richtig setzen */
		if (key != KT_UNIQUE_ONLY && key != KT_KEY_ONLY)
			/* Union ist nicht KeyOnly */
			last_rec->rt.rt_len += cur_struct->fd.fd_len;
		last_rec->rt.rt_onlykey += cur_struct->fd.fd_len;
	}
	if (onlyflag == 1) ++onlyflag;
	cur_struct = NULL;
}


/* Berechnen der Field/Record - Parameter */
int finish_up()
{
	register struct record_info *r;
	register struct file_info *f;
	register struct field_info *d;
	register int offset;
	register int rno, fno, maxi;
	struct record_info *pr;
	struct field_info *pf;
	
	for (rno = 0, r = rec_list; r; r = r->next_rec, ++rno) {
        /* Berechnen der Feldoffsets im Record */
		offset = 0;
		for (d = field_list; d; d = d->next_field) {
			if (d->fd.fd_rec == rno) {
				if (d->fd.fd_type != FT_CHARACTER) {
					r->rt.rt_len += offset % 2;
					offset += offset % 2;
				}
				d->fd.fd_ptr = offset;
				if (d->fd.fd_type != FT_UNION && d->fd.fd_type != FT_STRUCT)
					offset += d->fd.fd_len;
			}
		}
	}
	
	if (key_tab_init () < 0)        /* Berechnen der Key-Tabelle */
		return (-1);
	
	/* Berechnen der Pageaufteilung */
	for (fno = 0, f = file_list; f; f = f->next_file, ++fno) {
		maxi = 0;
		switch (f->ft.ft_type) {
		case DATAFILE:
			for (r = rec_list; r; r = r->next_rec)
				if (r->rt.rt_file == fno) {
					/* finden der groessten Record im File */
					if (r->rt.rt_len > maxi) {
						maxi = r->rt.rt_len;
						pr = r;
					}
				}
				if (maxi < sizeof(INT)) maxi = sizeof(INT);
				if (maxi > PageSize - PAGEHDRSIZE) {
					fprintf(stderr, "Fataler Fehler - Record %s ist zu grosz\n",
						pr->rec_name);
					exit(1);
				}
				f->ft.ft_slsize = maxi = maxi + (maxi % 2);
				f->ft.ft_slots = (PageSize - PAGEHDRSIZE)/maxi;
				break;
				
		case HTREEFILE:
			f->ft.ft_slsize = maxi = sizeof(HTSLOT);
			f->ft.ft_slots = (PageSize-PAGEHDRSIZE)/maxi;
			break;
			
		case CTREEFILE:
			f->ft.ft_slsize = maxi = sizeof(CTSLOT);
			f->ft.ft_slots = (PageSize-PAGEHDRSIZE)/maxi;
			break;
			
		case QTREEFILE:
			f->ft.ft_slsize = maxi = sizeof(QTSLOT);
			f->ft.ft_slots = (PageSize-PAGEHDRSIZE)/maxi;
			break;
			
		case TREEKEYFILE:       /* Keydatei fuer GeoKeys */
			for (d = field_list; d; d = d->next_field) {
				if (d->fd.fd_key != KT_NOKEY && d->fd.fd_keyfile == fno) {
					if (d->fd.fd_len > maxi)  {
						maxi = d->fd.fd_len;
						pf = d;
					}
				}
			}
			if (maxi > PageSize - PAGEHDRSIZE) {
				fprintf(stderr, "Fataler Fehler - Feld %s ist zu grosz\n",
					pf->fld_name);
				exit (1);
			}
			maxi += sizeof (INT);   /* fuer Verweis auf Targetdatei */
			f->ft.ft_slsize = maxi = maxi + (maxi % 4);
			f->ft.ft_slots = (PageSize - PAGEHDRSIZE)/maxi;
			break;
				
#ifdef BACKUP
		case BACKUPFILE:
			break;
#endif
			
		default:
			for (d = field_list; d; d = d->next_field) {
				if (d->fd.fd_key != KT_NOKEY && d->fd.fd_keyfile == fno) {
					if (d->fd.fd_len > maxi)  {
						maxi = d->fd.fd_len;
						pf = d;
					}
				}
			}
			if (maxi > (int)(PageSize - PAGEHDRSIZE - sizeof(long))) {
				fprintf(stderr, "Fataler Fehler - Feld %s ist zu groß\n",
					pf->fld_name);
				exit (1);
			}
			maxi += 2*sizeof (INT); /* fuer Childpointer und
			Verweis auf Targetdatei */
			f->ft.ft_slsize = maxi = maxi + (maxi % 4);
			f->ft.ft_slots = (PageSize - PAGEHDRSIZE - sizeof(INT))/maxi;
			break;
		}
	}
}


/* Initialisieren der Key-Tabelle */
static int
key_tab_init () {
	register struct field_info *p;
	register struct key_info *k;
	register struct file_info *f;
	register struct record_info *r;
	int rno;
	int file;
	
	tot_keys = 0;
	for (p = field_list; p; p = p->next_field) {
		if (p->fd.fd_keyfile >= 0) {
			k = (struct key_info *)calloc (1, sizeof(struct key_info));
			if (k == NULL) 
				abort ("Kein Speicherplatz");
			if (last_key == NULL) 
				key_list = k;
			else 
				last_key->next_key = k;
			last_key = k;
			k->kt.kt_keyfile = p->fd.fd_keyfile;
			k->kt.kt_treefile = p->fd.fd_treefile;
			k->kt.kt_len = p->fd.fd_len;
			k->kt.kt_file = p->fd.fd_file;
			k->kt.kt_offset = p->fd.fd_ptr;
			k->kt_rec = p->fd.fd_rec;
			k->kt.kt_chain = -1;    /* letzter Key (vorerst) */
			find_key (p->fd.fd_rec, tot_keys);      /* verketten */
			strcpy (k->key_name, p->fld_name);
			for (rno = 0, r = rec_list; r; r = r->next_rec, ++rno) {
				if (rno == p->fd.fd_rec)
					break;
			}
			if (r->rt.rt_keyfile == -1)
				r->rt.rt_keyfile = p->fd.fd_keyno;
			if ((f = find_file (r->rec_name, &file)) == NULL) {
				yyerror ("Record ist in keiner Daten-Datei enthalten");
				return (-1);
			}
			k->kt.kt_type = p->fd.fd_key;
			k->kt.kt_field = p->fd.fd_type;
			++tot_keys;
		}
	}
	
	return (0);
}

/* Verketten der Key-Tabelleneintraege, die zu einer Record gehoeren */
void find_key (recno, keyno)
int recno, keyno;
{
	register int i;
	register struct key_info *k;
	
	for (i = 0, k = key_list; k; ++i, k = k->next_key) {
		if (k->kt_rec == recno && k->kt.kt_chain == -1 && i != keyno)
			k->kt.kt_chain = keyno;
	}
}

/* Schreiben des Steuerfiles (Filetabelle etc. ) */
void write_tables()
{
	register struct file_info *f;
	register struct record_info *r;
	register struct key_info *k;
	register struct field_info *d;
	char tfn[_MAX_PATH];  /* table-file Name */
	FILE *tfile;        /* table file Pointer */
	char copyright[81];     /* Copyright fuer Ausgabe in '*.dbd' */
	
	/* Generieren des Steuerfilenamens */
	if ('\0' != fnout)
		strcpy (tfn, fnout);
	else
		strcpy (tfn, db_name);
	strcpy (ffn, tfn);
	strcat (ffn, ".f");
	
	if (h_flag) fprintf (ifile, "\n/* Record- und Feld-Tabelleneintraege */\n");
	
	if (!c_flag) {
        /* Ausgabefile eroeffnen */
		strcat (tfn, ".dbd");
#ifdef unix
		if ((tfile = fopen(tfn,"w")) == NULL)
#endif
#ifndef unix
		if ((tfile = fopen(tfn, "wb")) == NULL)
#endif
			abort ("Kann Tabellendatei nicht eroeffnen");
		if (!s_flag) printf ("Steuerdateiname : %s\n", tfn);
		fflush (stdout);
		
		/* Copyright schreiben */
		memset (copyright, '\0', 80);
		sprintf (copyright, "%s - %s%s %s\r\n\032", Copyright, Version, Release, Date);
		fwrite (copyright, 1, 80, tfile);
		
		/* Ausgabe der Tabellengroessen */
		fwrite(&tot_files, sizeof(short), 1, tfile);
		fwrite(&tot_keys, sizeof(short), 1, tfile);
		fwrite(&tot_records, sizeof(short), 1, tfile);
		fwrite(&tot_fields, sizeof(short), 1, tfile);
		
#ifdef BACKUP
		/* Ausgabe des Backup-Flags */
		fwrite (&backup_flag, sizeof(short), 1, tfile);
#endif
		
		/* Ausgabe der Filetabelle */
		for (f = file_list; f; f = f->next_file)
			fwrite (&(f->ft), sizeof(FT_ENTRY), 1, tfile);
		for (f = file_list; f; f = f->next_file)
			fwrite (f->name, FILENMLEN, 1, tfile);
		
		/* Ausgabe der Keytabelle */
		for (k = key_list; k; k = k->next_key)
			fwrite (&(k->kt), sizeof (KEY_ENTRY), 1, tfile);
		for (k = key_list; k; k = k->next_key)
			fwrite (k->key_name, NAMELEN, 1, tfile);
		
		/* Ausgabe der Recordtabelle */
		for (r = rec_list; r; r = r->next_rec)
			fwrite (&(r->rt), sizeof (RECORD_ENTRY), 1, tfile);
		for (r = rec_list; r; r = r->next_rec)
			fwrite (r->rec_name, NAMELEN, 1, tfile);
		
		/* Ausgabe der Feldtabelle */
		for (d = field_list; d; d = d->next_field)
			fwrite (&(d->fd), sizeof (FIELD_ENTRY), 1, tfile);
		for (d = field_list; d; d = d->next_field)
			fwrite (d->fld_name, NAMELEN, 1, tfile);
		
		/* VersionsNummer ans Ende schreiben */
		fwrite (&DBVersion, sizeof(DBVersion), 1, tfile);
		fwrite (&PageSize, sizeof(PageSize), 1, tfile);
		fwrite (dbd_ext, 1, 4, tfile);
		
		fclose(tfile);
	} /* Ende !c_flag */
	
	if (f_flag) 
		wr_f77_inc (ffn);   /* F77 Includefile generieren */
	if (h_flag)
		wr_C_inc();        /* C Includefile weiterschreiben */
	if (!s_flag) 
		printf ("\n");
	if (r_flag) 
		print_tables();
	
	if (h_flag) fclose(ifile);
}


static void wr_f77_inc (name)
char *name;             /* Filename */
{
	struct key_info *kp; 
	register struct record_info *r;
	time_t timev;
	static char sizstr[7] = { 'S', 'I', 'Z', '\0' };
	register int k;
	
	/* F77 Includefile */
	if ((ffile = fopen (name, "w")) == NULL)
		abort ("Kann F77 Includedatei nicht eroeffnen");
	if (!s_flag) printf ("F77 Includedatei: %s\n\n", ffn);
	fprintf (ffile, "C\nC\tRecord- und Felddefinitionen\nC Datei: %s\t\t", ffn);
	time (&timev);
	fprintf (ffile, "generiert: %sC\n", ctime (&timev));
	
	for (r = rec_list, k = 0; r; r = r->next_rec, ++k) {
		fprintf (ffile, "C Record: %s", upper (r->rec_name));
		fprintf (ffile, "\n\tINTEGER*4 N%s\n\tPARAMETER (N%s = %d)\n",
			r->rec_name, r->rec_name, k);
		wr_rec (r, "\tINTEGER*4 ", "%s", "\n");
		wr_rec (r, "\tPARAMETER (", "%s = %d", ")\n");
		sizstr[3] = '\0';
		fprintf (ffile, "\tINTEGER*4 %s\n", strncat (sizstr, r->rec_name, 3));
		fprintf (ffile, "\tPARAMETER (%s = %d)\n", sizstr, r->rt.rt_len/sizeof(INT));
	}
	fprintf (ffile, "C\nC\tSchluesselnummerdefinitionen\nC\n");
	for (kp = key_list, k = 0; kp; kp = kp->next_key, ++k) {
		fprintf (ffile, "C Schluessel: %s\n", upper (kp->key_name));
		fprintf (ffile, "\tINTEGER*4 S%s\n", kp->key_name);
		fprintf (ffile, "\tPARAMETER (S%s = %d)\n", kp->key_name, k);
	}
	fclose (ffile);
}


static void
wr_rec (r, string1, format, string2)
struct record_info *r;
char *string1, *format, *string2;
{
	register struct field_info *d;
	int offset;
	register int j, k;
	int count = 0;
	struct field_info *union_p = NULL;
	
	for (d = field_list, j = 0; j != r->rt.rt_fields; d = d->next_field, ++j)
		;
	offset = 0;
	for (j = 0, k = 0; j < r->rt.rt_fdtot; d = d->next_field, ++j, ++k) {
        /* j zaehlt alle Felder einer Record */
        /* k zaehlt die ausgegebenen Felder */
		if (d->fd.fd_type == FT_STRUCT) {
			--k; continue;
		}
		if (count == 0 && union_p != NULL) {
			offset += union_p->fd.fd_len;
			union_p = 0;
		}
		if (d->fd.fd_type == FT_UNION) {
			/* Feld ist Union */
			count = d->union_cnt;
			union_p = d;
			--k;
			continue;
		}
		if (!testadr (offset, d)) {
			if (count > 0) --count;
			else offset += d->fd.fd_len;
			--k;
			continue;
		}
		if (!(k % 3)) fprintf (ffile, string1);
		fprintf (ffile, format, upper (d->fld_name), offset/sizeof(INT)+1);
		if (j+1 == r->rt.rt_fdtot || !((k+1)%3))
			fprintf (ffile, string2);
		else
			fprintf (ffile, ", ");
		
		if (count > 0) --count;
		else offset += d->fd.fd_len;
	}
}


int testadr (offset, d)
int offset;
register struct field_info *d;
{
	if (offset % sizeof (INT) || d->fd.fd_len % sizeof (INT))
		return (FALSE);
	else
		return (TRUE);
}

static void wr_C_inc ()
{
	register struct key_info *k;
	register struct record_info *r;
	register int i;
	
	if (!h_flag) return;

	/* C Includefile */
	/* Ausgabe der Record-Tabelleneintraege */
	fprintf (ifile, "\n/* Konstanten fuer Recordnamen */\n");
	for (i = 0, r = rec_list; r; ++i, r = r->next_rec)
		fprintf(ifile,"#define %s %d\n", upper(r->rec_name), i);
	/* Key-Feld Eintraege */
	fprintf (ifile, "\n/* Konstanten fuer Schluesselfelder */\n");
	for (i = 0, k = key_list; k; k = k->next_key, ++i)
		fprintf (ifile, "#define %s %d\n", upper (k->key_name), i);
}


/* Ausgeben der Datenbank-Tabellen */
void print_tables()
{
	register struct file_info *f;
	register struct record_info *r;
	register struct key_info *k;
	register int i;
	int j;
	time_t clock;
	
	time (&clock);
	printf("Datenbankstruktur: %s\n%s\n", db_name, ctime(&clock));
	
	for (i= 0, f = file_list; f; f = f->next_file, ++i) {
		char *filetype;
		
		printf("DATEI: %s\n", upper (f->name));
		printf("   Nummer: %d\n",i);
		switch ((int)f->ft.ft_type) {
		case KEYFILE:           filetype = "BTreeKey"; break;
		case HTREEFILE:         filetype = "HexTree"; break;
		case CTREEFILE:         filetype = "CubicTree"; break;
		case QTREEFILE:         filetype = "QuadTree"; break;
		case TREEKEYFILE:       filetype = "TreeKey"; break;
		case DATAFILE:          filetype = "Data"; break;
#ifdef BACKUP
		case BACKUPFILE:        filetype = "Backup"; break;
#endif
		default:                filetype = "Unknown"; break;
		}
		printf("   Typ   : %s\n", filetype);
		printf("   Groesse der Record-slots : %d\n",f->ft.ft_slsize);
		printf("   Record-slots je Page     : %d\n",f->ft.ft_slots);
		printf("   Ungenutzte Bytes je Page : %d\n",
			PageSize - (PAGEHDRSIZE + f->ft.ft_slots*f->ft.ft_slsize));
		printf ("\n");
	}
	for (i = 0, r = rec_list; r; r = r->next_rec, ++i) {
		/* Finden des File-Tabelleneintrages dieser Record */
		f = file_search (r->rt.rt_file, &j);
		printf("RECORD: %s\n",r->rec_name);
		printf("   Nummer : %d\n",i);
		printf("   Datei  : %s [%d]\n",f->name, r->rt.rt_file);
		printf("   Recordgroesse            : %d\n",r->rt.rt_len);
		printf("   Ungenutzte Bytes je Slot : %d\n",f->ft.ft_slsize - r->rt.rt_len);
		if (r->rt.rt_keyfile >= 0)
			printf("   Keynummer                : %d\n",
			r->rt.rt_keyfile);
		if (r->rt.rt_chain >= 0)
			printf("   Recordkette              : %d\n",
			r->rt.rt_chain);
		printf ("\n");
	}
	for (i = 0, k = key_list; k; k = k->next_key, ++i) {
		char *keytype;
		
		printf("KEYFELD: %s\n", k->key_name);
		printf("   Nummer : %d\n", i);
		f = file_search (k->kt.kt_file, &j);
		printf("   Targetdatei: %s [%d]\n", f->name, j);
		if (k->kt.kt_treefile >= 0) {
			f = file_search (k->kt.kt_treefile, &j);
			printf("   Treedatei  : %s [%d]\n", f->name, j);
		}
		f = file_search (k->kt.kt_keyfile, &j);
		printf("   Keydatei   : %s [%d]\n", f->name, j);
		switch ((int)k->kt.kt_field) {
		case 'c':       keytype = "Character"; break;
		case 'C':       keytype = "Char_Array"; break;
		case 'g':       keytype = "Struktur"; break;
		case 'G':       keytype = "Union"; break;
		case 's':       keytype = "Short_Integer"; break;
		case 'i':       keytype = "Integer"; break;
		case 'l':       keytype = "Long_Integer"; break;
		case 'f':       keytype = "Float"; break;
		case 'F':       keytype = "Double_Float"; break;
		case 'd':       keytype = "DB_Adresse"; break;
		default:        keytype = "Unknown"; break;
		}
		printf("   Feldtyp    : %s\n", keytype);
		printf("   Feldoffset : %d\n", k->kt.kt_offset);
		printf("   Feldlaenge : %d\n", k->kt.kt_len);
		if (k->kt.kt_chain != -1)
			printf("   Keykette   : %d\n", k->kt.kt_chain);
		switch ((int)k->kt.kt_type) {
		case 'd':       keytype = "Key"; break;
		case 'D':       keytype = "Only Key"; break;
		case 'u':       keytype = "Unique Key"; break;
		case 'U':       keytype = "Unique and Only Key"; break;
		default:        keytype = "Unknown"; break;
		}
		printf("   Keytyp     : %s\n\n", keytype);
	}
}



struct file_info *file_search (nummer, j)
register int nummer;
register int *j;
{
	register struct file_info *f;
	
	for (*j = 0, f = file_list; *j != nummer; ++(*j), f = f->next_file)
		;
	
	return f;
}
