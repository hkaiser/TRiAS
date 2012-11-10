/* Geometriezugriff fuer WINDOW- orientierte Objektsuche        */
/* File: QTWINDOW.C             last update: 11. Oktober 1989   */

#include "trias01p.hxx"
 
#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define COMPARE 1
#define NOCOMP  0
 
/* lokale Funktionen */
static int FUNCTYPE scan_no (DB_ADDR *pDBA, unsigned char filled);
static int FUNCTYPE scan_cmp (DB_ADDR *pDBA, unsigned char filled);

/* lokal-globale Variablen */
static long (*qtwact)(DB_ADDR *, ...); /* soll fuer jedes Objekt im Window aufgerufen werden */
static WINDOW *w;       /* vorgegebenes Window */
static FLAG found;
 
#ifdef unix
#ifdef vax
#define z8000
#endif
#endif

#ifdef z8000
static QUADRANT rootqd;         /* Wurzelbereich */
#endif
#ifndef z8000
static QUADRANT NEAR rootqd = { 0, 0, MAXKOORD };    /* Wurzelbereich */
#endif
 
/* Interne Steuerinformationen */
/*
static short index[QDIM] = { 0,  1,  3,  2, };
*/
struct qt_chginfo {
        short koord;
        short sign;
} NEAR qt_chginfo[QDIM] = {
                {0,  1}, {1,  1}, {0, -1}, {1, -1},
};
 
/* F77 rufbare Routine, welche fuer jedes Objekt der Liste `rec' der
   Datenbasis, dessen Koordinaten im vorgegebenen Window `window'
   liegen, die vorgegebene Routine `action' aufruft
        Aufruf (Beispiel):
                INTEGER*4 KL            ! z.B. Kantenliste (s. AKS.FTN)
                INTEGER*4 WFELD(4)      ! Window
                EXTERNAL FKT            ! zu rufende Funktion
                INTEGER*2 IRC,WINDOW,FKT
                IRC=QWINDOW(KL,WFELD,FKT)
                        ! IRC = 0: Fehlerfrei
 
        Die Routine FKT wird folgendermassen aufgerufen:
                INTEGER*4 DBADDR(2)     ! DBADDR(1) - Filenummer
                                        ! DBADDR(2) - Recordnummer
                IRC=FKT(DBADDR)
                        ! IRC = 0: Fehlerfrei
*/
 
extern "C" 
int FUNCTYPE EXPORT01 qwindow (
	HPROJECT hPr, WINDOW *window, long (*action)(DB_ADDR *, ...), 
	register short keyindex)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

	TX_ASSERT(action);
	TX_ASSERT_POINTER(window, WINDOW);
	TX_ASSERT(keyindex >= 0 && keyindex < size_kt);

QTSLOT noddat;                  /* Root */
QTSLOT *data;
 
	qtwact = action;	/* abspeichern der Parameter */
	w = window;
 
	found = FALSE;          /* Voreinstllung: Kein Objekt gefunden */
 
/* Setzen der defaultwerte fuer den Schluesselzugriff */
	if (key_init (key_table+keyindex) != S_OKAY) return (db_status);

DB_ADDR treewdba(hPr);

	if ((treewdba.file_no = qtfile) < 0)
		return (dberr (S_NOKEY, QTWINDOW));
 
	treewdba.rec_no = ROOT_ADDR;
	if (tdb_read (&treewdba, (void **)&data) != S_OKAY) return (db_status);
	
	TX_ASSERT(data);
	noddat = *data;
 
/* ab in den Baum */
#ifdef z8000
	rootqd.w.qd_x = rootqd.w.qd_y = 0L;
	rootqd.w.qd_len = MAXKOORD;
#endif
	if (qtwalk (&noddat, &rootqd, 0, COMPARE, &treewdba) != S_OKAY) return (db_status);
        
	working_file = NONE;
	if (found) return (db_status = S_OKAY);
	else return (db_error (S_NOTFOUND, QTWINDOW));
}
 
 
/* Iterative Baumsuchroutine */
int FUNCTYPE qtwalk (QTSLOT *node, register QUADRANT *qd, short level, FLAG comp, DB_ADDR *pDBA)
// QTSLOT *node;           /* Baumknoten */
// register QUADRANT *qd;  /* aktueller Hyperwuerfel */
// short level;            /* aktuelles Verschachtelungsniveau */
// FLAG comp; /* NOCOMP:  Hyperwuerfel ist als Ganzes interessant,
//             COMPARE: jeder untergeordnete Hyperwuerfel muss getestet werden */
{
QTSLOT noddat, *data;   	/* neuer Knoten, nebst Pointer */
register short i;               /* Laufvariable */
register WINDOW *win = w;       /* Suchwindow */
 
	qd->w.qd_len /= 2;      /* Kantenlaenge halbieren */
	for (i = 0; i < QDIM; ++i) {    /* fuer jeden Subwuerfel */
		pDBA -> rec_no = node->records[i];
	
	/* weiter im Baum */
		if (comp == NOCOMP
			|| (win->x_min <= qd->w.qd_x
			&& win->y_min <= qd->w.qd_y
			&& win->x_max > qd->w.qd_x+qd->w.qd_len
			&& win->y_max > qd->w.qd_y+qd->w.qd_len)) 
		{
		/* Hyperwürfel vollständig in Window enthalten */
			if (pDBA->rec_no > 0) {
				if (tdb_read (pDBA, (void **)&data) != S_OKAY)
					return (db_status);
				noddat = *data;
				if (qtwalk (&noddat, qd, level+1, NOCOMP, pDBA) != S_OKAY)
					return (db_status);
			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				found = TRUE;   /* mind. ein Objekt gefunden */
				if (scan_no (pDBA, node->filled[i]) != S_OKAY)
					return (db_status);
			}
		} else if (win->x_min <= qd->w.qd_x+qd->w.qd_len
					&& win->y_min <= qd->w.qd_y+qd->w.qd_len
					&& win->x_max > qd->w.qd_x
					&& win->y_max > qd->w.qd_y) 
		{
		/* Hyperwürfel teilweise in Window enthalten */
			if (pDBA->rec_no > 0) {
				if (tdb_read (pDBA, (void **)&data) != S_OKAY)
					return (db_status);
				noddat = *data;
				if (qtwalk (&noddat, qd, level+1, COMPARE, pDBA) != S_OKAY)
					return (db_status);
			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				if (scan_cmp (pDBA, node->filled[i]) != S_OKAY)
					return (db_status);
			}
		}
		{
		/* nächsten Hyperwürfel berechnen */
		register struct qt_chginfo *ci_p;
 
			if ((ci_p = &qt_chginfo[i])->sign > 0)
				qd->feld[ci_p->koord] += qd->feld[2];
			else
				qd->feld[ci_p->koord] -= qd->feld[2];
		}
	}
	qd->w.qd_len *= 2;      /* Kantenlaenge des Wuerfels wiederherstellen */
 
return (db_status = S_OKAY);
}
 
 
/* Abtasten eines Blattknotens (ohne Containertest) */
static int FUNCTYPE scan_no (DB_ADDR *pDBA, register unsigned char filled)
{
NODE *nd;
register QT_KEY_SLOT *ks;
register INT irc;
DB_ADDR dbadr(pDBA->db_no);
SUGGESTPAGE SE;
int iWork = working_file;

	memset (&SE, 0, sizeof(SUGGESTPAGE));
	for (unsigned int ui = 0; ui < filled; ui++) {      /* fuer jeden gefuellten Slot */
	// jedesmal nachladen, da in qtwact eine andere Page druntergeladen werden kann

		if (dio_get (-pDBA->rec_no, &nd, &SE) != S_OKAY) 
			return (db_status);
		ks = &((QT_KEY_SLOT *)nd->nd_slots)[ui];

		dbadr.file_no = short(ks->ks_rec_no / MAXQTREC);
		dbadr.rec_no = ks->ks_rec_no % MAXQTREC;

		if ((irc = (*qtwact)(&dbadr)) != S_OKAY)
			return (dberr ((short)irc, USER_FUNC));
		working_file = iWork;

		++ks;
	}
 
return (db_status = S_OKAY);
}
 
 
/* Abtasten eines Blattknotens (mit Containertest) */
static int FUNCTYPE scan_cmp (DB_ADDR *pDBA, register unsigned char filled)
{
NODE *nd;
register QT_KEY_SLOT *ks;
register INT irc;
DB_ADDR dbadr(pDBA->db_no);
register WINDOW *win = w;
SUGGESTPAGE SE;
int iWork = working_file;

	memset (&SE, 0, sizeof(SUGGESTPAGE));
	for (unsigned int ui = 0; ui < filled; ui++) {      /* fuer jeden gefuellten Slot */
	// jedesmal nachladen, da in qtwact eine andere Page druntergeladen werden kann
		if (dio_get (-pDBA->rec_no, &nd, &SE) != S_OKAY) 
			return (db_status);
		ks = &((QT_KEY_SLOT *)nd->nd_slots)[ui];
                
		if (win->x_min <= ks->ks_key[0] &&
			win->y_min <= ks->ks_key[1] &&
			win->x_max >= ks->ks_key[0] &&
			win->y_max >= ks->ks_key[1]) 
		{
			found = TRUE;   /* mind. ein Objekt gefunden */
			dbadr.file_no = short(ks->ks_rec_no / MAXQTREC);
			dbadr.rec_no = ks->ks_rec_no % MAXQTREC;

			if ((irc = (*qtwact)(&dbadr)) != S_OKAY)
				return (dberr ((short)irc, USER_FUNC));
			working_file = iWork;
		}
		++ks;
	}
 
return (db_status = S_OKAY);
}
