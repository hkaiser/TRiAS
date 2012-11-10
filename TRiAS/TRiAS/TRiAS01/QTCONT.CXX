/* Routine zur Berechnung des Containers der Punktobjekte       */
/* File: QTCONT.C                                               */

#include "trias01p.hxx"
 
#include "syncdb.hxx"

/* lokal-globale Variablen */
QUADRANT NEAR rootqd;
 
static struct chg_info {
        short koord;
        short sign;
} NEAR chg_info[QDIM] = {
        {0,  1}, {1,  1}, {0, -1}, {1, -1},
};
 
// static functions
static int FUNCTYPE qt_contwalk (QTSLOT *node, QUADRANT *qd, CONTAINER *c_p);
static int FUNCTYPE qt_page (CONTAINER *c_p, unsigned char filled);

extern "C" int FUNCTYPE EXPORT01 qtcont (HPROJECT hPr, CONTAINER *cont, register short keyindex)
// CONTAINER *cont;                /* zu bestimmender Container */
// register short keyindex;        /* Index in Keytabelle */
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

QTSLOT noddat;                  /* Root */
QTSLOT FAR *data;
 
/* Setzen der defaultwerte fuer den Schluesselzugriff */
	if (key_init (key_table+keyindex) != S_OKAY) return (db_status);
	if ((treedba.file_no = qtfile) < 0)
		return (dberr (S_NOKEY, QTCONT));

	treedba.db_no = hPr;		// auf aktives Projekt setzen 
	treedba.rec_no = ROOT_ADDR;
	if (tdb_read (&treedba, (void **)&data) != S_OKAY) return (db_status);
	
	noddat = *data;
 
/* ab in den Baum */
	rootqd.w.qd_x =
	rootqd.w.qd_y = 0L;
	rootqd.w.qd_len = MAXKOORD;

	if (qt_contwalk (&noddat, &rootqd, cont) != S_OKAY) 
		return (db_status);
	working_file = NONE;
 
return (db_status = S_OKAY);
}
 
 
/* Iterative Baumsuchroutine */
static int FUNCTYPE qt_contwalk (QTSLOT *node, register QUADRANT *qd, 
				 register CONTAINER *c_p)
// QTSLOT *node;           /* Baumknoten */
// register QUADRANT *qd;  /* aktueller Hyperwuerfel */
// register CONTAINER *c_p;
{
QTSLOT noddat, FAR *data;	 /* neuer Knoten, nebst Pointer */
register short i;               /* Laufvariable */
 
	qd->w.qd_len /= 2;      /* Kantenlaenge halbieren */

long lLen = qd->w.qd_len;

	for (i = 0; i < QDIM; ++i) {    /* fuer jeden Subwuerfel */
		treedba.rec_no = node->records[i];

		if (c_p->x_min > qd->w.qd_x || c_p->x_max < (qd->w.qd_x + lLen) ||
			c_p->y_min > qd->w.qd_y || c_p->y_max < (qd->w.qd_y + lLen))
		{
		/* wenn Container korrigiert werden muss */ 
			if (treedba.rec_no > 0) {
			/* weiter im Baum */
				if (tdb_read (&treedba, (void **)&data) != S_OKAY)
					return (db_status);
				noddat = *data;
				if (qt_contwalk (&noddat, qd, c_p) != S_OKAY)
					return (db_status);
			} else if (treedba.rec_no < 0) {        /* Blattknoten erreicht */
				if (qt_page (c_p, (unsigned char)node->filled[i]) != S_OKAY)
					return (db_status);
			}
		}
		{
		/* naechsten Hyperwuerfel berechnen */
		register struct chg_info *ci_p;
 
			if ((ci_p = &chg_info[i])->sign > 0)
				qd->feld[ci_p->koord] += qd->feld[2];
			else
				qd->feld[ci_p->koord] -= qd->feld[2];
		}
	} /*for*/

/* Kantenlaenge des Wuerfels wiederherstellen */
	qd->w.qd_len *= 2;      
 
return (db_status = S_OKAY);
}

//#if _MSC_VER == 1200
//#pragma optimize ("", off)
//#else
//#pragma MSG("Ist dieser compilerbug noch da ?")
//#endif // _MSC_VER == 1200

/* Abtasten eines Blattknotens */
static int FUNCTYPE qt_page (register CONTAINER *c_p, unsigned char filled)
{
NODE FAR *nd;
register QT_KEY_SLOT FAR *ks;
 
	if (dio_get (-treedba.rec_no, &nd) != S_OKAY) return (db_status);

	ks = (QT_KEY_SLOT FAR *)nd->nd_slots;
	while (filled--) {
	/* fuer jeden Eintrag im Knoten */
		if (ks->ks_key[0] < c_p->x_min) c_p->x_min = ks->ks_key[0]; 
		if (ks->ks_key[1] < c_p->y_min) c_p->y_min = ks->ks_key[1]; 
		if (ks->ks_key[0] > c_p->x_max) c_p->x_max = ks->ks_key[0]; 
		if (ks->ks_key[1] > c_p->y_max) c_p->y_max = ks->ks_key[1]; 
		++ks;
	}
 
return (db_status = S_OKAY);
}
 
