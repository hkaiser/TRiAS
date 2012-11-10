/* Routine liefert das naechste Geometrieobjekt (Kante, Punkt)  */
/* File: NGM.C                  last update: 3.August 1989      */

#include "trias01p.hxx"
#include "syncdb.hxx"

/* Aufruf: irc=ngmini(iz,ist,wfeld)
           irc=ngmc(iz,ist)
 
   Erstaufruf:      ngmini(...)
   weitere Aufrufe: ngmc(...)
 
   Rueckkehrparameter:
        iz:     siehe ist, I*4
        ist:     0 -- iz enthaelt naechste Kante    I*4
                -1 -- iz enthaelt naechsten Punkt
        irc:     0 -- nicht fertig                  I*4
                 1 -- fertig
 
   Aufrufparameter:
        wfeld:  zu untersuchendes Window (xmin, xmax, ymin, ymax),
                I*4 wfeld(4)
 
   Aufgabenstellung: 'ngmc' liefert das naechste Geometrieobjekt
                     (Kante, Masche, Punkt) aus den Listen KAL und SPL
 
*/

#define S_NOMORE 1
 
/* normale Variante (keine parallele Arbeit) */
 
extern "C" long FUNCTYPE EXPORT01 ngmini_ (HPROJECT hPr, REC_NO *recno, long *ist, long *w)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

register short irc;
 
	/* Erstaufruf */
	reslis_ ();     /* Zuruecksetzen der dynamischen Listen */
	if ((irc = hwindow (hPr, (WINDOW *)w, putlis_, KCONT)) != S_OKAY && irc != S_NOTFOUND)
	/* Kanten */
		return ((INT)db_status);
	if ((irc = qwindow (hPr, (WINDOW *)w, putlis_, KPKRD)) != S_OKAY && irc != S_NOTFOUND)
	/* Punkte */
		return ((INT)db_status);
 
return (ngmc_ (recno, ist));
}
 
 
extern "C" long FUNCTYPE EXPORT01 ngmc_ (REC_NO *recno, long *ist)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

short file_no;
 
    file_no = KAL;
    if (!getlis_ (&file_no, recno)) {
            *ist = 0L;
            return ((INT)S_OKAY);
    }
/*      file_no = MAL;
        if (!getlis_ (&file_no, recno)) {
                *ist = 0L;
                return ((INT)S_OKAY);
        }
*/
	file_no = POL;
	if (!getlis_ (&file_no, recno)) {
			*ist = -1L;
			return ((INT)S_OKAY);
	} else
			return ((INT)S_NOMORE);
}
