/* Suchen in einem QuadTree                                     */
/* File: QTSEARCH.C             last update: 11. Oktober 1989   */

#include "trias01p.hxx"

int FUNCTYPE qtsearch (REC_NO node, QUADRANT *quadleaf, register short level)
// REC_NO node;            /* REC_NO des naechsten HTree Eintrages */
// QUADRANT *quadleaf;     /* aktueller Hyperwuerfel */
// register short level;           /* Baumniveau */
{
	QTSLOT *data;
	REC_NO n_node;
	
	treedba.rec_no = node;
	cubparent[level] = node;
	if (tdb_read (&treedba, (void **)&data) != S_OKAY) return (db_status);
	n_node = data->records[cubslots[level] = quad (quadleaf, (QTPOINT *)GeoKey.ks_key, TRUE)];
	if (n_node > 0) {
        /* weiter im Baum */
		if (level == MAXTREELEVEL -1) return (dberr (S_QTLEVEL, QTSEARCH));
		if (qtsearch (n_node, quadleaf, level +1) != S_OKAY)
			return (db_status);
	} else {
        /* dieses Niveau ist eigentliches Keyfile */
		QTSLOT noddat;
		
		noddat = *data;
		if ((*qtaction)(-n_node, quadleaf, &noddat, level) != S_OKAY)
			return (db_status);
		treedba.rec_no = node;
		tdb_write (&treedba, (char *)&noddat);
	}
	
	return (db_status = S_OKAY);
}
