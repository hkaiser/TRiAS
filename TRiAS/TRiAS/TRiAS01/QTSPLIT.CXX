/* Aufsplitten einer Node des Quadtrees in 4 Pages              */
/* File: QTSPLIT.C              last update: 11. Oktober 1989   */

#include "trias01p.hxx"

static short splitslot[((MAXPAGESIZE-PAGEHDRSIZE)/sizeof(QT_KEY_SLOT))+1];

int FUNCTYPE qt_split (QUADRANT *qd, short level)
// QUADRANT *qd;           /* aktueller Quadrant */
// short level;
{
	QTSLOT *dat;
	register QTSLOT *data;
	NODE *nd;
	REC_NO node;
	register int j, l;
	short i;
	register short cmp, filled;
	QTSLOT noddat;
	
	filled = d +1;
	/* neuen Node im HTree-File anlegen und einordnen */
	if (db_pzalloc (qtfile, &node) != S_OKAY)
		return (db_status);
	treedba.rec_no = cubparent[level];
	tdb_read (&treedba, (void **)&dat);
	(data = dat)->records[cubslots[level]] = node;
	data->filled[cubslots[level]] = 0;
	tdb_write (&treedba, NULL);
	
	for (l = 0; l < filled; ++l)
        /* welchem Subwuerfel gehoert slot an */
		splitslot[l] = quad (qd, (QTPOINT *)((char *)(buf+1)+l*slot_len), FALSE);
	
	for (cmp = splitslot[0], l = 1; l < filled; ++l)
		if (cmp != splitslot[l]) break;
        if (l == filled) {
			/* alle Slots gehoeren zu gleichem Subwuerfel */
			if (level == MAXTREELEVEL -1) return (dberr (S_QTLEVEL, QTSPLIT));
			cubparent[++level] = node;
			cubslots[level] = splitslot[0];
			quad (qd, (QTPOINT *)(buf+1), TRUE);
			return (qt_split (qd, level));
        }
		
        treedba.rec_no = node;
		if (tdb_read (&treedba, (void **)&dat) != S_OKAY) return (db_status);
        noddat = *dat;
        data = &noddat;
        for (j = 0; j < QDIM; ++j) {    /* Slots neu sortieren */
			data->filled[j] = 0;
			for (l = 0; l < filled; ++ l)
				if (splitslot[l] == j)
					break;
                if (l < filled) {
					/* wenn Elemente in diesen Hyperwuerfel fallen */
					REC_NO tmpnode;
					
					if (db_pzalloc (keyfile, &tmpnode) != S_OKAY)
						return (db_status);
					if (dio_get (tmpnode, (NODE FAR **)&nd) != S_OKAY) return (db_status);
					for ( ; l < filled; ++l) {
                        /* fuer alle alten Elemente (Slots) */
						if (splitslot[l] == j) {
							/* wenn Slot 'j' hierher gehoert */
							t_locate_slot ((INT *)((char *)(buf)+l*slot_len),
								(INT *)(nd->nd_slots),
								data->filled[j], &i);
							t_put_inline ((char *)(buf)+l*slot_len,
								nd->nd_slots,
								data->filled[j], i);
							++data->filled[j];
						}
					}
					dio_touch (tmpnode);
					data->records[j] = -tmpnode;
                } else
					data->records[j] = 0;
        }
        /*  neuen Node abspeichern */
        tdb_write (&treedba, (char *)data);
		
		return (db_status = S_OKAY);
}
