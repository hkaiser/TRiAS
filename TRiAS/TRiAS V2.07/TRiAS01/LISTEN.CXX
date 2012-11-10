/* Dynamische Listenverwaltung fuer Window                      */
/* File: LISTEN.C               last update: 22. November 1989  */

#include "trias01p.hxx"
 
#define MEMSTEP 50
#define S_NOMORE 1
 
#if defined(MSWIND)	// Variante fuer MS-Windows (tm)
 
static REC_NO *liskpl = (REC_NO *)NULL; /* Stuetzpunktliste */
static REC_NO *liskal = (REC_NO *)NULL; /* Kantenfolgeliste */
static REC_NO *lismal = (REC_NO *)NULL; /* Maschenliste */
static HGLOBAL hKpl = NULL;
static HGLOBAL hKal = NULL;
static HGLOBAL hMal = NULL;

static short kplsize = 0;       /* Groesse der Listen */
static short kalsize = 0;
static short malsize = 0;
 
/* Zeiger fuer Ein- und Ausgabe */
static short kplin = 0, kplout = 0;
static short kalin = 0, kalout = 0;
static short malin = 0, malout = 0;
 
/* Ruecksetzen der Listen */
 
extern "C" void __cdecl EXPORT01 reslis_ (void)
{
	if (hKpl != NULL) {
                GlobalFree (hKpl);
                kplsize = kplin = kplout = 0;
                hKpl = NULL;
        }
	if (hKal != NULL) {
                GlobalFree (hKal);
                kalsize = kalin = kalout = 0;
                hKal = NULL;
        }
	if (hMal != NULL) {
                GlobalFree (hMal);
                malsize = malin = malout = 0;
                hMal = NULL;
        }
}
 
 
/* Element in Listen einfuegen */       

extern "C" long __cdecl EXPORT01 putlis_ (DB_ADDR *dba, ...)
{
        switch ((int)dba->file_no) {
        case POL:
		if (hKpl == NULL) {
                        if ((hKpl = GlobalAlloc (GHND, 
						 MEMSTEP*sizeof(REC_NO))) == NULL)
                                return (dberr (S_NOMEMORY, PUTLIST));
                        kplsize = MEMSTEP;
                        kplin = kplout = 0;
                }
                if (kplin >= kplsize) {
                        if ((hKpl = GlobalReAlloc (hKpl, 
				(kplsize+MEMSTEP)*sizeof(REC_NO),
				GMEM_MOVEABLE)) == NULL)
                                return (dberr (S_NOMEMORY, PUTLIST));
			kplsize += MEMSTEP;
                }
		liskpl = (REC_NO *)GlobalLock (hKpl);
                liskpl[kplin++] = dba->rec_no;
		GlobalUnlock (hKpl);
                break;
 
        case KAL:
		if (hKal == NULL) {
                        if ((hKal = GlobalAlloc (GHND,
						 MEMSTEP*sizeof(REC_NO))) == NULL)
                                return (dberr (S_NOMEMORY, PUTLIST));
                        kalsize = MEMSTEP;
                        kalin = kalout = 0;
                }
                if (kalin >= kalsize) {
                        if ((hKal = GlobalReAlloc (hKal, 
				(kalsize+MEMSTEP)*sizeof(REC_NO),
				GMEM_MOVEABLE)) == NULL)
                                return (dberr (S_NOMEMORY, PUTLIST));   
			kalsize += MEMSTEP;
                }
		liskal = (REC_NO *)GlobalLock (hKal);
                liskal[kalin++] = dba->rec_no;
		GlobalUnlock (hKal);
                break;
 
        case MAL:
		if (hMal == NULL) {
                        if ((hMal = GlobalAlloc (GHND,
						 MEMSTEP*sizeof(REC_NO))) == NULL)
                                return (dberr (S_NOMEMORY, PUTLIST));
                        malsize = MEMSTEP;
                        malin = malout = 0;
                }
                if (malin >= malsize) {
                        if ((hMal = GlobalReAlloc (hMal, 
				(malsize+MEMSTEP)*sizeof(REC_NO),
				GMEM_MOVEABLE)) == NULL)
                                return (dberr (S_NOMEMORY, PUTLIST));   
			malsize += MEMSTEP;
                }
		lismal = (REC_NO *)GlobalLock (hMal);
                lismal[malin++] = dba->rec_no;
		GlobalUnlock (hMal);
                break;
 
        default:
                return (dberr (S_NOKEY, PUTLIST));
        }
 
return (db_status = S_OKAY);
}
 
 
/* naechstes Element aus Liste auslesen */

extern "C" int __cdecl EXPORT01 getlis_ (short *lon, long *rec_no)
{
        switch (*lon) {
        case POL:
                if (kplsize == 0) return (db_status = S_NOMORE);
                if (kplout >= kplin || kplout >= kplsize) {
                        kplout = kplin = 0;
                        GlobalFree (hKpl);
                        hKpl = NULL;
                        kplsize = 0;
                        return (db_status = S_NOMORE);
                }
		liskpl = (REC_NO *)GlobalLock (hKpl);
                *rec_no = liskpl[kplout++];
		GlobalUnlock (hKpl);
                return (db_status = S_OKAY);
 
        case KAL:
                if (kalsize == 0) return (db_status = S_NOMORE);
                if (kalout >= kalin || kalout >= kalsize) {
                        kalout = kalin = 0;
                        GlobalFree (hKal);
                        hKal = NULL;
                        kalsize = 0;
                        return (db_status = S_NOMORE);
                }
		liskal = (REC_NO *)GlobalLock (hKal);
                *rec_no = liskal[kalout++];
		GlobalFree (hKal);
                return (db_status = S_OKAY);
 
        case MAL:
                if (malsize == 0) return (db_status = S_NOMORE);
                if (malout >= malin || malout >= malsize) {
                        malout = malin = 0;
                        GlobalFree (hMal);
                        hMal = NULL;
                        malsize = 0;
                        return (db_status = S_NOMORE);
                }
		lismal = (REC_NO *)GlobalLock (hMal);
                *rec_no = lismal[kalout++];
		GlobalUnlock (hMal);
                return (db_status = S_OKAY);
 
        default:
                return (dberr (S_NOKEY, GETLIST));
        }
}

#else // MSWIND 
/* normale Variante */
 
static REC_NO *liskpl = (REC_NO *)NULL; /* Stuetzpunktliste */
static REC_NO *liskal = (REC_NO *)NULL; /* Kantenfolgeliste */
static REC_NO *lismal = (REC_NO *)NULL; /* Maschenliste */
 
static short kplsize = 0;       /* Groesse der Listen */
static short kalsize = 0;
static short malsize = 0;
 
/* Zeiger fuer Ein- und Ausgabe */
static short kplin = 0, kplout = 0;
static short kalin = 0, kalout = 0;
static short malin = 0, malout = 0;
 
/* Ruecksetzen der Listen */
 
void
reslis_ (void)
{
        if (liskpl != ((REC_NO *)NULL)) {
                free ((char *)liskpl);
                kplsize = kplin = kplout = 0;
                liskpl = (REC_NO *)NULL;
        }
        if (liskal != ((REC_NO *)NULL)) {
                free ((char *)liskal);
                kalsize = kalin = kalout = 0;
                liskal = (REC_NO *)NULL;
        }
        if (lismal != ((REC_NO *)NULL)) {
                free ((char *)lismal);
                malsize = malin = malout = 0;
                lismal = (REC_NO *)NULL;
        }
}
 
 
/* Element in Listen einfuegen */       
   
INT _cdecl
putlis_ (dba)
DB_ADDR *dba;
{
        switch ((int)dba->file_no) {
        case POL:
                if (liskpl == ((REC_NO *)NULL)) {
                        if ((liskpl = (REC_NO *)calloc (MEMSTEP, sizeof (REC_NO))) == ((REC_NO *)0))
                                return (dberr (S_NOMEMORY, PUTLIST));
                        kplsize = MEMSTEP;
                        kplin = kplout = 0;
                }
                if (kplin >= kplsize) {
                        if ((liskpl = (REC_NO *)realloc (liskpl, (kplsize += MEMSTEP)*sizeof (REC_NO))) == ((REC_NO *)0))
                                return (dberr (S_NOMEMORY, PUTLIST));
                }
                liskpl[kplin++] = dba->rec_no;
                break;
 
        case KAL:
                if (liskal == ((REC_NO *)NULL)) {
                        if ((liskal = (REC_NO *)calloc (MEMSTEP, sizeof (REC_NO))) == ((REC_NO *)0))
                                return (dberr (S_NOMEMORY, PUTLIST));
                        kalsize = MEMSTEP;
                        kalin = kalout = 0;
                }
                if (kalin >= kalsize) {
                        if ((liskal = (REC_NO *)realloc (liskal, (kalsize += MEMSTEP)*sizeof (REC_NO))) == ((REC_NO *)0))
                                return (dberr (S_NOMEMORY, PUTLIST));   
                }
                liskal[kalin++] = dba->rec_no;
                break;
 
        case MAL:
                if (lismal == ((REC_NO *)NULL)) {
                        if ((lismal = (REC_NO *)calloc (MEMSTEP, sizeof (REC_NO))) == ((REC_NO *)0))
                                return (dberr (S_NOMEMORY, PUTLIST));
                        malsize = MEMSTEP;
                        malin = malout = 0;
                }
                if (malin >= malsize) {
                        if ((lismal = (REC_NO *)realloc (lismal, (malsize += MEMSTEP)*sizeof (REC_NO))) == ((REC_NO *)0))
                                return (dberr (S_NOMEMORY, PUTLIST));   
                }
                lismal[malin++] = dba->rec_no;
                break;
 
        default:
                return (dberr (S_NOKEY, PUTLIST));
        }
 
return (db_status = S_OKAY);
}
 
 
/* naechstes Element aus Liste auslesen */
 
int _cdecl getlis_ (lon, rec_no)
short *lon;
long *rec_no;
{
        switch (*lon) {
        case POL:
                if (kplsize == 0) return (db_status = S_NOMORE);
                if (kplout >= kplin || kplout >= kplsize) {
                        kplout = kplin = 0;
                        free ((char *)liskpl);
                        liskpl = ((REC_NO *)NULL);
                        kplsize = 0;
                        return (db_status = S_NOMORE);
                }
                *rec_no = liskpl[kplout++];
                return (db_status = S_OKAY);
 
        case KAL:
                if (kalsize == 0) return (db_status = S_NOMORE);
                if (kalout >= kalin || kalout >= kalsize) {
                        kalout = kalin = 0;
                        free ((char *)liskal);
                        liskal = ((REC_NO *)NULL);
                        kalsize = 0;
                        return (db_status = S_NOMORE);
                }
                *rec_no = liskal[kalout++];
                return (db_status = S_OKAY);
 
        case MAL:
                if (malsize == 0) return (db_status = S_NOMORE);
                if (malout >= malin || malout >= malsize) {
                        malout = malin = 0;
                        free ((char *)lismal);
                        lismal = ((REC_NO *)NULL);
                        malsize = 0;
                        return (db_status = S_NOMORE);
                }
                *rec_no = lismal[kalout++];
                return (db_status = S_OKAY);
 
        default:
                return (dberr (S_NOKEY, GETLIST));
        }
}

#endif // MSWIND
