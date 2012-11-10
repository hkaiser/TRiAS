// Lesen und ausgeben der TXR-Datei aus einer PBD -----------------------------
// File: PBDGETKR.C

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dbtypes.h"
#include "errdef.h"
#include "idtdb.h"

static char *usage = "Verwendung: %s PBD-Name TXR-Datei.\n";

main (int argc, char *argv[])
{
register int dbnum;
register FILE *fpTXR;
DB_ADDR dbaMRL, dbaMRF;
struct mrl MRLSatz;
struct mrf MRFSatz;
// alte Version
struct mrl_001 MRL001Satz;
struct mrf_001 MRF001Satz;
char *pExt = NULL;

        if (argc < 3) {
                fprintf (stderr, usage, argv[0]);
                exit (1);
        }
        if ((fpTXR = fopen (argv[2], "w")) == NULL) {
                fprintf (stderr, "%s: Kann Ausgabedatei %s nicht eroeffnen.\n", argv[0], argv[2]);
                exit (3);
        }
	if (argc == 4) pExt = argv[3];
        if ((dbnum = z_open (argv[1], argv[1], "", pExt)) != S_OKAY) {
                fprintf (stderr, "%s: Kann DB %s nicht eroeffnen.\n", argv[0], argv[1]);
                exit (2);
        }

// ersten Satz finden
	err_install (S_NOTFOUND, E_IGNORE, NULL);
        dbaMRL.file_no = MRL;
	dbaMRF.file_no = MRF;
        if (z_keyfirst (&dbaMRL, PRIREL) != S_OKAY) {
                fprintf (stderr, "%s: Kein Relationscode vorhanden\n.", argv[1]);
                z_close (dbnum);
                exit (0);
        }

// Versionen unterscheiden
	if (GetDBVersion() <= PBD030000001) {
		do {
			if (z_readrec (&dbaMRL, &MRL001Satz) != S_OKAY) {
		                fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
        		        z_close (dbnum);
                		exit (4);
			}
			dbaMRF.rec_no = MRL001Satz.zntxtr;
			MRL001Satz.zntxtr = 0;	// Stringende sicher ausnullen
			fprintf (fpTXR, "%08ld %c /*%-.16s*/%s", MRL001Satz.prirel, 
								 MRL001Satz.reltyp,
								 MRL001Satz.ktextr,
								 MRL001Satz.textr);
			while (dbaMRF.rec_no != 0) {
			// Folges„tze ausgeben
	
				if (z_readrec (&dbaMRF, &MRF001Satz) != S_OKAY) {
					fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
					z_close (dbnum);
					exit (4);
				}
				dbaMRF.rec_no = MRF001Satz.ztxtrf;
				MRF001Satz.ztxtrf = 0;	// Stringende sicher ausnullen
				fprintf (fpTXR, "\\\n%s", MRF001Satz.textrf);
			}
			fprintf (fpTXR, "\n");
		} while (z_keynext (&dbaMRL, PRIREL) == S_OKAY && z_readrec (&dbaMRL, &MRL001Satz) == S_OKAY);
	} else if (GetDBVersion() >= PBD030000002) {
		do {
			if (z_readrec (&dbaMRL, &MRLSatz) != S_OKAY) {
		                fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
        		        z_close (dbnum);
                		exit (4);
			}
			dbaMRF.rec_no = MRLSatz.zntxtr;
			MRLSatz.zntxtr = 0;	// Stringende sicher ausnullen
			fprintf (fpTXR, "%08ld %c /*%-.16s*/%s", MRLSatz.prirel, 
								 MRLSatz.reltyp,
								 MRLSatz.ktextr,
								 MRLSatz.textr);
			while (dbaMRF.rec_no != 0) {
			// Folges„tze ausgeben
	
				if (z_readrec (&dbaMRF, &MRFSatz) != S_OKAY) {
					fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
					z_close (dbnum);
					exit (4);
				}
				dbaMRF.rec_no = MRFSatz.ztxtrf;
				MRFSatz.ztxtrf = 0;	// Stringende sicher ausnullen
				fprintf (fpTXR, "\\\n%s", MRFSatz.textrf);
			}
			fprintf (fpTXR, "\n");
		} while (z_keynext (&dbaMRL, PRIREL) == S_OKAY && z_readrec (&dbaMRL, &MRLSatz) == S_OKAY);
	}

	err_install (S_NOTFOUND, E_DEFAULT, NULL);
        z_close (dbnum);
        fclose (fpTXR);
        
exit (0);
}

