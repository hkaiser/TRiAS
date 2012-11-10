// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/25/1998 02:34:12 PM (first version: 31. Juli 1989)
//
// @doc
// @module HtWindow.cpp | Geometriezugriff für WINDOW- orientierte Objektsuche

#include "trias01p.hxx"

#include "syncdb.hxx"
#include "KeyInitWrapper.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/* lokale Funktionen */
static HRESULT ht_scan_no (double *pdWindow, HPROJECT hPr, long lPage, unsigned char filled, HTWINDOWACTIONPROC action, UINT_PTR dwData);
static HRESULT ht_scan_cmp (double *pdWindow, HPROJECT hPr, long lPage, unsigned char filled, HTWINDOWACTIONPROC action, UINT_PTR dwData);
static HRESULT ht_walk (double *pdWindow, HTSLOT *node, HYPERCUBE *hc, short level, FLAG comp, DB_ADDR *pDBA, HTWINDOWACTIONPROC action, UINT_PTR dwData);

namespace {

/* Interne Steuerinformationen */
struct HTCHGINFO {
	short koord;
	short sign;
};

HTCHGINFO ht_chginfo[] = {
	{0,  1}, {1,  1}, {0, -1}, {2,	1},
	{0,  1}, {1, -1}, {0, -1}, {3,	1},
	{0,  1}, {1,  1}, {0, -1}, {2, -1},
	{0,  1}, {1, -1}, {0, -1}, {3, -1}
};

} // namespace 

HRESULT HtWindow (
	HPROJECT hPr, double *pdWindow, HTWINDOWACTIONPROC action, 
	long iKeyIndex, UINT_PTR dwData)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

// Setzen der Defaultwerte für den Schlüsselzugriff
CKeyInitWrapper key (iKeyIndex);

	if (!key.IsValid())
		return key.Result();

DB_ADDR htwdba(hPr);
HTSLOT noddat;		// Root 
HTSLOT *data;

	if ((htwdba.file_no = htfile) < 0)
		return (dberr (S_NOKEY, HTWINDOW));
 
	htwdba.rec_no = ROOT_ADDR;
	if (tdb_read (&htwdba, (void **)&data) != S_OKAY) return (db_status);
		noddat = *data;
 
// ab in den Baum 
static HYPERCUBE roothc = { 0, 0, 0, 0, MAXKOORD };	 /* Wurzelbereich */

	return ht_walk (pdWindow, &noddat, &roothc, 0, COMPARE, &htwdba, action, dwData);
}
 
#if defined(_USE_LEGACY_CODE) 
extern "C" 
int FUNCTYPE EXPORT01 hwindow (
		HPROJECT hPr, WINDOW *window, HTWINDOWACTIONPROC action, 
		register short iKeyIndex)
{
	TX_ASSERT_POINTER(window, WINDOW);

double dWind[4] = { window -> x_min, window -> x_max, window -> y_min, window -> y_max };
HRESULT hr = HtWindow (hPr, dWind, action, iKeyIndex, NULL);

	if (FAILED(hr)) return hr; 

	if (S_OK == hr) 
		return db_status = S_OKAY;
	return db_error (S_NOTFOUND, QTWINDOW); 	// nichts gefunden
}
#endif // _USE_LEGACY_CODE
 
/* Iterative Baumsuchroutine */
static HRESULT ht_walk (
	double *win, HTSLOT *node, HYPERCUBE *hc, short level, 
	FLAG comp, DB_ADDR *pDBA, HTWINDOWACTIONPROC action, UINT_PTR dwData)
{
HTSLOT noddat, *data;	/* neuer Knoten, nebst Pointer */
HRESULT hr = E_FAIL;
BOOL fFound = FALSE;
ErrCode RC;
 
	hc->w.hc_len /= 2;		/* Kantenlänge halbieren */
	for (int i = 0; i < HDIM; ++i) {	/* für jeden Subwürfel */
		pDBA->rec_no = node->records[i];

	/* weiter im Baum */
		if (comp == NOCOMP || 
			(win[XMIN] <= hc->w.hc_x && win[YMIN] <= hc->w.hc_z	&& 
			 win[XMAX] > hc->w.hc_w+hc->w.hc_len && 
			 win[YMAX] > hc->w.hc_y+hc->w.hc_len)) 
		{
		/* Hyperwurfel vollständig in Window enthalten */
			if (pDBA->rec_no > 0) {
				DBASSERTHR(tdb_read (pDBA, (void **)&data));
				noddat = *data;

				RETURN_FAILED_HRESULT(hr = ht_walk (win, &noddat, hc, level+1, NOCOMP, pDBA, action, dwData));
				if (S_OK == hr) fFound = TRUE;		// propagate fFound

			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				fFound = TRUE;	/* mind. ein Objekt gefunden */
				RETURN_FAILED_HRESULT(ht_scan_no (win, pDBA->db_no, -pDBA->rec_no, node->filled[i], action, dwData));
			}
		} 
		else if (win[XMIN] <= hc->w.hc_x+hc->w.hc_len && 
				 win[YMIN] <= hc->w.hc_z+hc->w.hc_len &&
				 win[XMAX] > hc->w.hc_w && win[YMAX] > hc->w.hc_y) 
		{
		/* Hyperwuerfel teilweise in Window enthalten */
			if (pDBA->rec_no > 0) {
				DBASSERTHR(tdb_read (pDBA, (void **)&data));
				noddat = *data;

				RETURN_FAILED_HRESULT(hr = ht_walk (win, &noddat, hc, level+1, COMPARE, pDBA, action, dwData));
				if (S_OK == hr) fFound = TRUE;		// propagate fFound

			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				RETURN_FAILED_HRESULT(hr = ht_scan_cmp (win, pDBA->db_no, -pDBA->rec_no, node->filled[i], action, dwData));
				if (S_OK == hr) fFound = TRUE;		// propagate fFound
			}
		}
		{
		/* naechsten Hyperwuerfel berechnen */
		register HTCHGINFO *ci_p;
 
			if ((ci_p = &ht_chginfo[i])->sign > 0)
				hc->feld[ci_p->koord] += hc->feld[4];
			else
				hc->feld[ci_p->koord] -= hc->feld[4];
		}
	}
	hc->w.hc_len *= 2;		/* Kantenlaenge des Wuerfels wiederherstellen */
	db_status = S_OKAY;

	return fFound ? S_OK : S_FALSE;
}
 
/* Abtasten eines Blattknotens (ohne Containertest) */
static HRESULT ht_scan_no (
	double *win, HPROJECT hPr, long lPage, unsigned char filled, HTWINDOWACTIONPROC action, UINT_PTR dwData)
{
long irc;
DB_ADDR dbadr(hPr);
SUGGESTPAGE SP;
int iWork = working_file;
ErrCode RC;

	memset (&SP, 0, sizeof(SUGGESTPAGE));
	for (unsigned int ui = 0; ui < filled; ui++) {		/* für jeden gefüllten Slot */
	NODE *nd;

		DBASSERTHR(dio_get (lPage, &nd, &SP)) ;
	
	HT_KEY_SLOT *ks = &((HT_KEY_SLOT *)nd->nd_slots)[ui];

		dbadr.file_no = short(ks->ks_rec_no / MAXHTREC);
		dbadr.rec_no = ks->ks_rec_no % MAXHTREC;

		if ((irc = (*action)(&dbadr, win, dwData)) != S_OKAY)
			return HRESULT_FROM_ERRCODE(dberr (irc, USER_FUNC));
		working_file = iWork;
	}
	db_status = S_OKAY;
	return S_OK;
}
 
/* Abtasten eines Blattknotens (mit Containertest) */
static HRESULT ht_scan_cmp (
	double *win, HPROJECT hPr, long lPage, unsigned char filled,
	HTWINDOWACTIONPROC action, UINT_PTR dwData)
{
DB_ADDR dbadr(hPr);
SUGGESTPAGE SP;
int iWork = working_file;
BOOL fFound = FALSE;
ErrCode RC;

	memset (&SP, 0, sizeof(SUGGESTPAGE));
	for (unsigned int ui = 0; ui < filled; ui++)	   /* für jeden gefüllten Slot */
	{
	NODE *nd;

		DBASSERTHR(dio_get (lPage, &nd, &SP)) ;
	
	HT_KEY_SLOT *ks = &((HT_KEY_SLOT *)nd->nd_slots)[ui];

		if (win[XMIN] <= ks->ks_key[1] && win[YMIN] <= ks->ks_key[3] && 
			win[XMAX] >= ks->ks_key[0] && win[YMAX] >= ks->ks_key[2]) 
		{
			fFound = TRUE;	/* mind. ein Objekt gefunden */
						
			dbadr.file_no = short(ks->ks_rec_no / MAXHTREC);
			dbadr.rec_no = ks->ks_rec_no % MAXHTREC;
						
		long irc = (*action)(&dbadr, win, dwData);

			if (S_OKAY != irc)
				return HRESULT_FROM_ERRCODE(dberr (irc, USER_FUNC));
			working_file = iWork;
		}
	}

	db_status = S_OKAY;
	return fFound ? S_OK : S_FALSE;
}

