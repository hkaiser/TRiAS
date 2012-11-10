/* Nachbildung von LADR() und LREC() fuer ifnd/datver-Schnittstelle     */
/* File: LADRC.C                last update: 30. November 1989          */

#include "trias01p.hxx"
#include "syncdb.hxx"

/* Liefert letzen belegten Satz in DB-Datei */
extern "C" long FUNCTYPE EXPORT01 ladr_ (HPROJECT hPr, short *lon, BOOL fLast)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

//	return (pgzero[record_table[(short)*lon].rt_file].pz_next);
int num = (int)hPr -1;

	if (num < 0 || num >= MAXDB) {
		db_error (S_ACTIV, ZACTIV);
		return 0L;
	}

DBASE *pDB = &db_table[num];
int iFile = (pDB -> db_rtab)[(short)*lon].rt_file;
PGZERO *pZero = &(pDB -> db_pztab)[iFile];
INT lChain = pZero -> pz_dchain;
INT lNext = pZero -> pz_next-1;

	if (fLast) return lNext;

DB_ADDR dba (hPr);
char *ptr;

	dba.file_no = iFile;
	while (0 != lChain && lNext > 0) {
		--lNext;				// nur rückwärts zählen
		dba.rec_no = lChain;
		if (S_OKAY != tdb_read (&dba, (void **)&ptr))
			break;
		lChain = *((INT *)(ptr)+1);
	}

return lNext;
}
 
/* Liefert Slotlaenge in DB-Datei */
extern "C" long FUNCTYPE EXPORT01 lrec_ (short *lon)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

	return ((INT)file_table[record_table[(short)*lon].rt_file].ft_slsize/sizeof(INT));
}
