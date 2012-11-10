/* Setzen einiger default-Werte aus File- und Key-Tabelle       */
/* File: KEYINI.C               last update: 26. September 1989 */

#include "trias01p.hxx"

/* Datendefinition der externen Variablen */
short d;                /* Anzahl der slots je Page */
short key_len;          /* Key-Laenge (== 1 fuer B*, == 4 fuer Htree) */
short slot_len;         /* Kopie aus File-Tabelle */
FLAG unique = FALSE;    /* TRUE, wenn aktueller Key einmalig sein soll */
short keyfile;          /* aktuelles Key-working-File */
short htfile;           /* aktuelles HTree-File */
short qtfile;           /* aktuelles QuadTree File */
short ctfile;           /* aktuelles CubicTree File */
short key_type;         /* Typ des aktuellen Schluessels */
short find_field = NONE; /* aktuelle Schluesselnummer */

/* Daten fuer Geometriearbeit */
HTACTIONPROC htaction;
QTACTIONPROC qtaction;

PAGE_NO cubparent[MAXTREELEVEL];
short cubslots[MAXTREELEVEL];
DB_ADDR NEAR treedba(0);

/* Arbeitspuffer */
INT buf[(2*MAXPAGESIZE+MAXPAGESIZE/2)/sizeof (INT)];

/* aktueller durchschrittener Pfad im Suchbaum */
PAGE_NO *parent = NULL;	/* Seitennummer */
short *slots = NULL;	/* Slotnummer */
short lvl;                     /* aktueller Level im Suchbaum */

/* aktueller Key-Eintrag */
KEY_SLOT key;
CT_KEY_SLOT2 GeoKey;

int FUNCTYPE key_init_index (int iIndex)
{
	return key_init (key_table + iIndex);
}

int FUNCTYPE key_init (register KEY_ENTRY *key_ptr)
{
	register FILE_ENTRY FAR *p;
	
#ifndef MSWIND
	if (parent == NULL) {
		parent = (PAGE_NO *)calloc(MAXLEVEL, sizeof(PAGE_NO));
		slots = (short *)calloc(MAXLEVEL, sizeof(short));
		if (!parent || !slots) return (db_error (S_NOMEMORY, KEY_INIT));
	}
#else // MSWIND
	if (parent == NULL) {
		TX_TRY(parent = new PAGE_NO [MAXLEVEL]);
		TX_TRY(slots = new short [MAXLEVEL]);
		if (!parent || !slots) {
			DELETE_OBJ(parent);
			return (db_error (S_NOMEMORY, KEY_INIT));
		}
	}
#endif
	p = &file_table[keyfile = key_ptr->kt_keyfile];
	if (p->ft_access == O_NOACC) return (dberr (S_ACCESS, KEY_INIT));
	htfile = qtfile = ctfile = -1;
	if (key_ptr->kt_treefile != -1) {
		switch (file_table[key_ptr->kt_treefile].ft_type) {
		case KT_HTREE:     htfile = key_ptr->kt_treefile; break;
		case KT_QTREE:     qtfile = key_ptr->kt_treefile; break;
		case KT_CTREE:     ctfile = key_ptr->kt_treefile; break;
		}
	}
	d = p->ft_slots;
	slot_len = p->ft_slsize;
	key_len = key_ptr->kt_len / sizeof (INT);
	unique = (key_ptr->kt_type == KT_UNIQUE || key_ptr->kt_type == KT_UNIQUE_ONLY);
	key_type = key_ptr->kt_field;
	working_file = keyfile;
	
	return (db_status = S_OKAY);
}

void FUNCTYPE key_deinit (void)
{
	working_file = NONE;
}

