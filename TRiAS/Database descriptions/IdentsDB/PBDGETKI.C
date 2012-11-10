// Lesen und ausgeben der TXI-Datei aus einer PBD -----------------------------
// File: PBDGETKI.C

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dbtypes.h"
#include "errdef.h"
#include "idtdb.h"

static char *usage = "Verwendung: %s PBD-Name TXI-Datei.\n";

main (int argc, char *argv[])
{
register int dbnum;
register FILE *fpTXI;
DB_ADDR dbaMID, dbaMIF;
struct mid MIDSatz;
struct mif MIFSatz;
struct mid_001 MID001Satz;
struct mif_001 MIF001Satz;
char *pExt = NULL;

        if (argc < 3) {
                fprintf (stderr, usage, argv[0]);
                exit (1);
        }
        if ((fpTXI = fopen (argv[2], "w")) == NULL) {
                fprintf (stderr, "%s: Kann Ausgabedatei %s nicht eroeffnen.\n", argv[0], argv[2]);
                exit (3);
        }
	SetCopyrightFlag (FALSE);
	if (argc == 4) pExt = argv[3];
        if ((dbnum = z_open (argv[1], argv[1], "", pExt)) != S_OKAY) {
                fprintf (stderr, "%s: Kann DB %s nicht eroeffnen.\n", argv[0], argv[1]);
                exit (2);
        }

// ersten Satz finden
	err_install (S_NOTFOUND, E_IGNORE, NULL);
        dbaMID.file_no = MID;
	dbaMIF.file_no = MIF;
        if (z_keyfirst (&dbaMID, IDS) != S_OKAY) {
                fprintf (stderr, "%s: Kein Identifikator vorhanden\n.", argv[1]);
                z_close (dbnum);
                exit (0);
        }

// je nach Version, verschiedene Satztypen verwenden
	if (GetDBVersion() <= PBD030000001) {
		do {
			if (z_readrec (&dbaMID, &MID001Satz) != S_OKAY) {
	        	        fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
        	        	z_close (dbnum);
	                	exit (4);
			}
			dbaMIF.rec_no = MID001Satz.zntxti;
			MID001Satz.zntxti = 0;	// Stringende sicher ausnullen
			fprintf (fpTXI, "%08ld /*%-.16s*/%s",   MID001Satz.ids, 
							MID001Satz.ktexti,
							MID001Satz.texti);
			while (dbaMIF.rec_no != 0) {
			// Folges„tze ausgeben

				if (z_readrec (&dbaMIF, &MIF001Satz) != S_OKAY) {
					fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
					z_close (dbnum);
					exit (4);
				}
				dbaMIF.rec_no = MIF001Satz.ztxtif;
				MIF001Satz.ztxtif = 0;	// StringEnde sicher ausnullen
				fprintf (fpTXI, "\\\n%s", MIF001Satz.textif);
			}
			fprintf (fpTXI, "\n");
		} while (z_keynext (&dbaMID, IDS) == S_OKAY && z_readrec (&dbaMID, &MID001Satz) == S_OKAY);
	} else if (GetDBVersion() >= PBD030000002) {
	// Version mit langen Kurztexten
		do {
			if (z_readrec (&dbaMID, &MIDSatz) != S_OKAY) {
	        	        fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
        	        	z_close (dbnum);
	                	exit (4);
			}
			dbaMIF.rec_no = MIDSatz.zntxti;
			MIDSatz.zntxti = 0;	// Stringende sicher ausnullen
			fprintf (fpTXI, "%08ld /*%-.32s*/%s",   MIDSatz.ids, 
								MIDSatz.ktexti,
								MIDSatz.texti);
			while (dbaMIF.rec_no != 0) {
			// Folges„tze ausgeben

				if (z_readrec (&dbaMIF, &MIFSatz) != S_OKAY) {
					fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
					z_close (dbnum);
					exit (4);
				}
				dbaMIF.rec_no = MIFSatz.ztxtif;
				MIFSatz.ztxtif = 0;	// StringEnde sicher ausnullen
				fprintf (fpTXI, "\\\n%s", MIFSatz.textif);
			}
			fprintf (fpTXI, "\n");
		} while (z_keynext (&dbaMID, IDS) == S_OKAY && z_readrec (&dbaMID, &MIDSatz) == S_OKAY);
	}
	err_install (S_NOTFOUND, E_DEFAULT, NULL);
        z_close (dbnum);
        fclose (fpTXI);
        
exit (0);
}

