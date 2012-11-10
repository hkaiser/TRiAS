/* Geometriezugriff fuer WINDOW- orientierte Objektsuche        */
/* File: QTWINDOW.C             last update: 11. Oktober 1989   */

#include "trias01p.hxx"
 
#include "syncdb.hxx"
#include "KeyInitWrapper.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define COMPARE 1
#define NOCOMP  0

// Position der Koordinaten in einem double[4]-Fenster
#define XMIN	0
#define XMAX	1
#define YMIN	2
#define YMAX	3

///////////////////////////////////////////////////////////////////////////////
// lokale Funktionen 
static HRESULT scan_no (DB_ADDR *pDBA, unsigned char filled, long (__cdecl *action)(struct db_addr *, ...), void *pData);
static HRESULT scan_cmp (double *win, DB_ADDR *pDBA, unsigned char filled, long (__cdecl *action)(struct db_addr *, ...), void *pData);
static HRESULT qtwalk(struct qtslot *node,union quadrant *qd, short level, short comp, struct db_addr *pdba, long (__cdecl *action)(struct db_addr *, ...), void *pData);

namespace {

// Interne Steuerinformationen 
struct QTCHGINFO  {
	short koord;
	short sign;
}; 

const QTCHGINFO qt_chginfo[] = { {0,  1}, {1,  1}, {0, -1}, {1, -1}, };

} // namespace 
 
extern "C" 
int FUNCTYPE EXPORT01 qwindow (
	HPROJECT hPr, WINDOW *window, long (*action)(DB_ADDR *, ...), long iKeyIndex)
{
	TX_ASSERT_POINTER(window, WINDOW);

double dWind[4] = { window -> x_min, window -> x_max, window -> y_min, window -> y_max };
HRESULT hr = QtWindow (hPr, dWind, action, iKeyIndex, NULL);

	if (FAILED(hr)) return hr; 

	if (S_OK == hr) 
		return db_status = S_OKAY;
	return db_error (S_NOTFOUND, QTWINDOW);		// nichts gefunden
}

HRESULT QtWindow (HPROJECT Pr, double *pdWindow, long (* action)(DB_ADDR *, ...), void *pData, long iKeyIndex)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

	TX_ASSERT(NULL != action);
	TX_ASSERT(iKeyIndex >= 0 && iKeyIndex < size_kt);

// Setzen der defaultwerte für den Schlüsselzugriff 
CKeyInitWrapper key (keyindex);

	if (!key.IsValid())
		return key.Result();

DB_ADDR treewdba(hPr);
QTSLOT noddat;		// Root
QTSLOT *data;
 
	if ((treewdba.file_no = qtfile) < 0)
		return dberr (S_NOKEY, QTWINDOW);
 
	treewdba.rec_no = ROOT_ADDR;
	if (tdb_read (&treewdba, (void **)&data) != S_OKAY) return (db_status);
	
	TX_ASSERT(NULL != data);
	noddat = *data;
 
// ab in den Baum 
QUADRANT rootqd = { 0, 0, MAXKOORD };    /* Wurzelbereich */

	return qtwalk (pdWindow, &noddat, &rootqd, 0, COMPARE, &treewdba, action, pData);
}
 
 
/* Iterative Baumsuchroutine */
static HRESULT qtwalk (
	double *win, QTSLOT *node, register QUADRANT *qd, short level, 
	FLAG comp, DB_ADDR *pDBA, long (__cdecl *action)(struct db_addr *, ...), void *pData)
{
QTSLOT noddat, *data;   	/* neuer Knoten, nebst Pointer */
register short i;               /* Laufvariable */
BOOL fFound = FALSE;
HRESULT hr = E_FAIL;

	qd->w.qd_len /= 2;      /* Kantenlaenge halbieren */
	for (i = 0; i < QDIM; ++i) {    /* fuer jeden Subwuerfel */
		pDBA -> rec_no = node->records[i];
	
	/* weiter im Baum */
		if (comp == NOCOMP ||
			(win[XMIN] <= qd->w.qd_x && win[YMIN] <= qd->w.qd_y && 
			 win[XMAX] > qd->w.qd_x+qd->w.qd_len && 
			 win[YMAX] > qd->w.qd_y+qd->w.qd_len)) 
		{
		/* Hyperwürfel vollständig in Window enthalten */
			if (pDBA->rec_no > 0) {
				if (tdb_read (pDBA, (void **)&data) != S_OKAY)
					return (db_status);
				noddat = *data;

				RETURN_FAILED_HRESULT(hr = qtwalk (win, &noddat, qd, level+1, NOCOMP, pDBA, action, pData));
				if (S_OK == hr) fFound = TRUE;		// propagate fFound

			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				found = TRUE;   /* mind. ein Objekt gefunden */
				RETURN_FAILED_HRESULT(hr = scan_no (pDBA, node->filled[i], action, pData));
			}
		}  
		else if (win[XMIN] <= qd->w.qd_x+qd->w.qd_len && 
				 win[YMIN] <= qd->w.qd_y+qd->w.qd_len && 
				 win[XMAX] > qd->w.qd_x && win[YMAX] > qd->w.qd_y) 
		{
		/* Hyperwürfel teilweise in Window enthalten */
			if (pDBA->rec_no > 0) {
				if (tdb_read (pDBA, (void **)&data) != S_OKAY)
					return (db_status);
				noddat = *data;
				
				RETURN_FAILED_HRESULT(hr = qtwalk (win, &noddat, qd, level+1, COMPARE, pDBA, action, pData));
				if (S_OK == hr) fFound = TRUE;		// propagate fFound

			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				RETURN_FAILED_HRESULT(hr = scan_cmp (win, pDBA, node->filled[i], action, pData));
				if (S_OK == hr)	fFound = TRUE;
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
	db_status = S_OKAY;

	return fFound ? S_OK : S_FALSE;
}
 
/* Abtasten eines Blattknotens (ohne Containertest) */
static HRESULT scan_no (
	DB_ADDR *pDBA, unsigned char filled, long (__cdecl *action)(struct db_addr *, ...), void *pData)
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

		if ((irc = (*action)(&dbadr, pData)) != S_OKAY)
			return HRESULT_FROM_ERRCODE(dberr ((short)irc, USER_FUNC));
		working_file = iWork;

		++ks;
	}

	db_status = S_OKAY;
 	return S_OK;
}
 
/* Abtasten eines Blattknotens (mit Containertest) */
static HRESULT scan_cmp (
	double *win, DB_ADDR *pDBA, unsigned char filled, 
	long (__cdecl *action)(struct db_addr *, ...), void *pData)
{
NODE *nd;
register QT_KEY_SLOT *ks;
register INT irc;
DB_ADDR dbadr(pDBA->db_no);
SUGGESTPAGE SE;
int iWork = working_file;
BOOL fFound = FALSE;

	memset (&SE, 0, sizeof(SUGGESTPAGE));
	for (unsigned int ui = 0; ui < filled; ui++) {      /* fuer jeden gefuellten Slot */
	// jedesmal nachladen, da in qtwact eine andere Page druntergeladen werden kann
		if (dio_get (-pDBA->rec_no, &nd, &SE) != S_OKAY) 
			return (db_status);
		ks = &((QT_KEY_SLOT *)nd->nd_slots)[ui];
                
		if (win[XMIN] <= ks->ks_key[0] && win[YMIN] <= ks->ks_key[1] &&
			win[XMAX] >= ks->ks_key[0] && win[YMAX] >= ks->ks_key[1]) 
		{
			found = TRUE;   /* mind. ein Objekt gefunden */
			dbadr.file_no = short(ks->ks_rec_no / MAXQTREC);
			dbadr.rec_no = ks->ks_rec_no % MAXQTREC;

			if ((irc = (*action)(&dbadr, pData)) != S_OKAY)
				return HRESULT_FROM_ERRCODE(dberr ((short)irc, USER_FUNC));
			working_file = iWork;
		}
		++ks;
	}

	db_status = S_OKAY;
	return fFound ? S_OK : S_FALSE;
}
