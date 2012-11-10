/* Geometriezugriff fuer WINDOW- orientierte Objektsuche        */
/* File: HTWINDOW.C             last update: 31. Juli 1989      */

#include "trias01p.hxx"

#include "syncdb.hxx"

#define COMPARE 1
#define NOCOMP  0
 
/* lokale Funktionen */
static int FUNCTYPE scan_no (HPROJECT hPr, long lPage, unsigned char filled);
static int FUNCTYPE scan_cmp (HPROJECT hPr, long lPage, unsigned char filled);

/* lokal-globale Variablen */
typedef long (__cdecl *HTWINDOWACTIONPROC)(DB_ADDR *, ...);

static HTWINDOWACTIONPROC NEAR htact;	/* soll fuer jedes Objekt im Window aufgerufen werden */
static WINDOW * NEAR w;       		/* vorgegebenes Window */
static FLAG NEAR found;

#ifdef unix
#ifdef vax
#define z8000
#endif
#endif

#ifdef z8000
static HYPERCUBE roothc;                /* Wurzelbereich */
#else
static HYPERCUBE NEAR roothc = { 0, 0, 0, 0, MAXKOORD };     /* Wurzelbereich */
#endif
 
/* Interne Steuerinformationen */
// static short index[HDIM] = { 0,  1,  3,  2,  7,  6,  4,  5,
//                             15, 14, 12, 13,  8,  9, 11, 10 };

struct ht_chginfo {
        short koord;
        short sign;
} NEAR ht_chginfo[HDIM] = {
                {0,  1}, {1,  1}, {0, -1}, {2,  1},
                {0,  1}, {1, -1}, {0, -1}, {3,  1},
                {0,  1}, {1,  1}, {0, -1}, {2, -1},
                {0,  1}, {1, -1}, {0, -1}, {3, -1}
};
 
/* F77 rufbare Routine, welche fuer jedes Objekt der Liste `rec' der
   Datenbasis, dessen Container mit dem vorgegebenen Window `window'
   in Beruehrung kommt, die vorgegebene Routine `action' aufruft
        Aufruf (Beispiel):
                INTEGER*4 KL            ! z.B. Kantenliste (s. AKS.FTN)
                INTEGER*4 WFELD(4)      ! Window
                EXTERNAL FKT            ! zu rufende Funktion
                INTEGER*2 IRC,WINDOW,FKT
                IRC=HWINDOW(KL,WFELD,FKT)
                        ! IRC = 0: Fehlerfrei
 
        Die Routine FKT wird folgendermassen aufgerufen:
                INTEGER*4 DBADDR(2)     ! DBADDR(1) - Filenummer
                                        ! DBADDR(2) - Recordnummer
                IRC=FKT(DBADDR)
                        ! IRC = 0: Fehlerfrei
*/
 
extern "C" int FUNCTYPE EXPORT01 hwindow (
		HPROJECT hPr, WINDOW *window, HTWINDOWACTIONPROC action, 
		register short keyindex)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

HTSLOT noddat;                  /* Root */
HTSLOT *data;
 
	htact = action;         /* abspeichern der Parameter */
	w = window;
 
	found = FALSE;          /* Voreinstllung: Kein Objekt gefunden */
 
 /* Setzen der defaultwerte für den Schlüsselzugriff */
	if (key_init (key_table+keyindex) != S_OKAY) return (db_status);

DB_ADDR htwdba(hPr);

	if ((htwdba.file_no = htfile) < 0)
		return (dberr (S_NOKEY, HTWINDOW));
 
	htwdba.rec_no = ROOT_ADDR;
	if (tdb_read (&htwdba, (void **)&data) != S_OKAY) return (db_status);
        noddat = *data;
 
/* ab in den Baum */
#ifdef z8000
	roothc.w.hc_w = roothc.w.hc_x = roothc.w.hc_y = roothc.w.hc_z = 0L;
	roothc.w.hc_len = MAXKOORD;
#endif
	if (htwalk (&noddat, &roothc, 0, COMPARE, &htwdba) != S_OKAY) return (db_status);
	working_file = NONE;
	if (found) return (db_status = S_OKAY);
	else return (db_error (S_NOTFOUND, HTWINDOW));
}
 
 
/* Iterative Baumsuchroutine */
int FUNCTYPE htwalk (HTSLOT *node, register HYPERCUBE *hc, short level, FLAG comp, DB_ADDR *pDBA)
// HTSLOT *node;           /* Baumknoten */
// register HYPERCUBE *hc; /* aktueller Hyperwuerfel */
// short level;            /* aktuelles Verschachtelungsniveau */
// FLAG comp; /* NOCOMP:  Hyperwuerfel ist als Ganzes interessant,
//              COMPARE: jeder untergeordnete Hyperwuerfel muss getestet werden */
{
HTSLOT noddat, *data;   /* neuer Knoten, nebst Pointer */
register short i;               /* Laufvariable */
 
		hc->w.hc_len /= 2;      /* Kantenlaenge halbieren */
		for (i = 0; i < HDIM; ++i) {    /* fuer jeden Subwuerfel */
		register WINDOW *win;
 
		pDBA->rec_no = node->records[i];

	/* weiter im Baum */
		if (comp == NOCOMP
		 || ((win = w)->x_min <= hc->w.hc_x
				&& win->y_min <= hc->w.hc_z
				&& win->x_max > hc->w.hc_w+hc->w.hc_len
				&& win->y_max > hc->w.hc_y+hc->w.hc_len)) 
		{
		/* Hyperwurfel vollständig in Window enthalten */
			if (pDBA->rec_no > 0) {
				if (tdb_read (pDBA, (void **)&data) != S_OKAY)
					return (db_status);
				noddat = *data;
				if (htwalk (&noddat, hc, level+1, NOCOMP, pDBA) != S_OKAY)
					return (db_status);
			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				found = TRUE;   /* mind. ein Objekt gefunden */
				if (scan_no (pDBA->db_no, -pDBA->rec_no, node->filled[i]) != S_OKAY)
						return (db_status);
			}
		} else if (win->x_min <= hc->w.hc_x+hc->w.hc_len
					&& win->y_min <= hc->w.hc_z+hc->w.hc_len
					&& win->x_max > hc->w.hc_w
					&& win->y_max > hc->w.hc_y) 
		{
		/* Hyperwuerfel teilweise in Window enthalten */
			if (pDBA->rec_no > 0) {
				if (tdb_read (pDBA, (void **)&data) != S_OKAY)
					return (db_status);
				noddat = *data;
				if (htwalk (&noddat, hc, level+1, COMPARE, pDBA) != S_OKAY)
					return (db_status);
			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				if (scan_cmp (pDBA->db_no, -pDBA->rec_no, node->filled[i]) != S_OKAY)
					return (db_status);
			}
		}
		{
		/* naechsten Hyperwuerfel berechnen */
		register struct ht_chginfo *ci_p;
 
			if ((ci_p = &ht_chginfo[i])->sign > 0)
				hc->feld[ci_p->koord] += hc->feld[4];
			else
				hc->feld[ci_p->koord] -= hc->feld[4];
			}
		}
		hc->w.hc_len *= 2;      /* Kantenlaenge des Wuerfels wiederherstellen */
 
return (db_status = S_OKAY);
}
 
 
/* Abtasten eines Blattknotens (ohne Containertest) */
static int FUNCTYPE scan_no (HPROJECT hPr, long lPage, register unsigned char filled)
{
NODE FAR *nd;
register HT_KEY_SLOT *ks;
register INT irc;
DB_ADDR dbadr(hPr);
SUGGESTPAGE SP;
int iWork = working_file;

	memset (&SP, 0, sizeof(SUGGESTPAGE));
	for (unsigned int ui = 0; ui < filled; ui++) {      /* fuer jeden gefuellten Slot */

		if (dio_get (lPage, &nd, &SP) != S_OKAY) 
			return (db_status);
		ks = &((HT_KEY_SLOT *)nd->nd_slots)[ui];

		dbadr.file_no = short(ks->ks_rec_no / MAXHTREC);
		dbadr.rec_no = ks->ks_rec_no % MAXHTREC;

		if ((irc = (*htact)(&dbadr, w)) != S_OKAY)
			return (dberr ((short)irc, USER_FUNC));
		working_file = iWork;

		++ks;
	}
 
return (db_status = S_OKAY);
}
 
 
/* Abtasten eines Blattknotens (mit Containertest) */
static int FUNCTYPE scan_cmp (HPROJECT hPr, long lPage, register unsigned char filled)
{
NODE FAR *nd;
register HT_KEY_SLOT *ks;
register INT irc;
DB_ADDR dbadr(hPr);
register WINDOW *win = w;
SUGGESTPAGE SP;
int iWork = working_file;

	memset (&SP, 0, sizeof(SUGGESTPAGE));
	for (unsigned int ui = 0; ui < filled; ui++)       /* fuer jeden gefuellten Slot */
	{
		if (dio_get (lPage, &nd, &SP) != S_OKAY) 
			return (db_status);
		ks = &((HT_KEY_SLOT *)nd->nd_slots)[ui];

		if (win->x_min <= ks->ks_key[1] && 
			win->y_min <= ks->ks_key[3] && 
			win->x_max >= ks->ks_key[0] &&
			win->y_max >= ks->ks_key[2]) 
		{
			found = TRUE;   /* mind. ein Objekt gefunden */
                        
			dbadr.file_no = short(ks->ks_rec_no / MAXHTREC);
			dbadr.rec_no = ks->ks_rec_no % MAXHTREC;
                        
			if ((irc = (*htact)(&dbadr, win)) != S_OKAY)
				return (dberr ((short)irc, USER_FUNC));
			working_file = iWork;
		}
		++ks;
	}
 
return (db_status = S_OKAY);
}

