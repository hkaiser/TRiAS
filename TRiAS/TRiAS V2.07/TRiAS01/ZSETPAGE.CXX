/* Setzen der Anzahl der virtuell verwalteten Speicherpages     */
/* File: ZSETPAGE.C             last update: 5. Dezember 1989   */

#include "trias01p.hxx"

#include "syncdb.hxx"

extern "C" int FUNCTYPE EXPORT01 z_setpages (int num)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

#ifndef MULTI_DB
        if (dbopen) return (dberr (S_DBOPEN, ZSETP));
#else
register int i;

        for (i = 0; i < MAXDB; ++i)
                if (db_table[i].db_name || db_table[i].db_pIStorage) 
        		break;
        if (i != MAXDB) return (dberr (S_DBOPEN, ZSETP));
#endif  
        /* Einstellen der Pageanzahl */
        if (num < 2) no_of_pages = DEFPAGES;
        else no_of_pages = num;
#ifdef PAGEHASH
        /* Berechnen der Groesse der Hashtabelle */
        hashsize = prim (no_of_pages);
#endif
 
return (db_status = S_OKAY);
}

#ifdef PAGEHASH
int FUNCTYPE prim (int zahl)
// int zahl;       /* Berechnen der naechstfolgenden Primzahl */
{
register int i;
register int flag = 1;          /* ersten Durchlauf gewaehrleisten */
register int prim;

        for (prim = 4*zahl; flag; ++prim) {
        /* Weiterzaehlen */
                flag = 0;
                for (i = 2; i * i <= prim; ++i) 
                /* Testen ob Primzahl */
                        if (!(prim % i)) flag = 1;
        }
        
return (prim -1);
}
#endif
