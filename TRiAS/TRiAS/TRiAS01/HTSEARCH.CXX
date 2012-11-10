/* Suchen in einem HexadezimalTree                              */
/* File: HTSEARCH.C             last update: 14. Juli 1989      */

#include "trias01p.hxx"

int FUNCTYPE htsearch (REC_NO node, HYPERCUBE *hcube, register short level)
{
HTSLOT *data;
REC_NO n_node;
 
        treedba.rec_no = node;
        cubparent[level] = node;
	if (tdb_read (&treedba, (void **)&data) != S_OKAY) return (db_status);
        n_node = data->records[cubslots[level] = cube (hcube, 
						  (CONTAINER *)GeoKey.ks_key, 
						  TRUE)];
        if (n_node > 0) {
        /* weiter im Baum */
                if (level == MAXTREELEVEL -1) 
			return (dberr (S_HTLEVEL, HTSEARCH));
                if (htsearch (n_node, hcube, level +1) != S_OKAY)
                        return (db_status);
        } else {
        /* dieses Niveau ist eigentliches Keyfile */
        HTSLOT noddat;
 
                noddat = *data;
		if ((*htaction)(-n_node, hcube, &noddat, level) != S_OKAY)
                        return (db_status);
                treedba.rec_no = node;
                tdb_write (&treedba, (char *)&noddat);
        }
 
return (db_status = S_OKAY);
}
