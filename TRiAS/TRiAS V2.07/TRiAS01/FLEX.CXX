/* Dynamische Felder fuer F77 Anwendungen                       */
/* File: FLEX.C                                                 */

#include "trias01p.hxx"

#include <flex.h>

#if !defined(_MSC_VER)
#define _MSC_VER 500
#endif

FLEX flexes[MAXFLEXES] = {
	{ NULL, 0, 0, FALSE, FALSE },          /*  1 */
	{ NULL, 0, 0, FALSE, FALSE },          /*  2 */
	{ NULL, 0, 0, FALSE, FALSE },          /*  3 */
	{ NULL, 0, 0, FALSE, FALSE },          /*  4 */
	{ NULL, 0, 0, FALSE, FALSE },          /*  5 */
	{ NULL, 0, 0, FALSE, FALSE },          /*  6 */
	{ NULL, 0, 0, FALSE, FALSE },          /*  7 */
	{ NULL, 0, 0, FALSE, FALSE },          /*  8 */
	{ NULL, 0, 0, FALSE, FALSE },          /*  9 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 10 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 11 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 12 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 13 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 14 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 15 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 16 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 17 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 18 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 19 */
	{ NULL, 0, 0, FALSE, FALSE },          /* 20 */
};


// static functions
int flcomp (const void FAR *prim, const void FAR *sec);

/* Initialisieren eines Flex's */
extern "C" long FUNCTYPE EXPORT01 feini_ (long *lnum)
// INT *lnum;      /* wenn gleich 0, dann neuen Flex anfordern */
{
register short num = (short)*lnum;
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
register FLEX __based((__segment)&flexes) *fl_p;
#else
register FLEX *fl_p;
#endif

	if (num < 0 || num >= MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_INI));
	if (num == 0) {
	/* Flex noch nicht existent */
	register int i;

		for (i = 0; i < MAXFLEXES; ++i) 
			if (flexes[i].used == FALSE) break;
		if (i == MAXFLEXES)
		/* Kein Flex mehr frei */
			return ((long)db_error (S_NOFLEX, FLEX_INI));
		*lnum = num = i + 1;
		flexes[i].used = TRUE;
	}
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
	fl_p = (FLEX __based((__segment)&flexes) *)&flexes[num-1];
#else
	fl_p = &flexes[num-1];
#endif

/* Freigeben des Speicherplatzes */
	if (fl_p->pFlex != NULL) {
#ifdef MSWIND
		GlobalUnlock (fl_p->handle);
		GlobalFree (fl_p->handle);
		fl_p->handle = 0;
#else
		free (fl_p->pFlex);
#endif
	}
	fl_p->pFlex = NULL;
/* Initialisieren der Laengenangaben */
	fl_p->len = 0;
	fl_p->max = 0;
	fl_p->iShrink = FALSE;

return ((long)(db_status = S_OKAY));
}

/* Setzen des Flags, welches die Verdichtbarkeit beschreibt */
extern "C" long FUNCTYPE EXPORT01 FlexShrink (short num, short newFlag) 
{
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
register FLEX __based((__segment)&flexes) *fl_p;
#else
register FLEX *fl_p;
#endif

	if (num <= 0 || num > MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_SHRINK));
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
	fl_p = (FLEX __based((__segment)&flexes) *)&flexes[num-1];
#else
	fl_p = &flexes[num-1];
#endif

// ShrinkFlag setzen
	fl_p -> iShrink = newFlag;

return ((long)(db_status = S_OKAY));
}


/* Freigeben eines Flex's */
extern "C" long FUNCTYPE EXPORT01 ferel_ (long *lnum) 
{
register short num = (short)*lnum;
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
register FLEX __based((__segment)&flexes) *fl_p;
#else
register FLEX *fl_p;
#endif

	if (num <= 0 || num > MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_RELEASE));
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
	fl_p = (FLEX __based((__segment)&flexes) *)&flexes[num-1];
#else
	fl_p = &flexes[num-1];
#endif

/* Freigeben des Speicherplatzes */
	if (fl_p->pFlex != NULL) {
#ifdef MSWIND
		GlobalUnlock (fl_p->handle);
		GlobalFree (fl_p->handle);
		fl_p->handle = 0;
#else
		free (fl_p->pFlex);
#endif
	}
	fl_p->pFlex = NULL;
/* Initialisieren der Laengenangaben */
	fl_p->len = 0;
	fl_p->max = 0;
	fl_p->used = FALSE;
	fl_p->iShrink = FALSE;

return ((long)(db_status = S_OKAY));
}

/* Einspeichern eines Elementes */
extern "C" long FUNCTYPE EXPORT01 feput_ (long *lnum, long *new_elem)
{
register short num = (short)*lnum;
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
register FLEX __based ((__segment)&flexes) *fl_p;
#else
register FLEX *fl_p;
#endif

	if (num <= 0 || num > MAXFLEXES) return ((long)db_error (S_BADFLEX, FLEX_PUT));
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
	fl_p = (FLEX __based((__segment)&flexes) *)&flexes[num-1];
#else
	fl_p = &flexes[num-1];
#endif
	if (fl_p->pFlex == NULL) {
#ifdef MSWIND
		fl_p -> handle = GlobalAlloc (GHND, FLEXSTEP*sizeof(long));
		if (fl_p -> handle == NULL)
			return ((long)db_error (S_NOMEMORY, FLEX_PUT));
		fl_p->pFlex = (long *)GlobalLock (fl_p -> handle);
#else
		fl_p->pFlex = calloc (FLEXSTEP, sizeof(long));
#endif
		if (fl_p->pFlex == NULL)
			return ((long)db_error (S_NOMEMORY, FLEX_PUT));
		fl_p->max = FLEXSTEP;
		fl_p->len = 0;
	} else if (fl_p->len == fl_p->max) {
	// Feld ist zu klein, evtl. vergrößern
/*		if (fl_p -> iShrink == TRUE) {
		// Feld wird zu klein, erst mal packen		#HK920205
		INT newLen;

			flqsrt_ (lnum);			// sortieren
			flredn_ (lnum, &newLen);	// und packen
		}
		if (fl_p->len == fl_p->max) 
*/		{
		// Feld ist immer noch zu klein
		unsigned long newSize = ((unsigned)fl_p->max * 2L)*sizeof(long);
#ifdef MSWIND
			GlobalUnlock (fl_p -> handle);
			fl_p -> handle = GlobalReAlloc (fl_p -> handle,
//				 (fl_p->max+FLEXSTEP)*sizeof(INT),
				 newSize,
				 GMEM_MOVEABLE);
			if (fl_p -> handle == NULL)
				return ((long)db_error (S_NOMEMORY, FLEX_PUT));
			fl_p->pFlex = (long *)GlobalLock (fl_p->handle);
#else
			fl_p->pFlex = realloc (fl_p->pFlex,
				(fl_p->max + FLEXSTEP)*sizeof(long));
#endif
			if (fl_p->pFlex == NULL)
				return ((long)db_error (S_NOMEMORY, FLEX_PUT));
//			fl_p->max += FLEXSTEP;
			fl_p->max = newSize/sizeof(long);
		}
	}
	fl_p->pFlex[fl_p->len++] = *new_elem;

	db_status = S_OKAY;
	
return ((long)fl_p->len);
}

/* Lesen eines Elementes aus einem Flex */
extern "C" long FUNCTYPE EXPORT01 feget_ (long *lnum, long *index, long *elem)
// INT *lnum;      /* Flexnummer */
// INT *index;     /* Flexindex */
// INT *elem;      /* Element hierhin schreiben */
{
register short num = (short)*lnum;
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
register FLEX __based((__segment)&flexes) *fl_p;
#else
register FLEX *fl_p;
#endif

	if (num <= 0 || num > MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_GET));
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
	fl_p = (FLEX __based((__segment)&flexes) *)&flexes[num-1];
#else
	fl_p = &flexes[num-1];
#endif
	if (fl_p->pFlex == NULL)
		return ((long)db_error (S_FLEXINI, FLEX_GET));
	if (*index <= 0 || *index > (long)fl_p->len) 
		return ((long)db_error (S_BADINDEX, FLEX_GET));
	*elem = fl_p->pFlex[*index-1];

return ((long)(db_status = S_OKAY));
}


/* Feststellen der Flexlaenge */
extern "C" long FUNCTYPE EXPORT01 felen_ (long *lnum, long *len)
// INT *lnum;      /* Flexnummer */
// INT *len;               /* Resultat: Flexlaenge */
{
register short num = (short)*lnum;
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
register FLEX __based((__segment)&flexes) *fl_p;
#else
register FLEX *fl_p;
#endif

	if (num <= 0 || num > MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_LEN));
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
	fl_p = (FLEX __based((__segment)&flexes) *)&flexes[num-1];
#else
	fl_p = &flexes[num-1];
#endif
	if (fl_p->pFlex == NULL) 
		*len = 0;
	else
		*len = fl_p->len;

return ((long)(db_status = S_OKAY));
}


/* Lesen eines Bereiches eines Flex's */
extern "C" long FUNCTYPE EXPORT01 feread_ (long *num, long *lbegin, long *llen, long *feld)
// INT *num;               /* Flexnummer */
// INT *lbegin;            /* Startindex */
// INT *llen;              /* Feldgroesse */
// INT *feld;              /* wohin zu schreiben */
{
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
register FLEX __based((__segment)&flexes) *fl_p;
#else
register FLEX *fl_p;
#endif
long begin = *lbegin, len = *llen;
long i;
long j;

	if (*num <= 0 || *num > MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_READ));
#if !defined(WIN32) && defined(_MSC_VER) && _MSC_VER >= 600
	fl_p = (FLEX __based((__segment)&flexes) *)&flexes[*num-1];
#else
	fl_p = &flexes[*num-1];
#endif
	if (fl_p->pFlex == NULL)
		return ((long)db_error (S_FLEXINI, FLEX_READ));
	if (begin > (long)fl_p->len || begin + len <= 0)
		return ((long)db_error (S_BADINDEX, FLEX_READ));

	for (i = (begin > 0) ? begin -1 : 0, j = 0; 
	     i < ((begin + len -1 <= (long)fl_p->len) ? begin + len -1 : 
						       (long)fl_p->len);
	     ++i, ++j) 
	/* Teilfeld umkopieren */
		feld[j] = fl_p->pFlex[i];
	/* Anzahl der real geschriebenen Feldelemente */
	*llen = j;
	
return ((long)(db_status = S_OKAY));
}

/* Schreiben eines Bereiches eines Flex's */
extern "C" long FUNCTYPE EXPORT01 fewrit_ (long *num, long *begin, long *len, long *feld)
// INT *num;               /* Flexnummer */
// INT *begin;             /* Startindex */
// INT *len;               /* Feldgroesse */
// INT *feld;              /* Quellfeld */
{
register FLEX *fl_p;
register long i, j;

	if (*num <= 0 || *num > MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_WRITE));
	fl_p = &flexes[*num-1];
	if (fl_p->pFlex == NULL)
		return ((long)db_error (S_FLEXINI, FLEX_WRITE));
	if (*begin > (long)fl_p->len || *begin + *len <= 0)
		return ((long)db_error (S_BADINDEX, FLEX_WRITE));

	for (i = (*begin > 0) ? *begin -1 : 0, j = 0;
	     i < ((*begin + *len -1 <= (long)fl_p->len) ? *begin + *len -1 : (long)fl_p->len);
	     ++i, ++j) 
	/* Teilfeld umkopieren */
		fl_p->pFlex[i] = feld[j];

	while (j < *len) 
	/* solange Feld noch nicht vollstaendig geschrieben */
		if (feput_ (num, &feld[j++]) < 0) return ((long)db_status);

	/* Anzahl der real geschriebenen Feldelemente */
	*len = j;
	
return ((long)(db_status = S_OKAY));
}

/* Sortieren eines der dynamischen Felder */
extern "C" long FUNCTYPE EXPORT01 flqsrt_ (long *num)
{
register FLEX *fl_p;

	if (*num <= 0 || *num > MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_QSRT));
	fl_p = &flexes[*num-1];
	if (fl_p->pFlex == NULL)
		return ((long)db_error (S_FLEXINI, FLEX_QSRT));

	qsort (fl_p->pFlex, (size_t)fl_p->len, sizeof(long), flcomp);

return ((long)(db_status = S_OKAY));
}

/* Vergleichsfunktion fuer QSORT */
int flcomp (const void *prim, const void *sec)
{
long tmp = *(long *)prim - *(long *)sec;

	if (tmp < 0) return -1;
	if (tmp > 0) return 1;
	return 0;
}


/* loeschen doppelter Feldelemente, setzt voraus, dass Feld sortiert ist */
extern "C" long FUNCTYPE EXPORT01 flredn_ (long *lnum, long *len)
// INT *lnum;       /* Feldnummer */
// INT *len;       /* Rueckgabewert: neue Feldlaenge */
{
short num = (short)*lnum;
register FLEX *fl_p;
register long __huge *pNew, __huge *old;
long __huge *top;
	
	if (num <= 0 || num > MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_REDN));
	fl_p = &flexes[num-1];
	if (fl_p->pFlex == NULL)
		return ((long)db_error (S_FLEXINI, FLEX_REDN));
	top = &fl_p->pFlex[fl_p->len];
	for (pNew = fl_p->pFlex, old = pNew + 1; old < top; ++old) {
		if (*pNew == *old) 
		/* gleiche Feldelemente */
			continue;       /* nur oberen Zeiger weitersetzen */
		else if (old - pNew > 1) 
		/* Elemente ungleich und kopieren */
			*++pNew = *old;
		else 
		/* Elemente ungleich aber nicht kopieren */
			++pNew;          /* naechstes Bezugselement */
	}
	*len = fl_p->len = pNew - fl_p->pFlex + 1;   /* neue Feldlaenge */

return ((long)(db_status = S_OKAY));
}

// Funktion liefert die Speicheradresse eines Flex's
extern "C" long FUNCTYPE EXPORT01 FlexAdr (short lnum, long **Address) 
{
	if (lnum <= 0 || lnum > MAXFLEXES) 
		return ((long)db_error (S_BADFLEX, FLEX_ADR));
	*Address = flexes[lnum-1].pFlex;

return ((long)(db_status = S_OKAY));
}
