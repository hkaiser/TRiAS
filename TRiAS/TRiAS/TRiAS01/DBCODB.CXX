/* Basisfunktion: Berechnen des DB-Containers                   */
/* File: DBCODB.C                                               */

#include "trias01p.hxx"
#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/* Aufruf:      irc = dbcodb(cont)
                integer*4 irc,dbcodb,cont(4)

        liefert:
                irc  - Rueckkehrcode (eokay, ... )
                cont - zu berechnender Container

   Die Bestimmung des DB-Containers erfolgt durch Ablaufen der Geometrie-
   verwaltungsstrukturen (HTree, QTree).

 */

extern "C" 
long FUNCTYPE EXPORT01 dbcodb_ (HPROJECT hPr, long *pCont)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

CONTAINER *cont = (CONTAINER *)pCont;

	TX_ASSERT(TIsValidAddress (cont, sizeof(CONTAINER)));

	cont->x_min = cont->y_min = MAXKOORD;
	cont->x_max = cont->y_max = 0L;

CONNECTFILTEREX *pCF = NULL;

	if (SUCCEEDED(::GetConnectFilter(hPr, &pCF))) {
		cont->x_min = pCF -> m_dXMin;
		cont->x_max = pCF -> m_dXMax;
		cont->y_min = pCF -> m_dYMin;
		cont->y_max = pCF -> m_dYMax;
	}
	else {
		if (htcont (hPr, cont, KCONT) != S_OKAY) 
			return ((INT)db_status);
		if (qtcont (hPr, cont, KPKRD) != S_OKAY) 
			return ((INT)db_status);
	}

	if ((MAXKOORD == cont->x_min && 0L == cont->x_max) || 
		(MAXKOORD == cont->y_min && 0L == cont->y_max)) 
	{
	// keine Objekte, also kein Container
		cont->x_min = cont->y_min = 0L;
		cont->x_max = cont->y_max = 0L;
		return (INT)(db_status = S_DUMMY);		// gültig, aber falsch
	}
	return ((INT)(db_status = S_OKAY));
}
