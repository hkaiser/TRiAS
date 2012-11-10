/* Fortranschnittstelle (UNIX) - Abschliessen einer Datenbasis  */
/* File: ZCLOSE_F.C             last update: 19 .Mai 1989       */

#include "trias01p.hxx"
 
#ifdef vms
#define zclose_ zclose
#endif

long FUNCTYPE EXPORT01 zclose_ (long *db_slot)
{
register short i;
register FILE_ENTRY *fe_p;

#ifndef MULTI_DB
        if (dbopen) {
#else
register DBASE *db_p;

        if (*db_slot < 0 || *db_slot >= MAXDB) 
		return (dberr (S_CLOSE, ZCLOSE_F));
        if ((db_p = &db_table[*db_slot])->db_name != NULL || db_p -> db_pIStorage != NULL) 
        {
        register DBASE *old_slot;

                old_slot = activate (db_p);
#endif
                db_flush (FLUSH_ACTDB);    /* alle Pages wegschreiben */
                for (i = 0, fe_p = file_table; i < size_ft; ++i, ++fe_p) {
                        if (fe_p->ft_status == OPEN)
                                file_close (fe_p);
                }
                db_pzflush (TRUE);  /* alle Page 0 wegschreiben */
                free ((char *)pgzero);  /* Page 0 freigeben */
                /* Tabellen Freigeben */
                if (file_table) {
                        free (file_table[0].ft_name);
                        free ((char *)file_table);
                }
                if (key_table) free ((char *)key_table);
                if (record_table) free ((char *)record_table);
                /* Schluesselsuchposition freigeben */
                if (parent) {
                        free ((char *)parent);
                        free ((char *)slots);
                }
#ifndef MULTI_DB
                dbopen = FALSE;
                db_free ();             /* Speicherseiten freigeben */
#else
        /* DB-slot freimachen */
                free (db_p->db_name);
                db_p->db_name = NULL;
                db_p->db_sft = 0;
                
        /* ueberpruefen ob noch eine DB aktiv ist */
                for (i = 0; i < MAXDB; ++i)
                        if (db_table[i].db_name != NULL) break;
                if (i == MAXDB) 
                /* keine DB mehr aktiv --> Speicherseiten freigeben */
                        db_free ();     /* Speicherplatz wieder freigeben */

                if (old_slot != db_p) activate (old_slot);
                else                  activate (NULL);
#endif
        } else 
                return (dberr (S_CLOSE, ZCLOSE_F));

 
return (db_status = S_OKAY);
}
 
