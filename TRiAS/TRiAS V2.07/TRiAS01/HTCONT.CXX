/* Routine zur Berechnung des Containers des HT-Baumes          */
/* File: HTCONT.C                                               */

#include "trias01p.hxx"
#include "syncdb.hxx"
 
/* lokal-globale Variablen */
HYPERCUBE NEAR roothc;
 
static struct chg_info {
        short koord;
        short sign;
} NEAR chg_info[HDIM] = {
        {0,  1}, {1,  1}, {0, -1}, {2,  1},
        {0,  1}, {1, -1}, {0, -1}, {3,  1},
        {0,  1}, {1,  1}, {0, -1}, {2, -1},
        {0,  1}, {1, -1}, {0, -1}, {3, -1},
};

// static functions
static int FUNCTYPE ht_contwalk (HTSLOT *node, HYPERCUBE *hc, CONTAINER *c_p);
static int FUNCTYPE ht_page (CONTAINER *c_p, char filled);

extern "C" 
int FUNCTYPE EXPORT01 htcont (HPROJECT hPr, CONTAINER *cont, register short keyindex)
// CONTAINER *cont;                /* zu bestimmender Container */
// register short keyindex;        /* Index in keytabelle */
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

HTSLOT noddat;                  /* Root */
HTSLOT *data;
 
/* Setzen der defaultwerte fuer den Schluesselzugriff */
	if (key_init (key_table+keyindex) != S_OKAY) 
		return (db_status);
	if ((treedba.file_no = htfile) < 0)
		return (dberr (S_NOKEY, HTCONT));
 
	treedba.db_no = hPr;		// auf aktives Projekt setzen
	treedba.rec_no = ROOT_ADDR;
	if (tdb_read (&treedba, (void **)&data) != S_OKAY) return (db_status);
	
	noddat = *data;
 
/* ab in den Baum */
	roothc.w.hc_w =
	roothc.w.hc_x =
	roothc.w.hc_y =
	roothc.w.hc_z = 0L;
	roothc.w.hc_len = MAXKOORD;

	if (ht_contwalk (&noddat, &roothc, cont) != S_OKAY) 
		return (db_status);
	
	working_file = NONE;
 
return (db_status = S_OKAY);
}
 
 
/* Iterative Baumsuchroutine */
static int FUNCTYPE ht_contwalk (HTSLOT *node, register HYPERCUBE *hc, 
				 register CONTAINER *c_p)
// HTSLOT *node;           /* Baumknoten */
// register HYPERCUBE *hc; /* aktueller Hyperwuerfel */
// register CONTAINER *c_p;
{
HTSLOT noddat, FAR *data;	 /* neuer Knoten, nebst Pointer */
register short i;               /* Laufvariable */
 
	hc->w.hc_len /= 2;      /* Kantenlaenge halbieren */

long lLen = hc->w.hc_len;

	for (i = 0; i < HDIM; ++i) {    /* fuer jeden Subwuerfel */
		treedba.rec_no = node->records[i];

		if (c_p->x_min > hc->w.hc_w || c_p->x_max < (hc->w.hc_x + lLen) ||
			c_p->y_min > hc->w.hc_y || c_p->y_max < (hc->w.hc_z + lLen)) 
		{
		/* wenn Container korrigiert werden muss */ 
			if (treedba.rec_no > 0) {
			/* weiter im Baum */
				if (tdb_read (&treedba, (void **)&data) != S_OKAY)
					return (db_status);
				noddat = *data;
				if (ht_contwalk (&noddat, hc, c_p) != S_OKAY)
					return (db_status);
			} else if (treedba.rec_no < 0) { 
			/* Blattknoten erreicht */
				if (ht_page (c_p, node->filled[i]) != S_OKAY)
					return (db_status);
			}
		}
		{
		/* nächsten Hyperwürfel berechnen */
		register struct chg_info *ci_p;
 
			if ((ci_p = &chg_info[i])->sign > 0)
				hc->feld[ci_p->koord] += hc->feld[4];
			else
				hc->feld[ci_p->koord] -= hc->feld[4];
		}
	} /*for*/
	
	/* Kantenlaenge des Wuerfels wiederherstellen */
		hc->w.hc_len *= 2;
 
return (db_status = S_OKAY);
}
 
 
/* Abtasten eines Blattknotens */
static int FUNCTYPE ht_page (register CONTAINER *c_p, char filled) 
{
NODE FAR *nd;
register HT_KEY_SLOT FAR *ks;
 
	if (dio_get (-treedba.rec_no, &nd) != S_OKAY) return (db_status);
	ks = (HT_KEY_SLOT FAR *)nd->nd_slots;
	while (filled--) {
	/* fuer jeden Eintrag im Knoten */
		if (ks->ks_key[0] < c_p->x_min) c_p->x_min = ks->ks_key[0]; 
		if (ks->ks_key[2] < c_p->y_min) c_p->y_min = ks->ks_key[2]; 
		if (ks->ks_key[1] > c_p->x_max) c_p->x_max = ks->ks_key[1]; 
		if (ks->ks_key[3] > c_p->y_max) c_p->y_max = ks->ks_key[3]; 
		++ks;
	}
 
return (db_status = S_OKAY);
}
 
