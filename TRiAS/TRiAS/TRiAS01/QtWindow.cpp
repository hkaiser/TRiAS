// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/25/1998 02:21:31 PM (first version: 11. Oktober 1989)
//
// @doc
// @module QtWindow.cpp | Geometriezugriff für WINDOW- orientierte Objektsuche

#include "trias01p.hxx"
 
#include "syncdb.hxx"
#include "KeyInitWrapper.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// lokale Funktionen 
static HRESULT qt_scan_no (double *win, DB_ADDR *pDBA, unsigned char filled, QTWINDOWACTIONPROC action, UINT_PTR dwData);
static HRESULT qt_scan_cmp (double *win, DB_ADDR *pDBA, unsigned char filled, QTWINDOWACTIONPROC action, UINT_PTR dwData);
static HRESULT qt_walk (double *win, struct qtslot *node, union quadrant *qd, short level, FLAG comp, struct db_addr *pdba, QTWINDOWACTIONPROC action, UINT_PTR dwData);

namespace {

// Interne Steuerinformationen 
struct QTCHGINFO  {
	short koord;
	short sign;
}; 

const QTCHGINFO qt_chginfo[] = { {0,  1}, {1,  1}, {0, -1}, {1, -1}, };

} // namespace 

HRESULT QtWindow (
	HPROJECT hPr, double *pdWindow, QTWINDOWACTIONPROC action, 
	long iKeyIndex, UINT_PTR dwData)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

	TX_ASSERT(NULL != action);

// Setzen der Defaultwerte für den Schlüsselzugriff 
CKeyInitWrapper key (iKeyIndex);

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
static QUADRANT rootqd = { 0, 0, MAXKOORD };	 /* Wurzelbereich */

	return qt_walk (pdWindow, &noddat, &rootqd, 0, COMPARE, &treewdba, action, dwData);
}
 
#if defined(_USE_LEGACY_CODE) 
extern "C" 
int FUNCTYPE EXPORT01 qwindow (
	HPROJECT hPr, WINDOW *window, QTWINDOWACTIONPROC action, short iKeyIndex)
{
	TX_ASSERT_POINTER(window, WINDOW);

double dWind[4] = { window -> x_min, window -> x_max, window -> y_min, window -> y_max };
HRESULT hr = QtWindow (hPr, dWind, action, iKeyIndex, NULL);

	if (FAILED(hr)) return hr; 

	if (S_OK == hr) 
		return db_status = S_OKAY;
	return db_error (S_NOTFOUND, QTWINDOW); 	// nichts gefunden
}
#endif // _USE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Iterative Baumsuchroutine
static HRESULT qt_walk (
	double *win, QTSLOT *node, register QUADRANT *qd, short level, 
	FLAG comp, DB_ADDR *pDBA, QTWINDOWACTIONPROC action, UINT_PTR dwData)
{
QTSLOT noddat, *data;		/* neuer Knoten, nebst Pointer */
BOOL fFound = FALSE;
HRESULT hr = E_FAIL;
ErrCode RC;

	qd->w.qd_len /= 2;		/* Kantenlaenge halbieren */
	for (int i = 0; i < QDIM; ++i) {	/* fuer jeden Subwuerfel */
		pDBA -> rec_no = node->records[i];
	
	/* weiter im Baum */
		if (comp == NOCOMP ||
			(win[XMIN] <= qd->w.qd_x && win[YMIN] <= qd->w.qd_y && 
			 win[XMAX] > qd->w.qd_x+qd->w.qd_len && 
			 win[YMAX] > qd->w.qd_y+qd->w.qd_len)) 
		{
		/* Hyperwürfel vollständig in Window enthalten */
			if (pDBA->rec_no > 0) {
				DBASSERTHR(tdb_read (pDBA, (void **)&data));
				noddat = *data;

				RETURN_FAILED_HRESULT(hr = qt_walk (win, &noddat, qd, level+1, NOCOMP, pDBA, action, dwData));
				if (S_OK == hr) fFound = TRUE;		// propagate fFound

			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				fFound = TRUE;	 /* mind. ein Objekt gefunden */
				RETURN_FAILED_HRESULT(hr = qt_scan_no (win, pDBA, node->filled[i], action, dwData));
			}
		}  
		else if (win[XMIN] <= qd->w.qd_x+qd->w.qd_len && 
				 win[YMIN] <= qd->w.qd_y+qd->w.qd_len && 
				 win[XMAX] > qd->w.qd_x && win[YMAX] > qd->w.qd_y) 
		{
		/* Hyperwürfel teilweise in Window enthalten */
			if (pDBA->rec_no > 0) {
				DBASSERTHR(tdb_read (pDBA, (void **)&data));
				noddat = *data;
				
				RETURN_FAILED_HRESULT(hr = qt_walk (win, &noddat, qd, level+1, COMPARE, pDBA, action, dwData));
				if (S_OK == hr) fFound = TRUE;		// propagate fFound

			} else if (pDBA->rec_no < 0) {
			/* Blattknoten erreicht */
				RETURN_FAILED_HRESULT(hr = qt_scan_cmp (win, pDBA, node->filled[i], action, dwData));
				if (S_OK == hr) fFound = TRUE;
			}
		}
		{
		/* nächsten Hyperwürfel berechnen */
		register const QTCHGINFO *ci_p;
 
			if ((ci_p = &qt_chginfo[i])->sign > 0)
				qd->feld[ci_p->koord] += qd->feld[2];
			else
				qd->feld[ci_p->koord] -= qd->feld[2];
		}
	}
	qd->w.qd_len *= 2;		/* Kantenlaenge des Wuerfels wiederherstellen */
	db_status = S_OKAY;

	return fFound ? S_OK : S_FALSE;
}
 
/* Abtasten eines Blattknotens (ohne Containertest) */
static HRESULT qt_scan_no (
	double *win, DB_ADDR *pDBA, unsigned char filled, QTWINDOWACTIONPROC action, UINT_PTR dwData)
{
NODE *nd;
register QT_KEY_SLOT *ks;
register INT irc;
DB_ADDR dbadr(pDBA->db_no);
SUGGESTPAGE SE;
int iWork = working_file;
ErrCode RC;

	memset (&SE, 0, sizeof(SUGGESTPAGE));
	for (unsigned int ui = 0; ui < filled; ui++) {		/* fuer jeden gefuellten Slot */
	// jedesmal nachladen, da in qtwact eine andere Page druntergeladen werden kann

		DBASSERTHR(dio_get (-pDBA->rec_no, &nd, &SE));
		ks = &((QT_KEY_SLOT *)nd->nd_slots)[ui];

		dbadr.file_no = short(ks->ks_rec_no / MAXQTREC);
		dbadr.rec_no = ks->ks_rec_no % MAXQTREC;

		if ((irc = (*action)(&dbadr, win, dwData)) != S_OKAY)
			return HRESULT_FROM_ERRCODE(dberr (irc, USER_FUNC));
		working_file = iWork;

		++ks;
	}

	db_status = S_OKAY;
	return S_OK;
}
 
/* Abtasten eines Blattknotens (mit Containertest) */
static HRESULT qt_scan_cmp (
	double *win, DB_ADDR *pDBA, unsigned char filled, QTWINDOWACTIONPROC action, UINT_PTR dwData)
{
DB_ADDR dbadr(pDBA->db_no);
SUGGESTPAGE SE;
int iWork = working_file;
BOOL fFound = FALSE;
ErrCode RC;

	memset (&SE, 0, sizeof(SUGGESTPAGE));
	for (unsigned int ui = 0; ui < filled; ui++) {		/* fuer jeden gefuellten Slot */
	// jedesmal nachladen, da in qtwact eine andere Page druntergeladen werden kann
	NODE *nd;

		DBASSERTHR(dio_get (-pDBA->rec_no, &nd, &SE));
	
	QT_KEY_SLOT *ks = &((QT_KEY_SLOT *)nd->nd_slots)[ui];
				
		if (win[XMIN] <= ks->ks_key[0] && win[YMIN] <= ks->ks_key[1] &&
			win[XMAX] >= ks->ks_key[0] && win[YMAX] >= ks->ks_key[1]) 
		{
			fFound = TRUE;	 /* mind. ein Objekt gefunden */
			dbadr.file_no = short(ks->ks_rec_no / MAXQTREC);
			dbadr.rec_no = ks->ks_rec_no % MAXQTREC;

		long irc = (*action)(&dbadr, win, dwData);

			if (S_OKAY != irc)
				return HRESULT_FROM_ERRCODE(dberr (irc, USER_FUNC));
			working_file = iWork;
		}
	}

	db_status = S_OKAY;
	return fFound ? S_OK : S_FALSE;
}
